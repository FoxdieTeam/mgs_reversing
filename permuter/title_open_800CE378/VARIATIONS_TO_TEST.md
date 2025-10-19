# Manual Variations to Test on decomp.me

**Current Best**: 730 score @ 90.39% match from base.c

## Test Plan

Upload each variation to decomp.me (https://decomp.me/scratch/c4GoH) and compare scores:

### Variation 1: Combined Pointer Calculation
**File**: `variation_1_combined_pointer.c`
**Change**: Combine pointer calc into single statement: `(RGBElement *)((char *)work + 0x18C) + index`
**Theory**: Might change register allocation order
**Expected**: Could affect how compiler generates pointer arithmetic

### Variation 2: Scoped temp Variables
**File**: `variation_2_temp_in_case.c`
**Change**: Declare `temp` inside each case with braces `{ int temp = ... }`
**Theory**: Scope affects register lifetime and allocation
**Expected**: May match compiler's natural register usage

### Variation 3: Register Allocation Hints
**File**: `variation_3_register_hints.c`
**Change**: Use `register __asm__("$4")` to hint base pointer in a0
**Theory**: PSYQ gcc may respect register hints for pointer allocation
**Expected**: Could align register usage with target assembly

## Assembly Analysis Hints

Target assembly shows:
- `a0` (work pointer) → base calculation at work+0x18C
- `a1` (index) → multiply by 40 for element offset
- `a2` used for elem pointer throughout cases
- Jump table at 0x800CE3AC for switch statement

Current base.c likely differs in:
1. Register assignment (a2 vs a1 for elem)
2. Pointer arithmetic sequence
3. Control flow optimizations

## Next Steps

1. Test each variation on decomp.me
2. Record scores
3. If any beat 730, use that as new base
4. Combine winning patterns if multiple improvements found
5. Consider permuter with corrected target binary if we get stuck
