# S32K389 watchdog testing

## What is implemented

The S32K3 SWT model is connected to the S32K389 board at:

| Instance | Base           | IRQ |
| -------- | -------------- | --: |
| SWT0     | `0x40270000` | 177 |
| SWT1     | `0x4046c000` | 178 |
| SWT2     | `0x40470000` | 179 |
| SWT3     | `0x40070000` | 180 |

The model uses a 32,768 Hz counter clock:

```text
timeout_seconds = TO / 32768
```

Examples:

|    `TO` |              Duration |
| --------: | --------------------: |
|     `1` | approximately 30.5 us |
| `0x320` | approximately 24.4 ms |
| `32768` |     approximately 1 s |

The normal firmware cycle is:

1. Unlock SWT software lock with `SR = 0xc520`, followed by `SR = 0xd928`.
2. Write a timeout to `TO`.
3. Set `CR[WEN]`.
4. Service with `SR = 0xa602`, followed by `SR = 0xb480`, before expiry.
5. If the service sequence is omitted, `IR[TIF]` is set and the configured QEMU watchdog action runs.

With `CR[ITR]` set, the first timeout raises the SWT interrupt and reloads the timer; the second timeout performs the configured action. Clearing `ITR` makes the first timeout perform the action.

## Watchdog fault firmware

The test firmware is [watchdog_fault_test.c](../Eth_InternalLoopback_S32K388/src/watchdog_fault_test.c). It:

- writes `32768` to SWT0 `TO`;
- writes `1` to SWT0 `CR`;
- never writes the service sequence;
- executes a busy loop so the timeout does not depend on low-power clock behavior.

Because SWT reset state is software-locked, the firmware first writes the
documented unlock keys (`0xc520`, `0xd928`) to `SR`.

The resulting ELF is:

[Eth_InternalLoopback_S32K388_WatchdogFault.elf](../Eth_InternalLoopback_S32K388/Debug_FLASH/Eth_InternalLoopback_S32K388_WatchdogFault.elf)

No new guest ELF is needed for QEMU model-only changes, but this ELF is useful for testing automatic expiry.

## Multicore watchdog fault firmware

The multicore test image is
[watchdog_multicore_fault_test.c](../Eth_InternalLoopback_S32K388/src/watchdog_multicore_fault_test.c).
All four S32K389 cores execute the image and claim diagnostic SRAM slots. The
atomic allocation counter rotates the SWT0 configuration owner on each boot,
so watchdog reset need not clear shared SRAM and only one core performs the
unlock sequence. After SWT0 is armed, the cores enter deterministic,
core-specific failure modes: CPU-bound deadlock, usage fault, hard fault, or a
corrupted-state loop. None services SWT0, so the shared watchdog eventually
resets the board.

The resulting ELF is:

[Eth_InternalLoopback_S32K388_WatchdogMulticoreFault.elf](../Eth_InternalLoopback_S32K388/Debug_FLASH/Eth_InternalLoopback_S32K388_WatchdogMulticoreFault.elf)

### Guest execution diagnostics

The firmware does not use `printf`; the image has no guaranteed initialized
console for all four cores. Instead, it writes phase and heartbeat values to
shared SRAM at `0x2040f000`:

| Address | Meaning |
|---|---|
| `+0x00`, `+0x08`, `+0x10`, `+0x18` | Core-slot phase |
| `+0x04`, `+0x0c`, `+0x14`, `+0x1c` | Core-slot heartbeat |
| `+0x20` | Atomic slot-allocation counter |
| `+0x28` | Watchdog-arm status |

Phase values are:

```text
0x10000000 + slot  claimed a slot
0x20000000 + slot  core armed SWT0 (global status at `+0x28`)
0x30000000 + slot  CPU-bound deadlock loop
0x40000000 + slot  usage fault (UDF)
0x50000000 + slot  hard-fault test (UDF)
0x60000000 + slot  corrupted-state-style loop
```

Before the watchdog action, inspect the markers from the QEMU monitor:

```text
xp/12xw 0x2040f000
xp/8xw  0x40270000
info registers
```

The heartbeat words change continuously for cores that reached their loop.
The phase words remain stable and identify how far each core progressed.
After a reset, these values may be overwritten by the next boot; use
`watchdog_action pause` when inspecting transient state.

QEMU execution and exception logging should be enabled from the host:

```bash
build/qemu-system-arm ... -d int,guest_errors -D /tmp/s32k389-qemu.log \
  -msg timestamp=on
grep -E 'HardFault|UsageFault|s32k3_swt|watchdog' /tmp/s32k389-qemu.log
```

## Build the QEMU binary

From the repository root:

```bash
ninja -C build qemu-system-arm
```

The executable is `build/qemu-system-arm`.

## Automatic reset test

The firmware unlocks and arms SWT0 automatically. Do not use `swt_trigger`.

```bash
scripts/s32k389-watchdog-test.sh reset
```

Expected output includes:

```text
VM status: running
watchdog reset test passed
```

The VM remains running because the watchdog reset restarts the guest.

## Automatic pause test

```bash
scripts/s32k389-watchdog-test.sh pause
```

Expected output includes:

```text
VM status: paused (watchdog)
watchdog pause test passed
```

If monitor port 5555 is already in use, select another port:

```bash
MONITOR_PORT=5565 scripts/s32k389-watchdog-test.sh pause
```

The script writes the QEMU debug log to `s32k389-watchdog-test.log`. Inspect it from the host shell:

```bash
grep -E 's32k3_swt|watchdog' s32k389-watchdog-test.log
```

Expected timeout message:

```text
s32k3_swt[0]: watchdog timeout, performing configured watchdog action
```

## Manual monitor test

Launch QEMU with:

```bash
build/qemu-system-arm \
  -M s32k389 \
  -kernel Eth_InternalLoopback_S32K388/Debug_FLASH/Eth_InternalLoopback_S32K388_WatchdogFault.elf \
  -watchdog-action pause \
  -d int,guest_errors \
  -D /tmp/s32k389-qemu.log \
  -display none \
  -serial telnet:127.0.0.1:5556,server=on,wait=off \
  -monitor telnet:127.0.0.1:5555,server=on,wait=off
```

Connect to the QEMU monitor:

```bash
telnet 127.0.0.1 5555
```

Valid monitor commands:

```text
info status
info registers
xp/8xw 0x40270000
watchdog_action pause
watchdog_action reset
swt_trigger 0
cont
```

`watchdog_action` selects the action; it does not trigger or resume the VM. `swt_trigger 0` is an explicit immediate test hook. It sets `TO = 1`, sets `WEN`, clears `ITR`, and schedules expiry. It is not required for the automatic firmware test.

Use `cont` after a pause before attempting another test. Shell commands such as `grep` must be run in the host terminal, not at the `(qemu)` prompt.

## Observed results

- The HMP command parser initially failed because command documentation was placed after the next command definition; the documentation was reordered.
- Generic QEMU targets initially failed to link because the monitor handler referenced the optional SWT implementation. A weak fallback was added, and the S32K389 board provides a link anchor for the real implementation.
- `qemu-system-arm` and `qemu-system-avr` were rebuilt successfully.
- `watchdog_action pause` followed by `swt_trigger 0` produced `VM status: paused (watchdog)`.
- `watchdog_action reset` produced the SWT timeout log and restarted the guest; the VM then reported `running`.
- The post-reset SWT registers show reset/firmware values, so transient trigger values should be inspected with the pause action.
