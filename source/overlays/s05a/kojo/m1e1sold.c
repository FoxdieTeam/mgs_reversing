#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;   /* 0x000 */
    CONTROL control;  /* 0x020 */
    OBJECT  body;     /* 0x09C */
} Work;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DDCBC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEC18.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEDE8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF834.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF9C8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DFFC0.s")

void s05a_800DFFF8(Work *work, int action, int interp)
{
    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, interp);
    }
}

void s05a_800E002C(Work *work, int action, int interp, u_long mask)
{
    if (work->body.action2 != action)
    {
        GM_ConfigObjectOverride(&work->body, action, 0, interp, mask);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0068.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0080.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0098.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00B0.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00C4.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00D8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00EC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E066C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0D38.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0E28.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0F64.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1014.s")
