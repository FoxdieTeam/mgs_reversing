#include "equip.h"

#include "common.h"
#include "Game/camera.h"
#include "linkvar.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Thing/sight.h"
#include "strcode.h"

extern int DG_CurrentGroupID;
extern int dword_8009F604;
extern GM_Camera GM_Camera_800B77E8;

/*---------------------------------------------------------------------------*/

typedef struct BoxWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            invisible;
    const char   **names;
    int            unused;
} BoxWork;

#define EXEC_LEVEL GV_ACTOR_AFTER
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )
/*---------------------------------------------------------------------------*/

STATIC int box_1p_view_flag = 0;

STATIC const char *box_texture_names[8] = {
    "cb_box11", "cb_box12",
    "cb_box41", "cb_box42", // cb_box3 (Canyon) was cut
    "cb_box21", "cb_box22",
    "cb_box41", "cb_box42"
};

STATIC int BoxCheckMessage(BoxWork *work)
{
    CONTROL *control = work->control;
    GV_MSG  *msg;
    int      n_msgs;
    u_short  code;

    control->field_56 = GV_ReceiveMessage(control->name, &control->field_5C_mesg);
    msg = control->field_5C_mesg;

    for (n_msgs = control->field_56; n_msgs > 0; n_msgs--)
    {
        if (GV_StrCode("段ボール") == msg->message[0])
        {
            code = msg->message[1];

            if (code == 1)
            {
                work->invisible = 1;
                return 1;
            }
        }

        msg++;
    }

    return 0;
}

STATIC void BoxAct(BoxWork *work)
{
    GM_CurrentMap =  work->control->map->index;

    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

    BoxCheckMessage(work);
    if ( work->invisible )
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else if ( GM_Camera_800B77E8.first_person && (work->parent->objs->flag & DG_FLAG_INVISIBLE) )
    {
        DG_InvisibleObjs(work->object.objs);

        if ( dword_8009F604 != SGT_CB_BOX )
        {
            box_1p_view_flag = 1;
            NewSight_80071CDC(SGT_CB_BOX, SGT_CB_BOX, (short*)&box_1p_view_flag, 1, NULL);
        }
    }
    else
    {
        box_1p_view_flag = 0;
        DG_VisibleObjs(work->object.objs);
    }
}

STATIC void BoxDie(BoxWork *work)
{
    const char **name;
    int          i;

    GM_FreeObject((OBJECT *)&work->object);

    name = work->names;
    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture(name[i], box_texture_names[i]);
    }

    box_1p_view_flag = 0;
}

STATIC int BoxGetResources(BoxWork *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *object = &work->object;
    const char    **name;
    int             i;

    GM_InitObjectNoRots(object, GV_StrCode("cb_box"), BODY_FLAG, 0);

    if (!work->object.objs)
    {
        return -1;
    }

    work->object.objs->objs[0].raise = 250;
    GM_ConfigObjectRoot((OBJECT *)object, parent, 0);

    name = &box_texture_names[(GM_CurrentItemId - ITEM_C_BOX_A) * 2];
    work->names = name;

    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture(box_texture_names[i], name[i]);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBox(CONTROL *control, OBJECT *parent, int num_parent)
{
    BoxWork *work = GV_NewActor(EXEC_LEVEL, sizeof(BoxWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, BoxAct, BoxDie, "box.c");

        if (BoxGetResources(work, parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
    }

    return (void *)work;
}
