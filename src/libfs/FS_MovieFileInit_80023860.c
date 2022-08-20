#include "libfs.h"
#include "libgv/libgv.h"
#include "mts/mts_new.h"

extern FS_MOVIE_FILE_TABLE *fs_movie_file_table_8009D50C;

extern const char aMovieFileIsWro[]; // = "movie file is wrong\n"
extern const char aMovieNumD[]; // = "MOVIE NUM %d\n";
extern const char aTablenumDSizeD[]; // = "tablenum %d size %d\n";
extern const char aIdDFrameDPosD[]; // = "id %d frame %d pos %d\n";

void FS_MovieFileInit_80023860(void *pHeap, int startSector)
{  
    int tablenum;
    FS_MOVIE_FILE *file;
    
    if (startSector < 150)
    {
        mts_printf_8008BBA0(aMovieFileIsWro);
        fs_movie_file_table_8009D50C = 0;
        return;
    }

    CDBIOS_ReadRequest_8002280C(pHeap, startSector, 2048, 0);

    while (CDBIOS_ReadSync_80022854() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    mts_printf_8008BBA0(aMovieNumD, *(int *)pHeap);

    if (!fs_movie_file_table_8009D50C)
    {
        fs_movie_file_table_8009D50C = GV_AllocResidentMemory_800163D8(sizeof(FS_MOVIE_FILE_TABLE));
    }

    GV_CopyMemory_800160D8(pHeap, fs_movie_file_table_8009D50C, sizeof(FS_MOVIE_FILE_TABLE));
    mts_printf_8008BBA0(aTablenumDSizeD, fs_movie_file_table_8009D50C->field_0_tablenum, sizeof(FS_MOVIE_FILE_TABLE));

    file = fs_movie_file_table_8009D50C->field_4_files_8Array;

    for (tablenum = fs_movie_file_table_8009D50C->field_0_tablenum; tablenum > 0; tablenum--)
    {
        file->field_4_pos += startSector;
        mts_printf_8008BBA0(aIdDFrameDPosD, file->field_0_id, file->field_2_frame, file->field_4_pos);
        file++;
    }
}