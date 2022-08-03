#include "menuman.h"
#include "linker.h"
#include "gcl.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98   gGameState_800B4D98;

// force gp
extern int           dword_800ABAE8;
int SECTION(".sbss") dword_800ABAE8;

extern int  GM_GameStatus_800AB3CC;

extern int gSnakeLifeYPos_800ABAF0;
int SECTION(".sbss") gSnakeLifeYPos_800ABAF0;

extern BarConfig gSnakeLifeBarConfig_8009E5F4;

unsigned int menu_bar_draw_8003ED4C(Menu_Prim_Buffer *pBuffer, int xpos, int ypos, int hp1, int hp2, int maxHp, BarConfig *pConfig);

void sub_8003ECC0(void)
{
  dword_800ABAE8 = 0;
}

#pragma INCLUDE_ASM("asm/menu_bars_update_helper_8003ECCC.s")
#pragma INCLUDE_ASM("asm/menu_bar_draw_8003ED4C.s")
#pragma INCLUDE_ASM("asm/menu_bars_update_helper2_8003F30C.s")
#pragma INCLUDE_ASM("asm/sub_8003F408.s")
#pragma INCLUDE_ASM("asm/sub_8003F464.s")

unsigned int Menu_render_snake_life_bar_8003F4B8(Menu_Prim_Buffer *ot, int xpos, int ypos)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    return menu_bar_draw_8003ED4C(
               ot,
               xpos,
               ypos,
               gGameState_800B4D98.field_16_snake_current_health,
               gGameState_800B4D98.field_16_snake_current_health,
               gGameState_800B4D98.field_18_snake_max_health,
               &gSnakeLifeBarConfig_8009E5F4);
}

void menu_font_kill_helper_8003F50C(void)
{
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_16;
}

#pragma INCLUDE_ASM("asm/menu_bars_update_8003F530.s")
void menu_bars_update_8003F530(Actor_MenuMan *pActor, int **ot);

void menu_bars_init_8003F7E0(Actor_MenuMan *pActor)
{
    MenuMan_MenuBars* pBar;
    
    pActor->m7FnPtrs_field_2C[0] = menu_bars_update_8003F530;
    pActor->field_28_flags |= 1;
  
    pBar = &pActor->field_204_bars;
    pBar->field_6_snake_hp = gGameState_800B4D98.field_16_snake_current_health;
    pBar->field_A_k10_decrement = 10;
    pBar->field_2_bar_x = 16;
    pBar->field_0_state = 0;
    pBar->field_4_bar_y = -48;
    pBar->field_1_O2_hp = 0;
    gSnakeLifeYPos_800ABAF0 = -48;
}


void menu_bars_kill_8003F838(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~1u;
}
