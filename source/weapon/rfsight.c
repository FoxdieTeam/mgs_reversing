#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "thing/sight.h"
#include "chara/snake/sna_init.h"
#include "linkvar.h"

extern int dword_8009F604;
extern GV_PAD GV_PadData_800B05C0[4];
extern DVECTOR dvector_800BDD18[3];

/*---------------------------------------------------------------------------*/
// PSG1 Rifle Sight

#define EXEC_LEVEL      GV_ACTOR_AFTER

#define RIFLE_SIGHT1    0xa796  // GV_StrCode("rifle1")
#define RIFLE_SIGHT2    0xa797  // GV_StrCode("rifle2")
#define RIFLE_SIGHT3    0xa798  // GV_StrCode("rifle3")

#define HUD_MOVE_DELAY  10

typedef void *(*newsight_t)(int, int, short *, short, short *);

typedef struct _Work
{
    GV_ACT        actor;
    DVECTOR      *field_20;
    int           field_24;
    int           timer;
    newsight_t    func;
} Work;

/*---------------------------------------------------------------------------*/

static void MoveSightElement(int time, GV_PAD *pad, DVECTOR *axis, int dir, short sens, short max)
{
    u_short status;

    if (time < HUD_MOVE_DELAY)
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

/*---------------------------------------------------------------------------*/

static short rfsight_flag_800ABBE0[4];

static void Act(Work *work)
{
    GV_PAD *pad;
    int i;
    newsight_t func;
    int time;

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

        work->timer = 0;

        func = work->func;
        func(RIFLE_SIGHT1, GV_StrCode("rifle"), rfsight_flag_800ABBE0, IT_Scope, (short *)&work->field_20[0]);
        func(RIFLE_SIGHT3, GV_StrCode("rifle"), rfsight_flag_800ABBE0, IT_Scope, (short *)&work->field_20[1]);
        func(RIFLE_SIGHT2, GV_StrCode("rifle"), rfsight_flag_800ABBE0, IT_Scope, NULL);
    }
    else
    {
        time = work->timer++;
        work->timer = time + 1;

        MoveSightElement(time, pad, &work->field_20[0], 3, 1, 8);
        MoveSightElement(time, pad, &work->field_20[1], 3, 1, 8);
    }
}

static void Die(Work *work)
{
    rfsight_flag_800ABBE0[0] = 0;
    work->field_24 = 0;
}

static int GetResources(Work *work)
{
    int i;

    work->field_20 = dvector_800BDD18;

    for (i = 0; i < 3; i++)
    {
        work->field_20[i].vx = work->field_20[i].vy = 0;
    }

    work->timer = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewRifleSight(void)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "rfsight.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->func = &NewSight;
    }

    return (void *)work;
}

void *NewRifleSightFast(void)
{
    Work *work = GV_NewActor(EXEC_LEVEL, sizeof(Work));

    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "rfsight.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        rfsight_flag_800ABBE0[0] = 1;
        work->func = &NewSightFast;
    }

    return (void *)work;
}
