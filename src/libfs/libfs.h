#ifndef _LIBFS_H_
#define _LIBFS_H_

#include "Game/loader.h"

#include "data/data/data.h" // TODO: move FS_FILE_INFO_8009D49C here

int                   CDBIOS_ReadSync_80022854(void);
int                   FS_CdMakePositionTable_80022B5C(void *pHeap, FS_FILE_INFO_8009D49C *pDirRecs);
int                   FS_ResetCdFilePosition_80021E2C(void *pHeap);
void                  CDBIOS_ForceStop_80022864(void);
void                  CDBIOS_Reset_80021F70(void);
void                  CDFS_Init_80021EC4();
void                  FS_CdStageFileInit_80022D00(void *pHeap, int startSector);
void                  FS_MovieFileInit_80023860(void *pHeap, int startSector);
void                  FS_StartDaemon_80014A7C(void);
void                  FS_StreamCD_80023F8C(void);
void                  FS_StreamTaskInit_80023E1C(void);
void                  CDBIOS_ReadRequest_8002280C(void *pHeap, int startSector, int sectorSize, void *fnCallBack);
void                  FS_CdStageProgBinFix_80014AAC(void);
int                   Loader_80023624(struct Loader_Record *pRec);
int                   FS_CdGetStageFileTop_80022DCC(char *pFileName);
int                   Loader_CD_Read_CallBack_80023274(int *a1);
int                   FS_LoadStageSync_800237C0(struct Loader_Record *pRec);
struct Loader_Record *FS_LoadStageRequest_800236E0(const char *pFileName);
void                  FS_LoadStageComplete_80023804(struct Loader_Record *pFileName);
int                   FS_StreamGetData_800240E0(unsigned int);
void                  FS_StreamOpen_80024060();
void                  FS_StreamClose_80024098(void);
int                   CDBIOS_TaskState_80022888(void);

#endif // _LIBFS_H_
