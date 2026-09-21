# S32K389 NVIC Technical Report

## Result

The S32K389 board uses QEMU's generic ARMv7-M NVIC correctly at the
integration level. Source inspection validates controller creation, CPU
association, PPB mapping, peripheral IRQ hookup, and interrupt state
management. Runtime ISR execution remains unverified because this worktree
does not contain `build/qemu-system-arm`.

## Architecture

`hw/arm/armv7m.c` creates and realizes `armv7m_nvic` below `ARMV7MState`,
links it to the Cortex-M CPU, connects its output to `ARM_CPU_IRQ`, and maps
its system registers at `0xe000e000`. `ARMV7MState` exposes the NVIC input
GPIOs to the board.

The S32K389 configuration is:

- CPU: Cortex-M7
- External IRQs: 240
- Internal exception vectors: 16
- Total NVIC vectors: 256
- Implemented priority bits: 4
- Initial vector/reset address: `0x00402000`

External NVIC input `n` represents exception `16 + n`.

## Verified NVIC behavior

`hw/intc/armv7m_nvic.c` implements:

- enable/disable and pending/clear-pending registers
- active-state reads
- external and system-handler priorities
- priority arbitration and nesting
- exception acknowledge and completion
- SysTick and NMI inputs
- masking and privilege checks
- fault escalation and level-sensitive pending behavior

Reset initializes architectural exception priorities and state. Register
writes recompute interrupt arbitration.

## Board IRQ wiring

The board connects IRQ outputs for LPUART3, FlexIO, 12 FlexCAN, 6 LPSPI,
2 LPI2C, 4 SWT, 3 ADC, 3 eMIOS, 32 eDMA channels, 2 GMAC, QuadSPI, and
2 SAI devices through `sysbus_connect_irq()` and
`qdev_get_gpio_in()`.

Verified or source-documented mappings:

- LPUART3
- FlexIO
- FlexCAN
- LPSPI

Unverified placeholder mappings in `hw/arm/s32k389.h`:

- LPI2C, SWT, ADC, eMIOS, eDMA
- GMAC, QuadSPI, SAI

Known fidelity limits:

- eMIOS is reduced to one OR'd IRQ per instance.
- Only core 0 receives modeled peripheral IRQs; cores 1–3 have independent
  NVICs but no peripheral routing.

## Validation status

### Passed by source inspection

- NVIC/CPU realization and association
- PPB register mapping
- CPU interrupt output connection
- vector-table configuration
- peripheral-to-NVIC GPIO wiring pattern
- enable, pending, active, priority, masking, arbitration, acknowledge, and
  completion paths

