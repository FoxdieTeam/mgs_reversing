#include "idaTypes.h"
#include "actor.h"

extern const char   aDBloodrC[];

extern int          d_bloodr_act_80072C10(int a1);
extern int          d_bloodr_kill_80072BD4(int a1);
extern int          d_bloodr_loader_800730EC(struct Actor *pActor, int a2);

struct Actor *NewKetchap_r_80073148(int arg0)
{
    struct Actor *actor;

    actor = GV_NewActor_800150E4(7, 0xDC);
    if (actor)
    {
        GV_SetNamedActor_8001514C(actor,
                            (TActorFunction)&d_bloodr_act_80072C10,
                            (TActorFunction)&d_bloodr_kill_80072BD4,
                            aDBloodrC);
        if (d_bloodr_loader_800730EC(actor, arg0) < 0)
        {
            GV_DestroyActor_800151C8(actor);
            return 0;
        }
    }
    return actor;
}
