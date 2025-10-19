# Metal Gear Solid Reverse Engineering - Development Plan

## 🎯 Project Overview

**Goal**: Complete reverse engineering of Metal Gear Solid Integral (PSX) back to C source code

**Current Status**:
- ✅ Main executables (SLPM_862.47/48/49): **100% decompiled** (626 KB)
- 🚧 Overlays: **1,327 assembly files remaining** to decompile
- 📊 Progress: ~30% of total project complete

## 📋 Decompilation Status by Overlay

### Completed Overlays ✅
- change (Disc Change) - 12 KB
- d00a (Loading Dock Cutscene) - 122 KB
- d01a (Heliport Cutscene) - 57 KB
- d03a (Holding Cell Cutscene) - 18 KB
- d11c (Communication Tower B Cutscene) - 14 KB
- d16e (Underground Base Cutscene) - 65 KB
- demosel (Demo Theater) - 16 KB
- ending/endingr (Ending Demos) - 40 KB each
- opening (Opening Demo) - 42 KB
- preope (Previous Operations) - 25 KB
- roll (Staff Roll) - 39 KB
- s00a (Loading Dock) - 120 KB
- s01a (Heliport) - 137 KB
- s02a/b/c (Tank Hangar variants) - ~130 KB each

### In Progress 🚧
| Overlay | Files | Size | Description |
|---------|-------|------|-------------|
| **camera** | 41 | 54 KB | JPEG Photo Menu |
| **d18a** | 148 | 96 KB | Supply Route Cutscene |
| **option** | 1 | 26 KB | Options Menu |

### Not Started ❌
| Overlay | Files | Size | Description | Priority |
|---------|-------|------|-------------|----------|
| **title** | 18 | ? | Title Screen | 🔴 HIGH - Small, good starting point |
| **abst** | ? | 46 KB | Save/Load Menu | 🟡 MEDIUM |
| **brf** | ? | 125 KB | Briefing | 🟢 LOW - Large and complex |
| **rank** | ? | 139 KB | Ranking Screen | 🟢 LOW - Large and complex |

### Game Level Overlays (Large)
| Overlay | Files | Size | Description |
|---------|-------|------|-------------|
| **s04c** | 50 | ? | Game Level |
| **s08b** | 358 | ? | Game Level (HUGE) |
| **s11d** | 135 | ? | Game Level |
| **s11g** | 61 | ? | Game Level |
| **s12a** | 34 | ? | Game Level |
| **s12c** | 35 | ? | Game Level |
| **s15c** | 47 | ? | Game Level |
| **s19b** | 399 | ? | Game Level (LARGEST) |

**Total Remaining**: 1,327 assembly files

## 🛠️ Build Environment Setup

### Prerequisites
- Python 3.x (✅ installed)
- Wine (for macOS/Linux to run PSX SDK .exe files)
- PSYQ SDK (✅ cloned)

### Installation Steps

1. **Install Wine** (required for macOS):
```bash
brew install --cask --no-quarantine wine-stable
```

2. **Make SDK executables runnable**:
```bash
cd psyq_sdk/psyq_4.4/bin
chmod +x *.exe
```

3. **Install Python dependencies** (✅ completed):
```bash
cd mgs_reversing/build
pip3 install -r requirements.txt
```

4. **Build the project**:
```bash
# Dev variant (easiest for testing)
python3 build.py --variant=dev_exe

# Matching build (verifies accuracy)
python3 build.py

# VR executable variant
python3 build.py --variant=vr_exe
```

## 🎓 Decompilation Workflow

### 1. Choose a Function
- Start with small overlays: **title** (18 files) or **option** (1 file)
- Look in `asm/overlays/<overlay_name>/*.s` for assembly files
- Choose small functions first to learn the process

### 2. Use decomp.me
- Website: https://decomp.me/
- Preset: "Metal Gear Solid (overlays)"
- Tool to help match C code to assembly

### 3. Decompilation Process
```bash
# From build/ directory
python decompme_asm.py [path to .s file]
# This copies assembly to clipboard for decomp.me
```

**Steps**:
1. Create new decomp.me scratch with copied assembly
2. Use context from existing scratches: https://decomp.me/preset/19
3. Implement C function that matches the assembly
4. Iterate until it matches perfectly
5. Move decompiled C code to appropriate source file

### 4. Integration
- Place decompiled functions in `source/<module>/<file>.c`
- Follow existing code organization patterns
- Update build files if needed
- Verify with: `python3 build.py --variant=dev_exe`

### 5. Testing
- Use PCSX-Redux emulator for testing
- Helper scripts in `build/pcsx-redux_scripts/`
- Run: `python3 run.py --iso <ISO_PATH> --pcsx-redux <EMULATOR_PATH>`

## 📚 Recommended Learning Path

### Phase 1: Familiarization (Week 1-2)
- ✅ Clone and build project
- ✅ Understand project structure
- 📖 Study existing decompiled code in `source/`
- 🎮 Play with decomp.me scratches
- 🔍 Analyze small completed overlays (e.g., `change`, `d03a`)

### Phase 2: First Decompilations (Week 3-4)
- 🎯 **Start with**: `title` overlay (18 files, small and manageable)
- Practice on 3-5 small functions
- Learn common patterns and idioms
- Get comfortable with decomp.me workflow

### Phase 3: Medium Complexity (Month 2-3)
- 📸 Continue **camera** overlay (41 files, in progress)
- ⚙️ Complete **option** overlay (1 file remaining)
- 💾 Tackle **abst** (Save/Load Menu, 46 KB)

### Phase 4: Large Overlays (Month 4+)
- 🎬 **brf** (Briefing, 125 KB)
- 🏆 **rank** (Ranking Screen, 139 KB)
- 🎮 Game level overlays (s04c, s11g, s12a, s12c, s15c)

### Phase 5: Massive Overlays (Long-term)
- 🗻 **s08b** (358 files)
- 🏔️ **s19b** (399 files - the final boss!)

## 🤝 Community Resources

- **Discord**: https://discord.gg/tTvhQ8w
  - Channel: `#metal_gear_dev`
  - Ask for help when stuck
  - Share progress and discoveries

- **decomp.me**: https://decomp.me/preset/19
  - Study existing scratches
  - Learn matching techniques
  - See how others approached similar problems

## 📊 Progress Tracking

### Metrics to Track
- [ ] Functions decompiled per week
- [ ] Overlays completed
- [ ] Build success rate
- [ ] Match accuracy

### Current Baseline
- Date: 2025-10-18
- Overlays completed: ~15/~50
- Main executable: 100% ✅
- Total assembly files: 1,327
- Estimated completion: 12-18 months (at moderate pace)

## 🎯 Short-term Goals (Next 30 Days)

1. ✅ Setup build environment (Wine installation pending)
2. 🎯 Complete **title** overlay (18 files)
3. 🎯 Finish **option** overlay (1 file)
4. 🎯 Make progress on **camera** overlay (target: 10+ files)
5. 📖 Study and document common code patterns
6. 🤝 Join Discord community and introduce yourself

## 🔧 Development Tools

- **Code Editor**: VSCode/CLion with C/Assembly support
- **Emulator**: PCSX-Redux for testing
- **Diff Tool**: For comparing assembly output
- **decomp.me**: Online decompilation matcher
- **Python scripts**: In `build/` directory for automation

## 📝 Notes

- The main executable was 626 KB and took the community ~2-3 years
- Overlays are smaller but numerous (1,327 files)
- Quality over quantity - accurate matches are crucial
- The community is friendly and helpful
- Document your discoveries and patterns
- Take breaks to avoid burnout

## 🚀 Next Actions

1. **Install Wine**: `brew install --cask --no-quarantine wine-stable`
2. **Test build**: `python3 build.py --variant=dev_exe`
3. **Study code**: Read through `source/` directory
4. **Pick first target**: Start with `title` overlay
5. **Join Discord**: Get connected with the community
6. **First function**: Decompile one small function to learn workflow

---

**Remember**: This is a marathon, not a sprint. The MGS community has been working on this for years. Every function you decompile is a contribution to preserving gaming history! 🎮🐍
