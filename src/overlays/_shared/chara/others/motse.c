#include "motse.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_AFTER

typedef struct MotseElem
{
    int param1;
    int param2;
} MotseElem;

typedef struct _Work
{
    GV_ACT     actor;
    int        m_opt;
    int        n_elems;
    MotseElem *elems;
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    MotseElem *elem;
    int        i;

    if ((GM_PlayerStatus & PLAYER_ACT_ONLY) && GM_PlayerAction == work->m_opt)
    {
        for (i = 0, elem = work->elems; i < work->n_elems; i++, elem++)
        {
            if (elem->param1 == dword_800AB9D4)
            {
                GM_SeSetMode(&GM_PlayerControl->mov, elem->param2, GM_SEMODE_BOMB);
                return;
            }
        }
    }
}

static void Die(Work *work)
{
    GV_DelayedFree(work->elems);
}

static int GetResources(Work *work, int name)
{
    int            i, count;
    unsigned char *param;
    MotseElem     *elems;

    work->m_opt = GCL_StrToInt(GCL_GetOption('m'));
    work->n_elems = count = GCL_StrToInt(GCL_GetOption('n'));
    work->elems = elems = GV_Malloc(count * sizeof(MotseElem));

    GCL_GetOption('s');

    for (i = 0; (param = GCL_GetParamResult()) && i != count; i++, elems++)
    {
        elems->param1 = GCL_StrToInt(param);
        elems->param2 = GCL_StrToInt(GCL_GetParamResult());
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewMotionSoundEffect(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "motse.c");
        if (GetResources(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
