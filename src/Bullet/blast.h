#ifndef _BLAST_H_
#define _BLAST_H_

#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/target.h"

typedef struct Blast_Data
{
    int field_0;   // hp
    int field_4;
    int field_8_z; // size
    int field_C;   // also size?
    int field_10;  // TARGET->field_44
} Blast_Data;

typedef struct BlastWork
{
    GV_ACT   actor;
    int      map;
    SVECTOR  pos;
    DG_PRIM *prim;
    int      unused1;
    int      unused2;
    int      time;
    TARGET   target;
} BlastWork;

void AN_Blast_Single_8006E224( SVECTOR *pos );
void AN_Blast_Mini_8006E2A8( SVECTOR *pos );
void AN_Blast_Minimini_8006E32C( SVECTOR *pos );
void AN_Blast_high_8006E4A4( SVECTOR *pos );
void AN_Blast_high2_8006E6CC( SVECTOR *pos, SVECTOR *offset );

GV_ACT *NewBlast_8006DFDC( MATRIX *world, Blast_Data *blast_data );
GV_ACT *NewBlast2_8006E0F0( MATRIX *world, Blast_Data *blast_data, int doSound, int side );

#endif // _BLAST_H_
