#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "game/camera.h"
#include "linkvar.h"

extern GM_Camera GM_Camera_800B77E8;
extern int       dword_8009F46C;

/*---------------------------------------------------------------------------*/
// Goggle Manager

typedef struct GoggleManagerWork
{
    GV_ACT  actor;
    int     type; // type of goggles (5 = night vision, 6 = thermal)
    int     time;
    GV_ACT *sight;
} GoggleManagerWork;

#define EXEC_LEVEL GV_ACTOR_AFTER2

/*---------------------------------------------------------------------------*/

STATIC void GoggleManagerAct(GoggleManagerWork *work)
{
    if (GM_Camera_800B77E8.first_person != 0)
    {
        if (GM_CurrentWeaponId == WP_Stinger ||
            GM_CurrentWeaponId == WP_Rifle ||
            dword_8009F46C == 1 ||
            (GM_PlayerStatus & PLAYER_NOT_SIGHT))
        {
            work->time = 0;

            if (work->sight)
            {
                GV_DestroyOtherActor(work->sight);
                work->sight = NULL;
            }
        }
        else if (++work->time == 8)
        {
            work->sight = NewGoggleSight(work->type);
        }
    }
    else
    {
        if (work->sight)
        {
            GV_DestroyOtherActor(work->sight);
            work->sight = NULL;
        }

        work->time = 0;
    }
}

STATIC void GoggleManagerDie(GoggleManagerWork *work)
{
    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

/*---------------------------------------------------------------------------*/

void *NewGoggleManager(int type)
{
    GoggleManagerWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(GoggleManagerWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, GoggleManagerAct, GoggleManagerDie, "gglmng.c");
        work->type = type;
        work->time = 0;
        work->sight = NULL;
    }

    return (void *)work;
}
