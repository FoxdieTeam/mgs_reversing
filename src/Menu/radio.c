#include "radio.h"
#include "menuman.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "radar.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

int                       SECTION(".sbss") dword_800ABAF8;
int                       SECTION(".sbss") gRadioClut_800ABAFC;
int                       SECTION(".sbss") gCodecAction;
char                     *SECTION(".sbss") dword_800ABB04;
MenuCallbackProc_800ABB08 SECTION(".sbss") gMenuCallbackProc_800ABB08;
int                       SECTION(".sbss") dword_800ABB10;
int                       SECTION(".sbss") dword_800ABB14;
short                     SECTION(".sbss") gCodecFadingCount;
short                     SECTION(".sbss") word_800ABB1A;
int                       SECTION(".sbss") dword_800ABB1C;

extern PANEL_TEXTURE     dword_800BDA10;
extern PANEL_TEXTURE     dword_800BDA30;
extern RadioIncomingCall gRadioIncomingCall_8009E708;
extern int               GV_Clock;

STATIC char dword_800AB610[8] = {2, 4, 3, 1, 4, 3, 1, 0};

extern int GM_PlayerStatus;
extern int GV_PauseLevel;

extern int FS_DiskNum_800ACBF0;

extern char menu_string_format_8009E714[];

// 7 segment digit bits
//   --0--
//  |     |
//  1     2
//   --3--
//  4     5
//  |     |
//   --6--
// example 4 = 0b101110 = 0x2E
//                                   8,    1,    2,    3,    4,    5,   6,    7,    8,    9,     0
char gDigit7Segment_8009E60C[] = {0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B, 0x7B, 0x25, 0x7F, 0x6F, 0x00, 0x00};

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

// width map for the special characters
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

enum CodecAction {
    CODEC_ACTION_NONE = 0x00,
    CODEC_ACTION_PTT = 0x01,
    CODEC_ACTION_MEMORY = 0x02,
    CODEC_ACTION_RIGHT = 0x04,
    CODEC_ACTION_LEFT = 0x08,
};

/**
 * @brief Fade in/out the codec screen.
 *
 * This function creates a semi-transparent tile to fade in or out the codec
 * screen using the intensity specified.
 *
 * @param work Pointer to the MenuWork structure.
 * @param pOt Pointer to the ordering table.
 * @param opacity The intensity for the fade effect (0-255).
 */
void FadeCodecScreen(MenuWork *work, unsigned char *pOt, int opacity)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    NEW_PRIM(tile, work);

    if (opacity > 255)
    {
        opacity = 255;
    }
    if (opacity < 0)
    {
        opacity = 0;
    }
    LSTORE(opacity << 16 | opacity << 8 | opacity, &tile->r0);

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

// draw the 7 segment display on the codec screen
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
    iVar1 = gDigit7Segment_8009E60C[param_4];

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

// Highlight the codec arrow buttons when changing frequency
// (idx 0 = right, idx 1 = left)
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

// Highlight codec ui element depending on the action flags
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

    // Highlight PTT text when calling
    if (flags & CODEC_ACTION_PTT)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x90;
        conf.ypos = ypos + 0x28;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        _menu_number_draw_string2(pGlue, &conf, "P#3T#3T");
    }
    // Highlight MEMORY text when browsing the codec memory
    if (flags & CODEC_ACTION_MEMORY)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x86;
        conf.ypos = ypos + 0x77;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        _menu_number_draw_string2(pGlue, &conf, "MEMORY");
    }
    if (flags & CODEC_ACTION_RIGHT)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 0);
    }
    if (flags & CODEC_ACTION_LEFT)
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
    if (GV_Clock == 0)
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

    time = (GV_Time / 2) % 128;

    _NEW_PRIM(tpage1, pGlue);
    _NEW_PRIM(tpage2, pGlue);

    if (GV_Clock == 0)
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

extern Radio_8009E664 dword_8009E664[];

void menu_radio_codec_helper_helper14_80040DC4(MenuWork *work, int param_2)
{
    DR_TPAGE *tpage;
    DR_STP   *stp;
    MenuPrim *pGlue;

    if (work->field_210_codec_state != 11 && work->field_210_codec_state != 14)
    {
        pGlue = work->field_20_otBuf;
        menu_radio_codec_helper_helper14_helper4_800408BC(pGlue, 0, 128, 140, 89, 90, 30);
        menu_radio_codec_helper_helper14_helper6_800407A4(pGlue, -90, 90, gCodecAction);
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

STATIC RECT RADIO_MES_VRAM_POS_800AB630 = {960, 260, 63, 76};

void init_radio_message_board_80040F74(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&RADIO_MES_VRAM_POS_800AB630, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &RADIO_MES_VRAM_POS_800AB630, 960, 510);
        font_set_kcb(ptr_local_kcb, -1, -1, 0, 6, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(GV_PACKET_MEMORY0, font_get_buffer_size(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer(ptr_local_kcb, allocated_kcb + 1);
        font_set_color(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color(ptr_local_kcb, 2, 0x3a4b, 0);
        font_set_color(ptr_local_kcb, 3, 0x1094, 0);
        font_clut_update(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));

        dword_800ABB04 = NULL;
    }
}

void menu_radio_codec_helper__helper13_800410E4(MenuWork *work, char *string)
{
    KCB *kcb = work->field_214_font;
    dword_800ABB04 = string;
    font_print_string(kcb, string);
    font_update(kcb);
}

void sub_80041118(MenuWork *work)
{
    KCB *kcb = work->field_214_font;
    dword_800ABB04 = NULL;
    font_clear(kcb);
    font_update(kcb);
}

int draw_radio_message(MenuWork *work, unsigned char *pOt)
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

    pPrim->u0 = (RADIO_MES_VRAM_POS_800AB630.x % 64) * 4;
    pPrim->v0 = RADIO_MES_VRAM_POS_800AB630.y;
    pPrim->w = 252;
    pPrim->h = 76;
    pPrim->clut = 32700;
    pPrim->x0 = (320 - kcb->max_width) / 2;
    pPrim->y0 = 132;

    setSprt(pPrim);
    addPrim(pOt, pPrim);
    return 1;
}

void sub_8004124C(MenuWork *work)
{
    GV_FreeMemory(GV_PACKET_MEMORY0, work->field_214_font);
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
    ypos = kcb->ytop;

    font_clear(kcb);

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

        font_draw_string(kcb, 0, ypos, string, color);

        if (var_s7 < kcb->max_width)
        {
            var_s7 = kcb->max_width;
        }

        ypos += 18;
        index++;
    }

    if (last_index != pMenuChara->field_1A_index)
    {
        GM_SeSet2(0, 63, SE_MENU_CURSOR);
    }

    font_update(kcb);

    kcb->max_width = var_s7;

    if (pPad->press & PAD_CIRCLE)
    {
        GM_LastResultFlag = pMenuChara->field_1A_index;
        sub_80041118(work);
        return 1;
    }

    return 0;
}

void draw_radio_wait_mark(MenuWork *work, unsigned char *pOt)
{
    MenuPrim *pOtBuffer; // $v1
    POLY_F3 *pPrim; // $a0

    if ( GV_Time % 16 >= 4 )
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

STATIC int codec_freq_800AB638 = 14000;

// call a frequency
STATIC void menu_radio_codec_helper_helper11_8004150C(MenuWork *work)
{
    int   pRadioCode;
    short codec_freq_800AB638_copy;

    init_radio_message_board_80040F74(work);
    work->field_212 = 0x1e;
    GM_SeSet2(0, 0x3f, SE_RADIO_SEND);
    pRadioCode = MENU_GetRadioCode(codec_freq_800AB638);
    if (pRadioCode >= 0)
    {
        sub_80047D70(work, codec_freq_800AB638, pRadioCode);
        codec_freq_800AB638_copy = codec_freq_800AB638;
        work->field_210_codec_state = 2;
        gMenuCallbackProc_800ABB08.type = 0;
        gMenuCallbackProc_800ABB08.param2 = codec_freq_800AB638_copy;
        return;
    }

    work->field_210_codec_state = 9;
}

STATIC int   dword_800AB63C = 0;
STATIC short gCodecFadingStep = 0;
STATIC int   dword_800AB644 = -1;

STATIC void menu_radio_codec_helper_8004158C(MenuWork *work, unsigned char *pOt, GV_PAD *pPad)
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

    if (gCodecFadingStep == 0)
    {
        if (gCodecFadingCount == 0)
        {
            goto skip_fading;
        }
    }
    else
    {
        gCodecFadingCount += gCodecFadingStep;
        if (gCodecFadingCount >= 0xFF)
        {
            gCodecFadingCount = 0xFF;
            gCodecFadingStep = 0;
        }
        else if (gCodecFadingCount <= 0)
        {
            gCodecFadingCount = 0;
            gCodecFadingStep = 0;
        }
    }

    FadeCodecScreen(work, pOt, gCodecFadingCount);
skip_fading:

    switch (work->field_210_codec_state)
    {
    case 0: // codec opening
        if (gCodecFadingStep == 0)
        {
            work->field_210_codec_state = 1;
        }
        break;
    case 1: // codec open

        // if we have an incoming call
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
            codec_freq_800AB638 = gRadioIncomingCall_8009E708.field_0;
            sub_80047D70(work, gRadioIncomingCall_8009E708.field_0, gRadioIncomingCall_8009E708.field_4);
            work->field_210_codec_state = 2;
            init_radio_message_board_80040F74(work);
            gRadioIncomingCall_8009E708.field_0 = 0;
        }
        else
        {
            gCodecAction = CODEC_ACTION_NONE;
            if (pPad->press & (PAD_SELECT | PAD_CROSS))
            {
                work->field_212 = 0;
                work->field_210_codec_state = 0x12;
            }
            else if (pPad->press & PAD_DOWN)
            {
                gCodecAction = CODEC_ACTION_MEMORY;
                menu_radio_codec_helper_helper4_8004DE20(work);
                work->field_210_codec_state = 0xA;
                GM_SeSet2(0, 0x3F, SE_RADIO_SELECT);
            }
            else if (pPad->press & (PAD_UP | PAD_CIRCLE))
            {
                gCodecAction = CODEC_ACTION_PTT;
                menu_radio_codec_helper_helper11_8004150C(work);
            }
            else if (pPad->status & (PAD_LEFT | PAD_RIGHT))
            {
                if (pPad->status & PAD_LEFT)
                {
                    direction = -1;
                    gCodecAction = CODEC_ACTION_LEFT;
                }
                else
                {
                    direction = 1;
                    gCodecAction = CODEC_ACTION_RIGHT;
                }
                if (dword_800ABB10 == direction)
                {
                    if (dword_800AB63C < 10)
                    {
                        dword_800AB63C++;
                    }
                    else if (direction != 0)
                    {
                        codec_freq_800AB638 += direction;
                        GM_SeSet2(0, 0x3F, SE_RADIO_TUNING);
                        dword_800AB63C++;
                    }
                }
                else
                {
                    dword_800AB63C = 0;
                    dword_800ABB10 = direction;
                    codec_freq_800AB638 += direction;
                    GM_SeSet2(0, 0x3F, SE_RADIO_TUNING);
                }
                if (codec_freq_800AB638 >= 14200)
                {
                    codec_freq_800AB638 = 14000;
                }
                else if (codec_freq_800AB638 < 14000)
                {
                    codec_freq_800AB638 = 14199;
                }
            }
            else
            {
                dword_800ABB10 = 0;
                dword_800AB63C = 0;
            }

            // Blink the "PRESS SELECT TO EXIT" text periodically
            if (GV_Time % 64 < 0x34)
            {
                MENU_Locate(0xA0, 0x82, 2);
                MENU_Color(0x2E, 0x47, 0x3D);
                MENU_Printf("PRESS SELECT TO EXIT");
                menu_Text_Init_80038B98();
            }
        }
        break;
    case 10: // Codec Memory open
        menu_radio_draw_mem(work, pOt);
        ret1 = menu_radio_codec_helper_helper2_8004DF68(work, pPad);
        if (pPad->press & PAD_SELECT)
        {
            work->field_212 = 0;
            work->field_210_codec_state = 0x12;
            menu_radio_codec_helper__helper3_sub_8004DF44(work);
            sub_8004124C(work);
        }
        else if (ret1 != 0)
        {
            menu_radio_codec_helper__helper3_sub_8004DF44(work);
            sub_8004124C(work);
            if (ret1 >= 0)
            {
                codec_freq_800AB638 = ret1;
                menu_radio_codec_helper_helper11_8004150C(work);
            }
            else
            {
                work->field_210_codec_state = 1;
            }
        }
        break;
    case 2: // codec call ringing
        work->field_212--;
        if (work->field_212 > 0)
        {
            menu_radio_codec_helper_helper9_80047FF4();
        }
        else if (menu_radio_codec_helper_helper9_80047FF4() <= 0)
        {
            dword_800ABAF8 = 0;
            work->field_210_codec_state = 3;
            menu_radio_codec_state_2_helper_80048024(work);
            work->field_212 = 0x10;
            if (!(gMenuCallbackProc_800ABB08.type & 0x10))
            {
                GM_SeSet2(0, 0x3F, SE_RADIO_STATIC);
            }
        }
        break;
    case 3: // codec call started?
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
                        gCodecFadingStep = -0x20;
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
                        work->field_210_codec_state = 4;
                        work->field_212 = pPad->status;
                    }
                    else
                    {
                        work->field_210_codec_state = 5;
                        pCharaStruct->field_10_subtitles = NULL;
                        work->field_212 = 0;
                    }
                    break;
                case 2:
                    printf("set call freq %d\n", codec_freq_800AB638);
                    menu_radio_codec_helper_helper_8004E198(codec_freq_800AB638);
                    work->field_210_codec_state = 6;
                    break;
                case 3:
                    menu_radio_init_save_mode((int)pCharaStruct->field_C_pScript,
                                              pCharaStruct->field_1A_index);
                    work->field_210_codec_state = 0xB;
                    gCodecFadingStep = 0x20;
                    break;
                case 4:
                    work->field_210_codec_state = 16;
                    break;
                }
            }
        }
        break;
    case 4: // codec call interrupted
        draw_radio_wait_mark(work, pOt);
        if ((pPad->release &
             (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE)) &&
            work->field_212 == 0)
        {
            menu_radio_codec_helper_helper8_80048044();
            sub_80041118(work);
            work->field_210_codec_state = 3;
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
    case 5: // codec call in progress
        pCharaStruct2 = work->field_218;
        if (!(GV_Time & 3))
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
            work->field_210_codec_state = 3;
        }
        else
        {
            if (!(pCharaStruct2->field_18 & 1) && (pPad->release & PAD_CROSS))
            {
                menu_radio_codec_helper__helper13_800410E4(work, pCharaStruct2->field_C_pScript);
                dword_800ABAF8 = 8;
                pCharaStruct2->field_14_bInExecBlock = 0;
                pCharaStruct2->field_18 |= 0x100;
                GM_StreamPlayStop();
                if (pCharaStruct2->field_0_state == 1)
                {
                    work->field_210_codec_state = 4;
                }
                else
                {
                    work->field_210_codec_state = 3;
                }
            }
            else
            {
                if (pCharaStruct2->field_0_state == 2)
                {
                    work->field_210_codec_state = 6;
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
            draw_radio_wait_mark(work, pOt);
            if (pPad->press &
                (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_TRIANGLE | PAD_CROSS | PAD_SQUARE | PAD_CIRCLE))
            {
                work->field_210_codec_state = 7;
            }
        }
        break;
    case 6:
        if (!(gMenuCallbackProc_800ABB08.type & 0x20))
        {
            menu_radio_codec_helper_helper3_80047F44(work, 1);
        }
        work->field_210_codec_state = 7;
    case 7: // codec call terminating
        pCharaStruct3 = work->field_218;
        dword_800ABAF8 = 0;
        if (gMenuCallbackProc_800ABB08.type & 0x20)
        {
            sub_8004124C(work);
            gCodecFadingStep = 0x10;
            work->field_212 = 0;
            work->field_210_codec_state = 0x13;
        }
        else if (pCharaStruct3->field_1C_radioDatFragment != NULL)
        {
            if (menu_radio_end_check() != 0)
            {
                menu_radio_codec_helper_helper7_80048080();
                ResetCodecState();
            }
        }
        else
        {
            sub_8004124C(work);
            if ((gMenuCallbackProc_800ABB08.type & 0xF) == 2)
            {
                work->field_212 = 0;
                work->field_210_codec_state = 18;
            }
            else
            {
                work->field_210_codec_state = 1;
            }
        }
        break;
    case 18:
        if (dword_800ABB14 >= 0)
        {
            GM_VoxStream(dword_800ABB14, 0x40000000);
            work->field_210_codec_state = 0x11;
            dword_800ABB14 = -1;
        }
        GM_SetSound(0x01ffff21, SD_ASYNC);
        gCodecFadingStep = 0x10;
        work->field_212 = 0;
        work->field_210_codec_state = 0x13;
        break;
    case 19: // codec screen closing
        if (gCodecFadingStep == 0)
        {
            if (work->field_212 == 0 && (gMenuCallbackProc_800ABB08.type & 0x20))
            {
                menu_radio_codec_helper_helper7_80048080();
            }
            work->field_212++;
            if (work->field_212 >= 3)
            {
                work->field_210_codec_state = 20;
            }
        }
        break;
    case 11: // opening save screen
        if (gCodecFadingCount >= 0xFF)
        {
            gCodecFadingCount = 0;
            gCodecFadingStep = 0;
            work->field_210_codec_state = 12;
        }
        break;
    case 12: // save screen open
        if (menu_radio_do_file_mode(work, pPad) != 0)
        {
            work->field_210_codec_state = 13;
            gCodecFadingCount = 0xFF;
            gCodecFadingStep = -32;
            return;
        }
        return;
    case 13: // closing save screen
        if ((gCodecFadingCount <= 0) && (pPad->status == 0))
        {
            work->field_210_codec_state = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    case 14:
        ret2 = menu_radio_do_file_mode(work, pPad);
        if (ret2 != 0)
        {
            sub_8004124C(work);
            work->field_210_codec_state = 15;
            GM_SetSound(0x01ffff21, SD_ASYNC);
            gMenuCallbackProc_800ABB08.param2 = 0;
            if (ret2 == 2)
            {
                GCL_RestoreVar();
                codec_freq_800AB638 = 0x36B0;
                gMenuCallbackProc_800ABB08.param2 = FS_DiskNum_800ACBF0 + 1;
                return;
            }
        }
        return;
    case 15:
        work->field_210_codec_state = 20;
        return;
    case 16: // save dialog
        if (menu_radio_codec_helper_helper12_80041280(work, pOt, pPad) != 0)
        {
            work->field_210_codec_state = 3;
            menu_radio_codec_helper_helper8_80048044();
        }
        break;
    }

    draw_radio_message(work, pOt);

    NEW_PRIM(tpage1, work);
    setDrawTPage(tpage1, 1, 0, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage1);

    menu_radio_codec_helper_helper15_80040B8C(work->field_20_otBuf);
    menu_radio_draw_face(work, work->field_218);
    menu_radio_codec_helper_helper14_80040DC4(work, codec_freq_800AB638);

    NEW_PRIM(tpage2, work);
    setDrawTPage(tpage2, 0, 1, getTPage(0, 0, 960, 256));
    addPrim(pOt, tpage2);
}

STATIC void menu_radio_update_helper5_80042160(MenuWork *work)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    work->field_212 = 8;
    work->field_210_codec_state = 0;
    menu_radio_codec_create_state_80047CE4(work);
}

STATIC void menu_radio_init_nullsub_80042190(MenuWork *work)
{
}

STATIC int dword_800AB648 = 0;

STATIC void menu_radio_update_80042198(MenuWork *work, unsigned char *pOt)
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
    if (GM_PlayerStatus & 0x8000)
    {
        return;
    }
    if (state == MENU_CLOSED)
    {
        if (!(GM_GameStatus & (STATE_VOX_STREAM | STATE_TAKING_PHOTO | STATE_RADIO_OFF)) && GV_PauseLevel == 0)
        {
            if ((gRadioIncomingCall_8009E708.field_0 > 0 && gRadioIncomingCall_8009E708.field_2_timer < 0) ||
                pPad->press & PAD_SELECT)
            {
                dword_800ABB1C = DG_FrameRate;
                DG_FrameRate = 2;
                gMenuCallbackProc_800ABB08.type = 0xF;
                GM_GameStatus &= ~(STATE_PADMASK | STATE_PADRELEASE);
                work->field_2A_state = MENU_CODEC_OPEN;
                menu_radio_update_helper2_80038A7C();
                MENU_JimakuClear();
                GV_PauseLevel |= 1;
                DG_FreeObjectQueue();
                DG_BackGroundBlack();
                GV_SetPacketTempMemory();
                menu_radio_update_helper5_80042160(work);
                gCodecFadingStep = -32;
                gCodecFadingCount = 0xFF;
                if (gRadioIncomingCall_8009E708.field_0 > 0)
                {
                    codec_freq_800AB638 = gRadioIncomingCall_8009E708.field_0;
                    if (gRadioIncomingCall_8009E708.field_2_timer == -2 ||
                        gRadioIncomingCall_8009E708.field_2_timer == -4)
                    {
                        gCodecFadingStep = 0;
                        work->field_210_codec_state = 1;
                    }
                }
                if (gRadioIncomingCall_8009E708.field_8 != 0)
                {
                    gRadioIncomingCall_8009E708.field_2_timer = -1;
                }
                work->field_214_font = NULL;
                streamStatus = GM_StreamStatus();
                if (streamStatus != -1)
                {
                    lastCode = GM_StreamGetLastCode();
                    dword_800ABB14 = lastCode;
                    printf("GetPotion %d\n", lastCode);
                }
                else
                {
                    dword_800ABB14 = streamStatus;
                }
                GM_StreamPlayStop();
                DG_UnDrawFrameCount = 2;
                dword_800AB648 = 3;
                GM_SetSound(0x01ffff20, SD_ASYNC);
                if (gRadioIncomingCall_8009E708.field_0 >= 1 && gRadioIncomingCall_8009E708.field_0 <= 2)
                {
                    init_radio_message_board_80040F74(work);
                    if (gRadioIncomingCall_8009E708.field_0 == 1)
                    {
                        menu_radio_update_helper4_8004D2D0(gRadioIncomingCall_8009E708.field_4);
                    }
                    else
                    {
                        menu_radio_init_save_mode((int)gRadioIncomingCall_8009E708.field_4, 0);
                    }
                    work->field_210_codec_state = 14;
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
                        MENU_Color(0xFF, 0xFF, 0xFF);
                        MENU_Locate(0xA0, 0x3F, 2);
                        MENU_Printf("PUSH SELECT");
                        menu_Text_Init_80038B98();
                    }
                    if (timer == 0 &&
                        (gRadioIncomingCall_8009E708.field_2_timer > 240 || gRadioIncomingCall_8009E708.field_8 != 0))
                    {
                        GM_SeSet2(0, 0x3F, SE_RADIO_INCOMING);
                        return;
                    }
                }
            }
        }
    }
    else if (state == MENU_CODEC_OPEN)
    {
        if (work->field_210_codec_state == 20 && GM_StreamStatus() != 0)
        {
            work->field_2A_state = MENU_CLOSED;
            menu_radio_update_helper_80038A6C();
            menu_radio_update_helper6_80047D40(work);
            GV_ResetPacketMemory();
            GV_PauseLevel &= ~1;
            DG_ResetObjectQueue();
            menu_radio_init_nullsub_80042190(work);
            DrawSync(0);
            sub_8003CB98(work);
            sub_8003EBDC(work);
            menu_radar_load_rpk_8003AD64();
            gRadioIncomingCall_8009E708.field_0 = 0;
            GM_GameStatus &= ~STATE_MENU_OFF;
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
            DG_ChangeReso(0);
            DG_UnDrawFrameCount = 3;
            DG_BackGroundNormal();
            DG_FrameRate = dword_800ABB1C;
            printf("EXIT MUSENKI\n");
            return;
        }
        if (--dword_800AB648 == -1)
        {
            DG_ChangeReso(1);
        }
        menu_radio_codec_helper_8004158C(work, pOt, pPad);
    }
}

void menu_radio_init(MenuWork *work)
{
    work->field_2C_modules[MENU_RADIO] = menu_radio_update_80042198;
    work->field_28_flags |= 0x10u;
}

void menu_radio_kill(MenuWork *work)
{
    work->field_28_flags &= ~0x10u;
}

void MENU_RadioCall(int param_1, int param_2, int time)
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
            GV_PadMask = 0x100;
            GM_GameStatus |= STATE_PADMASK;
        }
        else
        {
            gRadioIncomingCall_8009E708.field_2_timer = -time;
            gRadioIncomingCall_8009E708.field_8 = 0;
        }

        GM_GameStatus |= STATE_MENU_OFF;
    }
}

void MENU_SetLoad(int procNameHashed, int param_2, short param_3)
{
    gRadioIncomingCall_8009E708.field_0 = param_3;
    gRadioIncomingCall_8009E708.field_2_timer = -1;
    gRadioIncomingCall_8009E708.field_4 = param_2;
    gMenuCallbackProc_800ABB08.procNameHashed = procNameHashed;
    gMenuCallbackProc_800ABB08.type = 1;
}

void MENU_ResetCall(void)
{
    gRadioIncomingCall_8009E708.field_0 = 0;
    gRadioIncomingCall_8009E708.field_4 = 0;
    gRadioIncomingCall_8009E708.field_2_timer = 0;
    gRadioIncomingCall_8009E708.field_8 = 0;

    gMenuCallbackProc_800ABB08.procNameHashed = -1;
}

void MENU_SetRadioCallbackProc(int proc_id)
{
    gMenuCallbackProc_800ABB08.procNameHashed = proc_id;
}

// TODO: Functions from this point forward don't belong to radio.c!

void menu_set_string2(void);

// rect_800AB64C is declared as a 1-element array
// in order for menu_number_init
// to declare extern to an array with unspecified size.
// That way the "small data" optimization of -G8 doesn't kick
// in (the compiler then doesn't know that rect_800AB64C is 8 bytes large,
// under the "8 bytes" threshold in G8). Without it, it would force
// us to compile this function (and the entire file) with -G0.
STATIC RECT SECTION(".sdata") rect_800AB64C[] = {{960, 488, 64, 10}};

extern SPRT gRadioNumberSprt_800bd9b0;
extern SPRT gRadioNumberSprt2_800bd9d0;

void menu_number_init(MenuWork *work)
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
    menu_set_string2();
}

void menu_number_kill(MenuWork *work)
{
    /* do nothing */
}

void _menu_number_draw(MenuPrim *pOt, TextConfig *pSettings, int number)
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

/**
 * @brief Adjusts the horizontal position of a series of sprites based on
 * an alignment value and the alignment flags.
 *
 * @param pPrim Pointer to the first SPRT primitive to be adjusted.
 * @param pFreeLocation Pointer to the end of the primitive buffer.
 * @param x The initial x-coordinate.
 * @param align The alignment value
 * @param flags TextConfig_Flags value that determines the alignment.
 * @return The final x-coordinate after adjustment.
 */
STATIC int _menu_draw_number_draw_helper(SPRT *pPrim, char *pFreeLocation, int x, int align, int flags)
{
    int offset_x0;

    // check if the PRIM is valid and if it's within the buffer
    if (pPrim != 0 && (char*)pPrim < pFreeLocation)
    {
        switch (flags & 0xF)
        {
        case TextConfig_Flags_eLeftAlign_00:
        default:
            offset_x0 = x;
            x = align + offset_x0;
            break;

        case TextConfig_Flags_eRightAlign_01:
            x -= align;
            offset_x0 = x;
            break;

        case TextConfig_Flags_eCentreAlign_02:
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

void _menu_number_draw_string(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
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
            _menu_draw_number_draw_helper(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
            // move to the next line
            pTextConfig->ypos += 8;
            pSprt = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
            width = 0;
            continue;
        }
        // convert to lowercase
        lc = c | 0x20;

        // if is a number
        if ((lc - '0') < 10)
        {
            tpx = (lc - '0') * 6;
            tpy = 488;
            skip = 6;
        }
        // if is a letter
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
        else // if special character
        {
            xoffset = 0;
            pFormat = menu_string_format_8009E714;
            // iterate over the menu_string_format_8009E714 map
            // to find the "skip" value
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
                // if not found ignore the character
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

        // draw the character sprite
        LSTORE(colour, &pSprt2->r0);

        pSprt2->x0 = width;
        pSprt2->y0 = pTextConfig->ypos;
        pSprt2->u0 = tpx;
        pSprt2->v0 = tpy;

        addPrim(pOt, pSprt2);
        width += skip;
    }

    pTextConfig->xpos = _menu_draw_number_draw_helper(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
}

void menu_number_draw_magazine(MenuWork *work, unsigned int *pOt, int xoff, int yoff,
                               int pMagSize, int pAmmo, int pSubCnt2)
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

int menu_number_draw(MenuWork *work, unsigned int *pOt, int xpos, int ypos, int number, int flags)
{
    TextConfig textConfig; // [sp+10h] [-10h] BYREF

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    _menu_number_draw(work->field_20_otBuf, &textConfig, number);
    return textConfig.xpos;
}

extern SPRT gRadioNumberSprt_800bd9b0;

int menu_number_draw_number2(MenuWork *work, int xpos, int ypos, int current, int total)
{
    SPRT      *pPrim;
    TextConfig textConfig;

    // Draw the "current" number
    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.flags = 0;
    // Use red color if "current" is 0, otherwise use grey
    textConfig.colour = (current == 0 ? 0x64002080 : 0x64575757);
    _menu_number_draw(work->field_20_otBuf, &textConfig, current);

    // Draw the "/" separator between the current and total numbers
    NEW_PRIM(pPrim, work);

    *pPrim = gRadioNumberSprt_800bd9b0;
    LSTORE(textConfig.colour, &pPrim->r0);
    pPrim->x0 = textConfig.xpos;
    pPrim->y0 = textConfig.ypos;
    pPrim->u0 = 224;

    addPrim(work->field_20_otBuf->mPrimBuf.mOt, pPrim);

    // Draw the "total" number
    textConfig.xpos = textConfig.xpos + 6;
    _menu_number_draw(work->field_20_otBuf, &textConfig, total);
    return textConfig.xpos;
}

int menu_number_draw_string(MenuWork *work, unsigned int *pOt, int xpos, int ypos, const char *str, int flags)
{
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    _menu_number_draw_string(work->field_20_otBuf, &textConfig, str);
    return textConfig.xpos;
}

STATIC RECT gRadioStringRect_800AB658 = {960, 498, 0, 0};

extern SPRT gRadioStringSprt_800BD9F0;

void menu_set_string2(void)
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

// wider spacing because of the larger font
void _menu_number_draw_string2(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str)
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
        // convert to lowercase
        lc = c | 0x20;

        if (c == '\n')
        {
            _menu_draw_number_draw_helper(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
            // move to the next line
            pTextConfig->ypos += 8;
            pSprt = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
            width = 0;
            continue;
        }

        // if is a number
        if ((lc - '0') < 10)
        {
            tpx = (lc - '0') * 8;
            tpy = 248;
            skip = 9;
        }
        // if is a letter
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
        // Add spacing equal to the value of the next character
        else if (lc == '#')
        {
            width += (str2[1] - '0');
            str2++;
            continue;
        }
        else // if special character
        {
            xoffset = 0;
            pFormat = menu_string_format_8009E714;
            // iterate over the menu_string_format_8009E714 map
            // to find the "skip" value
            while (1)
            {
                if (pFormat[0] == '\0')
                {
                    // if not found ignore the character
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

        // draw the character sprite
        LSTORE(colour, &pSprt2->r0);

        pSprt2->x0 = width;
        pSprt2->y0 = pTextConfig->ypos;
        pSprt2->u0 = tpx;
        pSprt2->v0 = tpy;

        addPrim(pOt, pSprt2);
        width += skip;
loop:
    }

    pTextConfig->xpos = _menu_draw_number_draw_helper(pSprt, pGlue->mPrimBuf.mFreeLocation, pTextConfig->xpos, width, pTextConfig->flags);
}

void menu_restore_nouse(void)
{
    sub_8003CFE0(&dword_800BDA10, 2);
    sub_8003CFE0(&dword_800BDA30, 3);
}

void menu_init_nouse(void)
{
    dword_800BDA10.field_8_bufid = 0;
    menu_init_rpk_item_8003DDCC(&dword_800BDA10, 40, 39);
    menu_init_rpk_item_8003DDCC(&dword_800BDA30, 48, 39);
    menu_restore_nouse();
}

STATIC void sub_800434F4(MenuPrim *pGlue, int offset_x, int offset_y, PANEL_TEXTURE *pUnk)
{
    SPRT *pPrim;

    _NEW_PRIM(pPrim, pGlue);

    LSTORE(0x80808080, &pPrim->r0);
    menu_init_sprt_8003D0D0(pPrim, pUnk, offset_x - 2, offset_y + 6);

    setSprt(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

void menu_draw_nouse(MenuPrim *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA10);
}

void menu_draw_frozen(MenuPrim *pGlue, int offset_x, int offset_y)
{
    sub_800434F4(pGlue, offset_x, offset_y, &dword_800BDA30);
}

void menu_draw_triangle(MenuPrim *pGlue, Menu_Triangle *pTriangle)
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
