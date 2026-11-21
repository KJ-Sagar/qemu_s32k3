# QEMU S32K388 and S32K389 Board Status Report

**Status snapshot:** 21 November 2026  
**Repository:** `KJ-Sagar/qemu_s32k3`  
**Reviewed revision:** `8709eca1da6bf2e78629f73f11e9d37f4d8102cd` (`main`, same as `origin/main`)  
**Overall assessment:** Both machine types are present and buildable. S32K389 has broader peripheral coverage and focused, passing GMAC/watchdog tests. Neither machine is a complete, silicon-faithful virtual development kit (VDK); S32K388 is substantially more skeletal.

## Executive assessment

The QEMU tree provides useful firmware bring-up and peripheral-driver development targets, especially for S32K389's Ethernet descriptor paths and watchdog behavior. Its board support should be described as **functional in selected paths, mixed-fidelity elsewhere, and not comprehensively validated**, rather than as complete hardware emulation.

S32K389 maps a broad set of devices, exposes four Cortex-M7 CPU objects, and has substantial GMAC tests. Most of its peripheral models are intentionally simplified and do not yet have dedicated automated regression tests. Peripheral interrupt wiring is to core 0 only. S32K388 models a single Cortex-M7, a console path, six FlexCAN devices and two generic GMAC devices, with many other addresses served by stubs or a catch-all. The repository's own memory-map workbook marks FlexCAN6 and FlexCAN7 present on S32K388, but the board currently instantiates only FlexCAN0-5.

The review also found a concrete tooling blocker: `scripts/validate_s32k389_spec.py`, described by the roadmap as a required regression gate, contains unresolved merge-conflict markers and fails Python parsing. The S32K388 launcher points at a nonexistent `scripts/build` path rather than the repository's `build` directory.

## Latest project status

- Before adding this report, the local `main` source tree had no pre-existing changes and matched `origin/main` at `8709eca`.
- GitHub's latest commit is the **26 October 2026** merge of the S32K389 Ethernet testing work ([PR #15](https://github.com/KJ-Sagar/qemu_s32k3/pull/15)). No later upstream commit was returned for the default branch at report time.
- GitHub reports no open issues. The returned pull requests are closed/merged; the latest is #15.
- The merged work focuses on S32K389 GMAC/EQOS: three descriptor DMA channels per controller, RX queue-to-channel mapping, packet filtering, separate channel IRQs, and simplified MDIO/PHY behavior.
- `VDK_IMPLEMENTATION_ROADMAP.md` correctly frames the target as further work: correct static wiring is a baseline, not proof of driver-equivalent behavior.

## Current board capabilities

| Area | S32K388 | S32K389 |
|---|---|---|
| Machine / CPU | `s32k388`; one Cortex-M7, configured for 320 MHz | `s32k389`; four Cortex-M7 objects, configured for 320 MHz |
| Memory and boot | ITCM/DTCM, flash, SRAM, ELF loading and semihosting | Larger 12 MB code flash, 256 KB data flash, SRAM3 and four per-core TCM views; ELF loaded from shared flash |
| Console and serial | LPUART3 console; a FlexIO-to-LPUART helper | Same |
| CAN | FlexCAN0-5 instantiated (six); FlexCAN6-7 are absent despite being marked present in the workbook | FlexCAN0-11 instantiated (12) |
| Ethernet | Two NPCM GMAC instances at the S32K3 addresses, but the board does not enable the S32K3 compatibility mode or have a board-specific GMAC test | Two GMACs in S32K3 mode; channelized EQOS datapath and GMAC1 backend support |
| Other modeled peripherals | Most peripheral windows are generic unimplemented regions or simple boot stubs; LPSPI is not instantiated | Six LPSPI, two LPI2C, four SWT, three ADC, three eMIOS, one eDMA, one QSPI, two SAI and one CRC model |
| Board test coverage | No S32K388-specific qtest found | Eight S32K389 GMAC qtests; watchdog reset/pause script; no broad per-peripheral qtest suite found |

### S32K388 in practice

The S32K388 machine is a single-core bootable board shell with the memory regions and the devices wired in [`hw/arm/s32k388.c`](hw/arm/s32k388.c) and [`hw/arm/s32k388.h`](hw/arm/s32k388.h). The directly exposed functional paths are:

- Cortex-M7 firmware execution, a serial console on LPUART3, and semihosting.
- A FlexIO helper wired to the console UART for a limited UART-loopback use case. This is not a full FlexIO peripheral model.
- Six FlexCAN instances attached to QEMU CAN buses when configured. The shared model implements basic classic CAN message-buffer RX/TX, filtering and IRQ behavior. It has 32 message buffers with up to 8 data bytes each.
- Two GMAC devices. The board instantiates the generic `TYPE_NPCM_GMAC` without enabling the S32K3-specific EQOS mode used by S32K389. Treat S32K388 Ethernet register/datapath compatibility as unverified, not equivalent to the S32K389-tested path.
- Minimal early-boot placeholders for modules such as MSCM, SWT0, RTC, MC_RGM, DCM, SXOSC and MC_ME, plus an unimplemented peripheral aperture. These placeholders can let firmware probe addresses, but they do not supply the actual device behavior.

The S32K388 header defines LPSPI addresses and state fields, but the machine does not instantiate LPSPI devices. The same applies to other peripherals not explicitly initialized in `s32k388_init()`. The NXP memory-map workbook marks FlexCAN0-7 as present for S32K388; the current board only initializes instances 0-5, leaving two documented hardware instances unavailable.

### S32K389 in practice

The S32K389 machine has a more developed platform baseline and broad device composition in [`hw/arm/s32k389.c`](hw/arm/s32k389.c) and [`hw/arm/s32k389.h`](hw/arm/s32k389.h):

- Four Cortex-M7s are created unconditionally. Additional cores get private ITCM/DTCM aliases while sharing flash, SRAM and peripheral address space. All cores use the same loaded image and initial vector table.
- Memory includes the S32K389 flash/SRAM regions, including the additional SRAM3 bank.
- Twelve FlexCANs, LPUART3/FlexIO helper, six LPSPI, two LPI2C, four SWT, three ADC, three eMIOS, 32-channel eDMA, two GMACs, QSPI, two SAI and CRC are instantiated.
- The generic peripherals beneath these names are not all equally complete; the selected behavior and gaps are summarized below.

The multi-core model is useful for bring-up but is not a literal lockstep representation. The header explicitly describes all four CPU objects as independently programmable, including physical cores that may operate as lockstep checkers on real hardware. Peripheral IRQs are connected to core 0's NVIC only; cores 1-3 do not receive peripheral interrupt wiring.

## Functional scope and boundaries

| Peripheral / area | Implemented behavior | Important limits |
|---|---|---|
| FlexCAN | Message-buffer classic CAN TX/RX, standard/extended ID matching, basic masks, interrupt flags and QEMU CAN-bus connection | No CAN FD; small subset of hardware error/bus-off and timing behavior; only one message-buffer IRQ output is connected per instance. S32K388 omits two present instances. No dedicated S32K3 CAN qtests were found. |
| GMAC/EQOS (S32K389) | Three DMA channels per GMAC; descriptor TX/RX including multi-descriptor packets and ring progression; static RX queue mapping; selected MAC filtering; W1C status and per-channel IRQ outputs; simplified synchronous Clause 22 MDIO/PHY at address 0 | Not complete silicon behavior. Dynamic queue selection/MTL arbitration, full VLAN/offload corner cases, Clause 45, real PHY/PCS/RGMII/link negotiation, complete PTP/TSN, and sustained high-load/reset validation remain incomplete. The external-network firmware evidence is narrower than a complete IP-stack test. |
| GMAC (S32K388) | Two generic GMAC device instances and host NIC attachment points | No S32K3 mode enabled at board setup and no S32K388-specific GMAC regression test. Do not assume the S32K389 EQOS feature coverage applies. |
| LPSPI | Controller/master transfers through a QEMU SSI bus; FIFOs, status and interrupts; transfers complete synchronously | Peripheral/target mode, timing, circular FIFO behavior, and frames wider than 32 bits are not modeled. |
| LPI2C | Master FIFO/register behavior and transactions through QEMU's I2C infrastructure | Synchronous/immediate completion rather than cycle-accurate bus timing; DMA requests are not modeled; device-level coverage is absent. |
| ADC | Software-triggered normal conversion sweep; enabled channels return a fixed mid-scale sample (`0x800`); status and selected interrupts | No analog inputs or configurable sensor values; conversion is immediate. Injected conversions, DMA, watchdog, presampling and calibration behavior are storage-only or unmodeled. |
| eMIOS | Selected autonomous timer/counter modes; virtual-clock CNT progression, match flags and a shared per-instance IRQ | Only a subset of modes is active; external pins/counter buses and detailed output waveforms are absent. The assumed 80 MHz module clock is unverified; interrupt routing is simplified to one shared line. |
| eDMA | 32 software-started channels; TCD field handling; synchronous major-loop guest-memory copies and selected completion/error/IRQ behavior | Peripheral request signaling, scatter/gather, channel linking, minor-loop offsets, modulo, bandwidth and real arbitration are not modeled. Channel IRQ map is called out in source as unverified. |
| SWT | Four timer-backed watchdogs; service/unlock sequences; timeout interrupt and QEMU watchdog action | Keyed service and window-mode enforcement are simplified; stop/debug freeze and full system reset-controller semantics are absent. |
| QSPI | IP-command path interprets LUT read/write operations against an internal 16 MB flash backing store; RX/TX FIFOs and completion status | No AHB memory-mapped flash window, DMA service, NOR erase/status timing, full LUT instruction execution, or signal timing. The model is wired on S32K389; S32K388 does not initialize it. |
| SAI | Two S32K389 instances; TX FIFO drains on a virtual timer and exposes selected status/interrupt behavior | No connected audio output or meaningful external RX source; RX remains empty; exact audio framing/timing is simplified. |
| CRC | Register-driven CRC engine | No interrupt; not covered by the board's discovered qtests. |
| Boot / clock / safety glue | Minimal MSCM reads, MC_ME boot-ready stand-ins, clock-generator register storage and an STCU2 placeholder | Clock-generator behavior is not a model; MC_ME values are simplified rather than reset-accurate. STCU2 base/register behavior is explicitly unverified and its status reports a synthetic pass. |

## Verified behavior in this review

The current tree was rebuilt with:

```sh
ninja -C build qemu-system-arm tests/qtest/s32k389-gmac-test
```

The build completed successfully. The S32K389 GMAC qtest executable then passed **all 8 tests**:

1. EQOS RX packet delivery and descriptor completion.
2. Multi-descriptor RX and ring exhaustion/re-arm behavior.
3. EQOS TX.
4. Multi-descriptor TX.
5. GMAC1 datapath and IRQ wiring.
6. Simplified MDIO/PHY behavior.
7. DMA error, reset and recovery path.
8. DMA channels and RX queue routing.

The watchdog test script also passed both live scenarios on this build:

- `reset`: observed the configured watchdog timeout and QEMU returned to running state.
- `pause`: observed QEMU paused by the watchdog.

Both S32K388 and S32K389 appear in the built QEMU machine list. These results establish the exercised code paths only. They do **not** establish complete firmware compatibility, silicon conformance, S32K388 Ethernet behavior, or system-wide peripheral correctness. The only S32K3 qtest registered in `tests/qtest/meson.build` is the S32K389 GMAC suite; the watchdog is tested by a separate script.

## Blockers and material limitations

### Immediate correctness / workflow blockers

1. **S32K389 specification validator cannot run.** `scripts/validate_s32k389_spec.py` contains unresolved `<<<<<<<`, `=======` and `>>>>>>>` conflict markers beginning around line 178. A Python syntax check fails with `SyntaxError`. This breaks the roadmap's claimed static-map regression gate.
2. **S32K388 CAN instance coverage is incomplete.** The checked-in NXP memory-map workbook marks FlexCAN0-7 as present for S32K388, but `S32K388_CAN_COUNT` is 6 and the board maps only instances 0-5.
3. **S32K388 launcher points to the wrong binary path.** `scripts/launch_qemu_388.sh` constructs `scripts/build/qemu-system-arm`; the checked-out build is at repository-root `build/qemu-system-arm`. The script therefore reports a missing QEMU binary in this repository layout.
4. **No dedicated S32K388 or general peripheral qtest suite.** GMAC regression coverage is strong for a selected subset on S32K389, but there are no registered S32K388 qtests and no comparable qtests for CAN, LPSPI, I2C, ADC, eMIOS, eDMA, QSPI, SAI or CRC.

### Fidelity / validation blockers

- **Multi-core semantics:** S32K389 creates four independent Cortex-M7s, while real silicon supports lockstep/split-lock configurations. Peripheral IRQ delivery only reaches core 0. Firmware relying on core-specific interrupt routing, core boot controls or hardware lockstep cannot be considered validated.
- **Peripheral coverage gaps:** Many controllers implement only selected register flows. Unsupported operations may be inert, synchronous, storage-only, or report `LOG_UNIMP`; they should not be assumed to behave like devices on silicon.
- **Pin-level and clock-tree integration:** There is no complete pin mux/GPIO/electrical model, realistic power/clock gating, analog signal source, external PHY/PCS/RGMII, or complete clock-tree simulation. Several emulated timers use an assumed rate.
- **Non-volatile storage semantics:** Main flash regions are QEMU ROM regions for firmware loading, not complete flash controllers. QSPI offers a separate simplified IP-command backing store, not a fully mapped external flash subsystem.
- **Runtime evidence is uneven:** Ethernet has qtests and selected TAP observations; watchdog reset/pause has a focused script. Most other board functions are supported primarily by source-level modeling and manual/documented intent, not repeatable end-to-end firmware validation.
- **Documentation drift:** The Ethernet status document contains inconsistent test-count wording (the current executable registers eight tests) and references changes as uncommitted despite the clean reviewed tree. The handoff document also describes a separate worktree/branch and should not be treated as the current checkout status.

## Recommended next steps

1. Remove the conflict markers and run `scripts/validate_s32k389_spec.py` successfully as a required check.
2. Complete S32K388 board coverage: add FlexCAN6/7 using confirmed addresses/IRQs; decide and document S32K388 QSPI and other hardware-supported peripherals; fix the S32K388 launcher path.
3. Add machine-level smoke tests for both boards (boot, map/register access, memory boundaries and IRQ routing), then targeted tests for CAN and the implemented S32K389 peripherals.
4. Define and document the intended S32K389 CPU topology. Either model the target split-lock configuration explicitly or label the independent-four-core approximation as a bring-up-only topology; add tests for reset and interrupt behavior across cores.
5. Prioritize realistic feature work from actual guest firmware requirements: CAN message/error behavior, GMAC PHY/link and advanced queues, peripheral DMA requests, and clock/reset/pin integration.
6. Keep a per-device evidence matrix distinguishing **instantiated**, **register-accessible**, **functional in a tested data path**, and **silicon-validated**. Do not describe a mapped device as fully implemented without runtime evidence.

## Concise bullet list

- **S32K389:** Four-core board model with broad peripheral inventory; S32K389 GMAC datapaths and watchdog actions are demonstrably functional in focused tests.
- **S32K388:** Single-core bring-up shell with UART/FlexIO helper, six classic FlexCANs, two generic GMACs and boot stubs; at least FlexCAN6/7 are missing versus the local NXP map.
- **Strongest tested area:** S32K389 GMAC/EQOS: all 8 qtests passed on the reviewed build, including GMAC1 and three-channel DMA routing.
- **Also tested:** S32K389 watchdog reset and pause paths both passed.
- **Main blocker:** S32K389 map-validation script has merge-conflict markers and is not executable.
- **Other immediate issue:** S32K388 launcher looks under `scripts/build`, and there is no S32K388-specific qtest.
- **Main technical limits:** Simplified/non-cycle-accurate peripheral models, missing pin/clock/power integration, incomplete PHY/CAN/eDMA and IRQ semantics, and core 1-3 peripheral IRQs not wired.
- **Bottom line:** Useful for focused firmware bring-up and selected driver tests; **not yet a complete or production-grade S32K388/S32K389 VDK**.

## Evidence and source references

- Board definitions and wiring: [`hw/arm/s32k388.c`](hw/arm/s32k388.c), [`hw/arm/s32k388.h`](hw/arm/s32k388.h), [`hw/arm/s32k389.c`](hw/arm/s32k389.c), [`hw/arm/s32k389.h`](hw/arm/s32k389.h).
- Device models and documented scope: [`hw/net/can/s32k3_flexcan.c`](hw/net/can/s32k3_flexcan.c), [`hw/net/npcm_gmac.c`](hw/net/npcm_gmac.c), [`hw/dma/s32k3_edma.h`](hw/dma/s32k3_edma.h), [`hw/adc/s32k3_adc.h`](hw/adc/s32k3_adc.h), [`hw/timer/s32k3_emios.h`](hw/timer/s32k3_emios.h), [`hw/ssi/s32k3_lpspi.h`](hw/ssi/s32k3_lpspi.h), [`hw/ssi/s32k3_qspi.h`](hw/ssi/s32k3_qspi.h), [`hw/audio/s32k3_sai.h`](hw/audio/s32k3_sai.h), [`hw/watchdog/s32k3_swt.h`](hw/watchdog/s32k3_swt.h).
- Test registration and Ethernet tests: [`tests/qtest/meson.build`](tests/qtest/meson.build), [`tests/qtest/s32k389-gmac-test.c`](tests/qtest/s32k389-gmac-test.c), [`scripts/s32k389-watchdog-test.sh`](scripts/s32k389-watchdog-test.sh).
- Map data and validator: [`NXP Manuals/S32K3xx_memory_map.xlsx`](NXP%20Manuals/S32K3xx_memory_map.xlsx), [`NXP Manuals/S32K3xx_interrupt_map.xlsx`](NXP%20Manuals/S32K3xx_interrupt_map.xlsx), [`scripts/validate_s32k389_spec.py`](scripts/validate_s32k389_spec.py).
- Existing project status references: [`VDK_IMPLEMENTATION_ROADMAP.md`](VDK_IMPLEMENTATION_ROADMAP.md), [`HANDOFFS/S32K389_ETHERNET_DEVELOPMENT_STATUS.md`](HANDOFFS/S32K389_ETHERNET_DEVELOPMENT_STATUS.md), [`HANDOFFS/NVIC_VALIDATION.md`](HANDOFFS/NVIC_VALIDATION.md).
- Latest upstream work: [PR #15](https://github.com/KJ-Sagar/qemu_s32k3/pull/15), merged 26 October 2026.
