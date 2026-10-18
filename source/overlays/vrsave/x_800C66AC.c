// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_helper2_helper_8004A4C4, menu_radio_do_file_mode_helper4_helper_8004A54C, sub_8004A648, menu_radio_do_file_mode_helper3_helper_8004A790), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "mts/mts.h"
#include "mts/taskid.h"

extern char *MGS_MemoryCardName; /* in main.c */

void vrsave_800C86A0(MenuPrim *pGlue, SELECT_INFO *info);

void vrsave_800C66AC(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    TextConfig         textConfig;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord(&pUnk->field_8, 2);
        pUnk->field_18 = 0x3d482e;
    }
    textConfig.xpos = pUnk->field_8 >> 16;
    textConfig.ypos = pUnk->field_10 >> 16; // pUnk->field_10 / 65536 wouldn't match
    textConfig.flags = 0x12;
    textConfig.color = pUnk->field_18 | 0x66000000;

    _menu_number_draw_string2(pGlue, &textConfig, (char *)pUnk->field_4); // TODO: Fix cast
}

void vrsave_800C6734(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    LINE_F2           *pPrim;
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord(&pUnk->field_4, 4);
    }

    if (pUnk->field_4 != pUnk->field_14 || pUnk->field_C != pUnk->field_1C)
    {
        _NEW_PRIM(pPrim, pGlue);

        LSTORE(pUnk->field_24, &pPrim->r0);
        pPrim->x0 = pUnk->field_4 >> 16;
        pPrim->y0 = pUnk->field_C >> 16;
        pPrim->x1 = pUnk->field_14 >> 16;
        pPrim->y1 = pUnk->field_1C >> 16; // pUnk->field_1C / 65536 wouldn't match
        setLineF2(pPrim);
        addPrim(pGlue->ot, pPrim);
    }
}

void vrsave_800C6830(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;
    int                x, y, w, h;
    TILE              *pTile;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord(&pUnk->field_4, 4);
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
    addPrim(pGlue->ot, pTile);

    radio_draw_face_frame(pGlue, x, y, w, h);
    radio_draw_face_frame(pGlue, x, y, w, h);
}

void vrsave_800C6978(MenuPrim *pGlue, RadioFileModeStruElem *pElem)
{
    RadioFileModeUnk1 *pUnk;

    pUnk = pElem->field_C_unk1;
    if (pElem->field_0 == 1)
    {
        move_coord(&pUnk->field_4, 2);
    }

    *(short *)pUnk->field_14 = pUnk->field_4 >> 16; // TODO: Fix type of field_14
    *(short *)(pUnk->field_14 + 2) = pUnk->field_C >> 16; // pUnk->field_C / 65536 wouldn't match
    vrsave_800C86A0(pGlue, (SELECT_INFO *)pUnk->field_14);
}
