#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "kojo/demo.h"
#include "hind.h"
#include "libgcl/libgcl.h"

SVECTOR s11g_dword_800C3598 = {5000, 3000, 5000, 0};
SVECTOR s11g_dword_800C35A0 = {100, 0, 0, 0};

void HindAct(HindWork *work);
void HindDie(HindWork *work);

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

    GV_SetNamedActor(work, HindAct, HindDie, "hind.c");

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
