// vrtitle: VR revision copy of overlays/rank/chara/pocket/entry.c
// (rank_800D21BC), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "game/game.h"

// Sets the color of a textured quad, keeping the semi-transparency bit of its code
void vrtitle_800C3C10( POLY_FT4 *prim, unsigned int rgb )
{
    unsigned int code;

    code = prim->code;
    code &= 2;
    code |= 0x2C;
    code <<= 24;
    rgb |= code;
    // FIXME: word store of r0/g0/b0/code
    *(unsigned int *)&prim->r0 = rgb;
}
