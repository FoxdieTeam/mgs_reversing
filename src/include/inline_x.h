/* clang-format off */

/*
 *      Macro definitions w/o DMPSX for METAL GEAR SOLID
 *      inline_x.h
 */

/* additional functions */

#define gte_read_opz( r0 ) __asm__ volatile (                   \
        "mfc2   %0, $24"                                        \
        : "=r"( r0 ) )

#define gte_ldVXY0( r0 ) __asm__ volatile (                     \
        "mtc2   %0, $0"                                         \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldVZ0( r0 ) __asm__ volatile (                      \
        "mtc2   %0, $1"                                         \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldVXY1( r0 ) __asm__ volatile (                     \
        "mtc2   %0, $2"                                         \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldVZ1( r0 ) __asm__ volatile (                      \
        "mtc2   %0, $3"                                         \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldVXY2( r0 ) __asm__ volatile (                     \
        "mtc2   %0, $4"                                         \
        :                                                       \
        : "r"( r0 ) )

#define gte_ldVZ2( r0 ) __asm__ volatile (                      \
        "mtc2   %0, $5"                                         \
        :                                                       \
        : "r"( r0 ) )

/* clang-format on */
