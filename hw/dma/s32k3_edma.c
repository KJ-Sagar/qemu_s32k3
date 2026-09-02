/*
 * NXP S32K3xx Enhanced Direct Memory Access (eDMA) Emulation
 *
 * See s32k3_edma.h for the manual cross-reference (S32K3xx Reference
 * Manual Rev. 11, Chapter 15) and the list of modeling simplifications.
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
#include "system/address-spaces.h"
#include "qom/object.h"
#include "s32k3_edma.h"

static int32_t sext16(uint32_t v)
{
    return (int16_t)(v & 0xFFFF);
}

static uint32_t s32k3_edma_size_bytes(uint32_t code)
{
    switch (code) {
    case 0: return 1;
    case 1: return 2;
    case 2: return 4;
    case 3: return 8;
    default: return 0; /* 16/32/64-byte burst or reserved - unsupported */
    }
}

static void s32k3_edma_update_irq(S32K3EdmaChannel *c)
{
    S32K3EdmaState *s = c->owner;

    qemu_set_irq(s->irq[c->index], !!(c->intr & S32K3_EDMA_CH_INT_INT));
}

static void s32k3_edma_set_error(S32K3EdmaChannel *c, uint32_t es_bit)
{
    S32K3EdmaState *s = c->owner;

    c->es |= S32K3_EDMA_CH_ES_ERR | es_bit;
    s->mgmt_es = (1u << S32K3_EDMA_MGMT_ES_VLD_SHIFT) |
                 ((uint32_t)c->index << S32K3_EDMA_MGMT_ES_ERRCHN_SHIFT);

    if (c->csr & S32K3_EDMA_CH_CSR_EEI) {
        /* Manual 15.6.2.3: an enabled error is OR'd onto the channel's
         * done/INT interrupt. */
        c->intr |= S32K3_EDMA_CH_INT_INT;
        s32k3_edma_update_irq(c);
    }
}

/* Perform the entire major loop (CITER minor-loop iterations of NBYTES
 * bytes each) synchronously - see the header's scope note re: why this
 * model runs a whole major loop to completion on a single START write
 * rather than pumping one minor loop per hardware request. */
static void s32k3_edma_start(S32K3EdmaChannel *c)
{
    uint32_t ssize_code = (c->attr & S32K3_EDMA_ATTR_SSIZE_MASK) >>
                          S32K3_EDMA_ATTR_SSIZE_SHIFT;
    uint32_t dsize_code = c->attr & S32K3_EDMA_ATTR_DSIZE_MASK;
    uint32_t ssize = s32k3_edma_size_bytes(ssize_code);
    uint32_t dsize = s32k3_edma_size_bytes(dsize_code);
    uint32_t iters = c->citer & S32K3_EDMA_ITER_COUNT_MASK;
    int32_t soff = sext16(c->soff);
    int32_t doff = sext16(c->doff);

    if (c->tcd_csr & S32K3_EDMA_TCD_CSR_ESG) {
        qemu_log_mask(LOG_UNIMP,
                      "s32k3_edma: channel %d requests scatter/gather "
                      "(TCDn_CSR[ESG]), which is not modeled - ignored\n",
                      c->index);
    }
    if (c->tcd_csr & S32K3_EDMA_TCD_CSR_MAJORELINK) {
        qemu_log_mask(LOG_UNIMP,
                      "s32k3_edma: channel %d requests major-loop channel "
                      "linking (TCDn_CSR[MAJORELINK]), which is not "
                      "modeled - ignored\n", c->index);
    }

    if (c->nbytes == 0 || ssize == 0 || dsize == 0 ||
        (c->nbytes % ssize) != 0 || (c->nbytes % dsize) != 0 || iters == 0) {
        s32k3_edma_set_error(c, S32K3_EDMA_CH_ES_NCE);
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: channel %d NBYTES/CITER/ATTR "
                      "configuration error (NBYTES=%u SSIZE=%u DSIZE=%u "
                      "CITER=%u)\n", c->index, c->nbytes, ssize, dsize,
                      iters);
        return;
    }

    bool size_mismatch = (ssize != dsize);

    if (size_mismatch) {
        qemu_log_mask(LOG_UNIMP,
                      "s32k3_edma: channel %d has SSIZE(%u) != DSIZE(%u) - "
                      "size-converting packing is not modeled, copying the "
                      "correct total byte count byte-by-byte instead\n",
                      c->index, ssize, dsize);
    }

    for (uint32_t iter = 0; iter < iters; iter++) {
        uint32_t saddr = c->saddr;
        uint32_t daddr = c->daddr;

        if (size_mismatch) {
            uint8_t buf[4096];
            uint32_t remaining = c->nbytes;
            uint32_t off = 0;

            while (remaining) {
                uint32_t chunk = remaining > sizeof(buf) ? sizeof(buf) : remaining;
                address_space_read(&address_space_memory, saddr + off,
                                   MEMTXATTRS_UNSPECIFIED, buf, chunk);
                address_space_write(&address_space_memory, daddr + off,
                                    MEMTXATTRS_UNSPECIFIED, buf, chunk);
                remaining -= chunk;
                off += chunk;
            }
        } else {
            uint32_t transfers = c->nbytes / ssize;

            for (uint32_t t = 0; t < transfers; t++) {
                uint8_t buf[8];

                address_space_read(&address_space_memory, saddr,
                                   MEMTXATTRS_UNSPECIFIED, buf, ssize);
                address_space_write(&address_space_memory, daddr,
                                    MEMTXATTRS_UNSPECIFIED, buf, dsize);
                saddr += soff;
                daddr += doff;
            }
        }
    }

    /* Major loop complete: apply the last-address adjustments (manual
     * 15.6.2.12/17 - SLAST_SDA/DLAST_SGA as plain signed adjustments;
     * ESDA "store destination address" and scatter/gather reinterpretation
     * of these fields are not modeled). */
    c->saddr = c->saddr + (int32_t)c->slast;
    c->daddr = c->daddr + (int32_t)c->dlast_sga;

    /* Reload CITER from BITER for the next activation. */
    c->citer = c->biter;

    c->csr &= ~S32K3_EDMA_CH_CSR_ACTIVE;
    c->csr |= S32K3_EDMA_CH_CSR_DONE;

    if (c->tcd_csr & S32K3_EDMA_TCD_CSR_DREQ) {
        c->csr &= ~S32K3_EDMA_CH_CSR_ERQ;
    }
    if (c->tcd_csr & S32K3_EDMA_TCD_CSR_INTMAJOR) {
        c->intr |= S32K3_EDMA_CH_INT_INT;
    }
    s32k3_edma_update_irq(c);
}

static uint64_t s32k3_edma_mgmt_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3EdmaState *s = opaque;

    if (addr >= S32K3_EDMA_MGMT_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: mgmt read from invalid offset 0x%"
                      HWADDR_PRIx "\n", addr);
        return 0;
    }

    switch (addr) {
    case S32K3_EDMA_MGMT_CSR:
        return s->mgmt_csr; /* ACTIVE/ACTIVE_ID always read 0 - see scope note */
    case S32K3_EDMA_MGMT_ES:
        return s->mgmt_es;
    case S32K3_EDMA_MGMT_INT: {
        uint32_t v = 0;

        for (int i = 0; i < S32K3_EDMA_NUM_CHANNELS; i++) {
            if (s->ch[i].intr & S32K3_EDMA_CH_INT_INT) {
                v |= BIT(i);
            }
        }
        return v;
    }
    case S32K3_EDMA_MGMT_HRS:
        return 0; /* no hardware request lines modeled - see scope note */
    default:
        if (addr >= 0x100 && addr < S32K3_EDMA_MGMT_REGS_MEM_SIZE) {
            return s->grpri[(addr - 0x100) / 4];
        }
        return 0;
    }
}

static void s32k3_edma_mgmt_write(void *opaque, hwaddr addr, uint64_t val64,
                                    unsigned size)
{
    S32K3EdmaState *s = opaque;
    uint32_t val = val64;

    if (addr >= S32K3_EDMA_MGMT_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: mgmt write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n", addr, val);
        return;
    }

    switch (addr) {
    case S32K3_EDMA_MGMT_CSR:
        s->mgmt_csr = val & S32K3_EDMA_MGMT_CSR_RW_MASK;
        break;
    case S32K3_EDMA_MGMT_ES:
    case S32K3_EDMA_MGMT_INT:
    case S32K3_EDMA_MGMT_HRS:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: mgmt offset 0x%" HWADDR_PRIx
                      " is read-only\n", addr);
        break;
    default:
        if (addr >= 0x100 && addr < S32K3_EDMA_MGMT_REGS_MEM_SIZE) {
            s->grpri[(addr - 0x100) / 4] = val & 0x1F;
        }
        break;
    }
}

static const MemoryRegionOps s32k3_edma_mgmt_ops = {
    .read = s32k3_edma_mgmt_read,
    .write = s32k3_edma_mgmt_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = { .min_access_size = 4, .max_access_size = 4 },
    .valid = { .min_access_size = 4, .max_access_size = 4 },
};

static uint64_t s32k3_edma_ch_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3EdmaState *s = opaque;

    if (addr >= S32K3_EDMA_CH_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: channel-page read from invalid offset "
                      "0x%" HWADDR_PRIx "\n", addr);
        return 0;
    }

    int idx = addr / S32K3_EDMA_CH_STRIDE;
    int sub = addr % S32K3_EDMA_CH_STRIDE;
    S32K3EdmaChannel *c = &s->ch[idx];

    switch (sub) {
    case S32K3_EDMA_CH_CSR:
        return c->csr;
    case S32K3_EDMA_CH_ES:
        return c->es;
    case S32K3_EDMA_CH_INT:
        return c->intr;
    case S32K3_EDMA_CH_SBR:
        return c->sbr;
    case S32K3_EDMA_CH_PRI:
        return c->pri;
    case S32K3_EDMA_TCD_SADDR:
        return c->saddr;
    case S32K3_EDMA_TCD_SOFF:
        /* SOFF (0x24) and ATTR (0x26) are adjacent 16-bit registers; a
         * 32-bit access at 0x24 reads both combined (SDKs commonly do
         * this), a 16-bit access reads just SOFF. */
        if (size == 4) {
            return (c->soff & 0xFFFF) | ((c->attr & 0xFFFFu) << 16);
        }
        return c->soff & 0xFFFF;
    case S32K3_EDMA_TCD_ATTR:
        return c->attr & 0xFFFF;
    case S32K3_EDMA_TCD_NBYTES:
        return c->nbytes;
    case S32K3_EDMA_TCD_SLAST:
        return c->slast;
    case S32K3_EDMA_TCD_DADDR:
        return c->daddr;
    case S32K3_EDMA_TCD_DOFF:
        /* DOFF (0x34) / CITER (0x36) combined 32-bit access, same idea
         * as SOFF/ATTR above. */
        if (size == 4) {
            return (c->doff & 0xFFFF) | ((c->citer & 0xFFFFu) << 16);
        }
        return c->doff & 0xFFFF;
    case S32K3_EDMA_TCD_CITER:
        return c->citer & 0xFFFF;
    case S32K3_EDMA_TCD_DLAST_SGA:
        return c->dlast_sga;
    case S32K3_EDMA_TCD_CSR:
        /* CSR (0x3C) / BITER (0x3E) combined 32-bit access. */
        if (size == 4) {
            return (c->tcd_csr & 0xFFFF) | ((c->biter & 0xFFFFu) << 16);
        }
        return c->tcd_csr & 0xFFFF;
    case S32K3_EDMA_TCD_BITER:
        return c->biter & 0xFFFF;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: channel %d read from invalid sub-offset "
                      "0x%x\n", idx, sub);
        return 0;
    }
}

static void s32k3_edma_ch_write(void *opaque, hwaddr addr, uint64_t val64,
                                  unsigned size)
{
    S32K3EdmaState *s = opaque;
    uint32_t val = val64;

    if (addr >= S32K3_EDMA_CH_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: channel-page write to invalid offset "
                      "0x%" HWADDR_PRIx " (value 0x%" PRIx32 ")\n", addr,
                      val);
        return;
    }

    int idx = addr / S32K3_EDMA_CH_STRIDE;
    int sub = addr % S32K3_EDMA_CH_STRIDE;
    S32K3EdmaChannel *c = &s->ch[idx];

    switch (sub) {
    case S32K3_EDMA_CH_CSR: {
        /* DONE is W1C (writing 1 clears it); ACTIVE is RO (always 0 in
         * this synchronous model). Other bits (EBW/EEI/EARQ/ERQ) are
         * plain read/write. */
        uint32_t new_done = (c->csr & S32K3_EDMA_CH_CSR_DONE) &&
                             !(val & S32K3_EDMA_CH_CSR_DONE) ?
                             S32K3_EDMA_CH_CSR_DONE : 0;

        c->csr = (val & ~(S32K3_EDMA_CH_CSR_ACTIVE | S32K3_EDMA_CH_CSR_DONE)) |
                 new_done;
        break;
    }
    case S32K3_EDMA_CH_ES:
        c->es &= ~(val & S32K3_EDMA_CH_ES_W1C_MASK);
        if (!(c->es & S32K3_EDMA_CH_ES_W1C_MASK)) {
            c->es &= ~S32K3_EDMA_CH_ES_ERR;
        }
        break;
    case S32K3_EDMA_CH_INT:
        if (val & S32K3_EDMA_CH_INT_INT) {
            c->intr &= ~S32K3_EDMA_CH_INT_INT;
            s32k3_edma_update_irq(c);
        }
        break;
    case S32K3_EDMA_CH_SBR:
        c->sbr = val;
        break;
    case S32K3_EDMA_CH_PRI:
        c->pri = val & (S32K3_EDMA_CH_PRI_ECP | S32K3_EDMA_CH_PRI_DPA |
                        S32K3_EDMA_CH_PRI_APL_MASK);
        break;
    case S32K3_EDMA_TCD_SADDR:
        c->saddr = val;
        break;
    case S32K3_EDMA_TCD_SOFF:
        c->soff = val & 0xFFFF;
        if (size == 4) {
            c->attr = (val >> 16) & 0xFFFF;
        }
        break;
    case S32K3_EDMA_TCD_ATTR:
        c->attr = val & 0xFFFF;
        break;
    case S32K3_EDMA_TCD_NBYTES:
        c->nbytes = val;
        break;
    case S32K3_EDMA_TCD_SLAST:
        c->slast = val;
        break;
    case S32K3_EDMA_TCD_DADDR:
        c->daddr = val;
        break;
    case S32K3_EDMA_TCD_DOFF:
        c->doff = val & 0xFFFF;
        if (size == 4) {
            c->citer = (val >> 16) & 0xFFFF;
        }
        break;
    case S32K3_EDMA_TCD_CITER:
        c->citer = val & 0xFFFF;
        break;
    case S32K3_EDMA_TCD_DLAST_SGA:
        c->dlast_sga = val;
        break;
    case S32K3_EDMA_TCD_CSR:
        c->tcd_csr = val & 0xFFFF;
        if (size == 4) {
            c->biter = (val >> 16) & 0xFFFF;
        }
        if (c->tcd_csr & S32K3_EDMA_TCD_CSR_START) {
            c->tcd_csr &= ~S32K3_EDMA_TCD_CSR_START; /* self-clearing */
            s32k3_edma_start(c);
        }
        break;
    case S32K3_EDMA_TCD_BITER:
        c->biter = val & 0xFFFF;
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_edma: channel %d write to invalid sub-offset "
                      "0x%x (value 0x%" PRIx32 ")\n", idx, sub, val);
        break;
    }
}

static const MemoryRegionOps s32k3_edma_ch_ops = {
    .read = s32k3_edma_ch_read,
    .write = s32k3_edma_ch_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    /* Most TCD fields are 32-bit, but SOFF/ATTR/DOFF/CITER/CSR/BITER are
     * genuinely 16-bit-wide registers (manual section 15.6.2) that
     * firmware commonly accesses with 16-bit stores - see the combined
     * 32-bit-access handling in the read/write callbacks above. */
    .impl = { .min_access_size = 2, .max_access_size = 4 },
    .valid = { .min_access_size = 2, .max_access_size = 4 },
};

static void s32k3_edma_reset(DeviceState *dev)
{
    S32K3EdmaState *s = S32K3_EDMA(dev);

    s->mgmt_csr = 0;
    s->mgmt_es = 0;
    memset(s->grpri, 0, sizeof(s->grpri));

    for (int i = 0; i < S32K3_EDMA_NUM_CHANNELS; i++) {
        S32K3EdmaChannel *c = &s->ch[i];

        c->csr = 0;
        c->es = 0;
        c->intr = 0;
        c->sbr = 0x8002; /* manual 15.6.2.1 memory-map reset value */
        c->pri = 0;
        c->saddr = 0;
        c->soff = 0;
        c->attr = 0;
        c->nbytes = 0;
        c->slast = 0;
        c->daddr = 0;
        c->doff = 0;
        c->citer = 0;
        c->dlast_sga = 0;
        c->tcd_csr = 0;
        c->biter = 0;
        s32k3_edma_update_irq(c);
    }
}

static void s32k3_edma_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3EdmaState *s = S32K3_EDMA(obj);

    memory_region_init_io(&s->mgmt_iomem, obj, &s32k3_edma_mgmt_ops, s,
                          TYPE_S32K3_EDMA ".mgmt", S32K3_EDMA_MGMT_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->mgmt_iomem);

    memory_region_init_io(&s->ch_iomem, obj, &s32k3_edma_ch_ops, s,
                          TYPE_S32K3_EDMA ".channels", S32K3_EDMA_CH_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->ch_iomem);

    for (int i = 0; i < S32K3_EDMA_NUM_CHANNELS; i++) {
        s->ch[i].owner = s;
        s->ch[i].index = i;
        sysbus_init_irq(sbd, &s->irq[i]);
    }
}

static void s32k3_edma_realize(DeviceState *dev, Error **errp)
{
    s32k3_edma_reset(dev);
}

static void s32k3_edma_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_edma_realize;
}

static const TypeInfo s32k3_edma_info = {
    .name = TYPE_S32K3_EDMA,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3EdmaState),
    .instance_init = s32k3_edma_instance_init,
    .class_init = s32k3_edma_class_init,
};

static void s32k3_edma_register_types(void)
{
    type_register_static(&s32k3_edma_info);
}

type_init(s32k3_edma_register_types)
