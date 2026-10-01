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
#define MAC_CONFIG              0x0000
#define MAC_PACKET_FILTER       0x0008
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

#define RX_DESC_BASE            0x20501700
#define RX_BUFFER_BASE           0x20501900
#define RX_BUFFER2_BASE          0x20501b00
#define RX_DESC_STRIDE           32
#define TX_DESC_BASE             0x20501a00
#define TX_BUFFER_BASE           0x20501c00
#define TX_BUFFER2_BASE          0x20501d00
#define TX_DESC_STRIDE           32
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
#define DMA_STATUS_TI            BIT(0)
#define DMA_STATUS_NIS           BIT(15)
#define DMA_INT_NIE              BIT(15)

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
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d",
                      sockets[1]);
    close(sockets[1]);

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
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_RX_DESC),
                    ==, RX_DESC_BASE + RX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_RI | DMA_STATUS_NIS);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_STATUS) &
                    (DMA_STATUS_RI | DMA_STATUS_NIS), ==, 0);

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
    qts = qtest_initf("-machine s32k389 -nic socket,fd=%d",
                      sockets[1]);
    close(sockets[1]);

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
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + DMA_CH0_CURRENT_TX_DESC),
                    ==, TX_DESC_BASE + TX_DESC_STRIDE);
    qtest_writel(qts, GMAC0_BASE + DMA_CH0_STATUS,
                 DMA_STATUS_TI | DMA_STATUS_NIS);
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

    qtest_quit(qts);
    close(sockets[0]);
}

#endif

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
#ifndef _WIN32
    qtest_add_func("s32k389/gmac/eqos-rx", test_eqos_rx);
    qtest_add_func("s32k389/gmac/eqos-tx", test_eqos_tx);
#endif
    return g_test_run();
}
