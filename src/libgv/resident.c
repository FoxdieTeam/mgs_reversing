#include "libgv.h"
#include <stdio.h>
#include "common.h"

extern unsigned char *gOverlayBase_800AB9C8;

unsigned char *SECTION(".sbss") GV_ResidentMemoryBottom;
STATIC int     SECTION(".sbss") dword_800AB944;

// TODO: Use sizeof(resident)+1 when the start is known
// TODO: hardcoded address
void *GV_ResidentAreaBottom = GV_NORMAL_MEMORY_TOP;

// either this or the next is GV_InitResidentMemory
void GV_ResidentHeapReset(void)
{
    GV_ResidentMemoryBottom = GV_ResidentAreaBottom;
}

void GV_SaveResidentTop(void)
{
    GV_ResidentAreaBottom = GV_ResidentMemoryBottom;
}

/**
 * @brief   Reserves a block of memory from the bottom
 *          of the resident memory area.
 *
 * @param   size    The size of the memory block to reserve.
 *
 * @return  pointer to the new resident memory bottom
 */
void *GV_AllocResidentMemory(long size)
{
#ifdef DEV_EXE
    // linker-defined symbol
    extern unsigned char _bss_orgend[];
#endif

    // Align the size to 4 bytes
    size = (size + 3) & ~3;

    // decrement the bottom of the resident memory
    GV_ResidentMemoryBottom -= size;

#ifdef DEV_EXE
    // dev_exe has to compare to _bss_orgend since the overlay base pointer
    // used by the OG code will be pointing somewhere in the .data section.
    if (GV_ResidentMemoryBottom < _bss_orgend)
#else
    // BUG: the overlay can potentially be alloc'd over with no warning.
    if (GV_ResidentMemoryBottom < gOverlayBase_800AB9C8)
#endif
    {
        printf("Resident Memory Over !!\n");
    }

    return GV_ResidentMemoryBottom;
}
