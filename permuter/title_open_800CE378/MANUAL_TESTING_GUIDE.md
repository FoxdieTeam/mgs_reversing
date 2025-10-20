# Manual Testing Guide - Reaching 100% Match

**Current Best**: 730 score @ 90.39% match (base.c)
**Goal**: 0 score @ 100% match
**Gap to Close**: 9.61% (~730 points)

## Testing Procedure on decomp.me

### Setup
1. Open https://decomp.me/scratch/c4GoH in your browser
2. The scratch already has the correct compiler settings:
   - Platform: PSX
   - Compiler: psyq 4.4
   - Compiler flags: `-O2 -g0 -c`
   - Target assembly: title_open_800CE378.s

### Test Sequence

#### Test 1: Variation 1 - Combined Pointer Calculation

**File**: `variation_1_combined_pointer.c`

**Change from base.c**:
```c
// OLD (base.c):
RGBElement *base = (RGBElement *)((char *)work + 0x18C);
RGBElement *elem = &base[index];

// NEW (variation 1):
RGBElement *elem = (RGBElement *)((char *)work + 0x18C) + index;
```

**Steps**:
1. Copy contents of `variation_1_combined_pointer.c`
2. Paste into decomp.me code editor
3. Wait for compilation and scoring
4. Record score: ___________
5. Note: Did it improve? Yes / No

**Expected**: May change pointer arithmetic sequence, affecting register allocation

---

#### Test 2: Variation 2 - Scoped temp Variables

**File**: `variation_2_temp_in_case.c`

**Change from base.c**:
```c
// OLD (base.c):
int temp;
switch (work->fA8C) {
    case 1:
        temp = work->f178;
        // ...

// NEW (variation 2):
switch (work->fA8C) {
    case 1:
    {
        int temp = work->f178;  // Scoped inside case
        // ...
    }
```

**Steps**:
1. Copy contents of `variation_2_temp_in_case.c`
2. Paste into decomp.me code editor
3. Wait for compilation and scoring
4. Record score: ___________
5. Note: Did it improve? Yes / No

**Expected**: Variable scope affects register lifetime and allocation patterns

---

#### Test 3: Variation 3 - Register Allocation Hints

**File**: `variation_3_register_hints.c`

**Change from base.c**:
```c
// OLD (base.c):
RGBElement *base = (RGBElement *)((char *)work + 0x18C);

// NEW (variation 3):
#ifdef __GNUC__
  register RGBElement *r_base __asm__("$4");  // Force a0 register
  r_base = (RGBElement *)((char *)work + 0x18C);
  base = r_base;
#else
  base = (RGBElement *)((char *)work + 0x18C);
#endif
```

**Steps**:
1. Copy contents of `variation_3_register_hints.c`
2. Paste into decomp.me code editor
3. Wait for compilation and scoring
4. Record score: ___________
5. Note: Did it improve? Yes / No

**Expected**: Inline asm register hints may align with PSYQ compiler's natural allocation

---

## Analysis

### Score Interpretation

| Score Range | Match % | Status |
|-------------|---------|--------|
| 730 | 90.39% | Current best (base.c) |
| 700-729 | 90.5-90.4% | Minor improvement |
| 500-699 | 91-93% | Significant improvement |
| 1-499 | 93-99% | Major improvement |
| 0 | 100% | **PERFECT MATCH!** ✨ |

### What to Look For

**In the diff view on decomp.me**, examine:
1. **Register differences**: Is elem in a2 or a1?
2. **Pointer arithmetic**: How is `work + 0x18C + (index * 40)` calculated?
3. **Control flow**: Jump table structure, branch patterns
4. **Delay slots**: nop placement, instruction reordering

### Next Steps Based on Results

#### If ONE variation improves:
- Use that as new base.c
- Try combining with patterns from other variations
- Continue iterative refinement

#### If MULTIPLE variations improve:
- Identify which aspects of each helped
- Create hybrid variation combining winning patterns
- Test hybrid

#### If NONE improve (all ≥ 730):
- 90.39% may be the practical limit for manual decompilation
- The remaining 9.6% may require:
  1. Permuter with corrected target.o (once binary format issue is solved)
  2. Deeper assembly analysis to identify exact compiler quirks
  3. Accepting 90.39% as excellent result and moving to next function

### Additional Variations to Try (if needed)

**Variation 4 - Pointer Arithmetic Order**:
```c
// Try different multiplication pattern
RGBElement *elem = (RGBElement *)(((unsigned int)work) + 0x18C + (index * 40));
```

**Variation 5 - Explicit unsigned**:
```c
// Cast work to unsigned int first
unsigned int base_addr = (unsigned int)work + 0x18C;
RGBElement *elem = (RGBElement *)(base_addr + (index * 40));
```

**Variation 6 - Direct offset calculation**:
```c
// Manual calculation matching assembly pattern:
// sll v0,a1,0x2 → index * 4
// addu v0,v0,a1 → (index * 4) + index = index * 5
// sll v0,v0,0x3 → (index * 5) * 8 = index * 40
int offset = ((index << 2) + index) << 3;
RGBElement *elem = (RGBElement *)((char *)work + 0x18C + offset);
```

## Recording Results

Create `TEST_RESULTS.md` with:

```markdown
# Variation Test Results

| Variation | Score | Match % | Improved? | Notes |
|-----------|-------|---------|-----------|-------|
| Base (current) | 730 | 90.39% | - | Starting point |
| Variation 1 | ___ | ___% | Yes/No | Combined pointer |
| Variation 2 | ___ | ___% | Yes/No | Scoped temps |
| Variation 3 | ___ | ___% | Yes/No | Register hints |

## Best Result
- **Winning variation**: ___________
- **Final score**: ___________
- **Match percentage**: ___________

## Next Actions
[Describe what to do next based on results]
```

## Tips

1. **Wait for compilation**: decomp.me can take 10-20 seconds per compilation
2. **Check for errors**: Red error messages mean syntax/compile issues
3. **Compare assembly**: Use the side-by-side diff view to see differences
4. **Save winners**: Create new scratch or save winning code locally
5. **Document patterns**: Note which patterns helped for future functions

Good luck reaching 100%! 🎯
