# Understanding MCU boot, ELF loading, and QEMU emulation

This document is a focused study guide for understanding how a
microcontroller boots, how an ELF image becomes executable firmware, and how
the same process is represented in QEMU. The examples use an ARM Cortex-M style
system, which is the right mental model for S32K3-class MCUs such as S32K344,
S32K388, and S32K389.

The most important idea is:

> A microcontroller does not run an ELF file as an operating system would.
> Firmware is linked for a fixed memory map, programmed into flash or loaded
> into RAM, and started through the CPU reset/vector-table mechanism. QEMU
> recreates the software-visible parts of that environment with C device models.

---

## 1. Embedded systems fundamentals

Before studying boot code or QEMU internals, it helps to separate the basic
pieces of an embedded system.

### 1.1 Microcontroller versus desktop CPU

A desktop/server CPU usually runs under firmware, an operating system, virtual
memory, device drivers, dynamic process loading, and complex external chipsets.

A microcontroller usually contains most of the system on one chip:

- CPU core
- flash or non-volatile memory
- SRAM
- interrupt controller
- timers
- serial interfaces
- GPIO
- watchdog
- clock/reset control
- peripheral registers exposed through memory-mapped I/O

On a bare-metal MCU there may be no operating system. Your firmware is the
program that directly configures the chip and talks to hardware.

### 1.2 Memory map basics

An MCU address map assigns meaning to address ranges. A simplified Cortex-M
style map often looks like this:

| Region | Typical purpose |
| --- | --- |
| `0x00000000` | Boot alias, vector table, ITCM, or flash alias depending on MCU |
| Internal flash | Program code and read-only data |
| SRAM/DTCM | Stack, heap, `.data`, `.bss`, runtime buffers |
| Peripheral region | MMIO registers for UART, GPIO, timers, watchdog, CAN, etc. |
| System control region | CPU/NVIC/SysTick/debug registers |

For the S32K344 model in this tree, examples of modeled addresses include:

- `INT_ITCM_BASE = 0x00000000`
- `INT_DTCM_BASE = 0x20000000`
- `INT_CODE_FLASH0_BASE = 0x00400000`
- `INT_SRAM_0_BASE = 0x20408000`
- `S32K3_PERIPH_BASE = 0x40000000`
- `S32K3_CONSOLE_LPUART_BASE = 0x40334000`

These addresses matter because both the firmware linker script and the QEMU
machine model must agree on them.

### 1.3 Instruction execution, MMIO, and interrupts

Instruction execution means the CPU fetches instructions from memory and
executes them.

Memory-mapped I/O means peripheral registers appear as memory addresses. A C
statement like:

```c
*(volatile uint32_t *)0x40334000 = value;
```

is not normal RAM access if `0x40334000` is a UART register. It is a hardware
operation. On real silicon it changes a peripheral register. In QEMU it calls a
C read/write callback in the device model.

Interrupts and exceptions are asynchronous control-flow changes. A timer, UART,
CAN controller, fault, or software event can cause the CPU to stop the current
code path and branch to a handler address stored in the vector table.

### 1.4 CPU modes and reset behavior on Cortex-M

Cortex-M processors are designed for microcontrollers. Key ideas:

- They boot through a vector table.
- They have a Main Stack Pointer.
- They use exceptions for reset, faults, SysTick, and interrupts.
- They use the NVIC for interrupt prioritization and delivery.
- They normally execute in Thumb state.
- They have special registers such as `MSP`, `PSP`, `CONTROL`, `PRIMASK`,
  `BASEPRI`, and `FAULTMASK`.

At reset, the CPU is not a fully initialized C runtime. It only has the reset
state defined by the architecture and the chip integration.

---

## 2. How a microcontroller actually boots

Boot is the process that turns a powered chip into a running application.

### 2.1 Power-on reset

The high-level flow is:

1. Power reaches a valid level.
2. Reset logic holds the system in reset until power and clocks are safe enough.
3. The CPU leaves reset.
4. The CPU obtains its initial stack pointer and reset handler address.
5. Boot ROM, startup code, or application reset code begins executing.

Real chips also include details such as brown-out detection, reset cause
registers, watchdog reset, debug reset, low-power wakeup, and boot-mode pins or
fuses.

### 2.2 Reset vector and vector table

On Cortex-M, the vector table is central. At the vector table base:

| Offset | Meaning |
| --- | --- |
| `0x00` | Initial Main Stack Pointer value |
| `0x04` | Reset handler address |
| `0x08` | NMI handler |
| `0x0c` | HardFault handler |
| later entries | Other exceptions and IRQ handlers |

The CPU effectively does this on reset:

```text
MSP = *(uint32_t *)(vector_table_base + 0x00)
PC  = *(uint32_t *)(vector_table_base + 0x04)
```

The reset handler address must have bit 0 set in the vector table, because
Cortex-M code runs in Thumb state. For example, if the handler is at
`0x00401000`, the vector entry is commonly `0x00401001`.

### 2.3 Boot ROM or bootloader

Many MCUs have vendor boot ROM. It may:

- inspect boot pins, fuses, option bytes, or lifecycle state
- validate an image
- check signatures or secure-boot metadata
- select internal flash, external memory, serial boot, or debug boot
- initialize minimal clocks or flash access
- jump to the user application vector table

Some systems skip a visible boot ROM path for normal application startup, while
others always execute ROM first. The exact sequence is vendor specific.

### 2.4 Startup code

The reset handler usually enters startup code before `main()`. Startup code is
part of the firmware and is often supplied by the SDK or runtime.

Common startup responsibilities:

- set or confirm the stack pointer
- optionally set the vector table base register (`VTOR`)
- copy `.data` initial values from flash to SRAM
- zero `.bss`
- initialize clocks and PLLs
- configure flash wait states
- disable or service watchdogs
- initialize TCM/cache/MPU/FPU when present
- call C/C++ runtime initialization
- call `main()`

A simplified startup sequence looks like:

```text
Reset_Handler:
    set stack pointer
    configure vector table
    copy .data from flash load address to RAM run address
    zero .bss
    configure early clocks and watchdog
    call SystemInit()
    call __libc_init_array()
    call main()
```

### 2.5 Clock initialization

Real MCU clocks are physical. Firmware may need to configure:

- internal oscillator
- external crystal oscillator
- PLL
- clock dividers
- peripheral clock gates
- flash wait states for higher frequencies

If clocks are wrong, UART baud rates are wrong, timers count at the wrong rate,
flash reads may fail, or peripherals may never leave reset.

In QEMU, clocks are usually functional objects or constants. The model may use
a clock frequency for timers and UART baud calculations, but it does not model
analog oscillator startup in the same way as silicon.

### 2.6 Flash, SRAM, and access setup

Firmware is commonly stored in flash and executes from flash or from TCM/RAM.
Initialized variables live in SRAM at runtime, but their initial values are
stored in flash.

That creates two addresses for `.data`:

- load memory address: where initial bytes are stored in flash
- virtual/run memory address: where the variable lives in SRAM

Startup code copies from the load address to the run address.

The `.bss` section is different: it occupies RAM at runtime but does not need
stored bytes in flash. Startup code simply fills it with zero.

### 2.7 Boot modes and alternate entry points

Real MCUs often support multiple boot modes:

- normal internal flash boot
- bootloader/ROM serial boot
- debug boot
- external memory boot
- recovery or factory programming mode
- secure and non-secure boot paths

These modes may choose different vector tables or require image headers before
the application vector table.

---

## 3. ELF loading and execution

### 3.1 What an ELF file contains

An ELF file is a structured executable format. It can contain:

- ELF header
- program headers
- section headers
- machine architecture information
- entry point
- `.text`
- `.rodata`
- `.data`
- `.bss`
- symbol tables
- debug information
- relocation records

For embedded work, two views are important:

- Sections describe logical pieces used by linkers and debuggers.
- Program headers describe loadable memory segments.

When loading executable content, loaders usually care more about program
headers than section headers.

### 3.2 Compiler, assembler, linker, and objcopy

The build pipeline is usually:

```text
C/C++ source -> compiler -> object files
assembly     -> assembler -> object files
object files + linker script -> linker -> ELF
ELF -> objcopy -> .bin/.hex/.srec, if needed
```

The ELF is often the richest output because it keeps symbols and debug
information. Flashing tools may use the ELF directly, or they may use a raw
binary, Intel HEX, Motorola S-record, or a vendor-specific container.

### 3.3 Linker script and memory layout

The linker script tells the linker where code and data belong. A simplified
example:

```ld
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00400000, LENGTH = 1M
    SRAM  (rwx) : ORIGIN = 0x20408000, LENGTH = 320K
}

SECTIONS
{
    .vectors : {
        KEEP(*(.isr_vector))
    } > FLASH

    .text : {
        *(.text*)
        *(.rodata*)
    } > FLASH

    .data : {
        *(.data*)
    } > SRAM AT > FLASH

    .bss : {
        *(.bss*)
        *(COMMON)
    } > SRAM
}
```

This script says:

- vector table and code execute from flash
- initialized data executes from SRAM
- `.data` initial bytes are stored in flash
- `.bss` is allocated in SRAM and zeroed during startup

### 3.4 Entry point versus reset vector

The ELF header has an entry point, but Cortex-M firmware usually depends on the
vector table. These are related but not identical concepts.

The ELF entry point is metadata used by loaders and debuggers. The Cortex-M
reset vector is data at the vector table address. Hardware reset uses the vector
table, not a desktop-style process loader.

For correct MCU boot, the important question is:

> Is the vector table located where the CPU or boot ROM expects it, and does it
> contain a valid stack pointer and reset handler?

### 3.5 Relocations

Relocations are linker or loader fixups. They are needed when final addresses
are not known at compile time.

In many bare-metal MCU images, the final firmware is statically linked. That
means most relocations are resolved by the linker before flashing. The running
MCU does not perform dynamic relocation like a desktop OS dynamic loader.

Relocation-like work still happens at startup when `.data` is copied from flash
to RAM, but that is not the same as dynamic linking.

### 3.6 Loading into flash versus running from RAM

Common execution styles:

| Style | Description |
| --- | --- |
| Execute from flash | Code stays in flash; `.data` is copied to RAM |
| Execute from RAM | Code is loaded/copied to RAM and PC jumps there |
| Execute from TCM | Performance-critical code runs from tightly coupled memory |
| Boot ROM launches app | ROM validates/selects image, then jumps to app vector |
| Debugger loads RAM image | Debug probe writes image to RAM and sets PC/SP |

The linker script must match the selected style.

---

## 4. Real hardware boot flow

A realistic MCU boot sequence has several layers.

### 4.1 Hardware layer

The chip and board must provide:

- valid power rails
- reset release
- clock source
- accessible flash or boot ROM
- accessible SRAM
- valid boot configuration
- no fatal safety/reset condition

### 4.2 Vendor ROM or bootloader layer

The ROM may:

- decide the boot source
- check security state
- authenticate the application
- configure enough flash access to read the image
- jump to the application vector table

### 4.3 Application startup layer

The firmware startup code:

- establishes the C runtime
- configures system clocks
- initializes memory sections
- installs interrupt vectors
- starts drivers
- calls application logic

### 4.4 Application layer

The application uses drivers to access peripherals:

- UART for logs
- timers for periodic scheduling
- GPIO for pins
- CAN/Ethernet/SPI/I2C for communication
- ADC/DAC/PWM for physical interaction
- watchdog for recovery

The startup path must succeed before this layer can work reliably.

---

## 5. QEMU's view of the same system

QEMU is a functional emulator. It builds a software model of the board, not a
physical duplicate of the board.

### 5.1 QEMU machine model

A QEMU machine model is C code that describes a board. It usually:

- creates the CPU object
- creates RAM and ROM memory regions
- maps flash/SRAM/MMIO regions into the guest address space
- creates peripheral device models
- maps device MMIO registers
- connects interrupt lines
- loads the guest image
- registers reset behavior

For the S32K344 machine in this tree, the initialization flow in
`hw/arm/s32k344.c` does exactly this: it creates the Cortex-M object, maps
memory, initializes UART/FlexIO/FlexCAN-related devices, creates an
unimplemented peripheral catch-all region, enables semihosting, and calls
`armv7m_load_kernel()`.

### 5.2 QEMU memory regions

QEMU represents guest memory with `MemoryRegion` objects. A region can be:

- RAM
- ROM/flash-like memory
- MMIO backed by callbacks
- an alias of another region
- an unimplemented placeholder device

When guest code reads or writes an MMIO address, QEMU dispatches that access to
the device model's read/write functions.

### 5.3 QEMU device model

A peripheral model is normally a QOM/sysbus device. A simplified device flow:

```text
create device object
set properties
realize device
map MMIO region at guest physical address
connect device IRQ output to CPU/NVIC input
```

In code, this often appears as:

```c
dev = qdev_new(TYPE_SOME_DEVICE);
sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_fatal);
sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, DEVICE_BASE_ADDRESS);
sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0, qdev_get_gpio_in(cpu_device, irq));
```

### 5.4 Interrupt routing in QEMU

For Cortex-M systems, external interrupts are delivered through the NVIC
integrated with the ARMv7-M/ARMv8-M CPU model.

The device model asserts a `qemu_irq`. QEMU routes that line to the CPU/NVIC
input. The guest sees an interrupt pending in the normal architectural way, and
the CPU model uses the vector table to enter the handler.

### 5.5 QEMU image loading

For M-profile boards, QEMU commonly calls:

```c
armv7m_load_kernel(cpu, filename, mem_base, mem_size);
```

In this tree, `hw/arm/armv7m.c` implements that helper. It attempts to load an
ELF with `load_elf_as()`. If ELF loading fails, it falls back to loading a raw
image into the target physical address with `load_image_targphys_as()`.

For the S32K344 model, the call is:

```c
armv7m_load_kernel(s->armv7m.cpu,
                   machine->kernel_filename,
                   INT_CODE_FLASH0_BASE,
                   INT_CODE_FLASH0_SIZE);
```

That means a raw binary fallback is placed at `0x00400000`, while an ELF is
loaded according to its ELF load addresses.

### 5.6 QEMU reset handling

QEMU must model CPU reset and board reset. The `armv7m_load_kernel()` helper
also registers a reset callback for the CPU. On reset, the Cortex-M CPU model
uses the vector table semantics expected by M-profile software.

The exact details depend on the CPU model and board configuration, but the
important point is that QEMU starts the guest from a modeled architectural reset
state, not from physical power ramp behavior.

---

## 6. Real hardware versus QEMU

### 6.1 What is similar

Both real hardware and QEMU can provide:

- CPU instruction execution
- addressable flash/SRAM regions
- MMIO register accesses
- exception and interrupt behavior
- UART/timer/GPIO-style device interactions
- reset into firmware startup code

This is why the same bare-metal firmware can often run in both places.

### 6.2 What is different

Real hardware includes:

- analog clocks and oscillator startup
- electrical reset timing
- flash wait states and error conditions
- peripheral timing quirks
- external board components
- bus arbitration and contention
- safety/security lifecycle state
- silicon errata

QEMU usually provides:

- functional CPU execution
- modeled memory map
- modeled MMIO side effects
- approximate timers
- simplified reset state
- selected peripherals, often partial
- placeholders for unimplemented regions

QEMU is usually not cycle-accurate. It is best understood as
software-visible functional emulation.

### 6.3 Why firmware can pass in QEMU and fail on hardware

Common reasons:

- clock setup is incomplete but QEMU does not require the real sequence
- watchdog behavior is missing or simplified
- flash timing constraints are not modeled
- peripheral registers have incomplete behavior in QEMU
- firmware depends on external board hardware
- interrupt timing differs
- boot ROM or secure-boot checks are skipped
- reset cause or boot-mode registers return simplified values

### 6.4 Why firmware can fail in QEMU and pass on hardware

The reverse also happens:

- the QEMU machine model is missing a peripheral
- an MMIO register is unimplemented
- an interrupt line is not connected
- a memory region has the wrong base or size
- the ELF is linked for a different address than the model expects
- the model's reset value for a register differs from silicon

When debugging QEMU bring-up, always compare:

- linker script addresses
- vector table address
- first stack pointer value
- reset handler address
- flash and SRAM mappings
- MMIO base addresses
- IRQ numbers
- clock assumptions

---

## 7. Peripherals needed in the real world

### 7.1 Minimum bring-up hardware

At the board/chip level, a real product needs:

- power supply
- decoupling capacitors
- reset circuit
- clock source
- flash or boot memory
- SRAM
- debug interface such as SWD/JTAG
- boot configuration pins/fuses
- basic clock/reset control

Without these, the CPU may never reach application code.

### 7.2 Minimum firmware-visible blocks

Early firmware usually depends on:

- CPU core
- vector table
- NVIC
- system control block
- flash controller
- SRAM controller
- clock/reset controller
- watchdog
- fault handlers

Even a "hello world" firmware may touch watchdog, clocks, pin mux, and UART
before printing anything.

### 7.3 Common MCU peripherals

Typical application peripherals:

- GPIO
- UART/LPUART/USART
- timers/counters
- SysTick
- watchdog
- DMA
- RTC
- PWM
- ADC/DAC
- SPI/LPSPI
- I2C/LPI2C
- CAN/FlexCAN
- Ethernet
- USB
- external memory controllers

### 7.4 Board-level peripherals

The MCU may also interact with:

- LEDs
- buttons
- external flash
- external RAM
- sensors
- CAN/LIN/Ethernet transceivers
- power-management ICs
- motor drivers
- displays
- connectors

These are outside the MCU but still matter to real firmware.

---

## 8. Peripherals implemented in QEMU and how

### 8.1 Commonly implemented peripherals

QEMU often models:

- UART serial console
- timers
- GPIO controllers
- interrupt controllers
- flash/ROM/RAM regions
- watchdogs
- selected SPI/I2C/CAN/Ethernet/storage devices
- placeholder devices for unimplemented MMIO ranges

Support varies by board. A peripheral being common in QEMU does not mean it is
implemented for every machine.

### 8.2 How QEMU implements MMIO devices

An MMIO peripheral model typically defines read and write callbacks:

```text
guest load/store at peripheral address
    -> QEMU memory subsystem
    -> device read/write callback
    -> update device state
    -> maybe raise/lower interrupt
    -> return value to guest
```

For example:

- UART transmit register write sends a byte to a host chardev.
- Timer compare register write updates a QEMU timer.
- GPIO output register write changes internal pin state.
- CAN register write updates controller state or sends a frame to a CAN backend.

### 8.3 Unimplemented devices

QEMU can map an unimplemented region so firmware reads/writes do not crash QEMU
itself. This is useful during bring-up because firmware often probes many
registers before the device model is complete.

However, an unimplemented placeholder does not provide real behavior. It only
prevents immediate "no device at this address" failures.

### 8.4 Practical implementation checklist for an MCU peripheral

To add or improve a QEMU MCU peripheral, check:

1. Correct base address
2. Correct register size and alignment
3. Reset values
4. Read/write side effects
5. Interrupt status bits
6. IRQ output line and NVIC number
7. Clock/reset gating behavior if firmware depends on it
8. DMA interactions if applicable
9. Backend connection if it talks to the host, such as serial, CAN, net, or block
10. Tests or traces that prove guest-visible behavior

---

## 9. Boot and ELF debugging checklist

Use this checklist when firmware does not boot.

### 9.1 Verify the image

Useful commands:

```sh
arm-none-eabi-readelf -h firmware.elf
arm-none-eabi-readelf -l firmware.elf
arm-none-eabi-objdump -h firmware.elf
arm-none-eabi-nm -n firmware.elf | head
```

Check:

- ELF machine is ARM
- entry point is plausible
- load segments target expected flash/RAM addresses
- vector table section is present
- `.text` is in flash
- `.data` has flash load address and RAM run address
- `.bss` is in RAM

### 9.2 Verify the vector table

At the vector table base:

- word 0 should be a valid stack pointer in RAM
- word 1 should be a valid reset handler address in executable memory
- reset handler address should have Thumb bit set
- exception entries should point to real handlers or safe default handlers

For S32K-style flash boot, check whether the vector table is expected at
`0x00400000`, `0x00400800`, `0x00402000`, or another vendor-specific offset.
The linker script, boot header, and QEMU machine model must agree.

### 9.3 Verify QEMU machine mapping

In the machine model, check:

- flash base and size
- SRAM base and size
- ITCM/DTCM base and size
- peripheral base addresses
- UART console base and IRQ
- timer IRQs
- `armv7m_load_kernel()` arguments
- whether missing registers are handled or intentionally unimplemented

For this tree, start with:

- `hw/arm/s32k344.h`
- `hw/arm/s32k344.c`
- `hw/arm/armv7m.c`

### 9.4 Trace early boot

Useful QEMU techniques:

- use `-S -s` to wait for a debugger
- attach `gdb-multiarch` or `arm-none-eabi-gdb`
- inspect SP and PC immediately after reset
- disassemble the reset handler
- enable QEMU logs for interrupts or guest errors
- add temporary logging to device read/write callbacks

Good first questions:

- Did QEMU load the image?
- Did the CPU fetch the initial stack pointer?
- Did PC enter `Reset_Handler`?
- Did startup code reach `.data` copy?
- Did it fault on an MMIO access?
- Did it wait forever for a clock/status bit?

---

## 10. Guide to implementing the rest of the S32K389 peripherals in QEMU

This section is a practical guide for adding the remaining S32K389 peripherals
to the QEMU board model. The goal is not to perfectly reproduce silicon on the
first attempt. The goal is to implement enough software-visible behavior that
real firmware can boot, initialize drivers, exchange data, and exercise
interrupt paths.

### 10.1 Prerequisites

Before implementing more peripherals, be comfortable with these topics:

- C programming in QEMU style
- QOM object model basics
- `SysBusDevice`
- `MemoryRegion` and `MemoryRegionOps`
- MMIO register read/write callbacks
- Cortex-M NVIC interrupt numbering
- QEMU reset functions
- QEMU timers when modeling timer peripherals
- QEMU character backends for UART-like devices
- QEMU CAN/net/block backends when modeling communication devices
- S32K389 reference manual register descriptions
- `S32K3xx_memory_map.xlsx`
- `S32K3xx_interrupt_map.xlsx`
- existing S32K files in this tree

Useful files in this tree:

- `hw/arm/s32k389.c`
- `hw/arm/s32k389.h`
- `hw/char/s32k3_uart.*`
- `hw/char/s32k3_flexio_uart.*`
- `hw/net/s32k3_flexcan.*`
- `hw/arm/armv7m.c`
- `hw/misc/unimp.c`

The spreadsheet gives addresses and presence/absence by chip. The reference
manual gives register meaning. The interrupt map gives NVIC IRQ numbers.

### 10.2 First classify each peripheral

Do not implement every peripheral at full detail immediately. Classify each
peripheral by how the firmware uses it.

| Class | Meaning | Example implementation |
| --- | --- | --- |
| Must behave | Firmware depends on real behavior | UART TX/RX, timer interrupt, CAN frame path |
| Must initialize | Firmware only configures it and checks status bits | clock gate, reset controller, pin mux |
| Must not crash | Firmware probes/writes it but does not depend on behavior | many analog or safety blocks during early boot |
| Can ignore for now | Firmware never touches it in your current test | leave unmapped or covered by unimplemented region |

This classification keeps the model manageable. Many peripherals can start as
small register banks with correct reset values and a few status bits.

### 10.3 Recommended bring-up order for S32K389

A practical implementation order is:

1. Memory map correctness
2. Boot/status registers needed by startup code
3. Clock/reset/status registers that firmware waits on
4. Pin mux/SIUL2 enough for driver initialization
5. UART/LPUART console
6. PIT/STM/SysTick-style timers
7. Watchdog behavior or watchdog-disable behavior
8. GPIO read/write behavior
9. FlexCAN instances and interrupt paths
10. SPI/I2C only when firmware uses external devices
11. DMA only when a peripheral driver requires it
12. ADC/PWM/analog blocks as stubs unless application logic depends on them
13. Safety/security/HSE blocks only to the level required by boot code

For early firmware boot, clock/reset/status registers are often more important
than the "interesting" peripherals because startup code may spin forever waiting
for a ready bit.

### 10.4 Standard QEMU peripheral implementation procedure

Use this procedure for each new peripheral.

1. Identify the peripheral in the XLSX memory map.
2. Confirm the S32K389 column says it exists.
3. Record base address, end address, and region size.
4. Find IRQ numbers in the interrupt map.
5. Read the reference manual chapter for registers, reset values, and status
   bits.
6. Search the firmware for registers it actually touches.
7. Decide the minimum behavior needed for the firmware.
8. Create or reuse a QEMU device model.
9. Add a state struct containing registers and runtime state.
10. Add `MemoryRegionOps` read/write callbacks.
11. Add reset behavior.
12. Add IRQ output lines if the device can interrupt.
13. Add properties for instance number, backend, clock, or board wiring.
14. Instantiate and map the device in `s32k389.c`.
15. Connect its IRQs to `qdev_get_gpio_in(DEVICE(&s->armv7m), irq_number)`.
16. Build QEMU.
17. Run firmware and inspect the first missing behavior.
18. Iterate based on actual guest accesses.

The fastest path is usually "minimal truthful behavior, then expand".

### 10.5 Basic device model skeleton

A simple MMIO peripheral usually has a header and a C file. The state structure
contains the QEMU parent object, the MMIO region, IRQ lines, and registers.

```c
typedef struct S32K3ExampleState {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;

    uint32_t regs[REG_COUNT];
} S32K3ExampleState;
```

The read path decodes an offset and returns the register value:

```c
static uint64_t s32k3_example_read(void *opaque, hwaddr offset, unsigned size)
{
    S32K3ExampleState *s = opaque;

    if (size != 4 || offset >= DEVICE_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3-example: invalid read size %u @0x%"
                      HWADDR_PRIx "\n", size, offset);
        return 0;
    }

    return s->regs[offset >> 2];
}
```

The write path stores values and performs side effects:

```c
static void s32k3_example_write(void *opaque, hwaddr offset,
                                uint64_t value, unsigned size)
{
    S32K3ExampleState *s = opaque;

    if (size != 4 || offset >= DEVICE_SIZE) {
        qemu_log_mask(LOG_GUEST_ERROR,
                      "s32k3-example: invalid write size %u @0x%"
                      HWADDR_PRIx ", value 0x%" PRIx64 "\n",
                      size, offset, value);
        return;
    }

    s->regs[offset >> 2] = value;
}
```

The `MemoryRegionOps` connects guest MMIO accesses to those callbacks:

```c
static const MemoryRegionOps s32k3_example_ops = {
    .read = s32k3_example_read,
    .write = s32k3_example_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl.min_access_size = 4,
    .impl.max_access_size = 4,
    .valid.min_access_size = 4,
    .valid.max_access_size = 4,
};
```

In the device `realize` function:

```c
memory_region_init_io(&s->iomem, OBJECT(dev), &s32k3_example_ops, s,
                      "s32k3-example", DEVICE_SIZE);
sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);
sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->irq);
```

Then the board maps and wires it:

```c
dev = qdev_new(TYPE_S32K3_EXAMPLE);
sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_fatal);
sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, S32K3_EXAMPLE_BASE);
sysbus_connect_irq(SYS_BUS_DEVICE(dev), 0,
                   qdev_get_gpio_in(DEVICE(&s->armv7m), S32K3_EXAMPLE_IRQ));
```

### 10.6 Register modeling rules

For each register, decide its behavior:

- read/write
- read-only
- write-only
- write-one-to-clear
- write-one-to-set
- self-clearing command bit
- reserved bits read as zero
- reserved bits preserve previous value
- status bit controlled by internal device state
- status bit always ready for simplified boot

Do not blindly store every write. Real firmware often depends on details such
as write-one-to-clear interrupt flags. If those are wrong, the guest may get
stuck in an interrupt loop or wait forever.

For unknown registers, a reasonable early strategy is:

- return documented reset values for reads
- log unimplemented writes with `LOG_UNIMP`
- preserve harmless configuration writes
- implement status bits that firmware waits on
- implement interrupt flags only when needed

### 10.7 Reset behavior

Every device should reset to documented hardware reset values. In QEMU this is
usually done with a reset function:

```c
static void s32k3_example_reset(DeviceState *dev)
{
    S32K3ExampleState *s = S32K3_EXAMPLE(dev);

    memset(s->regs, 0, sizeof(s->regs));
    s->regs[SOME_STATUS_REG] = SOME_READY_BIT;
    qemu_set_irq(s->irq, 0);
}
```

Reset values matter because MCU startup code often checks reset status before
doing anything visible.

### 10.8 Interrupt implementation

A useful interrupt model has:

- interrupt enable bits
- interrupt status flags
- a function that recomputes the IRQ line
- write-one-to-clear behavior for flags

Typical pattern:

```c
static void s32k3_example_update_irq(S32K3ExampleState *s)
{
    bool pending = (s->status & s->irq_enable) != 0;

    qemu_set_irq(s->irq, pending);
}
```

Call this after:

- setting a status flag
- clearing a status flag
- changing interrupt enable bits
- reset

For Cortex-M, connect device IRQs to the `ARMv7MState` GPIO inputs with the
NVIC interrupt number from the S32K389 interrupt map.

### 10.9 Timers

Timer peripherals need QEMU timers. The model usually stores:

- load/compare value
- current counter
- enable bit
- interrupt enable bit
- QEMU timer object
- input clock frequency

When firmware enables the timer, schedule a QEMU timer for the next expiry.
When it expires, set the interrupt flag and assert the IRQ if enabled.

For a first implementation, exact cycle behavior is less important than:

- firmware can program the timer
- time advances
- interrupt fires
- status flag clears correctly
- periodic mode reschedules

### 10.10 UART and serial devices

UART-style devices usually connect to a QEMU chardev. Minimum useful behavior:

- transmit data register write sends bytes to host serial output
- receive data register reads bytes from host serial input
- status register reports TX ready
- status register reports RX ready when data is available
- interrupts work if firmware uses interrupt-driven UART

For logs, polling TX-ready plus transmit writes may be enough.

### 10.11 GPIO and pin mux

GPIO and pin mux are easy to underestimate. Firmware may initialize many pins
before using UART, CAN, SPI, or LEDs.

Minimum SIUL2/pin-mux behavior often means:

- accept writes to mux/control registers
- return stored values on reads
- expose GPIO output register state
- expose GPIO input register state
- optionally connect pins to another QEMU device

If the firmware only configures pins but QEMU devices do not depend on pin mux,
the model can start as a register bank.

### 10.12 Clock, reset, and mode-entry blocks

Clock and reset blocks are usually needed early. Firmware often does:

1. write a control register
2. wait for a status bit
3. enable peripheral clock gates
4. wait for mode transition complete

For QEMU, the minimum model is often:

- accept control writes
- immediately set "ready", "valid", or "transition complete" bits
- report enabled peripheral clocks when firmware asks
- keep reset bits in a state that lets drivers proceed

This is exactly why small models for `MC_ME`, clock status, and boot status are
valuable before implementing complex peripherals.

### 10.13 DMA

DMA is only needed when firmware drivers actually use DMA channels. A minimal
DMA model is harder than a simple register bank because it must read and write
guest memory.

Implement DMA later unless the firmware blocks without it. When needed, study
QEMU's DMA helpers and implement:

- channel configuration registers
- source/destination addresses
- transfer size
- start/complete bits
- memory access through the guest address space
- completion interrupt

For early driver bring-up, it may be enough to report "DMA disabled" or make
the firmware choose polling mode.

### 10.14 Analog, safety, and security peripherals

ADC, analog comparators, HSE/security, FCCU, safety monitors, and similar
blocks can be complex. For most firmware bring-up, start with one of these
approaches:

- register bank only
- always-ready status
- fixed input values
- unimplemented device region with logging
- narrow behavior required by boot code

Only model detailed analog or security behavior when the application needs it.
QEMU is strongest at digital software-visible behavior, not physical analog
simulation.

### 10.15 Adding a peripheral to the build

When creating a new device file:

1. Put the C file in the appropriate QEMU directory, such as `hw/misc`,
   `hw/timer`, `hw/gpio`, `hw/ssi`, `hw/i2c`, `hw/net`, or `hw/char`.
2. Put the header in `include/hw/...` or `hw/...` following local style.
3. Add the source file to the relevant `meson.build`.
4. Add a Kconfig symbol if the device should be selected by machines.
5. Select the device from the S32K389 machine Kconfig if needed.
6. Include the header in `s32k389.c`.
7. Add the device state pointer or embedded object to `S32K389State`.
8. Instantiate, realize, map, and connect it in `s32k389_init()`.

If an S32K3 family model already exists, prefer reusing it with instance
properties over creating a separate S32K389-only copy.

### 10.16 Validating a new peripheral

Use a small validation loop:

1. Build QEMU.
2. Boot the firmware with guest-error and unimplemented logging enabled.
3. Check whether the firmware reaches the next milestone.
4. Add logs to the new device's read/write callbacks.
5. Compare guest register accesses with the reference manual.
6. Fix reset values, status bits, and interrupt behavior.
7. Remove or reduce noisy logs once the device works.

Useful commands and options:

```sh
ninja -C build qemu-system-arm
./build/qemu-system-arm -machine s32k389 -kernel firmware.elf -nographic
./build/qemu-system-arm -machine s32k389 -kernel firmware.elf -nographic -d guest_errors,unimp
./build/qemu-system-arm -machine s32k389 -kernel firmware.elf -S -s
```

With `-S -s`, connect GDB and check:

- current PC
- current SP
- fault status registers
- last MMIO address touched
- interrupt pending/active state
- whether firmware is spinning on a status bit

### 10.17 Common bugs when adding MCU peripherals

Common implementation mistakes:

- wrong base address
- wrong MMIO region size
- wrong IRQ number
- missing IRQ clear behavior
- status bit never becomes ready
- register reset value is wrong
- access size rejects firmware's byte/halfword access
- endian setting is wrong
- device is created but not mapped
- device is mapped but IRQ is not connected
- unimplemented catch-all region hides a more specific device
- overlapping memory regions use the wrong priority
- firmware uses an alias address that is not mapped
- linker script places stack/data outside modeled RAM

When a firmware hangs, it is often waiting for one bit. Find that bit first.

### 10.18 How to decide between full model, stub, and unimplemented region

Use this decision rule:

- Full model: required for application behavior or data exchange.
- Functional stub: required for initialization but not real data movement.
- Register bank: firmware writes and reads configuration only.
- Unimplemented region: firmware may touch it but current behavior does not
  depend on it.
- Leave absent: firmware never touches it.

Examples:

- LPUART console: full enough for TX/RX/status.
- MC_ME mode status: functional stub with ready bits.
- SIUL2 pin mux: register bank first.
- ADC: fixed values or stub unless application reads real channels.
- Watchdog: allow disable/service path first.
- PIT/STM: functional timer if firmware uses delays or scheduler ticks.
- FlexCAN: full enough for mailboxes, flags, and CAN backend if testing CAN.

### 10.19 Suggested S32K389 peripheral tracking table

Maintain a table while you work:

| Peripheral | Base | Size | IRQs | Model status | Firmware depends on | Notes |
| --- | --- | --- | --- | --- | --- | --- |
| MC_ME | `0x402D0000` | `0x20000` | none/varies | partial | boot | ready/status bits |
| LPUART3 | `0x40334000` | from XLSX/RM | `144` | partial/full | console | connected to serial |
| FlexIO | `0x40324000` | from XLSX/RM | `139` | partial | loopback | board-specific use |
| FlexCAN0 | `0x40304000` | from XLSX/RM | `110` | partial/full | CAN tests | mailbox IRQ |
| PIT0 | from XLSX | from XLSX | from interrupt map | todo | timers | implement before RTOS tick |
| SIUL2 | from XLSX | from XLSX | from interrupt map | todo | pin mux/GPIO | register bank first |
| SWT | from XLSX | from XLSX | from interrupt map | todo | watchdog | support disable/service |

Keep this table close to the code or in a board bring-up note. It prevents
guesswork when the firmware starts touching many blocks.

### 10.20 A good first milestone

A strong S32K389 peripheral milestone is:

1. Firmware reaches `main()`.
2. UART prints logs.
3. Clock/status initialization does not hang.
4. Watchdog initialization does not reset or trap.
5. Timer interrupt fires.
6. One GPIO output can be observed in QEMU logs/state.
7. One FlexCAN instance can send/receive through the QEMU CAN backend.

After that, implement peripherals according to the firmware you actually need
to run. That keeps the model grounded in real software behavior.

---

## 11. Focused study sequence

Study in this order:

1. Cortex-M reset behavior and vector table layout
2. Startup assembly and C runtime initialization
3. Linker scripts, ELF sections, and loadable segments
4. Flash versus RAM execution
5. MMIO and volatile register access
6. NVIC interrupt delivery
7. Real MCU clock/reset/watchdog behavior
8. QEMU machine initialization
9. QEMU `MemoryRegion`, sysbus devices, and IRQ lines
10. QEMU ELF/raw image loading
11. Real hardware versus emulation limitations
12. Peripheral-by-peripheral model validation

---

## 12. Short answers to the main questions

### How does a microcontroller boot?

It leaves reset, reads the initial stack pointer and reset handler from the
vector table or follows a vendor boot ROM path, runs startup code, initializes
memory and clocks, and eventually calls the application.

### How is the ELF loaded?

The ELF is produced by the linker using a linker script. On real hardware it is
usually programmed into flash or converted to a flashable format. In QEMU, an
ELF can be loaded directly into guest memory according to its load addresses; if
loading a raw binary, QEMU places it at the machine-provided base address.

### How does QEMU compare to real hardware?

Real hardware boots through physical reset, clocks, flash, ROM, buses, and
peripherals. QEMU builds a functional software model of the CPU, memory map, and
selected peripherals so firmware sees similar addresses and registers, but it
usually does not model exact timing, analog behavior, or every silicon detail.

### What peripherals are needed in the real world?

At minimum: power, reset, clocks, flash, SRAM, debug access, CPU/NVIC/system
control, watchdog handling, and enough board support to reach application code.
Practical firmware commonly also needs UART, timers, GPIO, DMA, SPI/I2C, CAN,
Ethernet, ADC, PWM, and board-level devices.

### What peripherals are implemented in QEMU?

QEMU implements peripherals as C device models connected to the machine memory
map and interrupt lines. Common examples are UARTs, timers, GPIO, interrupt
controllers, flash/RAM regions, and selected communication devices. Missing
vendor-specific peripherals may be partially modeled or represented as
unimplemented MMIO placeholders.

---

## 13. Best single-sentence summary

To understand MCU boot under QEMU, learn how Cortex-M reset uses the vector
table, how the linker places ELF contents into the MCU memory map, and how QEMU
recreates enough CPU, memory, MMIO, and interrupt behavior for that firmware to
run.
