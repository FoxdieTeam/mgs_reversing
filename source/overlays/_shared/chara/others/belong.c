#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "strcode.h"

extern int      DG_CurrentGroupID;
extern CONTROL *GM_WhereList[96];
extern int      gControlCount_800AB9B4;

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *field_24;
    OBJECT_NO_ROTS field_28;
    int            field_4C;
    int            name;
    int            field_54;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

/*---------------------------------------------------------------------------*/

static void CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     count;
    int     i;

    i = count = GV_ReceiveMessage(work->name, &msg);
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

static void Act(Work *work)
{
    int group_id;

    CheckMessage(work);
    if (work->field_54 != 1)
    {
        GM_CurrentMap = work->control->map->index;
        work->field_28.objs->group_id = group_id = DG_CurrentGroupID;
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

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->field_28);
}

static int GetResources(Work *work, int name, int where)
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
    work->control = NULL;
    work->field_24 = NULL;

    whereListIter = GM_WhereList;
    parent_obj = NULL;
    for (i = gControlCount_800AB9B4 - 1; i >= 0; i--)
    {
        control = *whereListIter++;

        if (control->name == name_opt)
        {
            work->control = control;
            parent_obj = work->field_24 = (OBJECT *)(control + 1);
            break;
        }
    }
    obj = &work->field_28;
    if (work->control == NULL)
    {
        printf("name %d is not exist\n", name_opt);
        return -1;
    }
    GM_InitObjectNoRots(obj, model, 0x6D, 0);
    GM_ConfigObjectRoot((OBJECT *)obj, parent_obj, num_parent);
    work->name = name;
    work->field_54 = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBelong(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "belong.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
