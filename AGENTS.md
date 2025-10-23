# Repository Guidelines

## Project Structure & Module Organization
- `source/`: C sources by subsystem; headers in `source/include/`. Overlay code lives under `source/overlays/<overlay>/`.
- `asm/`: assembly stubs awaiting decompilation.
- `build/`: Python build tooling (`build.py`, `run.py`, helper scripts) and `requirements.txt`.
- `um/`: original overlay binaries; `obj`, `obj_vr`, `obj_dev`: build outputs.

## Build, Test, and Development Commands
- Setup: `cd build && pip3 install -r requirements.txt`
- Build main/VR/dev: `python3 build.py [--variant=main_exe|vr_exe|dev_exe] [--psyq_path /path/to/psyq_sdk]`
- Dev run (auto‑reload): `python3 run.py --iso <SLPM-86247 image> --pcsx-redux <path>`
- macOS/Linux: install Wine if needed: `brew install --cask --no-quarantine wine-stable`
- PSYQ SDK path: set `PSYQ_SDK` or pass `--psyq_path`. Build emits `build.ninja` and `_mgsi.exe`; `obj_dev/build_success.txt` is touched after a successful dev build.

## Coding Style & Naming Conventions
- Use `.clang-format` (Microsoft base). Format before pushing: `./clang-format-all source`.
- Line endings are LF (`.gitattributes`).
- Indentation (`.editorconfig`): C/H 4-space; Python 4-space; ASM uses tabs (width 8).
- Keep existing prefixes and folder-based names (e.g., `s08b_*`, `takabe/*`). Pair headers with C files where applicable; use lower_snake_case for filenames.

## Testing Guidelines
- Primary test is a matching build. Successful `python3 build.py` prints a SHA256 that must match the original; fix any new warnings (CI blocks non‑whitelisted ones).
- After decompiling, ensure no orphan `.s` remain; the build will suggest deletions (from `build/post_build_checkup.py`).
- Optional diffing: `python3 build/compare.py` to inspect mismatches.

## Commit & Pull Request Guidelines
- Commit messages: imperative and concise (e.g., "Cleanup takabe/shakemdl.c", "Decompile DG_ChangeReso").
- PRs: include scope (subsystem/overlay/function), rationale, and approach; link related issues/scratches when relevant.
- Evidence: note variant built and that hashes matched; confirm formatting applied; avoid broad renames/refactors without discussion.

## Security & Configuration Tips
- Do not commit SDK paths, emulator binaries, or game assets/ISOs.
- Keep `PSYQ_SDK` configured locally; prefer flags/env vars over hardcoded paths.

