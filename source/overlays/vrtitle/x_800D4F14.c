// vrtitle: VR revision copy of onoda/abst/abst.c
// (abst_800C5318), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_sprt_outline[2][4];
    SPRT  text_sprt2[2];
    SPRT  text_sprt_outline2[2][4];
    SPRT  text_sprt3[2];
    SPRT  text_sprt4[2];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short unk1;
    short unk2;
    short x0;
    short y0;
    short cx;
    short cy;
    short unk3;
    short unk4;
    short x1;
    short y1;
} Unknown;

// FIXME: it's the same struct (but without num) as in preope.c (in preope overlay)
typedef struct _Unknown2
{
    short x, y;
    int   color;
} Unknown2;

typedef struct _AbstRes
{
    int id;
    int file;
    int size;
} AbstRes;

typedef struct _Work
{
    GV_ACT   actor;
    int      end_proc;
    GV_PAD  *pad;
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    POLY_FT4 polys1[6];
    POLY_FT4 polys2[9];
    int      attrs1[6]; /* new name needed */
    int      attrs2[9]; /* new name needed */
    int      field_2C4;
    KCB      kcb[12];
    char     pad1[0x14];
    DR_TPAGE tpage[6];
    Unknown  field_51C[12];
    int      font_x;
    int      font_y;
    int      clut_x;
    int      clut_y;
    int      field_1D5C;
    char     pad3[0x4];
    int      field_1D64;
    int      field_1D68;
    char     pad4[0x20];
    MenuPrim primbuf;
    char     field_1DA0[0x2000];
    char     field_3DA0[0x2000];
    int      field_5DA0;
    int      field_5DA4;
} Work;

// TODO: give these proper names

void vrtitle_800D4F14(MenuPrim *prim, int x, int y, int w, int h)
{
    TILE *pTile;

    _NEW_PRIM(pTile, prim);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(prim->ot, pTile);

    radio_draw_face_frame(prim, x, y, w, h);
    radio_draw_face_frame(prim, x, y, w, h);
}
