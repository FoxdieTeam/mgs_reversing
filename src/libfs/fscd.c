#include "libfs.h"

#include <stdio.h>
#include "common.h"
#include "mts/mts.h"

extern int FS_DiskNum_800ACBF0;

#include "file.cnf"     // defines fs_file_info

int FS_ResetCdFilePosition(void *pHeap)
{
    int disk_num = FS_CdMakePositionTable(pHeap, fs_file_info);
    printf("Position end\n");
    if (disk_num >= 0)
    {
        printf("DISK %d\n", disk_num);
        FS_CdStageFileInit(pHeap, fs_file_info[FS_FILEID_STAGE].pos);
        FS_MovieFileInit(pHeap, fs_file_info[FS_FILEID_ZMOVIE].pos);
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
    FS_DiskNum_800ACBF0 = FS_ResetCdFilePosition((void *)0x80117000 /*heap_80117000*/); // addi vs ori
    FS_StreamCD();
    FS_StreamTaskInit();
    mts_wait_vbl(2);
}

void FS_LoadFileRequest(int fileno, int offset, int size, void *buffer)
{
    CDBIOS_ReadRequest(buffer, fs_file_info[fileno].pos + offset, size, NULL);
}

int FS_LoadFileSync(void)
{
    return CDBIOS_ReadSync();
}

void MakeFullPath(int name, char *buffer)
{
    /* do nothing */
}
