#include "libgv.h"
#include <stdio.h>
#include "common.h"

M_Sys SECTION(".bss") MemorySystems[ MAX_MEMSYS ];

/* Unused, does it really belong to memory.c ? */
STATIC short SECTION(".sbss") dword_800AB93C;

/*---------------------------------------------------------------------------*/

/**
 * @brief   Find in a specific heap the allocation that contains the address.
 *
 * @param   heap    heap to search in
 * @param   addr    address to search for
 *
 * @return  the allocation block that contains the address
 */
static void *GV_FindAllocation( M_Sys *sys, void *addr )
{
    int     i;
    M_Unit  *start;
    M_Unit  *end;

    // return if the address is not within the heap
    if (addr < sys->start || addr >= sys->end)
        return NULL;

    start = sys->units;

    // search for the allocation that contains the address
    for (i = sys->n_units; i >= 2; i /= 2)
    {
        end = &start[i / 2];

        // the address is at the start of the allocation
        if (addr == end->addr)
            return end;

        if (end->addr < addr)
        {
            i--;
            start = end + 1;
        }
    }

    // if the address is not found return NULL
    if (i <= 0 || start->addr != addr)
        return NULL;

    return start;
}

/**
 * @brief   Finds a free memory allocation in the heap that can accommodate
 *          a specified size.
 *
 * This function iterates through the memory allocations in the specified heap
 * to find a free block that is large enough to accommodate the requested size.
 * If such a block is found, it returns a pointer to the memory allocation.
 * Otherwise, it returns NULL.
 *
 * @param   heap    pointer to the heap structure
 * @param   size    size of the memory block to find
 *
 * @return  Pointer to the found memory allocation,
 *          or NULL if no suitable block is found.
 */
static M_Unit *GV_FindFreeMemory( M_Sys *sys, int size )
{
    M_Unit  *unit;
    void    *start;
    void    *next;
    int     i;
    int     bytes;

    // Initialize j with the start address of the first allocation
    unit = sys->units;
    start = unit[0].addr;

    // Iterate through the heap
    for (i = sys->n_units; i > 0; i--)
    {
       // Get the start address of the next allocation
        next = unit[1].addr;

        // Calculate the size of the current block
        bytes = (char *)next - (char *)start;

        // Find a large enough free block
        if (bytes >= size && unit->addr_ptr == FREE_UNIT)
        {
            return unit;
        }

        start = next;
        unit++;
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
 * @param   heap    pointer to the heap structure
 * @param   alloc   pointer to the memory allocation to be inserted
 */
static void GV_SplitAllocation( M_Sys *sys, M_Unit *unit )
{
    int     used;
    M_Unit  *last;
    int     size;
    int     i;

    used = sys->n_units;

    // Pointer to the last allocation in the heap
    last = &sys->units[used];

    // Calculate the size of the new allocation
    size = unit - sys->units;

    // Shift existing allocations to make space for the new allocation
    for (i = used - size; i >= 0; i--)
    {
        last[1] = last[0];
        last--;
    }

    sys->n_units++;
}

/**
 * @brief Merges adjacent free memory blocks in the heap.
 *
 * This function merges adjacent free memory blocks in the specified heap by
 * shifting memory allocations and updating the heap's unit count.
 *
 * @param   heap    pointer to the heap structure
 * @param   alloc   pointer to the memory allocation to start merging from
 * @param   n_unit  number of units to merge
 */
static void GV_MergeMemory( M_Sys *sys, M_Unit *unit, int n_unit )
{
    M_Unit  *next;
    int     size;
    int     shift;
    int     i;

    next = &unit[n_unit];

    // Calculate the number of units to shift
    size = unit - sys->units;
    shift = sys->n_units - size - n_unit;

    // Shift memory allocations to merge free blocks
    for (i = shift; i > -1; i--)
    {
        *unit = *next;
        unit++;
        next++;
    }

    // Update the heap's unit count to reflect the merged blocks
    sys->n_units -= n_unit;
}

/**
 * @brief Resets the heap by compacting voided memory allocations.
 *
 * This function iterates through the memory allocations in the specified heap
 * and compacts voided (free) memory blocks.
 *
 * It ensures that all valid allocations are moved to the start of the heap,
 * and any voided blocks are merged into a single free block.
 *
 * Updates the heap's unit count.
 *
 * @param   heap    pointer to the heap structure
 */
static void GV_ResetVoidedMemorySystem( M_Sys *sys )
{
    M_Unit  *unit;
    M_Unit  *new;
    int     voided;
    int     i;

    unit = sys->units;
    new = unit;

    voided = 0;

    for (i = sys->n_units; i > 0; i--)
    {
        if (unit->addr_ptr != FREE_UNIT && unit->addr_ptr != VOID_UNIT)
        {
            *new++ = *unit;
            voided = 0;
        }
        else if (!voided)
        {
            voided = 1;
            new->addr = unit->addr;
            new->addr_ptr = FREE_UNIT;
            new++;
        }

        unit++;
    }

    // Mark the end of the heap
    new->addr = sys->end;
    new->addr_ptr = USED_UNIT;

    sys->n_units = new - sys->units;
}

/**
 * @brief Resets the dynamic memory allocations in the specified heap.
 *
 * This function compacts the memory allocations in the heap by moving them to
 * the start address of the heap.
 *
 * It iterates through the memory allocations, copying them to the new location
 * if necessary, and updates the allocation metadata.
 *
 * @param   heap    Pointer to the heap structure.
 */
static void GV_ResetDynamicMemorySystem( M_Sys *sys )
{
    M_Unit  *unit;
    M_Unit  *new;
    char    *addr;
    int     i;
    void    **addr_ptr;
    int     size;
    void    *start;

    unit = sys->units;
    new = unit;

    addr = sys->start;

    // Iterate through all memory allocations in the heap
    for (i = sys->n_units; i > 0; i--)
    {
        addr_ptr = unit->addr_ptr;

        if (addr_ptr != FREE_UNIT && addr_ptr != VOID_UNIT)
        {
            start = unit->addr;
            size = unit[1].addr - start;

            if (start != addr)
            {
                new->addr = addr;
                new->addr_ptr = addr_ptr;

                // Write the new start address to the userdata pointer
                *addr_ptr = addr;
                GV_CopyMemory( start, addr, size );
            }

            addr += size;
            new++;
        }

        unit++;
    }

    // If the last allocation is not at the end of the heap, add a new one
    if (addr != sys->end)
    {
        new->addr = addr;
        new->addr_ptr = FREE_UNIT;
        new++;
    }

    // Add a final allocation to mark the end of the heap
    new->addr = sys->end;
    new->addr_ptr = USED_UNIT;

    sys->n_units = new - sys->units;
}

/*---------------------------------------------------------------------------*/

void GV_InitMemorySystemAll( void )
{
    int i;

    for (i = 0; i < MAX_MEMSYS; i++)
    {
        GV_InitMemorySystem( i, 0, NULL, 0 );
    }
}

/**
 * @brief Initializes a specific heap in the memory system.
 *
 * This function initializes an heap the specified index. It sets up the
 * structure, aligns the end pointer, and marks the initial memory allocations
 * as free and used.
 *
 * @param   which       index of the heap to initialize
 * @param   dynamic     flag indicating whether the heap is dynamic
 * @param   memory      pointer to the start of the memory block
 * @param   size        size of the memory block
 */
void GV_InitMemorySystem( int which, int dynamic, void *memory, int size )
{
    M_Sys   *sys;
    M_Unit  *unit;
    unsigned char *end;

    sys = &MemorySystems[which];
    unit = sys->units;

    // Align the end to 16 bytes
    end = (char *)memory + (size & ~15);

    sys->stat = dynamic != 0;
    sys->start = memory;

    sys->end = end;
    sys->n_units = 1;

    // First entry is free
    unit[0].addr = memory;
    unit[0].addr_ptr = FREE_UNIT;

    // Second is used and is the entire space
    unit[1].addr = end;
    unit[1].addr_ptr = USED_UNIT;
}

/**
 * @brief Clears the memory for the specified heap.
 *
 * This function checks the flags of the specified heap and performs the
 * necessary reset operations if the heap has failed or contains voided memory
 * blocks. It resets the heap's flags accordingly.
 *
 * @param   which   index of the heap to clear
 */
void GV_ClearMemorySystem( int which )
{
    M_Sys   *sys;
    int      stat;

    sys = &MemorySystems[which];
    stat = sys->stat;

    if (stat & (MEMORY_FAILED | MEMORY_VOIDED))
    {
        if (stat & MEMORY_FAILED)
        {
            if (stat & MEMORY_DYNAMIC)
            {
                GV_ResetDynamicMemorySystem( sys );
                sys->stat &= ~(MEMORY_FAILED | MEMORY_VOIDED);
            }
        }

        if (stat & MEMORY_VOIDED)
        {
            GV_ResetVoidedMemorySystem( sys );
            sys->stat &= ~MEMORY_VOIDED;
        }
    }

    sys->stat &= ~(MEMORY_FAILED | MEMORY_VOIDED);
}

/**
 * @brief Checks and prints the status of the specified heap.
 *
 * This function prints detailed information about the specified heap,
 * It also calculates and prints the total free memory, total voided memory,
 * and the size of the largest free block.
 *
 * @param   which   index of the heap to check
 */
void GV_CheckMemorySystem( int which )
{
    M_Sys   *sys;
    int     total;
    int     voided;
    int     max_free;
    int     free;
    M_Unit  *unit;
    int     i;
    void    **addr_ptr;
    void    *start;
    void    *next;
    int     size;

    sys = &MemorySystems[which];

    printf("system %d ( ", which);

    if (sys->stat & MEMORY_DYNAMIC)
        printf("dynamic ");

    if (sys->stat & MEMORY_VOIDED)
        printf("voided ");

    if (sys->stat & MEMORY_FAILED)
        printf("failed ");

    printf(")\n");

    printf("  addr = %08x - %08x, units = %d\n",
        (unsigned int)sys->start, (unsigned int)sys->end, sys->n_units);

    total = sys->end - sys->start;

    free = 0;
    voided = 0;
    max_free = 0;

    unit = &sys->units[0];
    for (i = sys->n_units; i > 0; i--)
    {
        addr_ptr = unit->addr_ptr;

        start = unit->addr;
        next = unit[1].addr;
        size = next - start;

        if (addr_ptr == FREE_UNIT)
        {
            free += size;

            if (size > max_free)
            {
                max_free = size;
            }
        }
        else if (addr_ptr == VOID_UNIT)
        {
            voided += size;
        }

        unit++;
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
 * @param   which   index of the heap to dump
 */
void GV_DumpMemorySystem( int which )
{
    M_Sys   *sys;
    M_Unit  *unit;
    int     i;
    void    **addr_ptr;
    void    *start;
    void    *next;
    int     size;

    sys = &MemorySystems[which];

    printf("system %d ( ", which);

    if (!(sys->stat & MEMORY_DYNAMIC))
        printf("static ");
    else
        printf("dynamic ");

    if (sys->stat & MEMORY_VOIDED)
        printf("voided ");

    if (sys->stat & MEMORY_FAILED)
        printf("failed ");

    printf(")\n");

    unit = &sys->units[0];

    for (i = sys->n_units; i > 0; i--)
    {
        addr_ptr = unit->addr_ptr;

        start = unit->addr;
        next = unit[1].addr;
        size = next - start;

        if (addr_ptr == FREE_UNIT) {
            printf("---- %8d bytes ( from %08x free )\n",
                   size, (unsigned int)unit->addr);
        }
        else if (addr_ptr == VOID_UNIT) {
            printf("==== %8d bytes ( from %08x void )\n",
                   size, (unsigned int)unit->addr);
        }
        else if (addr_ptr == USED_UNIT) {
            printf("++++ %8d bytes ( from %08x used )\n",
                   size, (unsigned int)unit->addr);
        }
        else {
            printf("**** %8d bytes ( from %08x user %08x )\n",
                   size, (unsigned int)unit->addr, (unsigned int)addr_ptr);
        }

        unit++;
    }

    printf("\n");
}

void *GV_AllocMemory( int which, int size )
{
    return GV_AllocMemory2( which, size, USED_UNIT );
}

/**
 * @brief   Allocates memory from the specified heap with a start pointer
 *          for dynamic allocations.
 *
 * This function allocates a block of memory from the specified heap. It aligns
 * the requested size to a 16-byte boundary, finds a suitable free block, and
 * updates the heap's memory allocation structures. If the allocation is
 * successful, it returns a pointer to the start of the allocated memory block.
 * If the allocation fails, it sets the heap's failed flag and returns NULL.
 *
 * @param   which   index of the heap to allocate memory from
 * @param   size    size of the memory block to allocate
 * @param   pstart  MEM_TAG_STATE_USED for GV_AllocMemory, or a pointer to
 *                  receive the start address otherwise
 *
 * @return  pointer to the start of the allocated memory block,
 *          or NULL if the allocation fails
 */
void *GV_AllocMemory2( int which, int size, void **pstart )
{
    M_Sys   *sys;
    void    **normal;
    M_Unit  *unit;
    void    *start;

    sys = &MemorySystems[which];
    normal = USED_UNIT;

    // Check if there is space for more allocations
    if (sys->n_units >= (MAX_MEMUNIT - 1))
    {
        return NULL;
    }

    // Align size to 16-byte boundary
    size = (size + 15) & ~15;

    // Find a free block that can accommodate the requested size
    unit = GV_FindFreeMemory( sys, size );

    if (!unit)
    {
        // Set the heap's failed flag if no suitable block is found
        sys->stat |= MEMORY_FAILED;
    }
    else
    {
        start = unit->addr;

        // If the free block is larger than the requested size, split it
        if ((unit[1].addr - start) > size)
        {
            GV_SplitAllocation( sys, unit );
            unit[1].addr = start + size;
            unit[1].addr_ptr = FREE_UNIT;
        }

        // Mark the allocation as used
        unit->addr_ptr = pstart;

        if (pstart != normal)
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
 * @param   which   index of the heap
 * @param   addr    address of the memory block to be freed
 */
void GV_FreeMemory( int which, void *addr )
{
    M_Sys   *sys;
    M_Unit  *unit;
    M_Unit  *merge;
    int     units;

    sys = &MemorySystems[which];
    unit = GV_FindAllocation( sys, addr );

    // Return if the allocation is not found or already free
    if (!unit || unit->addr_ptr == FREE_UNIT)
        return;

    unit->addr_ptr = FREE_UNIT;
    merge = unit;

    units = 0;

    // Check if the previous allocation is also free
    if (unit != sys->units && unit[-1].addr_ptr == FREE_UNIT)
    {
        units++;
    }
    else
    {
        merge++;
    }

    // Check if the next allocation is also free
    if (unit[1].addr_ptr == FREE_UNIT)
    {
        units++;
    }

    // If there are adjacent free blocks, merge them
    if (units)
    {
        GV_MergeMemory( sys, merge, units );
    }
}

/**
 * @brief Marks a memory allocation as voided in the specified heap.
 *
 * This function finds the memory allocation corresponding to the given address
 * in the specified heap and marks it as voided. It also sets the heap's flag to
 * indicate that it contains voided allocations.
 *
 * @param   which   index of the heap.
 * @param   addr    pointer to the address of the memory block to be voided
 */
void GV_FreeMemory2( int which, void **addr )
{
    M_Sys   *sys;
    M_Unit  *unit;

    sys = &MemorySystems[which];
    unit = GV_FindAllocation( sys, *addr );

    if (unit)
    {
        unit->addr_ptr = VOID_UNIT;
        sys->stat |= MEMORY_VOIDED;
    }
}

void GV_CopyMemory( void *from, void *to, int size )
{
    typedef struct { long d0, d1, d2, d3; } Unit;
    int     i, i2;
    Unit    *u0;
    Unit    *u1;
    char    *c0;
    char    *c1;

    c0 = (char *)from;
    c1 = (char *)to;

    // Calculate the alignment of the source and destination addresses
    i = 3 & (long)from;
    i2 = 3 & (long)to;

    // If the alignments are different, copy byte by byte
    if (i2 != i) {
        for (i = size; i > 0; --i) {
            *(c1++) = *(c0++);
        }
    } else {
        // Adjust size to account for initial unaligned bytes
        size = size - i;
        for (; i > 0; --i) {
            *(c1++) = *(c0++);
        }
        // Copy using the Unit structure for larger chunks
        u0 = (Unit *)c0;
        u1 = (Unit *)c1;
        for (i = size / sizeof(Unit); i > 0; --i) {
            *(u1++) = *(u0++);
        }
        // Copy any remaining bytes
        c0 = (char *)u0;
        c1 = (char *)u1;
        for (i = (sizeof(Unit) - 1) & size; i > 0; --i) {
            *(c1++) = *(c0++);
        }
    }
}

// clang-format off
void GV_ZeroMemory( void *to, int size )
{
    typedef struct { long d0, d1, d2, d3; } Unit;
    Unit    *u;
    char    *c;
    int     i;

    c = (char *)to;
    i = 3 & (long)to;
    size -= i;
    for (; i > 0; --i) {
        *(c++) = 0;
    }
    u = (Unit *)c;
    for (i = size / sizeof(Unit); i > 0; --i) {
        u->d0 = 0;
        u->d1 = 0;
        u->d2 = 0;
        u->d3 = 0;
        u++;
    }
    c = (char *)u;
    for (i = (sizeof(Unit) - 1) & size; i > 0; --i) {
        *(c++) = 0;
    }
}

void *GV_Malloc( int size )
{
    return GV_AllocMemory( GV_NORMAL_MEMORY, size );
}

void GV_Free( void *addr )
{
    GV_FreeMemory( GV_NORMAL_MEMORY, addr );
}

void GV_DelayedFree( void *addr )
{
    GV_FreeMemory2( GV_NORMAL_MEMORY, &addr );
}
// clang-format on

/**
 * @brief   Finds and allocates the largest contiguous free memory block
 *          in the specified heap.
 *
 * @param   which   index of the heap to search
 *
 * @return  pointer to the allocated memory block
 */
void *GV_GetMaxFreeMemory( int which )
{
    int     max;
    M_Sys   *sys;
    M_Unit  *unit;
    int     i;
    int     size;

    max = 0;

    sys = &MemorySystems[which];
    unit = sys->units;

    for (i = sys->n_units; i > 0; i--)
    {
        if (unit->addr_ptr == FREE_UNIT)
        {
            size = unit[1].addr - unit->addr;
            if (size > max)
            {
                // keep track of the largest free block
                max = size;
            }
        }

        unit++;
    }

    return GV_AllocMemory( which, max );
}

/**
 * @brief   Resizes an existing memory allocation in the specified heap.
 *
 * @param   which   index of the heap
 * @param   addr    address of the memory block to resize
 * @param   size    new size of the memory block
 *
 * @return  pointer to the resized memory block, or NULL if resizing fails
 */
void *GV_SplitMemory( int which, void *addr, int size )
{
    M_Sys   *sys;
    M_Unit  *unit;

    sys = &MemorySystems[which];
    unit = GV_FindAllocation( sys, addr );

    if (!unit || unit->addr_ptr != USED_UNIT)
        return NULL;

    if ((unit[1].addr - unit->addr) == size)
        return NULL;

    GV_SplitAllocation( sys, unit );

    unit[1].addr = unit->addr + size;
    unit[1].addr_ptr = FREE_UNIT;

    return unit[1].addr;
}
