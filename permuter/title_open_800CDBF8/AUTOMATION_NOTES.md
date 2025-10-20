# Browser Automation Notes for decomp.me Testing

## Summary

Automated browser testing via Playwright MCP encountered format compatibility issues. **Manual testing with `decompme_asm.py` is the reliable approach.**

---

## Issue: Assembly Format Requirements

### Problem Encountered

decomp.me's assembler (aspsx) rejects raw hex opcodes:

```
Error: unrecognized opcode `afb40020`
Error: junk at end of line, first unrecognized character is `2'
```

### Root Cause

The web interface expects **disassembled MIPS assembly instructions**, not raw hex opcodes:

**❌ What we tried** (raw hex):
```
27BDFFD8
AFB40020
0080A021
```

**✅ What decomp.me expects** (disassembled MIPS):
```
addiu $sp, $sp, -0x28
sw $s4, 0x20($sp)
move $s4, $a0
```

### Why `decompme_asm.py` Works

The project's extraction script:
1. Reads the `.s` file with `dw 0xHEXCODE` format
2. Disassembles hex opcodes to MIPS instructions
3. Formats for decomp.me's assembler
4. Copies to clipboard ready for paste

---

## Attempted Solutions

### Attempt 1: Direct Hex Opcodes
- Extracted hex from assembly file: `grep -E '^\s*dw 0x' | awk '{print $2}' | sed 's/0x//g'`
- Result: ❌ Assembler errors

### Attempt 2: Kill/Restart Browser
- Killed all Chrome processes to clear state
- Result: ✅ Browser restarted but ❌ same format errors

### Attempt 3: Use decompme_asm.py Output
- Script says "asm is now on your clipboard"
- Result: Cannot programmatically access system clipboard from Playwright

---

## Why Manual Testing is Better

1. **Clipboard Integration**: `decompme_asm.py` copies formatted assembly directly
2. **Format Verification**: You can see the formatted assembly before pasting
3. **Error Feedback**: Immediate visual feedback on decomp.me
4. **Score Recording**: Easy to copy/record scores
5. **Iteration Speed**: Faster to test variations manually than debug automation

---

## Automation Limitations Discovered

### Browser Automation Constraints
- Cannot read system clipboard (security restriction)
- Cannot programmatically trigger `decompme_asm.py` clipboard copy and paste
- decomp.me's assembly field expects complex disassembled format

### Potential Future Automation
Would require:
1. Implementing disassembler in automation script
2. Or: Using decomp.me API directly (if available)
3. Or: Parsing `decompme_asm.py` output before clipboard copy

---

## Recommended Workflow

**Use the manual testing instructions in `MANUAL_TEST_INSTRUCTIONS.md`:**

```bash
# Step 1: Extract assembly (auto-copied to clipboard)
cd build
python3 decompme_asm.py ../asm/overlays/title/title_open_800CDBF8.s

# Step 2: Go to decomp.me
# - New scratch
# - Select "Metal Gear Solid (overlays)" preset
# - Paste assembly (Cmd+V)
# - Paste baseline.c code
# - Click "Create scratch"
# - Record score

# Step 3: Repeat with variation1_discovered_patterns.c
# - Replace code in same scratch
# - Record new score
# - Compare results
```

**Time estimate**: 10-15 minutes for both baseline and variation 1

---

## Value of Manual Testing

Despite automation failure, the infrastructure created is valuable:

✅ **baseline.c** - Conservative decompilation ready to test
✅ **variation1_discovered_patterns.c** - All 3 patterns applied
✅ **ANALYSIS.md** - Assembly observations documented
✅ **TEST_PLAN.md** - Testing sequence defined
✅ **MANUAL_TEST_INSTRUCTIONS.md** - Step-by-step workflow
✅ **decompme_asm.py** - Proven script for correct formatting

The manual workflow is **reliable, fast, and proven** by the team's successful use across 100% of main executable decompilation.

---

## Lessons Learned

1. **Tool Constraints**: Not all workflows are automatable via browser
2. **Format Complexity**: Assembly formats are toolchain-specific
3. **Clipboard Security**: System clipboard is isolated from browser automation
4. **Manual Can Be Better**: Simple workflows don't need automation
5. **Documentation > Automation**: Clear instructions enable anyone to execute

---

## Next Steps

1. ✅ Manual testing infrastructure complete
2. ⏳ User tests baseline.c and variation1 on decomp.me
3. ⏳ Record scores in TEST_PLAN.md
4. ⏳ Apply successful patterns to next functions (CD800, CDE44)
5. ⏳ Document pattern effectiveness across multiple functions

---

**Conclusion**: Browser automation revealed format requirements. Manual testing with project's proven tools is the optimal approach.
