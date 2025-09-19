#include "prim.h"

#include <stddef.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"

extern DG_CHANL DG_Chanls[3];

/*---------------------------------------------------------------------------*/

static POLY_FT4 *MakeIndividualRect3DPrimHandler(DG_PRIM *prim, POLY_FT4 *packs, int n_packs)
{
    SVECTOR *verts;
    SVECTOR *in;
    int      clip_dist;
    int      zdiv;
    int      range;
    int      x, y;
    int      clamp;

    verts = prim->vertices;
    in = (SVECTOR *)getScratchAddr(0);

    clip_dist = DG_Chanls[1].clip_distance;

    while (--n_packs >= 0)
    {
        zdiv = LLOAD(&in->vz);

        if (zdiv != 0)
        {
            range = (verts->pad * clip_dist) / zdiv;

            SSTOREL(zdiv, &packs->tag);

            x = in->vx;
            y = in->vy;

            clamp = x - range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            packs->x0 = clamp;
            packs->x2 = clamp;

            clamp = x + range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            packs->x1 = clamp;
            packs->x3 = clamp;

            clamp = y - range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            packs->y0 = clamp;
            packs->y1 = clamp;

            clamp = y + range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            packs->y2 = clamp;
            packs->y3 = clamp;
        }
        else
        {
            SSTOREL(0, &packs->tag);
        }

        in++;
        packs++;
        verts++;
    }

    return packs;
}

DG_PRIM *Takabe_MakeIndividualRect3DPrim(int n_vertices, SVECTOR *vertices)
{
    DG_PRIM *prim = DG_GetPrim(DG_PRIM_FREEPACKS | DG_PRIM_POLY_FT4, n_vertices, 0, vertices, NULL);

    prim->handler = &MakeIndividualRect3DPrimHandler;
    prim->n_vertices = n_vertices;

    return prim;
}
