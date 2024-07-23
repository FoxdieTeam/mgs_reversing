#ifndef _COMMON_H_
#define _COMMON_H_

#define __min(x, y) (((x) < (y)) ? (x) : (y))
#define __max(x, y) (((x) > (y)) ? (x) : (y))

#define __clamp(x, min, max) (__max(__min(x, max), min))

#define ABS(x) (((x) >= 0) ? (x) : -(x))

#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

// These macros were taken from "GTE Advanced Topics" (slide 18),
// originally presented at the March 1996 PlayStation Developer's Conference.
//
// "spadstk.h" from the SDK's texture address modulation sample
// (psx/sample/graphics/texaddr/wave) defines slightly modified versions
// of SetSpadStack/ResetSpadStack that add/sub 24 from $sp instead of 4.

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
    __asm__ volatile ("addiu $29,$29,4" :::"$29","memory"); \
    __asm__ volatile ("lw $29,0($29)"   :::"$29","memory"); \
}

#define GetStackAddr(addr) { \
    __asm__ volatile ("move $8,%0"  ::"r"(addr):"$8","memory"); \
    __asm__ volatile ("sw $29,0($8)"::         :"$8","memory"); \
}
// clang-format on

#endif // _COMMON_H_
