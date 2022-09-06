#include "libdg.h"

void DG_LoadInitPcx_helper_8001D880(int hash, int tp, int abr, DG_Image *a, DG_Image *b, int param_6)
{
    DG_TEX *tex;
    
    int x, y, w, h;
    int cx, cy;
    int tpage;
    int temp;
    
    if (DG_SearchForTextureRecord_8001D778(hash, &tex) && tex->field_2_bUsed.c[0])
    {
        tex->field_0_hash = 0;
    }

    tex->field_0_hash = hash;
    tex->field_2_bUsed.c[1] = param_6;
    tex->field_2_bUsed.c[0] = 0;

    x = a->dim.x;
    y = a->dim.y;

    cx = b->dim.x;
    cy = b->dim.y;

    // They didn't use the LIBGPU macros :(
    temp = x;
    tpage = ((temp / 64) + ((y / 256) << 4)) | ((tp << 7) | (abr << 5));

    tex->field_4_tPage = tpage;
    tex->field_6_clut = cy << 6 | cx >> 4;
    
    x %= 64;

    w = a->dim.w;
    h = a->dim.h;
    
    if (tp == 0)
    {
        x *= 4;
        w *= 4;
    }
    else
    {
        x *= 2;
        w *= 2;
    }

    tex->field_8_offx = x;
    tex->field_9_offy = y % 256;

    tex->field_A_width = w - 1;
    temp = h;
    tex->field_B_height = temp - 1;
}
