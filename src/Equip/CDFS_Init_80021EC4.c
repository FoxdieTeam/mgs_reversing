#include "linker.h"
#include "mts_new.h"
#include "data.h"

void CDBIOS_Reset_80021F70(void);
void FS_StreamCD_80023F8C(void);
void FS_StreamTaskInit_80023E1C(void);
int FS_ResetCdFilePosition_80021E2C(void*);

void CDBIOS_ReadRequest_8002280C(void *pHeap, int startSector, int sectorSize, void *fnCallBack);

extern unsigned char heap_80117000[];

extern FS_FILE_INFO_8009D49C gDirFiles_8009D49C[];

int SECTION(".gDiskNum_800ACBF0") gDiskNum_800ACBF0;

void CDFS_Init_80021EC4()
{
    CDBIOS_Reset_80021F70();
    gDiskNum_800ACBF0 = FS_ResetCdFilePosition_80021E2C((void*)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD_80023F8C();
    FS_StreamTaskInit_80023E1C();
    mts_wait_vbl_800895F4(2);
}

void FS_LoadFileRequest_80021F0C(int dirFile, int startSector, int endSector, void* pBuffer)
{
    CDBIOS_ReadRequest_8002280C(
               pBuffer,
               gDirFiles_8009D49C[dirFile].field_4_sector + startSector,
               endSector,
               0);
}
