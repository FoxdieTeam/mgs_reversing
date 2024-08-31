#include "libgv.h"
#include "mts/mts_new.h"

/**bss***************************************************************/
extern GV_Heap MemorySystems_800AD2F0[3];
/********************************************************************/

/***$gp****************************************************************/
extern unsigned char *GV_ResidentMemoryBottom_800AB940;
unsigned char        *SECTION(".sbss") GV_ResidentMemoryBottom_800AB940;
/*********************************************************************/

extern unsigned char *gOverlayBase_800AB9C8;

void *System_FindAlloc_80015758(GV_Heap *pHeap, void *a1)
{
    int                  i;
    GV_MemoryAllocation *pAlloc;
    GV_MemoryAllocation *pAlloc2;

    if (a1 < pHeap->mStartAddr || a1 >= pHeap->mEndAddr)
        return 0;

    pAlloc = pHeap->mAllocs;

    for (i = pHeap->mUnitsCount; i >= 2; i /= 2)
    {
        pAlloc2 = &pAlloc[i / 2];

        if (a1 == pAlloc2->mPDataStart)
            return pAlloc2;

        if (pAlloc2->mPDataStart < a1)
        {
            i--;
            pAlloc = pAlloc2 + 1;
        }
    }

    if (i <= 0 || pAlloc->mPDataStart != a1)
        return 0;

    return pAlloc;
}

GV_MemoryAllocation *sub_80015818(GV_Heap *pHeap, int a1)
{
    int                  i, j, k;
    GV_MemoryAllocation *pAlloc;

    j = (int)pHeap->mAllocs[0].mPDataStart;
    pAlloc = pHeap->mAllocs;

    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
        k = (int)pAlloc[1].mPDataStart;
        j = k - j;

        if (j >= a1)
        {
            if (!pAlloc->mAllocType)
                return pAlloc;
        }
        j = k;
        pAlloc++;
    }
    return 0;
}

void sub_80015874(GV_Heap *pHeap, GV_MemoryAllocation *pAlloc)
{
    int                  i, x;
    int                  size;
    GV_MemoryAllocation *pAlloc2;

    x = pHeap->mUnitsCount;
    pAlloc2 = &pHeap->mAllocs[x];

    size = (pAlloc - pHeap->mAllocs);

    for (i = x - size; i > -1; --i)
    {
        pAlloc2[1] = pAlloc2[0];
        pAlloc2--;
    }

    pHeap->mUnitsCount++;
}

void sub_800158C8(GV_Heap *pHeap, GV_MemoryAllocation *pAlloc, int n_unit)
{

    int                  i;
    GV_MemoryAllocation *pAlloc2 = &pAlloc[n_unit];

    i = pHeap->mUnitsCount - (pAlloc - pHeap->mAllocs);

    for (i = i - n_unit; i > -1; --i)
    {
        *pAlloc = *pAlloc2;
        pAlloc++;
        pAlloc2++;
    }

    pHeap->mUnitsCount -= n_unit;
}

void System_voided_reset_80015924(GV_Heap *pHeap)
{
    int                  i, bUnknown;
    GV_MemoryAllocation *pAlloc = pHeap->mAllocs;
    GV_MemoryAllocation *pAlloc2 = pAlloc;

    bUnknown = 0;
    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
        if (pAlloc2->mAllocType >= (unsigned int)2)
        {
            *pAlloc = *pAlloc2;
            pAlloc++;
            bUnknown = 0;
        }
        else
        {
            if (!bUnknown)
            {
                bUnknown = 1;
                pAlloc->mPDataStart = pAlloc2->mPDataStart;
                pAlloc->mAllocType = 0;
                pAlloc++;
            }
        }

        pAlloc2++;
    }

    pAlloc->mPDataStart = pHeap->mEndAddr;
    pAlloc->mAllocType = 2;

    pHeap->mUnitsCount = (pAlloc - pHeap->mAllocs);
}

void System_dynamic_reset_800159B8(GV_Heap *pHeap)
{
    int                  i;
    int                  diff;
    int                  alloc_type;
    void                *addr;
    void                *pDataStart;
    GV_MemoryAllocation *pAlloc;
    GV_MemoryAllocation *pAlloc2;

    pAlloc = pHeap->mAllocs;
    addr = pHeap->mStartAddr;
    pAlloc2 = pAlloc;

    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
        alloc_type = pAlloc2->mAllocType;
        if (alloc_type >= (unsigned int)2)
        {
            pDataStart = pAlloc2->mPDataStart;
            diff = pAlloc2[1].mPDataStart - pDataStart;
            if (pDataStart != addr)
            {
                pAlloc->mPDataStart = addr;
                pAlloc->mAllocType = alloc_type;
                *(int *)alloc_type = (int)addr; // this seems wrong
                GV_CopyMemory(pDataStart, addr, diff);
            }
            addr += diff;
            pAlloc++;
        }
        pAlloc2++;
    }

    if (addr != pHeap->mEndAddr)
    {
        pAlloc->mPDataStart = addr;
        pAlloc->mAllocType = 0;
        pAlloc++;
    }

    pAlloc->mPDataStart = pHeap->mEndAddr;
    pAlloc->mAllocType = 2;

    pHeap->mUnitsCount = (pAlloc - pHeap->mAllocs);
}

void GV_InitMemorySystemAll(void)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        GV_InitMemorySystem(i, 0, 0, 0);
    }
}

void GV_InitMemorySystem(int index, int bIsDynamic, void *pMemory, int size)
{
    GV_Heap             *pHeap = &MemorySystems_800AD2F0[index];
    GV_MemoryAllocation *pAllocs = &pHeap->mAllocs[0];
    unsigned char       *alignedEndPtr = ((unsigned char *)pMemory) + (size & 0xfffffff0); // align

    pHeap->mFlags = bIsDynamic != 0;
    pHeap->mStartAddr = pMemory;

    pHeap->mEndAddr = alignedEndPtr;
    pHeap->mUnitsCount = 1;

    // First entry is free
    pAllocs[0].mPDataStart = pMemory;
    pAllocs[0].mAllocType = GV_MEMORY_STATE_FREE;

    // Second is used and is the entire space
    pAllocs[1].mPDataStart = alignedEndPtr;
    pAllocs[1].mAllocType = GV_MEMORY_STATE_USED;
}

void GV_ClearMemorySystem(int which)
{
    GV_Heap *pHeap = &MemorySystems_800AD2F0[which];
    int      flags = pHeap->mFlags;

    if (flags & (GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED))
    {
        if (flags & GV_HEAP_FLAG_FAILED)
        {
            if (flags & GV_HEAP_FLAG_DYNAMIC)
            {
                System_dynamic_reset_800159B8(pHeap);
                pHeap->mFlags &= ~(GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED);
            }
        }
        if (flags & GV_HEAP_FLAG_VOIDED)
        {
            System_voided_reset_80015924(pHeap);
            pHeap->mFlags &= ~GV_HEAP_FLAG_VOIDED;
        }
    }
    pHeap->mFlags &= ~(GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED);
}

void GV_CheckMemorySystem(int heapIdx)
{
    int maxFree;
    int voidedCount;
    int freeCount;
    int size;
    int                  unitCounter;
    GV_MemoryAllocation *pAllocIter;

    GV_Heap *pHeap = &MemorySystems_800AD2F0[heapIdx];

    printf("system %d ( ", heapIdx);

    if (pHeap->mFlags & GV_HEAP_FLAG_DYNAMIC)
    {
        printf("dynamic ");
    }

    if (pHeap->mFlags & GV_HEAP_FLAG_VOIDED)
    {
        printf("voided ");
    }

    if (pHeap->mFlags & GV_HEAP_FLAG_FAILED)
    {
        printf("failed ");
    }

    printf(")\n");
    printf("  addr = %08x - %08x, units = %d\n",
           (unsigned int)pHeap->mStartAddr, (unsigned int)pHeap->mEndAddr, pHeap->mUnitsCount);
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

        if (type == GV_MEMORY_STATE_FREE)
        {
            freeCount += allocSize;
            if (maxFree < allocSize)
            {
                maxFree = allocSize;
            }
        }
        else if (type == GV_MEMORY_STATE_VOID)
        {
            voidedCount += allocSize;
        }

        pAllocIter++;
    }

    printf("  free = %d / %d, voided = %d, max_free = %d\n",
                        freeCount, size, voidedCount, maxFree);
}

void GV_DumpMemorySystem(int heapIdx)
{
    int                  unitCounter;
    GV_MemoryAllocation *pAllocIter;

    GV_Heap *pHeap = &MemorySystems_800AD2F0[heapIdx];
    printf("system %d ( ", heapIdx);

    if (!(pHeap->mFlags & GV_HEAP_FLAG_DYNAMIC))
    {
        printf("static ");
    }
    else
    {
        printf("dynamic ");
    }

    if (pHeap->mFlags & GV_HEAP_FLAG_VOIDED)
    {
        printf("voided ");
    }

    if (pHeap->mFlags & GV_HEAP_FLAG_FAILED)
    {
        printf("failed ");
    }

    printf(")\n");

    pAllocIter = &pHeap->mAllocs[0];

    for (unitCounter = pHeap->mUnitsCount; unitCounter > 0; unitCounter--)
    {
        int            allocType = pAllocIter->mAllocType;
        unsigned char *firstSize = pAllocIter->mPDataStart;
        unsigned char *nextSize = pAllocIter[1].mPDataStart;

        int allocSize = nextSize - firstSize;

        if (allocType == GV_MEMORY_STATE_FREE)
        {
            printf("---- %8d bytes ( from %08x free )\n",
                   allocSize, (unsigned int)pAllocIter->mPDataStart);
        }
        else if (allocType == GV_MEMORY_STATE_VOID)
        {
            printf("==== %8d bytes ( from %08x void )\n",
                   allocSize, (unsigned int)pAllocIter->mPDataStart);
        }
        else if (allocType == GV_MEMORY_STATE_USED)
        {
            printf("++++ %8d bytes ( from %08x used )\n",
                   allocSize, (unsigned int)pAllocIter->mPDataStart);
        }
        else
        {
            printf("**** %8d bytes ( from %08x user %08x )\n",
                   allocSize, (unsigned int)pAllocIter->mPDataStart, allocType);
        }

        pAllocIter++;
    }

    printf("\n");
}

void *GV_AllocMemory(int which, int size)
{
    return GV_AllocMemory2(which, size, (void **)2);
}

void *GV_AllocMemory2(int which, int size, void **type)
{
    int                  state;
    void                *pDataStart;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;

    pHeap = &MemorySystems_800AD2F0[which];
    state = GV_MEMORY_STATE_USED;

    if (pHeap->mUnitsCount < 511)
    {
        // Align size to 16-byte boundary
        size = (size + 15) & ~15;

        pAlloc = sub_80015818(pHeap, size);

        if (!pAlloc)
        {
            pHeap->mFlags |= GV_HEAP_FLAG_FAILED;
        }
        else
        {
            pDataStart = pAlloc->mPDataStart;

            if (size < pAlloc[1].mPDataStart - pDataStart)
            {
                sub_80015874(pHeap, pAlloc);
                pAlloc[1].mPDataStart = pDataStart + size;
                pAlloc[1].mAllocType = 0;
            }

            pAlloc->mAllocType = (int)type;

            if ((int)type != state)
            {
                type[0] = pDataStart;
            }

            return pDataStart;
        }
    }

    return 0;
}

void GV_FreeMemory(int which, void *addr)
{
    int                  state;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;
    GV_MemoryAllocation *pAlloc2;

    pHeap = &MemorySystems_800AD2F0[which];
    pAlloc = System_FindAlloc_80015758(pHeap, addr);

    if (!pAlloc)
        return;

    if (!pAlloc->mAllocType)
        return;

    pAlloc->mAllocType = 0;
    pAlloc2 = pAlloc;

    state = GV_MEMORY_STATE_FREE;

    if (pAlloc != pHeap->mAllocs && !pAlloc2[-1].mAllocType)
    {
        state = GV_MEMORY_STATE_VOID;
    }
    else
    {
        pAlloc2++;
    }

    if (!pAlloc[1].mAllocType)
    {
        state++;
    }

    if (state)
    {
        sub_800158C8(pHeap, pAlloc2, state);
    }
}

void GV_FreeMemory2(int which, void **addr)
{
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;

    pHeap = &MemorySystems_800AD2F0[which];
    pAlloc = System_FindAlloc_80015758(pHeap, addr[0]);

    if (!pAlloc)
        return;

    pAlloc->mAllocType = 1;
    pHeap->mFlags |= GV_HEAP_FLAG_VOIDED;
}

void GV_CopyMemory(void *from, void *to, int size)
{
    typedef struct { long d0, d1, d2, d3; } Unit;
    int   i, i2;
    Unit *u0;
    Unit *u1;
    char *c0;
    char *c1;

    c0 = (char *)from;
    c1 = (char *)to;

    i = 3 & (long)from;
    i2 = 3 & (long)to;

    if (i2 != i)
    {
        for (i = size; i > 0; --i)
        {
            *(c1++) = *(c0++);
        }
    }
    else
    {
        size = size - i;
        for (; i > 0; --i)
        {
            *(c1++) = *(c0++);
        }
        u0 = (Unit *)c0;
        u1 = (Unit *)c1;
        for (i = size / sizeof(Unit); i > 0; --i)
        {
            *(u1++) = *(u0++);
        }
        c0 = (char *)u0;
        c1 = (char *)u1;
        for (i = (sizeof(Unit) - 1) & size; i > 0; --i)
        {
            *(c1++) = *(c0++);
        }
    }
}

// TODO: Use sizeof(resident)+1 when the start is known
// TODO: hardcoded
void *GV_ResidentAreaBottom_800AB370 = (void *)0x80117000; // This goes backwards not "into" this heap buffer

// from leaked original MGS source code

void GV_ZeroMemory(void *to, int size)
{
    typedef struct { long d0, d1, d2, d3; } Unit;
    Unit *u;
    char *c;
    int   i;

    c = (char *)to;
    i = 3 & (long)to;
    size -= i;
    for (; i > 0; --i)
    {
        *(c++) = 0;
    }
    u = (Unit *)c;
    for (i = size / sizeof(Unit); i > 0; --i)
    {
        u->d0 = 0;
        u->d1 = 0;
        u->d2 = 0;
        u->d3 = 0;
        u++;
    }
    c = (char *)u;
    for (i = (sizeof(Unit) - 1) & size; i > 0; --i)
    {
        *(c++) = 0;
    }
}

void *GV_Malloc(int size)
{
    return GV_AllocMemory(GV_NORMAL_MEMORY, size);
}

void GV_Free(void *addr)
{
    GV_FreeMemory(GV_NORMAL_MEMORY, addr);
}

void GV_DelayedFree(void *addr)
{
    GV_FreeMemory2(GV_NORMAL_MEMORY, &addr);
}

void *GV_GetMaxFreeMemory(int which)
{
    int                  i;
    int                  size;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;

    size = 0;
    pHeap = &MemorySystems_800AD2F0[which];
    pAlloc = pHeap->mAllocs;

    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
        if (!pAlloc->mAllocType)
        {
            int diff = pAlloc[1].mPDataStart - pAlloc->mPDataStart;
            if (size < diff)
            {
                size = diff;
            }
        }
        pAlloc++;
    }

    return GV_AllocMemory(which, size);
}

void *GV_ResizeMemory(int which, void *addr, int size)
{
    void                *new_addr;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;

    pHeap = &MemorySystems_800AD2F0[which];
    pAlloc = System_FindAlloc_80015758(pHeap, addr);

    if (!pAlloc)
        return 0;

    if (pAlloc->mAllocType != 2)
        return 0;

    if (pAlloc[1].mPDataStart - pAlloc->mPDataStart == size)
        return 0;

    sub_80015874(pHeap, pAlloc);
    new_addr = pAlloc->mPDataStart + size;
    pAlloc[1].mPDataStart = new_addr;
    pAlloc[1].mAllocType = 0;

    return new_addr;
}

// either this or the next is GV_InitResidentMemory
void GV_ResidentHeapReset(void)
{
    GV_ResidentMemoryBottom_800AB940 = GV_ResidentAreaBottom_800AB370;
}

void GV_SaveResidentTop(void)
{
    GV_ResidentAreaBottom_800AB370 = GV_ResidentMemoryBottom_800AB940;
}

void *GV_AllocResidentMemory(long size)
{
    size = (size + 3) & -4;

    GV_ResidentMemoryBottom_800AB940 -= size;
    if (GV_ResidentMemoryBottom_800AB940 < gOverlayBase_800AB9C8)
    {
        printf("Resident Memory Over !!\n");
    }

    return GV_ResidentMemoryBottom_800AB940;
}
