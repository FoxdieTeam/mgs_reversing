#include "gmsight.h"
#include "Game/game.h"
#include "Thing/sight.h"
#include "libgcl/hash.h"

// gas mask first person

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_8009F604;
extern short            word_800BDCC0;

void gmsight_act_800635BC(GasmaskSightWork *work)
{
    if (dword_8009F604 != SGT_MASK)
    {
        NewSight_80071CDC(SGT_MASK, SGT_MASK, &word_800BDCC0, 1, NULL);
    }

    if ((++work->field_20 == 45) && !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
    {
        GM_SeSet2_80032968(0, 63, 114);
        work->field_20 = 0;
    }
}

void gmsight_kill_80063644(GasmaskSightWork *work)
{
    word_800BDCC0 = 0;
}

int gmsight_loader_80063650(GasmaskSightWork *work, int unused, int unused2)
{
    word_800BDCC0 = 1;
    work->field_20 = 0;
    return 0;
}

GasmaskSightWork * NewGasmaskSight_80063668(int unused, int unused2, int unused3)
{
    GasmaskSightWork *work;

    word_800BDCC0 = 0;
    work = (GasmaskSightWork *)GV_NewActor_800150E4(6, sizeof(GasmaskSightWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)&gmsight_act_800635BC,
                                  (TActorFunction)&gmsight_kill_80063644, "gmsight.c");

        if (gmsight_loader_80063650(work, unused2, unused3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
    }

    return work;
}
