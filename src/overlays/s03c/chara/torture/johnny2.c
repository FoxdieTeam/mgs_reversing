#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
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
    GV_ACT        *shadow;

    // unused
    short field_7EC;
    short field_7EE;
    char  pad_7F0[0x8];

    SVECTOR svec_7F8;
} Johnny2Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern int s03c_dword_800C33D8;

GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *arg4);
GV_ACT *NewGunLight_800D3AD4(MATRIX *world, int **pvisible);

void Johnny2Act_800CDF84(Johnny2Work *work)
{
    CONTROL *control;
    OBJECT  *object;
    int      rand;

    if (s03c_dword_800C33D8 == 1)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    object = &work->object;
    GM_ActMotion(object);

    control = &work->control;
    GM_ActControl(control);
    GM_ActObject(object);
    DG_GetLightMatrix2(&control->mov, work->light);

    work->control.height = work->object.height;

    if (work->object.is_end != 0)
    {
        work->control.mov.vx = 6000;
        work->control.mov.vz = 750;

        rand = GV_RandU(64);
        if (rand < 16)
        {
            if (work->object.action != 11)
            {
                GM_ConfigObjectAction(object, 11, 0, 4);
            }
        }
        else if (rand < 32)
        {
            if (work->object.action != 15)
            {
                GM_ConfigObjectAction(object, 15, 0, 4);
            }
        }
        else if (rand < 48)
        {
            if (work->object.action != 10)
            {
                GM_ConfigObjectAction(object, 10, 0, 4);
            }
        }
        else if (work->object.action != 9)
        {
            GM_ConfigObjectAction(object, 9, 0, 4);
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
        GV_DestroyOtherActor(work->shadow);
    }

    if (work->jfamas != NULL)
    {
        GV_DestroyOtherActor(work->jfamas);
    }

    if (work->gunlight != NULL)
    {
        GV_DestroyOtherActor(work->gunlight);
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
}

void Johnny2_800CE154(Johnny2Work *work)
{
    work->jfamas = NewJFamas_800CAFAC(&work->control, &work->object, 4, &work->field_7DC);
    work->gunlight = NewGunLight_800D3AD4(&work->object.objs->objs[4].world, &work->gunlight_pvisible);

    work->field_7EE = 0;
    work->field_7EC = 0;

    work->svec_7F8 = DG_ZeroVector;
}

int Johnny2GetResources_800CE1D0(Johnny2Work *work)
{
    SVECTOR     indices;
    CONTROL    *control;
    OBJECT     *obj;
    RADAR_CONE *cone;

    control = &work->control;
    if (GM_InitControl(control, GV_StrCode("ジョニー"), 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, control->mov.vy, -1, -1);
    GM_ConfigControlAttribute(control, 5);

    work->control.mov.vx = 6000;
    control->mov.vz = 750;
    control->mov.vy = 750;

    cone = &work->control.radar_cone;
    obj = &work->object;

    control->rot.vy = 1024;
    control->turn.vy = 1024;

    cone->len = 6000;
    cone->ang = 1024;

    GM_InitObject(obj, GV_StrCode("johnny"), 0x32D, GV_StrCode("joh_03c"));
    GM_ConfigObjectJoint(obj);
    GM_ConfigMotionControl(obj, &work->motion, GV_StrCode("joh_03c"), work->oar1, work->oar2, control,
                           work->rots);
    GM_ConfigObjectLight(obj, work->light);
    GM_ConfigObjectAction(obj, 10, 0, 0);

    Johnny2_800CE154(work);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow_800602CC(control, obj, indices);

    if (work->shadow == NULL)
    {
        return -1;
    }

    return 0;
}

GV_ACT *NewJohnny2_800CE368()
{
    Johnny2Work *work;

    work = (Johnny2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Johnny2Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (GV_ACTFUNC)Johnny2Act_800CDF84,
                     (GV_ACTFUNC)Johnny2Die_800CE0DC, "johnny2.c");

    if (Johnny2GetResources_800CE1D0(work) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return &work->actor;
}
