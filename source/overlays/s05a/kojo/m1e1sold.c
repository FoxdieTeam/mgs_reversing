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
typedef struct _CamBbox
{
    char    pad_00[8];
    u_short field_08;
    char    pad_0A[0x10 - 0x0A];
    u_short field_10;
    char    pad_12[0x14 - 0x12];
    u_short field_14;
    char    pad_16[0x1C - 0x16];
    u_short field_1C;
} CamBbox;

typedef struct _CamModel
{
    char     pad_000[0x420];
    CamBbox *field_420;
    char     pad_424[0x4AC - 0x424];
    u_short  field_4AC;
    char     pad_4AE[0x4B0 - 0x4AE];
    u_short  field_4B0;
    char     pad_4B2[0x4B4 - 0x4B2];
    u_short  field_4B4;
} CamModel;

typedef struct _CamEb0
{
    char  pad_000[0x1C0];
    char *field_1C0;
} CamEb0;

typedef struct _CamActor
{
    char      pad_000[0xDC];
    CamModel *field_DC;
    char      pad_E0[0xDFC - 0xE0];
    int       field_DFC;
    char      pad_E00[0xE60 - 0xE00];
    int       field_E60;
    char      pad_E64[0xEB0 - 0xE64];
    CamEb0   *field_EB0;
} CamActor;

typedef struct _DfVec
{
    u_short field_0;
    u_short field_2;
    u_short field_4;
} DfVec;

extern CamActor *s05a_dword_800C362C;

int s05a_800DF834(int arg0, DfVec *vec, u_short *arg3)
{
    SVECTOR d;
    SVECTOR e;
    int     dist;

    if (arg0 != 0)
    {
        return 0;
    }
    if (s05a_dword_800C362C->field_EB0 == NULL)
    {
        return 0;
    }

    d.vx = s05a_dword_800C362C->field_DC->field_4AC;
    d.vy = s05a_dword_800C362C->field_DC->field_4B0;
    d.vz = s05a_dword_800C362C->field_DC->field_4B4;
    d.vx -= vec->field_0;
    d.vy -= vec->field_2;
    d.vz -= vec->field_4;

    e.vx = s05a_dword_800C362C->field_DC->field_420->field_14 -
           s05a_dword_800C362C->field_DC->field_420->field_08;
    e.vz = s05a_dword_800C362C->field_DC->field_420->field_1C -
           s05a_dword_800C362C->field_DC->field_420->field_10;
    e.vx = (e.vx + e.vz) >> 2;

    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist < e.vx * s05a_dword_800C362C->field_DFC)
    {
        GM_SeSetPan((SVECTOR *)(s05a_dword_800C362C->field_EB0->field_1C0 + 8), 0xB2,
                    s05a_dword_800C362C->field_E60);
        *arg3 |= 4;
        return 1;
    }
    return 0;
}
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
