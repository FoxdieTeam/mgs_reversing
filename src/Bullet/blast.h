#ifndef _BLAST_H_
#define _BLAST_H_

#include <sys/types.h>
#include <libgte.h>

#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/target.h"

typedef struct BLAST_DATA
{
    int field_0;   // hp
    int field_4;
    int field_8_z; // size
    int field_C;   // also size?
    int field_10;  // TARGET->field_44
} BLAST_DATA;

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

GV_ACT *NewBlast( MATRIX *world, BLAST_DATA *blast_data );
GV_ACT *NewBlast2( MATRIX *world, BLAST_DATA *blast_data, int doSound, int side );

void AN_Blast_Single( SVECTOR *pos );
void AN_Blast_Mini( SVECTOR *pos );
void AN_Blast_Minimini( SVECTOR *pos );
void AN_Blast_high( SVECTOR *pos );
void AN_Blast_high2( SVECTOR *pos, SVECTOR *offset );

#endif // _BLAST_H_
