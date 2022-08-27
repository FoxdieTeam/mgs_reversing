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
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int field_8C;
    int field_90;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    int field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    int field_FC;
} sgtrect3_0x100;

typedef struct Actor_sgtrect3
{
    Actor          field_0_actor;
    int            field_20;
    short          field_24;
    short          field_26;
    int            field_28;
    char           field_2C;
    char           field_2D;
    char           field_2E;
    char           field_2F;
    GM_Target     *field_30_target;
    int            field_34_count;
    int            field_38;
    sgtrect3_0x600 field_3C[2];
    sgtrect3_0x800 field_C3C[2];
    sgtrect3_lines field_1C3C_lines[2];
    int            field_217C;
    int            field_2180;
    int            field_2184;
    int            field_2188;
    int            field_218C;
    int            field_2190;
    int            field_2194;
    int            field_2198;
    int            field_219C;
    int            field_21A0;
    int            field_21A4;
    int            field_21A8;
    int            field_21AC_target_count;
    int            field_21B0;
    int            field_21B4;
    sgtrect3_0x100 field_21B8[2];
    DR_TPAGE       field_23B8_prim[2];
} Actor_sgtrect3;

int sgtrect3_init_80071010(short *, int, int *, int);

#endif // _SGTRECT3_H_
