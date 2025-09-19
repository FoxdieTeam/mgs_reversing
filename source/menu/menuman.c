#define _BUILDING_MENUMAN_
#include "menuman.h"

#include <stdio.h>
#include "common.h"
#include "radar.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

extern MenuWork      gMenuWork_800BD360;
extern unsigned char gPrimBackingBuffers_800B9360[2][8192];

extern int MENU_PrimUse;

extern GV_PAD *GM_CurrentPadData;
GV_PAD        *GM_CurrentPadData;

void menu_texture_init_8003CC94(MenuWork *work);
void menu_radar_init_8003B474(MenuWork *work);
void menu_radio_init(MenuWork *work);
void menu_item_init_8003CBF0(MenuWork *work);
void menu_weapon_init_8003EC2C(MenuWork *work);
void menu_life_init_8003F7E0(MenuWork *work);
void menu_number_init(MenuWork *work);
void menu_jimaku_init(MenuWork *work);

TInitKillFn gMenuInitFns_8009E290[] = {
    menu_texture_init_8003CC94,
    menu_radar_init_8003B474,
    menu_radio_init,
    menu_item_init_8003CBF0,
    menu_weapon_init_8003EC2C,
    menu_life_init_8003F7E0,
    menu_number_init,
    menu_jimaku_init,
    NULL};

void menu_radar_kill_8003B554(MenuWork *work);
void menu_radio_kill(MenuWork *work);
void menu_item_kill_8003CC74(MenuWork *work);
void menu_weapon_kill_8003ECAC(MenuWork *work);
void menu_life_kill_8003F838(MenuWork *work);
void menu_number_kill(MenuWork *work);

TInitKillFn gMenuKillFns_8009E2B4[] = {
    menu_radar_kill_8003B554,
    menu_radio_kill,
    menu_item_kill_8003CC74,
    menu_weapon_kill_8003ECAC,
    menu_life_kill_8003F838,
    menu_number_kill,
    NULL};

MenuPrim gMenuPrimBuffer_8009E2D0 = {{0, 0, 0}, {0, 0}};
TextConfig gMenuTextConfig_8009E2E4 = {0, 0, 0, 0x64808080};

void menuman_act_800386A4(MenuWork *work)
{
    unsigned char *pOtStart;
    int            idx_as_flag;
    int            field_28_flags;
    int            i;

    pOtStart = (&gMenuPrimBuffer_8009E2D0)->mPrimBuf.mOt;
    work->field_24_pInput = &GM_CurrentPadData[2];
    menu_jimaku_act(work, (unsigned int *)pOtStart);
    if ( ( !(GV_PauseLevel & 2) && (GM_LoadComplete > 0) ) &&
         ( !GM_LoadRequest ) )
    {
        idx_as_flag = 1;
        if (GM_GameStatus >= 0)
        {
            field_28_flags = work->field_28_flags;
            for (i = 0; i < MENU_MODULE_MAX; i++)
            {
                if ((field_28_flags & idx_as_flag) != 0)
                {
                    work->field_2C_modules[i](work, pOtStart);
                }
                idx_as_flag *= 2;
            }
        }
    }

    addPrim(pOtStart, &work->field_4C_drawEnv[GV_Clock]);
}

void menuman_kill_800387E8(MenuWork *work)
{
    TInitKillFn *pIter;

    pIter = gMenuKillFns_8009E2B4;
    while (*pIter)
    {
        (*pIter)(work);
        pIter++;
    }

    menu_viewer_kill(work);
}

void menu_init_subsystems_8003884C(MenuWork *work)
{
    TInitKillFn *pIter;
    DRAWENV      drawEnv;

    work->field_2A_state = MENU_CLOSED;
    work->field_29 = 0;
    work->field_28_flags = 0;

    work->field_20_otBuf = &gMenuPrimBuffer_8009E2D0;

    gMenuPrimBuffer_8009E2D0.mPrimPtrs[0] = &gPrimBackingBuffers_800B9360[0][0];
    gMenuPrimBuffer_8009E2D0.mPrimPtrs[1] = &gPrimBackingBuffers_800B9360[1][0];

    DG_InitDrawEnv(&drawEnv, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv(&work->field_4C_drawEnv[0], &drawEnv);

    DG_InitDrawEnv(&drawEnv, 320, 0, FRAME_WIDTH, FRAME_HEIGHT);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv(&work->field_4C_drawEnv[1], &drawEnv);

    menu_rpk_init_8003DD1C("item");

    pIter = &gMenuInitFns_8009E290[0];
    while (*pIter)
    {
        (*pIter)(work);
        pIter++;
    }

    menu_viewer_init(work);
}

void menuman_init_80038954(void)
{
    GV_SetNamedActor(&gMenuWork_800BD360.actor, menuman_act_800386A4,
                     menuman_kill_800387E8, "menuman.c");
    menu_init_subsystems_8003884C(&gMenuWork_800BD360);
    MENU_InitRadioTable();
}

void menuman_Reset(void)
{
    MENU_ResetCall();
    MENU_ClearRadioTable();
    MENU_SetRadarScale(4096);
    MENU_SetRadarFunc(NULL);
    gMenuWork_800BD360.field_CC_radar_data.prev_mode = 0;
    gMenuWork_800BD360.field_CC_radar_data.counter = 0;
    gMenuWork_800BD360.field_2B = 0;
    gMenuWork_800BD360.field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
    gMenuWork_800BD360.field_1F0_menu_weapon.field_12_flashingAnimationFrame = 0;
    menu_life_init_8003F7E0(&gMenuWork_800BD360);
}

void MENU_ResetTexture(void)
{
    menu_weapon_unknown_8003DEB0();
}

void MENU_StartDeamon(void)
{
    GV_InitActor(GV_ACTOR_MANAGER, &gMenuWork_800BD360.actor, NULL);
    GV_SetNamedActor(&gMenuWork_800BD360.actor, NULL, NULL, "menuman.c");
}

void menu_radio_update_helper_80038A6C(void)
{
    gMenuWork_800BD360.field_CC_radar_data.display_flag = 1;
}

void menu_radio_update_helper2_80038A7C(void)
{
    gMenuWork_800BD360.field_CC_radar_data.display_flag = 0;
}

void MENU_ResetSystem(void)
{
    unsigned char *pFreeLoc = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd < pFreeLoc)
    {
        fprintf(-1, "!!!! MENU PRIM OVER !!!!\n");
    }

    MENU_PrimUse =
        gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation - gMenuPrimBuffer_8009E2D0.mPrimPtrs[1 - GV_Clock];

    gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation = gMenuPrimBuffer_8009E2D0.mPrimPtrs[GV_Clock];
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation + 0x2000;
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOt = DG_ChanlOTag(1);
    menu_Text_Init_80038B98();
}

void MENU_Locate(int xpos, int ypos, int flags)
{
    TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;

    pTextConfig->xpos = xpos;
    pTextConfig->ypos = ypos;
    pTextConfig->flags = flags;
}

void MENU_Color(int r, int g, int b)
{
    unsigned int newColour;
    unsigned int unknown;
    TextConfig  *pTextConfig = &gMenuTextConfig_8009E2E4;

    if ((pTextConfig->flags & TextConfig_Flags_eSemiTransparent_20) != 0)
    {
        newColour = r | g << 8 | b << 16;
        unknown = 0x66000000;
    }
    else
    {
        newColour = r | g << 8 | b << 16;
        unknown = 0x64000000;
    }

    pTextConfig->colour = newColour | unknown;
}

void menu_Text_Init_80038B98(void)
{
    TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;
    pTextConfig->colour = 0x64808080;
    pTextConfig->flags = 0;
}

void menu_Text_PrimUnknown_80038BB4(void)
{
    DR_TPAGE *pPrim; // $a0

    pPrim = (DR_TPAGE*)gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);
    setDrawTPage(pPrim, 1, 1, getTPage(0, gMenuTextConfig_8009E2E4.flags >> 8, 960, 256));

    addPrim(gMenuPrimBuffer_8009E2D0.mPrimBuf.mOt, pPrim);
}

int MENU_Printf(const char *fmt, const char *str, int param_3, int param_4, int param_5)
{
    int          string_length;
    unsigned int free_space;
    char         string_buffer[64];

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {
        sprintf(string_buffer, (char *)fmt, str, param_3, param_4, param_5);
        free_space = gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd - gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
        string_length = strlen(string_buffer);
        if (string_length * 0x14 + 0x28U <= free_space)
        {
            if (gMenuTextConfig_8009E2E4.flags & TextConfig_Flags_eLargeFont_10)
            {
                _menu_number_draw_string2(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4,
                                          string_buffer);
            }
            else
            {
                _menu_number_draw_string(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4,
                                         string_buffer);
            }
            menu_Text_PrimUnknown_80038BB4();
        }
    }
    return gMenuTextConfig_8009E2E4.xpos;
}

int menu_draw_num(int number)
{
    if (!gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {

        return gMenuTextConfig_8009E2E4.xpos;
    }
    _menu_number_draw(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4, number);
    menu_Text_PrimUnknown_80038BB4();
    return gMenuTextConfig_8009E2E4.xpos;
}

MenuPrim *MENU_GetPrimInfo(void)
{
    return &gMenuPrimBuffer_8009E2D0;
}

// specifically an enemy life bar
void MENU_DrawBar(int xpos, int ypos, int rest, int now, MENU_BAR_CONF *bconf)
{
    GM_GameStatus |= STATE_SHOW_LIFEBAR;
    draw_life_8003F464(&gMenuPrimBuffer_8009E2D0, xpos, ypos, rest, now, 1024, bconf);
    menu_Text_PrimUnknown_80038BB4();
}

void MENU_DrawBar2(int ypos, int rest, int now, int max, MENU_BAR_CONF *bconf)
{
    draw_life_defaultX_8003F408(&gMenuPrimBuffer_8009E2D0, ypos, rest, now, max, bconf);
}
