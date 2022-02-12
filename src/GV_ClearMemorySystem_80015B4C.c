#include "linker.h"
#include "system.h"

extern GV_Heap MemorySystems_800AD2F0[3];

void System_dynamic_reset_800159B8(GV_Heap *pHeap);
void System_voided_reset_80015924(GV_Heap *pHeap);

void GV_ClearMemoryGV_ClearMemoryGV_ClearMemoryGV_ClearMemorySystem_80015B4C(int idx)
{
    GV_Heap *pHeap = &MemorySystems_800AD2F0[idx];
    int flags = pHeap->mFlags;
    if (flags & (GV_Heap_Flags_Failed_4 | GV_Heap_Flags_Voided_2))
    {
        if (flags & GV_Heap_Flags_Failed_4)
        {
            if (flags & GV_Heap_Flags_Dynamic_1)
            {
                System_dynamic_reset_800159B8(pHeap);
                pHeap->mFlags &= ~(GV_Heap_Flags_Failed_4 | GV_Heap_Flags_Voided_2);
            }
        }
        if (flags & GV_Heap_Flags_Voided_2)
        {
            System_voided_reset_80015924(pHeap);
            pHeap->mFlags &= ~GV_Heap_Flags_Voided_2;
        }
    }
    pHeap->mFlags &= ~(GV_Heap_Flags_Failed_4 | GV_Heap_Flags_Voided_2);
}
