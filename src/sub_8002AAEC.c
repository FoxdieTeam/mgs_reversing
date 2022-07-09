#include "linker.h"

extern void GM_Sound_80032C48(int, int);
extern void MENU_JimakuClear_80049518(void);
extern int  GM_GameStatus_800AB3CC;
extern int GV_PauseLevel_800AB928;

int SECTION(".sbss") GM_GameStatus_800AB3CC;

void sub_8002AAEC(void)
{
    GV_PauseLevel_800AB928 &= 0xfffffffd;
    GM_Sound_80032C48(0x1ffff02, 0);
    MENU_JimakuClear_80049518();
    GM_GameStatus_800AB3CC &= 0xffffff7f;
    return;
}
