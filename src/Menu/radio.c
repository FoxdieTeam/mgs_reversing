#include "linker.h"
#include "menuman.h"
#include "radio.h"
#include "unknown.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "radar.h"

int SECTION(".sdata") dword_800AB63C = 0; // declared

extern char *dword_800ABB04;
char        *SECTION(".sbss") dword_800ABB04;

extern MenuCallbackProc_800ABB08 SECTION(".sbss") gMenuCallbackProc_800ABB08;
MenuCallbackProc_800ABB08        SECTION(".sbss") gMenuCallbackProc_800ABB08;

extern int dword_800ABB10;
int        SECTION(".sbss") dword_800ABB10; // declared

extern unsigned char menu_current_debug_screen_800ABB20;
unsigned char        SECTION(".sbss") menu_current_debug_screen_800ABB20;

extern short word_800ABB22;
short        SECTION(".sbss") word_800ABB22;

extern DG_TEX *dword_800ABB24;
DG_TEX        *SECTION(".sbss") dword_800ABB24;

extern int gRadioClut_800ABAFC;
int        SECTION(".sbss") gRadioClut_800ABAFC;

extern int dword_800ABB1C;
int        dword_800ABB1C;

extern short word_800AB640;
short        word_800AB640;

extern short word_800ABB18;
short        word_800ABB18;

extern int dword_800ABB14;
int        dword_800ABB14;

extern int dword_800AB648;
int        dword_800AB648;

extern int dword_800AB644;
int        dword_800AB644;

extern int   GV_Time_800AB330;

extern DG_TEX gTextureRecs_800B1F50[512];

extern PANEL_TEXTURE     dword_800BDA10;
extern PANEL_TEXTURE     dword_800BDA30;
extern RadioIncomingCall gRadioIncomingCall_8009E708;
extern int               GV_PadMask_800AB374;
extern int               GV_Clock_800AB920;

extern char dword_800AB610[8];

extern const char aCall[]; // = "call"

extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;
extern int DG_FrameRate_8009D45C;
extern int DG_UnDrawFrameCount_800AB380;

extern int gDiskNum_800ACBF0;

extern GV_Heap MemorySystems_800AD2F0[ 3 ];

extern char menu_string_format_8009E714[];

char dword_8009E60C[] = {0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B, 0x7B, 0x25, 0x7F, 0x6F, 0x00, 0x00};

RadioUnknown dword_8009E618 =
{
    {{1, 0, 7, 2}, {0, 1, 2, 7}, {7, 1, 2, 7}, {1, 7, 7, 2}, {0, 9, 2, 7}, {7, 9, 2, 7}, {1, 15, 7, 2}},
    0x3D472E,
    0x3D472E
};

RadioUnknown dword_8009E63C =
{
    {{1, 0, 5, 2}, {0, 1, 2, 6}, {5, 1, 2, 6}, {1, 6, 5, 2}, {0, 8, 2, 6}, {5, 8, 2, 6}, {1, 13, 5, 2}},
    0x3D472E,
    0x3D472E
};

char dword_8009E660[] = {10, 10, 15, 12};

Radio_8009E664 dword_8009E664[] = {
//    x0   y0   w   h    r0    g0    b0  code (code = TILE)
    {120,  58, 80, 48, 0x13, 0x1F, 0x1A, 0x60},
    {116,  55,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {199,  55,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {116, 107,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {199, 107,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {121,  55, 78,  1, 0x20, 0x30, 0x29, 0x60},
    {121, 108, 78,  1, 0x20, 0x30, 0x29, 0x60},
    {129,  38, 62, 10, 0x13, 0x1F, 0x1A, 0x60},
    {129, 117, 62, 10, 0x13, 0x1F, 0x1A, 0x60},
    {90,   76, 25, 11, 0x13, 0x1F, 0x1A, 0x60},
    {205,  76, 25, 11, 0x13, 0x1F, 0x1A, 0x60},
    {84,   38, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193,  38, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {84,  126, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193, 126, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {91,   46, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193,  46, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {91,  118, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193, 118, 36,  1, 0x13, 0x1F, 0x1A, 0x60}
};

RadioCoordsStru_8009E6FC gRadioCoords_8009E6FC[] = {
    {222, 81, 214, 77, 214, 85},
    {98,  81, 106, 77, 106, 85}
};

RadioIncomingCall gRadioIncomingCall_8009E708 = {0, 0, -1, 0};

char menu_string_format_8009E714[] = {
    '.', 2,
    '@', 2,
    ':', 2,
    '_', 4,
    '!', 2,
    '?', 6,
    '+', 6,
    '-', 6,
    '/', 6,
    '*', 6,
    '{', 3,
    '}', 3,
    '\0'
};

TUnkRadioFn menu_debug_screens_8009E730[] = {
    menu_draw_mem_debug_80043678,
    menu_draw_pow_debug_80043A24,
    menu_draw_ply_debug_80043FD0,
    menu_draw_obj_debug_800442E4,
    menu_draw_tex_debug_800445F8
};

extern char aEmpty[];
extern char aMem[];
extern char aPow[];
extern char aPly[];
extern char aObj[];
extern char aTex[];

char *menu_debug_screen_labels_8009E744[] = {
    aEmpty,
    aMem,
    aPow,
    aPly,
    aObj,
    aTex
};

void menu_radio_codec_helper_helper16_8003FC54(Actor_MenuMan *pActor, unsigned char *pOt, int colour)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    NEW_PRIM(tile, pActor);

    if (colour > 255)
    {
        colour = 255;
    }
    if (colour < 0)
    {
        colour = 0;
    }
    LSTORE(colour << 0x10 | colour << 8 | colour, &tile->r0);

    setTile(tile);
    setSemiTrans(tile, 1);

    tile->x0 = 0;
    tile->y0 = 0;
    tile->w = 320;
    tile->h = 224;
    addPrim(pOt, tile);

    NEW_PRIM(tpage, pActor);

    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 960, 256));
    addPrim(pOt, tpage);
}

void sub_8003FD50(MenuPrim *pMenuPrim, int xoff, int yoff, int param_4, RadioUnknown *pRadioUnknown, int abe)
{
    int          bit;
    int          iVar1;
    int          i;
    unsigned int color;
    LINE_F4     *pLine;
    char        *pCoords;
    int          iVar2;

    bit = 1;
    iVar1 = dword_8009E60C[param_4];

    for (i = 0; i < 7; i++, bit <<= 1)
    {
        if (iVar1 & bit)
        {
            color = pRadioUnknown->color1;
        }
        else
        {
            color = pRadioUnknown->color2;

            if (color == 0)
            {
                continue;
            }
        }

        _NEW_PRIM(pLine, pMenuPrim);
        LSTORE(color, &pLine->r0);

        pCoords = pRadioUnknown->coords[i];
        pLine->x0 = pCoords[0] + xoff;
        pLine->y0 = pCoords[1] + yoff;

        iVar2 = dword_800AB610[i];

        if (iVar2 < 3)
        {
            pLine->x1 = pLine->x0 + pCoords[2] - 1;
            pLine->y1 = pLine->y0;
            pLine->x2 = pLine->x1;
            pLine->y2 = pLine->y0 + pCoords[3] - 1;
            pLine->x3 = pLine->x0;
            pLine->y3 = pLine->y2;

            if (iVar2 == 1)
            {
                pLine->x0++;
                pLine->x1--;
            }
            else
            {
                pLine->x2--;
                pLine->x3++;
            }
        }
        else
        {
            pLine->x1 = pLine->x0;
            pLine->y1 = pLine->y0 + pCoords[3] - 1;
            pLine->x2 = pLine->x1 + pCoords[2] - 1;
            pLine->y2 = pLine->y1;
            pLine->x3 = pLine->x2;
            pLine->y3 = pLine->y0;

            if (iVar2 == 3)
            {
                pLine->y0++;
                pLine->y1--;
            }
            else
            {
                pLine->y2--;
                pLine->y3++;
            }
        }

        setLineF4(pLine);
        setSemiTrans(pLine, abe);
        addPrim(pMenuPrim->mPrimBuf.mOt, pLine);
    }
}

void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pUnk, int offset_x, int offset_y);

void sub_8003FFB0(MenuPrim *pGlue, int x0, int y0, int rgb)
{
    TILE *pPrim;

    _NEW_PRIM(pPrim, pGlue);

    pPrim->w = 2;
    pPrim->h = 2;
    LSTORE(rgb, &pPrim->r0);
    pPrim->x0 = x0 + 11;
    pPrim->y0 = y0 + 15;

    setTile(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

extern RadioUnknown dword_8009E618;
extern RadioUnknown dword_8009E63C;
extern char         dword_8009E660[]; // This should have at least 5 elements (loop in menu_radio_codec_helper_helper14_helper_80040034 has 5 iterations)

void menu_radio_codec_helper_helper14_helper_80040034(MenuPrim *pGlue, int x, int y, int param_4)
{
    int           color;
    int           idx;
    int           count;
    RadioUnknown *pRadioUnknown;

    color = 0x3D472E;

    pRadioUnknown = &dword_8009E63C;
    pRadioUnknown->color1 = color;
    pRadioUnknown->color2 = 0;

    idx = 0;
    count = 10000;

    while (count > 0)
    {
        sub_8003FD50(pGlue, x, y, (param_4 / count) % 10, pRadioUnknown, 0);

        if (count == 100)
        {
            sub_8003FFB0(pGlue, x, y, color);
        }
        else if (count == 1000)
        {
            pRadioUnknown = &dword_8009E618;
            pRadioUnknown->color1 = color;
            pRadioUnknown->color2 = 0;
            y -= 2;
        }

        count /= 10;
        x += dword_8009E660[idx++];
    }
}

void menu_radio_codec_helper_helper14_helper2_800401AC(MenuPrim *pGlue, int xoff, int yoff)
{
    RadioUnknown *pUnk;
    int           i;
    int           color;

    color = 0x3D472E;

    pUnk = &dword_8009E63C;
    pUnk->color1 = color;

    for (i = 0; i < 5; xoff += dword_8009E660[i], i++) // TODO: does this read one past the end of dword_8009E660?
    {
        sub_8003FD50(pGlue, xoff, yoff, 8, pUnk, 0);
        if (i == 1)
        {
            pUnk = &dword_8009E618;
            pUnk->color1 = color;

            yoff -= 2;
        }
        else if (i == 2)
        {
            sub_8003FFB0(pGlue, xoff, yoff, color);
        }
    }
}

void menu_radio_codec_helper_helper14_helper5_800402A0(MenuPrim *pGlue, int xoff, int yoff, int param_4)
{
    int   color, color2;
    int   i;
    TILE *pTile;
    int   width;

    color2 = (param_4 < 0) ? 0x3D472E : 0;
    param_4 *= 5;

    for (i = 1; i < 44; i++)
    {
        if ((i % 5) == 0)
        {
            continue;
        }

        if (param_4 > (44 - i))
        {
            color = 0x3D472E;
        }
        else
        {
            color = color2;

            if (color == 0)
            {
                continue;
            }
        }

        _NEW_PRIM(pTile, pGlue);

        pTile->x0 = xoff;
        pTile->y0 = yoff + i;

        width = 300;
        width /= i;
        width += 3;

        if (width > 76)
        {
            width = 76;
        }

        pTile->w = width;
        pTile->h = 1;
        LSTORE(color, &pTile->r0);

        setTile(pTile);
        addPrim(pGlue->mPrimBuf.mOt, pTile);
    }
}

void menu_RadioCall_helper_800403E4(void)
{
    int        id;
    ResHeader *pRes;
    RECT       clut_rect;
    char      *buf;
    RECT      *pRect;

    id = GV_CacheID2_800152FC(aCall, 'r');
    pRes = GV_GetCache_8001538C(id);

    clut_rect.x = 960;
    clut_rect.y = 371;
    clut_rect.w = 16;
    clut_rect.h = 1;

    LoadImage(&clut_rect, (char *)pRes->field_14);

    buf = (char *)&pRes->field_14[pRes->field_8 >> 1];
    pRect = (RECT *)(buf - 8);

    gRadioClut_800ABAFC = getClut(clut_rect.x, clut_rect.y);

    pRect->x = 960;
    pRect->y = 372;

    LoadImage(pRect, buf);
}

void menu_radio_update_helper3_80040498(MenuPrim *pGlue)
{
    SPRT     *pPrim;
    DR_TPAGE *tpage;

    _NEW_PRIM(pPrim, pGlue);

    LSTORE(0x80808080, &pPrim->r0);
    pPrim->u0 = 0;
    pPrim->v0 = 116;
    pPrim->x0 = 130;
    pPrim->y0 = 49;
    pPrim->w = 60;
    pPrim->h = 12;
    pPrim->clut = gRadioClut_800ABAFC;

    setSprt(pPrim);
    setSemiTrans(pPrim, 1);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);

    _NEW_PRIM(tpage, pGlue);

    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 960, 256));

    addPrim(pGlue->mPrimBuf.mOt, tpage);
}

void menu_radio_codec_helper_helper14_helper3_80040590(MenuPrim *pGlue, Radio_8009E664 *param_2, int cnt, int xoff, int yoff)
{
    Radio_8009E664 *tileInfo;
    TILE *tile;

    tileInfo = param_2;
    while (cnt > 0)
    {
        _NEW_PRIM(tile, pGlue);

        setlen(tile, 3); // part of setTile()
        LCOPY(&tileInfo->r0, &tile->r0);

        tile->x0 = tileInfo->x0 + xoff;
        tile->y0 = tileInfo->y0 + yoff;
        tile->w = tileInfo->w;
        tile->h = tileInfo->h;

        addPrim(pGlue->mPrimBuf.mOt, tile);
        cnt--;
        tileInfo++;
    }
}

extern RadioCoordsStru_8009E6FC gRadioCoords_8009E6FC[];

static inline RadioCoordsStru_8009E6FC *get_gRadioCoords(int idx)
{
    return &gRadioCoords_8009E6FC[idx];
}

void menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuPrim *pGlue, int xpos, int ypos, int colour, int idx)
{
    short                     coord;
    POLY_F3                  *pPoly;
    LINE_F4                  *pLine;
    RadioCoordsStru_8009E6FC *radioCoords;

    _NEW_PRIM(pPoly, pGlue);
    _NEW_PRIM(pLine, pGlue);

    LSTORE(colour, &pPoly->r0);
    LSTORE(colour, &pLine->r0);

    setPolyF3(pPoly);
    setLineF4(pLine);

    radioCoords = get_gRadioCoords(idx);
    coord = radioCoords->field_0 + xpos;
    pLine->x0 = coord;
    pPoly->x0 = coord;
    pLine->x3 = coord;
    coord = radioCoords->field_1 + ypos;
    pLine->y0 = coord;
    pPoly->y0 = coord;
    pLine->y3 = coord;
    coord = radioCoords->field_2 + xpos;
    pLine->x1 = coord;
    pPoly->x1 = coord;
    coord = radioCoords->field_3 + ypos;
    pLine->y1 = coord;
    pPoly->y1 = coord;
    coord = radioCoords->field_4 + xpos;
    pLine->x2 = coord;
    pPoly->x2 = coord;
    coord = radioCoords->field_5 + ypos;
    pLine->y2 = coord;
    pPoly->y2 = coord;

    addPrim(pGlue->mPrimBuf.mOt, pPoly);
    addPrim(pGlue->mPrimBuf.mOt, pLine);
}

extern char aP3t3t[];  // = "P#3T#3T";
extern char aMemory[]; // = "MEMORY";

void menu_radio_codec_helper_helper14_helper6_800407A4(MenuPrim *pGlue, int xpos, int ypos, int flags)
{
    unsigned colour;

    if (flags < 0)
    {
        flags = 0xf; // Go into all branches below
        colour = 0x3d472e;
    }
    else
    {
        colour = 0x3d472e;
    }

    if (flags & 1)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x90;
        conf.ypos = ypos + 0x28;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aP3t3t);
    }
    if (flags & 2)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x86;
        conf.ypos = ypos + 0x77;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aMemory);
    }
    if (flags & 4)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 0);
    }
    if (flags & 8)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 1);
    }
    return;
}

void menu_radio_codec_helper_helper14_helper4_800408BC(MenuPrim *pGlue, int x, int y, int w, int h, int x2, int y2)
{
    TILE     *pTile;
    DR_TPAGE *pTpage;
    SPRT     *pSprt;
    SPRT     *pSprt2;
    int       i, j;
    int       ia, ja;
    int       color;
    int       color2;

    _NEW_PRIM(pTile, pGlue);

    LSTORE(0, &pTile->r0);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setTile(pTile);
    addPrim(pGlue->mPrimBuf.mOt, pTile);

    _NEW_PRIM(pTpage, pGlue);
    _NEW_PRIM(pSprt, pGlue);

    color2 = 0x808080;
    if (GV_Clock_800AB920 == 0)
    {
        setDrawTPage(pTpage, 0, 1, 0x120);
        pSprt->u0 = x;
    }
    else
    {
        setDrawTPage(pTpage, 0, 1, 0x124);
        pSprt->u0 = x + 64;
    }

    pSprt->v0 = y;
    pSprt->w = w;
    pSprt->h = h;
    pSprt->x0 = x2;
    pSprt->y0 = y2;

    setSprt(pSprt);
    LSTORE(0x66000000 | color2, &pSprt->r0);

    addPrim(pGlue->mPrimBuf.mOt, pSprt);
    color2 >>= 1;

    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            ia = abs(i);
            ja = abs(j);

            color = color2;

            if ((ja + ia) == 2)
            {
                color >>= 1;
            }

            if ((j != 0) || (i != 0))
            {
                _NEW_PRIM(pSprt2, pGlue);

                *pSprt2 = *pSprt;
                LSTORE(0x66000000 | color, &pSprt2->r0);

                pSprt2->x0 += j;
                pSprt2->y0 += i;

                addPrim(pGlue->mPrimBuf.mOt, pSprt2);
            }
        }
    }

    addPrim(pGlue->mPrimBuf.mOt, pTpage);
}

void menu_radio_codec_helper_helper15_80040B8C(MenuPrim *pGlue)
{
    DR_TPAGE *tpage1, *tpage2;
    SPRT     *sprt1, *sprt2;
    int       time;
    short     w, w_2;
    short     u0, u0_2;

    time = (GV_Time_800AB330 / 2) % 128;

    _NEW_PRIM(tpage1, pGlue);
    _NEW_PRIM(tpage2, pGlue);

    if (GV_Clock_800AB920 == 0)
    {
        setDrawTPage(tpage1, 0, 1, getTPage(2, 1, 0, 0));
        setDrawTPage(tpage2, 0, 1, getTPage(2, 1, 256, 0));

        u0 = 0;
        w = 256;
        u0_2 = 0;
        w_2 = 64;
    }
    else
    {
        setDrawTPage(tpage1, 0, 1, getTPage(2, 1, 256, 0));
        setDrawTPage(tpage2, 0, 1, getTPage(2, 1, 512, 0));

        u0 = 64;
        w = 192;
        u0_2 = 0;
        w_2 = 128;
    }

    _NEW_PRIM(sprt1, pGlue);

    LSTORE(0x181818, &sprt1->r0);
    sprt1->y0 = time;
    sprt1->x0 = 0;
    sprt1->w = w;
    sprt1->u0 = u0;
    sprt1->h = 8;
    sprt1->v0 = time;

    setSprt(sprt1);
    setSemiTrans(sprt1, 1);

    addPrim(pGlue->mPrimBuf.mOt, sprt1);
    addPrim(pGlue->mPrimBuf.mOt, tpage1);

    _NEW_PRIM(sprt2, pGlue);

    *sprt2 = *sprt1;
    sprt2->x0 = w;
    sprt2->w = w_2;
    sprt2->u0 = u0_2;

    addPrim(pGlue->mPrimBuf.mOt, sprt2);
    addPrim(pGlue->mPrimBuf.mOt, tpage2);
}

extern int dword_800ABB00;
int        SECTION(".sbss") dword_800ABB00;

extern int dword_800ABAF8;
int        SECTION(".sbss") dword_800ABAF8;

extern Radio_8009E664 dword_8009E664[];

void menu_radio_codec_helper_helper14_80040DC4(Actor_MenuMan *pActor, int param_2)
{
    DR_TPAGE *tpage;
    DR_STP   *stp;
    MenuPrim *pGlue;

    if (pActor->field_210 != 11 && pActor->field_210 != 14)
    {
        pGlue = pActor->field_20_otBuf;
        menu_radio_codec_helper_helper14_helper4_800408BC(pGlue, 0, 128, 140, 89, 90, 30);
        menu_radio_codec_helper_helper14_helper6_800407A4(pGlue, -90, 90, dword_800ABB00);
        menu_radio_codec_helper_helper14_helper_80040034(pGlue, 51, 178, param_2);
        menu_radio_codec_helper_helper14_helper5_800402A0(pGlue, 32, 149, dword_800ABAF8);
        menu_radio_codec_helper_helper14_helper6_800407A4(pGlue, 0, -8, -1);
        menu_radio_codec_helper_helper14_helper2_800401AC(pGlue, 141, 80);
        menu_radio_codec_helper_helper14_helper5_800402A0(pGlue, 122, 51, -1);
        menu_radio_codec_helper_helper14_helper3_80040590(pGlue, dword_8009E664, 19, 0, -8);

        _NEW_PRIM(stp, pGlue);
        SetDrawStp(stp, 1);
        addPrim(pGlue->mPrimBuf.mOt, stp);

        _NEW_PRIM(tpage, pGlue);
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(pGlue->mPrimBuf.mOt, tpage);
    }
}

extern RECT rect_800AB630;
RECT        SECTION(".sdata") rect_800AB630;

void init_radio_message_board_80040F74(Actor_MenuMan *pActor)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (pActor->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory_8001619C(ptr_local_kcb, sizeof(KCB));
        ClearImage(&rect_800AB630, 0, 0, 0);

        font_init_kcb_80044BE0(ptr_local_kcb, &rect_800AB630, 960, 510);
        font_set_kcb_80044C90(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory_80015EB8(0, font_get_buffer_size_80044F38(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer_80044FD8(ptr_local_kcb, allocated_kcb + 1);
        font_set_color_80044DC4(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color_80044DC4(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color_80044DC4(ptr_local_kcb, 2, 0x3a4b, 0);
        font_set_color_80044DC4(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update_80046980(ptr_local_kcb);

        pActor->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        dword_800ABB04 = NULL;
    }
}

void menu_radio_codec_helper__helper13_800410E4(Actor_MenuMan *pActor, char *string)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = string;
    font_print_string_800469A4(kcb, string);
    font_update_8004695C(kcb);
}

void sub_80041118(Actor_MenuMan *pActor)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = NULL;
    font_clear_800468FC(kcb);
    font_update_8004695C(kcb);
}

int draw_radio_message_8004114C(Actor_MenuMan *pActor, unsigned char *pOt)
{
    KCB  *kcb;
    SPRT *pPrim;

    if (!dword_800ABB04)
    {
        return 0;
    }

    kcb = pActor->field_214_font;

    NEW_PRIM(pPrim, pActor);

    setRGB0(pPrim, 128, 128, 128);

    pPrim->u0 = (rect_800AB630.x % 64) * 65536 >> 0xe; // FIXME
    pPrim->v0 = rect_800AB630.y;
    pPrim->w = 252;
    pPrim->h = 76;
    pPrim->clut = 32700;
    pPrim->x0 = (320 - kcb->char_arr[7]) / 2;
    pPrim->y0 = 132;

    setSprt(pPrim);
    addPrim(pOt, pPrim);
    return 1;
}

void sub_8004124C(Actor_MenuMan *pActor)
{
    GV_FreeMemory_80015FD0(0, pActor->field_214_font);
    pActor->field_214_font = NULL;
    dword_800ABB04 = NULL;
}

int menu_radio_codec_helper_helper12_80041280(Actor_MenuMan *pActor, unsigned char *pOt, GV_PAD *pPad)
{
    menu_chara_struct *pMenuChara;
    KCB               *kcb;
    int                last_index;
    int                var_s7;
    int                var_s2;
    int                index;
    int                ypos;
    int                color;
    char              *string;

    pMenuChara = pActor->field_218;
    kcb = pActor->field_214_font;

    dword_800ABB04 = pMenuChara->field_C_pScript;
    last_index = pMenuChara->field_1A_index;

    if ((pPad->press & PAD_UP) && (pMenuChara->field_1A_index > 0))
    {
        pMenuChara->field_1A_index--;
    }

    if (pPad->press & PAD_DOWN)
    {
        pMenuChara->field_1A_index++;
    }

    var_s7 = 0;
    var_s2 = 0;
    index = 0;
    ypos = kcb->char_arr[3];

    font_clear_800468FC(kcb);

    GCL_SetArgTop_80020690(pMenuChara->field_C_pScript);

    while (var_s2 >= 0)
    {
        color = 0;
        string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());

        if (index == pMenuChara->field_1A_index)
        {
            color = 1;
            var_s2 = 1;
        }

        if (!GCL_Get_Param_Result_80020AA4())
        {
            if (var_s2 == 0)
            {
                pMenuChara->field_1A_index = index;
                color = 1;
            }

            var_s2 = -1;
        }

        font_draw_string_80045D0C(kcb, 0, ypos, string, color);

        if (var_s7 < kcb->char_arr[7])
        {
            var_s7 = kcb->char_arr[7];
        }

        ypos += 18;
        index++;
    }

    if (last_index != pMenuChara->field_1A_index)
    {
        GM_SeSet2_80032968(0, 63, 31); // Menu beep sound
    }

    font_update_8004695C(kcb);

    kcb->char_arr[7] = var_s7;

    if (pPad->press & PAD_CIRCLE)
    {
        GM_LastResultFlag = pMenuChara->field_1A_index;
        sub_80041118(pActor);
        return 1;
    }

    return 0;
}

void draw_radio_wait_mark_8004143C(Actor_MenuMan *pActor, unsigned char *pOt)
{
    MenuPrim *pOtBuffer; // $v1
    POLY_F3 *pPrim; // $a0

    if ( GV_Time_800AB330 % 16 >= 4 )
    {
        pOtBuffer = pActor->field_20_otBuf;
        _NEW_PRIM(pPrim, pOtBuffer);
        pPrim->x1 = 288;
        pPrim->y1 = 210;

        pPrim->x0 = pPrim->x1 - 4;
        pPrim->x2 = pPrim->x1 + 4;

        pPrim->y0 = pPrim->y2 = pPrim->y1 - 4;

         *(int *)&pPrim->r0 = 0x80808080;
        setPolyF3(pPrim);
        addPrim(pOt, pPrim);
    }
}

extern int dword_800AB638;
int        SECTION(".sbss") dword_800AB638;

void menu_radio_codec_helper_helper11_8004150C(Actor_MenuMan *pActor)
{
    int   pRadioCode;
    short dword_800AB638_copy;

    init_radio_message_board_80040F74(pActor);
    pActor->field_212 = 0x1e;
    GM_SeSet2_80032968(0, 0x3f, 0x56);
    pRadioCode = menu_GetRadioCode_800497C4(dword_800AB638);
    if (pRadioCode >= 0)
    {
        sub_80047D70(pActor, dword_800AB638, pRadioCode);
        dword_800AB638_copy = dword_800AB638;
        pActor->field_210 = 2;
        gMenuCallbackProc_800ABB08.type = 0;
        gMenuCallbackProc_800ABB08.param2 = dword_800AB638_copy;
        return;
    }

    pActor->field_210 = 9;
}

void menu_radio_codec_helper_8004158C(Actor_MenuMan *pActor, unsigned char *pOt, GV_PAD *pPad)
{
    menu_chara_struct *pCharaStruct;
    menu_chara_struct *pCharaStruct2;
    menu_chara_struct *pCharaStruct3;
    int                ret1;
    int                ret2;
    int                direction;
    DR_TPAGE          *tpage1;
    DR_TPAGE          *tpage2;
    void              *subtitles;

    if (word_800AB640 == 0)
    {
        if (word_800ABB18 == 0)
        {
            goto skip_helper16;
        }
    }
    else
    {
        word_800ABB18 += word_800AB640;
        if (word_800ABB18 >= 0xFF)
        {
            word_800ABB18 = 0xFF;
            word_800AB640 = 0;
        }
        else if (word_800ABB18 <= 0)
        {
            word_800ABB18 = 0;
            word_800AB640 = 0;
        }
    }

    menu_radio_codec_helper_helper16_8003FC54(pActor, pOt, word_800ABB18);
skip_helper16:

    switch (pActor->field_210)
    {
    case 0:
        if (word_800AB640 == 0)
        {
            pActor->field_210 = 1;
        }
        break;
    case 1:
        if (gRadioIncomingCall_8009E708.field_0 > 0)
        {
            if (gRadioIncomingCall_8009E708.field_2_timer < 0)
            {
                gMenuCallbackProc_800ABB08.type = (~gRadioIncomingCall_8009E708.field_2_timer << 4) | 2;
            }
            else
            {
                gMenuCallbackProc_800ABB08.type = 1;
            }
            gMenuCallbackProc_800ABB08.param2 = gRadioIncomingCall_8009E708.field_0;
            dword_800AB638 = gRadioIncomingCall_8009E708.field_0;
            sub_80047D70(pActor, gRadioIncomingCall_8009E708.field_0, gRadioIncomingCall_8009E708.field_4);
            pActor->field_210 = 2;
            init_radio_message_board_80040F74(pActor);
            gRadioIncomingCall_8009E708.field_0 = 0;
        }
        else
        {
            dword_800ABB00 = 0;
            if (pPad->press & (PAD_SELECT | PAD_CROSS))
            {
                pActor->field_212 = 0;
                pActor->field_210 = 0x12;
            }
            else if (pPad->press & PAD_DOWN)
            {
                dword_800ABB00 = 2;
                menu_radio_codec_helper_helper4_8004DE20(pActor);
                pActor->field_210 = 0xA;
                GM_SeSet2_80032968(0, 0x3F, 0x55);
            }
            else if (pPad->press & (PAD_UP | PAD_CIRCLE))
            {
                dword_800ABB00 = 1;
                menu_radio_codec_helper_helper11_8004150C(pActor);
            }
            else if (pPad->status & (PAD_LEFT | PAD_RIGHT))
            {
                if (pPad->status & PAD_LEFT)
                {
                    direction = -1;
                    dword_800ABB00 = 8;
                }
                else
                {
                    direction = 1;
                    dword_800ABB00 = 4;
                }
                if (dword_800ABB10 == direction)
                {
                    if (dword_800AB63C < 10)
                    {
                        dword_800AB63C++;
                    }
                    else if (direction != 0)
                    {
                        dword_800AB638 += direction;
                        GM_SeSet2_80032968(0, 0x3F, 0x67);
                        dword_800AB63C++;
                    }
                }
                else
                {
                    dword_800AB63C = 0;
                    dword_800ABB10 = direction;
                    dword_800AB638 += direction;
                    GM_SeSet2_80032968(0, 0x3F, 0x67);
                }
                if (dword_800AB638 >= 14200)
                {
                    dword_800AB638 = 14000;
                }
                else if (dword_800AB638 < 14000)
                {
                    dword_800AB638 = 14199;
                }
            }
            else
            {
                dword_800ABB10 = 0;
                dword_800AB63C = 0;
            }

            if (GV_Time_800AB330 % 64 < 0x34)
            {
                menu_Text_XY_Flags_80038B34(0xA0, 0x82, 2);
                menu_Color_80038B4C(0x2E, 0x47, 0x3D);
                menu_Text_80038C38("PRESS SELECT TO EXIT");
                menu_Text_Init_80038B98();
            }
        }
        break;
    case 10:
        menu_radio_codec_helper_helper5_8004D628(pActor, pOt);
        ret1 = menu_radio_codec_helper_helper2_8004DF68(pActor, pPad);
        if (pPad->press & PAD_SELECT)
        {
            pActor->field_212 = 0;
            pActor->field_210 = 0x12;
            menu_radio_codec_helper__helper3_sub_8004DF44(pActor);
            sub_8004124C(pActor);
        }
        else if (ret1 != 0)
        {
            menu_radio_codec_helper__helper3_sub_8004DF44(pActor);
            sub_8004124C(pActor);
            if (ret1 >= 0)
            {
                dword_800AB638 = ret1;
                menu_radio_codec_helper_helper11_8004150C(pActor);
            }
            else
            {
                pActor->field_210 = 1;
            }
        }
        break;
    case 2:
        pActor->field_212--;
        if (pActor->field_212 > 0)
        {
            menu_radio_codec_helper_helper9_80047FF4();
        }
        else if (menu_radio_codec_helper_helper9_80047FF4() <= 0)
        {
            dword_800ABAF8 = 0;
            pActor->field_210 = 3;
            menu_radio_codec_state_2_helper_80048024(pActor);
            pActor->field_212 = 0x10;
            if (!(gMenuCallbackProc_800ABB08.type & 0x10))
            {
                GM_SeSet2_80032968(0, 0x3F, 0x6C);
            }
        }
        break;
    case 3:
        pCharaStruct = pActor->field_218;
        if (pCharaStruct->field_0_state != 5)
        {
            if (pActor->field_212 > 0)
            {
                if (pActor->field_212 == 8)
                {
                    if (gMenuCallbackProc_800ABB08.type & 0x10)
                    {
                        menu_radio_codec_helper_helper10_80047EFC(pActor, 0);
                        word_800AB640 = -0x20;
                    }
                    else
                    {
                        menu_radio_codec_helper_helper10_80047EFC(pActor, 1);
                    }
                }
                pActor->field_212--;
                dword_800ABAF8 = (0x10 - pActor->field_212) / 2;
            }
            else
            {
                switch (pCharaStruct->field_0_state)
                {
                case 0:
                    break;
                case 1:
                    if (pCharaStruct->field_14_bInExecBlock == 0)
                    {
                        menu_radio_codec_helper__helper13_800410E4(pActor, pCharaStruct->field_C_pScript);
                        pActor->field_210 = 4;
                        pActor->field_212 = pPad->status;
                    }
                    else
                    {
                        pActor->field_210 = 5;
                        pCharaStruct->field_10_subtitles = NULL;
                        pActor->field_212 = 0;
                    }
                    break;
                case 2:
                    printf("set call freq %d\n", dword_800AB638);
                    menu_radio_codec_helper_helper_8004E198(dword_800AB638);
                    pActor->field_210 = 6;
                    break;
                case 3:
                    menu_radio_init_save_mode_8004D280((int)pCharaStruct->field_C_pScript,
                                                       pCharaStruct->field_1A_index);
                    pActor->field_210 = 0xB;
                    word_800AB640 = 0x20;
                    break;
                case 4:
                    pActor->field_210 = 0x10;
                    break;
                }
            }
        }
        break;
    case 4:
        draw_radio_wait_mark_8004143C(pActor, pOt);
        if ((pPad->release &
             (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE)) &&
            pActor->field_212 == 0)
        {
            menu_radio_codec_helper_helper8_80048044();
            sub_80041118(pActor);
            pActor->field_210 = 3;
        }
        if (!(pPad->status & pActor->field_212))
        {
            pActor->field_212 = 0;
        }
        else
        {
            pActor->field_212 = pPad->status;
        }
        break;
    case 5:
        pCharaStruct2 = pActor->field_218;
        if (!(GV_Time_800AB330 & 3))
        {
            if (rand() % 4 <= 0)
            {
                if (dword_800ABAF8 < 7)
                {
                    dword_800AB644 = 1;
                }
            }
            else
            {
                if (dword_800ABAF8 >= 7)
                {
                    dword_800AB644 = -1;
                }
            }
            if (!(rand() & 7))
            {
                dword_800AB644 = -dword_800AB644;
            }
            dword_800ABAF8 += dword_800AB644;
            if (dword_800ABAF8 >= 0xA)
            {
                dword_800ABAF8 = 9;
            }
            else if (dword_800ABAF8 < 6)
            {
                dword_800ABAF8 = 6;
            }
        }
        if (pCharaStruct2->field_14_bInExecBlock == 0)
        {
            pActor->field_210 = 3;
        }
        else
        {
            if (!(pCharaStruct2->field_18 & 1) && (pPad->release & PAD_CROSS))
            {
                menu_radio_codec_helper__helper13_800410E4(pActor, pCharaStruct2->field_C_pScript);
                dword_800ABAF8 = 8;
                pCharaStruct2->field_14_bInExecBlock = 0;
                pCharaStruct2->field_18 |= 0x100;
                GM_StreamPlayStop_80037D64();
                if (pCharaStruct2->field_0_state == 1)
                {
                    pActor->field_210 = 4;
                }
                else
                {
                    pActor->field_210 = 3;
                }
            }
            else
            {
                if (pCharaStruct2->field_0_state == 2)
                {
                    pActor->field_210 = 6;
                }
                else if (pCharaStruct2->field_0_state != 1)
                {
                    break;
                }

                subtitles = menu_radio_codec_helper_helper17_80038678();
                if (pCharaStruct2->field_10_subtitles != subtitles)
                {
                    if (subtitles == NULL)
                    {
                        sub_80041118(pActor);
                        menu_radio_codec_helper_helper8_80048044(pActor);
                    }
                    else
                    {
                        menu_radio_codec_helper__helper13_800410E4(pActor, pCharaStruct2->field_C_pScript);
                    }
                    pCharaStruct2->field_10_subtitles = subtitles;
                }
            }
        }
        break;
    case 9:
        if (pActor->field_212 > 0)
        {
            pActor->field_212--;
            if (pActor->field_212 == 0)
            {
                if (GM_GameStatusFlag & 0x100)
                {
                    menu_radio_codec_helper__helper13_800410E4(pActor, "NO RESPONSE");
                }
                else
                {
                    // 応 ありません。
                    // (Translation: Answer No.)
                    menu_radio_codec_helper__helper13_800410E4(
                        pActor, "\x90\xAD\x90\xAE\x81\x02\x81\x4A\x81\x3E\x81\x1B\x81\x53\xD0\x03");
                }
            }
        }
        else
        {
            draw_radio_wait_mark_8004143C(pActor, pOt);
            if (pPad->press &
                (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE))
            {
                pActor->field_210 = 7;
            }
        }
        break;
    case 6:
        if (!(gMenuCallbackProc_800ABB08.type & 0x20))
        {
            menu_radio_codec_helper_helper3_80047F44(pActor, 1);
        }
        pActor->field_210 = 7;
    case 7:
        pCharaStruct3 = pActor->field_218;
        dword_800ABAF8 = 0;
        if (gMenuCallbackProc_800ABB08.type & 0x20)
        {
            sub_8004124C(pActor);
            word_800AB640 = 0x10;
            pActor->field_212 = 0;
            pActor->field_210 = 0x13;
        }
        else if (pCharaStruct3->field_1C_radioDatFragment != NULL)
        {
            if (menu_radio_end_check_80048F98() != 0)
            {
                menu_radio_codec_helper_helper7_80048080();
                menu_radio_codec_helper__helper6_80048100();
            }
        }
        else
        {
            sub_8004124C(pActor);
            if ((gMenuCallbackProc_800ABB08.type & 0xF) == 2)
            {
                pActor->field_212 = 0;
                pActor->field_210 = 18;
            }
            else
            {
                pActor->field_210 = 1;
            }
        }
        break;
    case 18:
        if (dword_800ABB14 >= 0)
        {
            GM_VoxStream_80037E40(dword_800ABB14, 0x40000000);
            pActor->field_210 = 0x11;
            dword_800ABB14 = -1;
        }
        GM_Sound_80032C48(0x01FFFF21, 0);
        word_800AB640 = 0x10;
        pActor->field_212 = 0;
        pActor->field_210 = 0x13;
        break;
    case 19:
        if (word_800AB640 == 0)
        {
            if (pActor->field_212 == 0 && (gMenuCallbackProc_800ABB08.type & 0x20))
            {
                menu_radio_codec_helper_helper7_80048080();
            }
            pActor->field_212++;
            if (pActor->field_212 >= 3)
            {
                pActor->field_210 = 0x14;
            }
        }
        break;
    case 11:
        if (word_800ABB18 >= 0xFF)
        {
            word_800ABB18 = 0;
            word_800AB640 = 0;
            pActor->field_210 = 0xC;
        }
        break;
    case 12:
        if (menu_radio_do_file_mode_8004C418(pActor, pPad) != 0)
        {
            pActor->field_210 = 0xD;
            word_800ABB18 = 0xFF;
            word_800AB640 = -32;
            return;
        }
        return;
    case 13:
        if ((word_800ABB18 <= 0) && (pPad->status == 0))
        {
            pActor->field_210 = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    case 14:
        ret2 = menu_radio_do_file_mode_8004C418(pActor, pPad);
        if (ret2 != 0)
        {
            sub_8004124C(pActor);
            pActor->field_210 = 0xF;
            GM_Sound_80032C48(0x01FFFF21, 0);
            gMenuCallbackProc_800ABB08.param2 = 0;
            if (ret2 == 2)
            {
                GCL_RestoreVar_80021488();
                dword_800AB638 = 0x36B0;
                gMenuCallbackProc_800ABB08.param2 = gDiskNum_800ACBF0 + 1;
                return;
            }
        }
        return;
    case 15:
        pActor->field_210 = 0x14;
        return;
    case 16:
        if (menu_radio_codec_helper_helper12_80041280(pActor, pOt, pPad) != 0)
        {
            pActor->field_210 = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    }

    draw_radio_message_8004114C(pActor, pOt);

    NEW_PRIM(tpage1, pActor);
    setDrawTPage(tpage1, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage1);

    menu_radio_codec_helper_helper15_80040B8C(pActor->field_20_otBuf);
    menu_radio_draw_face_80048DB0(pActor, pActor->field_218);
    menu_radio_codec_helper_helper14_80040DC4(pActor, dword_800AB638);

    NEW_PRIM(tpage2, pActor);
    setDrawTPage(tpage2, 0, 1, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage2);
}

void menu_radio_update_helper5_80042160(Actor_MenuMan *menuMan)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    menuMan->field_212 = 8;
    menuMan->field_210 = 0;
    menu_radio_codec_create_state_80047CE4(menuMan);
}

void menu_radio_init_nullsub_80042190(Actor_MenuMan *pActor)
{
}

void menu_radio_update_80042198(Actor_MenuMan *pActor, unsigned char *pOt)
{
    GCL_ARGS args;
    long     argv[2];

    GV_PAD      *pPad;
    int          timer;
    int          streamStatus;
    int          lastCode;
    unsigned int state;

    state = pActor->field_2A_state;
    pPad = pActor->field_24_pInput;
    if (GM_PlayerStatus_800ABA50 & 0x8000)
    {
        return;
    }

    if (state == 0)
    {
        if (!(GM_GameStatus_800AB3CC & 0x2420) && GV_PauseLevel_800AB928 == 0)
        {
            if ((gRadioIncomingCall_8009E708.field_0 > 0 && gRadioIncomingCall_8009E708.field_2_timer < 0) ||
                pPad->press & PAD_SELECT)
            {
                dword_800ABB1C = DG_FrameRate_8009D45C;
                DG_FrameRate_8009D45C = 2;
                gMenuCallbackProc_800ABB08.type = 0xF;
                GM_GameStatus_800AB3CC &= ~0x18000000;
                pActor->field_2A_state = 4;
                menu_radio_update_helper2_80038A7C();
                menu_JimakuClear_80049518();
                GV_PauseLevel_800AB928 |= 1;
                DG_FreeObjectQueue_800183D4();
                DG_BackGroundBlack_80018520();
                GV_SetPacketTempMemory_80014C28();
                menu_radio_update_helper5_80042160(pActor);
                word_800AB640 = -32;
                word_800ABB18 = 0xFF;
                if (gRadioIncomingCall_8009E708.field_0 > 0)
                {
                    dword_800AB638 = gRadioIncomingCall_8009E708.field_0;
                    if (gRadioIncomingCall_8009E708.field_2_timer == -2 ||
                        gRadioIncomingCall_8009E708.field_2_timer == -4)
                    {
                        word_800AB640 = 0;
                        pActor->field_210 = 1;
                    }
                }
                if (gRadioIncomingCall_8009E708.field_8 != 0)
                {
                    gRadioIncomingCall_8009E708.field_2_timer = -1;
                }
                pActor->field_214_font = NULL;
                streamStatus = GM_StreamStatus_80037CD8();
                if (streamStatus != -1)
                {
                    lastCode = GM_StreamGetLastCode_80037DC8();
                    dword_800ABB14 = lastCode;
                    printf("GetPotion %d\n", lastCode);
                }
                else
                {
                    dword_800ABB14 = streamStatus;
                }
                GM_StreamPlayStop_80037D64();
                DG_UnDrawFrameCount_800AB380 = 2;
                dword_800AB648 = 3;
                GM_Sound_80032C48(0x1ffff20, 0);
                if (gRadioIncomingCall_8009E708.field_0 >= 1 && gRadioIncomingCall_8009E708.field_0 <= 2)
                {
                    init_radio_message_board_80040F74(pActor);
                    if (gRadioIncomingCall_8009E708.field_0 == 1)
                    {
                        menu_radio_update_helper4_8004D2D0(gRadioIncomingCall_8009E708.field_4);
                    }
                    else
                    {
                        menu_radio_init_save_mode_8004D280((int)gRadioIncomingCall_8009E708.field_4, 0);
                    }
                    pActor->field_210 = 14;
                    gMenuCallbackProc_800ABB08.type = 1;
                }
            }
            if (gRadioIncomingCall_8009E708.field_0 > 0 && gRadioIncomingCall_8009E708.field_2_timer > 0)
            {
                if (--gRadioIncomingCall_8009E708.field_2_timer == 0)
                {
                    if (gRadioIncomingCall_8009E708.field_8 != 0)
                    {
                        gRadioIncomingCall_8009E708.field_2_timer = -1;
                        return;
                    }
                    gRadioIncomingCall_8009E708.field_0 = 0;
                    return;
                }
                if (gRadioIncomingCall_8009E708.field_8 != 0 || gRadioIncomingCall_8009E708.field_2_timer > 80)
                {
                    timer = (399 - gRadioIncomingCall_8009E708.field_2_timer) % 40;
                    if (timer < 26 && timer % 13 < 8)
                    {
                        menu_radio_update_helper3_80040498(pActor->field_20_otBuf);
                        menu_Color_80038B4C(0xFF, 0xFF, 0xFF);
                        menu_Text_XY_Flags_80038B34(0xA0, 0x3F, 2);
                        menu_Text_80038C38("PUSH SELECT");
                        menu_Text_Init_80038B98();
                    }
                    if (timer == 0 &&
                        (gRadioIncomingCall_8009E708.field_2_timer > 240 || gRadioIncomingCall_8009E708.field_8 != 0))
                    {
                        GM_SeSet2_80032968(0, 0x3F, 0x10);
                        return;
                    }
                }
            }
        }
    }
    else if (state == 4)
    {
        if (pActor->field_210 == 20 && GM_StreamStatus_80037CD8() != 0)
        {
            pActor->field_2A_state = 0;
            menu_radio_update_helper_80038A6C();
            menu_radio_update_helper6_80047D40(pActor);
            GV_ResetPacketMemory_80014BD8();
            GV_PauseLevel_800AB928 &= ~1;
            DG_8001844C();
            menu_radio_init_nullsub_80042190(pActor);
            DrawSync(0);
            sub_8003CB98(pActor);
            sub_8003EBDC(pActor);
            menu_radar_load_rpk_8003AD64();
            gRadioIncomingCall_8009E708.field_0 = 0;
            GM_GameStatus_800AB3CC &= ~0x80000;
            printf("callback type %d proc %X\n", gMenuCallbackProc_800ABB08.type,
                                gMenuCallbackProc_800ABB08.procNameHashed);
            if (gMenuCallbackProc_800ABB08.type != 0xF && gMenuCallbackProc_800ABB08.procNameHashed > 0)
            {
                args.argc = 2;
                args.argv = argv;
                argv[0] = gMenuCallbackProc_800ABB08.type & 0xF;
                argv[1] = gMenuCallbackProc_800ABB08.param2;
                printf("ExecProc\n");
                GCL_ExecProc_8001FF2C(gMenuCallbackProc_800ABB08.procNameHashed, &args);
            }
            DG_ChangeReso_80017154(0);
            DG_UnDrawFrameCount_800AB380 = 3;
            DG_BackGroundNormal_80018548();
            DG_FrameRate_8009D45C = dword_800ABB1C;
            printf("EXIT MUSENKI\n");
            return;
        }
        if (--dword_800AB648 == -1)
        {
            DG_ChangeReso_80017154(1);
        }
        menu_radio_codec_helper_8004158C(pActor, pOt, pPad);
    }
}

void menu_radio_init_80042700(Actor_MenuMan *pMenu)
{
    pMenu->field_2C_modules[MENU_RADIO] = menu_radio_update_80042198;
    pMenu->field_28_flags |= 0x10u;
}

void menu_radio_kill_8004271C(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~0x10u;
}

void menu_RadioCall_80042730(int param_1, int param_2, int time)
{
    gRadioIncomingCall_8009E708.field_0 = param_1;
    gRadioIncomingCall_8009E708.field_4 = param_2;

    if (time == 0)
    {
        gRadioIncomingCall_8009E708.field_2_timer = 360;
        gRadioIncomingCall_8009E708.field_8 = 0;
        menu_RadioCall_helper_800403E4();
    }

    else
    {
        if (time >= 5)
        {
            menu_RadioCall_helper_800403E4();
            gRadioIncomingCall_8009E708.field_8 = 1;
            gRadioIncomingCall_8009E708.field_2_timer = 40;
            GV_PadMask_800AB374 = 0x100;
            GM_GameStatus_800AB3CC |= 0x8000000;
        }
        else
        {
            gRadioIncomingCall_8009E708.field_2_timer = -time;
            gRadioIncomingCall_8009E708.field_8 = 0;
        }

        GM_GameStatus_800AB3CC |= 0x80000;
    }
}

void menu_SetLoad_800427E8(int procNameHashed, int param_2, short param_3)
{
    gRadioIncomingCall_8009E708.field_0 = param_3;
    gRadioIncomingCall_8009E708.field_2_timer = -1;
    gRadioIncomingCall_8009E708.field_4 = param_2;
    gMenuCallbackProc_800ABB08.procNameHashed = procNameHashed;
    gMenuCallbackProc_800ABB08.type = 1;
}

void menu_ResetCall_80042814()
{
    gRadioIncomingCall_8009E708.field_0 = 0;
    gRadioIncomingCall_8009E708.field_4 = 0;
    gRadioIncomingCall_8009E708.field_2_timer = 0;
    gRadioIncomingCall_8009E708.field_8 = 0;

    gMenuCallbackProc_800ABB08.procNameHashed = -1;
}

void menu_SetRadioCallbackProc_8004283C(int procNameHashed)
{
    gMenuCallbackProc_800ABB08.procNameHashed = procNameHashed;
}

// TODO: Functions from this point forward don't belong to radio.c!

void menu_set_string2_80043138();

extern RECT       rect_800AB64C[];
extern const char aNum[]; // = "num";
extern SPRT       gRadioNumberSprt_800bd9b0;
extern SPRT       gRadioNumberSprt2_800bd9d0;

void menu_number_init_80042848(Actor_MenuMan *pActor)
{
    RECT       rect1, rect2;
    ResHeader *pRes;
    SPRT      *pSprt;

    rect1 = rect_800AB64C[0];

    // Loads "num.res" (c70e.r) file:
    pRes = GV_GetCache_8001538C(GV_CacheID2_800152FC(aNum, 'r'));

    pRes->field_14[0] = 0; // TODO: Why zero out the first pixel of image?

    rect2.x = 960;
    rect2.y = 511;
    rect2.w = 16;
    rect2.h = 1;

    LoadImage(&rect2, (char *)pRes->field_14);
    LoadImage(&rect1, (char *)&pRes->field_14[pRes->field_8 >> 1]);

    pSprt = &gRadioNumberSprt_800bd9b0;
    setSprt(pSprt);
    pSprt->r0 = 128;
    pSprt->g0 = 128;
    pSprt->b0 = 128;
    pSprt->u0 = 0x9c;
    pSprt->v0 = 0xe8;
    pSprt->w = 6;
    pSprt->h = 7;
    pSprt->clut = 0x7ffc;

    pSprt = &gRadioNumberSprt2_800bd9d0;
    setSprt(pSprt);
    pSprt->r0 = 128;
    pSprt->g0 = 128;
    pSprt->b0 = 128;
    pSprt->u0 = 0;
    pSprt->v0 = 0xed;
    pSprt->w = 6;
    pSprt->h = 5;
    pSprt->clut = 0x7ffc;
    menu_set_string2_80043138();
}

void menu_number_kill_80042980(Actor_MenuMan *pMenu)
{
}

void menu_number_draw_80042988(MenuPrim *pOt, TextConfig *pSettings, int number)
{
    int            digit;
    SPRT          *sprtIter;
    int            x0;
    int            minimumDigits; // Pad the displayed number with leading 0s
    SPRT          *firstSprt;
    int            xpos;
    SPRT          *sprt;
    unsigned char *mOt;
    int            colour;

    x0 = 0;
    firstSprt = 0;
    mOt = pOt->mPrimBuf.mOt;
    colour = pSettings->colour;
    minimumDigits = 0;

    if (pSettings->flags & TextConfig_Flags_ePadding_40)
    {
        minimumDigits = pSettings->flags >> 8;
    }

    do
    {
        _NEW_PRIM(sprt, pOt);

        x0 -= 6;

        digit = number % 10;
        number /= 10;

        if (!firstSprt)
        {
            firstSprt = sprt;
        }

        *sprt = gRadioNumberSprt_800bd9b0;
        LSTORE(colour, &sprt->r0);
        sprt->x0 = x0;
        sprt->y0 = pSettings->ypos;
        sprt->u0 = digit * 6 - 100;
        addPrim(mOt, sprt);

        minimumDigits--;
    } while (number > 0 || minimumDigits > 0);

    if (firstSprt)
    {
        switch (pSettings->flags & 0xF)
        {
        case 0:
        default:
            xpos = pSettings->xpos - x0;
            pSettings->xpos = xpos;
            break;
        case 1:
            xpos = pSettings->xpos;
            pSettings->xpos = xpos + x0;
            break;
        case 2:
            xpos = pSettings->xpos - x0 / 2;
            break;
        }
        for (sprtIter = firstSprt; sprtIter < (SPRT *)pOt->mPrimBuf.mFreeLocation; sprtIter++)
        {
            sprtIter->x0 += xpos;
        }
    }
}

int menu_draw_number_draw_helper_80042B64(SPRT *pPrim, char *pFreeLocation, int x, int align, int flags)
{
    int offset_x0;

    if (pPrim != 0 && (char*)pPrim < pFreeLocation)
    {
        switch (flags & 0xF)
        {
        case 0:
        default:
            offset_x0 = x;
            x = align + offset_x0;
            break;

        case 1:
            x -= align;
            offset_x0 = x;
            break;

        case 2:
            offset_x0 = x - align / 2;
            x = align;
            break;

        }

        while ((char*)pPrim < pFreeLocation)
        {
            pPrim->x0 += offset_x0;
            pPrim++;
        }
    }

    return x;
}

void menu_number_draw_string_80042BF4(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
{
    SPRT        *pSprt;
    int          width;
    char        *pOt;
    int          colour;
    const char  *str2;
    unsigned int c;
    unsigned int lc;
    int          tpx, tpy;
    int          skip;
    int          xoffset;
    char        *pFormat;
    SPRT        *pSprt2;

    pSprt = NULL;
    width = 0;

    pOt = pGlue->mPrimBuf.mOt;
    colour = pTextConfig->colour;

    str2 = str;

    for (c = *str2; c != 0; c = *++str2)
    {
        if (c == '\n')
        {
            menu_draw_number_draw_helper_80042B64(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
            pTextConfig->ypos += 8;
            pSprt = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
            width = 0;
            continue;
        }

        lc = c | 0x20;

        if ((lc - '0') < 10)
        {
            tpx = (lc - '0') * 6;
            tpy = 488;
            skip = 6;
        }
        else if ((lc - 'a') < 26)
        {
            tpx = (lc - 'a') * 6;
            tpy = 493;

            if (lc == 'i')
            {
                skip = 3;
                width += 1;
            }
            else
            {
                skip = 6;
            }
        }
        else if (lc == ' ')
        {
            width += 4;
            continue;
        }
        else if (lc == '#')
        {
            width += 6;
            continue;
        }
        else
        {
            xoffset = 0;
            pFormat = menu_string_format_8009E714;

            while (1)
            {
                if (pFormat[0] == '\0')
                {
                    break;
                }

                tpx = 60 + xoffset;

                if (pFormat[0] == lc)
                {
                    break;
                }

                pFormat += 2;
                xoffset += 6;
            }

            if (pFormat[0] == '\0')
            {
                continue;
            }

            skip = pFormat[1];
            tpy = 488;

            if (skip < 3)
            {
                width += 1;
                skip += 1;
            }
        }

        _NEW_PRIM(pSprt2, pGlue);

        if (!pSprt)
        {
            pSprt = pSprt2;
        }

        *pSprt2 = gRadioNumberSprt2_800bd9d0;

        LSTORE(colour, &pSprt2->r0);

        pSprt2->x0 = width;
        pSprt2->y0 = pTextConfig->ypos;
        pSprt2->u0 = tpx;
        pSprt2->v0 = tpy;

        addPrim(pOt, pSprt2);
        width += skip;
    }

    pTextConfig->xpos = menu_draw_number_draw_helper_80042B64(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
}

void menu_number_draw_magazine_80042E38(Actor_MenuMan *pActor, unsigned int *pOt, int xoff, int yoff, int pMagSize,
                                        int pAmmo, int pSubCnt2)
{
    SPRT *sprt;
    int   i;

    for (i = 0; i < pAmmo; i++)
    {
        NEW_PRIM(sprt, pActor);

        xoff = xoff - 3;
        *sprt = gRadioNumberSprt2_800bd9d0;
        sprt->x0 = xoff;
        sprt->y0 = yoff;

        if (i < pMagSize)
        {
            if (i < pSubCnt2)
            {
                sprt->r0 = 128;
                sprt->g0 = 32;
                sprt->b0 = 32;
            }
            sprt->u0 = 0xD8;
            sprt->v0 = 0xE8;
        }
        else
        {
            sprt->u0 = 0xDC;
            sprt->v0 = 0xE8;
        }

        sprt->w = 4;
        sprt->h = 9;
        addPrim(pOt, sprt);
    }
}

int menu_number_draw_80042F78(Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, int number, int flags)
{
    TextConfig textConfig; // [sp+10h] [-10h] BYREF

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, number);
    return textConfig.xpos;
}

extern SPRT gRadioNumberSprt_800bd9b0;

int menu_number_draw_number2_80042FC0(Actor_MenuMan *pActor, int xpos, int ypos, int current, int total)
{
    SPRT      *pPrim;
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.flags = 0;
    textConfig.colour = (current == 0 ? 0x64002080 : 0x64575757);
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, current);

    NEW_PRIM(pPrim, pActor);

    *pPrim = gRadioNumberSprt_800bd9b0;
    LSTORE(textConfig.colour, &pPrim->r0);
    pPrim->x0 = textConfig.xpos;
    pPrim->y0 = textConfig.ypos;
    pPrim->u0 = 224;

    addPrim(pActor->field_20_otBuf->mPrimBuf.mOt, pPrim);

    textConfig.xpos = textConfig.xpos + 6;
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, total);
    return textConfig.xpos;
}

int menu_number_draw_string_800430F0(Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, const char *str, int flags)
{
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, str);
    return textConfig.xpos;
}

extern RECT gRadioStringRect_800AB658;
RECT        SECTION(".sdata") gRadioStringRect_800AB658;

extern SPRT gRadioStringSprt_800BD9F0;

void menu_set_string2_80043138()
{
    PANEL_TEXTURE pPanelTex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&pPanelTex, 45, 44);

    gRadioStringRect_800AB658.w = pPanelTex.field_10_w / 4;
    gRadioStringRect_800AB658.h = pPanelTex.field_12_h;
    LoadImage(&gRadioStringRect_800AB658, pPanelTex.field_0_pixels);

    rect.x = 976;
    rect.y = 511;
    rect.w = 16;
    rect.h = 1;

    LoadImage(&rect, pPanelTex.field_4_word_ptr_pixels);

    gRadioStringSprt_800BD9F0.u0 = 0;
    LSTORE(0x80808080, &gRadioStringSprt_800BD9F0.r0);
    gRadioStringSprt_800BD9F0.v0 = 242;
    gRadioStringSprt_800BD9F0.w = 8;
    gRadioStringSprt_800BD9F0.h = 6;
    setSprt(&gRadioStringSprt_800BD9F0);
    setClut(&gRadioStringSprt_800BD9F0, rect.x, rect.y);
}

void menu_number_draw_string2_80043220(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
{
    SPRT        *pSprt;
    int          width;
    char        *pOt;
    int          colour;
    const char  *str2;
    unsigned int c;
    unsigned int lc;
    int          tpx, tpy;
    int          skip;
    int          xoffset;
    char        *pFormat;
    SPRT        *pSprt2;
    short        test;

    pSprt = NULL;
    width = 0;

    pOt = pGlue->mPrimBuf.mOt;
    colour = pTextConfig->colour;

    str2 = str;

    for (c = *str2; c != 0; c = *++str2)
    {
        lc = c | 0x20;

        if (c == '\n')
        {
            menu_draw_number_draw_helper_80042B64(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
            pTextConfig->ypos += 8;
            pSprt = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
            width = 0;
            continue;
        }

        if ((lc - '0') < 10)
        {
            tpx = (lc - '0') * 8;
            tpy = 248;
            skip = 9;
        }
        else if ((lc - 'a') < 26)
        {
            tpx = (lc - 'a') * 8;
            tpy = 242;

            if (lc == 'i')
            {
                skip = 4;
                width += 1;
            }
            else
            {
                skip = 9;
            }
        }
        else if (lc == ' ')
        {
            width += 4;
            continue;
        }
        else if (lc == '#')
        {
            width += (str2[1] - '0');
            str2++;
            continue;
        }
        else
        {
            xoffset = 0;
            pFormat = menu_string_format_8009E714;

            while (1)
            {
                if (pFormat[0] == '\0')
                {
                    goto loop;
                }

                tpx = xoffset + 80;

                if (pFormat[0] == lc)
                {
                    skip = pFormat[1];
                    tpy = 248;

                    if (skip < 3)
                    {
                        width += 1;
                        skip += 1;
                    }
                    else if (skip == 6)
                    {
                        skip = 9;
                    }
                    break;
                }

                pFormat += 2;
                xoffset += 8;
            }
        }

        _NEW_PRIM(pSprt2, pGlue);

        test = !pSprt;
        if (test)
        {
            pSprt = pSprt2;
        }

        *pSprt2 = gRadioStringSprt_800BD9F0;

        LSTORE(colour, &pSprt2->r0);

        pSprt2->x0 = width;
        pSprt2->y0 = pTextConfig->ypos;
        pSprt2->u0 = tpx;
        pSprt2->v0 = tpy;

        addPrim(pOt, pSprt2);
        width += skip;
loop:
    }

    pTextConfig->xpos = menu_draw_number_draw_helper_80042B64(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
}

void menu_restore_nouse_80043470()
{
    sub_8003CFE0(&dword_800BDA10, 2);
    sub_8003CFE0(&dword_800BDA30, 3);
}

void menu_init_nouse_800434A8()
{
    dword_800BDA10.field_8_bufid = 0;
    menu_init_rpk_item_8003DDCC(&dword_800BDA10, 40, 39);
    menu_init_rpk_item_8003DDCC(&dword_800BDA30, 48, 39);
    menu_restore_nouse_80043470();
}

void sub_800434F4(MenuPrim *pGlue, int offset_x, int offset_y, PANEL_TEXTURE *pUnk)
{
    SPRT *pPrim;

    _NEW_PRIM(pPrim, pGlue);

    LSTORE(0x80808080, &pPrim->r0);
    menu_init_sprt_8003D0D0(pPrim, pUnk, offset_x - 2, offset_y + 6);

    setSprt(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

void menu_draw_nouse_800435A4(MenuPrim *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA10);
}

void menu_draw_frozen_800435C8(MenuPrim *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA30);
}

void menu_draw_triangle_800435EC(MenuPrim *pGlue, Menu_Triangle *pTriangle)
{
    POLY_F3 *pPrim;

    _NEW_PRIM(pPrim, pGlue);

    LCOPY(&pTriangle->field_0_x0, &pPrim->x0);
    LCOPY(&pTriangle->field_4_x1, &pPrim->x1);
    LCOPY(&pTriangle->field_8_x2, &pPrim->x2);
    LCOPY(&pTriangle->field_C_rgb, &pPrim->r0);

    setPolyF3(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

int menu_draw_mem_debug_80043678(Actor_MenuMan *pActor, unsigned int *pOt)
{
    GV_Heap             *pHeap;
    LINE_F2             *pLine;
    int                  i;
    GV_MemoryAllocation *pAlloc;
    int                  heap_size;
    char                *alloc_start;
    LINE_G4             *pLine2;
    int                  alloc_len;
    int                  alloc_len2;
    int                  used;
    int                  units;
    int                  color;
    int                  allocated;
    int                  size;
    int                  x1;

    pHeap = MemorySystems_800AD2F0;

    NEW_PRIM(pLine, pActor);
    setXY2(pLine, 272, 120, 272, 168);

    LSTORE(0xFF0000, &pLine->r0);

    setLineF2(pLine);
    addPrim(pOt, pLine);

    used = 1;
    for (i = 0; i < 3; i++, pHeap++)
    {
        size = pHeap->mEndAddr - pHeap->mStartAddr;
        pAlloc = pHeap->mAllocs;
        heap_size = size;

        if (heap_size == 0)
        {
            continue;
        }

        allocated = 0;

        for (units = pHeap->mUnitsCount; units > 0; units--, pAlloc++)
        {
            alloc_start = pAlloc->mPDataStart;

            if (pAlloc->mAllocType == 0)
            {
                continue;
            }

            if (pAlloc->mAllocType == 1)
            {
                color = 0xFFFFFF;

                while (pAlloc[1].mAllocType == 1 && units > 2)
                {
                    pAlloc++;
                    units--;
                }
            }
            else
            {
                color = 0xFF00;

                while (pAlloc[1].mAllocType >= 2 && units > 2)
                {
                    pAlloc++;
                    units--;
                }
            }

            alloc_len = (alloc_start - (char *)pHeap->mStartAddr) * 240;
            alloc_len = (alloc_len / heap_size) + 32;

            x1 = 120 + i * 16;

            size = (char *)pAlloc[1].mPDataStart - alloc_start;

            alloc_len2 = ((char *)pAlloc[1].mPDataStart - (char *)pHeap->mStartAddr) * 240;
            alloc_len2 = (alloc_len2 / heap_size) + 32;

            if (used < 256)
            {
                NEW_PRIM(pLine2, pActor);
                setXY4(pLine2, alloc_len, x1, alloc_len2, x1, alloc_len2, 134 + i * 16, alloc_len, 134 + i * 16);
                LSTORE(0, &pLine2->r0);
                LSTORE(color, &pLine2->r1);
                LSTORE(color, &pLine2->r2);
                LSTORE(0, &pLine2->r3);

                setLineG4(pLine2);
                addPrim(pOt, pLine2);
            }

            allocated += size;
            used++;
        }

        menu_number_draw_80042F78(pActor, pOt, 300, 168 - ((3 - i) * 12), (allocated * 100) / heap_size, 1);
    }

    return used;
}

extern short word_800AB660;
short        word_800AB660;

extern short word_800AB662;
short        word_800AB662;

extern int dword_800AB664;
int        dword_800AB664;

extern int dword_800AB668;
int        dword_800AB668;

extern short word_800AB66C;
short        word_800AB66C;

extern short word_800AB66E;
short        word_800AB66E;

extern int dword_800AB670;
int        dword_800AB670;

extern short          N_ChanlPerfMax_800AB980;
extern unsigned short word_800AB982;

extern GV_PAD GV_PadData_800B05C0[4];

extern unsigned short gOldRootCnt_800B1DC8[32];

int menu_draw_pow_debug_80043A24(Actor_MenuMan *pActor, unsigned int *pOt)
{
    int             prims_used, left, right, bottom, idx, i;
    unsigned short *pCount;
    unsigned        first_count;
    LINE_G4        *pLine;
    unsigned short  delta;
    LINE_G2        *pLine2;

    prims_used = 0;

    pCount = gOldRootCnt_800B1DC8;
    first_count = *pCount++;

    left = 0;
    bottom = 136;

    for (idx = N_ChanlPerfMax_800AB980 - 1; idx > 0; idx--)
    {
        right = (*pCount++ - first_count) & 0xFFFF;

        if (right > 511)
        {
            right = 511;
        }
        right = right * 240 / 512;

        // Draw top blue bar
        NEW_PRIM(pLine, pActor);

        setXY4(pLine, left + 32, bottom, right + 32, 136, right + 32, 150, left + 32, bottom + 14);

        LSTORE(0, &pLine->r0);
        LSTORE(0xFF0000, &pLine->r1);
        LSTORE(0xFF0000, &pLine->r2);
        LSTORE(0, &pLine->r3);

        setLineG4(pLine);
        addPrim(pOt, pLine);
        prims_used++;

        bottom = 136; // to get a match
        left = right;
    }

    if (GV_PadData_800B05C0[1].press & PAD_L1)
    {
        dword_800AB668 = (dword_800AB668 + 1) % N_ChanlPerfMax_800AB980;
        dword_800AB664 = 0;
        word_800AB660 = 0;
    }

    if (dword_800AB668 == 0)
    {
        delta = gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - gOldRootCnt_800B1DC8[1];
    }
    else
    {
        delta = gOldRootCnt_800B1DC8[dword_800AB668] - gOldRootCnt_800B1DC8[dword_800AB668 - 1];
        menu_number_draw_80042F78(pActor, pOt, 270, 168, dword_800AB668, 1);
    }

    dword_800AB664 += delta;
    if (++word_800AB660 >= 128)
    {
        word_800AB662 = dword_800AB664 / word_800AB660;
        word_800AB660 = 0;
        dword_800AB664 = 0;
    }

    menu_number_draw_80042F78(pActor, pOt, 300, 168, word_800AB662, 1);
    dword_800AB670 += (unsigned short)(gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - first_count);

    if (++word_800AB66C >= 128)
    {
        word_800AB66E = dword_800AB670 / word_800AB66C;
        word_800AB66C = 0;
        dword_800AB670 = 0;
    }

    menu_number_draw_80042F78(pActor, pOt, 240, 168, word_800AB66E, 1);
    menu_number_draw_80042F78(pActor, pOt, 300, 144,
                              (unsigned short)(gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - first_count), 1);

    right = (unsigned short)(word_800AB982 - first_count);
    if (right > 511)
    {
        right = 511;
    }
    right = right * 240 / 512;

    bottom = 152; // to get a match
    i = 32;       // to get a match
    right += 32;

    // Draw bottom red bar
    NEW_PRIM(pLine, pActor);

    setXY4(pLine, 32, 152, right, 152, right, 166, 32, 166);

    LSTORE(0, &pLine->r0);
    LSTORE(0xFF, &pLine->r1);
    LSTORE(0xFF, &pLine->r2);
    LSTORE(0, &pLine->r3);

    setLineG4(pLine);
    addPrim(pOt, pLine);
    prims_used++;

    menu_number_draw_80042F78(pActor, pOt, 300, 156, (unsigned short)(word_800AB982 - first_count), 1);

    // Draw vertical bars
    for (i = 0; i <= 240; i += 24)
    {
        NEW_PRIM(pLine2, pActor);
        bottom = 132; // to get a match

        setXY2(pLine2, i + 32, 132, i + 32, 164);

        // Red for centre bar otherwise green
        if (i == 120)
        {
            LSTORE(0xFF, &pLine2->r0);
        }
        else
        {
            LSTORE(0xFF00, &pLine2->r0);
        }
        LSTORE(0, &pLine2->r1);

        setLineG2(pLine2);
        addPrim(pOt, pLine2);
        prims_used++;
    }

    return prims_used;
}

int menu_draw_ply_debug_80043FD0(Actor_MenuMan *pMenuMan, unsigned int *pOt)
{
    u_char       *chnlOt;
    int           numOTEntries;
    u_char       *otMin;
    u_char       *curPrim;
    int           primCount;
    int           totalprimCount;

    LINE_F2      *lineF2;
    LINE_G4      *lineG4;
    int           x_0_1;
    int           y_0_1;
    int           x_2_3;
    int           y_2_3;

    int           i;

    int           returnVal;

    totalprimCount = 0;
    returnVal = 0;
    y_0_1 = 0xa8;
    y_2_3 = 0xa8;

    chnlOt = DG_Chanl(0)->mOrderingTables[1 - GV_Clock_800AB920];
    numOTEntries = DG_Chanl(0)->word_6BC374_8 - 4;

    NEW_PRIM(lineF2, pMenuMan);

    setXY2(lineF2, 0x20, 0x76, 0x110, 0x76);
    LSTORE(0x800000, &lineF2->r0);
    setLineF2(lineF2);
    addPrim(pOt, lineF2);

    for (i = 0; i < 16; i++)
    {
        otMin = chnlOt + ((i << numOTEntries) * 4);
        for (curPrim = chnlOt + (((i + 1) << numOTEntries) * 4), primCount = 0;
             (otMin < curPrim) || (curPrim < chnlOt); curPrim = nextPrim(curPrim))
        {
            if (getlen(curPrim) != 0)
            {
                primCount++;
            }
        }

        totalprimCount += primCount;
        x_0_1 = i * 15;
        x_2_3 = x_0_1 + 13;
        x_0_1 += 32;
        x_2_3 += 32;

        if (primCount > 0)
        {
            primCount = primCount / 2;

            if (primCount > 176)
            {
                primCount = 176;
            }

            NEW_PRIM(lineG4, pMenuMan);
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1 - primCount, x_2_3, y_2_3 - primCount, x_2_3, y_2_3);
            LSTORE(0, &lineG4->r0);
            LSTORE(0xff00, &lineG4->r1);
            returnVal++;
            LSTORE(0xff00, &lineG4->r2);
            LSTORE(0, &lineG4->r3);
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
        else
        {
            NEW_PRIM(lineG4, pMenuMan);
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1, x_2_3, y_2_3, x_2_3, y_2_3);
            LSTORE(0, &lineG4->r0);
            LSTORE(0xff0000, &lineG4->r1);
            LSTORE(0xff0000, &lineG4->r2);
            LSTORE(0, &lineG4->r3);
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
    }

    menu_number_draw_80042F78(pMenuMan, pOt, 0x110, 0x9c, totalprimCount, 1);

    return returnVal;
}

extern char aTotalD[]; //  = "TOTAL %d\n";
extern char aClipD[];  // = "CLIP %d\n";

int menu_draw_obj_debug_800442E4(Actor_MenuMan *pActor, unsigned int *pOt)
{
    DG_OBJS **ppQueue;
    DG_OBJS  *pObjs;
    DG_OBJ   *pObj;
    LINE_G2  *pLine;
    LINE_G4  *pLine2;
    int       object_count;
    int       num_models;
    int       total;
    int       clip;

    unsigned int color;
    int          lhs;
    int          rhs;
    int          returnVal;
    int          last_color;

    int bottom, top;

    rhs = 0;
    lhs = 0;

    top = 152;
    last_color = 0;
    returnVal = 0;

    clip = 0;
    total = 0;

    object_count = DG_Chanl(0)->mTotalObjectCount;
    ppQueue = DG_Chanl(0)->mQueue;

    for (; object_count > 0; object_count--)
    {
        pObjs = *ppQueue++;

        NEW_PRIM(pLine, pActor);
        setXY2(pLine, rhs + 32, top - 6, rhs + 32, top + 19);

        LSTORE(0xFF0000, &pLine->r0);
        LSTORE(0, &pLine->r1);

        setLineG2(pLine);
        addPrim(pOt, pLine);

        pObj = pObjs->objs;
        for (num_models = pObjs->n_models; num_models > 0; num_models--)
        {
            rhs++;

            color = 0xFF00;

            if (pObj->bound_mode == 0)
            {
                color = 0xFF;
                clip++;
            }

            if (last_color == 0)
            {
                last_color = color;
            }

            bottom = 152;

            if (color != last_color)
            {
                NEW_PRIM(pLine2, pActor);

                setXY4(pLine2, lhs + 32, top, rhs + 32, bottom, rhs + 32, 165, lhs + 32, top + 13);
                top = bottom;

                LSTORE(0, &pLine2->r0);
                LSTORE(last_color, &pLine2->r1);
                LSTORE(last_color, &pLine2->r2);
                LSTORE(0, &pLine2->r3);

                setLineG4(pLine2);
                addPrim(pOt, pLine2);

                returnVal++;
                lhs = rhs;
                last_color = color;
            }

            pObj++;
            total++;
        }
    }

    bottom = 152;

    if (lhs != rhs)
    {
        NEW_PRIM(pLine2, pActor);
        returnVal++;

        setXY4(pLine2, lhs + 32, top, rhs + 32, bottom, rhs + 32, 165, (bottom = lhs + 32) /* to get a match */,
               top + 13);

        LSTORE(0, &pLine2->r0);
        LSTORE(last_color, &pLine2->r1);
        LSTORE(last_color, &pLine2->r2);
        LSTORE(0, &pLine2->r3);

        setLineG4(pLine2);
        addPrim(pOt, pLine2);
    }

    menu_Text_XY_Flags_80038B34(300, 128, 0x1);
    menu_Text_80038C38(aTotalD, total);
    menu_Text_80038C38(aClipD, clip);

    return returnVal;
}

extern GV_PAD GV_PadData_800B05C0[4];
extern char   aNoD[];  // = "No %d\n";
extern char   aIdD[];  // = "ID %d\n";
extern char   aColD[]; // = "COL %d\n";
extern char   aXDYD[]; // = "x %d y %d\n";
extern char   aWDHD[]; // = "w %d h %d\n";

int menu_draw_tex_debug_800445F8(Actor_MenuMan *pActor, unsigned int *pOt)
{
    const int textureRecsCount = sizeof(gTextureRecs_800B1F50) / sizeof(gTextureRecs_800B1F50[0]);
    short     x0, y0;
    int       i;
    DG_TEX   *iterTex;
    POLY_FT4 *pPoly;
    int       width, height;
    int       offx, offy;
    int       direction;

    iterTex = dword_800ABB24;
    direction = 0;
    if (GV_PadData_800B05C0[0].status & PAD_RIGHT)
    {
        direction = 1;
    }
    else if (GV_PadData_800B05C0[0].status & PAD_LEFT)
    {
        direction = -1;
    }
    else
    {
        word_800ABB22 = -1;
    }
    if (direction != 0)
    {
        if (word_800ABB22 <= 0)
        {
            for (i = textureRecsCount; i > 0; i--)
            {
                iterTex += direction;
                if (iterTex == &gTextureRecs_800B1F50[textureRecsCount])
                {
                    iterTex -= textureRecsCount;
                }
                if (iterTex < &gTextureRecs_800B1F50[0])
                {
                    iterTex = &gTextureRecs_800B1F50[textureRecsCount - 1];
                }
                if (iterTex->field_0_hash != 0)
                {
                    break;
                }
            }
            if (word_800ABB22 < 0)
            {
                word_800ABB22 = 10;
            }
            else if (word_800ABB22 == 0)
            {
                word_800ABB22 = 2;
            }
        }
        word_800ABB22--;
    }

    if (iterTex->field_0_hash == 0)
    {
        return 0;
    }

    dword_800ABB24 = iterTex;

    menu_Text_XY_Flags_80038B34(300, 128, 1);
    menu_Text_80038C38(aNoD, iterTex - gTextureRecs_800B1F50);
    menu_Text_80038C38(aIdD, iterTex->field_0_hash);
    menu_Text_80038C38(aColD, iterTex->field_2_bUsed.c[1]);
    menu_Text_80038C38(aXDYD, iterTex->field_8_offx, iterTex->field_9_offy);
    menu_Text_80038C38(aWDHD, iterTex->field_A_width + 1, iterTex->field_B_height + 1);

    NEW_PRIM(pPoly, pActor);

    LSTORE(0x808080, &pPoly->r0);

    setPolyFT4(pPoly);

    pPoly->clut = iterTex->field_6_clut;
    pPoly->tpage = iterTex->field_4_tPage;

    width = iterTex->field_A_width;
    height = iterTex->field_B_height;
    offx = iterTex->field_8_offx;
    offy = iterTex->field_9_offy;

    x0 = (319 - width) / 2;
    y0 = (239 - height) / 2;

    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x1 = x0 + width;
    pPoly->x2 = x0;
    pPoly->y2 = y0 + height;
    pPoly->y3 = y0 + height;
    pPoly->x3 = x0 + width;
    pPoly->u0 = offx;
    pPoly->v0 = offy;
    pPoly->u1 = offx + width;
    pPoly->v1 = offy;
    pPoly->u2 = offx;
    pPoly->v2 = offy + height;
    pPoly->u3 = offx + width;
    pPoly->v3 = offy + height;

    addPrim(pOt, pPoly);
    return 1;
}

extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;
extern int MENU_PrimUse_800AB68C;
int        MENU_PrimUse_800AB68C;

extern TUnkRadioFn menu_debug_screens_8009E730[];
extern char       *menu_debug_screen_labels_8009E744[];

void menu_draw_debug_screen_800448C0(Actor_MenuMan *pActor, unsigned int *pOt)
{
    mts_read_pad_8008C25C(2);
    if (GM_GameStatus_800AB3CC & 0x1000000)
    {
        menu_draw_pow_debug_80043A24(pActor, pOt);
        return;
    }
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_PREVENT_WEAPON_ITEM_SWITCH) && GV_PauseLevel_800AB928 != 0 &&
        (GV_PadData_800B05C0[0].press & PAD_L1))
    {
        if (menu_current_debug_screen_800ABB20 == 5)
        {
            GV_PauseLevel_800AB928 &= ~4;
        }
        menu_current_debug_screen_800ABB20++;
        if (menu_current_debug_screen_800ABB20 == 6)
        {
            menu_current_debug_screen_800ABB20 = 0;
        }
        if (menu_current_debug_screen_800ABB20 == 5)
        {
            GV_PauseLevel_800AB928 |= 4;
        }
    }
    else if (menu_current_debug_screen_800ABB20 != 0)
    {
        menu_Text_XY_Flags_80038B34(300, 8, 1);
        menu_draw_num_80038D10(MENU_PrimUse_800AB68C * 100 / 8192);
        menu_Text_XY_Flags_80038B34(300, 112, 1);
        menu_Text_80038C38(menu_debug_screen_labels_8009E744[menu_current_debug_screen_800ABB20]);
        menu_debug_screens_8009E730[menu_current_debug_screen_800ABB20 - 1](pActor, pOt);
    }
}

void menu_viewer_init_80044A70(Actor_MenuMan *param_1)
{
    menu_current_debug_screen_800ABB20 = 0;
    dword_800ABB24 = gTextureRecs_800B1F50;
    word_800ABB22 = -1;
}

void menu_viewer_kill_80044A90(Actor_MenuMan *pActor)
{
    menu_current_debug_screen_800ABB20 = 0;
    return;
}
