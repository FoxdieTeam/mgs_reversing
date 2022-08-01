#include "actor.h"
#include "game.h"
#include "GM_Control.h"
#include "object.h"
#include "strcode.h"

extern const char aGoggleC[]; // = "goggle.c"
extern const char aGoggles_0[];

typedef struct Actor_google
{
  Actor field_0_actor;
  OBJECT field_20_obj;
  GM_Control *field_44_pCtrl;
  OBJECT *field_48_pObj;
  int field_4C_head_hidden;
  int field_50;
  Actor *field_54_pScn_mask;
  Actor *field_58_actor_unknown;
  short field_5C_saved_n_packs;
  short field_5E_saved_rise;
} Actor_google;


// TODO: Move to a header
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);

void DG_ResetExtPaletteMakeFunc_800791E4();

extern int goggle_act_800775B4(int a1);
extern void GV_DestroyActor_800151C8(struct Actor *pActor);
extern int  goggle_loader_8007773C(Actor_google *a1, OBJECT *a2);

extern int GM_GameStatus_800AB3CC;

Actor* gglmng_init_800779B8(int type);

#pragma INCLUDE_ASM("asm/Takabe/goggle_8007743C.s") // 132 bytes
#pragma INCLUDE_ASM("asm/Takabe/goggle_act_helper_800774C0.s") // 244 bytes
#pragma INCLUDE_ASM("asm/Takabe/goggle_act_800775B4.s") // 248 bytes

void goggle_kill_800776AC(Actor_google *pActor)
{
    GM_GameStatus_800AB3CC &= ~4u;
    DG_ResetExtPaletteMakeFunc_800791E4();

    if ( pActor->field_54_pScn_mask )
    {
        GV_DestroyOtherActor_800151D8(pActor->field_54_pScn_mask);
    }

    if ( pActor->field_58_actor_unknown )
    {
        GV_DestroyOtherActor_800151D8(pActor->field_58_actor_unknown);
    }

    if ( pActor->field_4C_head_hidden )
    {
        GM_FreeObject_80034BF8(&pActor->field_20_obj);
        EQ_VisibleHead_80060DF0(pActor->field_48_pObj, &pActor->field_5C_saved_n_packs, &pActor->field_5E_saved_rise);
    }
}

int goggle_loader_8007773C(Actor_google *pActor, OBJECT *pParent)
{
    OBJECT *pObj = &pActor->field_20_obj;
    if ( pParent->objs->n_models >= 7 )
    {
        GM_InitObjectNoRots_800349B0(( OBJECT_NO_ROTS * )pObj, GV_StrCode_80016CCC(aGoggles_0), 0x6D, 0);
        if ( !pObj->objs )
        {
            return -1;
        }
        GM_ConfigObjectRoot_80034C5C(pObj, pParent, 6);
        if ( pParent->light )
        {
            GM_ConfigObjectLight_80034C44(pObj, pParent->light);
        }
        pActor->field_48_pObj = pParent;
        EQ_InvisibleHead_80060D5C(pParent, &pActor->field_5C_saved_n_packs, &pActor->field_5E_saved_rise);
        pActor->field_4C_head_hidden = 1;
    }

    pActor->field_58_actor_unknown = gglmng_init_800779B8(5);
    if ( !pActor->field_58_actor_unknown )
    {
        return -1;
    }

    return 0;
}

Actor_google *NewGoggle_8007781C(GM_Control* a1, OBJECT *parent_obj)
{
    Actor_google *goggle_actor = (Actor_google*)GV_NewActor_800150E4(6, sizeof(Actor_google));

    if (goggle_actor)
    {
        GV_SetNamedActor_8001514C(
            &goggle_actor->field_0_actor,
            (TActorFunction)&goggle_act_800775B4,
            (TActorFunction)&goggle_kill_800776AC,
            aGoggleC);

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
