// Not sure what this file is acutally called. Rename at a later date.
#include "common.h"
#include "libdg.h"
#include "psyq.h"

extern DG_CHANL DG_Chanls_800B1800[3];

extern MATRIX DG_ZeroMatrix;

void DG_SetPos( MATRIX *matrix )
{
    gte_SetRotMatrix(matrix);
    gte_SetTransMatrix(matrix);
}

void DG_SetPos2( SVECTOR *svector, SVECTOR *svector2 )
{
    MATRIX m;
    RotMatrixYXZ_gte(svector2, &m);

    m.t[0] = svector->vx;
    m.t[1] = svector->vy;
    m.t[2] = svector->vz;

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);
}

void DG_MovePos( SVECTOR *svector )
{
    VECTOR vec;

    gte_ldv0(svector);
    gte_rt();
    gte_stlvnl(&vec);
    gte_SetTransVector(&vec);
}

void DG_RotatePos( SVECTOR *svector )
{
    MATRIX matrix;

    RotMatrixYXZ_gte(svector, &matrix);
    MulRotMatrix(&matrix);
    gte_SetRotMatrix(&matrix);
}

void DG_PutObjs( DG_OBJS *objs )
{
    gte_ReadRotMatrix(&objs->world);
}

void DG_PutPrim( MATRIX *matrix )
{
    gte_ReadRotMatrix(matrix);
}

void DG_PutVector( SVECTOR *svector, SVECTOR *svector2, int count )
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

void DG_RotVector( SVECTOR *svector, SVECTOR *svector2, int count )
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

void DG_PersVector( SVECTOR *svector, DVECTOR *dvector, int count )
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

void DG_PointCheck( SVECTOR *svector, int n_points )
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

int DG_PointCheckOne( DVECTOR *line )
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

STATIC void DG_ScreenModelsSingle( DG_OBJS *objs, int n_models )
{
    DG_OBJ *obj;

    // view x world -> screen
    gte_CompMatrix(getScratchAddr(0), getScratchAddr(8), getScratchAddr(16));

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        obj->world = *(MATRIX *)getScratchAddr(8);
        obj->screen = *(MATRIX *)getScratchAddr(16);
        obj++;
    }
}

void DG_ScreenModels( DG_OBJS *objs, int n_models )
{
    MATRIX *screen;
    DG_OBJ *obj;

    gte_SetRotMatrix((MATRIX *)getScratchAddr(0));
    gte_SetTransMatrix((MATRIX *)getScratchAddr(0));

    screen = (MATRIX *)getScratchAddr(16);

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        DG_CompMatrix(screen, &obj->screen);
        obj++;
        screen++;
    }
}

#ifdef VR_EXE
// duplicate of DG_ScreenModels, but with added "*screen = obj->world;"
STATIC void DG_ScreenModelsUnk400( DG_OBJS *objs, int n_models )
{
    MATRIX *screen;
    DG_OBJ *obj;

    gte_SetRotMatrix((MATRIX *)getScratchAddr(0));
    gte_SetTransMatrix((MATRIX *)getScratchAddr(0));

    screen = (MATRIX *)getScratchAddr(16);

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        // Seems to destroy rots/movs for any child models
        *screen = obj->world;

        DG_CompMatrix(screen, &obj->screen);
        obj++;
        screen++;
    }
}
#endif

STATIC void DG_ApplyMovs( DG_OBJS *objs, int n_models )
{
    SVECTOR *movs;
    MATRIX  *world;
    MATRIX  *out;
    DG_OBJ  *obj;
    MATRIX  *parent;

    movs = objs->movs;

    world = (MATRIX *)getScratchAddr(8);
    gte_SetRotMatrix(world);

    out = (MATRIX *)getScratchAddr(16);

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        parent = (MATRIX *)getScratchAddr(16) + obj->model->parent;

        gte_SetTransMatrix(parent);
        gte_ldv0(movs);
        gte_rt();
        gte_ReadRotMatrix(out);
        gte_stlvnl(out->t);

        obj->world = *out;

        movs++;
        obj++;
        out++;
    }
}

STATIC void DG_ApplyRots( DG_OBJS *objs, int n_models )
{
    MATRIX  *out;
    DG_OBJ  *obj;
    MATRIX  *world;
    SVECTOR *rots;
    SVECTOR *adjust;
    SVECTOR *waist_rot;
    DG_MDL  *model;
    MATRIX  *root;
    int      i;
    MATRIX  *parent;
    MATRIX  *modelm;

    out = (MATRIX *)getScratchAddr( 16 );
    obj = objs->objs;
    world = (MATRIX *)getScratchAddr( 216 );
    rots = objs->rots;
    adjust = objs->adjust;
    waist_rot = objs->waist_rot;
    model = obj->model;
    root = (MATRIX *)getScratchAddr( 208 );

    if ( waist_rot )
    {
        RotMatrixZYX_gte( waist_rot, root );
    }
    else
    {
        RotMatrixZYX_gte( rots, root );
    }

    root->t[0] = model->pos.vx;
    root->t[1] = model->pos.vy;
    root->t[2] = model->pos.vz;

    if ( !adjust )
    {
        gte_CompMatrix( getScratchAddr( 8 ), root, root );
    }
    else
    {
        *world = *(MATRIX *)getScratchAddr( 8 );
        *(MATRIX *)getScratchAddr( 8 ) = DG_ZeroMatrix;
    }

    for ( i = n_models; i > 0; i-- )
    {
        model = obj->model;
        parent = (MATRIX *)getScratchAddr( 16 ) + model->parent;

        RotMatrixZYX_gte( rots, out );

        out->t[0] = model->pos.vx;
        out->t[1] = model->pos.vy;
        out->t[2] = model->pos.vz;

        if ( i == ( n_models - 1 ) )
        {
            modelm = root;
        }
        else
        {
            modelm = parent;
        }

        gte_CompMatrix( modelm, out, out );

        if ( !adjust )
        {
            obj->world = *out;
        }
        else
        {
            if ( adjust->vz ) RotMatrixZ( adjust->vz, out );
            if ( adjust->vx ) RotMatrixX( adjust->vx, out );
            if ( adjust->vy ) RotMatrixY( adjust->vy, out );
            adjust++;
        }

        obj++;
        out++;
        rots++;
    }

    if ( adjust )
    {
        out = (MATRIX *)getScratchAddr( 16 );
        obj = objs->objs;

        gte_SetRotMatrix( world );
        gte_SetTransMatrix( world );

        for ( i = n_models; i > 0; i-- )
        {
            DG_CompMatrix( out, out );
            obj->world = *out;
            obj++;
            out++;
        }
    }
}

STATIC void DG_ScreenObjs( DG_OBJS *objs )
{
    int n_models;

    n_models = objs->n_models;

    if (objs->root)
    {
        objs->world = *objs->root;
    }

    *(MATRIX *)getScratchAddr(8) = objs->world;

    if (objs->flag & DG_FLAG_ONEPIECE)
    {
        DG_ScreenModelsSingle(objs, n_models);
    }
#ifdef VR_EXE
    else if (objs->flag & DG_FLAG_UNKNOWN_400)
    {
        DG_ScreenModelsUnk400(objs, n_models);
    }
#endif
    else
    {
        if (objs->rots)
        {
            DG_ApplyRots(objs, n_models);
        }
        else if (objs->movs)
        {
            DG_ApplyMovs(objs, n_models);
        }

        DG_ScreenModels(objs, n_models);
    }
}

void DG_ScreenChanl( DG_CHANL *chanl, int idx )
{
    DG_OBJS **queue;
    int       i;

    queue = chanl->mQueue;

    *(MATRIX *)getScratchAddr(0) = chanl->field_10_eye_inv;
    DG_AdjustOverscan((MATRIX *)getScratchAddr(0));

    for (i = chanl->mTotalObjectCount; i > 0; i--)
    {
        DG_ScreenObjs(*queue++);
    }
}
