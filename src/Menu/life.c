#include "menuman.h"

#include "common.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"

extern short GM_O2_800ABA34;

MENU_BAR_CONF gSnakeLifeBarConfig_8009E5F4 = {"LIFE", {0x10, 0x8F, 0x7F}, {0x1F, 0xDF, 0x3F}, 0};
MENU_BAR_CONF gSnakeO2BarConfig_8009E600 = {"O2", {0x1F, 0x3F, 0xC0}, {0x1F, 0x7F, 0xFF}, 1};

STATIC int gTakeDamageCounter_800AB5FC = 0;

STATIC RECT rect_800AB600 = {960, 256, 50, 80};

STATIC short coords_800AB600[2][2] = {{86, 72}, {44, 72}};

// force gp
extern int dword_800ABAE8;
int        SECTION(".sbss") dword_800ABAE8;

extern int gSnakeLifeYPos_800ABAF0;
int        SECTION(".sbss") gSnakeLifeYPos_800ABAF0;

void MENU_ResetWeaponPos(void)
{
    dword_800ABAE8 = 0;
}

/**
 * @brief Updates the displayed health bar value to match the actual health of Snake.
 *
 * This function gradually updates the displayed health bar value (`displayedHp`) to match
 * the actual health (`GM_SnakeCurrentHealth`). It uses a delay counter to control the speed
 * of the update, making the health bar decrease more slowly when Snake takes damage.
 *
 * @param pBars Pointer to the MenuMan_MenuBars structure containing the health bar state.
 * @return 1 if the displayed health was updated, 0 otherwise.
 */
int menu_life_update_helper_8003ECCC(MenuMan_MenuBars *pBars)
{
    short displayedHp;

    displayedHp = pBars->field_6_snake_hp;

    if (displayedHp == GM_SnakeCurrentHealth)
    {
        pBars->health_delay_counter = 10;
        return 0;
    }
    else
    {
        if (GM_SnakeCurrentHealth < displayedHp)
        {
            if (pBars->health_delay_counter == 0)
            {
                // try to decrease the displayed health faster
                pBars->field_6_snake_hp = displayedHp - 64;
            }
            else
            {
                --pBars->health_delay_counter;
            }
        }
        // if we overshhoot the displayed health, just match real health
        if (pBars->field_6_snake_hp < GM_SnakeCurrentHealth)
        {
            pBars->field_6_snake_hp = GM_SnakeCurrentHealth;
        }
        return 1;
    }
}

/**
 * @brief Draws a status bar (such as a health or oxygen bar) on the screen.
 *
 * This function renders a status bar with a gradient fill, displaying the
 * current value (`now`) relative to the maximum value (`max`).
 * It also handles the visualization of the portion of the bar that will be
 * removed (`rest`) in red if the character is taking damage.
 * The function takes into account various game states and configurations to
 * determine the appearance and behavior of the bar.
 *
 * @param prim Pointer to the structure containing the primitive.
 * @param x The x-coordinate of the bar's position.
 * @param y The y-coordinate of the bar's position.
 * @param rest Value for portion of the bar that will be removed.
 * @param now The current value to be displayed on the bar.
 * @param max The maximum value of the bar.
 * @param pConfig Pointer to the bar's configuration (such as text and colors).
 */
void menu_draw_bar(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf)
{
    TextConfig text_config;
    int        scaled_max_val;
    int        sp2C;
    char      *pOt;
    TILE      *pTile;
    TILE      *pTile_2;
    TILE      *pTile_3;
    POLY_G4   *pPoly;
    DR_TPAGE  *pTpage;
    int        y_with_offset;
    int        x_text;
    int        diff;
    int        width;

    if (GM_GameStatus & (STATE_TAKING_PHOTO | STATE_LIFEBAR_OFF | STATE_DEMO))
    {
        return;
    }

    pOt = prim->mPrimBuf.mOt;

    sp2C = 5 - bconf->field_A_bar_height;
    y_with_offset = y + 1;
    scaled_max_val = max / 8;

    // offset text by 4 pixels to the right
    text_config.xpos = x + 4;
    x_text = text_config.xpos;

    text_config.flags = 0;
    // offset text by 4 pixels down
    text_config.ypos = y + 4;

    if ( !((int)bconf & 0x80000000) )
    {
        // Blue color of the O2 bar text
        text_config.colour = 0x643030FF;
    }
    else
    {
        // White color for everything else
        text_config.colour = 0x64FFFFFF;
    }

    _menu_number_draw_string(prim, &text_config, bconf->field_0_text);

    width = text_config.xpos - x_text + 2;
    pTile = menu_render_rect_8003DB2C(prim, x_text - 1, text_config.ypos - 1, width, 7, 0);
    setSemiTrans(pTile, 1);

    if (rest > max)
    {
        rest = max;
    }

    // if snake is taking damage, draw in red the part of the health that will
    // be removed
    if (rest > now)
    {
        _NEW_PRIM(pTile_2, prim);

        setTile(pTile_2);

        diff = (rest - now) / 8;

        pTile_2->x0 = x + now / 8;
        pTile_2->y0 = y_with_offset;

        pTile_2->w = diff;
        pTile_2->h = sp2C;

        pTile_2->r0 = 200;
        pTile_2->g0 = 0;
        pTile_2->b0 = 0;

        addPrim(pOt, pTile_2);
    }

    _NEW_PRIM(pPoly, prim);

    setXYWH(pPoly, x, y_with_offset, (now + 7) / 8, sp2C);

    // Set the color of the bar as gradient fill. The color is interpolated
    // between the left and right color.
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

    pTile_3 = menu_render_rect_8003DB2C(prim, x, y_with_offset, scaled_max_val, sp2C, 0x181800);
    setSemiTrans(pTile_3, 1);

    menu_render_rect_8003DB2C(prim, x - 1, y, 1, sp2C + 2, 0);
    menu_render_rect_8003DB2C(prim, x, y, scaled_max_val, 1, 0);
    menu_render_rect_8003DB2C(prim, x, y + sp2C + 1, scaled_max_val, 1, 0);
    menu_render_rect_8003DB2C(prim, x + scaled_max_val, y, 1, sp2C + 2, 0);

    _NEW_PRIM(pTpage, prim);

    setDrawTPage(pTpage, 1, 1, getTPage(0, 0, 960, 256));
    addPrim(prim->mPrimBuf.mOt, pTpage);
}

/**
 * @brief Draws the life and oxygen bars for Snake.
 *
 * This function updates the position and state of the life bar and oxygen bar
 * for Snake. It handles the visualization of damage taken by changing the color
 * of the life bar text to red when Snake takes damage.
 *
 * @param prim Pointer to the MenuPrim structure containing the primitive.
 * @param pBars Pointer to the MenuMan_MenuBars structure containing the bar states.
 */
void menu_life_update_helper2_8003F30C(MenuPrim *prim, MenuMan_MenuBars *pBars)
{
    MENU_BAR_CONF *pBar;

    pBar = &gSnakeLifeBarConfig_8009E5F4;
    gSnakeLifeYPos_800ABAF0 = pBars->field_4_bar_y;

    // Reset the flag and start the damage counter if we taken damage
    if ((GM_GameStatus & STATE_DAMAGED) != 0)
    {
        gTakeDamageCounter_800AB5FC = 8;
        GM_GameStatus &= ~STATE_DAMAGED;
    }

    // If the damage counter is active, decrement it and set the bar to render
    // in red
    if (gTakeDamageCounter_800AB5FC > 0)
    {
        --gTakeDamageCounter_800AB5FC;
        pBar = UNTAG_PTR(MENU_BAR_CONF, pBar); // pointer flag to make it render in red
    }

    menu_draw_bar(prim,
                  pBars->field_2_bar_x,
                  pBars->field_4_bar_y,
                  pBars->field_6_snake_hp,
                  GM_SnakeCurrentHealth,
                  GM_SnakeMaxHealth,
                  pBar);

    // If the oxygen bar is not full then draw it
    if (pBars->field_1_O2_hp)
    {
        menu_draw_bar(prim,
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
    GM_GameStatus |= STATE_SHOW_LIFEBAR;
    menu_draw_bar(prim,
                  16,
                  y + gSnakeLifeYPos_800ABAF0 - 16,
                  rest,
                  now,
                  max,
                  bconf);
}

void draw_life_8003F464(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf)
{
    GM_GameStatus |= STATE_SHOW_LIFEBAR;
    menu_draw_bar(prim,
                  x,
                  y + gSnakeLifeYPos_800ABAF0 - 16,
                  rest,
                  now,
                  max,
                  bconf);
}

void draw_player_life_8003F4B8(MenuPrim *prim, long x, long y)
{
    GM_GameStatus |= STATE_SHOW_LIFEBAR;
    menu_draw_bar(prim,
                  x,
                  y,
                  GM_SnakeCurrentHealth,
                  GM_SnakeCurrentHealth,
                  GM_SnakeMaxHealth,
                  &gSnakeLifeBarConfig_8009E5F4);
}

void menu_font_kill_helper_8003F50C(void)
{
    GM_GameStatus &= ~STATE_SHOW_LIFEBAR;
}



/**
 * @brief Display the life bar and oxygen bar according to the bar state.
 *
 * This function updates the position and visibility of the life bar and oxygen
 * bar based on the current state of the game and the player's health.
 *
 * @param work Pointer to the MenuWork structure containing the bar states.
 * @param unused
 */
void menu_life_update_8003F530(MenuWork *work, unsigned char *unused)
{
    int               updated;
    MenuMan_MenuBars *pBars;
    int               state;

    updated = menu_life_update_helper_8003ECCC(&work->field_204_bars);
    pBars = &work->field_204_bars;
    state = work->field_2A_state;

    // if the oxygen is not full
    if (GM_O2_800ABA34 < 1024)
    {
        updated = 1;
        pBars->field_1_O2_hp = -106;
    }
    if (state)
    {
        return;
    }

    if (GM_GameStatus & STATE_HIDE_LIFEBAR)
    {
        pBars->field_0_state = BAR_STATE_MOVING_UP;
    }

    if ((pBars->field_0_state == BAR_STATE_HIDDEN || pBars->field_0_state == BAR_STATE_MOVING_UP) &&
        (updated || GM_GameStatus & STATE_SHOW_LIFEBAR || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth))
    {
        // hide the bar by moving it off screen
        if (pBars->field_0_state == BAR_STATE_HIDDEN)
        {
            pBars->field_4_bar_y = -48;
        }

        pBars->field_0_state = BAR_STATE_MOVING_DOWN;
        gTakeDamageCounter_800AB5FC = 0;
    }

    if (pBars->field_0_state == BAR_STATE_HIDDEN)
    {
        return;
    }

    switch (pBars->field_0_state)
    {
    case BAR_STATE_MOVING_DOWN:
        // move the life bar down
        pBars->field_4_bar_y += 8;

        // if the bar is fully visible then move to state 2
        if (pBars->field_4_bar_y >= 16)
        {
            // saturate the vertical position of the bar
            pBars->field_4_bar_y = 16;
            pBars->field_0_state = BAR_STATE_VISIBLE;
            pBars->field_8_hide_bar_delay_counter = 150;
        }
        break;

    case BAR_STATE_MOVING_UP:
        // we need to slowly hide the bars
        // reduce the vertical position of the bars by 8
        pBars->field_4_bar_y -= 8;

        // if the bars are off finally screen
        if (pBars->field_4_bar_y < -47)
        {
            pBars->field_0_state = BAR_STATE_HIDDEN;
            pBars->field_4_bar_y = -48;

            if (GM_GameStatus & STATE_HIDE_LIFEBAR)
            {
                GM_GameStatus = (GM_GameStatus & ~STATE_HIDE_LIFEBAR) | STATE_LIFEBAR_OFF;
            }
            // if oxygen is full then hide the oxygen bar
            if (GM_O2_800ABA34 == 1024)
            {
                pBars->field_1_O2_hp = 0;
            }

            return;
        }
        break;

    case BAR_STATE_VISIBLE:
        if (updated || (GM_SnakeMaxHealth / 2) >= GM_SnakeCurrentHealth || GM_GameStatus & STATE_SHOW_LIFEBAR)
        {
            pBars->field_8_hide_bar_delay_counter = 150;
            // If the oxigen bar is not hidden then decrease the oxygen bar
            if (pBars->field_1_O2_hp)
            {
                pBars->field_1_O2_hp--;
            }
        }
        // Keep the bars visible until the delay is over
        else if (--pBars->field_8_hide_bar_delay_counter <= 0)
        {
            pBars->field_0_state = BAR_STATE_MOVING_UP;
        }
        break;

    case BAR_STATE_FORCE_HIDE:
        pBars->field_0_state = BAR_STATE_HIDDEN;
        pBars->field_4_bar_y = -48;
        break;
    }

    menu_life_update_helper2_8003F30C(work->field_20_otBuf, pBars);
}

/**
 * @brief Initialize the bars menu module.
 * Set the update function for the bars module and initialize the default state.
 *
 * @param work Pointer to the Menu actor.
 */
void menu_life_init_8003F7E0(MenuWork *work)
{
    MenuMan_MenuBars *pBar;

    work->field_2C_modules[MENU_LIFE] = menu_life_update_8003F530;
    // Set initialized flag
    work->field_28_flags |= 1;

    pBar = &work->field_204_bars;
    pBar->field_6_snake_hp = GM_SnakeCurrentHealth;
    pBar->health_delay_counter = 10;
    pBar->field_2_bar_x = 16;
    pBar->field_0_state = BAR_STATE_HIDDEN;
    // start with the bars off screen
    pBar->field_4_bar_y = -48;
    pBar->field_1_O2_hp = 0;
    gSnakeLifeYPos_800ABAF0 = -48;
}

/**
 * @brief Deinitialize the bars menu module by clearing the initialized flag.
 *
 * @param work Pointer to the Menu actor.
 */
void menu_life_kill_8003F838(MenuWork *work)
{
    // Clear the initialized flag
    work->field_28_flags &= ~1u;
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

    font_init_kcb(&font_800BD968, &rect_800AB600, 960, 510);
    font_set_kcb(&font_800BD968, -1, -1, 0, 6, 2, 0);

    font_buffer = GV_Malloc(font_get_buffer_size(&font_800BD968));
    if (font_buffer == NULL)
    {
        return 0;
    }

    font_set_buffer(&font_800BD968, font_buffer);
    font_set_color(&font_800BD968, 0, 0x6739, 0);
    font_clut_update(&font_800BD968);
    return 1;
}

void menu_printDescription_8003F97C(char *description)
{
    font_print_string(&font_800BD968, description);
    font_update(&font_800BD968);
}

// When scrolling items/weapons menu, draws the life bar, the text "EQUIP" or
// "WEAPON" and the background rectangle around the item/weapon description.
void menu_drawDescriptionPanel_8003F9B4(MenuWork *work, unsigned int *pOt, const char *str)
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

    x4 = menu_number_draw_string(work, pOt, x1 - 8, gMenuSprt_800bd998.y0 - 7, str, 0);
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
  ptr = font_get_buffer_ptr(&font_800BD968);
  GV_Free(ptr);
}
