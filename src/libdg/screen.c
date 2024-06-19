// Not sure what this file is acutally called. Rename at a later date.
#include "linker.h"
#include "libdg.h"
#include "psyq.h"

extern DG_CHNL DG_Chanls_800B1800[3];

extern MATRIX DG_ZeroMatrix_8009D430;

#define gte_MulMatrix02(r1, r2, r3)                                                                                    \
    {                                                                                                                  \
        gte_ldlv0(r1);                                                                                                 \
        gte_rt();                                                                                                      \
        gte_stlvnl(r1);                                                                                                \
        gte_ldclmv(r2);                                                                                                \
        gte_rtir();                                                                                                    \
        gte_stclmv(r3);                                                                                                \
        gte_ldclmv((char *)r2 + 2);                                                                                    \
        gte_rtir();                                                                                                    \
        gte_stclmv((char *)r3 + 2);                                                                                    \
        gte_ldclmv((char *)r2 + 4);                                                                                    \
        gte_rtir();                                                                                                    \
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
    RotMatrixYXZ_gte(svector2, &m);

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
    gte_rt();
    gte_stlvnl(&vec);
    gte_SetTransVector(&vec);
}

void DG_RotatePos_8001BD64(SVECTOR *svector)
{
    MATRIX matrix;

    RotMatrixYXZ_gte(svector, &matrix);
    MulRotMatrix(&matrix);
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
        gte_rt();
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
        gte_rtir();
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
        gte_rtps();
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

    matrix = &DG_Chanls_800B1800[1].field_10_eye_inv;
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

int DG_PointCheckOne_8001C18C(DVECTOR *line)
{
    DVECTOR first_points;
    DVECTOR second_points;

    MATRIX *matrix = &DG_Chanls_800B1800[1].field_10_eye_inv;
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
    gte_rtir();

    gte_stclmv(&matrix[2]);
    gte_ldclmv(&matrix[1].m[0][1]);
    gte_rtir();

    gte_stclmv(&matrix[2].m[0][1]);
    gte_ldclmv(&matrix[1].m[0][2]);
    gte_rtir();

    gte_stclmv(&matrix[2].m[0][2]);

    gte_SetTransMatrix((MATRIX *)SCRPAD_ADDR);
    gte_ldlv0(&matrix[1].t);
    gte_rt();

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
        gte_rt();

        gte_stlvnl(&obj->screen.t);
        gte_ldclmv(matrix);
        gte_rtir();

        gte_stclmv(&obj->screen);
        gte_ldclmv(&matrix->m[0][1]);
        gte_rtir();

        gte_stclmv(&obj->screen.m[0][1]);
        gte_ldclmv(&matrix->m[0][2]);
        gte_rtir();

        gte_stclmv(&obj->screen.m[0][2]);
        obj++;
        matrix++;
    }
}

#ifdef VR_EXE
// duplicate of sub_8001C460, but with added "*matrix = obj->world;"
void sub_8001C540(DG_OBJS *objs, int n_obj)
{
    DG_OBJ *obj;
    MATRIX *matrix;

    gte_SetRotMatrix((MATRIX *)SCRPAD_ADDR);
    gte_SetTransMatrix((MATRIX *)SCRPAD_ADDR);

    matrix = (MATRIX *)(SCRPAD_ADDR + 0x40);
    obj = objs->objs;

    for (; n_obj > 0; n_obj--)
    {
        *matrix = obj->world; // added in this version of sub_8001C460
        gte_ldlv0(matrix->t);
        gte_rt();

        gte_stlvnl(&obj->screen.t);
        gte_ldclmv(matrix);
        gte_rtir();

        gte_stclmv(&obj->screen);
        gte_ldclmv(&matrix->m[0][1]);
        gte_rtir();

        gte_stclmv(&obj->screen.m[0][1]);
        gte_ldclmv(&matrix->m[0][2]);
        gte_rtir();

        gte_stclmv(&obj->screen.m[0][2]);
        obj++;
        matrix++;
    }
}
#endif

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
        gte_SetTransMatrix(&parentMatrix[obj->model->parent]);
        gte_ldv0(movs);
        gte_rt();

        gte_ReadRotMatrix(matrix2);
        gte_stlvnl(matrix2->t);

        movs++;

        obj->world = *matrix2;
        obj++;
        matrix2++;
    }
}

void sub_8001C708( DG_OBJS* objs, int n_obj )
{
    int i;
    MATRIX* matrix4;
    MATRIX* matrix;
    MATRIX* matrix2;
    SVECTOR* rots;
    MATRIX* matrix3;
    DG_OBJ* obj;
    SVECTOR* adjust;
    SVECTOR* waist_rot;
    void* temp_matrix;
    DG_MDL* mdl;
    DG_MDL* temp_mdl;

    matrix  = (MATRIX*)(SCRPAD_ADDR + 0x040);
    obj = objs->objs;
    matrix2 = (MATRIX*)(SCRPAD_ADDR + 0x360);

    rots       = objs->rots;
    adjust     = objs->adjust;
    waist_rot  = objs->waist_rot;

    mdl = obj->model;
    matrix3 = (MATRIX*)(SCRPAD_ADDR + 0x340);

    waist_rot ? RotMatrixZYX_gte( waist_rot, matrix3 ) :
                RotMatrixZYX_gte( rots,      matrix3 ) ;

    matrix3->t[0] = mdl->pos.vx;
    matrix3->t[1] = mdl->pos.vy;
    matrix3->t[2] = mdl->pos.vz;

    if (!adjust)
    {
        gte_CompMatrix( 0x1F800020, matrix3, matrix3 );
    }
    else
    {
        matrix4 = (MATRIX*)(SCRPAD_ADDR + 0x20);
        *matrix2 = *matrix4;
        *matrix4 = DG_ZeroMatrix_8009D430;
    }

    for ( i = n_obj; i > 0; i-- )
    {
        temp_mdl = obj->model;
        mdl = temp_mdl; //provides fake match
        temp_matrix = (void*)temp_mdl->parent;
        temp_matrix = (void*)((int)temp_matrix << 5) ;
        temp_matrix +=  SCRPAD_ADDR  + 0x40;
        //MATRIX* temp_matrix = (MATRIX* )(SCRPAD_ADDR  + 0x40);
        //temp_matrix = &temp_matrix[mdl->parent]; should be this but registers dont match
        RotMatrixZYX_gte( rots, matrix );

        matrix->t[0] = mdl->pos.vx;
        matrix->t[1] = mdl->pos.vy;
        matrix->t[2] = mdl->pos.vz;

        if ( i == ( n_obj - 1 ) )
        {
            temp_matrix = matrix3;
        }

        gte_CompMatrix( temp_matrix, matrix, matrix );

        if ( !adjust )
        {
            obj->world = *matrix;
        }
        else
        {
            if  (adjust->vz ) RotMatrixZ( adjust->vz, matrix );
            if  (adjust->vx ) RotMatrixX( adjust->vx, matrix );
            if  (adjust->vy ) RotMatrixY( adjust->vy, matrix );
            adjust++;
        }

        obj++;
        matrix++;
        rots++;
    }

    if ( adjust )
    {
        matrix = (MATRIX* )(SCRPAD_ADDR  + 0x40);
        obj = objs->objs;
        gte_SetRotMatrix  ( matrix2 );
        gte_SetTransMatrix( matrix2 );

        for ( i = n_obj; i > 0; i-- )
        {
            gte_MulMatrix02( matrix->t, matrix, matrix );
            obj->world = *matrix;
            obj++;
            matrix++;
        }
    }
}

void DG_8001CDB8(DG_OBJS *pObjs)
{
    MATRIX *root = pObjs->root;
    int     n_models = pObjs->n_models;
    if (root)
    {
        pObjs->world = *root;
    }

    *((MATRIX *)0x1F800020) = pObjs->world;

    if ((pObjs->flag & DG_FLAG_ONEPIECE) != 0)
    {
        sub_8001C248(pObjs, n_models);
    }
#ifdef VR_EXE
    else if ((pObjs->flag & DG_FLAG_UNKNOWN_400) != 0)
    {
        sub_8001C540(pObjs, n_models);
    }
#endif
    else
    {
        if (pObjs->rots)
        {
            sub_8001C708(pObjs, n_models);
        }
        else if (pObjs->movs)
        {
            sub_8001C5CC(pObjs, n_models);
        }
        sub_8001C460(pObjs, n_models);
    }
}

void DG_Screen_Chanl_8001CEE0(DG_CHNL *pOt, int idx)
{
    DG_OBJS **mQueue;
    int       i;

    mQueue = pOt->mQueue;

    *((MATRIX *)0x1F800000) = pOt->field_10_eye_inv;
    DG_800174DC((MATRIX *)0x1F800000);

    for (i = pOt->mTotalObjectCount; i > 0; --i)
    {
        DG_8001CDB8(*mQueue++);
    }
}
