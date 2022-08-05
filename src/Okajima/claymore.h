#ifndef _CLAYMORE_H_
#define _CLAYMORE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"
#include "libgv/actor.h"
#include "target.h"
#include "libdg/libdg.h"

typedef struct Actor_Claymore
{
    Actor     field_0;
    int       field_20_map;
    SVECTOR   field_24;
    SVECTOR   field_2C;
    SVECTOR   field_34;
    GM_Target field_3C_target;
    DG_PRIM  *field_84_pPrim;
    SVECTOR   field_88;
    int       field_90;
    int       field_94;
    int       field_98;
    int       field_9C;
    int       field_A0;
    int       field_A4;
    int       field_A8;
    int       field_AC;
    int       field_B0;
    int       field_B4;
    int       field_B8;
    int       field_BC;
    int       field_C0;
    int       field_C4;
    SVECTOR   field_C8;
    int       field_D0;
    int       field_D4;
    int       field_D8;
    int       field_DC;
    int       field_E0;
    int       field_E4;
    int       field_E8;
    int       field_EC;
    int       field_F0;
    int       field_F4;
    int       field_F8;
    int       field_FC;
    int       field_100;
    int       field_104;
    int       field_108;
    int       field_10C;
    SVECTOR   field_110;
    SVECTOR   field_118;
    int       field_120;
    int       field_124;
    int       field_128;
} Actor_Claymore;

#endif // _CLAYMORE_H_
