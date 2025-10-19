# FINAL ATTACK PLAN: 510 @ 91.36% → 100% Match

**Obiettivo**: Raggiungere il 100% match (score 0) per `title_open_800D2374`
**Stato attuale**: 510 @ 91.36% matching
**Gap rimanente**: 8.64% (44 punti Levenshtein)

---

## 📊 Situazione Attuale

### Successi Ottenuti ✅
1. **Breakthrough Phase 1+2**: 825 → 510 (-38% score, +5.34% match)
2. **Rimossa ottimizzazione permuter** che creava 3 istruzioni extra
3. **Fixato tipo struct** da `int f24B4` a `struct _OpenWork *f24B4`
4. **Compiler flag corretto**: `-G8` per MGS overlays

### Differenze Rimanenti (dal screenshot decomp.me)

**Analisi visiva del diff al 510 @ 91.36%**:

1. **Line 0x48**: Register difference
   - Target: `lw a0, 0x24b4(s1)`
   - Current: `lw v0, 0x24b4(s1)`
   - **Problema**: Return value caricato in registro sbagliato

2. **Line 0x60**: Instruction inserted
   - Current ha: `move v0, s1`
   - Target NON ha questa istruzione
   - **Problema**: Movimento di registro extra

3. **Lines 0x70, 0x74, 0x78**: Jump table differences
   - Branch targets leggermente diversi
   - **Problema**: Code layout o jump table generation

4. **Lines 0x98, 0xb4**: Jump instruction differences
   - Differenze nei salti alla fine dei case
   - **Problema**: Branch optimization patterns

---

## 🎯 STRATEGIA FINALE (Multi-Track Approach)

### Track 1: ANALISI APPROFONDITA DIFF (Priorità: ALTA) ⚡

**Obiettivo**: Capire esattamente cosa causa ogni differenza rimanente

**FASE 1A: Screenshot e Analisi Dettagliata**
1. ✅ Già fatto: Screenshot a 510 @ 91.36%
2. ⏳ Fare screenshot COMPLETO del diff assembly (scroll up/down per vedere tutto)
3. ⏳ Creare tabella comparativa linea-per-linea:
   ```
   Offset | Target ASM | Current ASM | Tipo Diff | Causa Possibile
   0x48   | lw a0,..   | lw v0,..    | register  | return value handling
   0x60   | (none)     | move v0,s1  | insert    | extra register move
   ```

**FASE 1B: Reverse Engineering delle Differenze**
- Per ogni differenza, ipotizzare quale pattern C potrebbe generarla
- Testare ipotesi su decomp.me
- Documentare risultati

**Probabilità successo**: 60% - Analisi sistematica spesso rivela patterns nascosti

---

### Track 2: VARIANTI CODICE SISTEMATICHE (Priorità: ALTA) 🔬

**Obiettivo**: Testare variazioni C code che potrebbero influenzare register allocation e code generation

**FASE 2A: Return Statement Variations**

Il diff mostra differenze nel return value handling (a0 vs v0). Testare:

```c
// VARIANTE 1: Explicit temporary per return
OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;
  OpenWork *ret;  // NEW: Explicit return variable

  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    ret = work->f24B4;
    return ret;  // Return via temporary
  }
  // ... rest of function
}
```

```c
// VARIANTE 2: Inline conditionals
OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;

  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  // Single line if-return
  if (work->f24BC != 0) return work->f24B4;

  // ... rest of function
}
```

```c
// VARIANTE 3: Const qualifier
OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;
  const int f24BC = work->f24BC;  // Cache with const

  // ... loop

  if (f24BC != 0)
  {
    return work->f24B4;
  }
  // ... rest
}
```

**FASE 2B: Switch Statement Variations**

```c
// VARIANTE 4: Explicit variable for switch expression
if (work->f24EC != 0)
{
  int switchVal = work->f24AC;  // Explicit variable
  switch (switchVal)
  {
    // ... cases
  }
}
```

```c
// VARIANTE 5: Reorder case statements
// Provare ordine diverso dei case (compiler potrebbe riordinare jump table)
switch (work->f24AC)
{
  case 0:
  case 2:  // Swap case order
  case 1:
  case 3:
  // ...
}
```

```c
// VARIANTE 6: Separate if-else instead of empty case
// Instead of:
case 1:
  break;

// Try:
case 1:
  /* nothing */
  break;
```

**FASE 2C: Variable Declaration Order**

```c
// VARIANTE 7: Move 'i' declaration later
OpenWork *title_open_800D2374(OpenWork *work)
{
  // Declare 'i' closer to usage

  int i;
  for (i = 0; i < 24; i++)
  // ...
}
```

**Probabilità successo**: 70% - Piccole variazioni C possono avere grandi effetti su assembly PS1

---

### Track 3: COMMUNITY EXPERTISE (Priorità: MEDIA) 👥

**Obiettivo**: Ottenere feedback da esperti PS1 decompilation

**FASE 3A: Discord PSX.Dev Engagement**

1. **Preparare post dettagliato**:
   ```markdown
   Title: 91.36% match on MGS title_open function - need help with final 8.64%

   Hey everyone! 👋

   Working on decompiling `title_open_800D2374` from MGS PS1 (overlays).
   Made great progress but stuck at 510 @ 91.36% matching.

   Scratch: https://decomp.me/scratch/F1WN5
   Compiler: PSYQ 4.4 (gcc 2.8.1), flags: -O2 -Wall -G8

   Main remaining differences:
   - Line 0x48: Return value in v0 instead of a0
   - Line 0x60: Extra `move v0, s1` instruction
   - Jump table address resolution differences

   Any suggestions on C patterns that might help?
   Thanks! 🙏
   ```

2. **Canali dove postare**:
   - #mgs-reversing (primary)
   - #decompilation (general help)
   - #psx-dev (PS1 specific)

3. **Follow-up**:
   - Rispondere rapidamente a suggerimenti
   - Testare immediatamente su decomp.me
   - Condividere risultati

**FASE 3B: FoxdieTeam Collaboration**

- Controllare se qualcuno nel team ha esperienza con questa funzione
- Chiedere se ci sono pattern specifici per le funzioni title overlay
- Verificare se ci sono struct definitions aggiuntive che potrebbero aiutare

**Probabilità successo**: 50% - Community spesso ha insights cruciali

---

### Track 4: ADVANCED TECHNIQUES (Priorità: BASSA) 🧪

**Obiettivo**: Tecniche avanzate se approcci standard falliscono

**FASE 4A: Decomp.me Context Experiments**

Testare diverse configurazioni nel Context tab:

```c
// CONTEXT 1: Additional PSX typedefs
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

// CONTEXT 2: MGS-specific defines
#define MGS_OVERLAY
#define TITLE_OVERLAY
```

**FASE 4B: Compiler Flag Experiments**

Attualmente: `-O2 -Wall -G8`

Provare:
- `-O2 -Wall -G8 -fno-builtin` (disable built-in functions)
- `-O2 -Wall -G8 -fno-common` (no common symbols)
- `-O2 -Wall -G8 -fno-defer-pop` (don't defer pop operations)

**FASE 4C: Assembly-Level Analysis**

Se tutto fallisce:
1. Studiare esattamente quali istruzioni MIPS genera ogni pattern C
2. Creare "assembly cheat sheet" per PSYQ gcc 2.8.1
3. Craft C code reverse-engineered dall'assembly target

**Probabilità successo**: 30% - Molto time-consuming, solo come last resort

---

## 📅 TIMELINE ESECUZIONE

### Week 1: Analisi e Test Sistematici
- **Day 1-2**: Track 1 (Analisi diff approfondita) + Track 2 FASE 2A (Return variations)
- **Day 3**: Track 2 FASE 2B (Switch variations)
- **Day 4**: Track 2 FASE 2C (Variable declarations) + Community post preparazione
- **Day 5**: Track 3 FASE 3A (Discord engagement)

### Week 2: Community & Advanced
- **Day 6-7**: Iterazione su feedback community
- **Day 8-9**: Track 4 (Advanced techniques) se necessario
- **Day 10**: Documentazione finale e PR preparation (se 100% raggiunto)

---

## 🎲 PROBABILITY MATRIX

| Track | Technique | Probability Success | Time Required | Priority |
|-------|-----------|---------------------|---------------|----------|
| 1 | Analisi diff approfondita | 60% | 4 hours | ⚡ ALTA |
| 2A | Return statement variations | 70% | 2 hours | ⚡ ALTA |
| 2B | Switch variations | 65% | 3 hours | ⚡ ALTA |
| 2C | Variable declarations | 50% | 2 hours | ⚡ ALTA |
| 3A | Discord community | 50% | Variable | 🔶 MEDIA |
| 3B | FoxdieTeam collab | 40% | Variable | 🔶 MEDIA |
| 4A | Context experiments | 30% | 2 hours | 🔵 BASSA |
| 4B | Compiler flags | 25% | 1 hour | 🔵 BASSA |
| 4C | Assembly-level RE | 30% | 8+ hours | 🔵 BASSA |

**Overall probability of reaching 100%**: **~85%** (with community help)

---

## ✅ SUCCESS CRITERIA

**100% Match Achieved** when:
- decomp.me score = 0
- All assembly lines match exactly
- No 'r', 'i', '|', '<' markers in diff

**Acceptable Alternative**:
- Score < 100 (95%+ matching)
- Only cosmetic differences (NOPs, padding)
- Function behavior 100% identical

---

## 📋 IMMEDIATE NEXT STEPS

### Action Items (in order):

1. **[15 min]** Screenshot completo del diff assembly su decomp.me
2. **[30 min]** Creare tabella comparativa diff dettagliata
3. **[1 hour]** Testare VARIANTE 1 (explicit return temporary) su decomp.me
4. **[1 hour]** Testare VARIANTE 2 (inline conditionals) su decomp.me
5. **[30 min]** Preparare Discord post per community engagement
6. **[ongoing]** Documentare ogni test e risultato in DECOMP_ME_RESULTS.md

### Files to Update:
- `DECOMP_ME_RESULTS.md` - Add each test result
- `phase2_variation_*.c` - Each code variation tested
- `DISCORD_POST.md` - Community help request draft

---

## 🎖️ MISSION STATEMENT

> "Siamo al 91.36% - un risultato eccezionale che FoxdieTeam non ha ancora raggiunto.
> Con analisi sistematica, test metodici e supporto community, raggiungeremo il 100%.
> Il gap rimanente è piccolo ma richiede precisione chirurgica.
> Andiamo a prenderci quella funzione! 🎯"

**Status**: READY TO EXECUTE
**Commander**: wonderwall + Claude Code
**Target**: 100% match, 0 score
**ETA**: 1-2 weeks with systematic approach

---

*Generated*: 2025-10-19
*Previous best*: 510 @ 91.36%
*Next milestone*: < 300 (95%+ matching)
