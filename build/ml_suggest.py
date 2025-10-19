#!/usr/bin/env python3

"""
ML-aided function suggestion tool.

Generates top-K candidate matches from compiled objects for each target .s file.
Outputs build/ml_suggestions.json and supports an optional interactive picker.

Design goals:
- Minimal deps (uses capstone + Levenshtein already used in repo).
- Robust to reloc/immediates via instruction-token abstraction.
- Works on Mac (CPU) and Linux.
"""

import argparse
import json
import os
import re
import sys
from glob import glob
from pathlib import Path
from typing import Dict, List, Tuple

from objlib.obj import get_obj_funcs  # build/objlib

try:
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
    HAVE_CAPSTONE = True
except Exception:
    HAVE_CAPSTONE = False

try:
    from Levenshtein import ratio as levenshtein_ratio
    HAVE_LEVENSHTEIN = True
except Exception:
    HAVE_LEVENSHTEIN = False


def read_obj_functions() -> Dict[str, bytes]:
    funcs: Dict[str, bytes] = {}
    for obj_file in glob(os.path.join("obj*", "**", "*.obj"), recursive=True):
        if "_fixme" in obj_file:
            continue
        for func_name, code_segments in get_obj_funcs(obj_file):
            code = b"".join(code for _, code in code_segments)
            name = func_name.decode("utf-8")
            # Keep the longest version if duplicates occur across variants
            if name not in funcs or len(code) > len(funcs[name]):
                funcs[name] = code
    return funcs


DW_RE = re.compile(r"^\s*dw\s+0x([0-9A-Fa-f]{8})\b")


def parse_s_bytes(path: str) -> bytes:
    words = []
    with open(path, "r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            m = DW_RE.match(line)
            if m:
                w = int(m.group(1), 16)
                words.append(w)
    # Pack as big-endian words (matches hex in .s)
    b = bytearray()
    for w in words:
        b.extend(w.to_bytes(4, byteorder="big", signed=False))
    return bytes(b)


def bytes_to_words_be(b: bytes) -> List[int]:
    n = len(b) // 4
    return [int.from_bytes(b[i * 4 : (i + 1) * 4], "big") for i in range(n)]


def ngrams(seq: List[int], n: int) -> List[Tuple[int, ...]]:
    if len(seq) < n:
        return []
    return [tuple(seq[i : i + n]) for i in range(len(seq) - n + 1)]


def jaccard(a: List[Tuple[int, ...]], b: List[Tuple[int, ...]]) -> float:
    sa, sb = set(a), set(b)
    if not sa and not sb:
        return 1.0
    return len(sa & sb) / max(1, len(sa | sb))


def disassemble_tokens(code: bytes) -> List[int]:
    if not HAVE_CAPSTONE:
        # Fallback to word stream as tokens
        return bytes_to_words_be(code)
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 + CS_MODE_LITTLE_ENDIAN)
    md.detail = True
    tokens: List[int] = []
    # Walk code in 4B steps; capstone is tolerant to unknown words
    for insn in md.disasm(code, 0):
        tokens.append(insn.id)
        # Append register operands only; drop immediates (reloc-robust)
        for op in getattr(insn, "operands", []):
            if op.type == 1:  # REG
                tokens.append(op.value.reg)
    if not tokens:
        # Fallback if nothing decoded
        return bytes_to_words_be(code)
    return tokens


def distance_score(lhs_bytes: bytes, rhs_bytes: bytes) -> float:
    # Word n-gram Jaccard + byte-level Levenshtein composite
    lhs_words = bytes_to_words_be(lhs_bytes)
    rhs_words = bytes_to_words_be(rhs_bytes)

    # Early prune on size ratio
    if len(rhs_words) == 0:
        return 1.0
    size_ratio = len(lhs_words) / max(1, len(rhs_words))
    if size_ratio < 0.5 or size_ratio > 2.0:
        return 0.99  # high (bad) score to de-prioritize

    # Jaccard on 3-grams of words
    j_lhs = ngrams(lhs_words, 3)
    j_rhs = ngrams(rhs_words, 3)
    j = jaccard(j_lhs, j_rhs)
    j_comp = 1.0 - j

    # Levenshtein on raw bytes (fast path). If unavailable, approximate with length diff
    if HAVE_LEVENSHTEIN:
        lev = 1.0 - levenshtein_ratio(lhs_bytes, rhs_bytes)
    else:
        L = max(len(lhs_bytes), len(rhs_bytes))
        lev = abs(len(lhs_bytes) - len(rhs_bytes)) / max(1, L)

    # Instruction-token Jaccard for re-ranking (cheap, ignore if capstone missing)
    if HAVE_CAPSTONE:
        t_lhs = disassemble_tokens(lhs_bytes)
        t_rhs = disassemble_tokens(rhs_bytes)
        t_j = jaccard(ngrams(t_lhs, 4), ngrams(t_rhs, 4))
        t_comp = 1.0 - t_j
        return 0.4 * lev + 0.3 * j_comp + 0.3 * t_comp
    else:
        return 0.6 * lev + 0.4 * j_comp


def suggest_for_overlay(
    overlay: str,
    topk: int,
    filter_self: bool = True,
    deprioritize_overlay_prefix: bool = True,
) -> Dict[str, List[Dict]]:
    asm_glob = os.path.join("asm", "overlays", overlay, "*.s")
    asm_files = sorted(glob(asm_glob))
    if not asm_files:
        print("No .s files found for overlay:", overlay, file=sys.stderr)
        return {}

    print(f"Loading object functions from obj*/ ...", file=sys.stderr)
    obj_funcs = read_obj_functions()
    print(f"Loaded {len(obj_funcs)} reference functions", file=sys.stderr)

    # Precompute bytes for all obj functions
    obj_items = list(obj_funcs.items())

    results: Dict[str, List[Dict]] = {}
    overlay_prefix = f"{overlay}_"

    for idx, s_path in enumerate(asm_files, 1):
        base = os.path.basename(s_path)
        symbol = os.path.splitext(base)[0]
        print(f"[{idx}/{len(asm_files)}] {base}", file=sys.stderr)
        try:
            s_bytes = parse_s_bytes(s_path)
        except Exception as e:
            print("  skip (parse error):", e, file=sys.stderr)
            continue
        if len(s_bytes) < 8:
            continue

        scored: List[Tuple[float, str]] = []
        for name, code in obj_items:
            score = distance_score(s_bytes, code)
            # Re-ranking tweaks
            if deprioritize_overlay_prefix and name.startswith(overlay_prefix):
                score += 0.02
            scored.append((score, name))

        scored.sort(key=lambda x: x[0])

        if filter_self:
            scored = [(s, n) for (s, n) in scored if n != symbol]

        top = scored[: topk]
        results[base] = [
            {"candidate": name, "score": round(score, 4), "note": "lower is better"}
            for score, name in top
        ]
    return results


def interactive_picker(overlay: str, results: Dict[str, List[Dict]]):
    try:
        from iterfzf import iterfzf
    except Exception:
        print("iterfzf not installed. Run: pip install iterfzf", file=sys.stderr)
        return

    options = []
    for s_file, cands in results.items():
        line = f"{s_file}  |  " + ", ".join(
            f"{c['candidate']} ({c['score']})" for c in cands[:3]
        )
        options.append(line)

    picked = iterfzf(options, prompt=f"overlay {overlay}> ")
    if not picked:
        return
    s_file = picked.split("|")[0].strip()
    s_path = os.path.join("asm", "overlays", overlay, s_file)

    # Pipe to decompme helper to copy ASM
    helper = os.path.join("build", "decompme_asm.py")
    if not Path(helper).exists():
        print("Helper not found:", helper, file=sys.stderr)
        return
    os.execvp(sys.executable, [sys.executable, helper, s_path])


def main():
    p = argparse.ArgumentParser(description="Suggest similar functions for overlay .s files")
    p.add_argument("--overlay", required=True, help="Overlay name (e.g., title, camera)")
    p.add_argument("--topk", type=int, default=5, help="Top-K candidates per function")
    p.add_argument("--interactive", action="store_true", help="Interactive picker via fzf")
    p.add_argument("--keep-self", action="store_true", help="Keep self-matches in results")
    p.add_argument(
        "--no-deprioritize-prefix",
        action="store_true",
        help="Do not down-rank candidates starting with '<overlay>_'",
    )
    p.add_argument("--out", default=os.path.join("build", "ml_suggestions.json"))
    args = p.parse_args()

    results = suggest_for_overlay(
        args.overlay,
        args.topk,
        filter_self=not args.keep_self,
        deprioritize_overlay_prefix=not args.no_deprioritize_prefix,
    )
    os.makedirs(os.path.dirname(args.out), exist_ok=True)
    with open(args.out, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2)
    print("Saved:", args.out)

    if args.interactive and results:
        interactive_picker(args.overlay, results)


if __name__ == "__main__":
    main()
