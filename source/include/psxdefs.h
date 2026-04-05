/**
 * Supplemental definitions for PSX SDK headers
 */
#ifndef __MGS_PSXDEFS_H__
#define __MGS_PSXDEFS_H__

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

// getScratchAddr() but cast as a pointer to the specified type.
// Unlike the original, offset is NOT multiplied by the sizeof(type).
#define getScratchAddr2(type, offset)   ((type *)(0x1f800000+(offset)))

/*---------------------------------------------------------------------------*/
// clang-format off

#define SCRPAD_ADDR     0x1f800000
#define SCRPAD_SIZE     0x400

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
// libgpu.h's setPrimXX macros set these codes, but sometimes we need
// to specify them ourselves. libgs.h (which MGS does not use) provides
// named constants, but they only account for the POLYGON types.

#define GPU_CODE_SHADETEX       0x01    /* disables shading */
#define GPU_CODE_SEMITRANS      0x02    /* enables semitransparency */

#define GPU_CODE_POLY_F3        0x20    /* GPU_COM_F3   */
#define GPU_CODE_POLY_FT3       0x24    /* GPU_COM_TF3  */
#define GPU_CODE_POLY_F4        0x28    /* GPU_COM_F4   */
#define GPU_CODE_POLY_FT4       0x2C    /* GPU_COM_TF4  */
#define GPU_CODE_POLY_G3        0x30    /* GPU_COM_G3   */
#define GPU_CODE_POLY_GT3       0x34    /* GPU_COM_TG3  */
#define GPU_CODE_POLY_G4        0x38    /* GPU_COM_G4   */
#define GPU_CODE_POLY_GT4       0x3C    /* GPU_COM_TG4  */
#define GPU_CODE_LINE_F2        0x40
#define GPU_CODE_LINE_F3        0x48
#define GPU_CODE_LINE_F4        0x4C
#define GPU_CODE_LINE_G2        0x50
#define GPU_CODE_LINE_G3        0x58
#define GPU_CODE_LINE_G4        0x5C
#define GPU_CODE_TILE           0x60
#define GPU_CODE_SPRT           0x64
#define GPU_CODE_TILE_1         0x68
#define GPU_CODE_TILE_8         0x70
#define GPU_CODE_SPRT_8         0x74
#define GPU_CODE_TILE_16        0x78
#define GPU_CODE_SPRT_16        0x7C

#endif // __MGS_PSXDEFS_H__
