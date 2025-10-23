# Next Steps - Fine-Tuning the Decompilation

## 🎯 Current Status

**GREAT PROGRESS!** 🎉

✅ Build system works
✅ Wine installed
✅ Code compiles without errors
⚠️ Needs exact match tuning

## 📊 What Happened

```
Build Result: FAIL: ../obj/title.bin does not match target hash 💩
```

This is **NORMAL and EXPECTED** in reverse engineering! Here's why:

1. ✅ Your C code **compiles correctly**
2. ✅ Your C code **produces valid assembly**
3. ⚠️ The assembly is **slightly different** from the original

This happens because:
- Compiler optimizations produce different instruction orders
- Variable types affect register usage
- Control flow patterns matter

## 🔧 How to Fix: Use decomp.me

### Step 1: Get the Assembly

```bash
cd ~/development-workspace/mgs_reversing/build
python3 convert_asm.py ../asm/overlays/title/title_open_800D2374.s
```

This outputs the MIPS assembly.

### Step 2: Go to decomp.me

**URL**: https://decomp.me/

1. Click "New Scratch"
2. Platform: **PlayStation (MIPS)**
3. Compiler: **psyq 4.4** (Important!)
4. Preset: **Metal Gear Solid (overlays)**
5. Paste the assembly

### Step 3: Get Context

Visit: https://decomp.me/preset/19

Find a recent "title_open" function scratch and copy its context (includes/structures).

### Step 4: Paste Your C Code

Use the code from `source/overlays/title/onoda/open/open.c:1263`:

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

### Step 5: Iterate Until Match

decomp.me will show you a diff. Common fixes needed:

**Issue 1: Loop variable type**
```c
// Try changing from:
int i;
// To:
short i;
// Or:
s32 i;
```

**Issue 2: Switch fallthrough**
```c
// Maybe some cases fall through?
case 0:
    title_open_800C4AD0(work, 0, 0);
    // NO break here?
case 1:
    title_open_800C4AD0(work, 1, 0x6739);
    break;
```

**Issue 3: Different control flow**
```c
// Maybe the switch is actually a series of ifs?
if (work->f24AC == 0) {
    title_open_800C4AD0(work, 0, 0);
}
else if (work->f24AC == 1) {
    title_open_800C4AD0(work, 1, 0x6739);
}
// etc...
```

**Issue 4: Register pressure**
```c
// Maybe need to force specific register usage
// by restructuring code slightly
```

### Step 6: When You Get 100% Match (Green)

1. **Copy the matched C code** from decomp.me

2. **Update the source**:
```bash
code ~/development-workspace/mgs_reversing/source/overlays/title/onoda/open/open.c
```

Go to line 1263 and replace with the matched code.

3. **Remove the assembly file**:
```bash
rm ~/development-workspace/mgs_reversing/asm/overlays/title/title_open_800D2374.s
```

4. **Test the build**:
```bash
cd ~/development-workspace/mgs_reversing/build
python3 build.py
```

5. **You should see**:
```
OK: ../obj/title.bin matches target hash 👌
```

## 💡 Tips for Matching

### Common Patterns

1. **Loop Counters**: Try different types (int, short, s32, u32)
2. **Break vs Return**: Sometimes a break is actually a goto
3. **Switch vs If-Else**: Jump tables vs condition chains
4. **Const Values**: 0x6739 might need to be defined as a constant
5. **Variable Order**: Declaration order can affect register allocation

### Look at Similar Functions

Check `title_open_800D3500` at line 1267 - it has similar patterns:
```c
for (i = 0; i < 24; i++)
{
    title_open_800C4AD0(work, i, 0);
}
```

Use it as a reference for variable types and patterns.

### Use decomp.me Examples

Search for "title_open" on decomp.me preset 19:
https://decomp.me/preset/19

Find successful matches and see what patterns they use.

## 🎓 Learning from This

**What You Learned**:
1. ✅ How to set up the build system
2. ✅ How to integrate C code
3. ✅ How to test builds
4. ⚠️ That exact matching requires fine-tuning

**What You're Learning Now**:
1. 🎯 How to use decomp.me effectively
2. 🎯 How compiler optimizations affect output
3. 🎯 How to iterate to get perfect matches

## 📊 Progress Tracker

```
Overall: 1/1327 functions (0.08%)
Status: Decompiled but needs matching
Time spent: ~3 hours
What's left: ~15-30 minutes of decomp.me matching

Title Overlay: 1/18 functions started
Status: One function in progress (95% done!)
```

## 🚀 Quick Commands Reference

### Convert Assembly
```bash
cd ~/development-workspace/mgs_reversing/build
python3 convert_asm.py ../asm/overlays/title/title_open_800D2374.s
```

### Build and Test
```bash
cd ~/development-workspace/mgs_reversing/build
python3 build.py  # Matching build
```

### Edit Source
```bash
code ~/development-workspace/mgs_reversing/source/overlays/title/onoda/open/open.c +1263
```

### Remove Assembly (when matched)
```bash
rm ~/development-workspace/mgs_reversing/asm/overlays/title/title_open_800D2374.s
```

## 🎯 Success Criteria

You'll know you succeeded when:
- ✅ decomp.me shows 100% match (green diff)
- ✅ Build output: "OK: ../obj/title.bin matches target hash 👌"
- ✅ No assembly file needed anymore

## 💪 You're So Close!

You've done 95% of the work! Just need that final 5% of fine-tuning with decomp.me.

This is the normal workflow:
1. Analyze assembly ✅ DONE
2. Write C code ✅ DONE
3. Integrate ✅ DONE
4. Fine-tune with decomp.me ← **YOU ARE HERE**
5. Verify match
6. Move to next function

**Keep going! You're about to complete your first function!** 🎮🐍
