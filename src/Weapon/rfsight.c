#include "linker.h"
#include "rfsight.h"
#include "chara/snake/sna_init.h"

// PSG1 first person HUD

extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;

void rfsight_act_helper_80069478(int a1, GV_PAD *pPad, DVECTOR *pAxis, int dir, short sens, short max)
{
    unsigned short status;

    if (a1 < 10)
    {
        return;
    }

    status = pPad->status;
    GM_CheckShukanReverse_8004FBF8(&status);

    if (GV_PauseLevel_800AB928 || (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000))
    {
        status = 0;
    }

    if (dir & 1)
    {
        if (status & (PAD_LEFT | PAD_RIGHT))
        {
            if (status & PAD_RIGHT)
            {
                if (!(dir & 4))
                {
                    if (pAxis->vx < max)
                    {
                        pAxis->vx += sens;
                    }
                }
                else if (pAxis->vx > -max)
                {
                    pAxis->vx -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (pAxis->vx > -max)
                {
                    pAxis->vx -= sens;
                }
            }
            else if (pAxis->vx < max)
            {
                pAxis->vx += sens;
            }
        }
        else if (pAxis->vx > 0)
        {
            pAxis->vx -= sens;
        }
        else if (pAxis->vx < 0)
        {
            pAxis->vx += sens;
        }
    }

    if (dir & 2)
    {
        if (status & (PAD_DOWN | PAD_UP))
        {
            if (status & PAD_DOWN)
            {
                if (!(dir & 4))
                {
                    if (pAxis->vy < max)
                    {
                        pAxis->vy += sens;
                    }
                }
                else if (pAxis->vy > -max)
                {
                    pAxis->vy -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (pAxis->vy > -max)
                {
                    pAxis->vy -= sens;
                }
            }
            else if (pAxis->vy < max)
            {
                pAxis->vy += sens;
            }
        }
        else if (pAxis->vy > 0)
        {
            pAxis->vy -= sens;
        }
        else if (pAxis->vy < 0)
        {
            pAxis->vy += sens;
        }
    }
}

extern int dword_8009F604;

extern short word_800ABBE0[2];
short SECTION(".sbss") word_800ABBE0[2];

extern GV_PAD GV_PadData_800B05C0[4];

extern const char aRifle[]; // = "rifle";

void rfsight_act_800696CC(Actor_Rfsight *pActor)
{
    GV_PAD *pPad;
    int i;
    rfsight_pfn_t pfn;
    int f28;

    if (pActor->field_24 < 16000)
    {
        pActor->field_24++;
    }

    pPad = GV_PadData_800B05C0;

    if (dword_8009F604 != GV_StrCode_80016CCC(aRifle))
    {
        for (i = 0; i < 3; i++)
        {
            pActor->field_20[i].vx = pActor->field_20[i].vy = 0;
        }

        pActor->field_28 = 0;

        pfn = pActor->field_2c_pfn;
        pfn(42902, GV_StrCode_80016CCC(aRifle), word_800ABBE0, 1, (short *)&pActor->field_20[0]);
        pfn(42904, GV_StrCode_80016CCC(aRifle), word_800ABBE0, 1, (short *)&pActor->field_20[1]);
        pfn(42903, GV_StrCode_80016CCC(aRifle), word_800ABBE0, 1, 0);
    }
    else
    {
        f28 = pActor->field_28++;
        pActor->field_28 = f28 + 1;

        rfsight_act_helper_80069478(f28, pPad, &pActor->field_20[0], 3, 1, 8);
        rfsight_act_helper_80069478(f28, pPad, &pActor->field_20[1], 3, 1, 8);
    }
}

void rfsight_kill_80069850(Actor_Rfsight *pActor)
{
    word_800ABBE0[0] = 0;
    pActor->field_24 = 0;
}

extern DVECTOR dvector_800BDD18[3];

int rfsight_init_helper_8006985C(Actor_Rfsight *pActor)
{
    int i;

    pActor->field_20 = dvector_800BDD18;

    for (i = 0; i < 3; i++)
    {
        pActor->field_20[i].vx = pActor->field_20[i].vy = 0;
    }

    pActor->field_28 = 0;
    return 0;
}

extern const char aRfsightC[]; // = "rfsight.c"

Actor_Rfsight * NewRifleSight_8006989C(void)
{
    Actor_Rfsight *pActor = (Actor_Rfsight *)GV_NewActor_800150E4(6, sizeof(Actor_Rfsight));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&rfsight_act_800696CC,
                                  (TActorFunction)&rfsight_kill_80069850, aRfsightC);

        if (rfsight_init_helper_8006985C(pActor) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        word_800ABBE0[0] = 1;
        pActor->field_2c_pfn = &NewSight_80071CDC;
    }

    return pActor;
}

Actor_Rfsight * NewRifleSightFast_80069920(void)
{
    Actor_Rfsight *pActor = (Actor_Rfsight *)GV_NewActor_800150E4(6, sizeof(Actor_Rfsight));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&rfsight_act_800696CC,
                                  (TActorFunction)&rfsight_kill_80069850, aRfsightC);

        if (rfsight_init_helper_8006985C(pActor) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        word_800ABBE0[0] = 1;
        pActor->field_2c_pfn = &sight_init_80071EA8;
    }

    return pActor;
}
