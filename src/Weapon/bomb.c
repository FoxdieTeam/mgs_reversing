#include "bomb.h"
#include "Game/object.h"

extern char aC4Bomb[]; // "c4_bomb"
extern char aBombC[];  // "bomb.c"
extern short d_800AB9EC_mag_size;
extern short dword_800ABA2C;

void bomb_act_8006788C(int param_1);
int bomb_loader_80067A94(Actor_Bomb *actor_bomb, OBJECT *parent_obj, int num_parent);

#pragma INCLUDE_ASM("asm/Weapon/bomb_act_8006788C.s") // 488 bytes

void bomb_kill_80067A74(Actor_Bomb *actor)
{
    GM_FreeObject_80034BF8(&actor->f28_obj);
}

int bomb_loader_80067A94(Actor_Bomb *actor_bomb, OBJECT *parent_obj, int num_parent)
{
    OBJECT *obj = &actor_bomb->f28_obj;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*)obj, GV_StrCode_80016CCC(aC4Bomb), 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Bomb *NewBomb_80067B20(int a1, OBJECT *parent_obj, int num_parent, int a4, int a5)
{
    Actor_Bomb *actor = (Actor_Bomb*)GV_NewActor_800150E4(6, sizeof(Actor_Bomb));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)bomb_act_8006788C, (TActorFunction)bomb_kill_80067A74, aBombC);
        if (bomb_loader_80067A94(actor, parent_obj, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        actor->f20 = a1;
        actor->parent_obj = parent_obj;
        actor->num_parent = num_parent;
        actor->f50 = a4;
        actor->f54 = 0;
        actor->f58 = a5;
    }
    
    dword_800ABA2C = 0;
    d_800AB9EC_mag_size = 0;
    
    return actor;
}
