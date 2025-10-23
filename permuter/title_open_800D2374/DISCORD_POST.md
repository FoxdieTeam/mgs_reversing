# Discord Community Help Request

**Channel**: #mgs-reversing (primary) or #decompilation

---

## Title
**91.36% match on MGS title_open function - need help with final 8.64%**

## Message Body

Hey everyone! 👋

I'm working on decompiling `title_open_800D2374` from **Metal Gear Solid PS1** (title overlay).
Made great progress but **stuck at 510 @ 91.36% matching** and need some expert PS1 insights!

### 🔗 Links
- **decomp.me scratch**: https://decomp.me/scratch/F1WN5
- **Compiler**: PSYQ 4.4 (gcc 2.8.1 + aspsx 2.79)
- **Flags**: `-O2 -Wall -G8`
- **Platform**: PlayStation 1 (MGS overlays)

### 📊 Current Status
- **Score**: 510 (91.36% matching)
- **Progress**: Started at 4020 → 825 → **510** (major breakthrough removing permuter optimization)
- **Remaining gap**: ~44 Levenshtein distance points

### 🔍 Main Remaining Differences

Looking at the assembly diff on decomp.me:

1. **Line 0x48**: Register allocation difference
   - **Target**: `lw a0, 0x24b4(s1)` ← uses `a0` for return value!
   - **Current**: `lw v0, 0x24b4(s1)` ← standard `v0` return register
   - **Question**: Why would PSYQ use `a0` instead of `v0` for loading return value here?

2. **Line 0x60**: Extra instruction inserted
   - **Target**: (no instruction)
   - **Current**: `move v0, s1`
   - **Question**: How to eliminate this extra register move?

3. **Lines 0x70, 0x74, 0x78, 0x98, 0xb4**: Jump table/branch differences
   - Minor address resolution differences in switch jump table
   - Branches using symbolic vs hardcoded addresses

### 🧪 What I've Already Tried

**Systematic C code variations (all stayed at 510)**:
1. ✅ Explicit return temporary variable pattern
2. ✅ Inline conditional (single-line if-return)
3. ✅ Const qualifier for cached field access
4. ✅ Explicit switch expression variable

**Struct configuration**:
- Using simplified struct with padding for only accessed fields
- Tested FoxdieTeam's complete 137-line struct → made it worse (840 vs 510)

**Compiler flags**:
- Confirmed `-G8` is critical for MGS overlays
- Tested multiple PSYQ versions (4.3 and 4.4) - same result

### 🎯 Specific Questions

1. **Register allocation**: Is there a C pattern that would make PSYQ gcc 2.8.1 use `a0` instead of `v0` for early return values?

2. **Extra move elimination**: The `move v0, s1` at line 0x60 - is this related to delay slot filling or branch optimization?

3. **Switch jump table**: Any known PSYQ quirks with switch statement generation that affect jump table address calculations?

### 📝 Function Context

```c
OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;

  // Loop through 24 calls
  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  // Early return if flag set
  if (work->f24BC != 0)
  {
    return work->f24B4;  // ← This becomes "lw v0" but target has "lw a0"
  }

  // Switch statement based on another field
  if (work->f24EC != 0)
  {
    switch (work->f24AC)
    {
      case 0: ... case 10:  // 11 cases total
        // Various function calls and returns
    }
  }
  return work;
}
```

### 🙏 Any Help Appreciated!

- Have you seen PSYQ generate `lw a0` for return values in similar contexts?
- Any suggestions on C patterns that might affect register allocation this way?
- Should I try different struct member ordering or packing?
- Are there PSYQ-specific pragmas or attributes worth trying?

This would be the **first matched function in title overlay** for FoxdieTeam's MGS reversing project, so getting this 100% would be huge! 🎯

Thanks in advance for any insights! 🙏

---

**Note**: I have multiple 8 permuter instances running in background, but after 4 systematic manual variations, I think this needs human expertise more than brute-force permutation.
