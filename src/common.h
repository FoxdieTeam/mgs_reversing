#ifndef _COMMON_H_
#define _COMMON_H_

#define __min(x, y) (((x) < (y)) ? (x) : (y))
#define __max(x, y) (((x) > (y)) ? (x) : (y))

#define __clamp(x, min, max) (__max(__min(x, max), min))

#define ABS(x) (((x) >= 0) ? (x) : -(x))

#define DCache 0x1F8003FC

// Put stack on scratchpad
#define SetSpadStack(addr)                                                                                             \
    {                                                                                                                  \
        __asm__ volatile("move $8,%0" ::"r"(addr) : "$8", "memory");                                                   \
        __asm__ volatile("sw $29,0($8)" ::: "$8", "memory");                                                           \
        __asm__ volatile("addiu $8,$8,-4" ::: "$8", "memory");                                                         \
        __asm__ volatile("move $29,$8" ::: "$8", "memory");                                                            \
    }

// reset scratchpad stack
#define ResetSpadStack()                                                                                               \
    {                                                                                                                  \
        __asm__ volatile("addiu $29,$29,4" ::: "$29", "memory");                                                       \
        __asm__ volatile("lw $29,0($29)" ::: "$29", "memory");                                                         \
    }

#endif // _COMMON_H_
