#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libdg/libdg.h"

void rank_800DAD08(int prim, POLY_FT4 *poly, int xl, int yt, int xr, int yb, int abe);

void rank_800DAD78(int prim, int tex_id, POLY_FT4 *poly, int xl, int yt, int xr, int yb, int abe, int orient)
{
    DG_TEX *tex;

    rank_800DAD08(prim, poly, xl, yt, xr, yb, abe);
    tex = DG_GetTexture(tex_id);

    if (orient == 0)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w + 1;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h + 1;
        poly->u3 = u + w + 1;
        poly->v3 = v + h + 1;
    }
    else if (orient == 1)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w + 1;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h;
        poly->u3 = u + w + 1;
        poly->v3 = v + h;
    }
    else if (orient == 2)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h + 1;
        poly->u3 = u + w;
        poly->v3 = v + h + 1;
    }
    else if (orient == 3)
    {
        int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
        poly->u0 = u;
        poly->v0 = v;
        poly->u1 = u + w;
        poly->v1 = v;
        poly->u2 = u;
        poly->v2 = v + h;
        poly->u3 = u + w;
        poly->v3 = v + h;
    }
    else
    {
        return;
    }

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
