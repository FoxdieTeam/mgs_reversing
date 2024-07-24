#include "libfs.h"

FS_FILE_INFO fs_file_info_8009D49C[] = {
    {"STAGE.DIR", 0},
    {"RADIO.DAT", 0},
    {"FACE.DAT", 0},
    {"ZMOVIE.STR", 0},
    {"VOX.DAT", 0},
    {"DEMO.DAT", 0},
    {"BRF.DAT", 0},
    {NULL, 0}
};

extern int gDiskNum_800ACBF0;

int FS_ResetCdFilePosition_80021E2C(void *pHeap)
{
    int disk_num = FS_CdMakePositionTable_80022B5C(pHeap, fs_file_info_8009D49C);
    printf("Position end\n");
    if (disk_num >= 0)
    {
        printf("DISK %d\n", disk_num);
        FS_CdStageFileInit_80022D00(pHeap, fs_file_info_8009D49C[0].sector);
        FS_MovieFileInit_80023860(pHeap, fs_file_info_8009D49C[3].sector);
    }
    else
    {
        printf("illegal DISK\n");
    }
    return disk_num;
}

void CDFS_Init_80021EC4()
{
    CDBIOS_Reset_80021F70();
    // TODO: hardcoded pointer
    gDiskNum_800ACBF0 = FS_ResetCdFilePosition_80021E2C((void *)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD_80023F8C();
    FS_StreamTaskInit_80023E1C();
    mts_wait_vbl_800895F4(2);
}

void FS_LoadFileRequest_80021F0C(int dirFile, int startSector, int sectorSize, void *pBuffer)
{
    CDBIOS_ReadRequest_8002280C(pBuffer, fs_file_info_8009D49C[dirFile].sector + startSector, sectorSize, 0);
}

int FS_LoadFileSync_80021F48(void)
{
    return CDBIOS_ReadSync_80022854();
}