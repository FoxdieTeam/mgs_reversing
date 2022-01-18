#include "libgv.h"

/***$gp*************************************************/
extern LibGV_FileRecord *dword_800AB930;
LibGV_FileRecord *SECTION(".sbss") dword_800AB930;
/******************************************************/

extern LibGV_FileRecord *GV_FileCacheFind_80015240( int id );

int	GV_SetCache_800153C0( int id, void * buf )
{
	if ( !GV_FileCacheFind_80015240( id ) )
	{
		if (dword_800AB930)
		{
			dword_800AB930->mId  = id;
			dword_800AB930->mFileBuffer = buf;
			return 0;
		}
	}

	return -1;
}