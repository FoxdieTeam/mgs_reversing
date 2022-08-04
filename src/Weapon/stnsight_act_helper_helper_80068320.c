#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/game.h"

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim)
{
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        addPrim(ot, prim);
    }
}
