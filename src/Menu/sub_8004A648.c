#include "radio.h"
#include "libdg/libdg.h"

void sub_8004A648(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    int                x, y, w, h;
    TILE              *pTile;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord_8004A494(&pUnk->field_4, 4);
    }
    x = (pUnk->field_4 >> 16);
    y = (pUnk->field_C >> 16);
    w = pUnk->field_14 >> 16;
    h = pUnk->field_1C >> 16;
    x -= w / 2;
    y -= h / 2;

    _NEW_PRIM(pTile, pGlue);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(pGlue->mPrimBuf.mOt, pTile);

    radio_draw_face_frame_800481CC(pGlue, x, y, w, h);
    radio_draw_face_frame_800481CC(pGlue, x, y, w, h);
}
