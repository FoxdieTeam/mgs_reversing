# ML Toolkit for Function Suggestions

This folder contains optional ML/IR tools to speed up overlay decompilation by suggesting similar/matching functions from already-decompiled objects.

## What It Does
- Parses `.s` files (dw 0xXXXXXXXX) into instruction words.
- Loads compiled functions from `obj*/**/*.obj` as a reference library.
- Computes similarity (word-level and instruction-level) and outputs top-K candidates per `.s`.
- Optional interactive picker to open the `.s` in decomp.me helper.

## Quick Start (Mac M1, CPU)
- Create venv and install deps:
  - `python3 -m venv .venv && source .venv/bin/activate`
  - `pip install -r tools/ml/requirements-cpu.txt`
- Generate suggestions for an overlay:
  - `python build/ml_suggest.py --overlay title --topk 5`
- Optional TUI to pick a target and copy ASM to clipboard:
  - `python build/ml_suggest.py --overlay title --interactive`

## GPU Setup (Linux + RTX 3090)
- Create a conda env with CUDA + FAISS GPU for future models:
  - `conda env create -f tools/ml/environment-gpu.yml`
  - `conda activate mgs-ml`
- Current script runs on CPU; GPU becomes useful when training a Siamese/Transformer model.

## Outputs
- `build/ml_suggestions.json`: top-K candidates for each `.s` file with scores and references.

## Notes
- No changes to the build pipeline are required. These tools are optional and local.
- Dependencies are separate from `build/requirements.txt` to keep CI minimal.
- Capstone is used to derive instruction tokens; we fall back to byte/word features if needed.

