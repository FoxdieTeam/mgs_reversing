#ifndef LIBGV_H_
#define LIBGV_H_

#include "linker.h"
#include "mts_new.h"

#include <sys/types.h>
#include <LIBGTE.H>

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

typedef struct
{
    int field_0_count;
    GV_MSG field_4_msgs[16];
} GV_Messages;

//has to be in a struct to match
typedef struct CacheSystems
{
	LibGV_FileRecord tags[128];
} CacheSystems;

#define MAX_UNITS 512
#define GV_NORMAL_MEMORY 2 // seen from leaks

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

typedef	struct	{
	unsigned short	status ;	 
	unsigned short	press ;		 
	unsigned short	release ;	 
	unsigned short	quick ;		 
	short		    dir ;		 

	short		    analog ;
	unsigned char	right_dx ;
	unsigned char	right_dy ;
	unsigned char	left_dx ;
	unsigned char	left_dy ;
} GV_PAD ;

enum	{
	GV_PAD_DIGITAL = 0,
	GV_PAD_ANAJOY = 1,
	GV_PAD_ANALOG = 2
} ;

//cache

//memory
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
	 
void GV_InitResidentMemory( void );  //unsure what function this maps to
void *GV_AllocResidentMemory_800163D8( long size );

//pad
extern	void    GV_InitPadSystem_800167C8 ( void ) ;
extern	void    GV_UpdatePadSystem_8001682C ( void ) ;
extern	void    GV_OriginPadSystem_80016C78( int ) ;
extern	int     GV_GetPadOrigin_80016C84( void ) ;
extern	int     GV_GetPadDirNoPadOrg_80016C90 ( unsigned int ) ;

//strCode
//extern  int     GV_StrCode_80016CCC( const char* string );

//math

void GV_SubVec3_80016D40(SVECTOR* vec1, SVECTOR* vec2, SVECTOR* dst);
int GV_VecLen3_80016D80(SVECTOR* vec);


#endif // LIBGV_H