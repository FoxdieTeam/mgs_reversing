// #include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Thing/sight.h"
#include "SD/g_sound.h"
#include "strcode.h"

extern PlayerStatusFlag GM_PlayerStatus;
extern int              dword_8009F604;
extern short            word_800BDCC0;

/*---------------------------------------------------------------------------*/
// Gas Mask sight

typedef struct _GasmaskSightWork
{
    GV_ACT actor;
    int    time;
} GasmaskSightWork;

#define EXEC_LEVEL 6

STATIC void GasmaskSightAct(GasmaskSightWork *work)
{
    if (dword_8009F604 != SGT_MASK)
    {
        NewSight_80071CDC(SGT_MASK, SGT_MASK, &word_800BDCC0, 1, NULL);
    }

    if ((++work->time == 45) && !(GM_PlayerStatus & PLAYER_NOT_SIGHT))
    {
        GM_SeSet2(0, 63, SE_GASMASK_BREATH);
        work->time = 0;
    }
}

STATIC void GasmaskSightDie(GasmaskSightWork *work)
{
    word_800BDCC0 = 0;
}

STATIC int GasmaskSightGetResources(GasmaskSightWork *work, OBJECT *parent, int num_parent)
{
    word_800BDCC0 = 1;
    work->time = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewGasmaskSight(CONTROL *control, OBJECT *parent, int num_parent)
{
    GasmaskSightWork *work;

    word_800BDCC0 = 0;

    work = (GasmaskSightWork *)GV_NewActor(EXEC_LEVEL, sizeof(GasmaskSightWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&GasmaskSightAct,
                         (GV_ACTFUNC)&GasmaskSightDie, "gmsight.c");

        if (GasmaskSightGetResources(work, parent, num_parent) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (GV_ACT *)work;
}
