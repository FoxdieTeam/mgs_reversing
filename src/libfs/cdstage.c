#include "libfs.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"        // for mts_wait_vbl
#include "libgv/libgv.h"    // for GV_xxxMemory

/*---------------------------------------------------------------------------*/

#define FS_DIRNAME_MAX  8
#define FS_STAGEDIR_MAX 170     // ((FS_SECTOR_SIZE - 4) / sizeof(FS_DIR_ENTRY))

typedef struct _FS_DIR_ENTRY {
    char    name[FS_DIRNAME_MAX];   // ASCII stage name
    int     offset;                 // in number of sectors
} FS_DIR_ENTRY;

typedef struct _FS_DIR_INFO {
    int             pos;            // LBA position of stage archive
    int             table_size;     // size of the directory table
    int             n_stages;       // number of stage directories
    FS_DIR_ENTRY   *table_buf;      // in-memory copy of the dir table
} FS_DIR_INFO;

STATIC FS_DIR_INFO fs_dir_info = {};

// NOTE: This code registers a single DIR-format archive and keeps it for
// the full duration of the game's runtime. This is only cleared at shutdown,
// since there are no deinitialization routines for LibFS's position tables.
//
// Theoretically, if there were more than one DIR-format archives present on
// the CD-ROM, the game could dynamically select which to register at startup,
// however, the program is currently hard-coded to load only "STAGE.DIR".

/*---------------------------------------------------------------------------*/

STATIC int FS_CdStageReadCallback(CDBIOS_TASK *task)
{
    unsigned int size, rounded;

    if (task->sectors_delivered == 0)
    {
        size = *(unsigned int *)task->buffer;
        rounded = (size + 3) / 4;

        task->size = rounded;
        task->remaining = rounded - 512;

        fs_dir_info.table_size = size;
    }
    return 1;
}

/**
 * @brief       Registers the DIR archive to read from.
 *
 * @note        Because the dir entry table is expected to fit within
 *              the first 2048 bytes (1 sector) of the file, archives
 *              can contain a maximum of 170 stage entries.
 *
 *              Therefore, the the maximum size of the entry table is
 *              2040 bytes (sizeof(FS_DIR_ENTRY) * FS_STAGEDIR_MAX).
 *
 * @param[out]  buffer      temporary work buffer
 * @param[in]   sector      starting LBA position of the DIR archive
 */
void FS_CdStageFileInit(void *buffer, int sector)
{
    int table_size;

    fs_dir_info.pos = sector;
    CDBIOS_ReadRequest(buffer, sector, FS_SECTOR_SIZE, &FS_CdStageReadCallback);

    while (CDBIOS_ReadSync() > 0)
    {
        mts_wait_vbl(1);
    }

    table_size = fs_dir_info.table_size;

    if (fs_dir_info.table_buf == NULL)
    {
        fs_dir_info.table_buf = GV_AllocResidentMemory(table_size);
    }

    printf("%X %X %d\n",
        (unsigned int)buffer + 4,               // src address
        (unsigned int)fs_dir_info.table_buf,    // dest address
        table_size);                            // size

    GV_CopyMemory((char *)buffer + 4, fs_dir_info.table_buf, table_size);

    fs_dir_info.n_stages = table_size / sizeof(FS_DIR_ENTRY);
}

/**
 * Gets the starting offset (logical block address) of a requested
 * stage block within the registered DIR archive.
 *
 * @param       dirname     name of the requested stage
 *
 * @return      LBA position of the requested stage block.
 *              Returns -1 if the stage is not found.
 */
int FS_CdGetStageFileTop(char *dirname)
{
    FS_DIR_ENTRY *dir;
    int count;

    dir = fs_dir_info.table_buf;

    for (count = fs_dir_info.n_stages; count > 0; count--)
    {
        if (strncmp(dir->name, dirname, FS_DIRNAME_MAX) == 0)
        {
            return dir->offset + fs_dir_info.pos;
        }
        dir++;
    }
    return -1;
}
