/*
 * S32K3X8 LPUART Emulation
 *
 * QEMU emulation for the S32K3X8 series MCU LPUART peripheral
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#include "qemu/osdep.h"
#include "hw/core/sysbus.h"
#include "migration/vmstate.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "qemu/log.h"
#include "qemu/module.h"
#include "qemu/timer.h"
#include "chardev/char-fe.h"
#include "chardev/char-serial.h"
#include "hw/core/qdev-properties-system.h"
#include "hw/core/sysbus.h"  
#include "trace.h"
#include "qom/object.h"
#include "hw/core/irq.h"
#include "s32k3_uart.h"

/* Function forward declarations */
static void s32k3x8_lpuart_reset(DeviceState *dev);
static uint64_t s32k3x8_lpuart_read(void *opaque, hwaddr addr, unsigned size);
static void s32k3x8_lpuart_write(void *opaque, hwaddr addr, uint64_t val, unsigned size);
static int s32k3x8_lpuart_can_receive(void *opaque);
static void s32k3x8_lpuart_receive(void *opaque, const uint8_t *buf, int size);
static void s32k3x8_lpuart_event(void *opaque, QEMUChrEvent event);

/* FIFO management function declarations */
static void fifo_reset(S32K3X8LPUARTState *s, bool tx);
static bool fifo_is_empty(S32K3X8LPUARTState *s, bool tx);
static bool fifo_is_full(S32K3X8LPUARTState *s, bool tx);
static uint32_t fifo_count(S32K3X8LPUARTState *s, bool tx);
static void fifo_push(S32K3X8LPUARTState *s, uint8_t data, bool tx);
static uint8_t fifo_pop(S32K3X8LPUARTState *s, bool tx);
static void update_uart_status_from_fifo(S32K3X8LPUARTState *s);


/* Update interrupt state */
static void s32k3x8_lpuart_update_irq(S32K3X8LPUARTState *s)
{
    bool irq_state = false;
    
    /* Check receive data register full interrupt */
    if ((s->ctrl & CTRL_RIE) && (s->stat & STAT_RDRF)) {
        irq_state = true;
    }
    
    /* Check transmit data register empty interrupt */
    if ((s->ctrl & CTRL_TIE) && (s->stat & STAT_TDRE)) {
        irq_state = true;
    }
    
    /* Check transmission complete interrupt */
    if ((s->ctrl & CTRL_TCIE) && (s->stat & STAT_TC)) {
        irq_state = true;
    }
    
    /* Check idle line interrupt */
    if ((s->ctrl & CTRL_ILIE) && (s->stat & STAT_IDLE)) {
        irq_state = true;
    }
    
    /* Set interrupt state */
    qemu_set_irq(s->irq, irq_state);
}

/* Memory access operations structure */
static const MemoryRegionOps s32k3x8_lpuart_ops = {
    .read = s32k3x8_lpuart_read,
    .write = s32k3x8_lpuart_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = {
        .min_access_size = 1,
        .max_access_size = 4,
    },
    .valid = {
        .min_access_size = 1,
        .max_access_size = 4,
    }
};

/* Register read function */
static uint64_t s32k3x8_lpuart_read(void *opaque, hwaddr addr, unsigned size)
{
    S32K3X8LPUARTState *s = (S32K3X8LPUARTState *)opaque;
    uint64_t ret = 0;
    
    switch (addr) {
    case VERID_OFFSET:
        ret = s->verid;
        break;
    case PARAM_OFFSET:
        ret = s->param;
        break;
    case GLOBAL_OFFSET:
        ret = s->global;
        break;
    case PINCFG_OFFSET:
        ret = s->pincfg;
        break;
    case BAUD_OFFSET:
        ret = s->baud;
        break;
    case STAT_OFFSET:
        ret = s->stat;
        break;
    case CTRL_OFFSET:
        ret = s->ctrl;
        break;
    case DATA_OFFSET:
        /* If receive FIFO is not empty, read data from FIFO */
        if (!fifo_is_empty(s, false)) {
            s->data = fifo_pop(s, false);
            
            /* Update status flags */
            update_uart_status_from_fifo(s);
        }
        ret = s->data;
        break;
    case MATCH_OFFSET:
        ret = s->match;
        break;
    case MODIR_OFFSET:
        ret = s->modir;
        break;
    case FIFO_OFFSET:
        /* Dynamically update FIFO status bits */
        if (fifo_is_empty(s, true)) {
            s->fifo |= (1 << 23); /* TXEMPT */
        } else {
            s->fifo &= ~(1 << 23);
        }
        
        if (fifo_is_empty(s, false)) {
            s->fifo |= (1 << 22); /* RXEMPT */
        } else {
            s->fifo &= ~(1 << 22);
        }
        
        ret = s->fifo;
        break;
    case WATER_OFFSET:
        /* Update TXCOUNT and RXCOUNT fields */
        ret = s->water & ~(0x1F00001F); /* Clear count fields */
        ret |= (fifo_count(s, false) & 0x1F) << 24; /* RXCOUNT */
        ret |= (fifo_count(s, true) & 0x1F) << 8;   /* TXCOUNT */
        break;
    case DATARO_OFFSET:
        ret = s->dataro;
        break;
    case MCR_OFFSET:
        ret = s->mcr;
        break;
    case MSR_OFFSET:
        ret = s->msr;
        break;
    case REIR_OFFSET:
        ret = s->reir;
        break;
    case TEIR_OFFSET:
        ret = s->teir;
        break;
    case HDCR_OFFSET:
        ret = s->hdcr;
        break;
    case TOCR_OFFSET:
        ret = s->tocr;
        break;
    case TOSR_OFFSET:
        ret = s->tosr;
        break;
    default:
        if (addr >= 0x60 && addr <= 0x6C) {
            /* Timeout registers */
            ret = s->timeout[(addr - 0x60) / 4];
        } else {
            qemu_log_mask(LOG_GUEST_ERROR,
                        "s32k3x8_lpuart: Read from invalid offset 0x%"HWADDR_PRIx"\n",
                        addr);
            ret = 0;
        }
        break;
    }
    
    return ret;
}

/* Register write function */
static void s32k3x8_lpuart_write(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    S32K3X8LPUARTState *s = (S32K3X8LPUARTState *)opaque;
    uint8_t ch;
    uint32_t old_ctrl;
    
    switch (addr) {
    case GLOBAL_OFFSET:
        if (val & GLOBAL_RST) {
            /* Software reset */
            s32k3x8_lpuart_reset(DEVICE(s));
            /* Clear reset flag */
            val &= ~GLOBAL_RST;
        }
        s->global = val;
        break;
        
    case PINCFG_OFFSET:
        s->pincfg = val;
        break;
        
    case BAUD_OFFSET:
        s->baud = val;
        break;
        
    case STAT_OFFSET:
        /* Handle clearable status bits */
        if (val & STAT_IDLE) {
            s->stat &= ~STAT_IDLE;
        }
        if (val & STAT_OR) {
            s->stat &= ~STAT_OR;
        }
        if (val & STAT_NF) {
            s->stat &= ~STAT_NF;
        }
        if (val & STAT_FE) {
            s->stat &= ~STAT_FE;
        }
        if (val & STAT_PF) {
            s->stat &= ~STAT_PF;
        }
        /* Other status bits are read-only or require special handling */
        break;
        
    case CTRL_OFFSET:
        /* Save old control register value to detect changes */
        old_ctrl = s->ctrl;
        
        s->ctrl = val;
        
        /* Handle transmit enable bit changes */
        if ((val & CTRL_TE) && !(old_ctrl & CTRL_TE)) {
            /* Transmit enable changed from 0 to 1 */
            s->tx_enabled = true;
            /* Set transmit data register empty flag */
            s->stat |= STAT_TDRE;
            /* Clear transmission complete flag */
            s->stat &= ~STAT_TC;
        } else if (!(val & CTRL_TE) && (old_ctrl & CTRL_TE)) {
            /* Transmit enable changed from 1 to 0 */
            s->tx_enabled = false;
            /* Set transmission complete flag when last character is sent */
            if (fifo_is_empty(s, true)) {
                s->stat |= STAT_TC;
            }
        }
        
        /* Handle receive enable bit changes */
        if ((val & CTRL_RE) && !(old_ctrl & CTRL_RE)) {
            /* Receive enable changed from 0 to 1 */
            s->rx_enabled = true;
        } else if (!(val & CTRL_RE) && (old_ctrl & CTRL_RE)) {
            /* Receive enable changed from 1 to 0 */
            s->rx_enabled = false;
        }
        
        /* Update interrupt state */
        s32k3x8_lpuart_update_irq(s);
        break;
        
    case DATA_OFFSET:
        if (s->tx_enabled) {
            s->data = val & 0x3FF; /* Store 9/10 bits of data */
            ch = val & 0xFF;       /* Get byte to transmit */
            
            /* Push data to TX FIFO */
            if (!fifo_is_full(s, true)) {
                fifo_push(s, ch, true);
                
                /* Immediately handle transmission - simulates hardware automatically taking data from FIFO */
                if (qemu_chr_fe_backend_connected(&s->chr)) {
                    /* Take data from FIFO and transmit */
                    uint8_t tx_byte = fifo_pop(s, true);
                    qemu_chr_fe_write(&s->chr, &tx_byte, 1);
                    if (s->tx_sink) {
                        s->tx_sink(s->tx_sink_opaque, tx_byte);
                    }
                    
                    /* If FIFO is empty, set TC flag to indicate transmission complete */
                    if (fifo_is_empty(s, true)) {
                        s->stat |= STAT_TC;
                    } else {
                        /* If FIFO still has data, clear TC flag */
                        s->stat &= ~STAT_TC;
                    }
                }
                
                /* Update TDRE flag - based on FIFO watermark */
                uint32_t txwater = (s->water >> 0) & 0xF; /* Extract TX watermark setting */
                if (fifo_count(s, true) <= txwater) {
                    s->stat |= STAT_TDRE;  /* Below or equal to watermark, set TDRE */
                } else {
                    s->stat &= ~STAT_TDRE; /* Above watermark, clear TDRE */
                }
            } else {
                /* FIFO is full - in real hardware, write might be ignored */
                error_report("LPUART: TX FIFO overflow - data lost");
            }
        }
        break;
        
    case MATCH_OFFSET:
        s->match = val;
        break;
        
    case MODIR_OFFSET:
        s->modir = val;
        break;
        
    case FIFO_OFFSET:
        /* Handle FIFO flush operations */
        if (val & FIFO_TXFLUSH) {
            fifo_reset(s, true); /* Flush TX FIFO */
            s->stat |= STAT_TDRE;
        }
        if (val & FIFO_RXFLUSH) {
            fifo_reset(s, false); /* Flush RX FIFO */
            s->stat &= ~STAT_RDRF;
        }
        
        /* Store FIFO configuration except flush bits */
        s->fifo = val & ~(FIFO_TXFLUSH | FIFO_RXFLUSH);
        break;
        
    case WATER_OFFSET:
        s->water = val;
        break;
        
    case MCR_OFFSET:
        s->mcr = val;
        break;
        
    case MSR_OFFSET:
        /* Handle clearable status bits */
        s->msr = val;
        break;
        
    case REIR_OFFSET:
        s->reir = val;
        break;
        
    case TEIR_OFFSET:
        s->teir = val;
        break;
        
    case HDCR_OFFSET:
        s->hdcr = val;
        break;
        
    case TOCR_OFFSET:
        s->tocr = val;
        break;
        
    case TOSR_OFFSET:
        s->tosr = val;
        break;
        
    default:
        if (addr >= 0x60 && addr <= 0x6C) {
            /* Timeout registers */
            s->timeout[(addr - 0x60) / 4] = val;
        } else if (addr >= 0x200 && addr < 0x400) {
            /* Transmit Command Burst (TCBR) region */
            /* Simplified handling, actual implementation should follow the manual */
            ch = val & 0xFF;
            if (s->tx_enabled && qemu_chr_fe_backend_connected(&s->chr)) {
                qemu_chr_fe_write(&s->chr, &ch, 1);
            }
        } else if (addr >= 0x400 && addr < 0x800) {
            /* Transmit Data Burst (TDBR) region */
            /* Simplified handling, actual implementation should follow the manual */
            ch = val & 0xFF;
            if (s->tx_enabled && qemu_chr_fe_backend_connected(&s->chr)) {
                qemu_chr_fe_write(&s->chr, &ch, 1);
            }
        } else {
            qemu_log_mask(LOG_GUEST_ERROR,
                        "s32k3x8_lpuart: Write to invalid offset 0x%"HWADDR_PRIx"\n",
                        addr);
        }
        break;
    }
    
    /* Update interrupt state */
    s32k3x8_lpuart_update_irq(s);
}

/* Device reset function */
static void s32k3x8_lpuart_reset(DeviceState *dev)
{
    S32K3X8LPUARTState *s = S32K3X8_LPUART(dev);
    
    /* Reset registers to default values, according to reference manual */
    s->verid = 0x04040007;   /* Instance dependent */
    s->param = 0x00000202;   /* Instance dependent */
    s->global = 0x00000000;
    s->pincfg = 0x00000000;
    s->baud = 0x0F000004;
    s->stat = 0x00C00000;    /* TDRE=1, TC=1 */
    s->ctrl = 0x00000000;
    s->data = 0x00001000;
    s->match = 0x00000000;
    s->modir = 0x00000000;
    s->fifo = 0x00000000;    /* Instance dependent */
    s->water = 0x00000000;
    s->dataro = 0x00001000;
    s->mcr = 0x00000000;
    s->msr = 0x00000000;
    s->reir = 0x00000000;
    s->teir = 0x00000000;
    s->hdcr = 0x00000000;
    s->tocr = 0x00000000;
    s->tosr = 0x0000000F;
    
    /* Reset internal state */
    s->tx_enabled = false;
    s->rx_enabled = false;
    
    /* Reset FIFOs */
    fifo_reset(s, true);  /* TX FIFO */
    fifo_reset(s, false); /* RX FIFO */
    
    /* Update interrupt state */
    s32k3x8_lpuart_update_irq(s);
}

/* Update UART status flags based on FIFO state */
static void update_uart_status_from_fifo(S32K3X8LPUARTState *s)
{
    /* Update TX FIFO related status */
    uint32_t txwater = (s->water >> 0) & 0xF; /* Extract TX watermark */
    
    /* Update TDRE flag - based on FIFO watermark */
    if (fifo_count(s, true) <= txwater) {
        s->stat |= STAT_TDRE;  /* Below or equal to watermark, set TDRE */
    } else {
        s->stat &= ~STAT_TDRE; /* Above watermark, clear TDRE */
    }
    
    /* Update TC flag - only set when FIFO is empty */
    if (fifo_is_empty(s, true)) {
        s->stat |= STAT_TC;    /* FIFO is empty, set TC */
    } else {
        s->stat &= ~STAT_TC;   /* FIFO is not empty, clear TC */
    }
    
    /* Update RX FIFO related status */
    uint32_t rxwater = (s->water >> 16) & 0xF; /* Extract RX watermark */
    
    /* Update RDRF flag - based on FIFO watermark */
    if (fifo_count(s, false) > rxwater) {
        s->stat |= STAT_RDRF;  /* Above watermark, set RDRF */
    } else {
        s->stat &= ~STAT_RDRF; /* Below or equal to watermark, clear RDRF */
    }
    
    /* Update interrupt state */
    s32k3x8_lpuart_update_irq(s);
}

/* FIFO management function implementations */
static void fifo_reset(S32K3X8LPUARTState *s, bool tx)
{
    if (tx) {
        /* Reset transmit FIFO */
        if (s->tx_fifo.data == NULL && s->tx_fifo.size > 0) {
            s->tx_fifo.data = g_malloc0(s->tx_fifo.size);
        } else if (s->tx_fifo.data != NULL) {
            memset(s->tx_fifo.data, 0, s->tx_fifo.size);
        }
        s->tx_fifo.read_pos = 0;
        s->tx_fifo.write_pos = 0;
        s->tx_fifo.count = 0;
        
        /* Update status after FIFO reset */
        s->stat |= STAT_TDRE;  /* FIFO is empty, set TDRE */
        s->stat |= STAT_TC;    /* FIFO is empty, set TC */
    } else {
        /* Reset receive FIFO */
        if (s->rx_fifo.data == NULL && s->rx_fifo.size > 0) {
            s->rx_fifo.data = g_malloc0(s->rx_fifo.size);
        } else if (s->rx_fifo.data != NULL) {
            memset(s->rx_fifo.data, 0, s->rx_fifo.size);
        }
        s->rx_fifo.read_pos = 0;
        s->rx_fifo.write_pos = 0;
        s->rx_fifo.count = 0;
        
        /* Update status after FIFO reset */
        s->stat &= ~STAT_RDRF; /* FIFO is empty, clear RDRF */
    }
    
    /* Update interrupt state */
    s32k3x8_lpuart_update_irq(s);
}

static bool fifo_is_empty(S32K3X8LPUARTState *s, bool tx)
{
    if (tx) {
        return s->tx_fifo.count == 0;
    } else {
        return s->rx_fifo.count == 0;
    }
}

static bool fifo_is_full(S32K3X8LPUARTState *s, bool tx)
{
    if (tx) {
        return s->tx_fifo.count >= s->tx_fifo.size;
    } else {
        return s->rx_fifo.count >= s->rx_fifo.size;
    }
}

static uint32_t fifo_count(S32K3X8LPUARTState *s, bool tx)
{
    if (tx) {
        return s->tx_fifo.count;
    } else {
        return s->rx_fifo.count;
    }
}

static void fifo_push(S32K3X8LPUARTState *s, uint8_t data, bool tx)
{
    if (tx) {
        if (s->tx_fifo.count < s->tx_fifo.size) {
            s->tx_fifo.data[s->tx_fifo.write_pos] = data;
            s->tx_fifo.write_pos = (s->tx_fifo.write_pos + 1) % s->tx_fifo.size;
            s->tx_fifo.count++;
        }
    } else {
        if (s->rx_fifo.count < s->rx_fifo.size) {
            s->rx_fifo.data[s->rx_fifo.write_pos] = data;
            s->rx_fifo.write_pos = (s->rx_fifo.write_pos + 1) % s->rx_fifo.size;
            s->rx_fifo.count++;
        }
    }
}

static uint8_t fifo_pop(S32K3X8LPUARTState *s, bool tx)
{
    uint8_t data = 0;
    
    if (tx) {
        if (s->tx_fifo.count > 0) {
            data = s->tx_fifo.data[s->tx_fifo.read_pos];
            s->tx_fifo.read_pos = (s->tx_fifo.read_pos + 1) % s->tx_fifo.size;
            s->tx_fifo.count--;
        }
    } else {
        if (s->rx_fifo.count > 0) {
            data = s->rx_fifo.data[s->rx_fifo.read_pos];
            s->rx_fifo.read_pos = (s->rx_fifo.read_pos + 1) % s->rx_fifo.size;
            s->rx_fifo.count--;
        }
    }
    
    return data;
}

/* CharBackend interface implementation */
static int s32k3x8_lpuart_can_receive(void *opaque)
{
    S32K3X8LPUARTState *s = (S32K3X8LPUARTState *)opaque;
    
    /* Can receive only when receive is enabled and FIFO is not full */
    if (s->rx_enabled && !fifo_is_full(s, false)) {
        return 1;
    }
    
    return 0;
}

static void s32k3x8_lpuart_receive(void *opaque, const uint8_t *buf, int size)
{
    S32K3X8LPUARTState *s = (S32K3X8LPUARTState *)opaque;
    
    /* Process receive only when receive is enabled */
    if (!s->rx_enabled) {
        return;
    }
    
    /* Process each received byte */
    for (int i = 0; i < size; i++) {
        /* If FIFO is full, set overflow flag */
        if (fifo_is_full(s, false)) {
            s->stat |= STAT_OR;
            break;
        }
        
        /* Put data into receive FIFO */
        fifo_push(s, buf[i], false);
    }
    
    /* Update status flags */
    update_uart_status_from_fifo(s);
}

void s32k3x8_lpuart_set_tx_sink(S32K3X8LPUARTState *s, S32K3LPUARTTxSink sink, void *opaque) {
    s->tx_sink = sink;
    s->tx_sink_opaque = opaque;
}

void s32k3x8_lpuart_receive_byte(S32K3X8LPUARTState *s, uint8_t byte) {
    s32k3x8_lpuart_receive(s, &byte, 1);
}

void s32k3x8_lpuart_write_console(S32K3X8LPUARTState *s, uint8_t byte) {
    qemu_chr_fe_write(&s->chr, &byte, 1);
}

static void s32k3x8_lpuart_event(void *opaque, QEMUChrEvent event)
{
    /* Handle character device events, such as connect/disconnect */
    /* S32K3X8LPUARTState *s = (S32K3X8LPUARTState *)opaque; */
    
    switch (event) {
    case CHR_EVENT_BREAK:
        /* Handle break event */
        break;
    case CHR_EVENT_OPENED:
        /* Terminal connected */
        break;
    case CHR_EVENT_CLOSED:
        /* Terminal disconnected */
        break;
    default:
        break;
    }
}

/* Device property definitions */
static const Property s32k3x8_lpuart_properties[] = {
    DEFINE_PROP_CHR("chardev", S32K3X8LPUARTState, chr),
    DEFINE_PROP_UINT32("lpuart_id", S32K3X8LPUARTState, instance_ID, 0),
    DEFINE_PROP_UINT32("rx-size", S32K3X8LPUARTState, rx_fifo.size, 32),
    DEFINE_PROP_UINT32("tx-size", S32K3X8LPUARTState, tx_fifo.size, 32),
};

/* Device initialization function */
static void s32k3x8_lpuart_instance_init(Object *obj)
{
    SysBusDevice *dev = SYS_BUS_DEVICE(obj);
    S32K3X8LPUARTState *s = S32K3X8_LPUART(obj);

    /* Initialize memory region */
    memory_region_init_io(&s->iomem, obj, &s32k3x8_lpuart_ops, s,
                          TYPE_S32E8_LPUART, S32K3X8_LPUART_REGS_MEM_SIZE);
    sysbus_init_mmio(dev, &s->iomem);
    
    /* Initialize interrupt */
    sysbus_init_irq(dev, &s->irq);
}

/* Device realization function */
static void s32k3x8_lpuart_realize(DeviceState *dev, Error **errp)
{
    S32K3X8LPUARTState *s = S32K3X8_LPUART(dev);

    /* Reset device */
    s32k3x8_lpuart_reset(dev);

    /* Set character device callbacks */
    qemu_chr_fe_set_handlers(
        &s->chr,
        s32k3x8_lpuart_can_receive,
        s32k3x8_lpuart_receive,
        s32k3x8_lpuart_event,
        NULL,
        s,
        NULL,
        true
    );
    
    /* Initialize FIFOs */
    if (s->rx_fifo.data == NULL && s->rx_fifo.size > 0) {
        s->rx_fifo.data = g_malloc0(s->rx_fifo.size);
    }
    
    if (s->tx_fifo.data == NULL && s->tx_fifo.size > 0) {
        s->tx_fifo.data = g_malloc0(s->tx_fifo.size);
    }
}

/* Device class initialization function */
static void s32k3x8_lpuart_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    
    dc->realize = s32k3x8_lpuart_realize;
    /* In newer QEMU versions, reset is typically set via vmstate */
    /* dc->reset in newer QEMU versions might not exist, need to use VMStateDescription */
    device_class_set_props(dc, s32k3x8_lpuart_properties);
}

/* Type information definition */
static const TypeInfo s32k3x8_lpuart_info = {
    .name = TYPE_S32E8_LPUART,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(S32K3X8LPUARTState),
    .instance_init = s32k3x8_lpuart_instance_init,
    .class_init = s32k3x8_lpuart_class_init,
};

/* Type registration function */
void s32k3x8_lpuart_register_types(void)
{
    type_register_static(&s32k3x8_lpuart_info);
}

type_init(s32k3x8_lpuart_register_types);
