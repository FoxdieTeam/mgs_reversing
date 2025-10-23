# First Function Decompilation: title_open_800D2374

## 📊 Function Analysis

**Location**: `asm/overlays/title/title_open_800D2374.s`
**Target file**: `source/overlays/title/onoda/open/open.c:1263`
**Size**: 59 instructions (~236 bytes)
**Difficulty**: ⭐⭐ Medium (loop + switch/if statements)

## 🔍 Assembly Analysis

### Function Structure

```c
// Pseudo-code from assembly analysis:
void title_open_800D2374(OpenWork *work)
{
    int i;

    // Loop: initialize 24 elements
    for (i = 0; i < 24; i++) {
        title_open_800C4AD0(work, i, 0);
    }

    // Conditional checks
    if (work->f24BC != 0) {
        // Do something with work->f24B4
        return;
    }

    if (work->f24EC != 0) {
        // Switch on work->f24AC (values 0-10)
        switch (work->f24AC) {
            case 0:
                title_open_800C4AD0(work, ?, 0);
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
            case ?:
                title_open_800C4AD0(work, 5, 0x6739);
                break;
        }
    }
}
```

### Key Instructions

1. **Loop (lines 3-10)**:
```mips
  move $s0, $zero              # i = 0
loop:
  jal 0x800c4ad0               # call title_open_800C4AD0
  move $a2, $zero              # a2 = 0 (color)
  addiu $s0, $s0, 1            # i++
  slti $v0, $s0, 0x18          # i < 24?
  bnez $v0, loop               # if yes, continue loop
```

2. **First conditional (lines 11-15)**:
```mips
  lw $v0, 0x24bc($s1)          # load work->f24BC
  beqz $v0, else_block         # if == 0, skip
  lw $a0, 0x24b4($s1)          # load work->f24B4
  j return                      # jump to return
```

3. **Switch table (lines 16-26)**:
```mips
  lw $v0, 0x24ec($s1)          # load work->f24EC
  beqz $v0, return             # if == 0, return
  lw $v1, 0x24ac($s1)          # load work->f24AC (switch value)
  sltiu $v0, $v1, 0xb          # check < 11
  beqz $v0, return             # if >= 11, return
  lui $v0, 0x800e
  addiu $v0, $v0, -0x7330      # address of jump table
  sll $v1, $v1, 2              # index * 4
  addu $v1, $v1, $v0           # table + offset
  lw $v0, ($v1)                # load jump address
  jr $v0                        # jump to case
```

4. **Case handlers (lines 27-46)**:
```mips
case_0:
  move $a0, $s1
  j end_switch
  move $a1, $zero

case_1:
  move $a0, $s1
  addiu $a1, $zero, 1
  jal 0x800c4ad0
  addiu $a2, $zero, 0x6739     # color = 0x6739

case_2:
  move $a0, $s1
  j end_switch
  addiu $a1, $zero, 2

case_3:
  move $a0, $s1
  j end_switch
  addiu $a1, $zero, 3

case_x:
  move $a0, $s1
  addiu $a1, $zero, 5
  jal 0x800c4ad0
  addiu $a2, $zero, 0x6739
```

## 📝 OpenWork Structure Fields

From assembly analysis, we can see these fields are accessed:

```c
struct OpenWork {
    // ... other fields ...
    int f24AC;  // offset 0x24AC - switch value
    int f24B4;  // offset 0x24B4 - used in first conditional
    int f24BC;  // offset 0x24BC - first condition check
    int f24EC;  // offset 0x24EC - second condition check
    // ... other fields ...
};
```

## 🎯 Comparing with Similar Function

The already-decompiled `title_open_800D3500` at line 1267:

```c
void title_open_800D3500(OpenWork *work, int arg1)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->fA74 >= 18 && work->fA74 <= 19)
    {
        title_open_800C4AD0(work, 21, 0x6739);

        MENU_Locate(54, 60, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf(title_aMemorycardslot_800D8FAC);

        if (work->f24F0 == 3)
        {
            // ...
        }
    }
}
```

**Similarities**:
- Both have a `for (i = 0; i < 24; i++)` loop
- Both call `title_open_800C4AD0(work, i, 0)`
- Both use color `0x6739` in some calls
- Both check conditions on work fields

## 💡 Proposed C Implementation

Based on the assembly analysis:

```c
void title_open_800D2374(OpenWork *work)
{
    int i;

    // Initialize 24 elements
    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    // First conditional
    if (work->f24BC != 0)
    {
        // Not sure what happens here - assembly shows:
        // lw $a0, 0x24b4($s1)
        // j return
        // Possibly just early return?
        return;
    }

    // Second conditional with switch
    if (work->f24EC != 0)
    {
        // Switch on work->f24AC (0-10)
        switch (work->f24AC)
        {
            case 0:
                title_open_800C4AD0(work, 0, 0);  // Guess: index 0
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

            // case 4? Unknown - goes to case with index 5

            case 5:  // Or maybe case 4?
                title_open_800C4AD0(work, 5, 0x6739);
                break;
        }
    }
}
```

## ❓ Uncertainties

1. **Field names**: f24AC, f24B4, f24BC, f24EC - need to check if better names exist
2. **First conditional**: What does `lw $a0, 0x24b4($s1)` before return mean?
3. **Switch cases**: The jump table makes it hard to know exact case values without seeing the table at 0x800e8cd0
4. **Missing cases**: There seem to be only 5 case handlers visible, but check is `< 11`

## 🚀 Next Steps

1. **Go to decomp.me**: https://decomp.me/
   - Create new scratch
   - Select preset: "Metal Gear Solid (overlays)"
   - Paste the assembly from convert_asm.py output

2. **Choose context**: Use context from https://decomp.me/preset/19
   - Look for similar "title_open" functions
   - Copy headers/includes

3. **Iterative matching**:
   - Start with the C code above
   - Adjust types (int vs short vs char)
   - Fix switch cases based on diff output
   - Match the assembly exactly

4. **Integration**:
   - Once matched, replace line 1263 in `source/overlays/title/onoda/open/open.c`
   - Change from: `#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2374.s")`
   - Change to: Your C code
   - Test build: `python3 build.py --variant=dev_exe`

## 📚 Useful References

- **Helper function**: `title_open_800C4AD0` at line 241
- **Similar function**: `title_open_800D3500` at line 1267
- **OpenWork struct**: Defined at line 30
- **decomp.me scratches**: https://decomp.me/preset/19

Good luck! This is a perfect first function to learn the workflow! 🎮
