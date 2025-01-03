#include "libfs.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"

#define FS_DIRNAME_MAX 8

typedef struct _FS_DIR_ENTRY {
    char    name[FS_DIRNAME_MAX];
    int     offset;     // in number of sectors
} FS_DIR_ENTRY;

typedef struct _FS_FILE_TABLE {
    int             start;
    int             size;
    int             count;
    FS_DIR_ENTRY   *dirs;
} FS_FILE_TABLE;

STATIC FS_FILE_TABLE fs_file_table = {};

STATIC int FS_CdStageReadCallback(CDBIOS_TASK *task)
{
    unsigned int size, rounded;

    if (task->sectors_delivered == 0)
    {
        size = *(unsigned int *)task->buffer;
        rounded = (size + 3) / 4;

        task->size = rounded;
        task->remaining = rounded - 512;

        fs_file_table.size = size;
    }

    return 1;
}

void FS_CdStageFileInit(void *pHeap, int startSector)
{
    int size;

    fs_file_table.start = startSector;
    CDBIOS_ReadRequest(pHeap, startSector, FS_SECTOR_SIZE, &FS_CdStageReadCallback);

    while (CDBIOS_ReadSync() > 0)
    {
        mts_wait_vbl(1);
    }

    size = fs_file_table.size;

    if (!fs_file_table.dirs)
    {
        fs_file_table.dirs = GV_AllocResidentMemory(size);
    }

    printf("%X %X %d\n", (unsigned int)pHeap + 4, (unsigned int)fs_file_table.dirs, size);
    GV_CopyMemory((char *)pHeap + 4, fs_file_table.dirs, size);

    fs_file_table.count = size / sizeof(FS_DIR_ENTRY);
}

int FS_CdGetStageFileTop(char *dirname)
{
    FS_DIR_ENTRY *dir;
    int count;

    dir = fs_file_table.dirs;

    for (count = fs_file_table.count; count > 0; count--)
    {
        if (strncmp(dir->name, dirname, FS_DIRNAME_MAX) == 0)
        {
            return dir->offset + fs_file_table.start;
        }
        dir++;
    }
    return -1;
}
