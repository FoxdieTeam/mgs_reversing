// VR-DISC only: snwarp.c ("snake warp")
// A copy of Snake's model that follows the player's body and is shown instead of
// him while it grows/shrinks (scaled through a table): "entering" (HASH_ENTER)
// shrinks it away and shows Snake again, "leaving" (HASH_LEAVE) expands it and
// hides Snake.

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define BODY_MODEL      GV_StrCode("snake")
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

#define OPT_HIDE_SNAKE  0x1         // 's' option: start with Snake hidden

#define STEP_HIDDEN     15          // warp model fully shown, Snake hidden
#define STEP_ENTER      0x1F        // counts down to STEP_ENTER_END
#define STEP_ENTER_END  0x10
#define STEP_LEAVE      0x20        // counts up to STEP_LEAVE_END
#define STEP_LEAVE_END  0x2F

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT  object;     // 0x20
    int     time;       // 0x104
    int     name;       // 0x108
    int     flags;      // 0x10C
    int     mode;       // 0x110: HASH_ENTER (show Snake) / HASH_LEAVE (show the warp model) / 0
    short   step;       // 0x114
    short   pad;        // 0x116
    short   scale_xz;   // 0x118
    short   scale_y;    // 0x11A
    MATRIX  light[2];   // 0x11C
} Work;

/*---------------------------------------------------------------------------*/

static short snwarp_scale[2][16] = {
    /* x, z */ { 4096, 1024, 256, 64, 16, 4, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
    /* y */    { 4096, 8000, 12000, 16000, 8000, 4096, 2048, 512, 128, 32, 16, 1, 0, 0, 0, 0 },
};

/*---------------------------------------------------------------------------*/

static void FollowPlayer(Work *work)
{
    DG_OBJS *objs;

    objs = work->object.objs;
    objs->world = GM_PlayerBody->objs->world;
    objs->rots = GM_PlayerBody->objs->rots;
}

static void CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     count;

    if (work->flags & OPT_HIDE_SNAKE)
    {
        work->flags &= ~OPT_HIDE_SNAKE;
        DG_InvisibleObjs(GM_PlayerBody->objs);
        work->step = STEP_HIDDEN;
    }

    count = GV_ReceiveMessage(work->name, &msg);
    for (; count > 0; count--, msg++)
    {
        if (msg->message[0] == HASH_ENTER)
        {
            work->step = STEP_ENTER;
        }
        else if (msg->message[0] == HASH_LEAVE)
        {
            work->step = STEP_LEAVE;
        }
    }
}

static void UpdateStep(Work *work)
{
    int index;

    if (work->step & 0x10)
    {
        if (--work->step == STEP_ENTER_END)
        {
            work->mode = HASH_ENTER;
            work->step = 0;
        }
    }

    if (work->step & 0x20)
    {
        if (++work->step == STEP_LEAVE_END)
        {
            work->step = STEP_HIDDEN;
        }
    }

    if (work->step != 0)
    {
        work->mode = HASH_LEAVE;
    }

    index = work->step & 15;
    work->scale_xz = snwarp_scale[0][index];
    work->scale_y = snwarp_scale[1][index];
}

static void ScaleModel(Work *work)
{
    VECTOR scale;

    scale.vx = scale.vz = work->scale_xz;
    scale.vy = work->scale_y;
    ScaleMatrix(&work->object.objs->world, &scale);
}

static void SetVisibility(Work *work)
{
    if (work->mode == HASH_ENTER)
    {
        DG_InvisibleObjs(work->object.objs);
        DG_VisibleObjs(GM_PlayerBody->objs);
    }
    else if (work->mode == HASH_LEAVE)
    {
        DG_VisibleObjs(work->object.objs);
        DG_InvisibleObjs(GM_PlayerBody->objs);
    }
}

static void Act(Work *work)
{
    if (GM_PlayerControl)
    {
        work->mode = 0;
        CheckMessage(work);
        FollowPlayer(work);
        UpdateStep(work);
        ScaleModel(work);
        SetVisibility(work);

        if (!(work->object.objs->flag & DG_FLAG_INVISIBLE))
        {
            DG_GetLightMatrix2(&GM_PlayerPosition, work->light);
        }
    }

    work->time++;
}

static void Die(Work *work)
{
    GM_FreeObject(&work->object);
}

static int GetResources(Work *work, int name)
{
    OBJECT *object;
    char   *opt;

    object = &work->object;
    GM_InitObject(object, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectJoint(object);
    GM_ConfigObjectLight(object, work->light);

    work->name = name;
    work->step = 0;
    work->flags = 0;

    opt = GCL_GetOption('s');
    if (opt)
    {
        work->flags = GCL_StrToInt(opt);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewSnakeWarp(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "snwarp.c");

        if (GetResources(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
