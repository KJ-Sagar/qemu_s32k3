#!/usr/bin/env python3
"""Validate S32K389 board constants against the official NXP spreadsheets.

This is a focused regression check for the values that are directly exposed to
firmware and QEMU: the interrupt vectors and the primary MMIO base addresses.
It intentionally checks only the subset that is explicitly documented in the
S32K3xx memory/interrupt map workbooks so we do not silently invent values.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

from openpyxl import load_workbook

ROOT = Path(__file__).resolve().parents[1]
HEADER = ROOT / "hw/arm/s32k389.h"
MEMORY_WORKBOOK = ROOT / "NXP Manuals" / "S32K3xx_memory_map.xlsx"
INTERRUPT_WORKBOOK = ROOT / "NXP Manuals" / "S32K3xx_interrupt_map.xlsx"
# These workbooks have different layouts: S32K389 is column 23 (zero-based)
# in the memory map and column 22 in the interrupt map.
S32K389_MEMORY_COLUMN = 23
S32K389_INTERRUPT_COLUMN = 22


def read_header_macros() -> dict[str, int]:
    text = HEADER.read_text(encoding="utf-8")
    definitions = re.findall(
        r"^#define\s+((?:S32K3|S32K389)[A-Z0-9_]+)\s+([^\n]+)",
        text,
        re.MULTILINE,
    )
    macros: dict[str, int] = {}
    pending = {}
    for name, expression in definitions:
        expression = expression.split("/*", 1)[0].split("//", 1)[0].strip()
        if re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", expression):
            macros[name] = int(expression, 0)
        else:
            pending[name] = expression

    operand = r"(S32K3[A-Z0-9_]+|S32K389[A-Z0-9_]+|0x[0-9A-Fa-f]+|\d+)"
    expression_pattern = re.compile(rf"^\(?\s*{operand}\s*([+-])\s*{operand}\s*\)?$")
    reference_pattern = re.compile(rf"^{operand}$")
    while pending:
        resolved = {}
        for name, expression in pending.items():
            match = expression_pattern.fullmatch(expression)
            if match:
                left, operator, right = match.groups()
                if left not in macros and not left.startswith("0x") and not left.isdigit():
                    continue
                if right not in macros and not right.startswith("0x") and not right.isdigit():
                    continue
                lhs = macros.get(left, int(left, 0) if left.startswith("0x") or left.isdigit() else 0)
                rhs = macros.get(right, int(right, 0) if right.startswith("0x") or right.isdigit() else 0)
                resolved[name] = lhs + rhs if operator == "+" else lhs - rhs
            else:
                match = reference_pattern.fullmatch(expression)
                if match:
                    reference = match.group(1)
                    if reference in macros:
                        resolved[name] = macros[reference]
        if not resolved:
            break
        macros.update(resolved)
        for name in resolved:
            del pending[name]

    return macros


def normalize_name(name: str) -> str:
    value = str(name).strip().lower()
    value = value.replace("_", " ")
    value = re.sub(r"[^a-z0-9 ]+", " ", value)
    value = re.sub(r"\s+", " ", value).strip()
    return value


def build_irq_lookup() -> dict[tuple[str, str], int]:
    ws = load_workbook(INTERRUPT_WORKBOOK, read_only=True)["Interrupts"]
    lookup: dict[tuple[str, str], int] = {}
    for row in ws.iter_rows(values_only=True):
        if (len(row) <= S32K389_INTERRUPT_COLUMN
                or row[S32K389_INTERRUPT_COLUMN] != "YES"):
            continue
        inst = str(row[6] or "").strip()
        req = str(row[7] or "").strip()
        irq = row[2]
        if not inst or not req or irq is None:
            continue
        try:
            irq_num = int(irq)
        except (TypeError, ValueError):
            continue
        lookup[(normalize_name(inst), normalize_name(req))] = irq_num
    return lookup


def build_base_lookup() -> dict[str, int]:
    ws = load_workbook(MEMORY_WORKBOOK, read_only=True)["Peripherals"]
    lookup: dict[str, int] = {}
    for row in ws.iter_rows(values_only=True):
        if (len(row) <= S32K389_MEMORY_COLUMN
                or row[S32K389_MEMORY_COLUMN] != "YES"):
            continue
        inst = str(row[0] or "").strip()
        start = row[3]
        if not inst or start is None:
            continue
        try:
            lookup[normalize_name(inst)] = int(str(start), 16)
        except (TypeError, ValueError):
            continue
    return lookup


def validate_irq_macros(macros: dict[str, int], irq_lookup: dict[tuple[str, str], int]) -> list[str]:
    expected = {
        "S32K3_LPI2C0_IRQ": ("lpi2c 0", "lpi2c master interrupt"),
        "S32K3_LPI2C1_IRQ": ("lpi2c 1", "lpi2c master interrupt"),
        "S32K3_LPSPI0_IRQ": ("lpspi 0", "lpspi interrupt"),
        "S32K3_LPSPI1_IRQ": ("lpspi 1", "lpspi interrupt"),
        "S32K3_LPSPI2_IRQ": ("lpspi 2", "lpspi interrupt"),
        "S32K3_LPSPI3_IRQ": ("lpspi 3", "lpspi interrupt"),
        "S32K3_LPSPI4_IRQ": ("lpspi 4", "lpspi interrupt"),
        "S32K3_LPSPI5_IRQ": ("lpspi 5", "lpspi interrupt"),
        "S32K3_ADC0_IRQ": ("adc 0", "end of conversion"),
        "S32K3_ADC1_IRQ": ("adc 1", "end of conversion"),
        "S32K3_ADC2_IRQ": ("adc 2", "end of conversion"),
        "S32K3_EMIOS0_IRQ": ("emios 0", "interrupt request 23"),
        "S32K3_EMIOS1_IRQ": ("emios 1", "interrupt request 23"),
        "S32K3_EMIOS2_IRQ": ("emios 2", "interrupt request 23"),
        "S32K3_QSPI_IRQ": ("qspi", "tx buffer fill interrupt"),
        "S32K389_GMAC0_IRQ": ("gmac0", "common interrupt"),
        "S32K389_GMAC1_IRQ": ("gmac1", "common interrupt"),
        "S32K3_SAI0_IRQ": ("synchronous audio interface 0", "rx interrupt"),
        "S32K3_SAI1_IRQ": ("synchronous audio interface 1", "rx interrupt"),
        "S32K3_SWT0_IRQ": ("watchdog 0", "platform watchdog initial time out"),
        "S32K3_SWT1_IRQ": ("watchdog 1", "platform watchdog initial time out"),
        "S32K3_SWT2_IRQ": ("watchdog 2", "platform watchdog initial time out"),
        "S32K3_SWT3_IRQ": ("watchdog 3", "platform watchdog initial time out"),
        "S32K3_CONSOLE_LPUART_IRQ": ("lpuart 3", "transmit interrupt"),
        **{
            f"S32K3_FLEXCAN{i}_MB_IRQ": (
                f"flexcan{i} 1",
                "message buffer interrupt line 0",
            )
            for i in range(12)
        },
    }
    failures: list[str] = []
    for macro, key in expected.items():
        actual = macros.get(macro)
        if actual is None:
            failures.append(f"missing {macro} in {HEADER}")
            continue
        expected_irq = irq_lookup.get((key[0], key[1]))
        if expected_irq is None:
            failures.append(f"spreadsheet row missing for {macro}: {key!r}")
            continue
        if actual != expected_irq:
            failures.append(
                f"{macro}: header {actual} != spreadsheet {expected_irq} "
                f"(expected from {key!r})"
            )
    return failures


def validate_base_macros(macros: dict[str, int], base_lookup: dict[str, int]) -> list[str]:
    expected = {
        "S32K3_ADC0_BASE": "adc 0",
        "S32K3_ADC1_BASE": "adc 1",
        "S32K3_ADC2_BASE": "adc 2",
<<<<<<< HEAD
        **{
            f"S32K3_FLEXCAN{i}_BASE": f"flexcan {i}"
            for i in range(12)
        },
=======
        "S32K3_FLEXCAN0_BASE": "flexcan 0",
        "S32K3_FLEXCAN1_BASE": "flexcan 1",
        "S32K3_FLEXCAN2_BASE": "flexcan 2",
        "S32K3_FLEXCAN3_BASE": "flexcan 3",
        "S32K3_FLEXCAN4_BASE": "flexcan 4",
        "S32K3_FLEXCAN5_BASE": "flexcan 5",
        "S32K3_FLEXCAN6_BASE": "flexcan 6",
        "S32K3_FLEXCAN7_BASE": "flexcan 7",
        "S32K3_FLEXCAN8_BASE": "flexcan 8",
        "S32K3_FLEXCAN9_BASE": "flexcan 9",
        "S32K3_FLEXCAN10_BASE": "flexcan 10",
        "S32K3_FLEXCAN11_BASE": "flexcan 11",
        "S32K3_LPI2C0_BASE": "lpi2c 0",
        "S32K3_LPI2C1_BASE": "lpi2c 1",
        "S32K3_LPSPI0_BASE": "lpspi 0",
        "S32K3_LPSPI1_BASE": "lpspi 1",
        "S32K3_LPSPI2_BASE": "lpspi 2",
        "S32K3_LPSPI3_BASE": "lpspi 3",
        "S32K3_LPSPI4_BASE": "lpspi 4",
        "S32K3_LPSPI5_BASE": "lpspi 5",
        "S32K3_EDMA_MGMT_BASE": "edma",
        "S32K3_EDMA_CH_BASE": "edma tcd 0",
>>>>>>> bf1ff38d14763391fc50f0e4a9625b32fa80c2ff
        "S32K3_EMIOS0_BASE": "emios0",
        "S32K3_EMIOS1_BASE": "emios1",
        "S32K3_EMIOS2_BASE": "emios2",
        "S32K389_GMAC0_BASE": "gmac0",
        "S32K389_GMAC1_BASE": "gmac1",
        "S32K3_QSPI_BASE": "quadspi",
        "S32K3_SAI0_BASE": "sai0",
        "S32K3_SAI1_BASE": "sai1",
        "S32K3_SWT0_BASE": "swt 0",
        "S32K3_SWT1_BASE": "swt 1",
        "S32K3_SWT2_BASE": "swt 2",
        "S32K3_SWT3_BASE": "swt 3",
        "S32K3_LPUART3_BASE": "lpuart 3",
    }
    failures: list[str] = []
    for macro, key_name in expected.items():
        actual = macros.get(macro)
        if actual is None:
            failures.append(f"missing {macro} in {HEADER}")
            continue
        expected_base = base_lookup.get(normalize_name(key_name))
        if expected_base is None:
            failures.append(f"spreadsheet row missing for {macro}: {key_name!r}")
            continue
        if actual != expected_base:
            failures.append(
                f"{macro}: header {actual:#x} != spreadsheet {expected_base:#x}"
            )
    return failures


def main() -> int:
    macros = read_header_macros()
    irq_lookup = build_irq_lookup()
    base_lookup = build_base_lookup()

    failures = []
    failures.extend(validate_irq_macros(macros, irq_lookup))
    failures.extend(validate_base_macros(macros, base_lookup))

    if failures:
        print("S32K389 specification validation failed:")
        for item in failures:
            print(f" - {item}")
        return 1

    print("S32K389 specification validation passed.")
    print(f"Validated IRQ and MMIO definitions from {HEADER.name} against the NXP workbooks.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
