#include "common.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Game/vibrate.h"

typedef struct _CraneWork
{
    GV_ACT  actor;
    OBJECT  main;
    OBJECT  arm;
    MATRIX  light_main[2];
    MATRIX  light_arm[2];
    char    pad1[0x40];
    TARGET *target;
    HZD_SEG f2AC[4];
    char    pad2[0x4];
    int     f2F0;
    SVECTOR f2F4[2];
    int     f304;
    int     f308;
    int     f30C;
    int     f310;
    int     f314;
    int     f318;
    SVECTOR f31C;
    SVECTOR f324;
    SVECTOR f32C;
    SVECTOR f334;
    SVECTOR f33C;
    SVECTOR f344;
    char    pad3[0x8];
    int     f354;
    int     map;
    int     f35C;
    int     f360;
    int     f364;
    int     has_target;
    int     ticks;
    int     f370;
    int     f374;
    int     f378;
    int     f37C;
    int     f380;
    int     f384;
    int     f388;
    int     f38C;
    int     f390;
} CraneWork;

extern SVECTOR  DG_ZeroVector_800AB39C;
extern int      GM_GameOverTimer_800AB3D4;
extern int      GM_CurrentMap_800AB9B0;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PadVibration_800ABA3C;
extern int      GM_PlayerStatus_800ABA50;
extern int      GM_PadVibration2_800ABA54;

char crane_800C35F4[] = {0x00, 0x00, 0x00, 0x00};
char crane_800C35F8[] = {0xAF, 0x04, 0x28, 0x03, 0x23, 0x03, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00};
char crane_800C3604[] = {0x7F, 0x01, 0x00, 0x00};
char crane_800C3608[] = {0xAF, 0x04, 0x28, 0x03, 0x23, 0x03, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00};

SVECTOR crane_800C3614 = {500, 500, 300, 0};

void AN_Unknown_800CCA40(SVECTOR *pos);
void AN_Unknown_800CCB84(SVECTOR *pos);

#define EXEC_LEVEL 4

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

    DG_SetPos_8001BC44(world);
    DG_PutVector_8001BE48(bbox, bbox, 8);

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
    bmin[0].vy = __min(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[0].vy = __max(bbox[idx].vy, bbox[idx + 4].vy);

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
    bmin[1].vy = __min(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[1].vy = __max(bbox[idx].vy, bbox[idx + 4].vy);

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
    bmin[2].vy = __min(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[2].vy = __max(bbox[idx].vy, bbox[idx + 4].vy);

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
    bmin[3].vy = __min(bbox[idx].vy, bbox[idx + 4].vy);
    bmax[3].vy = __max(bbox[idx].vy, bbox[idx + 4].vy);

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
    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(res, out);
        out++;
        count++;
    }

    return count;
}

void s13a_crane_800D408C(CraneWork *work)
{
    SVECTOR pos;
    int     mult;

    mult = work->f354;
    work->f32C.vx = (work->f31C.vx * mult) / 255 + work->f2F4[0].vx + work->f324.vx + work->f334.vx;
    work->f32C.vy = (work->f31C.vy * mult) / 255 + work->f2F4[0].vy + work->f324.vy + work->f334.vy;
    work->f32C.vz = (work->f31C.vz * mult) / 255 + work->f2F4[0].vz + work->f324.vz + work->f334.vz;

    if (work->f364 == 0 && work->f32C.vy <= 1000)
    {
        work->f364 = 128;
    }

    if (work->f35C != 0 && work->f360 < 150)
    {
        work->f360++;

        pos.vx = work->f32C.vx - 2400;
        pos.vy = work->f32C.vy - 1500;
        pos.vz = work->f32C.vz;

        if (work->f37C == 0)
        {
            AN_Unknown_800CCA40(&pos);
        }
    }
}

int s13a_crane_800D420C(CraneWork *work)
{
    switch (work->f30C)
    {
    case 0:
        GM_SeSet_80032858(&work->f32C, 179);

        work->f314 = GV_RandU_80017090(64) + 128;
        work->f30C = 1;
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
    switch (work->f30C)
    {
    case 0:
        work->f314 = GV_RandU_80017090(32) + 32;
        work->f310 = 0;
        work->f30C = 1;
        /* fallthrough */

    case 1:
        if ((mts_get_tick_count_8008BBB0() - work->ticks) > 25)
        {
            work->ticks = mts_get_tick_count_8008BBB0();
            GM_SeSet_80032858(&work->f32C, 178);
        }

        if (work->f354 > 255)
        {
            work->f354 = 255;
            work->f318 = -1;
            return 1;
        }

        if (work->f354 < 0)
        {
            work->f354 = 0;
            work->f318 = 1;
            return 1;
        }

        if (work->f314-- > 0)
        {
            work->f354 += work->f318;
            return 0;
        }
        break;
    }

    return 1;
}

int s13a_crane_800D4390(CraneWork *work)
{
    switch (work->f30C)
    {
    case 0:
        work->f310 = 0;
        work->f314 = GV_RandU_80017090(128) + 64;
        work->f30C = 1;
        /* fallthrough */

    case 1:
        if ((mts_get_tick_count_8008BBB0() - work->ticks) > 25)
        {
            work->ticks = mts_get_tick_count_8008BBB0();
            GM_SeSet_80032858(&work->f32C, 178);
        }

        if (work->f354 > 255)
        {
            work->f354 = 255;
            work->f318 = -1;
            return 1;
        }

        if (work->f354 < 0)
        {
            work->f354 = 0;
            work->f318 = 1;
            return 1;
        }

        if (work->f314-- > 0)
        {
            work->f354 += work->f318 * 2;
            return 0;
        }
        break;
    }

    return 1;
}

int s13a_crane_800D4498(CraneWork *work)
{
    switch (work->f30C)
    {
    case 0:
        work->f310 = 32;
        work->f314 = 8;
        work->f30C = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f324.vz = GV_RandS_800170BC(16);
            return 0;
        }

        work->f324 = DG_ZeroVector_800AB39C;
        break;
    }

    return 1;
}

int s13a_crane_800D4548(CraneWork *work)
{
    switch (work->f30C)
    {
    case 0:
        if (work->f37C < 1 || work->f37C > 2)
        {
            GM_SeSet2_80032968(0, 63, 188);
        }

        work->f310 = 0;
        work->f314 = 16;
        work->f30C = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f33C.vz += 10;
            work->f334.vy -= 48;
            work->f334.vx += 12;

            work->f324.vx = GV_RandS_800170BC(16);
            work->f324.vy = GV_RandS_800170BC(16);
            work->f324.vz = GV_RandS_800170BC(16);
            return 0;
        }

        work->f314 = 16;
        work->f30C = 2;
        /* fallthrough */

    case 2:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 10;
            work->f33C.vy += 8;
            work->f334.vz += 22;

            work->f324.vx = GV_RandS_800170BC(16);
            work->f324.vy = GV_RandS_800170BC(16);
            work->f324.vz = GV_RandS_800170BC(16);
            return 0;
        }

        work->f314 = 32;
        work->f30C = 3;
        /* fallthrough */

    case 3:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 5;
            work->f33C.vy += 4;
            work->f334.vz += 11;

            work->f324.vx = GV_RandS_800170BC(16);
            work->f324.vy = GV_RandS_800170BC(16);
            work->f324.vz = GV_RandS_800170BC(16);
            return 0;
        }

        work->f324 = DG_ZeroVector_800AB39C;
        break;
    }

    return 1;
}

int s13a_crane_800D4724(CraneWork *work)
{
    unsigned short f314;

    switch (work->f30C)
    {
    case 0:
        if (work->f37C != 2)
        {
            GM_SeSet2_80032968(0, 63, 189);
        }

        work->f314 = 80;
        work->f30C = 1;
        /* fallthrough */

    case 1:
        if (work->f314-- > 0)
        {
            work->f33C.vx += 20;

            f314 = work->f314;
            work->f334.vy -= 4 * f314 & 0xffff;

            f314 = work->f314;
            work->f32C.vy -= 4 * f314 & 0xffff;
            return 0;
        }

        DG_InvisibleObjs(work->main.objs);
        DG_InvisibleObjs(work->arm.objs);

        work->f324 = DG_ZeroVector_800AB39C;
        break;
    }

    return 1;
}

int s13a_crane_800D4844(CraneWork *work)
{
    SVECTOR pos;

    switch (work->f30C)
    {
    case 0:
        work->f314 = 200;
        work->f30C = 2;
        /* fallthrough */

    case 2:
        if (work->f314-- > 0)
        {
            pos = work->f32C;
            pos.vy = -1000;

            if (work->f37C != 2)
            {
                AN_Unknown_800CCB84(&pos);
            }

            return 0;
        }

        work->f324 = DG_ZeroVector_800AB39C;
        break;
    }

    return 1;
}

void s13a_crane_800D4918(CraneWork *work)
{
    switch (work->f308)
    {
    case 3:
        if (s13a_crane_800D4498(work))
        {
            if (GV_RandU_80017090(16) < 8)
            {
                work->f308 = 1;
            }
            else
            {
                work->f308 = 2;
            }

            work->f30C = 0;
        }
        break;

    case 4:
        if (s13a_crane_800D4498(work))
        {
            work->f308 = 0;
            work->f30C = 0;
        }
        break;

    case 0:
        if (s13a_crane_800D420C(work))
        {
            work->f308 = 3;
            work->f30C = 0;
        }
        break;

    case 1:
        if (s13a_crane_800D428C(work))
        {
            work->f308 = 4;
            work->f30C = 0;
        }
        break;

    case 2:
        if (s13a_crane_800D4390(work))
        {
            work->f308 = 4;
            work->f30C = 0;
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
    switch (work->f308)
    {
    case 6:
        if (s13a_crane_800D4548(work))
        {
            work->f308 = 8;
            work->f30C = 0;
        }
        break;

    case 8:
        if (work->f35C >= 2 && s13a_crane_800D4724(work))
        {
            work->f308 = 9;
            work->f30C = 0;
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
    switch (work->f304)
    {
    case 0:
        s13a_crane_800D4918(work);
        break;

    case 1:
        s13a_crane_800D4A60(work);
        break;
    }
}

void s13a_crane_800D4BDC(CraneWork *work, int param)
{
    GCL_ARGS args;
    long     data[2];

    data[0] = param;
    data[1] = work->f354;

    args.argc = 2;
    args.argv = data;

    if (work->f374 != -1)
    {
        GCL_ExecProc_8001FF2C(work->f374, &args);
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

    GM_CurrentMap_800AB9B0 = work->map;

    hzd = Map_FromId_800314C0(work->map)->field_8_hzd;

    if (work->f37C == 2)
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
                GM_PadVibration_800ABA3C = 1;
                GM_PadVibration2_800ABA54 = 255;
            }
            break;

        case 1:
            if (work->f38C == 0)
            {
                work->f38C = -1;
                NewPadVibration_8005D58C(crane_800C35F4, 1);
                NewPadVibration_8005D58C(crane_800C35F8, 2);
            }
            break;
        }

        if (work->f388 == 0)
        {
            NewPadVibration_8005D58C(crane_800C3604, 1);
            NewPadVibration_8005D58C(crane_800C3608, 2);
        }
    }

    if (work->f378 < 10)
    {
        work->f378++;
    }

    if (work->f378 > 4 &&
        GM_PlayerPosition_800ABA10.vx < -7500 &&
        ((GM_PlayerPosition_800ABA10.vz < -5000 && GM_PlayerPosition_800ABA10.vz > -12500) || GM_PlayerPosition_800ABA10.vz > -2000) &&
        !(GM_PlayerStatus_800ABA50 & PLAYER_ON_WALL) &&
        work->f370 != -1)
    {
        if (GM_SnakeCurrentHealth == 0)
        {
            GM_GameOverTimer_800AB3D4 = 0;
            GM_PlayerControl_800AB9F4->field_55_skip_flag &= ~CTRL_SKIP_TRAP;
            GM_SnakeCurrentHealth = 1;
        }

        GCL_ExecProc_8001FF2C(work->f370, NULL);

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

        pos = &work->f32C;
        rot = &work->f33C;

        sp18.vx = 0;
        sp18.vy = 0;
        sp18.vz = 0;

        DG_SetPos2_8001BC8C(pos, rot);
        DG_MovePos_8001BD20(&sp18);

        GM_ActObject2_80034B88(&work->main);
        DG_GetLightMatrix_8001A3C4(pos, work->light_main);

        DG_SetPos2_8001BC8C(pos, &work->f344);
        DG_MovePos_8001BD20(&sp18);

        sp20.vx = -400;
        sp20.vy = 200;
        sp20.vz = 0;

        DG_MovePos_8001BD20(&sp20);

        GM_ActObject2_80034B88(&work->arm);
        DG_GetLightMatrix_8001A3C4(pos, work->light_arm);

        HZD_DequeueDynamicSegment2_8006FE44(hzd, &work->f2AC[1]);
        HZD_DequeueDynamicSegment2_8006FE44(hzd, &work->f2AC[3]);

        DG_SetPos2_8001BC8C(pos, rot);
        ReadRotMatrix(&world);

        bound[0].vx = -3000;
        bound[0].vy = -500;
        bound[0].vz = -250;

        bound[1].vx = 3000;
        bound[1].vy = 500;
        bound[1].vz = 250;

        world.t[1] += 500;

        s13a_crane_800D3994(work->f2AC, &world, &bound[0], &bound[1]);

        if ((work->f35C == 2 && work->f378 > 300) || work->f37C == 2)
        {
            HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[1], 0xD7);
            HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[3], 0xD7);
        }
        else
        {
            HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[1], 0x57);
            HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[3], 0x57);
        }

        target = work->target;

        if (work->f35C == 0)
        {
            if (target->field_6_flags & 0x4 || work->f37C != 0)
            {
                switch (work->f37C)
                {
                case 0:
                    s13a_crane_800D4BDC(work, 1);
                    break;

                case 1:
                    work->f354 = work->f380;
                    work->f32C.vz = work->f2F4[0].vz + (work->f31C.vz * work->f354) / 255;
                    break;

                case 2:
                    break;
                }

                target->field_6_flags &= ~0x4;

                if (target->field_3E == 2 || work->f37C != 0)
                {
                    work->f35C = 1;
                    work->f304 = 1;
                    work->f308 = 6;
                    work->f30C = 0;
                    return;
                }
            }

            if (target->field_6_flags & 0x8)
            {
                if (((work->f308 > 0 && work->f308 < 3 && work->f314 > 0 &&
                    ((work->f32C.vz - GM_PlayerPosition_800ABA10.vz) * work->f318) < 0) ||
                    ABS(work->f32C.vz - GM_PlayerPosition_800ABA10.vz) < 400) &&
                    work->f370 != -1)
                {
                    if (GM_SnakeCurrentHealth == 0)
                    {
                        GM_GameOverTimer_800AB3D4 = 0;
                        GM_PlayerControl_800AB9F4->field_55_skip_flag &= ~CTRL_SKIP_TRAP;
                        GM_SnakeCurrentHealth = 1;
                    }

                    GCL_ExecProc_8001FF2C(work->f370, NULL);
                    work->f370 = -1;

                    GM_SeSet2_80032968(0, 63, 51);

                    work->f388 = 48;
                    work->f390 = 0;
                    work->f38C = 10;
                }

                target->field_6_flags &= ~0x8;
            }

            sp10.vx = work->f32C.vx - 2200;
            sp10.vy = work->f32C.vy - 1000;
            sp10.vz = work->f32C.vz;
            GM_Target_SetVector_8002D500(target, &sp10);
        }

        else if (work->f35C == 1)
        {
            if ((target->field_6_flags & 0x4 && target->field_3E == 2) || work->f37C >= 2)
            {
                if (work->f37C < 2)
                {
                    s13a_crane_800D4BDC(work, 2);
                }

                work->f35C = 2;
                work->f378 = 111;

                target->field_6_flags &= ~0x4;
                GM_FreeTarget_8002D4B0(work->target);
                work->has_target = 0;
                return;
            }

            sp10.vx = work->f32C.vx - 1900;
            sp10.vy = work->f32C.vy - 1000;
            sp10.vz = work->f32C.vz;
            GM_Target_SetVector_8002D500(target, &sp10);
        }
        else if (work->has_target != 0 && work->f37C >= 2)
        {
            work->f378 = 111;
        }
    }
}

void s13a_crane_800D5338(CraneWork *work)
{
    TARGET *target;

    target = GM_AllocTarget_8002D400();
    work->target = target;
    GM_SetTarget_8002DC74(target, TARGET_SEEK | TARGET_PUSH | TARGET_POWER, NO_SIDE, &crane_800C3614);
    target->field_3C = 1;
    work->has_target = 1;
}

int s13a_crane_800D5394(CraneWork *work, int name)
{
    SVECTOR  sp10;
    SVECTOR  sp18;
    HZD_HDL *hzd;
    int      opt;

    hzd = Map_FromId_800314C0(work->map)->field_8_hzd;

    s13a_crane_800D5338(work);

    opt = GCL_GetOption_80020968('r');
    if (opt != NULL)
    {
        work->f2F0 = s13a_crane_800D4038((char *)opt, work->f2F4);
        work->f32C.vx = work->f2F4[0].vx;
        work->f32C.vy = work->f2F4[0].vy;
        work->f32C.vz = work->f2F4[0].vz;
    }

    work->f334 = DG_ZeroVector_800AB39C;
    work->f33C = DG_ZeroVector_800AB39C;

    opt = GCL_GetOption_80020968('d');
    if (opt != NULL)
    {
        work->f370 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f370 = -1;
    }

    opt = GCL_GetOption_80020968('p');
    if (opt != NULL)
    {
        work->f374 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f374 = -1;
    }

    opt = GCL_GetOption_80020968('c');
    if (opt != NULL)
    {
        work->f37C = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f37C = 0;
    }

    if (work->f37C == 1)
    {
        opt = GCL_GetOption_80020968('f');
        if (opt != NULL)
        {
            work->f380 = GCL_StrToInt_800209E8((char *)opt);
        }
        else
        {
            work->f380 = 0;
        }
    }

    work->f378 = 0;
    work->f304 = 0;
    work->f308 = 0;
    work->f30C = 0;
    work->f318 = 1;
    work->f354 = 0;

    sp10 = work->f2F4[0];
    sp18 = work->f2F4[1];

    work->f31C.vx = sp18.vx - sp10.vx;
    work->f31C.vy = sp18.vy - sp10.vy;
    work->f31C.vz = sp18.vz - sp10.vz;

    work->f324 = DG_ZeroVector_800AB39C;

    work->f35C = 0;
    work->f360 = 0;
    work->f364 = 0;

    if (work->f37C == 2)
    {
        HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[1], 0xD7);
        HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[3], 0xD7);
    }
    else
    {
        HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[1], 0x57);
        HZD_QueueDynamicSegment2_8006FDDC(hzd, &work->f2AC[3], 0x57);
    }

    work->f384 = 0;
    return 0;
}

int CraneGetResources_800D5620(CraneWork *work, int map)
{
    SVECTOR step;
    OBJECT *object;

    work->map = map;
    step = DG_ZeroVector_800AB39C;

    object = &work->main;
    GM_InitObject_80034A18(object, GV_StrCode_80016CCC("cr_main"), 0x2D, 0);
    GM_ConfigObjectJoint_80034CB4(object);
    GM_ConfigObjectLight_80034C44(object, work->light_main);
    GM_ConfigObjectStep_80034C54(object, &step);

    object = &work->arm;
    GM_InitObject_80034A18(object, GV_StrCode_80016CCC("cr_arm"), 0x2D, 0);
    GM_ConfigObjectJoint_80034CB4(object);
    GM_ConfigObjectLight_80034C44(object, work->light_arm);
    GM_ConfigObjectStep_80034C54(object, &step);

    work->ticks = mts_get_tick_count_8008BBB0();
    work->f388 = -1;
    work->f38C = -1;
    return 0;
}

void CraneDie_800D5724(CraneWork *work)
{
    HZD_HDL *hzd;

    hzd = Map_FromId_800314C0(work->map)->field_8_hzd;
    HZD_DequeueDynamicSegment2_8006FE44(hzd, &work->f2AC[1]);
    HZD_DequeueDynamicSegment2_8006FE44(hzd, &work->f2AC[3]);

    GM_FreeObject_80034BF8(&work->main);
    GM_FreeObject_80034BF8(&work->arm);

    if (work->has_target != 0)
    {
        GM_FreeTarget_8002D4B0(work->target);
    }
}

GV_ACT * NewCrane_800D57A0(int name, int where)
{
    CraneWork *work;

    work = (CraneWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(CraneWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)CraneAct_800D4C28, (TActorFunction)CraneDie_800D5724, "crane.c");

        if (CraneGetResources_800D5620(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        s13a_crane_800D5394(work, name);
    }

    return &work->actor;
}
