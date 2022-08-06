#ifndef _LIBFS_H_
#define _LIBFS_H_

struct Loader_Rec_2
{
    char field_0;
    char field_1;
};

struct Loader_Record // TODO: Share in a header
{
    int                  field_0;
    int                  field_4; // cnf count?
    struct Loader_Rec_2 *field_8_p2Alloc;
    int                  field_C; // str ptr?
    int                  field_10;
    int                  field_14; // last size?
    int                  field_18; // state ?
    int                  field_1C; // cnf ptr?
    int                  field_20;
    int                  field_24;
    int                  field_28;
    int                  field_2C;
    int                  field_30;
    int                  field_34;
};

#include "data/data/data.h" // TODO: move FS_FILE_INFO_8009D49C here

int  CDBIOS_ReadSync_80022854(void);
int  FS_CdMakePositionTable_80022B5C(void *pHeap, FS_FILE_INFO_8009D49C *pDirRecs);
int  FS_ResetCdFilePosition_80021E2C(void *pHeap);
void CDBIOS_ForceStop_80022864(void);
void CDBIOS_Reset_80021F70(void);
void CDFS_Init_80021EC4();
void FS_CdStageFileInit_80022D00(void *pHeap, int startSector);
void FS_MovieFileInit_80023860(void *pHeap, int startSector);
void FS_StartDaemon_80014A7C(void);
void FS_StreamCD_80023F8C(void);
void FS_StreamTaskInit_80023E1C(void);
void CDBIOS_ReadRequest_8002280C(void *pHeap, int startSector, int sectorSize, void *fnCallBack);
void FS_CdStageProgBinFix_80014AAC(void);
int  Loader_80023624(struct Loader_Record *pRec);
int  FS_CdGetStageFileTop_80022DCC(char *pFileName);
int  Loader_CD_Read_CallBack_80023274(int *a1);

#endif // _LIBFS_H_
