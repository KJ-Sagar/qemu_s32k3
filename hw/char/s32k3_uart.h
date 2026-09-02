#ifndef S32K3X8_UART_H
#define S32K3X8_UART_H

#include "hw/core/sysbus.h"
#include "hw/core/qdev.h"
#include "chardev/char-fe.h"
#include "qom/object.h"


typedef void (*S32K3LPUARTTxSink)(void *opaque, uint8_t byte);

/* LPUART Register Offsets */
#define VERID_OFFSET      0x00    /* Version ID Register */
#define PARAM_OFFSET      0x04    /* Parameter Register */
#define GLOBAL_OFFSET     0x08    /* Global Register */
#define PINCFG_OFFSET     0x0C    /* Pin Configuration Register */
#define BAUD_OFFSET       0x10    /* Baud Rate Register */
#define STAT_OFFSET       0x14    /* Status Register */
#define CTRL_OFFSET       0x18    /* Control Register */
#define DATA_OFFSET       0x1C    /* Data Register */
#define MATCH_OFFSET      0x20    /* Match Address Register */
#define MODIR_OFFSET      0x24    /* MODEM IrDA Register */
#define FIFO_OFFSET       0x28    /* FIFO Register */
#define WATER_OFFSET      0x2C    /* Watermark Register */
#define DATARO_OFFSET     0x30    /* Data Read-Only Register */
#define MCR_OFFSET        0x40    /* MODEM Control Register */
#define MSR_OFFSET        0x44    /* MODEM Status Register */
#define REIR_OFFSET       0x48    /* Receiver Extended Idle Register */
#define TEIR_OFFSET       0x4C    /* Transmitter Extended Idle Register */
#define HDCR_OFFSET       0x50    /* Half-Duplex Control Register */
#define TOCR_OFFSET       0x58    /* Timeout Control Register */
#define TOSR_OFFSET       0x5C    /* Timeout Status Register */

/* Register Bit Definitions */
/* GLOBAL Register Bits */
#define GLOBAL_RST        (1 << 0)    /* Software Reset */
#define GLOBAL_ENABLE     (1 << 1)    /* UART Enable */

/* CTRL Register Bits */
#define CTRL_TE           (1 << 19)   /* Transmitter Enable */
#define CTRL_RE           (1 << 18)   /* Receiver Enable */
#define CTRL_RIE          (1 << 21)   /* Receiver Interrupt Enable */
#define CTRL_TIE          (1 << 23)   /* Transmitter Interrupt Enable */
#define CTRL_TCIE         (1 << 22)   /* Transmission Complete Interrupt Enable */
#define CTRL_ILIE         (1 << 20)   /* Idle Interrupt Enable */

/* FIFO Register Bits */
#define FIFO_TXFE         (1 << 7)    /* Transmit FIFO Enable */
#define FIFO_RXFE         (1 << 3)    /* Receive FIFO Enable */
#define FIFO_TXFLUSH      (1 << 15)   /* Transmit FIFO Flush */
#define FIFO_RXFLUSH      (1 << 14)   /* Receive FIFO Flush */

/* STAT Register Bits */
#define STAT_TDRE         (1 << 23)   /* Transmit Data Register Empty Flag */
#define STAT_TC           (1 << 22)   /* Transmission Complete Flag */
#define STAT_RDRF         (1 << 21)   /* Receive Data Register Full Flag */
#define STAT_IDLE         (1 << 20)   /* Idle Line Flag */
#define STAT_OR           (1 << 19)   /* Receiver Overflow Flag */
#define STAT_NF           (1 << 18)   /* Noise Flag */
#define STAT_FE           (1 << 17)   /* Frame Error Flag */
#define STAT_PF           (1 << 16)   /* Parity Error Flag */

/* LPUART Module/Device Type Macros */
#define TYPE_S32E8_LPUART "S32E8_LPUART"
#define S32K3X8_LPUART_REGS_MEM_SIZE 0x800
#define I_(reg) (reg / sizeof(uint32_t))

/* LPUART State Structure Definition */
typedef struct S32K3X8LPUARTState {
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    CharFrontend chr;
    qemu_irq irq;             /* Interrupt Request Line */

    uint32_t instance_ID;     /* LPUART Instance ID */
    uint32_t base_addr;       /* Base Address */

    /* FIFO Structure Definition */
    struct {
        uint8_t *data;
        uint32_t size;
        uint32_t read_pos;
        uint32_t write_pos;
        uint32_t count;
    } rx_fifo, tx_fifo;

    /* Register Group */
    uint32_t verid;    /* Version ID Register */
    uint32_t param;    /* Parameter Register */
    uint32_t global;   /* Global Register */
    uint32_t pincfg;   /* Pin Configuration Register */
    uint32_t baud;     /* Baud Rate Register */
    uint32_t stat;     /* Status Register */
    uint32_t ctrl;     /* Control Register */
    uint32_t data;     /* Data Register */
    uint32_t match;    /* Match Address Register */
    uint32_t modir;    /* MODEM IrDA Register */
    uint32_t fifo;     /* FIFO Register */
    uint32_t water;    /* Watermark Register */
    uint32_t dataro;   /* Data Read-Only Register */
    uint32_t mcr;      /* MODEM Control Register */
    uint32_t msr;      /* MODEM Status Register */
    uint32_t reir;     /* Receiver Extended Idle Register */
    uint32_t teir;     /* Transmitter Extended Idle Register */
    uint32_t hdcr;     /* Half-Duplex Control Register */
    uint32_t tocr;     /* Timeout Control Register */
    uint32_t tosr;     /* Timeout Status Register */
    uint32_t timeout[4]; /* Timeout Registers */

    /* Internal Status Flags */
    bool tx_enabled;
    bool rx_enabled;
    S32K3LPUARTTxSink tx_sink;
    void *tx_sink_opaque;
} S32K3X8LPUARTState;

#define S32K3X8_LPUART(obj) \
    OBJECT_CHECK(S32K3X8LPUARTState, (obj), TYPE_S32E8_LPUART)

/* Function Declaration */
void s32k3x8_lpuart_register_types(void);
void s32k3x8_lpuart_set_tx_sink(S32K3X8LPUARTState *s, S32K3LPUARTTxSink sink, void *opaque);
void s32k3x8_lpuart_receive_byte(S32K3X8LPUARTState *s, uint8_t byte);
void s32k3x8_lpuart_write_console(S32K3X8LPUARTState *s, uint8_t byte);

#endif /* S32K3X8_UART_H */
