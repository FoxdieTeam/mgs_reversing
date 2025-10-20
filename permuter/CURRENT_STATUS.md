# MGS Decompilation - Current Status

**Updated**: 2025-10-20

## Function 1: title_open_800D2374 ✅ Good Progress

**Location**: `asm/overlays/title/title_open_800D2374.s`
**Permuter directory**: `permuter/title_open_800D2374/`

### Scores
- **Base score**: 4020
- **Best permuter**: 3635 (output-3635-1 and output-3635-2)
- **Improvement**: 385 points (9.6% better)
- **Match percentage**: ~91%

### Status
- ✅ Permuter has explored and found improvements
- ✅ Two variations at 3635 score available
- ✅ Ready for manual review and potential combination of patterns

### Next Steps
1. Review `output-3635-1/source.c` and `output-3635-2/source.c`
2. Test both on decomp.me to verify scores
3. Identify which patterns helped
4. Potentially combine winning patterns for further improvement

---

## Function 2: title_open_800CE378 🎯 Ready to Push to 100%

**Location**: `asm/overlays/title/title_open_800CE378.s`
**Permuter directory**: `permuter/title_open_800CE378/`

### Scores
- **Verified best**: 730 @ 90.39% match (decomp.me verified) ✅
- **Target**: 0 @ 100% match
- **Gap to close**: 730 points (~9.6%)

### Status
- ✅ Correct target.o extracted (304 bytes)
- ✅ 3 manual variations ready to test
- ✅ Comprehensive testing guide created
- ⏳ Ready for manual testing on decomp.me

### Variations Ready
1. **variation_1_combined_pointer.c** - Single-statement pointer arithmetic
2. **variation_2_temp_in_case.c** - Scoped temp variables
3. **variation_3_register_hints.c** - Inline asm register allocation hints

### Testing Instructions
See `permuter/title_open_800CE378/MANUAL_TESTING_GUIDE.md` for complete step-by-step instructions.

**Quick start**:
1. Open https://decomp.me/scratch/c4GoH
2. Test each variation
3. Record scores
4. Report best result!

---

## Overall Progress

| Function | Assembly Lines | Base Score | Best Score | Match % | Status |
|----------|---------------|-----------|-----------|---------|--------|
| 800D2374 | ~50 lines | 4020 | 3635 | ~91% | ✅ Improved |
| 800CE378 | 81 lines | - | 730 | 90.39% | 🎯 Testing |

## Critical Findings

### ⚠️ Target Binary Issue (Resolved)
- **Problem**: Initially used wrong target.o for 800CE378
- **Discovery**: User caught that 730 was actual best, not permuter's 6695
- **Resolution**: Extracted correct target.o from assembly (304 bytes)
- **Documentation**: See `permuter/title_open_800CE378/CRITICAL_FINDING.md`

## Recommended Next Actions

### Priority 1: Test 800CE378 Variations
- Most likely to reach 100% with targeted manual variations
- All infrastructure ready
- Clear testing procedure available

### Priority 2: Review 800D2374 Permuter Results
- Examine output-3635-1 and output-3635-2
- Identify successful patterns
- Potentially combine for further improvement

### Priority 3: Continue Exploration
- If 800CE378 reaches 100%, document winning patterns
- Apply lessons learned to future functions
- Consider permuter with corrected binary if manual testing plateaus
