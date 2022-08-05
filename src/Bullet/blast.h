#ifndef _BLAST_H_
#define _BLAST_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/actor.h"
#include "target.h"

typedef struct Blast_Data
{
    int field_0;
    int field_4;
    int field_8_z;
    int field_C;
    int field_10;
    int field_14;
} Blast_Data;

typedef struct Actor_Blast
{
    Actor     field_0_actor;
    int       field_20_map_bits;
    SVECTOR   field_24_vec;
    int       field_2C;
    int       field_30;
    int       field_34;
    int       field_38;
    GM_Target field_3C_target;
} Actor_Blast;

#endif // _BLAST_H_
