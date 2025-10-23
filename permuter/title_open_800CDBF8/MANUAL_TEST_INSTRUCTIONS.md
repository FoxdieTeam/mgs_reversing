# Manual Testing Instructions for title_open_800CDBF8

## Overview

This guide provides step-by-step instructions for manually testing `baseline.c` and `variation1_discovered_patterns.c` on decomp.me. Due to assembly format requirements, we use the project's `decompme_asm.py` script to prepare the assembly correctly.

---

## Prerequisites

- Python 3 installed
- Access to https://decomp.me/
- Files ready in `permuter/title_open_800CDBF8/`:
  - `baseline.c`
  - `variation1_discovered_patterns.c`

---

## Step 1: Extract Assembly with Correct Format

The assembly file needs to be formatted for decomp.me using the project's extraction script.

```bash
# Navigate to build directory
cd /Users/wonderwall/development-workspace/mgs_reversing/build

# Extract and format assembly for decomp.me (copies to clipboard)
python3 decompme_asm.py ../asm/overlays/title/title_open_800CDBF8.s
```

**What this does**:
- Reads the raw assembly file
- Extracts only the hex opcodes (removes addresses and labels)
- Formats correctly for decomp.me's assembler
- **Copies the formatted assembly to your clipboard**

---

## Step 2: Test Baseline on decomp.me

### 2.1 Navigate to decomp.me
1. Go to https://decomp.me/
2. Click **"New scratch"** button

### 2.2 Configure Settings
1. **Platform**: Select "PlayStation" (should auto-select with preset)
2. **Compiler**: Should auto-populate as "gcc 2.8.1 + aspsx 2.79 (CCPSX)"
3. **Preset**: Select **"Metal Gear Solid (overlays)"** from dropdown
   - This loads the correct compiler settings: PSX, psyq 4.4, -O2 -g0 -c
   - Context is pre-populated from https://decomp.me/preset/19

### 2.3 Paste Assembly
1. Click in **"Target assembly"** field
2. **Paste from clipboard** (Cmd+V / Ctrl+V)
   - Assembly was copied by decompme_asm.py script in Step 1
3. Verify it looks like clean hex opcodes (no addresses):
   ```
   27BDFFD8
   AFB40020
   0080A021
   ...
   ```

### 2.4 Paste Baseline Code
1. Open `permuter/title_open_800CDBF8/baseline.c`
2. Copy the **entire content** (including typedefs)
3. Paste into **"Context"** field on decomp.me

### 2.5 Create Scratch and Record Score
1. Click **"Create scratch"** button
2. Wait for compilation and diff calculation
3. **Record the score** - displayed at top as "Score: XXXX @ XX.XX%"

**Record in TEST_PLAN.md**:
```markdown
| Function | Baseline | Var 1 | Best | Status |
|----------|----------|-------|------|--------|
| CDBF8 | XXXX @ XX.XX% | ? | ? | Testing Baseline |
```

---

## Step 3: Test Variation 1 (Discovered Patterns)

### 3.1 Same Assembly, Different Code
1. **Keep the same scratch open** on decomp.me (assembly unchanged)
2. OR create new scratch with same assembly from Step 2.3

### 3.2 Paste Variation 1 Code
1. Open `permuter/title_open_800CDBF8/variation1_discovered_patterns.c`
2. Copy the **entire content**
3. **Replace** the code in decomp.me's "Context" field
4. Click **"Compile"** or refresh

### 3.3 Record Variation 1 Score
1. Note the new score
2. **Compare to baseline**: Better / Same / Worse?

**Update TEST_PLAN.md**:
```markdown
| Function | Baseline | Var 1 | Best | Status |
|----------|----------|-------|------|--------|
| CDBF8 | XXXX @ XX.XX% | YYYY @ YY.YY% | [better one] | ✅ Tested |
```

---

## Step 4: Analyze Results

### If Variation 1 is Better:
✅ **Success!** The discovered patterns work for this function.
- Document improvement in TEST_RESULTS.md
- Patterns to apply to next functions:
  1. Pointer arithmetic (`elem += index`)
  2. Descriptive naming (`int shade`)
  3. Re-read struct fields in conditionals

### If Same or Worse:
⚖️ This function may have different characteristics.
- Check assembly at specific offsets mentioned in ANALYSIS.md
- May need custom variations based on control flow

---

## Step 5: Document Findings

Create or update `TEST_RESULTS.md`:

```markdown
## Test Results for title_open_800CDBF8

**Date**: 2025-10-20

### Baseline Test
- **Score**: XXXX @ XX.XX%
- **Code**: baseline.c
- **Observations**: [What you noticed about the diff]

### Variation 1 (Discovered Patterns)
- **Score**: YYYY @ YY.YY%
- **Improvement**: [+/- difference]
- **Analysis**: [Why did this happen?]
- **Status**: ✅ Improvement / ⚖️ No Change / ❌ Regression

### Key Findings
- Pattern 1 (Pointer Arithmetic): [Effective? Yes/No]
- Pattern 2 (Descriptive Naming): [Effective? Yes/No]
- Pattern 3 (Re-read Fields): [Effective? Yes/No]

### Recommendation
[Should these patterns be applied to title_open_800CD800?]
```

---

## Success Criteria Reference

- **✅ Excellent**: < 500 score (> 93%)
- **✅ Good**: 500-700 score (90-93%)
- **⚠️ Fair**: 700-900 score (88-90%)
- **❌ Needs Work**: > 900 score (< 88%)

---

## Troubleshooting

### Assembly Format Errors
**Problem**: "Error: junk at end of line" or "unrecognized opcode"

**Solution**:
- Make sure you used `decompme_asm.py` to extract assembly
- Don't manually copy from `.s` files (they include addresses)
- Verify assembly is pure hex opcodes (8 characters per line)

### Wrong Compiler Selected
**Problem**: Compilation succeeds but score is very high (>5000)

**Solution**:
- Verify "Metal Gear Solid (overlays)" preset is selected
- Check compiler is "gcc 2.8.1 + aspsx 2.79 (CCPSX)"
- Compiler flags should be: `-O2 -g0 -c`

### Context Errors
**Problem**: "Undefined reference" or "Unknown type"

**Solution**:
- Make sure you copied the **entire** baseline.c or variation file
- Includes typedef for OpenWork and RGBElement
- Preset should auto-populate context from Metal Gear Solid project

---

## Quick Reference Commands

```bash
# Extract assembly (copies to clipboard)
cd build && python3 decompme_asm.py ../asm/overlays/title/title_open_800CDBF8.s

# View baseline code
cat permuter/title_open_800CDBF8/baseline.c

# View variation 1 code
cat permuter/title_open_800CDBF8/variation1_discovered_patterns.c

# Edit TEST_PLAN.md to record results
code permuter/title_open_800CDBF8/TEST_PLAN.md
```

---

## Next Steps After Testing

1. ✅ If patterns work well (improvement):
   - Apply same patterns to `title_open_800CD800` (216 lines)
   - Document pattern effectiveness

2. ⚖️ If patterns show mixed results:
   - Create additional variations based on assembly analysis
   - Test incremental pattern application

3. ❌ If patterns don't help:
   - Deep-dive into assembly differences
   - This function may have unique characteristics
   - Consult ANALYSIS.md for function-specific insights

---

**Estimated Time**: 10-15 minutes for both baseline and variation 1 tests

**Goal**: Validate that discovered PSYQ gcc 2.8.1 patterns transfer to other functions
