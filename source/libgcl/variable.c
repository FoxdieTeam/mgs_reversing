#include <stdio.h>
#include "common.h"
#include "libgcl.h"

#include "game/game.h"
#include "menu/menuman.h"   // for RadioMemory
#include "linkvar.h"

short        linkvarbuf[ MAX_LINKVARBUF ];
static short var_buf[ 1024 ];

static short sv_linkvarbuf[ MAX_LINKVARBUF ];
static short sv_var_buf[ 1024 ];

static char stage_name[ 16 ];

extern RadioMemory radio_memory[RADIO_MEMORY_COUNT];

#define SAVE_LINKVAR(buf, var)  (buf[((short*)&var - (short*)&linkvarbuf)])

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
    short       area_history[8];
    short       linkvar[0x60];
    short       varbuf[1024];
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
    typedef struct { short f[sizeof(radio_memory) / sizeof(short)]; } RdMem;

    SAVE_FILE *save_file;
    SAVE_DATA *save_data;

    save_file = (SAVE_FILE *)save_buf;
    save_data = &save_file->data;

    save_data->version = SAVE_VERSION;
    save_data->version2 = SAVE_VERSION2;
    save_data->totalFrameTime = gTotalFrameTime;

    GM_LastSaveHours = GM_PlayTimeHours;
    GM_LastSaveSeconds = GM_PlayTimeSeconds;
    SAVE_LINKVAR(sv_linkvarbuf, GM_LastSaveHours) = GM_PlayTimeHours;
    SAVE_LINKVAR(sv_linkvarbuf, GM_LastSaveSeconds) = GM_PlayTimeSeconds;
    SAVE_LINKVAR(sv_linkvarbuf, GM_SaveCount) = GM_SaveCount;

    save_data->padding[0] = 0;
    save_data->padding[1] = 0;
    save_data->padding[2] = 0;

    strcpy(save_data->stage_name, stage_name);
    GM_GetAreaHistory(save_data->area_history);

    memcpy(save_data->linkvar, sv_linkvarbuf, 0xC0);
    memcpy(save_data->varbuf, sv_var_buf, 1024 * sizeof(short));

    *(RdMem *)&save_data->radio_memory = *(RdMem *)&radio_memory;

    save_file->size = (void *)save_data + sizeof(SAVE_DATA) - (void *)save_buf;
    save_file->checksum = crc32(sizeof(SAVE_DATA), (char *)save_data); // size 0xA38

    return save_file->size;
}

int GCL_SetLoadFile(char *save_buf)
{
    typedef struct { short f[sizeof(radio_memory) / sizeof(short)]; } RdMem;

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
    strcpy(stage_name, save_data->stage_name);
    GM_SetAreaHistory(save_data->area_history);

    memcpy(sv_linkvarbuf, save_data->linkvar, 0xC0);
    memcpy(sv_var_buf, save_data->varbuf, 1024 * sizeof(short));
    memcpy(linkvarbuf, save_data->linkvar, 0xC0);
    memcpy(var_buf, save_data->varbuf, 1024 * sizeof(short));

    *(RdMem *)&radio_memory = *(RdMem *)&save_data->radio_memory;

    return 1;
}

/*---------------------------------------------------------------------------*/

void GCL_InitVar( void )
{
    int option;
    int level;

    option = GM_Configuration;
    level = GM_GameLevel;

    memset( var_buf, 0, 1024 * sizeof(short) );
    memset( linkvarbuf, 0, MAX_LINKVARBUF * sizeof(short) );

    GM_GameLevel = level;
    GM_Configuration = option;
}

void GCL_InitClearVar( void )
{
    memset( var_buf, 0, 1024 * sizeof(short) );
    memset( &GM_SaveArea, 0, 0xb4 );

    GCL_SaveVar();
}

void GCL_SaveVar( void )
{
    memcpy( sv_linkvarbuf, linkvarbuf, MAX_LINKVARBUF * sizeof(short) );
    memcpy( sv_var_buf, var_buf, 1024 * sizeof(short) );
    strcpy( stage_name, GM_GetArea( 0 ) );
}

void GCL_RestoreVar( void )
{
    memcpy( linkvarbuf, sv_linkvarbuf, 0x9C );
    memcpy( var_buf, sv_var_buf, 1024 * sizeof(short) );

    GM_SetArea( GV_StrCode( stage_name ), stage_name );
}

// This function takes a GCL variable and return the associated C variable
//
// gcl_variable example: 0x11800002 (difficulty_level)
//     1 = type variable
//     1 = type short
//    80 = linkvarbuf
//  0002 = offset (not index) into linkvarbuf

char *GCL_GetVar( char *top, int *type_p, int *value_p )
{
    int   gcl_var;
    int   gcl_code;
    char *ptr;

    gcl_var = GCL_GetLong( top );
    gcl_code = GCL_GetVarTypeCode(gcl_var);

    *type_p = gcl_code;
    if (GCL_IsGameStateVar(gcl_var))
    {
        ptr = (char *)linkvarbuf;
    }
    else
    {
        ptr = (char *)&var_buf;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCL_SHORT: // $w:
    case GCL_STRID: // $s:
    case GCL_PROCID:
        if (gcl_code == GCL_SHORT)
        {
            *value_p = *(short *)ptr;
        }
        else
        {
            *value_p = *(unsigned short *)ptr;
        }
        break;

    case GCL_BYTE: // $b:
    case GCL_CHAR: // $c:
        *value_p = (unsigned char)*ptr;
        break;

    case GCL_BOOL: // $f:
        *value_p = (*ptr & GCL_GetFlagBitFlag(gcl_var)) != 0;
        break;

    default:
        break;
    }
    return top + sizeof(gcl_var);
}

char *GCL_SetVar( char *top, int value )
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
        ptr = (char *)&var_buf;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCL_SHORT: // $w:
    case GCL_STRID: // $s:
    case GCL_PROCID:
        *(unsigned short *)ptr = value;
        break;

    case GCL_BYTE: // $b:
    case GCL_CHAR: // $c:
        *ptr = value;
        break;

    case GCL_BOOL: // $f:
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

char *GCL_VarSaveBuffer( char *top )
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
        ptr = (char *)&sv_var_buf;
    }
    ptr += GCL_GetVarOffset(gcl_var);
    switch (gcl_code)
    {
    case GCL_SHORT: // $w:
    case GCL_STRID: // $s:
    case GCL_PROCID:
        *(short *)ptr = (short)value;
        break;

    case GCL_BYTE: // $b:
    case GCL_CHAR: // $c:
        *ptr = (char)value;
        break;

    case GCL_BOOL: // $f:
        bitFlag = GCL_GetFlagBitFlag(gcl_var);
        if (value)
        {
            *ptr |= bitFlag;
        }
        else
        {
            *ptr &= ~bitFlag;
        }

    case GCL_VECTOR:
    case GCL_STRING:
    default:
        break;
    }
    return top + sizeof(gcl_var);
}
