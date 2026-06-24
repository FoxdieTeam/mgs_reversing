#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;    /* 0x000 */
    CONTROL control;   /* 0x020 */
    OBJECT  body;      /* 0x09C */
    char    pad_180[0x894 - 0x180];
    int     field_894; /* 0x894 */
    char    pad_898[0x9B8 - 0x898];
    int     field_9B8; /* 0x9B8 */
    int     field_9BC; /* 0x9BC */
    char    pad_9C0[0xA2A - 0x9C0];
    unsigned short field_A2A; /* 0xA2A */
    char    pad_A2C[0xA38 - 0xA2C];
    short   field_A38; /* 0xA38 */
    short   field_A3A; /* 0xA3A */
} Work;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DDCBC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEC18.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEDE8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF834.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF9C8.s")

void s05a_800DFFC0(Work *work, int arg)
{
    short v;

    work->field_9B8 = arg;
    work->field_9BC = 0;
    work->field_A3A = 0;
    work->field_A38 = 0;
    v = 0;
    if (GM_PlayerStatus & PLAYER_GROUND)
    {
        v = work->field_A2A;
    }
    work->control.turn.vx = v;
    work->control.turn.vz = 0;
}

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

int s05a_800E00D8(Work *work, int mask)
{
    return (work->field_894 & mask) != 0;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00EC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E066C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0D38.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0E28.s")
void s05a_800E0F64(CONTROL *control, HZD_HDL *hzd)
{
    SVECTOR react;
    int     n;

    n = HZD_NearHazardCheck(hzd, &control->mov, 0x1F4, 4, control->seg_flag);
    if (n > 0)
    {
        SVECTOR *vecs;

        control->n_touches = n;
        HZD_GetNearHazard(control->segs);
        HZD_GetIsEdge(control->is_edge);
        vecs = control->vecs;
        HZD_GetNearVector(vecs);
        HZD_HazardReaction(vecs, n, control->r_sphere, &react);
        control->mov.vx += react.vx;
        control->mov.vz += react.vz;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1014.s")
