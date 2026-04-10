#include "johnny2.h"
#include "jfamas.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

#include "chara/snake/shadow.h" // for NewShadow
#include "enemy/glight.h"       // for NewGunLight

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[17];
    MOTION_SEGMENT m_segs2[17];
    SVECTOR        rots[32];
    MATRIX         light[2];
    GV_ACT        *weapon;
    int            trigger;
    GV_ACT        *gunlight;
    int           *enable_gunlight;
    GV_ACT        *shadow;
    short          field_7EC;
    short          field_7EE;
    char           pad1[0x8];
    SVECTOR        svec_7F8;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern int s03c_dword_800C33D8;

static void Act(Work *work)
{
    CONTROL *control;
    OBJECT  *body;
    int      rand;

    if (s03c_dword_800C33D8 == 1)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    body = &work->body;
    GM_ActMotion(body);

    control = &work->control;
    GM_ActControl(control);
    GM_ActObject(body);
    DG_GetLightMatrix2(&control->mov, work->light);

    work->control.height = work->body.height;

    if (work->body.is_end != 0)
    {
        work->control.mov.vx = 6000;
        work->control.mov.vz = 750;

        rand = GV_RandU(64);
        if (rand < 16)
        {
            if (work->body.action != 11)
            {
                GM_ConfigObjectAction(body, 11, 0, 4);
            }
        }
        else if (rand < 32)
        {
            if (work->body.action != 15)
            {
                GM_ConfigObjectAction(body, 15, 0, 4);
            }
        }
        else if (rand < 48)
        {
            if (work->body.action != 10)
            {
                GM_ConfigObjectAction(body, 10, 0, 4);
            }
        }
        else if (work->body.action != 9)
        {
            GM_ConfigObjectAction(body, 9, 0, 4);
        }
    }
    if (work->svec_7F8.vy < 0 && work->control.level_flag != 0)
    {
        work->svec_7F8.vy = 0;
    }

    work->svec_7F8.vy -= 32;

    work->control.step.vy = work->control.step.vy + work->svec_7F8.vy;
    work->control.radar_cone.dir = work->control.rot.vy;
}

static void Die(Work *work)
{
    if (work->shadow != NULL)
    {
        GV_DestroyOtherActor(work->shadow);
    }

    if (work->weapon != NULL)
    {
        GV_DestroyOtherActor(work->weapon);
    }

    if (work->gunlight != NULL)
    {
        GV_DestroyOtherActor(work->gunlight);
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

static void InitExtra(Work *work)
{
    work->weapon = NewJohnnyFamas(&work->control, &work->body, 4, &work->trigger);
    work->gunlight = NewGunLight(&work->body.objs->objs[4].world, &work->enable_gunlight);

    work->field_7EE = 0;
    work->field_7EC = 0;

    work->svec_7F8 = DG_ZeroVector;
}

static int GetResources(Work *work)
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
    obj = &work->body;

    control->rot.vy = 1024;
    control->turn.vy = 1024;

    cone->len = 6000;
    cone->ang = 1024;

    GM_InitObject(obj, GV_StrCode("johnny"), 0x32D, GV_StrCode("joh_03c"));
    GM_ConfigObjectJoint(obj);
    GM_ConfigMotionControl(obj, &work->m_ctrl, GV_StrCode("joh_03c"), work->m_segs1, work->m_segs2, control,
                           work->rots);
    GM_ConfigObjectLight(obj, work->light);
    GM_ConfigObjectAction(obj, 10, 0, 0);

    InitExtra(work);

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow(control, obj, indices);

    if (work->shadow == NULL)
    {
        return -1;
    }

    return 0;
}

void *NewJohnny2(void)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "johnny2.c");

    if (GetResources(work) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return (void *)work;
}
