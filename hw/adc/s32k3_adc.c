/*
 * NXP S32K3xx Analog-to-Digital Converter (ADC) Emulation
 *
 * See s32k3_adc.h for the manual cross-reference (S32K3xx Reference Manual
 * Rev. 11, Chapter 60) and the list of modeling simplifications.
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
#include "qom/object.h"
#include "s32k3_adc.h"

static inline uint32_t s32k3_adc_reg(S32K3ADCState *s, hwaddr addr)
{
    return s->regs[addr / 4];
}

static inline void s32k3_adc_set_reg(S32K3ADCState *s, hwaddr addr,
                                      uint32_t val)
{
    s->regs[addr / 4] = val;
}

static void s32k3_adc_update_irq(S32K3ADCState *s)
{
    uint32_t isr = s32k3_adc_reg(s, S32K3_ADC_ISR);
    uint32_t imr = s32k3_adc_reg(s, S32K3_ADC_IMR);
    bool level = false;

    if ((imr & S32K3_ADC_IMR_MSKECH) && (isr & S32K3_ADC_ISR_ECH)) {
        level = true;
    }
    if ((imr & S32K3_ADC_IMR_MSKEOC) && (isr & S32K3_ADC_ISR_EOC)) {
        level = true;
    }
    if ((imr & S32K3_ADC_IMR_MSKJECH) && (isr & S32K3_ADC_ISR_JECH)) {
        level = true;
    }
    if ((imr & S32K3_ADC_IMR_MSKJEOC) && (isr & S32K3_ADC_ISR_JEOC)) {
        level = true;
    }
    if ((imr & S32K3_ADC_IMR_MSKEOBCTU) && (isr & S32K3_ADC_ISR_EOBCTU)) {
        level = true;
    }

    qemu_set_irq(s->irq, level);
}

/* Software-triggered normal conversion sweep (MCR[NSTART] rising edge).
 * Converts every channel enabled in NCMR0/1/2 to the fixed mid-scale
 * sample (no real analog input model - see file header), posts VALID on
 * each converted channel's data register, sets the per-group
 * CEOCFR/end-of-conversion flags, and the top-level ECH/EOC interrupt
 * status. Runs to completion synchronously - no conversion-time delay. */
static void s32k3_adc_do_conversion(S32K3ADCState *s)
{
    uint32_t ncmr0 = s32k3_adc_reg(s, S32K3_ADC_NCMR0);
    uint32_t ncmr1 = s32k3_adc_reg(s, S32K3_ADC_NCMR1);
    uint32_t ncmr2 = s32k3_adc_reg(s, S32K3_ADC_NCMR2);
    uint32_t ceocfr0 = s32k3_adc_reg(s, S32K3_ADC_CEOCFR0);
    uint32_t ceocfr1 = s32k3_adc_reg(s, S32K3_ADC_CEOCFR1);
    uint32_t ceocfr2 = s32k3_adc_reg(s, S32K3_ADC_CEOCFR2);
    uint32_t cdr_val = S32K3_ADC_CDR_VALID | S32K3_ADC_FIXED_SAMPLE;
    bool any = false;

    for (int ch = 0; ch < S32K3_ADC_NUM_PRECISION; ch++) {
        if (ncmr0 & BIT(ch)) {
            s32k3_adc_set_reg(s, S32K3_ADC_PCDR(ch), cdr_val);
            ceocfr0 |= BIT(ch);
            any = true;
        }
    }
    for (int ch = 0; ch < S32K3_ADC_NUM_STANDARD; ch++) {
        if (ncmr1 & BIT(ch)) {
            s32k3_adc_set_reg(s, S32K3_ADC_ICDR(ch), cdr_val);
            ceocfr1 |= BIT(ch);
            any = true;
        }
    }
    for (int ch = 0; ch < S32K3_ADC_NUM_EXTERNAL; ch++) {
        if (ncmr2 & BIT(ch)) {
            s32k3_adc_set_reg(s, S32K3_ADC_ECDR(ch), cdr_val);
            ceocfr2 |= BIT(ch);
            any = true;
        }
    }

    s32k3_adc_set_reg(s, S32K3_ADC_CEOCFR0, ceocfr0);
    s32k3_adc_set_reg(s, S32K3_ADC_CEOCFR1, ceocfr1);
    s32k3_adc_set_reg(s, S32K3_ADC_CEOCFR2, ceocfr2);

    if (any) {
        uint32_t isr = s32k3_adc_reg(s, S32K3_ADC_ISR);

        s32k3_adc_set_reg(s, S32K3_ADC_ISR,
                          isr | S32K3_ADC_ISR_ECH | S32K3_ADC_ISR_EOC);
    } else {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_adc[%u]: NSTART written with no channels "
                      "enabled in NCMR0/1/2\n", s->instance_id);
    }
}

static uint64_t s32k3_adc_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3ADCState *s = opaque;

    if (addr >= S32K3_ADC_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_adc[%u]: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", s->instance_id, addr);
        return 0;
    }

    switch (addr) {
    case S32K3_ADC_MCR:
        /* ABORT/ABORTCHAIN always read 0 (manual 60.6.2.2); never stored. */
        return s32k3_adc_reg(s, S32K3_ADC_MCR);
    case S32K3_ADC_MSR:
        return s32k3_adc_reg(s, S32K3_ADC_MSR);
    default:
        break;
    }

    /* Conversion data registers: VALID auto-clears on read (manual
     * 60.6.2.34 "automatically reset to 0 when the data is read"). */
    for (int ch = 0; ch < S32K3_ADC_NUM_PRECISION; ch++) {
        if (addr == S32K3_ADC_PCDR(ch)) {
            uint32_t val = s32k3_adc_reg(s, addr);
            s32k3_adc_set_reg(s, addr, val & ~S32K3_ADC_CDR_VALID);
            return val;
        }
    }
    for (int ch = 0; ch < S32K3_ADC_NUM_STANDARD; ch++) {
        if (addr == S32K3_ADC_ICDR(ch)) {
            uint32_t val = s32k3_adc_reg(s, addr);
            s32k3_adc_set_reg(s, addr, val & ~S32K3_ADC_CDR_VALID);
            return val;
        }
    }
    for (int ch = 0; ch < S32K3_ADC_NUM_EXTERNAL; ch++) {
        if (addr == S32K3_ADC_ECDR(ch)) {
            uint32_t val = s32k3_adc_reg(s, addr);
            s32k3_adc_set_reg(s, addr, val & ~S32K3_ADC_CDR_VALID);
            return val;
        }
    }

    return s32k3_adc_reg(s, addr);
}

static void s32k3_adc_write(void *opaque, hwaddr addr, uint64_t val64,
                             unsigned size)
{
    S32K3ADCState *s = opaque;
    uint32_t val = val64;

    if (addr >= S32K3_ADC_REGS_MEM_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_adc[%u]: write to invalid offset 0x%"
                      HWADDR_PRIx " (value 0x%" PRIx32 ")\n",
                      s->instance_id, addr, val);
        return;
    }

    switch (addr) {
    case S32K3_ADC_MCR: {
        uint32_t old = s32k3_adc_reg(s, S32K3_ADC_MCR);
        bool nstart_rising = !(old & S32K3_ADC_MCR_NSTART) &&
                              (val & S32K3_ADC_MCR_NSTART);

        /* ABORT/ABORTCHAIN/JSTART are pulses that always read back 0. */
        val &= ~(S32K3_ADC_MCR_ABORT | S32K3_ADC_MCR_ABORTCHAIN |
                S32K3_ADC_MCR_JSTART);

        if (nstart_rising) {
            s32k3_adc_set_reg(s, S32K3_ADC_MCR, val);
            s32k3_adc_do_conversion(s);
            /* Single-conversion mode: NSTART self-clears once the sweep
             * completes (manual 60.6.2.2). Continuous mode leaves it set
             * until software writes 0; since our conversions are
             * synchronous there's no periodic re-trigger to model. */
            if (!(val & S32K3_ADC_MCR_MODE)) {
                val &= ~S32K3_ADC_MCR_NSTART;
            }
        }
        s32k3_adc_set_reg(s, S32K3_ADC_MCR, val);
        s32k3_adc_update_irq(s);
        break;
    }
    case S32K3_ADC_MSR:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_adc[%u]: MSR is read-only\n", s->instance_id);
        break;
    case S32K3_ADC_ISR:
        s32k3_adc_set_reg(s, addr,
                          s32k3_adc_reg(s, addr) & ~(val & S32K3_ADC_ISR_W1C_MASK));
        s32k3_adc_update_irq(s);
        break;
    case S32K3_ADC_CEOCFR0:
    case S32K3_ADC_CEOCFR1:
    case S32K3_ADC_CEOCFR2:
        /* W1C: writing 1 to a channel bit clears its EOC flag. */
        s32k3_adc_set_reg(s, addr, s32k3_adc_reg(s, addr) & ~val);
        break;
    case S32K3_ADC_IMR:
        s32k3_adc_set_reg(s, addr, val);
        s32k3_adc_update_irq(s);
        break;
    default:
        s32k3_adc_set_reg(s, addr, val);
        break;
    }
}

static const MemoryRegionOps s32k3_adc_ops = {
    .read = s32k3_adc_read,
    .write = s32k3_adc_write,
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

static void s32k3_adc_reset(DeviceState *dev)
{
    S32K3ADCState *s = S32K3_ADC(dev);

    memset(s->regs, 0, sizeof(s->regs));

    /* Reset values taken directly from the manual's memory-map table
     * (section 60.6.2.1); every register not listed there resets to 0. */
    s32k3_adc_set_reg(s, S32K3_ADC_MCR, S32K3_ADC_MCR_RESET);
    s32k3_adc_set_reg(s, S32K3_ADC_MSR,
                      S32K3_ADC_MSR_CALIBRTD | S32K3_ADC_MSR_ADCSTATUS_IDLE);
    s32k3_adc_set_reg(s, 0x94, 0x00000016); /* CTR0 */
    s32k3_adc_set_reg(s, 0x98, 0x00000016); /* CTR1 */
    s32k3_adc_set_reg(s, 0x9C, 0x00000016); /* CTR2 */
    s32k3_adc_set_reg(s, 0x60, 0x7FFF0000); /* THRHLR0 */
    s32k3_adc_set_reg(s, 0x64, 0x7FFF0000); /* THRHLR1 */
    s32k3_adc_set_reg(s, 0x68, 0x7FFF0000); /* THRHLR2 */
    s32k3_adc_set_reg(s, 0x6C, 0x7FFF0000); /* THRHLR3 */
    s32k3_adc_set_reg(s, 0x340, 0x18182507); /* STCR1 */
    s32k3_adc_set_reg(s, 0x344, 0x00000005); /* STCR2 */
    s32k3_adc_set_reg(s, 0x348, 0x00000300); /* STCR3 */
    s32k3_adc_set_reg(s, 0x34C, 0x00050000); /* STBRR */
    s32k3_adc_set_reg(s, 0x380, 0x072704C5); /* STAW0R */
    s32k3_adc_set_reg(s, 0x388, 0x00003FF9); /* STAW1R */
    s32k3_adc_set_reg(s, 0x38C, 0x00003FF9); /* STAW2R */
    s32k3_adc_set_reg(s, 0x394, 0x00103FF0); /* STAW4R */
    s32k3_adc_set_reg(s, 0x398, 0x00103FF0); /* STAW5R */
    s32k3_adc_set_reg(s, 0x39C, 0x00000811); /* AMSIO */
    s32k3_adc_set_reg(s, 0x3A8, 0x00040000); /* OFSGNUSR */
    s32k3_adc_set_reg(s, 0x3B4, 0x43008243); /* CAL2 */
}

static void s32k3_adc_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3ADCState *s = S32K3_ADC(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_adc_ops, s,
                          TYPE_S32K3_ADC, S32K3_ADC_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq);
}

static void s32k3_adc_realize(DeviceState *dev, Error **errp)
{
    s32k3_adc_reset(dev);
}

static const Property s32k3_adc_properties[] = {
    DEFINE_PROP_UINT32("adc-id", S32K3ADCState, instance_id, 0),
};

static void s32k3_adc_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_adc_realize;
    device_class_set_props(dc, s32k3_adc_properties);
}

static const TypeInfo s32k3_adc_info = {
    .name = TYPE_S32K3_ADC,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3ADCState),
    .instance_init = s32k3_adc_instance_init,
    .class_init = s32k3_adc_class_init,
};

static void s32k3_adc_register_types(void)
{
    type_register_static(&s32k3_adc_info);
}

type_init(s32k3_adc_register_types)
