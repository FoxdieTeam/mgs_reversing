#include "libgv/libgv.h"
#include "Game/game.h"

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

extern int      dword_800AB9D4;
extern CONTROL *gSnaControl_800AB9F4;
extern SVECTOR  svector_800ABA10;
extern int      GM_PlayerStatus_800ABA50;

extern const char aAsioto_800C5874[];    // = "asioto.c"
extern const char s16b_dword_800C582C[]; // = " asioto se set err \n"
extern const char s16b_dword_800C5844[]; // = " asioto se noise set err \n"
extern const char s16b_dword_800C5860[]; // = " migi sodesuri %d \n"

#define EXEC_LEVEL 4

#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3278.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C32D8.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3320.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C33A0.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C34F0.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3718.s")

// Functions above are probably not a part of asioto.c

int asioto_800C38AC(Work *work)
{
    Res_Control_unknown *unknown;
    int                  i;
    int                  j;

    unknown = &gSnaControl_800AB9F4->field_10_pStruct_hzd_unknown;
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
    return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_PRONE | PLAYER_MOVING)) == PLAYER_MOVING;
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

    if (!gSnaControl_800AB9F4)
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

                bank = gSnaControl_800AB9F4->field_60_vecs_ary[0].pad & 3;
                GM_SeSet_80032858(&svector_800ABA10, work->se_duct[bank][index]);
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
                GM_SeSet_80032858(&svector_800ABA10, work->se[bank2][index]);

                if (work->noise[bank2] != 0)
                {
                    GM_SetNoise(100, 4, &svector_800ABA10);
                }
            }
            else
            {
                bank = gSnaControl_800AB9F4->field_60_vecs_ary[0].pad & 3;
                GM_SeSet_80032858(&svector_800ABA10, work->se2[bank][index]);
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

    if (GCL_GetParam_80020968('t'))
    {
        while ((result = GCL_Get_Param_Result_80020AA4()))
        {
            *hash++ = GCL_GetNextInt_800209E8(result);
            work->count++;
        }
    }

    i = 0;
    if (GCL_GetParam_80020968('s'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se[i][0] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se[i][1] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }

        if (i != work->count)
        {
            printf(s16b_dword_800C582C);
            return -1;
        }
    }

    work->se2[0][0] = 169;
    work->se2[0][1] = 168;

    i = 0;
    if (GCL_GetParam_80020968('f'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se2[i][0] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se2[i][1] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
    }

    i = 0;
    if (GCL_GetParam_80020968('n'))
    {
        for (; i < work->count; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->noise[i] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
        }
    }

    if (i != work->count)
    {
        printf(s16b_dword_800C5844);
        return -1;
    }

    work->se_duct[0][0] = 5;
    work->se_duct[0][1] = 6;

    i = 0;
    if (GCL_GetParam_80020968('i'))
    {
        for (; i < 4; i++)
        {
            if (!GCL_Get_Param_Result_80020AA4())
            {
                break;
            }

            work->se_duct[i][0] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
            work->se_duct[i][1] = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());

            printf(s16b_dword_800C5860, work->se_duct[i][0]);
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
                                  (TActorFunction)AsiotoDie_800C3B8C, aAsioto_800C5874);
        if (AsiotoGetResources_800C3B94(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
    }

    return (GV_ACT *)work;
}
