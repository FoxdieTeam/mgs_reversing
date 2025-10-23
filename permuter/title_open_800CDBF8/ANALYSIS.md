# title_open_800CDBF8 - Function Analysis

## Assembly Size
**152 instructions** - Smallest remaining function in title overlay

## Key Observations from Assembly

### Stack Frame
- Stack adjustment: 0x27BDFFD8 (subtract 0x28 from sp)
- Saves multiple registers (a4, a3, a2, a1, a0, s4, s3, s2, s1, s0, ra)
- Small frame suggests function takes few parameters

### Parameter Usage
- Assembly shows loading from work structure (a0)
- Index parameter (a1) appears to be used for calculations

### Struct Access Patterns
- Offset 0xA7C: Likely state field (loaded early, checked with branch)
- Offset 0xAA0/0xAA4: Possibly array access patterns
- Offset 0x18C: Suggests pointer arithmetic to similar element array

### Control Flow
- Initial branch at 0x0460007C suggests large state/value check
- Multiple conditional jumps suggest switch-like structure
- Repeated instruction patterns suggest cases or loops

## Hypothesis

Based on pattern similarity to adjacent functions, this function likely:
1. Takes an OpenWork structure and index
2. Manipulates an array of RGB/color elements
3. Uses a state machine (switch on work->fA8C or similar)
4. Has multiple cases with different transformations

## Testing Strategy

**Step 1**: Test baseline with standard struct definitions
**Step 2**: If baseline matches poorly, analyze assembly for:
   - Exact offset values for state fields
   - Loop vs switch structure
   - Function call patterns
**Step 3**: Apply discovered patterns incrementally
   - Pointer arithmetic
   - Descriptive naming
   - Field re-reading in conditionals

## Comparison to title_open_800CE378

| Aspect | CE378 (94.74%) | CDBF8 (unknown) |
|--------|---|---|
| Size | 248 instructions | 152 instructions |
| Structure | RGB fade state machine | Unknown, likely similar |
| Parameters | work, index | work, index |
| Pattern Success | All 3 patterns worked | TBD |

## Next Action

1. Test baseline on decomp.me
2. Record baseline score
3. Apply patterns based on assembly analysis
4. Iterate with variations if needed
