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

extern int MENU_RadarScale_800AB480;
int        SECTION(".sdata") MENU_RadarScale_800AB480;
extern int MENU_RadarRangeH_800AB484;
int        SECTION(".sdata") MENU_RadarRangeH_800AB484;
extern int MENU_RadarRangeV_800AB488;
int        SECTION(".sdata") MENU_RadarRangeV_800AB488;

extern MATRIX gRadarScaleMatrix_800BD580;
extern MATRIX DG_ZeroMatrix_8009D430;

extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;

void menu_SetRadarScale_80038E28(int scale)
{
    int    scale2;
    VECTOR scale_vec;

    MENU_RadarScale_800AB480 = scale * 13 / 4096;

    scale2 = 65536 * 13 / MENU_RadarScale_800AB480;

    MENU_RadarRangeH_800AB484 = scale2 / 3;
    MENU_RadarRangeV_800AB488 = scale2 / 4;

    gRadarScaleMatrix_800BD580 = DG_ZeroMatrix_8009D430;
    scale_vec.vz = MENU_RadarScale_800AB480;
    scale_vec.vy = MENU_RadarScale_800AB480;
    scale_vec.vx = MENU_RadarScale_800AB480;
    ScaleMatrix_800930D8(&gRadarScaleMatrix_800BD580, &scale_vec);
}

void menu_SetRadarFunc_80038F30(int param_1)
{
    gFn_radar_800AB48C = param_1;
}

void draw_radar_helper2_helper_80038F3C(Actor_MenuMan *pActor, char *pOt, unsigned short *param_3, short x, short y,
                                        int rgb1, int rgb2, int param_8)
{
    // TODO: Isn't param_3 just a SVECTOR*?
    POLY_G4 *pPrim;
    int      a2;
    int      diffdir;
    SVECTOR  vec1, vec2, vec3;

    a2 = ((param_3[1] * param_8 / 4096) * 3) / 2;
    GV_DirVec2_80016F24(param_3[0], a2, &vec3);

    diffdir = GV_DiffDirU_80017040(param_3[0], param_3[2] / 2);
    GV_DirVec2_80016F24(diffdir, a2, &vec1);

    diffdir = GV_DiffDirU_80017040(param_3[0], -param_3[2] / 2);
    GV_DirVec2_80016F24(diffdir, a2, &vec2);

    pPrim = (POLY_G4 *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(POLY_G4);

    pPrim->x0 = x - vec2.vx;
    pPrim->y0 = vec2.vz + y;
    pPrim->x1 = x;
    pPrim->y1 = y;
    pPrim->x2 = vec3.vx + x;
    pPrim->y2 = vec3.vz + y;
    pPrim->x3 = x - vec1.vx;
    pPrim->y3 = vec1.vz + y;

    LSTORE(rgb1, &pPrim->r1);
    LSTORE(rgb2, &pPrim->r0);
    LSTORE(rgb2, &pPrim->r2);
    LSTORE(rgb2, &pPrim->r3);

    setPolyG4(pPrim);
    setSemiTrans(pPrim, 1);

    addPrim(pOt, pPrim);
}

void draw_radar_helper_800390FC(struct Actor_MenuMan *menuMan)
{
    int x1, y1, x2, y2;

    x1 = menuMan->field_CC_radar_data.field_108_radarXOffsetFromDefault;
    y1 = menuMan->field_CC_radar_data.field_10A_radarYOffsetFromDefault;
    x2 = x1 + 0xea;
    y2 = y1 + 0xf;
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y2, 1, 53, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y2, 70, 1, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x1 + 304, y2, 1, 54, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y1 + 68, 70, 1, 0);
}

#pragma INCLUDE_ASM("asm/draw_radar_helper2_800391D0.s") // 2956 bytes

extern int gRadarClut_800AB498;
int        SECTION(".sdata") gRadarClut_800AB498;

void sub_80039D5C(SPRT *pPrim, int x, int y, radar_uv *pRadarUV, int rgb)
{
    short clut;

    pPrim->x0 = x;
    pPrim->y0 = y;
    pPrim->u0 = pRadarUV->field_0_u0;
    pPrim->v0 = pRadarUV->field_1_v0;
    pPrim->w = pRadarUV->field_2_w;
    pPrim->h = pRadarUV->field_3_h;

    do {} while (0); // Force a match

    clut = gRadarClut_800AB498;
    LSTORE(rgb, &pPrim->r0);

    setSprt(pPrim);
    setSemiTrans(pPrim, 1);

    pPrim->clut = clut;
}

void draw_radar_helper3_helper_helper_80039DB4(MenuGlue *pGlue, SPRT *pSprt, radar_uv *pRadarUV)
{
    int   x0;
    TILE *tile1;
    TILE *tile2;

    x0 = pSprt->x0;

    tile1 = (TILE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(TILE);

    tile1->x0 = -34;
    tile1->y0 = pSprt->y0;
    tile1->w = x0 - tile1->x0;
    tile1->h = pRadarUV->field_3_h;
    LCOPY(&pSprt->r0, &tile1->r0);

    setTile(tile1);
    setSemiTrans(tile1, 1);
    addPrim(pGlue->mPrimBuf.mOt, tile1);

    tile2 = (TILE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(TILE);

    *tile2 = *tile1;
    tile2->x0 = pRadarUV->field_2_w + x0;
    tile2->w = 69 - tile2->x0;

    addPrim(pGlue->mPrimBuf.mOt, tile2);
}

extern radar_uv_pair gRadarUV_8009E30C[];
extern int           gRadarRGBTable_8009E3B8[];
extern int           GV_Time_800AB330;

static inline void draw_radar_helper3_helper_helper2(MenuGlue *pGlue, int height, radar_uv *pRadarUV, int *rgbs)
{
    SPRT *pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    sub_80039D5C(pPrim, -pRadarUV->field_2_w / 2, height, pRadarUV, rgbs[0]);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
    draw_radar_helper3_helper_helper_80039DB4(pGlue, pPrim, pRadarUV);
}

void draw_radar_helper3_helper_80039EC4(MenuGlue *pGlue, int height, int idx)
{
    int       time, time2;
    int       rgbs[2];
    radar_uv *pRadarUV;

    rgbs[0] = gRadarRGBTable_8009E3B8[idx];

    time = GV_Time_800AB330 % 16;

    if (time < 8)
    {
        time2 = time * 512;
        gte_ldfcdir(0, 0, 0);
        gte_lddp(time2);
        gte_ldrgb(rgbs);
        gte_dpcs();
        gte_strgb(&rgbs[1]);
        LCOPY(&rgbs[1], rgbs);
    }

    pRadarUV = &gRadarUV_8009E30C[idx].field_4;
    draw_radar_helper3_helper_helper2(pGlue, height, pRadarUV, rgbs);

    height += pRadarUV->field_3_h;
    pRadarUV = &gRadarUV_8009E30C[4].field_0;
    draw_radar_helper3_helper_helper2(pGlue, height, pRadarUV, rgbs);
}

#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper3_helper_8003A0BC.s") // 532 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper2_8003A2D0.s") // 916 bytes
#pragma INCLUDE_ASM("asm/draw_radar_helper3_helper3_8003A664.s") // 788 bytes

void draw_radar_helper3_helper4_8003A978(MenuGlue *pGlue, int x, int index)
{
    SPRT *pPrim;

    pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    // index seems to be between 0 and 3 (inclusive)
    sub_80039D5C(pPrim, x - 34, -12, &gRadarUV_8009E30C[index].field_0, gRadarRGBTable_8009E3B8[index]);
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

void menu_radar_helper_8003ADD8(Actor_MenuMan *pActor, int index)
{
    DRAWENV drawEnv;
    menu_radar_data *radar_data = &pActor->field_CC_radar_data;

    if (index == 0)
    {
        DG_Init_DrawEnv_80018384(&drawEnv, radar_data->field_108_radarXOffsetFromDefault + 235,
                                 radar_data->field_10A_radarYOffsetFromDefault + 16, 69, 52);
        drawEnv.ofs[0] = radar_data->field_108_radarXOffsetFromDefault + 269;
        drawEnv.ofs[1] = radar_data->field_10A_radarYOffsetFromDefault + 42;
    }
    else
    {
        DG_Init_DrawEnv_80018384(&drawEnv, radar_data->field_108_radarXOffsetFromDefault + 555,
                                 radar_data->field_10A_radarYOffsetFromDefault + 16, 69, 52);
        drawEnv.ofs[0] = radar_data->field_108_radarXOffsetFromDefault + 589;
        drawEnv.ofs[1] = radar_data->field_10A_radarYOffsetFromDefault + 42;
    }

    pActor->field_CC_radar_data.field_80_clip = drawEnv.clip;
    drawEnv.isbg = 0;
    SetDrawEnv_800906B0(&pActor->field_CC_radar_data.field_0[index], &drawEnv);
}

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
        clipY = pActor->field_CC_radar_data.field_10A_radarYOffsetFromDefault - 16;
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
        clipY = pActor->field_CC_radar_data.field_10A_radarYOffsetFromDefault + 16;
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
        pActor->field_CC_radar_data.field_10A_radarYOffsetFromDefault = -64;
      }
      else
      {
        pActor->field_CC_radar_data.field_10A_radarYOffsetFromDefault = clipY;
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
    pActor->field_CC_radar_data.field_108_radarXOffsetFromDefault = 0;
    pActor->field_CC_radar_data.field_10A_radarYOffsetFromDefault = 0;
    pActor->field_28_flags = field_28_flags | 8;
    menu_radar_helper_8003ADD8(pActor, 0);
    menu_radar_helper_8003ADD8(pActor, 1);

    pActor->field_CC_radar_data.field_88 = pActor->field_4C_drawEnv[0];
    pActor->field_CC_radar_data.field_C8 = pActor->field_4C_drawEnv[1];

    menu_init_radar_helper_8003ADAC();
    gFn_radar_800AB48C = 0;
    menu_SetRadarScale_80038E28(4096);
}

void menu_radar_kill_8003B554(struct Actor_MenuMan *pActor)
{
    pActor->field_28_flags &= ~8u;
}
