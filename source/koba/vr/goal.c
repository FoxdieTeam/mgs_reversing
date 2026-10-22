#include "goal.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "strcode.h"
#include "koba/vr/vr.h"

/*---------------------------------------------------------------------------*/

// GCL options
#define OPT_MODEL          'm'    // model
#define OPT_POS            'p'    // position
#define OPT_DIR            'd'    // rotation
#define OPT_VISIBLE        'v'    // initially visible

// VR-DISC goal marker: a spinning model that fades out once the mission
// is cleared

#define GOAL_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_BOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_INVISIBLE | DG_FLAG_AMBIENT )

#define GOAL_RADAR_ATR  ( RADAR_VISIBLE | RADAR_UNK1 )

#define GOAL_SPIN       68
#define GOAL_FADE_TIME  64
#define GOAL_COLOR      127

#define MSG_GOAL_SHOW   0x8C8F

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT  object;         // 0x20
    MATRIX  light[2];       // 0x104
    SVECTOR pos;            // 0x144
    SVECTOR rot;            // 0x14C
    int     name;           // 0x154
    CONTROL control;        // 0x158
    int     visible;        // 0x1D4
    int     timer;          // 0x1D8
} Work;

/*---------------------------------------------------------------------------*/

static void CheckMessages(Work *work)
{
    GV_MSG *msg;
    int     n_msgs;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == MSG_GOAL_SHOW)
        {
            DG_VisibleObjs(work->object.objs);
            GM_ConfigControlAttribute(&work->control, GOAL_RADAR_ATR);
        }
    }
}

static void Act(Work *work)
{
    MATRIX *light;

    CheckMessages(work);

    RotMatrixYXZ_gte(&work->rot, &work->object.objs->world);
    work->rot.vy = (work->rot.vy + GOAL_SPIN) & 0xFFF;

    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    if (GM_Vitality > 0 && VR_Status == VR_STATUS_CLEAR)
    {
        if (work->timer > 0)
        {
            work->timer--;
        }
        else
        {
            GV_DestroyActor(&work->actor);
        }

        light = work->object.objs->light;
        light[0].t[0] = light[0].t[1] = light[0].t[2] =
        light[1].t[0] = light[1].t[1] = light[1].t[2] = work->timer * 2;
    }
}

static void Die(Work *work)
{
    work->object.objs->flag = GOAL_FLAG;
    GM_FreeObject(&work->object);
    GM_FreeControl(&work->control);
}

static int GetResources(Work *work, SVECTOR *pos, SVECTOR *dir, int model, int map, int name)
{
    SVECTOR  position;
    OBJECT  *object;
    CONTROL *control;
    MATRIX  *light;

    object = &work->object;
    position = *pos;

    GM_CurrentMap = map;
    GM_InitObject(object, model, GOAL_FLAG, map);
    GM_ConfigObjectJoint(object);

    work->pos = position;
    DG_SetPos2(&position, dir);
    work->rot = *dir;
    DG_PutObjs(work->object.objs);

    control = &work->control;
    GM_InitControl(control, name, 0);
    GM_ConfigControlVector(control, &work->pos, &work->rot);
    GM_ConfigObjectLight(object, work->light);

    light = work->object.objs->light;
    light[0].t[0] = light[0].t[1] = light[0].t[2] =
    light[1].t[0] = light[1].t[1] = light[1].t[2] = GOAL_COLOR;

    if (work->visible)
    {
        DG_VisibleObjs(work->object.objs);
        GM_ConfigControlAttribute(control, GOAL_RADAR_ATR);
    }

    work->timer = GOAL_FADE_TIME;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewGoal(int name, int where)
{
    SVECTOR pos;
    SVECTOR dir;
    Work   *work;
    int     model;
    char   *param;

    work = GV_NewActor(GV_ACTOR_AFTER2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "goal.c");

        model = 0;
        param = GCL_GetOption(OPT_MODEL);
        if (param != 0)
        {
            model = GCL_StrToInt(param);
        }

        param = GCL_GetOption(OPT_POS);
        if (param != 0)
        {
            GCL_StrToSV(param, (short *)&pos);
        }
        else
        {
            pos = DG_ZeroVector;
        }

        param = GCL_GetOption(OPT_DIR);
        if (param != 0)
        {
            GCL_StrToSV(param, (short *)&dir);
        }
        else
        {
            dir = DG_ZeroVector;
        }

        param = GCL_GetOption(OPT_VISIBLE);
        if (param != 0)
        {
            work->visible = GCL_StrToInt(param);
        }
        else
        {
            work->visible = TRUE;
        }

        if (GetResources(work, &pos, &dir, model, where, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
