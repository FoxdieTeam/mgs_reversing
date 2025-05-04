#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "sd/g_sound.h"

typedef struct _LifeUpWork
{
    GV_ACT actor;
    int    max;
    int    f24;
    int    f28;
    int    proc;
    char   pad[0x4];
    int    f34;
    int    time;
} LifeUpWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL2

STATIC void LifeUpAct_800DF1A8(LifeUpWork *work)
{
    GM_GameStatus |= PLAYER_MENU_DISABLE;

    if (work->f34 <= 0)
    {
        GM_SnakeMaxHealth += work->f28;
        if (GM_SnakeMaxHealth > work->max)
        {
            GM_SnakeMaxHealth = work->max;
        }
    }

    if (work->f34 < work->f24)
    {
        work->f24 = work->f34;
    }

    GM_SnakeCurrentHealth += work->f24;
    work->f34 -= work->f24;

    if (GM_SnakeCurrentHealth > work->max)
    {
        GM_SnakeCurrentHealth = work->max;
    }

    if (GM_SnakeCurrentHealth > GM_SnakeMaxHealth)
    {
        GM_SnakeMaxHealth = GM_SnakeCurrentHealth;
    }

    work->time += GV_PassageTime;
    if (work->time >= 12)
    {
        work->time -= 12;
        GM_SeSet(NULL, SE_LIFE_UP);
    }

    if (GM_SnakeMaxHealth == work->max)
    {
        if (work->proc != 0)
        {
            GCL_ExecProc(work->proc, NULL);
        }

        GV_DestroyActor(&work->actor);
    }
}

STATIC void LifeUpDie_800DF318(LifeUpWork *work)
{
    GM_GameStatus &= ~(STATE_PADRELEASE | STATE_SHOW_LIFEBAR);
}

STATIC int LifeUpGetResources_800DF334(LifeUpWork *work, int name, int map)
{
    if (GCL_GetOption('m'))
    {
        work->max = GCL_StrToInt(GCL_GetParamResult());
    }

    if (GCL_GetOption('e'))
    {
        work->proc = GCL_StrToInt(GCL_GetParamResult());
    }

    if (GCL_GetOption('c'))
    {
        work->f24 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f24 = 8;
    }

    if (GCL_GetOption('l'))
    {
        work->f34 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f34 = work->max - GM_SnakeCurrentHealth;
    }

    work->f28 = work->f24;

    GM_GameStatus |= PLAYER_SECOND_AVAILABLE | PLAYER_MENU_DISABLE;
    return 0;
}

void *NewLifeUp_800DF428(int name, int where)
{
    LifeUpWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(LifeUpWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, LifeUpAct_800DF1A8, LifeUpDie_800DF318, "life_up.c");

        if (LifeUpGetResources_800DF334(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
