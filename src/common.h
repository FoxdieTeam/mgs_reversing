#ifndef _COMMON_H_
#define _COMMON_H_

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

#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

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

#endif // _COMMON_H_
