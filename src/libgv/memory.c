#include "libgv.h"

#include <stdio.h>
#include "common.h"

/**bss***************************************************************/
extern GV_HEAP MemorySystems_800AD2F0[3];
/********************************************************************/

/***$gp****************************************************************/
extern unsigned char *GV_ResidentMemoryBottom_800AB940;
unsigned char        *SECTION(".sbss") GV_ResidentMemoryBottom_800AB940;
/*********************************************************************/

extern unsigned char *gOverlayBase_800AB9C8;

/**
 * @brief Find in a specific heap the allocation that contains the address.
 *
 * @param heap heap to search in
 * @param addr address to search for
 * @return GV_ALLOC* the allocation block that contains the address
 */
void *GV_FindAllocation(GV_HEAP *heap, void *addr)
{
    int       i;
    GV_ALLOC *start;
    GV_ALLOC *end;

    // return if the address is not within the heap
    if (addr < heap->start || addr >= heap->end)
        return NULL;

    start = heap->units;

    // search for the allocation that contains the address
    for (i = heap->used; i >= 2; i /= 2)
    {
        end = &start[i / 2];

        // the address is at the start of the allocation
        if (addr == end->start)
            return end;

        if (end->start < addr)
        {
            i--;
            start = end + 1;
        }
    }

    // if the address is not found return NULL
    if (i <= 0 || start->start != addr)
        return NULL;

    return start;
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
 * @param heap Pointer to the heap structure.
 * @param size The size of the memory block to find.
 * @return GV_ALLOC* Pointer to the found memory allocation,
 *         or NULL if no suitable block is found.
 */
GV_ALLOC *GV_FindFreeMemory(GV_HEAP *heap, int size)
{
    GV_ALLOC *alloc;
    void     *start;
    void     *next;
    int       i;
    int       bytes;

    // Initialize j with the start address of the first allocation
    alloc = heap->units;
    start = alloc[0].start;

    // Iterate through the heap
    for (i = heap->used; i > 0; i--)
    {
       // Get the start address of the next allocation
        next = alloc[1].start;

        // Calculate the size of the current block
        bytes = (char *)next - (char *)start;

        // Find a large enough free block
        if (bytes >= size && alloc->state == GV_ALLOC_STATE_FREE)
        {
            return alloc;
        }

        start = next;
        alloc++;
    }

    // Return NULL if no suitable block is found
    return NULL;
}

/**
 * @brief Inserts a new memory allocation into the heap.
 *
 * This function inserts a new memory allocation into the specified heap by
 * shifting existing allocations to make space for the new allocation.
 * It updates the heap's unit count accordingly.
 *
 * @param heap Pointer to the heap structure.
 * @param alloc Pointer to the memory allocation to be inserted.
 */
void GV_SplitAllocation(GV_HEAP *heap, GV_ALLOC *alloc)
{
    int       used;
    GV_ALLOC *last;
    int       size;
    int       i;

    used = heap->used;

    // Pointer to the last allocation in the heap
    last = &heap->units[used];

    // Calculate the size of the new allocation
    size = alloc - heap->units;

    // Shift existing allocations to make space for the new allocation
    for (i = used - size; i >= 0; i--)
    {
        last[1] = last[0];
        last--;
    }

    heap->used++;
}

/**
 * @brief Merges adjacent free memory blocks in the heap.
 *
 * This function merges adjacent free memory blocks in the specified heap by
 * shifting memory allocations and updating the heap's unit count.
 *
 * @param heap Pointer to the heap structure.
 * @param alloc Pointer to the memory allocation to start merging from.
 * @param n_unit The number of units to merge.
 */
void GV_MergeMemory(GV_HEAP *heap, GV_ALLOC *alloc, int n_unit)
{
    GV_ALLOC *next;
    int       size;
    int       shift;
    int       i;

    next = &alloc[n_unit];

    // Calculate the number of units to shift
    size = alloc - heap->units;
    shift = heap->used - size - n_unit;

    // Shift memory allocations to merge free blocks
    for (i = shift; i > -1; i--)
    {
        *alloc = *next;
        alloc++;
        next++;
    }

    // Update the heap's unit count to reflect the merged blocks
    heap->used -= n_unit;
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
 * @param heap Pointer to the heap structure.
 */
void GV_ResetVoidedMemorySystem(GV_HEAP *heap)
{
    GV_ALLOC *alloc;
    GV_ALLOC *new;
    int       voided;
    int       i;

    alloc = heap->units;
    new = alloc;

    voided = 0;

    for (i = heap->used; i > 0; i--)
    {
        if (alloc->state != GV_ALLOC_STATE_FREE && alloc->state != GV_ALLOC_STATE_VOID)
        {
            *new++ = *alloc;
            voided = 0;
        }
        else if (!voided)
        {
            voided = 1;
            new->start = alloc->start;
            new->state = GV_ALLOC_STATE_FREE;
            new++;
        }

        alloc++;
    }

    // Mark the end of the heap
    new->start = heap->end;
    new->state = GV_ALLOC_STATE_USED;

    heap->used = new - heap->units;
}

/**
 * @brief Resets the dynamic memory allocations in the specified heap.
 *
 * This function compacts the memory allocations in the heap by moving them to
 * the start address of the heap.
 * It iterates through the memory allocations, copying them to the new location
 * if necessary, and updates the allocation metadata.
 *
 * @param heap Pointer to the heap structure.
 */
void GV_ResetDynamicMemorySystem(GV_HEAP *heap)
{
    GV_ALLOC *alloc;
    GV_ALLOC *new;
    char     *addr;
    int       i;
    int       state;
    int       size;
    void     *start;

    alloc = heap->units;
    new = alloc;

    addr = heap->start;

    // Iterate through all memory allocations in the heap
    for (i = heap->used; i > 0; i--)
    {
        state = alloc->state;

        if (state != GV_ALLOC_STATE_FREE && state != GV_ALLOC_STATE_VOID)
        {
            start = alloc->start;
            size = alloc[1].start - start;

            if (start != addr)
            {
                new->start = addr;
                new->state = state;

                // Write the new start address to the userdata pointer
                *(void **)state = addr;
                GV_CopyMemory(start, addr, size);
            }

            addr += size;
            new++;
        }

        alloc++;
    }

    // If the last allocation is not at the end of the heap, add a new one
    if (addr != heap->end)
    {
        new->start = addr;
        new->state = GV_ALLOC_STATE_FREE;
        new++;
    }

    // Add a final allocation to mark the end of the heap
    new->start = heap->end;
    new->state = GV_ALLOC_STATE_USED;

    heap->used = new - heap->units;
}

void GV_InitMemorySystemAll(void)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        GV_InitMemorySystem(i, 0, NULL, 0);
    }
}

/**
 * @brief Initializes a specific heap in the memory system.
 *
 * This function initializes an heap the specified index. It sets up the
 * structure, aligns the end pointer, and marks the initial memory allocations
 * as free and used.
 *
 * @param which The index of the heap to initialize.
 * @param dynamic A flag indicating whether the heap is dynamic.
 * @param memory Pointer to the start of the memory block.
 * @param size The size of the memory block.
 */
void GV_InitMemorySystem(int which, int dynamic, void *memory, int size)
{
    GV_HEAP  *heap;
    GV_ALLOC *alloc;
    unsigned char *end;

    heap = &MemorySystems_800AD2F0[which];
    alloc = heap->units;

    // Align the end to 16 bytes
    end = (char *)memory + (size & ~15);

    heap->flags = dynamic != 0;
    heap->start = memory;

    heap->end = end;
    heap->used = 1;

    // First entry is free
    alloc[0].start = memory;
    alloc[0].state = GV_ALLOC_STATE_FREE;

    // Second is used and is the entire space
    alloc[1].start = end;
    alloc[1].state = GV_ALLOC_STATE_USED;
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
    GV_HEAP *heap;
    int      flags;

    heap = &MemorySystems_800AD2F0[which];
    flags = heap->flags;

    if (flags & (GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED))
    {
        if (flags & GV_HEAP_FLAG_FAILED)
        {
            if (flags & GV_HEAP_FLAG_DYNAMIC)
            {
                GV_ResetDynamicMemorySystem(heap);
                heap->flags &= ~(GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED);
            }
        }

        if (flags & GV_HEAP_FLAG_VOIDED)
        {
            GV_ResetVoidedMemorySystem(heap);
            heap->flags &= ~GV_HEAP_FLAG_VOIDED;
        }
    }

    heap->flags &= ~(GV_HEAP_FLAG_FAILED | GV_HEAP_FLAG_VOIDED);
}

/**
 * @brief Checks and prints the status of the specified heap.
 *
 * This function prints detailed information about the specified heap,
 * It also calculates and prints the total free memory, total voided memory,
 * and the size of the largest free block.
 *
 * @param which The index of the heap to check.
 */
void GV_CheckMemorySystem(int which)
{
    GV_HEAP  *heap;
    int       total;
    int       voided;
    int       max_free;
    int       free;
    GV_ALLOC *alloc;
    int       i;
    int       state;
    void     *start;
    void     *next;
    int       size;

    heap = &MemorySystems_800AD2F0[which];

    printf("system %d ( ", which);

    if (heap->flags & GV_HEAP_FLAG_DYNAMIC)
    {
        printf("dynamic ");
    }

    if (heap->flags & GV_HEAP_FLAG_VOIDED)
    {
        printf("voided ");
    }

    if (heap->flags & GV_HEAP_FLAG_FAILED)
    {
        printf("failed ");
    }

    printf(")\n");

    printf("  addr = %08x - %08x, units = %d\n",
           (unsigned int)heap->start, (unsigned int)heap->end, heap->used);

    total = heap->end - heap->start;

    free = 0;
    voided = 0;
    max_free = 0;

    alloc = &heap->units[0];
    for (i = heap->used; i > 0; i--)
    {
        state = alloc->state;

        start = alloc->start;
        next = alloc[1].start;
        size = next - start;

        if (state == GV_ALLOC_STATE_FREE)
        {
            free += size;

            if (size > max_free)
            {
                max_free = size;
            }
        }
        else if (state == GV_ALLOC_STATE_VOID)
        {
            voided += size;
        }

        alloc++;
    }

    printf("  free = %d / %d, voided = %d, max_free = %d\n",
           free, total, voided, max_free);
}

/**
 * @brief Dumps the memory system information for the specified heap.
 *
 * Helper function to print information about the memory allocations in the
 * specified heap.
 *
 * @param which The index of the heap.
 */
void GV_DumpMemorySystem(int which)
{
    GV_HEAP  *heap;
    GV_ALLOC *alloc;
    int       i;
    int       state;
    void     *start;
    void     *next;
    int       size;

    heap = &MemorySystems_800AD2F0[which];

    printf("system %d ( ", which);

    if (!(heap->flags & GV_HEAP_FLAG_DYNAMIC))
    {
        printf("static ");
    }
    else
    {
        printf("dynamic ");
    }

    if (heap->flags & GV_HEAP_FLAG_VOIDED)
    {
        printf("voided ");
    }

    if (heap->flags & GV_HEAP_FLAG_FAILED)
    {
        printf("failed ");
    }

    printf(")\n");

    alloc = &heap->units[0];

    for (i = heap->used; i > 0; i--)
    {
        state = alloc->state;

        start = alloc->start;
        next = alloc[1].start;
        size = next - start;

        if (state == GV_ALLOC_STATE_FREE)
        {
            printf("---- %8d bytes ( from %08x free )\n",
                   size, (unsigned int)alloc->start);
        }
        else if (state == GV_ALLOC_STATE_VOID)
        {
            printf("==== %8d bytes ( from %08x void )\n",
                   size, (unsigned int)alloc->start);
        }
        else if (state == GV_ALLOC_STATE_USED)
        {
            printf("++++ %8d bytes ( from %08x used )\n",
                   size, (unsigned int)alloc->start);
        }
        else
        {
            printf("**** %8d bytes ( from %08x user %08x )\n",
                   size, (unsigned int)alloc->start, state);
        }

        alloc++;
    }

    printf("\n");
}

void *GV_AllocMemory(int which, int size)
{
    return GV_AllocMemory2(which, size, (void **)GV_ALLOC_STATE_USED);
}

/**
 * @brief Allocates memory from the specified heap with a start pointer for
 *        dynamic allocations.
 *
 * This function allocates a block of memory from the specified heap. It aligns
 * the requested size to a 16-byte boundary, finds a suitable free block, and
 * updates the heap's memory allocation structures. If the allocation is
 * successful, it returns a pointer to the start of the allocated memory block.
 * If the allocation fails, it sets the heap's failed flag and returns NULL.
 *
 * @param which The index of the heap to allocate memory from.
 * @param size The size of the memory block to allocate.
 * @param pstart GV_ALLOC_STATE_USED for GV_AllocMemory, or a pointer to
 *               receive the start address otherwise.
 * @return void* Pointer to the start of the allocated memory block,
 *               or NULL if the allocation fails.
 */
void *GV_AllocMemory2(int which, int size, void **pstart)
{
    GV_HEAP  *heap;
    int       normal;
    GV_ALLOC *alloc;
    void     *start;

    heap = &MemorySystems_800AD2F0[which];
    normal = GV_ALLOC_STATE_USED;

    // Check if there is space for more allocations
    if (heap->used >= (MAX_ALLOC_UNITS - 1))
    {
        return NULL;
    }

    // Align size to 16-byte boundary
    size = (size + 15) & ~15;

    // Find a free block that can accommodate the requested size
    alloc = GV_FindFreeMemory(heap, size);

    if (!alloc)
    {
        // Set the heap's failed flag if no suitable block is found
        heap->flags |= GV_HEAP_FLAG_FAILED;
    }
    else
    {
        start = alloc->start;

        // If the free block is larger than the requested size, split it
        if ((alloc[1].start - start) > size)
        {
            GV_SplitAllocation(heap, alloc);
            alloc[1].start = start + size;
            alloc[1].state = GV_ALLOC_STATE_FREE;
        }

        // Mark the allocation as used
        alloc->state = (int)pstart;

        if ((int)pstart != normal)
        {
            *pstart = start;
        }

        // Return the start address of the allocation
        return start;
    }

    // Return NULL if the allocation fails
    return NULL;
}

/**
 * @brief Frees a memory allocation in the specified heap.
 *
 * This function finds the memory allocation corresponding to the given address
 * in the specified heap and marks it as free. It also handles merging adjacent
 * free blocks and updating the heap's state.
 *
 * @param which The index of the heap.
 * @param addr The address of the memory block to be freed.
 */
void GV_FreeMemory(int which, void *addr)
{
    GV_HEAP  *heap;
    GV_ALLOC *alloc;
    GV_ALLOC *merge;
    int       units;

    // Get the heap
    heap = &MemorySystems_800AD2F0[which];
    // Find the memory allocation corresponding to the given address
    alloc = GV_FindAllocation(heap, addr);

    // Return if the allocation is not found or already free
    if (!alloc || alloc->state == GV_ALLOC_STATE_FREE)
        return;

    alloc->state = GV_ALLOC_STATE_FREE;
    merge = alloc;

    units = 0;

    // Check if the previous allocation is also free
    if (alloc != heap->units && alloc[-1].state == GV_ALLOC_STATE_FREE)
    {
        units++;
    }
    else
    {
        merge++;
    }

    // Check if the next allocation is also free
    if (alloc[1].state == GV_ALLOC_STATE_FREE)
    {
        units++;
    }

    // If there are adjacent free blocks, merge them
    if (units)
    {
        GV_MergeMemory(heap, merge, units);
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
    GV_HEAP  *heap;
    GV_ALLOC *alloc;

    heap = &MemorySystems_800AD2F0[which];
    alloc = GV_FindAllocation(heap, *addr);

    if (alloc)
    {
        alloc->state = GV_ALLOC_STATE_VOID;
        heap->flags |= GV_HEAP_FLAG_VOIDED;
    }
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
void *GV_ResidentAreaBottom = (void *)0x80117000;

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
    int       max;
    GV_HEAP  *heap;
    GV_ALLOC *alloc;
    int       i;
    int       size;

    max = 0;

    heap = &MemorySystems_800AD2F0[which];
    alloc = heap->units;

    for (i = heap->used; i > 0; i--)
    {
        if (alloc->state == GV_ALLOC_STATE_FREE)
        {
            size = alloc[1].start - alloc->start;
            if (size > max)
            {
                // keep track of the largest free block
                max = size;
            }
        }

        alloc++;
    }

    return GV_AllocMemory(which, max);
}

/**
 * @brief Resizes an existing memory allocation in the specified heap.
 *
 * @param which The index of the heap.
 * @param addr The address of the memory block to resize.
 * @param size The new size of the memory block.
 * @return void* Pointer to the resized memory block, or 0 if resizing fails.
 */
void *GV_SplitMemory(int which, void *addr, int size)
{
    GV_HEAP  *heap;
    GV_ALLOC *alloc;

    heap = &MemorySystems_800AD2F0[which];
    alloc = GV_FindAllocation(heap, addr);

    if (!alloc || alloc->state != GV_ALLOC_STATE_USED)
        return NULL;

    if ((alloc[1].start - alloc->start) == size)
        return NULL;

    GV_SplitAllocation(heap, alloc);

    alloc[1].start = alloc->start + size;
    alloc[1].state = GV_ALLOC_STATE_FREE;

    return alloc[1].start;
}

// either this or the next is GV_InitResidentMemory
void GV_ResidentHeapReset(void)
{
    GV_ResidentMemoryBottom_800AB940 = GV_ResidentAreaBottom;
}

void GV_SaveResidentTop(void)
{
    GV_ResidentAreaBottom = GV_ResidentMemoryBottom_800AB940;
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
    size = (size + 3) & ~3;

    // decrement the bottom of the resident memory
    GV_ResidentMemoryBottom_800AB940 -= size;
    if (GV_ResidentMemoryBottom_800AB940 < gOverlayBase_800AB9C8)
    {
        printf("Resident Memory Over !!\n");
    }

    return GV_ResidentMemoryBottom_800AB940;
}
