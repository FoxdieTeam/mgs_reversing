#include "linker.h"
#include "libdg\libdg.h"

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int SECTION(".sbss") N_StageObjs_800ABAA4;

extern DG_OBJS *StageObjs_800B7890[32];
extern MATRIX DG_ZeroMatrix_8009D430;

extern int gMapsChanged_800ABAAC;
int SECTION(".sbss") gMapsChanged_800ABAAC;

// re-declare to force GP usage
extern int gMapCount_800ABAA8;
int SECTION(".sbss") gMapCount_800ABAA8;

void Map_ResetMapCountAndKmdsCount_800310A0()
{
    DG_OBJS **v0; // $v0
    int i;        // $v1

    v0 = StageObjs_800B7890;
    for (i = 32; i > 0; --i)
    {
        *v0++ = 0;
    }

    N_StageObjs_800ABAA4 = 0;
    gMapCount_800ABAA8 = 0;
    gMapsChanged_800ABAAC = 0;
}
