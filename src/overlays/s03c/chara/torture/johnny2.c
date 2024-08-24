#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "chara/snake/shadow.h"

typedef struct Johnny2Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    MOTION_SEGMENT oar1[17];
    MOTION_SEGMENT oar2[17];
    SVECTOR        rots[32];
    MATRIX         light[2];
    GV_ACT        *jfamas;
    int            field_7DC;
    GV_ACT        *gunlight;
    int           *gunlight_pvisible;
    ShadowWork    *shadow;

    // unused
    short field_7EC;
    short field_7EE;
    char  pad_7F0[0x8];

    SVECTOR svec_7F8;
} Johnny2Work;

#define EXEC_LEVEL 5

extern int s03c_dword_800C33D8;

extern SVECTOR DG_ZeroVector_800AB39C;

GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *arg4);
GV_ACT *NewGunLight_800D3AD4(MATRIX *world, int **pvisible);

void Johnny2Act_800CDF84(Johnny2Work *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      rand;

    if (s03c_dword_800C33D8 == 1)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    object = &work->object;
    GM_ActMotion_80034A7C(object);

    control = &work->control;
    GM_ActControl_80025A7C(control);
    GM_ActObject_80034AF4(object);
    DG_GetLightMatrix2_8001A5D8(&control->mov, work->light);

    work->control.height = work->object.field_18;

    if (work->object.is_end != 0)
    {
        work->control.mov.vx = 6000;
        work->control.mov.vz = 750;

        rand = GV_RandU_80017090(64);
        if (rand < 16)
        {
            if (work->object.action_flag != 11)
            {
                GM_ConfigObjectAction_80034CD4(object, 11, 0, 4);
            }
        }
        else if (rand < 32)
        {
            if (work->object.action_flag != 15)
            {
                GM_ConfigObjectAction_80034CD4(object, 15, 0, 4);
            }
        }
        else if (rand < 48)
        {
            if (work->object.action_flag != 10)
            {
                GM_ConfigObjectAction_80034CD4(object, 10, 0, 4);
            }
        }
        else if (work->object.action_flag != 9)
        {
            GM_ConfigObjectAction_80034CD4(object, 9, 0, 4);
        }
    }
    if (work->svec_7F8.vy < 0 && work->control.field_57 != 0)
    {
        work->svec_7F8.vy = 0;
    }

    work->svec_7F8.vy -= 32;

    work->control.step.vy = work->control.step.vy + work->svec_7F8.vy;
    work->control.radar_cone.dir = work->control.rot.vy;
}

void Johnny2Die_800CE0DC(Johnny2Work *work)
{
    if (work->shadow != NULL)
    {
        GV_DestroyOtherActor_800151D8(&work->shadow->field_0_actor);
    }

    if (work->jfamas != NULL)
    {
        GV_DestroyOtherActor_800151D8(work->jfamas);
    }

    if (work->gunlight != NULL)
    {
        GV_DestroyOtherActor_800151D8(work->gunlight);
    }

    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);
}

void Johnny2_800CE154(Johnny2Work *work)
{
    work->jfamas = NewJFamas_800CAFAC(&work->control, &work->object, 4, &work->field_7DC);
    work->gunlight = NewGunLight_800D3AD4(&work->object.objs->objs[4].world, &work->gunlight_pvisible);

    work->field_7EE = 0;
    work->field_7EC = 0;

    work->svec_7F8 = DG_ZeroVector_800AB39C;
}

int Johnny2GetResources_800CE1D0(Johnny2Work *work)
{
    SVECTOR     indices;
    CONTROL    *control;
    OBJECT     *obj;
    RADAR_CONE *cone;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, GV_StrCode_80016CCC("ジョニー"), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(control, control->mov.vy, -1, -1);
    GM_ConfigControlAttribute_8002623C(control, 5);

    work->control.mov.vx = 6000;
    control->mov.vz = 750;
    control->mov.vy = 750;

    cone = &work->control.radar_cone;
    obj = &work->object;

    control->rot.vy = 1024;
    control->turn.vy = 1024;

    cone->len = 6000;
    cone->ang = 1024;

    GM_InitObject_80034A18(obj, GV_StrCode_80016CCC("johnny"), 0x32D, GV_StrCode_80016CCC("joh_03c"));
    GM_ConfigObjectJoint_80034CB4(obj);
    GM_ConfigMotionControl_80034F08(obj, &work->motion, GV_StrCode_80016CCC("joh_03c"), work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight_80034C44(obj, work->light);
    GM_ConfigObjectAction_80034CD4(obj, 10, 0, 0);

    Johnny2_800CE154(work);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = shadow_init_800602CC(control, obj, indices);

    if (work->shadow == NULL)
    {
        return -1;
    }

    return 0;
}

GV_ACT *NewJohnny2_800CE368()
{
    Johnny2Work *work;

    work = (Johnny2Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Johnny2Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Johnny2Act_800CDF84, (TActorFunction)Johnny2Die_800CE0DC,
                              "johnny2.c");

    if (Johnny2GetResources_800CE1D0(work) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }

    return &work->actor;
}
