/*
 * S32K388 board peripheral map smoke tests.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "qemu/osdep.h"
#include "libqtest.h"
#include "hw/watchdog/s32k3_swt.h"

#define FLEXCAN6_BASE       0x4031c000
#define FLEXCAN7_BASE       0x40320000
#define FLEXCAN_RXMGMASK    0x0010
#define SWT0_BASE           0x40270000
#define SWT3_BASE           0x40070000
#define GMAC0_BASE          0x40484000
#define GMAC_MAC_CONFIG     0x0000

#ifndef _WIN32
#include "qemu/bswap.h"
#include "qemu/iov.h"
#include "qemu/sockets.h"
#include <poll.h>

#define GMAC_CH0_CONTROL    0x1100
#define GMAC_CH0_TX_CTRL    0x1104
#define GMAC_CH0_TX_DESC    0x1114
#define GMAC_CH0_TX_TAIL    0x1120
#define GMAC_CH0_TX_RING    0x112c
#define GMAC_CH0_INT_ENA    0x1134
#define GMAC_CH0_STATUS     0x1160
#define GMAC_TX_IRQ         225
#define GMAC_DMA_STATUS_TI  BIT(0)
#define GMAC_DMA_INT_NIE    BIT(15)
#define TX_DESC_BASE        0x20490000
#define TX_BUFFER_BASE      0x20491000
#define TX_DESC_OWN         BIT(31)
#define TX_DESC_FD          BIT(29)
#define TX_DESC_LD          BIT(28)
#define TX_DESC_IOC         BIT(31)
#define TX_DESC_STRIDE      32

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
#endif

static void test_s32k388_peripheral_map(void)
{
    QTestState *qts = qtest_init("-machine s32k388");

    qtest_irq_intercept_in(qts, "/machine/armv7m");

    g_assert_cmphex(qtest_readl(qts, FLEXCAN6_BASE + FLEXCAN_RXMGMASK),
                    ==, UINT32_MAX);
    g_assert_cmphex(qtest_readl(qts, FLEXCAN7_BASE + FLEXCAN_RXMGMASK),
                    ==, UINT32_MAX);
    g_assert_cmphex(qtest_readl(qts, SWT0_BASE + S32K3_SWT_CR),
                    ==, S32K3_SWT_CR_RESET);
    g_assert_cmphex(qtest_readl(qts, SWT3_BASE + S32K3_SWT_CR),
                    ==, S32K3_SWT_CR_RESET);

    qtest_writel(qts, GMAC0_BASE + GMAC_MAC_CONFIG, BIT(0));
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + GMAC_MAC_CONFIG),
                    ==, BIT(0));

    qtest_quit(qts);
}

#ifndef _WIN32
static void test_s32k388_gmac_tx(void)
{
    static const uint8_t packet[60] = {
        0x66, 0x55, 0x44, 0x33, 0x22, 0x11,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x08, 0x00,
        0x45, 0x00, 0x00, 0x2e, 0x00, 0x00, 0x00, 0x00,
        0x40, 0x11, 0x00, 0x00, 0xc0, 0xa8, 0x00, 0x01,
        0xc0, 0xa8, 0x00, 0x02, 0x12, 0x34, 0x56, 0x78,
        0x00, 0x1a, 0x00, 0x00,
        0x53, 0x33, 0x4b, 0x33, 0x38, 0x38, 0x2d, 0x54,
        0x58, 0x2d, 0x54, 0x45, 0x53, 0x54, 0x00, 0x00,
    };
    uint32_t descriptor[8] = {
        cpu_to_le32(TX_BUFFER_BASE),
        0,
        cpu_to_le32(TX_DESC_IOC | sizeof(packet)),
        cpu_to_le32(TX_DESC_OWN | TX_DESC_FD | TX_DESC_LD | sizeof(packet)),
    };
    uint8_t transmitted[sizeof(packet)] = { 0 };
    int sockets[2];
    QTestState *qts;

    g_assert_cmpint(socketpair(PF_UNIX, SOCK_STREAM, 0, sockets), ==, 0);
    qts = qtest_initf("-machine s32k388 -nic socket,fd=%d,model=gmac0",
                      sockets[1]);
    close(sockets[1]);
    qtest_irq_intercept_in(qts, "/machine/armv7m");

    qtest_memwrite(qts, TX_DESC_BASE, descriptor, sizeof(descriptor));
    qtest_memwrite(qts, TX_BUFFER_BASE, packet, sizeof(packet));
    qtest_writel(qts, GMAC0_BASE + GMAC_MAC_CONFIG, BIT(1));
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_CONTROL, 2 << 18);
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_INT_ENA,
                 GMAC_DMA_STATUS_TI | GMAC_DMA_INT_NIE);
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_TX_DESC, TX_DESC_BASE);
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_TX_RING, 0);
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_TX_CTRL, BIT(0));
    qtest_writel(qts, GMAC0_BASE + GMAC_CH0_TX_TAIL,
                 TX_DESC_BASE + TX_DESC_STRIDE);

    send_frame(sockets[0], packet, sizeof(packet));
    receive_frame(sockets[0], transmitted, sizeof(transmitted));
    g_assert_cmpmem(transmitted, sizeof(transmitted), packet, sizeof(packet));
    g_assert_cmphex(qtest_readl(qts, TX_DESC_BASE + 12) & TX_DESC_OWN,
                    ==, 0);
    g_assert_cmphex(qtest_readl(qts, GMAC0_BASE + GMAC_CH0_STATUS) &
                    GMAC_DMA_STATUS_TI, ==, GMAC_DMA_STATUS_TI);
    g_assert_true(qtest_get_irq(qts, GMAC_TX_IRQ));

    qtest_quit(qts);
    close(sockets[0]);
}
#endif

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    qtest_add_func("s32k388/board/peripheral-map",
                   test_s32k388_peripheral_map);
#ifndef _WIN32
    qtest_add_func("s32k388/gmac/tx", test_s32k388_gmac_tx);
#endif
    return g_test_run();
}
