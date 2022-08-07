#include "grenade.h"
#include "Game/target.h"
#include "Game/object.h"

// grenade/stun/chaff (in hands)

extern const char     aGrenadeC[]; // = "grenade.c"
extern short          d_800AB9EC_mag_size;
extern short          dword_800ABA2C;
extern unsigned short dword_8009F3E4[];

extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR stru_800ABA10;
void           grenade_800663A0(void)
{
    GM_Target GStack88;
    SVECTOR   local_10;

    local_10.vz = 0xfa;
    local_10.vy = 0xfa;
    local_10.vx = 0xfa;
    GM_SetTarget_8002DC74(&GStack88, 4, 0, &local_10);
    GM_Target_8002DCCC(&GStack88, 3, 1, 0x40, -1, (SVECTOR *)&DG_ZeroVector_800AB39C);
    GM_Target_SetVector_8002D500(&GStack88, (SVECTOR *)&stru_800ABA10);
    sub_8002D7DC(&GStack88);
}

#pragma INCLUDE_ASM("asm/Weapon/grenade_act_8006641C.s") // 1144 bytes

void grenade_kill_80066894(Actor_Grenade *grenade)
{
    GM_FreeObject_80034BF8(&grenade->f28_obj);
}

int grenade_loader_800668B4(Actor_Grenade *actor_grenade, OBJECT *parent_obj, int num_parent, int index)
{
    OBJECT *obj = &actor_grenade->f28_obj;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, dword_8009F3E4[index], 0x6d, 0);

    if (!obj->objs)
        return -1;

    GM_ConfigObjectRoot_80034C5C(obj, parent_obj, num_parent);
    return 0;
}

Actor_Grenade *grenade_init_80066944(Unknown_Grenade_Member *a1, OBJECT *parent_obj, int num_parent, int a4, int a5,
                                     int index)
{
    Actor_Grenade *actor_grenade = (Actor_Grenade *)GV_NewActor_800150E4(6, sizeof(Actor_Grenade));

    if (actor_grenade)
    {
        GV_SetNamedActor_8001514C((Actor *)actor_grenade, (TActorFunction)&grenade_act_8006641C,
                                  (TActorFunction)&grenade_kill_80066894, aGrenadeC);
        if (grenade_loader_800668B4(actor_grenade, parent_obj, num_parent, index) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)actor_grenade);
            return 0;
        }

        actor_grenade->f20 = (int)a1->a;
        actor_grenade->f24_parent_obj = parent_obj;
        actor_grenade->f4c = num_parent;
        actor_grenade->f50 = a4;
        actor_grenade->f5c = 120;
        actor_grenade->f60 = index;
        actor_grenade->f64 = 0;
        actor_grenade->f54 = *a1;
    }

    dword_800ABA2C = 0;
    d_800AB9EC_mag_size = 0;

    return actor_grenade;
}

Actor_Grenade *grenade_create_80066A4C(Unknown_Grenade_Member *a1, OBJECT *a2, int num_parent, int a4, int a5)
{
    return grenade_init_80066944(a1, a2, num_parent, a4, a5, 0);
}

Actor_Grenade *NewStanGrenade_80066A74(Unknown_Grenade_Member *a1, OBJECT *obj, int num_parent, int a4, int a5)
{
    return grenade_init_80066944(a1, obj, num_parent, a4, a5, 1);
}

Actor_Grenade *NewChaffGrenade_80066AA0(Unknown_Grenade_Member *a1, OBJECT *a2, int num_parent, int a4, int a5)
{
    return grenade_init_80066944(a1, a2, num_parent, a4, a5, 2);
}

Actor_Grenade *NewTimerBomb_80066ACC(Unknown_Grenade_Member *a1, OBJECT *a2, int num_parent, int a4, int a5)
{
    return grenade_init_80066944(a1, a2, num_parent, a4, a5, 3);
}
