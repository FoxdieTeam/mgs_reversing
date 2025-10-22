#ifndef __MGS_BULLET_BLAST_H__
#define __MGS_BULLET_BLAST_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct BLAST_DATA
{
    int field_0;   // hp
    int field_4;
    int field_8_z; // size
    int field_C;   // also size?
    int weapon;
} BLAST_DATA;

void *NewBlast( MATRIX *world, BLAST_DATA *blast_data );
void *NewBlast2( MATRIX *world, BLAST_DATA *blast_data, int doSound, int side );

void AN_Blast_Single( SVECTOR *pos );
void AN_Blast_Mini( SVECTOR *pos );
void AN_Blast_Minimini( SVECTOR *pos );
void AN_Blast_high( SVECTOR *pos );
void AN_Blast_high2( SVECTOR *pos, SVECTOR *offset );

#endif // __MGS_BULLET_BLAST_H__
