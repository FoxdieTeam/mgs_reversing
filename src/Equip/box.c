#include "box.h"
#include "map/map.h"
#include "Thing/sight.h"

extern const char aBoxC[];
extern int DG_CurrentGroupID_800AB968;
extern int dword_8009F604;
extern int dword_8009F284;
extern GM_Camera GM_Camera_800B77E8;

#pragma INCLUDE_ASM("asm/Equip/BoxCheckMessage_8006195C.s") // 184 bytes

void BoxAct_80061A14(Actor_Box *pActor)
{
    GM_CurrentMap_800AB9B0 =  pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;

    DG_SetObjectGroupId(pActor->field_20.objs, DG_CurrentGroupID_800AB968);

    BoxCheckMessage_8006195C(pActor);
    if ( pActor->field_4C_bFound )
    {
        pActor->field_20.objs->flag |= 0x80u;
    }
    else if ( GM_Camera_800B77E8.field_22 && (pActor->field_48_pParent->objs->flag & 0x80) != 0 )
    {
        pActor->field_20.objs->flag |= 0x80u;
        if ( dword_8009F604 != 58025 )
        {
            dword_8009F284 = 1;
            NewSight_80071CDC(58025, 58025, (short*)&dword_8009F284, 1, 0);
        }
    }
    else
    {
        dword_8009F284 = 0;
        pActor->field_20.objs->flag &= ~0x80u;
    }
}

#pragma INCLUDE_ASM("asm/Equip/BoxDie_80061B30.s")          // 112 bytes
#pragma INCLUDE_ASM("asm/Equip/BoxGetResources_80061BA0.s") // 220 bytes

Actor *NewBox_80061C7C(GM_Control *pCtrl, OBJECT *pObj)
{
    Actor_Box *pActor = (Actor_Box *)GV_NewActor_800150E4(6, sizeof(Actor_Box));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)BoxAct_80061A14,
                                  (TActorFunction)BoxDie_80061B30, aBoxC);
        if (BoxGetResources_80061BA0(pActor, pObj) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pParent = pObj;
    }
    return &pActor->field_0_actor;
}
