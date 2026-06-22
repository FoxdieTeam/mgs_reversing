#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;    /* 0x000 */
    CONTROL control;   /* 0x020 */
    OBJECT  body;      /* 0x09C */
    char    pad_180[0x894 - 0x180];
    int     field_894; /* 0x894 */
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

int s05a_800E0068(int mask)
{
    return (GM_PlayerStatus & mask) != 0;
}

int s05a_800E0080(int mask)
{
    return GM_PlayerStatus |= mask;
}

void s05a_800E0098(int mask)
{
    GM_PlayerStatus &= ~mask;
}

int s05a_800E00B0(Work *work, int mask)
{
    return work->field_894 |= mask;
}

int s05a_800E00C4(Work *work, int mask)
{
    return work->field_894 &= ~mask;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00D8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00EC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E066C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0D38.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0E28.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0F64.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1014.s")
