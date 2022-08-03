#include "menuman.h"
#include "linker.h"
#include "gcl.h"
#include "Script_tbl_map_8002BB44.h"

extern GameState_800B4D98   gGameState_800B4D98;

extern int  GM_GameStatus_800AB3CC;
extern short GM_O2_800ABA34;

extern BarConfig gSnakeLifeBarConfig_8009E5F4;
extern BarConfig gSnakeO2BarConfig_8009E600;

// force gp
extern int           dword_800ABAE8;
int SECTION(".sbss") dword_800ABAE8;

extern int gSnakeLifeYPos_800ABAF0;
int SECTION(".sbss") gSnakeLifeYPos_800ABAF0;

extern int gTakeDamageCounter_800AB5FC;
int SECTION(".sbss") gTakeDamageCounter_800AB5FC;

unsigned int menu_bar_draw_8003ED4C(Menu_Prim_Buffer *pBuffer, int xpos, int ypos, int hp1, int hp2, int maxHp, BarConfig *pConfig);

void sub_8003ECC0(void)
{
  dword_800ABAE8 = 0;
}

int menu_bars_update_helper_8003ECCC(MenuMan_MenuBars *pBars)
{
    short snakeHp = pBars->field_6_snake_hp;
    if ( snakeHp == gGameState_800B4D98.field_16_snake_current_health )
    {
        pBars->field_A_k10_decrement = 10;
        return 0;
    }
    else
    {
        if ( gGameState_800B4D98.field_16_snake_current_health < snakeHp )
        {
            if ( pBars->field_A_k10_decrement == 0 )
            {
                pBars->field_6_snake_hp = snakeHp - 64;
            }
            else
            {
                --pBars->field_A_k10_decrement;
            }
        }
        
        if ( pBars->field_6_snake_hp < gGameState_800B4D98.field_16_snake_current_health )
        {
            pBars->field_6_snake_hp = gGameState_800B4D98.field_16_snake_current_health;
        }
        return 1;
    }
}

#pragma INCLUDE_ASM("asm/menu_bar_draw_8003ED4C.s")

void menu_bars_update_helper2_8003F30C(Menu_Prim_Buffer *ot, MenuMan_MenuBars *pBars)
{
    BarConfig *pBar = &gSnakeLifeBarConfig_8009E5F4;
    gSnakeLifeYPos_800ABAF0 = pBars->field_4_bar_y;

    if ( (GM_GameStatus_800AB3CC & 0x2000000) != 0 )
    {
        gTakeDamageCounter_800AB5FC = 8;
        GM_GameStatus_800AB3CC &= ~0x2000000u;
    }

    if ( gTakeDamageCounter_800AB5FC > 0 )
    {
        --gTakeDamageCounter_800AB5FC;
        pBar = UNTAG_PTR(BarConfig, pBar); // pointer flag to make it render in red
    }

    menu_bar_draw_8003ED4C(
        ot,
        pBars->field_2_bar_x,
        pBars->field_4_bar_y,
        pBars->field_6_snake_hp,
        gGameState_800B4D98.field_16_snake_current_health,
        gGameState_800B4D98.field_18_snake_max_health,
        pBar);

    if ( pBars->field_1_O2_hp )
    {
        menu_bar_draw_8003ED4C(
            ot,
            pBars->field_2_bar_x,
            pBars->field_4_bar_y + 12,
            GM_O2_800ABA34,
            GM_O2_800ABA34,
            1024,
            &gSnakeO2BarConfig_8009E600);
    }
}

unsigned int menu_8003F408(Menu_Prim_Buffer *ot, int ypos, int a3, int a4, int a5, BarConfig *pConfig)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    return menu_bar_draw_8003ED4C(ot, 16, ypos + gSnakeLifeYPos_800ABAF0 - 16, a3, a4, a5, pConfig);
}

unsigned int menu_8003F464(Menu_Prim_Buffer *ot, int xpos, int ypos, int a4, int a5, int a6, BarConfig *pBarConfig)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    return menu_bar_draw_8003ED4C(ot, xpos, ypos + gSnakeLifeYPos_800ABAF0 - 16, a4, a5, a6, pBarConfig);
}

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
