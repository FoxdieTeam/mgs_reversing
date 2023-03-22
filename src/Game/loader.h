#ifndef _LOADER_H_
#define _LOADER_H_

#include "libfs/cdbios.h"
#include "libgv/libgv.h"

typedef struct _STAGE_HEADER
{
    char  field_0;
    char  field_1;
    short field_2_size;
} STAGE_HEADER;

typedef struct _STAGE_CONFIG
{
    unsigned short field_0_hash;
    short          field_2_type;
    int            field_4_size;
} STAGE_CONFIG;

// Circular dependency
struct _CDBIOS_TASK;

typedef struct _STAGE_FILE
{
    int           field_0;
    CDBIOS_TASK  *field_4_pTask;
    void         *field_8_pBuffer;
    STAGE_HEADER *field_C_pHeader;
    void         *field_10_pContents;
    STAGE_CONFIG *field_14_pConfigStart1;
    STAGE_CONFIG *field_18_pConfigEnd1;
    STAGE_CONFIG *field_1C;
    STAGE_CONFIG *field_20_pConfigEnd2;
    int           field_24;
    int           field_28;
    STAGE_CONFIG *field_2C_config;
    STAGE_CONFIG *field_30_current;
    int           field_34_remaining;
} STAGE_FILE;

struct Loader
{
    GV_ACT      base;
    STAGE_FILE *field_20_pStageFile;
    int         field_24_proc_cancel_flags;
    int         field_28_bRunning;
    int         field_2C_counter;
};

struct Loader *Loader_Init_8002E460(const char *pStageName);

#endif // _LOADER_H_
