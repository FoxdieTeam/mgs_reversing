# decomp.me - Istruzioni Step-by-Step

## 📋 File Preparati

- **Assembly**: `/tmp/title_open_800D2374_asm.txt`
- **C Code**: `/tmp/title_open_800D2374_code.c`

## 🚀 Procedura (5 minuti)

### Step 1: Apri decomp.me

```bash
open https://decomp.me/
```

(Già fatto - dovrebbe aprirsi nel browser)

### Step 2: Crea Nuovo Scratch

1. Click su **"Create"** o **"New Scratch"**
2. Scegli Platform: **"PlayStation 1 (PSX)"**
3. Scegli Preset: **"Metal Gear Solid (overlays)"**
   - Questo preset ha i context pre-configurati!

### Step 3: Incolla Assembly

1. Tab **"Target"** o **"Assembly"**
2. Copia il contenuto di `/tmp/title_open_800D2374_asm.txt`:

```bash
cat /tmp/title_open_800D2374_asm.txt | pbcopy
```

3. Incolla nel campo assembly (CMD+V)

### Step 4: Incolla C Code

1. Tab **"Source"** o **"Code"**
2. Copia il C code:

```bash
cat /tmp/title_open_800D2374_code.c | pbcopy
```

3. Incolla nel campo code (CMD+V)

### Step 5: Seleziona Compiler

- Compiler: **"PSYQ 4.4"** o **"GCC 2.95.2"**
- Flags: **"-O2 -G8"**
  (Dovrebbero essere già settati dal preset MGS)

### Step 6: Compila e Vedi Score

1. Click **"Compile"** o attendi auto-compile
2. Vedi lo score in alto
3. **Guarda il diff** a destra

### Step 7: Prova Context Diversi

Il preset MGS overlays ha circa 10 context pre-configurati. Prova questi:

1. **"title_open context"** - structs specifici per overlay title
2. **"OpenWork context"** - struct OpenWork definition
3. **"minimal context"** - minimal headers
4. **"full includes"** - tutti gli include MGS

**Per ogni context**:
- Cambia dropdown "Context"
- Ricompila
- **Annota lo score migliore!**

### Step 8: Se Score Migliora

1. Click **"Share"** per salvare scratch
2. Copia URL (es: `https://decomp.me/scratch/abc123`)
3. Torna qui e dimmi l'URL + score ottenuto

### Step 9: Se Score Peggiora o Uguale

- Prova modificare C code leggermente:
  - Tipo variabili (int vs unsigned)
  - Ordine dichiarazioni
  - Parentesi nelle espressioni

## 🎯 Obiettivo

**Score attuale**: 1655 punti
**Target**: < 1000 (buono), < 500 (ottimo), 0 (perfetto)

## 💡 Tips

1. **NOPs sono il problema**: Guarda dove sono i NOPs nel diff
2. **Register allocation**: Nota quali registri usa (v1 vs s0)
3. **Context conta!**: Struct definitions cambiano tutto
4. **Community**: Puoi rendere scratch pubblico per aiuto

## 📊 Cosa Annotare

Per ogni context testato:
```
Context: [nome]
Score: [numero]
Note: [cosa è cambiato nel diff]
```

## 🔄 Iterare

Se trovi score migliore:
1. Copia C code migliorato da decomp.me
2. Sostituisci in `base.c`
3. Rilancia permuter locale
4. Ripeti!

## ❓ Se Bloccato

- Chiedi su Discord: https://discord.com/invite/psx-dev-642647820683444236
- Canale: #mgs-reversing o #decompilation
- Condividi scratch URL

---

**Preparato da**: Claude Code Analysis
**Score Baseline**: 1655
**Target**: Miglioramento > 50%
