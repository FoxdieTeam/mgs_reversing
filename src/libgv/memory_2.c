//I'm guessing this got compiled further into the linker file becuase it doesn't get used until later
#include "libgv.h"

//**bss*************************************//
extern GV_Heap MemorySystems_800AD2F0[3];
//******************************************//

void *GV_SplitMemory_80018FA4(int which, void *addr, int size)
{
    int                  sum;
    int                  i, t2;
    GV_Heap             *heap;
    GV_MemoryAllocation *alloc;

    t2 = 0;
    heap = &MemorySystems_800AD2F0[ which ];

    alloc = heap->mAllocs;
    i = heap->mUnitsCount;
    while (i > 0)
    {
        if (alloc->mAllocType == GV_MemoryAllocation_States_Free_0)
        {
            sum = (alloc[1].mPDataStart - alloc[0].mPDataStart) / size;
            t2 += sum;
        }
        --i;
        alloc++;
    }

    *(long*)addr = t2;
    return heap;
}