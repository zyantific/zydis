#!/usr/bin/env python3
"""Generates the ZydisFuzzEncoderStructured seed corpus from the upstream test cases.

Each seed mirrors the `ZydisFuzzControlBlock` layout of
`tools/ZydisFuzzEncoderStructured.c` (natural C alignment, enums are 4 bytes,
`ZyanBool` is 1 byte) followed by the raw instruction bytes of one decoder test
case. The instruction bytes decode into a structurally valid encoder-request
skeleton (including KNC/MVEX cases, which enable the KNC decoder mode); the
control-block fields rotate the option-field sweep space on top of it.
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
            ("encodings_sel", ctypes.c_uint8),
            ("prefixes_sel", ctypes.c_uint8),
            ("branch_sel", ctypes.c_uint8),
            ("hint_sel", ctypes.c_uint8),
            ("evex_sel", ctypes.c_uint8),
            ("mvex_sel", ctypes.c_uint8),
            ("abs_mode", ctypes.c_uint8),
            ("sweep_count", ctypes.c_uint8),
            ("runtime_address", ctypes.c_uint64),
        ]

    count = 0
    with zipfile.ZipFile(out_zip, "w", zipfile.ZIP_DEFLATED) as zf:
        for i, (name, mode, payload, knc) in enumerate(parse_cases(cases_dir)):
            machine_mode, stack_width = MACHINE_MODES[mode]
            cb = ControlBlock()
            cb.machine_mode = machine_mode
            cb.stack_width = stack_width
            if knc and knc_index >= 0:
                cb.decoder_mode[knc_index] = 1
            cb.encodings_sel = i % 8
            cb.prefixes_sel = (i * 3) % 8
            cb.branch_sel = (i * 5) % 8
            cb.hint_sel = (i * 7) % 8
            cb.evex_sel = (i * 11) % 8
            cb.mvex_sel = (i * 13) % 8 if name.startswith("mvex") else i % 8
            cb.abs_mode = i % 2
            cb.sweep_count = 8
            cb.runtime_address = 0x00400000 + i * 0x40
            seed = bytes(cb) + payload[:32]
            zf.writestr(f"{name}.bin", seed)
            count += 1
    print(f"encoder-structured seeds: wrote {count} cases to {out_zip}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
