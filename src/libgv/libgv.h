#ifndef LIBGV_H_
#define LIBGV_H_

#include "linker.h"

typedef struct
{
    int mId;
    void *mFileBuffer;
} LibGV_FileRecord;

typedef struct
{
    unsigned short address;
    unsigned short _len;
    unsigned short message[7];
    unsigned short message_len;
} GV_MSG; // from mem leak

struct GV_Messages
{
    int field_0_count;
    GV_MSG field_4_msgs[16];
};

//has to be in a struct to match
typedef struct CacheSystems
{
	LibGV_FileRecord tags[128];
} CacheSystems;

#define MAX_UNITS 512

enum GV_MemoryAllocation_States
{
    GV_MemoryAllocation_States_Free_0 = 0,
    GV_MemoryAllocation_States_Void_1 = 1,
    GV_MemoryAllocation_States_Used_2 = 2,
};

typedef union AllocType
{
    int     type;
    void**  addr;
} AllocType;

typedef struct GV_MemoryAllocation
{
    void *mPDataStart;
    int mAllocType;     //might be union if its > 2 its void** ?
} GV_MemoryAllocation;

enum GV_Heap_Flags
{
    GV_Heap_Flags_Dynamic_1 = 1,
    GV_Heap_Flags_Voided_2 = 2,
    GV_Heap_Flags_Failed_4 = 4,
};

typedef struct GV_Heap
{
    int mFlags;
    void *mStartAddr;
    void *mEndAddr;
    int mUnitsCount;
    GV_MemoryAllocation mAllocs[MAX_UNITS];
} GV_Heap;

extern	void	GV_InitMemorySystemAll_80015AB0() ;
extern	void	GV_InitMemorySystem_80015AF4( int, int, void *, int ) ;
extern	void	*GV_AllocMemory_80015EB8( int, int ) ;
extern	void	*GV_AllocMemory2_80015ED8( int, int, void ** ) ;
extern	void	GV_FreeMemory_80015FD0( int, void * ) ;
extern	void	GV_FreeMemory2_80016078( int, void ** ) ;
extern	void	GV_ClearMemorySystem_80015B4C( int ) ;
extern	void	GV_CheckMemorySystem_80015BF8( int ) ;
extern	void	GV_DumpMemorySystem_80015D48( int ) ;
extern	void	GV_CopyMemory_800160D8( void *, void *, int ) ;
extern	void	GV_ZeroMemory_8001619C( void *, int ) ;
extern	void	*GV_Malloc_8001620C( int ) ;
extern	void	GV_Free_80016230( void * ) ;
extern	void	GV_DelayedFree_80016254( void * ) ;

void *GV_GetMaxFreeMemory_8001627C( int which );
void *GV_SplitMemory( int which, void *addr, int size ); //unsure what function this maps to

	 
void GV_InitResidentMemory_8001642C( void );
void *GV_AllocResidentMemory_800163D8( long size );

#endif // LIBGV_H