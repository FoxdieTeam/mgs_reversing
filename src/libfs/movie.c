#include "libfs.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "mts/mts.h"

typedef struct _FS_MOVIE_INFO
{
    int           tablenum;
    FS_MOVIE_FILE files[8];
} FS_MOVIE_INFO;

STATIC FS_MOVIE_INFO *fs_movie_info = NULL;

void FS_MovieFileInit(void *pHeap, int startSector)
{
    int count;
    FS_MOVIE_FILE *file;

    if (startSector < 150)
    {
        printf("movie file is wrong\n");
        fs_movie_info = 0;
        return;
    }

    CDBIOS_ReadRequest(pHeap, startSector, FS_SECTOR_SIZE, NULL);

    while (CDBIOS_ReadSync() > 0)
    {
        mts_wait_vbl(1);
    }

    printf("MOVIE NUM %d\n", *(int *)pHeap);

    if (!fs_movie_info)
    {
        fs_movie_info = GV_AllocResidentMemory(sizeof(FS_MOVIE_INFO));
    }

    GV_CopyMemory(pHeap, fs_movie_info, sizeof(FS_MOVIE_INFO));
    printf("tablenum %d size %d\n", fs_movie_info->tablenum, sizeof(FS_MOVIE_INFO));

    file = fs_movie_info->files;

    for (count = fs_movie_info->tablenum; count > 0; count--)
    {
        file->pos += startSector;
        printf("id %d frame %d pos %d\n", file->id, file->frame, file->pos);
        file++;
    }
}

FS_MOVIE_FILE *FS_GetMovieInfo( unsigned int to_find )
{
    FS_MOVIE_FILE  *file;
    int             count;

    if ( fs_movie_info != 0 )
    {
        count = fs_movie_info->tablenum;
        file = fs_movie_info->files;
        while ( count > 0 )
        {
            count--;
            if ( file->id == to_find )
            {
                return file;
            }
            file++;
        }
    }
    return NULL;
}
