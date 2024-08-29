#include "gglmng.h"
#include "gglsight.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

// Goggle Manager?
// used by all items and weapons that can go first person in order to transition into their first person modes?

extern GM_Camera GM_Camera_800B77E8;
extern int       GM_PlayerStatus_800ABA50;
extern int       dword_8009F46C;

void gglmng_act_800778B4(GglMngWork *work)
{
    if (GM_Camera_800B77E8.field_22 != 0)
    {
        if (GM_CurrentWeaponId == WEAPON_STINGER ||
            GM_CurrentWeaponId == WEAPON_PSG1 || dword_8009F46C == 1 ||
            (GM_PlayerStatus_800ABA50 & 0x4000000) != 0)
        {
            work->field_24 = 0;
            if (work->field_28_pGglsight)
            {
                GV_DestroyOtherActor_800151D8(work->field_28_pGglsight);
                work->field_28_pGglsight = 0;
            }
        }
        else
        {
            work->field_24++;
            if (work->field_24 == 8)
            {
                work->field_28_pGglsight = (GV_ACT *)gglsight_init_80078520(work->field_20_type);
            }
        }
    }
    else
    {
        if (work->field_28_pGglsight)
        {
            GV_DestroyOtherActor_800151D8(work->field_28_pGglsight);
            work->field_28_pGglsight = 0;
        }
        work->field_24 = 0;
    }
}

void gglmng_kill_80077988(GglMngWork *work)
{
    if (work->field_28_pGglsight)
    {
        GV_DestroyOtherActor_800151D8(work->field_28_pGglsight);
    }
}

GV_ACT *gglmng_init_800779B8(int type)
{
    GglMngWork *work; // $s0

    work = (GglMngWork *)GV_NewActor_800150E4(7, sizeof(GglMngWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)gglmng_act_800778B4,
                                  (TActorFunction)gglmng_kill_80077988, "gglmng.c");
        work->field_20_type = type;
        work->field_24 = 0;
        work->field_28_pGglsight = 0;
    }
    return &work->actor;
}
