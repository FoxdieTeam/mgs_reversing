#include "linker.h"
#include "font.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

extern char *gFontBegin;
char        *SECTION(".sdata") gFontBegin;

extern int rubi_display_flag_800AB6B0;
int        SECTION(".sdata") rubi_display_flag_800AB6B0;

// Menu-related?

extern int rubi_left_pos_x_800ABB2C;
int        SECTION(".sbss") rubi_left_pos_x_800ABB2C;

extern int rubi_left_pos_y_800ABB30;
int        SECTION(".sbss") rubi_left_pos_y_800ABB30;

extern int rubi_left_pos_xmax_800ABB34;
int        SECTION(".sbss") rubi_left_pos_xmax_800ABB34;

extern char *dword_800ABB28;
char        *SECTION(".sbss") dword_800ABB28;

extern char *gFontEnd;
char        *SECTION(".sbss") gFontEnd;

extern RubiRes *gRubiRes_800AB6B4;
RubiRes        *SECTION(".sbss") gRubiRes_800AB6B4;

extern int                  dword_800AB6B8;
int        SECTION(".sbss") dword_800AB6B8;

extern int                  dword_800AB6BC;
int        SECTION(".sbss") dword_800AB6BC;

extern void *dword_8009E75C[];

void font_load_80044A9C(void)
{
    char *temp_a1;
    char *ptr;

    // Load 'font.res' file:
    dword_800ABB28 = GV_GetCache_8001538C(GV_CacheID_800152DC(0xCA68, 'r'));

    if (dword_800ABB28)
    {
        // Load 'rubi.res' file:
        gRubiRes_800AB6B4 = (RubiRes *)GV_GetCache_8001538C(GV_CacheID_800152DC(0xE0E3, 'r'));

        temp_a1 = dword_800ABB28;
        LSTORE((temp_a1[0] << 24) | (temp_a1[1] << 16) | (temp_a1[2] << 8) | temp_a1[3], temp_a1);

        temp_a1 = dword_800ABB28;
        LSTORE((temp_a1[4] << 24) | (temp_a1[5] << 16) | (temp_a1[6] << 8) | temp_a1[7], temp_a1 + 4);

        gFontBegin = temp_a1 + 8;
        gFontEnd = temp_a1 + LLOAD(temp_a1 + 0);
        dword_8009E75C[0] = temp_a1 + LLOAD(temp_a1 + 4);

        for (ptr = temp_a1 + 8; ptr < gFontEnd; ptr += 4)
        {
            LSTORE((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3], ptr);
        }
    }
}

void font_set_font_addr_80044BC0(int arg1, void *data)
{
    dword_8009E75C[arg1] = data;
}

void sub_80044BD8(void)
{
    return;
}

int font_init_kcb_80044BE0(KCB *kcb, RECT *rect_data, short x, short y)
{
    *kcb = ( KCB ){{ 0 }};
    kcb->rect_data = rect_data;
    kcb->font_rect = *rect_data;
    kcb->font_clut_rect.w = 16;
    kcb->font_clut_rect.h = 1;
    kcb->font_clut_rect.x = x;
    kcb->font_clut_rect.y = y;
    return font_set_kcb_80044C90(kcb, -1, -1, 0, 0, 4, 0);
}

int font_set_kcb_80044C90(KCB *kcb, int arg1, int arg2, int arg3,
                                    int arg4, int arg5, int arg6)
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

int font_draw_string_helper4_80044FF4(int code)
{
    int new_var2;
    int var_v0;
    int temp_v0;
    int temp_a0;

    code &= ~0x6000;

    if (code < 0x8200)
    {
        var_v0 = code - 0x8101;
    }
    else if (code < 0x8300)
    {
        var_v0 = code - 0x81ae;
    }
    else if (code < 0x9600)
    {
        var_v0 = (code - 0x8F71 - (code / 256)) + 0xA9;
    }
    else if (code < 0x9A00)
    {
        var_v0 = ((code - 0x956B) - (code / 256)) | 0x1000;
    }
    else
    {
        temp_v0 = (code - 0x9a00) / 512;
        temp_a0 = code - 0x9A00 - (temp_v0 * 512);
        new_var2 = temp_v0 + 2;
        var_v0 = (temp_a0 - 1 - (temp_a0 / 256)) | (new_var2 * 4096);
    }

    return var_v0 + 1;
}

unsigned int sub_800450F4(int a1)
{
    if (a1 > 0)
    {
        if (a1 > 128)
        {
            a1 -= 34;
        }

        a1 -= 32;
    }

    return LLOAD(&gFontBegin[4 * a1]);
}

void font_draw_string_helper5_80045124(char *arg0, int arg1, int arg2, int arg3, char *arg4)
{
    unsigned int i;
    int          j;
    int          temp_a1;
    char        *temp_v1;
    int          var_a2;
    int          var_t5;
    int          var_v1;
    unsigned int var_v0;
    char        *temp_a0;
    char        *temp_v1_2;
    char        *var_a1;
    char        *var_t1;
    unsigned int temp_t3;
    char         temp_v0;
    char         var_t4;
    int          new_var;
    int          new_var2;

    temp_v0 = dword_800AB6BC;
    temp_t3 = (temp_v0 << 6) | (temp_v0 * 4);

    if (dword_800AB6B8 != 0)
    {
        var_v1 = arg2 - 4;

        if (rubi_display_flag_800AB6B0 == 0)
        {
            var_v1 = arg2 - 2;
        }

        temp_v1 = arg0 + ((arg1 + 5) / 2);
        temp_a0 = temp_v1 + ((var_v1 - 1) * arg3);
        temp_a1 = temp_t3 | 0x33;
        *temp_a0 |= temp_a1;
        temp_v1_2 = temp_v1 + (var_v1 * arg3);
        *temp_v1_2 |= temp_a1;
    }

    var_a1 = arg4;
    arg0 = arg0 + (arg1 / 2) + ((++arg2) * arg3);

    if (!(arg1 & 1))
    {
        if (var_a1 == NULL)
        {
            for (i = 0; i < 12; i++)
            {
                *arg0++ = temp_t3;
                *arg0++ = temp_t3;
                *arg0++ = temp_t3;
                *arg0++ = temp_t3;
                *arg0++ = temp_t3;
                *arg0++ = temp_t3;
                arg0 += arg3 - 6;
            }

            return;
        }

        for (i = 0; i < 12; i++)
        {
            *arg0++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *arg0++ = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 16));
            var_a1++;

            *arg0++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *arg0++ = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 0x10));
            var_a1++;

            *arg0++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *arg0 = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 0x10));
            var_a1++;

            arg0 = (arg0 + arg3) - 5;
        }

        return;
    }

    if (var_a1 == NULL)
    {
        for (i = 0; i < 12; i++)
        {
            *arg0++ = (*arg0 & 0xF) | (temp_t3 & 0xF0);
            *arg0++ = temp_t3;
            *arg0++ = temp_t3;
            *arg0++ = temp_t3;
            *arg0++ = temp_t3;
            *arg0++ = temp_t3;
            *arg0 = (*arg0 & 0xF0) | (temp_t3 & 0xF);
            arg0 += arg3 - 6;
        }

        return;
    }

    var_t5 = 4;
    new_var2 = (dword_800AB6BC & 0xff) << 2;
    var_t4 = *var_a1;

    for (i = 0; i < 12; i++)
    {
        var_a2 = (1 - (arg1 % 2)) * 4;
        var_t1 = arg0;
        temp_t3 = new_var2;

        for (j = 0; j < 12; j++)
        {
            var_v0 = var_t4;
            var_v0 >>= 6;
            new_var = temp_t3 | var_v0;

            if (--var_t5 == 0)
            {
                var_a1++;
                var_t4 = *var_a1;
                var_t5 = 4;
            }
            else
            {
                var_t4 <<= 2;
            }

            *var_t1 |= (new_var & 0xFF) << (4 - var_a2);

            if (var_a2 == 0)
            {
                var_t1++;
                var_a2 = 4;
            }
            else
            {
                var_a2 = 0;
            }
        }

        arg0 += arg3;
    }
}

#pragma INCLUDE_ASM("asm/Font/font_draw_string_helper6_8004544C.s") // 716 bytes

unsigned int font_draw_string_helper_80045718(int a1)
{
    if (a1 == 0x8000)
    {
        return 0;
    }

    if (a1 < 0x8100)
    {
        if ((a1 != 0x8023) && ((a1 < 0x8010) || (a1 >= 0x8020)))
        {
            return (sub_800450F4(a1 & 0xFF) >> 24) & 0xF;
        }
    }

    return 12;
}

void set_rubi_display_flag_80045788(int display_flag)
{
    rubi_display_flag_800AB6B0 = display_flag;
}

void set_rubi_left_pos_80045794(int xmax, int x, int y)
{
    rubi_left_pos_x_800ABB2C = x;
    rubi_left_pos_y_800ABB30 = y;
    rubi_left_pos_xmax_800ABB34 = xmax;
}

void set_rubi_left_xmax_800457A8(int xmax)
{
    rubi_left_pos_xmax_800ABB34 = xmax;
}

#define ASCII_TO_RUBI(c) (c + 0x8000)

int get_rubi_char_index_800457B4(int c)
{
    if (c < 0x8100)
    {
        if (c >= ASCII_TO_RUBI('0') && c <= ASCII_TO_RUBI('9'))
        {
            return c - 0x7fdf;
        }
        if (c >= ASCII_TO_RUBI('A') && c <= ASCII_TO_RUBI('Z'))
        {
            return c - 0x7fe6;
        }
        if (c >= ASCII_TO_RUBI('-') && c <= ASCII_TO_RUBI('.'))
        {
            return c - 0x7fb8;
        }
        if (c == ASCII_TO_RUBI(127)) // del
        {
            return 0x76;
        }
        if (c == ASCII_TO_RUBI('-'))
        {
            return 0x75;
        }
        if (c == ASCII_TO_RUBI(' '))
        {
            return 0;
        }
    }
    else
    {
        if (c >= 0x8201 && c <= 0x824D) // Katakana character ('ァ' ... 'ロ')
        {
            return c - 0x8200;
        }
        if (c == 0x824f) // 'ヲ'
        {
            return 0x4e;
        }
        if (c == 0x8252)
        {
            return 0x4f;
        }
        if (c == 0x8253) // 'ン'
        {
            return 0x50;
        }
        if (c == 0x9006)
        {
            return 0x75;
        }
        if (c == 0x9001) // '　'
        {
            return 0;
        }
    }
    return -1;
}

extern char aWrongRubiCodeX[];

int font_draw_string_helper3_helper_800458B8(int *outIterCount, unsigned char *str)
{
    RubiRes       *rubiRes;
    int            rubiCode;
    int            retval; // some sort of length corrected by rubi codes?
    int            i, idx;
    unsigned char *strIter;

    rubiRes = gRubiRes_800AB6B4;
    retval = 0;

    for (i = 0, strIter = str;; i++)
    {
        if (strIter[0] < 128)
        {
            rubiCode = strIter[0] | 0x8000;
            strIter += 1;
        }
        else
        {
            rubiCode = (strIter[0] << 8) | strIter[1];
            strIter += 2;
        }

        rubiCode &= ~0x6000;
        if (rubiCode == 0x807D)
            break;

        idx = get_rubi_char_index_800457B4(rubiCode);
        if (idx < 0)
        {
            mts_printf_8008BBA0(aWrongRubiCodeX, rubiCode);
            idx = 0;
        }

        if (idx == 0)
        {
            retval += 4;
        }
        else
        {
            retval += rubiRes[idx - 1].field_0;
        }
    }
    *outIterCount = i;
    return retval;
}

int font_draw_string_helper3_helper2_800459B0(char *arg0, int arg1, int arg2, int arg3, int arg4)
{
    int          oddIter, var_a1, j, var_t3, i, var_v0_2, rubiField0, var_t0;
    unsigned int var_v0;
    RubiRes     *rubiRes;
    char        *arg0_iter1, *rubiRes_iter, *rubiResPtr, *arg0_iter2;

    i = 0;
    rubiRes = &gRubiRes_800AB6B4[arg4];
    rubiResPtr = &rubiRes->field_0;
    rubiField0 = *rubiResPtr;

    arg2++;
    arg0_iter1 = arg0 + arg1 / 2 + arg2 * arg3;
    arg0_iter2 = arg0_iter1;
    rubiResPtr = rubiRes->field_1;

    for (; i < 6; arg0_iter1 += arg3, arg0_iter2 = arg0_iter1, i++)
    {
        rubiRes_iter = &rubiResPtr[i / 2 * 3];
        oddIter = i & 1;
        var_t3 = (1 - arg1 % 2) * 4;

        if (oddIter)
        {
            rubiRes_iter++;
            var_t0 = *rubiRes_iter;
            rubiRes_iter++;
        }
        else
        {
            var_t0 = *rubiRes_iter;
            rubiRes_iter++;
        }

        if (oddIter)
        {
            var_t0 *= 16;
            var_a1 = 2;
        }
        else
        {
            var_a1 = 4;
        }

        for (j = 0; j < rubiField0; j++)
        {
            var_v0 = var_t0 & 0xFF;
            do
            {
                var_a1 -= 1;
            } while (0);

            var_v0_2 = var_v0 >> 6;
            if (var_a1 == 0)
            {
                var_t0 = *rubiRes_iter;
                rubiRes_iter++;
                var_a1 = 4;
            }
            else
            {
                var_t0 *= 4;
            }

            *arg0_iter2 |= var_v0_2 << (4 - var_t3);
            if (var_t3 == 0)
            {
                arg0_iter2++;
                var_t3 = 4;
            }
            else
            {
                var_t3 = 0;
            }
        }
    }
    return rubiField0;
}

void font_draw_string_helper3_80045AE4(char *arg0, int x, int y, int arg3, unsigned char *arg4)
{
    int            iterCount;
    int            len;
    int            rubiCode, pos_y_2;
    int            pos_x;
    int            pos_x_2;
    int            x_offset;
    int            pos_y;
    int            rubiIndex;
    unsigned char *str;
    str = arg4;
    if (arg0 == 0)
    {
        return;
    }
    len = font_draw_string_helper3_helper_800458B8(&iterCount, str);
    pos_y_2 = y;

    if (rubi_left_pos_y_800ABB30 < pos_y_2)
    {
        pos_x = rubi_left_pos_xmax_800ABB34 - rubi_left_pos_x_800ABB2C;
        pos_y = rubi_left_pos_y_800ABB30;
        if (x / 2 >= pos_x)
        {
            do
            {
                pos_y = y;
            } while (0);
            pos_x = x;
            rubi_left_pos_x_800ABB2C = 0;
        }
    }
    else
    {
        pos_y = pos_y_2;
        pos_x = x - rubi_left_pos_x_800ABB2C;
    }

    x_offset = 1;
    iterCount--;
    if (iterCount > 0 && (len - pos_x) < 0)
    {
        x_offset = (pos_x - len) / iterCount;
        if (x_offset >= 5)
        {
            x_offset = 4;
        }
        if (x_offset <= 0)
        {
            x_offset = 1;
        }
    }
    len += x_offset * iterCount;
    pos_x = rubi_left_pos_x_800ABB2C + (pos_x - len) / 2;
    if (rubi_left_pos_xmax_800ABB34 < pos_x + len)
    {
        pos_x = rubi_left_pos_xmax_800ABB34 - len;
    }
    if (pos_x < 0)
    {
        pos_x = 0;
    }
    pos_x_2 = pos_x;
    while (1)
    {
        if (str[0] < 128)
        {
            do
            {
                rubiCode = str[0] | 0x8000;
                str += 1;
            } while (0);
        }
        else
        {
            rubiCode = (str[0] << 8) | str[1];
            str += 2;
        }
        rubiCode &= ~0x6000;
        if (rubiCode == 0x807D)
        {
            break;
        }
        rubiIndex = get_rubi_char_index_800457B4(rubiCode);
        if (rubiIndex < 0)
        {
            mts_printf_8008BBA0(aWrongRubiCodeX, rubiCode);
            rubiIndex = 0;
        }
        if (rubiIndex == 0)
        {
            pos_x_2 += 4 + x_offset;
        }
        else
        {
            pos_x_2 +=
                font_draw_string_helper3_helper2_800459B0(arg0, pos_x_2, pos_y - 6, arg3, rubiIndex - 1) + x_offset;
        }
    }
}

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

void sub_800469A4(KCB *param_1, char *param_2)
{
    font_clear_800468FC(param_1);
    font_draw_string_80045D0C(param_1, 0, (unsigned int)param_1->char_arr[3], param_2,
                              (unsigned int)param_1->char_arr[5]);
}
