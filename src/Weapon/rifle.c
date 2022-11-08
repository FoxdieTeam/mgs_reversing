#include "rifle.h"
#include "Game/object.h"
#include "Game/game.h"
#include "Game/camera.h"

// PSG1

extern char      aRifle_0[]; // = "rifle"
extern GM_Camera GM_Camera_800B77E8;

#pragma INCLUDE_ASM("asm/Weapon/rifle_act_helper_80067BFC.s") // 356 bytes
#pragma INCLUDE_ASM("asm/Weapon/rifle_act_80067D60.s")        // 952 bytes

void rifle_kill_80068118(Actor_Rifle *rifle)
{
    GM_FreeObject_80034BF8(&rifle->field_20_obj);

    if (gGameState_800B4D98[GM_CurrentWeapon] != WEAPON_PSG1)
    {
        GM_Camera_800B77E8.field_20 = 0x140;
    }

    sd_set_cli_800887EC(0x1ffff21, 0);

    if ((Actor *)rifle->field_5c)
    {
        GV_DestroyOtherActor_800151D8((Actor *)rifle->field_5c);
    }
}

int rifle_loader_80068184(Actor_Rifle *actor_rifle, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_rifle->field_20_obj;

    int id = GV_StrCode_80016CCC(aRifle_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    actor_rifle->field_5c = 0;

    return 0;
}

extern char  aRifleC[]; // = "rifle.c";
extern short d_800AB9EC_mag_size;
extern short d_800ABA2C_ammo;

Actor_Rifle * NewRifle_80068214(GM_Control *pCtrl, OBJECT *pParentObj, int numParent, int a4, int a5)
{
    Actor_Rifle *pActor = (Actor_Rifle *)GV_NewActor_800150E4(6, sizeof(Actor_Rifle));
    int ammo, magSize;

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&rifle_act_80067D60,
                                  (TActorFunction)&rifle_kill_80068118, aRifleC);

        if (rifle_loader_80068184(pActor, pParentObj, numParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }

        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pParentObj = pParentObj;
        pActor->field_4c_numParent = numParent;
        pActor->field_50 = a4;
        pActor->field_54 = a5;
        pActor->field_58 = 0;
    }

    ammo = d_800AB9EC_mag_size ? 6 : 5;
    magSize = gGameState_800B4D98[GM_WeaponRifle];

    if (ammo > 0 && ammo < magSize)
    {
        magSize = ammo;
    }

    d_800ABA2C_ammo = ammo;
    d_800AB9EC_mag_size = magSize;

    return pActor;
}
