#include "idaTypes.h"
#include "actor.h"

extern const char   aDBloodrC[];

extern int          d_bloodr_act_80072C10(int a1);
extern int          d_bloodr_kill_80072BD4(int a1);
extern int          d_bloodr_loader_800730EC(struct Actor *pActor, int a2);

struct Actor *d_bloodr_init_80073148(int arg0)
{
    struct Actor *actor;

    actor = GV_ActorAlloc_800150e4(7, 0xDC);
    if (actor)
    {
        GV_ActorInit_8001514c(actor,
                            (TActorFunction)&d_bloodr_act_80072C10,
                            (TActorFunction)&d_bloodr_kill_80072BD4,
                            aDBloodrC);
        if (d_bloodr_loader_800730EC(actor, arg0) < 0)
        {
            GV_ActorDelayedKill_800151c8(actor);
            return 0;
        }
    }
    return actor;
}
