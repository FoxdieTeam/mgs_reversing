#include "linker.h"
#include "mts/mts_new.h"
#include "Font/font.h"
#include "unknown.h"

// Redeclare to force $gp usage.
extern void *MENU_JimakuTextBody_800ABB40;
void        *SECTION(".sbss") MENU_JimakuTextBody_800ABB40;

void menu_jimaku_init_helper_800493F8(KCB *kcb)
{
    RECT rect;
    setRECT(&rect, 960, 256, 64, 38);

    font_init_kcb_80044BE0(kcb, &rect, 960, 510);
    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);
    mts_printf_8008BBA0("jimaku_font_buffer_size %d\n", font_get_buffer_size_80044F38(kcb));
    MENU_JimakuTextBody_800ABB40 = GV_AllocResidentMemory_800163D8(font_get_buffer_size_80044F38(kcb));
    font_set_buffer_80044FD8(kcb, MENU_JimakuTextBody_800ABB40);
    font_set_color_80044DC4(kcb, 0, 0x6739, 0);
    font_clut_update_80046980(kcb);
}
