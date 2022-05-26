#include "grenade.h"

extern const char aGrenadeC[];  // = "grenade.c"
extern short dword_800AB9EC;
extern short dword_800ABA2C;

extern int grenade_act_8006641C(int a1);
extern int grenade_kill_80066894(int a1);

extern struct Actor *GV_NewActor_800150E4(int level, int memSize);
extern int grenade_loader_800668B4(Actor_Grenade *actor_grenade, OBJECT *parent_obj, int num_parent, int index);
extern void GV_SetNamedActor_8001514C(Actor *pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown, const char *pActorName);

Actor_Grenade *grenade_init_80066944(Unknown_Grenade_Member *a1, OBJECT *parent_obj, int num_parent, int a4, int a5, int index)
{
    Actor_Grenade *actor_grenade = (Actor_Grenade*)GV_NewActor_800150E4(6, sizeof(Actor_Grenade));

    if (actor_grenade)
    {
        GV_SetNamedActor_8001514C((Actor*)actor_grenade, (TActorFunction)&grenade_act_8006641C, (TActorFunction)&grenade_kill_80066894, aGrenadeC);
        if (grenade_loader_800668B4(actor_grenade, parent_obj, num_parent, index) < 0)
        {
            GV_DestroyActor_800151C8((Actor*)actor_grenade);
            return 0;
        }
        
        actor_grenade->f20 = a1->a;
        actor_grenade->f24_parent_obj = parent_obj;
        actor_grenade->f4c = num_parent;
        actor_grenade->f50 = a4;
        actor_grenade->f5c = 120;
        actor_grenade->f60 = index;
        actor_grenade->f64 = 0;
        actor_grenade->f54 = *a1;
    }
    
    dword_800ABA2C = 0;
    dword_800AB9EC = 0;
    
    return actor_grenade;
}
