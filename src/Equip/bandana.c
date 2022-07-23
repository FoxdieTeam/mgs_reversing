#include "bandana.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98   gGameState_800B4D98;

extern short                d_800AB9EC_mag_size;

extern const char aBandanaC[];

extern void bandana_80061D14(OBJECT *param_1);
#pragma INCLUDE_ASM("asm/Equip/bandana_80061D14.s")

/*
short SECTION(".snake_mag_size_800BDCB8") snake_mag_size_800BDCB8;
short SECTION(".snake_mag_size_800BDCB8") snake_weapon_idx_800BDCBA;
short SECTION(".snake_mag_size_800BDCB8") snake_weapon_max_ammo_800BDCBC;
*/

// not matching yet
#pragma INCLUDE_ASM("asm/Equip/bandana_act_80061DA0.s")
void bandana_act_80061DA0(Actor_bandana *pActor);

/*
void bandana_act_80061DA0(Actor_bandana *pActor)
{
    if ( snake_weapon_idx_800BDCBA >= 0 )
    {
        if ( gGameState_800B4D98.field_22_weapon_states[gGameState_800B4D98.field_1C_equipped_weapon] < snake_weapon_max_ammo_800BDCBC )
        {
            gGameState_800B4D98.field_22_weapon_states[snake_weapon_idx_800BDCBA] = snake_weapon_max_ammo_800BDCBC;
        }
        if ( d_800AB9EC_mag_size < snake_mag_size_800BDCB8 )
        {
            d_800AB9EC_mag_size = snake_mag_size_800BDCB8;
        }
    }
}
*/

void bandana_kill_80061E1C(Actor_bandana *pActor)
{
    bandana_80061D14(pActor->field_20_pParent);
}

Actor* NewBandana_80061E40(GM_Control* pCtrl, OBJECT *pParent)
{
    Actor_bandana *pActor = (Actor_bandana *)GV_NewActor_800150E4(7, sizeof(Actor_bandana));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(
            &pActor->field_0_actor,
            (TActorFunction)bandana_act_80061DA0,
            (TActorFunction)bandana_kill_80061E1C,
            aBandanaC);
        pActor->field_20_pParent = pParent;
        bandana_80061D14(pParent);
    }
    return &pActor->field_0_actor;
}
