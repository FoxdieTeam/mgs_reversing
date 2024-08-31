#include "menuman.h"
#include "linker.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"
#include "Game/linkvarbuf.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"

extern int   GM_GameStatus_800AB3CC;
extern short GM_O2_800ABA34;

MENU_BAR_CONF gSnakeLifeBarConfig_8009E5F4 = {"LIFE", {0x10, 0x8F, 0x7F}, {0x1F, 0xDF, 0x3F}, 0};
MENU_BAR_CONF gSnakeO2BarConfig_8009E600 = {"O2", {0x1F, 0x3F, 0xC0}, {0x1F, 0x7F, 0xFF}, 1};

int gTakeDamageCounter_800AB5FC = 0;

RECT rect_800AB600 = {960, 256, 50, 80};

short coords_800AB600[2][2] = {{86, 72}, {44, 72}};

// force gp
extern int dword_800ABAE8;
int        SECTION(".sbss") dword_800ABAE8;

extern int gSnakeLifeYPos_800ABAF0;
int        SECTION(".sbss") gSnakeLifeYPos_800ABAF0;

void MENU_ResetWeaponPos_8003ECC0(void)
{
    dword_800ABAE8 = 0;
}

int menu_life_update_helper_8003ECCC(MenuMan_MenuBars *pBars)
{
    short snakeHp;

    snakeHp = pBars->field_6_snake_hp;
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

void menu_draw_bar_8003ED4C(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf)
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

    if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_11 | GAME_FLAG_BIT_18 | GAME_IN_DEMO))
    {
        return;
    }

    pOt = prim->mPrimBuf.mOt;

    sp2C = 5 - bconf->field_A_bar_height;
    temp_fp = y + 1;
    sp28 = max / 8;

    text_config.xpos = x + 4;
    temp_v1 = text_config.xpos;

    text_config.flags = 0;
    text_config.ypos = y + 4;

    if ( !((int)bconf & 0x80000000) )
    {
        text_config.colour = 0x643030FF;
    }
    else
    {
        text_config.colour = 0x64FFFFFF;
    }

    _menu_number_draw_string_80042BF4(prim, &text_config, bconf->field_0_text);

    width = text_config.xpos - temp_v1 + 2;
    pTile = menu_render_rect_8003DB2C(prim, temp_v1 - 1, text_config.ypos - 1, width, 7, 0);
    setSemiTrans(pTile, 1);

    if (rest > max)
    {
        rest = max;
    }

    if (rest > now)
    {
        _NEW_PRIM(pTile_2, prim);

        setTile(pTile_2);

        diff = (rest - now) / 8;

        pTile_2->x0 = x + now / 8;
        pTile_2->y0 = temp_fp;

        pTile_2->w = diff;
        pTile_2->h = sp2C;

        pTile_2->r0 = 200;
        pTile_2->g0 = 0;
        pTile_2->b0 = 0;

        addPrim(pOt, pTile_2);
    }

    _NEW_PRIM(pPoly, prim);

    setXYWH(pPoly, x, temp_fp, (now + 7) / 8, sp2C);

    pPoly->r0 = bconf->field_4_rgb_left[0];
    pPoly->g0 = bconf->field_4_rgb_left[1];
    pPoly->b0 = bconf->field_4_rgb_left[2];
    pPoly->r1 = bconf->field_4_rgb_left[0] + ((bconf->field_7_rgb_right[0] - bconf->field_4_rgb_left[0]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->g1 = bconf->field_4_rgb_left[1] + ((bconf->field_7_rgb_right[1] - bconf->field_4_rgb_left[1]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->b1 = bconf->field_4_rgb_left[2] + ((bconf->field_7_rgb_right[2] - bconf->field_4_rgb_left[2]) * (pPoly->x1 - pPoly->x0)) / 128;
    pPoly->r2 = bconf->field_4_rgb_left[0] + ((bconf->field_7_rgb_right[0] - bconf->field_4_rgb_left[0]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->g2 = bconf->field_4_rgb_left[1] + ((bconf->field_7_rgb_right[1] - bconf->field_4_rgb_left[1]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->b2 = bconf->field_4_rgb_left[2] + ((bconf->field_7_rgb_right[2] - bconf->field_4_rgb_left[2]) * (pPoly->x2 - pPoly->x0)) / 128;
    pPoly->r3 = bconf->field_4_rgb_left[0] + ((bconf->field_7_rgb_right[0] - bconf->field_4_rgb_left[0]) * (pPoly->x3 - pPoly->x0)) / 128;
    pPoly->g3 = bconf->field_4_rgb_left[1] + ((bconf->field_7_rgb_right[1] - bconf->field_4_rgb_left[1]) * (pPoly->x3 - pPoly->x0)) / 128;
    pPoly->b3 = bconf->field_4_rgb_left[2] + ((bconf->field_7_rgb_right[2] - bconf->field_4_rgb_left[2]) * (pPoly->x3 - pPoly->x0)) / 128;

    setPolyG4(pPoly);
    addPrim(pOt, pPoly);

    pTile_3 = menu_render_rect_8003DB2C(prim, x, temp_fp, sp28, sp2C, 0x181800);
    setSemiTrans(pTile_3, 1);

    menu_render_rect_8003DB2C(prim, x - 1, y, 1, sp2C + 2, 0);
    menu_render_rect_8003DB2C(prim, x, y, sp28, 1, 0);
    menu_render_rect_8003DB2C(prim, x, y + sp2C + 1, sp28, 1, 0);
    menu_render_rect_8003DB2C(prim, x + sp28, y, 1, sp2C + 2, 0);

    _NEW_PRIM(pTpage, prim);

    setDrawTPage(pTpage, 1, 1, getTPage(0, 0, 960, 256));
    addPrim(prim->mPrimBuf.mOt, pTpage);
}

void menu_life_update_helper2_8003F30C(MenuPrim *prim, MenuMan_MenuBars *pBars)
{
    MENU_BAR_CONF *pBar;

    pBar = &gSnakeLifeBarConfig_8009E5F4;
    gSnakeLifeYPos_800ABAF0 = pBars->field_4_bar_y;

    if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_26) != 0)
    {
        gTakeDamageCounter_800AB5FC = 8;
        GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_26;
    }

    if (gTakeDamageCounter_800AB5FC > 0)
    {
        --gTakeDamageCounter_800AB5FC;
        pBar = UNTAG_PTR(MENU_BAR_CONF, pBar); // pointer flag to make it render in red
    }

    menu_draw_bar_8003ED4C(prim,
                           pBars->field_2_bar_x,
                           pBars->field_4_bar_y,
                           pBars->field_6_snake_hp,
                           GM_SnakeCurrentHealth,
                           GM_SnakeMaxHealth,
                           pBar);

    if (pBars->field_1_O2_hp)
    {
        menu_draw_bar_8003ED4C(prim,
                               pBars->field_2_bar_x,
                               pBars->field_4_bar_y + 12,
                               GM_O2_800ABA34,
                               GM_O2_800ABA34,
                               1024,
                               &gSnakeO2BarConfig_8009E600);
    }
}

void draw_life_defaultX_8003F408(MenuPrim *prim, long y, long rest, long now, long max, MENU_BAR_CONF *bconf)
{
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_16;
    menu_draw_bar_8003ED4C(prim,
                           16,
                           y + gSnakeLifeYPos_800ABAF0 - 16,
                           rest,
                           now,
                           max,
                           bconf);
}

void draw_life_8003F464(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf)
{
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_16;
    menu_draw_bar_8003ED4C(prim,
                           x,
                           y + gSnakeLifeYPos_800ABAF0 - 16,
                           rest,
                           now,
                           max,
                           bconf);
}

void draw_player_life_8003F4B8(MenuPrim *prim, long x, long y)
{
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_16;
    menu_draw_bar_8003ED4C(prim,
                           x,
                           y,
                           GM_SnakeCurrentHealth,
                           GM_SnakeCurrentHealth,
                           GM_SnakeMaxHealth,
                           &gSnakeLifeBarConfig_8009E5F4);
}

void menu_font_kill_helper_8003F50C(void)
{
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_16;
}

void menu_life_update_8003F530(MenuWork *work, unsigned char *pOt)
{
    int               updated;
    MenuMan_MenuBars *pBars;
    int               state;

    updated = menu_life_update_helper_8003ECCC(&work->field_204_bars);
    pBars = &work->field_204_bars;
    state = work->field_2A_state;

    if (GM_O2_800ABA34 < 1024)
    {
        updated = 1;
        pBars->field_1_O2_hp = -106;
    }

    if (state)
    {
        return;
    }

    if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_17)
    {
        pBars->field_0_state = 3;
    }

    if ((pBars->field_0_state == 0 || pBars->field_0_state == 3) &&
        (updated || GM_GameStatus_800AB3CC & GAME_FLAG_BIT_16 || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth))
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

            if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_17)
            {
                GM_GameStatus_800AB3CC = (GM_GameStatus_800AB3CC & ~GAME_FLAG_BIT_17) | GAME_FLAG_BIT_18;
            }

            if (GM_O2_800ABA34 == 1024)
            {
                pBars->field_1_O2_hp = 0;
            }

            return;
        }
        break;

    case 2:
        if (updated || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth || GM_GameStatus_800AB3CC & GAME_FLAG_BIT_16)
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

    menu_life_update_helper2_8003F30C(work->field_20_otBuf, pBars);
}

void menu_life_init_8003F7E0(MenuWork *work)
{
    MenuMan_MenuBars *pBar;

    work->field_2C_modules[MENU_LIFE] = menu_life_update_8003F530;
    work->field_28_flags |= 1;

    pBar = &work->field_204_bars;
    pBar->field_6_snake_hp = GM_SnakeCurrentHealth;
    pBar->field_A_k10_decrement = 10;
    pBar->field_2_bar_x = 16;
    pBar->field_0_state = 0;
    pBar->field_4_bar_y = -48;
    pBar->field_1_O2_hp = 0;
    gSnakeLifeYPos_800ABAF0 = -48;
}

void menu_life_kill_8003F838(MenuWork *pMenu)
{
    pMenu->field_28_flags &= ~1u;
}

//below may be separate to life but draws it in one function
extern SPRT gMenuSprt_800bd998;
extern KCB  font_800BD968;

int sub_8003F84C(int idx)
{
    void *font_buffer;

    setSprt(&gMenuSprt_800bd998);

    gMenuSprt_800bd998.u0 = 0;
    gMenuSprt_800bd998.v0 = rect_800AB600.y;

    gMenuSprt_800bd998.r0 = 128;
    gMenuSprt_800bd998.g0 = 128;
    gMenuSprt_800bd998.b0 = 128;

    gMenuSprt_800bd998.w = 200;
    gMenuSprt_800bd998.h = 80;

    // Callers to this function call it with idx = 0 or idx = 1
    gMenuSprt_800bd998.x0 = coords_800AB600[idx][0];
    gMenuSprt_800bd998.y0 = coords_800AB600[idx][1];
    gMenuSprt_800bd998.clut = 0x7fbc;

    ClearImage(&rect_800AB600, 0, 0, 0);

    font_init_kcb_80044BE0(&font_800BD968, &rect_800AB600, 960, 510);
    font_set_kcb_80044C90(&font_800BD968, -1, -1, 0, 6, 2, 0);

    font_buffer = GV_Malloc(font_get_buffer_size_80044F38(&font_800BD968));
    if (font_buffer == NULL)
    {
        return 0;
    }

    font_set_buffer_80044FD8(&font_800BD968, font_buffer);
    font_set_color_80044DC4(&font_800BD968, 0, 0x6739, 0);
    font_clut_update_80046980(&font_800BD968);
    return 1;
}

void sub_8003F97C(char *string)
{
    font_print_string_800469A4(&font_800BD968, string);
    font_update_8004695C(&font_800BD968);
}

void menu_8003F9B4(MenuWork *work, unsigned int *pOt, const char *str)
{
    POLY_F4 *polyF4;
    TILE    *tile;
    SPRT    *sprt;
    int      i;
    int      w;

    // Variables storing temporary X coordinate calculations
    // It's required to get a match...
    int x0, x1, x2, x3, x4;

    work->field_2B |= 2;

    NEW_PRIM(sprt, work);

    *sprt = gMenuSprt_800bd998;
    addPrim(pOt, sprt);

    x0 = gMenuSprt_800bd998.x0;
    x3 = x0 - 10;
    w = gMenuSprt_800bd998.w + 10;
    x1 = x0;

    x4 = menu_number_draw_string_800430F0(work, pOt, x1 - 8, gMenuSprt_800bd998.y0 - 7, str, 0);
    draw_player_life_8003F4B8(work->field_20_otBuf, x3, 24);

    i = 0;
    x0 = 12;
    x0 = x1 - x0;
    x2 = x3 + (x4 - x0);

    for (; i < 2; i++)
    {
        NEW_PRIM(polyF4, work);

        LSTORE(0, &polyF4->r0);
        polyF4->x0 = x3;
        polyF4->y0 = gMenuSprt_800bd998.y0 - 9;
        polyF4->x1 = x2;
        polyF4->y1 = gMenuSprt_800bd998.y0 - 9;
        polyF4->x2 = x3;
        polyF4->y2 = gMenuSprt_800bd998.y0;
        polyF4->x3 = x2;
        polyF4->y3 = gMenuSprt_800bd998.y0;
        polyF4->x3 += 10;

        setPolyF4(polyF4);
        setSemiTrans(polyF4, 1);
        addPrim(pOt, polyF4);

        NEW_PRIM(tile, work);

        LSTORE(0, &tile->r0);
        tile->x0 = x3;
        tile->y0 = gMenuSprt_800bd998.y0;
        tile->w = w;
        tile->h = gMenuSprt_800bd998.h;

        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(pOt, tile);
    }
}

extern MenuWork gMenuWork_800BD360;

void menu_font_kill_8003FC0C(void)
{
  void *ptr;

  gMenuWork_800BD360.field_2B &= ~2;
  menu_font_kill_helper_8003F50C();
  ptr = font_get_buffer_ptr_80044FE8(&font_800BD968);
  GV_Free(ptr);
}
