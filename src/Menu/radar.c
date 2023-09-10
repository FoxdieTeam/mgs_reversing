#include "menuman.h"
#include "linker.h"
#include "psyq.h"
#include "radar.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

// force gp
extern TRadarFn_800AB48C gFn_radar_800AB48C;
TRadarFn_800AB48C        SECTION(".sdata") gFn_radar_800AB48C;

extern Menu_rpk_item *gRadar_rpk_800ABAC8;
Menu_rpk_item        *SECTION(".sbss") gRadar_rpk_800ABAC8;

extern int MENU_RadarScale_800AB480;
int        SECTION(".sdata") MENU_RadarScale_800AB480;
extern int MENU_RadarRangeH_800AB484;
int        SECTION(".sdata") MENU_RadarRangeH_800AB484;
extern int MENU_RadarRangeV_800AB488;
int        SECTION(".sdata") MENU_RadarRangeV_800AB488;

extern RECT     rect_800AB490;
extern short    image_8009E338[];
extern char     dword_8009E60C[];
extern short    dword_800AB4A0[4];
extern short    dword_800AB4A8[4];

extern MATRIX gRadarScaleMatrix_800BD580;
extern MATRIX DG_ZeroMatrix_8009D430;

extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;

// Used in unmatched draw_radar_helper2_800391D0
int dword_8009E2F4[] = {0x808000, 0x100000, 0xA0, 0x10, 0xA0A0, 0x808};

radar_uv gRadarUV_8009E30C[] = {
    {128,  80, 28, 12},
    {128,  92, 44,  7},
    {156,  80, 28, 12},
    {128,  99, 58,  7},
    {184,  80, 28, 12},
    {180,  92, 44,  7},
    {138, 106, 58, 12},
    {138, 118, 58,  7},
    {188,  99, 36,  3},
    {128, 106, 10, 16},
    {196, 102, 28, 22}
};


// 32x2 image:
short image_8009E338[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210};

int gRadarRGBTable_8009E3B8[] = {0x182589, 0x184789, 0x182589, 0x338918};

radar_uv gRadarUVs_8009E3C8[] = {
    { 7, 29, 55, 1},
    { 7, 50, 55, 1},
    {33, 46,  3, 2}
};
int gRadarRGBTable2_8009E3D4[] = {0x48A000, 0x6E6E, 0xDE, 0x181800};

#define CONSOLE_WIDTH      24
//#define CONSOLE_HEIGHT

//#define CENTER_X
//#define CENTER_Y

#define CONSOLE_LONG_LINES 5 // 7 in the leaks

//#define CONSOLE_LONG_X0    ( 6 - CENTER_X )
//#define CONSOLE_LONG_Y0    ( 30 - CENTER_Y )
#define CONSOLE_X0         4
#define CONSOLE_Y0         -12

//#define CONSOLE_LONG_WIDTH 56
//#define CONSOLE_TEX_WIDTH  28

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

void menu_SetRadarFunc_80038F30(TRadarFn_800AB48C func)
{
    gFn_radar_800AB48C = func;
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

    NEW_PRIM(pPrim, pActor);

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

void draw_radar_helper_800390FC(Actor_MenuMan *menuMan, unsigned char *pOt)
{
    int x1, y1, x2, y2;

    x1 = menuMan->field_CC_radar_data.pos_x;
    y1 = menuMan->field_CC_radar_data.pos_y;
    x2 = x1 + 0xea;
    y2 = y1 + 0xf;
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y2, 1, 53, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y2, 70, 1, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x1 + 304, y2, 1, 54, 0);
    menu_render_rect_8003DB2C(menuMan->field_20_otBuf, x2, y1 + 68, 70, 1, 0);
}

#pragma INCLUDE_ASM("asm/Menu/draw_radar_helper2_800391D0.s") // 2956 bytes
void draw_radar_helper2_800391D0(Actor_MenuMan *pActor, unsigned char *pOt, int param_3);

extern short gRadarClut_800AB498[4];
short        SECTION(".sdata") gRadarClut_800AB498[4];

void sub_80039D5C(SPRT *pPrim, int x, int y, radar_uv *pRadarUV, int rgb)
{
    short clut;

    pPrim->x0 = x;
    pPrim->y0 = y;
    pPrim->u0 = pRadarUV->field_0_x;
    pPrim->v0 = pRadarUV->field_1_y;
    pPrim->w = pRadarUV->field_2_w;
    pPrim->h = pRadarUV->field_3_h;

    do {} while (0); // Force a match

    clut = gRadarClut_800AB498[0];
    LSTORE(rgb, &pPrim->r0);

    setSprt(pPrim);
    setSemiTrans(pPrim, 1);

    pPrim->clut = clut;
}

void draw_radar_helper3_helper_helper_80039DB4(MenuPrim *prim, SPRT *pSprt, radar_uv *pRadarUV)
{
    int   x0;
    TILE *tile1;
    TILE *tile2;

    x0 = pSprt->x0;

    _NEW_PRIM( tile1, prim );

    tile1->x0 = -34;
    tile1->y0 = pSprt->y0;
    tile1->w = x0 - tile1->x0;
    tile1->h = pRadarUV->field_3_h;
    LCOPY(&pSprt->r0, &tile1->r0);

    setTile(tile1);
    setSemiTrans(tile1, 1);
    addPrim(prim->mPrimBuf.mOt, tile1);

    _NEW_PRIM( tile2, prim );

    *tile2 = *tile1;
    tile2->x0 = pRadarUV->field_2_w + x0;
    tile2->w = 69 - tile2->x0;

    addPrim(prim->mPrimBuf.mOt, tile2);
}

extern int           GV_Time_800AB330;

static inline void draw_radar_helper3_helper_helper2(MenuPrim *prim, int height, radar_uv *pRadarUV, int *rgbs)
{
    SPRT *sprt;

    _NEW_PRIM( sprt, prim );

    sub_80039D5C(sprt, -pRadarUV->field_2_w / 2, height, pRadarUV, rgbs[0]);
    addPrim(prim->mPrimBuf.mOt, sprt);
    draw_radar_helper3_helper_helper_80039DB4(prim, sprt, pRadarUV);
}

void draw_radar_helper3_helper_80039EC4(MenuPrim *pGlue, int height, int idx)
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

    pRadarUV = &gRadarUV_8009E30C[idx * 2 + 1];
    draw_radar_helper3_helper_helper2(pGlue, height, pRadarUV, rgbs);

    height += pRadarUV->field_3_h;
    pRadarUV = &gRadarUV_8009E30C[8];
    draw_radar_helper3_helper_helper2(pGlue, height, pRadarUV, rgbs);
}

extern int cons_current_y_800AB4B0;
int        cons_current_y_800AB4B0;
extern int cons_current_x_800AB4B4;
int        cons_current_x_800AB4B4;

void draw_radar_helper3_helper3_helper_8003A0BC(MenuPrim *prim, int code)
{
    SPRT     *spb;
    radar_uv *uv; // CHARA_TABLE *tp;
    int       i;
    int       h;
    int       color;

    uv = &gRadarUV_8009E30C[10]; // tp = &( radar_chara[ CHARA_RANDOM ] );
    color = gRadarRGBTable_8009E3B8[code];
    h = cons_current_y_800AB4B0 > CONSOLE_LONG_LINES ? CONSOLE_LONG_LINES : cons_current_y_800AB4B0;

    _NEW_PRIM( spb, prim );

    spb->clut = gRadarClut_800AB498[0];

    spb->x0 = CONSOLE_X0;
    spb->y0 = CONSOLE_Y0 + h * 2;

    spb->u0 = uv->field_0_x;
    spb->v0 = cons_current_y_800AB4B0 % 16 + uv->field_1_y;

    spb->w = cons_current_x_800AB4B4;
    spb->h = 1;

    LSTORE(color, &spb->r0);

    setSprt(spb);
    setSemiTrans(spb, 1);
    addPrim(prim->mPrimBuf.mOt, spb);

    for( i = 1; i <= h; i++ )
    {
		SPRT *sprt;
		_NEW_PRIM( sprt, prim );
		*sprt = *spb;
		sprt->y0 = spb->y0 - i * 2;
		sprt->w = CONSOLE_WIDTH;
		sprt->v0 = uv->field_1_y + ( cons_current_y_800AB4B0 - i + 16 ) % 16;
		addPrim( prim->mPrimBuf.mOt, sprt );
	}

    if (++cons_current_x_800AB4B4 > CONSOLE_WIDTH)
    {
        cons_current_x_800AB4B4 = 0;
        cons_current_y_800AB4B0++;
    }
}

void draw_radar_helper3_helper2_8003A2D0(MenuPrim *pGlue, int idx)
{
    int       i;
    int       count;
    SPRT     *sprt1, *sprt2, *sprt3, *sprt4;
    radar_uv *uv;
    int       rgb;
    short     clut;
    short     y0;

    uv = &gRadarUV_8009E30C[10];
    rgb = gRadarRGBTable_8009E3B8[idx];

    count = 7;
    if (cons_current_y_800AB4B0 < 8)
    {
        count = cons_current_y_800AB4B0;
    }

    _NEW_PRIM(sprt1, pGlue);
    clut = gRadarClut_800AB498[0];

    sprt1->x0 = -28;
    sprt1->y0 = count * 2 + 4;
    sprt1->clut = clut;
    sprt1->u0 = uv->field_0_x;
    sprt1->v0 = uv->field_1_y + cons_current_y_800AB4B0 % 16;
    sprt1->h = 1;
    LSTORE(rgb, &sprt1->r0);

    setSprt(sprt1);
    setSemiTrans(sprt1, 1);
    addPrim(pGlue->mPrimBuf.mOt, sprt1);

    if (cons_current_x_800AB4B4 > 28)
    {
        sprt1->w = 28;

        _NEW_PRIM(sprt2, pGlue);
        *sprt2 = *sprt1;

        sprt2->v0 = uv->field_1_y + (cons_current_y_800AB4B0 + 3) % 16;
        sprt2->x0 += 28;
        sprt2->w = cons_current_x_800AB4B4 - 28;

        addPrim(pGlue->mPrimBuf.mOt, sprt2);
    }
    else
    {
        sprt1->w = cons_current_x_800AB4B4;
    }

    for (i = 1; i <= count; i++)
    {
        _NEW_PRIM(sprt3, pGlue);
        *sprt3 = *sprt1;

        y0 = sprt1->y0;

        sprt3->w = 28;
        sprt3->y0 = y0 - i * 2;
        sprt3->v0 = uv->field_1_y + (cons_current_y_800AB4B0 - i + 16) % 16;

        addPrim(pGlue->mPrimBuf.mOt, sprt3);

        _NEW_PRIM(sprt4, pGlue);
        *sprt4 = *sprt3;

        sprt4->w = 28;
        sprt4->v0 = uv->field_1_y + (cons_current_y_800AB4B0 - i + 19) % 16;
        sprt4->x0 += 28;

        addPrim(pGlue->mPrimBuf.mOt, sprt4);
    }

    cons_current_x_800AB4B4++;
    if (cons_current_x_800AB4B4 >= 57)
    {
        cons_current_x_800AB4B4 = 0;
        cons_current_y_800AB4B0++;
    }
}

void draw_radar_helper3_helper3_8003A664(MenuPrim *pGlue, int param_2, int code)
{
    int       temp_v0_3;
    int       i, j;
    int       var_s2;
    short    *var_a0;
    int       var_v1;
    TILE     *pTile;
    SPRT     *pSprt;
    radar_uv *pUV;
    radar_uv *pUV2;
    int       six;

    if (param_2 == 255)
    {
        param_2 = 256;
    }

    param_2 = (param_2 * 9999) / 256;

    for (i = 0; i < 4; i++, var_a0++)
    {
        temp_v0_3 = param_2 % 10;
        param_2 /= 10;

        var_a0 = &image_8009E338[i * 16 + 1];
        var_v1 = dword_8009E60C[temp_v0_3];

        for (j = 0; j < 7; j++, var_a0++, var_v1 >>= 1)
        {
            if (var_v1 & 1)
            {
                *var_a0 = dword_800AB4A0[code];
            }
            else
            {
                *var_a0 = dword_800AB4A8[code];
            }
        }
    }

    LoadImage_8008FB10(&rect_800AB490, (unsigned char *)image_8009E338);

    pUV = gRadarUVs_8009E3C8;

    for (i = 3; i > 0; i--)
    {
        pTile = (TILE *)pGlue->mPrimBuf.mFreeLocation;
        pGlue->mPrimBuf.mFreeLocation += sizeof(TILE);

        pTile->x0 = pUV->field_0_x - 34;
        pTile->y0 = pUV->field_1_y - 26;
        LSTORE(gRadarRGBTable_8009E3B8[code], &pTile->r0);
        pTile->w = pUV->field_2_w;
        pTile->h = pUV->field_3_h;

        setTile(pTile);
        setSemiTrans(pTile, 1);

        addPrim(pGlue->mPrimBuf.mOt, pTile);

        pUV++;
    }

    pUV2 = &gRadarUV_8009E30C[9];
    var_s2 = -25;
    six = 6;

    for (i = 0; i < 4; i++)
    {
        pSprt = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
        pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

        sub_80039D5C(pSprt, var_s2, six, pUV2, 0x80808080);
        pSprt->clut = gRadarClut_800AB498[3 - i];

        addPrim(pGlue->mPrimBuf.mOt, pSprt);

        var_s2 += 12;
        if (i == 1)
        {
            var_s2 += 5;
        }
    }

    draw_radar_helper3_helper3_helper_8003A0BC(pGlue, code);
}

void draw_radar_helper3_helper4_8003A978(MenuPrim *prim, int x, int code)
{
    SPRT *sprt;

    _NEW_PRIM(sprt, prim);

    // code seems to be between 0 and 3 (inclusive)
    sub_80039D5C(sprt, x - 34, -12, &gRadarUV_8009E30C[code * 2], gRadarRGBTable_8009E3B8[code]);
    addPrim(prim->mPrimBuf.mOt, sprt);
}

void draw_radar_helper3_8003AA2C(Actor_MenuMan *pActor, char *pOt, int param_3, int param_4)
{
    unsigned int randValue;
    DR_TPAGE    *tpage1;
    TILE        *tile;
    DR_TPAGE    *tpage2;
    LINE_F2     *line;
    int          i;

    switch (param_3)
    {
    case 1:
        LoadImage_8008FB10(&rect_800AB490, (unsigned char *)image_8009E338);
        draw_radar_helper3_helper4_8003A978(pActor->field_20_otBuf, 6, 3);
        draw_radar_helper3_helper2_8003A2D0(pActor->field_20_otBuf, 3);
        draw_radar_helper3_helper_80039EC4(pActor->field_20_otBuf, -25, 3);
        break;

    case 0:
        param_3 = 4;
        break;

    default:
        draw_radar_helper3_helper3_8003A664(pActor->field_20_otBuf, param_4, 3 - param_3);
        draw_radar_helper3_helper4_8003A978(pActor->field_20_otBuf, 9, 3 - param_3);
        draw_radar_helper3_helper_80039EC4(pActor->field_20_otBuf, -25, 3 - param_3);
        break;
    }

    NEW_PRIM(tpage1, pActor);

    setDrawTPage(tpage1, 1, 0, getTPage(0, 2, 960, 256));
    addPrim(pOt, tpage1);

    randValue = (rand() << 16) | (rand());
    for (i = 0; i < 52;)
    {
        NEW_PRIM(line, pActor);

        line->y0 = i - 26;
        line->y1 = i - 26;
        line->x0 = randValue % 138 - 69;
        line->x1 = line->x0 + (randValue / 256) % 69 + 8;
        LSTORE(gRadarRGBTable2_8009E3D4[param_3 - 1], &line->r0);

        setLineF2(line);
        setSemiTrans(line, 1);
        addPrim(pOt, line);

        i += 4 + (randValue >> 24 & 7);
        randValue = randValue << 25 | randValue >> 7;
    }

    NEW_PRIM(tile, pActor);

    tile->x0 = -34;
    tile->w = 69;
    tile->y0 = -26;
    tile->h = 52;
    LSTORE(gRadarRGBTable2_8009E3D4[param_3 - 1], &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    addPrim(pOt, tile);

    NEW_PRIM(tpage2, pActor);
    setDrawTPage(tpage2, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage2);
}

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
    RADAR_T *radar;

    radar = &pActor->field_CC_radar_data;
    if (index == 0)
    {
        DG_Init_DrawEnv_80018384(&drawEnv,
                                 radar->pos_x + 235,
                                 radar->pos_y + 16,
                                 69, 52);
        drawEnv.ofs[0] = radar->pos_x + 269;
        drawEnv.ofs[1] = radar->pos_y + 42;
    }
    else
    {
        DG_Init_DrawEnv_80018384(&drawEnv,
                                 radar->pos_x + 555,
                                 radar->pos_y + 16,
                                 69, 52);
        drawEnv.ofs[0] = radar->pos_x + 589;
        drawEnv.ofs[1] = radar->pos_y + 42;
    }

    pActor->field_CC_radar_data.clip_rect = drawEnv.clip;
    drawEnv.isbg = 0;
    SetDrawEnv_800906B0(&pActor->field_CC_radar_data.dr_env[index], &drawEnv);
}

extern int              GM_AlertMode_800ABA00;
extern int              GM_AlertLevel_800ABA18;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

extern int cons_current_y_800AB4B0;
int        cons_current_y_800AB4B0;

typedef enum // GM_RadarMode_800ABA80
{
	RADAR_VISIBLE = 0,
	RADAR_JAMMED = 1,
	RADAR_EVASION = 2,
	RADAR_ALERT = 3
} RadarMode;

typedef enum // GM_AlertMode_800ABA00
{
	ALERT_DISABLED = 0,
	ALERT_ENABLED = 1,
	ALERT_EVASION = 2 // > 2 = ALERT_EVASION
} AlertMode;

void draw_radar_8003AEC0(Actor_MenuMan *pActor, unsigned char *pOt)
{
    int       alertLevel, alertMode;
    DR_TWIN  *twin, *twin2, *twin3;
    POLY_G4  *polyG4;
    DR_TPAGE *tpage;
    RECT      clip;

    alertLevel = GM_AlertLevel_800ABA18;
    alertMode = GM_AlertMode_800ABA00;

    if (alertMode >= 4)
    {
        alertMode = ALERT_DISABLED;
    }

    if (alertMode == ALERT_DISABLED && gFn_radar_800AB48C == NULL)
    {

        if (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON_DUCT)
        {
            return;
        }

        if (GM_GameStatusFlag & STATUS_RADAR_OFF)
        {
            return;
        }
    }

    draw_radar_helper_800390FC(pActor, pOt);
    addPrim(pOt, &pActor->field_CC_radar_data.org_env[GV_Clock_800AB920]);

    if (gFn_radar_800AB48C)
    {
        gFn_radar_800AB48C(pActor, pOt);
    }
    else
    {
        if (alertMode == ALERT_DISABLED)
        {
            if (GM_GameStatus_800AB3CC & 0x800001)
            {
                alertMode = ALERT_ENABLED;
            }
        }

        switch (alertMode)
        {
        case ALERT_DISABLED:
            alertLevel = pActor->field_CC_radar_data.counter;

            if (alertLevel > 0)
            {
                alertLevel -= 24;

                if (alertLevel == 69)
                {
                    GM_SeSet2_80032968(0, 0x3f, 0xe);
                }

                clip = pActor->field_CC_radar_data.clip_rect;

                if (alertLevel >= 0)
                {
                    draw_radar_helper3_8003AA2C(pActor, pOt, 0, 0);
                    clip.w = alertLevel;
                    clip.x += 69;
                    clip.x -= alertLevel;
                    NEW_PRIM(twin2, pActor);
                    twin = twin2;
                    SetTexWindow_800905F0(twin, &clip);
                    addPrim(pOt, twin);
                }

                NEW_PRIM(polyG4, pActor);

                polyG4->x0 = 11 - alertLevel;
                polyG4->y0 = -26;
                polyG4->x1 = 35 - alertLevel;
                polyG4->y1 = -26;
                polyG4->x2 = 11 - alertLevel;
                polyG4->y2 = clip.h - 26;
                polyG4->x3 = 35 - alertLevel;
                polyG4->y3 = clip.h - 26;

                LSTORE(0x000000, &polyG4->r0);
                LSTORE(0x000000, &polyG4->r2);
                LSTORE(0x48a000, &polyG4->r1);
                LSTORE(0x48a000, &polyG4->r3);
                setPolyG4(polyG4);
                setSemiTrans(polyG4, 1);
                addPrim(pOt, polyG4);

                NEW_PRIM(tpage, pActor);
                setDrawTPage(tpage, 1, 0, getTPage(0, 1, 960, 256));

                addPrim(pOt, tpage);

                draw_radar_helper2_800391D0(pActor, pOt, 0);
                clip = pActor->field_CC_radar_data.clip_rect;

                if (alertLevel >= 0)
                {
                    clip.w = (0x45 - alertLevel);
                }

                NEW_PRIM(twin3, pActor);
                twin = twin3;
                SetTexWindow_800905F0(twin, &clip);
                addPrim(pOt, twin);
                pActor->field_CC_radar_data.counter -= 2;
            }
            else
            {
                draw_radar_helper2_800391D0(pActor, pOt, 0);
                cons_current_y_800AB4B0 = 0;
                cons_current_x_800AB4B4 = 0;
            }
            break;

        case ALERT_ENABLED:
        case ALERT_EVASION:
        case 3:
            pActor->field_CC_radar_data.counter = 93;

            if (alertMode == 1 && pActor->field_CC_radar_data.prev_mode == 0)
            {
                GM_SeSet2_80032968(0, 0x3f, 0x78);
            }
            draw_radar_helper3_8003AA2C(pActor, pOt, alertMode, alertLevel);
            break;
        }

        pActor->field_CC_radar_data.prev_mode = alertMode;
    }

    addPrim(pOt, &pActor->field_CC_radar_data.dr_env[GV_Clock_800AB920]);
}

void menu_radar_update_8003B350(Actor_MenuMan *pActor, unsigned char *pOt)
{
  int clipY;

  if (pActor->field_CC_radar_data.display_flag)
  {
    if (pActor->field_2A_state == 0)
    {
      if ((GM_GameStatus_800AB3CC & 0x200000) != 0)
      {
        clipY = pActor->field_CC_radar_data.pos_y - 16;
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
        clipY = pActor->field_CC_radar_data.pos_y + 16;
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
        pActor->field_CC_radar_data.pos_y = -64;
      }
      else
      {
        pActor->field_CC_radar_data.pos_y = clipY;
        menu_radar_helper_8003ADD8(pActor, GV_Clock_800AB920);
        draw_radar_8003AEC0(pActor, pOt);
      }
    }
  }
}


void menu_radar_init_8003B474(Actor_MenuMan *pActor)
{
    unsigned char field_28_flags; // $v1

    field_28_flags = pActor->field_28_flags;
    pActor->field_2C_modules[MENU_RADAR] = menu_radar_update_8003B350;
    pActor->field_CC_radar_data.display_flag = 1;
    pActor->field_CC_radar_data.pos_x = 0;
    pActor->field_CC_radar_data.pos_y = 0;
    pActor->field_28_flags = field_28_flags | 8;
    menu_radar_helper_8003ADD8(pActor, 0);
    menu_radar_helper_8003ADD8(pActor, 1);

    pActor->field_CC_radar_data.org_env[0] = pActor->field_4C_drawEnv[0];
    pActor->field_CC_radar_data.org_env[1] = pActor->field_4C_drawEnv[1];

    menu_init_radar_helper_8003ADAC();
    gFn_radar_800AB48C = 0;
    menu_SetRadarScale_80038E28(4096);
}

void menu_radar_kill_8003B554(Actor_MenuMan *pActor)
{
    pActor->field_28_flags &= ~8u;
}
