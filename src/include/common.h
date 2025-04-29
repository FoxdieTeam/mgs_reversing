#ifndef _COMMON_H_
#define _COMMON_H_

#include <stddef.h>     // for NULL
#include <sys/types.h>

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

typedef int             BOOL;

#ifndef FALSE
#define FALSE           (0)
#endif
#ifndef TRUE
#define TRUE            (!FALSE)
#endif

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

#define SCRPAD_ADDR     0x1f800000

// These macros were taken from "GTE Advanced Topics" (slide 18),
// originally presented at the March 1996 PlayStation Developer's Conference.
//
// According to stack.txt (in Japanese) from the seminar sample code,
// compiler optimizations should be set to -O1 or higher, otherwise
// the $fp register may be used, potentially resulting in a crash.
//
// In addition, function calls with 5 or more arguments will use the stack
// for passing the 5th argument onwards. The callee will receive garbage data
// if these are set before the stack switch.

// clang-format off
/* scratch pad address 0x1f800000 - 0x1f800400 */
#define SPAD_STACK_ADDR 0x1f8003fc

#define SetSpadStack(addr) { \
    __asm__ volatile ("move $8,%0"     ::"r"(addr):"$8","memory"); \
    __asm__ volatile ("sw $29,0($8)"   ::         :"$8","memory"); \
    __asm__ volatile ("addiu $8,$8,-4" ::         :"$8","memory"); \
    __asm__ volatile ("move $29,$8"    ::         :"$8","memory"); \
}

#define ResetSpadStack() { \
    __asm__ volatile ("addiu $29,$29,4":::"$29","memory"); \
    __asm__ volatile ("lw $29,0($29)"  :::"$29","memory"); \
}

#define GetStackAddr(addr) { \
    __asm__ volatile ("move $8,%0"     ::"r"(addr):"$8","memory"); \
    __asm__ volatile ("sw $29,0($8)"   ::         :"$8","memory"); \
}
// clang-format on

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

#endif // _COMMON_H_
