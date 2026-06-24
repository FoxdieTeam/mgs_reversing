#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;    /* 0x000 */
    CONTROL control;   /* 0x020 */
    OBJECT  body;      /* 0x09C */
    char    pad_180[0x204 - 0x180];
    int     field_204; /* 0x204 */
    int     field_208; /* 0x208 */
    char    pad_20C[0x238 - 0x20C];
    short   field_238; /* 0x238 */
    char    pad_23A[0x894 - 0x23A];
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
int s05a_800DEC18(Work *work, SVECTOR *s2, int a2)
{
    int     v;
    int     heights[2];
    SVECTOR local;

    v = 1;
    if (work->field_204 == 0)
    {
        work->field_208 = 0;
    }

    if (a2 - s2->vy <= 0)
    {
        work->field_204 += s2->vy - a2;
    }
    if (work->field_204 < 0x190)
    {
        return a2;
    }

    if (work->field_208 == 0)
    {
        v = work->field_238;
        if (v <= 0)
        {
            v = 1;
        }
    }

    local = *s2;
    local.vy += 0x2710;
    if (HZD_LevelHazardCheck(work->control.map->hzd, &local, 3) != 1)
    {
        local.vy = 0;
    }
    else
    {
        HZD_GetLevelHeight(heights);
        local.vy = heights[0];
    }
    local.vy += 0x64;

    if (work->field_208 == 0)
    {
        work->field_208 = (s2->vy - local.vy) / v;
    }

    v = s2->vy - work->field_208;
    if (v < local.vy)
    {
        v = local.vy;
    }
    {
        int t = work->field_208 * 15;
        work->field_208 = t / 14;
    }
    if (work->field_208 >= 0x3E9)
    {
        work->field_208 = 0x3E8;
    }
    return v;
}
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
void s05a_800E0E28(CONTROL *control, HZD_HDL *hzd)
{
    SVECTOR local;
    int     half = control->r_sphere / 2;
    int     dist = control->step.vx;

    if (dist < 0)
    {
        dist = -dist;
    }
    if (control->step.vz > 0)
    {
        dist += control->step.vz;
    }
    else
    {
        dist -= control->step.vz;
    }

    if (half < dist)
    {
        GV_AddVec3(&control->mov, &control->step, &local);
        if (HZD_OnlineHazardCheck(hzd, &control->mov, &local, 5, control->seg_flag))
        {
            int len;
            int diff;

            control->n_touches = 1;
            control->segs[0] = HZD_GetOnlineHazard();
            control->is_edge[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(control->vecs);
            len = GV_VecLen3(control->vecs);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(control->vecs, &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(control->vecs, &local, len, diff);
            }
            control->step = local;
        }
    }
}
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
