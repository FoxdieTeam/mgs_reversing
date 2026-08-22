#include "game/game.h"
#include "chara/snake/sna_init.h"
#include "libhzd/libhzd.h"

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DDCBC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEC18.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEDE8.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF834.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DF9C8.s")
void s05a_800DFFC0(SnaInitWork *work, void *pFn)
{
    short vec_x = 0;
    work->field_9B8_fn_anim = pFn;
    work->field_9BC_anim_frame = 0;
    work->field_A3A = 0;
    work->field_A38_local_data = 0;

    if ((GM_PlayerStatus & PLAYER_GROUND) != 0)
    {
        vec_x = work->field_A2A;
    }

    work->control.turn.vx = vec_x;
    work->control.turn.vz = 0;
}
void s05a_800DFFF8(SnaInitWork *work, int action_flag, int interp)
{
    if (work->body.action != action_flag)
    {
        GM_ConfigObjectAction(&work->body, action_flag, 0, interp);
    }
}
void s05a_800E002C(SnaInitWork *work, int a2, int interp, int a4)
{
    if (work->body.action2 != a2)
    {
        GM_ConfigObjectOverride(&work->body, a2, 0, interp, a4);
    }
}
int s05a_800E0068(PlayerStatusFlag flag)
{
    return (GM_PlayerStatus & flag) != 0;
}

int s05a_800E0080(PlayerStatusFlag flag)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus | flag;
    GM_PlayerStatus = temp_v0;
    return temp_v0;
}

void s05a_800E0098(PlayerStatusFlag flag)
{
    GM_PlayerStatus &= ~flag;
}

void s05a_800E00B0(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void s05a_800E00C4(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int s05a_800E00D8(SnaInitWork *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00EC.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E066C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E0D38.s")
void s05a_800E0E28(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR local;
    int     half;
    int     dist;
    int     len;
    int     diff;

    half = work->r_sphere / 2;
    dist = work->step.vx;
    if (dist < 0)
    {
        dist = -dist;
    }
    if (work->step.vz > 0)
    {
        dist += work->step.vz;
    }
    else
    {
        dist -= work->step.vz;
    }

    if (half < dist)
    {
        GV_AddVec3(&work->mov, &work->step, &local);
        if (HZD_OnlineHazardCheck(hzd, &work->mov, &local, 5, work->seg_flag) != 0)
        {
            work->n_touches = 1;
            work->segs[0] = HZD_GetOnlineHazard();
            work->is_edge[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(&work->vecs[0]);
            len = GV_VecLen3(&work->vecs[0]);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(&work->vecs[0], &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(&work->vecs[0], &local, len, diff);
            }
            work->step = local;
        }
    }
}
void s05a_800E0F64(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR react;
    int     hazard;

    hazard = HZD_NearHazardCheck(hzd, &work->mov, 0x1F4, 4, work->seg_flag);
    if (hazard > 0)
    {
        work->n_touches = hazard;
        HZD_GetNearHazard(&work->segs[0]);
        HZD_GetIsEdge(&work->is_edge[0]);
        HZD_GetNearVector(&work->vecs[0]);
        HZD_HazardReaction(&work->vecs[0], hazard, work->r_sphere, &react);
        work->mov.vx += react.vx;
        work->mov.vz += react.vz;
    }
}

void s05a_800E1014(CONTROL *work, HZD_HDL *hzd)
{
    int height[2];
    int flags;
    int y;
    int base;
    int lo;

    y = work->mov.vy + work->step.vy;
    base = work->height;
    work->grounded = 0;
    flags = HZD_LevelHazardCheck(hzd, &work->mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(height);

    if (flags & HZD_CHK_D_FLOOR)
    {
        if ((unsigned int)(height[1] - work->levels[0] + 0xC7) < 0x18F)
        {
            height[0] = height[1];
            flags &= ~HZD_CHK_D_FLOOR;
        }
    }
    if (!(flags & HZD_CHK_F_FLOOR))
    {
        height[0] = 0;
    }
    if (!(flags & HZD_CHK_D_FLOOR))
    {
        height[1] = 0x7D00;
    }

    lo = base;
    if (flags & HZD_CHK_F_FLOOR)
    {
        lo += height[0];
    }

    if (y < lo)
    {
        y = lo;
        work->grounded = 1;
    }
    else if ((flags & HZD_CHK_D_FLOOR) && height[1] - base < y)
    {
        y = height[1] - base;
        work->grounded = 2;
    }

    work->levels[0] = height[0];
    lo = (work->levels[1] = height[1]);
    work->mov.vy = y;
}
