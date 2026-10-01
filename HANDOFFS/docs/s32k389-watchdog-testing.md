# S32K389 Watchdog Binary Test

## Purpose

The test binary
[Eth_InternalLoopback_S32K389_WatchdogMulticoreFault.elf](../ELF/s32k389/Eth_InternalLoopback_S32K389_WatchdogMulticoreFault.elf)
is a deliberately faulty S32K389 guest image. It verifies that the QEMU SWT
watchdog detects loss of watchdog servicing and performs the configured
`reset` or `pause` action without using the manual `swt_trigger` command.

The S32K389 model creates four Cortex-M7 cores. All cores execute the same ELF.
SWT0 is shared, so one timeout event controls the board-level action.

## Binary workflow

1. QEMU loads the ELF through the reset vector.
2. Each core enters `main()` and atomically claims a diagnostic slot from
   shared SRAM.
3. Each core records that it reached the test.
4. The core assigned slot 0 unlocks and configures the shared SWT0.
5. SWT0 is configured for approximately one second.
6. Every core stops servicing the watchdog and enters a deterministic fault
   state:
   - slot 0: CPU-bound non-servicing loop;
   - slot 1: undefined instruction (`UDF #0`);
   - slot 2: second undefined-instruction path (`UDF #1`);
   - slot 3: non-servicing corrupted-state-style loop.
7. SWT0 expires and QEMU performs the selected watchdog action.

The source is
[watchdog_multicore_fault_test.c](../Eth_InternalLoopback_S32K388/src/watchdog_multicore_fault_test.c).

## Watchdog configuration

SWT0 base address:

```text
0x40270000
```

Registers used:

| Register | Address | Use |
|---|---:|---|
| `CR` | `0x40270000` | Enable watchdog with `WEN = 1` |
| `TO` | `0x40270008` | Set timeout |
| `SR` | `0x40270010` | Unlock SWT |

The binary writes:

```c
SWT0_SR = 0xC520;
SWT0_SR = 0xD928;
SWT0_TO = 32768;
SWT0_CR = 1;
```

The QEMU model uses a 32,768 Hz SWT clock:

```text
32768 counts / 32768 Hz = approximately 1 second
```

`CR[ITR]` remains clear, so the first timeout performs the configured QEMU
watchdog action. The binary never writes the SWT service sequence
`0xA602`, `0xB480`.

## Diagnostic SRAM

The binary writes debug state to shared SRAM starting at `0x2040f000`:

| Offset | Meaning |
|---:|---|
| `0x00`, `0x08`, `0x10`, `0x18` | Per-core phase |
| `0x04`, `0x0c`, `0x14`, `0x1c` | Per-core heartbeat |
| `0x20` | Atomic slot counter |
| `0x28` | SWT-arm status |

Inspect these values before a timeout with:

```text
xp/12xw 0x2040f000
```

The heartbeat changes while a core is executing. Phase values identify the
state reached by each core. Use pause mode for inspection because reset mode
can immediately start another boot and overwrite the markers.

## Build locations

QEMU executable:

```text
build/qemu-system-arm
```

Build QEMU:

```bash
ninja -C build qemu-system-arm
```

Watchdog ELF:

```text
ELF/s32k389/Eth_InternalLoopback_S32K389_WatchdogMulticoreFault.elf
```

The ELF is an ARM Cortex-M7 ELF32 image and is built separately from QEMU
using the existing S32DS-generated compiler/linker configuration.

## Automated tests

From the repository root:

```bash
scripts/s32k389-watchdog-test.sh reset
```

Expected result:

```text
VM status: running
watchdog reset test passed
```

The watchdog reset restarts the guest, so QEMU remains running.

Test pause behavior:

```bash
MONITOR_PORT=5600 scripts/s32k389-watchdog-test.sh pause
```

Expected result:

```text
VM status: paused (watchdog)
watchdog pause test passed
```

The script uses the multicore ELF by default. Override values when needed:

```bash
QEMU_BIN=/path/to/qemu-system-arm \
S32K389_WATCHDOG_ELF=/path/to/test.elf \
MONITOR_PORT=5600 \
RUN_SECONDS=3 \
scripts/s32k389-watchdog-test.sh reset
```

The script writes the QEMU log to `s32k389-watchdog-test.log` and verifies
that it contains:

```text
s32k3_swt[0]: watchdog timeout, performing configured watchdog action
```

## Manual QEMU run

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

Connect to the monitor:

```bash
telnet 127.0.0.1 5555
```

Useful monitor commands:

```text
info status
info registers
xp/12xw 0x2040f000
xp/8xw 0x40270000
```

The watchdog action can be selected at runtime:

```text
watchdog_action pause
watchdog_action reset
```

`watchdog_action` selects behavior; it does not trigger the timer. The
automatic firmware test does not require `swt_trigger`. Use `cont` to resume
after a watchdog pause.

Inspect exception and watchdog logging from the host shell, not the QEMU
monitor:

```bash
grep -E 'HardFault|UsageFault|s32k3_swt|watchdog' /tmp/s32k389-qemu.log
```
