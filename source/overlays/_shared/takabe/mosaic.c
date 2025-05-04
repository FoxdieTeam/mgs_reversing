#include "mosaic.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/map.h"
#include "takabe/thing.h"
#include "strcode.h"

typedef struct MosaicWork
{
    GV_ACT actor;
    int    field_20;
    void  *field_24;
    int    field_28;
    int    field_2C;
    int    field_30;
    int    field_34;
    int    field_38;
    int    field_3C;
    int    field_40;
    int    field_44;
    void  *field_48;
    int    field_4C;
    int    field_50;
    int    field_54;
    int    field_58;
    int    field_5C;
    int    field_60;
    int    field_64;
    int    field_68;
} MosaicWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL3

unsigned short mosaic_mes_list[] = {HASH_ON2, HASH_OFF2};

// This actor is probably the naked Johnny censorship (missing in Integral),
// so a lot of functions here are just stubbed-out and the actor
// doesn't do anything meaningful.

void s00a_mosaic_800DC928()
{
}

void s00a_mosaic_800DC930()
{
}

void MosaicAct_800DC938(MosaicWork *work)
{
    char unused[16];
    int  found;

    if (!GV_PauseLevel)
    {
        found = THING_Msg_CheckMessage(work->field_20, 2, mosaic_mes_list);
        switch (found)
        {
        case 0:
            work->field_60 = 1;
            return;
        case 1:
            work->field_60 = 0;
            break;
        }
    }
}

void MosaicDie_800DC9A0(MosaicWork *work)
{
    void *allocated;

    allocated = work->field_48;
    if (allocated != NULL)
    {
        GV_DelayedFree(allocated);
    }
}

int MosaicGetResources_800DC9D0(MosaicWork *arg0, void *arg1, int arg2, int arg3, int arg4)
{
    arg0->field_58 = 16;
    arg0->field_5C = 16;
    arg0->field_24 = arg1;
    arg0->field_4C = arg2;
    arg0->field_50 = arg3;
    arg0->field_54 = arg3;
    return 0;
}

void *NewMosaicSet_800DC9F4(void *arg0, int arg1, int arg2, int arg3)
{
    MosaicWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(MosaicWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, MosaicAct_800DC938, MosaicDie_800DC9A0, "mosaic.c");
        if (MosaicGetResources_800DC9D0(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_60 = 1;
        work->field_20 = GV_StrCode("Mosaic");
    }
    return (void *)work;
}

void *NewMosaic_800DCABC(int name, int where, int argc, char **argv)
{
    SVECTOR     vec;
    MosaicWork *work;
    int         s, d;

    work = GV_NewActor(EXEC_LEVEL, sizeof(MosaicWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, MosaicAct_800DC938, MosaicDie_800DC9A0, "mosaic.c");
        s = THING_Gcl_GetIntDefault('s', 500);
        d = THING_Gcl_GetIntDefault('d', 4);
        work->field_60 = THING_Gcl_GetInt('f');
        THING_Gcl_GetSVector('p', &vec);
        work->field_3C = vec.vx;
        work->field_40 = vec.vy;
        work->field_44 = vec.vz;
        if (MosaicGetResources_800DC9D0(work, &work->field_28, s, d, 0) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_20 = name;
    }
    return (void *)work;
}
