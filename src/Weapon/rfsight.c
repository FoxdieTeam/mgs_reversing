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

    if (GV_PauseLevel_800AB928 || (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF))
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

static short rfsight_flag_800ABBE0[4];

extern GV_PAD GV_PadData_800B05C0[4];

void rfsight_act_800696CC(RfSightWork *work)
{
    GV_PAD *pPad;
    int i;
    rfsight_pfn_t pfn;
    int f28;

    if (work->field_24 < 16000)
    {
        work->field_24++;
    }

    pPad = GV_PadData_800B05C0;

    if (dword_8009F604 != GV_StrCode_80016CCC("rifle"))
    {
        for (i = 0; i < 3; i++)
        {
            work->field_20[i].vx = work->field_20[i].vy = 0;
        }

        work->field_28 = 0;

        pfn = work->field_2c_pfn;
        pfn(42902, GV_StrCode_80016CCC("rifle"), rfsight_flag_800ABBE0, 1, (short *)&work->field_20[0]);
        pfn(42904, GV_StrCode_80016CCC("rifle"), rfsight_flag_800ABBE0, 1, (short *)&work->field_20[1]);
        pfn(42903, GV_StrCode_80016CCC("rifle"), rfsight_flag_800ABBE0, 1, 0);
    }
    else
    {
        f28 = work->field_28++;
        work->field_28 = f28 + 1;

        rfsight_act_helper_80069478(f28, pPad, &work->field_20[0], 3, 1, 8);
        rfsight_act_helper_80069478(f28, pPad, &work->field_20[1], 3, 1, 8);
    }
}

void rfsight_kill_80069850(RfSightWork *work)
{
    rfsight_flag_800ABBE0[0] = 0;
    work->field_24 = 0;
}

extern DVECTOR dvector_800BDD18[3];

int rfsight_init_helper_8006985C(RfSightWork *work)
{
    int i;

    work->field_20 = dvector_800BDD18;

    for (i = 0; i < 3; i++)
    {
        work->field_20[i].vx = work->field_20[i].vy = 0;
    }

    work->field_28 = 0;
    return 0;
}

GV_ACT *NewRifleSight_8006989C(void)
{
    RfSightWork *work = (RfSightWork *)GV_NewActor_800150E4(6, sizeof(RfSightWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)&rfsight_act_800696CC,
                                  (TActorFunction)&rfsight_kill_80069850, "rfsight.c");

        if (rfsight_init_helper_8006985C(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->field_2c_pfn = &NewSight_80071CDC;
    }

    return &work->field_0_actor;
}

GV_ACT *NewRifleSightFast_80069920(void)
{
    RfSightWork *work = (RfSightWork *)GV_NewActor_800150E4(6, sizeof(RfSightWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)&rfsight_act_800696CC,
                                  (TActorFunction)&rfsight_kill_80069850, "rfsight.c");

        if (rfsight_init_helper_8006985C(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->field_2c_pfn = &sight_init_80071EA8;
    }

    return &work->field_0_actor;
}
