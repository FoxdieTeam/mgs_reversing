#include "psyq.h"
#include "unknown.h"
#include "Game/game.h"

extern int         gTotalFrameTime_800AB9E8;
extern GCL_Vars    gGcl_memVars_800b4588;
extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

extern char gStageName_800B4D88[16];

extern short gGameState_800B4D98[0x60];
extern short gGcl_gameStateVars_800B44C8[0x60];

int GCL_MakeSaveFile_80020C0C(char *saveBuf)
{
    typedef struct
    {
        short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)];
    } RdMem;
    SaveFile *saveFile;
    SaveGame *save;

    saveFile = (SaveFile *)saveBuf;
    save = &saveFile->f008_saveGame;

    save->f008_version = 0x60;
    save->f00C_version2 = 0x800;
    save->f010_totalFrameTime = gTotalFrameTime_800AB9E8;

    // Save time of last save (probably used for shadow mantis demo)
    gGameState_800B4D98[GM_LastSaveHours]           = gGameState_800B4D98[GM_PlaytimeHours];
    gGameState_800B4D98[GM_LastSaveSeconds]         = gGameState_800B4D98[GM_PlaytimeSeconds];
    gGcl_gameStateVars_800B44C8[GM_LastSaveHours]   = gGameState_800B4D98[GM_PlaytimeHours];
    gGcl_gameStateVars_800B44C8[GM_LastSaveSeconds] = gGameState_800B4D98[GM_PlaytimeSeconds];
    gGcl_gameStateVars_800B44C8[GM_SaveCount]       = gGameState_800B4D98[GM_SaveCount];

    save->f014_padding[0] = 0;
    save->f014_padding[1] = 0;
    save->f014_padding[2] = 0;

    strcpy_8008E768(save->f020_stageName, gStageName_800B4D88);
    GM_GetAreaHistory_8002A730(&save->f030_areaHistory);

    memcpy(save->f040_gameState, gGcl_gameStateVars_800B44C8, 0xC0);
    save->f100_gcl_vars = gGcl_memVars_800b4588;
    *(RdMem *)&save->f900_radio_memory = *(RdMem *)&gRadioMemory_800BDB38;

    saveFile->f000_size = (void *)save + sizeof(SaveGame) - (void *)saveBuf;
    saveFile->f004_checksum = crc32_80020BB4(sizeof(SaveGame), (char *)save); // size 0xA38

    return saveFile->f000_size;
}
