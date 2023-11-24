#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

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

extern int GM_GameStatus_800AB3CC;
extern int GV_PassageTime_800AB924;

#define EXEC_LEVEL 2

void LifeUpAct_800DF1A8(LifeUpWork *work)
{
    GM_GameStatus_800AB3CC |= PLAYER_PREVENT_WEAPON_ITEM_SWITCH;

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

    work->time += GV_PassageTime_800AB924;
    if (work->time >= 12)
    {
        work->time -= 12;
        GM_SeSet_80032858(NULL, 126);
    }

    if (GM_SnakeMaxHealth == work->max)
    {
        if (work->proc != 0)
        {
            GCL_ExecProc_8001FF2C(work->proc, NULL);
        }

        GV_DestroyActor_800151C8(&work->actor);
    }
}

void LifeUpDie_800DF318(LifeUpWork *work)
{
    GM_GameStatus_800AB3CC &= ~(PLAYER_CAN_USE_CONTROLLER_PORT_2 | PLAYER_PREVENT_WEAPON_ITEM_SWITCH);
}

int LifeUpGetResources_800DF334(LifeUpWork *work, int name, int map)
{
    if (GCL_GetOption_80020968('m'))
    {
        work->max = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('e'))
    {
        work->proc = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('c'))
    {
        work->f24 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f24 = 8;
    }

    if (GCL_GetOption_80020968('l'))
    {
        work->f34 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f34 = work->max - GM_SnakeCurrentHealth;
    }

    work->f28 = work->f24;

    GM_GameStatus_800AB3CC |= PLAYER_CAN_USE_CONTROLLER_PORT_2 | PLAYER_PREVENT_WEAPON_ITEM_SWITCH;
    return 0;
}

GV_ACT * NewLifeUp_800DF428(int name, int where)
{
    LifeUpWork *work;

    work = (LifeUpWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(LifeUpWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)LifeUpAct_800DF1A8, (TActorFunction)LifeUpDie_800DF318, "life_up.c");

        if (LifeUpGetResources_800DF334(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
