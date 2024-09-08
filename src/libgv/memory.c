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

/**
 * @brief Find in a specific heap the allocation that contains the address.
 *
 * @param pHeap heap to search in
 * @param a1 address to search for
 * @return GV_MemoryAllocation* the allocation block that contains the address
 */
void *System_FindAlloc_80015758(GV_Heap *pHeap, void *a1)
{
    int                  i;
    GV_MemoryAllocation *pAlloc;
    GV_MemoryAllocation *pAlloc2;

    // return if the address is not within the heap
    if (a1 < pHeap->mStartAddr || a1 >= pHeap->mEndAddr)
        return 0;

    pAlloc = pHeap->mAllocs;

    // search for the allocation that contains the address
    for (i = pHeap->mUnitsCount; i >= 2; i /= 2)
    {
        pAlloc2 = &pAlloc[i / 2];

        // the address is at the start of the allocation
        if (a1 == pAlloc2->mPDataStart)
            return pAlloc2;

        if (pAlloc2->mPDataStart < a1)
        {
            i--;
            pAlloc = pAlloc2 + 1;
        }
    }
    // if the address is not found return 0
    if (i <= 0 || pAlloc->mPDataStart != a1)
        return 0;

    return pAlloc;
}

/**
 * @brief Finds a free memory allocation in the heap that can accommodate a
 * specified size.
 *
 * This function iterates through the memory allocations in the specified heap
 * to find a free block that is large enough to accommodate the requested size.
 * If such a block is found, it returns a pointer to the memory allocation.
 * Otherwise, it returns NULL.
 *
 * @param pHeap Pointer to the heap structure.
 * @param size The size of the memory block to find.
 * @return GV_MemoryAllocation* Pointer to the found memory allocation,
 *         or NULL if no suitable block is found.
 */
GV_MemoryAllocation *GV_FindFreeBlockBySize_80015818(GV_Heap *pHeap, int size)
{
    int                  i, j, k;
    GV_MemoryAllocation *pAlloc;

    // Initialize j with the start address of the first allocation
    j = (int)pHeap->mAllocs[0].mPDataStart;
    pAlloc = pHeap->mAllocs;

    // Iterate through the heap
    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
       // Get the start address of the next allocation
        k = (int)pAlloc[1].mPDataStart;
        // Calculate the size of the current block
        j = k - j;

        // Check if the current block is large
        if (j >= size)
        {
            // if is free return it
            if (!pAlloc->mAllocType)
                return pAlloc;
        }
        j = k;
        pAlloc++;
    }
    // Return NULL if no suitable block is found
    return 0;
}

/**
 * @brief Inserts a new memory allocation into the heap.
 *
 * This function inserts a new memory allocation into the specified heap by
 * shifting existing allocations to make space for the new allocation.
 * It updates the heap's unit count accordingly.
 *
 * @param pHeap Pointer to the heap structure.
 * @param pAlloc Pointer to the memory allocation to be inserted.
 */
void GV_InsertMemoryAllocation_80015874(GV_Heap *pHeap, GV_MemoryAllocation *pAlloc)
{
    int                  i, x;
    int                  size;
    GV_MemoryAllocation *pAlloc2;

    x = pHeap->mUnitsCount;
    // Pointer to the last allocation in the heap
    pAlloc2 = &pHeap->mAllocs[x];

    // Calculate the size of the new allocation
    size = (pAlloc - pHeap->mAllocs);

    // Shift existing allocations to make space for the new allocation
    for (i = x - size; i > -1; --i)
    {
        pAlloc2[1] = pAlloc2[0];
        pAlloc2--;
    }

    pHeap->mUnitsCount++;
}

/**
 * @brief Merges adjacent free memory blocks in the heap.
 *
 * This function merges adjacent free memory blocks in the specified heap by
 * shifting memory allocations and updating the heap's unit count.
 *
 * @param pHeap Pointer to the heap structure.
 * @param pAlloc Pointer to the memory allocation to start merging from.
 * @param n_unit The number of units to merge.
 */
void GV_MergeMemory_800158C8(GV_Heap *pHeap, GV_MemoryAllocation *pAlloc, int n_unit)
{

    int                  i;
    GV_MemoryAllocation *pAlloc2 = &pAlloc[n_unit];

    // Calculate the number of units to shift
    i = pHeap->mUnitsCount - (pAlloc - pHeap->mAllocs);

    // Shift memory allocations to merge free blocks
    for (i = i - n_unit; i > -1; --i)
    {
        *pAlloc = *pAlloc2;
        pAlloc++;
        pAlloc2++;
    }

    // Update the heap's unit count to reflect the merged blocks
    pHeap->mUnitsCount -= n_unit;
}


/**
 * @brief Resets the heap by compacting voided memory allocations.
 *
 * This function iterates through the memory allocations in the specified heap
 * and compacts voided (free) memory blocks.
 * It ensures that all valid allocations are moved to the start of the heap,
 * and any voided blocks are merged into a single free block.
 * Updates the heap's unit count.
 *
 * @param pHeap Pointer to the heap structure.
 */
void System_voided_reset_80015924(GV_Heap *pHeap)
{
    int                  i, is_void_block_found;
    GV_MemoryAllocation *pAlloc = pHeap->mAllocs;
    GV_MemoryAllocation *pAlloc2 = pAlloc;

    is_void_block_found = 0;
    for (i = pHeap->mUnitsCount; i > 0; --i)
    {
        if (pAlloc2->mAllocType >= (unsigned int)2)
        {
            *pAlloc = *pAlloc2;
            pAlloc++;
            is_void_block_found = 0;
        }
        else
        {
            if (!is_void_block_found)
            {
                is_void_block_found = 1;
                pAlloc->mPDataStart = pAlloc2->mPDataStart;
                pAlloc->mAllocType = 0;
                pAlloc++;
            }
        }

        pAlloc2++;
    }

    // Mark the end of the heap
    pAlloc->mPDataStart = pHeap->mEndAddr;
    pAlloc->mAllocType = 2;

    pHeap->mUnitsCount = (pAlloc - pHeap->mAllocs);
}

/**
 * @brief Resets the dynamic memory allocations in the specified heap.
 *
 * This function compacts the memory allocations in the heap by moving them to
 * the start address of the heap.
 * It iterates through the memory allocations, copying them to the new location
 * if necessary, and updates the allocation metadata.
 *
 * @param pHeap Pointer to the heap structure.
 */
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

    // Iterate through all memory allocations in the heap
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

    // if the last allocation is not at the end of the heap, add a new one
    if (addr != pHeap->mEndAddr)
    {
        pAlloc->mPDataStart = addr;
        pAlloc->mAllocType = 0;
        pAlloc++;
    }
    // Add a final allocation to mark the end of the heap
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

/**
 * @brief Initializes a specific heap in the memory system.
 *
 * This function initializes an heap the specified index. It sets up the
 * structure, aligns the end pointer, and marks the initial memory allocations
 * as free and used.
 *
 * @param index The index of the heap to initialize.
 * @param bIsDynamic A flag indicating whether the heap is dynamic.
 * @param pMemory Pointer to the start of the memory block.
 * @param size The size of the memory block.
 */
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


/**
 * @brief Clears the memory for the specified heap.
 *
 * This function checks the flags of the specified heap and performs the
 * necessary reset operations if the heap has failed or contains voided memory
 * blocks. It resets the heap's flags accordingly.
 *
 * @param which The index of the heap to clear.
 */
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

/**
 * @brief Checks and prints the status of the specified heap.
 *
 * This function prints detailed information about the specified heap,
 * It also calculates and prints the total free memory, total voided memory,
 * and the size of the largest free block.
 *
 * @param heapIdx The index of the heap to check.
 */
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

/**
 * @brief Dumps the memory system information for the specified heap.
 *
 * Helper function to print information about the memory allocations in the
 * specified heap.
 *
 * @param heapIdx The index of the heap.
 */
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

/**
 * @brief Allocates memory from the specified heap and with the specified type.
 *
 * This function allocates a block of memory from the specified heap. It aligns
 * the requested size to a 16-byte boundary, finds a suitable free block, and
 * updates the heap's memory allocation structures. If the allocation is
 * successful, it returns a pointer to the start of the allocated memory block.
 * If the allocation fails, it sets the heap's failed flag and returns NULL.
 *
 * @param which The index of the heap to allocate memory from.
 * @param size The size of the memory block to allocate.
 * @param type A pointer to the type of memory allocation.
 * @return void* Pointer to the start of the allocated memory block,
 *               or NULL if the allocation fails.
 */
void *GV_AllocMemory2(int which, int size, void **type)
{
    int                  state;
    void                *pDataStart;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;

    pHeap = &MemorySystems_800AD2F0[which];
    state = GV_MEMORY_STATE_USED;

    // Check if there is space for more allocations
    if (pHeap->mUnitsCount < 511)
    {
        // Align size to 16-byte boundary
        size = (size + 15) & ~15;

        // Find a free block that can accommodate the requested size
        pAlloc = GV_FindFreeBlockBySize_80015818(pHeap, size);

        if (!pAlloc)
        {
            // Set the heap's failed flag if no suitable block is found
            pHeap->mFlags |= GV_HEAP_FLAG_FAILED;
        }
        else
        {
            pDataStart = pAlloc->mPDataStart;

            // If the free block is larger than the requested size, split it
            if (size < pAlloc[1].mPDataStart - pDataStart)
            {
                GV_InsertMemoryAllocation_80015874(pHeap, pAlloc);
                pAlloc[1].mPDataStart = pDataStart + size;
                pAlloc[1].mAllocType = 0;
            }

            // Mark the allocation as used
            pAlloc->mAllocType = (int)type;

            if ((int)type != state)
            {
                type[0] = pDataStart;
            }
            // Return the start address of the allocation
            return pDataStart;
        }
    }
    // Return NULL if the allocation fails
    return 0;
}

/**
 * @brief Frees a memory allocation in the specified heap.
 *
 * This function finds the memory allocation corresponding to the given address
 * in the specified heap and marks it as free. It also handles merging adjacent
 * free blocks and updating the heap's state.
 *
 * @param index The index of the heap.
 * @param addr The address of the memory block to be freed.
 */
void GV_FreeMemory(int index, void *addr)
{
    int                  state;
    GV_Heap             *pHeap;
    GV_MemoryAllocation *pAlloc;
    GV_MemoryAllocation *pAlloc2;

    // Get the heap
    pHeap = &MemorySystems_800AD2F0[index];
    // Find the memory allocation corresponding to the given address
    pAlloc = System_FindAlloc_80015758(pHeap, addr);

    // If the allocation is not found
    if (!pAlloc)
        return;
    // or is already free, return
    if (!pAlloc->mAllocType)
        return;

    pAlloc->mAllocType = 0;
    pAlloc2 = pAlloc;

    state = GV_MEMORY_STATE_FREE;

    // Check if the previous allocation is also free
    if (pAlloc != pHeap->mAllocs && !pAlloc2[-1].mAllocType)
    {
        state = GV_MEMORY_STATE_VOID;
    }
    else
    {
        pAlloc2++;
    }

    // Check if the next allocation is also free
    if (!pAlloc[1].mAllocType)
    {
        state++;
    }

    // If there are adjacent free blocks, merge them
    if (state)
    {
        GV_MergeMemory_800158C8(pHeap, pAlloc2, state);
    }
}

/**
 * @brief Marks a memory allocation as voided in the specified heap.
 *
 * This function finds the memory allocation corresponding to the given address
 * in the specified heap and marks it as voided. It also sets the heap's flag to
 * indicate that it contains voided allocations.
 *
 * @param which The index of the heap.
 * @param addr Pointer to the address of the memory block to be voided.
 */
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

/**
 * @brief Copies a block of memory from one location to another.
 *
 * This function copies a block of memory from the source address `from` to the
 * destination address `to`. It optimizes the copying process by using a
 * structure to copy multiple bytes at a time when possible.
 *
 * @param from Pointer to the source memory block.
 * @param to Pointer to the destination memory block.
 * @param size The size of the memory block in bytes.
 */
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

    // Calculate the alignment of the source and destination addresses
    i = 3 & (long)from;
    i2 = 3 & (long)to;

    // If the alignments are different, copy byte by byte
    if (i2 != i)
    {
        for (i = size; i > 0; --i)
        {
            *(c1++) = *(c0++);
        }
    }
    else
    {
        // Adjust size to account for initial unaligned bytes
        size = size - i;
        for (; i > 0; --i)
        {
            *(c1++) = *(c0++);
        }
        // Copy using the Unit structure for larger chunks
        u0 = (Unit *)c0;
        u1 = (Unit *)c1;
        for (i = size / sizeof(Unit); i > 0; --i)
        {
            *(u1++) = *(u0++);
        }
        // Copy any remaining bytes
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
// This goes backwards not "into" this heap buffer
void *GV_ResidentAreaBottom_800AB370 = (void *)0x80117000;

// from leaked original MGS source code
/**
 * @brief Sets a block of memory to zero.
 *
 * This function sets a block of memory to zero, optimizing the process by
 * using a structure to zero out multiple bytes at a time when possible.
 *
 * @param to Pointer to the start of the memory block to be zeroed.
 * @param size The size of the memory block in bytes.
 */
void GV_ZeroMemory(void *to, int size)
{
    typedef struct { long d0, d1, d2, d3; } Unit;
    Unit *u;
    char *c;
    int   i;
    // align the start of the memory block
    c = (char *)to;
    i = 3 & (long)to;
    size -= i;
    for (; i > 0; --i)
    {
        *(c++) = 0;
    }
    // use the Unit structure to zero out larger chunks
    u = (Unit *)c;
    for (i = size / sizeof(Unit); i > 0; --i)
    {
        u->d0 = 0;
        u->d1 = 0;
        u->d2 = 0;
        u->d3 = 0;
        u++;
    }
    // zero out any remaining bytes
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

/**
 * @brief Finds and allocates the largest contiguous free memory block in the
 * specified heap.
 *
 * @param which The index of the heap to search.
 * @return void* Pointer to the allocated memory block.
 */
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
                // keep track of the largest free block
                size = diff;
            }
        }
        pAlloc++;
    }

    return GV_AllocMemory(which, size);
}


/**
 * @brief Resizes an existing memory allocation in the specified heap.
 *
 * @param which The index of the heap.
 * @param addr The address of the memory block to resize.
 * @param size The new size of the memory block.
 * @return void* Pointer to the resized memory block, or 0 if resizing fails.
 */
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

    GV_InsertMemoryAllocation_80015874(pHeap, pAlloc);
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

/**
 * @brief Reserves a block of memory from the bottom of the resident memory area.
 *
 * @param size The size of the memory block to reserve.
 * @return void* pointer to the new resident memory bottom
 */
void *GV_AllocResidentMemory(long size)
{
    // Align the size to 4 bytes
    size = (size + 3) & -4;

    // decrement the bottom of the resident memory
    GV_ResidentMemoryBottom_800AB940 -= size;
    if (GV_ResidentMemoryBottom_800AB940 < gOverlayBase_800AB9C8)
    {
        printf("Resident Memory Over !!\n");
    }

    return GV_ResidentMemoryBottom_800AB940;
}
