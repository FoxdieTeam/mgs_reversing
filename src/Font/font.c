#include "linker.h"
#include "font.h"
#include "psyq.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"

char    *gFontBegin = NULL;
char    *gFontEnd = NULL;
int      rubi_display_flag_800AB6B0 = 1;
RubiRes *gRubiRes_800AB6B4 = NULL;
int      dword_800AB6B8 = 0;
int      font_palette_800AB6BC = 0;
int      r_flag_800AB6C0 = 0;
int      rubi_flag_800AB6C4 = 0;

// Menu-related?

extern int rubi_left_pos_x_800ABB2C;
int        SECTION(".sbss") rubi_left_pos_x_800ABB2C;

extern int rubi_left_pos_y_800ABB30;
int        SECTION(".sbss") rubi_left_pos_y_800ABB30;

extern int rubi_left_pos_xmax_800ABB34;
int        SECTION(".sbss") rubi_left_pos_xmax_800ABB34;

extern char *dword_800ABB28;
char        *SECTION(".sbss") dword_800ABB28;

char *dword_8009E75C[] = {NULL, NULL, NULL, NULL};

#define HASH_FONT   0xCA68  // GV_StrCode("font")
#define HASH_RUBI   0xE0E3  // GV_StrCode("rubi")

void font_load_80044A9C(void)
{
    char *temp_a1;
    char *ptr;

    // Load 'font.res' file:
    dword_800ABB28 = GV_GetCache_8001538C(GV_CacheID_800152DC(HASH_FONT, 'r'));

    if (dword_800ABB28)
    {
        // Load 'rubi.res' file:
        gRubiRes_800AB6B4 = (RubiRes *)GV_GetCache_8001538C(GV_CacheID_800152DC(HASH_RUBI, 'r'));

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

void font_free_80044BD8(void)
{
    return;
}

int font_init_kcb_80044BE0(KCB *kcb, RECT *rect_data, int x, int y)
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

// letter_spacing - space between letters
//                  lower values - letters close to each other
//                  h i g h e r  v a l u e s - letters farther apart
// top_padding - vertical space before a line
// maximum_width - if the text is longer than (roughly) maximum_width number of characters it will wrap
//                 -1 - no limit
int font_set_kcb_80044C90(KCB *kcb, int maximum_width, int arg2, int letter_spacing,
                                    int top_padding, int arg5, int arg6)
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
    if (letter_spacing >= 0)
    {
        kcb->char_arr[2] = letter_spacing;
    }
    if (top_padding >= 0)
    {
        kcb->char_arr[3] = top_padding;
    }

    quotient0 = (kcb->rect_data->w * 4) / (kcb->char_arr[2] + 12);

    quotient1 = kcb->rect_data->h / (kcb->char_arr[3] + 12);

    val0 = quotient0 + 1;
    if ((arg6 & 0x2) == 0)
    {
        val0 = quotient0;
    }

    if (maximum_width > 0 && val0 >= maximum_width)
    {
        kcb->char_arr[0] = maximum_width;
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

void font_set_color_80044DC4(KCB *kcb, int code, int fore, int back)
{
    int             fr, fg, fb;
    int             br, bg, bb;
    int             ir, ig, ib;
    unsigned short *pClut;
    int             i;

    if (code > 3)
    {
        return;
    }

    pClut = (unsigned short *)kcb->font_clut_buffer + code * 4;

    fr = fore & 0x1f;
    fg = (fore >> 5) & 0x1f;
    fb = (fore >> 10) & 0x1f;

    br = back & 0x1f;
    bg = (back >> 5) & 0x1f;
    bb = (back >> 10) & 0x1f;

    ir = (fr + br * 2) / 3;
    ig = (fg + bg * 2) / 3;
    ib = (fb + bb * 2) / 3;
    pClut[0] = back;
    pClut[1] = ir | (ig << 5) | (ib << 10);

    // Dead code that messes up the codegen :)
    ir = (fr * 5 + br * 3) / 8;
    ig = (fg * 5 + bg * 3) / 8;
    ib = (fb * 5 + bb * 3) / 8;

    ir = (fr * 2 + br) / 3;
    ig = (fg * 2 + bg) / 3;
    ib = (fb * 2 + bb) / 3;
    pClut[2] = ir | (ig << 5) | (ib << 10);
    pClut[3] = fore;

    for (i = 0; i < 4; i++)
    {
        if (pClut[i] != 0)
        {
            pClut[i] |= 0x8000;
        }
    }
}

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

int font_get_glyph_index_80044FF4(int code)
{
    int new_var2;
    int var_v0;
    int temp_v0;
    int temp_a0;

    // Clear flags from code
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
        temp_a0 = (code - 0x9A00) - (temp_v0 * 512);
        new_var2 = temp_v0 + 2;
        var_v0 = (temp_a0 - 1 - (temp_a0 / 256)) | (new_var2 * 4096);
    }

    return var_v0 + 1;
}

unsigned int font_get_glyph_config_800450F4(int a1)
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

void font_draw_glyph_80045124(char *buffer, int x, int y, int width, char *glyph)
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

    temp_v0 = font_palette_800AB6BC;
    temp_t3 = (temp_v0 << 6) | (temp_v0 << 2);

    if (dword_800AB6B8 != 0)
    {
        var_v1 = y - 4;

        if (rubi_display_flag_800AB6B0 == 0)
        {
            var_v1 = y - 2;
        }

        temp_v1 = buffer + ((x + 5) / 2);
        temp_a0 = temp_v1 + ((var_v1 - 1) * width);
        temp_a1 = temp_t3 | 0x33;
        *temp_a0 |= temp_a1;
        temp_v1_2 = temp_v1 + (var_v1 * width);
        *temp_v1_2 |= temp_a1;
    }

    var_a1 = glyph;
    buffer = buffer + (x / 2) + ((++y) * width);

    if (!(x & 1))
    {
        if (var_a1 == NULL)
        {
            for (i = 0; i < 12; i++)
            {
                *buffer++ = temp_t3;
                *buffer++ = temp_t3;
                *buffer++ = temp_t3;
                *buffer++ = temp_t3;
                *buffer++ = temp_t3;
                *buffer++ = temp_t3;
                buffer += width - 6;
            }

            return;
        }

        for (i = 0; i < 12; i++)
        {
            *buffer++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *buffer++ = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 16));
            var_a1++;

            *buffer++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *buffer++ = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 0x10));
            var_a1++;

            *buffer++ = temp_t3 | ((*var_a1 >> 6) | (*var_a1 & 0x30));
            *buffer = temp_t3 | (((*var_a1 & 0xC) >> 2) | ((*var_a1 & 3) * 0x10));
            var_a1++;

            buffer = (buffer + width) - 5;
        }

        return;
    }

    if (var_a1 == NULL)
    {
        for (i = 0; i < 12; i++)
        {
            *buffer++ = (*buffer & 0xF) | (temp_t3 & 0xF0);
            *buffer++ = temp_t3;
            *buffer++ = temp_t3;
            *buffer++ = temp_t3;
            *buffer++ = temp_t3;
            *buffer++ = temp_t3;
            *buffer = (*buffer & 0xF0) | (temp_t3 & 0xF);
            buffer += width - 6;
        }

        return;
    }

    var_t5 = 4;
    new_var2 = (font_palette_800AB6BC & 0xff) << 2;
    var_t4 = *var_a1;

    for (i = 0; i < 12; i++)
    {
        var_a2 = (1 - (x % 2)) * 4;
        var_t1 = buffer;
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

        buffer += width;
    }
}

// Observations about the font.res file used by the font library:
// Big Endian in memory, byte swapped at runtime in font_load().
// The file begins with an 8-byte 'header' that has two 32-bit words.
// Bytes 0-3 is the size of 'Table 1' which describes the ASCII glyphs. (96 entries for font.res)
// Bytes 4-7 is the offset for the font loaded to index 0. (offset 2306 for font.res)
//
// Following this there is a table of 32-bit words, the size is determined by bytes 0-3.
// The first table appears to have the following layout from reading the code.
//
// Table 1 entry:
// +----------------------+-------------+------------------------+
// | 31:28 Y-Offset (0-2) | 27:24 Width | 23:0 Index into table2 |
// +----------------------+-------------+------------------------+
// This table seems to only be used for the ASCII range.
//
// The glyphs used for the ASCII range are 12 pixels tall with a width specified by bits 27:24.
// Each pixel in memory is 2 bits. It is combined with a 2-bit color index in the font buffer.
// The pixel can then be drawn using a 16 entry LUT on the GPU side.
int font_draw_ascii_glyph_8004544C(char *buffer, int x, int y, int width, unsigned char code)
{
    char *location, *location2, *location3, *location4, *locationIter;
    char *font_location;

    unsigned int   glyph, glyph3;
    char           glyph2;
    int            glyph4, glyph5, glyph6;
    unsigned short glyph7, glyph8;

    int shift, shift2;
    int i, j, y2, counter, retval, loops;

    location = buffer + x / 2 + y * width;

    if (code > 0 && code < 0xFF)
    {
        glyph = font_get_glyph_config_800450F4(code);
        font_location = gFontEnd + (glyph & 0xFFFFFF);
        retval = (glyph >> 24) & 0xF;
        loops = 12;

        if (dword_800AB6B8)
        {
            shift = (retval + 1) / 2 - 1;

            if (rubi_display_flag_800AB6B0)
            {
                y2 = y - 4;
            }
            else
            {
                y2 = y - 2;
            }

            glyph2 = font_palette_800AB6BC;

            location3 = buffer + (x + shift) / 2;
            location2 = location3 + (y2 - 1) * width;

            glyph3 = (glyph2 << 2) | (glyph2 << 6);
            glyph3 |= 0x33;

            *location2 |= glyph3;

            location4 = location3 + y2 * width;

            *location4 |= glyph3;
        }

        counter = 4;

        glyph5 = *font_location++;

        location = location + width * (glyph >> 28);
        locationIter = location;

        glyph8 = (font_palette_800AB6BC & 0xFF) << 2;

        for (i = 0; i < loops; location += width, locationIter = location, i++)
        {
            shift2 = (1 - x % 2) * 4;

            for (j = 0; j < retval; j++)
            {
                glyph7 = (glyph5 & 0xFF) >> 6;

                if (--counter == 0)
                {
                    // Next 4 pixels are in next char.
                    glyph5 = *font_location++;
                    counter = 4;
                }
                else
                {
                    // Advance to next pixel
                    glyph5 <<= 2;
                }

                *locationIter |= ((glyph8 | glyph7) & 0xFF) << (4 - shift2);

                if (shift2 == 0)
                {
                    locationIter++;
                    shift2 = 4;
                }
                else
                {
                    shift2 = 0;
                }
            }
        }
    }
    else
    {
        if (code)
        {
            return 0;
        }

        y2 = 18;
        shift = x % 2;

        glyph6 = font_palette_800AB6BC & 0xFF;

        location = location + width * 5;

        glyph4 = glyph6 << 6 | (0x33 | glyph6 << 2);

        if (shift > 0)
        {
            y2 = shift + 16;
            *location++ |= (glyph4 & 0xFF) >> (shift * 4);
        }

        while (y2 >= 2)
        {
            y2 -= 2;
            *location++ |= glyph4;
        }

        if (y2 > 0)
        {
            shift = (2 - y2) * 4;
            *location |= (glyph4 & 0xFF) << (4 - shift);
        }

        retval = 18;
    }
    return retval;
}

unsigned int font_get_glyph_width_80045718(int a1)
{
    if (a1 == 0x8000)
    {
        return 0;
    }

    if (a1 < 0x8100)
    {
        if ((a1 != 0x8023) && ((a1 < 0x8010) || (a1 >= 0x8020)))
        {
            return (font_get_glyph_config_800450F4(a1 & 0xFF) >> 24) & 0xF;
        }
    }

    return 12;
}

void font_set_rubi_display_mode_80045788(int display_flag)
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

int font_draw_rubi_string_helper_800458B8(int *length, const char *str)
{
    RubiRes    *rubiRes;
    int         rubiCode;
    int         retval; // some sort of length corrected by rubi codes?
    int         i, idx;
    const char *strIter;

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
            printf("Wrong rubi code %x\n", rubiCode);
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
    *length = i;
    return retval;
}

int font_draw_rubi_string_helper2_800459B0(char *buffer, int x, int y, int width, int arg4)
{
    int          oddIter, var_a1, j, var_t3, i, var_v0_2, rubiField0, var_t0;
    unsigned int var_v0;
    RubiRes     *rubiRes;
    char        *buffer_iter1, *rubiRes_iter, *rubiResPtr, *buffer_iter2;

    i = 0;
    rubiRes = &gRubiRes_800AB6B4[arg4];
    rubiResPtr = &rubiRes->field_0;
    rubiField0 = *rubiResPtr;

    y++;
    buffer_iter1 = buffer + x / 2 + y * width;
    buffer_iter2 = buffer_iter1;
    rubiResPtr = rubiRes->field_1;

    for (; i < 6; buffer_iter1 += width, buffer_iter2 = buffer_iter1, i++)
    {
        rubiRes_iter = &rubiResPtr[i / 2 * 3];
        oddIter = i & 1;
        var_t3 = (1 - x % 2) * 4;

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

            *buffer_iter2 |= var_v0_2 << (4 - var_t3);
            if (var_t3 == 0)
            {
                buffer_iter2++;
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

void font_draw_rubi_string_80045AE4(char *buffer, int x, int y, int width, const char *arg4)
{
    int         iterCount;
    int         len;
    int         rubiCode, pos_y_2;
    int         pos_x;
    int         pos_x_2;
    int         x_offset;
    int         pos_y;
    int         rubiIndex;
    const char *str;
    str = arg4;
    if (buffer == 0)
    {
        return;
    }
    len = font_draw_rubi_string_helper_800458B8(&iterCount, str);
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
            printf("Wrong rubi code %x\n", rubiCode);
            rubiIndex = 0;
        }
        if (rubiIndex == 0)
        {
            pos_x_2 += 4 + x_offset;
        }
        else
        {
            pos_x_2 +=
                font_draw_rubi_string_helper2_800459B0(buffer, pos_x_2, pos_y - 6, width, rubiIndex - 1) + x_offset;
        }
    }
}

#define MAP_ASCII(c) (0x8000 | (unsigned char)(c))

#define MSB_NOT_SET(c) (((signed char)(c)) >= 0)
#define TWO_BYTE_CHAR(p) ((((unsigned char *)(p))[0] << 8) | ((unsigned char *)(p))[1])

// Returns to the 1-or-2-byte character at `p`.
#define PEEK_CHAR(p) (MSB_NOT_SET(*(p)) ? MAP_ASCII(*(p)) : TWO_BYTE_CHAR(p))

// Reads the next character at p, assigns it into `dest`, and advances p to the next char.
// NOTE: This macro is not properly guarded, so it can't be used anywhere a normal statement
//       could. However, guarding it with `do {...} while(0)` makes the optimizer produce
//       different code.
#define READ_CHAR(dest, p)                                                                                             \
    if (MSB_NOT_SET(*(p)))                                                                                             \
    {                                                                                                                  \
        dest = MAP_ASCII(*(p));                                                                                        \
        ++(p);                                                                                                         \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        (dest) = TWO_BYTE_CHAR((p));                                                                                   \
        (p) += 2;                                                                                                      \
    }

// Advances p to the next char, skipping the current one.
// NOTE: This macro is not properly guarded, so it can't be used anywhere a normal statement
//       could. However, guarding it with `do {...} while(0)` makes the optimizer produce
//       different code.
#define SKIP_CHAR(p)                                                                                                   \
    if (MSB_NOT_SET(*(p)))                                                                                             \
    {                                                                                                                  \
        ++(p);                                                                                                         \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        (p) += 2;                                                                                                      \
    }

long font_draw_string_80045D0C(KCB *kcb, long xtop, long ytop, const char *string, long color)
{
    void *font_buffer;
    int   x, y;

    const char *m2;

    int flag1, counter1;
    int xmax;
    int height_info, width_info;
    int retval;

    const char *m;

    int flag2;

    int var_a0;
    int current_code;

    int   counter2;
    int   current_char;
    int   coord;
    short character_mask = 0x9FFF;
    int   d;

    int idx1;
    int current_code2;
    int ascii_closing_bracket = MAP_ASCII('}');

    char *ptr;

    // Return if font.res hasn't been loaded
    if (!dword_800ABB28)
    {
        return 0;
    }

    counter1 = 0;
    dword_800AB6B8 = 0;
    xmax = kcb->short1;
    font_buffer = kcb->font_buffer;
    height_info = kcb->height_info;

    if (!(kcb->char_arr[6] & 2))
    {
        xmax -= 12;
    }

    x = xtop;
    m = string;

    retval = 0;
    flag1 = 0;
    font_palette_800AB6BC = color;
    kcb->short3 = kcb->char_arr[3] + 0xe;
    kcb->char_arr[6] = kcb->char_arr[6] & 0xEF;
    kcb->char_arr[7] = 0;
    flag2 = 0;
    width_info = kcb->width_info;
    y = ytop;

    while (*m)
    {
        // Fetch byte code and convert ASCII to an unused part of the SJIS map
        // 0x80xx is unused by SJIS
        current_char = PEEK_CHAR(m);

        // 0x8000 - 0x807F represents the standard ASCII range now
        // Character codes are either 8xxx or 9xxx from this point on.
        // This leaves two unused bits (0x2000 and 0x4000) that are used
        // as flags below. The logic below uses character_mask (0x9FFF)
        // in order to get the character code without flags.
        current_code = current_char & character_mask;

        // If character is an ASCII control code with no flags set,
        // consume it and move on to the next step.
        if (current_char < MAP_ASCII(' '))
        {
            READ_CHAR(current_char, m);
        }
        else if (current_code == MAP_ASCII('#'))
        {
            SKIP_CHAR(m); // skip '#'

            READ_CHAR(d, m); // consume "command" char
            d &= character_mask;

            switch (d)
            {
            case MAP_ASCII('1'):
                current_code = MAP_ASCII('@');
                goto block_136;

            case MAP_ASCII('N'):
                current_char = MAP_ASCII('\n');
                break;

            case MAP_ASCII('R'):
                m += 2;
                // fallthrough
            case MAP_ASCII('{'):
                r_flag_800AB6C0 = 1;

                if (rubi_display_flag_800AB6B0)
                {
                    rubi_flag_800AB6C4 = 1;
                    set_rubi_left_pos_80045794(xmax, x, y);

                    d = PEEK_CHAR(m);
                    d &= character_mask;

                    if (d == MAP_ASCII('!'))
                    {
                        m += 2;
                    }
                }
                else
                {
                    d = PEEK_CHAR(m);
                    d &= character_mask;

                    if (d == MAP_ASCII('!'))
                    {
                        while (1)
                        {
                            if (d == 0x9002)
                            {
                                break;
                            }

                            READ_CHAR(d, m);
                            d &= character_mask;

                            if (d == MAP_ASCII(','))
                            {
                                goto block_110;
                            }
                        }
                    }
                }
                break;

            case MAP_ASCII('-'):
            case 0x9006:
                counter2 = font_draw_ascii_glyph_8004544C(font_buffer, x, y, width_info, 0);
                goto block_155;

            case MAP_ASCII('S'):
                current_char = 0x8009;
                break;

            case MAP_ASCII('W'):
                if (kcb->char_arr[7] < x)
                {
                    kcb->char_arr[7] = x;
                }
                counter2 = 0;
                if (flag1)
                {
                    goto error;
                }
                goto block_155;

            case MAP_ASCII('T'):
                m += 2;
                if (kcb->char_arr[3] >= 3)
                {
                    dword_800AB6B8 = 1;
                }

                r_flag_800AB6C0 = 1;
                break;

            case MAP_ASCII('2'):
                current_code = MAP_ASCII('~'); // This represents the overline character in SJIS
                goto block_136;

            case 0x901D:
                current_code = (GM_GameStatusFlag & 7) == 2 ? 0x9024 : 0x901D;
                goto block_136;

            case 0x901E:
            case 0x9024:
                switch (GM_GameStatusFlag & 7)
                {
                case 0:
                    current_code = d;
                    break;
                case 1:
                    current_code = 0x9018;
                    break;
                case 2:
                    current_code = 0x901D;
                    break;
                }
                goto block_136;
            default:
                // go back 4 bytes, but if '#' was one byte then '#X' is at most
                // 3 bytes (if 'X' is 2-byte). Bug?
                m -= 4;
                break;
            }
        }
        else if (r_flag_800AB6C0 &&
                 (current_code == 0x9002 || current_code == 0x9004 || current_code == ascii_closing_bracket))
        {
            if (rubi_flag_800AB6C4 == 1 && (current_code == 0x9002 || current_code == 0x9004))
            {
                font_draw_rubi_string_80045AE4(font_buffer, x, y, width_info, m + 2);
            }

            rubi_flag_800AB6C4 = 0;

            do
            {
                READ_CHAR(current_code, m);
                current_code &= character_mask;
            } while (current_code != ascii_closing_bracket);

            current_code = PEEK_CHAR(m);
            if (current_code == MAP_ASCII('#'))
            {
                SKIP_CHAR(m);
            }

            dword_800AB6B8 = 0;
            r_flag_800AB6C0 = 0;
            counter2 = 0;
            goto block_155;
        }
        else if (current_code == MAP_ASCII('|'))
        {
            SKIP_CHAR(m);
            current_char = MAP_ASCII('\n');
        }

    block_110:
        // is it an ASCII control character?
        if (current_char < MAP_ASCII(' '))
        {
            switch (current_char)
            {
            case MAP_ASCII('\n'):
                if (!flag2)
                {
                    if (kcb->char_arr[7] < x)
                    {
                        kcb->char_arr[7] = x;
                    }
                    x = xtop;
                    coord = kcb->char_arr[3] + 12;
                    y += coord;
                    coord = y + 14;
                    counter1 += 1;
                    kcb->short3 = y + 14;
                    if (height_info <= y + 11)
                    {
                        goto error;
                    }

                    if (kcb->char_arr[6] & 1)
                    {
                        goto error;
                    }
                    if (counter1 >= kcb->char_arr[1])
                    {
                        goto error;
                    }
                    break;
                }
                flag2 = 0;
                break;

            case MAP_ASCII('\t'):
                coord = kcb->char_arr[2] + 12;
                var_a0 = coord * kcb->char_arr[4];
                if (var_a0 > 0)
                {
                    x = (x / var_a0 + 1) * var_a0;
                }
                break;

            case MAP_ASCII('\f'):
                READ_CHAR(current_char, m);
                font_palette_800AB6BC = current_char - MAP_ASCII('0');
                break;
            }
            continue;
        }

        m2 = m;
        READ_CHAR(current_char, m);
        current_code = current_char & character_mask;

    block_136:
        // is it an ASCII character?
        if (current_code <= MAP_ASCII(0xFF))
        {
            counter2 = font_draw_ascii_glyph_8004544C(font_buffer, x, y, width_info, current_code & 0xFF);
            counter2 += kcb->char_arr[2];
            if (current_code == MAP_ASCII('!') || current_code == MAP_ASCII('?'))
            {
                current_code = PEEK_CHAR(m);
                current_code = current_code & character_mask;
                if (current_code != MAP_ASCII('!') && current_code != MAP_ASCII('?'))
                {
                    if (current_code != MAP_ASCII('(') && current_code != MAP_ASCII(')') &&
                        (current_code < 0x9009 || current_code > 0x900E) && current_code != 0x9015)
                    {
                        counter2 += 8;
                    }
                    else
                    {
                        counter2 += 2;
                    }
                }
            }
        }
        else
        {
            idx1 = font_get_glyph_index_80044FF4(current_code);
            if (idx1 > 0)
            {
                ptr = dword_8009E75C[idx1 >> 12] + ((idx1 & 0xFFF) - 1) * 36;
            }
            else
            {
                ptr = 0;
            }
            font_draw_glyph_80045124(font_buffer, x, y, width_info, ptr);
            coord = kcb->char_arr[2];
            counter2 = coord + 0xC;
        }

        flag1 = 1;

    block_155:
        current_code = PEEK_CHAR(m);
        current_code2 = current_code & character_mask;

        var_a0 = font_get_glyph_width_80045718(current_code2);
        coord = x + counter2;
        if (var_a0 > 0)
        {
            coord += var_a0;
            d = kcb->char_arr[2];
            coord += d;
            coord -= 1;
            if (coord >= xmax)
            {
                if (!(kcb->char_arr[6] & 2))
                {
                    if (current_char & 0x2000)
                    {
                        font_draw_glyph_80045124(font_buffer, x, y, width_info, 0);
                        m = m2;
                        counter2 = 0;
                    }
                    else if (current_code & 0x4000)
                    {
                        current_char = current_code2;
                        if (!r_flag_800AB6C0 ||
                            (current_char != 0x9002 && current_char != 0x9004 && current_char != ascii_closing_bracket))
                        {
                            d = PEEK_CHAR(m + 2);
                            if (current_char == 0x9003 || !(d & 0x4000) || (d & character_mask) == 0x8123)
                            {
                                READ_CHAR(current_char, m);
                                current_code = current_char & character_mask;

                                if (current_code <= 0x80FF)
                                {
                                    counter2 += font_draw_ascii_glyph_8004544C(font_buffer, x + counter2, y,
                                                                               width_info, current_code & 0xFF);
                                }
                                else
                                {
                                    idx1 = font_get_glyph_index_80044FF4(current_code);
                                    if (idx1 > 0)
                                    {
                                        ptr = dword_8009E75C[idx1 >> 12] + ((idx1 & 0xFFF) - 1) * 36;
                                    }
                                    else
                                    {
                                        ptr = 0;
                                    }
                                    font_draw_glyph_80045124(font_buffer, x + counter2, y, width_info, ptr);
                                    counter2 += 12;
                                }
                            }
                        }
                        else
                        {
                            goto block_194;
                        }
                    }
                }
                if (rubi_flag_800AB6C4)
                {
                    set_rubi_left_xmax_800457A8(x + counter2);
                }
                retval = 1;
                flag2 = 1;

                if (x + counter2 > kcb->char_arr[7])
                {
                    kcb->char_arr[7] = x + counter2;
                }

                x = xtop;

                coord = kcb->char_arr[3] + 12;
                y += coord;

                counter1 += 1;
                kcb->short3 = y + 14;

                if (kcb->char_arr[6] & 1 || y + 11 >= height_info || counter1 >= kcb->char_arr[1])
                {
                    if (rubi_flag_800AB6C4)
                    {
                        rubi_flag_800AB6C4 = 2;
                    }

                    if (*m)
                    {
                        goto error;
                    }

                    return 0;
                }

                goto block_195;
            }
        }

    block_194:
        x += counter2;
        flag2 = 0;

    block_195:
        if (x > kcb->char_arr[7])
        {
            kcb->char_arr[7] = x;
        }
    }
    return retval;

error:
    if (kcb->char_arr[7] < x)
    {
        kcb->char_arr[7] = x;
    }

    // return the position where the error happened, with MSB set to signal error.
    return 0x80000000 | (m - string);
}

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
    LoadImage(&kcb->font_rect, kcb->font_buffer);
}

void font_clut_update_80046980(KCB *kcb)
{
    LoadImage(&kcb->font_clut_rect, kcb->font_clut_buffer);
}

void font_print_string_800469A4(KCB *kcb, const char *string)
{
    font_clear_800468FC(kcb);
    font_draw_string_80045D0C(kcb, 0, kcb->char_arr[3], string, kcb->char_arr[5]);
}
