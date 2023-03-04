#include "Font/font.h"
#include "libgv/libgv.h"

extern short coords_800AB600[2][2];

extern RECT rect_800AB600;
RECT        rect_800AB600;

extern SPRT gMenuSprt_800bd998;
extern KCB  font_800BD968;

int sub_8003F84C(int idx)
{
    void *font_buffer;

    setSprt(&gMenuSprt_800bd998);

    gMenuSprt_800bd998.u0 = 0;
    gMenuSprt_800bd998.v0 = rect_800AB600.y;

    gMenuSprt_800bd998.r0 = 128;
    gMenuSprt_800bd998.g0 = 128;
    gMenuSprt_800bd998.b0 = 128;

    gMenuSprt_800bd998.w = 200;
    gMenuSprt_800bd998.h = 80;

    // Callers to this function call it with idx = 0 or idx = 1
    gMenuSprt_800bd998.x0 = coords_800AB600[idx][0];
    gMenuSprt_800bd998.y0 = coords_800AB600[idx][1];
    gMenuSprt_800bd998.clut = 0x7fbc;

    ClearImage(&rect_800AB600, 0, 0, 0);

    font_init_kcb_80044BE0(&font_800BD968, &rect_800AB600, 960, 510);
    font_set_kcb_80044C90(&font_800BD968, -1, -1, 0, 6, 2, 0);

    font_buffer = GV_Malloc_8001620C(font_get_buffer_size_80044F38(&font_800BD968));
    if (font_buffer == NULL)
    {
        return 0;
    }

    font_set_buffer_80044FD8(&font_800BD968, font_buffer);
    font_set_color_80044DC4(&font_800BD968, 0, 0x6739, 0);
    font_clut_update_80046980(&font_800BD968);
    return 1;
}
