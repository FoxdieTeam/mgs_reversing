// vrtitle: VR revision copy of overlays/rank/chara/pocket/pkt_back.c
// (rank_800D007C), adapted from the asm.
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "game/game.h"

extern int vrtitle_dword_800C13F8;

// Positions the three background quads (left, middle, right) for the given zoom
void vrtitle_800C5B60( POLY_FT4 *polys, int step, int mid )
{
    int scale;
    int bottom_px;
    int right_px;
    int left;
    int top;
    int right;
    int bottom;
    int x1;
    int x2;

    scale = vrtitle_dword_800C13F8 + step;
    right_px = scale * 0xA0;
    left = -right_px / vrtitle_dword_800C13F8;
    bottom_px = scale * 0x70;
    top = -bottom_px / vrtitle_dword_800C13F8;
    right = right_px / vrtitle_dword_800C13F8;
    bottom = bottom_px / vrtitle_dword_800C13F8;
    x1 = mid * scale / vrtitle_dword_800C13F8;
    x2 = ( mid + 0xA0 ) * scale / vrtitle_dword_800C13F8;

    polys[ 0 ].x0 = left;
    polys[ 0 ].y0 = top;
    polys[ 0 ].y1 = top;
    polys[ 0 ].x2 = left;
    polys[ 0 ].y2 = bottom;
    polys[ 0 ].y3 = bottom;
    polys[ 1 ].y0 = top;
    polys[ 1 ].y1 = top;
    polys[ 1 ].y2 = bottom;
    polys[ 1 ].y3 = bottom;
    polys[ 2 ].y0 = top;
    polys[ 2 ].x1 = right;
    polys[ 2 ].y1 = top;
    polys[ 2 ].y2 = bottom;
    polys[ 2 ].x3 = right;
    polys[ 2 ].y3 = bottom;
    polys[ 0 ].x1 = x1;
    polys[ 0 ].x3 = x1;
    polys[ 1 ].x0 = x1;
    polys[ 1 ].x2 = x1;
    polys[ 1 ].x1 = x2;
    polys[ 1 ].x3 = x2;
    polys[ 2 ].x0 = x2;
    polys[ 2 ].x2 = x2;
}
