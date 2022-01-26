#include "linker.h"
#include "libdg.h"

void item_init_prim_buffer_800336A4(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1
  
    setPolyFT4(prims);
    setSemiTrans(prims, 1);    

    t_u0 = tex->field_8_offx;
    t_u1 = t_u0 + tex->field_A_width;

    t_v0 = tex->field_9_offy;
    t_v2 = t_v0 + tex->field_B_height;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->field_4_tPage;
    prims->clut = tex->field_6_clut;
}
