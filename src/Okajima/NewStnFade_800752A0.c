#include "idaTypes.h"
#include "actor.h"

extern const char   aStgfdIoC[];

extern int          stgfd_io_act_80074F5C(int *a1);
extern int          stgfd_io_kill_80075164(int a1);
extern int          stgfd_io_loader_80075194(struct Actor *pActor);

struct Actor *NewStnFade_800752A0(void)
{
    struct Actor *actor;

    actor = GV_NewActor_800150E4(3, 0x40);
    if (actor)
    {
        GV_SetNamedActor_8001514C(actor,
                            (TActorFunction)&stgfd_io_act_80074F5C,
                            (TActorFunction)&stgfd_io_kill_80075164,
                            aStgfdIoC);
        if (stgfd_io_loader_80075194(actor) < 0)
        {
            GV_DestroyActor_800151C8(actor);
            return 0;
        }
    }
    return actor;
}
