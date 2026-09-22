# S32K389 QEMU Board: VDK-Level Implementation Roadmap

## Objective

Raise the S32K389 QEMU machine from its current state of valid board wiring and MMIO/IRQ mapping to a VDK-level implementation, where each peripheral behaves like the real hardware under real NXP driver software and firmware usage.

This roadmap is intentionally centered on correctness and per-peripheral validation, not on a single boot image or one specific ELF.

## Guiding principle

A VDK-level implementation is not "the board boots." It is:

- correct memory map and instance count
- correct IRQ routes and interrupt behavior
- correct default/reset/register semantics
- correct DMA and buffering behavior where applicable
- correct protocol behavior for CAN, Ethernet, UART, SPI, I2C, ADC, timers, watchdog, and other critical peripherals
- runtime validation with representative firmware and driver flows

## Current status assessment

The current board model is significantly better than a placeholder implementation:

- the S32K389 MMIO map and IRQ values have been validated against the NXP workbook data
- the board is built and runs on the current tree
- major peripherals are instantiated and wired into the machine
- Ethernet and CAN are present at the board level and connected to the generic QEMU device infrastructure

However, this is still not VDK-equivalent fidelity for all peripherals. The current state is best described as:

- functional board integration
- validated static configuration
- partially validated runtime behavior
- not yet a full silicon-faithful driver-equivalent implementation across the entire SoC

## Roadmap phases

### Phase 0: Freeze the hardware truth

Goal: prevent drift and unsupported assumptions.

Actions:
- Keep the workbook-based memory map and interrupt map as the source of truth.
- Treat [scripts/validate_s32k389_spec.py](scripts/validate_s32k389_spec.py) as a required regression gate.
- Document every per-instance value with direct evidence from the NXP manuals/workbooks.
- Require a rationale for every change before modifying a register layout, interrupt, or base address.

Acceptance:
- all board constants remain traceable to spec data
- no unverified IRQ or base address is left undocumented
- validation script passes in CI/local regression runs

### Phase 1: Harden the platform baseline

Goal: make the SoC core and shared infrastructure behave reliably before peripheral work becomes deeper.

Focus areas:
- reset and boot flow
- system clocking and default frequencies
- flash/SRAM aliasing and contiguous region mapping
- interrupt controller wiring
- NVIC prioritization and masking semantics
- DMA controller baseline behavior
- power/reset gating and stubbed peripheral glue

Actions:
- audit the machine-initialization path in [hw/arm/s32k389.c](hw/arm/s32k389.c)
- validate the ARMv7-M core configuration and interrupt delivery path
- ensure the shared system bus and catch-all memory regions do not hide peripheral bugs
- keep the platform model deterministic and testable

Acceptance:
- firmware can boot and access a broad range of peripherals without bus faults caused by platform glue
- the board behaves consistently across reset and startup flows

### Phase 2: CAN implementation parity

Goal: move CAN from board-level presence to realistic message-level behavior.

Focus areas:
- FlexCAN instance map and IRQ routing
- message buffer semantics
- RX/TX ordering and queue behavior
- frame filtering / acceptance masks
- bus-off and error interrupts
- CAN FD support if needed by the target firmware
- bus connectivity through QEMU CAN infrastructure

Actions:
- review [hw/net/s32k3_flexcan.c](hw/net/s32k3_flexcan.c) and [hw/net/s32k3_flexcan.h](hw/net/s32k3_flexcan.h)
- validate each FlexCAN instance against the S32K389 interrupt and map data
- add real frame-level tests for RX and TX paths
- verify message buffering and status register behavior
- validate end-to-end against a simple CAN driver or loopback use case

Acceptance:
- each CAN instance can exchange valid frames with the expected message buffer semantics
- status/error bits update realistically
- driver-visible behavior matches NXP register expectations

### Phase 3: Ethernet implementation parity

Goal: move GMAC from usable NIC exposure to a realistic Ethernet peripheral model.

Focus areas:
- GMAC register block behavior
- DMA descriptor handling
- RX/TX ring semantics
- interrupt generation and clearing
- MAC filtering, unicast/broadcast/multicast behavior
- link state and PHY/loopback semantics
- host network backend integration
- packet-level validation under normal network traffic

Actions:
- inspect and improve the GMAC integration in [hw/arm/s32k389.c](hw/arm/s32k389.c)
- review the underlying NIC model in [hw/net/npcm_gmac.c](hw/net/npcm_gmac.c)
- add stable per-instance MAC configuration and verify host networking usage
- validate packet receive/transmit at the register and DMA level
- ensure generated interrupts match expected packet and error conditions

Acceptance:
- packets flow through the controller in a realistic way
- per-instance MAC and IRQ behavior are consistent
- guest firmware sees a credible Ethernet interface rather than only a connected placeholder

### Phase 4: UART, SPI, and I2C parity

Goal: bring the communication peripherals to driver-style parity.

Focus areas:
- UART FIFO/baud/interrupt semantics
- SPI mode control and data transfer validity
- I2C address handling and transaction states
- interrupt generation, status bits, and error flags

Actions:
- verify each instance map and IRQ against the workbook
- add targeted loopback and transaction tests
- validate a realistic driver flow rather than only register reads

Acceptance:
- each peripheral behaves acceptably under a typical RTD/SDK driver sequence
- status and error registers reflect real operation

### Phase 5: ADC, timers, watchdog, DMA, and control peripherals

Goal: finish the platform beyond the communication blocks.

Focus areas:
- ADC conversion complete and trigger semantics
- eMIOS timer behavior and counter operations
- SWT watchdog timeout and reset behavior
- DMA channel transfer and completion logic
- CRC and safety/peripheral status behavior

Actions:
- verify the full instance count and IRQ routing
- implement realistic register-level side effects
- create small tests for each block using the same validation matrix approach

Acceptance:
- peripheral behavior is not merely non-faulting but visibly correct under firmware use
- timing and completion behavior are internally consistent

### Phase 6: Validation and regression hardening

Goal: maintain VDK-level quality over time.

Actions:
- create automated regression tests for MMIO/IRQ mapping
- create per-peripheral runtime tests
- store expected behavior for each simulated controller
- run a full board validation pass after every change affecting shared infrastructure

Acceptance:
- every new board change is checked against reference data and functional tests
- the model does not silently regress from one peripheral to another

## Per-peripheral validation matrix

Each peripheral should satisfy this checklist before being considered VDK-level quality:

- base address is correct
- instance count is correct
- IRQ number is correct
- reset/default values are correct
- read/write access semantics are correct
- data path works (FIFO, buffer, DMA, descriptor, packet, frame)
- interrupts fire and clear correctly
- error/timeout states behave realistically
- host/device connection is valid
- the software driver stack sees expected behavior

## Priority order

Recommended execution order:

1. Platform baseline and shared infrastructure
2. CAN
3. Ethernet
4. UART / SPI / I2C
5. ADC / timers / watchdog / DMA
6. remaining control and safety peripherals
7. full regression suite

This order reflects both hardware criticality and the immediate impact on real firmware use.

## Practical implementation strategy

To make this tractable and safe:

- do not expand scope to multiple unrelated boards or architectures
- keep validation evidence in the repo for each device
- prefer existing QEMU patterns and APIs over creating new infrastructure unless necessary
- update the validation script as new source-backed values are confirmed
- document each device as either:
  - validated and functional
  - partially implemented but bounded
  - placeholder / not yet hardware-faithful

## Completion criteria

This roadmap is complete when the board crosses from "wired and usable" to "VDK-equivalent" in the following sense:

- all major peripherals are individually validated against real hardware data
- each peripheral has a runtime behavior that matches driver expectations
- representative firmware can exercise the device path without hacks
- the board is robust enough to support production-oriented software development, not just smoke tests

## Key files and focus areas

- [hw/arm/s32k389.h](hw/arm/s32k389.h)
- [hw/arm/s32k389.c](hw/arm/s32k389.c)
- [hw/net/s32k3_flexcan.c](hw/net/s32k3_flexcan.c)
- [hw/net/s32k3_flexcan.h](hw/net/s32k3_flexcan.h)
- [hw/net/npcm_gmac.c](hw/net/npcm_gmac.c)
- [scripts/validate_s32k389_spec.py](scripts/validate_s32k389_spec.py)
- [HANDOFFS/HANDOFF.md](HANDOFFS/HANDOFF.md)

## Summary

The current S32K389 board model already has a strong static foundation. The next step is not to optimize one ELF or one use case, but to systematically bring each peripheral up to VDK-level quality using evidence, runtime validation, and per-device acceptance criteria.

The highest-value next work is CAN and Ethernet, followed by the rest of the peripheral set. The roadmap above is structured to achieve that incrementally and safely.
