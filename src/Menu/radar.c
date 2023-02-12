#include "menuman.h"
#include "linker.h"
#include "psyq.h"
#include "radar.h"
#include "libdg/libdg.h"

// force gp
extern int gFn_radar_800AB48C;
int        SECTION(".sdata") gFn_radar_800AB48C;

extern Menu_rpk_item *gRadar_rpk_800ABAC8;
Menu_rpk_item        *SECTION(".sbss") gRadar_rpk_800ABAC8;

extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;

#pragma INCLUDE_ASM("asm/menu_SetRadarScale_80038E28.s") // 264 bytes

void menu_SetRadarFunc_80038F30(int param_1)
{
    gFn_radar_800AB48C = param_1;
}

#pragma INCLUDE_ASM("asm/draw_radar_helper2_helper_80038F3C.s") // 448 bytes

void draw_radar_helper_800390FC(struct Actor_MenuMan *menuMan)
{
    int x1, y1, x2, y2;

    x1 = menuMan->field_1D4_radarXOffsetFromDefault;
    y1 = menuMan->field_1D6_radarYOffsetFromDefault;
    x2 = x1 + 0xea;
    y2 = y1 + 0xf;
    menu_render_rect_8003DB2C((MenuGlue *)menuMan->field_20_otBuf, x2, y2, 1, 53, 0); // TODO: fix cast
    menu_render_rect_8003DB2C((MenuGlue *)menuMan->field_20_otBuf, x2, y2, 70, 1, 0);
    menu_render_rect_8003DB2C((MenuGlue *)menuMan->field_20_otBuf, x1 + 304, y2, 1, 54, 0);
    menu_render_rect_8003DB2C((MenuGlue *)menuMan->field_20_otBuf, x2, y1 + 68, 70, 1, 0);
}

#pragma INCLUDE_ASM("asm/draw_radar_helper2_800391D0.s") // 2956 bytes

extern int gRadarClut_800AB498;
int        SECTION(".sdata") gRadarClut_800AB498;

void sub_80039D5C(SPRT *pPrim, int x, int y, radar_sprt_params_8009E30C *pSprtParams, int rgb)
{
    short clut;

    pPrim->x0 = x;
    pPrim->y0 = y;
    pPrim->u0 = pSprtParams->u0;
    pPrim->v0 = pSprtParams->v0;
    pPrim->w  = pSprtParams->w;
    pPrim->h  = pSprtParams->h;

    do {} while (0); // Force a match

    clut = gRadarClut_800AB498;
    LSTORE(rgb, &pPrim->r0);

    setSprt(pPrim);
    setSemiTrans(pPrim, 1);

    pPrim->clut = clut;
}

#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper_helper_80039DB4.s") // 272 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper_80039EC4.s") // 504 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper3_helper_8003A0BC.s") // 532 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper2_8003A2D0.s") // 916 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper3_8003A664.s") // 788 bytes

extern radar_sprt_params_8009E30C gRadarSprtParams_8009E30C[];
extern int                        gRadarRGBTable_8009E3B8[];

void draw_radar_helper3_helper4_8003A978(MenuGlue *pGlue, int x, int index)
{
    SPRT *pPrim;

    pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    // index seems to be between 0 and 3 (inclusive)
    sub_80039D5C(pPrim, x - 34, -12, &gRadarSprtParams_8009E30C[index], gRadarRGBTable_8009E3B8[index]);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

#pragma INCLUDE_ASM("asm/draw_radar_helper3_8003AA2C.s") // 824 bytes

void menu_radar_load_rpk_8003AD64()
{
    RECT rect;
    rect.x = 992;
    rect.y = 336;
    rect.w = gRadar_rpk_800ABAC8->field_2_w;
    rect.h = gRadar_rpk_800ABAC8->field_3_h;
    LoadImage_8008FB10(&rect, (unsigned char *)&gRadar_rpk_800ABAC8[1]);
}

void menu_init_radar_helper_8003ADAC(void)
{
    gRadar_rpk_800ABAC8 = menu_rpk_get_img_8003DDB4(41);
    menu_radar_load_rpk_8003AD64();
}

#pragma INCLUDE_ASM("asm/menu_radar_helper_8003ADD8.s") // 232 bytes
#pragma INCLUDE_ASM("asm/draw_radar_8003AEC0.s") // 1168 bytes



void menu_radar_update_8003B350(struct Actor_MenuMan* pActor, unsigned char * pOt)
{
  int clipY;

  if (pActor->field_1D8_healthBarDisplayCountdown)
  {
    if (pActor->field_2A_state == 0)
    {
      if ((GM_GameStatus_800AB3CC & 0x200000) != 0)
      {
        clipY = pActor->field_1D6_radarYOffsetFromDefault - 16;
        if (clipY < (-63))
        {
          GM_GameStatus_800AB3CC |= 0x400000;
          GM_GameStatus_800AB3CC &= ~0x200000;
          clipY = -64;
        }
      }
      else
        if ((GM_GameStatus_800AB3CC & 0x100000) != 0)
      {
        GM_GameStatus_800AB3CC &= ~0x400000u;
        clipY = pActor->field_1D6_radarYOffsetFromDefault + 16;
        if (clipY >= 0)
        {
          clipY = 0;
          GM_GameStatus_800AB3CC &= (~0x100000u);
        }
      }
      else
      {
        clipY = 0;
      }
      if ((GM_GameStatus_800AB3CC & 0x400800) != 0)
      {
        pActor->field_1D6_radarYOffsetFromDefault = -64;
      }
      else
      {
        pActor->field_1D6_radarYOffsetFromDefault = clipY;
        menu_radar_helper_8003ADD8(pActor, GV_Clock_800AB920);
        draw_radar_8003AEC0(pActor, pOt);
      }
    }
  }
}


void menu_radar_init_8003B474(struct Actor_MenuMan *pActor)
{
    unsigned char field_28_flags; // $v1

    field_28_flags = pActor->field_28_flags;
    pActor->m7FnPtrs_field_2C[3] = menu_radar_update_8003B350;
    pActor->field_1D8_healthBarDisplayCountdown = 1;
    pActor->field_1D4_radarXOffsetFromDefault = 0;
    pActor->field_1D6_radarYOffsetFromDefault = 0;
    pActor->field_28_flags = field_28_flags | 8;
    menu_radar_helper_8003ADD8(pActor, 0);
    menu_radar_helper_8003ADD8(pActor, 1);

    pActor->field_154 = pActor->field_4C_drawEnv[0];
    pActor->field_194 = pActor->field_4C_drawEnv[1];

    menu_init_radar_helper_8003ADAC();
    gFn_radar_800AB48C = 0;
    menu_SetRadarScale_80038E28(4096);
}

void menu_radar_kill_8003B554(struct Actor_MenuMan *pActor)
{
    pActor->field_28_flags &= ~8u;
}
