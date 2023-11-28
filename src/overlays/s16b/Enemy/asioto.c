#include "libgv/libgv.h"
#include "Game/game.h"
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

const char aAsiotoSeSetErr[] = " asioto se set err \n";
const char aAsiotoSeNoiseSetErr[] = " asioto se noise set err \n";
const char aMigiSodesuri[] = " migi sodesuri %d \n";
const char aAsiotoC[] = "asioto.c";

extern int      dword_800AB9D4;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PlayerStatus_800ABA50;

#define EXEC_LEVEL 4

int asioto_800C38AC(Work *work)
{
    HZD_EVT *unknown;
    int                  i;
    int                  j;

    unknown = &GM_PlayerControl_800AB9F4->field_10_events;
    for (i = 0; i < unknown->field_6_count; i++)
    {
        for (j = 0; j < work->count; j++)
        {
            if (unknown->field_8_array[i] == work->hash[j])
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
    return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_GROUND | PLAYER_MOVING)) == PLAYER_MOVING;
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

    if (!GM_PlayerControl_800AB9F4)
    {
        return;
    }

    do
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON_DUCT)
        {
            if (GM_PlayerStatus_800ABA50 & PLAYER_MOVING)
            {
                index = asioto_800C39B8();
                if (index < 0)
                {
                    return;
                }

                bank = GM_PlayerControl_800AB9F4->field_60_vecs_ary[0].pad & 3;
                GM_SeSet_80032858(&GM_PlayerPosition_800ABA10, work->se_duct[bank][index]);
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
                GM_SeSet_80032858(&GM_PlayerPosition_800ABA10, work->se[bank2][index]);

                if (work->noise[bank2] != 0)
                {
                    GM_SetNoise(100, 4, &GM_PlayerPosition_800ABA10);
                }
            }
            else
            {
                bank = GM_PlayerControl_800AB9F4->field_60_vecs_ary[0].pad & 3;
                GM_SeSet_80032858(&GM_PlayerPosition_800ABA10, work->se2[bank][index]);
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

    if (GCL_GetOption_80020968('t'))
    {
        while ((result = GCL_Get_Param_Result_80020AA4()))
        {
            *hash++ = GCL_StrToInt_800209E8(result);
            work->count++;
        }
    }

    i = 0;
    if (GCL_GetOption_80020968('s'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se[i][0] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se[i][1] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }

        if (i != work->count)
        {
            printf(aAsiotoSeSetErr);
            return -1;
        }
    }

    work->se2[0][0] = 169;
    work->se2[0][1] = 168;

    i = 0;
    if (GCL_GetOption_80020968('f'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se2[i][0] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se2[i][1] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
    }

    i = 0;
    if (GCL_GetOption_80020968('n'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->noise[i] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
    }

    if (i != work->count)
    {
        printf(aAsiotoSeNoiseSetErr);
        return -1;
    }

    work->se_duct[0][0] = 5;
    work->se_duct[0][1] = 6;

    i = 0;
    if (GCL_GetOption_80020968('i'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se_duct[i][0] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se_duct[i][1] = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());

            printf(aMigiSodesuri, work->se_duct[i][0]);
        }
    }

    return 0;
}

GV_ACT *NewAsioto_800C3E08(int name, int where, int argc, char **argv)
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)AsiotoAct_800C39E8,
                                  (TActorFunction)AsiotoDie_800C3B8C, aAsiotoC);
        if (AsiotoGetResources_800C3B94(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
    }

    return &work->actor;
}
