#include "libfs.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"

extern FS_MOVIE_FILE_TABLE *fs_movie_file_table_8009D50C;

void FS_MovieFileInit_80023860(void *pHeap, int startSector)
{
    int tablenum;
    FS_MOVIE_FILE *file;

    if (startSector < 150)
    {
        printf("movie file is wrong\n");
        fs_movie_file_table_8009D50C = 0;
        return;
    }

    CDBIOS_ReadRequest_8002280C(pHeap, startSector, 2048, 0);

    while (CDBIOS_ReadSync_80022854() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    printf("MOVIE NUM %d\n", *(int *)pHeap);

    if (!fs_movie_file_table_8009D50C)
    {
        fs_movie_file_table_8009D50C = GV_AllocResidentMemory(sizeof(FS_MOVIE_FILE_TABLE));
    }

    GV_CopyMemory(pHeap, fs_movie_file_table_8009D50C, sizeof(FS_MOVIE_FILE_TABLE));
    printf("tablenum %d size %d\n", fs_movie_file_table_8009D50C->field_0_tablenum, sizeof(FS_MOVIE_FILE_TABLE));

    file = fs_movie_file_table_8009D50C->field_4_files_8Array;

    for (tablenum = fs_movie_file_table_8009D50C->field_0_tablenum; tablenum > 0; tablenum--)
    {
        file->field_4_pos += startSector;
        printf("id %d frame %d pos %d\n", file->field_0_id, file->field_2_frame, file->field_4_pos);
        file++;
    }
}

FS_MOVIE_FILE * FS_GetMovieInfo_8002399C( unsigned int toFind )
{
    FS_MOVIE_FILE *pIter;
    int             count;

    if ( fs_movie_file_table_8009D50C != 0 )
    {
        count = fs_movie_file_table_8009D50C->field_0_tablenum;
        pIter = fs_movie_file_table_8009D50C->field_4_files_8Array;
        while ( count > 0 )
        {
            count--;
            if ( pIter->field_0_id == toFind )
            {
                return pIter;
            }
            pIter++;
        }
    }
    return 0;
}