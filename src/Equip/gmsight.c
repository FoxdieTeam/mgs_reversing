#include "gmsight.h"
#include "Game/game.h"
#include "Thing/sight.h"

// gas mask first person

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_8009F604;
extern short            word_800BDCC0;

void gmsight_act_800635BC(Actor_gmsight *pActor)
{
    if (dword_8009F604 != 4867)
    {
        NewSight_80071CDC(4867, 4867, &word_800BDCC0, 1, NULL);
    }

    if ((++pActor->field_20 == 45) && !(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        GM_Sound_80032968(0, 63, 114);
        pActor->field_20 = 0;
    }
}

void gmsight_kill_80063644(Actor_gmsight *pActor)
{
    word_800BDCC0 = 0;
}

int gmsight_loader_80063650(Actor_gmsight *pActor, int unused, int unused2)
{
    word_800BDCC0 = 1;
    pActor->field_20 = 0;
    return 0;
}

extern const char aGmsightC[]; // = "gmsight.c"

Actor_gmsight * NewGasmaskSight_80063668(int unused, int unused2, int unused3)
{
    Actor_gmsight *pActor;

    word_800BDCC0 = 0;
    pActor = (Actor_gmsight *)GV_NewActor_800150E4(6, sizeof(Actor_gmsight));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&gmsight_act_800635BC,
                                  (TActorFunction)&gmsight_kill_80063644, aGmsightC);

        if (gmsight_loader_80063650(pActor, unused2, unused3) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }
    }

    return pActor;
}
