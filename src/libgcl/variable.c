#include <stdio.h>
#include "common.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern short sv_linkvarbuf_800B44C8[0x60];

void GCL_SaveLinkVar(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)sv_linkvarbuf_800B44C8;
    offset = (char *)gameVar - (char *)linkvarbuf;
    *(short *)(addr + offset) = *gameVar;
}

// Used for save files
STATIC unsigned int crc32(int len, unsigned char *ptr)
{
    unsigned int  crc;
    int           counter;
    unsigned char dataByte;

    crc = 0xffffffff;
    if (len != 0)
    {
        do
        {
            dataByte = *ptr;
            crc ^= dataByte; // crc = v0
            ptr++;

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

extern short sv_linkvarbuf_800B44C8[0x60];

int GCL_MakeSaveFile(char *saveBuf)
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
    GM_LinkVar(sv_linkvarbuf_800B44C8, GM_LastSaveHours) = GM_TotalHours;
    GM_LinkVar(sv_linkvarbuf_800B44C8, GM_LastSaveSeconds) = GM_TotalSeconds;
    GM_LinkVar(sv_linkvarbuf_800B44C8, GM_TotalSaves) = GM_TotalSaves;

    save->f014_padding[0] = 0;
    save->f014_padding[1] = 0;
    save->f014_padding[2] = 0;

    strcpy(save->f020_stageName, gStageName_800B4D88);
    GM_GetAreaHistory(&save->f030_areaHistory);

    memcpy(save->f040_varbuf, sv_linkvarbuf_800B44C8, 0xC0);
    save->f100_gcl_vars = gGcl_memVars_800b4588;
    *(RdMem *)&save->f900_radio_memory = *(RdMem *)&gRadioMemory_800BDB38;

    saveFile->f000_size = (void *)save + sizeof(SaveGame) - (void *)saveBuf;
    saveFile->f004_checksum = crc32(sizeof(SaveGame), (char *)save); // size 0xA38

    return saveFile->f000_size;
}

extern char        gStageName_800B4D88[16];
extern GCL_Vars    gGcl_vars_800B3CC8;

int GCL_SetLoadFile(char *saveBuf)
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
    if (saveFile->f004_checksum != crc32(sizeof(SaveGame), (char *)save))
    {
        printf("CRC ERROR !!\n");
        return 0;
    }

    gTotalFrameTime_800AB9E8 = save->f010_totalFrameTime;
    strcpy(gStageName_800B4D88, save->f020_stageName);
    GM_SetAreaHistory(&save->f030_areaHistory);

    memcpy(sv_linkvarbuf_800B44C8, save->f040_varbuf, 0xC0);
    gGcl_memVars_800b4588 = save->f100_gcl_vars;
    memcpy(linkvarbuf, save->f040_varbuf, 0xC0);
    gGcl_vars_800B3CC8 = save->f100_gcl_vars;
    *(RdMem *)&gRadioMemory_800BDB38 = *(RdMem *)&save->f900_radio_memory;

    return 1;
}

void GCL_InitVar(void)
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

void GCL_InitClearVar(void)
{
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(&GM_CurrentStageFlag, 0, 0xb4);
    GCL_SaveVar();
}

void GCL_SaveVar(void)
{
    memcpy(sv_linkvarbuf_800B44C8, linkvarbuf, 0xC0);
    gGcl_memVars_800b4588 = gGcl_vars_800B3CC8;
    strcpy(gStageName_800B4D88, GM_GetArea(0));
}

void GCL_RestoreVar(void)
{
    memcpy(linkvarbuf, sv_linkvarbuf_800B44C8, 0x9C);
    gGcl_vars_800B3CC8 = gGcl_memVars_800b4588;

    GM_SetArea(GV_StrCode(gStageName_800B4D88), gStageName_800B4D88);
}

// This function takes a GCL variable and return the associated C variable
//
// gcl_variable example: 0x11800002 (difficulty_level)
//     1 = type variable
//     1 = type short
//    80 = linkvarbuf
//  0002 = offset (not index) into linkvarbuf

unsigned char *GCL_GetVar(unsigned char *top, int *type_p, int *value_p)
{
    int   gcl_var;
    int   gcl_code;
    char *ptr;

    gcl_var = GCL_GetLong(top);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    *type_p = gcl_code;
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
            *value_p = *((short *)ptr);
        }
        else
        {
            *value_p = *((unsigned short *)ptr);
        }
        break;

    case GCLCODE_BYTE: // $b:
    case GCLCODE_CHAR:
        *value_p = (unsigned char)*ptr;
        break;

    case GCLCODE_FLAG: // $f:
        *value_p = (*ptr & GCL_GetFlagBitFlag(gcl_var)) != 0;
        break;

    default:
        break;
    }
    return top + sizeof(gcl_var);
}

unsigned char *GCL_SetVar(unsigned char *top, unsigned int value)
{
    int   gcl_var, gcl_code;
    char *ptr;
    char  bitFlag;

    gcl_var = GCL_GetLong(top);
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

    case GCLCODE_FLAG:
        bitFlag = GCL_GetFlagBitFlag(gcl_var);
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
    return top + sizeof(gcl_var);
}

unsigned char *GCL_VarSaveBuffer(unsigned char *top)
{
    int   gcl_var, gcl_code, value;
    char *ptr;
    char  bitFlag;

    GCL_GetVar(top, &gcl_code, &value);
    gcl_var = GCL_GetLong(top);
    gcl_code = GCL_GetVarTypeCode(gcl_var);
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)sv_linkvarbuf_800B44C8;
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

    case GCLCODE_FLAG: // $f:
        bitFlag = GCL_GetFlagBitFlag(gcl_var);
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
    return top + sizeof(gcl_var);
}
