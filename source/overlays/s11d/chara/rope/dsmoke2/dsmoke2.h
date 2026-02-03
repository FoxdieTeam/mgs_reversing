#ifndef S11D_DSMOKE2_H
#define S11D_DSMOKE2_H

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

// DSmoke2 work structure - 0x28C bytes (652 bytes)
typedef struct _DSmoke2Work
{
    GV_ACT      actor;         // 0x00 - 0x20 (32 bytes)
    CONTROL     control;       // 0x20 - 0x84 (100 bytes)
    int         field_84;      // 0x84
    int         field_88;      // 0x88
    int         field_8C;      // 0x8C
    int         field_90;      // 0x90
    int         field_94;      // 0x94
    int         field_98[8];   // 0x98-0xB8 (GCL related)
    short       field_B0;      // 0xB0 - map
    short       field_B2;      // 0xB2
    short       field_B4;      // 0xB4
    short       field_B6;      // 0xB6
    short       field_B8;      // 0xB8
    short       field_BA;      // 0xBA
    short       field_BC;      // 0xBC - timer
    short       field_BE;      // 0xBE
    int         field_C0[32];  // 0xC0-0x140 (primitive data)
    int         field_140[32]; // 0x140-0x1C0
    int         field_1C0[32]; // 0x1C0-0x240
    void       *prims[16];     // 0x240-0x280 (16 primitive pointers)
    DG_PRIM    *field_280;     // 0x280
    short       field_284;     // 0x284
    short       field_286;     // 0x286
    short       field_288;     // 0x288
    short       field_28A;     // 0x28A
} DSmoke2Work;

// Function declarations
void *s11d_dsmoke2_800CCD54(int name, int where, int argc, char **argv);

#endif // S11D_DSMOKE2_H
