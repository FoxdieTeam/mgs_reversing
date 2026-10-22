// vrsave: VR revision copy of menu/radio.c
// (init_radio_message_board_80040F74), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "menu/menuman.h"

#include <stdio.h>
#include <string.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "font/font.h"
#include "menu/radio.h"

extern RECT vrsave_dword_800D152C; // = {960, 260, 63, 76}

void vrsave_800CA144(MenuWork *work)
{
    KCB  local_kcb;
    KCB *allocated_kcb;
    RECT rect;

    rect = vrsave_dword_800D152C;
    rect.x = 896;
    rect.h = 128;

    if (work->field_214_font == NULL)
    {
        KCB *ptr_local_kcb = &local_kcb;

        GV_ZeroMemory(ptr_local_kcb, sizeof(KCB));
        ClearImage(&rect, 0, 0, 0);

        font_init_kcb(ptr_local_kcb, &rect, 960, 510);
        font_set_kcb(ptr_local_kcb, -1, -1, 0, 0, 2, 0);

        allocated_kcb = (KCB *)GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(ptr_local_kcb) + sizeof(KCB));
        font_set_buffer(ptr_local_kcb, allocated_kcb + 1);
        font_set_color(ptr_local_kcb, 0, 0x6739, 0);
        font_set_color(ptr_local_kcb, 1, 0x3bef, 0);
        font_set_color(ptr_local_kcb, 2, 0x3a4b, 0);
        font_clut_update(ptr_local_kcb);

        work->field_214_font = allocated_kcb;
        memcpy(allocated_kcb, ptr_local_kcb, sizeof(KCB));
    }
}
