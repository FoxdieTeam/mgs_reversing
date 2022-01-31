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

#define MAX_TAGS 128

// initialises cache system by setting all entries to 0
// also sets the resident caches entries to 0 as well
void GV_InitCacheSystem_80015458( void )
{
	int i;
	LibGV_FileRecord *tag = GV_CacheSystem.tags;

	for ( i = MAX_TAGS; i > 0; i-- )
	{
		tag->mId = 0;
		tag++;
	}

	GV_ResidentFileRecords_0x800AB934 = 0;
	N_ResidentFileRecords_0x800AB938  = 0;
}
