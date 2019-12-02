#ifndef _SYSTEM_H
#define _SYSTEM_H

enum GV_MemoryAllocation_States
{
    GV_MemoryAllocation_States_Free_0 = 0,
    GV_MemoryAllocation_States_Void_1 = 1,
    GV_MemoryAllocation_States_Used_2 = 2,
};

typedef struct GV_MemoryAllocation
{
    unsigned char *mPDataStart;
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
    unsigned char *mStartAddr;
    unsigned char *mEndAddr;
    int mUnitsCount;
    GV_MemoryAllocation mAllocs[512];
} GV_Heap;

extern GV_Heap gv_heaps_800AD2F0[3];

void System_init_clear_3_heaps_80015AB0(void);
void System_init_80015AF4(int index, int bIsDynamic, void *pMemory, unsigned int size);

#endif // _SYSTEM_H
