#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"

extern int GV_PauseLevel;
extern int dword_8009F604;
extern GV_PAD GV_PadData_800B05C0[4];
extern DVECTOR dvector_800BDD18[3];

/*---------------------------------------------------------------------------*/
// PSG1 Rifle Sight

typedef SightWork *(*rfsight_pfn_t)(int, int, short *, short, short *);

typedef struct _RfSightWork
{
    GV_ACT        actor;
    DVECTOR      *field_20;
    int           field_24;
    int           field_28;
    rfsight_pfn_t func;
} RfSightWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

/*---------------------------------------------------------------------------*/

STATIC void rfsight_act_helper_80069478(int a1, GV_PAD *pad, DVECTOR *axis, int dir, short sens, short max)
{
    unsigned short status;

    if (a1 < 10)
    {
        return;
    }

    status = pad->status;
    GM_CheckShukanReverse(&status);

    if (GV_PauseLevel || (GM_PlayerStatus & PLAYER_PAD_OFF))
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
                    if (axis->vx < max)
                    {
                        axis->vx += sens;
                    }
                }
                else if (axis->vx > -max)
                {
                    axis->vx -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (axis->vx > -max)
                {
                    axis->vx -= sens;
                }
            }
            else if (axis->vx < max)
            {
                axis->vx += sens;
            }
        }
        else if (axis->vx > 0)
        {
            axis->vx -= sens;
        }
        else if (axis->vx < 0)
        {
            axis->vx += sens;
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
                    if (axis->vy < max)
                    {
                        axis->vy += sens;
                    }
                }
                else if (axis->vy > -max)
                {
                    axis->vy -= sens;
                }
            }
            else if (!(dir & 4))
            {
                if (axis->vy > -max)
                {
                    axis->vy -= sens;
                }
            }
            else if (axis->vy < max)
            {
                axis->vy += sens;
            }
        }
        else if (axis->vy > 0)
        {
            axis->vy -= sens;
        }
        else if (axis->vy < 0)
        {
            axis->vy += sens;
        }
    }
}

static short rfsight_flag_800ABBE0[4];

STATIC void RifleSightAct(RfSightWork *work)
{
    GV_PAD *pad;
    int i;
    rfsight_pfn_t pfn;
    int f28;

    if (work->field_24 < 16000)
    {
        work->field_24++;
    }

    pad = GV_PadData_800B05C0;

    if (dword_8009F604 != GV_StrCode("rifle"))
    {
        for (i = 0; i < 3; i++)
        {
            work->field_20[i].vx = work->field_20[i].vy = 0;
        }

        work->field_28 = 0;

        pfn = work->func;
        pfn(42902, GV_StrCode("rifle"), rfsight_flag_800ABBE0, 1, (short *)&work->field_20[0]);
        pfn(42904, GV_StrCode("rifle"), rfsight_flag_800ABBE0, 1, (short *)&work->field_20[1]);
        pfn(42903, GV_StrCode("rifle"), rfsight_flag_800ABBE0, 1, 0);
    }
    else
    {
        f28 = work->field_28++;
        work->field_28 = f28 + 1;

        rfsight_act_helper_80069478(f28, pad, &work->field_20[0], 3, 1, 8);
        rfsight_act_helper_80069478(f28, pad, &work->field_20[1], 3, 1, 8);
    }
}

STATIC void RifleSightDie(RfSightWork *work)
{
    rfsight_flag_800ABBE0[0] = 0;
    work->field_24 = 0;
}

STATIC int RifleSightGetResources(RfSightWork *work)
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

/*---------------------------------------------------------------------------*/

void *NewRifleSight(void)
{
    RfSightWork *work = GV_NewActor(EXEC_LEVEL, sizeof(RfSightWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &RifleSightAct, &RifleSightDie, "rfsight.c");

        if (RifleSightGetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->func = &NewSight_80071CDC;
    }

    return (void *)work;
}

void *NewRifleSightFast(void)
{
    RfSightWork *work = GV_NewActor(EXEC_LEVEL, sizeof(RfSightWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &RifleSightAct, &RifleSightDie, "rfsight.c");

        if (RifleSightGetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->func = &sight_init_80071EA8;
    }

    return (void *)work;
}
