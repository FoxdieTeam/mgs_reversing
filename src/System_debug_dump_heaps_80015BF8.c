#include "linker.h"
#include "system.h"

extern const char aSystemD[];
extern const char aDynamic[];
extern const char aVoided[];
extern const char aFailed[];
extern const char asc_800AB360[];
extern const char aAddr08x08xUnit[];
extern const char aFreeDDVoidedDM[];

extern void mg_printf_8008BBA0(const char *, ...);

extern GV_Heap gv_heaps_800AD2F0[3];

void System_debug_dump_heap_stats_80015BF8(unsigned int heapIdx)
{
    int maxFree;
    int voidedCount;
    int freeCount;

    int size;

    int unitCounter;
    GV_MemoryAllocation *pAllocIter;

    GV_Heap *pHeap = &gv_heaps_800AD2F0[heapIdx];

    mg_printf_8008BBA0(aSystemD, heapIdx);

    if (pHeap->mFlags & GV_Heap_Flags_Dynamic_1)
    {
        mg_printf_8008BBA0(aDynamic);
    }

    if (pHeap->mFlags & GV_Heap_Flags_Voided_2)
    {
        mg_printf_8008BBA0(aVoided);
    }

    if (pHeap->mFlags & GV_Heap_Flags_Failed_4)
    {
        mg_printf_8008BBA0(aFailed);
    }

    mg_printf_8008BBA0(asc_800AB360);
    mg_printf_8008BBA0(aAddr08x08xUnit, pHeap->mStartAddr, pHeap->mEndAddr, pHeap->mUnitsCount);
    size = pHeap->mEndAddr - pHeap->mStartAddr;

    freeCount = 0;
    voidedCount = 0;
    maxFree = 0;

    pAllocIter = &pHeap->mAllocs[0];

    for (unitCounter = pHeap->mUnitsCount; unitCounter > 0; unitCounter--)
    {
        int type = pAllocIter->mAllocType;

        unsigned char *firstSize = pAllocIter->mPDataStart;
        unsigned char *nextSize = pAllocIter[1].mPDataStart;

        int allocSize = nextSize - firstSize;

        if (type == GV_MemoryAllocation_States_Free_0)
        {
            freeCount += allocSize;
            if (maxFree < allocSize)
            {
                maxFree = allocSize;
            }
        }
        else if (type == GV_MemoryAllocation_States_Void_1)
        {
            voidedCount += allocSize;
        }

        pAllocIter++;
    }

    mg_printf_8008BBA0(aFreeDDVoidedDM,
                       freeCount,
                       size,
                       voidedCount,
                       maxFree);
}

extern const char aDynamic[];
extern const char a8dBytesFrom08x[];
extern const char a8dBytesFrom08x_0[];
extern const char a8dBytesFrom08x_1[];
extern const char a8dBytesFrom08x_2[];
extern const char aStatic[];
extern const char asc_800AB36C[];

extern int null_printf_8008BBA8(const char *, ...);

void System_debug_dump_heap_units_80015D48(int heapIdx)
{
    int unitCounter;
    GV_MemoryAllocation *pAllocIter;

    GV_Heap *pHeap = &gv_heaps_800AD2F0[heapIdx];
    mg_printf_8008BBA0(aSystemD, heapIdx);

    if (!(pHeap->mFlags & GV_Heap_Flags_Dynamic_1))
    {
        mg_printf_8008BBA0(aStatic);
    }
    else
    {
        mg_printf_8008BBA0(aDynamic);
    }

    if (pHeap->mFlags & GV_Heap_Flags_Voided_2)
    {
        mg_printf_8008BBA0(aVoided);
    }

    if (pHeap->mFlags & GV_Heap_Flags_Failed_4)
    {
        mg_printf_8008BBA0(aFailed);
    }

    mg_printf_8008BBA0(asc_800AB360);

    pAllocIter = &pHeap->mAllocs[0];

    for (unitCounter = pHeap->mUnitsCount; unitCounter > 0; unitCounter--)
    {
        int allocType = pAllocIter->mAllocType;
        unsigned char *firstSize = pAllocIter->mPDataStart;
        unsigned char *nextSize = pAllocIter[1].mPDataStart;

        int allocSize = nextSize - firstSize;

        if (allocType == GV_MemoryAllocation_States_Free_0)
        {
            mg_printf_8008BBA0(a8dBytesFrom08x, allocSize, pAllocIter->mPDataStart);
        }
        else if (allocType == GV_MemoryAllocation_States_Void_1)
        {
            mg_printf_8008BBA0(a8dBytesFrom08x_0, allocSize, pAllocIter->mPDataStart);
        }
        else if (allocType == GV_MemoryAllocation_States_Used_2)
        {
            mg_printf_8008BBA0(a8dBytesFrom08x_1, allocSize, pAllocIter->mPDataStart);
        }
        else
        {
            mg_printf_8008BBA0(a8dBytesFrom08x_2, allocSize, pAllocIter->mPDataStart, allocType);
        }

        pAllocIter++;
    }

    mg_printf_8008BBA0(asc_800AB36C);
}
