#include "rifle.h"
#include "Game/object.h"
#include "Game/game.h"
#include "Game/camera.h"

// PSG1

extern char               aRifle_0[]; // = "rifle"
extern GameState_800B4D98 gGameState_800B4D98;
extern GM_Camera   GM_Camera_800B77E8;

#pragma INCLUDE_ASM("asm/Weapon/rifle_act_helper_80067BFC.s") // 356 bytes
#pragma INCLUDE_ASM("asm/Weapon/rifle_act_80067D60.s")        // 952 bytes

void rifle_kill_80068118(Actor_Rifle *rifle)
{
    GM_FreeObject_80034BF8(&rifle->f20_obj);
    if (gGameState_800B4D98.field_1C_equipped_weapon != WEAPON_PSG1)
    {
        GM_Camera_800B77E8.field_20 = 0x140;
    }
    sd_set_cli_800887EC(0x1ffff21, 0);
    if ((Actor *)rifle->f5c)
    {
        GV_DestroyOtherActor_800151D8((Actor *)rifle->f5c);
    }
}

int rifle_loader_80068184(Actor_Rifle *actor_rifle, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_rifle->f20_obj;

    int id = GV_StrCode_80016CCC(aRifle_0);
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, id, WEAPON_FLAG, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    actor_rifle->f5c = 0;

    return 0;
}

#pragma INCLUDE_ASM("asm/Weapon/NewRifle_80068214.s") // 268 bytes
