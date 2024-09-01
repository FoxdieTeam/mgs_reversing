#include "linker.h"
#include "menuman.h"
#include "psyq.h"
#include "radar.h"
#include "radio.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

extern char *dword_800ABB04;
char        *SECTION(".sbss") dword_800ABB04;

extern MenuCallbackProc_800ABB08 SECTION(".sbss") gMenuCallbackProc_800ABB08;
MenuCallbackProc_800ABB08        SECTION(".sbss") gMenuCallbackProc_800ABB08;

extern int dword_800ABB10;
int        SECTION(".sbss") dword_800ABB10; // declared

extern int gRadioClut_800ABAFC;
int        SECTION(".sbss") gRadioClut_800ABAFC;

extern int dword_800ABB1C;
int        dword_800ABB1C;

extern short word_800ABB18;
short        word_800ABB18;

extern int dword_800ABB14;
int        dword_800ABB14;

extern int   GV_Time_800AB330;

extern PANEL_TEXTURE     dword_800BDA10;
extern PANEL_TEXTURE     dword_800BDA30;
extern RadioIncomingCall gRadioIncomingCall_8009E708;
extern int               GV_PadMask_800AB374;
extern int               GV_Clock_800AB920;

char dword_800AB610[8] = {2, 4, 3, 1, 4, 3, 1, 0};

extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;
extern int DG_FrameRate_8009D45C;
extern int DG_UnDrawFrameCount_800AB380;

extern int gDiskNum_800ACBF0;

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

void menu_radio_codec_helper_helper16_8003FC54(MenuWork *work, unsigned char *pOt, int colour)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    NEW_PRIM(tile, work);

    if (colour > 255)
    {
        colour = 255;
    }
    if (colour < 0)
    {
        colour = 0;
    }
    LSTORE(colour << 16 | colour << 8 | colour, &tile->r0);

    setTile(tile);
    setSemiTrans(tile, 1);

    tile->x0 = 0;
    tile->y0 = 0;
    tile->w = 320;
    tile->h = 224;
    addPrim(pOt, tile);

    NEW_PRIM(tpage, work);

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

    id = GV_CacheID2("call", 'r');
    pRes = GV_GetCache(id);

    clut_rect.x = 960;
    clut_rect.y = 371;
    clut_rect.w = 16;
    clut_rect.h = 1;

    LoadImage(&clut_rect, (u_long *)pRes->field_14);

    buf = (char *)&pRes->field_14[pRes->field_8 >> 1];
    pRect = (RECT *)(buf - 8);

    gRadioClut_800ABAFC = getClut(clut_rect.x, clut_rect.y);

    pRect->x = 960;
    pRect->y = 372;

    LoadImage(pRect, (u_long *)buf);
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
        _menu_number_draw_string2_80043220(pGlue, &conf, "P#3T#3T");
    }
    if (flags & 2)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x86;
        conf.ypos = ypos + 0x77;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        _menu_number_draw_string2_80043220(pGlue, &conf, "MEMORY");
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

void menu_radio_codec_helper_helper14_80040DC4(MenuWork *work, int param_2)
{
    DR_TPAGE *tpage;
    DR_STP   *stp;
    MenuPrim *pGlue;

    if (work->field_210 != 11 && work->field_210 != 14)
    {
        pGlue = work->field_20_otBuf;
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

RECT rect_800AB630 = {960, 260, 63, 76};

void init_radio_message_board_80040F74(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&rect_800AB630, 0, 0, 0);

        font_init_kcb_80044BE0(ptr_local_kcb, &rect_800AB630, 960, 510);
        font_set_kcb_80044C90(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(0, font_get_buffer_size_80044F38(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer_80044FD8(ptr_local_kcb, allocated_kcb + 1);
        font_set_color_80044DC4(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color_80044DC4(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color_80044DC4(ptr_local_kcb, 2, 0x3a4b, 0);
        font_set_color_80044DC4(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update_80046980(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        dword_800ABB04 = NULL;
    }
}

void menu_radio_codec_helper__helper13_800410E4(MenuWork *work, char *string)
{
    KCB *kcb = work->field_214_font;
    dword_800ABB04 = string;
    font_print_string_800469A4(kcb, string);
    font_update_8004695C(kcb);
}

void sub_80041118(MenuWork *work)
{
    KCB *kcb = work->field_214_font;
    dword_800ABB04 = NULL;
    font_clear_800468FC(kcb);
    font_update_8004695C(kcb);
}

int draw_radio_message_8004114C(MenuWork *work, unsigned char *pOt)
{
    KCB  *kcb;
    SPRT *pPrim;

    if (!dword_800ABB04)
    {
        return 0;
    }

    kcb = work->field_214_font;

    NEW_PRIM(pPrim, work);

    setRGB0(pPrim, 128, 128, 128);

    pPrim->u0 = (rect_800AB630.x % 64) * 65536 >> 14; // FIXME
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

void sub_8004124C(MenuWork *work)
{
    GV_FreeMemory(0, work->field_214_font);
    work->field_214_font = NULL;
    dword_800ABB04 = NULL;
}

// nop count was incorrect to this point
// was a new function added in VR?
// or simply I made a counting mistake and no function was added

int menu_radio_codec_helper_helper12_80041280(MenuWork *work, unsigned char *pOt, GV_PAD *pPad)
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

    pMenuChara = work->field_218;
    kcb = work->field_214_font;

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

    GCL_SetArgTop(pMenuChara->field_C_pScript);

    while (var_s2 >= 0)
    {
        color = 0;
        string = GCL_ReadString(GCL_GetParamResult());

        if (index == pMenuChara->field_1A_index)
        {
            color = 1;
            var_s2 = 1;
        }

        if (!GCL_GetParamResult())
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
        sub_80041118(work);
        return 1;
    }

    return 0;
}

void draw_radio_wait_mark_8004143C(MenuWork *work, unsigned char *pOt)
{
    MenuPrim *pOtBuffer; // $v1
    POLY_F3 *pPrim; // $a0

    if ( GV_Time_800AB330 % 16 >= 4 )
    {
        pOtBuffer = work->field_20_otBuf;
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

int dword_800AB638 = 14000;

void menu_radio_codec_helper_helper11_8004150C(MenuWork *work)
{
    int   pRadioCode;
    short dword_800AB638_copy;

    init_radio_message_board_80040F74(work);
    work->field_212 = 0x1e;
    GM_SeSet2_80032968(0, 0x3f, 0x56);
    pRadioCode = MENU_GetRadioCode_800497C4(dword_800AB638);
    if (pRadioCode >= 0)
    {
        sub_80047D70(work, dword_800AB638, pRadioCode);
        dword_800AB638_copy = dword_800AB638;
        work->field_210 = 2;
        gMenuCallbackProc_800ABB08.type = 0;
        gMenuCallbackProc_800ABB08.param2 = dword_800AB638_copy;
        return;
    }

    work->field_210 = 9;
}

int   dword_800AB63C = 0;
short word_800AB640 = 0;
int   dword_800AB644 = -1;

void menu_radio_codec_helper_8004158C(MenuWork *work, unsigned char *pOt, GV_PAD *pPad)
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

    menu_radio_codec_helper_helper16_8003FC54(work, pOt, word_800ABB18);
skip_helper16:

    switch (work->field_210)
    {
    case 0:
        if (word_800AB640 == 0)
        {
            work->field_210 = 1;
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
            sub_80047D70(work, gRadioIncomingCall_8009E708.field_0, gRadioIncomingCall_8009E708.field_4);
            work->field_210 = 2;
            init_radio_message_board_80040F74(work);
            gRadioIncomingCall_8009E708.field_0 = 0;
        }
        else
        {
            dword_800ABB00 = 0;
            if (pPad->press & (PAD_SELECT | PAD_CROSS))
            {
                work->field_212 = 0;
                work->field_210 = 0x12;
            }
            else if (pPad->press & PAD_DOWN)
            {
                dword_800ABB00 = 2;
                menu_radio_codec_helper_helper4_8004DE20(work);
                work->field_210 = 0xA;
                GM_SeSet2_80032968(0, 0x3F, 0x55);
            }
            else if (pPad->press & (PAD_UP | PAD_CIRCLE))
            {
                dword_800ABB00 = 1;
                menu_radio_codec_helper_helper11_8004150C(work);
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
                MENU_Locate_80038B34(0xA0, 0x82, 2);
                MENU_Color_80038B4C(0x2E, 0x47, 0x3D);
                MENU_Printf_80038C38("PRESS SELECT TO EXIT");
                menu_Text_Init_80038B98();
            }
        }
        break;
    case 10:
        menu_radio_codec_helper_helper5_8004D628(work, pOt);
        ret1 = menu_radio_codec_helper_helper2_8004DF68(work, pPad);
        if (pPad->press & PAD_SELECT)
        {
            work->field_212 = 0;
            work->field_210 = 0x12;
            menu_radio_codec_helper__helper3_sub_8004DF44(work);
            sub_8004124C(work);
        }
        else if (ret1 != 0)
        {
            menu_radio_codec_helper__helper3_sub_8004DF44(work);
            sub_8004124C(work);
            if (ret1 >= 0)
            {
                dword_800AB638 = ret1;
                menu_radio_codec_helper_helper11_8004150C(work);
            }
            else
            {
                work->field_210 = 1;
            }
        }
        break;
    case 2:
        work->field_212--;
        if (work->field_212 > 0)
        {
            menu_radio_codec_helper_helper9_80047FF4();
        }
        else if (menu_radio_codec_helper_helper9_80047FF4() <= 0)
        {
            dword_800ABAF8 = 0;
            work->field_210 = 3;
            menu_radio_codec_state_2_helper_80048024(work);
            work->field_212 = 0x10;
            if (!(gMenuCallbackProc_800ABB08.type & 0x10))
            {
                GM_SeSet2_80032968(0, 0x3F, 0x6C);
            }
        }
        break;
    case 3:
        pCharaStruct = work->field_218;
        if (pCharaStruct->field_0_state != 5)
        {
            if (work->field_212 > 0)
            {
                if (work->field_212 == 8)
                {
                    if (gMenuCallbackProc_800ABB08.type & 0x10)
                    {
                        menu_radio_codec_helper_helper10_80047EFC(work, 0);
                        word_800AB640 = -0x20;
                    }
                    else
                    {
                        menu_radio_codec_helper_helper10_80047EFC(work, 1);
                    }
                }
                work->field_212--;
                dword_800ABAF8 = (0x10 - work->field_212) / 2;
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
                        menu_radio_codec_helper__helper13_800410E4(work, pCharaStruct->field_C_pScript);
                        work->field_210 = 4;
                        work->field_212 = pPad->status;
                    }
                    else
                    {
                        work->field_210 = 5;
                        pCharaStruct->field_10_subtitles = NULL;
                        work->field_212 = 0;
                    }
                    break;
                case 2:
                    printf("set call freq %d\n", dword_800AB638);
                    menu_radio_codec_helper_helper_8004E198(dword_800AB638);
                    work->field_210 = 6;
                    break;
                case 3:
                    menu_radio_init_save_mode_8004D280((int)pCharaStruct->field_C_pScript,
                                                       pCharaStruct->field_1A_index);
                    work->field_210 = 0xB;
                    word_800AB640 = 0x20;
                    break;
                case 4:
                    work->field_210 = 0x10;
                    break;
                }
            }
        }
        break;
    case 4:
        draw_radio_wait_mark_8004143C(work, pOt);
        if ((pPad->release &
             (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE)) &&
            work->field_212 == 0)
        {
            menu_radio_codec_helper_helper8_80048044();
            sub_80041118(work);
            work->field_210 = 3;
        }
        if (!(pPad->status & work->field_212))
        {
            work->field_212 = 0;
        }
        else
        {
            work->field_212 = pPad->status;
        }
        break;
    case 5:
        pCharaStruct2 = work->field_218;
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
            work->field_210 = 3;
        }
        else
        {
            if (!(pCharaStruct2->field_18 & 1) && (pPad->release & PAD_CROSS))
            {
                menu_radio_codec_helper__helper13_800410E4(work, pCharaStruct2->field_C_pScript);
                dword_800ABAF8 = 8;
                pCharaStruct2->field_14_bInExecBlock = 0;
                pCharaStruct2->field_18 |= 0x100;
                GM_StreamPlayStop_80037D64();
                if (pCharaStruct2->field_0_state == 1)
                {
                    work->field_210 = 4;
                }
                else
                {
                    work->field_210 = 3;
                }
            }
            else
            {
                if (pCharaStruct2->field_0_state == 2)
                {
                    work->field_210 = 6;
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
                        sub_80041118(work);
                        menu_radio_codec_helper_helper8_80048044(work);
                    }
                    else
                    {
                        menu_radio_codec_helper__helper13_800410E4(work, pCharaStruct2->field_C_pScript);
                    }
                    pCharaStruct2->field_10_subtitles = subtitles;
                }
            }
        }
        break;
    case 9:
        if (work->field_212 > 0)
        {
            work->field_212--;
            if (work->field_212 == 0)
            {
                if (GM_GameStatusFlag & 0x100)
                {
                    menu_radio_codec_helper__helper13_800410E4(work, "NO RESPONSE");
                }
                else
                {
                    // 応 ありません。
                    // (Translation: Answer No.)
                    menu_radio_codec_helper__helper13_800410E4(
                        work, "\x90\xAD\x90\xAE\x81\x02\x81\x4A\x81\x3E\x81\x1B\x81\x53\xD0\x03");
                }
            }
        }
        else
        {
            draw_radio_wait_mark_8004143C(work, pOt);
            if (pPad->press &
                (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE))
            {
                work->field_210 = 7;
            }
        }
        break;
    case 6:
        if (!(gMenuCallbackProc_800ABB08.type & 0x20))
        {
            menu_radio_codec_helper_helper3_80047F44(work, 1);
        }
        work->field_210 = 7;
    case 7:
        pCharaStruct3 = work->field_218;
        dword_800ABAF8 = 0;
        if (gMenuCallbackProc_800ABB08.type & 0x20)
        {
            sub_8004124C(work);
            word_800AB640 = 0x10;
            work->field_212 = 0;
            work->field_210 = 0x13;
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
            sub_8004124C(work);
            if ((gMenuCallbackProc_800ABB08.type & 0xF) == 2)
            {
                work->field_212 = 0;
                work->field_210 = 18;
            }
            else
            {
                work->field_210 = 1;
            }
        }
        break;
    case 18:
        if (dword_800ABB14 >= 0)
        {
            GM_VoxStream_80037E40(dword_800ABB14, 0x40000000);
            work->field_210 = 0x11;
            dword_800ABB14 = -1;
        }
        GM_Sound_80032C48(0x01ffff21, 0);
        word_800AB640 = 0x10;
        work->field_212 = 0;
        work->field_210 = 0x13;
        break;
    case 19:
        if (word_800AB640 == 0)
        {
            if (work->field_212 == 0 && (gMenuCallbackProc_800ABB08.type & 0x20))
            {
                menu_radio_codec_helper_helper7_80048080();
            }
            work->field_212++;
            if (work->field_212 >= 3)
            {
                work->field_210 = 0x14;
            }
        }
        break;
    case 11:
        if (word_800ABB18 >= 0xFF)
        {
            word_800ABB18 = 0;
            word_800AB640 = 0;
            work->field_210 = 0xC;
        }
        break;
    case 12:
        if (menu_radio_do_file_mode_8004C418(work, pPad) != 0)
        {
            work->field_210 = 0xD;
            word_800ABB18 = 0xFF;
            word_800AB640 = -32;
            return;
        }
        return;
    case 13:
        if ((word_800ABB18 <= 0) && (pPad->status == 0))
        {
            work->field_210 = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    case 14:
        ret2 = menu_radio_do_file_mode_8004C418(work, pPad);
        if (ret2 != 0)
        {
            sub_8004124C(work);
            work->field_210 = 0x0f;
            GM_Sound_80032C48(0x01ffff21, 0);
            gMenuCallbackProc_800ABB08.param2 = 0;
            if (ret2 == 2)
            {
                GCL_RestoreVar();
                dword_800AB638 = 0x36B0;
                gMenuCallbackProc_800ABB08.param2 = gDiskNum_800ACBF0 + 1;
                return;
            }
        }
        return;
    case 15:
        work->field_210 = 0x14;
        return;
    case 16:
        if (menu_radio_codec_helper_helper12_80041280(work, pOt, pPad) != 0)
        {
            work->field_210 = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    }

    draw_radio_message_8004114C(work, pOt);

    NEW_PRIM(tpage1, work);
    setDrawTPage(tpage1, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage1);

    menu_radio_codec_helper_helper15_80040B8C(work->field_20_otBuf);
    menu_radio_draw_face_80048DB0(work, work->field_218);
    menu_radio_codec_helper_helper14_80040DC4(work, dword_800AB638);

    NEW_PRIM(tpage2, work);
    setDrawTPage(tpage2, 0, 1, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage2);
}

void menu_radio_update_helper5_80042160(MenuWork *work)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    work->field_212 = 8;
    work->field_210 = 0;
    menu_radio_codec_create_state_80047CE4(work);
}

void menu_radio_init_nullsub_80042190(MenuWork *work)
{
}

int dword_800AB648 = 0;

void menu_radio_update_80042198(MenuWork *work, unsigned char *pOt)
{
    GCL_ARGS args;
    long     argv[2];

    GV_PAD      *pPad;
    int          timer;
    int          streamStatus;
    int          lastCode;
    unsigned int state;

    state = work->field_2A_state;
    pPad = work->field_24_pInput;
    if (GM_PlayerStatus_800ABA50 & 0x8000)
    {
        return;
    }
    if (state == 0)
    {
        if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_06 | GAME_FLAG_BIT_11 | GAME_FLAG_BIT_14)) && GV_PauseLevel_800AB928 == 0)
        {
            if ((gRadioIncomingCall_8009E708.field_0 > 0 && gRadioIncomingCall_8009E708.field_2_timer < 0) ||
                pPad->press & PAD_SELECT)
            {
                dword_800ABB1C = DG_FrameRate_8009D45C;
                DG_FrameRate_8009D45C = 2;
                gMenuCallbackProc_800ABB08.type = 0xF;
                GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_28 | GAME_FLAG_BIT_29);
                work->field_2A_state = 4;
                menu_radio_update_helper2_80038A7C();
                MENU_JimakuClear_80049518();
                GV_PauseLevel_800AB928 |= 1;
                DG_FreeObjectQueue_800183D4();
                DG_BackGroundBlack_80018520();
                GV_SetPacketTempMemory();
                menu_radio_update_helper5_80042160(work);
                word_800AB640 = -32;
                word_800ABB18 = 0xFF;
                if (gRadioIncomingCall_8009E708.field_0 > 0)
                {
                    dword_800AB638 = gRadioIncomingCall_8009E708.field_0;
                    if (gRadioIncomingCall_8009E708.field_2_timer == -2 ||
                        gRadioIncomingCall_8009E708.field_2_timer == -4)
                    {
                        word_800AB640 = 0;
                        work->field_210 = 1;
                    }
                }
                if (gRadioIncomingCall_8009E708.field_8 != 0)
                {
                    gRadioIncomingCall_8009E708.field_2_timer = -1;
                }
                work->field_214_font = NULL;
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
                GM_Sound_80032C48(0x01ffff20, 0);
                if (gRadioIncomingCall_8009E708.field_0 >= 1 && gRadioIncomingCall_8009E708.field_0 <= 2)
                {
                    init_radio_message_board_80040F74(work);
                    if (gRadioIncomingCall_8009E708.field_0 == 1)
                    {
                        menu_radio_update_helper4_8004D2D0(gRadioIncomingCall_8009E708.field_4);
                    }
                    else
                    {
                        menu_radio_init_save_mode_8004D280((int)gRadioIncomingCall_8009E708.field_4, 0);
                    }
                    work->field_210 = 14;
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
                        menu_radio_update_helper3_80040498(work->field_20_otBuf);
                        MENU_Color_80038B4C(0xFF, 0xFF, 0xFF);
                        MENU_Locate_80038B34(0xA0, 0x3F, 2);
                        MENU_Printf_80038C38("PUSH SELECT");
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
        if (work->field_210 == 20 && GM_StreamStatus_80037CD8() != 0)
        {
            work->field_2A_state = 0;
            menu_radio_update_helper_80038A6C();
            menu_radio_update_helper6_80047D40(work);
            GV_ResetPacketMemory();
            GV_PauseLevel_800AB928 &= ~1;
            DG_ResetObjectQueue_8001844C();
            menu_radio_init_nullsub_80042190(work);
            DrawSync(0);
            sub_8003CB98(work);
            sub_8003EBDC(work);
            menu_radar_load_rpk_8003AD64();
            gRadioIncomingCall_8009E708.field_0 = 0;
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_20;
            printf("callback type %d proc %X\n", gMenuCallbackProc_800ABB08.type,
                                gMenuCallbackProc_800ABB08.procNameHashed);
            if (gMenuCallbackProc_800ABB08.type != 0xF && gMenuCallbackProc_800ABB08.procNameHashed > 0)
            {
                args.argc = 2;
                args.argv = argv;
                argv[0] = gMenuCallbackProc_800ABB08.type & 0xF;
                argv[1] = gMenuCallbackProc_800ABB08.param2;
                printf("ExecProc\n");
                GCL_ExecProc(gMenuCallbackProc_800ABB08.procNameHashed, &args);
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
        menu_radio_codec_helper_8004158C(work, pOt, pPad);
    }
}

void menu_radio_init_80042700(MenuWork *work)
{
    work->field_2C_modules[MENU_RADIO] = menu_radio_update_80042198;
    work->field_28_flags |= 0x10u;
}

void menu_radio_kill_8004271C(MenuWork *work)
{
    work->field_28_flags &= ~0x10u;
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
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_28;
        }
        else
        {
            gRadioIncomingCall_8009E708.field_2_timer = -time;
            gRadioIncomingCall_8009E708.field_8 = 0;
        }

        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_20;
    }
}

void MENU_SetLoad_800427E8(int procNameHashed, int param_2, short param_3)
{
    gRadioIncomingCall_8009E708.field_0 = param_3;
    gRadioIncomingCall_8009E708.field_2_timer = -1;
    gRadioIncomingCall_8009E708.field_4 = param_2;
    gMenuCallbackProc_800ABB08.procNameHashed = procNameHashed;
    gMenuCallbackProc_800ABB08.type = 1;
}

void MENU_ResetCall_80042814(void)
{
    gRadioIncomingCall_8009E708.field_0 = 0;
    gRadioIncomingCall_8009E708.field_4 = 0;
    gRadioIncomingCall_8009E708.field_2_timer = 0;
    gRadioIncomingCall_8009E708.field_8 = 0;

    gMenuCallbackProc_800ABB08.procNameHashed = -1;
}

void MENU_SetRadioCallbackProc_8004283C(int procNameHashed)
{
    gMenuCallbackProc_800ABB08.procNameHashed = procNameHashed;
}

// TODO: Functions from this point forward don't belong to radio.c!

void menu_set_string2_80043138();

// rect_800AB64C is declared as a 1-element array
// in order for menu_number_init_80042848
// to declare extern to an array with unspecified size.
// That way the "small data" optimization of -G8 doesn't kick
// in (the compiler then doesn't know that rect_800AB64C is 8 bytes large,
// under the "8 bytes" threshold in G8). Without it, it would force
// us to compile this function (and the entire file) with -G0.
RECT SECTION(".sdata") rect_800AB64C[] = {{960, 488, 64, 10}};

extern SPRT gRadioNumberSprt_800bd9b0;
extern SPRT gRadioNumberSprt2_800bd9d0;

void menu_number_init_80042848(MenuWork *work)
{
    RECT       rect1, rect2;
    ResHeader *pRes;
    SPRT      *pSprt;

    rect1 = rect_800AB64C[0];

    // Loads "num.res" (c70e.r) file:
    pRes = GV_GetCache(GV_CacheID2("num", 'r'));

    pRes->field_14[0] = 0; // TODO: Why zero out the first pixel of image?

    rect2.x = 960;
    rect2.y = 511;
    rect2.w = 16;
    rect2.h = 1;

    LoadImage(&rect2, (u_long *)pRes->field_14);
    LoadImage(&rect1, (u_long *)&pRes->field_14[pRes->field_8 >> 1]);

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

void menu_number_kill_80042980(MenuWork *work)
{
}

void _menu_number_draw_80042988(MenuPrim *pOt, TextConfig *pSettings, int number)
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

void _menu_number_draw_string_80042BF4(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
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

void menu_number_draw_magazine_80042E38(MenuWork *work, unsigned int *pOt, int xoff, int yoff, int pMagSize,
                                        int pAmmo, int pSubCnt2)
{
    SPRT *sprt;
    int   i;

    for (i = 0; i < pAmmo; i++)
    {
        NEW_PRIM(sprt, work);

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

int menu_number_draw_80042F78(MenuWork *work, unsigned int *pOt, int xpos, int ypos, int number, int flags)
{
    TextConfig textConfig; // [sp+10h] [-10h] BYREF

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    _menu_number_draw_80042988(work->field_20_otBuf, &textConfig, number);
    return textConfig.xpos;
}

extern SPRT gRadioNumberSprt_800bd9b0;

int menu_number_draw_number2_80042FC0(MenuWork *work, int xpos, int ypos, int current, int total)
{
    SPRT      *pPrim;
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.flags = 0;
    textConfig.colour = (current == 0 ? 0x64002080 : 0x64575757);
    _menu_number_draw_80042988(work->field_20_otBuf, &textConfig, current);

    NEW_PRIM(pPrim, work);

    *pPrim = gRadioNumberSprt_800bd9b0;
    LSTORE(textConfig.colour, &pPrim->r0);
    pPrim->x0 = textConfig.xpos;
    pPrim->y0 = textConfig.ypos;
    pPrim->u0 = 224;

    addPrim(work->field_20_otBuf->mPrimBuf.mOt, pPrim);

    textConfig.xpos = textConfig.xpos + 6;
    _menu_number_draw_80042988(work->field_20_otBuf, &textConfig, total);
    return textConfig.xpos;
}

int menu_number_draw_string_800430F0(MenuWork *work, unsigned int *pOt, int xpos, int ypos, const char *str, int flags)
{
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    _menu_number_draw_string_80042BF4(work->field_20_otBuf, &textConfig, str);
    return textConfig.xpos;
}

RECT gRadioStringRect_800AB658 = {960, 498, 0, 0};

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

void _menu_number_draw_string2_80043220(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
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
