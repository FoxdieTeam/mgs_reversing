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

/***extern********************************************* ***/
extern void *GV_AllocResidentMemory_800163D8( long size );
/*********************************************************/

#define MAX_TAGS 128
#define RESIDENT_REGION_FLAG 0x1000000

//GV_InitResidentCacheSystem?
//Iterates all the records in the cache system and checks the
//region flag to see if it should be placed in the resident area
void GV_ResidentFileCache_80015484( void )
{
	int i;
	int n_resident_tags;
	LibGV_FileRecord *tag; 
	LibGV_FileRecord *temp_tag;
	tag = (LibGV_FileRecord* )&GV_CacheSystem.tags;
	n_resident_tags = 0;

	for ( i = MAX_TAGS; i > 0; i-- )
	{
		
		if ( tag->mId & RESIDENT_REGION_FLAG )
		{
			n_resident_tags++;
		}
		tag++;
	}

	temp_tag = (LibGV_FileRecord* )&GV_CacheSystem.tags;

	if ( n_resident_tags ) 
	{
		LibGV_FileRecord* resident_tag = GV_AllocResidentMemory_800163D8(n_resident_tags * sizeof(LibGV_FileRecord));
		tag = temp_tag;
	
		GV_ResidentFileRecords_0x800AB934 = resident_tag;
		N_ResidentFileRecords_0x800AB938 = n_resident_tags;

		for ( i= MAX_TAGS; i > 0; i-- )
		{
			if ( tag->mId & RESIDENT_REGION_FLAG )
			{
				*resident_tag = *tag;
				resident_tag++;
			}
			tag++;
		}	
	}
}