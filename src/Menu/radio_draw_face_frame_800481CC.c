#include "libdg/libdg.h"
#include "Menu/menuman.h"

extern int dword_800ABB3C;
int        dword_800ABB3C;

void radio_draw_face_frame_800481CC(MenuPrim *pGlue, int x, int y, int w, int h)
{
    POLY_FT4  *polys[8];
    int        xn, yn;
    int        xend, yend;
    int        size;
    int        i;
    POLY_FT4 * pPoly;
    int        px, py;
    POLY_FT4 **ppPoly;
    POLY_FT4  *pPoly2;
    int        x2, y2;

    x += 3;
    y += 3;
    w -= 7;
    h -= 7;

    if (w < 0)
    {
        return;
    }

    // No idea why it copies x and y
    xn = x;
    yn = y;

    xend = xn + w;
    yend = yn + h;

    size = 9;

    for (i = 0; i < 8; i++)
    {
        _NEW_PRIM(pPoly, pGlue);
        LSTORE(0x80808080, &pPoly->r0);
        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        pPoly->clut = dword_800ABB3C;
        pPoly->tpage = getTPage(0, 1, 960, 256);

        if (i < 4)
        {
            px = (i % 2) * 10 - 64;
            py = (i / 2) * 10 - 80;
            setUVWH(pPoly, px, py, 9, 9);
        }

        addPrim(pGlue->mPrimBuf.mOt, pPoly);
        polys[i] = pPoly;
    }

    polys[0]->x0 = polys[2]->x0 = xn - size;
    polys[1]->x0 = polys[3]->x0 = xend;
    polys[0]->y0 = polys[1]->y0 = yn - size;
    polys[2]->y0 = polys[3]->y0 = yend;

    for (i = 0, ppPoly = polys; i < 4; ppPoly++, i++)
    {
        pPoly2 = *ppPoly;

        x2 = pPoly2->x0;
        y2 = pPoly2->y0;

        pPoly2->x1 = x2 + size;
        pPoly2->y1 = y2;
        pPoly2->x2 = x2;
        pPoly2->y2 = y2 + size;
        pPoly2->x3 = x2 + size;
        pPoly2->y3 = y2 + size;
    }

    setUVWH(polys[4], 201, 176, 1, 9);
    setXYWH(polys[4], xn, yn - size, w, 9);

    setUVWH(polys[5], 201, 186, 1, 9);
    setXYWH(polys[5], xn, yend, w, 9);

    setUVWH(polys[6], 192, 185, 9, 1);
    setXYWH(polys[6], xn - size, yn, 9, h);

    setUVWH(polys[7], 202, 185, 9, 1);
    setXYWH(polys[7], xend, yn, 9, h);
}
