#include "asioto.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "asioto.h"

typedef struct _Work
{
    GV_ACT actor;
    int    hash[4];
    int    count;
    int    se[4][2];
    int    se2[4][2];
    int    se_duct[4][2];
    int    noise[4];
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int asioto_800C38AC(Work *work)
{
    HZD_EVT *event;
    int      i;
    int      j;

    event = &GM_PlayerControl->event;
    for (i = 0; i < event->n_triggers; i++)
    {
        for (j = 0; j < work->count; j++)
        {
            if (event->triggers[i] == work->hash[j])
            {
                return j;
            }
        }
    }

    return -1;
}

int asioto_800C392C(Work *work)
{
    return asioto_800C38AC(work);
}

int asioto_800C394C()
{
    return (GM_PlayerStatus & (PLAYER_CAUTION | PLAYER_GROUND | PLAYER_MOVE)) == PLAYER_MOVE;
}

int asioto_800C396C(Work *work)
{
    if (asioto_800C394C() == 0)
        return -1;

    if (dword_800AB9D4 == 8)
    {
        return 0;
    }
    if (dword_800AB9D4 == 0x10)
    {
        return 1;
    }
    return -1;
}

int asioto_800C39B8(void)
{
    if (dword_800AB9D4 == 0xC)
        return 0;
    if (dword_800AB9D4 == 0x18)
        return 1;
    return -1;
}

void AsiotoAct_800C39E8(Work *work)
{
    int index;
    int bank;
    int bank2;

    if (!GM_PlayerControl)
    {
        return;
    }

    do
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            if (GM_PlayerStatus & PLAYER_MOVE)
            {
                index = asioto_800C39B8();
                if (index < 0)
                {
                    return;
                }

                bank = GM_PlayerControl->nearvecs[0].pad & 3;
                GM_SeSet(&GM_PlayerPosition, work->se_duct[bank][index]);
            }
        }
        else
        {
            index = asioto_800C396C(work);
            if (index < 0)
            {
                return;
            }

            bank2 = asioto_800C392C(work);
            if (bank2 >= 0)
            {
                GM_SeSet(&GM_PlayerPosition, work->se[bank2][index]);

                if (work->noise[bank2] != 0)
                {
                    GM_SetNoise(100, 4, &GM_PlayerPosition);
                }
            }
            else
            {
                bank = GM_PlayerControl->nearvecs[0].pad & 3;
                GM_SeSet(&GM_PlayerPosition, work->se2[bank][index]);
            }
        }
    } while (0);
}

void AsiotoDie_800C3B8C(Work *work)
{
}

int AsiotoGetResources_800C3B94(Work *work)
{
    int  *hash;
    char *result;
    int   i;

    hash = work->hash;
    work->count = 0;

    if (GCL_GetOption('t'))
    {
        while ((result = GCL_GetParamResult()))
        {
            *hash++ = GCL_StrToInt(result);
            work->count++;
        }
    }

    i = 0;
    if (GCL_GetOption('s'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_GetParamResult())
            {
                break;
            }

            work->se[i][0] = GCL_StrToInt(GCL_GetParamResult());
            work->se[i][1] = GCL_StrToInt(GCL_GetParamResult());
        }

        if (i != work->count)
        {
            printf(" asioto se set err \n");
            return -1;
        }
    }

    work->se2[0][0] = 169;
    work->se2[0][1] = 168;

    i = 0;
    if (GCL_GetOption('f'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_GetParamResult())
            {
                break;
            }

            work->se2[i][0] = GCL_StrToInt(GCL_GetParamResult());
            work->se2[i][1] = GCL_StrToInt(GCL_GetParamResult());
        }
    }

    i = 0;
    if (GCL_GetOption('n'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_GetParamResult())
            {
                break;
            }

            work->noise[i] = GCL_StrToInt(GCL_GetParamResult());
        }
    }

    if (i != work->count)
    {
        printf(" asioto se noise set err \n");
        return -1;
    }

    work->se_duct[0][0] = 5;
    work->se_duct[0][1] = 6;

    i = 0;
    if (GCL_GetOption('i'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_GetParamResult())
            {
                break;
            }

            work->se_duct[i][0] = GCL_StrToInt(GCL_GetParamResult());
            work->se_duct[i][1] = GCL_StrToInt(GCL_GetParamResult());

            printf(" migi sodesuri %d \n", work->se_duct[i][0]);
        }
    }

    return 0;
}

void *NewAsioto_800C3E08(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, AsiotoAct_800C39E8, AsiotoDie_800C3B8C, "asioto.c");
        if (AsiotoGetResources_800C3B94(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
