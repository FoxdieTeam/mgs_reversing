#include "box.h"
#include "libgcl/hash.h"
#include "Equip/effect.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "Game/object.h"
#include "Thing/sight.h"

extern int DG_CurrentGroupID_800AB968;
extern int dword_8009F604;
extern GM_Camera GM_Camera_800B77E8;

int dword_8009F284 = 0;
const char *off_8009F288[8] = {
    "cb_box11", "cb_box12",
    "cb_box41", "cb_box42", // cb_box3 (Canyon) was cut
    "cb_box21", "cb_box22",
    "cb_box41", "cb_box42"
};

int BoxCheckMessage_8006195C(BoxWork *work)
{
    CONTROL *pCtrl = work->control;
    GV_MSG *pMsg;
    int count;
    unsigned short message;

    pCtrl->field_56 = GV_ReceiveMessage(pCtrl->name, &pCtrl->field_5C_mesg);
    pMsg = &pCtrl->field_5C_mesg[0];

    for (count = pCtrl->field_56; count > 0; pMsg++, count--)
    {
        if (GV_StrCode("段ボール") == pMsg->message[0])
        {
            message = pMsg->message[1];

            if (message == 1)
            {
                work->field_4C_bFound = message;
                return 1;
            }
        }
    }

    return 0;
}

void BoxAct_80061A14(BoxWork *work)
{
    GM_CurrentMap_800AB9B0 =  work->control->map->index;

    DG_GroupObjs(work->field_20.objs, DG_CurrentGroupID_800AB968);

    BoxCheckMessage_8006195C(work);
    if ( work->field_4C_bFound )
    {
        DG_InvisibleObjs(work->field_20.objs);
    }
    else if ( GM_Camera_800B77E8.field_22 && (work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0 )
    {
        DG_InvisibleObjs(work->field_20.objs);

        if ( dword_8009F604 != SGT_CB_BOX )
        {
            dword_8009F284 = 1;
            NewSight_80071CDC(SGT_CB_BOX, SGT_CB_BOX, (short*)&dword_8009F284, 1, 0);
        }
    }
    else
    {
        dword_8009F284 = 0;
        DG_VisibleObjs(work->field_20.objs);
    }
}

void BoxDie_80061B30(BoxWork *work)
{
    const char **ppName;
    int i;

    GM_FreeObject_80034BF8((OBJECT *)&work->field_20);

    ppName = work->field_50_ppName;
    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(ppName[i], off_8009F288[i]);
    }

    dword_8009F284 = 0;
}

int BoxGetResources_80061BA0(BoxWork *work, OBJECT *pParent)
{
    OBJECT_NO_ROTS *pObject = &work->field_20;
    short currentItem;
    const char **ppName;
    int i;

    GM_InitObjectNoRots_800349B0(pObject, GV_StrCode("cb_box"), 109, 0);

    if (!work->field_20.objs)
    {
        return -1;
    }

    work->field_20.objs->objs[0].raise = 250;
    GM_ConfigObjectRoot_80034C5C((OBJECT *)pObject, pParent, 0);

    currentItem = GM_CurrentItemId;
    ppName = &off_8009F288[(currentItem - 2) * 2];
    work->field_50_ppName = ppName;

    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(off_8009F288[i], ppName[i]);
    }

    return 0;
}

GV_ACT * NewBox_80061C7C(CONTROL *pCtrl, OBJECT *pParent, int unused)
{
    BoxWork *work = (BoxWork *)GV_NewActor(6, sizeof(BoxWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)BoxAct_80061A14,
                         (TActorFunction)BoxDie_80061B30, "box.c");
        if (BoxGetResources_80061BA0(work, pParent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }
        work->control = pCtrl;
        work->field_48_pParent = pParent;
    }

    return &work->actor;
}
