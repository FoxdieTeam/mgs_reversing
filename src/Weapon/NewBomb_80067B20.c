#include "bomb.h"

extern char aBombC[];
extern short dword_800AB9EC;
extern short dword_800ABA2C;

extern void bomb_act_8006788C(int param_1);
extern void bomb_kill_80067A74(int param_1);

extern int bomb_loader_80067A94(Actor_Bomb *actor_bomb, OBJECT *parent_obj, int num_parent);

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
    dword_800AB9EC = 0;
    
    return actor;
}
