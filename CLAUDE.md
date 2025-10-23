# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a decompilation project for **Metal Gear Solid Integral** (PlayStation 1), aiming to reverse engineer the game back to C source code that produces identical assembly when compiled with PSYQ SDK 4.4.

**Current Status**: Main executables (SLPM_862.47/48/49) are 100% decompiled. Active work focuses on decompiling overlays (per-stage executable code loaded dynamically).

## Build System

### Core Build Commands

```bash
# Generate ninja build files and build
cd build
python3 build.py                    # Main executable (matching build)
python3 build.py --variant=vr_exe   # VR disc variant
python3 build.py --variant=dev_exe  # Development build (non-matching, for testing)

# Build system uses ninja (auto-generated from build.py)
ninja -C ..                         # Direct ninja build after build.py
```

### Prerequisites

- **PSYQ SDK**: Environment variable `PSYQ_SDK` or default path `../../psyq_sdk`
- **Wine** (macOS/Linux): Required to run PSYQ compilers (.exe files)
  - macOS: `brew install --cask --no-quarantine wine-stable`
- **Python 3** with dependencies from project root

### Build Variants

- `main_exe`: Matching build for SLPM_862.47/48 (Integral Disc 1/2)
- `vr_exe`: Matching build for SLPM_862.49 (VR Disc) with `VR_EXE` define
- `dev_exe`: Non-matching development build for testing modifications

## Decompilation Workflow

### Using decomp.me

The project uses decomp.me for matching functions to target assembly:

```bash
# 1. Extract assembly for decomp.me
cd build
python3 decompme_asm.py ../asm/overlays/<overlay>/<function>.s

# 2. Go to https://decomp.me/
#    - Use "Metal Gear Solid (overlays)" preset
#    - Paste assembly from clipboard
#    - Choose context from: https://decomp.me/preset/19

# 3. Write C code until diff shows 100% match (green)

# 4. Copy matched C code to appropriate source file
#    See source/ directory structure below
```

### Using Permuter

For difficult functions, the project includes permuter support:

```bash
cd permuter/<function_name>

# Test variations manually
# - Copy variation code to decomp.me
# - Record scores in TEST_RESULTS.md

# Document patterns discovered
# - Update BEST_CODE_*.txt with winning variation
# - Note compiler-specific patterns for reuse
```

## Architecture

### Directory Structure

```
source/              # Decompiled C source code
├── overlays/        # Per-stage overlay code
├── game/            # Core game engine
├── libgv/           # Game vector library
├── libdg/           # Display/graphics library
├── libgcl/          # Game control library
├── chara/           # Character/actor systems
├── weapon/          # Weapon implementations
├── equip/           # Equipment systems
└── [many more]      # Various game subsystems

asm/                 # Target assembly to match
├── overlays/        # Overlay assembly files
└── [functions].s    # Individual function assembly

build/               # Build scripts and utilities
obj/                 # Object files (main_exe)
obj_vr/              # Object files (vr_exe)
obj_dev/             # Object files (dev_exe)

permuter/            # Manual variation testing directories
└── <function_name>/ # Per-function permuter workspaces
```

### Overlay System

Metal Gear Solid loads per-stage overlays dynamically. Each overlay contains:
- Stage-specific actor code
- Custom game logic for that level
- Level-specific data structures

**Key overlays**:
- `title` (18 files) - Title screen, recommended starter
- `option` (1 file) - Options menu, easiest target
- `camera` (41 files) - Camera system, partially complete
- `s??a/s??b/s??c` - Stage-specific code (numbered by level)

Overlay code often uses `#pragma INCLUDE_ASM("asm/overlays/<overlay>/<function>.s")` for functions not yet decompiled.

### PSYQ SDK Compiler Patterns

The project targets **PSYQ SDK 4.4** with **gcc 2.8.1** and **aspsx 2.79**. Key compiler behaviors:

#### Pattern 1: Pointer Arithmetic
```c
// ✅ Preferred by PSYQ gcc
elem = base;
elem += index;

// ❌ Less optimal (different register allocation)
elem = &base[index];
```

#### Pattern 2: Descriptive Variable Naming
```c
// ✅ Better register allocation
int shade = work->field;

// ❌ Generic names may allocate differently
int temp = work->field;
```

#### Pattern 3: Struct Field Re-reading
```c
// ✅ PSYQ gcc prefers fresh loads in conditionals
value = work->field;
use(value);
if (work->field >= threshold)  // Re-read field

// ❌ May not match (register reuse instead of load)
if (value >= threshold)  // Use cached variable
```

These patterns were discovered through systematic assembly analysis and are documented in `permuter/title_open_800CE378/` as a case study.

## Key Build Utilities

### Analysis and Comparison

```bash
# Compare compiled output to target
python3 compare_asm.py              # Assembly comparison
python3 compare_detailed.py         # Detailed diff analysis
python3 progress.py                 # Show decompilation progress

# Function analysis
python3 dump_funcs.py               # Extract function information
python3 ml_suggest.py               # ML-based function suggestions
```

### Code Management

```bash
# Fix INCLUDE_ASM pragmas
python3 include_asm_fixup.py

# Rename symbols across codebase
python3 rename.py

# Clean build artifacts
python3 clean.py
```

### Testing with Emulator

```bash
# Run with PCSX-Redux (auto-reload on rebuild)
python3 run.py --iso <path_to_iso> --pcsx-redux <path_to_emulator>
```

## Development Patterns

### Starting a New Function

1. **Find target assembly**: Navigate to `asm/overlays/<overlay>/`
2. **Prepare for decomp.me**: `python3 build/decompme_asm.py <asm_file>`
3. **Match on decomp.me**: Iteratively write C until 100% match
4. **Integrate**: Place matched code in appropriate `source/` file
5. **Build and verify**: `python3 build.py` should still match

### Handling Difficult Functions

1. **Study adjacent functions**: Look at nearby decompiled code for patterns
2. **Create permuter workspace**: `mkdir permuter/<function_name>`
3. **Test variations systematically**: Document in `TEST_RESULTS.md`
4. **Analyze assembly differences**: Compare your output to target
5. **Apply discovered patterns**: Update code with compiler-specific patterns
6. **Document findings**: Update `BEST_CODE_*.txt` for future reference

### Code Organization

- Place overlay functions in `source/overlays/<overlay>/`
- Main executable code goes in respective subsystem directories
- Include files in `source/include/`
- Follow existing naming conventions and file organization

### Pragma INCLUDE_ASM

Functions not yet decompiled use:
```c
#pragma INCLUDE_ASM("asm/overlays/<overlay>/<function>.s")
```

When you decompile a function, **replace this pragma with your C code**.

## Common Issues

### Build Failures

- **Wine not installed**: Required on macOS/Linux for PSYQ compilers
- **PSYQ_SDK path wrong**: Set environment variable or use `--psyq_path`
- **Missing dependencies**: Run `pip3 install -r requirements.txt` from project root

### Matching Failures

- **Wrong types**: Use correct sizes (int vs short vs char)
- **Cast issues**: PSYQ gcc is sensitive to explicit casts
- **Operator precedence**: Parentheses matter for matching
- **Variable naming**: While names don't affect matching, they affect register allocation

### Assembly Differences

- **Register allocation**: Try pointer arithmetic vs array indexing
- **Control flow**: Different `break`/`return`/`goto` patterns produce different jumps
- **Struct access**: Re-reading fields vs caching in locals affects codegen
- **Jump table labels**: Linker-level symbols (`jtbl_*` vs `.rdata`) can't be controlled from C

## Score Interpretation (decomp.me)

- **0**: Perfect 100% match ✅
- **1-499**: Very close (93-99%), minor differences
- **500-699**: Good progress (91-93%), significant differences
- **700+**: Major differences (< 91%), needs work

Lower score = better match. Score is Levenshtein distance between assembly outputs.

## Resources

- **decomp.me preset**: https://decomp.me/preset/19
- **Discord**: https://discord.gg/tTvhQ8w (#metal_gear_dev)
- **Repository README**: Comprehensive documentation of overlay status and build system
- **Existing source**: Study `source/` for patterns and conventions
- **Permuter case study**: `permuter/title_open_800CE378/` demonstrates systematic variation testing
