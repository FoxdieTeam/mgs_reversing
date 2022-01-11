#include "libgv.h"

//has to be in a struct to match
typedef struct CacheWork
{
	LibGV_FileRecord tags[128];
} CacheWork;

/**bss*******************************************************/
CacheWork SECTION(".CacheWork_800ACEF0") GV_CacheWork;
/***********************************************************/

/***$gp*************************************************/
extern LibGV_FileRecord *dword_800AB930;
LibGV_FileRecord *SECTION(".sbss") dword_800AB930;
/******************************************************/

LibGV_FileRecord *GV_FileCacheFind_80015240 ( int id )
{

	LibGV_FileRecord *tag;
	LibGV_FileRecord *selectedTag;
	int pos;
	int i;
	int remainder;
	int cacheID;

	selectedTag = 0;
	pos = id % 0x80;
	tag = &GV_CacheWork.tags[pos];

	remainder = 0x80 - pos;
	i = 0x80;

	while ( i > 0 )
	{
		cacheID = tag->mId & 0xFFFFFF;

		if (!cacheID)
		{
			if ( selectedTag == 0 )
			{
				selectedTag = tag;
			}
			break;
		}
		else
		{
			remainder--;
			
			if ( cacheID == id )
			{
				return tag;
			}
			else
			{
				tag++;
				if ( !remainder )
				{
					tag = GV_CacheWork.tags;
				}
				i--;
			}
		}
	}

	dword_800AB930 = selectedTag;
	return 0;

}