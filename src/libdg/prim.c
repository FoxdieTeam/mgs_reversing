#include "libdg.h"
#include "inline_n.h"

extern int GV_Clock_800AB920;

void DG_PrimStart_8001AC00()
{
}

void DG_8001AC08(DVECTOR *xy0, DVECTOR *xy1, DVECTOR *xy2, DVECTOR *xy3)
{
    int x0 = xy0->vx;
    int x1 = xy1->vx;
    int y0 = xy0->vy;
    int y1 = xy1->vy;
    int x1_x0_diff = x1 - x0;
    int y1_y0_diff = y1 - y0;

    if ( x1_x0_diff < 0 )
    {
        x1_x0_diff = -x1_x0_diff;
    }

    if ( y1_y0_diff < 0 )
    {
        y1_y0_diff = -y1_y0_diff;
    }

    if ( y1_y0_diff >= x1_x0_diff )
    {
        xy2->vx = x0 + 2;
        xy2->vy = y0;
        xy3->vx = x1 + 2;
        xy3->vy = y1;
    }
    else
    {
        xy2->vy = y0 + 1;
        xy2->vx = x0;
        xy3->vx = x1;
        xy3->vy = y1 + 1;
    }
}

void DG_8001AC74(DG_PRIM *pPrims, int prim_type)
{
    // TODO: Check if these prim types are actually correct when we have more context
    if ( prim_type == 21 )
    {
        int n_prims;
        POLY_FT4 *i = (POLY_FT4 *)pPrims->field_40_pBuffers[GV_Clock_800AB920];
        for (n_prims = (signed short)pPrims->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((DVECTOR *)&i->x0, (DVECTOR *)&i->x1, (DVECTOR *)&i->x2, (DVECTOR *)&i->x3);
            i++;
        }
    }
    else // prim_type == 22 ?
    {
        int n_prims;
        POLY_GT4 *i = (POLY_GT4 *)pPrims->field_40_pBuffers[GV_Clock_800AB920];
        for (n_prims = (signed short)pPrims->n_prims ; n_prims > 0; --n_prims )
        {
            DG_8001AC08((DVECTOR *)&i->x0, (DVECTOR *)&i->x1, (DVECTOR *)&i->x2, (DVECTOR *)&i->x3);
            i++;
        }
    }
}

SVECTOR* sub_8001AD28( SVECTOR *svec, int n_svec )
{
  int      i;
  SVECTOR *svec2;
  
  svec2 = (SVECTOR*)0x1F800000;

  for ( i = n_svec - 1 ; i >= 0 ; --i ) 
  {
    gte_ldv3c( svec );
    gte_rtpt();
    gte_stsxy3( &svec2[0].vx, &svec2[1].vx, &svec2[2].vx );
    gte_stsz3(  &svec2[0].vz, &svec2[1].vz, &svec2[2].vz );
    svec  += 3;
    svec2 += 3;
  }

  return svec;
}