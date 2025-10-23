# MGS Reversing - Quick Start Guide

## ⚡ Immediate Next Steps

### 1. Complete Build Environment Setup

The build failed because **Wine is not installed**. Wine is required on macOS to run the PlayStation SDK compilers (.exe files).

```bash
# Install Wine (will ask for sudo password)
brew install --cask --no-quarantine wine-stable

# Verify installation
which wine
```

After Wine is installed, test the build:

```bash
cd development-workspace/mgs_reversing/build
python3 build.py --variant=dev_exe
```

### 2. Choose Your First Target

**Recommended: Start with the `title` overlay** (18 files)
- Small enough to be manageable
- Good for learning the workflow
- Visible results (title screen!)

**Location**: `mgs_reversing/asm/overlays/title/`

```bash
cd mgs_reversing/asm/overlays/title
ls -la  # See the assembly files
```

### 3. Decompilation Workflow (Quick Reference)

```bash
# 1. From build/ directory, copy assembly to clipboard
cd mgs_reversing/build
python3 decompme_asm.py ../asm/overlays/title/<function_name>.s

# 2. Go to decomp.me
# - Visit: https://decomp.me/
# - Choose preset: "Metal Gear Solid (overlays)"
# - Paste assembly from clipboard
# - Choose a context from: https://decomp.me/preset/19

# 3. Write C code that matches the assembly
# - Iterative process
# - Use decomp.me's diff view
# - Goal: 100% match (green diff)

# 4. When matched, copy C code to appropriate source file
# Look at existing code in source/ to understand organization

# 5. Test
python3 build.py --variant=dev_env
```

## 📊 Current Project State

### ✅ What's Working
- Repository cloned ✅
- PSYQ SDK cloned ✅
- Python dependencies installed ✅
- Project structure analyzed ✅
- Decompilation plan created ✅

### ⚠️ What Needs Fixing
- Wine installation (required for build)
- First successful build
- First function decompilation

### 📈 Statistics
```
Total Assembly Files: 1,327
Recommended Starting Point: title overlay (18 files)

Priority Queue:
1. title (18 files) - Good starter
2. option (1 file) - Quick win
3. camera (41 files) - In progress
4. abst (? files) - Medium difficulty
```

## 🎯 Your First Decompilation Session

### Session Goal
Decompile **ONE** function from the `title` overlay

### Step-by-Step

1. **Pick the smallest file**:
```bash
cd mgs_reversing/asm/overlays/title
ls -lS *.s | tail -5  # Show 5 smallest files
```

2. **Study the assembly**:
```bash
cat <smallest_file>.s
```

3. **Copy to clipboard for decomp.me**:
```bash
cd ../../build
python3 decompme_asm.py ../asm/overlays/title/<smallest_file>.s
```

4. **Go to decomp.me**:
- Create new scratch
- Paste assembly
- Select Metal Gear Solid preset
- Choose a context (use one from existing scratches)

5. **Write C code**:
- Look at existing source in `source/` for patterns
- Common patterns:
  - Actor systems
  - Memory management
  - Graphics/drawing functions
  - Game logic

6. **Match it**:
- Use decomp.me diff view
- Adjust until green (100% match)
- Common issues:
  - Wrong types (int vs short vs char)
  - Wrong operator order
  - Missing casts
  - Wrong variable names (doesn't affect match!)

7. **Integrate**:
```c
// Add to appropriate file in source/
// Update build system if needed
// Rebuild and test
```

## 🔧 Useful Commands

### Project Navigation
```bash
# Go to project root
cd ~/development-workspace/mgs_reversing

# See overlays
ls -la asm/overlays/

# See source code
ls -la source/

# Build directory
cd build
```

### Build Commands
```bash
# Dev build (easiest for testing)
python3 build.py --variant=dev_exe

# Matching build (verifies accuracy)
python3 build.py

# Check for specific overlay
python3 build.py --help
```

### Analysis Commands
```bash
# Count assembly files in an overlay
find asm/overlays/<overlay_name> -name "*.s" | wc -l

# Find smallest files (good starting points)
cd asm/overlays/<overlay_name>
ls -lS *.s | tail -10

# Search for patterns in source
grep -r "pattern" source/
```

## 🤝 Getting Help

### When Stuck on Decompilation
1. Check decomp.me existing scratches: https://decomp.me/preset/19
2. Look for similar functions in `source/`
3. Ask on Discord: https://discord.gg/tTvhQ8w (#metal_gear_dev)

### When Stuck on Build Issues
1. Check appveyor.yml for CI build process
2. Verify Wine installation: `wine --version`
3. Check psyq_sdk path is correct
4. Ask on Discord

### When Stuck on Understanding Code
1. Read README.md for architecture overview
2. Study completed overlays (e.g., `change`, `d03a`)
3. Look at main executable source in `source/`
4. Ask on Discord

## 📚 Essential Reading

Before diving deep into decompilation:

1. **Project README**: `mgs_reversing/README.md`
   - Build instructions
   - Overlay list with status
   - How to use decomp.me

2. **Existing Source Code**: `mgs_reversing/source/`
   - See how functions are organized
   - Learn common patterns
   - Understand naming conventions

3. **decomp.me Scratches**: https://decomp.me/preset/19
   - Study successful matches
   - Learn matching techniques
   - See community solutions

## ⚡ Quick Wins to Build Momentum

### Easy Targets (1-2 hours each)
1. **option overlay** - Just 1 file!
2. **title overlay** - 18 small files
3. Finish incomplete functions in **camera** overlay

### Medium Targets (1-2 days each)
1. **abst** (Save/Load Menu) - 46 KB
2. **s04c** - 50 files
3. **s12a** - 34 files

### Long-term Goals (weeks/months)
1. Complete all small overlays
2. Tackle **brf** (Briefing) - 125 KB
3. Take on **s08b** - 358 files
4. The final boss: **s19b** - 399 files

## 🎮 Testing Your Changes

### Using PCSX-Redux Emulator

1. **Download PCSX-Redux**:
   - macOS: https://install.appcenter.ms/orgs/grumpycoders/apps/pcsx-redux-linux64/distribution_groups/public

2. **Run with your build**:
```bash
cd mgs_reversing/build
python3 run.py --iso <path/to/MGS_ISO> --pcsx-redux <path/to/emulator>
```

3. **Auto-reload on rebuild**:
   - Keep `run.py` running
   - In another terminal, rebuild: `python3 build.py --variant=dev_exe`
   - Emulator will automatically reload with changes

## 💡 Pro Tips

1. **Start Small**: Don't try to decompile a 100KB overlay first
2. **Use decomp.me**: It's your best friend for matching
3. **Study Existing Code**: Learn from already-decompiled functions
4. **Join Discord Early**: Community is friendly and helpful
5. **Document Patterns**: Keep notes on common code patterns you find
6. **Take Breaks**: Decompilation can be mentally taxing
7. **Celebrate Progress**: Every matched function is a win!

## 🎯 Success Criteria

You'll know you're making progress when:
- ✅ Wine is installed and build works
- ✅ You've successfully matched one function on decomp.me
- ✅ You've integrated one function into the source
- ✅ Your build produces matching assembly for that function
- ✅ You understand the workflow end-to-end

## 🚀 Start Here Right Now

```bash
# 1. Install Wine (if not already done)
brew install --cask --no-quarantine wine-stable

# 2. Test build
cd ~/development-workspace/mgs_reversing/build
python3 build.py --variant=dev_exe

# 3. Pick first target
cd ../asm/overlays/title
ls -lS *.s | tail -5

# 4. Copy smallest file to decomp.me
cd ../../build
python3 decompme_asm.py ../asm/overlays/title/<file>.s

# 5. Go to https://decomp.me/ and start!
```

Good luck! Every function you decompile brings Metal Gear Solid one step closer to being fully preserved! 🐍🎮
