# S32K389 QEMU Board Handoff

This document is the continuation point for work on the NXP S32K389 QEMU
machine, with emphasis on the watchdog, Cortex-M NVIC, and Ethernet/GMAC
implementations.

## 1. Repository and current state

**Repository:** `KJ-Sagar/qemu_s32k3`

**Active worktree:**

```text
/home/kj/QEMU/qemu_s32k3.worktrees/qemu-s32k389-ethernet-testing
```

**Branch:**

```text
agents/qemu-s32k389-ethernet-testing
```

**Important:** `/home/kj/QEMU/qemu_s32k3` is a different checkout (`main`).
The current Ethernet and eDMA-warning fixes are in the worktree above. The
launcher computes its QEMU path relative to itself, so always run the launcher
from this worktree or use its absolute path. Running
`~/QEMU/qemu_s32k3/scripts/launch_qemu_389.sh` uses the main checkout's
`build/qemu-system-arm`, which may contain older code and can reproduce the
PTP/eDMA warnings.

Current worktree modifications:

```text
hw/dma/s32k3_edma.c
hw/net/npcm_gmac.c
include/hw/net/npcm_gmac.h
tests/qtest/npcm_gmac-test.c
HANDOFFS/HANDOFF.md
```

The QEMU binary built for the active worktree is:

```text
build/qemu-system-arm
```

The S32K389 machine is registered as:

```text
s32k389  NXP S32K389 Development Board (Cortex-M7)
```

## 2. S32K389 board architecture

Board implementation:

- [s32k389.c](../hw/arm/s32k389.c)
- [s32k389.h](../hw/arm/s32k389.h)

The model currently creates:

- Four Cortex-M7 CPU cores.
- A shared system-memory/peripheral view.
- Per-core ITCM/DTCM aliases for the additional cores.
- 12 FlexCAN instances.
- Console LPUART3 and a FlexIO UART helper.
- 6 LPSPI instances.
- 2 LPI2C instances.
- 4 SWT watchdog instances.
- 3 ADC instances.
- 3 eMIOS instances.
- One 32-channel eDMA controller.
- 2 GMAC Ethernet instances.
- One QuadSPI instance.
- 2 SAI instances.
- Minimal MSCM, MC_ME, clock-generator, STCU2, and other boot-support stubs.

The machine forces four CPUs:

```c
mc->default_cpus = S32K389_NUM_CORES;
mc->min_cpus = S32K389_NUM_CORES;
mc->max_cpus = S32K389_NUM_CORES;
```

The ELF reset/vector placement used by the supplied images is:

```text
flash base:  0x00400000
core 0 VTOR: 0x00402000
```

The memory map includes 12 MB of code flash, 256 KB data flash, and the
S32K389 SRAM layout including SRAM3.

## 3. Watchdog/SWT implementation

Source:

- [s32k3_swt.c](../hw/watchdog/s32k3_swt.c)
- [s32k3_swt.h](../hw/watchdog/s32k3_swt.h)
- [s32k389-watchdog-testing.md](../docs/s32k389-watchdog-testing.md)
- [s32k389-watchdog-test.sh](../scripts/s32k389-watchdog-test.sh)

### 3.1 Instances and addresses

S32K389 has one SWT per Cortex-M7 core:

| Instance | Base | Board IRQ |
|---|---:|---:|
| SWT0 | `0x40270000` | `177` |
| SWT1 | `0x4046c000` | `178` |
| SWT2 | `0x40470000` | `179` |
| SWT3 | `0x40070000` | `180` |

The addresses are documented as verified against the S32K3xx reference
manual. The IRQ values remain marked as unverified placeholders because the
interrupt-map spreadsheet was not available when the board model was built.

### 3.2 Register model

Register offsets:

| Register | Offset |
|---|---:|
| CR | `0x00` |
| IR | `0x04` |
| TO | `0x08` |
| WN | `0x0c` |
| SR | `0x10` |
| CO | `0x14` |
| SK | `0x18` |
| RRR | `0x1c` |

Implemented behavior:

- `CR[WEN]` arms/disarms a virtual timer.
- `TO` is interpreted using a 32,768 Hz SIRC-derived counter.
- `CO` is latched when disabling an active watchdog and reads zero while
  watchdog operation is enabled, matching the modeled manual behavior.
- `IR[TIF]` is a write-one-to-clear timeout flag.
- `CR[ITR]` supports interrupt-then-reset behavior:
  - first expiry sets `TIF` and raises the SWT IRQ;
  - the next expiry invokes the configured QEMU watchdog action.
- Normal service sequence is recognized:

```text
SR = 0xA602
SR = 0xB480
```

- Software unlock sequence is recognized:

```text
SR = 0xC520
SR = 0xD928
```

- `RRR[0]` resets the individual SWT model.
- Software/hardware lock handling is modeled sufficiently for normal firmware
  startup and service flows.
- A monitor/HMP trigger hook is available through
  `s32k3_swt_trigger(instance_id, errp)`.

### 3.3 Explicit simplifications

Not fully modeled:

- Keyed service mode (`CR[SMD] = 01`); two service writes are accepted and an
  unimplemented message is logged.
- Window-mode early-service violations (`CR[WND]`/`WN`).
- Stop-mode and debug-mode timer freezing (`STP`/`FRZ`).
- Full reset-controller interaction; timeout uses QEMU's generic
  `watchdog_perform_action()`.
- Runtime system-reset integration for every custom peripheral is not
  complete; the SWT has explicit device/individual reset behavior.

### 3.4 Watchdog validation

Fault-injection ELF:

```text
ELF/s32k389/Eth_InternalLoopback_S32K389_WatchdogMulticoreFault.elf
```

The firmware starts all four cores, arms SWT0 for approximately one second,
then stops servicing it. It intentionally enters non-servicing/fault loops.

Automated tests:

```bash
scripts/s32k389-watchdog-test.sh reset
MONITOR_PORT=5600 scripts/s32k389-watchdog-test.sh pause
```

Expected outcomes:

- `reset`: QEMU remains running after the guest restarts.
- `pause`: monitor reports `VM status: paused (watchdog)`.
- Log contains:

```text
s32k3_swt[0]: watchdog timeout, performing configured watchdog action
```

Useful manual run:

```bash
build/qemu-system-arm \
  -M s32k389 \
  -kernel ELF/s32k389/Eth_InternalLoopback_S32K389_WatchdogMulticoreFault.elf \
  -watchdog-action pause \
  -d int,guest_errors \
  -D /tmp/s32k389-qemu.log \
  -msg timestamp=on \
  -display none \
  -monitor telnet:127.0.0.1:5555,server=on,wait=off
```

Useful monitor commands:

```text
info status
info registers
xp/12xw 0x2040f000
xp/8xw 0x40270000
```

Diagnostic SRAM begins at `0x2040f000`. The multicore watchdog image records
per-core phase/heartbeat values there and uses `0x2040f028` for SWT-arm status.

## 4. NVIC and interrupt implementation

The board uses QEMU's generic ARMv7-M NVIC:

- [armv7m_nvic.c](../hw/intc/armv7m_nvic.c)
- [armv7m_nvic.h](../include/hw/intc/armv7m_nvic.h)
- [armv7m.c](../hw/arm/armv7m.c)
- [NVIC_VALIDATION.md](NVIC_VALIDATION.md)

### 4.1 S32K389 NVIC configuration

Board configuration:

```text
CPU: Cortex-M7
external IRQ inputs: 240
internal exception vectors: 16
total vector capacity: 256
implemented priority bits: 4
NVIC/PPB base: 0xe000e000
initial VTOR: 0x00402000
```

An external QEMU IRQ input `n` corresponds to ARM exception number `16 + n`.

### 4.2 Implemented generic NVIC behavior

The generic model provides:

- Enable/disable registers.
- Set-pending/clear-pending registers.
- Active-state reads.
- External and system-handler priority registers.
- Priority arbitration and interrupt nesting.
- Exception acknowledge and completion.
- SysTick and NMI input paths.
- PRIMASK/BASEPRI/FAULTMASK-related masking behavior.
- Privilege checks and fault escalation paths.
- Level-sensitive pending handling.
- `SEVONPEND` event behavior.
- v8-M security-bank support in the generic implementation where applicable.

The S32K389 CPU is configured through the normal ARMv7-M object path; no
S32K389-specific NVIC fork exists.

### 4.3 Board IRQ wiring

The board connects peripheral IRQ outputs with
`sysbus_connect_irq()` and `qdev_get_gpio_in()` to core 0's ARMv7-M NVIC.
Wired groups include:

- LPUART3.
- FlexIO.
- 12 FlexCAN instances.
- 6 LPSPI instances.
- 2 LPI2C instances.
- 4 SWT instances.
- 3 ADC instances.
- 3 eMIOS instances.
- 32 eDMA channels.
- 2 GMAC instances.
- QuadSPI.
- 2 SAI instances.

Only core 0 receives board peripheral IRQs. Cores 1–3 have independent
Cortex-M7/NVIC instances but no peripheral interrupt-routing policy has been
implemented. Firmware that expects a peripheral interrupt on a secondary
core needs a future routing design.

### 4.4 IRQ confidence

The following are source-documented or cross-checked more strongly:

- LPUART3.
- FlexIO.
- FlexCAN.
- LPSPI.

The following IRQ values are still placeholders or rely on reuse from the
S32K388 model and should be checked against the official S32K389 interrupt
map before claiming hardware-accurate routing:

- LPI2C.
- SWT.
- ADC.
- eMIOS.
- eDMA.
- GMAC.
- QuadSPI.
- SAI.

### 4.5 NVIC validation status

Source inspection validates:

- NVIC creation and CPU association.
- PPB/system-register mapping.
- peripheral-to-NVIC connection pattern.
- vector-table setup.
- enable/pending/active/priority/arbitration paths.

Runtime ISR validation is incomplete. A future continuation should add a small
S32K389 ELF that enables one peripheral IRQ, causes a deterministic event, and
records entry/exit in SRAM or UART. The existing `nvic_test.log` is historical
diagnostic output, not a complete automated regression test.

## 5. Ethernet/GMAC implementation

Sources:

- [npcm_gmac.c](../hw/net/npcm_gmac.c)
- [npcm_gmac.h](../include/hw/net/npcm_gmac.h)
- [npcm_gmac-test.c](../tests/qtest/npcm_gmac-test.c)
- [launch_qemu_389.sh](../scripts/launch_qemu_389.sh)

The current device is based on QEMU's NPCM GMAC model and is reused for the
S32K389 GMAC instances. This is a functional approximation, not a complete
S32K389-specific TSN/PCS implementation.

### 5.1 Instances and addresses

| Instance | Base | IRQ | QEMU ID |
|---|---:|---:|---|
| GMAC0 | `0x40484000` | `224` | `gmac0` |
| GMAC1 | `0x40488000` | `171` | `gmac1` |

The manual groups S32K388 and S32K389 as having two GMAC instances. Base/IRQ
reuse from the S32K388 model is documented in `s32k389.h`; several IRQ values
remain unverified.

### 5.2 Implemented datapaths

Legacy DMA path:

- TX descriptor fetch and ownership handling.
- TX buffer 1/buffer 2 and chained/last-segment handling.
- Optional checksum calculation.
- Packet delivery to QEMU networking.
- TX descriptor ownership return and completion status.

- RX descriptor fetch and ownership handling.
- Buffer 1/buffer 2 and chained/ring progression.
- Guest-memory packet writes.
- Frame length, first/last descriptor, frame-type, and RX interrupt updates.
- RX queue flushing when DMA RX is enabled or RU is cleared.

EQOS-style TX path:

- Descriptor-list/tail-pointer traversal.
- FD/LD and frame-length handling.
- Buffer DMA reads.
- OWN-bit clearing.
- IOC/TX interrupt handling.

### 5.3 Filtering and loopback additions

The current worktree adds:

- Promiscuous receive mode.
- Broadcast filtering.
- Perfect-match filtering against MAC0–MAC3.
- Multicast filtering.
- Hash-based multicast/unicast filtering using the GMAC hash registers.
- Filtered frames are rejected before consuming an RX descriptor and update the
  missed-frame counter.
- Internal MAC loopback for both legacy and EQOS transmit paths.
- Basic PTP seconds/nanoseconds time reads based on QEMU virtual time.
- Writable PTP system/target-time-style registers with an offset.
- PTP offset migration state.

The firmware-generated frame seen in captures:

```text
66:55:44:33:22:11 > 66:55:44:33:22:11
802.3 LLC, zero-filled payload
```

is a raw Ethernet test frame. Its identical source/destination addresses
strongly suggest a self-addressed or loopback test. TAP capture proves guest
TX-to-host delivery; it does not by itself prove guest RX descriptor delivery.

### 5.4 MII/PHY/PTP limitations

MII/PHY behavior is simplified:

- A fixed PHY register image is provided.
- Link state mirrors QEMU NIC link state.
- MDIO accesses are handled synchronously.
- Autonegotiation completion is simplified.
- No complete S32K389 PCS/RGMII model exists.

PTP is only basic counter support:

- No complete IEEE-1588 timestamp engine.
- No accurate TX/RX hardware timestamp insertion.
- No full target-timestamp interrupt behavior.
- No TSN scheduling or traffic-class model.

Other remaining limitations:

- Exact vendor-specific PCF/inverse-filter semantics are not complete.
- VLAN filtering and advanced TSN behavior are not complete.
- Frame error/checksum semantics are simplified.
- Descriptor behavior should be tested against the S32K389 driver, not only
  the NPCM qtest.

### 5.5 Network launcher

The launcher is:

```text
scripts/launch_qemu_389.sh
```

Supported modes:

```text
--ethernet off|user|tap
--ethernet-ifname NAME
--can off|auto|internal|socketcan
--can-ifname NAME
```

Recommended TAP run from the active worktree:

```bash
cd /home/kj/QEMU/qemu_s32k3.worktrees/qemu-s32k389-ethernet-testing

sudo ./scripts/launch_qemu_389.sh \
  --ethernet tap \
  --ethernet-ifname tap0 \
  ELF/s32k389/Eth_InternalLoopback_S32K389.elf
```

The script creates/brings up `tap0` and `vcan0` when requested and uses:

```text
-nic tap,ifname=tap0,id=gmac0,script=no,downscript=no
```

Only GMAC0 is connected by the launcher. GMAC1 is instantiated by the board
but has no peer, so this warning is expected:

```text
qemu-system-arm: warning: nic npcm-gmac.1 has no peer
```

This is harmless if firmware uses GMAC0. A future launcher enhancement should
add a distinct GMAC1 backend option rather than attaching one TAP device to
both GMACs.

### 5.6 Ethernet runtime warnings and checkout mismatch

Older binaries produced:

```text
s32k3_edma: channel 31 write to invalid sub-offset 0x1c (value 0x0)
/machine/gmac0: Write of read-only reg: offset: 0x070c, value: 0x3ffffff
```

The active worktree contains fixes for both:

- eDMA reserved channel-space accesses at offsets `0x14`–`0x1f` are ignored.
- PTP time registers are no longer treated as read-only.

If those warnings still appear, verify the launcher and binary:

```bash
readlink -f build/qemu-system-arm
stat build/qemu-system-arm
grep -R "Reserved channel space" -n hw/dma/s32k3_edma.c
grep -n "A_NPCM_GMAC_PTP_STNSR" hw/net/npcm_gmac.c
```

Do not confuse the active worktree binary with
`/home/kj/QEMU/qemu_s32k3/build/qemu-system-arm`.

## 6. Build and validation

The build tree is a normal Linux QEMU build. Reconfigure if `build.ninja` is
missing or after build-system changes:

```bash
./configure \
  --target-list=arm-softmmu \
  --disable-werror \
  --disable-docs \
  --disable-gtk \
  --disable-sdl \
  --disable-vte \
  --disable-vnc-sasl \
  --disable-curl \
  --disable-slirp
```

Build:

```bash
ninja -C build -j4 qemu-system-arm
```

Fast source checks:

```bash
git diff --check
build/qemu-system-arm -machine help | grep s32k389
```

Ethernet ELF smoke run:

```bash
timeout 10s build/qemu-system-arm \
  -M s32k389 \
  -kernel ELF/s32k389/Eth_InternalLoopback_S32K389.elf \
  -nographic \
  -serial null \
  -d guest_errors
```

The timeout is expected for a continuously running firmware image. A clean
updated-worktree smoke run should not emit the old eDMA/PTP warnings.

Capture guest TX:

```bash
sudo tcpdump -i tap0 -n -e -vv
```

Observed healthy traffic includes:

- IPv6 MLDv2 reports to `ff02::16`.
- IPv6 router solicitations to `ff02::2`.
- mDNS queries to `ff02::fb`.
- Raw self-addressed test frames using `66:55:44:33:22:11`.

The existing NPCM GMAC qtest is listed for NPCM8xx configurations. It is not
currently a complete S32K389 integration test. The qtest source has basic
PTP coverage, but the local minimal configuration may not generate a
standalone qtest executable.

## 7. Current known gaps and recommended next work

Priority order:

1. Add a true S32K389 GMAC integration test ELF or qtest that verifies:
   TX descriptors, RX descriptors, RX interrupts, internal loopback, and
   multicast filtering.
2. Add a host-to-guest RX test; current tcpdump evidence primarily proves
   guest-to-host TX.
3. Verify all S32K389 IRQ numbers against the official interrupt map.
4. Decide and implement secondary-core peripheral IRQ routing.
5. Add a second Ethernet backend option for GMAC1.
6. Implement complete S32K389 PCS/RGMII and MII semantics if the firmware
   requires them.
7. Improve IEEE-1588 PTP timestamp behavior and TSN features.
8. Implement complete VLAN, filtering corner cases, receive error flags, and
   checksum semantics.
9. Replace the shared NPCM naming/model assumptions with a dedicated S32K389
   GMAC model if register-level accuracy is required.
10. Add runtime reset/migration coverage for all custom S32K389 peripherals.

## 8. Do not regress these invariants

- Keep the S32K389 machine at four Cortex-M7 cores unless the test explicitly
  targets a reduced-core configuration.
- Preserve core 0 peripheral IRQ wiring while secondary-core routing is
  unresolved.
- Keep SWT timer behavior tied to QEMU virtual time and the generic
  `-watchdog-action` mechanism.
- Keep GMAC0 launcher ID as `gmac0`; existing scripts depend on it.
- Do not attach GMAC1 to the same TAP interface as GMAC0.
- When diagnosing runtime output, first confirm the exact worktree and
  `build/qemu-system-arm` path.
