# S32K389 Ethernet Driver Audit

## Scope and method

This audit uses the S32K389 Ethernet ELF as a black-box workload and traces
GMAC0 MMIO writes while it runs under QEMU. It records observable device
configuration and compares it with the QEMU model. It does not copy or modify
vendor driver source.

The audited image is:

```text
ELF/s32k389/Eth_InternalLoopback_S32K389.elf
```

Run a focused MMIO trace from the repository root with:

```bash
timeout 20s build/qemu-system-arm \
  -M s32k389 \
  -kernel ELF/s32k389/Eth_InternalLoopback_S32K389.elf \
  -nographic -monitor none -serial null \
  -trace enable=npcm_gmac_reg_write
```

The timeout is expected because the firmware continues running.

## Observed GMAC0 configuration

The trace shows that the firmware uses the EQOS-style channel-0 DMA register
window for both transmit and receive. The following offsets are relative to
GMAC0's base address (`0x40484000`).

| Register offset | Observed write(s) | Interpretation |
|---:|---:|---|
| `0x1000` | `0x00020101`, `0x00010000` | Legacy DMA bus-mode setup/reset activity |
| `0x1004` | `0x00001000` | Legacy transmit poll demand |
| `0x1100` | `0x00080000` | EQOS channel-0 DMA control configuration |
| `0x1104` | `0x00080010`, later `0x00080011` | EQOS channel-0 TX control; start bit is set in the later value |
| `0x1108` | `0x00080080`, later `0x00080081` | EQOS channel-0 RX control; start bit is set in the later value |
| `0x1114` | `0x20501a00` | TX descriptor-list base |
| `0x1120` | `0x20501a00`, later `0x20501a20` | TX descriptor tail updates |
| `0x112c` | `3` | TX ring length field |
| `0x111c` | `0x20501700` | RX descriptor-list base |
| `0x1128` | `0x20501780` | RX descriptor tail |
| `0x1130` | `3` | RX ring length field |
| `0x1134` | `0` | Channel interrupt-enable register is written as zero in this trace |
| `0x0300`, `0x0304` | `0x80001122`, `0x33445566` | EQOS MAC-address programming; observed packet source/destination is `66:55:44:33:22:11` |
| `0x0710`, `0x070c` | `0x03ffffff` | PTP-related register writes |

The RX ring occupies `0x80` bytes from `0x20501700` through `0x2050177f`.
At runtime, the first descriptor-sized region starts with these eight
little-endian words:

```text
0x20501900  0x00000000  0x00000000  0xc1000000
0x20501900  0x00000040  0x20501900  0x00000000
```

This is recorded as a memory observation, not as a definitive descriptor
field interpretation. Confirm the exact layout and completion format against
the applicable public hardware documentation before relying on individual
word meanings.

## Model comparison

The current model has an EQOS-style TX routine and legacy DMA RX handling.
Its network `can_receive` gate tests the legacy MAC receive-enable bit and
legacy DMA RX start bit. Its packet receive handler then follows the legacy
RX descriptor base/current-descriptor registers.

The observed firmware configures EQOS channel-0 RX control, descriptor-list,
tail, and ring-length registers, but the trace contains no write enabling the
legacy DMA RX path at offset `0x1018`. Therefore the model's existing receive
gate/handler does not match the RX path configured by this workload. This is
the primary driver-level gap to address next: implement EQOS channel-0 RX
availability, descriptor processing, completion status, and queue/tail
progression, and test it with injected host frames.

The firmware also programs the EQOS MAC address registers at offsets
`0x300/0x304`. The current model's perfect-match receive filter reads the
legacy address slots at offsets `0x40` through `0x5c`; it does not use the
observed EQOS address writes. As a result, unicast filtering against the
firmware-configured MAC address is not established and is likely incorrect.
The EQOS address register behavior and the MAC address used by RX filtering
must be aligned and tested with a frame addressed to `66:55:44:33:22:11`.

The trace writes zero to the channel interrupt-enable register. This workload
may be using polling for at least this channel configuration. Do not treat
interrupt delivery as proven or required by this trace alone; validate
interrupt behavior separately with a test configuration that enables it.

## Evidence and limitations

- Guest-generated Ethernet frames have been observed on TAP, which confirms
  guest-to-backend transmission for the tested run.
- The MMIO trace confirms that the firmware sets up EQOS RX descriptors, but
  does not prove that a host-injected frame reaches guest RAM.
- No RX descriptor completion, received payload, or RX interrupt has yet been
  demonstrated end to end.
- GMAC1 is not involved in this GMAC0 trace.
- This audit does not establish complete S32K389 PHY/PCS, VLAN, TSN, or PTP
  conformance.

## Next test milestone

Build a repeatable test around the observed EQOS RX setup:

1. Provide an RX descriptor ring and buffers, with ownership transferred to
   DMA.
2. Inject a deterministic Ethernet frame from the host backend.
3. Verify the payload in guest memory and the descriptor's completion/status
   fields, including ownership return.
4. Verify ring advancement and behavior at the tail/ring boundary.
5. Add a separate enabled-interrupt case and verify interrupt assertion and
   guest acknowledgement.

Use the target ELF as an additional black-box regression workload after the
descriptor semantics are established from public hardware documentation.
