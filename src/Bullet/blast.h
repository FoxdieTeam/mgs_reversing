#ifndef _BLAST_H_
#define _BLAST_H_

#include "Game/target.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include <LIBGPU.H>
#include <LIBGTE.H>
#include <SYS/TYPES.H>

typedef struct	Blast_Data
{
	int			field_0;
	int			field_4;
	int			field_8_z;
	int			field_C;
	int			field_10;
} Blast_Data;

typedef struct	BlastWork
{
	GV_ACT    field_0_actor;
	int       field_20_map_bits;
	SVECTOR   field_24_vec;
	DG_PRIM  *field_2C_prim;
	int       field_30;
	int       field_34;
	int       field_38;
	TARGET field_3C_target;
} BlastWork;

void blast_act_8006DD18( BlastWork *work );
void AN_Blast_Single_8006E224( SVECTOR *pVec );
void blast_8006DDEC( Blast_Data *pBlastData, BlastWork *pBlast, int targetSidePicker );
void AN_Blast_Minimini_8006E32C( SVECTOR *pVec );
void AN_Blast_8006E2A8(SVECTOR *pos);

BlastWork * NewBlast_8006DFDC( MATRIX *pMtx, Blast_Data *pBlastData );
BlastWork * NewBlast2_8006E0F0( MATRIX *pMtx, Blast_Data *pBlastData, int doSound, int whichSidePicker );

void NewStanBlast_80074B5C( MATRIX *pMtx );

#endif // _BLAST_H_
