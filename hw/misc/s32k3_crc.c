/*
 * NXP S32K3xx Cyclic Redundancy Check (CRC) Emulation
 *
 * See s32k3_crc.h for the manual cross-reference (S32K3xx Reference Manual
 * Rev. 11, Chapter 58) and the list of modeling simplifications.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "qapi/error.h"
#include "qemu/bswap.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qom/object.h"
#include "s32k3_crc.h"

static uint8_t s32k3_crc_revbit8(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

static uint32_t s32k3_crc_revbit32(uint32_t v)
{
    v = (v & 0xFFFF0000u) >> 16 | (v & 0x0000FFFFu) << 16;
    v = (v & 0xFF00FF00u) >> 8  | (v & 0x00FF00FFu) << 8;
    v = (v & 0xF0F0F0F0u) >> 4  | (v & 0x0F0F0F0Fu) << 4;
    v = (v & 0xCCCCCCCCu) >> 2  | (v & 0x33333333u) << 2;
    v = (v & 0xAAAAAAAAu) >> 1  | (v & 0x55555555u) << 1;
    return v;
}

static bool s32k3_crc_is_32bit(S32K3CRCState *s)
{
    return s->ctrl & S32K3_CRC_CTRL_TCRC;
}

static uint32_t s32k3_crc_width_mask(S32K3CRCState *s)
{
    return s32k3_crc_is_32bit(s) ? 0xFFFFFFFFu : 0xFFFFu;
}

static uint32_t s32k3_crc_poly(S32K3CRCState *s)
{
    if (s32k3_crc_is_32bit(s)) {
        return s->gpoly;
    }
    return s->gpoly & 0xFFFF;
}

/* reg[31:0] -> per-byte bit reversal, byte positions unchanged (manual
 * 58.3.3.1, transpose type 01b: "reg[31:0] becomes
 * {reg[24:31], reg[16:23], reg[8:15], reg[0:7]}"). */
static uint32_t s32k3_transpose_bits_in_bytes(uint32_t v)
{
    uint32_t out = 0;
    for (int byte = 0; byte < 4; byte++) {
        uint8_t b = (v >> (byte * 8)) & 0xFF;
        out |= (uint32_t)s32k3_crc_revbit8(b) << (byte * 8);
    }
    return out;
}

/* Full 32-bit mirror: both bit-in-byte and byte order reversed (transpose
 * type 10b). */
static uint32_t s32k3_transpose_full_mirror(uint32_t v)
{
    return s32k3_crc_revbit32(v);
}

/* Byte-swap only, no bit reversal within a byte (transpose type 11b). */
static uint32_t s32k3_transpose_bytes_only(uint32_t v)
{
    return bswap32(v);
}

static uint32_t s32k3_transpose_apply(uint32_t v, uint32_t sel)
{
    switch (sel) {
    case 0:
        return v;
    case 1:
        return s32k3_transpose_bits_in_bytes(v);
    case 2:
        return s32k3_transpose_full_mirror(v);
    case 3:
        return s32k3_transpose_bytes_only(v);
    default:
        g_assert_not_reached();
    }
}

/* One byte through the bit-serial CRC engine (non-reflected, MSB-first -
 * matches the GPOLY reset value 0x1021, the classic CRC-16/CCITT-FALSE
 * polynomial, which is defined for this convention). Manual 58.3.2.1/
 * 58.3.2.2 describe this as "CRC is calculated bytewise". */
static uint32_t s32k3_crc_step_byte(uint32_t crc, uint8_t byte, uint32_t poly,
                                     int width)
{
    uint32_t top_bit = 1u << (width - 1);
    uint32_t mask = (width == 32) ? 0xFFFFFFFFu : ((1u << width) - 1);

    crc ^= ((uint32_t)byte) << (width - 8);
    for (int i = 0; i < 8; i++) {
        if (crc & top_bit) {
            crc = (crc << 1) ^ poly;
        } else {
            crc = crc << 1;
        }
    }
    return crc & mask;
}

static void s32k3_crc_feed_word(S32K3CRCState *s, uint32_t word, unsigned size)
{
    uint32_t poly = s32k3_crc_poly(s);
    int width = s32k3_crc_is_32bit(s) ? 32 : 16;
    uint32_t crc = s->data & s32k3_crc_width_mask(s);
    uint32_t tot = (s->ctrl & S32K3_CRC_CTRL_TOT_MASK) >>
                   S32K3_CRC_CTRL_TOT_SHIFT;

    /* Full 32-bit accesses: apply TOT to the whole written word first
     * (manual 58.3.3.1), then feed all 4 bytes MSB-first. For sub-word
     * (1/2 byte) accesses we feed the literal byte(s) as written, in
     * MSB-first bus order, without attempting the manual's documented
     * "zero-pad to 32 bits, transpose, then extract" behavior for that
     * case - see file header. */
    if (size == 4) {
        uint32_t transposed = s32k3_transpose_apply(word, tot);

        for (int shift = 24; shift >= 0; shift -= 8) {
            crc = s32k3_crc_step_byte(crc, (transposed >> shift) & 0xFF,
                                       poly, width);
        }
    } else {
        for (int i = (int)size - 1; i >= 0; i--) {
            uint8_t b = (word >> (i * 8)) & 0xFF;
            crc = s32k3_crc_step_byte(crc, b, poly, width);
        }
    }

    s->data = crc;
}

static uint64_t s32k3_crc_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3CRCState *s = opaque;

    switch (addr) {
    case S32K3_CRC_DATA: {
        uint32_t totr = (s->ctrl & S32K3_CRC_CTRL_TOTR_MASK) >>
                        S32K3_CRC_CTRL_TOTR_SHIFT;
        uint32_t val = s32k3_transpose_apply(s->data, totr);

        if (s->ctrl & S32K3_CRC_CTRL_FXOR) {
            val = ~val;
        }
        return val & s32k3_crc_width_mask(s);
    }
    case S32K3_CRC_GPOLY:
        return s->gpoly;
    case S32K3_CRC_CTRL:
        return s->ctrl;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_crc: read from invalid offset 0x%"
                      HWADDR_PRIx "\n", addr);
        return 0;
    }
}

static void s32k3_crc_write(void *opaque, hwaddr addr, uint64_t val64,
                             unsigned size)
{
    S32K3CRCState *s = opaque;
    uint32_t val = val64;

    switch (addr) {
    case S32K3_CRC_DATA:
        if (s->ctrl & S32K3_CRC_CTRL_WAS) {
            /* Programming the seed value (manual 58.3.2). */
            s->data = val & s32k3_crc_width_mask(s);
        } else {
            s32k3_crc_feed_word(s, val, size);
        }
        break;
    case S32K3_CRC_GPOLY:
        if (s32k3_crc_is_32bit(s)) {
            s->gpoly = val;
        } else {
            /* manual 58.7.1.3: writes to GPOLY[HIGH] ignored in 16-bit mode */
            s->gpoly = (s->gpoly & 0xFFFF0000u) | (val & 0xFFFFu);
        }
        break;
    case S32K3_CRC_CTRL:
        s->ctrl = val & (S32K3_CRC_CTRL_TOT_MASK | S32K3_CRC_CTRL_TOTR_MASK |
                         S32K3_CRC_CTRL_FXOR | S32K3_CRC_CTRL_WAS |
                         S32K3_CRC_CTRL_TCRC);
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3_crc: write to invalid offset 0x%" HWADDR_PRIx
                      " (value 0x%" PRIx32 ")\n", addr, val);
        break;
    }
}

static const MemoryRegionOps s32k3_crc_ops = {
    .read = s32k3_crc_read,
    .write = s32k3_crc_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
    .valid = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
};

static void s32k3_crc_reset(DeviceState *dev)
{
    S32K3CRCState *s = S32K3_CRC(dev);

    s->data = 0xFFFFFFFF;
    s->gpoly = 0x00001021;
    s->ctrl = 0;
}

static void s32k3_crc_instance_init(Object *obj)
{
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    S32K3CRCState *s = S32K3_CRC(obj);

    memory_region_init_io(&s->iomem, obj, &s32k3_crc_ops, s,
                          TYPE_S32K3_CRC, S32K3_CRC_REGS_MEM_SIZE);
    sysbus_init_mmio(sbd, &s->iomem);
}

static void s32k3_crc_realize(DeviceState *dev, Error **errp)
{
    s32k3_crc_reset(dev);
}

static void s32k3_crc_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->realize = s32k3_crc_realize;
}

static const TypeInfo s32k3_crc_info = {
    .name = TYPE_S32K3_CRC,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3CRCState),
    .instance_init = s32k3_crc_instance_init,
    .class_init = s32k3_crc_class_init,
};

static void s32k3_crc_register_types(void)
{
    type_register_static(&s32k3_crc_info);
}

type_init(s32k3_crc_register_types)
