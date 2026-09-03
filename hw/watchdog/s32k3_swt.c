/*
 * NXP S32K3xx Software Watchdog Timer (SWT) Emulation
 *
 * See s32k3_swt.h for the manual cross-reference (S32K3xx Reference Manual
 * Rev. 11, Chapter 66) and the list of modeling simplifications.
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
#include "system/watchdog.h"
#include "qom/object.h"
#include "s32k3_swt.h"

static S32K3SWTState *s32k3_swt_instances[S32K3_SWT_MAX_INSTANCES];

static int64_t s32k3_swt_counts_to_ns(uint32_t counts)
{
    return (int64_t)counts * 1000000000LL / S32K3_SWT_COUNTER_HZ;
}

static void s32k3_swt_update_irq(S32K3SWTState *s)
{
    qemu_set_irq(s->irq, !!(s->ir & S32K3_SWT_IR_TIF));
}

/* Recompute the live remaining-count value from the timer's expiry time.
 * Used both for CO readback (while WEN=0, per manual 66.6.7) and internally. */
static uint32_t s32k3_swt_remaining_counts(S32K3SWTState *s)
{
    int64_t now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);
    uint64_t expiry = timer_expire_time_ns(s->timer);
    int64_t remaining_ns;

    if (expiry == (uint64_t)-1) {
        return s->to; /* timer not armed */
    }
    remaining_ns = (int64_t)expiry - now;
    if (remaining_ns <= 0) {
        return 0;
    }
    return (uint32_t)(remaining_ns * S32K3_SWT_COUNTER_HZ / 1000000000);
}

static void s32k3_swt_rearm(S32K3SWTState *s)
{
    int64_t now = qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL);

    timer_mod(s->timer, now + s32k3_swt_counts_to_ns(s->to));
}

static void s32k3_swt_timeout(void *opaque)
{
    S32K3SWTState *s = opaque;

    if ((s->cr & S32K3_SWT_CR_ITR) && !s->timed_out_once) {
        /* Interrupt-then-reset mode: first timeout raises IRQ only. */
        s->timed_out_once = true;
        s->ir |= S32K3_SWT_IR_TIF;
        s32k3_swt_update_irq(s);
        s32k3_swt_rearm(s);
        return;
    }

    s->ir |= S32K3_SWT_IR_TIF;
    s32k3_swt_update_irq(s);
    qemu_log_mask(CPU_LOG_INT,
                  "s32k3_swt[%u]: watchdog timeout, performing configured "
                  "watchdog action\n", s->instance_id);
    watchdog_perform_action();
}

void s32k3_swt_trigger(uint32_t instance_id, Error **errp)
{
    S32K3SWTState *s;

    if (instance_id >= ARRAY_SIZE(s32k3_swt_instances) ||
        !(s = s32k3_swt_instances[instance_id])) {
        error_setg(errp, "S32K3 SWT instance %u is not available", instance_id);
        return;
    }

    /*
     * This is an explicit monitor test hook: arm the selected SWT with the
     * shortest possible timeout and bypass interrupt-then-reset mode so the
     * configured QEMU watchdog action is reached on this expiry.
     */
    s->to = 1;
    s->cr |= S32K3_SWT_CR_WEN;
    s->cr &= ~S32K3_SWT_CR_ITR;
    s->timed_out_once = false;
    timer_mod(s->timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL));
}

static void s32k3_swt_service(S32K3SWTState *s)
{
    s->timed_out_once = false;
    s32k3_swt_rearm(s);
}

static void s32k3_swt_do_reset(S32K3SWTState *s)
{
    s->cr = S32K3_SWT_CR_RESET;
    s->ir = 0;
    s->to = 0x320; /* manual 66.6.1 reset value: SWT_MIN_TO-derived default */
    s->wn = 0;
    s->co_latched = 0;
    s->sk = 0;
    s->service_seen_first = 0;
    s->timed_out_once = false;
    timer_del(s->timer);
}

static void s32k3_swt_reset(DeviceState *dev)
{
    S32K3SWTState *s = S32K3_SWT(dev);

    s32k3_swt_do_reset(s);
    s32k3_swt_update_irq(s);
}

static uint64_t s32k3_swt_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3SWTState *s = opaque;

    switch (addr) {
    case S32K3_SWT_CR:
        return s->cr;
    case S32K3_SWT_IR:
        return s->ir;
    case S32K3_SWT_TO:
        return s->to;
    case S32K3_SWT_WN:
        return s->wn;
    case S32K3_SWT_SR:
        return 0; /* WSC always reads 0 (manual 66.6.6) */
    case S32K3_SWT_CO:
        /* manual 66.6.7: CNT shows the live timer only while WEN=0; while
         * running it reads back 0. */
        if (s->cr & S32K3_SWT_CR_WEN) {
            return 0;
        }
        return s->co_latched;
    case S32K3_SWT_SK:
        return s->sk;
    case S32K3_SWT_RRR:
        return 0;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_swt[%u]: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", s->instance_id, addr);
        return 0;
    }
}

static void s32k3_swt_write(void *opaque, hwaddr addr, uint64_t val64,
                             unsigned size)
{
    S32K3SWTState *s = opaque;
    uint32_t val = val64;

    if ((s->cr & S32K3_SWT_CR_LOCKED) && addr != S32K3_SWT_SR &&
        addr != S32K3_SWT_IR && addr != S32K3_SWT_RRR) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_swt[%u]: write to offset 0x%" HWADDR_PRIx
                      " while locked (CR[HLK/SLK]), ignored\n",
                      s->instance_id, addr);
        return;
    }

    switch (addr) {
    case S32K3_SWT_CR: {
        bool wen_rising = !(s->cr & S32K3_SWT_CR_WEN) &&
                           (val & S32K3_SWT_CR_WEN);
        bool wen_falling = (s->cr & S32K3_SWT_CR_WEN) &&
                            !(val & S32K3_SWT_CR_WEN);

        /* HLK can only be cleared by reset; SLK only by the unlock
         * sequence (manual 66.6.2) - preserve both if already set. */
        val = (val & ~(S32K3_SWT_CR_HLK | S32K3_SWT_CR_SLK)) |
              (s->cr & (S32K3_SWT_CR_HLK | S32K3_SWT_CR_SLK));
        s->cr = val;

        if (wen_falling) {
            s->co_latched = s32k3_swt_remaining_counts(s);
            timer_del(s->timer);
        }
        if (wen_rising) {
            s->timed_out_once = false;
            s32k3_swt_rearm(s);
        }
        break;
    }
    case S32K3_SWT_IR:
        if (val & S32K3_SWT_IR_TIF) {
            s->ir &= ~S32K3_SWT_IR_TIF;
        }
        s32k3_swt_update_irq(s);
        break;
    case S32K3_SWT_TO:
        s->to = val;
        break;
    case S32K3_SWT_WN:
        s->wn = val;
        break;
    case S32K3_SWT_SR: {
        uint16_t wsc = val & 0xFFFF;

        if (((s->cr & S32K3_SWT_CR_SMD_MASK) >> S32K3_SWT_CR_SMD_SHIFT) == 1) {
            /* Keyed service mode: not modeled (manual 66.3.3). Accept any
             * two consecutive writes as a valid service. */
            qemu_log_mask(LOG_UNIMP,
                          "s32k3_swt[%u]: keyed service mode is not "
                          "modeled; treating write as a valid service\n",
                          s->instance_id);
            if (s->cr & S32K3_SWT_CR_WEN) {
                s32k3_swt_service(s);
            }
            break;
        }

        if (s->service_seen_first == 0) {
            if (wsc == S32K3_SWT_SERVICE_KEY1 || wsc == S32K3_SWT_UNLOCK_KEY1) {
                s->service_seen_first = wsc;
            }
        } else {
            uint16_t first = s->service_seen_first;

            s->service_seen_first = 0;
            if (first == S32K3_SWT_SERVICE_KEY1 &&
                wsc == S32K3_SWT_SERVICE_KEY2) {
                if (s->cr & S32K3_SWT_CR_WEN) {
                    s32k3_swt_service(s);
                }
            } else if (first == S32K3_SWT_UNLOCK_KEY1 &&
                       wsc == S32K3_SWT_UNLOCK_KEY2) {
                s->cr &= ~S32K3_SWT_CR_SLK;
            }
        }
        break;
    }
    case S32K3_SWT_CO:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_swt[%u]: CO is read-only\n", s->instance_id);
        break;
    case S32K3_SWT_SK:
        s->sk = val & 0xFFFF;
        break;
    case S32K3_SWT_RRR:
        if (val & BIT(0)) {
            /* Reset only the SWT (manual 66.6.9 / 66.3.7): reinitialize
             * this instance's logic without a full chip reset. */
            s32k3_swt_do_reset(s);
            s32k3_swt_update_irq(s);
        }
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_swt[%u]: write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n",
                      s->instance_id, addr, val);
        break;
    }
}

static const MemoryRegionOps s32k3_swt_ops = {
    .read = s32k3_swt_read,
    .write = s32k3_swt_write,
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

static void s32k3_swt_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3SWTState *s = S32K3_SWT(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_swt_ops, s,
                          TYPE_S32K3_SWT, S32K3_SWT_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);

    s->timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, s32k3_swt_timeout, s);
}

static void s32k3_swt_realize(DeviceState *dev, Error **errp)
{
    S32K3SWTState *s = S32K3_SWT(dev);

    if (s->instance_id >= ARRAY_SIZE(s32k3_swt_instances)) {
        error_setg(errp, "invalid S32K3 SWT instance id %u", s->instance_id);
        return;
    }
    s32k3_swt_instances[s->instance_id] = s;
    s32k3_swt_reset(dev);
}

static const Property s32k3_swt_properties[] = {
    DEFINE_PROP_UINT32("swt-id", S32K3SWTState, instance_id, 0),
};

static void s32k3_swt_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_swt_realize;
    device_class_set_props(dc, s32k3_swt_properties);
}

static const TypeInfo s32k3_swt_info = {
    .name = TYPE_S32K3_SWT,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3SWTState),
    .instance_init = s32k3_swt_instance_init,
    .class_init = s32k3_swt_class_init,
};

static void s32k3_swt_register_types(void)
{
    type_register_static(&s32k3_swt_info);
}

type_init(s32k3_swt_register_types)
