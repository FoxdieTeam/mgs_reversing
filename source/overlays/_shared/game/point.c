#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/control.h"
#include "game/game.h"
#include "strcode.h"

typedef struct _PointWork
{
    GV_ACT  actor;
    CONTROL control;
} PointWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void PointAct_800C5928(PointWork *work)
{
    CONTROL *control;
    int      n_msgs;
    GV_MSG  *msg;
    int      message;

    control = &work->control;
    n_msgs = GV_ReceiveMessage(control->name, &control->field_5C_mesg);

    if (n_msgs <= 0)
    {
        return;
    }

    msg = control->field_5C_mesg;
    while (--n_msgs >= 0)
    {
        message = msg->message[0];

        if (message == HASH_ON)
        {
            control->radar_atr |= RADAR_VISIBLE;
        }

        if (message == HASH_OFF)
        {
            control->radar_atr &= ~RADAR_VISIBLE;
        }

        if (message == HASH_KILL)
        {
            GV_DestroyActor(&work->actor);
        }
    }
}

void PointDie_800C59FC(PointWork *work)
{
    GM_FreeControl(&work->control);
}

int PointGetResources_800C5A1C(PointWork *work, int where, int name)
{
    char *pos, *dir;
    int color;

    if (GM_InitControl(&work->control, name, where) < 0)
    {
        return 0;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(&work->control, pos, dir);

    color = 1 << 12;
    if (GCL_GetOption('c'))
    {
        color = GCL_GetNextParamValue() << 12;
    }

    GM_ConfigControlAttribute(&work->control, color | RADAR_ALL_MAP | RADAR_VISIBLE);
    return 1;
}

void *NewPoint_800C5AB4(int name, int where, int argc, char **argv)
{
    PointWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(PointWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, PointAct_800C5928, PointDie_800C59FC, "point.c");

        if (!PointGetResources_800C5A1C(work, where, name))
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
