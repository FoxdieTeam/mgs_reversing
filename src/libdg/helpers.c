//Not sure what this file is acutally called. Rename at a later date.

#include "libdg.h"
#include <INLINE_C.H>

extern MATRIX* RotMatrixYXZ_gte_80094108( SVECTOR* r, MATRIX* m) ;
extern MATRIX* MulRotMatrix_80092B58( MATRIX *m0 );

//GTE MVMVA Command: Vector 0 (V0) * Rotation Matrix (RT) + Translation Vector (TR) - 8 Cycles
#define rtv0tr() __asm__ volatile ( \
	"nop;"                          \
	"nop;"                          \
	"cop2 0x0480012" )

// GTE MVMVA Command: Vector 3 (IR) * Rotation Matrix (RT) - 8 Cycles
#define rtir12() __asm__ volatile ( \
	"nop;"                          \
	"nop;"                          \
	"cop2 0x049E012" )

// GTE Coordinate Calculation Commands: Perspective Transformation (Single) - 15 Cycles
#define rtps() __asm__ volatile ( \
	"nop;"                          \
	"nop;"                          \
	"cop2 0x0180001" )

void DG_SetPos_8001BC44( MATRIX* matrix )
{
    gte_SetRotMatrix ( matrix );
    gte_SetTransMatrix ( matrix );
}

void DG_SetPos2_8001BC8C( SVECTOR* svector, SVECTOR* svector2 )
{
    MATRIX m;
    RotMatrixYXZ_gte_80094108( svector2, &m );
    
    m.t[0] = svector->vx;
    m.t[1] = svector->vy;
    m.t[2] = svector->vz;

    gte_SetRotMatrix ( &m );
    gte_SetTransMatrix ( &m );
}

void DG_MovePos_8001BD20( SVECTOR* svector )
{
    SVECTOR svec, svec2;

    gte_ldv0( svector );
    rtv0tr();
    gte_stlvnl( &svec );
    gte_SetTransVector( &svec );
}

void DG_RotatePos_8001BD64( SVECTOR* svector )
{
    MATRIX  matrix;
    
    RotMatrixYXZ_gte_80094108( svector, &matrix ) ;
    MulRotMatrix_80092B58( &matrix ) ;
    gte_SetRotMatrix( &matrix ) ;
}

void DG_PutObjs_8001BDB8( MATRIX* matrix )
{
    gte_ReadRotMatrix( matrix ) ;
}

void DG_PutPrim_8001BE00( MATRIX* matrix )
{
    gte_ReadRotMatrix( matrix ) ;
}

void DG_PutVector_8001BE48( SVECTOR* svector, SVECTOR* svector2, int count )
{
    while (--count > -1 )
    {
        gte_ldv0( svector );
        rtv0tr();
        gte_stsv( svector2 );
        svector++;
        svector2++;
    }
}

void DG_RotVector_8001BE98( SVECTOR* svector, SVECTOR* svector2, int count )
{
    while (--count > -1 )
    {
        gte_ldsv( svector );
        rtir12();
        gte_stsv( svector2 );
        svector++;
        svector2++;
    }
}

void DG_PersVector_8001BEF8( SVECTOR* svector, DVECTOR* dvector, int count )
{
    while (--count > -1 )
    {
        gte_ldv0( svector );
        rtps();
        gte_stsxy( dvector );
        svector++;
        dvector++;
    }
}