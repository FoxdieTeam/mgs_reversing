# PSYQ gcc 2.8.1 Pattern Application Guide

**Status**: Framework documented from title_open_800CE378 breakthrough (94.74% match)
**Discovery Date**: 2025-10-20
**Patterns Validated**: 3 major patterns discovered through systematic testing

## Quick Reference: The Three Patterns

### Pattern 1: Pointer Arithmetic ⭐ High Impact
```c
// ✅ PSYQ gcc PREFERS this
RGBElement *elem = (RGBElement *)((char *)work + BASE_OFFSET);
elem += index;

// ❌ Less optimal (different register allocation)
RGBElement *base = (RGBElement *)((char *)work + BASE_OFFSET);
RGBElement *elem = &base[index];
```
**Impact**: Changes register allocation significantly
**Testing**: Variation 4 improved 730 → 600 (92.11%) with this pattern
**Detection**: Look for array indexing patterns in assembly

---

### Pattern 2: Descriptive Variable Naming ⭐ Medium Impact
```c
// ✅ Better register allocation
int shade = work->color_field;
process_color(shade);

// ❌ Generic names may not match compiler's preference
int temp = work->color_field;
process_color(temp);
```
**Impact**: Affects register allocation decisions in PSYQ gcc
**Testing**: Part of Variation 4 improvement
**Detection**: Look for generic variable names (temp, val, x, y) that could be more descriptive

---

### Pattern 3: Struct Field Re-reading ⭐⭐ Highest Impact
```c
// ✅ PSYQ gcc STRONGLY PREFERS fresh loads in conditionals
int value = work->field;
use_value(value);
if (work->field >= THRESHOLD)  // Re-read the field!
{
    work->state = NEXT_STATE;
}

// ❌ Even though semantically identical, doesn't match assembly
int value = work->field;
use_value(value);
if (value >= THRESHOLD)  // Using cached variable
{
    work->state = NEXT_STATE;
}
```
**Impact**: Single pattern can improve 600 → 400 (92.11% → 94.74%, +2.63%)
**Testing**: Variation 5 discovered this pattern through assembly analysis
**Detection**: Compare assembly - look for extra `lw` (load word) instructions in target

---

## Application Checklist

### Step 1: Identify Candidates ✅
- [ ] Function uses struct pointer parameters
- [ ] Function performs array/pointer arithmetic
- [ ] Function has conditional checks on struct fields
- [ ] Function size < 500 lines assembly (easier to match)
- [ ] Similar function exists in adjacent decompiled code

**Good Candidates**: Functions manipulating RGB, colors, or dynamic data

---

### Step 2: Initial Analysis 📊
- [ ] Extract assembly: `python3 build/decompme_asm.py asm/overlays/<overlay>/<func>.s`
- [ ] Study adjacent decompiled functions for patterns
- [ ] Check struct definitions in source files
- [ ] Identify pointer arithmetic and conditional patterns

---

### Step 3: First Attempt (Baseline) 📝
Create initial decompilation using:
1. **Pointer Arithmetic**: Look for patterns like `elem += index` in similar functions
2. **Descriptive Naming**: Use field-related names when caching values
3. **Conservative Conditionals**: Start with re-reading fields rather than using cached values

```c
// Template for RGB color manipulation functions
void color_function(OpenWork *work, int index)
{
    RGBElement *elem;
    int shade;  // Descriptive name, not "temp"

    // Pattern 1: Pointer arithmetic
    elem = (RGBElement *)((char *)work + BASE_OFFSET);
    elem += index;

    switch (work->state_field)
    {
        case 0:
            if (work->threshold_field >= VALUE)
            {
                work->state_field = 1;
                work->counter_field = 0;
            }
            break;
        case 1:
            shade = work->threshold_field;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            // Pattern 3: Re-read field in conditional
            if (work->threshold_field >= NEXT_VALUE)
            {
                work->state_field = 2;
            }
            break;
        // ... more cases following Pattern 3
    }
}
```

---

### Step 4: Test on decomp.me 🧪

1. **Get baseline score**
   - Paste initial attempt
   - Record score (if worse than 90%, need bigger changes)

2. **Analyze differences** (if not 100% match)
   - Check register allocation (a0, a1, a2, v0)
   - Look for extra instructions in target
   - Compare conditional generation

3. **Apply variations systematically**
   - Variation A: Remove re-read patterns, use cached values
   - Variation B: Try different pointer arithmetic styles
   - Variation C: Adjust variable naming

---

### Step 5: Documentation 📋

Create `TEST_RESULTS.md` documenting:
```markdown
| Variation | Score | Match % | Key Change | Status |
|-----------|-------|---------|-----------|--------|
| Variation 1 (patterns)  | XXX | XX% | Applied patterns | ⏳ Testing |
| Variation 1A (no reread)  | XXX | XX% | Removed Pattern 3 | ⏳ Testing |
```

---

## Assembly Pattern Recognition

### Look for these in target assembly

**Pattern 1 indicators** (Pointer Arithmetic):
```assembly
addiu a2, a0, 0x18c    ; Base + offset
addu a2, a2, v0        ; Add index
```

**Pattern 3 indicators** (Field Re-reading):
```assembly
lw v0, 0x178(a0)       ; Load field
# ... use v0 ...
lw v1, 0x178(a0)       ; Re-load same field (indicates re-read pattern)
slt v0, v1, a1         ; Compare
```

---

## Success Metrics

✅ **Excellent** (< 400 score, > 94%)
- All three patterns successfully applied
- Only linker/compiler-level differences remain

✅ **Good** (400-700 score, 90-94%)
- Two patterns successfully applied
- Register allocation mostly matches

⚠️ **Needs Work** (> 700 score, < 90%)
- Single pattern may apply
- Need more systematic analysis
- Consider studying more adjacent decompiled functions

---

## Common Pitfalls

❌ **Don't assume all functions follow same pattern**
- If function has different register usage, patterns may not apply
- Always check assembly differences carefully

❌ **Don't mix pointer arithmetic and array indexing**
- Consistency matters to PSYQ gcc
- If one part uses `+=`, maintain throughout

❌ **Don't add Pattern 3 everywhere blindly**
- Only re-read fields immediately before conditionals
- Re-reading in the middle of calculations breaks things

✅ **DO study adjacent decompiled code first**
- Similar functions = similar patterns
- The team's existing code shows what works

✅ **DO create separate variations**
- Test each pattern independently
- Document what each change affects

---

## Next Candidates in Priority Order

| Function | Size | Reason | Expected Impact |
|----------|------|--------|-----------------|
| title_open_800CDBF8 | 152 lines | Smallest, likely similar pattern | High |
| title_open_800CD800 | 216 lines | Similar RGB manipulation | High |
| title_open_800CDE44 | 338 lines | Sequence suggests similar pattern | High |
| title_open_800CD3B8 | 7.0K | Medium size, good for learning | Medium |
| title_open_800CEB14 | 20K | Larger, save for later | Medium |

---

## Long-term Strategy

1. **Phase 1** (Current): Apply patterns to RGB manipulation functions
   - Target: title_open_800CDBF8, title_open_800CD800, title_open_800CDE44
   - Expected: 92-95% match rates on 2-3 functions

2. **Phase 2**: Extend patterns to other overlays
   - Look for similar functions in camera, option overlays
   - Adapt patterns for different struct layouts

3. **Phase 3**: Build pattern library
   - Document per-function pattern variations
   - Create reusable decompilation templates

4. **Phase 4**: Tackle remaining functions
   - Functions that don't follow standard patterns
   - Use accumulated knowledge for custom optimizations

---

## Resources

- **Case Study**: `permuter/title_open_800CE378/`
- **Pattern Discovery**: `permuter/title_open_800CE378/TEST_RESULTS.md`
- **Implementation**: `permuter/title_open_800CE378/BEST_CODE_400.txt`
- **Developer Guide**: `CLAUDE.md`

## Key Insight

> **Pattern 3 (Struct Field Re-reading) is the pattern with the highest impact.** Even small functions can achieve 94%+ match by systematically applying this pattern. The pattern appears to be an intrinsic PSYQ gcc 2.8.1 optimization preference that can't be explained by standard compiler theory - it's a quirk specific to this toolchain.

---

*Last Updated: 2025-10-20*
*Author: Systematic Analysis of title_open_800CE378*
