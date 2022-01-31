#include "libgv.h"

/**bss*******************************************************/
CacheSystems SECTION(".CacheSystems_800ACEF0") GV_CacheSystem;
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
	tag = &GV_CacheSystem.tags[pos];

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
					tag = GV_CacheSystem.tags;
				}
				i--;
			}
		}
	}

	dword_800AB930 = selectedTag;
	return 0;

}