#include "equip.h"

#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

extern GM_Camera GM_Camera_800B77E8;
extern int       GM_PlayerStatus;
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
        if (GM_CurrentWeaponId == WEAPON_STINGER ||
            GM_CurrentWeaponId == WEAPON_PSG1 ||
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

GV_ACT *NewGoggleManager(int type)
{
    GoggleManagerWork *work;

    work = (GoggleManagerWork *)GV_NewActor(EXEC_LEVEL, sizeof(GoggleManagerWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)GoggleManagerAct,
                         (GV_ACTFUNC)GoggleManagerDie, "gglmng.c");
        work->type = type;
        work->time = 0;
        work->sight = NULL;
    }

    return (GV_ACT *)work;
}
