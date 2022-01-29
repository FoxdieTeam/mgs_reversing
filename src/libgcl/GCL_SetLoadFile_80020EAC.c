#include "mts_new.h"
#include "Script_tbl_map_8002BB44.h"

extern const char   aCrcError[];
extern const char   aSaveDataVersio[];

extern int                  dword_800AB9E8;
extern GameState_800B4D98   gGameState_800B4D98;
extern GameState_800B4D98   gGcl_gameStateVars_800B44C8;
extern GCL_Vars             gGcl_memVars_800b4588;
extern RadioMemory          gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];
extern char                 gStageName_800B4D88[16];
extern GCL_Vars             gGcl_vars_800B3CC8;

extern unsigned int CRC32_80020BB4(int param_1, char *param_2);
extern void         GM_RestoreAreaHistory_8002A784(AreaHistory *param_1);
extern char*        strcpy_8008E768(char *, char *);

int GCL_SetLoadFile_80020EAC(char *saveBuf)
{
    typedef struct  { short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)]; } RdMem;
    SaveFile        *saveFile;
    SaveGame        *save;

    saveFile = (SaveFile*)saveBuf;
    save = &saveFile->f008_saveGame;

    if ((save->f008_version != 0x60) || (save->f00C_version2 != 0x800))
    {
        mts_printf_8008BBA0(aSaveDataVersio);
    }
    if (saveFile->f004_checksum != CRC32_80020BB4(sizeof(SaveGame), (char*)save))
    {
        mts_printf_8008BBA0(aCrcError);
        return 0;
    }

    dword_800AB9E8 = save->f010_unk;
    strcpy_8008E768(gStageName_800B4D88, save->f020_stageName);
    GM_RestoreAreaHistory_8002A784(&save->f030_areaHistory);

    gGcl_gameStateVars_800B44C8 =       save->f040_gameState;
    gGcl_memVars_800b4588 =             save->f100_gcl_vars;
    gGameState_800B4D98 =               save->f040_gameState;
    gGcl_vars_800B3CC8 =                save->f100_gcl_vars;
    *(RdMem*)&gRadioMemory_800BDB38 =   *(RdMem*)&save->f900_radio_memory;

    return 1;
}
