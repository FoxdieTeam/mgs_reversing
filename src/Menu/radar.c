#include "menuman.h"
#include "linker.h"
#include "psyq.h"
#include "radar.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

int               MENU_RadarScale_800AB480 = 13;
int               MENU_RadarRangeH_800AB484 = 21845;
int               MENU_RadarRangeV_800AB488 = 16383;
TRadarFn_800AB48C gFn_radar_800AB48C = NULL;
RECT              rect_800AB490 = {992, 382, 32, 2};
short             gRadarClut_800AB498[4] = {0x5FBE, 0x5FBF, 0x5FFE, 0x5FFF};
short             dword_800AB4A0[4] = {0x8C91, 0x8D11, 0x8C91, 0x9A23};
short             dword_800AB4A8[4] = {0x8023, 0x8023, 0x8023, 0x0000};
int               cons_current_y_800AB4B0 = 0;
int               cons_current_x_800AB4B4 = 0;


extern Menu_rpk_item *gRadar_rpk_800ABAC8;
Menu_rpk_item        *SECTION(".sbss") gRadar_rpk_800ABAC8;

extern short    image_8009E338[];
extern char     dword_8009E60C[];

extern MATRIX gRadarScaleMatrix_800BD580;
extern MATRIX DG_ZeroMatrix_8009D430;

extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;

typedef struct rgb_pair
{
    int rgb1, rgb2;
} rgb_pair;

rgb_pair dword_8009E2F4[] = {{0x808000, 0x100000}, {0xA0, 0x10}, {0xA0A0, 0x808}};

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
    ScaleMatrix(&gRadarScaleMatrix_800BD580, &scale_vec);
}

void menu_SetRadarFunc_80038F30(TRadarFn_800AB48C func)
{
    gFn_radar_800AB48C = func;
}

// TODO: vec is passed in from an SVECTOR, but the accesses are all unsigned
void draw_radar_vision_cone_80038F3C(Actor_MenuMan *work, char *pOt, unsigned short *vec, int x, int y, int rgb1,
                                     int rgb2, int scale)
{
    POLY_G4 *pPrim;
    int      a2;
    int      diffdir;
    SVECTOR  vec1, vec2, vec3;

    a2 = ((vec[1] * scale / 4096) * 3) / 2;
    GV_DirVec2_80016F24(vec[0], a2, &vec3);

    diffdir = GV_DiffDirU_80017040(vec[0], vec[2] / 2);
    GV_DirVec2_80016F24(diffdir, a2, &vec1);

    diffdir = GV_DiffDirU_80017040(vec[0], -vec[2] / 2);
    GV_DirVec2_80016F24(diffdir, a2, &vec2);

    NEW_PRIM(pPrim, work);

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

#define SCRATCH(type, offset) ((type *)((char *)0x1F800000 + (offset)))

// gte_stbv but with sh instead of sb
#define gte_stbh(r0)                                                                                                   \
    __asm__ volatile("mfc2   $12, $9;"                                                                                 \
                     "mfc2   $13, $10;"                                                                                \
                     "sh $12, 0( %0 );"                                                                                \
                     "sh $13, 2( %0 )"                                                                                 \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12", "$13", "memory")

// gte_ldv0 but without the second load
#define gte_ldv0h(r0) __asm__ volatile("lwc2   $0, 0( %0 )" : : "r"(r0))

extern CONTROL         *GM_WhereList_800B56D0[96];
extern int              GV_Time_800AB330;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              gControlCount_800AB9B4;
extern int              GM_PlayerMap_800ABA0C;

extern int dword_800AB9A8[2];

void draw_radar_helper2_800391D0(Actor_MenuMan *work, unsigned char *pOt, int arg2)
{
    SVECTOR vec;

    CONTROL   **pWhereList;
    MAP *pMap;

    int xoff;
    int zoff;

    HZD_SEG  *pWalls;
    HZD_SEG **ppWalls;
    void     *pLimit;
    int       area_bits;

    CONTROL *pWhere;

    TILE     *pTile;
    TILE_1   *pTile1;
    TILE_1   *pTile1_2;
    DR_TPAGE *pTpage;
    DR_TPAGE *pTpage_2;

    int *prim;

    int x;
    int z;

    int areas;
    int count;
    int count2;
    int count3;

    int scale;

    int cmp1, cmp2;

    int vy;
    int cond1;
    int i;
    int area_mask;

    int cond2;
    int rgb;

    int     *pOt2;
    LINE_F2 *pLine;

    int field_3A;

    char *pWallFlags;
    char *pWallFlags2;

    HZD_AREA *pArea;
    HZD_SEG  *pWall;
    HZD_HDL  *pHzdMap;

    short *scratchShort;

    DG_PVECTOR *pvec;
    SVECTOR    *svec;

    int *pWallDst;
    int *pWallDst2;
    int  j;

    if (GM_GameStatus_800AB3CC < 0)
    {
        return;
    }

    scale = MENU_RadarScale_800AB480;

    pWhereList = GM_WhereList_800B56D0;
    pWhere = pWhereList[0]; // pWhereList[0] is Snake

    *SCRATCH(SVECTOR, 0) = pWhereList[0]->field_0_mov;
    SCRATCH(SVECTOR, 0)->vy = pWhere->field_34_hzd_height;

    pWhereList++;

    pMap = pWhere->field_2C_map;

    if (!pMap)
    {
        return;
    }

    xoff = (SCRATCH(SVECTOR, 0)->vx * scale) / 4096;
    zoff = (SCRATCH(SVECTOR, 0)->vz * scale) / 4096;

    if ((GV_Time_800AB330 % 8) >= 2)
    {
        // Draw white dot for Snake in middle of radar
        NEW_PRIM(pTile1, work);
        LSTORE(0xC8C8C8, &pTile1->r0);
        setTile1(pTile1);
        setXY0(pTile1, 0, 0);
        addPrim(pOt, pTile1);

        if (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON)
        {
            // Draw Snake's vision cone in first person
            vec.vx = pWhere->field_8_rot.vy;
            vec.vy = (rcos(pWhere->field_8_rot.vx) * 6144) / 4096;
            vec.vz = 600;

            draw_radar_vision_cone_80038F3C(work, pOt, (unsigned short *)&vec, 0, 0, 0x48A000, 0, scale);
        }

        for (count = gControlCount_800AB9B4 - 1; count > 0; count--)
        {
            pWhere = *pWhereList++;
            field_3A = (unsigned short)pWhere->field_3A_radar_atr;

            x = ((pWhere->field_0_mov.vx * scale) / 4096) - xoff;
            z = ((pWhere->field_0_mov.vz * scale) / 4096) - zoff;

            if ((field_3A & RADAR_VISIBLE) && ((field_3A & RADAR_ALL_MAP) || (pWhere->field_2C_map->field_0_map_index_bit & GM_PlayerMap_800ABA0C)))
            {
                NEW_PRIM(pTile1_2, work);

                setXY0(pTile1_2, x, z);

                if (field_3A & RADAR_NOISE)
                {
                    LSTORE(0x80FF00, &pTile1_2->r0);
                    setTile1(pTile1_2);
                    addPrim(pTile1, pTile1_2);

                    for (j = 0; j < 16; j++)
                    {
                        int new_var;
                        NEW_PRIM(pTile1_2, work);

                        new_var = 2;
                        pTile1_2->x0 = x - new_var + rand() % 4;
                        pTile1_2->y0 = z - new_var + rand() % 4;

                        LSTORE(0x64C800, &pTile1_2->r0);
                        setTile1(pTile1_2);
                        addPrim(pTile1, pTile1_2);
                    }
                }
                else
                {
                    vy = pWhere->field_0_mov.vy - SCRATCH(SVECTOR, 0)->vy;

                    // bool inline?
                    cond1 = 0;

                    if (field_3A & RADAR_UNK2)
                    {
                        short vy_s = vy;
                        cond1 = (vy_s >= 0) && (vy_s < 6000);
                        field_3A |= RADAR_SIGHT;
                    }
                    else
                    {
                        short vy_s = vy;
                        if (field_3A & RADAR_UNK1)
                        {
                            cond2 = (vy > -2750) && (vy < 2000); // why???
                        }
                        else
                        {
                            cond2 = (vy_s >= -2000) && (vy_s < 2000);
                        }

                        if (cond2 != 0)
                        {
                            cond1 = 1;
                        }
                    }

                    if (cond1)
                    {
                        LSTORE(0x64FF, &pTile1_2->r0);
                        setTile1(pTile1_2);
                        addPrim(pOt, pTile1_2);

                        if (field_3A & RADAR_SIGHT)
                        {
                            int idx = field_3A >> 12;
                            draw_radar_vision_cone_80038F3C(work, pOt, (unsigned short *)&pWhere->field_3C, x, z,
                                                            dword_8009E2F4[idx].rgb1, dword_8009E2F4[idx].rgb2,
                                                            scale);
                        }
                    }
                    else
                    {
                        LSTORE(0xC8, &pTile1_2->r0);
                        setTile1(pTile1_2);
                        addPrim(pTile1, pTile1_2);
                    }
                }
            }
        }

        NEW_PRIM(pTpage, work);
        setDrawTPage(pTpage, 1, 0, getTPage(0, 1, 960, 256));
        addPrim(pOt, pTpage);
    }

    NEW_PRIM(prim, work);
    *prim = 0;
    addPrim(pOt, prim);

    pvec = SCRATCH(DG_PVECTOR, 0);
    svec = SCRATCH(SVECTOR, 0);

    pvec[1].vxy = svec[0].vx - MENU_RadarRangeH_800AB484 / 2;
    pvec[1].vz = svec[0].vx + MENU_RadarRangeH_800AB484 / 2;

    pvec[2].vxy = svec[0].vz - MENU_RadarRangeV_800AB488 / 2;
    pvec[2].vz = svec[0].vz + MENU_RadarRangeV_800AB488 / 2;

    pvec[3].vxy = svec[0].vy + 1000;
    pvec[3].vz = svec[0].vy - 800;

    pLine = (LINE_F2 *)work->field_20_otBuf->mPrimBuf.mFreeLocation;
    pLimit = work->field_20_otBuf->mPrimBuf.mOtEnd - 1024;

    gRadarScaleMatrix_800BD580.t[0] = -xoff;
    gRadarScaleMatrix_800BD580.t[1] = -zoff;

    gte_SetRotMatrix(&gRadarScaleMatrix_800BD580);
    gte_SetTransMatrix(&gRadarScaleMatrix_800BD580);

    for (i = 0; i < 2; i++)
    {
        pHzdMap = NULL;
        pWallDst = SCRATCH(int, 0x20);
        pWallDst2 = SCRATCH(int, 0x24);
        scratchShort = (short *)svec;
        area_bits = dword_800AB9A8[0];

        area_mask = 1 << pMap->field_8_hzd->f00_header->n_areas;
        areas = pMap->field_8_hzd->f00_header->n_areas * 24;

        while (1)
        {
            if (i == 0)
            {
                area_mask >>= 1;
                areas -= 24;

                if (area_mask == 0)
                {
                    break;
                }

                if (!(area_bits & area_mask))
                {
                    continue;
                }

                pArea = (HZD_AREA *)((char *)pMap->field_8_hzd->f00_header->areas + areas);
                pWallFlags = pArea->wallsFlags;
                pWallFlags2 = (char *)pArea->wallsFlags + pArea->n_walls;
                pWalls = pArea->walls;
                count2 = pArea->n_walls;
            }
            else
            {
                pHzdMap = Map_Enum_Get_Hzd_80031580(pHzdMap);

                if (!pHzdMap)
                {
                    break;
                }

                ppWalls = pHzdMap->f20_dynamic_segments;
                pWallFlags = pHzdMap->f24_dynamic_flags;
                pWallFlags2 = pWallFlags + pHzdMap->f12_max_dynamic_segments;
                count2 = pHzdMap->f0A_dynamic_queue_index;
            }

            for (count3 = count2; count3 > 0; count3--, pWallFlags++, pWallFlags2++)
            {
                if (i == 0)
                {
                    pWall = pWalls++;
                }
                else
                {
                    pWall = *ppWalls++;
                }

                if (*pWallFlags & 0x80)
                {
                    continue;
                }

                *pWallDst = *(int *)&pWall->p1.x;
                *pWallDst2 = *(int *)&pWall->p2.x;

                if (((short *)scratchShort)[0x20 / 2] > ((int *)scratchShort)[0xC / 4])
                {
                    continue;
                }

                if (((int *)scratchShort)[0x8 / 4] > ((short *)scratchShort)[0x24 / 2])
                {
                    continue;
                }

                // The scratchpad and its consequences have been a disaster for the human race.
                cmp1 = scratchShort[0x22 / 2];
                cmp2 = scratchShort[0x26 / 2];

                if (cmp1 > cmp2)
                {
                    if (((int *)scratchShort)[0x14 / 4] < cmp2 || cmp1 < ((int *)scratchShort)[0x10 / 4])
                    {
                        continue;
                    }
                }
                else
                {
                    if (((int *)scratchShort)[0x14 / 4] < cmp1 || cmp2 < ((int *)scratchShort)[0x10 / 4])
                    {
                        continue;
                    }
                }

                gte_ldv0h(0x1F800020);
                gte_rt();

                if (((((int *)scratchShort)[0x18 / 4] < pWall->p1.y) ||
                     ((pWall->p1.y + pWall->p1.h) < ((int *)scratchShort)[0x1C / 4])) &&
                    ((((int *)scratchShort)[0x18 / 4] < pWall->p2.y) ||
                     ((pWall->p2.y + pWall->p2.h) < ((int *)scratchShort)[0x1C / 4])))
                {
                    rgb = 0x40004000;
                    pOt2 = (int *)pOt;
                }
                else
                {
                    if (*pWallFlags2 & 0x80)
                    {
                        rgb = 0x404020B4;
                    }
                    else
                    {
                        rgb = 0x4048A000;
                    }

                    pOt2 = prim;
                }

                gte_stbh(&pLine->x0);

                gte_ldv0h(0x1F800024);
                gte_rt();

                LSTORE(rgb, &pLine->r0);
                pLine->tag = *pOt2 | 0x03000000;
                *pOt2 = (int)(pLine)&0xffffff;
                gte_stbh(&pLine->x1);

                pLine++;

                if ((void *)pLine > pLimit)
                {
                    goto end;
                }
            }
        }
    }

end:
    work->field_20_otBuf->mPrimBuf.mFreeLocation = (unsigned char *)pLine;

    NEW_PRIM(pTile, work);

    pTile->x0 = -34;
    pTile->w = 69;
    pTile->y0 = -26;
    pTile->h = 52;

    if (arg2 == 0)
    {
        LSTORE(0x181800, &pTile->r0);
    }
    else
    {
        LSTORE(0x00FFFF, &pTile->r0);
    }

    setTile(pTile);
    setSemiTrans(pTile, 1);
    addPrim(pOt, pTile);

    NEW_PRIM(pTpage_2, work);
    setDrawTPage(pTpage_2, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(pOt, pTpage_2);
}

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

    LoadImage(&rect_800AB490, (u_long *)image_8009E338);

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

void draw_radar_helper3_8003AA2C(Actor_MenuMan *work, char *pOt, int param_3, int param_4)
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
        LoadImage(&rect_800AB490, (u_long *)image_8009E338);
        draw_radar_helper3_helper4_8003A978(work->field_20_otBuf, 6, 3);
        draw_radar_helper3_helper2_8003A2D0(work->field_20_otBuf, 3);
        draw_radar_helper3_helper_80039EC4(work->field_20_otBuf, -25, 3);
        break;

    case 0:
        param_3 = 4;
        break;

    default:
        draw_radar_helper3_helper3_8003A664(work->field_20_otBuf, param_4, 3 - param_3);
        draw_radar_helper3_helper4_8003A978(work->field_20_otBuf, 9, 3 - param_3);
        draw_radar_helper3_helper_80039EC4(work->field_20_otBuf, -25, 3 - param_3);
        break;
    }

    NEW_PRIM(tpage1, work);

    setDrawTPage(tpage1, 1, 0, getTPage(0, 2, 960, 256));
    addPrim(pOt, tpage1);

    randValue = (rand() << 16) | (rand());
    for (i = 0; i < 52;)
    {
        NEW_PRIM(line, work);

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

    NEW_PRIM(tile, work);

    tile->x0 = -34;
    tile->w = 69;
    tile->y0 = -26;
    tile->h = 52;
    LSTORE(gRadarRGBTable2_8009E3D4[param_3 - 1], &tile->r0);
    setTile(tile);
    setSemiTrans(tile, 1);
    addPrim(pOt, tile);

    NEW_PRIM(tpage2, work);
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
    LoadImage(&rect, (u_long *)&gRadar_rpk_800ABAC8[1]);
}

void menu_init_radar_helper_8003ADAC(void)
{
    gRadar_rpk_800ABAC8 = menu_rpk_get_img_8003DDB4(41);
    menu_radar_load_rpk_8003AD64();
}

void menu_radar_helper_8003ADD8(Actor_MenuMan *work, int index)
{
    DRAWENV drawEnv;
    RADAR_T *radar;

    radar = &work->field_CC_radar_data;
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

    work->field_CC_radar_data.clip_rect = drawEnv.clip;
    drawEnv.isbg = 0;
    SetDrawEnv(&work->field_CC_radar_data.dr_env[index], &drawEnv);
}

extern int              GM_AlertMode_800ABA00;
extern int              GM_AlertLevel_800ABA18;

extern int cons_current_y_800AB4B0;
int        cons_current_y_800AB4B0;

typedef enum // GM_RadarMode_800ABA80
{
    RADAR_ENABLED = 0,
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

void draw_radar_8003AEC0(Actor_MenuMan *work, unsigned char *pOt)
{
    int       alertLevel, alertMode;
    DR_AREA  *twin, *twin2, *twin3;
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

    draw_radar_helper_800390FC(work, pOt);
    addPrim(pOt, &work->field_CC_radar_data.org_env[GV_Clock_800AB920]);

    if (gFn_radar_800AB48C)
    {
        gFn_radar_800AB48C(work, pOt);
    }
    else
    {
        if (alertMode == ALERT_DISABLED)
        {
            if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_01 | GAME_FLAG_BIT_24))
            {
                alertMode = ALERT_ENABLED;
            }
        }

        switch (alertMode)
        {
        case ALERT_DISABLED:
            alertLevel = work->field_CC_radar_data.counter;

            if (alertLevel > 0)
            {
                alertLevel -= 24;

                if (alertLevel == 69)
                {
                    GM_SeSet2_80032968(0, 0x3f, 0xe);
                }

                clip = work->field_CC_radar_data.clip_rect;

                if (alertLevel >= 0)
                {
                    draw_radar_helper3_8003AA2C(work, pOt, 0, 0);
                    clip.w = alertLevel;
                    clip.x += 69;
                    clip.x -= alertLevel;
                    NEW_PRIM(twin2, work);
                    twin = twin2;
                    SetDrawArea(twin, &clip);
                    addPrim(pOt, twin);
                }

                NEW_PRIM(polyG4, work);

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

                NEW_PRIM(tpage, work);
                setDrawTPage(tpage, 1, 0, getTPage(0, 1, 960, 256));

                addPrim(pOt, tpage);

                draw_radar_helper2_800391D0(work, pOt, 0);
                clip = work->field_CC_radar_data.clip_rect;

                if (alertLevel >= 0)
                {
                    clip.w = (0x45 - alertLevel);
                }

                NEW_PRIM(twin3, work);
                twin = twin3;
                SetDrawArea(twin, &clip);
                addPrim(pOt, twin);
                work->field_CC_radar_data.counter -= 2;
            }
            else
            {
                draw_radar_helper2_800391D0(work, pOt, 0);
                cons_current_y_800AB4B0 = 0;
                cons_current_x_800AB4B4 = 0;
            }
            break;

        case ALERT_ENABLED:
        case ALERT_EVASION:
        case 3:
            work->field_CC_radar_data.counter = 93;

            if (alertMode == 1 && work->field_CC_radar_data.prev_mode == 0)
            {
                GM_SeSet2_80032968(0, 0x3f, 0x78);
            }
            draw_radar_helper3_8003AA2C(work, pOt, alertMode, alertLevel);
            break;
        }

        work->field_CC_radar_data.prev_mode = alertMode;
    }

    addPrim(pOt, &work->field_CC_radar_data.dr_env[GV_Clock_800AB920]);
}

void menu_radar_update_8003B350(Actor_MenuMan *work, unsigned char *pOt)
{
  int clipY;

  if (work->field_CC_radar_data.display_flag)
  {
    if (work->field_2A_state == 0)
    {
      if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_22) != 0)
      {
        clipY = work->field_CC_radar_data.pos_y - 16;
        if (clipY < (-63))
        {
          GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_23;
          GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_22;
          clipY = -64;
        }
      }
      else
        if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_21) != 0)
      {
        GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_23;
        clipY = work->field_CC_radar_data.pos_y + 16;
        if (clipY >= 0)
        {
          clipY = 0;
          GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_21;
        }
      }
      else
      {
        clipY = 0;
      }
      if ((GM_GameStatus_800AB3CC & (GAME_RADAR_ENABLED | GAME_FLAG_BIT_23)) != 0)
      {
        work->field_CC_radar_data.pos_y = -64;
      }
      else
      {
        work->field_CC_radar_data.pos_y = clipY;
        menu_radar_helper_8003ADD8(work, GV_Clock_800AB920);
        draw_radar_8003AEC0(work, pOt);
      }
    }
  }
}


void menu_radar_init_8003B474(Actor_MenuMan *work)
{
    unsigned char field_28_flags; // $v1

    field_28_flags = work->field_28_flags;
    work->field_2C_modules[MENU_RADAR] = menu_radar_update_8003B350;
    work->field_CC_radar_data.display_flag = 1;
    work->field_CC_radar_data.pos_x = 0;
    work->field_CC_radar_data.pos_y = 0;
    work->field_28_flags = field_28_flags | 8;
    menu_radar_helper_8003ADD8(work, 0);
    menu_radar_helper_8003ADD8(work, 1);

    work->field_CC_radar_data.org_env[0] = work->field_4C_drawEnv[0];
    work->field_CC_radar_data.org_env[1] = work->field_4C_drawEnv[1];

    menu_init_radar_helper_8003ADAC();
    gFn_radar_800AB48C = 0;
    menu_SetRadarScale_80038E28(4096);
}

void menu_radar_kill_8003B554(Actor_MenuMan *work)
{
    work->field_28_flags &= ~8u;
}
