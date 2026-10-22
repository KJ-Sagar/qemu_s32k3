# S32K389 QEMU Ethernet Development Status

**Status date:** 22 October 2026  
**Scope:** GMAC0 and GMAC1 on the S32K389 QEMU machine

## Executive summary

The S32K389 machine now has two instantiated GMAC devices using a shared QEMU
NPCM GMAC implementation with an S32K3/EQOS compatibility mode. The work
progressed from an initial mismatch between the supplied firmware's EQOS
register setup and the model's legacy DMA receive path to test-covered
channelized TX/RX datapaths, basic static RX queue routing, separate interrupt
outputs for all three DMA channels on both instances, packet filtering, and a
configurable backend for GMAC1.

This is a substantially more capable Ethernet model than the starting point,
but it is not a complete or silicon-accurate S32K389 Ethernet subsystem. The
implemented and tested scope includes three normal descriptor DMA channels,
simple static RX queue-to-channel mapping, basic filtering, and a simplified
PHY register interface. Full PHY/PCS and link negotiation, dynamic queue
selection, complete PTP/TSN and VLAN behavior, sustained reset/recovery stress,
and validation against feature-rich firmware remain open.

The current checkout also contains uncommitted changes to EQOS MDIO handling
and its qtest. Those changes implement synchronous Clause 22-style PHY-register
reads/writes and simplified autonegotiation state. They have now been built
and verified by the focused MDIO test and the complete six-test S32K389 GMAC
qtest suite.

## Starting point and implementation objective

The supplied `Eth_InternalLoopback_S32K389` firmware was useful as an
observable workload, but it exposed a key integration gap:

- The firmware configures EQOS channel-0 RX control, descriptor-list, tail,
  and ring-length registers.
- The earlier receive gate and descriptor handler used legacy DMA registers,
  so host-injected packets did not follow the receive configuration used by
  this firmware.
- The EQOS MAC address registers programmed by firmware were not initially
  the registers used by receive filtering.
- GMAC1 needed independent board IRQ wiring, device selection, and backend
  configuration rather than being assumed to share GMAC0's path.

The initial implementation objective was to support the observable S32K3
EQOS channel-0 behavior on both GMAC instances while preserving the existing
NPCM GMAC behavior for machines that use it. Channel support has since been
expanded to all three DMA channels.

## Features added

### Board integration and both GMAC instances

- GMAC0 and GMAC1 are instantiated by the S32K389 machine using the existing
  shared GMAC device type, with S32K3 mode enabled per instance.
- The board maps GMAC0 at `0x40484000` and GMAC1 at `0x40488000`.
- Common and all three channels' directional IRQs are wired separately:

  | Instance | Common | CH0 TX/RX | CH1 TX/RX | CH2 TX/RX |
  |---|---:|---:|---:|---:|
  | GMAC0 | 224 | 225 / 226 | 227 / 228 | 229 / 230 |
  | GMAC1 | 171 | 172 / 233 | 234 / 235 | 236 / 237 |

- GMAC1 is selectable through its `gmac1` NIC model alias and can be tested
  independently of GMAC0.

### Three-channel descriptor DMA

- EQOS-style TX walks the programmed descriptor list and tail, reads packet
  buffers from guest memory, assembles multi-descriptor packets, and returns
  descriptor ownership with completion status.
- EQOS-style RX uses each selected channel's S32K3 receive controls and ring
  state:
  descriptor-list base, current descriptor, tail, ring length, DMA DSL,
  ownership, buffer validity/size, and supported 64-bit buffer addresses.
- RX packets can be split across descriptors, with descriptor completion,
  first/last indicators, packet length, ownership return, ring progression,
  and ring-exhaustion status updates.
- The backend frame is completed with an Ethernet FCS before delivery to guest
  RX DMA; the RX packet length includes the FCS.
- Each of the three EQOS DMA channels has independent TX/RX descriptor,
  tail-pointer, ring, control, status, and interrupt-enable register state.
- RX availability follows the EQOS MAC receive-enable and selected channel's
  RX-start controls. Starting RX or advancing its tail makes newly available
  work eligible for processing.
- Basic descriptor-driven status is reflected in DMA channel status,
  including RX/TX completion and relevant unavailable/error conditions.

### RX queues and DMA channel mapping

- Three RX queues are selected using the configured untagged queue or VLAN
  PCP-to-queue masks.
- Static queue-to-DMA-channel mappings are read from `MTL_RxQ_DMA_Map0`.
- Invalid static mappings are reported as guest errors and fall back to DMA
  channel 0; dynamic DA/L3-L4 mapping currently falls back to channel 0.
- Tests cover independent channel-1/channel-2 TX and RX DMA, queue selection
  for untagged and VLAN-priority traffic, and routing isolation on both GMACs.
- This is a focused subset, not full MTL arbitration, VLAN parsing, or EQOS
  classification behavior.

### Filtering, loopback, and packet handling

- Receive filtering supports promiscuous mode, broadcast, perfect MAC address
  matching, multicast acceptance, and hash-based multicast/unicast matching.
- EQOS filtering uses the programmed EQOS MAC address slots and packet-filter
  configuration.
- Filtered frames do not consume an RX descriptor and update the missed-frame
  counter.
- Basic internal MAC loopback is supported on the legacy and EQOS transmit
  paths.
- Existing TX checksum insertion support is retained for the supported
  descriptor path; this should not be interpreted as complete checksum
  offload fidelity.

### Interrupt behavior

- The combined GMAC summary remains available on the common IRQ.
- In S32K3 mode, each channel's TX and RX interrupt outputs are derived
  separately from its corresponding enabled DMA status sources.
- DMA status bits are write-one-to-clear (W1C); clearing the relevant status
  updates the summary and directional IRQ outputs.
- The board IRQ values above are covered by the GMAC qtests for both instances
  where applicable.

### MDIO and PHY model

- The baseline model exposed a simplified fixed PHY register image and link
  state derived from QEMU NIC link state.
- The current uncommitted changes add EQOS MAC MDIO address/data transaction
  handling for synchronous Clause 22-style reads and writes, PHY/register
  address extraction, PHY reset handling, and simplified autonegotiation
  status/partner advertisement behavior. The S32K3 model exposes a PHY at
  address 0; reads from other PHY addresses return `0xffff`.
- Clause 45 MDIO, a real PCS/RGMII model, timing-accurate negotiation, and
  hardware-specific PHY identity/behavior are not implemented.
- The qtest exercises PHY identification, register access, and basic
  link/autonegotiation behavior on GMAC0 and GMAC1.

### Runtime configuration

- `scripts/launch_qemu_389.sh` supports independent GMAC1 backend selection:
  `--ethernet-gmac1 off|user|tap` and
  `--ethernet-gmac1-ifname <name>`.
- GMAC1 backend defaults to off, preserving the previous GMAC0-only default.
- The launcher uses explicit `gmac0`/`gmac1` model aliases so a backend is
  attached to the intended controller.

## Code changes by file

| File | Role of the changes |
|---|---|
| [`hw/net/npcm_gmac.c`](../hw/net/npcm_gmac.c) | Shared GMAC implementation; S32K3 mode behavior; three EQOS DMA channels; static RX queue mapping; descriptor and ring progression; filtering and loopback; DMA status/IRQ updates; simplified PHY/MDIO behavior. |
| [`include/hw/net/npcm_gmac.h`](../include/hw/net/npcm_gmac.h) | Device state and three independent TX/RX channel IRQ outputs. |
| [`hw/arm/s32k389.c`](../hw/arm/s32k389.c) | GMAC0/GMAC1 instantiation, S32K3 mode selection, NIC setup, MMIO mapping, and common plus per-channel TX/RX IRQ connections. |
| [`hw/arm/s32k389.h`](../hw/arm/s32k389.h) | GMAC instance base addresses, DMA channel count, and board IRQ definitions. |
| [`tests/qtest/s32k389-gmac-test.c`](../tests/qtest/s32k389-gmac-test.c) | Socket-backed EQOS RX/TX, multi-descriptor and ring behavior, filtering, MDIO/link tests, DMA error/reset/recovery, queue/channel tests, and GMAC1 datapath/IRQ checks. |
| [`tests/qtest/meson.build`](../tests/qtest/meson.build) | Registers/builds the S32K389 GMAC qtest target. |
| [`scripts/launch_qemu_389.sh`](../scripts/launch_qemu_389.sh) | Adds separate optional GMAC1 backend configuration while preserving GMAC0 launcher behavior. |
| [`HANDOFFS/docs/s32k389-ethernet-driver-audit.md`](./docs/s32k389-ethernet-driver-audit.md) | Records the original firmware MMIO observations, initial model mismatch, and black-box test context. |

The shared implementation is intentional: the S32K3 behavior is gated by a
device property so the changes do not redefine the NPCM register model for
other boards.

## Validation completed and evidence

### Automated qtests

The S32K389 GMAC qtests exercise the following behaviors:

- Host-to-guest EQOS RX, including programmed MAC filtering, payload delivery,
  FCS length, and descriptor writeback.
- Multi-descriptor RX, ring progression/re-arm, and ring exhaustion.
- Guest-to-host EQOS TX, including descriptor completion and multi-descriptor
  packet assembly.
- DMA buffer error reporting, W1C clearing, software reset, and datapath
  recovery.
- Three independent TX/RX DMA channels, untagged/VLAN PCP RX queue routing,
  and GMAC0/GMAC1 datapath isolation.
- Common and per-channel directional IRQ assertion and W1C deassertion.
- MDIO/PHY identification, register access, reset/autonegotiation behavior,
  and independent coverage on GMAC0 and GMAC1.

The current qtest executable was built and the complete S32K389 GMAC suite
passed: all eight tests, including MDIO/link behavior, DMA error/reset/recovery,
three-channel queue routing, and GMAC1 channel datapaths and IRQs. The MDIO
test initially exposed incorrect reads from unimplemented PHY addresses; the
model was restricted to PHY address 0 and the updated test then passed. QEMU
emits the expected `has no peer` warning when a qtest instantiates only one of
the two NIC backends.

The queue/channel test was also run independently after its GMAC1 coverage was
added. The separate `npcm_gmac-test` regression target is not configured in
this build directory; the S32K389 qtests exercise the shared device's S32K3
mode.

### Firmware and TAP observations

- The supplied firmware generated outbound Ethernet traffic observable on a
  TAP interface. This demonstrated guest-to-host TX for that run.
- Later manual tests used the EQOS RX descriptor setup from the firmware and
  injected deterministic Ethernet frames through TAP. Monitor observations
  showed RX descriptor ownership returning to software, channel-0 current RX
  descriptor advancing by 32 bytes, and the descriptor packet length
  accounting for a 60-byte frame plus four-byte FCS.
- The firmware's interrupt masks were zero in the observed configuration, so
  the polling firmware run did not prove guest ISR delivery. IRQ assertion and
  W1C behavior are instead covered at qtest level.
- The provided image is an internal-loopback / smoke-test example. It uses a
  small ring and polling and does not validate a complete external network
  stack, PHY negotiation, GMAC1 firmware use, multiple queues, or advanced
  offloads.

### What the evidence does and does not establish

It establishes functional, testable three-channel datapaths for the exercised
descriptor forms, static queue mapping, backend packet movement, selected
filtering behavior, and board IRQ line routing. It does **not** establish production-grade
compatibility, full S32K389 silicon conformance, complete feature coverage,
or reliability under long-duration/high-load use.

## Current limitations

1. **DMA queues/channels:** Three channels and basic static queue-to-channel
   mapping are implemented. Dynamic DA/L3-L4 selection, full VLAN priority
   mapping, MTL arbitration, and complete per-queue behavior are not modeled.
2. **PHY/PCS/link:** MDIO is simplified and synchronous. Clause 45, a full
   PHY/PCS/RGMII model, timing-dependent autonegotiation, speed/duplex
   resolution, and PHY interrupt behavior remain unimplemented or unverified.
3. **Reset and recovery:** Device/DMA reset sequencing, in-flight packet
   behavior, queue restart after errors, and sustained recovery are not
   comprehensively covered.
4. **Filtering and protocol features:** VLAN and control-frame corner cases,
   complete source-address filtering, and full checksum/error reporting need
   more work and reference-based validation.
5. **PTP/TSN:** Basic time-counter/register behavior exists, but complete
   IEEE-1588 TX/RX timestamping, timestamp interrupt behavior, TSN scheduling,
   traffic classes, and time-aware shaping are not implemented.
6. **Firmware coverage:** The local loopback ELF is not a comprehensive
   validation workload. Feature-rich NXP firmware for external networking,
   MDIO, GMAC1, multiple queues, and advanced MAC functions is still needed.
7. **Hardware accuracy:** Several register/descriptor details are based on
   the available manual, supplied interrupt map, and observed firmware. All
   supported descriptor variants and feature bits still need cross-checking
   against authoritative S32K389 documentation and representative drivers.

## Recommended next steps

### 1. Extend MDIO validation against firmware requirements

- The suite covers invalid PHY addresses, unsupported Clause 45 requests,
  PHY reset, link-down/up, autonegotiation restart, and BMCR power-down/up.
  Preserve these regressions when changing MDIO behavior.
- Add timing, negotiated speed/duplex, and PHY interrupt coverage when
  authoritative device behavior or a target firmware trace is available.

### 2. Strengthen channelized DMA conformance and error behavior

- Verify descriptor layouts and status bits against the applicable S32K3
  reference manual and vendor driver definitions.
- Extend invalid-buffer, malformed-length, DMA read/write-failure, FCS/error
  flag, and recovery coverage across channels 1/2 and both GMACs.
- Test ring wrap, tail semantics, and reset while descriptors are owned by
  DMA for every channel used by target firmware.

### 3. Complete queue behavior deliberately

- Confirm queue enable and VLAN PCP semantics against the exact S32K389
  register definitions and target firmware traces.
- Implement dynamic DA/L3-L4 channel selection only if the target firmware
  requires it, then test independent queue progress and IRQ routing.

### 4. Build feature-rich firmware coverage

- Obtain an NXP S32K3 RTD/S32 Design Studio or AUTOSAR example that performs
  external PHY/MDIO setup and non-loopback IP networking.
- Add workloads for GMAC1, multiple RX/TX queues, checksum/VLAN, and PTP/TSN
  where available.
- Record the exact firmware configuration, QEMU command line, packet captures,
  register traces, and expected results so each feature has repeatable
  evidence.

### 5. Implement advanced features only against requirements

- Scope VLAN, checksum, PTP, and TSN work from actual firmware requirements
  and public hardware definitions instead of approximating unused register
  fields.
- Add model state migration/reset coverage if these devices are expected to
  participate in those QEMU lifecycle operations.
- Reassess whether continued reuse of the NPCM model remains maintainable or
  whether a dedicated S32K3 EQOS device should be extracted once feature
  divergence becomes substantial.

## Reproduction and useful references

Build the QEMU binary and qtest target using the configured build directory:

```bash
ninja -C build qemu-system-arm tests/qtest/s32k389-gmac-test
```

Run the MDIO test:

```bash
QTEST_QEMU_BINARY="$PWD/build/qemu-system-arm" \
  ./build/tests/qtest/s32k389-gmac-test \
  -p /arm/s32k389/gmac/eqos-mdio-phy
```

Run the S32K389 GMAC qtests:

```bash
QTEST_QEMU_BINARY="$PWD/build/qemu-system-arm" \
  ./build/tests/qtest/s32k389-gmac-test
```

For a firmware-backed TAP test, use the launcher from this worktree and
configure GMAC1 separately when the test image requires it. The local
`Eth_InternalLoopback_S32K389` image is suitable for a focused smoke test, not
for validating the outstanding feature set.

Related documents:

- [Ethernet driver audit](./docs/s32k389-ethernet-driver-audit.md)
- [Implementation handoff](./HANDOFF_NEW.md)
