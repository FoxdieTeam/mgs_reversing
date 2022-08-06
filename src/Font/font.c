#include "linker.h"
#include "font.h"
#include "psyq.h"

extern int dword_800AB6A8;
int        SECTION(".sdata") dword_800AB6A8;

extern int dword_800AB6B0;
int        SECTION(".sdata") dword_800AB6B0;

// Menu-related?

extern int dword_800ABB2C;
int        SECTION(".sbss") dword_800ABB2C;

extern int dword_800ABB30;
int        SECTION(".sbss") dword_800ABB30;

extern int dword_800ABB34;
int        SECTION(".sbss") dword_800ABB34;

int font_init_kcb_80044BE0(KCB *kcb, RECT *rect_data, short x, short y)
{
    memset_8008E688((char *)kcb, 0, 44);
    kcb->rect_data = rect_data;
    kcb->font_rect = *rect_data;
    kcb->font_clut_rect.w = 16;
    kcb->font_clut_rect.h = 1;
    kcb->font_clut_rect.x = x;
    kcb->font_clut_rect.y = y;
    return font_set_kcb_80044C90(kcb, -1, -1, 0, 0, 4, 0);
}

int font_set_kcb_80044C90(KCB *kcb, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int quotient0;
    int quotient1;
    int val0;

    if (arg6 >= 0)
    {
        kcb->char_arr[6] = arg6;
    }
    if (arg5 >= 0)
    {
        kcb->char_arr[4] = arg5;
    }
    if (arg3 >= 0)
    {
        kcb->char_arr[2] = arg3;
    }
    if (arg4 >= 0)
    {
        kcb->char_arr[3] = arg4;
    }

    quotient0 = (kcb->rect_data->w * 4) / (kcb->char_arr[2] + 12);

    quotient1 = kcb->rect_data->h / (kcb->char_arr[3] + 12);

    val0 = quotient0 + 1;
    if ((arg6 & 0x2) == 0)
    {
        val0 = quotient0;
    }

    if (arg1 > 0 && val0 >= arg1)
    {
        kcb->char_arr[0] = arg1;
    }
    else if (kcb->char_arr[0] != 0)
    {
        if (val0 < kcb->char_arr[0])
        {
            kcb->char_arr[0] = val0;
        }
    }
    else
    {
        kcb->char_arr[0] = val0;
    }

    if (arg2 > 0 && quotient1 >= arg2)
    {
        kcb->char_arr[1] = arg2;
    }
    else if (kcb->char_arr[1] == 0 || quotient1 < kcb->char_arr[1])
    {
        kcb->char_arr[1] = quotient1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/Font/font_set_color_80044DC4.s") // 372 bytes

int font_get_buffer_size_80044F38(KCB *kcb)
{
    short val_1 = (kcb->char_arr[2] + 0xc) * kcb->char_arr[0] - kcb->char_arr[2];
    int   val_2 = (int)val_1 + 7;
    kcb->short1 = val_1;
    if (val_2 < 0)
    {
        val_2 = kcb->short1 + 14;
    }

    kcb->width_info = ((val_2 >> 3) << 2);
    kcb->height_info = (kcb->char_arr[3] + 12) * kcb->char_arr[1] + 2;
    kcb->font_rect.w = kcb->width_info / 2;
    kcb->font_rect.h = kcb->height_info;

    return kcb->width_info * kcb->height_info + 32;
}

void font_set_buffer_80044FD8(KCB *kcb, void *buffer)
{
    kcb->font_clut_buffer = buffer;
    kcb->font_buffer = buffer + 0x20;
}

void *font_get_buffer_ptr_80044FE8(KCB *kcb)
{
    return kcb->font_clut_buffer;
}

#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper4_80044FF4.s") // 256 bytes

int sub_800450F4(int a1)
{
    if (a1 > 0)
    {
        if (a1 >= 129)
            a1 -= 34;
        a1 -= 32;
    }
    return *(int *)(4 * a1 + dword_800AB6A8);
}

#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper5_80045124.s") // 808 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper6_8004544C.s") // 716 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper_80045718.s")  // 112 bytes

void sub_80045788(int param_1)
{
    dword_800AB6B0 = param_1;
}

void font_draw_string_helper2_80045794(int param_1, int param_2, int param_3)
{
    dword_800ABB2C = param_2;
    dword_800ABB30 = param_3;
    dword_800ABB34 = param_1;
    return;
}

void font_draw_string_helper7_800457A8(int param_1)
{
    dword_800ABB34 = param_1;
}

#pragma INCLUDE_ASM("asm/Font/sub_800457B4.s")                              // 260 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper3_helper_800458B8.s")  // 248 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper3_helper2_800459B0.s") // 308 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper3_80045AE4.s")         // 552 bytes
#pragma INCLUDE_ASM("asm/Font/font_draw_string_80045D0C.s")                 // 3056 bytes

void font_clear_800468FC(KCB *kcb)
{
    int *font_buffer;
    int  i;

    if (!(kcb->char_arr[6] & 0x10))
    {
        font_buffer = kcb->font_buffer;
        i = (unsigned int)(kcb->width_info * kcb->height_info) / 4;
        for (; i > 0; i--)
        {
            *font_buffer++ = 0;
        }
        kcb->char_arr[6] |= 0x10;
    }
}

void font_update_8004695C(KCB *kcb)
{
    LoadImage_8008FB10(&kcb->font_rect, kcb->font_buffer);
}

void font_clut_update_80046980(KCB *kcb)
{
    LoadImage_8008FB10(&kcb->font_clut_rect, kcb->font_clut_buffer);
}
