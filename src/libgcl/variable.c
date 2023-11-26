#include "linker.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern short gGcl_gameStateVars_800B44C8[0x60];

void GCL_SaveLinkVar_80020B90(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)gGcl_gameStateVars_800B44C8;
    offset = (char *)gameVar - (char *)linkvarbuf;
    *(short *)(addr + offset) = *gameVar;
}

// Used for save files
unsigned int crc32_80020BB4(int len, unsigned char *pData)
{
    unsigned int  crc;
    int           counter;
    unsigned char dataByte;

    crc = 0xffffffff;
    if (len != 0)
    {
        do
        {
            dataByte = *pData;
            crc ^= dataByte; // crc = v0
            pData++;

            counter = 8;

            do
            {
                if ((crc & 1) != 0)
                {
                    crc = crc >> 1 ^ 0xedb88320;
                }
                else
                {
                    crc = crc >> 1;
                }
                counter--;
            } while (counter != 0);
            len--;
        } while (len != 0);
    }
    return ~crc;
}

extern int         gTotalFrameTime_800AB9E8;
extern GCL_Vars    gGcl_memVars_800b4588;
extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

extern char gStageName_800B4D88[16];

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

    GM_LastSaveHours = GM_TotalHours;
    GM_LastSaveSeconds = GM_TotalSeconds;
    GM_LinkVar(gGcl_gameStateVars_800B44C8, GM_LastSaveHours) = GM_TotalHours;
    GM_LinkVar(gGcl_gameStateVars_800B44C8, GM_LastSaveSeconds) = GM_TotalSeconds;
    GM_LinkVar(gGcl_gameStateVars_800B44C8, GM_TotalSaves) = GM_TotalSaves;

    save->f014_padding[0] = 0;
    save->f014_padding[1] = 0;
    save->f014_padding[2] = 0;

    strcpy(save->f020_stageName, gStageName_800B4D88);
    GM_GetAreaHistory_8002A730(&save->f030_areaHistory);

    memcpy(save->f040_gameState, gGcl_gameStateVars_800B44C8, 0xC0);
    save->f100_gcl_vars = gGcl_memVars_800b4588;
    *(RdMem *)&save->f900_radio_memory = *(RdMem *)&gRadioMemory_800BDB38;

    saveFile->f000_size = (void *)save + sizeof(SaveGame) - (void *)saveBuf;
    saveFile->f004_checksum = crc32_80020BB4(sizeof(SaveGame), (char *)save); // size 0xA38

    return saveFile->f000_size;
}

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
        printf("SAVE DATA VERSION ERROR!!\n");
    }
    if (saveFile->f004_checksum != crc32_80020BB4(sizeof(SaveGame), (char *)save))
    {
        printf("CRC ERROR !!\n");
        return 0;
    }

    gTotalFrameTime_800AB9E8 = save->f010_totalFrameTime;
    strcpy(gStageName_800B4D88, save->f020_stageName);
    GM_SetAreaHistory_8002A784(&save->f030_areaHistory);

    memcpy(gGcl_gameStateVars_800B44C8, save->f040_gameState, 0xC0);
    gGcl_memVars_800b4588 = save->f100_gcl_vars;
    memcpy(linkvarbuf, save->f040_gameState, 0xC0);
    gGcl_vars_800B3CC8 = save->f100_gcl_vars;
    *(RdMem *)&gRadioMemory_800BDB38 = *(RdMem *)&save->f900_radio_memory;

    return 1;
}

void GCL_InitVar_80021264()
{
    int flags;
    int difficulty;

    flags = GM_GameStatusFlag;
    difficulty = GM_DifficultyFlag;
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(linkvarbuf, 0, 0xC0);
    GM_DifficultyFlag = difficulty;
    GM_GameStatusFlag = flags;
}

void GCL_InitClearVar_800212CC()
{
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(&GM_CurrentStageFlag, 0, 0xb4);
    GCL_SaveVar_80021314();
}

void GCL_SaveVar_80021314()
{
    memcpy(gGcl_gameStateVars_800B44C8, linkvarbuf, 0xC0);
    gGcl_memVars_800b4588 = gGcl_vars_800B3CC8;
    strcpy(gStageName_800B4D88, GM_GetArea_8002A880(0));
}

void GCL_RestoreVar_80021488()
{
    memcpy(linkvarbuf, gGcl_gameStateVars_800B44C8, 0x9C);
    gGcl_vars_800B3CC8 = gGcl_memVars_800b4588;

    GM_SetArea_8002A7D8(GV_StrCode_80016CCC(gStageName_800B4D88), gStageName_800B4D88);
}

// This function takes a gcl variable and return the C variable associated
//
// gcl_variable example: 0x11800002 (difficulty_level)
//     1 = type variable
//     1 = type short
//    80 = gameState struct
//  0002 = offset in gameState struct

unsigned char *GCL_GetVar_80021634(unsigned char *pScript, int *retCode, int *retValue)
{
    int   gcl_var;
    int   gcl_code;
    char *ptr;

    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    *retCode = gcl_code;
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)linkvarbuf;
    }
    else
    {
        ptr = (char *)&gGcl_vars_800B3CC8;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:         // $w:
    case GCLCODE_HASHED_STRING: // $s:
    case GCLCODE_PROC_CALL:
        if (gcl_code == GCLCODE_SHORT)
        {
            *retValue = *((short *)ptr);
        }
        else
        {
            *retValue = *((unsigned short *)ptr);
        }
        break;

    case GCLCODE_BYTE: // $b:
    case GCLCODE_CHAR:
        *retValue = (unsigned char)*ptr;
        break;

    case GCLCODE_BOOL: // $f:
        *retValue = (*ptr & GCL_GetBoolVarBitFlag(gcl_var)) != 0;
        break;

    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}

unsigned char *GCL_SetVar_8002171C(unsigned char *pScript, unsigned int value)
{
    int   gcl_var, gcl_code;
    char *ptr;
    char  bitFlag;

    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)linkvarbuf;
    }
    else
    {
        ptr = (char *)&gGcl_vars_800B3CC8;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:
    case GCLCODE_HASHED_STRING:
    case GCLCODE_PROC_CALL:
        *(unsigned short *)ptr = value;
        break;

    case GCLCODE_BYTE:
    case GCLCODE_CHAR:
        *ptr = value;
        break;

    case GCLCODE_BOOL:
        bitFlag = GCL_GetBoolVarBitFlag(gcl_var);
        if (value)
        {
            *ptr |= bitFlag;
        }
        else
        {
            *ptr &= ~(char)bitFlag;
        }
        break;

    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}

unsigned char *GCL_VarSaveBuffer_800217F0(unsigned char *pScript)
{
    int   gcl_var, gcl_code, value;
    char *ptr;
    char  bitFlag;

    GCL_GetVar_80021634(pScript, &gcl_code, &value);
    gcl_var = GCL_GetLong(pScript);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)gGcl_gameStateVars_800B44C8;
    }
    else
    {
        ptr = (char *)&gGcl_memVars_800b4588;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCLCODE_SHORT:         // $w:
    case GCLCODE_HASHED_STRING: // $s:
    case GCLCODE_PROC_CALL:
        *(short *)ptr = (short)value;
        break;

    case GCLCODE_BYTE: // $b:
    case GCLCODE_CHAR:
        *ptr = (char)value;
        break;

    case GCLCODE_BOOL: // $f:
        bitFlag = GCL_GetBoolVarBitFlag(gcl_var);
        if (value)
        {
            *ptr |= bitFlag;
        }
        else
        {
            *ptr &= ~bitFlag;
        }

    case 5:
    case GCLCODE_STRING:
    default:
        break;
    }
    return pScript + sizeof(gcl_var);
}
