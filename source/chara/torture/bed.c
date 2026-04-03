#include "bed.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    MATRIX         light[2];
    SVECTOR        pos;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

static inline int CheckMessages(Work *work)
{
    int     found;
    GV_MSG *msg;
    int     i;

    found = 0;

    msg = &work->control.messages[work->control.n_messages] - 1;
    for (i = work->control.n_messages; i > 0; i--)
    {
        if (msg->message[0] == HASH_TURN)
        {
            found = 1;
            work->control.turn.vx = msg->message[1];
        }
        else if (msg->message[0] == HASH_LEAVE2)
        {
            work->control.mov.vy = 500;
        }

        msg--;
    }

    return found;
}

static void Act(Work *work)
{
    int found;

    if (work->control.n_messages == 0)
    {
        found = 0;
    }
    else
    {
        found = CheckMessages(work);
    }

    GM_ActControl(&work->control);
    GM_ActObject2((OBJECT *)&work->body);
    DG_GetLightMatrix(&work->control.mov, work->light);

    if (found != 0)
    {
        DG_MovePos(&work->pos);

        if (GM_PlayerBody)
        {
            DG_PutObjs(GM_PlayerBody->objs);
        }
    }
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->body);
}

int BedGetResources_800C6FD8(Work *work, int name, int map)
{
    CONTROL        *control;
    OBJECT_NO_ROTS *body;
    u_short         model;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, 0, -2, -2);

    body = &work->body;

    if (GCL_GetOption('m'))
    {
        model = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        model = GV_StrCode("03b_o1");
    }

    GM_InitObjectNoRots(body, model, BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)body, work->light);

    if (!GCL_GetOption('v'))
    {
        return -1;
    }

    GCL_StrToSV(GCL_GetParamResult(), &work->pos);
    return 0;
}

void *NewTortureBed(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "bed.c");

        if (BedGetResources_800C6FD8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
