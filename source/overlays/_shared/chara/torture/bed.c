#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/control.h"
#include "game/game.h"
#include "game/object.h"

typedef struct _BedWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    SVECTOR        pos;
} BedWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

static inline int BedCheckMessages(BedWork *work)
{
    int     found;
    GV_MSG *msg;
    int     i;

    found = 0;

    msg = &work->control.field_5C_mesg[work->control.field_56] - 1;
    for (i = work->control.field_56; i > 0; i--)
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

void BedAct_800C6EA8(BedWork *work)
{
    int found;

    if (work->control.field_56 == 0)
    {
        found = 0;
    }
    else
    {
        found = BedCheckMessages(work);
    }

    GM_ActControl(&work->control);
    GM_ActObject2((OBJECT *)&work->object);
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

void BedDie_800C6FA8(BedWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->object);
}

int BedGetResources_800C6FD8(BedWork *work, int name, int map)
{
    CONTROL        *control;
    char           *pos, *dir;
    OBJECT_NO_ROTS *object;
    unsigned short  model;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);
    GM_ConfigControlHazard(control, 0, -2, -2);

    object = &work->object;

    if (GCL_GetOption('m'))
    {
        model = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        model = GV_StrCode("03b_o1");
    }

    GM_InitObjectNoRots(object, model, BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)object, work->light);

    if (!GCL_GetOption('v'))
    {
        return -1;
    }

    GCL_StrToSV(GCL_GetParamResult(), &work->pos);
    return 0;
}

void *NewBed_800C70DC(int name, int where)
{
    BedWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(BedWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, BedAct_800C6EA8, BedDie_800C6FA8, "bed.c");

        if (BedGetResources_800C6FD8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
