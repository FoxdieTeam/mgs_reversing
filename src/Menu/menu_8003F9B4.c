#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "libdg/libdg.h"

extern SPRT gMenuSprt_800bd998;

void menu_8003F9B4(Actor_MenuMan *pActor, unsigned int *pOt, const char *str)
{
    POLY_F4 *polyF4;
    TILE    *tile;
    SPRT    *sprt;
    int      i;
    int      w;

    // Variables storing temporary X coordinate calculations
    // It's required to get a match...
    int x0, x1, x2, x3, x4;

    pActor->field_2B |= 2;

    sprt = (SPRT *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(SPRT);

    *sprt = gMenuSprt_800bd998;
    addPrim(pOt, sprt);

    x0 = gMenuSprt_800bd998.x0;
    x3 = x0 - 10;
    w = gMenuSprt_800bd998.w + 10;
    x1 = x0;

    x4 = menu_number_draw_string_800430F0(pActor, pOt, x1 - 8, gMenuSprt_800bd998.y0 - 7, str, 0);
    Menu_render_snake_life_bar_8003F4B8(pActor->field_20_otBuf, x3, 24);

    i = 0;
    x0 = 12;
    x0 = x1 - x0;
    x2 = x3 + (x4 - x0);

    for (; i < 2; i++)
    {
        polyF4 = (POLY_F4 *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
        pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(POLY_F4);

        LSTORE(0, &polyF4->r0);
        polyF4->x0 = x3;
        polyF4->y0 = gMenuSprt_800bd998.y0 - 9;
        polyF4->x1 = x2;
        polyF4->y1 = gMenuSprt_800bd998.y0 - 9;
        polyF4->x2 = x3;
        polyF4->y2 = gMenuSprt_800bd998.y0;
        polyF4->x3 = x2;
        polyF4->y3 = gMenuSprt_800bd998.y0;
        polyF4->x3 += 10;

        setPolyF4(polyF4);
        setSemiTrans(polyF4, 1);
        addPrim(pOt, polyF4);

        tile = (TILE *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
        pActor->field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(TILE);

        LSTORE(0, &tile->r0);
        tile->x0 = x3;
        tile->y0 = gMenuSprt_800bd998.y0;
        tile->w = w;
        tile->h = gMenuSprt_800bd998.h;

        setTile(tile);
        setSemiTrans(tile, 1);
        addPrim(pOt, tile);
    }
}
