#include "common.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Game/map.h"
#include "libdg/libdg.h"
#include <libgpu.h>

extern DG_CHNL DG_Chanls_800B1800[3];

extern int     GM_CurrentMap_800AB9B0;
int            SECTION(".sbss") GM_CurrentMap_800AB9B0;

POLY_FT4 * Takabe_MakeIndividualRect3DPrim_helper_80079284(DG_PRIM *pPrim, POLY_FT4 *pPolys, int numPrims)
{
    SVECTOR *pVec;
    SVECTOR *pVec2;
    int clip_dist;
    int zdiv;
    int range;
    int x, y;
    int clamp;

    pVec = pPrim->field_38_pUnknown;
    pVec2 = (SVECTOR *)getScratchAddr(0);

    clip_dist = DG_Chanls_800B1800[1].field_50_clip_distance;

    while (--numPrims >= 0)
    {
        zdiv = LLOAD(&pVec2->vz);

        if (zdiv != 0)
        {
            range = (pVec->pad * clip_dist) / zdiv;

            SSTOREL(zdiv, &pPolys->tag);

            x = pVec2->vx;
            y = pVec2->vy;

            clamp = x - range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            pPolys->x0 = clamp;
            pPolys->x2 = clamp;

            clamp = x + range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            pPolys->x1 = clamp;
            pPolys->x3 = clamp;

            clamp = y - range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            pPolys->y0 = clamp;
            pPolys->y1 = clamp;

            clamp = y + range;

            if (clamp > 1023)
            {
                clamp = 1023;
            }
            else if (clamp < -1024)
            {
                clamp = -1024;
            }

            pPolys->y2 = clamp;
            pPolys->y3 = clamp;
        }
        else
        {
            SSTOREL(0, &pPolys->tag);
        }

        pVec2++;
        pPolys++;
        pVec++;
    }

    return pPolys;
}

DG_PRIM * Takabe_MakeIndividualRect3DPrim_800793E8(int prim_count, SVECTOR *pVec)
{
    DG_PRIM *pNewPrim = DG_GetPrim(8210, prim_count, 0, pVec, NULL);

    pNewPrim->field_50_pFn = &Takabe_MakeIndividualRect3DPrim_helper_80079284;
    pNewPrim->field_48_prim_count = prim_count;
    return pNewPrim;
}
