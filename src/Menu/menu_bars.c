#include "linker.h"
#include "gcl.h"

// force gp
extern int           dword_800ABAE8;
int SECTION(".sbss") dword_800ABAE8;

extern int  GM_GameStatus_800AB3CC;

void sub_8003ECC0(void)
{
  dword_800ABAE8 = 0;
}

#pragma INCLUDE_ASM("asm/menu_bars_update_helper_8003ECCC.s")
#pragma INCLUDE_ASM("asm/sub_8003ED4C.s")
#pragma INCLUDE_ASM("asm/menu_bars_update_helper2_8003F30C.s")
#pragma INCLUDE_ASM("asm/sub_8003F408.s")
#pragma INCLUDE_ASM("asm/sub_8003F464.s")
#pragma INCLUDE_ASM("asm/sub_8003F4B8.s")

int menu_font_kill_helper_8003F50C(void)
{
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_16;
    return GM_GameStatus_800AB3CC;
}

#pragma INCLUDE_ASM("asm/menu_bars_update_8003F530.s")
#pragma INCLUDE_ASM("asm/menu_bars_init_8003F7E0.s")

void sub_8003F838(char *param_1)
{
  *(param_1 + 0x28) &= 0xfe;
}
