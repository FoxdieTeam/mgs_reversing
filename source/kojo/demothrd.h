#ifndef _DEMOTHRD_H_
#define _DEMOTHRD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "game/game.h"

#include "fmt_dmo.h"

typedef struct DEMO_M1E1
{
    OBJECT  object[2][3];
    int     field_558_idx[2];
    int     field_560;
    SVECTOR field_564[2];
} DEMO_M1E1;

typedef struct DEMO_HIND
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
} DEMO_HIND;

typedef struct DEMO_MODEL
{
    CONTROL    control;
    OBJECT     object;
    MATRIX     light[2];
    DEMO_M1E1 *extra; // union, can be DEMO_HIND also, depending on the current stage
} DEMO_MODEL;

typedef struct ACTNODE
{
    struct ACTNODE *prev;
    struct ACTNODE *next;
    int             used;
    GV_ACT         *actor1;
    GV_ACT         *actor2;
    DMO_CHA         chara;
    int             field_48;
    int             field_4C;
    short           field_50;
    short           field_52;
    short           field_54;
    short           field_56;
    MATRIX          field_58;
} ACTNODE;

typedef struct DemothrdWork
{
    GV_ACT       actor;
    int          flag;
    int          start_time;
    int          map;
    int          frame;
    DMO_DEF     *header;
    DEMO_MODEL  *models;
    ACTNODE      chain;
    int          field_B0; /* unused */
    int          field_B4; /* unused */
    int          field_B8; /* unused */
    int          field_BC; /* unused */
    DMO_DEF     *stream;
    CONTROL      control;
    OBJECT       object;
    MATRIX       light[2];
    int          field_264; /* unused */
    int          field_268; /* unused */
    int          field_26C; /* unused */
    DG_CHANLFUNC old_screen;
    int          old_game_status;
    GM_CAMERA    old_camera;
    int          old_item;
    int          old_weapon;
} DemothrdWork;

/* This should be replaced by loads of individual structs */
typedef struct DMO_DATA_0x36
{
    int field_0;
    int field_4_type;

    DG_SVECTOR field_8_vec1;
    DG_SVECTOR field_E_vec2;

    // TODO: Is there a cleaner way to model this structure?
    // Some of the variants are very similar. Once all
    // MakeChara functions are decompiled those fields
    // should be named properly (and maybe it'll be easier
    // to find patterns then).
    union {
        struct
        {
            int   field_14;
            short field_18;
        } variant_0x3;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x4;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x5;

        struct
        {
            short field_14;
        } variant_0x6;

        struct
        {
            short field_14;
        } variant_0x7;

        struct
        {
            short field_14;
        } variant_0x9;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
        } variant_0xA;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0xC;

        struct
        {
            int     field_14;
            SVECTOR field_18;
            short   field_20;
            short   field_22;
            short   field_24;
            short   field_26;
        } variant_0xE;

        struct
        {
            short field_14;
        } variant_0xF;

        struct
        {
            int field_14;
            int field_18;
            int field_1C;
            int field_20;
            int field_24;
            int field_28;
            int field_2C;
            int field_30;
        } variant_0x10;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
        } variant_0x12;

        struct
        {
            short field_14;
        } variant_0x13;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x14;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x15;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
        } variant_0x17;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x18;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
        } variant_0x19;

        struct
        {
            int field_14;
        } variant_0x1A;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x1B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
        } variant_0x1C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x1D;

        struct
        {
            short field_14;
        } variant_0x1E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
            short field_20;
        } variant_0x20;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x21;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x22;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
        } variant_0x23;

        struct
        {
            short field_14;
        } variant_0x24;

        struct
        {
            short field_14;
        } variant_0x25;

        struct
        {
            DG_OBJS *field_14;
            int      field_18;
        } variant_0x26;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            int   field_1C;
        } variant_0x28;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
        } variant_0x29;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x2A;

        struct
        {
            short field_14;
        } variant_0x2B;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
        } variant_0x2C;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            int   field_1C;
            short field_20;
            short field_22;
        } variant_0x2D;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
        } variant_0x2E;

        struct
        {
            short field_14;
        } variant_0x2F;

        struct
        {
            int   field_14;
            int   field_18;
            short field_1C;
            short field_1E;
            int   field_20;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
        } variant_0x34;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
        } variant_0x35;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x36;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
        } variant_0x37;

        struct
        {
            short field_14;
        } variant_0x39;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
        } variant_0x3A;

        struct
        {
            int   field_14;
            int   field_18;
            int   field_1C;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
        } variant_0x3B;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
            short field_24;
            short field_26;
            short field_28;
            short field_2A;
            short field_2C;
            short field_2E;
            short field_30;
            short field_32;
            short field_34;
        } variant_0x3C;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3D;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x3E;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
        } variant_0x3F;

        struct
        {
            short field_14;
        } variant_0x41;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x42;

        struct
        {
            int   field_14;
            short field_18;
        } variant_0x43;

        struct
        {
            short field_14;
            short field_16;
            int   field_18;
            short field_1C;
            short field_1E;
            short field_20;
            short field_22;
        } variant_0x44;

        struct
        {
            short field_14;
            short field_16;
            short field_18;
            short field_1A;
        } variant_0x45;

        struct
        {
            short field_14;
            short field_16;
        } variant_0x46;

        struct
        {
            short field_14;
        } variant_0x49;

        struct
        {
            int   field_14;
            short field_18;
            short field_1A;
            int   field_1C;
            int   field_20;
        } variant_0x4A;
    } data;
} DMO_DATA_0x36;

int DM_ThreadStream_80079460(int flag, int unused);
int DM_ThreadFile_800794E4(int param_1, int param_2);

#endif // _DEMOTHRD_H_
