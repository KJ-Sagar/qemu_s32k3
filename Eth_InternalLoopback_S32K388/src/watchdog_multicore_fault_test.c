#include <stdint.h>

#define SWT0_BASE 0x40270000u
#define  SWT0_CR (*(volatile uint32_t *)(SWT0_BASE + 0x00u))
#define SWT0_SR (*(volatile uint32_t *)(SWT0_BASE + 0x10u))
#define SWT0_TO (*(volatile uint32_t *)(SWT0_BASE + 0x08u))

/*
 * This shared area is only a diagnostic marker. Each S32K389 core executes
 * the same image, so the four slots show that every core reached the fault
 * state before the watchdog reset.
 */
#define CORE_MARKERS ((volatile uint32_t *)0x2040F000u)
#define CORE_PHASE(slot) (CORE_MARKERS[(slot) * 2u])
#define CORE_HEARTBEAT(slot) (CORE_MARKERS[(slot) * 2u + 1u])
#define WATCHDOG_STATUS (CORE_MARKERS[10])

enum {
    PHASE_CLAIMED = 0x10000000u,
    PHASE_WATCHDOG_ARMED = 0x20000000u,
    PHASE_DEADLOCK = 0x30000000u,
    PHASE_USAGE_FAULT = 0x40000000u,
    PHASE_HARD_FAULT = 0x50000000u,
    PHASE_CORRUPTED_LOOP = 0x60000000u,
};

static uint32_t claim_core_slot(void)
{
    uint32_t old_value;
    uint32_t new_value;
    uint32_t status;

    do {
        old_value = CORE_MARKERS[8];
        new_value = old_value + 1u;
        __asm__ volatile ("ldrex %0, [%3]\n"
                          "strex %1, %2, [%3]\n"
                          : "=&r"(old_value), "=&r"(status)
                          : "r"(new_value), "r"(&CORE_MARKERS[8])
                          : "memory");
    } while (status != 0u);

    return old_value % 4u;
}

int main(void)
{
    uint32_t slot = claim_core_slot();
    uint32_t state = 0xC0DE0000u | slot;

    CORE_PHASE(slot) = PHASE_CLAIMED | slot;
    CORE_HEARTBEAT(slot) = state;

    /*
     * SWT0 is shared by the cores. The atomic counter rotates ownership on
     * each boot, so persistent SRAM cannot cause every later boot to skip
     * watchdog setup, and only one core performs the unlock sequence.
     */
    if (slot == 0u) {
        SWT0_SR = 0xC520u;
        SWT0_SR = 0xD928u;
        SWT0_TO = 32768u;
        SWT0_CR = 1u;
        WATCHDOG_STATUS = PHASE_WATCHDOG_ARMED | slot;
    }

    /*
     * Deliberately strand every core after the watchdog is armed. The
     * different cases represent independent application failure modes while
     * preserving a deterministic test:
     *   0: CPU-bound deadlock
     *   1: usage fault
     *   2: hard fault
     *   3: corrupted-state loop
     */
    switch (slot) {
    case 1u:
        CORE_PHASE(slot) = PHASE_USAGE_FAULT | slot;
        __asm__ volatile ("udf #0");
        break;
    case 2u:
        CORE_PHASE(slot) = PHASE_HARD_FAULT | slot;
        __asm__ volatile ("udf #1");
        break;
    case 3u:
        CORE_PHASE(slot) = PHASE_CORRUPTED_LOOP | slot;
        break;
    default:
        CORE_PHASE(slot) = PHASE_DEADLOCK | slot;
        break;
    }

    for (;;) {
        state = (state * 1664525u) + 1013904223u;
        CORE_HEARTBEAT(slot) = state;
        __asm__ volatile ("nop");
    }
}
