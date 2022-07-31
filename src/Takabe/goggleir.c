#include "goggleir.h"
#include "object.h"
#include "strcode.h"
#include "map.h"

extern char aGoggleirC[]; // = "goggleir.c"
extern const char aGoggles_1[];

extern void GV_DestroyActor_800151C8(struct Actor *pActor);
//extern int  goggleir_loader_80078D8C(Actor_GoggleIr *a1, OBJECT *a2);
Actor* gglmng_init_800779B8(int type);

// TODO: Move to a header
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);

void DG_ResetExtPaletteMakeFunc_800791E4();

extern int GM_GameStatus_800AB3CC;
extern int DG_CurrentGroupID_800AB968;
int SECTION(".dword_800BDFA8") dword_800BDFA8;

#pragma INCLUDE_ASM("asm/goggleir_pal_convert_800789E0.s") // 216 bytes
void goggleir_pal_convert_800789E0(void);

#pragma INCLUDE_ASM("asm/goggleir_pal_cb_80078AB8.s") // 296 bytes
void goggleir_pal_cb_80078AB8(void);

void set_pal_effect_fns_80079194(void* fn1, void* fn2);

Actor* new_scn_mask_8007895C(int type);

void goggleir_act_80078BE0(Actor_GoggleIr *pActor)
{
    int new_map; // $a0
    if ( pActor->field_4C_head_hidden )
    {
        new_map = pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;
        DG_SetObjectGroupId(pActor->field_20_obj.objs, DG_CurrentGroupID_800AB968);
        GM_CurrentMap_800AB9B0 = new_map;
        if ( pActor->field_48_pParent->objs->flag & 0x80 )
        {
            pActor->field_20_obj.objs->flag |= 0x80u;
        }
        else
        {
            pActor->field_20_obj.objs->flag &= ~0x80u;
        }
    }

    if ( pActor->field_50 == 3 )
    {
        set_pal_effect_fns_80079194(
            goggleir_pal_cb_80078AB8,
            goggleir_pal_convert_800789E0);
        GM_GameStatus_800AB3CC |= 8u;
        dword_800BDFA8 = 1;
        pActor->field_54_pScn_mask = new_scn_mask_8007895C(1);
    }

    if ( pActor->field_50 < 11 )
    {
        pActor->field_50++;
    }
}

void goggleir_kill_80078CE4(Actor_GoggleIr *pActor)
{
    GM_GameStatus_800AB3CC &= ~8u;
    DG_ResetExtPaletteMakeFunc_800791E4();

    if (  pActor->field_54_pScn_mask )
    {
        GV_DestroyOtherActor_800151D8( pActor->field_54_pScn_mask);
    }

    if ( pActor->field_58_actor_unknown )
    {
        GV_DestroyOtherActor_800151D8(pActor->field_58_actor_unknown);
    }

    if (  pActor->field_64_pGglmng )
    {
        GV_DestroyOtherActor_800151D8( pActor->field_64_pGglmng);
    }

    if ( pActor->field_4C_head_hidden )
    {
        GM_FreeObject_80034BF8(&pActor->field_20_obj);
        EQ_VisibleHead_80060DF0(pActor->field_48_pParent, &pActor->field_68_savedNPacks, &pActor->field_6A_saved_raise);
    }
}

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
