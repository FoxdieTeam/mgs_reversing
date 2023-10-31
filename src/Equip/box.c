#include "box.h"
#include "unknown.h"
#include "Game/map.h"
#include "Thing/sight.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "libgcl/hash.h"

extern int DG_CurrentGroupID_800AB968;
extern int dword_8009F604;
extern GM_Camera GM_Camera_800B77E8;

int dword_8009F284 = 0;
const char *off_8009F288[8] = {"cb_box11", "cb_box12", "cb_box41", "cb_box42", "cb_box21", "cb_box22", "cb_box41", "cb_box42"};

int BoxCheckMessage_8006195C(Actor_Box *pActor)
{
    CONTROL *pCtrl = pActor->field_44_pCtrl;
    GV_MSG *pMsg;
    int count;
    unsigned short message;

    pCtrl->field_56 = GV_ReceiveMessage_80016620(pCtrl->field_30_scriptData, &pCtrl->field_5C_mesg);
    pMsg = &pCtrl->field_5C_mesg[0];

    for (count = pCtrl->field_56; count > 0; pMsg++, count--)
    {
        /* "段ボール" */
        if (GV_StrCode_80016CCC("\xC3\xCA\xA5\xDC\xA1\xBC\xA5\xEB") == pMsg->message[0])
        {
            message = pMsg->message[1];

            if (message == 1)
            {
                pActor->field_4C_bFound = message;
                return 1;
            }
        }
    }

    return 0;
}

void BoxAct_80061A14(Actor_Box *pActor)
{
    GM_CurrentMap_800AB9B0 =  pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;

    DG_GroupObjs(pActor->field_20.objs, DG_CurrentGroupID_800AB968);

    BoxCheckMessage_8006195C(pActor);
    if ( pActor->field_4C_bFound )
    {
        DG_InvisibleObjs(pActor->field_20.objs);
    }
    else if ( GM_Camera_800B77E8.field_22 && (pActor->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) != 0 )
    {
        DG_InvisibleObjs(pActor->field_20.objs);

        if ( dword_8009F604 != SGT_CB_BOX )
        {
            dword_8009F284 = 1;
            NewSight_80071CDC(SGT_CB_BOX, SGT_CB_BOX, (short*)&dword_8009F284, 1, 0);
        }
    }
    else
    {
        dword_8009F284 = 0;
        DG_VisibleObjs(pActor->field_20.objs);
    }
}

void BoxDie_80061B30(Actor_Box *pActor)
{
    const char **ppName;
    int i;

    GM_FreeObject_80034BF8((OBJECT *)&pActor->field_20);

    ppName = pActor->field_50_ppName;
    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(ppName[i], off_8009F288[i]);
    }

    dword_8009F284 = 0;
}

int BoxGetResources_80061BA0(Actor_Box *pActor, OBJECT *pParent)
{
    OBJECT_NO_ROTS *pObject = &pActor->field_20;
    short currentItem;
    const char **ppName;
    int i;

    GM_InitObjectNoRots_800349B0(pObject, GV_StrCode_80016CCC("cb_box"), 109, 0);

    if (!pActor->field_20.objs)
    {
        return -1;
    }

    pActor->field_20.objs->objs[0].raise = 250;
    GM_ConfigObjectRoot_80034C5C((OBJECT *)pObject, pParent, 0);

    currentItem = GM_CurrentItemId;
    ppName = &off_8009F288[(currentItem - 2) * 2];
    pActor->field_50_ppName = ppName;

    for (i = 0; i < 2; i++)
    {
        EQ_ChangeTexture_80060CE4(off_8009F288[i], ppName[i]);
    }

    return 0;
}

GV_ACT * NewBox_80061C7C(CONTROL *pCtrl, OBJECT *pParent, int unused)
{
    Actor_Box *pActor = (Actor_Box *)GV_NewActor_800150E4(6, sizeof(Actor_Box));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)BoxAct_80061A14,
                                  (TActorFunction)BoxDie_80061B30, "box.c");
        if (BoxGetResources_80061BA0(pActor, pParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pParent = pParent;
    }

    return &pActor->field_0_actor;
}
