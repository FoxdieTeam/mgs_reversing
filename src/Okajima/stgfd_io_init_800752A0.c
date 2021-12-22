#include "idaTypes.h"
#include "actor.h"

extern const char   aStgfdIoC[];

extern int          stgfd_io_act_80074F5C(int *a1);
extern int          stgfd_io_kill_80075164(int a1);
extern int          stgfd_io_loader_80075194(struct Actor *pActor);

struct Actor *stgfd_io_init_800752A0(void)
{
    struct Actor *actor;

    actor = GV_ActorAlloc_800150e4(3, 0x40);
    if (actor)
    {
        GV_ActorInit_8001514c(actor,
                            (TActorFunction)&stgfd_io_act_80074F5C,
                            (TActorFunction)&stgfd_io_kill_80075164,
                            aStgfdIoC);
        if (stgfd_io_loader_80075194(actor) < 0)
        {
            GV_ActorDelayedKill_800151c8(actor);
            return 0;
        }
    }
    return actor;
}
