/*
 * NXP S32K3xx Enhanced Modular IO Subsystem (eMIOS) Emulation
 *
 * See s32k3_emios.h for the manual cross-reference (S32K3xx Reference
 * Manual Rev. 11, Chapter 63) and the list of modeling simplifications.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "hw/core/qdev-properties.h"
#include "hw/core/irq.h"
#include "qapi/error.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qemu/timer.h"
#include "qom/object.h"
#include "s32k3_emios.h"

static uint32_t s32k3_emios_bsl(uint32_t c)
{
    return (c & S32K3_EMIOS_C_BSL_MASK) >> S32K3_EMIOS_C_BSL_SHIFT;
}

static uint32_t s32k3_emios_mode(uint32_t c)
{
    return c & S32K3_EMIOS_C_MODE_MASK;
}

/* Which UC MODE values this model treats as "autonomous counter" modes -
 * see the scope note in s32k3_emios.h. Covers MC (top bits 001), MCB /
 * OPWFMB / OPWMCB (top bits 101), OPWMB (top bits 110), plus SAOC, DAOC
 * (both variants) and OPWMT explicitly. */
static bool s32k3_emios_mode_is_counted(uint32_t mode)
{
    switch (mode) {
    case S32K3_EMIOS_MODE_SAOC:
    case S32K3_EMIOS_MODE_DAOC_B:
    case S32K3_EMIOS_MODE_DAOC_AB:
    case S32K3_EMIOS_MODE_OPWMT:
        return true;
    default:
        break;
    }
    if ((mode & 0x70) == 0x20) {
        return true; /* MC family */
    }
    if ((mode & 0x70) == 0x50) {
        return true; /* MCB / OPWFMB / OPWMCB family */
    }
    if ((mode & 0x70) == 0x60) {
        return true; /* OPWMB family */
    }
    return false;
}

static bool s32k3_emios_chan_is_running(S32K3EmiosState *s,
                                          S32K3EmiosChannel *c)
{
    return !(s->mcr & S32K3_EMIOS_MCR_MDIS) &&
           (c->c & S32K3_EMIOS_C_UCPREN) &&
           s32k3_emios_bsl(c->c) == S32K3_EMIOS_C_BSL_INTERNAL &&
           s32k3_emios_mode_is_counted(s32k3_emios_mode(c->c));
}

/* Derived tick period: module clock divided by (global prescaler, if
 * enabled) * per-channel prescaler. See S32K3_EMIOS_MODULE_CLK_HZ scope
 * note re: assumed clock rate. */
static int64_t s32k3_emios_tick_ns(S32K3EmiosState *s, S32K3EmiosChannel *c)
{
    uint32_t ucpre = 1 + ((c->c & S32K3_EMIOS_C_UCPRE_MASK) >>
                          S32K3_EMIOS_C_UCPRE_SHIFT);
    uint32_t gpre = 1;
    int64_t ns;

    if (s->mcr & S32K3_EMIOS_MCR_GPREN) {
        gpre = 1 + ((s->mcr & S32K3_EMIOS_MCR_GPRE_MASK) >>
                    S32K3_EMIOS_MCR_GPRE_SHIFT);
    }
    ns = (int64_t)ucpre * gpre * 1000000000LL / S32K3_EMIOS_MODULE_CLK_HZ;
    return ns > 0 ? ns : 1;
}

static uint32_t s32k3_emios_period(S32K3EmiosChannel *c)
{
    uint32_t period = (c->a & S32K3_EMIOS_DATA_MASK) + 1;

    return period ? period : 1;
}

static uint32_t s32k3_emios_live_cnt(S32K3EmiosState *s, S32K3EmiosChannel *c)
{
    int64_t now, elapsed, tick_ns;
    uint64_t ticks;

    if (!s32k3_emios_chan_is_running(s, c)) {
        return c->cnt;
    }
    now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    elapsed = now - c->epoch_ns;
    if (elapsed < 0) {
        elapsed = 0;
    }
    tick_ns = s32k3_emios_tick_ns(s, c);
    ticks = elapsed / tick_ns;
    return (uint32_t)(ticks % s32k3_emios_period(c));
}

static void s32k3_emios_update_irq(S32K3EmiosState *s)
{
    bool level = false;

    for (int i = 0; i < S32K3_EMIOS_NUM_CHANNELS; i++) {
        S32K3EmiosChannel *c = &s->ch[i];

        if ((c->s & S32K3_EMIOS_S_FLAG) && (c->c & S32K3_EMIOS_C_FEN)) {
            level = true;
            break;
        }
    }
    qemu_set_irq(s->irq, level);
}

/* (Re)schedule chan->timer for the next A-match instant, or disarm it if
 * the channel is no longer in a counted configuration. */
static void s32k3_emios_rearm(S32K3EmiosChannel *c)
{
    S32K3EmiosState *s = c->owner;
    int64_t tick_ns, period_ns, now, elapsed, into_period, remaining;

    if (!s32k3_emios_chan_is_running(s, c)) {
        timer_del(c->timer);
        return;
    }
    tick_ns = s32k3_emios_tick_ns(s, c);
    period_ns = (int64_t)s32k3_emios_period(c) * tick_ns;
    now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    elapsed = now - c->epoch_ns;
    if (elapsed < 0) {
        elapsed = 0;
    }
    into_period = elapsed % period_ns;
    remaining = period_ns - into_period;
    timer_mod(c->timer, now + remaining);
}

static void s32k3_emios_match(void *opaque)
{
    S32K3EmiosChannel *c = opaque;
    S32K3EmiosState *s = c->owner;

    if (c->s & S32K3_EMIOS_S_FLAG) {
        c->s |= S32K3_EMIOS_S_OVR; /* previous match not yet acknowledged */
    }
    c->s |= S32K3_EMIOS_S_FLAG;
    /* Toggle the modeled output-pin-state bit on each match - a stand-in
     * for the real per-mode A/B output-compare flip-flop behavior (see
     * scope note: exact per-submode output waveform is not modeled). */
    c->s ^= S32K3_EMIOS_S_UCOUT;

    s32k3_emios_update_irq(s);
    s32k3_emios_rearm(c);
}

static uint64_t s32k3_emios_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3EmiosState *s = opaque;

    if (addr >= S32K3_EMIOS_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_emios[%u]: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", s->instance_id, addr);
        return 0;
    }

    if (addr < S32K3_EMIOS_UC_BASE) {
        switch (addr) {
        case S32K3_EMIOS_MCR:
            return s->mcr;
        case S32K3_EMIOS_GFLAG: {
            uint32_t gflag = 0;

            for (int i = 0; i < S32K3_EMIOS_NUM_CHANNELS; i++) {
                if (s->ch[i].s & S32K3_EMIOS_S_FLAG) {
                    gflag |= BIT(i);
                }
            }
            return gflag;
        }
        case S32K3_EMIOS_OUDIS:
            return s->oudis;
        case S32K3_EMIOS_UCDIS:
            return s->ucdis;
        default:
            return 0;
        }
    }

    int idx = (addr - S32K3_EMIOS_UC_BASE) / S32K3_EMIOS_UC_STRIDE;
    int sub = (addr - S32K3_EMIOS_UC_BASE) % S32K3_EMIOS_UC_STRIDE;
    S32K3EmiosChannel *c = &s->ch[idx];

    switch (sub) {
    case S32K3_EMIOS_A_OFF:
        return c->a;
    case S32K3_EMIOS_B_OFF:
        return c->b;
    case S32K3_EMIOS_CNT_OFF:
        return s32k3_emios_live_cnt(s, c);
    case S32K3_EMIOS_C_OFF:
        return c->c;
    case S32K3_EMIOS_S_OFF:
        return c->s;
    case S32K3_EMIOS_ALTA_OFF:
        return c->alta;
    case S32K3_EMIOS_C2_OFF:
        return c->c2;
    default:
        return 0;
    }
}

static void s32k3_emios_write(void *opaque, hwaddr addr, uint64_t val64,
                                unsigned size)
{
    S32K3EmiosState *s = opaque;
    uint32_t val = val64;

    if (addr >= S32K3_EMIOS_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_emios[%u]: write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n",
                      s->instance_id, addr, val);
        return;
    }

    if (addr < S32K3_EMIOS_UC_BASE) {
        switch (addr) {
        case S32K3_EMIOS_MCR:
            s->mcr = val;
            /* Global prescaler / MDIS affects every running channel's
             * tick rate - rearm them all against the new configuration. */
            for (int i = 0; i < S32K3_EMIOS_NUM_CHANNELS; i++) {
                s32k3_emios_rearm(&s->ch[i]);
            }
            break;
        case S32K3_EMIOS_GFLAG:
            qemu_log_mask(LOG_GUEST_ERROR,
                          "s32k3_emios[%u]: GFLAG is read-only\n",
                          s->instance_id);
            break;
        case S32K3_EMIOS_OUDIS:
            s->oudis = val;
            break;
        case S32K3_EMIOS_UCDIS:
            s->ucdis = val;
            break;
        default:
            break;
        }
        return;
    }

    int idx = (addr - S32K3_EMIOS_UC_BASE) / S32K3_EMIOS_UC_STRIDE;
    int sub = (addr - S32K3_EMIOS_UC_BASE) % S32K3_EMIOS_UC_STRIDE;
    S32K3EmiosChannel *c = &s->ch[idx];

    switch (sub) {
    case S32K3_EMIOS_A_OFF:
        /* Refresh the frozen CNT snapshot before changing the period, so
         * a channel that isn't currently running doesn't silently jump. */
        c->a = val & S32K3_EMIOS_DATA_MASK;
        s32k3_emios_rearm(c);
        break;
    case S32K3_EMIOS_B_OFF:
        /* Stored for firmware readback; this simplified model does not
         * separately time a B-match event (see header scope note). */
        c->b = val & S32K3_EMIOS_DATA_MASK;
        break;
    case S32K3_EMIOS_CNT_OFF:
        c->cnt = val & S32K3_EMIOS_DATA_MASK;
        c->epoch_ns = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) -
                      (int64_t)c->cnt * s32k3_emios_tick_ns(s, c);
        s32k3_emios_rearm(c);
        break;
    case S32K3_EMIOS_C_OFF: {
        bool was_running = s32k3_emios_chan_is_running(s, c);

        /* FORCMA/FORCMB are pulses that always read back 0 (manual
         * 63.8.6.9); MODE changes always take effect immediately in this
         * model (the manual's "go through GPIO mode first" software
         * requirement is a firmware discipline note, not something this
         * model needs to enforce). */
        val &= ~(S32K3_EMIOS_C_FORCMA | S32K3_EMIOS_C_FORCMB);
        c->c = val;

        /* Mirror UCPRE's two bits into C2[UCEXTPRE] low bits per manual
         * 63.8.6.9 note. */
        c->c2 = (c->c2 & ~0x3u) |
                ((val & S32K3_EMIOS_C_UCPRE_MASK) >>
                 S32K3_EMIOS_C_UCPRE_SHIFT);

        bool now_running = s32k3_emios_chan_is_running(s, c);

        if (now_running && !was_running) {
            c->cnt = 0;
            c->epoch_ns = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
        } else if (!now_running && was_running) {
            c->cnt = s32k3_emios_live_cnt(s, c);
        }
        s32k3_emios_rearm(c);
        s32k3_emios_update_irq(s);
        break;
    }
    case S32K3_EMIOS_S_OFF:
        /* FLAG/OVR/OVFL are W1C; UCIN/UCOUT are read-only status bits. */
        c->s &= ~(val & (S32K3_EMIOS_S_FLAG | S32K3_EMIOS_S_OVR |
                         S32K3_EMIOS_S_OVFL));
        s32k3_emios_update_irq(s);
        break;
    case S32K3_EMIOS_ALTA_OFF:
        c->alta = val & S32K3_EMIOS_DATA_MASK;
        break;
    case S32K3_EMIOS_C2_OFF:
        c->c2 = val;
        break;
    default:
        break;
    }
}

static const MemoryRegionOps s32k3_emios_ops = {
    .read = s32k3_emios_read,
    .write = s32k3_emios_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void s32k3_emios_reset(DeviceState *dev)
{
    S32K3EmiosState *s = S32K3_EMIOS(dev);

    s->mcr = 0;
    s->oudis = 0;
    s->ucdis = 0;

    for (int i = 0; i < S32K3_EMIOS_NUM_CHANNELS; i++) {
        S32K3EmiosChannel *c = &s->ch[i];

        c->a = 0;
        c->b = 0;
        c->cnt = 0;
        c->c = 0;
        c->s = 0; /* UCIN's true reset value is undefined (manual 63.8.6.10
                   * footnote) - no modeled pin, so we settle it at 0. */
        c->alta = 0;
        c->c2 = 0;
        c->epoch_ns = 0;
        timer_del(c->timer);
    }
    s32k3_emios_update_irq(s);
}

static void s32k3_emios_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3EmiosState *s = S32K3_EMIOS(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_emios_ops, s,
                          TYPE_S32K3_EMIOS, S32K3_EMIOS_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);

    for (int i = 0; i < S32K3_EMIOS_NUM_CHANNELS; i++) {
        s->ch[i].owner = s;
        s->ch[i].index = i;
        s->ch[i].timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, s32k3_emios_match,
                                       &s->ch[i]);
    }
}

static void s32k3_emios_realize(DeviceState *dev, Error **errp)
{
    s32k3_emios_reset(dev);
}

static const Property s32k3_emios_properties[] = {
    DEFINE_PROP_UINT32("emios-id", S32K3EmiosState, instance_id, 0),
};

static void s32k3_emios_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_emios_realize;
    device_class_set_props(dc, s32k3_emios_properties);
}

static const TypeInfo s32k3_emios_info = {
    .name = TYPE_S32K3_EMIOS,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3EmiosState),
    .instance_init = s32k3_emios_instance_init,
    .class_init = s32k3_emios_class_init,
};

static void s32k3_emios_register_types(void)
{
    type_register_static(&s32k3_emios_info);
}

type_init(s32k3_emios_register_types)
