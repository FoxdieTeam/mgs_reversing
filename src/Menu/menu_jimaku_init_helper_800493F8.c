#include "linker.h"
#include "mts/mts_new.h"
#include "Font/kcb.h"

extern const char	aJimakuFontBuff[];

// Redeclare to force $gp usage.
extern void*		MENU_JimakuTextBody_800ABB40;
void* SECTION(".sbss") MENU_JimakuTextBody_800ABB40;

void*		GV_AllocResidentMemory_800163D8(long size);
int			font_get_buffer_size_80044F38(KCB* kcb);
int			font_init_kcb_80044BE0(KCB* kcb, RECT* rect_data, short x, short y);
void			font_set_buffer_80044FD8(KCB* kcb, void* buffer);
void			font_set_color_80044DC4(KCB* kcb, int arg1, int arg2, int arg3);
int			font_set_kcb_80044C90(KCB *kcb, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void			font_clut_update_80046980(KCB* kcb);

void menu_jimaku_init_helper_800493F8(KCB* kcb)
{
    RECT rect;
    setRECT(&rect, 960, 256, 64, 38);
	
    font_init_kcb_80044BE0(kcb, &rect, 960, 510);
    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);
    mts_printf_8008BBA0(aJimakuFontBuff, font_get_buffer_size_80044F38(kcb));
    MENU_JimakuTextBody_800ABB40 = GV_AllocResidentMemory_800163D8(font_get_buffer_size_80044F38(kcb));
    font_set_buffer_80044FD8(kcb, MENU_JimakuTextBody_800ABB40);
    font_set_color_80044DC4(kcb, 0, 0x6739, 0);
    font_clut_update_80046980(kcb);
}
