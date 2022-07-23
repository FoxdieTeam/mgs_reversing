#include "gasmask.h"
#include "object.h"
#include "strcode.h"

extern const char aGasmaskC[];
extern const char aGasMask_DUP[];

// TODO: Move to a header
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);

#pragma INCLUDE_ASM("asm/Equip/gasmask_act_800609C0.s")

#pragma INCLUDE_ASM("asm/Equip/gasmask_kill_80060B0C.s")

int gasmask_loader_80060B5C(Actor_gasmask *pActor, OBJECT *pChild, int unit)
{
    OBJECT *obj = &pActor->field_20_obj;

    pActor->field_48_pParent = pChild;
    pActor->field_4C_unit = unit;
    pActor->field_50_count = 0;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, GV_StrCode_80016CCC(aGasMask_DUP), 0x6D, 0);
    if ( !pActor->field_20_obj.objs )
    {
        return -1;
    }
    GM_ConfigObjectRoot_80034C5C(obj, pChild, unit);
    GM_ConfigObjectLight_80034C44(obj, pChild->light);
    EQ_InvisibleHead_80060D5C(pChild, &pActor->field_5A_head_saved_packs, &pActor->field_5C_head_saved_raise);
    pActor->field_54_gmsight = 0;
    return 0;
}

void gasmask_act_800609C0(Actor_gasmask *pActor);
void gasmask_kill_80060B0C(Actor_gasmask *pActor);

Actor* gasmask_init_80060C14(GM_Control *pCtrl, OBJECT *pParent, int unit)
{
    Actor_gasmask *pActor = (Actor_gasmask *)GV_NewActor_800150E4(6, sizeof(Actor_gasmask));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)gasmask_act_800609C0, (TActorFunction)gasmask_kill_80060B0C, aGasmaskC);
        if ( gasmask_loader_80060B5C(pActor, pParent, unit) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
    }
    return &pActor->field_0_actor;
}

