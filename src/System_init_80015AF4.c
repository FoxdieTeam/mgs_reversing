#include "linker.h"


enum GV_MemoryAllocation_States
{
    GV_MemoryAllocation_States_Free_0 = 0,
    GV_MemoryAllocation_States_Void_1 = 1,
    GV_MemoryAllocation_States_Used_2 = 2,
};

typedef struct GV_MemoryAllocation
{
    unsigned char* mPDataStart;
    int mAllocType;
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
    unsigned char* mStartAddr;
    unsigned char* mEndAddr;
    int mUnitsCount;
    GV_MemoryAllocation mAllocs[512];
} GV_Heap;

GV_Heap SECTION(".gv_heaps_800AD2F0") gv_heaps_800AD2F0[3];

void System_init_80015AF4(int index, int bIsDynamic, void* pMemory, unsigned int size)
{
    GV_Heap* pHeap = &gv_heaps_800AD2F0[index];
    GV_MemoryAllocation* pAllocs = &pHeap->mAllocs[0];
	unsigned char* alignedEndPtr = ((unsigned char*)pMemory) + (size & 0xfffffff0); // align
   
    pHeap->mFlags = bIsDynamic != 0;
    pHeap->mStartAddr = pMemory;
    
    pHeap->mEndAddr = alignedEndPtr;
    pHeap->mUnitsCount = 1;
	
    // First entry is free     
    pAllocs[0].mPDataStart = pMemory;
    pAllocs[0].mAllocType = GV_MemoryAllocation_States_Free_0;
 	
    // Second is used and is the entire space   
    pAllocs[1].mPDataStart = alignedEndPtr;
    pAllocs[1].mAllocType = GV_MemoryAllocation_States_Used_2;
}
