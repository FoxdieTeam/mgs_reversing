#include "equip.h"

#include "common.h"
#include "libdg/libdg.h"
#include "Game/linkvarbuf.h"

/*---------------------------------------------------------------------------*/

typedef struct BodyarmWork
{
    GV_ACT  actor;
    OBJECT *parent;
} BodyarmWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC const char *bodyarm_orig_tex[4] = {
    "sna_chest1",
    "sna_chest2",
    "sna_chest3",
    "sna_hip1"
};
STATIC const char *bodyarm_new_tex[4] = {
    "sna_armer1",
    "sna_armer2",
    "sna_armer3",
    "sna_armer4"
};

STATIC void BodyarmSwapTextures(OBJECT *a1)
{
    int i;

    for (i = 0; i < 2; ++i)
    {
        DG_FreeObjPacket(&a1->objs->objs[0], i);
        DG_FreeObjPacket(&a1->objs->objs[1], i);
    }

    for (i = 0; i < 4; i++)
    {
        EQ_ChangeTexture(bodyarm_orig_tex[i], bodyarm_new_tex[i]);
    }
}

STATIC void BodyarmDie(BodyarmWork *work)
{
    if (!(GM_GameStatusFlag & 0x20))
    {
        BodyarmSwapTextures(work->parent);
    }
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewBodyarm(CONTROL *control, OBJECT *parent, int num_parent)
{
    BodyarmWork *work = (BodyarmWork *)GV_NewActor(EXEC_LEVEL, sizeof(BodyarmWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, NULL, (GV_ACTFUNC)BodyarmDie, "bodyarm.c");

        work->parent = parent;

        if (!(GM_GameStatusFlag & 0x20))
        {
            BodyarmSwapTextures(parent);
        }
    }

    return (GV_ACT *)work;
}
