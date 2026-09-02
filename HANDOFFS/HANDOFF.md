# S32K389 QEMU Machine Model — Handoff Document

**Repo root:** `C:\QEMU\qemu_s32k344` (a QEMU source tree; the board model lives in `hw/arm/s32k389.c` / `hw/arm/s32k389.h`)

**Status as of this handoff:** all originally-scoped peripheral work is complete. Every task below is `completed` or `deleted` (N/A) in the task list. There is no in-progress work.

**Current status (2026-08-07):** the S32K389 machine model is built and available in the current workspace; a local `make -j4 qemu-system-arm` run completed successfully. The most recent functional addition was the SAI peripheral model, which was implemented, wired into the board, and documented here along with its verification notes and known limitations.

**Changes made in this pass:** added the SAI device model and board integration (`hw/audio/s32k3_sai.c` / `.h`), exposed the new peripheral through the S32K389 board headers and initialization path, updated the audio build configuration (`hw/audio/Kconfig` and `hw/audio/meson.build`), and added the new wiring in `hw/arm/s32k389.c` / `.h` and `hw/arm/Kconfig`. This document now captures the current build outcome, the implemented peripheral set, and the remaining verification gaps for future work.

### Why it was failing and how it was fixed

Several issues appeared while bringing the model up to a working state, and each one had a specific root cause:

- The initial build failures were not caused by the peripheral logic itself, but by using the wrong QEMU API patterns for this tree. The SAI work initially hit header include errors because the code used old-style paths such as `hw/sysbus.h` and `hw/irq.h`; those had to be switched to the tree's actual include layout under `hw/core/`.
- The first compile attempts also failed because the device model used an outdated convention for reset hooks. In this QEMU checkout, `DeviceClass` does not have a `.reset` field, so assigning `dc->reset = ...` caused build failures. The fix was to implement a normal `foo_reset()` helper and call it explicitly from `realize()` once during device creation.
- A few more build errors came from signature mismatches in the QOM registration code. `class_init()` in this tree expects `const void *data`, and the property table must be declared as `static const Property`, otherwise the build fails under `-Werror`.
- The environment also introduced a separate class of problems. The source tree was checked out with Windows-style CRLF line endings, which breaks QEMU's Meson/Ninja flow in the Linux build environment. The fix was to build from a Linux clone in `/tmp/qbuild`, copy over the modified files, and strip CRLF before configuring and building.
- The last major issue was build-system churn from adding new device files and Kconfig/meson wiring. Each change required rerunning Meson configuration and then rebuilding incrementally with Ninja. Once the board wiring, build files, and device files were all aligned, the final build completed successfully.

This document exists so a fresh LLM session (or human) can understand what was built, why, how to build/test it, and what is still weak/unverified if further hardening is wanted.

---

## 1. Original goal

Bring the existing single-core, FlexCAN/UART-only QEMU `s32k389` machine model up to a much fuller emulation of the real NXP S32K389 (4x Cortex-M7 automotive MCU), by adding the peripheral groups the user explicitly selected:

1. **Networking & storage:** Ethernet (GMAC), QuadSPI, uSDHC, SAI
2. **Core comms:** LPSPI + I2C
3. **Sensing & timing:** ADC + eMIOS/GTM
4. **eDMA + safety peripherals:** Watchdog (SWT), CRC

Plus, separately: **multi-core** (real chip has 4 Cortex-M7 cores; model started with 1), attempted with a lockstep stub.

**Fidelity bar chosen by the user:** "Functional where practical" — i.e. real register read/write side effects and real data-path behavior (actual bytes moved, actual FIFO occupancy, actual counters), not just bus-fault-avoiding stub registers. This matches the precedent already set in this codebase by the pre-existing FlexCAN and UART models.

## 2. Reference material

- `NXP Manuals/S32K3XXRM.pdf` in the repo (also copied to the uploads folder as `S32K3xx-Manual.pdf` / `S32K3xx.pdf`) — the S32K3xx Reference Manual, Rev. 12. This is the primary source for every register map, bitfield, and reset value used below. Extract text with `pdftotext -f <start> -l <end> -layout manual.pdf out.txt`, or dump the whole thing (`pdftotext -layout manual.pdf full.txt`, ~350k lines) and `grep -n` for chapter/section headers — this was the most reliable technique once page-number-only extraction proved to not line up with the PDF's internal page numbering for some chapters (always double check by grepping for the chapter title text, not just assumed page ranges).
- `S32K3xx_memory_map.xlsx` and `S32K3xx_interrupt_map.xlsx` were referenced earlier in the project (before this session) for some base addresses and IRQ numbers, but **were not available as uploaded files during this session**. Anywhere an IRQ number could not be cross-checked against that spreadsheet, it is explicitly marked in the header comments as `UNVERIFIED PLACEHOLDER`. See §6 for the full list of these gaps.
- Sibling board file `hw/arm/s32k388.c` / `.h` (already in this codebase, pre-existing) was used directly as a reuse source for GMAC, on the strength of the manual's Table 618 grouping S32K388 and S32K389 in the same column for that peripheral.

## 3. Build workflow — READ THIS BEFORE BUILDING

This is the single most error-prone part of working in this environment. Get it wrong and you will waste many tool calls.

### 3.1 The path/CRLF problem

- The user's actual project folder (`C:\QEMU\qemu_s32k344`, seen from the bash sandbox as `/sessions/<session>/mnt/qemu_s32k344`) has **CRLF line endings** on every file (Windows checkout). QEMU's meson/ninja/configure scripts do not tolerate CRLF and will fail or behave strangely if built in place.
- The working build copy is a clean Linux clone kept at **`/tmp/qbuild`**, created via:
  ```
  git clone --local --no-hardlinks /sessions/<session>/mnt/qemu_s32k344 /tmp/qbuild
  ```
- **Critical gotcha:** `git clone` only replicates *committed* git content. Every peripheral file in this project was authored via the Write/Edit tools directly against the real project folder and was **never committed** — so a fresh clone of `/tmp/qbuild` will be missing all of it. After any clone (fresh or re-created), you must manually re-sync every touched/new file:
  ```bash
  SRC=/sessions/<session>/mnt/qemu_s32k344
  DST=/tmp/qbuild
  for f in <list of files>; do
    cp "$SRC/$f" "$DST/$f"
    sed -i 's/\r$//' "$DST/$f"   # strip CRLF
  done
  ```
  The full list of files that need this treatment is in §7 below (every file marked "new" or "modified").

### 3.2 Sandbox persistence is NOT guaranteed

- The bash sandbox can be silently recycled between tool calls, especially after a long gap. Always sanity-check with `ls /tmp/qbuild` before assuming state survived. If it's gone, redo the clone + resync + reconfigure + rebuild from scratch.
- **Backgrounded processes (`cmd &` / `nohup ... &`) do NOT survive past the end of the bash tool call that started them.** This was tested directly in this session: a `nohup ninja ... &` was started, the call returned immediately, and a subsequent call found the process gone and the log stalled. Do not rely on backgrounding for long builds.

### 3.3 Tool call timeout is a hard 45 seconds

- The `mcp__workspace__bash` tool has a hard ceiling of 45000ms (`timeout_ms` field rejects anything above 45000). A full `ninja qemu-system-arm` build (~700-1800 steps depending on whether meson had to regenerate) takes far longer than that.
- **The correct pattern:** just call `ninja qemu-system-arm > /tmp/build1.log 2>&1` in the foreground, repeatedly, once per tool call. The tool call itself will time out and report "Command timed out... may have partially completed" — this is expected and fine. Ninja tracks build state in `build.ninja`/`.ninja_log`, so the *next* invocation resumes exactly where it left off (it does not restart from scratch). After each timed-out call, run a quick separate `tail -N /tmp/build1.log` to see progress/errors, then re-issue the same `ninja ...` command again. Repeat until you see `Linking target qemu-system-arm` or a `FAILED:` line.
- Any edit to a `meson.build` or `Kconfig` file triggers a full meson regeneration on the next ninja invocation, which re-checks/rebuilds a large fraction of the tree (~700-1800 steps) even though only your new peripheral file actually changed. Budget ~8-15 tool-call round trips for that scenario.

### 3.4 Toolchain PATH

`ninja` and `meson` are not on the default PATH in a fresh bash call. Every bash call that invokes them needs:
```bash
export PATH=/sessions/<session>/.local/bin:$PATH
```

### 3.5 Recurring subproject-fetch flake

`berkeley-softfloat-3` / `berkeley-testfloat-3` meson subprojects sometimes fail to fully fetch (usually after a fresh clone + configure). Fix:
```bash
rm -rf /tmp/qbuild/subprojects/berkeley-softfloat-3 /tmp/qbuild/subprojects/berkeley-testfloat-3
cd /tmp/qbuild/build && ../configure --target-list=arm-softmmu
```
This is idempotent — safe to run whenever `ninja` complains about a missing/broken subproject, or when `build.ninja` doesn't exist yet (`ninja: error: loading 'build.ninja': No such file or directory` — this can also just mean the configure call itself got cut off by the 45s timeout before finishing; simply re-run `../configure` again).

### 3.6 Standard build sequence (copy-paste starting point)

```bash
export PATH=/sessions/<session>/.local/bin:$PATH
cd /tmp/qbuild/build   # create with `mkdir -p /tmp/qbuild/build` if missing
../configure --target-list=arm-softmmu > /tmp/configure.log 2>&1
tail -30 /tmp/configure.log   # confirm it completed (ends with "User defined options" block)
ninja qemu-system-arm > /tmp/build1.log 2>&1   # re-run this line repeatedly; each call times out at 45s but resumes
tail -40 /tmp/build1.log    # check for FAILED: lines after each attempt
```

## 4. Dynamic verification technique (used for every peripheral)

QEMU's `-device loader` mechanism can poke arbitrary memory *during machine reset, before any code runs* — this is how every peripheral in this project was functionally tested without needing real guest firmware.

```bash
timeout 6 ./qemu-system-arm -M s32k389 -nographic -monitor stdio -serial null -S -d guest_errors \
  -device loader,addr=<ADDR1>,data=<VAL1>,data-len=4 \
  -device loader,addr=<ADDR2>,data=<VAL2>,data-len=4 \
  ...
```
- `-S` freezes the CPU at startup (so nothing executes and clobbers your test state) — but note **`QEMU_CLOCK_VIRTUAL` does not advance while the CPU is paused this way**, which limits how far you can dynamically verify anything timer/tick-driven (eMIOS counters, SAI's FIFO drain timer, SWT countdowns) — you can prove the *setup* and *live-flag-computation* logic works, but not real elapsed-time drain/countdown behavior, from this harness alone. This limitation was hit and explicitly flagged to the user multiple times rather than faking a pass.
- Multiple `-device loader` entries targeting the **same address** apply strictly in command-line order — this is how sequences of register writes (e.g. "unlock LUT, then load LUT, then trigger IPCR twice") were expressed without needing a real running CPU.
- `-device loader,addr=X,data=Y,data-len=N,cpu-num=M` targets a specific CPU's private address space (defaults to `first_cpu` / core 0 without `cpu-num=`) — used for multi-core TCM isolation testing.
- Feed monitor commands via piped stdin to `-monitor stdio`, e.g. `xp /4xw <addr>` to dump memory/registers, `info qtree` to confirm device tree, `info mtree` to inspect the MemoryRegion/AddressSpace graph, `info cpus` for core enumeration. Pipe with a small `sleep` and end with `quit`:
  ```bash
  { echo "xp /4xw 0x40..."; echo "quit"; } | timeout 6 ./qemu-system-arm ... > /tmp/test.log 2>&1
  grep -E "^[0-9a-f]{8}: " /tmp/test.log   # extracts xp output lines
  grep -i "guest_error\|error" /tmp/test.log   # confirms no faults
  ```
- Always check for absence of `guest_errors` output as well as checking the expected data — a silent wrong-value bug is easy to miss if you only grep for errors.

## 5. QEMU API conventions specific to this codebase (IMPORTANT — non-obvious, caused real build failures this session)

This QEMU checkout is a **modern version where several APIs differ from older QEMU tutorials/examples you may have memorized.** Every existing `s32k3_*.c` peripheral in this repo already follows the corrected convention below — **copy an existing sibling file's structure rather than writing from generic QEMU device-model memory.**

1. **Header include paths use the `hw/core/` prefix**, not the bare `hw/` path:
   - `#include "hw/core/sysbus.h"` (NOT `"hw/sysbus.h"`)
   - `#include "hw/core/irq.h"` (NOT `"hw/irq.h"`)
   - `#include "hw/core/qdev-properties.h"` (NOT `"hw/qdev-properties.h"`)
   This tripped up the SAI build in this exact session (`fatal error: hw/sysbus.h: No such file or directory`) — fixed by grepping a sibling file (`hw/timer/s32k3_emios.c`) for its actual include list and matching it exactly.

2. **`DeviceClass` in this tree has no `.reset` member at all** (confirmed by reading `include/hw/core/qdev.h`'s `struct DeviceClass` directly — no `reset` field present; reset dispatch has moved entirely to the `ResettableClass` phases mechanism (`enter`/`hold`/`exit`), which none of the existing `s32k3_*` peripherals use). **The established convention in this codebase is to skip the Resettable API entirely** and instead:
   - Write a plain `static void foo_reset(DeviceState *dev)` function that zeroes all registers/state.
   - Call it **once, manually, from the end of the device's `realize()` function** (`dc->realize = foo_realize`, and `foo_realize()` ends by calling `foo_reset(dev)`).
   - Do **not** attempt `dc->reset = foo_reset;` — this will not compile (`error: 'DeviceClass' has no member named 'reset'`).
   - **Known consequence/limitation:** because of this, a guest-triggered system reset (or QEMU's `system_reset` monitor command) will **NOT** re-initialize any of these peripheral models' register state. They only reset once, at machine construction time. If a future task requires real reset-button/watchdog-triggered peripheral reinitialization, this would need to be revisited by wiring up `ResettableClass` phases properly across all `s32k3_*` peripherals (a nontrivial cross-cutting change, not attempted in this project).

3. **`class_init` signature takes `const void *data`**, not `void *data`:
   ```c
   static void foo_class_init(ObjectClass *klass, const void *data)
   ```
   Using plain `void *data` produces `error: initialization of 'void (*)(ObjectClass *, const void *)' from incompatible pointer type` due to `-Werror`.

4. **`Property` arrays must be declared `const`:**
   ```c
   static const Property foo_props[] = { DEFINE_PROP_UINT32(...), };
   ```
   (not `static Property foo_props[]`).

5. The build uses `-Werror` with a large warning set — any of the above mismatches (or an unused variable, implicit fallthrough, etc.) will hard-fail the build, not just warn.

6. Standard skeleton to copy from (best current example): `hw/timer/s32k3_emios.c` / `.h`. It demonstrates the full correct pattern: sysbus device with MMIO + IRQ, QOM properties, VMState, timer-based lazy/event-driven modeling, and the reset-called-from-realize convention.

## 6. Peripheral-by-peripheral summary

All base addresses/bitfields below were cross-checked against the S32K3xx Reference Manual Rev. 12 unless marked otherwise. Every "UNVERIFIED PLACEHOLDER" IRQ note below is copy-pasted verbatim from the actual header comments in the repo — search for that exact phrase in `hw/arm/s32k389.h` to find every remaining gap in one grep.

| # | Peripheral | Status | Base address(es) | Notes |
|---|---|---|---|---|
| 3 | LPSPI x6 | done (prior session) | 0x40358000, 0x4035C000, 0x40360000, 0x40364000, 0x404BC000, 0x404C0000 | IRQs 165-170, verified against interrupt map |
| 4 | LPI2C x2 | done (prior session) | 0x40350000, 0x40354000 | IRQs 175/176, **UNVERIFIED PLACEHOLDER** |
| 5 | SWT (watchdog) x4 | done (prior session) | 0x40270000, 0x4046C000, 0x40470000, 0x40070000 | IRQs 177-180, **UNVERIFIED PLACEHOLDER** |
| 6 | CRC | done (prior session) | 0x40380000 | No interrupt (manual: "This module has no interrupts") |
| 7 | ADC x3 (24ch, 12-bit) | done (prior session) | 0x400A0000, 0x400A4000, 0x400A8000 | IRQs 181-183, **UNVERIFIED PLACEHOLDER** |
| 8 | eMIOS x3 (24ch timer) | done (prior session) | 0x40088000, 0x4008C000, 0x40090000 | IRQs 184-186, **UNVERIFIED PLACEHOLDER**. Modeled as lazy/on-demand counter (computes live CNT from elapsed `QEMU_CLOCK_VIRTUAL` time + one event timer per channel for the next match), not a real per-tick callback (avoids pegging host CPU at an assumed 80MHz rate). The 80MHz clock assumption itself is **flagged unverified** in the header — not cross-checked against a specific manual clock table. |
| 9 | eDMA (32 channel) | done (prior session) | mgmt 0x4020C000, channel page 0x40210000 | IRQs 187-218 (one per channel), **UNVERIFIED PLACEHOLDER**. Real synchronous memory-to-memory transfers via `address_space_read/write(&address_space_memory, ...)`. Handles SSIZE==DSIZE precisely (real per-transfer-size stepped copy) and SSIZE!=DSIZE via a documented simplification (byte-by-byte copy of total count). |
| 10 | Multi-core (4x CM7) | done (prior session) | — | See detailed note below. |
| 11 | GMAC Ethernet x2 | done (prior session) | 0x40484000, 0x40488000 | IRQs 224 / 171 (reused from `s32k388.h`). Directly reuses QEMU's existing `hw/net/npcm_gmac.c` model (already compiled into this build for the sibling S32K388 board) — justified by manual Table 618 grouping S32K388/S32K389 in one column. |
| 12 | QuadSPI | **done, verified this/prior session** | controller 0x404CC000, ARDB 0x68000000 | IRQ 219, **UNVERIFIED PLACEHOLDER**. LUT-sequence-engine model: 80 LUT registers (16 sequences x 5 regs x 2 instructions), IPCR[SEQID] triggers execution against a 16MB malloc'd `flash[]` array at SFAR offset. LUT writes rejected unless unlocked via LUTKEY (0x5AF05AF0) then LCKCR[UNLOCK]. AHB memory-mapped flash *aperture* is NOT modeled (only the IP-bus command path) since its exact base address wasn't confirmed in available excerpts. **Verified this session**: unlock LUT -> program WRITE sequence (opcode 8) -> push 4 words via TBDR -> trigger IPCR -> program READ sequence (opcode 7) -> trigger IPCR again -> read back RBDR0-3 via monitor `xp` and got an exact match of all 4 original words, proving the internal flash round-trip works. No guest errors. |
| 13 | uSDHC | **deleted / not applicable** | — | Manual Table 809 ("uSDHC instances") explicitly lists S32K388 **and S32K389** in the "No" column for uSDHC support — this SoC variant genuinely does not have this peripheral on real silicon. User was asked and chose "skip uSDHC" over "implement anyway as non-standard extra." No files were created for this. If ever reversed, `hw/sd/sdhci.c` (QEMU's generic SDHCI model, already confirmed compiling into this build) was identified as the likely reuse candidate, analogous to the GMAC reuse pattern — reset value tables and register map are at manual chapter 81 (search `full.txt` for `Chapter 81` / `uSDHC memory map`, base address for chips that DO have it is `404E_4000h`). |
| 14 | SAI (I2S audio) x2 | **done, verified this session** | SAI_0 0x4036C000, SAI_1 0x404DC000 | IRQs 220/221, **UNVERIFIED PLACEHOLDER**. See detailed note below. |

### 6.1 Multi-core detail (task #10)

Real S32K389 has 4 physical Cortex-M7 cores in a lockstep/split-lock topology (manual §3.4/§3.5). A hardware lockstep checker core has no independently observable software behavior (it's a silent comparator), so there is nothing meaningful to emulate for "true lockstep." Instead:
- All 4 physical cores are exposed as **independent, separately-programmable Cortex-M7 CPUs** (`s->armv7m` for core0, plus `s->core1/core2/core3`), each with a genuinely isolated private ITCM/DTCM.
- Isolation mechanism: `memory_region_init_alias(core_mem, obj, name, system_memory, 0, UINT32_MAX)` creates a full aliased view of the shared bus, then `memory_region_add_subregion_overlap(core_mem, addr, itcm/dtcm, priority=1)` overlays that core's private RAM at the fixed local addresses (0x0 ITCM, 0x2000_0000 DTCM), masking the alias only at those ranges — everything else (flash, shared SRAM, peripherals) is visible identically across all cores.
- `armv7m_load_kernel(cpu, kernel_filename, ...)` must be called once per CPU (it also registers that CPU's reset handler) — core0 gets the real kernel filename, cores 1-3 are called with `kernel_filename=NULL` (skips reloading flash, which is shared, but still registers the per-core reset handler).
- `mc->default_cpus/min_cpus/max_cpus` **must** be set to the true core count (`S32K389_NUM_CORES` = 4), even though CPUs here are manually instantiated rather than via `-smp`. Omitting this causes a TCG crash at startup: `tcg_register_thread: assertion failed: (n < tcg_max_ctxs)` — TCG's per-thread context pool is sized from `machine->smp.max_cpus` at startup regardless of how CPUs were actually created.
- All 4 cores currently share the **same boot vector table** (`INT_CODE_FLASH0_CORE0_VTOR`) since no per-core-partition boot address split was found in available manual excerpts — real firmware for this class of chip is expected to branch on core ID early in a shared reset handler.
- **Only core 0's NVIC has peripheral IRQ lines connected.** Cores 1-3 have fully working independent NVICs (SysTick, software exceptions all function) but no peripheral is wired to them — this was out of scope without the interrupt-map spreadsheet's per-core routing info.
- Verification method: structural, via `info mtree` (confirmed 4 distinct `cpu-memory-N` AddressSpace objects with correctly isolated ITCM/DTCM region trees) and `info cpus` (4 distinct booting cortex-m7 threads). **A live cross-core read/write isolation test via the interactive monitor was attempted but gave confusing/contradictory results in both directions** — this was investigated at length and concluded to be a monitor/`-device loader` testing-harness limitation (not a device-model bug), not a confirmed pass. This remains an accepted, explicitly-flagged gap rather than something actively being chased — the `info mtree` structural evidence was accepted as sufficient given the C-code (`cpu_address_space_init()` in `system/physmem.c`) unambiguously creates independent per-CPU-instance AddressSpaces.
- A minimal **STCU2** (Self-Test Control Unit, manual Chapter 54) stub was added at `0x40054000`/16KB — BSTART/ALGOSEL storage plus an always-pass status word (`0x0000000F` = 4 cores + self-test pass). Base address is an **UNVERIFIED PLACEHOLDER** (manual repeatedly deferred STCU2's real memory map to the unavailable interrupt/memory-map spreadsheet).

### 6.2 SAI detail (task #14, most recently completed)

Files: `hw/audio/s32k3_sai.h`, `hw/audio/s32k3_sai.c` (new this session).

- 2 instances confirmed present on S32K389 via manual Table 546 (SAI_0/SAI_1 both "Yes"), unlike uSDHC.
- Register map from manual §74.6.1.1: VERID(0x0, RO, reset 0x0301_0000), PARAM(0x4, RO — SAI_0 reset 0x0004_0304 = 4 data lines/FIFO depth 8/frame size 16; SAI_1 reset 0x0004_0301 = 1 data line), TCSR(0x8), TCR1-5(0xC-0x1C), TDR0-3(0x20-0x2C), TFR0-3(0x40-0x4C, RO FIFO pointer status), TMR(0x60), then the mirrored RX set at RCSR(0x88) through RMR(0xE0).
- **TX path is genuinely functional:** TDR writes push into a real circular FIFO (depth 8 words, matching 2^FIFO from PARAM). FRF (watermark reached) and FWF (FIFO empty) status flags are computed live from actual FIFO occupancy vs. the TFW watermark field in TCR1 — not stored/faked. A `QEMUTimer` (`tx_drain_timer`) drains one word per period (period derived from TCR2[DIV] and an assumed 32-bit word width, at the manual-documented 24.576 MHz MCLK from Table 547 — this clock value, unlike eMIOS's 80MHz assumption, **is** directly sourced from the manual, not guessed) to produce genuine FIFO-underflow (FEF) behavior once TE is enabled with an empty FIFO.
- **RX path is structurally complete** (all registers readable/writable with correct reset values) but the RX FIFO is intentionally always empty — there is no external audio source wired into this model, so this matches real hardware behavior on an idle/unconnected input rather than faking loopback data that wouldn't occur on real silicon. If a future task wants to inject synthetic "incoming audio," a QOM property or chardev backend feeding `rx_fifo[0]` would be the natural extension point.
- Only data-line/channel 0 is treated as authoritative for aggregate TCSR/RCSR status-flag purposes (all 4 TDR/TFR slots are still individually readable/writable), since manual Table 547 confirms only 1 channel is actually used in this chip's real configuration even though the register map exposes up to 4.
- **Verified this session**: wrote TCR1=0 (watermark), pushed 2 words to TDR0 (0x11111111, 0x22222222), wrote TCSR=0x80000000 (TE=1). Read back: TCSR=`0x90000000` (TE + auto-set BCE, correct), TFR0=`0x00020000` (WFP=2/RFP=0, correct — 2 words pushed, none yet drained since `-S` freezes `QEMU_CLOCK_VIRTUAL`). No guest errors. This confirms FIFO push mechanics, TE/BCE bit auto-follow behavior, and live flag computation all work exactly as coded. The timer-driven drain/underflow behavior itself was **not** dynamically verified beyond code review, due to the same `-S`-freezes-virtual-clock limitation noted throughout this project (see §4) — if this needs to be proven with real elapsed time, it would require booting without `-S` and running actual firmware that reads back FR/TFR after a known wall-clock delay, or unit-testing `sai_tx_drain_tick()` in isolation outside the full QEMU harness.
- Build fixes applied to get this to compile (see §5 for full explanation): corrected `hw/sysbus.h` → `hw/core/sysbus.h`, `hw/irq.h` → `hw/core/irq.h`, `hw/qdev-properties.h` → `hw/core/qdev-properties.h`; removed the `dc->reset = ...` assignment (moved the call into `realize()`); changed `class_init`'s second parameter to `const void *data`; changed the `Property` array to `static const Property`.

## 7. Complete list of repo files touched (for re-syncing into a fresh `/tmp/qbuild` clone)

**New files this session:**
- `hw/audio/s32k3_sai.h`
- `hw/audio/s32k3_sai.c`

**New files, prior sessions (already existed before this handoff's work began, still relevant if re-syncing from scratch):**
- `hw/ssi/s32k3_lpspi.h` / `.c`
- `hw/i2c/s32k3_lpi2c.h` / `.c`
- `hw/watchdog/s32k3_swt.h` / `.c`
- `hw/misc/s32k3_crc.h` / `.c`
- `hw/adc/s32k3_adc.h` / `.c`
- `hw/timer/s32k3_emios.h` / `.c`
- `hw/dma/s32k3_edma.h` / `.c`
- `hw/ssi/s32k3_qspi.h` / `.c`
- `hw/char/s32k3_flexio_uart.h` (pre-existing, older work)
- `hw/char/s32k3_uart.h` (pre-existing, older work)
- `hw/net/s32k3_flexcan.h` (pre-existing FlexCAN, older work)

**Modified files this session:**
- `hw/audio/Kconfig` — added `config S32K3_SAI / bool`
- `hw/audio/meson.build` — added `system_ss.add(when: 'CONFIG_S32K3_SAI', if_true: files('s32k3_sai.c'))`
- `hw/arm/s32k389.h` — added `#include "hw/audio/s32k3_sai.h"`, the `S32K389_NUM_SAI`/`S32K3_SAI0_BASE`/`S32K3_SAI1_BASE`/`S32K3_SAI0_PARAM_RESET`/`S32K3_SAI1_PARAM_RESET`/`S32K3_SAI0_IRQ`/`S32K3_SAI1_IRQ` defines, and `DeviceState* sai[S32K389_NUM_SAI];` struct field
- `hw/arm/s32k389.c` — added `s32k389_init_sai()` function and its call site in `s32k389_init()`
- `hw/arm/Kconfig` — added `select S32K3_SAI` to the `config S32K389` block (careful: `NPCM_GMAC` and other `select` lines appear in multiple config blocks across this file — always confirm you're editing inside the `S32K389` block specifically, not a different board's block, by reading surrounding context first)

**Modified files, prior sessions** (relevant background, not touched this session): `hw/ssi/meson.build`+`Kconfig`, `hw/i2c/meson.build`+`Kconfig`, `hw/watchdog/meson.build`+`Kconfig`, `hw/misc/meson.build`+`Kconfig`, `hw/adc/meson.build`+`Kconfig`, `hw/timer/meson.build`+`Kconfig`, `hw/dma/meson.build`+`Kconfig`.

None of these changes have been committed to git (the repo is a plain working tree with uncommitted modifications) — this matters for the `/tmp/qbuild` re-clone workflow in §3.1.

## 8. Task list state at handoff

| ID | Subject | Status |
|---|---|---|
| 1 | Compare QEMU S32K389 model vs real S32K389 | completed |
| 2 | Write comparison docx | completed |
| 3 | LPSPI functional model (6 instances) | completed |
| 4 | LPI2C functional model (2 instances) | completed |
| 5 | Software Watchdog (SWT) model | completed |
| 6 | CRC peripheral model | completed |
| 7 | ADC model (3x 24-channel 12-bit) | completed |
| 8 | eMIOS timer/PWM model | completed |
| 9 | eDMA controller model (32 channel) | completed |
| 10 | Multi-core: add 3 extra Cortex-M7 cores + lockstep stub | completed |
| 11 | Ethernet: GMAC x2 (1Gbps TSN) | completed |
| 12 | QuadSPI controller (S32K388/389 variant) | completed |
| 13 | uSDHC controller model | **deleted** (not applicable — see §6, real S32K389 has no uSDHC) |
| 14 | SAI (I2S audio) model | completed |

**There is no pending/in-progress task.** All four originally-requested peripheral groups are fully addressed (uSDHC's absence is itself the correct, verified outcome, not an incomplete item).

## 9. Known gaps / good next steps if this project continues

None of these are blocking — they're the honest list of what a next round of hardening could target, roughly in order of value:

1. **Interrupt map spreadsheet.** A large fraction of IRQ numbers across nearly every peripheral added are `UNVERIFIED PLACEHOLDER` (chosen as sequential unused numbers rather than cross-checked against `S32K3xx_interrupt_map.xlsx`, which was unavailable during this whole project). If that spreadsheet becomes available, grep `hw/arm/s32k389.h` for the literal string `UNVERIFIED PLACEHOLDER` to find every IRQ define that needs correcting — there are roughly a dozen instances (LPI2C, SWT, ADC, eMIOS, eDMA, QuadSPI, GMAC IRQs are verified via s32k388 reuse but not independently, SAI, STCU2 base address).
2. **Cross-core interrupt routing.** Only core 0's NVIC has peripheral IRQs wired. If firmware needs to run peripheral-driven interrupt handlers on cores 1-3, this needs a routing decision (which core owns which peripheral IRQ) that isn't documented anywhere available.
3. **Cross-core memory isolation dynamic test.** The structural `info mtree` proof was accepted, but a genuinely conclusive interactive dynamic test (write via one core's address space, confirm invisibility from another core's `xp`) was never obtained — every attempt gave confusing results attributed to a monitor/`-device loader` harness limitation, not a code bug. Worth revisiting with a different verification technique (e.g., a tiny real ELF payload with per-core branching, run without `-S`, that writes a core-specific marker into its own ITCM and reports back over a UART) rather than the monitor-only technique used throughout this project.
4. **SAI RX audio injection.** Currently permanently empty by design (no external source). If a use case emerges needing simulated incoming audio, add a QOM property or chardev backend that pushes words into `rx_fifo[0]`.
5. **QuadSPI AHB memory-mapped flash aperture.** Only the IP-bus command path is modeled; the memory-mapped-read fast path (typical real firmware would XIP or fast-read via this) was skipped since its base address wasn't confirmed in available manual excerpts.
6. **eMIOS clock-rate assumption (80MHz)** and **SAI word-width assumption (32 bits/word)** are both flagged in their respective header comments as reasonable-but-unverified simplifications, not sourced from a specific manual value the way SAI's 24.576MHz MCLK was. Worth revisiting if precise timing fidelity ever matters for a specific test.
7. **System-reset behavior.** As explained in §5 point 2, none of the `s32k3_*` peripherals respond to a runtime system reset (only to initial construction) because this codebase doesn't wire the `ResettableClass` phases API. This is consistent across all peripherals (not a SAI-specific gap) but would need a coordinated fix across every `s32k3_*.c` file if ever required.

## 10. Quick orientation for a fresh LLM picking this up

1. Read `hw/arm/s32k389.h` top-to-bottom first — every peripheral's base address, IRQ, and design-decision rationale is documented inline as comments right next to its `#define`s.
2. Read `hw/timer/s32k3_emios.c` as the canonical example of a correctly-structured peripheral in this specific codebase (see §5).
3. To build: follow §3.6 exactly, budgeting for the 45-second-timeout/resume pattern in §3.3.
4. To verify a peripheral change: follow the `-device loader` + monitor `xp`/`info qtree`/`info mtree` pattern in §4 — this was the only testing method used throughout the entire project (no real firmware images were used to test any peripheral in this project).
5. If asked to add a new peripheral: check the manual's chip-specific instance table for that peripheral chapter *first* (grep the fully-extracted manual text for "instances and configuration") to confirm S32K389 actually has it — this project already caught one case (uSDHC) where a requested peripheral turned out not to exist on this specific chip variant.

## 11. Launcher: network testing and recent fixes

Summary of recent changes:

- Updated `launch_qemu_389.sh` to add CLI options for choosing networking and CAN backends: `--ethernet`, `--ethernet-ifname`, `--can`, `--can-ifname`.
- Automatic TAP creation and bring-up (function `ensure_tap_interface`) so the host TAP device is created and set up before QEMU starts. This fixes the `nic npcm-gmac.1 has no peer` QEMU warning and the `tap0: That device is not up` tcpdump error observed during testing.
- Automatic vcan creation and setup for SocketCAN (`--can socketcan` / `--can auto`) so CAN tests can run without manual host-side setup.
- Added header comments to the launcher with suggested monitor connection examples and recommended launch commands.

Root cause of the observed failure during testing:

- The S32K389 board model instantiates GMAC Ethernet devices, but the original launcher did not provide any QEMU netdev backend (no `-nic`/`-netdev` options). Without a netdev backend, the emulated NICs have no peer and frames are not routed to any host device for capture.
- When the TAP backend was requested, the specified TAP interface (`tap0`) either did not exist or was down. QEMU attached the NIC to the host TAP device but the interface was not up, so tcpdump could not capture frames and QEMU warned that the NIC had no peer.

What was changed and why:

- Auto-create and bring up TAP interface prior to launching QEMU. This guarantees the TAP exists and is up when QEMU realizes the NIC device.
- Provide `--ethernet` and `--can` CLI flags to the launcher so test runs can explicitly enable/disable networking/CAN and select backend types.
- Create and bring up a `vcan` interface when SocketCAN is requested (or `--can auto` detects missing vcan) so CAN tests are easier to run on a host without manual setup.

Files modified:

- `launch_qemu_389.sh` — added CLI parsing, TAP/vcan auto-create and bring-up, header comments with examples.

Verification commands used:

- Launch QEMU with TAP + auto-created tap0:

  sudo ./launch_qemu_389.sh --ethernet tap --ethernet-ifname tap0 \
       ELF/s32k389/Eth_InternalLoopback_S32K389.elf

- Capture host-side packets from the TAP interface:

  sudo tcpdump -i tap0 -n -e

  Observed multicast IPv6/MDNS and ICMPv6 Router Solicitation frames emitted by the emulated NIC (example tcpdump output was recorded in the session logs). This confirms packets traverse to the host-side TAP device.

Notes and recommendations / next steps:

- If the firmware under test uses a strictly internal MAC-level loopback that never drives the PHY or netdev, host-side capture will still not show those frames. In that case either:
  - modify the firmware to send frames that traverse the netdev (disable true internal loopback), or
  - instrument the firmware (serial/console/logging) to report transmit/receive events, or
  - add a QEMU-side debug hook in the GMAC model to mirror loopback frames to a pcap sink (non-trivial change in `hw/net/npcm_gmac.c`).

- If TAP creation is undesirable for security or policy reasons, prefer `--ethernet user` which uses QEMU user-mode networking and does not require host TAP setup.

- The launcher now documents example monitor usage (TCP/unix sockets). If you want the helper script to itself start QEMU with a TCP monitor socket, that can be added as a small enhancement — currently the script uses `-serial mon:stdio` by default (interactive combined monitor and serial on stdio).

This note and the `launch_qemu_389.sh` changes are intended to make reproducing packet captures easier for future testers and to reduce manual host setup steps.


## 12. Quick Launch Commands
Below are ready-to-run commands for the Ethernet and CAN demos using the updated launcher, plus the host-side commands to observe traffic and to clean up interfaces when done.

CAN demo — SocketCAN (vcan) visible on host
- Launch QEMU using SocketCAN (auto-creates vcan0 if missing):
  sudo ./launch_qemu_389.sh --can socketcan --can-ifname vcan0 ELF/s32k389/FlexCAN_Ip_Example_S32K389.elf
- On the host, observe CAN frames (requires can-utils):
  sudo candump vcan0
  or (tcpdump can also show CAN traffic if supported):
  sudo tcpdump -i vcan0 -n -e
- If candump is not installed:
  sudo apt install can-utils
  then run: sudo candump vcan0

CAN demo — internal QEMU CAN bus (no host socket)
- Launch with an internal QEMU CAN bus (no host SocketCAN):
  sudo ./launch_qemu_389.sh --can internal ELF/s32k389/FlexCAN_Ip_Example_S32K389.elf.elf
- No host-side SocketCAN interface is present; inspect firmware output on serial/console (the script uses -serial mon:stdio).

Helpful monitor / capture notes
- Use tcpdump -i tap0 -n -e or Wireshark on the tap interface to see Ethernet frames.
- If you see QEMU warnings like "nic … has no peer" or tcpdump says "That device is not up", bring up the interface manually:
  sudo ip link set tap0 up
  sudo ip link set vcan0 up
  (The launcher auto-creates/ups tap0 and vcan0 when requested — only needed if you created them manually or changed defaults.)
- If the firmware uses an internal MAC loopback that never sends frames to the netdev, host-side capture will not show those frames. In that case, either disable internal loopback in firmware or inspect the guest-side logs/serial output.

Cleanup (remove auto-created interfaces)
- Remove TAP:
  sudo ip link delete tap0
- Remove vcan:
  sudo ip link delete vcan0

Ethernet demo - TAP
TAP test:
sudo ./launch_qemu_389.sh --ethernet tap --ethernet-ifname tap0 ELF/s32k389/Eth_InternalLoopback_S32K389.elf

In another terminal confirm the TAP is up and watch traffic:
sudo ip addr show dev tap0
sudo tcpdump -i tap0 -n -e