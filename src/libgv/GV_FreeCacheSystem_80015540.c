#include "libgv.h"

/**bss*******************************************************/
extern CacheSystems GV_CacheSystem;
/***********************************************************/

/***$gp*************************************************/
extern LibGV_FileRecord *GV_ResidentFileRecords_0x800AB934;
LibGV_FileRecord *SECTION(".sbss") GV_ResidentFileRecords_0x800AB934;

extern int N_ResidentFileRecords_0x800AB938;
int SECTION(".sbss") N_ResidentFileRecords_0x800AB938;
/******************************************************/

/***extern*************************************/
extern int GV_SetCache_800153C0( int id, void * buf );
/**********************************************/

#define MAX_TAGS 128

void GV_FreeCacheSystem_80015540( void )
{
	int i;
	LibGV_FileRecord* tag;
	tag = GV_CacheSystem.tags;

	for ( i = MAX_TAGS; i > 0; i-- )
	{
		tag->mId = 0;
		tag ++;
	}

	tag = GV_ResidentFileRecords_0x800AB934;

	if ( !tag ) return;

	for ( i = N_ResidentFileRecords_0x800AB938; i > 0; i-- )
	{
		GV_SetCache_800153C0(tag->mId, tag->mFileBuffer);
		tag++;
	}

}