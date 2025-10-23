# 🚀 Ready to Start Decompiling!

## ✅ Everything is Set Up

Congratulations! You're ready to decompile your first Metal Gear Solid function!

### What We've Done So Far

1. ✅ **Downloaded the project**
   - `mgs_reversing` repository cloned
   - `psyq_sdk` dependency cloned
   - Python dependencies installed

2. ✅ **Analyzed the project**
   - Identified 1,327 assembly files to decompile
   - Found the best starting point: `title` overlay
   - Located the smallest function: `title_open_800D2374.s` (59 instructions)

3. ✅ **Studied the code**
   - Examined existing decompiled functions
   - Understood the OpenWork structure
   - Analyzed similar patterns

4. ✅ **Prepared the function**
   - Converted assembly to decomp.me format
   - Created detailed analysis document
   - Proposed C implementation

### What's Left

⚠️ **Only one thing remaining: Install Wine**

```bash
brew install --cask --no-quarantine wine-stable
```

This is needed to compile the PlayStation SDK tools on macOS.

## 🎯 Your First Decompilation Mission

**Target**: `title_open_800D2374`
- **File**: `source/overlays/title/onoda/open/open.c:1263`
- **Size**: 59 instructions (~236 bytes)
- **Difficulty**: ⭐⭐ Medium

### Step-by-Step Instructions

#### 1. Get the Assembly (Already Done!)

```bash
cd ~/development-workspace/mgs_reversing/build
python3 convert_asm.py ../asm/overlays/title/title_open_800D2374.s
```

This outputs the MIPS assembly ready for decomp.me.

#### 2. Go to decomp.me

**URL**: https://decomp.me/

1. Click "New Scratch"
2. Choose platform: **PlayStation (MIPS)**
3. Select preset: **Metal Gear Solid (overlays)**
4. Paste the assembly output from step 1

#### 3. Choose a Context

Visit https://decomp.me/preset/19 and find a similar function.

Look for recent "title_open" scratches to copy the context (headers/includes).

Example context structure:
```c
#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "menu/menuman.h"
#include "game/game.h"
#include "sd/sd_cli.h"
#include "sd/g_sound.h"

// OpenWork structure definition
typedef struct _OpenWork { ... } OpenWork;

// Your function here
void title_open_800D2374(OpenWork *work) {
    // ...
}
```

#### 4. Start with the Proposed Implementation

Copy this into decomp.me:

```c
void title_open_800D2374(OpenWork *work)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->f24BC != 0)
    {
        return;
    }

    if (work->f24EC != 0)
    {
        switch (work->f24AC)
        {
            case 0:
                title_open_800C4AD0(work, 0, 0);
                break;

            case 1:
                title_open_800C4AD0(work, 1, 0x6739);
                break;

            case 2:
                title_open_800C4AD0(work, 2, 0);
                break;

            case 3:
                title_open_800C4AD0(work, 3, 0);
                break;

            case 5:
                title_open_800C4AD0(work, 5, 0x6739);
                break;
        }
    }
}
```

#### 5. Iterate Until It Matches

decomp.me will show you a diff between your C and the assembly.

**Common issues to fix**:
- Wrong variable types (int vs short vs char)
- Wrong switch case values
- Missing or extra breaks
- Wrong operator precedence

**Goal**: 🟢 GREEN DIFF (100% match)

#### 6. When Matched: Integrate!

Once you have a 100% match:

1. **Open the file**:
```bash
code ~/development-workspace/mgs_reversing/source/overlays/title/onoda/open/open.c
```

2. **Go to line 1263**:
Find: `#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2374.s")`

3. **Replace with your C code**:
```c
void title_open_800D2374(OpenWork *work)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->f24BC != 0)
    {
        return;
    }

    if (work->f24EC != 0)
    {
        switch (work->f24AC)
        {
            case 0:
                title_open_800C4AD0(work, 0, 0);
                break;

            case 1:
                title_open_800C4AD0(work, 1, 0x6739);
                break;

            case 2:
                title_open_800C4AD0(work, 2, 0);
                break;

            case 3:
                title_open_800C4AD0(work, 3, 0);
                break;

            case 5:
                title_open_800C4AD0(work, 5, 0x6739);
                break;
        }
    }
}
```

4. **Delete the .s file** (optional, for cleanliness):
```bash
rm ~/development-workspace/mgs_reversing/asm/overlays/title/title_open_800D2374.s
```

#### 7. Test the Build

```bash
cd ~/development-workspace/mgs_reversing/build

# Install Wine first if you haven't:
# brew install --cask --no-quarantine wine-stable

# Build
python3 build.py --variant=dev_exe
```

If it builds successfully and matches, **YOU DID IT!** 🎉

#### 8. Celebrate and Continue!

You just decompiled your first MGS function!

**Next targets** (in order of difficulty):
1. `title_open_800CE378.s` - 81 lines
2. `title_open_800D1B74.s` - 85 lines
3. `option` overlay - just 1 file!
4. Continue with `title` overlay - 18 files total

## 📁 Important Files Reference

| File | Purpose |
|------|---------|
| `DEVELOPMENT_PLAN.md` | Complete roadmap and timeline |
| `QUICK_START.md` | Quick reference commands |
| `FIRST_FUNCTION_ANALYSIS.md` | Detailed analysis of target function |
| `convert_asm.py` | Tool to prepare assembly for decomp.me |
| `source/overlays/title/onoda/open/open.c` | Where to integrate your code |
| `asm/overlays/title/title_open_800D2374.s` | Original assembly file |

## 🎓 Learning Resources

- **decomp.me preset**: https://decomp.me/preset/19
- **Discord**: https://discord.gg/tTvhQ8w (#metal_gear_dev)
- **Project README**: `README.md`

## 💡 Pro Tips

1. **Start Small**: Don't jump to the 399-file overlays yet!
2. **Study Examples**: Look at already-decompiled functions
3. **Use decomp.me**: It's your best friend
4. **Ask for Help**: Discord community is friendly
5. **Take Breaks**: Decompilation is mentally demanding
6. **Celebrate Progress**: Every function counts!

## 🚨 Common Issues

### Build fails with "Permission denied" on .exe files
**Solution**: Install Wine
```bash
brew install --cask --no-quarantine wine-stable
```

### Can't match the assembly
**Solution**:
- Check variable types (int vs short vs char)
- Look at similar functions for patterns
- Ask on Discord for hints

### Don't know what a function does
**Solution**:
- Look at where it's called in the code
- Study similar function names
- Read the assembly carefully

## 🎯 Success Metrics

You'll know you're making progress when:
- ✅ Wine builds successfully
- ✅ You match your first function on decomp.me
- ✅ Integration builds without errors
- ✅ You understand the workflow end-to-end

## 🚀 Ready?

**Your command to start**:

```bash
# 1. Install Wine
brew install --cask --no-quarantine wine-stable

# 2. Convert assembly
cd ~/development-workspace/mgs_reversing/build
python3 convert_asm.py ../asm/overlays/title/title_open_800D2374.s

# 3. Copy the output and go to https://decomp.me/

# 4. Start matching!
```

**Let's preserve gaming history, one function at a time!** 🎮🐍

---

*Remember: The MGS community spent years on this project. Every contribution matters!*
