#include "menuman.h"
#include "linker.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"
#include "Game/linkvarbuf.h"

extern int   GM_GameStatus_800AB3CC;
extern short GM_O2_800ABA34;

extern BarConfig gSnakeLifeBarConfig_8009E5F4;
extern BarConfig gSnakeO2BarConfig_8009E600;

// force gp
extern int dword_800ABAE8;
int        SECTION(".sbss") dword_800ABAE8;

extern int gSnakeLifeYPos_800ABAF0;
int        SECTION(".sbss") gSnakeLifeYPos_800ABAF0;

extern int gTakeDamageCounter_800AB5FC;
int        SECTION(".sbss") gTakeDamageCounter_800AB5FC;

void sub_8003ECC0(void)
{
    dword_800ABAE8 = 0;
}

int menu_life_update_helper_8003ECCC(MenuMan_MenuBars *pBars)
{
    short snakeHp = pBars->field_6_snake_hp;
    if (snakeHp == GM_SnakeCurrentHealth)
    {
        pBars->field_A_k10_decrement = 10;
        return 0;
    }
    else
    {
        if (GM_SnakeCurrentHealth < snakeHp)
        {
            if (pBars->field_A_k10_decrement == 0)
            {
                pBars->field_6_snake_hp = snakeHp - 64;
            }
            else
            {
                --pBars->field_A_k10_decrement;
            }
        }

        if (pBars->field_6_snake_hp < GM_SnakeCurrentHealth)
        {
            pBars->field_6_snake_hp = GM_SnakeCurrentHealth;
        }
        return 1;
    }
}

void menu_life_draw_8003ED4C(MenuPrim *pBuffer, int xpos, int ypos, int hp1, int hp2, int maxHp, BarConfig *pConfig)
{
    TextConfig text_config;
    int        sp28;
    int        sp2C;
    char      *pOt;
    TILE      *pTile;
    TILE      *pTile_2;
    TILE      *pTile_3;
    POLY_G4   *pPoly;
    DR_TPAGE  *pTpage;
    int        temp_fp;
    int        temp_v1;
    int        diff;
    int        width;

    if (GM_GameStatus_800AB3CC & 0x80020400)
    {
        return;
    }

    pOt = pBuffer->mPrimBuf.mOt;

    sp2C = 5 - pConfig->field_A_bar_height;
    temp_fp = ypos + 1;
    sp28 = maxHp / 8;

    text_config.xpos = xpos + 4;
    temp_v1 = text_config.xpos;

    text_config.flags = 0;
    text_config.ypos = ypos + 4;

    if ( !((int)pConfig & 0x80000000) )
    {
        text_config.colour = 0x643030FF;
    }
    else
    {
        text_config.colour = 0x64FFFFFF;
    }

    menu_number_draw_string_80042BF4(pBuffer, &text_config, pConfig->field_0_text);

    width = text_config.xpos - temp_v1 + 2;
    pTile = menu_render_rect_8003DB2C(pBuffer, temp_v1 - 1, text_config.ypos - 1, width, 7, 0);
    setSemiTrans(pTile, 1);

    if (hp1 > maxHp)
    {
        hp1 = maxHp;
    }

    if (hp1 > hp2)
    {
        _NEW_PRIM(pTile_2, pBuffer);

        setTile(pTile_2);

        diff = (hp1 - hp2) / 8;

        pTile_2->x0 = xpos + hp2 / 8;
        pTile_2->y0 = temp_fp;

        pTile_2->w = diff;
        pTile_2->h = sp2C;

        pTile_2->r0 = 200;
        pTile_2->g0 = 0;
        pTile_2->b0 = 0;

        addPrim(pOt, pTile_2);
    }

    _NEW_PRIM(pPoly, pBuffer);

    setXYWH(pPoly, xpos, temp_fp, (hp2 + 7) / 8, sp2C);

    pPoly->r0 = pConfig->field_4_rgb_left[0];
    pPoly->g0 = pConfig->field_4_rgb_left[1];
    pPoly->b0 = pConfig->field_4_rgb_left[2];
    pPoly->r1 = pConfig->field_4_rgb_left[0] + ((pConfig->field_7_rgb_right[0] - pConfig->field_4_rgb_left[0]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->g1 = pConfig->field_4_rgb_left[1] + ((pConfig->field_7_rgb_right[1] - pConfig->field_4_rgb_left[1]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->b1 = pConfig->field_4_rgb_left[2] + ((pConfig->field_7_rgb_right[2] - pConfig->field_4_rgb_left[2]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->r2 = pConfig->field_4_rgb_left[0] + ((pConfig->field_7_rgb_right[0] - pConfig->field_4_rgb_left[0]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->g2 = pConfig->field_4_rgb_left[1] + ((pConfig->field_7_rgb_right[1] - pConfig->field_4_rgb_left[1]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->b2 = pConfig->field_4_rgb_left[2] + ((pConfig->field_7_rgb_right[2] - pConfig->field_4_rgb_left[2]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->r3 = pConfig->field_4_rgb_left[0] + ((pConfig->field_7_rgb_right[0] - pConfig->field_4_rgb_left[0]) * (pPoly->x3 - pPoly->x0)) / 128;
    pPoly->g3 = pConfig->field_4_rgb_left[1] + ((pConfig->field_7_rgb_right[1] - pConfig->field_4_rgb_left[1]) * (pPoly->x3 - pPoly->x0)) / 128;
    pPoly->b3 = pConfig->field_4_rgb_left[2] + ((pConfig->field_7_rgb_right[2] - pConfig->field_4_rgb_left[2]) * (pPoly->x3 - pPoly->x0)) / 128;

    setPolyG4(pPoly);
    addPrim(pOt, pPoly);

    pTile_3 = menu_render_rect_8003DB2C(pBuffer, xpos, temp_fp, sp28, sp2C, 0x181800);
    setSemiTrans(pTile_3, 1);

    menu_render_rect_8003DB2C(pBuffer, xpos - 1, ypos, 1, sp2C + 2, 0);
    menu_render_rect_8003DB2C(pBuffer, xpos, ypos, sp28, 1, 0);
    menu_render_rect_8003DB2C(pBuffer, xpos, ypos + sp2C + 1, sp28, 1, 0);
    menu_render_rect_8003DB2C(pBuffer, xpos + sp28, ypos, 1, sp2C + 2, 0);

    _NEW_PRIM(pTpage, pBuffer);

    setDrawTPage(pTpage, 1, 1, getTPage(0, 0, 960, 256));
    addPrim(pBuffer->mPrimBuf.mOt, pTpage);
}

void menu_life_update_helper2_8003F30C(MenuPrim *ot, MenuMan_MenuBars *pBars)
{
    BarConfig *pBar = &gSnakeLifeBarConfig_8009E5F4;
    gSnakeLifeYPos_800ABAF0 = pBars->field_4_bar_y;

    if ((GM_GameStatus_800AB3CC & 0x2000000) != 0)
    {
        gTakeDamageCounter_800AB5FC = 8;
        GM_GameStatus_800AB3CC &= ~0x2000000u;
    }

    if (gTakeDamageCounter_800AB5FC > 0)
    {
        --gTakeDamageCounter_800AB5FC;
        pBar = UNTAG_PTR(BarConfig, pBar); // pointer flag to make it render in red
    }

    menu_life_draw_8003ED4C(ot,
                           pBars->field_2_bar_x,
                           pBars->field_4_bar_y,
                           pBars->field_6_snake_hp,
                           GM_SnakeCurrentHealth,
                           GM_SnakeMaxHealth,
                           pBar);

    if (pBars->field_1_O2_hp)
    {
        menu_life_draw_8003ED4C(ot,
                               pBars->field_2_bar_x,
                               pBars->field_4_bar_y + 12,
                               GM_O2_800ABA34,
                               GM_O2_800ABA34,
                               1024,
                               &gSnakeO2BarConfig_8009E600);
    }
}

void menu_8003F408(MenuPrim *ot, int ypos, int a3, int a4, int a5, BarConfig *pConfig)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    menu_life_draw_8003ED4C(ot,
                                  16,
                                  ypos + gSnakeLifeYPos_800ABAF0 - 16,
                                  a3,
                                  a4,
                                  a5,
                                  pConfig);
}

void menu_8003F464(MenuPrim *ot, int xpos, int ypos, int a4, int a5, int a6, BarConfig *pBarConfig)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    menu_life_draw_8003ED4C(ot,
                           xpos,
                           ypos + gSnakeLifeYPos_800ABAF0 - 16,
                           a4,
                           a5,
                           a6,
                           pBarConfig);
}

void Menu_render_snake_life_bar_8003F4B8(MenuPrim *ot, int xpos, int ypos)
{
    GM_GameStatus_800AB3CC |= 0x8000u;
    menu_life_draw_8003ED4C(ot,
                           xpos,
                           ypos,
                           GM_SnakeCurrentHealth,
                           GM_SnakeCurrentHealth,
                           GM_SnakeMaxHealth, &gSnakeLifeBarConfig_8009E5F4);
}

void menu_font_kill_helper_8003F50C(void)
{
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_16;
}

void menu_life_update_8003F530(Actor_MenuMan *pActor, unsigned char *pOt)
{
    int               updated;
    MenuMan_MenuBars *pBars;
    int               state;

    updated = menu_life_update_helper_8003ECCC(&pActor->field_204_bars);
    pBars = &pActor->field_204_bars;
    state = pActor->field_2A_state;

    if (GM_O2_800ABA34 < 1024)
    {
        updated = 1;
        pBars->field_1_O2_hp = -106;
    }

    if (state)
    {
        return;
    }

    if (GM_GameStatus_800AB3CC & 0x10000)
    {
        pBars->field_0_state = 3;
    }

    if ((pBars->field_0_state == 0 || pBars->field_0_state == 3) &&
        (updated || GM_GameStatus_800AB3CC & 0x8000 || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth))
    {
        if (!pBars->field_0_state)
        {
            pBars->field_4_bar_y = -48;
        }

        pBars->field_0_state = 1;
        gTakeDamageCounter_800AB5FC = 0;
    }

    if (pBars->field_0_state == 0)
    {
        return;
    }

    switch (pBars->field_0_state)
    {
    case 1:
        pBars->field_4_bar_y += 8;

        if (pBars->field_4_bar_y >= 16)
        {
            pBars->field_4_bar_y = 16;
            pBars->field_0_state = 2;
            pBars->field_8 = 150;
        }
        break;

    case 3:
        pBars->field_4_bar_y -= 8;

        if (pBars->field_4_bar_y < -47)
        {
            pBars->field_0_state = 0;
            pBars->field_4_bar_y = -48;

            if (GM_GameStatus_800AB3CC & 0x10000)
            {
                GM_GameStatus_800AB3CC = (GM_GameStatus_800AB3CC & ~0x10000) | 0x20000;
            }

            if (GM_O2_800ABA34 == 1024)
            {
                pBars->field_1_O2_hp = 0;
            }

            return;
        }
        break;

    case 2:
        if (updated || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth || GM_GameStatus_800AB3CC & 0x8000)
        {
            pBars->field_8 = 150;

            if (pBars->field_1_O2_hp)
            {
                pBars->field_1_O2_hp--;
            }
        }
        else if (--pBars->field_8 <= 0)
        {
            pBars->field_0_state = 3;
        }
        break;

    case 4:
        pBars->field_0_state = 0;
        pBars->field_4_bar_y = -48;
        break;
    }

    menu_life_update_helper2_8003F30C(pActor->field_20_otBuf, pBars);
}

void menu_life_init_8003F7E0(Actor_MenuMan *pActor)
{
    MenuMan_MenuBars *pBar;

    pActor->field_2C_modules[MENU_LIFE] = menu_life_update_8003F530;
    pActor->field_28_flags |= 1;

    pBar = &pActor->field_204_bars;
    pBar->field_6_snake_hp = GM_SnakeCurrentHealth;
    pBar->field_A_k10_decrement = 10;
    pBar->field_2_bar_x = 16;
    pBar->field_0_state = 0;
    pBar->field_4_bar_y = -48;
    pBar->field_1_O2_hp = 0;
    gSnakeLifeYPos_800ABAF0 = -48;
}

void menu_life_kill_8003F838(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~1u;
}
