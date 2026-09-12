#!/usr/bin/env python3
"""Extract the STM32 64x64 animation into CC2530 C source files."""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path


FRAME_COUNT = 30
FRAME_BYTES = 512
FRAME_WIDTH = 64
FRAME_HEIGHT = 64
BYTE_RE = re.compile(r"0x[0-9A-Fa-f]{1,2}")
ARRAY_RE = re.compile(r"\bcat\s*\[\s*\]\s*\[\s*512\s*\]\s*=")


def _extract_blocks(source: str) -> list[tuple[str, list[str]]]:
    match = ARRAY_RE.search(source)
    if match is None:
        raise ValueError("could not find cat[][512] initializer")

    outer_start = source.find("{", match.end())
    if outer_start < 0:
        raise ValueError("cat initializer has no opening brace")

    blocks: list[tuple[str, list[str]]] = []
    depth = 0
    block_start = -1
    cursor = outer_start
    while cursor < len(source):
        char = source[cursor]
        if char == "{":
            if depth == 1:
                block_start = cursor + 1
            depth += 1
        elif char == "}" and depth > 0:
            depth -= 1
            if depth == 1 and block_start >= 0:
                block = source[block_start:cursor]
                values = BYTE_RE.findall(block)
                before = source[max(0, block_start - 160):block_start]
                frame_match = re.search(r"frame-\d+", before)
                label = frame_match.group(0) if frame_match else f"frame-{len(blocks) + 1}"
                blocks.append((label, values))
                block_start = -1
            elif depth == 0:
                break
        cursor += 1

    if depth != 0:
        raise ValueError("cat initializer has unbalanced braces")
    return blocks


def extract(source_path: Path) -> list[tuple[str, list[str]]]:
    source = source_path.read_text(encoding="utf-8")
    blocks = _extract_blocks(source)
    if len(blocks) != FRAME_COUNT:
        raise ValueError(f"expected {FRAME_COUNT} frames, found {len(blocks)}")
    for index, (label, values) in enumerate(blocks, start=1):
        if len(values) != FRAME_BYTES:
            raise ValueError(
                f"{label} (block {index}) has {len(values)} bytes, expected {FRAME_BYTES}"
            )
    return blocks


def render_header() -> str:
    return """#ifndef EASTER_FRAMES_H
#define EASTER_FRAMES_H

#define EASTER_FRAME_WIDTH 64
#define EASTER_FRAME_HEIGHT 64
#define EASTER_FRAME_BYTES 512
#define EASTER_FRAME_COUNT 30

extern const unsigned char __code easter_frames[EASTER_FRAME_COUNT][EASTER_FRAME_BYTES];

#endif /* EASTER_FRAMES_H */
"""


def render_source(blocks: list[tuple[str, list[str]]]) -> str:
    lines = [
        '#include "easter_frames.h"',
        "",
        "const unsigned char __code easter_frames[EASTER_FRAME_COUNT][EASTER_FRAME_BYTES] = {",
        "",
    ]
    for index, (label, values) in enumerate(blocks):
        lines.append(f"/* {label} */")
        lines.append("{")
        for offset in range(0, FRAME_BYTES, 16):
            lines.append("    " + ", ".join(values[offset:offset + 16]) + ",")
        lines.append("}" + ("," if index + 1 < len(blocks) else ""))
    lines.extend(["};", ""])
    return "\n".join(lines)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path, help="STM32 main.c containing cat[][512]")
    parser.add_argument("--output-dir", type=Path, default=Path("Common"))
    parser.add_argument("--check", action="store_true", help="validate only; do not write files")
    args = parser.parse_args(argv)

    try:
        blocks = extract(args.input)
    except (OSError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1

    print(f"{len(blocks)} frames x {FRAME_BYTES} bytes")
    if args.check:
        return 0

    args.output_dir.mkdir(parents=True, exist_ok=True)
    # IAR 期望 CRLF；__code 让 15KB 帧数据留在 CODE 区，避免 XDATA 溢出
    (args.output_dir / "easter_frames.h").write_text(render_header(), encoding="ascii", newline="\r\n")
    (args.output_dir / "easter_frames.c").write_text(render_source(blocks), encoding="ascii", newline="\r\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
