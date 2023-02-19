#include "libfs/libfs.h"

extern FS_MOVIE_FILE_TABLE *fs_movie_file_table_8009D50C;

FS_MOVIE_FILE* FS_GetMovieInfo_8002399C( unsigned int toFind )
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