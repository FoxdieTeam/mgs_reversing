// Not sure what this file is acutally called. Rename at a later date.
#include "linker.h"
#include "libdg.h"
#include <INLINE_C.H>
#include "psyq.h"

extern MATRIX gUnknown_Matrix_800B19FC;

// GTE MVMVA Command: Vector 0 (V0) * Rotation Matrix (RT) + Translation Vector (TR) - 8 Cycles
#define rtv0tr()                                                                                                       \
    __asm__ volatile("nop;"                                                                                            \
                     "nop;"                                                                                            \
                     "cop2 0x0480012")

// GTE MVMVA Command: Vector 3 (IR) * Rotation Matrix (RT) - 8 Cycles
#define rtir12()                                                                                                       \
    __asm__ volatile("nop;"                                                                                            \
                     "nop;"                                                                                            \
                     "cop2 0x049E012")

// GTE Coordinate Calculation Commands: Perspective Transformation (Single) - 15 Cycles
#define rtps()                                                                                                         \
    __asm__ volatile("nop;"                                                                                            \
                     "nop;"                                                                                            \
                     "cop2 0x0180001")

// RTPT  equ 0x0280030 ; GTE Coordinate Calculation Commands: Perspective Transformation (Triple) - 23 Cycles
#define rtpt()                                                                                                         \
    __asm__ volatile("nop;"                                                                                            \
                     "nop;"                                                                                            \
                     "cop2 0x0280030")

#define rtpt_b() __asm__ volatile("cop2 0x0280030")

#define gte_MulMatrix0(r1, r2, r3)                                                                                     \
    {                                                                                                                  \
        gte_SetRotMatrix(r1);                                                                                          \
        gte_ldclmv(r2);                                                                                                \
        rtir12();                                                                                                      \
        gte_stclmv(r3);                                                                                                \
        gte_ldclmv((char *)r2 + 2);                                                                                    \
        rtir12();                                                                                                      \
        gte_stclmv((char *)r3 + 2);                                                                                    \
        gte_ldclmv((char *)r2 + 4);                                                                                    \
        rtir12();                                                                                                      \
        gte_stclmv((char *)r3 + 4);                                                                                    \
    }

#define gte_CompMatrix(r1, r2, r3)                                                                                     \
    {                                                                                                                  \
        gte_MulMatrix0(r1, r2, r3);                                                                                    \
        gte_SetTransMatrix(r1);                                                                                        \
        gte_ldlv0((char *)r2 + 20);                                                                                    \
        rtv0tr();                                                                                                      \
        gte_stlvnl((char *)r3 + 20);                                                                                   \
    }

#define gte_ApplyRotMatrix(r1, r2)                                                                                     \
    {                                                                                                                  \
        gte_ldv0(r1);                                                                                                  \
        rtv0tr();                                                                                                      \
        gte_stlvnl(r2);                                                                                                \
    }

#define gte_MulMatrix02(r1, r2, r3)                                                                                    \
    {                                                                                                                  \
        gte_ldlv0(r1);                                                                                                 \
        rtv0tr();                                                                                                      \
        gte_stlvnl(r1);                                                                                                \
        gte_ldclmv(r2);                                                                                                \
        rtir12();                                                                                                      \
        gte_stclmv(r3);                                                                                                \
        gte_ldclmv((char *)r2 + 2);                                                                                    \
        rtir12();                                                                                                      \
        gte_stclmv((char *)r3 + 2);                                                                                    \
        gte_ldclmv((char *)r2 + 4);                                                                                    \
        rtir12();                                                                                                      \
        gte_stclmv((char *)r3 + 4);                                                                                    \
    }

void DG_SetPos_8001BC44(MATRIX *matrix)
{
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);
}

void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2)
{
    MATRIX m;
    RotMatrixYXZ_gte_80094108(svector2, &m);

    m.t[0] = svector->vx;
    m.t[1] = svector->vy;
    m.t[2] = svector->vz;

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
}

void DG_MovePos_8001BD20(SVECTOR *svector)
{
    VECTOR vec;

    gte_ldv0(svector);
    rtv0tr();
    gte_stlvnl(&vec);
    gte_SetTransVector(&vec);
}

void DG_RotatePos_8001BD64(SVECTOR *svector)
{
    MATRIX matrix;

    RotMatrixYXZ_gte_80094108(svector, &matrix);
    MulRotMatrix_80092B58(&matrix);
    gte_SetRotMatrix(&matrix);
}

void DG_PutObjs_8001BDB8(DG_OBJS *objs)
{
    gte_ReadRotMatrix(&objs->world);
}

void DG_PutPrim_8001BE00(MATRIX *matrix)
{
    gte_ReadRotMatrix(matrix);
}

void DG_PutVector_8001BE48(SVECTOR *svector, SVECTOR *svector2, int count)
{
    while (--count > -1)
    {
        gte_ldv0(svector);
        rtv0tr();
        gte_stsv(svector2);
        svector++;
        svector2++;
    }
}

void DG_RotVector_8001BE98(SVECTOR *svector, SVECTOR *svector2, int count)
{
    while (--count > -1)
    {
        gte_ldsv(svector);
        rtir12();
        gte_stsv(svector2);
        svector++;
        svector2++;
    }
}

void DG_PersVector_8001BEF8(SVECTOR *svector, DVECTOR *dvector, int count)
{
    while (--count > -1)
    {
        gte_ldv0(svector);
        rtps();
        gte_stsxy(dvector);
        svector++;
        dvector++;
    }
}

#define SCRPAD_ADDR 0x1F800000
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

void DG_PointCheck_8001BF34(SVECTOR *svector, int n_points)
{
    MATRIX  *matrix;
    DVECTOR *first_points;
    DVECTOR *second_points;

    int     n_initial_points;
    MATRIX *matrix2 = (MATRIX *)SCRPAD_ADDR;

    gte_ReadRotMatrix(matrix2);

    matrix = &gUnknown_Matrix_800B19FC;
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);

    gte_ldv3c(svector);

    first_points = (DVECTOR *)(SCRPAD_ADDR + 0x20);  // 3 sets of dvector
    second_points = (DVECTOR *)(SCRPAD_ADDR + 0x2C); // 3 sets of dvector

    svector += 3;
    rtpt_b();

    for (n_initial_points = n_points - 3; n_initial_points > 0; n_initial_points -= 3)
    {
        gte_stsxy3c(first_points);
        gte_stsz3c(second_points);
        gte_ldv3c(svector);
        rtpt();

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

int DG_PointCheckOne_8001C18C(DVECTOR *line)
{
    DVECTOR first_points;
    DVECTOR second_points;

    MATRIX *matrix = &gUnknown_Matrix_800B19FC;
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);

    gte_ldv0(line);
    rtps();

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

// set obj world and screen ?
void sub_8001C248(DG_OBJS *objs, int n_obj)
{
    DG_OBJ *obj;
    MATRIX *matrix;
    MATRIX *matrix2;
    MATRIX *matrix3;

    matrix = (MATRIX *)SCRPAD_ADDR;
    gte_SetRotMatrix(matrix);

    gte_ldclmv(&matrix[1]);
    rtir12();

    gte_stclmv(&matrix[2]);
    gte_ldclmv(&matrix[1].m[0][1]);
    rtir12();

    gte_stclmv(&matrix[2].m[0][1]);
    gte_ldclmv(&matrix[1].m[0][2]);
    rtir12();

    gte_stclmv(&matrix[2].m[0][2]);

    gte_SetTransMatrix((MATRIX *)SCRPAD_ADDR);
    gte_ldlv0(&matrix[1].t);
    rtv0tr();

    gte_stlvnl(&matrix[2].t);

    obj = objs->objs;

    if (n_obj <= 0)
        return;

    matrix2 = &matrix[1];
    matrix3 = &matrix[2];

    for (; n_obj > 0; n_obj--)
    {
        obj->world = *matrix2;
        obj->screen = *matrix3;
        obj++;
    }
}

// set obj screen ?
void sub_8001C460(DG_OBJS *objs, int n_obj)
{
    DG_OBJ *obj;
    MATRIX *matrix;

    gte_SetRotMatrix((MATRIX *)SCRPAD_ADDR);
    gte_SetTransMatrix((MATRIX *)SCRPAD_ADDR);

    matrix = (MATRIX *)(SCRPAD_ADDR + 0x40);
    obj = objs->objs;

    for (; n_obj > 0; n_obj--)
    {
        gte_ldlv0(matrix->t);
        rtv0tr();

        gte_stlvnl(&obj->screen.t);
        gte_ldclmv(matrix);
        rtir12();

        gte_stclmv(&obj->screen);
        gte_ldclmv(&matrix->m[0][1]);
        rtir12();

        gte_stclmv(&obj->screen.m[0][1]);
        gte_ldclmv(&matrix->m[0][2]);
        rtir12();

        gte_stclmv(&obj->screen.m[0][2]);
        obj++;
        matrix++;
    }
}

// set obj world accoring to parent?
void sub_8001C5CC(DG_OBJS *objs, int n_obj)
{
    DG_OBJ  *obj;
    SVECTOR *movs = objs->movs;
    MATRIX  *matrix;
    MATRIX  *matrix2;

    matrix = (MATRIX *)(SCRPAD_ADDR + 0x20);
    gte_SetRotMatrix(matrix);

    matrix2 = (MATRIX *)(SCRPAD_ADDR + 0x40);

    obj = objs->objs;
    if (n_obj <= 0)
        return;

    for (; n_obj > 0; n_obj--)
    {
        // it appears all the matrices in the scratchpad are ordered according to dg_objs
        MATRIX *parentMatrix = (MATRIX *)(SCRPAD_ADDR + 0x40);
        gte_SetTransMatrix(&parentMatrix[obj->model->parent_2C]);
        gte_ldv0(movs);
        rtv0tr();

        gte_ReadRotMatrix(matrix2);
        gte_stlvnl(matrix2->t);

        movs++;

        obj->world = *matrix2;
        obj++;
        matrix2++;
    }
}

/* //unmatching, incorrect register order
void sub_8001C708( DG_OBJS* objs, int n_obj )
{
    int i;
    DG_MDL*temp_mdl;
    MATRIX* matrix4;
    DG_OBJ* local_obj;
    MATRIX* temp_matrix;
    MATRIX* matrix  = (MATRIX*)(SCRPAD_ADDR + 0x040); //s2
    DG_OBJ* obj = objs->objs;                         //s5
    MATRIX* matrix2 = (MATRIX*)(SCRPAD_ADDR + 0x360); //0x40+var_30($sp)

    SVECTOR* rots       = objs->rots;                 //0x40+var_2C($sp)
    SVECTOR* adjust     = objs->adjust;               //s7
    SVECTOR* waist_rot  = objs->waist_rot;            //a0

    DG_MDL* mdl = obj->model;                         //s1
    MATRIX* matrix3 = (MATRIX*)(SCRPAD_ADDR + 0x340); //fp

    waist_rot ? RotMatrixZYX_gte_80093F08( waist_rot, matrix3 ) :
                RotMatrixZYX_gte_80093F08( rots,      matrix3 ) ;

    matrix3->t[0] = mdl->pos.vx;
    matrix3->t[1] = mdl->pos.vy;
    matrix3->t[2] = mdl->pos.vz;
    // *(VECTOR3*)matrix3->t = mdl->pos; //this makes matrix3 fp like we want but messes other stuff up

    if (!adjust)
    {
        matrix4 = (MATRIX*)(SCRPAD_ADDR + 0x20);
        gte_CompMatrix( matrix4, matrix3, matrix3 );

    }
    else
    {
        matrix4 = (MATRIX*)(SCRPAD_ADDR + 0x20);
        *matrix2 = *matrix4;
        *matrix4 = DG_ZeroMatrix_8009D430;
    }

    for ( i = n_obj; i > 0; i-- )
    {
        //MATRIX* parentMatrix = (MATRIX* )(SCRPAD_ADDR  + 0x40);
        temp_mdl = obj->model;
        temp_matrix = &((MATRIX* )(SCRPAD_ADDR  + 0x40))[temp_mdl->parent];
        RotMatrixZYX_gte_80093F08( rots, matrix );

        matrix->t[0] = temp_mdl->pos.vx;
        matrix->t[1] = temp_mdl->pos.vy;
        matrix->t[2] = temp_mdl->pos.vz;

        if (i == (n_obj - 1))
        {
            temp_matrix = matrix3;
        }

        gte_CompMatrix( temp_matrix, matrix, matrix );

        if (!adjust)
        {
            obj->world = *matrix;
        }
        else
        {
            if (adjust->vz) RotMatrixZ_80093D68( adjust->vz, matrix );
            if (adjust->vx) RotMatrixX_80093A28( adjust->vx, matrix );
            if (adjust->vy) RotMatrixY_80093BC8( adjust->vy, matrix );
            adjust++;
        }

        obj++;
        matrix++;
        rots++;
    }

    if (adjust)
    {
        matrix = (MATRIX* )(SCRPAD_ADDR  + 0x40);
        local_obj = objs->objs;
        gte_SetRotMatrix  ( matrix2 );
        gte_SetTransMatrix( matrix2 );

        for (i = n_obj; i > 0; i--)
        {
            gte_MulMatrix02( matrix->t, matrix, matrix );
            local_obj->world = *matrix;
            local_obj++;
            matrix++;
        }

    }
}
*/
