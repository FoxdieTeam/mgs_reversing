#define _BUILDING_MENUMAN_
#include "menuman.h"
#include "radar.h"
#include "linker.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "psyq.h"

extern Actor_MenuMan gMenuMan_800BD360;
extern unsigned char gPrimBackingBuffers_800B9360[2][8192];

extern int         GV_Clock_800AB920;
extern int         MENU_PrimUse_800AB68C;
extern int GV_PauseLevel_800AB928;
extern int GM_LoadComplete_800ABA38;
extern int GM_GameStatus_800AB3CC;
extern int GM_LoadRequest_800AB3D0;


extern GV_PAD *GM_CurrentPadData_800AB91C;
GV_PAD        *GM_CurrentPadData_800AB91C;

void menu_texture_init_8003CC94(Actor_MenuMan *work);
void menu_radar_init_8003B474(Actor_MenuMan *work);
void menu_radio_init_80042700(Actor_MenuMan *work);
void menu_item_init_8003CBF0(Actor_MenuMan *work);
void menu_weapon_init_8003EC2C(Actor_MenuMan *work);
void menu_life_init_8003F7E0(Actor_MenuMan *work);
void menu_number_init_80042848(Actor_MenuMan *work);
void menu_jimaku_init_800494C4(Actor_MenuMan *work);

TInitKillFn gMenuInitFns_8009E290[] = {
    menu_texture_init_8003CC94,
    menu_radar_init_8003B474,
    menu_radio_init_80042700,
    menu_item_init_8003CBF0,
    menu_weapon_init_8003EC2C,
    menu_life_init_8003F7E0,
    menu_number_init_80042848,
    menu_jimaku_init_800494C4,
    NULL};

void menu_radar_kill_8003B554(Actor_MenuMan *work);
void menu_radio_kill_8004271C(Actor_MenuMan *work);
void menu_item_kill_8003CC74(Actor_MenuMan *work);
void menu_weapon_kill_8003ECAC(Actor_MenuMan *work);
void menu_life_kill_8003F838(Actor_MenuMan *work);
void menu_number_kill_80042980(Actor_MenuMan *work);

TInitKillFn gMenuKillFns_8009E2B4[] = {
    menu_radar_kill_8003B554,
    menu_radio_kill_8004271C,
    menu_item_kill_8003CC74,
    menu_weapon_kill_8003ECAC,
    menu_life_kill_8003F838,
    menu_number_kill_80042980,
    NULL};

MenuPrim gMenuPrimBuffer_8009E2D0 = {{0, 0, 0}, {0, 0}};
TextConfig gMenuTextConfig_8009E2E4 = {0, 0, 0, 0x64808080};

void menuman_act_800386A4(Actor_MenuMan *work)
{
  unsigned char *pOtStart;
  int            idx_as_flag;
  int            field_28_flags;
  int            i;

  pOtStart = (&gMenuPrimBuffer_8009E2D0)->mPrimBuf.mOt;
  work->field_24_pInput = &GM_CurrentPadData_800AB91C[2];
  menu_jimaku_act_80048FD4(work, (unsigned int *)pOtStart);
  if ( ( !(GV_PauseLevel_800AB928 & 2) && (GM_LoadComplete_800ABA38 > 0) ) &&
       ( !GM_LoadRequest_800AB3D0 ) )
  {
    idx_as_flag = 1;
    if (GM_GameStatus_800AB3CC >= 0)
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

  addPrim(pOtStart, &work->field_4C_drawEnv[GV_Clock_800AB920]);
}

void menuman_kill_800387E8(Actor_MenuMan *work)
{
    TInitKillFn *pIter;

    pIter = gMenuKillFns_8009E2B4;
    while (*pIter)
    {
        (*pIter)(work);
        pIter++;
    }

    menu_viewer_kill_80044A90(work);
}

void menu_init_subsystems_8003884C(Actor_MenuMan *pMenuMan)
{
    TInitKillFn *pIter;
    DRAWENV      drawEnv;

    pMenuMan->field_2A_state = 0;
    pMenuMan->field_29 = 0;
    pMenuMan->field_28_flags = 0;

    pMenuMan->field_20_otBuf = &gMenuPrimBuffer_8009E2D0;

    gMenuPrimBuffer_8009E2D0.mPrimPtrs[0] = &gPrimBackingBuffers_800B9360[0][0];
    gMenuPrimBuffer_8009E2D0.mPrimPtrs[1] = &gPrimBackingBuffers_800B9360[1][0];

    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv(&pMenuMan->field_4C_drawEnv[0], &drawEnv);

    DG_Init_DrawEnv_80018384(&drawEnv, 320, 0, 320, 224);
    drawEnv.isbg = 0;
    drawEnv.tpage = 31;
    SetDrawEnv(&pMenuMan->field_4C_drawEnv[1], &drawEnv);

    menu_rpk_init_8003DD1C("item");

    pIter = &gMenuInitFns_8009E290[0];
    while (*pIter)
    {
        (*pIter)(pMenuMan);
        pIter++;
    }

    menu_viewer_init_80044A70(pMenuMan);
}

void menuman_init_80038954(void)
{
    GV_SetNamedActor_8001514C(&gMenuMan_800BD360.field_0_actor, (TActorFunction)menuman_act_800386A4,
                              (TActorFunction)menuman_kill_800387E8, "menuman.c");
    menu_init_subsystems_8003884C(&gMenuMan_800BD360);
    menu_InitRadioTable_80049644();
}

void menuman_Reset_800389A8()
{
    menu_ResetCall_80042814();
    menu_ClearRadioTable_8004967C();
    menu_SetRadarScale_80038E28(4096);
    menu_SetRadarFunc_80038F30(NULL);
    gMenuMan_800BD360.field_CC_radar_data.prev_mode = 0;
    gMenuMan_800BD360.field_CC_radar_data.counter = 0;
    gMenuMan_800BD360.field_2B = 0;
    gMenuMan_800BD360.field_1DC_menu_item.field_12_flashingAnimationFrame = 0;
    gMenuMan_800BD360.field_1F0_menu_weapon.field_12_flashingAnimationFrame = 0;
    menu_life_init_8003F7E0(&gMenuMan_800BD360);
}

void menu_ResetTexture_80038A00(void)
{
    menu_weapon_unknown_8003DEB0();
}

void menu_StartDeamon_80038A20(void)
{
    GV_InitActor_800150A8(1, &gMenuMan_800BD360.field_0_actor, 0);
    GV_SetNamedActor_8001514C(&gMenuMan_800BD360.field_0_actor, 0, 0, "menuman.c");
}

void menu_radio_update_helper_80038A6C(void)
{
    gMenuMan_800BD360.field_CC_radar_data.display_flag = 1;
}

void menu_radio_update_helper2_80038A7C(void)
{
    gMenuMan_800BD360.field_CC_radar_data.display_flag = 0;
}

void menu_ResetSystem_80038A88()
{
    unsigned char *pFreeLoc = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd < pFreeLoc)
    {
        fprintf(-1, "!!!! MENU PRIM OVER !!!!\n");
    }

    MENU_PrimUse_800AB68C =
        gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation - gMenuPrimBuffer_8009E2D0.mPrimPtrs[1 - GV_Clock_800AB920];

    gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation = gMenuPrimBuffer_8009E2D0.mPrimPtrs[GV_Clock_800AB920];
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd = gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation + 0x2000;
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mOt = DG_ChanlOTag(1);
    menu_Text_Init_80038B98();
}

void MENU_Locate_80038B34(int xpos, int ypos, int flags)
{
    TextConfig *pTextConfig = &gMenuTextConfig_8009E2E4;

    pTextConfig->xpos = xpos;
    pTextConfig->ypos = ypos;
    pTextConfig->flags = flags;
}

void MENU_Color_80038B4C(int r, int g, int b)
{
    unsigned int newColour;
    unsigned int unknown;
    TextConfig  *pTextConfig = &gMenuTextConfig_8009E2E4;

    if ((pTextConfig->flags & TextConfig_Flags_eSemiTransparent_20) != 0)
    {
        newColour = r | g << 8 | b << 0x10;
        unknown = 0x66000000;
    }
    else
    {
        newColour = r | g << 8 | b << 0x10;
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

void menu_Text_PrimUnknown_80038BB4()
{
    DR_TPAGE *pPrim; // $a0

    pPrim = (DR_TPAGE*)gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
    gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);
    setDrawTPage(pPrim, 1, 1, getTPage(0, gMenuTextConfig_8009E2E4.flags >> 8, 960, 256));

    addPrim(gMenuPrimBuffer_8009E2D0.mPrimBuf.mOt, pPrim);
}

int MENU_Printf_80038C38(const char *fmt, const char *str, int param_3, int param_4, int param_5)
{
    int          string_length;
    unsigned int free_space;
    char         string_buffer[64];

    if (gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {
        sprintf(string_buffer, fmt, str, param_3, param_4, param_5);
        free_space = gMenuPrimBuffer_8009E2D0.mPrimBuf.mOtEnd - gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation;
        string_length = strlen(string_buffer);
        if (string_length * 0x14 + 0x28U <= free_space)
        {
            if (gMenuTextConfig_8009E2E4.flags & 0x10U)
            {
                menu_number_draw_string2_80043220(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4,
                                                  string_buffer);
            }
            else
            {
                menu_number_draw_string_80042BF4(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4,
                                                 string_buffer);
            }
            menu_Text_PrimUnknown_80038BB4();
        }
    }
    return gMenuTextConfig_8009E2E4.xpos;
}

int menu_draw_num_80038D10(int number)
{
    if (!gMenuPrimBuffer_8009E2D0.mPrimBuf.mFreeLocation)
    {

        return gMenuTextConfig_8009E2E4.xpos;
    }
    menu_number_draw_80042988(&gMenuPrimBuffer_8009E2D0, &gMenuTextConfig_8009E2E4, number);
    menu_Text_PrimUnknown_80038BB4();
    return gMenuTextConfig_8009E2E4.xpos;
}

MenuPrim *menu_GetPrimInfo_80038D68(void)
{
    return &gMenuPrimBuffer_8009E2D0;
}

void menu_DrawBar_80038D74(int xpos, int ypos, int rest, int now, MENU_BAR_CONF *bconf)
{
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_16;
    draw_life_8003F464(&gMenuPrimBuffer_8009E2D0, xpos, ypos, rest, now, 1024, bconf);
    menu_Text_PrimUnknown_80038BB4();
}

void menu_DrawBar2_80038DE0(int ypos, int rest, int now, int max, MENU_BAR_CONF *bconf)
{
    draw_life_defaultX_8003F408(&gMenuPrimBuffer_8009E2D0, ypos, rest, now, max, bconf);
}
