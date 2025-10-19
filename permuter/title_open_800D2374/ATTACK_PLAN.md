# Piano d'Attacco per Raggiungere 100% Match
## Function: `title_open_800D2374`

**Data Creazione**: 2025-10-19
**Stato Attuale**: 825 @ 86.02% matching
**Target**: 0 @ 100% matching

---

## 🎯 Analisi del Problema

### Stato Attuale
- **Score decomp.me**: 825 (86.02% matching)
- **Score permuter locale**: 1655 (dopo 26 iterazioni)
- **Differenza rimanente**: 14% (~16-17 istruzioni assembly)

### Differenze Chiave nell'Assembly

1. **3 Istruzioni Eliminate** (linee 0x60, 0x64, 0x68):
   ```
   60: nop
   64: lw v1,0x24ac(s1)    # work->f24AC load
   68: nop
   ```
   Queste NON esistono nel target ma sono presenti nel nostro codice!

2. **Allocazione Registri Diversa**:
   - Target usa `v1` per variabile switch
   - Nostro codice usa `s0` per variabile switch
   - Questo indica uso di variabile locale vs accesso diretto

3. **Return Value Register** (linea 0x48):
   - Target: `lw a0,0x24b4(s1)` (load diretto in a0)
   - Nostro: `lw v0,0x24b4(s1)` (load in v0, poi move)

---

## 💡 Ipotesi Principale

### Il Problema dell'Ottimizzazione del Permuter

Il permuter locale ha trovato questa "ottimizzazione" all'iterazione 26:
```c
i = work->f24AC;  // Pre-carica il valore
if (work->f24EC != 0) {
  switch (i) { ... }
}
```

**MA**: Questa ottimizzazione è SBAGLIATA per decomp.me perché:
1. Crea 3 istruzioni extra (load + 2 nop per alignment)
2. Cambia allocazione registri da `v1` (temp) a `s0` (saved)
3. Il target originale NON ha questa ottimizzazione

**Perché il permuter l'ha trovata?**:
- Il permuter locale usa una metrica DIVERSA da decomp.me
- Quella che aiuta localmente può PEGGIORARE su decomp.me
- Score 1655 (locale) sembrava buono, ma è peggio di non-ottimizzato per il target reale!

### Il Codice Originale Deve Essere

```c
if (work->f24EC != 0) {
  switch (work->f24AC) {  // Accesso DIRETTO, no variabile intermedia!
    case 0: ...
    case 1: ...
    // etc
  }
}
```

---

## 📋 Piano d'Attacco Step-by-Step

### FASE 1: Test Critico - Rimuovere Ottimizzazione (⏱️ 15 minuti)

**Priorità**: 🔴 MASSIMA (80% probabilità di successo)

**Azione**:
1. Modificare il codice attuale rimuovendo la linea `i = work->f24AC`
2. Cambiare `switch(i)` → `switch(work->f24AC)`
3. Rimuovere dichiarazione variabile `int i;` dal blocco switch (ma tenerla per il loop!)

**Codice da testare**:
```c
OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;

  // Loop usa ancora i
  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    return (OpenWork *) work->f24B4;
  }

  // RIMOSSO: i = work->f24AC;
  if (work->f24EC != 0)
  {
    switch (work->f24AC)  // ACCESSO DIRETTO!
    {
      case 0:
        title_open_800C4AD0(work, 0, 0);
        break;
      case 1:
        break;
      case 2:
        title_open_800C4AD0(work, 1, 0x6739);
        title_open_800C4AD0(work, 2, 0);
        break;
      case 3:
        title_open_800C4AD0(work, 3, 0);
        break;
      case 4:
        return work;
      case 5:
        title_open_800C4AD0(work, 5, 0x6739);
        break;
      case 6:
        return work;
      case 7:
        return work;
      case 8:
        return work;
      case 9:
        return work;
      case 10:
        return work;
    }
  }
  return work;
}
```

**Risultato Atteso**:
- Eliminazione delle 3 istruzioni extra
- Cambio allocazione registri da s0 a v1
- **Score stimato**: 600-700 (>90% match) o meglio!

**Se Score Migliora**: Procedi a FASE 2
**Se Score NON Migliora**: Analizza diff per nuovi problemi (vedi FASE 3)

---

### FASE 2: Fix Tipi Struct (⏱️ 30 minuti)

**Priorità**: 🟡 ALTA (15% probabilità di ulteriore miglioramento)

**Problema**: Il campo `f24B4` è dichiarato come `int` ma dovrebbe essere `OpenWork*`

**Azione**:
1. Modificare definizione struct:
```c
typedef struct _OpenWork
{
  char padding1[0x24AC];
  int f24AC;
  char padding2[(0x24B4 - 0x24AC) - 4];
  struct _OpenWork *f24B4;  // CAMBIATO da: int f24B4;
  char padding3[(0x24BC - 0x24B4) - 4];
  int f24BC;
  char padding4[(0x24EC - 0x24BC) - 4];
  int f24EC;
} OpenWork;
```

2. Rimuovere cast esplicito nella return:
```c
// PRIMA:
return (OpenWork *) work->f24B4;

// DOPO:
return work->f24B4;
```

**Risultato Atteso**:
- Fix register allocation a linea 0x48 (a0 vs v0)
- **Score stimato**: Ulteriore miglioramento di 50-100 punti

**Combinare con FASE 1**: Testare entrambe le modifiche insieme se FASE 1 migliora

---

### FASE 3: Automazione Test Varianti (⏱️ 1-2 ore)

**Priorità**: 🟢 MEDIA (necessaria solo se FASE 1+2 non raggiungono 100%)

**Obiettivo**: Creare sistema automatizzato per testare multiple varianti

**Script Python da Creare** (`test_variants.py`):
```python
#!/usr/bin/env python3
"""
Automated decomp.me testing for code variants
"""

import playwright.sync_api as pw
import time

variants = [
    # Variant 1: Original without i = work->f24AC
    {"name": "no_temp_var", "code": "...", "expected_improvement": "high"},

    # Variant 2: + struct pointer fix
    {"name": "no_temp_var_ptr_fix", "code": "...", "expected_improvement": "high"},

    # Variant 3: Different variable declarations
    {"name": "register_int_i", "code": "register int i;", "expected_improvement": "low"},

    # Variant 4: Volatile keyword
    {"name": "volatile_access", "code": "switch(work->f24AC)", "expected_improvement": "low"},

    # Variant 5-10: Systematic combinations
    # ... altri variants
]

def test_variant(browser, variant):
    """Test a code variant on decomp.me"""
    page = browser.new_page()
    page.goto("https://decomp.me/scratch/F1WN5")

    # Inject code
    inject_code(page, variant["code"])

    # Wait for compilation
    time.sleep(5)

    # Extract score
    score = extract_score(page)

    page.close()
    return score

# Run all variants and log results
for variant in variants:
    score = test_variant(browser, variant)
    print(f"{variant['name']}: {score}")
```

**Varianti da Testare Sistematicamente**:

1. **Ordine dichiarazioni variabili**
2. **Keyword register, volatile, const**
3. **Diversi tipi per loop counter** (int vs unsigned vs size_t)
4. **Switch case fall-through patterns**
5. **Ordine case statements**
6. **Parentesi nelle espressioni**
7. **Dichiarazioni separate vs combinate**

**Output**: File `variant_results.log` con tutti gli score

---

### FASE 4: Pattern Matching da Funzioni Matchate (⏱️ 1 ora)

**Priorità**: 🟢 BASSA (fallback se approcci precedenti non funzionano)

**Azione**:
1. Cercare in FoxdieTeam repo altre funzioni matched nell'overlay `title`
2. Analizzare pattern comuni:
   - Come accedono a struct fields?
   - Usano variabili intermedie o accesso diretto?
   - Quali idiomi C usano per switch statements?
   - Pattern di casting?

**Comandi per Analisi**:
```bash
cd /tmp/foxdie_mgs
# Trova funzioni matched (senza INCLUDE_ASM)
grep -v "INCLUDE_ASM" source/overlays/title/onoda/open/open.c | grep -A 30 "OpenWork"

# Analizza pattern switch
grep -A 20 "switch" source/overlays/title/onoda/open/open.c

# Pattern di accesso struct
grep "work->" source/overlays/title/onoda/open/open.c | head -50
```

---

### FASE 5: Community Consultation (⏱️ ongoing)

**Priorità**: 🟡 ALTA (da fare in parallelo)

**Risorse Discord**:
- **Server**: PSX.Dev Discord
- **Invite**: https://discord.com/invite/psx-dev-642647820683444236
- **Canali**: #mgs-reversing, #decompilation, #psyq-compiler

**Cosa Condividere**:
1. Link scratch: https://decomp.me/scratch/F1WN5
2. Score attuale: 825 @ 86.02%
3. Problemi identificati:
   - 3 istruzioni extra da ottimizzazione permuter
   - Register allocation v1 vs s0
   - Return value a0 vs v0
4. Codice testato e risultati

**Domande da Porre**:
- "Has anyone seen this pattern where local permuter optimization hurts decomp.me score?"
- "PSYQ compiler tricks for forcing v1 register allocation in switch statements?"
- "Should struct field be declared as pointer or int for this pattern?"
- "Any MGS overlay-specific compiler quirks to know?"

**Esperti da Taggare** (se appropriato):
- Maintainer del progetto FoxdieTeam/mgs_reversing
- Contributori attivi su overlay decompilation
- Esperti PSYQ compiler noti nella community

---

### FASE 6: Preparazione Contributo (⏱️ quando 100% raggiunto)

**Priorità**: 🎯 FINALE (solo se raggiungiamo 100%)

**Checklist Pre-Submission**:
1. ✅ Verifica score 0 @ 100% su decomp.me
2. ✅ Compila localmente con PSYQ toolchain
3. ✅ Confronta assembly byte-per-byte con target
4. ✅ Test che la funzione sia corretta (se possibile)
5. ✅ Documenta il processo di matching
6. ✅ Crediti appropriati (permuter, decomp.me, community help)

**Pull Request a FoxdieTeam**:
```markdown
## Title
Match function `title_open_800D2374` in title overlay (100%)

## Description
Successfully matched the `title_open_800D2374` function to 100% using a combination of:
- decomp.me testing (https://decomp.me/scratch/F1WN5)
- Local permuter iterations
- Struct field type optimization

Key insight: The local permuter's optimization (pre-loading work->f24AC into a variable)
actually prevented matching. Direct access in switch statement was required.

## Changes
- Replace INCLUDE_ASM pragma with decompiled C code
- Struct definition uses minimal padding for accessed fields

## Verification
- decomp.me score: 0 (100% match)
- Local objdump comparison: perfect byte match
- Compiler: PSYQ 4.4 with flags: -O2 -G8 -Wall

## Testing
[Describe any testing done to verify correctness]

## Credits
- decomp.me platform for comparison tool
- decomp-permuter for initial exploration
- [Community members if they helped]
```

---

## 📊 Metriche di Successo

### Benchmark di Progresso
| Score Range | Match % | Status | Action |
|-------------|---------|--------|--------|
| 825 | 86% | ✅ **ATTUALE** | Inizio FASE 1 |
| 700-800 | 87-88% | 🎯 Target FASE 1 | Procedi FASE 2 |
| 500-600 | 92-94% | 🎉 Eccellente | Fine-tuning |
| 100-200 | 98-99% | 🔥 Quasi perfetto | Dettagli finali |
| 0 | 100% | 🏆 **SUCCESSO!** | FASE 6 |

### Indicatori di Successo FASE 1
- ✅ Eliminazione 3 istruzioni (60, 64, 68)
- ✅ Cambio registro da s0 a v1
- ✅ Score < 700 (>88% match)

### Indicatori di Successo FASE 2
- ✅ Fix registro a0 vs v0 (linea 48)
- ✅ Score < 500 (>92% match)

---

## 🛠️ Risorse e Tool

### Toolchain Necessario
- ✅ Playwright MCP (già configurato)
- ✅ decomp.me access (scratch F1WN5)
- ✅ FoxdieTeam repository (clonato in /tmp/foxdie_mgs)
- ⏳ Python script automazione (da creare in FASE 3)

### File di Riferimento
- Target assembly: `/tmp/title_open_800D2374_asm.txt`
- Codice corrente: `/tmp/title_open_800D2374_code.c`
- Struct completa: `/tmp/title_open_800D2374_complete.c`
- Risultati: `DECOMP_ME_RESULTS.md`
- Questo piano: `ATTACK_PLAN.md`

### Documentazione Utile
- PSYQ compiler manual
- decomp.me help docs
- FoxdieTeam coding style guide
- PSX decompilation wiki

---

## ⚡ Quick Start - Esecuzione Immediata

**Per iniziare SUBITO con FASE 1** (la più promettente):

```bash
# 1. Crea il file con codice modificato
cat > /tmp/test_no_temp_var.c << 'EOF'
typedef struct _OpenWork
{
  char padding1[0x24AC];
  int f24AC;
  char padding2[(0x24B4 - 0x24AC) - 4];
  struct _OpenWork *f24B4;
  char padding3[(0x24BC - 0x24B4) - 4];
  int f24BC;
  char padding4[(0x24EC - 0x24BC) - 4];
  int f24EC;
} OpenWork;

extern void title_open_800C4AD0(OpenWork *work, int arg1, int arg2);

OpenWork *title_open_800D2374(OpenWork *work)
{
  int i;

  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    return work->f24B4;
  }

  if (work->f24EC != 0)
  {
    switch (work->f24AC)
    {
      case 0:
        title_open_800C4AD0(work, 0, 0);
        break;
      case 1:
        break;
      case 2:
        title_open_800C4AD0(work, 1, 0x6739);
        title_open_800C4AD0(work, 2, 0);
        break;
      case 3:
        title_open_800C4AD0(work, 3, 0);
        break;
      case 4:
        return work;
      case 5:
        title_open_800C4AD0(work, 5, 0x6739);
        break;
      case 6:
        return work;
      case 7:
        return work;
      case 8:
        return work;
      case 9:
        return work;
      case 10:
        return work;
    }
  }
  return work;
}
EOF

# 2. Usa Playwright per testare su decomp.me
# (vedi codice già sviluppato nelle sessioni precedenti)
```

**Cambiamenti Chiave Rispetto a Codice Attuale**:
1. ❌ RIMOSSA linea: `i = work->f24AC;`
2. ✅ CAMBIATO switch da: `switch (i)` → `switch (work->f24AC)`
3. ✅ CAMBIATO struct: `int f24B4` → `struct _OpenWork *f24B4`
4. ✅ RIMOSSO cast: `return (OpenWork *) work->f24B4` → `return work->f24B4`

---

## 🎯 Conclusione

**Probabilità di Successo**:
- FASE 1 sola: **80%** di raggiungere >90% match
- FASE 1 + FASE 2: **90%** di raggiungere >95% match
- Con FASE 3-4-5: **95%** di raggiungere 100% match eventualmente

**Tempo Stimato Totale**: 3-6 ore di lavoro distribuito

**Prossimo Step IMMEDIATO**: Eseguire FASE 1 test e verificare se l'ipotesi è corretta!

---

**Creato da**: Claude Code Analysis
**Ultima Modifica**: 2025-10-19
**Status**: ✅ PRONTO PER ESECUZIONE
