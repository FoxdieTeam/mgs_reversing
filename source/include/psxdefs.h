/**
 * Supplemental definitions for PSX SDK headers
 */
#ifndef __MGS_PSXDEFS_H__
#define __MGS_PSXDEFS_H__

// Due to none of the OpenEvent callbacks using the correct prototype,
// we now have to cast them to avoid warnings.
typedef long (*openevent_cb_t)();

/* scratch pad address 0x1f800000 - 0x1f800400 */
#define getScratchAddr2(type, offset)   ((type *)(0x1f800000+(offset)))

/*---------------------------------------------------------------------------*/
// libgpu.h's setPrimXX macros set these codes, but sometimes we need
// to specify them ourselves. libgs.h (which MGS does not use) provides
// named constants, but they only account for the POLYGON types.

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
