#include <stdio.h>
#include "common.h"
#include "libgcl.h"

#include "game/game.h"      // for AreaHistory
#include "menu/menuman.h"   // for RadioMemory
#include "linkvar.h"

extern short linkvarbuf[0x60];
extern short sv_linkvarbuf[0x60];

extern GCL_Vars     gGcl_vars_800B3CC8;
extern GCL_Vars     gGcl_memVars_800b4588;
extern char         gStageName_800B4D88[16];
extern RadioMemory  gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

/*---------------------------------------------------------------------------*/

#define SAVE_VERSION    0x60
#define SAVE_VERSION2   0x800

typedef struct SAVE_DATA
{
    int         version;
    int         version2;
    int         totalFrameTime;
    int         padding[3];
    char        stage_name[16];
    AreaHistory area_history;
    short       varbuf[0x60];
    GCL_Vars    gcl_vars;
    RadioMemory radio_memory[RADIO_MEMORY_COUNT];
} SAVE_DATA; // size 0xA38

typedef struct SAVE_FILE
{
    int         size;
    int         checksum;
    SAVE_DATA   data;
} SAVE_FILE;

/*---------------------------------------------------------------------------*/

void GCL_SaveLinkVar(short *gameVar)
{
    char *addr;
    int   offset;

    addr = (char *)sv_linkvarbuf;
    offset = (char *)gameVar - (char *)linkvarbuf;
    *(short *)(addr + offset) = *gameVar;
}

// Used for save files
static unsigned int crc32(int len, unsigned char *ptr)
{
    unsigned int  crc;
    int           counter;

    crc = 0xffffffff;
    if (len != 0)
    {
        do {
            crc ^= *ptr++;
            counter = 8;

            do {
                if ((crc & 1) != 0)
                {
                    crc = crc >> 1 ^ 0xedb88320;
                }
                else
                {
                    crc = crc >> 1;
                }
            } while (--counter != 0);
        } while (--len != 0);
    }
    return ~crc;
}

int GCL_MakeSaveFile(char *save_buf)
{
    typedef struct { short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)]; } RdMem;

    SAVE_FILE *save_file;
    SAVE_DATA *save_data;

    save_file = (SAVE_FILE *)save_buf;
    save_data = &save_file->data;

    save_data->version = SAVE_VERSION;
    save_data->version2 = SAVE_VERSION2;
    save_data->totalFrameTime = gTotalFrameTime;

    GM_LastSaveHours = GM_TotalHours;
    GM_LastSaveSeconds = GM_TotalSeconds;
    GM_LinkVar(sv_linkvarbuf, GM_LastSaveHours) = GM_TotalHours;
    GM_LinkVar(sv_linkvarbuf, GM_LastSaveSeconds) = GM_TotalSeconds;
    GM_LinkVar(sv_linkvarbuf, GM_TotalSaves) = GM_TotalSaves;

    save_data->padding[0] = 0;
    save_data->padding[1] = 0;
    save_data->padding[2] = 0;

    strcpy(save_data->stage_name, gStageName_800B4D88);
    GM_GetAreaHistory(&save_data->area_history);

    memcpy(save_data->varbuf, sv_linkvarbuf, 0xC0);
    save_data->gcl_vars = gGcl_memVars_800b4588;
    *(RdMem *)&save_data->radio_memory = *(RdMem *)&gRadioMemory_800BDB38;

    save_file->size = (void *)save_data + sizeof(SAVE_DATA) - (void *)save_buf;
    save_file->checksum = crc32(sizeof(SAVE_DATA), (char *)save_data); // size 0xA38

    return save_file->size;
}

int GCL_SetLoadFile(char *save_buf)
{
    typedef struct { short f[sizeof(gRadioMemory_800BDB38) / sizeof(short)]; } RdMem;

    SAVE_FILE *save_file;
    SAVE_DATA *save_data;

    save_file = (SAVE_FILE *)save_buf;
    save_data = &save_file->data;

    if ((save_data->version != SAVE_VERSION) || (save_data->version2 != SAVE_VERSION2))
    {
        printf("SAVE DATA VERSION ERROR!!\n");
    }
    if (save_file->checksum != crc32(sizeof(SAVE_DATA), (char *)save_data))
    {
        printf("CRC ERROR !!\n");
        return 0;
    }

    gTotalFrameTime = save_data->totalFrameTime;
    strcpy(gStageName_800B4D88, save_data->stage_name);
    GM_SetAreaHistory(&save_data->area_history);

    memcpy(sv_linkvarbuf, save_data->varbuf, 0xC0);
    gGcl_memVars_800b4588 = save_data->gcl_vars;
    memcpy(linkvarbuf, save_data->varbuf, 0xC0);
    gGcl_vars_800B3CC8 = save_data->gcl_vars;
    *(RdMem *)&gRadioMemory_800BDB38 = *(RdMem *)&save_data->radio_memory;

    return 1;
}

void GCL_InitVar(void)
{
    int option;
    int difficulty;

    option = GM_OptionFlag;
    difficulty = GM_DifficultyFlag;

    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(linkvarbuf, 0, 0xC0);

    GM_DifficultyFlag = difficulty;
    GM_OptionFlag = option;
}

void GCL_InitClearVar(void)
{
    gGcl_vars_800B3CC8 = ( GCL_Vars ){{ 0 }};
    memset(&GM_CurrentStageFlag, 0, 0xb4);
    GCL_SaveVar();
}

void GCL_SaveVar(void)
{
    memcpy(sv_linkvarbuf, linkvarbuf, 0xC0);
    gGcl_memVars_800b4588 = gGcl_vars_800B3CC8;
    strcpy(gStageName_800B4D88, GM_GetArea(0));
}

void GCL_RestoreVar(void)
{
    memcpy(linkvarbuf, sv_linkvarbuf, 0x9C);
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
        ptr = (char *)sv_linkvarbuf;
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
