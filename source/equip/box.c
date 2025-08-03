#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/camera.h"
#include "linkvar.h"
#include "game/map.h"
#include "game/object.h"
#include "thing/sight.h"

extern int DG_CurrentGroupID;
extern int dword_8009F604;
extern GM_CAMERA GM_Camera;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_AFTER
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE )

#define CB_BOX_SIGHT    0xe2a9  // GV_StrCode("cb_box")

#define CB_BOX_MODEL    GV_StrCode("cb_box")
#define CB_BOX_MSG      GV_StrCode("段ボール")

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    CONTROL       *control;
    OBJECT        *parent;
    int            invisible;
    const char   **names;
    int            unused;
} Work;

/*---------------------------------------------------------------------------*/

STATIC int box_1p_view_flag = FALSE;

STATIC const char *box_texture_names[8] = {
    "cb_box11", "cb_box12",
    "cb_box41", "cb_box42", // cb_box3 (Canyon) was cut
    "cb_box21", "cb_box22",
    "cb_box41", "cb_box42"
};

static int CheckMessage(Work *work)
{
    CONTROL *control = work->control;
    GV_MSG  *msg;
    int      n_msgs;
    u_short  code;

    control->n_messages = GV_ReceiveMessage(control->name, &control->messages);
    msg = control->messages;

    for (n_msgs = control->n_messages; n_msgs > 0; n_msgs--)
    {
        if (CB_BOX_MSG == msg->message[0])
        {
            code = msg->message[1];

            if (code == 1)
            {
                work->invisible = TRUE;
                return 1;
            }
        }

        msg++;
    }

    return 0;
}

static void Act(Work *work)
{
    GM_CurrentMap =  work->control->map->index;

    DG_GroupObjs(work->object.objs, DG_CurrentGroupID);

    CheckMessage(work);
    if ( work->invisible )
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else if ( GM_Camera.first_person && (work->parent->objs->flag & DG_FLAG_INVISIBLE) )
    {
        DG_InvisibleObjs(work->object.objs);

        if ( dword_8009F604 != CB_BOX_SIGHT )
        {
            box_1p_view_flag = TRUE;
            NewSight(CB_BOX_SIGHT, CB_BOX_SIGHT, (short*)&box_1p_view_flag, IT_Scope, NULL);
        }
    }
    else
    {
        box_1p_view_flag = FALSE;
        DG_VisibleObjs(work->object.objs);
    }
}

static void Die(Work *work)
{
    const char **name;
    int          i;

    GM_FreeObject((OBJECT *)&work->object);

    name = work->names;
    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture(name[i], box_texture_names[i]);
    }

    box_1p_view_flag = FALSE;
}

static int GetResources(Work *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *object = &work->object;
    const char    **name;
    int             i;

    GM_InitObjectNoRots(object, CB_BOX_MODEL, BODY_FLAG, 0);

    if (!work->object.objs)
    {
        return -1;
    }

    work->object.objs->objs[0].raise = 250;
    GM_ConfigObjectRoot((OBJECT *)object, parent, 0);

    name = &box_texture_names[(GM_CurrentItemId - IT_Box1) * 2];
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
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "box.c");

        if (GetResources(work, parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
    }

    return (void *)work;
}
