#include "libfs.h"
#include "libgv/libgv.h"
#include "mts/mts.h"

extern FS_MOVIE_FILE_TABLE *fs_movie_file_table_8009D50C;

void FS_MovieFileInit(void *pHeap, int startSector)
{
    int tablenum;
    FS_MOVIE_FILE *file;

    if (startSector < 150)
    {
        printf("movie file is wrong\n");
        fs_movie_file_table_8009D50C = 0;
        return;
    }

    CDBIOS_ReadRequest(pHeap, startSector, 2048, 0);

    while (CDBIOS_ReadSync() > 0)
    {
        mts_wait_vbl(1);
    }

    printf("MOVIE NUM %d\n", *(int *)pHeap);

    if (!fs_movie_file_table_8009D50C)
    {
        fs_movie_file_table_8009D50C = GV_AllocResidentMemory(sizeof(FS_MOVIE_FILE_TABLE));
    }

    GV_CopyMemory(pHeap, fs_movie_file_table_8009D50C, sizeof(FS_MOVIE_FILE_TABLE));
    printf("tablenum %d size %d\n", fs_movie_file_table_8009D50C->tablenum, sizeof(FS_MOVIE_FILE_TABLE));

    file = fs_movie_file_table_8009D50C->files;

    for (tablenum = fs_movie_file_table_8009D50C->tablenum; tablenum > 0; tablenum--)
    {
        file->pos += startSector;
        printf("id %d frame %d pos %d\n", file->id, file->frame, file->pos);
        file++;
    }
}

FS_MOVIE_FILE *FS_GetMovieInfo( unsigned int toFind )
{
    FS_MOVIE_FILE  *pIter;
    int             count;

    if ( fs_movie_file_table_8009D50C != 0 )
    {
        count = fs_movie_file_table_8009D50C->tablenum;
        pIter = fs_movie_file_table_8009D50C->files;
        while ( count > 0 )
        {
            count--;
            if ( pIter->id == toFind )
            {
                return pIter;
            }
            pIter++;
        }
    }
    return 0;
}
