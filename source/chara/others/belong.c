#include "belong.h"

#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"
#ifdef VR_EXE
#include "equip/equip.h"
#endif

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
#ifdef VR_EXE
    short          raise;       // 0x58 saved by EQ_InvisibleUnit
    short          n_packs;     // 0x5A
    int            unit_state;  // 0x5C see UNIT_*
#endif
} Work;

#ifdef VR_EXE
// FIXME: names guessed from the control flow of the VR revision
enum
{
    UNIT_NONE = 0,    // nothing hidden
    UNIT_SHOWN = 1,   // equipment unit of the parent was shown again
    UNIT_HIDDEN = 2   // equipment unit of the parent is hidden (EQ_InvisibleUnit)
};
#endif

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
#ifdef VR_EXE
            DG_VisibleObjs(work->field_28.objs);
            if (work->unit_state == UNIT_SHOWN)
            {
                EQ_InvisibleUnit(work->field_24, work->field_4C, &work->n_packs, &work->raise);
                work->unit_state = UNIT_HIDDEN;
            }
#else
            DG_VisibleObjs(work->field_28.objs);
#endif
            break;
        case HASH_OFF:
            DG_InvisibleObjs(work->field_28.objs);
            work->field_54 = 1;
#ifdef VR_EXE
            if (work->unit_state == UNIT_HIDDEN)
            {
                EQ_VisibleUnit(work->field_24, work->field_4C, &work->n_packs, &work->raise);
                work->unit_state = UNIT_SHOWN;
            }
#endif
            break;
        }
    }
}

static void Act(Work *work)
{
    CheckMessage(work);
    if (work->field_54 != 1)
    {
        GM_CurrentMap = work->control->map->index;
        DG_GroupObjsEx(work->field_28.objs);
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
#ifdef VR_EXE
    if (work->unit_state == UNIT_HIDDEN)
    {
        EQ_VisibleUnit(work->field_24, work->field_4C, &work->n_packs, &work->raise);
    }
#endif
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
    for (i = GM_N_WhereList - 1; i >= 0; i--)
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
#ifdef VR_EXE
    work->unit_state = UNIT_NONE;
    if (GCL_GetOption('v'))
    {
        GM_ConfigObjectLight((OBJECT *)obj, parent_obj->light);
        EQ_InvisibleUnit(work->field_24, work->field_4C, &work->n_packs, &work->raise);
        work->unit_state = UNIT_HIDDEN;
    }
#endif
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBelong(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
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
