#include "goggleir.h"
#include "object.h"
#include "strcode.h"

extern char aGoggleirC[]; // = "goggleir.c"

extern void goggleir_act_80078BE0(Actor_GoggleIr* pActor);
extern void goggleir_kill_80078CE4(Actor_GoggleIr* pActor);
extern void GV_DestroyActor_800151C8(struct Actor *pActor);
//extern int  goggleir_loader_80078D8C(Actor_GoggleIr *a1, OBJECT *a2);
Actor* gglmng_init_800779B8(int type);

void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);

#pragma INCLUDE_ASM("asm/goggleir_800789E0.s")
#pragma INCLUDE_ASM("asm/goggleir_act_helper_80078AB8.s")
#pragma INCLUDE_ASM("asm/goggleir_act_80078BE0.s")
#pragma INCLUDE_ASM("asm/goggleir_kill_80078CE4.s")

extern const char aGoggles_1[];

int goggleir_loader_80078D8C(Actor_GoggleIr *pActor, OBJECT *pParent)
{
    OBJECT *pObj = &pActor->field_20_obj;
    if ( pParent->objs->n_models >= 7 )
    {
        GM_InitObjectNoRots_800349B0(( OBJECT_NO_ROTS * )pObj, GV_StrCode_80016CCC(aGoggles_1), 877, 0);
        if ( !pObj->objs )
        {
            return -1;
        }
        GM_ConfigObjectRoot_80034C5C(pObj, pParent, 6);
        if ( pParent->light )
        {
            GM_ConfigObjectLight_80034C44(pObj, pParent->light);
        }
        pActor->field_48_pParent = pParent;
        EQ_InvisibleHead_80060D5C(pParent, &pActor->field_68_savedNPacks, &pActor->field_6A_saved_raise);
        pActor->field_4C_head_hidden = 1;
    }

    pActor->field_64_pGglmng = gglmng_init_800779B8(6);
    if ( !pActor->field_64_pGglmng )
    {
        return -1;
    }
    return 0;
}


Actor_GoggleIr *NewGoggleIr_80078E6C(GM_Control* pCtrl, OBJECT *parent_obj)
{
    Actor_GoggleIr *goggleir_actor = (Actor_GoggleIr*)GV_NewActor_800150E4(6, sizeof(Actor_GoggleIr));

    if (goggleir_actor)
    {
        GV_SetNamedActor_8001514C(
            &goggleir_actor->field_0_actor,
            (TActorFunction)&goggleir_act_80078BE0,
            (TActorFunction)&goggleir_kill_80078CE4,
            aGoggleirC);

        if (goggleir_loader_80078D8C(goggleir_actor, parent_obj) < 0)
        {
            GV_DestroyActor_800151C8(&goggleir_actor->field_0_actor);
            return 0;
        }
    }
    
    goggleir_actor->field_44_pCtrl = pCtrl;
    goggleir_actor->field_50 = 0;
    
    return goggleir_actor;
}
