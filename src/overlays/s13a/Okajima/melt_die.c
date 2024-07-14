#include "libgv/libgv.h"

typedef struct MeltDieWork
{
    GV_ACT  actor;
    int     map;
    int     counter;
    int     counter2;
    SVECTOR svec;

    // Fields below not used in a meaningful way
    int unused[5];
    int svec_vx;
    int svec_vy;
    int svec_vz;
} MeltDieWork;

#define EXEC_LEVEL 5

extern int GM_CurrentMap_800AB9B0;

void AN_Unknown_800DC94C(SVECTOR *pos);

void MeltDieAct_800E0DC8(MeltDieWork *work)
{
    SVECTOR svec;

    GM_CurrentMap_800AB9B0 = work->map;

    if (--work->counter > 0)
    {
        if (work->counter == work->counter / 6 * 6)
        {
            svec = work->svec;
            svec.vx += GV_RandS_800170BC(512);
            svec.vz += GV_RandS_800170BC(512);
            AN_Unknown_800DC94C(&svec);
        }
    }
    else if (--work->counter2 > 0)
    {
        if (!(work->counter & 3))
        {
            svec = work->svec;
            svec.vx += GV_RandS_800170BC(256);
            svec.vz += GV_RandS_800170BC(256);
            AN_Unknown_800DC94C(&svec);
        }
    }
    else
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

int MeltDieGetResources_800E0EE8(MeltDieWork *work, SVECTOR *arg1, int arg2)
{
    work->map = GM_CurrentMap_800AB9B0;

    work->svec = *arg1;

    work->svec_vx = arg1->vx;
    work->svec_vy = arg1->vy;
    work->svec_vz = arg1->vz;

    work->counter = arg2;
    work->counter2 = arg2 / 4;

    return 0;
}

void MeltDieDie_800E0F54(MeltDieWork *work)
{
}

GV_ACT *NewMeltDie_800E0F5C(SVECTOR *arg1, int arg2)
{
    MeltDieWork *work;

    work = (MeltDieWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(MeltDieWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)MeltDieAct_800E0DC8,
                                  (TActorFunction)MeltDieDie_800E0F54, "melt_die.c");
        if (MeltDieGetResources_800E0EE8(work, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
