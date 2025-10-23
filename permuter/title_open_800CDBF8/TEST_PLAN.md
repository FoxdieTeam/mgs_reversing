# title_open_800CDBF8 Testing Plan

## Baseline Setup

**Target Assembly**: title_open_800CDBF8.s (152 instructions)
**Base Function**: Similar to title_open_800CE378 but unknown exact structure
**Testing Platform**: decomp.me
**Compiler Settings**: PSX, psyq 4.4, -O2 -g0 -c

## Test Sequence

### Test 1: Baseline Conservative (START HERE)
**File**: `baseline.c`
**Patterns Applied**: None (conservative structure)
**Hypothesis**: Generic RGB manipulation similar to CE378
**What to do**:
1. Copy baseline.c contents
2. Go to https://decomp.me/
3. Create new scratch or use existing MGS preset
4. Paste baseline.c code
5. **Record score**: ___________
6. **Record match %**: ___________

**Expected Result**: Likely 85-92% if structure matches, higher if exact

---

### Test 2: Apply Pattern 1 (Pointer Arithmetic)
**File**: `variation1_discovered_patterns.c` (already created)
**Key Change**: Pointer arithmetic `elem += index` instead of `&base[index]`
**Hypothesis**: Should improve register allocation if function is similar to CE378
**What to do**:
1. Copy variation1_discovered_patterns.c
2. Paste to decomp.me
3. **Record score**: ___________
4. **Compare to baseline**: Better / Same / Worse?

**Decision Point**:
- ✅ If improves: Pattern 1 works for this function!
- ⚖️ If same: Try next variation
- ❌ If worse: Revert, try different approach

---

### Test 3: Pattern 3 Deep Dive (If needed)
**File**: To be created based on assembly analysis
**Key Change**: Re-read struct fields in conditionals
**Why**: Pattern 3 had highest impact on CE378 (+2.63%)
**What to do**:
1. Only if Test 2 doesn't improve much
2. Analyze assembly for re-read patterns
3. Apply Pattern 3 to conditionals
4. Test and record

---

## Documentation Template

For each test, fill in:

```
## Test X: [Variation Name]

**Baseline Score**: [from previous test]
**This Variation Score**: [new score]
**Difference**: [improvement or regression]
**Key Changes**: [what changed in code]
**Analysis**: [why did this happen?]
**Status**: ✅ Improvement / ⚖️ No Change / ❌ Regression
```

---

## Quick Reference: What to Copy for decomp.me

### Baseline
```c
// Copy the entire content of baseline.c to decomp.me
```

### Variation 1
```c
// Copy the entire content of variation1_discovered_patterns.c to decomp.me
```

---

## Success Criteria

- ✅ **Excellent**: < 500 score (> 93%)
- ✅ **Good**: 500-700 score (90-93%)
- ⚠️ **Fair**: 700-900 score (88-90%)
- ❌ **Needs Work**: > 900 score (< 88%)

---

## If It's Difficult

If baseline doesn't match well (> 800 score):

1. **Check assembly for unique patterns**:
   - Look for loops instead of switch
   - Check for different struct offsets
   - Find function calls and their purpose

2. **This might be a completely different function type**:
   - May not be RGB manipulation
   - May have different state machine
   - May use different struct layout

3. **Action**: Create ASSEMBLY_ANALYSIS.md documenting what we found

---

## Time Estimate

- Baseline test: 5 minutes
- Variation 1 test: 5 minutes
- Analysis & iteration: 10-20 minutes
- Total: 20-30 minutes to get first result

---

## Next Functions Queue (if this succeeds)

1. ✅ title_open_800CDBF8 (152 lines) - CURRENT
2. ⏳ title_open_800CD800 (216 lines)
3. ⏳ title_open_800CDE44 (338 lines)
4. ⏳ title_open_800CD3B8 (7.0K)

---

## Recording Results

After testing, update this file with actual scores:

| Function | Baseline | Var 1 | Var 2 | Best | Status |
|----------|----------|-------|-------|------|--------|
| CDBF8 | ? | ? | ? | ? | Testing |
| CD800 | - | - | - | - | Queued |
| CDE44 | - | - | - | - | Queued |

