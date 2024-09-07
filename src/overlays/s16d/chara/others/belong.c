#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "strcode.h"

typedef struct BelongWork
{
    GV_ACT         actor;
    CONTROL       *field_20;
    OBJECT        *field_24;
    OBJECT_NO_ROTS field_28;
    int            field_4C;
    int            field_50;
    int            field_54;
} BelongWork;

extern int      DG_CurrentGroupID_800AB968;
extern CONTROL *GM_WhereList_800B56D0[96];
extern int      gControlCount_800AB9B4;

void s16d_belong_800C37DC(BelongWork *work)
{
    GV_MSG *msg;
    int     count;
    int     i;

    i = count = GV_ReceiveMessage(work->field_50, &msg);
    if (count <= 0)
    {
        return;
    }

    for (--i; i >= 0; i--, msg++)
    {
        switch (msg->message[0])
        {
        case HASH_KILL:
            work->field_54 = 1;
            GV_DestroyActor(&work->actor);
            break;
        case HASH_ON:
            work->field_54 = 0;
            DG_VisibleObjs(work->field_28.objs);
            break;
        case HASH_OFF:
            DG_InvisibleObjs(work->field_28.objs);
            work->field_54 = 1;
            break;
        }
    }
}

void s16d_belong_800C38D0(BelongWork *work)
{
    int group_id;

    s16d_belong_800C37DC(work);
    if (work->field_54 != 1)
    {
        GM_CurrentMap_800AB9B0 = work->field_20->map->index;
        work->field_28.objs->group_id = group_id = DG_CurrentGroupID_800AB968;
        if (work->field_24->objs->flag & DG_FLAG_INVISIBLE)
        {
            DG_InvisibleObjs(work->field_28.objs);
        }
        else
        {
            DG_VisibleObjs(work->field_28.objs);
        }
    }
}

void s16d_belong_800C3974(BelongWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->field_28);
}

int s16d_belong_800C3994(BelongWork *work, int name, int where)
{
    CONTROL       **whereListIter;
    CONTROL        *control;
    OBJECT         *parent_obj;
    OBJECT_NO_ROTS *obj;
    int             name_opt;
    int             model;
    int             num_parent;
    int             i;

    model = GCL_StrToInt(GCL_GetOption('m'));
    num_parent = work->field_4C = GCL_StrToInt(GCL_GetOption('u'));
    name_opt = GCL_StrToInt(GCL_GetOption('c'));
    work->field_20 = NULL;
    work->field_24 = NULL;

    whereListIter = GM_WhereList_800B56D0;
    parent_obj = NULL;
    for (i = gControlCount_800AB9B4 - 1; i >= 0; i--)
    {
        control = *whereListIter++;

        if (control->name == name_opt)
        {
            work->field_20 = control;
            parent_obj = work->field_24 = (OBJECT *)(control + 1);
            break;
        }
    }
    obj = &work->field_28;
    if (work->field_20 == NULL)
    {
        printf("name %d is not exist\n", name_opt);
        return -1;
    }
    GM_InitObjectNoRots_800349B0(obj, model, 0x6D, 0);
    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, parent_obj, num_parent);
    work->field_50 = name;
    work->field_54 = 0;
    return 0;
}

GV_ACT *s16d_belong_800C3AD0(int name, int where, int argc, char **argv)
{
    BelongWork *work;

    work = (BelongWork *)GV_NewActor(5, sizeof(BelongWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)s16d_belong_800C38D0,
                         (TActorFunction)s16d_belong_800C3974, "belong.c");
        if (s16d_belong_800C3994(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
