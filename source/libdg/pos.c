#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

extern DG_CHANL DG_Chanls[3];

/*---------------------------------------------------------------------------*/

void DG_SetPos( MATRIX *world )
{
    gte_SetRotMatrix( world );
    gte_SetTransMatrix( world );
}

void DG_SetPos2( SVECTOR *mov, SVECTOR *rot )
{
    MATRIX tmp_mat;

    RotMatrixYXZ_gte( rot, &tmp_mat );

    tmp_mat.t[0] = mov->vx;
    tmp_mat.t[1] = mov->vy;
    tmp_mat.t[2] = mov->vz;

    gte_SetRotMatrix( &tmp_mat );
    gte_SetTransMatrix( &tmp_mat );
}

void DG_MovePos( SVECTOR *mov )
{
    VECTOR tmp_vec;

    gte_ldv0( mov );
    gte_rt();
    gte_stlvnl( &tmp_vec );
    gte_SetTransVector( &tmp_vec );
}

void DG_RotatePos( SVECTOR *rot )
{
    MATRIX tmp_mat;

    RotMatrixYXZ_gte( rot, &tmp_mat );
    MulRotMatrix( &tmp_mat );
    gte_SetRotMatrix( &tmp_mat );
}

/*---------------------------------------------------------------------------*/

void DG_PutObjs( DG_OBJS *objs )
{
    gte_ReadRotMatrix( &objs->world );
}

void DG_PutPrim( MATRIX *matrix )
{
    gte_ReadRotMatrix( matrix );
}

void DG_PutVector( SVECTOR *from, SVECTOR *to, int n )
{
    while (--n >= 0) {
        gte_ldv0( from );
        gte_rt();
        gte_stsv( to );
        from++;
        to++;
    }
}

void DG_RotVector( SVECTOR *from, SVECTOR *to, int n )
{
    while (--n >= 0) {
        gte_ldsv( from );
        gte_rtir();
        gte_stsv( to );
        from++;
        to++;
    }
}

void DG_PersVector( SVECTOR *from, DVECTOR *to, int n )
{
    while (--n >= 0) {
        gte_ldv0( from );
        gte_rtps();
        gte_stsxy( to );
        from++;
        to++;
    }
}

/*---------------------------------------------------------------------------*/

#define MAX_X (unsigned int)385
#define MAX_Y (unsigned int)305
#define DOES_TOUCH 1
#define DOESNT_TOUCH 0

// TODO: find a way to incorporate both this and pointcheckone's touch check in one function that matches
static inline void check_touches(SVECTOR *svector, DVECTOR *first_points, DVECTOR *second_points, int n_points)
{
    while (n_points > 0)
    {
        svector->pad = DOESNT_TOUCH;

        if (*(long *)second_points)
        {
            if (((first_points->vx + 0xC0) < MAX_X) && ((first_points->vy + 0x98) < MAX_Y))
            {
                svector->pad = DOES_TOUCH;
            }
        }

        n_points--;
        second_points++;
        first_points++;
        svector++;
    }
}

void DG_PointCheck( SVECTOR *svector, int n_points )
{
    MATRIX  *matrix;
    DVECTOR *first_points;
    DVECTOR *second_points;

    int     n_initial_points;
    MATRIX *matrix2 = (MATRIX *)SCRPAD_ADDR;

    gte_ReadRotMatrix(matrix2);

    matrix = &DG_Chanls[1].eye_inv;
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);

    gte_ldv3c(svector);

    first_points = (DVECTOR *)(SCRPAD_ADDR + 0x20);  // 3 sets of dvector
    second_points = (DVECTOR *)(SCRPAD_ADDR + 0x2C); // 3 sets of dvector

    svector += 3;
    gte_rtpt_b();

    for (n_initial_points = n_points - 3; n_initial_points > 0; n_initial_points -= 3)
    {
        gte_stsxy3c(first_points);
        gte_stsz3c(second_points);
        gte_ldv3c(svector);
        gte_rtpt();

        check_touches(svector - 3, first_points, second_points, 3);

        svector += 3;
        n_points -= 3;
    }

    gte_stsxy3c(first_points);
    gte_stsz3c(second_points);

    check_touches(svector - 3, first_points, second_points, n_points);

    gte_SetRotMatrix((MATRIX *)SCRPAD_ADDR);
    gte_SetTransMatrix((MATRIX *)SCRPAD_ADDR);
}

int DG_PointCheckOne( DVECTOR *line )
{
    DVECTOR first_points;
    DVECTOR second_points;

    MATRIX *matrix = &DG_Chanls[1].eye_inv;
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);

    gte_ldv0(line);
    gte_rtps();

    gte_stsxy(&first_points);
    gte_stsz(&second_points);

    if (!*(long *)&second_points)
    {
        return 0;
    }

    if (!(first_points.vx + 0xC0 < MAX_X))
    {
        return 0;
    }

    return first_points.vy + 0x98 < MAX_Y;
}
