#include "menuman.h"
#include "libdg/libdg.h"

void menu_radio_draw_face_helper4_80048868(MenuGlue *pGlue, short *param_2, int param_3)

{
    LINE_F4 *pPrim;
    LINE_F4 *pPrimCopy;
    short    coord;

    if (param_2[2] < 5)
    {
        coord = param_2[2] * 14;
    }
    else
    {
        coord = 54;
    }

    pPrim = (LINE_F4 *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(LINE_F4);
    pPrimCopy = pPrim; // To get a match

    LSTORE(0x1a1f13, &pPrimCopy->r0);

    if (param_3 == 0)
    {
        pPrimCopy->x0 = 83 - coord;
        pPrim->x3 = 83 - coord;
        pPrim->y0 = 30;
        pPrimCopy->y1 = 30;
        coord = 78 - coord;
        pPrimCopy->x1 = coord;
        pPrim->x2 = coord;
        pPrim->y2 = 118;
        pPrimCopy->y3 = 118;
    }
    else
    {
        pPrimCopy->x0 = coord + 236;
        pPrimCopy->x3 = coord + 236;
        pPrimCopy->y0 = 30;
        pPrimCopy->y1 = 30;
        coord = coord + 241;
        pPrimCopy->x1 = coord;
        pPrimCopy->x2 = coord;
        pPrimCopy->y2 = 118;
        pPrimCopy->y3 = 118;
    }

    setLineF4(pPrimCopy);
    addPrim(pGlue->mPrimBuf.mOt, pPrimCopy);
}
