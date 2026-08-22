#ifndef __MGS_FMT_TEX_H__
#define __MGS_FMT_TEX_H__
// clang-format off

#include <sys/types.h>

#define PCX_RLE_CODE ( 0x3 << 6 )

typedef struct PCXINFO {
    unsigned short  stamp;      /* always 12345 */
    unsigned short  flag;
    unsigned short  px, py;     /* pixel X/Y coords */
    unsigned short  cx, cy;     /* CLUT  X/Y coords */
    unsigned short  n_colors;
} PCXINFO;

typedef struct PCXDATA {
    unsigned char   manufacturer;
    unsigned char   version;
    unsigned char   encoding;
    unsigned char   bits_per_pixel;
    unsigned short  min_x, min_y;
    unsigned short  max_x, max_y;
    unsigned short  dpi_x, dpi_y;
    unsigned char   header_palette[ 48 ];
    unsigned char   reserved;
    unsigned char   n_planes;
    unsigned short  bytes_per_line;
    unsigned short  header_palette_class;
    unsigned short  screen_width, screen_height;
    PCXINFO         info;
    unsigned char   pad[ 54 - sizeof(PCXINFO) ];
    unsigned char   data[ 0 ];  /* image data */
} PCXDATA;

// NOTE: PCXDATA originally had a zero-length PCXINFO array clobbering
// the PCX header's padding section. Zero-length arrays (especially in
// the middle of structs) are a non-standard GCC extension.
//
//    PCXINFO         info[ 0 ] ;
//    unsigned char   pad[ 54 ] ;
//} PCXDATA;
//
// There's only ever one PCXINFO, so we changed this to a single member
// and the padding field was shrunk by the sizeof(PCXINFO).

typedef struct {
    u_char mode;
    u_char bit;
    u_short color;
    u_short width;
    u_short height;
    u_short flag;
    u_short px, py;
    u_short cx, cy;
    u_short n_data;
} PLL_HEADER;

// clang-format on
#endif // __MGS_FMT_TEX_H__
