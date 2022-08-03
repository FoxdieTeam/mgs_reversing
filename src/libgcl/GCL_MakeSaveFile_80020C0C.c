#include "idaTypes.h"
#include "Script_tbl_map_8002BB44.h"

extern int                  gTotalFrameTime_800AB9E8;
extern GameState_800B4D98   gGameState_800B4D98;
extern GameState_800B4D98   gGcl_gameStateVars_800B44C8;
extern GCL_Vars             gGcl_memVars_800b4588;
extern RadioMemory          gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

char SECTION(".gStageName_800B4D88") gStageName_800B4D88[16];

int          crc32_80020BB4(int a1, unsigned char *a2);
int          GM_GetAreaHistory_8002A730(AreaHistory *a1);
char*        strcpy_8008E768(char *, char *);


int GCL_MakeSaveFile_80020C0C(char *saveBuf)
{
    typedef struct  { short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)]; } RdMem;
    SaveFile        *saveFile;
    SaveGame        *save;

    saveFile = (SaveFile*)saveBuf;
    save = &saveFile->f008_saveGame;

    save->f008_version =                0x60;
    save->f00C_version2 =               0x800;
    save->f010_totalFrameTime =         gTotalFrameTime_800AB9E8;

    // Save time of last save (probably used for shadow mantis demo)
    gGameState_800B4D98.field_BA_last_save_hours =              gGameState_800B4D98.field_B6_total_hours_elapsed;
    gGameState_800B4D98.field_BC_last_save_seconds =            gGameState_800B4D98.field_B8_total_seconds_elapsed;
    gGcl_gameStateVars_800B44C8.field_BA_last_save_hours =      gGameState_800B4D98.field_B6_total_hours_elapsed;
    gGcl_gameStateVars_800B44C8.field_BC_last_save_seconds =    gGameState_800B4D98.field_B8_total_seconds_elapsed;

    gGcl_gameStateVars_800B44C8.field_B0_total_saves =  gGameState_800B4D98.field_B0_total_saves;

    save->f014_padding[0] =             0;
    save->f014_padding[1] =             0;
    save->f014_padding[2] =             0;
 
    strcpy_8008E768(save->f020_stageName, gStageName_800B4D88);
    GM_GetAreaHistory_8002A730(&save->f030_areaHistory);

    save->f040_gameState =              gGcl_gameStateVars_800B44C8;
    save->f100_gcl_vars =               gGcl_memVars_800b4588;
    *(RdMem*)&save->f900_radio_memory = *(RdMem*)&gRadioMemory_800BDB38;

    saveFile->f000_size = (void*)save + sizeof(SaveGame) - (void*)saveBuf;
    saveFile->f004_checksum = crc32_80020BB4(sizeof(SaveGame), (char*)save); // size 0xA38

    return saveFile->f000_size;
}