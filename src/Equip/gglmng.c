#include "gglmng.h"

#include "common.h"
#include "gglsight.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

// Goggle Manager
// used by all items and weapons that can go first person in order to transition into their first person modes?

typedef struct GglMngWork
{
    GV_ACT  actor;
    int     type; // type of goggles (5 = night vision, 6 = thermal)
    int     time;
    GV_ACT *sight;
} GglMngWork;

extern GM_Camera GM_Camera_800B77E8;
extern int       GM_PlayerStatus_800ABA50;
extern int       dword_8009F46C;

void GglmngAct_800778B4(GglMngWork *work)
{
    if (GM_Camera_800B77E8.first_person != 0)
    {
        if (GM_CurrentWeaponId == WEAPON_STINGER ||
            GM_CurrentWeaponId == WEAPON_PSG1 ||
            dword_8009F46C == 1 ||
            (GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
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
            work->sight = NewGglsight_80078520(work->type);
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

void GglmngDie_80077988(GglMngWork *work)
{
    if (work->sight)
    {
        GV_DestroyOtherActor(work->sight);
    }
}

GV_ACT *NewGglmng_800779B8(int type)
{
    GglMngWork *work;

    work = (GglMngWork *)GV_NewActor(7, sizeof(GglMngWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)GglmngAct_800778B4,
                         (TActorFunction)GglmngDie_80077988, "gglmng.c");
        work->type = type;
        work->time = 0;
        work->sight = NULL;
    }

    return (GV_ACT *)work;
}
