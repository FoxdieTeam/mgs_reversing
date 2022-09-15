#ifndef _BLAST_H_
#define _BLAST_H_

#include "Game/target.h"
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

typedef struct	Actor_Blast
{
	Actor		field_0_actor;
	int			field_20_map_bits;
	SVECTOR		field_24_vec;
	int			field_2C;
	int			field_30;
	int			field_34;
	int			field_38;
	GM_Target	field_3C_target;
} Actor_Blast;

void			blast_act_8006DD18( Actor_Blast *pActor );
void			AN_Blast_Single_8006E224( SVECTOR *pVec );
void			blast_8006DDEC( Blast_Data *pBlastData, Actor_Blast *pBlast, int targetSidePicker );

Actor			*NewBlast_8006DFDC( MATRIX *pMtx, Blast_Data *pBlastData );
void			NewStanBlast_80074B5C( MATRIX *pMtx );

#endif // _BLAST_H_
