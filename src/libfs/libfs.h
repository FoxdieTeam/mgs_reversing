#ifndef _LIBFS_H_
#define _LIBFS_H_

#include "cdbios.h"
#include "Game/loader.h"

typedef struct _FS_FILE_INFO_8009D49C
{
    const char *pDatName;
    int         field_4_sector;
} FS_FILE_INFO_8009D49C;

// TODO: This is a stage file
typedef struct _FS_FILE {
    char field_0_name[8];
    int  field_4_offset;
} FS_FILE;

typedef struct _FS_FILE_TABLE {
    int      field_0_start;
    int      field_4_size;
    int      field_8_count;
    FS_FILE *field_C_files;
} FS_FILE_TABLE;

typedef struct _FS_MOVIE_FILE
{
    unsigned short field_0_id;
    unsigned short field_2_frame;
    int            field_4_pos;
} FS_MOVIE_FILE;

typedef struct _FS_MOVIE_FILE_TABLE
{
    int           field_0_tablenum;
    FS_MOVIE_FILE field_4_files_8Array[8];
} FS_MOVIE_FILE_TABLE;

typedef struct _FS_MEMFILE
{
    int field_0;
    int field_4;
    int field_8;
} FS_MEMFILE;

typedef char * (*TFsCallback)(char *);
typedef void (*TFsSoundCallback)(void);

int         CDBIOS_ReadSync_80022854(void);
int         FS_CdMakePositionTable_80022B5C(char *pHeap, FS_FILE_INFO_8009D49C *pDirRecs);
int         FS_ResetCdFilePosition_80021E2C(void *pHeap);
void        CDBIOS_ForceStop_80022864(void);
int         CDBIOS_Reset_80021F70(void);
void        CDFS_Init_80021EC4();
void        FS_CdStageFileInit_80022D00(void *pHeap, int startSector);
void        FS_MovieFileInit_80023860(void *pHeap, int startSector);
void        FS_StartDaemon_80014A7C(void);
void        FS_StreamCD_80023F8C(void);
void        FS_StreamTaskInit_80023E1C(void);
void        CDBIOS_ReadRequest_8002280C(void *pHeap, unsigned int startSector, unsigned int sectorSize, void *fnCallBack);
void        FS_CdStageProgBinFix_80014AAC(void);
int         Loader_80023624(STAGE_FILE *pStageFile);
int         FS_CdGetStageFileTop_80022DCC(char *pFileName);
int         Loader_CD_Read_CallBack_80023274(CDBIOS_TASK *pTask);
int         FS_LoadStageSync_800237C0(STAGE_FILE *pStageFile);
STAGE_FILE *FS_LoadStageRequest_800236E0(const char *pFileName);
void        FS_LoadStageComplete_80023804(STAGE_FILE *pStageFile);
void       *FS_StreamGetData_800240E0(int);
void        FS_StreamOpen_80024060();
void        FS_StreamClose_80024098(void);
int         CDBIOS_TaskState_80022888(void);
int         FS_StreamTaskState_80023E0C(void);
void        FS_StreamStop_80024028();
void        FS_LoadFileRequest_80021F0C(int dirFile, int startSector, int sectorSize, void *pBuffer);
int         FS_LoadFileSync_80021F48(void);
void        CDBIOS_TaskStart_800227A8(void);
void        CDBIOS_Main_80022264(void);
int         FS_CdStageFileInit_helper_80022CBC(CDBIOS_TASK *task);
int         FS_CdMakePositionTable_helper_8002297C(char *pDirBlock, FS_FILE_INFO_8009D49C *pDirRecs);
int         FS_StreamGetTop_80023F94(int is_movie);
void        FS_StreamTaskStart_80023D94(int param_1);
int         FS_StreamInit_80023FD4(void *pHeap, int heapSize);
void        FS_StreamTickStart_800243D8();
int         FS_StreamGetTick_80024420(void);
int         FS_StreamIsForceStop_800243C8(void);
void        FS_StreamSoundMode_80024404();
int         FS_StreamIsEnd_800240D0(void);
int         FS_StreamSync_80023E24();
void        sub_80023C40(void);
int         sub_800239E8(CDBIOS_TASK *pTask);
int         Loader_helper2_80023460(STAGE_FILE *);
int         Loader_helper_8002336C(STAGE_FILE *, int);
int         FS_StreamGetEndFlag_800243B8(void);
void        MakeFullPath_80021F68(int, char *);
int         FS_StreamGetSize_80024188(int *ptr);
void        FS_EnableMemfile_800799A8(int cache_read_enable, int clear_cache_buffer);

int PCinit_80014B14(void);
int PCopen_80014B1C(const char *name, int flags, int perms);
int PCread_80014B24(int fd, char *buff, int len);
int PCclose_80014B2C(int fd);


#endif // _LIBFS_H_
