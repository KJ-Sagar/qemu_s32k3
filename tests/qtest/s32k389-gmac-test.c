/*
 * S32K389 GMAC EQOS datapath tests.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "qemu/bswap.h"
#include "libqtest.h"
#include "qemu/bitops.h"
#include "qemu/iov.h"
#include "qemu/sockets.h"

#ifndef _WIN32
#include <poll.h>

#define GMAC0_BASE              0x40484000
#define GMAC0_IRQ               224
#define GMAC0_TX_IRQ            225
#define GMAC0_RX_IRQ            226
#define GMAC0_CH1_TX_IRQ        227
#define GMAC0_CH1_RX_IRQ        228
#define GMAC0_CH2_TX_IRQ        229
#define GMAC0_CH2_RX_IRQ        230
#define GMAC1_BASE              0x40488000
#define GMAC1_IRQ               171
#define GMAC1_TX_IRQ            172
#define GMAC1_RX_IRQ            233
#define GMAC1_CH1_TX_IRQ        234
#define GMAC1_CH2_RX_IRQ        237
#define MAC_CONFIG              0x0000
#define MAC_PACKET_FILTER       0x0008
#define MAC_RXQ_CONTROL0        0x00a0
#define MAC_RXQ_CONTROL1        0x00a4
#define MAC_RXQ_CONTROL2        0x00a8
#define MTL_RXQ_DMA_MAP0        0x0c30
#define MAC_MDIO_ADDRESS        0x0200
#define MAC_MDIO_DATA           0x0204
#define DMA_BUS_MODE            0x1000
#define MAC_ADDR0_HI            0x0300
#define MAC_ADDR0_LO            0x0304
#define DMA_CH0_CONTROL         0x1100
#define DMA_CH0_TX_CONTROL      0x1104
#define DMA_CH0_RX_CONTROL      0x1108
#define DMA_CH0_TX_DESC_LIST    0x1114
#define DMA_CH0_RX_DESC_LIST    0x111c
#define DMA_CH0_TX_DESC_TAIL    0x1120
#define DMA_CH0_RX_DESC_TAIL    0x1128
#define DMA_CH0_TX_RING_LENGTH  0x112c
#define DMA_CH0_RX_CONTROL2     0x1130
#define DMA_CH0_INTERRUPT_ENA   0x1134
#define DMA_CH0_CURRENT_TX_DESC  0x1144
#define DMA_CH0_CURRENT_RX_DESC  0x114c
#define DMA_CH0_STATUS          0x1160
#define DMA_CH0_MISSED_FRAME    0x1164
#define DMA_CHANNEL_STRIDE      0x80
#define DMA_CH_REG(base, channel, offset) \
    ((base) + (offset) + (channel) * DMA_CHANNEL_STRIDE)
#define DMA_STATUS_FBE          BIT(12)
#define DMA_STATUS_AIS          BIT(14)
#define DMA_INT_AIE             BIT(14)

#define RX_DESC_BASE            0x20501700
#define RX_BUFFER_BASE           0x20501900
#define RX_BUFFER2_BASE          0x20501b00
#define RX_DESC_STRIDE           32
#define TX_DESC_BASE             0x20501a00
#define TX_BUFFER_BASE           0x20501c00
#define TX_BUFFER2_BASE          0x20501d00
#define TX_DESC_STRIDE           32
#define MULTI_RX_DESC_BASE       0x20503000
#define MULTI_RX_BUFFER_BASE     0x20504000
#define MULTI_TX_DESC_BASE       0x20505000
#define MULTI_TX_BUFFER_BASE     0x20506000
#define RX_DESC_OWN              BIT(31)
#define RX_DESC_IOC              BIT(30)
#define RX_DESC_BUF1V            BIT(24)
#define RX_DESC_FD               BIT(29)
#define RX_DESC_LD               BIT(28)
#define RX_DESC_PACKET_LEN_MASK   0x7fff
#define TX_DESC_OWN              BIT(31)
#define TX_DESC_IOC              BIT(31)
#define TX_DESC_FD               BIT(29)
#define TX_DESC_LD               BIT(28)
#define DMA_STATUS_RI            BIT(6)
#define DMA_STATUS_RBU           BIT(7)
#define DMA_STATUS_TI            BIT(0)
#define DMA_STATUS_NIS           BIT(15)
#define DMA_INT_NIE              BIT(15)
#define MDIO_GB                  BIT(0)
#define MDIO_C45E                BIT(1)
#define MDIO_GOC_WRITE           (1 << 2)
#define MDIO_GOC_READ            (3 << 2)
#define MDIO_PHY_SHIFT           21
#define MDIO_REG_SHIFT           16
#define MII_BMCR                 0
#define MII_BMSR                 1
#define MII_PHYID1               2
#define MII_PHYID2               3
#define MII_ANAR                 4
#define MII_ANLPAR               5
#define MII_BMCR_AUTOEN          BIT(12)
#define MII_BMCR_FD              BIT(8)
#define MII_BMCR_ANRESTART       BIT(9)
#define MII_BMCR_PDOWN           BIT(11)
#define MII_BMCR_RESET            BIT(15)
#define MII_BMSR_LINK_ST         BIT(2)
#define MII_BMSR_AN_COMP         BIT(5)
#define MII_ANLPAR_ACK            BIT(14)
#define MII_ANAR_ADVERTISEMENT    0x01e1

static void send_frame(int fd, const uint8_t *frame, size_t length)
{
    uint32_t packet_len = htonl(length);
    struct iovec iov[] = {
        { .iov_base = &packet_len, .iov_len = sizeof(packet_len) },
        { .iov_base = (void *)frame, .iov_len = length },
    };

    g_assert_cmpint(iov_send(fd, iov, ARRAY_SIZE(iov), 0,
                             sizeof(packet_len) + length),
                    ==, sizeof(packet_len) + length);
}

static void receive_frame(int fd, uint8_t *frame, size_t length)
{
    uint32_t packet_len;
    size_t received = 0;

    while (received < sizeof(packet_len)) {
        struct pollfd pfd = { .fd = fd, .events = POLLIN };
        ssize_t ret;

        g_assert_cmpint(poll(&pfd, 1, 1000), ==, 1);
        ret = recv(fd, (uint8_t *)&packet_len + received,
                   sizeof(packet_len) - received, MSG_DONTWAIT);
        g_assert_cmpint(ret, >, 0);
        received += ret;
    }
    g_assert_cmpuint(ntohl(packet_len), ==, length);

    received = 0;
    while (received < length) {
        struct pollfd pfd = { .fd = fd, .events = POLLIN };
        ssize_t ret;

        g_assert_cmpint(poll(&pfd, 1, 1000), ==, 1);
        ret = recv(fd, frame + received, length - received, MSG_DONTWAIT);
        g_assert_cmpint(ret, >, 0);
        received += ret;
    }
}

static uint32_t wait_for_rx_completion(QTestState *qts, uint32_t desc_addr)
{
    uint32_t rdes3 = RX_DESC_OWN;

    for (int i = 0; i < 100; i++) {
        qtest_clock_step(qts, 1000000);
        rdes3 = qtest_readl(qts, desc_addr + 12);
        if (!(rdes3 & RX_DESC_OWN)) {
            break;
        }
    }
    return rdes3;
}

static uint16_t eqos_mdio_read(QTestState *qts, uint32_t base,
                               uint8_t phy, uint8_t reg)
{
    uint32_t command = MDIO_GB | MDIO_GOC_READ |
                       ((uint32_t)phy << MDIO_PHY_SHIFT) |
                       ((uint32_t)reg << MDIO_REG_SHIFT);

    qtest_writel(qts, base + MAC_MDIO_ADDRESS, command);
    g_assert_cmphex(qtest_readl(qts, base + MAC_MDIO_ADDRESS) & MDIO_GB,
                    ==, 0);
    return qtest_readl(qts, base + MAC_MDIO_DATA) & 0xffff;
}

static void eqos_mdio_write(QTestState *qts, uint32_t base,
                            uint8_t phy, uint8_t reg, uint16_t data)
{
    uint32_t command = MDIO_GB | MDIO_GOC_WRITE |
                       ((uint32_t)phy << MDIO_PHY_SHIFT) |
                       ((uint32_t)reg << MDIO_REG_SHIFT);

    qtest_writel(qts, base + MAC_MDIO_DATA, data);
    qtest_writel(qts, base + MAC_MDIO_ADDRESS, command);
    g_assert_cmphex(qtest_readl(qts, base + MAC_MDIO_ADDRESS) & MDIO_GB,
                    ==, 0);
}

static void set_nic_link(QTestState *qts, unsigned index, bool up)
{
    g_autofree char *response =
        qtest_hmp(qts, "set_link net%u %s", index, up ? "on" : "off");

    g_assert_nonnull(response);
    g_assert_null(strstr(response, "Error"));
}

static void test_eqos_rx(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
        0x45, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01,
        0xc0, 0xa8, 0x00, 0x02, 0x12, 0x34, 0x56, 0x78,
        0x00, 0x1a, 0x00, 0x00,
        0x53, 0x33, 0x4b, 0x33, 0x38, 0x39, 0x2d, 0x52,
        0x58, 0x2d, 0x54, 0x45, 0x53, 0x54, 0x00, 0x00,
    };
    uint32_t descriptor[4] = {
        cpu_to_le32(RX_BUFFER_BASE),
        0,
        0,
        cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
    };
    uint32_t descriptor2[4] = {
        cpu_to_le32(RX_BUFFER2_BASE),
        0,
        0,
        cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
    };
    uint8_t received[sizeof(packet) + 4] = { 0 };
    uint8_t received2[sizeof(packet) + 4] = { 0 };
    uint8_t rejected_packet[sizeof(packet)];
    int sockets[2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");
    g_assert_false(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));

    qtest_memwrite(qts, RX_DESC_BASE, descriptor, sizeof(descriptor));
    qtest_memwrite(qts, RX_DESC_BASE + RX_DESC_STRIDE, descriptor2,
                   sizeof(descriptor2));
    qtest_memwrite(qts, RX_BUFFER_BASE, received, sizeof(received));
    qtest_memwrite(qts, RX_BUFFER2_BASE, received2, sizeof(received2));

    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC0_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_LIST, RX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL2, 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_TAIL,
                 RX_DESC_BASE + 2 * RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_RI | DMA_STATUS_NIS);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL, 0x80081);

    memcpy(rejected_packet, packet, sizeof(packet));
    rejected_packet[0] = 0x02;
    send_frame(sockets[0], rejected_packet, sizeof(rejected_packet));
    for (int i = 0; i < 10; i++) {
        qtest_clock_step(qts, 1000000);
    }
    g_assert_cmphex(qtest_readl(qts, RX_DESC_BASE + 12) & RX_DESC_OWN,
                    ==, RX_DESC_OWN);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_MISSED_FRAME),
                    ==, 1);

    send_frame(sockets[0], packet, sizeof(packet));
    uint32_t rdes3 = wait_for_rx_completion(qts, RX_DESC_BASE);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_MISSED_FRAME),
                    ==, 1);
    g_assert_cmphex(rdes3, ==,
                    RX_DESC_FD | RX_DESC_LD |
                    ((sizeof(packet) + 4) & RX_DESC_PACKET_LEN_MASK));

    qtest_memread(qts, RX_BUFFER_BASE, received, sizeof(received));
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
    g_assert_cmpmem(received + sizeof(packet), 4,
                    ((const uint8_t[]){ 0xe1, 0xa6, 0x4a, 0xaf }), 4);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_RI | DMA_STATUS_NIS),
                    ==, DMA_STATUS_RI | DMA_STATUS_NIS);
    g_assert_true(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_TX_IRQ));
    g_assert_true(qtest_get_irq(qts, GMAC0_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, RX_DESC_BASE + RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_RI | DMA_STATUS_NIS);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_RI | DMA_STATUS_NIS), ==, 0);
    g_assert_false(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));

    send_frame(sockets[0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, RX_DESC_BASE +
                                           RX_DESC_STRIDE), ==,
                    RX_DESC_FD | RX_DESC_LD |
                    ((sizeof(packet) + 4) & RX_DESC_PACKET_LEN_MASK));
    qtest_memread(qts, RX_BUFFER2_BASE, received2, sizeof(received2));
    g_assert_cmpmem(received2, sizeof(packet), packet, sizeof(packet));
    g_assert_cmpmem(received2 + sizeof(packet), 4,
                    ((const uint8_t[]){ 0xe1, 0xa6, 0x4a, 0xaf }), 4);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, RX_DESC_BASE + 2 * RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_RI | DMA_STATUS_NIS);

    qtest_memwrite(qts, RX_DESC_BASE, descriptor, sizeof(descriptor));
    memset(received, 0, sizeof(received));
    qtest_memwrite(qts, RX_BUFFER_BASE, received, sizeof(received));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_TAIL,
                 RX_DESC_BASE + RX_DESC_STRIDE);
    send_frame(sockets[0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, RX_DESC_BASE), ==,
                    RX_DESC_FD | RX_DESC_LD |
                    ((sizeof(packet) + 4) & RX_DESC_PACKET_LEN_MASK));
    qtest_memread(qts, RX_BUFFER_BASE, received, sizeof(received));
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
    g_assert_cmpmem(received + sizeof(packet), 4,
                    ((const uint8_t[]){ 0xe1, 0xa6, 0x4a, 0xaf }), 4);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, RX_DESC_BASE + RX_DESC_STRIDE);

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_eqos_rx_multidesc_and_ring_exhaustion(void)
{
    uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
    };
    uint32_t descriptor[2][4] = {
        {
            cpu_to_le32(RX_BUFFER_BASE), 0, 0,
            cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
        },
        {
            cpu_to_le32(RX_BUFFER2_BASE), 0, 0,
            cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
        },
    };
    uint8_t received[2][32] = { { 0 } };
    int sockets[2];
    QTestState *qts;

    for (size_t i = 6; i < sizeof(packet); i++) {
        packet[i] = i;
    }

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);

    qtest_memwrite(qts, RX_DESC_BASE, descriptor[0], sizeof(descriptor[0]));
    qtest_memwrite(qts, RX_DESC_BASE + RX_DESC_STRIDE, descriptor[1],
                   sizeof(descriptor[1]));
    qtest_memwrite(qts, RX_BUFFER_BASE, received[0], sizeof(received[0]));
    qtest_memwrite(qts, RX_BUFFER2_BASE, received[1], sizeof(received[1]));
    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC0_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_LIST, RX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL2, (32 << 17) | 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_TAIL,
                 RX_DESC_BASE + 2 * RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_RI | DMA_INT_NIE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL, 0x80081);

    send_frame(sockets[0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, RX_DESC_BASE +
                                           RX_DESC_STRIDE), ==,
                    RX_DESC_LD | (sizeof(packet) + 4));
    g_assert_cmphex(qtest_readl(qts, RX_DESC_BASE + 12), ==, RX_DESC_FD);
    qtest_memread(qts, RX_BUFFER_BASE, received[0], sizeof(received[0]));
    qtest_memread(qts, RX_BUFFER2_BASE, received[1], sizeof(received[1]));
    g_assert_cmpmem(received[0], sizeof(received[0]), packet,
                    sizeof(received[0]));
    g_assert_cmpmem(received[1], 28, packet + 32, 28);
    g_assert_cmpmem(received[1] + 28, 4,
                    ((const uint8_t[]){ 0xb3, 0xf8, 0x8a, 0xf1 }), 4);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, RX_DESC_BASE + 2 * RX_DESC_STRIDE);

    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS, DMA_STATUS_RI);
    send_frame(sockets[0], packet, sizeof(packet));
    for (int i = 0; i < 10; i++) {
        qtest_clock_step(qts, 1000000);
    }
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    DMA_STATUS_RBU, ==, DMA_STATUS_RBU);
    g_assert_cmphex(qtest_readl(qts, RX_DESC_BASE + 12), ==, RX_DESC_FD);
    g_assert_cmphex(qtest_readl(qts, RX_DESC_BASE + RX_DESC_STRIDE + 12),
                    ==, RX_DESC_LD | (sizeof(packet) + 4));

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_eqos_tx(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
        0x45, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01,
        0xc0, 0xa8, 0x00, 0x02, 0x12, 0x34, 0x56, 0x78,
        0x00, 0x1a, 0x00, 0x00,
        0x53, 0x33, 0x4b, 0x33, 0x38, 0x39, 0x2d, 0x54,
        0x58, 0x2d, 0x54, 0x45, 0x53, 0x54, 0x00, 0x00,
    };
    uint32_t descriptor[8] = {
        cpu_to_le32(TX_BUFFER_BASE),
        0,
        cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
        cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD | sizeof(packet)),
    };
    uint32_t descriptor2[8] = {
        cpu_to_le32(TX_BUFFER2_BASE),
        0,
        cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
        cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD | sizeof(packet)),
    };
    uint8_t transmitted[sizeof(packet)] = { 0 };
    int sockets[2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");
    g_assert_false(qtest_get_irq(qts, GMAC0_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));

    qtest_memwrite(qts, TX_DESC_BASE, descriptor, sizeof(descriptor));
    qtest_memwrite(qts, TX_DESC_BASE + TX_DESC_STRIDE, descriptor2,
                   sizeof(descriptor2));
    qtest_memwrite(qts, TX_BUFFER_BASE, packet, sizeof(packet));
    qtest_memwrite(qts, TX_BUFFER2_BASE, packet, sizeof(packet));
    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(1));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_DESC_LIST, TX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_RING_LENGTH, 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_TI | DMA_INT_NIE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_CONTROL, BIT(0));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_DESC_TAIL,
                 TX_DESC_BASE + TX_DESC_STRIDE);

    receive_frame(sockets[0], transmitted, sizeof(transmitted));
    g_assert_cmpmem(transmitted, sizeof(transmitted), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, TX_DESC_BASE + 12) & RX_DESC_OWN, ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_TI | DMA_STATUS_NIS),
                    ==, DMA_STATUS_TI | DMA_STATUS_NIS);
    g_assert_true(qtest_get_irq(qts, GMAC0_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_TX_DESC),
                    ==, TX_DESC_BASE + TX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_TI | DMA_STATUS_NIS);
    g_assert_false(qtest_get_irq(qts, GMAC0_TX_IRQ));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_DESC_TAIL,
                 TX_DESC_BASE + 2 * TX_DESC_STRIDE);
    receive_frame(sockets[0], transmitted, sizeof(transmitted));
    g_assert_cmpmem(transmitted, sizeof(transmitted), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, TX_DESC_BASE + TX_DESC_STRIDE + 12) &
                    TX_DESC_OWN, ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_TX_DESC),
                    ==, TX_DESC_BASE + 2 * TX_DESC_STRIDE);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_TI | DMA_STATUS_NIS),
                    ==, DMA_STATUS_TI | DMA_STATUS_NIS);
    g_assert_true(qtest_get_irq(qts, GMAC0_TX_IRQ));

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_eqos_tx_multidesc(void)
{
    uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
    };
    uint32_t descriptor[2][4] = {
        {
            cpu_to_le32(TX_BUFFER_BASE), 0, cpu_to_le32(30),
            cpu_to_le32(TX_DESC_OWN | TX_DESC_FD),
        },
        {
            cpu_to_le32(TX_BUFFER2_BASE), 0,
            cpu_to_le32(TX_DESC_IOC | 30),
            cpu_to_le32(TX_DESC_OWN | TX_DESC_LD | sizeof(packet)),
        },
    };
    uint8_t transmitted[sizeof(packet)] = { 0 };
    int sockets[2];
    QTestState *qts;

    for (size_t i = 6; i < sizeof(packet); i++) {
        packet[i] = i;
    }

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);

    qtest_memwrite(qts, TX_DESC_BASE, descriptor[0], sizeof(descriptor[0]));
    qtest_memwrite(qts, TX_DESC_BASE + TX_DESC_STRIDE, descriptor[1],
                   sizeof(descriptor[1]));
    qtest_memwrite(qts, TX_BUFFER_BASE, packet, 30);
    qtest_memwrite(qts, TX_BUFFER2_BASE, packet + 30, 30);
    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(1));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_DESC_LIST, TX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_RING_LENGTH, 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_TI | DMA_INT_NIE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_CONTROL, BIT(0));
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_TX_DESC_TAIL,
                 TX_DESC_BASE + 2 * TX_DESC_STRIDE);

    receive_frame(sockets[0], transmitted, sizeof(transmitted));
    g_assert_cmpmem(transmitted, sizeof(transmitted), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, TX_DESC_BASE + 12) & TX_DESC_OWN, ==, 0);
    g_assert_cmphex(qtest_readl(qts, TX_DESC_BASE + TX_DESC_STRIDE + 12) &
                    TX_DESC_OWN, ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_TX_DESC),
                    ==, TX_DESC_BASE + 2 * TX_DESC_STRIDE);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_TI | DMA_STATUS_NIS),
                    ==, DMA_STATUS_TI | DMA_STATUS_NIS);

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_gmac1_datapath_and_irqs(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
        0x45, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01,
        0xc0, 0xa8, 0x00, 0x02, 0x12, 0x34, 0x56, 0x78,
        0x00, 0x1a, 0x00, 0x00,
        0x53, 0x33, 0x4b, 0x33, 0x38, 0x39, 0x2d, 0x47,
        0x4d, 0x41, 0x43, 0x31, 0x2d, 0x54, 0x45, 0x53,
        0x54, 0x00,
    };
    const uint32_t rx_desc_base = 0x20502000;
    const uint32_t rx_buffer_base = 0x20502200;
    const uint32_t tx_desc_base = 0x20502400;
    const uint32_t tx_buffer_base = 0x20502600;
    uint32_t rx_desc[4] = {
        cpu_to_le32(rx_buffer_base), 0, 0,
        cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
    };
    uint32_t tx_desc[4] = {
        cpu_to_le32(tx_buffer_base), 0,
        cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
        cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD | sizeof(packet)),
    };
    uint8_t received[sizeof(packet) + 4] = { 0 };
    uint8_t transmitted[sizeof(packet)] = { 0 };
    int sockets[2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac1",
                      sockets[1]);
    close(sockets[1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");
    g_assert_false(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_RX_IRQ));

    qtest_memwrite(qts, tx_desc_base, tx_desc, sizeof(tx_desc));
    qtest_memwrite(qts, tx_buffer_base, packet, sizeof(packet));
    qtest_writel(qts, GMAC1_BASE + MAC_CONFIG, BIT(1));
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_TX_DESC_LIST, tx_desc_base);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_TI | DMA_INT_NIE);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_TX_CONTROL, BIT(0));
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_TX_DESC_TAIL,
                 tx_desc_base + TX_DESC_STRIDE);
    receive_frame(sockets[0], transmitted, sizeof(transmitted));
    g_assert_cmpmem(transmitted, sizeof(transmitted), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, tx_desc_base + 12) & TX_DESC_OWN, ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC1_BASE + DMA_CH0_CURRENT_TX_DESC),
                    ==, tx_desc_base + TX_DESC_STRIDE);
    g_assert_true(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_true(qtest_get_irq(qts, GMAC1_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS), ==, 0);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_TI | DMA_STATUS_NIS);
    g_assert_false(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_TX_IRQ));

    qtest_memwrite(qts, rx_desc_base, rx_desc, sizeof(rx_desc));
    qtest_memwrite(qts, rx_buffer_base, received, sizeof(received));
    qtest_writel(qts, GMAC1_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC1_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC1_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC1_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_RX_DESC_LIST, rx_desc_base);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_RX_CONTROL2, 0);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_RX_DESC_TAIL,
                 rx_desc_base + RX_DESC_STRIDE);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_RI | DMA_INT_NIE);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_RX_CONTROL, 0x80081);
    send_frame(sockets[0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, rx_desc_base), ==,
                    RX_DESC_FD | RX_DESC_LD | (sizeof(packet) + 4));
    qtest_memread(qts, rx_buffer_base, received, sizeof(received));
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, GMAC1_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, rx_desc_base + RX_DESC_STRIDE);
    g_assert_true(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_TX_IRQ));
    g_assert_true(qtest_get_irq(qts, GMAC1_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS), ==, 0);
    qtest_writel(qts, GMAC1_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_RI | DMA_STATUS_NIS);
    g_assert_false(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_RX_IRQ));

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_eqos_mdio_phy(void)
{
    int sockets[2][2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets[0]), ==, 0);
    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets[1]), ==, 0);
    qts = qtest_initf("-machine s32k389 "
                      "-nic socket,fd=%d,model=gmac0,id=net0 "
                      "-nic socket,fd=%d,model=gmac1,id=net1",
                      sockets[0][1], sockets[1][1]);
    close(sockets[0][1]);
    close(sockets[1][1]);

    for (int i = 0; i < 2; i++) {
        uint32_t base = i ? GMAC1_BASE : GMAC0_BASE;
        uint16_t bmcr = MII_BMCR_AUTOEN | MII_BMCR_FD;

        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_PHYID1), ==,
                        0x0362);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_PHYID2), ==,
                        0x5e6a);
        g_assert_cmphex(eqos_mdio_read(qts, base, 1, MII_PHYID1), ==,
                        0xffff);
        g_assert_cmphex(eqos_mdio_read(qts, base, 31, MII_PHYID1), ==,
                        0xffff);
        set_nic_link(qts, i, false);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMSR) &
                        (MII_BMSR_LINK_ST | MII_BMSR_AN_COMP), ==, 0);
        set_nic_link(qts, i, true);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMSR) &
                        (MII_BMSR_LINK_ST | MII_BMSR_AN_COMP), ==,
                        MII_BMSR_LINK_ST | MII_BMSR_AN_COMP);

        eqos_mdio_write(qts, base, 0, MII_ANAR, MII_ANAR_ADVERTISEMENT);
        eqos_mdio_write(qts, base, 0, MII_BMCR,
                        bmcr | MII_BMCR_ANRESTART);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMCR), ==,
                        bmcr & ~MII_BMCR_ANRESTART);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_ANAR), ==,
                        MII_ANAR_ADVERTISEMENT);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_ANLPAR), ==,
                        (MII_ANAR_ADVERTISEMENT & 0x0fff) |
                        MII_ANLPAR_ACK);

        eqos_mdio_write(qts, base, 0, MII_BMCR,
                        bmcr | MII_BMCR_PDOWN);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMSR) &
                        (MII_BMSR_LINK_ST | MII_BMSR_AN_COMP), ==, 0);
        eqos_mdio_write(qts, base, 0, MII_BMCR, bmcr);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMSR) &
                        (MII_BMSR_LINK_ST | MII_BMSR_AN_COMP), ==,
                        MII_BMSR_LINK_ST | MII_BMSR_AN_COMP);

        eqos_mdio_write(qts, base, 0, MII_BMCR,
                        bmcr | MII_BMCR_RESET);
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMCR), ==,
                        MII_BMCR_AUTOEN | MII_BMCR_FD | BIT(6));
        g_assert_cmphex(eqos_mdio_read(qts, base, 0, MII_BMSR) &
                        (MII_BMSR_LINK_ST | MII_BMSR_AN_COMP), ==,
                        MII_BMSR_LINK_ST | MII_BMSR_AN_COMP);

        qtest_writel(qts, base + MAC_MDIO_ADDRESS,
                     MDIO_GB | (2 << 2));
        g_assert_cmphex(qtest_readl(qts, base + MAC_MDIO_ADDRESS) & MDIO_GB,
                        ==, 0);
        qtest_writel(qts, base + MAC_MDIO_ADDRESS,
                     MDIO_GB | MDIO_C45E | MDIO_GOC_READ);
        g_assert_cmphex(qtest_readl(qts, base + MAC_MDIO_ADDRESS) & MDIO_GB,
                        ==, 0);
        g_assert_cmphex(qtest_readl(qts, base + MAC_MDIO_DATA) & 0xffff,
                        ==, 0xffff);
    }

    qtest_quit(qts);
    close(sockets[0][0]);
    close(sockets[1][0]);
}

static void test_eqos_dma_error_reset_recovery(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
    };
    uint32_t descriptor[4] = {
        cpu_to_le32(0xfffff000),
        cpu_to_le32(0xffffffff),
        0,
        cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
    };
    uint8_t received[sizeof(packet) + 4] = { 0 };
    int sockets[2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");

    qtest_memwrite(qts, RX_DESC_BASE, descriptor, sizeof(descriptor));
    qtest_memwrite(qts, RX_BUFFER_BASE, received, sizeof(received));
    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC0_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_LIST, RX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL2, 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_TAIL,
                 RX_DESC_BASE + RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_INTERRUPT_ENA,
                 DMA_STATUS_FBE | DMA_STATUS_AIS | DMA_INT_AIE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL, 0x80081);

    send_frame(sockets[0], packet, sizeof(packet));
    for (int i = 0; i < 100; i++) {
        qtest_clock_step(qts, 1000000);
    }
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    DMA_STATUS_FBE, ==, DMA_STATUS_FBE);
    g_assert_true(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, RX_DESC_BASE + 12) & RX_DESC_OWN,
                    ==, RX_DESC_OWN);

    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS, DMA_STATUS_FBE);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    DMA_STATUS_FBE, ==, 0);
    g_assert_false(qtest_get_irq(qts, GMAC0_IRQ));

    qtest_writel(qts, GMAC0_BASE + DMA_BUS_MODE, BIT(0));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS), ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL), ==, 0);
    g_assert_false(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC0_RX_IRQ));

    descriptor[0] = cpu_to_le32(RX_BUFFER_BASE);
    descriptor[1] = 0;
    qtest_memwrite(qts, RX_DESC_BASE, descriptor, sizeof(descriptor));
    memset(received, 0, sizeof(received));
    qtest_memwrite(qts, RX_BUFFER_BASE, received, sizeof(received));
    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_LIST, RX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL2, 1);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_DESC_TAIL,
                 RX_DESC_BASE + RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_RX_CONTROL, 0x80081);

    send_frame(sockets[0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, RX_DESC_BASE), ==,
                    RX_DESC_FD | RX_DESC_LD | (sizeof(packet) + 4));
    qtest_memread(qts, RX_BUFFER_BASE, received, sizeof(received));
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));

    qtest_quit(qts);
    close(sockets[0]);
}

static void test_eqos_dma_channels_and_queues(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
        0x45, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01,
        0xc0, 0xa8, 0x00, 0x02, 0x12, 0x34, 0x56, 0x78,
        0x00, 0x1a, 0x00, 0x00,
        0x53, 0x33, 0x4b, 0x33, 0x38, 0x39, 0x2d, 0x51,
        0x55, 0x45, 0x55, 0x45, 0x53, 0x00, 0x00, 0x00,
    };
    static const int tx_irqs[] = {
        GMAC0_TX_IRQ, GMAC0_CH1_TX_IRQ, GMAC0_CH2_TX_IRQ,
    };
    static const int rx_irqs[] = {
        GMAC0_RX_IRQ, GMAC0_CH1_RX_IRQ, GMAC0_CH2_RX_IRQ,
    };
    uint8_t tagged_packet[sizeof(packet) + 4];
    uint8_t received[sizeof(packet) + 8] = { 0 };
    int sockets[2][2];
    QTestState *qts;

    memcpy(tagged_packet, packet, 12);
    tagged_packet[12] = 0x81;
    tagged_packet[13] = 0x00;
    tagged_packet[14] = 0xa0;
    tagged_packet[15] = 0x00;
    tagged_packet[16] = 0x08;
    tagged_packet[17] = 0x00;
    memcpy(tagged_packet + 18, packet + 14, sizeof(packet) - 14);

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets[0]), ==, 0);
    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets[1]), ==, 0);
    qts = qtest_initf("-machine s32k389 "
                      "-nic socket,fd=%d,model=gmac0,id=net0 "
                      "-nic socket,fd=%d,model=gmac1,id=net1",
                      sockets[0][1], sockets[1][1]);
    close(sockets[0][1]);
    close(sockets[1][1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");

    qtest_writel(qts, GMAC0_BASE + MAC_CONFIG, BIT(0) | BIT(1));
    qtest_writel(qts, GMAC0_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC0_BASE + MAC_ADDR0_LO, 0x33445566);

    for (unsigned channel = 0; channel < 3; channel++) {
        uint32_t desc_addr = MULTI_RX_DESC_BASE +
                             channel * RX_DESC_STRIDE;
        uint32_t buffer_addr = MULTI_RX_BUFFER_BASE + channel * 0x100;
        uint32_t descriptor[4] = {
            cpu_to_le32(buffer_addr),
            0,
            0,
            cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
        };

        qtest_memwrite(qts, desc_addr, descriptor, sizeof(descriptor));
        qtest_memwrite(qts, buffer_addr, received, sizeof(received));
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel, DMA_CH0_CONTROL),
                     2 << 18);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_RX_DESC_LIST), desc_addr);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_RX_CONTROL2), 0);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_RX_DESC_TAIL),
                     desc_addr + RX_DESC_STRIDE);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_INTERRUPT_ENA),
                     DMA_STATUS_RI | DMA_INT_NIE);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_RX_CONTROL), 0x80091);
    }

    /* Queue 1 carries untagged traffic; VLAN PCP 5 selects queue 2. */
    qtest_writel(qts, GMAC0_BASE + MAC_RXQ_CONTROL0,
                 (2 << 2) | (2 << 4));
    qtest_writel(qts, GMAC0_BASE + MAC_RXQ_CONTROL1, 1 << 12);
    qtest_writel(qts, GMAC0_BASE + MAC_RXQ_CONTROL2, BIT(16 + 5));
    qtest_writel(qts, GMAC0_BASE + MTL_RXQ_DMA_MAP0,
                 (1 << 8) | (2 << 16));

    send_frame(sockets[0][0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(
                        qts, MULTI_RX_DESC_BASE + RX_DESC_STRIDE), ==,
                    RX_DESC_FD | RX_DESC_LD | (sizeof(packet) + 4));
    qtest_memread(qts, MULTI_RX_BUFFER_BASE + 0x100, received,
                  sizeof(packet) + 4);
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
    g_assert_true(qtest_get_irq(qts, GMAC0_IRQ));
    g_assert_true(qtest_get_irq(qts, rx_irqs[1]));
    g_assert_false(qtest_get_irq(qts, rx_irqs[0]));
    qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, 1, DMA_CH0_STATUS),
                 DMA_STATUS_RI | DMA_STATUS_NIS);

    send_frame(sockets[0][0], tagged_packet, sizeof(tagged_packet));
    g_assert_cmphex(wait_for_rx_completion(
                        qts, MULTI_RX_DESC_BASE + 2 * RX_DESC_STRIDE), ==,
                    RX_DESC_FD | RX_DESC_LD | (sizeof(tagged_packet) + 4));
    qtest_memread(qts, MULTI_RX_BUFFER_BASE + 0x200, received,
                  sizeof(tagged_packet) + 4);
    g_assert_cmpmem(received, sizeof(tagged_packet), tagged_packet,
                    sizeof(tagged_packet));
    g_assert_true(qtest_get_irq(qts, rx_irqs[2]));
    g_assert_false(qtest_get_irq(qts, rx_irqs[1]));
    qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, 2, DMA_CH0_STATUS),
                 DMA_STATUS_RI | DMA_STATUS_NIS);

    for (unsigned channel = 1; channel < 3; channel++) {
        uint32_t desc_addr = MULTI_TX_DESC_BASE +
                             channel * TX_DESC_STRIDE;
        uint32_t buffer_addr = MULTI_TX_BUFFER_BASE + channel * 0x100;
        uint32_t descriptor[8] = {
            cpu_to_le32(buffer_addr),
            0,
            cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
            cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD |
                        sizeof(packet)),
        };

        qtest_memwrite(qts, desc_addr, descriptor, sizeof(descriptor));
        qtest_memwrite(qts, buffer_addr, packet, sizeof(packet));
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel, DMA_CH0_CONTROL),
                     2 << 18);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_TX_DESC_LIST), desc_addr);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_TX_RING_LENGTH), 0);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_INTERRUPT_ENA),
                     DMA_STATUS_TI | DMA_INT_NIE);
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_TX_CONTROL), BIT(0));
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel,
                                     DMA_CH0_TX_DESC_TAIL),
                     desc_addr + TX_DESC_STRIDE);

        receive_frame(sockets[0][0], received, sizeof(packet));
        g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
        g_assert_cmphex(qtest_readl(qts, desc_addr + 12) & TX_DESC_OWN, ==,
                        0);
        g_assert_true(qtest_get_irq(qts, tx_irqs[channel]));
        g_assert_false(qtest_get_irq(qts, tx_irqs[0]));
        qtest_writel(qts, DMA_CH_REG(GMAC0_BASE, channel, DMA_CH0_STATUS),
                     DMA_STATUS_TI | DMA_STATUS_NIS);
        g_assert_false(qtest_get_irq(qts, tx_irqs[channel]));
    }

    uint32_t gmac1_rx_desc = MULTI_RX_DESC_BASE + 0x300;
    uint32_t gmac1_rx_buffer = MULTI_RX_BUFFER_BASE + 0x300;
    uint32_t gmac1_rx_descriptor[4] = {
        cpu_to_le32(gmac1_rx_buffer),
        0,
        0,
        cpu_to_le32(RX_DESC_OWN | RX_DESC_IOC | RX_DESC_BUF1V),
    };
    qtest_memwrite(qts, gmac1_rx_desc, gmac1_rx_descriptor,
                   sizeof(gmac1_rx_descriptor));
    qtest_writel(qts, GMAC1_BASE + MAC_CONFIG, BIT(0));
    qtest_writel(qts, GMAC1_BASE + MAC_PACKET_FILTER, 0);
    qtest_writel(qts, GMAC1_BASE + MAC_ADDR0_HI, 0x80001122);
    qtest_writel(qts, GMAC1_BASE + MAC_ADDR0_LO, 0x33445566);
    qtest_writel(qts, GMAC1_BASE + MTL_RXQ_DMA_MAP0, 2);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_CONTROL), 2 << 18);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_RX_DESC_LIST),
                 gmac1_rx_desc);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_RX_CONTROL2), 0);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_RX_DESC_TAIL),
                 gmac1_rx_desc + RX_DESC_STRIDE);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_INTERRUPT_ENA),
                 DMA_STATUS_RI | DMA_INT_NIE);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_RX_CONTROL),
                 0x80091);
    send_frame(sockets[1][0], packet, sizeof(packet));
    g_assert_cmphex(wait_for_rx_completion(qts, gmac1_rx_desc), ==,
                    RX_DESC_FD | RX_DESC_LD | (sizeof(packet) + 4));
    g_assert_true(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_true(qtest_get_irq(qts, GMAC1_CH2_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS), ==, 0);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 2, DMA_CH0_STATUS),
                 DMA_STATUS_RI | DMA_STATUS_NIS);

    uint32_t gmac1_tx_desc = MULTI_TX_DESC_BASE + 0x300;
    uint32_t gmac1_tx_buffer = MULTI_TX_BUFFER_BASE + 0x300;
    uint32_t gmac1_tx_descriptor[8] = {
        cpu_to_le32(gmac1_tx_buffer),
        0,
        cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
        cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD | sizeof(packet)),
    };
    qtest_memwrite(qts, gmac1_tx_desc, gmac1_tx_descriptor,
                   sizeof(gmac1_tx_descriptor));
    qtest_memwrite(qts, gmac1_tx_buffer, packet, sizeof(packet));
    qtest_writel(qts, GMAC1_BASE + MAC_CONFIG, BIT(1));
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_CONTROL), 2 << 18);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_TX_DESC_LIST),
                 gmac1_tx_desc);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_TX_RING_LENGTH), 0);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_INTERRUPT_ENA),
                 DMA_STATUS_TI | DMA_INT_NIE);
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_TX_CONTROL), BIT(0));
    qtest_writel(qts, DMA_CH_REG(GMAC1_BASE, 1, DMA_CH0_TX_DESC_TAIL),
                 gmac1_tx_desc + TX_DESC_STRIDE);
    receive_frame(sockets[1][0], received, sizeof(packet));
    g_assert_cmpmem(received, sizeof(packet), packet, sizeof(packet));
    g_assert_true(qtest_get_irq(qts, GMAC1_IRQ));
    g_assert_true(qtest_get_irq(qts, GMAC1_CH1_TX_IRQ));
    g_assert_false(qtest_get_irq(qts, GMAC1_CH2_RX_IRQ));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS), ==, 0);

    qtest_quit(qts);
    close(sockets[0][0]);
    close(sockets[1][0]);
}

#endif

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
#ifndef _WIN32
    qtest_add_func("s32k389/gmac/eqos-rx", test_eqos_rx);
    qtest_add_func("s32k389/gmac/eqos-rx-multidesc",
                   test_eqos_rx_multidesc_and_ring_exhaustion);
    qtest_add_func("s32k389/gmac/eqos-tx", test_eqos_tx);
    qtest_add_func("s32k389/gmac/eqos-tx-multidesc",
                   test_eqos_tx_multidesc);
    qtest_add_func("s32k389/gmac/gmac1-datapath-irqs",
                   test_gmac1_datapath_and_irqs);
    qtest_add_func("s32k389/gmac/eqos-mdio-phy", test_eqos_mdio_phy);
    qtest_add_func("s32k389/gmac/eqos-dma-error-reset",
                   test_eqos_dma_error_reset_recovery);
    qtest_add_func("s32k389/gmac/eqos-dma-channels-queues",
                   test_eqos_dma_channels_and_queues);
#endif
    return g_test_run();
}
