#include "aam.h"

extern char aAamC[]; // = "aam.c"
extern short dword_800AB9EC;
extern short dword_800ABA2C;

extern void aam_act_800670CC(int param_1);
extern void aam_kill_800673B0(int param_1);
extern int  aam_loader_800673F0(Actor_Aam *a1, OBJECT *a2, int a3);

Actor_Aam *NewAAM_80067480(int a1, OBJECT *parent_object, int num_parent, int a4, int a5)
{
    Actor_Aam *actor_aam = (Actor_Aam*)GV_NewActor_800150E4(6, sizeof(Actor_Aam));
    if (actor_aam)
    {
        GV_SetNamedActor_8001514C(&actor_aam->field_0_actor, (TActorFunction)aam_act_800670CC, (TActorFunction)aam_kill_800673B0, aAamC);
        if (aam_loader_800673F0(actor_aam, parent_object, num_parent) < 0)
        {
            GV_DestroyActor_800151C8(&actor_aam->field_0_actor);
            return 0;
        }

        actor_aam->f44 = a1;
        actor_aam->parent_object = parent_object;
        actor_aam->num_parent = num_parent;
        actor_aam->f50 = a4;
        actor_aam->f54 = a5;
        actor_aam->f58 = 0;
    }
    
    dword_800ABA2C = 0;
    dword_800AB9EC = 0;
    
    return actor_aam;
}