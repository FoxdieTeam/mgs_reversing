# CRITICAL FINDING: Permuter Target Binary Error

## Issue Discovered
The permuter was given the **WRONG target.o file** - it contained the binary from `title_open_800D2374` instead of `title_open_800CE378`.

## Evidence
- Both target.o files are identical (297 bytes each)
- Permuter base score: 9865 (measuring against wrong function)
- Permuter best: 6695 (still wrong function)
- **Actual best score: 730 from manual decomp.me work** ✅

## Real Achievement
```
Manual decomp.me Score: 730 @ 90.39% match
This is our ACTUAL best for title_open_800CE378
```

## Why This Happened
1. Copied target.o from previous function as placeholder
2. Did not properly compile title_open_800CE378.s to PSYQ LNK format
3. Permuter ran 450+ iterations on wrong assembly

## Lesson Learned
- Always verify target binary matches source assembly
- File size alone is not enough verification
- Manual decomp.me verification > automated permuter without proper target

## Current Status
**730 score IS our best result** - no need to run permuter further on wrong data.
Next step: Commit this excellent 90.39% match and move to next function.
