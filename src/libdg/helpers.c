//Not sure what this file is acutally called. Rename at a later date.
#include "linker.h"
#include "libdg.h"
#include <INLINE_C.H>

MATRIX SECTION(".gUnknown_Matrix_800B19FC") gUnknown_Matrix_800B19FC;

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

// RTPT  equ 0x0280030 ; GTE Coordinate Calculation Commands: Perspective Transformation (Triple) - 23 Cycles
#define rtpt() __asm__ volatile ( \
	"nop;"                          \
	"nop;"                          \
	"cop2 0x0280030" )

#define rtpt_b() __asm__ volatile ( \
	"cop2 0x0280030" )

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
    VECTOR vec;

    gte_ldv0( svector );
    rtv0tr();
    gte_stlvnl( &vec );
    gte_SetTransVector( &vec );
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

#define SCRPAD_ADDR 0x1F800000
#define MAX_X (unsigned int)385
#define MAX_Y (unsigned int)305

void DG_PointCheck_8001BF34( SVECTOR *svector, int n_points )
{
    SVECTOR* prev_vec;
    DVECTOR* temp_first_points;
    DVECTOR* temp_second_points;

    MATRIX* matrix;
    DVECTOR* first_points;
    DVECTOR* second_points;

    int n_initial_points;
    MATRIX* matrix2 = (MATRIX* )SCRPAD_ADDR;

    gte_ReadRotMatrix( matrix2 );

    matrix = &gUnknown_Matrix_800B19FC;
    gte_SetRotMatrix  ( matrix );
    gte_SetTransMatrix( matrix );

    gte_ldv3c( svector );

    first_points  = (DVECTOR*)(SCRPAD_ADDR + 0x20); //3 sets of dvector
    second_points = (DVECTOR*)(SCRPAD_ADDR + 0x2C); //3 sets of dvector

    svector += 3;
    rtpt_b();

    n_initial_points = n_points - 3;

    if ( n_initial_points > 0 )
    {
        short check = 1;

        while ( n_initial_points > 0 )
        {
            int i ;
            SVECTOR* prev_vec_2;
            DVECTOR* temp_first_points_1;
            DVECTOR* temp_second_points_2;
            gte_stsxy3c( first_points );
            gte_stsz3c ( second_points );
            gte_ldv3c( svector );
            rtpt();

            temp_first_points_1 = first_points;
            temp_second_points_2 = second_points;
            prev_vec_2 = svector - 3;

            i = 3;
            while ( i > 0 )
            {
                prev_vec_2->pad = 0;

                if ( *(long*)temp_second_points_2 )
                {
                    if ( ((temp_first_points_1->vx + 0xC0) < MAX_X) && 
                         ((temp_first_points_1->vy + 0x98) < MAX_Y) )
                    {
                        prev_vec_2->pad = check;
                    }
                }

                i--;
                temp_second_points_2 ++;
                temp_first_points_1 ++;
                prev_vec_2 ++;
            }

            svector += 3;
            n_initial_points -= 3;
            n_points -= 3;
        }
    }

    gte_stsxy3c( first_points );
    gte_stsz3c ( second_points );

    temp_first_points = first_points;
    temp_second_points = second_points;
    prev_vec = svector - 3;

    if ( n_points > 0 )
    {
        short check = 1;

        while ( n_points > 0 )
        {
            prev_vec->pad = 0;

            if ( *(long*)temp_second_points )
            {
                if ( ((temp_first_points->vx + 0xC0) < MAX_X) && 
                     ((temp_first_points->vy + 0x98) < MAX_Y) )
                {
                    prev_vec->pad = check;
                }
            }

            n_points--;
            temp_second_points++;
            temp_first_points++;
            prev_vec++;
        }

    }

    gte_SetRotMatrix  ( (MATRIX* )SCRPAD_ADDR ) ;
    gte_SetTransMatrix( (MATRIX* )SCRPAD_ADDR ) ;
}

int DG_PointCheckOne_8001C18C( SVECTOR* svec )
{
    DVECTOR first_points;
    DVECTOR second_points;

    MATRIX* matrix = &gUnknown_Matrix_800B19FC;
    gte_SetRotMatrix  ( matrix );
    gte_SetTransMatrix( matrix );

    gte_ldv0( svec ) ;
    rtps() ;

    gte_stsxy( &first_points );
    gte_stsz ( &second_points );

    if ( !*(long* )&second_points ) 
    {
        return 0;
    }

    if ( !( first_points.vx + 0xC0  < MAX_X ) ) 
    {
        return 0;
    }

    return first_points.vy + 0x98  < MAX_Y;
}

//set obj world and screen ?
void sub_8001C248( DG_OBJS* objs, int n_obj )
{
    DG_OBJ* obj;
    MATRIX* matrix;
    MATRIX* matrix2;
    MATRIX* matrix3;

    matrix = (MATRIX* )SCRPAD_ADDR;
    gte_SetRotMatrix( matrix );

    gte_ldclmv( &matrix[1] );
    rtir12();
    
    gte_stclmv( &matrix[2] );
    gte_ldclmv( &matrix[1].m[0][1] );
    rtir12();

    gte_stclmv( &matrix[2].m[0][1] );
    gte_ldclmv( &matrix[1].m[0][2] );
    rtir12();

    gte_stclmv( &matrix[2].m[0][2] );

    gte_SetTransMatrix( (MATRIX* )SCRPAD_ADDR );
    gte_ldlv0( &matrix[1].t );
    rtv0tr();

    gte_stlvnl( &matrix[2].t );

    obj = objs->objs;

    if ( n_obj <= 0)  return;

    matrix2 = &matrix[1];
    matrix3 = &matrix[2];

    for (; n_obj > 0 ; n_obj-- )
    {
        obj->world  = *matrix2;
        obj->screen = *matrix3;
        obj++;
    }
}

//set obj screen ?
void sub_8001C460( DG_OBJS* objs, int n_obj )
{
    DG_OBJ* obj;
    MATRIX* matrix;

    gte_SetRotMatrix  ( (MATRIX* )SCRPAD_ADDR );
    gte_SetTransMatrix( (MATRIX* )SCRPAD_ADDR );

    matrix = (MATRIX* )(SCRPAD_ADDR + 0x40);
    obj = objs->objs;

    for (; n_obj > 0 ; n_obj-- )
    {
        gte_ldlv0( matrix->t );
        rtv0tr();

        gte_stlvnl( &obj->screen.t );
        gte_ldclmv( matrix );
        rtir12();

        gte_stclmv( &obj->screen );
        gte_ldclmv( &matrix->m[0][1] );
        rtir12();

        gte_stclmv( &obj->screen.m[0][1] );
        gte_ldclmv( &matrix->m[0][2] );
        rtir12();

        gte_stclmv( &obj->screen.m[0][2] );
        obj++;
        matrix++;
    }
}

//set obj world accoring to parent?
void sub_8001C5CC( DG_OBJS* objs, int n_obj )
{
    DG_OBJ* obj;
    SVECTOR* movs = objs->movs;
    MATRIX* matrix;
    MATRIX* matrix2;

    matrix = (MATRIX* )(SCRPAD_ADDR  + 0x20);
    gte_SetRotMatrix( matrix );

    matrix2 = (MATRIX* )(SCRPAD_ADDR  + 0x40) ;
    
    obj = objs->objs;
    if ( n_obj <= 0)  return;

    for (; n_obj > 0 ; n_obj-- )
    {
        //it appears all the matrices in the scratchpad are ordered according to dg_objs
        MATRIX* parentMatrix = (MATRIX* )(SCRPAD_ADDR  + 0x40); 
        gte_SetTransMatrix( &parentMatrix[obj->model->parent_2C] );
        gte_ldv0( movs );
        rtv0tr();

        gte_ReadRotMatrix( matrix2 );
        gte_stlvnl( matrix2->t );

        movs++;

       obj->world = *matrix2;
       obj++;
       matrix2++;
    }
}