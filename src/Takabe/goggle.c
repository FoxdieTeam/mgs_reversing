#include "goggle.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/GM_Control.h"
#include "Game/object.h"
#include "map/map.h"
#include "unknown.h"
#include "scn_mask.h"
#include "Equip/gglmng.h"

// night vision goggles (screen effect)

extern const char aGoggleC[]; // = "goggle.c"
extern const char aGoggles_0[];

extern int GM_GameStatus_800AB3CC;
extern int DG_CurrentGroupID_800AB968;

#pragma INCLUDE_ASM("asm/Takabe/goggle_pal_convert_8007743C.s") // 132 bytes
#pragma INCLUDE_ASM("asm/Takabe/goggle_pal_cb_800774C0.s") // 244 bytes

void goggle_act_800775B4(Actor_goggle *pActor)
{
    DG_OBJS *objs;    // $a1
    int      new_map; // $a0

    if (pActor->field_4C_head_hidden)
    {
        objs = pActor->field_20_obj.objs;
        new_map = pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;
        DG_SetObjectGroupId(pActor->field_20_obj.objs, DG_CurrentGroupID_800AB968);

        GM_CurrentMap_800AB9B0 = new_map;
        if (pActor->field_48_pObj->objs->flag & 0x80)
        {
            pActor->field_20_obj.objs->flag |= 0x80u;
        }
        else
        {
            pActor->field_20_obj.objs->flag &= ~0x80u;
        }
    }

    if (pActor->field_50 == 2)
    {
        GM_GameStatus_800AB3CC |= 4u;
        set_pal_effect_fns_80079194(goggle_pal_cb_800774C0, goggle_pal_convert_8007743C);
        pActor->field_54_pScn_mask = (Actor *)new_scn_mask_8007895C(0);
    }

    if (pActor->field_50 < 11)
    {
        pActor->field_50++;
    }
}

void goggle_kill_800776AC(Actor_goggle *pActor)
{
    GM_GameStatus_800AB3CC &= ~4u;
    DG_ResetExtPaletteMakeFunc_800791E4();

    if (pActor->field_54_pScn_mask)
    {
        GV_DestroyOtherActor_800151D8(pActor->field_54_pScn_mask);
    }

    if (pActor->field_58_actor_unknown)
    {
        GV_DestroyOtherActor_800151D8(pActor->field_58_actor_unknown);
    }

    if (pActor->field_4C_head_hidden)
    {
        GM_FreeObject_80034BF8(&pActor->field_20_obj);
        EQ_VisibleHead_80060DF0(pActor->field_48_pObj, &pActor->field_5C_saved_n_packs, &pActor->field_5E_saved_rise);
    }
}

int goggle_loader_8007773C(Actor_goggle *pActor, OBJECT *pParent)
{
    OBJECT *pObj = &pActor->field_20_obj;
    if (pParent->objs->n_models >= 7)
    {
        GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)pObj, GV_StrCode_80016CCC(aGoggles_0), 0x6D, 0);
        if (!pObj->objs)
        {
            return -1;
        }
        GM_ConfigObjectRoot_80034C5C(pObj, pParent, 6);
        if (pParent->light)
        {
            GM_ConfigObjectLight_80034C44(pObj, pParent->light);
        }
        pActor->field_48_pObj = pParent;
        EQ_InvisibleHead_80060D5C(pParent, &pActor->field_5C_saved_n_packs, &pActor->field_5E_saved_rise);
        pActor->field_4C_head_hidden = 1;
    }

    pActor->field_58_actor_unknown = (Actor *)gglmng_init_800779B8(5);
    if (!pActor->field_58_actor_unknown)
    {
        return -1;
    }

    return 0;
}

Actor_goggle *NewGoggle_8007781C(GM_Control *a1, OBJECT *parent_obj)
{
    Actor_goggle *goggle_actor = (Actor_goggle *)GV_NewActor_800150E4(6, sizeof(Actor_goggle));

    if (goggle_actor)
    {
        GV_SetNamedActor_8001514C(&goggle_actor->field_0_actor, (TActorFunction)&goggle_act_800775B4,
                                  (TActorFunction)&goggle_kill_800776AC, aGoggleC);

        if (goggle_loader_8007773C(goggle_actor, parent_obj) < 0)
        {
            GV_DestroyActor_800151C8(&goggle_actor->field_0_actor);
            return 0;
        }
    }

    goggle_actor->field_44_pCtrl = a1;
    goggle_actor->field_50 = 0;

    return goggle_actor;
}
