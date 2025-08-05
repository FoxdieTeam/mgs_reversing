// #include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "thing/sight.h"
#include "sd/g_sound.h"
#include "linkvar.h"

extern int              dword_8009F604;
extern short            word_800BDCC0;

/*---------------------------------------------------------------------------*/
// Gas Mask sight

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define MASK_SIGHT      0x1303  // GV_StrCode("mask")
#define BREATH_DELAY    45

typedef struct _Work
{
    GV_ACT actor;
    int    time;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    if (dword_8009F604 != MASK_SIGHT)
    {
        NewSight(MASK_SIGHT, MASK_SIGHT, &word_800BDCC0, IT_Scope, NULL);
    }

    if ((++work->time == BREATH_DELAY) && !(GM_PlayerStatus & PLAYER_NOT_SIGHT))
    {
        GM_SeSet2(0, 63, SE_GASMASK_BREATH);
        work->time = 0;
    }
}

static void Die(Work *work)
{
    word_800BDCC0 = 0;
}

static int GetResources(Work *work, OBJECT *parent, int num_parent)
{
    word_800BDCC0 = 1;
    work->time = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewGasmaskSight(CONTROL *control, OBJECT *parent, int num_parent)
{
    Work *work;

    word_800BDCC0 = 0;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "gmsight.c");

        if (GetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
