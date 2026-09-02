/*
 * NXP S32K3xx Low Power Serial Peripheral Interface (LPSPI) Emulation
 *
 * See s32k3_lpspi.h for the manual cross-reference this model was built
 * against (S32K3xx Reference Manual Rev. 11, Chapter 70).
 *
 * Implements Controller (master) mode: each write to TDR clocks one word
 * out over a QEMU SSI bus via ssi_transfer() and captures the response into
 * the RX FIFO, following the same "transfer completes synchronously on
 * FIFO write" approach used by QEMU's other simple SPI controllers (e.g.
 * hw/ssi/imx_spi.c, hw/ssi/pl022.c) rather than a cycle-accurate clock
 * model. Peripheral (target) mode, the circular-FIFO option
 * (CFGR0[CIRFIFO]), and frames larger than 32 bits (which the real part
 * splits across multiple FIFO words) are not modeled; guest writes to
 * those configuration bits are stored (so firmware read-back works) but
 * have no behavioral effect.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "hw/core/qdev-properties.h"
#include "hw/core/irq.h"
#include "hw/ssi/ssi.h"
#include "qapi/error.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qom/object.h"
#include "s32k3_lpspi.h"

static void s32k3_lpspi_update_irq(S32K3LPSPIState *s)
{
    uint32_t txwater = s->fcr & S32K3_LPSPI_FCR_TXWATER_MASK;
    uint32_t rxwater = (s->fcr & S32K3_LPSPI_FCR_RXWATER_MASK) >>
                       S32K3_LPSPI_FCR_RXWATER_SHIFT;
    bool tdf = s->tx_count <= txwater;
    bool rdf = s->rx_count > rxwater;
    bool level = false;

    if ((s->ier & S32K3_LPSPI_IER_TDIE) && tdf) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_RDIE) && rdf) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_WCIE) && (s->sr & S32K3_LPSPI_SR_WCF)) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_FCIE) && (s->sr & S32K3_LPSPI_SR_FCF)) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_TCIE) && (s->sr & S32K3_LPSPI_SR_TCF)) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_TEIE) && (s->sr & S32K3_LPSPI_SR_TEF)) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_REIE) && (s->sr & S32K3_LPSPI_SR_REF)) {
        level = true;
    }
    if ((s->ier & S32K3_LPSPI_IER_DMIE) && (s->sr & S32K3_LPSPI_SR_DMF)) {
        level = true;
    }

    qemu_set_irq(s->irq, level);
}

static uint32_t s32k3_lpspi_compute_sr(S32K3LPSPIState *s)
{
    uint32_t txwater = s->fcr & S32K3_LPSPI_FCR_TXWATER_MASK;
    uint32_t rxwater = (s->fcr & S32K3_LPSPI_FCR_RXWATER_MASK) >>
                       S32K3_LPSPI_FCR_RXWATER_SHIFT;
    uint32_t sr = s->sr & S32K3_LPSPI_SR_W1C_MASK;

    if (s->tx_count <= txwater) {
        sr |= S32K3_LPSPI_SR_TDF;
    }
    if (s->rx_count > rxwater) {
        sr |= S32K3_LPSPI_SR_RDF;
    }
    /* MBF: transfers in this model complete synchronously, so LPSPI is
     * never observed mid-transfer; it only ever reads back idle. */
    return sr;
}

static void s32k3_lpspi_reset_tx_fifo(S32K3LPSPIState *s)
{
    s->tx_count = 0;
    memset(s->tx_fifo, 0, sizeof(s->tx_fifo));
}

static void s32k3_lpspi_reset_rx_fifo(S32K3LPSPIState *s)
{
    s->rx_count = 0;
    memset(s->rx_fifo, 0, sizeof(s->rx_fifo));
    s->sof_pending = true;
}

static uint32_t s32k3_lpspi_param_reset(S32K3LPSPIState *s)
{
    /* Exact per-instance reset values from manual section 70.6.1.3,
     * "Register reset values": LPSPI0 has 8 PCS pins, LPSPI1 has 6,
     * LPSPI2-5 have 4; all instances have a 4-word (2^2) TX and RX FIFO. */
    switch (s->instance_id) {
    case 0:
        return 0x00080202;
    case 1:
        return 0x00060202;
    default:
        return 0x00040202;
    }
}

static void s32k3_lpspi_do_reset(S32K3LPSPIState *s, bool keep_cr)
{
    uint32_t cr = s->cr;

    s->verid = 0x02000004;
    s->param = s32k3_lpspi_param_reset(s);
    if (!keep_cr) {
        s->cr = 0;
    } else {
        /* Software reset (CR[RST]) leaves CR itself untouched. */
        s->cr = cr;
    }
    s->sr = S32K3_LPSPI_SR_RESET;
    s->ier = 0;
    s->der = 0;
    s->cfgr0 = 0;
    s->cfgr1 = 0;
    s->dmr0 = 0;
    s->dmr1 = 0;
    s->ccr = 0;
    s->ccr1 = 0;
    s->fcr = 0;
    s->tcr = S32K3_LPSPI_TCR_RESET;
    s->rdror = 0;
    s32k3_lpspi_reset_tx_fifo(s);
    s32k3_lpspi_reset_rx_fifo(s);
}

static void s32k3_lpspi_reset(DeviceState *dev)
{
    S32K3LPSPIState *s = S32K3_LPSPI(dev);

    s32k3_lpspi_do_reset(s, false);
    s32k3_lpspi_update_irq(s);
}

/* Service the TX FIFO: clock out every queued word over the SSI bus and
 * capture the response into the RX FIFO. Runs to completion synchronously
 * (no timing model) whenever new data becomes available and the module is
 * enabled - see file header for rationale. */
static void s32k3_lpspi_service(S32K3LPSPIState *s)
{
    bool transferred_any = false;

    if (!(s->cr & S32K3_LPSPI_CR_MEN)) {
        return;
    }
    if (!(s->cfgr1 & S32K3_LPSPI_CFGR1_MASTER)) {
        qemu_log_mask(LOG_UNIMP,
                      "s32k3_lpspi[%u]: Peripheral (target) mode is not "
                      "modeled; no transfer performed\n", s->instance_id);
        return;
    }

    while (s->tx_count > 0) {
        uint32_t framesz = (s->tcr & S32K3_LPSPI_TCR_FRAMESZ_MASK) + 1;
        uint32_t tx_word, rx_word;
        uint32_t i;

        if (framesz > 32) {
            /* Multi-word (>32 bit) frames are not modeled; treat as 32-bit. */
            framesz = 32;
        }

        /* Pop front of tx_fifo (shift-based, fine for a 4-entry FIFO) */
        tx_word = s->tx_fifo[0];
        for (i = 1; i < s->tx_count; i++) {
            s->tx_fifo[i - 1] = s->tx_fifo[i];
        }
        s->tx_count--;

        if (framesz < 32) {
            tx_word &= (1u << framesz) - 1;
        }
        if (s->tcr & S32K3_LPSPI_TCR_LSBF) {
            uint32_t rev = 0;
            for (i = 0; i < framesz; i++) {
                if (tx_word & (1u << i)) {
                    rev |= 1u << (framesz - 1 - i);
                }
            }
            tx_word = rev;
        }
        if (s->tcr & S32K3_LPSPI_TCR_TXMSK) {
            tx_word = 0;
        }

        rx_word = ssi_transfer(s->spi, tx_word);
        transferred_any = true;

        if (framesz < 32) {
            rx_word &= (1u << framesz) - 1;
        }

        if (!(s->tcr & S32K3_LPSPI_TCR_RXMSK)) {
            if (s->rx_count >= S32K3_LPSPI_FIFO_DEPTH) {
                s->sr |= S32K3_LPSPI_SR_REF; /* RX FIFO overflow */
                break;
            }
            s->rx_fifo[s->rx_count++] = rx_word;

            /* Simple data-match check against DMR0 (manual 70.6.1.9
             * CFGR1[MATCFG]); only the plain "match first/any word to
             * MATCH0" mode is modeled, not the sequential or masked
             * variants. */
            if ((s->cfgr1 & S32K3_LPSPI_CFGR1_MATCFG_MASK) &&
                rx_word == s->dmr0) {
                s->sr |= S32K3_LPSPI_SR_DMF;
            }
        }
    }

    if (transferred_any) {
        s->sr |= S32K3_LPSPI_SR_WCF;
        if (s->tx_count == 0 && !(s->tcr & S32K3_LPSPI_TCR_CONT)) {
            s->sr |= S32K3_LPSPI_SR_FCF | S32K3_LPSPI_SR_TCF;
        }
    } else if (s->cr & S32K3_LPSPI_CR_MEN) {
        s->sr |= S32K3_LPSPI_SR_TEF; /* underrun: enabled but nothing to send */
    }

    s32k3_lpspi_update_irq(s);
}

static uint64_t s32k3_lpspi_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3LPSPIState *s = opaque;

    switch (addr) {
    case S32K3_LPSPI_VERID:
        return s->verid;
    case S32K3_LPSPI_PARAM:
        return s->param;
    case S32K3_LPSPI_CR:
        return s->cr; /* RTF/RRF always read 0, and are never stored set */
    case S32K3_LPSPI_SR:
        return s32k3_lpspi_compute_sr(s);
    case S32K3_LPSPI_IER:
        return s->ier;
    case S32K3_LPSPI_DER:
        return s->der;
    case S32K3_LPSPI_CFGR0:
        return s->cfgr0;
    case S32K3_LPSPI_CFGR1:
        return s->cfgr1;
    case S32K3_LPSPI_DMR0:
        return s->dmr0;
    case S32K3_LPSPI_DMR1:
        return s->dmr1;
    case S32K3_LPSPI_CCR:
        return s->ccr;
    case S32K3_LPSPI_CCR1:
        return s->ccr1;
    case S32K3_LPSPI_FCR:
        return s->fcr;
    case S32K3_LPSPI_FSR:
        return (s->rx_count << S32K3_LPSPI_FSR_RXCOUNT_SHIFT) |
               (s->tx_count << S32K3_LPSPI_FSR_TXCOUNT_SHIFT);
    case S32K3_LPSPI_TCR:
        return s->tcr;
    case S32K3_LPSPI_RSR:
        return (s->rx_count == 0 ? S32K3_LPSPI_RSR_RXEMPTY : 0) |
               (s->sof_pending ? S32K3_LPSPI_RSR_SOF : 0);
    case S32K3_LPSPI_RDR:
        if (s->rx_count > 0) {
            uint32_t val = s->rx_fifo[0];
            uint32_t i;

            for (i = 1; i < s->rx_count; i++) {
                s->rx_fifo[i - 1] = s->rx_fifo[i];
            }
            s->rx_count--;
            s->sof_pending = (s->rx_count == 0);
            s->rdror = val;
            s32k3_lpspi_update_irq(s);
            return val;
        }
        return s->rdror;
    case S32K3_LPSPI_RDROR:
        return s->rdror;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_lpspi[%u]: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", s->instance_id, addr);
        return 0;
    }
}

static void s32k3_lpspi_write(void *opaque, hwaddr addr, uint64_t val64,
                               unsigned size)
{
    S32K3LPSPIState *s = opaque;
    uint32_t val = val64;

    switch (addr) {
    case S32K3_LPSPI_CR: {
        bool men_rising = !(s->cr & S32K3_LPSPI_CR_MEN) &&
                           (val & S32K3_LPSPI_CR_MEN);
        bool rst_rising = !(s->cr & S32K3_LPSPI_CR_RST) &&
                           (val & S32K3_LPSPI_CR_RST);

        if (val & S32K3_LPSPI_CR_RTF) {
            s32k3_lpspi_reset_tx_fifo(s);
        }
        if (val & S32K3_LPSPI_CR_RRF) {
            s32k3_lpspi_reset_rx_fifo(s);
        }
        /* RTF/RRF always read back as 0 (manual 70.6.1.4) */
        s->cr = val & (S32K3_LPSPI_CR_MEN | S32K3_LPSPI_CR_RST |
                       S32K3_LPSPI_CR_DBGEN);

        if (rst_rising) {
            s32k3_lpspi_do_reset(s, true);
        }
        if (men_rising) {
            s32k3_lpspi_service(s);
        }
        break;
    }
    case S32K3_LPSPI_SR:
        s->sr &= ~(val & S32K3_LPSPI_SR_W1C_MASK);
        break;
    case S32K3_LPSPI_IER:
        s->ier = val;
        break;
    case S32K3_LPSPI_DER:
        s->der = val;
        if (val) {
            qemu_log_mask(LOG_UNIMP,
                          "s32k3_lpspi[%u]: DMA requests are not modeled "
                          "(no eDMA controller yet)\n", s->instance_id);
        }
        break;
    case S32K3_LPSPI_CFGR0:
        s->cfgr0 = val;
        break;
    case S32K3_LPSPI_CFGR1:
        s->cfgr1 = val;
        break;
    case S32K3_LPSPI_DMR0:
        s->dmr0 = val;
        break;
    case S32K3_LPSPI_DMR1:
        s->dmr1 = val;
        break;
    case S32K3_LPSPI_CCR:
        s->ccr = val;
        break;
    case S32K3_LPSPI_CCR1:
        s->ccr1 = val;
        break;
    case S32K3_LPSPI_FCR:
        s->fcr = val;
        s32k3_lpspi_update_irq(s);
        break;
    case S32K3_LPSPI_TCR:
        s->tcr = val;
        break;
    case S32K3_LPSPI_TDR:
        if (s->tx_count >= S32K3_LPSPI_FIFO_DEPTH) {
            qemu_log_mask(LOG_GUEST_ERROR,
                          "s32k3_lpspi[%u]: TDR write with TX FIFO full, "
                          "word dropped\n", s->instance_id);
            break;
        }
        s->tx_fifo[s->tx_count++] = val;
        s32k3_lpspi_service(s);
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_lpspi[%u]: write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n",
                      s->instance_id, addr, val);
        break;
    }
}

static const MemoryRegionOps s32k3_lpspi_ops = {
    .read = s32k3_lpspi_read,
    .write = s32k3_lpspi_write,
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

static void s32k3_lpspi_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3LPSPIState *s = S32K3_LPSPI(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_lpspi_ops, s,
                          TYPE_S32K3_LPSPI, S32K3_LPSPI_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);

    s->spi = ssi_create_bus(DEVICE(obj), "spi");
}

static void s32k3_lpspi_realize(DeviceState *dev, Error **errp)
{
    s32k3_lpspi_reset(dev);
}

static const Property s32k3_lpspi_properties[] = {
    DEFINE_PROP_UINT32("lpspi-id", S32K3LPSPIState, instance_id, 0),
};

static void s32k3_lpspi_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_lpspi_realize;
    device_class_set_props(dc, s32k3_lpspi_properties);
}

static const TypeInfo s32k3_lpspi_info = {
    .name = TYPE_S32K3_LPSPI,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3LPSPIState),
    .instance_init = s32k3_lpspi_instance_init,
    .class_init = s32k3_lpspi_class_init,
};

static void s32k3_lpspi_register_types(void)
{
    type_register_static(&s32k3_lpspi_info);
}

type_init(s32k3_lpspi_register_types)
