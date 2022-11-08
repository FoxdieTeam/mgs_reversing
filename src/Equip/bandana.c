#include "bandana.h"
#include "unknown.h"

extern short d_800AB9EC_mag_size;

extern const char aBandanaC[];

extern const char *off_8009F2A8[3];
extern const char *off_8009F2B4[3];

void bandana_80061D14(OBJECT *pObj)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        DG_FreeObjPacket_8001AAD0(&pObj->objs->objs[6], i);
    }

    for (i = 0; i < 3; i++)
    {
        EQ_ChangeTexture_80060CE4(off_8009F2A8[i], off_8009F2B4[i]);
    }
}

/*
short SECTION(".snake_mag_size_800BDCB8") snake_mag_size_800BDCB8;
short SECTION(".snake_mag_size_800BDCB8") snake_weapon_idx_800BDCBA;
short SECTION(".snake_mag_size_800BDCB8") snake_weapon_max_ammo_800BDCBC;
*/

// not matching yet
#pragma INCLUDE_ASM("asm/Equip/bandana_act_80061DA0.s") // 124 bytes

/*
void bandana_act_80061DA0(Actor_bandana *pActor)
{
    if ( snake_weapon_idx_800BDCBA >= 0 )
    {
        if ( gGameState_800B4D98[GM_WeaponBase + gGameState_800B4D98[GM_CurrentWeapon]] < snake_weapon_max_ammo_800BDCBC )
        {
            gGameState_800B4D98[GM_WeaponBase + snake_weapon_idx_800BDCBA] = snake_weapon_max_ammo_800BDCBC;
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

Actor *NewBandana_80061E40(GM_Control *pCtrl, OBJECT *pParent)
{
    Actor_bandana *pActor = (Actor_bandana *)GV_NewActor_800150E4(7, sizeof(Actor_bandana));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)bandana_act_80061DA0,
                                  (TActorFunction)bandana_kill_80061E1C, aBandanaC);
        pActor->field_20_pParent = pParent;
        bandana_80061D14(pParent);
    }
    return &pActor->field_0_actor;
}
