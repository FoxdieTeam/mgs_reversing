#include "linker.h"
#include "libdg/libdg.h"
#include "libdg/dgd.h"

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int        SECTION(".sbss") N_StageObjs_800ABAA4;

extern DG_OBJS *StageObjs_800B7890[32];

void DG_DequeueObjs_800181E4(DG_OBJS *objs);
void DG_FreeObjs_800318D0(DG_OBJS *objs);

void GM_FreeMapObjs_80031028()
{
    int       counter;  // $s1
    DG_OBJS **pObjIter; // $s0

    counter = N_StageObjs_800ABAA4;
    for (pObjIter = StageObjs_800B7890; counter > 0; ++pObjIter)
    {
        if (*pObjIter)
        {
            DG_DequeueObjs_800181E4(*pObjIter);
            DG_FreePreshade_80032110(*pObjIter);
            DG_FreeObjs_800318D0(*pObjIter);
        }
        *pObjIter = 0;
        --counter;
    }
    N_StageObjs_800ABAA4 = 0;
}
