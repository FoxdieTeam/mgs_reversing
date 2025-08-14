#include "equip.h"

#include "common.h"
#include "libdg/libdg.h"
#include "linkvar.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_AFTER

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT *parent;
} Work;

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

static void SwapTextures(OBJECT *a1)
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

static void Die(Work *work)
{
    if (!(GM_OptionFlag & OPTION_TUXEDO))
    {
        SwapTextures(work->parent);
    }
}

/*---------------------------------------------------------------------------*/

void *NewBodyArmor(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, NULL, Die, "bodyarm.c");

        work->parent = parent;

        if (!(GM_OptionFlag & OPTION_TUXEDO))
        {
            SwapTextures(parent);
        }
    }

    return (void *)work;
}
