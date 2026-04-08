#ifndef __MGS_COMMON_H__
#define __MGS_COMMON_H__

#include <stddef.h>     // for NULL
#include <sys/types.h>
#include "psxdefs.h"

/* omitted from the PSX Runtime Library's stddef.h */
#ifndef offsetof
#define offsetof(type, member)  ((size_t)&(((type *)0)->member))
#endif

/* MSVC defines _countof as an extension to stdlib.h */
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif
/* alternate names without the leading underscore */
#define countof(array)  _countof(array)
#define COUNTOF(array)  _countof(array)

/*---------------------------------------------------------------------------*/

#ifndef MIN
#define MIN(x, y)       (((x) < (y)) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y)       (((x) > (y)) ? (x) : (y))
#endif
#ifndef ABS
#define ABS(x)          (((x) >= 0) ? (x) : -(x))
#endif

#ifndef CLAMP
#define CLAMP(x, min, max) (MAX(MIN(x, max), min))
#endif

#ifndef SWAP
#define SWAP(a, b)                                              \
    do {                                                        \
        __typeof__(a) _temp = (a);                              \
        (a) = (b); (b) = _temp;                                 \
    } while (0)
#endif

/*---------------------------------------------------------------------------*/
// NOTE: (bool)0.5 evaluates to true, whereas (int)0.5 evaluates to 0.

typedef int             BOOL;

#ifndef FALSE
#define FALSE           (0)
#endif
#ifndef TRUE
#define TRUE            (!FALSE)
#endif

/*---------------------------------------------------------------------------*/

// NOTE: Within the PSX primitive structures, RGB color values are followed
// by either a GPU primitive code or padding. We'll still consider the fourth
// byte to be the "alpha" channel here.
//
// The GPU primitives store the RGB values in big-endian order (see P_TAG/P_CODE
// in libgpu.h), but MGS handles the values by reading/writing the whole row as
// a single 32-bit word, therefore R becomes the LSB, etc.

/* RGBA8888 format */
#ifdef WORDS_BIGENDIAN
#define RGBA_R_SHIFT    (24)
#define RGBA_G_SHIFT    (16)
#define RGBA_B_SHIFT    ( 8)
#define RGBA_A_SHIFT    ( 0)
#else
#define RGBA_R_SHIFT    ( 0)
#define RGBA_G_SHIFT    ( 8)
#define RGBA_B_SHIFT    (16)
#define RGBA_A_SHIFT    (24)
#endif

#define RGBA_R_MASK     (0xff << RGBA_R_SHIFT)
#define RGBA_G_MASK     (0xff << RGBA_G_SHIFT)
#define RGBA_B_MASK     (0xff << RGBA_B_SHIFT)
#define RGBA_A_MASK     (0xff << RGBA_A_SHIFT)

//#define MAKE_RGB_WITHOUT_BITMASK
#ifdef MAKE_RGB_WITHOUT_BITMASK
#define MAKE_RGBA(_r,_g,_b,_a)                                  \
        ((unsigned int)(((_r) << RGBA_R_SHIFT) |                \
                        ((_g) << RGBA_G_SHIFT) |                \
                        ((_b) << RGBA_B_SHIFT) |                \
                        ((_a) << RGBA_A_SHIFT)))
#else
#define MAKE_RGBA(_r,_g,_b,_a)                                  \
        ((unsigned int)((((_r) & 0xff) << RGBA_R_SHIFT) |       \
                        (((_g) & 0xff) << RGBA_G_SHIFT) |       \
                        (((_b) & 0xff) << RGBA_B_SHIFT) |       \
                        (((_a) & 0xff) << RGBA_A_SHIFT)))
#endif

#define MAKE_RGB0(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0x00)
#define MAKE_RGBX(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0xff) /* full-alpha */
#define MAKE_RGBH(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0x80) /* half-alpha */

#define GET_R_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_R_SHIFT) & 0xff)
#define GET_G_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_G_SHIFT) & 0xff)
#define GET_B_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_B_SHIFT) & 0xff)
#define GET_A_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_A_SHIFT) & 0xff)

/* simple version without bitmasks or zero-shift */
#ifdef WORDS_BIGENDIAN
#define MAKE_RGB(_r, _g, _b)                                    \
        ((unsigned int)(((_r) << 24) | ((_g) << 16) | ((_b) << 8)))
#else
#define MAKE_RGB(_r, _g, _b)                                    \
        ((unsigned int)((_r) | ((_g) << 8) | ((_b) << 16)))
#endif

/* common colors */
#define COLOR_BLACK     MAKE_RGB0(  0,  0,  0)  // 0x00000000
#define COLOR_WHITE     MAKE_RGB0(255,255,255)  // 0x00ffffff
#define COLOR_GRAY      MAKE_RGB0(128,128,128)  // 0x00808080
#define COLOR_RED       MAKE_RGB0(255,  0,  0)  // 0x000000ff
#define COLOR_GREEN     MAKE_RGB0(  0,255,  0)  // 0x0000ff00
#define COLOR_BLUE      MAKE_RGB0(  0,  0,255)  // 0x00ff0000
#define COLOR_CYAN      MAKE_RGB0(  0,255,255)  // 0x00ffff00
#define COLOR_MAGENTA   MAKE_RGB0(255,  0,255)  // 0x00ff00ff
#define COLOR_YELLOW    MAKE_RGB0(255,255,  0)  // 0x0000ffff

/*---------------------------------------------------------------------------*/

// #define USE_STATIC_KEYWORD
#ifdef USE_STATIC_KEYWORD
#define STATIC          static
#else
#define STATIC          /* fake keyword for documentation */
#endif

#define SECTION(x)      __attribute__((section(x)))

#define CATSTR_(pre, post) pre##post
#define CATSTR(pre, post) CATSTR_(pre, post)

#define STATIC_ASSERT(cond, msg) \
    typedef char CATSTR(__static_assert_t_, __LINE__)[(cond)?1:-1]

/*---------------------------------------------------------------------------*/

#define SCREEN_WIDTH    (320)
#define SCREEN_HEIGHT   (240)

#define FRAME_WIDTH     (320)
#define FRAME_HEIGHT    (224)   /* 240 minus 16-pixel overscan area */

/*---------------------------------------------------------------------------*/

static inline u_long LLOAD( void *from )
{
    return *(u_long *)from;
}

static inline void LSTORE( u_long from, void *to )
{
    *(u_long *)to = from;
}

static inline u_short SLOADL( void *from )
{
    return *(u_short *)from;
}

static inline void SSTOREL( u_short from, void *to )
{
    *(u_short *)to = from;
}

static inline void LCOPY( void *s1, void *d1 )
{
    *(u_long *)d1 = *(u_long *)s1;
}

static inline void LCOPY2( void *s1, void *d1, void *s2, void *d2 )
{
    u_long r1, r2;

    r1 = *(u_long *)s1;
    r2 = *(u_long *)s2;
    *(u_long *)d1 = r1;
    *(u_long *)d2 = r2;
}

static inline void SCOPYL( void *s1, void *d1 )
{
    *(u_short *)d1 = *(u_short *)s1;
}

static inline void SCOPYL2( void *s1, void *d1, void *s2, void *d2 )
{
    u_short r1, r2;

    r1 = *(u_short *)s1;
    r2 = *(u_short *)s2;
    *(u_short *)d1 = r1;
    *(u_short *)d2 = r2;
}

#endif // __MGS_COMMON_H__
