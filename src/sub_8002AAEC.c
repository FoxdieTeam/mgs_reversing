#include "linker.h"
#include "Game/game.h"
#include "Menu/menuman.h"

extern int GM_GameStatus_800AB3CC;
extern int GV_PauseLevel_800AB928;

int SECTION(".sbss") GM_GameStatus_800AB3CC;

void sub_8002AAEC(void)
{
    GV_PauseLevel_800AB928 &= ~2u;
    GM_Sound_80032C48(0x1ffff02, 0);
    menu_JimakuClear_80049518();
    GM_GameStatus_800AB3CC &= ~0x80u;
}
