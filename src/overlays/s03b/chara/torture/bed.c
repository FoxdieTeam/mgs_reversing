#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct _BedWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    SVECTOR        pos;
} BedWork;

extern OBJECT *GM_PlayerBody_800ABA20;

#define EXEC_LEVEL 5

static inline int BedCheckMessages(BedWork *work)
{
    int     found;
    GV_MSG *msg;
    int     i;

    found = 0;

    msg = &work->control.field_5C_mesg[work->control.field_56] - 1;
    for (i = work->control.field_56; i > 0; i--)
    {
        if (msg->message[0] == 0xE2E9)
        {
            found = 1;
            work->control.turn.vx = msg->message[1];
        }
        else if (msg->message[0] == 0x1A19)
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

    GM_ActControl_80025A7C(&work->control);
    GM_ActObject2_80034B88((OBJECT *)&work->object);
    DG_GetLightMatrix_8001A3C4(&work->control.mov, work->light);

    if (found != 0)
    {
        DG_MovePos_8001BD20(&work->pos);

        if (GM_PlayerBody_800ABA20)
        {
            DG_PutObjs_8001BDB8(GM_PlayerBody_800ABA20->objs);
        }
    }
}

void BedDie_800C6FA8(BedWork *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8((OBJECT *)&work->object);
}

int BedGetResources_800C6FD8(BedWork *work, int name, int map)
{
    CONTROL        *control;
    char           *pos, *dir;
    OBJECT_NO_ROTS *object;
    unsigned short  model;

    control = &work->control;
    if (GM_InitControl_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption_80020968('p');
    dir = GCL_GetOption_80020968('d');
    GM_ConfigControlString_800261C0(control, pos, dir);
    GM_ConfigControlHazard_8002622C(control, 0, -2, -2);

    object = &work->object;

    if (GCL_GetOption_80020968('m'))
    {
        model = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        model = GV_StrCode_80016CCC("03b_o1");
    }

    GM_InitObjectNoRots_800349B0(object, model, WEAPON_FLAG, 0);
    GM_ConfigObjectLight_80034C44((OBJECT *)object, work->light);

    if (!GCL_GetOption_80020968('v'))
    {
        return -1;
    }

    GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->pos);
    return 0;
}

GV_ACT * NewBed_800C70DC(int name, int where)
{
    BedWork *work;

    work = (BedWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(BedWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BedAct_800C6EA8, (TActorFunction)BedDie_800C6FA8, "bed.c");

        if (BedGetResources_800C6FD8(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
