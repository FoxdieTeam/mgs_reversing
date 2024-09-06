#include "libfs.h"

/* from libfs/file.cnf */
FS_FILE_INFO fs_file_info[] = {
    { "STAGE.DIR",  0 },    // 0
    { "RADIO.DAT",  0 },    // 1
    { "FACE.DAT",   0 },    // 2
    { "ZMOVIE.STR", 0 },    // 3
    { "VOX.DAT",    0 },    // 4
    { "DEMO.DAT",   0 },    // 5
    { "BRF.DAT",    0 },    // 6
    { NULL, 0 }
};

extern int gDiskNum_800ACBF0;

int FS_ResetCdFilePosition(void *pHeap)
{
    int disk_num = FS_CdMakePositionTable(pHeap, fs_file_info);
    printf("Position end\n");
    if (disk_num >= 0)
    {
        printf("DISK %d\n", disk_num);
        FS_CdStageFileInit(pHeap, fs_file_info[FILEID_STAGE].sector);
        FS_MovieFileInit(pHeap, fs_file_info[FILEID_ZMOVIE].sector);
    }
    else
    {
        printf("illegal DISK\n");
    }
    return disk_num;
}

void FS_CDInit(void)
{
    CDBIOS_Reset();
    // TODO: hardcoded pointer
    gDiskNum_800ACBF0 = FS_ResetCdFilePosition((void *)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD();
    FS_StreamTaskInit();
    mts_wait_vbl_800895F4(2);
}

void FS_LoadFileRequest(int file_id, int startSector, int sectorSize, void *pBuffer)
{
    CDBIOS_ReadRequest(pBuffer, fs_file_info[file_id].sector + startSector, sectorSize, 0);
}

int FS_LoadFileSync(void)
{
    return CDBIOS_ReadSync();
}
