#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void rank_800DAD08(int prim, POLY_FT4 *poly, int xl, int yt, int xr, int yb, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0x40, 0x40, 0x40);
    setXY4(poly, xl, yt, xr, yt, xl, yb, xr, yb);
    SetSemiTrans(poly, abe);
}
