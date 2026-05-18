#include "font.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "linkvar.h"

// This struct describes the structure of
// "rubi.res" file.
//
// Note that 'r' (0x72) can be either a ".rar",
// ".res" or ".rpk" file. It looks like different
// ".res" files could have different data structure,
// for example "rubi.res" file has a different structure
// and it is not the same as ResHeader in menu/.
//
typedef struct RubiRes
{
    char field_0;
    char field_1[9];
} RubiRes;

STATIC char    *gFontBegin = NULL;
STATIC char    *gFontEnd = NULL;
STATIC int      rubi_display_flag = TRUE;
STATIC RubiRes *gRubiRes_800AB6B4 = NULL;
STATIC int      dword_800AB6B8 = 0;
STATIC int      font_color = 0;
STATIC int      r_flag = 0;
STATIC int      rubi_flag = 0;

// Menu-related?

char *SECTION(".sbss") dword_800ABB28;
int   SECTION(".sbss") rubi_left_x;
int   SECTION(".sbss") rubi_left_y;
int   SECTION(".sbss") rubi_orikaeshi_xmax;

char *zendata[] = {NULL, NULL, NULL, NULL};

#define HASH_font   0xCA68  // GV_StrCode("font")
#define HASH_rubi   0xE0E3  // GV_StrCode("rubi")

#define PEEK_CHAR( code, m )                     \
    if ( *( m ) < 0x80 )                         \
    {                                            \
        ( code ) = 0x8000 | *( m );              \
    }                                            \
    else                                         \
    {                                            \
        ( code ) = ( *( m ) << 8 ) | *( m + 1 ); \
    }

#define GETNEXTCHAR( code, m )                   \
    if ( *( m ) < 0x80 )                         \
    {                                            \
        ( code ) = 0x8000 | *( m );              \
        ( m )++;                                 \
    }                                            \
    else                                         \
    {                                            \
        ( code ) = ( *( m ) << 8 ) | *( m + 1 ); \
        ( m ) += 2;                              \
    }


#define SKIPNEXTCHAR( m ) \
    if ( *( m ) < 0x80 )  \
    {                     \
        ( m )++;          \
    }                     \
    else                  \
    {                     \
        ( m ) += 2;       \
    }

#define GETCODE( code ) ( ( code ) & ~( TOP_KINSOKU_MASK | BACK_KINSOKU_MASK ) )

void font_load(void)
{
    char *temp_a1;
    char *ptr;

    // Load 'font.res' file:
    dword_800ABB28 = GV_GetCache(GV_CacheID(HASH_font, 'r'));

    if (dword_800ABB28)
    {
        // Load 'rubi.res' file:
        gRubiRes_800AB6B4 = (RubiRes *)GV_GetCache(GV_CacheID(HASH_rubi, 'r'));

        temp_a1 = dword_800ABB28;
        LSTORE((temp_a1[0] << 24) | (temp_a1[1] << 16) | (temp_a1[2] << 8) | temp_a1[3], temp_a1);

        temp_a1 = dword_800ABB28;
        LSTORE((temp_a1[4] << 24) | (temp_a1[5] << 16) | (temp_a1[6] << 8) | temp_a1[7], temp_a1 + 4);

        gFontBegin = temp_a1 + 8;
        gFontEnd = temp_a1 + LLOAD(temp_a1 + 0);
        zendata[0] = temp_a1 + LLOAD(temp_a1 + 4);

        for (ptr = temp_a1 + 8; ptr < gFontEnd; ptr += 4)
        {
            LSTORE((ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3], ptr);
        }
    }
}

void font_set_font_addr(int type, void *addr)
{
    zendata[type] = addr;
}

void font_free(void)
{
    return;
}

int font_init_kcb(KCB *kcb, RECT *rect, int x, int y)
{
    memset(kcb, 0, 44);
    kcb->rect_ptr = rect;
    kcb->rect = *rect;
    kcb->crect.w = 16;
    kcb->crect.h = 1;
    kcb->crect.x = x;
    kcb->crect.y = y;
    return font_set_kcb(kcb, -1, -1, 0, 0, 4, 0);
}

// c_skip - space between letters
//                  lower values - letters close to each other
//                  h i g h e r  v a l u e s - letters farther apart
// l_skip - vertical space before a line
// width - if the text is longer than (roughly) width number of characters it will wrap
//                 -1 - no limit
int font_set_kcb(KCB *kcb, int width, int height, int c_skip, int l_skip, int t_skip, int flag)
{
    int w, h;
    int w2;

    if (flag >= 0)
    {
        kcb->flag = flag;
    }

    if (t_skip >= 0)
    {
        kcb->t_skip = t_skip;
    }

    if (c_skip >= 0)
    {
        kcb->c_skip = c_skip;
    }

    if (l_skip >= 0)
    {
        kcb->l_skip = l_skip;
    }

    w = (kcb->rect_ptr->w * 4) / (kcb->c_skip + 12);
    h = kcb->rect_ptr->h / (kcb->l_skip + 12);

    w2 = w + 1;
    if ( !( flag & FONT_NO_KINSOKU ) )
    {
        w2 = w;
    }

    if (width > 0 && width <= w2)
    {
        kcb->c_width = width;
    }
    else if (kcb->c_width == 0 || w2 < kcb->c_width)
    {
        kcb->c_width = w2;
    }

    if (height > 0 && height <= h)
    {
        kcb->c_height = height;
    }
    else if (kcb->c_height == 0 || h < kcb->c_height)
    {
        kcb->c_height = h;
    }

    return 0;
}

void font_set_color(KCB *kcb, int code, int fore, int back)
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

    pClut = (unsigned short *)kcb->cbuffer + code * 4;

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

int font_get_buffer_size(KCB *kcb)
{
    short w = (kcb->c_skip + 12) * kcb->c_width - kcb->c_skip;
    int   val_2 = (int)w + 7;
    kcb->width = w;
    if (val_2 < 0)
    {
        val_2 = kcb->width + 14;
    }

    kcb->row = ((val_2 >> 3) << 2);
    kcb->height = (kcb->l_skip + 12) * kcb->c_height + 2;
    kcb->rect.w = kcb->row / 2;
    kcb->rect.h = kcb->height;

    return kcb->row * kcb->height + 32;
}

void font_set_buffer(KCB *kcb, void *buffer)
{
    kcb->cbuffer = buffer;
    kcb->buffer = buffer + 0x20;
}

void *font_get_buffer_ptr(KCB *kcb)
{
    return kcb->cbuffer;
}

static int get_zen_font_data(int code)
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

static unsigned int get_hantable(int a1)
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

static void put_zenkaku_4bpp(char *buffer, int x, int y, int width, char *glyph)
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

    temp_v0 = font_color;
    temp_t3 = (temp_v0 << 6) | (temp_v0 << 2);

    if (dword_800AB6B8 != 0)
    {
        var_v1 = y - 4;

        if (rubi_display_flag == FALSE)
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
    new_var2 = (font_color & 0xff) << 2;
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
static int put_hankaku_4bpp(char *buffer, int x, int y, int width, unsigned char code)
{
    char *location, *location2, *location3, *location4, *locationIter;
    char *font_location;

    unsigned int   glyph, glyph3;
    char           glyph2;
    int            glyph4, glyph5, glyph6;
    unsigned short glyph7, glyph8;

    int shift, shift2;
    int i, j, y2, counter, result, loops;

    location = buffer + x / 2 + y * width;

    if (code > 0 && code < 0xFF)
    {
        glyph = get_hantable(code);
        font_location = gFontEnd + (glyph & 0xFFFFFF);
        result = (glyph >> 24) & 0xF;
        loops = 12;

        if (dword_800AB6B8)
        {
            shift = (result + 1) / 2 - 1;

            if (rubi_display_flag)
            {
                y2 = y - 4;
            }
            else
            {
                y2 = y - 2;
            }

            glyph2 = font_color;

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

        glyph8 = (font_color & 0xFF) << 2;

        for (i = 0; i < loops; location += width, locationIter = location, i++)
        {
            shift2 = (1 - x % 2) * 4;

            for (j = 0; j < result; j++)
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

        glyph6 = font_color & 0xFF;

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

        result = 18;
    }
    return result;
}

static unsigned int font_get_glyph_width(int a1)
{
    if (a1 == 0x8000)
    {
        return 0;
    }

    if ( IS_HANKAKU( a1 ) )
    {
        if ((a1 != 0x8023) && ((a1 < 0x8010) || (a1 >= 0x8020)))
        {
            return (get_hantable(a1 & 0xFF) >> 24) & 0xF;
        }
    }

    return 12;
}

void font_set_rubi_display_mode(int flag)
{
    rubi_display_flag = flag;
}

static void set_rubi_left_pos(int xmax, int x, int y)
{
    rubi_left_x = x;
    rubi_left_y = y;
    rubi_orikaeshi_xmax = xmax;
}

static void set_rubi_orikaeshi(int xmax)
{
    rubi_orikaeshi_xmax = xmax;
}

#define ASCII_TO_RUBI(c) (c + 0x8000)

static int get_rubi_char_index(int c)
{
    if ( IS_HANKAKU( c ) )
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

static int get_rubi_width( int *count, const char *string )
{
    RubiRes    *res;
    const char *m;
    int         n, w;

    res = gRubiRes_800AB6B4;

    w = 0;
    n = 0;
    m = string;

    for ( ;; )
    {
        int code, rubi;

        GETNEXTCHAR( code, m );
        code = GETCODE( code );

        if ( code == CODE( '}' ) )
        {
            break;
        }

        rubi = get_rubi_char_index( code );
        if ( rubi < 0 )
        {
            printf("Wrong rubi code %x\n", code);
            rubi = 0;
        }

        if ( rubi == 0 )
        {
            w += 4;
        }
        else
        {
            w += res[rubi - 1].field_0;
        }

        n++;
    }

    *count = n;
    return w;
}

static int put_rubi(char *buffer, int x, int y, int width, int arg4)
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

static void draw_rubi_string(char *buffer, int x, int y, int width, const char *arg4)
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
    len = get_rubi_width(&iterCount, str);
    pos_y_2 = y;

    if (rubi_left_y < pos_y_2)
    {
        pos_x = rubi_orikaeshi_xmax - rubi_left_x;
        pos_y = rubi_left_y;
        if (x / 2 >= pos_x)
        {
            do
            {
                pos_y = y;
            } while (0);
            pos_x = x;
            rubi_left_x = 0;
        }
    }
    else
    {
        pos_y = pos_y_2;
        pos_x = x - rubi_left_x;
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
    pos_x = rubi_left_x + (pos_x - len) / 2;
    if (rubi_orikaeshi_xmax < pos_x + len)
    {
        pos_x = rubi_orikaeshi_xmax - len;
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
        rubiIndex = get_rubi_char_index(rubiCode);
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
            pos_x_2 += put_rubi(buffer, pos_x_2, pos_y - 6, width, rubiIndex - 1) + x_offset;
        }
    }
}

long font_draw_string(KCB *kcb, long xtop, long ytop, const char *string, long color)
{
    void *font_buffer;
    int   x, y;

    const char *m2;

    int flag1, counter1;
    int buf_width;
    int height, width_info;
    int result;

    const char *m;

    int cr_flag;

    int next_width;
    int next_mdata;

    int   dx;
    int   mdata;
    int   coord;
    short character_mask = 0x9FFF;
    int   d;

    int idx1;
    int next_code;
    int ascii_closing_bracket = CODE('}');

    char *ptr;

    // Return if font.res hasn't been loaded
    if (!dword_800ABB28)
    {
        return 0;
    }

    counter1 = 0;
    dword_800AB6B8 = 0;
    buf_width = kcb->width;
    font_buffer = kcb->buffer;
    height = kcb->height;

    if (!(kcb->flag & FONT_NO_KINSOKU))
    {
        buf_width -= 12;
    }

    x = xtop;
    m = string;

    result = 0;
    flag1 = 0;
    font_color = color;
    kcb->max_height = kcb->l_skip + 14;
    kcb->flag &= ~FONT_CLEAN;
    kcb->max_width = 0;
    cr_flag = 0;
    width_info = kcb->row;
    y = ytop;

    while (*m)
    {
        // Fetch byte code and convert ASCII to an unused part of the SJIS map
        // 0x80xx is unused by SJIS
        PEEK_CHAR(mdata, m);

        // 0x8000 - 0x807F represents the standard ASCII range now
        // Character codes are either 8xxx or 9xxx from this point on.
        // This leaves two unused bits (0x2000 and 0x4000) that are used
        // as flags below. The logic below uses character_mask (0x9FFF)
        // in order to get the character code without flags.
        next_mdata = mdata & character_mask;

        // If character is an ASCII control code with no flags set,
        // consume it and move on to the next step.
        if (mdata < CODE(' '))
        {
            GETNEXTCHAR(mdata, m);
        }
        else if (next_mdata == CODE('#'))
        {
            SKIPNEXTCHAR(m); // skip '#'

            GETNEXTCHAR(d, m); // consume "command" char
            d &= character_mask;

            switch (d)
            {
            case CODE('1'):
                next_mdata = CODE('@');
                goto block_136;

            case CODE('N'):
                mdata = CODE('\n');
                break;

            case CODE('R'):
                m += 2;
                // fallthrough
            case CODE('{'):
                r_flag = 1;

                if (rubi_display_flag)
                {
                    rubi_flag = 1;
                    set_rubi_left_pos(buf_width, x, y);

                    PEEK_CHAR(d, m);
                    d &= character_mask;

                    if (d == CODE('!'))
                    {
                        m += 2;
                    }
                }
                else
                {
                    PEEK_CHAR(d, m);
                    d &= character_mask;

                    if (d == CODE('!'))
                    {
                        while (1)
                        {
                            if (d == 0x9002)
                            {
                                break;
                            }

                            GETNEXTCHAR(d, m);
                            d &= character_mask;

                            if (d == CODE(','))
                            {
                                goto block_110;
                            }
                        }
                    }
                }
                break;

            case CODE('-'):
            case 0x9006:
                dx = put_hankaku_4bpp(font_buffer, x, y, width_info, 0);
                goto block_155;

            case CODE('S'):
                mdata = 0x8009;
                break;

            case CODE('W'):
                if (kcb->max_width < x)
                {
                    kcb->max_width = x;
                }
                dx = 0;
                if (flag1)
                {
                    goto OVER;
                }
                goto block_155;

            case CODE('T'):
                m += 2;
                if (kcb->l_skip >= 3)
                {
                    dword_800AB6B8 = 1;
                }

                r_flag = 1;
                break;

            case CODE('2'):
                next_mdata = CODE('~'); // This represents the overline character in SJIS
                goto block_136;

            case 0x901D:
                next_mdata = (GM_OptionFlag & OPTION_BUTTON_MASK) == OPTION_BUTTON_TYPE_C ? 0x9024 : 0x901D;
                goto block_136;

            case 0x901E:
            case 0x9024:
                switch (GM_OptionFlag & OPTION_BUTTON_MASK)
                {
                case OPTION_BUTTON_TYPE_A:
                    next_mdata = d;
                    break;
                case OPTION_BUTTON_TYPE_B:
                    next_mdata = 0x9018;
                    break;
                case OPTION_BUTTON_TYPE_C:
                    next_mdata = 0x901D;
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
        else if (r_flag &&
                 (next_mdata == 0x9002 || next_mdata == 0x9004 || next_mdata == ascii_closing_bracket))
        {
            if (rubi_flag == 1 && (next_mdata == 0x9002 || next_mdata == 0x9004))
            {
                draw_rubi_string(font_buffer, x, y, width_info, m + 2);
            }

            rubi_flag = 0;

            do
            {
                GETNEXTCHAR(next_mdata, m);
                next_mdata &= character_mask;
            } while (next_mdata != ascii_closing_bracket);

            PEEK_CHAR(next_mdata, m);
            if (next_mdata == CODE('#'))
            {
                SKIPNEXTCHAR(m);
            }

            dword_800AB6B8 = 0;
            r_flag = 0;
            dx = 0;
            goto block_155;
        }
        else if (next_mdata == CODE('|'))
        {
            SKIPNEXTCHAR(m);
            mdata = CODE('\n');
        }

    block_110:
        // is it an ASCII control character?
        if (mdata < CODE(' '))
        {
            switch (mdata)
            {
            case CODE('\n'):
                if (cr_flag == FALSE)
                {
                    /* goto DO_CR; */
                    if (kcb->max_width < x)
                    {
                        kcb->max_width = x;
                    }
                    x = xtop;
                    coord = kcb->l_skip + 12;
                    y += coord;
                    coord = y + 14;
                    counter1 += 1;
                    kcb->max_height = y + 14;
                    if (height <= y + 11)
                    {
                        goto OVER;
                    }

                    if (kcb->flag & FONT_NO_ORIKAESHI)
                    {
                        goto OVER;
                    }
                    if (counter1 >= kcb->c_height)
                    {
                        goto OVER;
                    }
                    break;
                }
                cr_flag = 0;
                break;

            case CODE('\t'):
                coord = kcb->c_skip + 12;
                next_width = coord * kcb->t_skip;
                if (next_width > 0)
                {
                    x = (x / next_width + 1) * next_width;
                }
                break;

            case CODE('\f'):
                GETNEXTCHAR(mdata, m);
                font_color = mdata - CODE('0');
                break;
            }
            continue;
        }

        m2 = m;
        GETNEXTCHAR(mdata, m);
        next_mdata = mdata & character_mask;

    block_136:
        // is it an ASCII character?
        if (next_mdata <= CODE(0xFF))
        {
            dx = put_hankaku_4bpp(font_buffer, x, y, width_info, next_mdata & 0xFF);
            dx += kcb->c_skip;
            if (next_mdata == CODE('!') || next_mdata == CODE('?'))
            {
                PEEK_CHAR(next_mdata, m);
                next_mdata = next_mdata & character_mask;
                if (next_mdata != CODE('!') && next_mdata != CODE('?'))
                {
                    if (next_mdata != CODE('(') && next_mdata != CODE(')') &&
                        (next_mdata < 0x9009 || next_mdata > 0x900E) && next_mdata != 0x9015)
                    {
                        dx += 8;
                    }
                    else
                    {
                        dx += 2;
                    }
                }
            }
        }
        else
        {
            idx1 = get_zen_font_data(next_mdata);
            if (idx1 > 0)
            {
                ptr = zendata[idx1 >> 12] + ((idx1 & 0xFFF) - 1) * 36;
            }
            else
            {
                ptr = 0;
            }
            put_zenkaku_4bpp(font_buffer, x, y, width_info, ptr);
            coord = kcb->c_skip;
            dx = coord + 0xC;
        }

        flag1 = 1;

    block_155:
        PEEK_CHAR(next_mdata, m);
        next_code = next_mdata & character_mask;

        next_width = font_get_glyph_width(next_code);
        if ( next_width > 0
             && ( x + dx + next_width + kcb->c_skip - 1 ) >= buf_width )
        {
            if (!(kcb->flag & FONT_NO_KINSOKU))
            {
                if (mdata & BACK_KINSOKU_MASK)
                {
                    put_zenkaku_4bpp(font_buffer, x, y, width_info, 0);
                    m = m2;
                    dx = 0;
                }
                else if (next_mdata & TOP_KINSOKU_MASK)
                {
                    mdata = next_code;
                    if (r_flag && (mdata == 0x9002 || mdata == 0x9004 || mdata == ascii_closing_bracket))
                    {
                        goto NO_KINSOKU;
                    }
                    else
                    {
                        PEEK_CHAR(d, m + 2);
                        if (mdata == 0x9003 || !(d & TOP_KINSOKU_MASK) || (d & character_mask) == 0x8123)
                        {
                            GETNEXTCHAR(mdata, m);
                            next_mdata = mdata & character_mask;

                            if ( IS_HANKAKU( next_mdata ) )
                            {
                                dx += put_hankaku_4bpp(font_buffer, x + dx, y, width_info, next_mdata & 0xFF);
                            }
                            else
                            {
                                idx1 = get_zen_font_data(next_mdata);
                                if (idx1 > 0)
                                {
                                    ptr = zendata[idx1 >> 12] + ((idx1 & 0xFFF) - 1) * 36;
                                }
                                else
                                {
                                    ptr = 0;
                                }

                                put_zenkaku_4bpp(font_buffer, x + dx, y, width_info, ptr);
                                dx += 12;
                            }
                        }
                    }
                }
            }

            if (rubi_flag)
            {
                set_rubi_orikaeshi(x + dx);
            }

            result = 1;
            cr_flag = 1;

            if (x + dx > kcb->max_width)
            {
                kcb->max_width = x + dx;
            }

            x = xtop;

            coord = kcb->l_skip + 12;
            y += coord;

            counter1 += 1;
            kcb->max_height = y + 14;

            if (kcb->flag & FONT_NO_ORIKAESHI || y + 12 - 1 >= height || counter1 >= kcb->c_height)
            {
                if (rubi_flag)
                {
                    rubi_flag = 2;
                }

                if (*m)
                {
                    goto OVER;
                }

                return 0;
            }
        }
        else
        {
NO_KINSOKU:
            x += dx;
            cr_flag = 0;
        }

        if ( kcb->max_width < x )
        {
            kcb->max_width = x;
        }
    }

    return result;

OVER:
    if (kcb->max_width < x)
    {
        kcb->max_width = x;
    }

    // return the position where the error happened, with MSB set to signal error.
    return 0x80000000 | (m - string);
}

void font_clear(KCB *kcb)
{
    int *font_buffer;
    int  i;

    if (!(kcb->flag & FONT_CLEAN))
    {
        font_buffer = kcb->buffer;
        i = (unsigned int)(kcb->row * kcb->height) / 4;
        for (; i > 0; i--)
        {
            *font_buffer++ = 0;
        }
        kcb->flag |= FONT_CLEAN;
    }
}

void font_update(KCB *kcb)
{
    LoadImage(&kcb->rect, kcb->buffer);
}

void font_clut_update(KCB *kcb)
{
    LoadImage(&kcb->crect, kcb->cbuffer);
}

void font_print_string(KCB *kcb, const char *string)
{
    font_clear(kcb);
    font_draw_string(kcb, 0, kcb->l_skip, string, kcb->color);
}
