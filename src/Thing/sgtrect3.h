#ifndef _SGTRECT3_H_
#define _SGTRECT3_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/GM_Control.h"
#include "Game/target.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

// stinger missile first person HUD + stinger HUD?

typedef struct sgtrect3_lines
{
    LINE_F4 field_0[24];
} sgtrect3_lines;

typedef struct sgtrect3_0x600
{
    LINE_F3 field_0[64];
} sgtrect3_0x600;

typedef struct sgtrect3_0x800
{
    LINE_F2 field_0[128];
} sgtrect3_0x800;

typedef struct sgtrect3_0x100
{
    DR_TPAGE field_0[32];
} sgtrect3_0x100;

typedef struct Actor_sgtrect3
{
    Actor          field_0_actor;
    int            field_20;
    short          field_24;
    short          field_26;
    char           field_28_r;
    char           field_28_g;
    char           field_28_b;
    char           field_28_pad;
    char           field_2C_r;
    char           field_2D_g;
    char           field_2E_b;
    char           field_2F_pad;
    GM_Target     *field_30_target;
    int            field_34_count;
    int            field_38;
    sgtrect3_0x600 field_3C[2];
    sgtrect3_0x800 field_C3C[2];
    sgtrect3_lines field_1C3C_lines[2];
    int            field_217C[12];
    int            field_21AC_target_count;
    int            field_21B0;
    int            field_21B4;
    sgtrect3_0x100 field_21B8[2];
    DR_TPAGE       field_23B8_prim[2];
} Actor_sgtrect3;

int  sgtrect3_init_80071010(short *, int, int *, int);
void sgtrect3_act_helper_80070820(void *ot, LINE_F3 *lineF3Arr, LINE_F2 *lineF2Arr, DVECTOR *screenCoords,
                                  ushort offset, unsigned int rgb);

#endif // _SGTRECT3_H_
