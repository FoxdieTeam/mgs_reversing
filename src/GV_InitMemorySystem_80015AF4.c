#include "linker.h"
#include "system.h"

GV_Heap SECTION(".MemorySystems_800AD2F0") MemorySystems_800AD2F0[3];

void GV_InitMemorySystem_80015AF4(int index, int bIsDynamic, void *pMemory, unsigned int size);

void GV_InitMemorySystemAll_80015AB0(void)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        GV_InitMemorySystem_80015AF4(i, 0, 0, 0);
    }
}

void GV_InitMemorySystem_80015AF4(int index, int bIsDynamic, void *pMemory, unsigned int size)
{
    GV_Heap *pHeap = &MemorySystems_800AD2F0[index];
    GV_MemoryAllocation *pAllocs = &pHeap->mAllocs[0];
    unsigned char *alignedEndPtr = ((unsigned char *)pMemory) + (size & 0xfffffff0); // align

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
