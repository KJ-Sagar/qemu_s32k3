/*
 * NXP S32K3xx Synchronous Audio Interface (SAI) - Chapter 74
 *
 * See s32k3_sai.h for scope notes and modeling simplifications.
 */
#include "qemu/osdep.h"
#include "hw/audio/s32k3_sai.h"
#include "hw/core/irq.h"
#include "hw/core/qdev-properties.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qemu/timer.h"
#include "migration/vmstate.h"

static uint32_t sai_fifo_count(const S32K3SaiFifo *f)
{
    return (f->wp - f->rp) & (2 * S32K3_SAI_FIFO_DEPTH - 1);
}

static bool sai_fifo_push(S32K3SaiFifo *f, uint32_t data)
{
    if (sai_fifo_count(f) >= S32K3_SAI_FIFO_DEPTH) {
        return false; /* full */
    }
    f->data[f->wp % S32K3_SAI_FIFO_DEPTH] = data;
    f->wp = (f->wp + 1) & (2 * S32K3_SAI_FIFO_DEPTH - 1);
    return true;
}

static bool sai_fifo_pop(S32K3SaiFifo *f, uint32_t *data)
{
    if (sai_fifo_count(f) == 0) {
        return false; /* empty */
    }
    *data = f->data[f->rp % S32K3_SAI_FIFO_DEPTH];
    f->rp = (f->rp + 1) & (2 * S32K3_SAI_FIFO_DEPTH - 1);
    return true;
}

static void sai_fifo_reset(S32K3SaiFifo *f)
{
    f->wp = 0;
    f->rp = 0;
}

static void sai_update_irq(S32K3SaiState *s)
{
    bool level = false;

    if ((s->tcsr & S32K3_SAI_XCSR_WSF) && (s->tcsr & S32K3_SAI_XCSR_WSIE)) {
        level = true;
    }
    if ((s->tcsr & S32K3_SAI_XCSR_SEF) && (s->tcsr & S32K3_SAI_XCSR_SEIE)) {
        level = true;
    }
    if ((s->tcsr & S32K3_SAI_XCSR_FEF) && (s->tcsr & S32K3_SAI_XCSR_FEIE)) {
        level = true;
    }
    if ((s->tcsr & S32K3_SAI_XCSR_FWF) && (s->tcsr & S32K3_SAI_XCSR_FWIE)) {
        level = true;
    }
    if ((s->tcsr & S32K3_SAI_XCSR_FRF) && (s->tcsr & S32K3_SAI_XCSR_FRIE)) {
        level = true;
    }
    if ((s->rcsr & S32K3_SAI_XCSR_WSF) && (s->rcsr & S32K3_SAI_XCSR_WSIE)) {
        level = true;
    }
    if ((s->rcsr & S32K3_SAI_XCSR_SEF) && (s->rcsr & S32K3_SAI_XCSR_SEIE)) {
        level = true;
    }
    if ((s->rcsr & S32K3_SAI_XCSR_FEF) && (s->rcsr & S32K3_SAI_XCSR_FEIE)) {
        level = true;
    }
    if ((s->rcsr & S32K3_SAI_XCSR_FWF) && (s->rcsr & S32K3_SAI_XCSR_FWIE)) {
        level = true;
    }
    if ((s->rcsr & S32K3_SAI_XCSR_FRF) && (s->rcsr & S32K3_SAI_XCSR_FRIE)) {
        level = true;
    }

    qemu_set_irq(s->irq, level);
}

/* Recompute the live (non-latched) TX status flags FWF/FRF from channel 0's
 * FIFO occupancy. Channel 0 is treated as "the" channel for aggregate
 * status purposes, since real chip configurations for this SoC only wire
 * up a single SAI data line (see header scope notes). */
static void sai_update_tx_flags(S32K3SaiState *s)
{
    uint32_t count = sai_fifo_count(&s->tx_fifo[0]);
    uint32_t watermark = s->tcr1 & S32K3_SAI_XCR1_TFW_MASK;

    s->tcsr &= ~(S32K3_SAI_XCSR_FWF | S32K3_SAI_XCSR_FRF);
    if (s->tcsr & S32K3_SAI_XCSR_TE_RE) {
        if (count == 0) {
            s->tcsr |= S32K3_SAI_XCSR_FWF;
        }
        if (count <= watermark) {
            s->tcsr |= S32K3_SAI_XCSR_FRF;
        }
    }
}

static void sai_update_rx_flags(S32K3SaiState *s)
{
    /* RX FIFO is never populated in this model (no external audio source
     * is wired up), so it is always "empty" while enabled - matching real
     * hardware behavior on an idle/unconnected input. */
    s->rcsr &= ~(S32K3_SAI_XCSR_FWF | S32K3_SAI_XCSR_FRF);
    if (s->rcsr & S32K3_SAI_XCSR_TE_RE) {
        s->rcsr |= S32K3_SAI_XCSR_FWF;
    }
}

static uint64_t sai_word_period_ns(S32K3SaiState *s)
{
    uint32_t div = s->tcr2 & S32K3_SAI_XCR2_DIV_MASK;
    uint64_t bitclk_div = (uint64_t)(div + 1) * 2;
    uint64_t bits_per_word = 32;

    return (uint64_t)NANOSECONDS_PER_SECOND * bitclk_div * bits_per_word /
           S32K3_SAI_AUDIO_MCLK_HZ;
}

static void sai_tx_drain_tick(void *opaque)
{
    S32K3SaiState *s = opaque;
    uint32_t dummy;

    if (!(s->tcsr & S32K3_SAI_XCSR_TE_RE)) {
        return; /* transmitter disabled; timer left unscheduled */
    }

    if (!sai_fifo_pop(&s->tx_fifo[0], &dummy)) {
        /* Underflow: nothing to send. */
        s->tcsr |= S32K3_SAI_XCSR_FEF;
        sai_update_tx_flags(s);
        sai_update_irq(s);
        return; /* stay idle until a TDR write re-arms the timer */
    }

    sai_update_tx_flags(s);
    sai_update_irq(s);
    timer_mod(s->tx_drain_timer,
              qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + sai_word_period_ns(s));
}

static void sai_tx_arm_if_needed(S32K3SaiState *s)
{
    if ((s->tcsr & S32K3_SAI_XCSR_TE_RE) &&
        sai_fifo_count(&s->tx_fifo[0]) > 0 &&
        !timer_pending(s->tx_drain_timer)) {
        timer_mod(s->tx_drain_timer,
                  qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) + sai_word_period_ns(s));
    }
}

static uint32_t sai_tfr_read(S32K3SaiState *s, int line)
{
    S32K3SaiFifo *f = &s->tx_fifo[line];

    return ((uint32_t)f->wp << 16) | (uint32_t)f->rp;
}

static uint32_t sai_rfr_read(S32K3SaiState *s, int line)
{
    S32K3SaiFifo *f = &s->rx_fifo[line];

    return ((uint32_t)f->wp << 16) | (uint32_t)f->rp;
}

static uint64_t s32k3_sai_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3SaiState *s = opaque;

    if (addr >= S32K3_SAI_TDR0 && addr <= S32K3_SAI_TDR3) {
        /* TDR is documented write-only for data; reads return 0. */
        return 0;
    }
    if (addr >= S32K3_SAI_TFR0 && addr <= S32K3_SAI_TFR3) {
        return sai_tfr_read(s, (addr - S32K3_SAI_TFR0) / 4);
    }
    if (addr >= S32K3_SAI_RDR0 && addr <= S32K3_SAI_RDR3) {
        return 0; /* RX FIFO always empty in this model; see header notes */
    }
    if (addr >= S32K3_SAI_RFR0 && addr <= S32K3_SAI_RFR3) {
        return sai_rfr_read(s, (addr - S32K3_SAI_RFR0) / 4);
    }

    switch (addr) {
    case S32K3_SAI_VERID:
        return S32K3_SAI_VERID_RESET;
    case S32K3_SAI_PARAM:
        return s->param_reset;
    case S32K3_SAI_TCSR:
        return s->tcsr;
    case S32K3_SAI_TCR1:
        return s->tcr1;
    case S32K3_SAI_TCR2:
        return s->tcr2;
    case S32K3_SAI_TCR3:
        return s->tcr3;
    case S32K3_SAI_TCR4:
        return s->tcr4;
    case S32K3_SAI_TCR5:
        return s->tcr5;
    case S32K3_SAI_TMR:
        return s->tmr;
    case S32K3_SAI_RCSR:
        return s->rcsr;
    case S32K3_SAI_RCR1:
        return s->rcr1;
    case S32K3_SAI_RCR2:
        return s->rcr2;
    case S32K3_SAI_RCR3:
        return s->rcr3;
    case S32K3_SAI_RCR4:
        return s->rcr4;
    case S32K3_SAI_RCR5:
        return s->rcr5;
    case S32K3_SAI_RMR:
        return s->rmr;
    default:
        qemu_log_mask(LOG_GUEST_ERROR, "s32k3_sai: bad read offset 0x%"
                      HWADDR_PRIx "\n", addr);
        return 0;
    }
}

static void s32k3_sai_write(void *opaque, hwaddr addr, uint64_t val,
                             unsigned size)
{
    S32K3SaiState *s = opaque;

    if (addr >= S32K3_SAI_TDR0 && addr <= S32K3_SAI_TDR3) {
        int line = (addr - S32K3_SAI_TDR0) / 4;
        if (!sai_fifo_push(&s->tx_fifo[line], (uint32_t)val)) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "s32k3_sai: TDR%d write while FIFO full\n", line);
        }
        sai_update_tx_flags(s);
        sai_tx_arm_if_needed(s);
        sai_update_irq(s);
        return;
    }
    if (addr >= S32K3_SAI_TFR0 && addr <= S32K3_SAI_TFR3) {
        return; /* read-only */
    }
    if (addr >= S32K3_SAI_RDR0 && addr <= S32K3_SAI_RDR3) {
        return; /* read-only */
    }
    if (addr >= S32K3_SAI_RFR0 && addr <= S32K3_SAI_RFR3) {
        return; /* read-only */
    }

    switch (addr) {
    case S32K3_SAI_VERID:
    case S32K3_SAI_PARAM:
        break; /* read-only */
    case S32K3_SAI_TCSR: {
        uint32_t old_te = s->tcsr & S32K3_SAI_XCSR_TE_RE;

        s->tcsr = (s->tcsr & ~0x300003FFu) | (val & 0x300003FFu);
        /* TE / DBGE / SR persist as written */
        s->tcsr = (s->tcsr & ~(S32K3_SAI_XCSR_TE_RE | S32K3_SAI_XCSR_DBGE |
                                S32K3_SAI_XCSR_SR)) |
                  (val & (S32K3_SAI_XCSR_TE_RE | S32K3_SAI_XCSR_DBGE |
                          S32K3_SAI_XCSR_SR));
        /* BCE auto-follows TE */
        if (s->tcsr & S32K3_SAI_XCSR_TE_RE) {
            s->tcsr |= S32K3_SAI_XCSR_BCE;
        } else if (!(val & S32K3_SAI_XCSR_BCE)) {
            s->tcsr &= ~S32K3_SAI_XCSR_BCE;
        }
        /* W1C flags */
        s->tcsr &= ~(val & S32K3_SAI_XCSR_W1C_MASK);
        /* FIFO reset pulse (self-clearing) */
        if (val & S32K3_SAI_XCSR_FR) {
            sai_fifo_reset(&s->tx_fifo[0]);
        }
        /* Software reset also clears FIFO pointers per manual */
        if (val & S32K3_SAI_XCSR_SR) {
            sai_fifo_reset(&s->tx_fifo[0]);
        }
        if (!old_te && (s->tcsr & S32K3_SAI_XCSR_TE_RE)) {
            sai_tx_arm_if_needed(s);
        }
        sai_update_tx_flags(s);
        sai_update_irq(s);
        break;
    }
    case S32K3_SAI_TCR1:
        s->tcr1 = val & S32K3_SAI_XCR1_TFW_MASK;
        sai_update_tx_flags(s);
        break;
    case S32K3_SAI_TCR2:
        s->tcr2 = val;
        break;
    case S32K3_SAI_TCR3:
        s->tcr3 = val;
        break;
    case S32K3_SAI_TCR4:
        s->tcr4 = val;
        break;
    case S32K3_SAI_TCR5:
        s->tcr5 = val;
        break;
    case S32K3_SAI_TMR:
        s->tmr = val & 0xFFFF;
        break;
    case S32K3_SAI_RCSR: {
        s->rcsr = (s->rcsr & ~(S32K3_SAI_XCSR_TE_RE | S32K3_SAI_XCSR_DBGE |
                                S32K3_SAI_XCSR_SR)) |
                  (val & (S32K3_SAI_XCSR_TE_RE | S32K3_SAI_XCSR_DBGE |
                          S32K3_SAI_XCSR_SR));
        s->rcsr = (s->rcsr & ~0x00001FFFu) | (val & 0x00001FFFu);
        s->rcsr &= ~(val & S32K3_SAI_XCSR_W1C_MASK);
        if (val & S32K3_SAI_XCSR_FR) {
            sai_fifo_reset(&s->rx_fifo[0]);
        }
        if (val & S32K3_SAI_XCSR_SR) {
            sai_fifo_reset(&s->rx_fifo[0]);
        }
        sai_update_rx_flags(s);
        sai_update_irq(s);
        break;
    }
    case S32K3_SAI_RCR1:
        s->rcr1 = val & S32K3_SAI_XCR1_TFW_MASK;
        break;
    case S32K3_SAI_RCR2:
        s->rcr2 = val;
        break;
    case S32K3_SAI_RCR3:
        s->rcr3 = val;
        break;
    case S32K3_SAI_RCR4:
        s->rcr4 = val;
        break;
    case S32K3_SAI_RCR5:
        s->rcr5 = val;
        break;
    case S32K3_SAI_RMR:
        s->rmr = val & 0xFFFF;
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR, "s32k3_sai: bad write offset 0x%"
                      HWADDR_PRIx "\n", addr);
        break;
    }
}

static const MemoryRegionOps s32k3_sai_ops = {
    .read = s32k3_sai_read,
    .write = s32k3_sai_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void s32k3_sai_reset(DeviceState *dev)
{
    S32K3SaiState *s = S32K3_SAI(dev);
    int i;

    s->tcsr = s->tcr1 = s->tcr2 = s->tcr3 = s->tcr4 = s->tcr5 = s->tmr = 0;
    s->rcsr = s->rcr1 = s->rcr2 = s->rcr3 = s->rcr4 = s->rcr5 = s->rmr = 0;
    for (i = 0; i < S32K3_SAI_NUM_DATALINE; i++) {
        sai_fifo_reset(&s->tx_fifo[i]);
        sai_fifo_reset(&s->rx_fifo[i]);
    }
    timer_del(s->tx_drain_timer);
}

static void s32k3_sai_init(Object *obj)
{
    S32K3SaiState *s = S32K3_SAI(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_sai_ops, s, "s32k3-sai",
                           S32K3_SAI_MEM_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->iomem);
    sysbus_init_irq(SYS_BUS_DEVICE(obj), &s->irq);

    s->param_reset = 0x00040304; /* default: 4 data lines (SAI_0-like) */
}

static void s32k3_sai_realize(DeviceState *dev, Error **errp)
{
    S32K3SaiState *s = S32K3_SAI(dev);

    s->tx_drain_timer = timer_new_ns(QEMU_CLOCK_VIRTUAL, sai_tx_drain_tick, s);
    s32k3_sai_reset(dev);
}

static const Property s32k3_sai_props[] = {
    DEFINE_PROP_UINT32("param-reset", S32K3SaiState, param_reset, 0x00040304),
};

static const VMStateDescription s32k3_sai_vmstate = {
    .name = "s32k3-sai",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (const VMStateField[]) {
        VMSTATE_UINT32(tcsr, S32K3SaiState),
        VMSTATE_UINT32(tcr1, S32K3SaiState),
        VMSTATE_UINT32(tcr2, S32K3SaiState),
        VMSTATE_UINT32(tcr3, S32K3SaiState),
        VMSTATE_UINT32(tcr4, S32K3SaiState),
        VMSTATE_UINT32(tcr5, S32K3SaiState),
        VMSTATE_UINT32(tmr, S32K3SaiState),
        VMSTATE_UINT32(rcsr, S32K3SaiState),
        VMSTATE_UINT32(rcr1, S32K3SaiState),
        VMSTATE_UINT32(rcr2, S32K3SaiState),
        VMSTATE_UINT32(rcr3, S32K3SaiState),
        VMSTATE_UINT32(rcr4, S32K3SaiState),
        VMSTATE_UINT32(rcr5, S32K3SaiState),
        VMSTATE_UINT32(rmr, S32K3SaiState),
        VMSTATE_UINT32(param_reset, S32K3SaiState),
        VMSTATE_END_OF_LIST()
    }
};

static void s32k3_sai_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_sai_realize;
    dc->vmsd = &s32k3_sai_vmstate;
    device_class_set_props(dc, s32k3_sai_props);
}

static const TypeInfo s32k3_sai_info = {
    .name = TYPE_S32K3_SAI,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3SaiState),
    .instance_init = s32k3_sai_init,
    .class_init = s32k3_sai_class_init,
};

static void s32k3_sai_register_types(void)
{
    type_register_static(&s32k3_sai_info);
}

type_init(s32k3_sai_register_types)
