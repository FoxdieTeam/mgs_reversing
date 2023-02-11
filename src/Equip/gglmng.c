#include "gglmng.h"
#include "gglsight.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/linkvarbuf.h"

// Goggle Manager?
// used by all items and weapons that can go first person in order to transition into their first person modes?

extern const char         aGglmngC[];
extern GM_Camera GM_Camera_800B77E8;
extern int                GM_PlayerStatus_800ABA50;
extern int                dword_8009F46C;

void gglmng_act_800778B4(Actor_gglmng *pActor)
{
    if (GM_Camera_800B77E8.field_22 != 0)
    {
        if (GM_CurrentWeaponId == WEAPON_STINGER ||
            GM_CurrentWeaponId == WEAPON_PSG1 || dword_8009F46C == 1 ||
            (GM_PlayerStatus_800ABA50 & 0x4000000) != 0)
        {
            pActor->field_24 = 0;
            if (pActor->field_28_pGglsight)
            {
                GV_DestroyOtherActor_800151D8(pActor->field_28_pGglsight);
                pActor->field_28_pGglsight = 0;
            }
        }
        else
        {
            pActor->field_24++;
            if (pActor->field_24 == 8)
            {
                pActor->field_28_pGglsight = (Actor *)gglsight_init_80078520(pActor->field_20_type);
            }
        }
    }
    else
    {
        if (pActor->field_28_pGglsight)
        {
            GV_DestroyOtherActor_800151D8(pActor->field_28_pGglsight);
            pActor->field_28_pGglsight = 0;
        }
        pActor->field_24 = 0;
    }
}

void gglmng_kill_80077988(Actor_gglmng *pActor)
{
    if (pActor->field_28_pGglsight)
    {
        GV_DestroyOtherActor_800151D8(pActor->field_28_pGglsight);
    }
}

Actor_gglmng *gglmng_init_800779B8(int type)
{
    Actor_gglmng *pActor; // $s0

    pActor = (Actor_gglmng *)GV_NewActor_800150E4(7, sizeof(Actor_gglmng));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)gglmng_act_800778B4,
                                  (TActorFunction)gglmng_kill_80077988, aGglmngC);
        pActor->field_20_type = type;
        pActor->field_24 = 0;
        pActor->field_28_pGglsight = 0;
    }
    return pActor;
}
