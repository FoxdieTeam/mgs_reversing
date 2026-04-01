#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "kojo/demo.h"
#include "hind.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "mts/mts.h"
#include "okajima/spark.h"
#include "takabe/cinema.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern DG_CHANL         DG_Chanls[3];
extern GM_CAMERA        GM_Camera;
extern int              MENU_RadarScale;

SVECTOR s11g_dword_800C3598 = {5000, 3000, 5000, 0};
SVECTOR s11g_dword_800C35A0 = {100, 0, 0, 0};

static void GetInts(u_char *param, int *out)
{
    u_char *result;

    while ((result = GCL_GetParamResult()))
    {
        *out++ = GCL_StrToInt(result);
    }
}

void *NewHind(int name, int where)
{
    SVECTOR   svec;
    VECTOR    vec1, vec2, vec3;
    HindWork *work;
    HZD_SEG  *walls;
    HZD_FLR  *floors;
    int       i;
    u_char   *param;

    work = GV_NewActor(EXEC_LEVEL, sizeof(HindWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, HindAct_800D3404, HindDie, "hind.c");

    if (GM_InitControl(&work->control, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    work->name = name;

    work->body_light[0].t[0] = 16;
    work->body_light[0].t[1] = 16;
    work->body_light[0].t[2] = 16;

    if (GCL_GetOption('a'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->body_light[0].t[0] = GCL_StrToInt(param);
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->body_light[0].t[1] = GCL_StrToInt(param);
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->body_light[0].t[2] = GCL_StrToInt(param);
        }
    }

    work->field_41C = 233;
    work->field_420 = 205;

    if (GCL_GetOption('r'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_41C = GCL_StrToInt(param);
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->field_420 = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('e'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_424 = GCL_StrToInt(param) * 1000000 / 108000 * 16;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_428 = GCL_StrToInt(param) * 16 / 30;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_42C = GCL_StrToInt(param) * 4096 / 360;
        }
    }

    work->field_444 = 1;

    if (GCL_GetOption('d'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_430 = work->field_434 = GCL_StrToInt(param);
        }

        work->field_650 = 1024 / work->field_430 + 1;

        param = GCL_GetParamResult();
        if (param)
        {
            work->field_438 = (GCL_StrToInt(param) + 1);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_43C = GCL_StrToInt(param) * 1000000 / 108000 * 16;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_440 = GCL_StrToInt(param) * 16 / 30;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_444 = GCL_StrToInt(param);
        }

        if (work->field_444 <= 0)
        {
            work->field_444 = 1;
        }
    }

    if (GCL_GetOption('g'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_448 = GCL_StrToInt(param) + 1;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_44C = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_450 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_454 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_458 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_45C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_460 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_464 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_468 = GCL_StrToInt(param) * 1000000 / 108000;
        }
    }

    if (GCL_GetOption('m'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_46C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_470 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_474 = GCL_StrToInt(param) + 1;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_478 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_47C = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_480 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_484 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_488 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_48C = GCL_StrToInt(param) * 1000000 / 108000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            if (GCL_StrToInt(param) == 1)
            {
                work->field_490 = &GM_PlayerPosition;
            }
        }
    }

    if (GCL_GetOption('p'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4BC.vx = GCL_StrToInt(param) * 1000;
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4BC.vy = GCL_StrToInt(param) * 1000;
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4BC.vz = (GCL_StrToInt(param) * 1000);
        }

        work->field_5FC = work->field_4BC;
        work->field_60C = work->field_4BC;

        param = GCL_GetParamResult();
        if (param)
        {
            work->control.turn.vx = GCL_StrToInt(param) * 4096 / 360;
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->control.turn.vy = GCL_StrToInt(param) * 4096 / 360;
        }

        param = GCL_GetParamResult();
        if (param)
        {
            work->control.turn.vz = GCL_StrToInt(param) * 4096 / 360;
        }

        param = GCL_GetParamResult();
        if (param)
        {
            svec.vx = 0;
            svec.vy = 0;
            svec.vz = 0;
            DG_SetPos2(&svec, &work->control.turn);
            svec.vz = GCL_StrToInt(param) * 1000000 / 108000 * 16;
            DG_PutVector(&svec, &svec, 1);
            work->field_4DC = svec.vx;
            work->field_4E0 = svec.vy;
            work->field_4E4 = svec.vz;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4A0 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_494 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_498 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_49C = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4AA = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4A4 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4A6 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4A8 = GCL_StrToInt(param) * 4096 / 360;
        }
    }

    if (GCL_GetOption('b'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4AC = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('w'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_4B0 = (GCL_StrToInt(param) * 1000);
        }
    }

    work->end_proc = -1;

    if (GCL_GetOption('z'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->end_proc = GCL_StrToInt(param);
        }
    }

    work->control.step_size = -2;
    work->control.interp = 0;

    GM_ConfigControlAttribute(&work->control, 4);

    GM_InitObject(&work->body, GV_StrCode("hind"), 0x12D, 0);
    GM_ConfigObjectJoint(&work->body);
    GM_ConfigObjectLight(&work->body, work->body_light);

    GM_InitObject(&work->missile1, GV_StrCode("hindmsil"), 0x12D, 0);
    GM_ConfigObjectLight(&work->missile1, work->missile1_light);
    GM_ConfigObjectJoint(&work->missile1);

    GM_InitObject(&work->missile2, GV_StrCode("hindmsil"), 0x12D, 0);
    GM_ConfigObjectLight(&work->missile2, work->missile2_light);
    GM_ConfigObjectJoint(&work->missile2);

    work->field_414 = 1;

    work->control.rot.vx = work->control.turn.vx;
    work->control.rot.vy = work->control.turn.vy;
    work->control.rot.vz = work->control.turn.vz;

    work->field_504 = work->field_448 / 2;
    work->field_508 = (work->field_474 / 2);

    work->target1 = GM_AllocTarget();
    work->target2 = GM_AllocTarget();
    work->target3 = GM_AllocTarget();

    work->target1->damaged &= ~TARGET_POWER;
    work->target2->damaged &= ~TARGET_POWER;
    work->target3->damaged &= ~TARGET_POWER;

    svec.vx = work->body.objs->objs[0].model->max.vx / 2;
    svec.vy = -work->body.objs->objs[0].model->min.vy / 4;
    svec.vz = work->body.objs->objs[0].model->max.vz / 2;

    if (work->field_4AC != 2)
    {
        switch (GM_DifficultyFlag)
        {
        default:
        case -1:
        case 0:
            GM_SetTarget(work->target1, 20, 2, &svec);
            GM_SetTarget(work->target2, 20, 2, &svec);
            GM_SetTarget(work->target3, 20, 2, &svec);
            break;
        case 1:
        case 2:
            svec.vx = svec.vx / 2;
            svec.vy = svec.vy / 2;
            svec.vz = svec.vz / 2;
            GM_SetTarget(work->target1, 20, 2, &svec);
            GM_SetTarget(work->target2, 20, 2, &svec);
            GM_SetTarget(work->target3, 20, 2, &svec);
            break;
        case 3:
            svec.vx = svec.vx / 2;
            svec.vy = svec.vy / 2;
            svec.vz = svec.vz / 2;
            GM_SetTarget(work->target1, 20, 2, &svec);
            GM_SetTarget(work->target2, 20, 2, &DG_ZeroVector);
            GM_SetTarget(work->target3, 20, 2, &DG_ZeroVector);

            work->target2->class &= ~0x14;
            work->target2->class |= 1;
            work->target3->class &= ~0x14;
            work->target3->class |= 1;
            break;
        }
    }
    else
    {
        GM_SetTarget(work->target1, 0, 2, &svec);
        GM_SetTarget(work->target2, 0, 2, &svec);
        GM_SetTarget(work->target3, 0, 2, &svec);

        work->target1->damaged |= TARGET_POWER;
        work->target2->damaged |= TARGET_POWER;
        work->target3->damaged |= TARGET_POWER;
    }

    work->field_654 = 1024;
    work->field_7F4 = 1024;

    work->field_4B4 = work->field_41C * 4096 / 1800;
    work->field_4B8 = work->field_420 * 4096 / 1800;

    work->field_514 = MAX(work->body.objs->def->max.vx - work->body.objs->def->min.vx,
                          work->body.objs->def->max.vy - work->body.objs->def->min.vy);
    work->field_514 = MAX(work->field_514, work->body.objs->def->max.vz - work->body.objs->def->min.vz);

    work->field_514 = 33200 - work->field_514 / 3;

    vec1.vx = -work->field_514;
    vec1.vy = 0;
    vec1.vz = 0;
    vec2.vx = -work->field_514;
    vec2.vy = 1;
    vec2.vz = 0;
    vec3.vx = -work->field_514;
    vec3.vy = 0;
    vec3.vz = 1;
    sub_8007F0D0(&work->field_518, &vec1, &vec2, &vec3);

    vec1.vx = work->field_514;
    vec1.vy = 0;
    vec1.vz = 0;
    vec2.vx = work->field_514;
    vec2.vy = 1;
    vec2.vz = 0;
    vec3.vx = work->field_514;
    vec3.vy = 0;
    vec3.vz = 1;
    sub_8007F0D0(&work->field_528, &vec1, &vec2, &vec3);

    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = -work->field_514;
    vec2.vx = 0;
    vec2.vy = 1;
    vec2.vz = -work->field_514;
    vec3.vx = 1;
    vec3.vy = 0;
    vec3.vz = -work->field_514;
    sub_8007F0D0(&work->field_538, &vec1, &vec2, &vec3);

    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = work->field_514;
    vec2.vx = 0;
    vec2.vy = 1;
    vec2.vz = work->field_514;
    vec3.vx = 1;
    vec3.vy = 0;
    vec3.vz = work->field_514;
    sub_8007F0D0(&work->field_548, &vec1, &vec2, &vec3);

    work->field_558 = 26200;
    work->field_55C = 26200;
    work->field_560 = 26200;
    work->field_568 = -26200;
    work->field_56C = -26200;
    work->field_570 = -26200;

    walls = work->control.map->hzd->group->walls;
    for (i = 0; i < work->control.map->hzd->group->n_walls; i++, walls++)
    {
        work->field_558 = MIN(work->field_558, walls->p1.x);
        work->field_55C = MIN(work->field_55C, walls->p1.y);
        work->field_560 = MIN(work->field_560, walls->p1.z);

        work->field_558 = MIN(work->field_558, walls->p2.x);
        work->field_55C = MIN(work->field_55C, walls->p2.y);
        work->field_560 = MIN(work->field_560, walls->p2.z);

        work->field_568 = MAX(work->field_568, walls->p1.x);
        work->field_56C = MAX(work->field_56C, walls->p1.y);
        work->field_570 = MAX(work->field_570, walls->p1.z + walls->p1.h);

        work->field_568 = MAX(work->field_568, walls->p2.x);
        work->field_56C = MAX(work->field_56C, walls->p2.y);
        work->field_570 = MAX(work->field_570, walls->p2.z + walls->p2.h);
    }

    floors = work->control.map->hzd->group->floors;
    for (i = 0; i < work->control.map->hzd->group->n_floors; i++, floors++)
    {
        work->field_558 = MIN(work->field_558, floors->b1.x);
        work->field_55C = MIN(work->field_55C, floors->b1.y);
        work->field_560 = MIN(work->field_560, floors->b1.z);

        work->field_558 = MIN(work->field_558, floors->b2.x);
        work->field_55C = MIN(work->field_55C, floors->b2.y);
        work->field_560 = MIN(work->field_560, floors->b2.z);

        work->field_568 = MAX(work->field_568, floors->b1.x);
        work->field_56C = MAX(work->field_56C, floors->b1.y);
        work->field_570 = MAX(work->field_570, floors->b1.z);

        work->field_568 = MAX(work->field_568, floors->b2.x);
        work->field_56C = MAX(work->field_56C, floors->b2.y);
        work->field_570 = MAX(work->field_570, floors->b2.z);
    }

    for (i = 0; i < 11; i++)
    {
        work->body.objs->objs[i].world = DG_ZeroMatrix;
    }

    param = GCL_GetOption('v');
    if (param)
    {
        GetInts(param, work->vox_ids);
    }

    param = GCL_GetOption('c');
    if (param)
    {
        work->field_8EC = GCL_StrToInt(param);
    }
    else
    {
        work->field_8EC = -1;
    }

    param = GCL_GetOption('s');
    if (param)
    {
        work->field_8F0 = GCL_StrToInt(param);
    }
    else
    {
        work->field_8F0 = -1;
    }

    work->field_5F4 = 1536;
    work->field_8C0 = 0;
    work->field_8C4 = 0;
    work->field_5C4 = 0;
    work->field_5C8 = 0;
    work->field_5E0 = 0;
    work->field_5E4 = 0;
    work->field_5E8 = 0;
    work->field_5EC = 0;
    work->field_5F0 = 0;
    work->field_5F8 = 0;
    work->field_5D4 = 0;
    work->field_5D8 = 0;
    work->field_5DC = 0;
    work->field_7F8 = 0;
    work->field_658 = 0;
    work->field_644 = DG_ZeroVector;
    work->field_8FC = 5400;
    work->field_50C = 0;
    work->field_674 = 0;
    work->field_678 = 0;
    work->field_8E0 = 0;
    work->field_8CC = 0;
    work->field_8D0 = 0;
    work->field_8D4 = 0;
    work->field_900 = 0;

    if (work->field_4AC == 2)
    {
        work->field_930 = 1;
    }
    else
    {
        work->field_930 = 0;
    }

    work->last_time = 0;
    work->last_time2 = 0;
    work->field_938 = 0;
    work->field_8E4 = NULL;
    work->field_93C = 0;
    work->field_940 = -1;
    work->field_94C = 0;
    work->field_950 = 0;
    work->field_954 = GV_RandU(8) + 8;
    work->field_958 = 0;
    work->field_95C = 0;
    work->field_960 = 0;

    GM_InitObject(&work->missile3, GV_StrCode("hindmsil"), 0x25D, 0);
    GM_ConfigObjectJoint(&work->missile3);
    GM_ConfigObjectLight(&work->missile3, work->missile3_light);
    GM_SetTarget(&work->field_57C, 4, 2, &s11g_dword_800C3598);

    switch (GM_DifficultyFlag)
    {
    default:
    case -1:
    case 0:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x100, 0, &s11g_dword_800C35A0);
        break;
    case 1:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x200, 0, &s11g_dword_800C35A0);
        break;
    case 2:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x400, 0, &s11g_dword_800C35A0);
        break;
    case 3:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x800, 0, &s11g_dword_800C35A0);
        break;
    }

    GM_VoxStream(work->vox_ids[0], 0x40000000);

    for (i = 0; i < 32; i++)
    {
        work->field_970[i] = DG_ZeroVector;
    }

    work->field_A74 = 0;

    return (void *)work;
}

void Hind_LookAt_800D2C1C(SVECTOR *eye, SVECTOR *center)
{
    DG_LookAt(&DG_Chanls[1], eye, center, 320);
    GM_Camera.field_2A = 0;
    gUnkCameraStruct2_800B7868.eye = *eye;
    gUnkCameraStruct2_800B7868.center = *center;
}

TILE SECTION(".bss") s11g_dword_800DD34C[2];

void s11g_hind_800D2CB4(HindWork *work)
{
    u_long *ot;
    TILE   *tile;
    int     scale;
    int     px, pz;
    int     x, z;
    int     clip;

    if (GM_GameStatus & (STATE_RADAR_OFF | STATE_CHAFF))
    {
        return;
    }

    if (GM_OptionFlag & OPTION_RADAR_OFF)
    {
        return;
    }

    if (GM_CurrentItemId == IT_Camera)
    {
        return;
    }

    ot = DG_Chanl(1)->ot[GV_Clock];
    tile = &s11g_dword_800DD34C[GV_Clock];

    SetTile(tile);

    scale = MENU_RadarScale;
    px = GM_PlayerPosition.vx;
    pz = GM_PlayerPosition.vz;
    x = ((work->field_4BC.vx - px) * scale) / 4096;
    z = ((work->field_4BC.vz - pz) * scale) / 4096;

    clip = 0;

    if (x < -34)
    {
        z = -(z * 34) / x;
        x = -34;
        clip = 1;
    }

    if (x > 32)
    {
        z = (z * 32) / x;
        x = 32;
        clip = 1;
    }

    if (z < -26)
    {
        x = -(x * 26) / z;
        z = -26;
        clip = 1;
    }

    if (z > 24)
    {
        x = (x * 24) / z;
        z = 24;
        clip = 1;
    }

    setXY0(tile, x + 270, z + 42);
    setWH(tile, 2, 2);

    if (clip == 0)
    {
        setRGB0(tile, 255, 0, 0);
    }
    else
    {
        setRGB0(tile, 255, 0, 255);
    }

    addPrim(ot, tile);
}

void s11g_hind_800D2F60(HindWork *work)
{
    DG_VECTOR sp10[2];
    VECTOR    sp30;
    VECTOR    sp38;
    VECTOR   *vec;
    int       len;
    int       len2;

    sp30.vx = GM_PlayerPosition.vx;
    sp30.vy = GM_PlayerPosition.vy;
    sp30.vz = GM_PlayerPosition.vz;
    sp38 = work->field_760;
    sub_8007F06C(sp10, &sp30, &sp38);

    vec = NULL;

    if (sp38.vx < -work->field_514)
    {
        vec = &work->field_518;
        sub_8007F1DC(&sp38, sp10, vec);
    }
    else if (sp38.vx > work->field_514)
    {
        vec = &work->field_528;
        sub_8007F1DC(&sp38, sp10, vec);
    }

    if (sp38.vz < -work->field_514)
    {
        vec = &work->field_538;
        sub_8007F1DC(&sp38, sp10, vec);
    }
    else if (sp38.vz > work->field_514)
    {
        vec = &work->field_548;
        sub_8007F1DC(&sp38, sp10, vec);
    }

    if (vec == NULL)
    {
        sp30.vx = 4096;
        sp30.vy = 4096;
        sp30.vz = 4096;
        ScaleMatrix(&work->missile3.objs->world, &sp30);
        work->field_670 = 4096;
        work->field_7D8.vx = work->field_760.vx;
        work->field_7D8.vy = work->field_760.vy;
        work->field_7D8.vz = work->field_760.vz;
        return;
    }

    sp30.vx = (work->field_760.vx - gUnkCameraStruct2_800B7868.eye.vx) >> 2;
    sp30.vy = (work->field_760.vy - gUnkCameraStruct2_800B7868.eye.vy) >> 2;
    sp30.vz = (work->field_760.vz - gUnkCameraStruct2_800B7868.eye.vz) >> 2;

    len = SquareRoot0(sp30.vx * sp30.vx + sp30.vy * sp30.vy + sp30.vz * sp30.vz) * 4;

    sub_8007F1DC(&sp38, sp10, vec);

    work->field_7D8.vx = sp38.vx;
    work->field_7D8.vy = sp38.vy;
    work->field_7D8.vz = sp38.vz;

    sp30.vx = sp38.vx - gUnkCameraStruct2_800B7868.eye.vx;
    sp30.vy = sp38.vy - gUnkCameraStruct2_800B7868.eye.vy;
    sp30.vz = sp38.vz - gUnkCameraStruct2_800B7868.eye.vz;

    len2 = SquareRoot0(sp30.vx * sp30.vx + sp30.vy * sp30.vy + sp30.vz * sp30.vz);
    if (len == 0)
    {
        len = len2 * 4096;
    }
    else
    {
        len = (len2 * 4096) / len;
    }

    sp30.vx = len;
    sp30.vy = len;
    sp30.vz = len;
    ScaleMatrix(&work->missile3.objs->world, &sp30);
    work->field_670 = len;
}

void s11g_hind_800D3214(HindWork *work)
{
    int field_654;
    int var_a2;
    int var_s1;

    if (GM_GameStatus & STATE_LIFEBAR_OFF)
    {
        return;
    }

    field_654 = work->field_654;
    if (field_654 < 0)
    {
        field_654 = 0;
    }

    var_s1 = work->field_7F4;
    var_a2 = var_s1;
    if (var_s1 < field_654)
    {
        var_a2 = field_654;
        var_s1 = field_654;
    }
    MENU_DrawBar(16, 28, var_a2, field_654, &work->lifebar);
    if (field_654 < var_s1)
    {
        work->field_7F4 -= 8;
        if (work->field_7F4 < field_654)
        {
            work->field_7F4 = field_654;
        }
    }
}

char SECTION(".bss") hind_lifebar_name[8];

void s11g_hind_800D32CC(HindWork *work)
{
    MENU_BAR_CONF *conf;

    strcpy(hind_lifebar_name, "HIND");

    conf = &work->lifebar;
    conf->name = hind_lifebar_name;
    conf->left[0] = 16;
    conf->left[1] = 111;
    conf->left[2] = 159;
    conf->right[0] = 31;
    conf->right[1] = 223;
    conf->right[2] = 127;
}

// Identical to d03a_red_alrt_800C437C
int HindReceiveMessage_800D3334(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void Hind_800D33CC(HindWork *work, int arg)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    argv[0] = arg;
    args.argv = argv;

    GCL_ExecProc(work->field_8F0, &args);
}

const char s11g_aBulletoff_800DD130[] = "bullet_off";
const char s11g_aBulleton_800DD13C[] = "bullet_on";
const char s11g_aDestroy_800DD148[] = "destroy";
const int s11g_dword_800DD150 = 0x800D3818;
const int s11g_dword_800DD154 = 0x800D36F8;
const int s11g_dword_800DD158 = 0x800D3704;
const int s11g_dword_800DD15C = 0x800D3734;
const int s11g_dword_800DD160 = 0x800D37E8;

int SECTION(".bss") s11g_dword_800DD374;
int SECTION(".bss") s11g_dword_800DD378;

#pragma INCLUDE_ASM("asm/overlays/s11g/HindAct_800D3404.s")

void HindDie(HindWork *work)
{
    GM_GameStatus &= ~STATE_PADDEMO;
    GM_GameStatus &= ~(STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF);

    if (work->end_proc >= 0 && work->field_94C != 1 && work->field_A74 == 1)
    {
        GCL_ForceExecProc(work->end_proc, NULL);
    }

    if (work->field_8E8)
    {
        GV_DestroyOtherActor(work->field_8E8);
        work->field_8E8 = NULL;
    }

    if (work->field_8E4)
    {
        GV_DestroyOtherActor(work->field_8E4);
        work->field_8E4 = NULL;
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->missile1);
    GM_FreeObject(&work->missile2);
    GM_FreeObject(&work->missile3);
    GM_FreeTarget(work->target1);
    GM_FreeTarget(work->target2);
    GM_FreeTarget(work->target3);
}

void s11g_hind_800D46B8(SVECTOR *pos, int se_id)
{
    GM_SeSetMode(pos, se_id, GM_SEMODE_BOMB);
}

void s11g_hind_800D46D8(HindWork *work, int index)
{
    if (work->field_94C != 1 && work->field_930 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->vox_ids[index], 0);
        }
    }
}

void s11g_hind_800D4744(HindWork *work)
{
    if (work->field_94C != 1 && work->field_930 == 0)
    {
        work->field_5F0 = 90;
        NewCinemaScreen(90, 0);

        work->field_A70 = work->body.objs->def->model[2].vertices;
        work->body.objs->def->model[2].vertices = work->field_970;

        work->last_item = GM_CurrentItemId;
        work->last_weapon = GM_CurrentWeaponId;

        if (GM_CurrentItemId == IT_Scope  ||
            GM_CurrentItemId == IT_Camera ||
            GM_CurrentItemId == IT_NVG    ||
            GM_CurrentItemId == IT_ThermG)
        {
            GM_CurrentItemId = IT_None;
        }

        if (GM_CurrentWeaponId == WP_Rifle ||
            GM_CurrentWeaponId == WP_Stinger)
        {
            GM_CurrentWeaponId = WP_None;
        }

        switch (work->field_8C4++ % 4)
        {
        case 0:
            s11g_hind_800D46D8(work, 0);
            break;
        case 1:
            s11g_hind_800D46D8(work, 1);
            break;
        case 2:
            s11g_hind_800D46D8(work, 2);
            break;
        case 3:
            s11g_hind_800D46D8(work, 3);
            break;
        }

        if (work->control.mov.vx <= 0)
        {
            work->field_5D8 = 1;
        }
        else
        {
            work->field_5D8 = -1;
        }
    }
}

void s11g_hind_800D48E8(HindWork *work)
{
    work->field_62C.vx = GM_PlayerPosition.vx + GV_RandS(2) * 500;
    work->field_62C.vy = GM_PlayerPosition.vy + GV_RandS(2) * 500;
    work->field_62C.vz = GM_PlayerPosition.vz + GV_RandS(2) * 500;
}

int s11g_hind_800D4990(HindWork *work)
{
    SVECTOR midpoint;

    midpoint.vx = (GM_PlayerPosition.vx + work->field_63C.vx) / 2;
    midpoint.vy = (GM_PlayerPosition.vy + work->field_63C.vy) / 2;
    midpoint.vz = (GM_PlayerPosition.vz + work->field_63C.vz) / 2;

    return HZD_LineCheck(work->control.map->hzd, &GM_PlayerPosition, &midpoint, ( HZD_CHECK_SEG | HZD_CHECK_FLR ), HZD_SEG_NO_PLAYER) != 0;
}

void s11g_hind_800D4A24(long *vec, long *pos, long *old, int len)
{
    int interp;

    interp = (*vec * (len - 1) + *pos) / len;
    *old = *vec - interp;
    *vec = interp;
}

void s11g_hind_800D4A80(VECTOR *vec, VECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void s11g_hind_800D4B68(SVECTOR *vec, SVECTOR *pos, int len)
{
    SVECTOR diff;
    int     interp;

    interp = len - 1;

    vec->vx &= 0xFFF;
    vec->vy &= 0xFFF;
    vec->vz &= 0xFFF;

    pos->vx &= 0xFFF;
    pos->vy &= 0xFFF;
    pos->vz &= 0xFFF;

    diff.vx = pos->vx - vec->vx;
    diff.vy = pos->vy - vec->vy;
    diff.vz = pos->vz - vec->vz;

    if (diff.vx >= 2048)
    {
        vec->vx += 4096;
    }

    if (diff.vy >= 2048)
    {
        vec->vy += 4096;
    }

    if (diff.vz >= 2048)
    {
        vec->vz += 4096;
    }

    if (diff.vx <= -2048)
    {
        pos->vx += 4096;
    }

    if (diff.vy <= -2048)
    {
        pos->vy += 4096;
    }

    if (diff.vz <= -2048)
    {
        pos->vz += 4096;
    }

    vec->vx = (vec->vx * interp + pos->vx) / len;
    vec->vy = (vec->vy * interp + pos->vy) / len;
    vec->vz = (vec->vz * interp + pos->vz) / len;
}

void s11g_hind_800D4DD0(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        /* fallthrough */
    case 1:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_5C8 = 2;
            work->field_5E4 = GV_RandU(16) + 60;
            work->field_60C = work->field_4BC;
            work->field_60C.vy = 20000;
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 64);
        }
        else
        {
            work->field_8CC = 1;
            work->field_5C8 = 3;
            work->field_5E4 = GV_RandU(32) + 90;
            work->field_5E8 = GV_RandU(2);

            if (work->field_60C.vx < 0)
            {
                work->field_60C.vx = GV_RandU(16384) + 55000;
                work->field_60C.vy = GV_RandU(4096) + 20000;
                work->field_60C.vz = 8000 - GV_RandU(4096);
            }
            else
            {
                work->field_60C.vx = -(GV_RandU(16384) + 55000);
                work->field_60C.vy = 20000;
                work->field_60C.vz = 12000 - GV_RandU(4096);
            }

            work->field_61C = work->field_60C;
        }
        break;
    case 3:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            if (work->field_5E8 < 0)
            {
                work->field_5C8 = 4;
                work->field_5E4 = GV_RandU(128) + 128;

                if (work->field_60C.vx < 0)
                {
                    work->field_60C.vx = -20000;
                }

                if (work->field_60C.vx > 0)
                {
                    work->field_60C.vx = 20000;
                }

                work->field_60C.vy = 7000;
                work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(4096);
                if (work->field_60C.vz > 12000)
                {
                    work->field_60C.vz = 12000 - GV_RandS(4096);
                }
            }
            else
            {
                work->field_5C8 = 3;
                work->field_5E4 = GV_RandU(16) + 10;
                work->field_60C.vx = work->field_61C.vx + GV_RandS(8192);
                work->field_60C.vy = work->field_61C.vy + GV_RandS(8192);
                work->field_60C.vz = work->field_61C.vz + GV_RandS(8192);
            }

            work->field_5E8--;
        }
        break;
    case 4:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

void s11g_hind_800D50F0(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        /* fallthrough */
    case 1:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_5C8 = 2;
            work->field_5E4 = GV_RandU(16) + 60;
            work->field_60C = work->field_4BC;
            work->field_60C.vy = 20000;
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 64);
        }
        else
        {
            work->field_5C8 = 3;
            work->field_5E4 = GV_RandU(32) + 150;
            work->field_5E8 = (GV_RandU(4) * 2) + 8;
            work->field_60C.vx = GV_RandS(4096) + 2000;
            work->field_60C.vy = GV_RandU(1024) + 9000;
            work->field_60C.vz = GV_RandS(2048) - 15000;
        }
        break;
    case 3:
        if ((work->field_5D4 == 1) && (GM_PlayerStatus & PLAYER_INVINCIBLE))
        {
            work->field_5D4 = 0;
            work->field_5C4 = 0;
            work->field_5C8 = 0;
            s11g_hind_800D4744(work);
        }
        else if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            switch (work->field_8C0++ % 4)
            {
            case 0:
                s11g_hind_800D46D8(work, 4);
                break;
            case 1:
                s11g_hind_800D46D8(work, 5);
                break;
            case 2:
                s11g_hind_800D46D8(work, 6);
                break;
            case 3:
                s11g_hind_800D46D8(work, 7);
                break;
            }

            if (GV_RandU(4) != 0)
            {
                if (!(work->field_5E8 & 1) && (work->field_5EC < 0))
                {
                    s11g_hind_800D48E8(work);
                    work->field_5D4 = 1;
                }
                else
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(8) + 8;
                }

                work->field_5C8 = 3;
                work->field_5E4 = GV_RandU(32) + 150;
                work->field_60C.vx = GV_RandS(4096) + 2000;
                work->field_60C.vy = GV_RandU(4096) + 12000;
                work->field_60C.vz = GV_RandS(2048) - 2000;
            }
            else
            {
                work->field_5D4 = 0;
                work->field_954 = GV_RandU(8) + 8;
                work->field_5C4 = 0;
                work->field_5C8 = 0;
            }

            work->field_5E8--;
        }
        break;
    }
}

void s11g_hind_800D5420(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        work->field_61C = work->field_4BC;
        work->field_5E8 = GV_RandU(4) + 4;
        s11g_hind_800D48E8(work);
        /* fallthrough */
    case 1:
        if ((work->field_5D4 == 1) && (GM_PlayerStatus & PLAYER_DAMAGED) && (work->field_5EC < 0))
        {
            work->field_5D4 = 0;
            work->field_954 = GV_RandU(2) + 4;
            work->field_5E4 = -1;
            work->field_5E8 = -1;
            work->field_5EC = 60;
            s11g_hind_800D4744(work);
        }

        if (work->field_5E4 <= 0)
        {
            work->field_61C.vy += 1500;
            if (work->field_61C.vy > 8000)
            {
                work->field_61C.vy = GV_RandS(4096) + 5000;
            }

            if ((work->field_5E8 < 0) || s11g_hind_800D4990(work))
            {
                if (GV_RandU(2) == 0)
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(4) + 4;

                    if (GV_RandU(8) == 0)
                    {
                        switch (GV_RandU(8))
                        {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            s11g_hind_800D46D8(work, 11);
                            break;
                        case 6:
                            s11g_hind_800D46D8(work, 12);
                            break;
                        case 7:
                            s11g_hind_800D46D8(work, 16);
                            break;
                        }
                    }

                    if (GV_RandU(8))
                    {
                        work->field_5C4 = 0;
                        work->field_5C8 = 0;
                    }
                    else
                    {
                        work->field_5C4 = 1;
                        work->field_5C8 = 0;
                    }
                }
                else
                {
                    switch (GV_RandU(4))
                    {
                    case 0:
                        s11g_hind_800D46D8(work, 10);
                        break;
                    case 1:
                        s11g_hind_800D46D8(work, 9);
                        break;
                    }

                    work->field_5C8 = 2;
                    work->field_5E4 = GV_RandU(32) + 60;
                    work->field_60C.vx = work->field_61C.vx;
                    work->field_60C.vy = work->field_61C.vy + GV_RandU(4096);
                    work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
                    if (work->field_60C.vz > 12000)
                    {
                        work->field_60C.vz = 12000 - GV_RandS(4096);
                    }
                }
            }
            else
            {
                if (!(work->field_5E8 & 0x1) && (work->field_5EC < 0))
                {
                    s11g_hind_800D48E8(work);
                    work->field_5D4 = 1;
                }
                else
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(4) + 4;
                }

                work->field_5C8 = 1;
                work->field_5E4 = GV_RandU(32) + 60;
                work->field_60C.vx = work->field_61C.vx;
                work->field_60C.vy = work->field_61C.vy + GV_RandS(2048);
                work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
                if (work->field_60C.vz > 12000)
                {
                    work->field_60C.vz = 12000 - GV_RandS(4096);
                }
            }

            work->field_5E8--;
        }
        else
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
            return;
        }
        else
        {
            work->field_5C8 = 1;
            work->field_5E4 = GV_RandU(32) + 60;
            work->field_5E8 = GV_RandU(2) + 2;
            work->field_60C.vx = work->field_61C.vx;
            work->field_60C.vy = work->field_61C.vy - GV_RandU(8192);
            work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
            if (work->field_60C.vz > 12000)
            {
                work->field_60C.vz = 12000 - GV_RandS(4096);
            }
        }
        break;
    }
}

void s11g_hind_800D5820(HindWork *work)
{
    SVECTOR rot;
    SVECTOR sp18;
    SVECTOR turn;
    SVECTOR pos;
    int     dx, dz;
    long    sp30;
    long    sp34;
    int     time;

    if (work->field_938 == 1)
    {
        s11g_hind_800D46D8(work, 8);
        GV_DestroyActor(&work->actor);
    }

    work->field_62C.vx = GM_PlayerPosition.vx;
    work->field_62C.vy = GM_PlayerPosition.vy;
    work->field_62C.vz = GM_PlayerPosition.vz;

    work->field_5E0++;
    work->field_5E4--;
    work->field_5EC--;

    work->field_8BC = GM_StreamStatus();

    switch (work->field_5C4)
    {
    case 0:
        s11g_hind_800D4DD0(work);
        break;
    case 1:
        s11g_hind_800D50F0(work);
        break;
    case 2:
        s11g_hind_800D5420(work);
        break;
    }

    time = work->field_5E0;
    work->field_5FC.vy += (rsin(time * 64) - rsin((time - 1) * 64)) / 2;
    work->field_5FC.vx += rsin(time * 23) - rsin((time - 1) * 23);
    work->field_5FC.vz += rsin(time * 32) - rsin((time - 1) * 32);

    if (GM_GameStatus & STATE_BEHIND_CAMERA)
    {
        pos.vx = (gUnkCameraStruct2_800B7868.eye.vx * 7 + work->field_4BC.vx) / 8;
        pos.vy = gUnkCameraStruct2_800B7868.eye.vy;
        pos.vz = (gUnkCameraStruct2_800B7868.eye.vz * 7 + work->field_4BC.vz) / 8;
    }
    else
    {
        pos.vx = (GM_PlayerPosition.vx * 7 + work->field_4BC.vx) / 8;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = (GM_PlayerPosition.vz * 7 + work->field_4BC.vz) / 8;
    }

    s11g_hind_800D4A24(&work->field_4BC.vx, &work->field_5FC.vx, &sp30, 40);
    turn.vx = sp30;

    s11g_hind_800D4A24(&work->field_4BC.vy, &work->field_5FC.vy, &sp34, 26);
    turn.vy = 0;

    s11g_hind_800D4A24(&work->field_4BC.vz, &work->field_5FC.vz, &sp30, 40);
    turn.vz = -sp30;

    dx = (GM_PlayerPosition.vx - work->field_4BC.vx) >> 1;
    dz = (GM_PlayerPosition.vz - work->field_4BC.vz) >> 1;

    sp18.vy = ratan2(dx, dz) & 0xFFF;
    sp18.vx = 0;
    sp18.vz = 0;

    s11g_hind_800D4B68(&work->control.turn, &sp18, 128);

    rot.vx = 0;
    rot.vy = work->control.rot.vy;
    rot.vz = 0;

    DG_SetPos2(&DG_ZeroVector, &rot);
    DG_PutVector(&turn, &turn, 1);

    work->control.turn.vx = turn.vz;
    work->control.turn.vz = turn.vx;

    work->body.rots[1].vy -= work->field_4B4;
    if (work->body.rots[1].vy < 0)
    {
        work->body.rots[1].vy += 4096;
    }

    work->body.rots[2].vx -= work->field_4B8;
    if (work->body.rots[2].vx < 0)
    {
        work->body.rots[2].vx += 4096;
    }

    if ((mts_get_tick_count() - work->last_time) >= 8)
    {
        work->last_time = mts_get_tick_count();

        if (work->field_930 == 0)
        {
            if (work->field_5F0 > 0)
            {
                GM_SeSet2(0, 63, 181);
            }
            else
            {
                switch (work->field_8CC)
                {
                case 0:
                    s11g_hind_800D46B8(&pos, 181);
                    break;
                case 1:
                    work->field_8CC = 2;
                    GM_SeSet2(0, 127, 0xB3);
                    s11g_hind_800D46B8(&pos, 181);
                    break;
                case 2:
                    work->field_8CC = 3;
                    s11g_hind_800D46B8(&pos, 182);
                    break;
                case 3:
                    work->field_8CC = 4;
                    s11g_hind_800D46B8(&pos, 183);
                    break;
                case 4:
                    work->field_8CC = 0;
                    s11g_hind_800D46B8(&pos, 184);
                    break;
                }
            }
        }
        else
        {
            GM_SeSet2(0, 8, 181);
        }
    }

    if (work->field_958 == 0 && (mts_get_tick_count() - work->last_time2) >= 4)
    {
        work->last_time2 =  mts_get_tick_count();

        if (work->field_930 == 0 && work->field_5D4 == 1)
        {
            s11g_hind_800D46B8(&pos, 177);
        }
    }
}
