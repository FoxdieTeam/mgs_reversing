#include "meryl72.h"
#include "libhzd/libhzd.h"
#include "mts/mts.h"

extern int GV_Time;

extern int      GM_PlayerMap_800ABA0C;
extern int      GM_NoisePower_800ABA24;
extern int      GM_NoiseLength_800ABA30;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  GM_NoisePosition_800AB9F8;
extern int      GM_AlertMode_800ABA00;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PlayerStatus_800ABA50;

void ML72_ExecPutChar_800CB600(Meryl72Work *);
void s07c_meryl72_unk1_800CABA0(Meryl72Work *);

void s07c_meryl72_unk2_800CEA04(Meryl72Work *);
void s07c_meryl72_unk2_800D0154(Meryl72Work *);

void s07c_meryl72_unk1_800CB660(Meryl72Work *work)
{
    RADAR_CONE *cone;

    cone = &work->control.radar_cone;
    cone->dir = work->vision.facedir;
    cone->len = work->vision.length;
    cone->ang = 1024;
    cone->_pad = 0;
}

void s07c_meryl72_unk1_800CB688(Meryl72Work *work)
{
    if (work->modetime[7] & 0x4)
    {
        if (work->target->damaged & (TARGET_POWER | TARGET_CAPTURE))
        {
            work->modetime[6] |= 0x4;
        }

        if (work->target2.damaged & TARGET_TOUCH)
        {
            work->vision.field_06 = 2;
        }
    }
}

int s07c_meryl72_unk1_800CB6E8(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to)
{
    int to_addr, from_addr;

    from_addr = HZD_GetAddress(hzd, from, -1);
    to_addr = HZD_GetAddress(hzd, to, -1);

    from_addr &= 0xFF;
    to_addr &= 0xFF;

    return HZD_ZoneDistance(hzd, from_addr, to_addr);
}

void s07c_meryl72_unk1_800CB748(Meryl72Work* work)
{
    CONTROL *control;
    int      dist;

    control = &work->control;

    if (!(work->modetime[7] & 1))
    {
        return;
    }

    if (!(control->map->index & GM_PlayerMap_800ABA0C))
    {
        return;
    }

    if (GM_NoisePower_800ABA24 == 0)
    {
        return;
    }

    switch (GM_NoisePower_800ABA24)
    {
    case 5:
        if (GV_DiffVec3(&GM_NoisePosition_800AB9F8, &control->mov) < 500)
        {
            work->modetime[6] |= 0x1;
        }
        break;

    case 200:
        if (GV_DiffVec3(&GM_NoisePosition_800AB9F8, &control->mov) < 4000)
        {
            work->modetime[6] |= 0x1;
        }
        break;

    case 100:
        dist = GV_DiffVec3(&GM_NoisePosition_800AB9F8, &control->mov);
        fprintf(1, "noise dis  =%d,\n", dist);

        if (dist < 4000)
        {
            dist = s07c_meryl72_unk1_800CB6E8(control->map->hzd, &control->mov, &GM_NoisePosition_800AB9F8);

            if (dist < 300)
            {
                work->modetime[6] |= 0x1;
                GM_NoiseLength_800ABA30 = 0;
                GM_NoisePower_800ABA24 = 0;
            }
        }
        break;

    case 255:
        work->modetime[6] |= 0x1;
        break;
    }
}

void s07c_meryl72_unk1_800CB8D4(Meryl72Work *work)
{
}

void s07c_meryl72_unk1_800CB8DC(Meryl72Work *work)
{
    work->modetime[6] = 0;

    s07c_meryl72_unk1_800CB748(work);

    if (GM_AlertMode_800ABA00 != 3)
    {
        s07c_meryl72_unk1_800CB688(work);
        s07c_meryl72_unk1_800CB8D4(work);
    }
}

void s07c_meryl72_unk1_800CB928(Meryl72Work *work)
{
    switch (work->vision.field_06)
    {
    case 0:
        if (work->fB18 != 255 || !(GM_PlayerStatus_800ABA50 & PLAYER_INTRUDE))
        {
            work->fB18 -= 4;
        }
        break;

    case 1:
        work->fB18--;
        break;

    case 2:
        work->fB18++;
        break;
    }

    if (work->fB18 < 0)
    {
        work->fB18 = 0;
    }
    else if (work->fB18 > 255)
    {
        work->fB18 = 255;
    }
}

void s07c_meryl72_unk1_800CB9DC(Meryl72Work *work)
{
    switch (work->vision.field_06)
    {
    case 0:
    case 1:
        work->fC0A -= 4;
        break;

    case 2:
        if (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON)
        {
            if (GV_DiffDirAbs(work->sn_dir, GM_PlayerControl_800AB9F4->rot.vy) > 1800)
            {
                work->fC0A++;
            }
            else
            {
                work->fC0A -= 2;
            }
        }
        else
        {
            work->fC0A -= 4;
        }
        break;
    }

    if (work->fC0A < 0)
    {
        work->fC0A = 0;
    }
    else if (work->fC0A > 1000)
    {
        work->fC0A = 1000;
    }
}

void s07c_meryl72_unk1_800CBA9C(Meryl72Work* work)
{
    SVECTOR  sn_diff;
    SVECTOR *mov;
    short   *pad;
    int      sn_dir, sn_dis;
    int      height;
    MAP     *map;

    pad = &work->vision.field_06;

    mov = &work->control.mov;
    GV_SubVec3(&GM_PlayerPosition_800ABA10, mov, &sn_diff);
    sn_diff.vy = 0;

    sn_dir = GV_VecDir2(&sn_diff);
    work->sn_dir = sn_dir;

    sn_dis = GV_VecLen3(&sn_diff);
    work->sn_dis = sn_dis;

    height = ABS(GM_PlayerPosition_800ABA10.vy - work->control.mov.vy);

    if (!(work->control.map->index & GM_PlayerMap_800ABA0C) || (GM_PlayerStatus_800ABA50 & PLAYER_INTRUDE))
    {
        work->vision.field_06 = 0;
        return;
    }

    if ((GV_Time % 3) != work->param.fAF8)
    {
        return;
    }

    if ((sn_dis > 6000) || (height > 2000) || (GV_DiffDirAbs(work->vision.facedir, sn_dir) > work->vision.angle))
    {
        *pad = 0;
        return;
    }

    map = work->control.map;
    if (HZD_80028454(map->hzd, &GM_PlayerPosition_800ABA10, mov, 0xF, 0x4) ||
        sub_8002E2A8(mov, &GM_PlayerPosition_800ABA10, map->index, &sn_diff))
    {
        work->vision.field_06 = 0;
    }
    else if (work->vision.length < sn_dis)
    {
        work->vision.field_06 = 1;
    }
    else
    {
        work->vision.field_06 = 2;
    }
}

void s07c_meryl72_unk1_800CBC44(Meryl72Work *work)
{
    if (work->f8BC.field_18 < 54)
    {
        s07c_meryl72_unk1_800CB660(work);
        s07c_meryl72_unk1_800CBA9C(work);
        s07c_meryl72_unk1_800CB8DC(work);
        s07c_meryl72_unk1_800CB928(work);
        s07c_meryl72_unk1_800CB9DC(work);

        if (work->fB94 == 0)
        {
            s07c_meryl72_unk2_800CEA04(work);
        }
        else
        {
            s07c_meryl72_unk2_800D0154(work);
        }

        ML72_ExecPutChar_800CB600(work);
    }

    s07c_meryl72_unk1_800CABA0(work);
}

void s07c_meryl72_unk1_800CBCD8(Meryl72Work *work)
{
    int      ang;
    TARGET  *target;
    int      f18;
    CONTROL *control;

    ang = 0;

    target = work->target;
    if (!(target->damaged & TARGET_PUSH))
    {
        return;
    }

    GV_AddVec3(&target->field_34_vec, &work->control.step, &work->control.step);
    target->damaged &= ~TARGET_PUSH;

    f18 = work->f8BC.field_18;
    if (f18 != 1 && f18 != 2)
    {
        return;
    }

    if (target->field_34_vec.pad != 0)
    {
        if (GV_Time & 256)
        {
            ang = target->field_34_vec.pad * 1024;
            if (!(work->param.fAF8 & 0x1))
            {
                ang = (target->field_34_vec.pad + 2) * 1024;
            }
        }
        else if (work->param.fAF8 & 1)
        {
            ang = (target->field_34_vec.pad + 2) * 1024;
        }
        else
        {
            ang = target->field_34_vec.pad * 1024;
        }

        ang &= 0xFFF;
    }

    control = &work->control;
    control->turn.vy = ang;
    control->field_36 = GV_NearExp2(control->field_36, work->f8BC.field_1A);
}
