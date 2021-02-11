#include "gcl.h"

extern int  game_state_flags_800AB3CC;

int sub_8003F50C(void)
{
    game_state_flags_800AB3CC &= ~GAME_FLAG_BIT_16;
    return game_state_flags_800AB3CC;
}
