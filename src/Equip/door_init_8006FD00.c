#include "linker.h"
#include "door.h"
#include "gcl.h"

extern int door_where_8009F5F4;

extern const char aDoorC[]; // "door.c";

int door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where);
void door_act_8006F318(struct Actor_Door *pDoor);
void door_kill_8006F718(struct Actor_Door *pDoor);

Actor *door_init_8006FD00(int name, int where, int argc, char **argv)
{
    int t_param_v;
    struct Actor_Door *pDoor;

    if (GCL_GetParam_80020968('t'))
    {
        t_param_v = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        t_param_v = 1;
    }

    pDoor = (struct Actor_Door *)GV_ActorAlloc_800150e4(5, sizeof(struct Actor_Door) + (sizeof(struct Actor_Door_TParam) * (t_param_v - 1)));

    door_where_8009F5F4 = 0;

    if (pDoor)
    {

        GV_ActorInit_8001514c(&pDoor->field_0_actor, (TActorFunction)door_act_8006F318, (TActorFunction)door_kill_8006F718, aDoorC);

        pDoor->field_E4_t_param_v = t_param_v;

        if (door_loader_8006FA60(pDoor, name, where) < 0)
        {
            GV_ActorDelayedKill_800151c8(&pDoor->field_0_actor);
            return 0;
        }
    }
    return &pDoor->field_0_actor;
}