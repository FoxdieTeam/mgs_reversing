#include "linker.h"
#include "stnsight.h"
#include "Game/game.h"

// stinger first person HUD

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}

#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_8006837C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068420.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068798.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068A24.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_helper_80068BF4.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_act_80068D0C.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_kill_80068ED8.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80068F74.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069100.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069184.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_helper_80069234.s")
#pragma INCLUDE_ASM("asm/Weapon/stnsight_init_helper_800692D0.s")

extern const char aStnsightC[]; // = "stnsight.c"

// re-declare to force GP usage
extern int dword_800AB8EC;
int        SECTION(".dword_800AB8EC") dword_800AB8EC;

Actor_stnsight * NewStnSight_800693E0(int type)
{
    Actor_stnsight *actor;

    if ((short)dword_800AB8EC != 0) {
        return 0;
    }

    actor = (Actor_stnsight *)GV_NewActor_800150E4(7, sizeof(Actor_stnsight));

    if (actor) {
        GV_SetNamedActor_8001514C(&actor->actor, (TActorFunction)stnsight_act_80068D0C, (TActorFunction)stnsight_kill_80068ED8, aStnsightC);

        if (stnsight_init_helper_800692D0(actor, type) < 0) {
            GV_DestroyActor_800151C8(&actor->actor);
            return 0;
        }

        *(short *)&dword_800AB8EC = 1;
    }

    return actor;
}
