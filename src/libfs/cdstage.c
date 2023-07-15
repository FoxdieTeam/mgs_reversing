#include "libfs.h"

FS_FILE_TABLE fs_file_table_8009D4E8 = {};

int FS_CdStageFileInit_helper_80022CBC(CDBIOS_TASK *task)
{
    unsigned int size, rounded;

    if (task->field_14_sectors_delivered == 0)
    {
        size = *(unsigned int *)task->field_8_buffer;
        rounded = (size + 3) / 4;

        task->field_18_size = rounded;
        task->field_1C_remaining = rounded - 512;

        fs_file_table_8009D4E8.field_4_size = size;
    }

    return 1;
}

void FS_CdStageFileInit_80022D00(void *pHeap, int startSector)
{
    int size;

    fs_file_table_8009D4E8.field_0_start = startSector;
    CDBIOS_ReadRequest_8002280C(pHeap, startSector, 2048, &FS_CdStageFileInit_helper_80022CBC);

    while (CDBIOS_ReadSync_80022854() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    size = fs_file_table_8009D4E8.field_4_size;

    if (!fs_file_table_8009D4E8.field_C_files)
    {
        fs_file_table_8009D4E8.field_C_files = GV_AllocResidentMemory_800163D8(size);
    }

    mts_printf_8008BBA0("%X %X %d\n", (char *)pHeap + 4, fs_file_table_8009D4E8.field_C_files, size);
    GV_CopyMemory_800160D8((char *)pHeap + 4, fs_file_table_8009D4E8.field_C_files, size);

    fs_file_table_8009D4E8.field_8_count = size / sizeof(FS_FILE);
}

int FS_CdGetStageFileTop_80022DCC(char *pFileName)
{
    FS_FILE *file;
    int count;

    file = fs_file_table_8009D4E8.field_C_files;

    for (count = fs_file_table_8009D4E8.field_8_count; count > 0; count--)
    {
        if (!strncmp_8008E7F8(file->field_0_name, pFileName, 8))
        {
            return file->field_4_offset + fs_file_table_8009D4E8.field_0_start;
        }

        file++;
    }

    return -1;
}
