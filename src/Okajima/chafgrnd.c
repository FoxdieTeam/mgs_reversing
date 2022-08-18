#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "libdg/libdg.h"

extern int   GM_GameStatus_800AB3CC;

void chafgrnd_init_tiles_800769EC(TILE *a1)
{
    TILE        *pIter = a1;
    int          i;
    unsigned int rand_width, rand_height;

    for (i = 64; i > 0; i--)
    {
        setTile(pIter);
        rand_width = GV_RandU_80017090(2) + 1;
        rand_height = GV_RandU_80017090(2) + 1;
        setWH(pIter, rand_width, rand_height);
        pIter++;
    }
}

#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A6C.s") // 44 bytes
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_helper_80076A98.s") // 144 bytes
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_act_80076B28.s")        // 1260 bytes
#pragma INCLUDE_ASM("asm/Okajima/chafgrnd_loader_80077014.s")     // 520 bytes

void chafgrnd_kill_8007721C(int param_1)
{
    DG_OBJS *objs;

    objs = *(DG_OBJS **)(param_1 + 0xa34);
    GM_GameStatus_800AB3CC &= ~1;

    if (objs)
    {
        DG_DequeuePrim_800182E0(objs);
        DG_FreePrim_8001BC04(objs);
    }
}

#pragma INCLUDE_ASM("asm/Okajima/NewChaffGrd_80077264.s")         // 472 bytes
