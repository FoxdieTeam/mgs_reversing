#include "mts/mts_new.h"
#include "psyq.h"
#include "unknown.h"
#include "Game/game.h"

extern int         gTotalFrameTime_800AB9E8;
extern GCL_Vars    gGcl_memVars_800b4588;
extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];
extern char        gStageName_800B4D88[16];
extern GCL_Vars    gGcl_vars_800B3CC8;

int GCL_SetLoadFile_80020EAC(char *saveBuf)
{
    typedef struct
    {
        short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)];
    } RdMem;
    SaveFile *saveFile;
    SaveGame *save;

    saveFile = (SaveFile *)saveBuf;
    save = &saveFile->f008_saveGame;

    if ((save->f008_version != 0x60) || (save->f00C_version2 != 0x800))
    {
        mts_printf_8008BBA0("SAVE DATA VERSION ERROR!!\n");
    }
    if (saveFile->f004_checksum != crc32_80020BB4(sizeof(SaveGame), (char *)save))
    {
        mts_printf_8008BBA0("CRC ERROR !!\n\x0\x0\x0");
        return 0;
    }

    gTotalFrameTime_800AB9E8 = save->f010_totalFrameTime;
    strcpy_8008E768(gStageName_800B4D88, save->f020_stageName);
    GM_SetAreaHistory_8002A784(&save->f030_areaHistory);

    memcpy(gGcl_gameStateVars_800B44C8, save->f040_gameState, 0xC0);
    gGcl_memVars_800b4588 = save->f100_gcl_vars;
    memcpy(gGameState_800B4D98, save->f040_gameState, 0xC0);
    gGcl_vars_800B3CC8 = save->f100_gcl_vars;
    *(RdMem *)&gRadioMemory_800BDB38 = *(RdMem *)&save->f900_radio_memory;

    return 1;
}
