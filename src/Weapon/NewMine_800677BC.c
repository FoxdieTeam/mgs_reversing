#include "mine.h"

extern char aMineC[];   // = "mine.c"
extern short dword_800AB9EC;
extern short dword_800ABA2C;

extern void mine_act_80067558(int param_1);
extern void mine_kill_80067710(int param_1);

extern int mine_loader_80067730(Actor_Mine *actor_mine, OBJECT *parent_obj, int num_parent);

Actor_Mine *mine_init_800677BC(int a1, OBJECT *parent_object, int num_parent, int a4)
{
    Actor_Mine *actor = (Actor_Mine*)GV_NewActor_800150E4(6, sizeof(Actor_Mine));
    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)mine_act_80067558, (TActorFunction)mine_kill_80067710, aMineC);        
        if (mine_loader_80067730(actor, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }
        
        actor->f20 = a1;
        actor->parent_object = parent_object;
        actor->num_parent = num_parent;
        actor->f40 = a4;
        actor->f54 = 0;
    }
    
    dword_800ABA2C = 0;
    dword_800AB9EC = 0;
    
    return actor;
}

