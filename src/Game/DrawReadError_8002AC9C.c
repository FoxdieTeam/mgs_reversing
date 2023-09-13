#include "psyq.h"
#include "libdg/libdg.h"

extern DG_TEX gMenuTextureRec_800B58B0;

void DrawReadError_8002AC9C()
{
    int      u_off;
    DR_TPAGE tpage;
    SPRT     sprt;
    TILE     tile;

    u_off = 16 * gMenuTextureRec_800B58B0.field_0_hash;
    gMenuTextureRec_800B58B0.field_0_hash = (gMenuTextureRec_800B58B0.field_0_hash + 1) % 6;

    DG_PutDrawEnv_From_DispEnv_80017890();

    setDrawTPage(&tpage, 1, 1, gMenuTextureRec_800B58B0.field_4_tPage);
    DrawPrim(&tpage);

    LSTORE(0, &tile.r0);
    setTile(&tile);
    tile.x0 = 287;
    tile.y0 = 15;
    tile.h = 18;
    tile.w = 18;
    DrawPrim(&tile);

    LSTORE(0x80808080, &sprt.r0);
    setSprt(&sprt);
    sprt.w = 16;
    sprt.h = 16;
    sprt.x0 = 288;
    sprt.y0 = 16;
    sprt.u0 = gMenuTextureRec_800B58B0.field_8_offx + u_off;
    sprt.v0 = gMenuTextureRec_800B58B0.field_9_offy;
    sprt.clut = gMenuTextureRec_800B58B0.field_6_clut;
    DrawPrim(&sprt);
}
