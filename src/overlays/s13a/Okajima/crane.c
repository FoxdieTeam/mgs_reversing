#include "common.h"
#include "mts/mts.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Game/vibrate.h"
#include "SD/g_sound.h"

typedef struct _CraneWork
{
    GV_ACT  actor;
    OBJECT  main;
    OBJECT  arm;
    MATRIX  light_main[2];
    MATRIX  light_arm[2];
    char    pad1[0x40];
    TARGET *target;
    HZD_SEG d_hzd_side[4];
    char    pad2[0x4];
    int     f2F0;
    SVECTOR nodes[2];
    int     think1;
    int     think2;
    int     think3;
    int     f310;
    int     f314;
    int     f318;
    SVECTOR dif;
    SVECTOR f324;
    SVECTOR mov;
    SVECTOR f334;
    SVECTOR f33C;
    SVECTOR f344;
    char    pad3[0x8];
    int     step_num;
    int     map;
    int     crash_flag;
    int     f360;
    int     f364;
    int     has_target;
    int     ticks;
    int     f370;
    int     f374;
    int     f378;
    int     status;
    int     before_step_num;
    int     f384;
    int     f388;
    int     f38C;
    int     f390;
} CraneWork;

extern int      GM_CurrentMap;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PadVibration;
extern int      GM_PlayerStatus;
extern int      GM_PadVibration2;

char crane_800C35F4[] = {0x00, 0x00, 0x00, 0x00};
char crane_800C35F8[] = {0xAF, 0x04, 0x28, 0x03, 0x23, 0x03, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00};
char crane_800C3604[] = {0x7F, 0x01, 0x00, 0x00};
char crane_800C3608[] = {0xAF, 0x04, 0x28, 0x03, 0x23, 0x03, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00};

SVECTOR crane_800C3614 = {500, 500, 300, 0};

void AN_Unknown_800CCA40(SVECTOR *pos);
void AN_Unknown_800CCB84(SVECTOR *pos);

#define EXEC_LEVEL GV_ACTOR_LEVEL4

void s13a_crane_800D3994(HZD_SEG *out, MATRIX *world, SVECTOR *min, SVECTOR *max)
{
    SVECTOR  bbox[8];
    SVECTOR  bmin[4];
    SVECTOR  bmax[4];
    int      idx;
    int      i;

    bbox[0].vx = min->vx;
    bbox[0].vy = min->vy;
    bbox[0].vz = min->vz;
    bbox[1].vx = min->vx;
    bbox[1].vy = min->vy;
    bbox[1].vz = max->vz;
    bbox[2].vx = max->vx;
    bbox[2].vy = min->vy;
    bbox[2].vz = max->vz;
    bbox[3].vx = max->vx;
    bbox[3].vy = min->vy;
    bbox[3].vz = min->vz;
    bbox[4].vx = min->vx;
    bbox[4].vy = max->vy;
    bbox[4].vz = min->vz;
    bbox[5].vx = min->vx;
    bbox[5].vy = max->vy;
    bbox[5].vz = max->vz;
    bbox[6].vx = max->vx;
    bbox[6].vy = max->vy;
    bbox[6].vz = max->vz;
    bbox[7].vx = max->vx;
    bbox[7].vy = max->vy;
    bbox[7].vz = min->vz;

    DG_SetPos(world);
    DG_PutVector(bbox, bbox, 8);

    idx = 0;
    bmin[0] = bbox[0];

    for (i = 0; i < 8; i++)
    {
        if (bbox[i].vx < bmin[0].vx || (bbox[i].vx == bmin[0].vx && bbox[i].vz < bmin[0].vz))
        {
            idx = i;
            bmin[0] = bbox[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    bmax[0] = bmin[0];
    bmin[0].vy = MIN(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[0].vy = MAX(bbox[idx].vy, bbox[idx + 4].vy);

    idx = 0;
    bmin[1] = bbox[0];

    for (i = 0; i < 8; i++)
    {
        if (bbox[i].vz > bmin[1].vz || (bbox[i].vz == bmin[1].vz && bbox[i].vx < bmin[1].vx))
        {
            idx = i;
            bmin[1] = bbox[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    bmax[1] = bmin[1];
    bmin[1].vy = MIN(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[1].vy = MAX(bbox[idx].vy, bbox[idx + 4].vy);

    idx = 0;
    bmin[2] = bbox[0];

    for (i = 0; i < 8; i++)
    {
        if (bbox[i].vx > bmin[2].vx || (bbox[i].vx == bmin[2].vx && bbox[i].vz > bmin[2].vz))
        {
            idx = i;
            bmin[2] = bbox[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    bmax[2] = bmin[2];
    bmin[2].vy = MIN(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[2].vy = MAX(bbox[idx].vy, bbox[idx + 4].vy);

    idx = 0;
    bmin[3] = bbox[0];

    for (i = 0; i < 8; i++)
    {
        if (bbox[i].vz < bmin[3].vz || (bbox[i].vz == bmin[3].vz && bbox[i].vx > bmin[3].vx))
        {
            idx = i;
            bmin[3] = bbox[i];
        }
    }

    if (idx >= 4)
    {
        idx -= 4;
    }

    bmax[3] = bmin[3];
    bmin[3].vy = MIN(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[3].vy = MAX(bbox[idx].vy, bbox[idx + 4].vy);

    out[1].p1.x = bmin[1].vx;
    out[1].p1.z = bmin[1].vz;
    out[1].p1.y = bmin[1].vy;
    out[1].p1.h = bmax[1].vy - bmin[1].vy;

    out[1].p2.x = bmin[2].vx;
    out[1].p2.z = bmin[2].vz;
    out[1].p2.y = bmin[2].vy;
    out[1].p2.h = bmax[2].vy - bmin[2].vy;

    out[3].p1.x = bmin[0].vx;
    out[3].p1.z = bmin[0].vz;
    out[3].p1.y = bmin[0].vy;
    out[3].p1.h = bmax[0].vy - bmin[0].vy;

    out[3].p2.x = bmin[3].vx;
    out[3].p2.z = bmin[3].vz;
    out[3].p2.y = bmin[3].vy;
    out[3].p2.h = bmax[3].vy - bmin[3].vy;
}

int s13a_crane_800D4038(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;
    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

void s13a_crane_800D408C(CraneWork *work)
{
    SVECTOR pos;
    int     mult;

    mult = work->step_num;
    work->mov.vx = (work->dif.vx * mult) / 255 + work->nodes[0].vx + work->f324.vx + work->f334.vx;
    work->mov.vy = (work->dif.vy * mult) / 255 + work->nodes[0].vy + work->f324.vy + work->f334.vy;
    work->mov.vz = (work->dif.vz * mult) / 255 + work->nodes[0].vz + work->f324.vz + work->f334.vz;

    if (work->f364 == 0 && work->mov.vy <= 1000)
    {
        work->f364 = 128;
    }

    if (work->crash_flag != 0 && work->f360 < 150)
    {
        work->f360++;

        pos.vx = work->mov.vx - 2400;
        pos.vy = work->mov.vy - 1500;
        pos.vz = work->mov.vz;

        if (work->status == 0)
        {
            AN_Unknown_800CCA40(&pos);
        }
    }
}

int s13a_crane_800D420C(CraneWork *work)
{
    switch (work->think3)
    {
    case 0:
        GM_SeSet(&work->mov, 179);

        work->f314 = GV_RandU(64) + 128;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            return 0;
        }
        break;
    }

    return 1;
}

int s13a_crane_800D428C(CraneWork *work)
{
    switch (work->think3)
    {
    case 0:
        work->f314 = GV_RandU(32) + 32;
        work->f310 = 0;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if ((mts_get_tick_count() - work->ticks) > 25)
        {
            work->ticks = mts_get_tick_count();
            GM_SeSet(&work->mov, 178);
        }

        if (work->step_num > 255)
        {
            work->step_num = 255;
            work->f318 = -1;
            return 1;
        }

        if (work->step_num < 0)
        {
            work->step_num = 0;
            work->f318 = 1;
            return 1;
        }

        if (work->f314-- > 0)
        {
            work->step_num += work->f318;
            return 0;
        }
        break;
    }

    return 1;
}

int s13a_crane_800D4390(CraneWork *work)
{
    switch (work->think3)
    {
    case 0:
        work->f310 = 0;
        work->f314 = GV_RandU(128) + 64;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if ((mts_get_tick_count() - work->ticks) > 25)
        {
            work->ticks = mts_get_tick_count();
            GM_SeSet(&work->mov, 178);
        }

        if (work->step_num > 255)
        {
            work->step_num = 255;
            work->f318 = -1;
            return 1;
        }

        if (work->step_num < 0)
        {
            work->step_num = 0;
            work->f318 = 1;
            return 1;
        }

        if (work->f314-- > 0)
        {
            work->step_num += work->f318 * 2;
            return 0;
        }
        break;
    }

    return 1;
}

int s13a_crane_800D4498(CraneWork *work)
{
    switch (work->think3)
    {
    case 0:
        work->f310 = 32;
        work->f314 = 8;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f324.vz = GV_RandS(16);
            return 0;
        }

        work->f324 = DG_ZeroVector;
        break;
    }

    return 1;
}

int s13a_crane_800D4548(CraneWork *work)
{
    switch (work->think3)
    {
    case 0:
        if (work->status < 1 || work->status > 2)
        {
            GM_SeSet2(0, 63, 188);
        }

        work->f310 = 0;
        work->f314 = 16;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f33C.vz += 10;
            work->f334.vy -= 48;
            work->f334.vx += 12;

            work->f324.vx = GV_RandS(16);
            work->f324.vy = GV_RandS(16);
            work->f324.vz = GV_RandS(16);
            return 0;
        }

        work->f314 = 16;
        work->think3 = 2;
        /* fallthrough */

    case 2:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 10;
            work->f33C.vy += 8;
            work->f334.vz += 22;

            work->f324.vx = GV_RandS(16);
            work->f324.vy = GV_RandS(16);
            work->f324.vz = GV_RandS(16);
            return 0;
        }

        work->f314 = 32;
        work->think3 = 3;
        /* fallthrough */

    case 3:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 5;
            work->f33C.vy += 4;
            work->f334.vz += 11;

            work->f324.vx = GV_RandS(16);
            work->f324.vy = GV_RandS(16);
            work->f324.vz = GV_RandS(16);
            return 0;
        }

        work->f324 = DG_ZeroVector;
        break;
    }

    return 1;
}

int s13a_crane_800D4724(CraneWork *work)
{
    unsigned short f314;

    switch (work->think3)
    {
    case 0:
        if (work->status != 2)
        {
            GM_SeSet2(0, 63, 189);
        }

        work->f314 = 80;
        work->think3 = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 20;

            f314 = work->f314;
            work->f334.vy -= 4 * f314 & 0xffff;

            f314 = work->f314;
            work->mov.vy -= 4 * f314 & 0xffff;
            return 0;
        }

        DG_InvisibleObjs(work->main.objs);
        DG_InvisibleObjs(work->arm.objs);

        work->f324 = DG_ZeroVector;
        break;
    }

    return 1;
}

int s13a_crane_800D4844(CraneWork *work)
{
    SVECTOR pos;

    switch (work->think3)
    {
    case 0:
        work->f314 = 200;
        work->think3 = 2;
        /* fallthrough */

    case 2:
        if (work->f314-- > 0)
        {
            pos = work->mov;
            pos.vy = -1000;

            if (work->status != 2)
            {
                AN_Unknown_800CCB84(&pos);
            }

            return 0;
        }

        work->f324 = DG_ZeroVector;
        break;
    }

    return 1;
}

void s13a_crane_800D4918(CraneWork *work)
{
    switch (work->think2)
    {
    case 3:
        if (s13a_crane_800D4498(work))
        {
            if (GV_RandU(16) < 8)
            {
                work->think2 = 1;
            }
            else
            {
                work->think2 = 2;
            }

            work->think3 = 0;
        }
        break;

    case 4:
        if (s13a_crane_800D4498(work))
        {
            work->think2 = 0;
            work->think3 = 0;
        }
        break;

    case 0:
        if (s13a_crane_800D420C(work))
        {
            work->think2 = 3;
            work->think3 = 0;
        }
        break;

    case 1:
        if (s13a_crane_800D428C(work))
        {
            work->think2 = 4;
            work->think3 = 0;
        }
        break;

    case 2:
        if (s13a_crane_800D4390(work))
        {
            work->think2 = 4;
            work->think3 = 0;
        }
        break;
    }

    work->f310++;
    work->f344.vx = rsin(work->f310 * work->f318 * 64) / (work->f310 * 4 + 64);

    if (work->f310 > 128)
    {
        work->f344.vx = 0;
    }
}

void s13a_crane_800D4A60(CraneWork *work)
{
    switch (work->think2)
    {
    case 6:
        if (s13a_crane_800D4548(work))
        {
            work->think2 = 8;
            work->think3 = 0;
        }
        break;

    case 8:
        if (work->crash_flag >= 2 && s13a_crane_800D4724(work))
        {
            work->think2 = 9;
            work->think3 = 0;
        }
        break;

    case 9:
        s13a_crane_800D4844(work);
        break;
    }

    work->f310++;
    work->f344.vx = (rsin(work->f310 * work->f318 * 64) * 4) / (work->f310 * 4 + 64);

    if (work->f310 > 256)
    {
        work->f344.vx = 0;
    }
}

void s13a_crane_800D4B8C(CraneWork *work)
{
    switch (work->think1)
    {
    case 0:
        s13a_crane_800D4918(work);
        break;

    case 1:
        s13a_crane_800D4A60(work);
        break;
    }
}

void CranePutData_800D4BDC(CraneWork *work, int param)
{
    GCL_ARGS args;
    long     data[2];

    data[0] = param;
    data[1] = work->step_num;

    args.argc = 2;
    args.argv = data;

    if (work->f374 != -1)
    {
        GCL_ExecProc(work->f374, &args);
    }
}

void CraneAct_800D4C28(CraneWork *work)
{
    SVECTOR  sp10;
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  bound[2];
    MATRIX   world;
    HZD_HDL *hzd;
    SVECTOR *pos;
    SVECTOR *rot;
    TARGET  *target;

    GM_CurrentMap = work->map;

    hzd = GM_GetMap(work->map)->hzd;

    if (work->status == 2)
    {
        DG_InvisibleObjs(work->main.objs);
        DG_InvisibleObjs(work->arm.objs);
    }

    if (work->f388 > 0)
    {
        work->f388--;

        switch (work->f390)
        {
        case 0:
            if (work->f38C-- > 0)
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = 255;
            }
            break;

        case 1:
            if (work->f38C == 0)
            {
                work->f38C = -1;
                NewPadVibration(crane_800C35F4, 1);
                NewPadVibration(crane_800C35F8, 2);
            }
            break;
        }

        if (work->f388 == 0)
        {
            NewPadVibration(crane_800C3604, 1);
            NewPadVibration(crane_800C3608, 2);
        }
    }

    if (work->f378 < 10)
    {
        work->f378++;
    }

    if (work->f378 > 4 &&
        GM_PlayerPosition_800ABA10.vx < -7500 &&
        ((GM_PlayerPosition_800ABA10.vz < -5000 && GM_PlayerPosition_800ABA10.vz > -12500) || GM_PlayerPosition_800ABA10.vz > -2000) &&
        !(GM_PlayerStatus & PLAYER_CAUTION) &&
        work->f370 != -1)
    {
        if (GM_SnakeCurrentHealth == 0)
        {
            GM_GameOverTimer = 0;
            GM_PlayerControl_800AB9F4->skip_flag &= ~CTRL_SKIP_TRAP;
            GM_SnakeCurrentHealth = 1;
        }

        GCL_ExecProc(work->f370, NULL);

        work->f390 = 1;
        work->f370 = -1;
        work->f388 = 48;
        work->f38C = 0;
    }

    if (work->f378 <= 500)
    {
        if (work->f378 > 100)
        {
            work->f378++;
        }

        s13a_crane_800D4B8C(work);
        s13a_crane_800D408C(work);

        pos = &work->mov;
        rot = &work->f33C;

        sp18.vx = 0;
        sp18.vy = 0;
        sp18.vz = 0;

        DG_SetPos2(pos, rot);
        DG_MovePos(&sp18);

        GM_ActObject2(&work->main);
        DG_GetLightMatrix(pos, work->light_main);

        DG_SetPos2(pos, &work->f344);
        DG_MovePos(&sp18);

        sp20.vx = -400;
        sp20.vy = 200;
        sp20.vz = 0;

        DG_MovePos(&sp20);

        GM_ActObject2(&work->arm);
        DG_GetLightMatrix(pos, work->light_arm);

        HZD_DequeueDynamicSegment(hzd, &work->d_hzd_side[1]);
        HZD_DequeueDynamicSegment(hzd, &work->d_hzd_side[3]);

        DG_SetPos2(pos, rot);
        ReadRotMatrix(&world);

        bound[0].vx = -3000;
        bound[0].vy = -500;
        bound[0].vz = -250;

        bound[1].vx = 3000;
        bound[1].vy = 500;
        bound[1].vz = 250;

        world.t[1] += 500;

        s13a_crane_800D3994(work->d_hzd_side, &world, &bound[0], &bound[1]);

        if ((work->crash_flag == 2 && work->f378 > 300) || work->status == 2)
        {
            HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[1], 0xD7);
            HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[3], 0xD7);
        }
        else
        {
            HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[1], 0x57);
            HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[3], 0x57);
        }

        target = work->target;

        if (work->crash_flag == 0)
        {
            if (target->damaged & TARGET_POWER || work->status != 0)
            {
                switch (work->status)
                {
                case 0:
                    CranePutData_800D4BDC(work, 1);
                    break;

                case 1:
                    work->step_num = work->before_step_num;
                    work->mov.vz = work->nodes[0].vz + (work->dif.vz * work->step_num) / 255;
                    break;

                case 2:
                    break;
                }

                target->damaged &= ~TARGET_POWER;

                if (target->a_mode == ATK_BLAST || work->status != 0)
                {
                    work->crash_flag = 1;
                    work->think1 = 1;
                    work->think2 = 6;
                    work->think3 = 0;
                    return;
                }
            }

            if (target->damaged & TARGET_PUSH)
            {
                if (((work->think2 > 0 && work->think2 < 3 && work->f314 > 0 &&
                    ((work->mov.vz - GM_PlayerPosition_800ABA10.vz) * work->f318) < 0) ||
                    ABS(work->mov.vz - GM_PlayerPosition_800ABA10.vz) < 400) &&
                    work->f370 != -1)
                {
                    if (GM_SnakeCurrentHealth == 0)
                    {
                        GM_GameOverTimer = 0;
                        GM_PlayerControl_800AB9F4->skip_flag &= ~CTRL_SKIP_TRAP;
                        GM_SnakeCurrentHealth = 1;
                    }

                    GCL_ExecProc(work->f370, NULL);
                    work->f370 = -1;

                    GM_SeSet2(0, 63, SE_HIT_FLOOR);

                    work->f388 = 48;
                    work->f390 = 0;
                    work->f38C = 10;
                }

                target->damaged &= ~0x8;
            }

            sp10.vx = work->mov.vx - 2200;
            sp10.vy = work->mov.vy - 1000;
            sp10.vz = work->mov.vz;
            GM_MoveTarget(target, &sp10);
        }

        else if (work->crash_flag == 1)
        {
            if ((target->damaged & 0x4 && target->a_mode == 2) || work->status >= 2)
            {
                if (work->status < 2)
                {
                    CranePutData_800D4BDC(work, 2);
                }

                work->crash_flag = 2;
                work->f378 = 111;

                target->damaged &= ~0x4;
                GM_FreeTarget(work->target);
                work->has_target = 0;
                return;
            }

            sp10.vx = work->mov.vx - 1900;
            sp10.vy = work->mov.vy - 1000;
            sp10.vz = work->mov.vz;
            GM_MoveTarget(target, &sp10);
        }
        else if (work->has_target != 0 && work->status >= 2)
        {
            work->f378 = 111;
        }
    }
}

void s13a_crane_800D5338(CraneWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, TARGET_SEEK | TARGET_PUSH | TARGET_POWER, NO_SIDE, &crane_800C3614);
    target->field_3C = 1;
    work->has_target = 1;
}

int s13a_crane_800D5394(CraneWork *work, int name)
{
    SVECTOR  sp10;
    SVECTOR  sp18;
    HZD_HDL *hzd;
    char    *opt;

    hzd = GM_GetMap(work->map)->hzd;

    s13a_crane_800D5338(work);

    opt = GCL_GetOption('r');
    if (opt != NULL)
    {
        work->f2F0 = s13a_crane_800D4038(opt, work->nodes);
        work->mov.vx = work->nodes[0].vx;
        work->mov.vy = work->nodes[0].vy;
        work->mov.vz = work->nodes[0].vz;
    }

    work->f334 = DG_ZeroVector;
    work->f33C = DG_ZeroVector;

    opt = GCL_GetOption('d');
    if (opt != NULL)
    {
        work->f370 = GCL_StrToInt(opt);
    }
    else
    {
        work->f370 = -1;
    }

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        work->f374 = GCL_StrToInt(opt);
    }
    else
    {
        work->f374 = -1;
    }

    opt = GCL_GetOption('c');
    if (opt != NULL)
    {
        work->status = GCL_StrToInt(opt);
    }
    else
    {
        work->status = 0;
    }

    if (work->status == 1)
    {
        opt = GCL_GetOption('f');
        if (opt != NULL)
        {
            work->before_step_num = GCL_StrToInt(opt);
        }
        else
        {
            work->before_step_num = 0;
        }
    }

    work->f378 = 0;
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->f318 = 1;
    work->step_num = 0;

    sp10 = work->nodes[0];
    sp18 = work->nodes[1];

    work->dif.vx = sp18.vx - sp10.vx;
    work->dif.vy = sp18.vy - sp10.vy;
    work->dif.vz = sp18.vz - sp10.vz;

    work->f324 = DG_ZeroVector;

    work->crash_flag = 0;
    work->f360 = 0;
    work->f364 = 0;

    if (work->status == 2)
    {
        HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[1], 0xD7);
        HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[3], 0xD7);
    }
    else
    {
        HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[1], 0x57);
        HZD_QueueDynamicSegment2(hzd, &work->d_hzd_side[3], 0x57);
    }

    work->f384 = 0;
    return 0;
}

int CraneGetResources_800D5620(CraneWork *work, int map)
{
    SVECTOR step;
    OBJECT *object;

    work->map = map;
    step = DG_ZeroVector;

    object = &work->main;
    GM_InitObject(object, GV_StrCode("cr_main"), 0x2D, 0);
    GM_ConfigObjectJoint(object);
    GM_ConfigObjectLight(object, work->light_main);
    GM_ConfigObjectStep(object, &step);

    object = &work->arm;
    GM_InitObject(object, GV_StrCode("cr_arm"), 0x2D, 0);
    GM_ConfigObjectJoint(object);
    GM_ConfigObjectLight(object, work->light_arm);
    GM_ConfigObjectStep(object, &step);

    work->ticks = mts_get_tick_count();
    work->f388 = -1;
    work->f38C = -1;
    return 0;
}

void CraneDie_800D5724(CraneWork *work)
{
    HZD_HDL *hzd;

    hzd = GM_GetMap(work->map)->hzd;
    HZD_DequeueDynamicSegment(hzd, &work->d_hzd_side[1]);
    HZD_DequeueDynamicSegment(hzd, &work->d_hzd_side[3]);

    GM_FreeObject(&work->main);
    GM_FreeObject(&work->arm);

    if (work->has_target != 0)
    {
        GM_FreeTarget(work->target);
    }
}

GV_ACT *NewCrane_800D57A0(int name, int where)
{
    CraneWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(CraneWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, CraneAct_800D4C28, CraneDie_800D5724, "crane.c");

        if (CraneGetResources_800D5620(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        s13a_crane_800D5394(work, name);
    }

    return &work->actor;
}
