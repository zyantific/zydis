#!/usr/bin/env python3
"""Generates the ZydisFuzzFormatter seed corpus from the upstream test cases.

Each seed mirrors the `ZydisFuzzControlBlock` layout of `tools/ZydisFuzzFormatter.c`
(natural C alignment, enums are 4 bytes, `ZyanBool` is 1 byte) followed by the raw
instruction bytes of one decoded-decoder test case. The control-block fields are
rotated over the sweep space, so the corpus covers style/property/hook/buffer-size
combinations for a diverse, structurally valid instruction set (including KNC/MVEX
cases, which enable the KNC decoder mode).
"""

import ctypes
import re
import sys
import zipfile
from pathlib import Path

MACHINE_MODES = {  # from tools/ZydisInfo.c usage table
    "-64": (0, 0),  # ZYDIS_MACHINE_MODE_LONG_64,     ZYDIS_STACK_WIDTH_64
    "-32": (3, 1),  # ZYDIS_MACHINE_MODE_LEGACY_32,   ZYDIS_STACK_WIDTH_32
    "-16": (2, 2),  # ZYDIS_MACHINE_MODE_LONG_COMPAT_16, ZYDIS_STACK_WIDTH_16
    "-real": (5, 2),  # ZYDIS_MACHINE_MODE_REAL_16,   ZYDIS_STACK_WIDTH_16
}


def decoder_modes(zydis_include: Path) -> list:
    text = (zydis_include / "Zydis" / "Decoder.h").read_text(encoding="utf-8")
    block = re.search(
        r"typedef enum ZydisDecoderMode_\s*\{(.*?)\}\s*ZydisDecoderMode;", text, re.S
    ).group(1)
    entries = [m for m in re.findall(r"ZYDIS_DECODER_MODE_\w+", block) if "=" not in m]
    seen, ordered = set(), []
    for e in entries:
        if e not in seen:
            seen.add(e)
            ordered.append(e)
    return ordered


def parse_cases(cases_dir: Path):
    for case in sorted(cases_dir.glob("*.in")):
        fields = case.read_text(encoding="utf-8", errors="replace").split()
        knc = False
        if fields and fields[0] == "-knc":
            knc = True
            fields = fields[1:]
        if len(fields) < 2 or fields[0] not in MACHINE_MODES:
            continue
        try:
            payload = bytes.fromhex(fields[-1])
        except ValueError:
            continue
        if not payload:
            continue
        yield case.stem, fields[0], payload, knc


def main() -> int:
    if len(sys.argv) != 4:
        print(f"usage: {sys.argv[0]} <tests/cases dir> <include dir> <output zip>", file=sys.stderr)
        return 2
    cases_dir, include_dir, out_zip = (Path(p) for p in sys.argv[1:4])
    modes = decoder_modes(include_dir)
    knc_index = modes.index("ZYDIS_DECODER_MODE_KNC") if "ZYDIS_DECODER_MODE_KNC" in modes else -1

    class ControlBlock(ctypes.Structure):
        _fields_ = [
            ("machine_mode", ctypes.c_uint32),
            ("stack_width", ctypes.c_uint32),
            ("decoder_mode", ctypes.c_uint8 * len(modes)),
            ("style_lo", ctypes.c_uint8),
            ("style_count", ctypes.c_uint8),
            ("prop_lo", ctypes.c_uint8),
            ("prop_count", ctypes.c_uint8),
            ("hook_mask", ctypes.c_uint8),
            ("hook_func", ctypes.c_uint8),
            ("formatter_max_len", ctypes.c_uint16),
            ("prop_value", ctypes.c_uint64),
            ("runtime_address", ctypes.c_uint64),
        ]

    max_len_cycle = (1, 8, 64, 255, 256, 32)
    count = 0
    with zipfile.ZipFile(out_zip, "w", zipfile.ZIP_DEFLATED) as zf:
        for i, (name, mode, payload, knc) in enumerate(parse_cases(cases_dir)):
            machine_mode, stack_width = MACHINE_MODES[mode]
            cb = ControlBlock()
            cb.machine_mode = machine_mode
            cb.stack_width = stack_width
            if knc and knc_index >= 0:
                cb.decoder_mode[knc_index] = 1
            cb.style_lo = i % 3
            cb.style_count = 3 if i % 3 else 1
            cb.prop_lo = (i * 5) % 16
            cb.prop_count = 16 if i % 2 else 6
            cb.hook_mask = i % 2
            cb.hook_func = (i * 7) % 18
            cb.formatter_max_len = max_len_cycle[i % len(max_len_cycle)]
            cb.prop_value = (i * 0x9E3779B97F4A7C15) % (1 << 64)
            cb.runtime_address = (0x00400000 + i * 0x40) if (i % 5) else (1 << 64) - 1
            seed = bytes(cb) + payload[:32]
            zf.writestr(f"{name}.bin", seed)
            count += 1
    print(f"formatter seeds: wrote {count} cases to {out_zip}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
