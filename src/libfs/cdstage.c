#include "libfs.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"

FS_FILE_TABLE fs_file_table_8009D4E8 = {};

STATIC int FS_CdStageFileInit_helper(CDBIOS_TASK *task)
{
    unsigned int size, rounded;

    if (task->field_14_sectors_delivered == 0)
    {
        size = *(unsigned int *)task->field_8_buffer;
        rounded = (size + 3) / 4;

        task->field_18_size = rounded;
        task->field_1C_remaining = rounded - 512;

        fs_file_table_8009D4E8.size = size;
    }

    return 1;
}

void FS_CdStageFileInit(void *pHeap, int startSector)
{
    int size;

    fs_file_table_8009D4E8.start = startSector;
    CDBIOS_ReadRequest(pHeap, startSector, 2048, &FS_CdStageFileInit_helper);

    while (CDBIOS_ReadSync() > 0)
    {
        mts_wait_vbl(1);
    }

    size = fs_file_table_8009D4E8.size;

    if (!fs_file_table_8009D4E8.files)
    {
        fs_file_table_8009D4E8.files = GV_AllocResidentMemory(size);
    }

    printf("%X %X %d\n", (unsigned int)pHeap + 4, (unsigned int)fs_file_table_8009D4E8.files, size);
    GV_CopyMemory((char *)pHeap + 4, fs_file_table_8009D4E8.files, size);

    fs_file_table_8009D4E8.count = size / sizeof(FS_FILE);
}

int FS_CdGetStageFileTop(char *filename)
{
    FS_FILE *file;
    int count;

    file = fs_file_table_8009D4E8.files;

    for (count = fs_file_table_8009D4E8.count; count > 0; count--)
    {
        if (!strncmp(file->name, filename, 8))
        {
            return file->offset + fs_file_table_8009D4E8.start;
        }

        file++;
    }

    return -1;
}
