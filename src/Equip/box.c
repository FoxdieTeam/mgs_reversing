#include "box.h"

#include <stddef.h> // for NULL
#include "Equip/effect.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Thing/sight.h"
#include "strcode.h"

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

extern int DG_CurrentGroupID_800AB968;
extern int dword_8009F604;
extern GM_Camera GM_Camera_800B77E8;

int box_first_person_8009F284 = 0;
const char *box_names_8009F288[8] = {
    "cb_box11", "cb_box12",
    "cb_box41", "cb_box42", // cb_box3 (Canyon) was cut
    "cb_box21", "cb_box22",
    "cb_box41", "cb_box42"
};

int BoxCheckMessage_8006195C(BoxWork *work)
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

void BoxAct_80061A14(BoxWork *work)
{
    GM_CurrentMap_800AB9B0 =  work->control->map->index;

    DG_GroupObjs(work->object.objs, DG_CurrentGroupID_800AB968);

    BoxCheckMessage_8006195C(work);
    if ( work->invisible )
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else if ( GM_Camera_800B77E8.first_person && (work->parent->objs->flag & DG_FLAG_INVISIBLE) )
    {
        DG_InvisibleObjs(work->object.objs);

        if ( dword_8009F604 != SGT_CB_BOX )
        {
            box_first_person_8009F284 = 1;
            NewSight_80071CDC(SGT_CB_BOX, SGT_CB_BOX, (short*)&box_first_person_8009F284, 1, NULL);
        }
    }
    else
    {
        box_first_person_8009F284 = 0;
        DG_VisibleObjs(work->object.objs);
    }
}

void BoxDie_80061B30(BoxWork *work)
{
    const char **name;
    int          i;

    GM_FreeObject((OBJECT *)&work->object);

    name = work->names;
    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(name[i], box_names_8009F288[i]);
    }

    box_first_person_8009F284 = 0;
}

int BoxGetResources_80061BA0(BoxWork *work, OBJECT *parent)
{
    OBJECT_NO_ROTS *object = &work->object;
    const char    **name;
    int             i;

    GM_InitObjectNoRots(object, GV_StrCode("cb_box"), WEAPON_FLAG, 0);

    if (!work->object.objs)
    {
        return -1;
    }

    work->object.objs->objs[0].raise = 250;
    GM_ConfigObjectRoot((OBJECT *)object, parent, 0);

    name = &box_names_8009F288[(GM_CurrentItemId - ITEM_C_BOX_A) * 2];
    work->names = name;

    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(box_names_8009F288[i], name[i]);
    }

    return 0;
}

GV_ACT *NewBox_80061C7C(CONTROL *control, OBJECT *parent, int num_parent)
{
    BoxWork *work = (BoxWork *)GV_NewActor(6, sizeof(BoxWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BoxAct_80061A14,
                         (TActorFunction)BoxDie_80061B30, "box.c");

        if (BoxGetResources_80061BA0(work, parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->control = control;
        work->parent = parent;
    }

    return (GV_ACT *)work;
}
