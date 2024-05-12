#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Takabe/thing.h"

typedef struct Monitor1Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  object;
    MATRIX  light[2];
    TARGET *target;
    int     flag;
    int     bound;
    int     flag2;
    int     vy;
    int     proc;
} Monitor1Work;

#define EXEC_LEVEL 5

extern SVECTOR DG_ZeroVector_800AB39C;
extern MATRIX  DG_ZeroMatrix_8009D430;

GV_ACT *NewSpark2_800CA714(MATRIX *world);
void    AN_Unknown_800DCE84(SVECTOR *pos);

void Monitor1Act_800DC8BC(Monitor1Work *work)
{
    MATRIX   world;
    SVECTOR  svec1;
    SVECTOR  pos;
    CONTROL *control;
    MATRIX  *light;
    OBJECT  *object;
    TARGET  *target;
    int      flag;

    flag = 0;

    control = &work->control;
    light = work->light;
    world = DG_ZeroMatrix_8009D430;
    target = work->target;

    work->flag2 = 0;
    DG_GetLightMatrix_8001A3C4(&control->field_0_mov, light);

    if ((target->field_6_flags & TARGET_POWER) && target->field_26_hp != 255 && work->bound == 0)
    {
        work->flag = 1;
        work->bound = 1;

        target->field_26_hp = 255;
        target->field_6_flags &= ~TARGET_POWER;

        GM_SeSet_80032858(&control->field_0_mov, 0x3C);

        object = &work->object;
        GM_FreeObject_80034BF8(object);
        GM_InitObject_80034A18(object, GV_StrCode_80016CCC("nanao_d"), 0x1D, 0);
        GM_ConfigObjectJoint_80034CB4(object);
        GM_ConfigObjectLight_80034C44(object, light);
        GM_ConfigObjectStep_80034C54(object, &work->control.field_44_step);

        control->field_8_rot.vz = -GV_RandU_80017090(128) - 128;
        control->field_44_step.vy = 32;

        svec1.vy = control->field_8_rot.vy - 1024;
        svec1.vz = 0;
        svec1.vx = control->field_8_rot.vz;

        world.t[0] = control->field_0_mov.vx;
        world.t[1] = control->field_0_mov.vy;
        world.t[2] = control->field_0_mov.vz;

        RotMatrixYXZ(&svec1, &world);

        flag = 1;

        if (work->proc)
        {
            GCL_ExecProc_8001FF2C(work->proc, NULL);
        }
    }

    if (work->flag)
    {
        if (control->field_0_mov.vy < work->vy)
        {
            control->field_44_step.vy = -control->field_44_step.vy / 4;
            control->field_0_mov.vy = work->vy;
            if (control->field_44_step.vy < 16)
            {
                work->flag = 0;
                control->field_44_step.vy = 0;
                control->field_0_mov.vy = work->vy;
                control->field_8_rot.vx = 0;
            }
        }
        else
        {
            control->field_44_step.vy -= 16;
            work->flag2 |= 1;
        }
    }

    if (work->flag2 == 0)
    {
        GM_ConfigControlHazard_8002622C(control, -1, 0, -1);
    }
    else
    {
        GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
    }

    GM_ActControl_80025A7C(control);
    GM_ActObject2_80034B88(&work->object);

    if (flag)
    {
        NewSpark2_800CA714(&world);
        svec1.vx = 0;
        svec1.vy = 0;
        svec1.vz = 0x15E;
        DG_SetPos_8001BC44(&world);
        DG_PutVector_8001BE48(&svec1, &pos, 1);
        AN_Unknown_800DCE84(&pos);
    }

    GM_Target_SetVector_8002D500(target, &work->control.field_0_mov);
    sub_8002DA14(target);
}

void Monitor1Die_800DCBB0(Monitor1Work *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);
    GM_FreeTarget_8002D4B0(work->target);
}

void Monitor1InitTarget_800DCBEC(Monitor1Work *work)
{
    SVECTOR svec1;
    SVECTOR svec2;
    TARGET *target;

    svec1.vx = 300;
    svec1.vy = 400;
    svec1.vz = 300;

    svec2 = DG_ZeroVector_800AB39C;

    target = GM_AllocTarget_8002D400();
    work->target = target;
    GM_SetTarget_8002DC74(target, TARGET_POWER | TARGET_SEEK, NO_SIDE, &svec1);
    GM_Target_8002DCCC(target, 1, -1, 0xFF, 0, &svec2);
}

int Monitor1GetResources_800DCC90(Monitor1Work *work, int arg1, int arg2)
{
    OBJECT  *object;
    CONTROL *control;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
    GM_ConfigControlInterp_80026244(control, 0);
    GM_ConfigControlString_800261C0(control, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));

    work->control.field_44_step = DG_ZeroVector_800AB39C;
    work->proc = THING_Gcl_GetInt('e');
    work->bound = THING_Gcl_GetInt('b');

    control->field_8_rot.vy += 1024;
    control->field_4C_turn.vy += 1024;

    object = &work->object;
    if (work->bound == 0)
    {
        GM_InitObject_80034A18(object, GV_StrCode_80016CCC("nanao"), 0x1D, 0);
    }
    else
    {
        GM_InitObject_80034A18(object, GV_StrCode_80016CCC("nanao_d"), 0x1D, 0);
    }

    GM_ConfigObjectJoint_80034CB4(object);
    GM_ConfigObjectLight_80034C44(object, work->light);
    GM_ConfigObjectStep_80034C54(object, &work->control.field_44_step);

    Monitor1InitTarget_800DCBEC(work);

    return 0;
}

GV_ACT *NewMonitor1_800DCDE0(int arg0, int arg1)
{
    Monitor1Work *work;

    work = (Monitor1Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Monitor1Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Monitor1Act_800DC8BC,
                                  (TActorFunction)Monitor1Die_800DCBB0, "monitor1.c");
        if (Monitor1GetResources_800DCC90(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->flag = 0;
        work->flag2 = 0;
        work->vy = work->control.field_0_mov.vy;
    }
    return &work->actor;
}
