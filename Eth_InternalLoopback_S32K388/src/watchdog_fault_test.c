#include <stdint.h>

#define SWT0_CR (*(volatile uint32_t *)0x40270000u)
#define SWT0_SR (*(volatile uint32_t *)0x40270010u)
#define SWT0_TO (*(volatile uint32_t *)0x40270008u)

int main(void)
{
    /*
     * Program a one-second timeout, enable SWT0, and deliberately stop
     * servicing it. QEMU's SWT model will execute the configured watchdog
     * action after the timeout expires.
     */
    /* SWT reset state is software-locked; use the documented unlock keys. */
    SWT0_SR = 0xC520u;
    SWT0_SR = 0xD928u;
    SWT0_TO = 32768u;
    SWT0_CR = 1u;

    for (;;) {
        /*
         * Keep the virtual CPU executing rather than entering WFI. This makes
         * the timeout independent of low-power clock-gating behavior.
         */
        __asm__ volatile ("nop");
    }
}
