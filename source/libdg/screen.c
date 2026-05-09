#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

typedef	struct
{
    MATRIX eye;
    MATRIX world;
    MATRIX temp[ 24 ];
    MATRIX root;
    MATRIX world2;
} ScrPad;

#define	SCRPAD  ((ScrPad *)SCRPAD_ADDR)

#define	EYE     (&(SCRPAD->eye))
#define	WORLD   (&(SCRPAD->world))
#define	TEMP    (SCRPAD->temp)
#define	ROOT    (&(SCRPAD->root))
#define	WORLD2  (&(SCRPAD->world2))

STATIC void DG_ScreenModelsSingle( DG_OBJS *objs, int n_models )
{
    DG_OBJ *obj;

    // view x world -> screen
    gte_CompMatrix(EYE, WORLD, TEMP);

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        obj->world = *WORLD;
        obj->screen = *TEMP;
        obj++;
    }
}

void DG_ScreenModels( DG_OBJS *objs, int n_models )
{
    MATRIX *screen;
    DG_OBJ *obj;

    gte_SetRotMatrix(EYE);
    gte_SetTransMatrix(EYE);

    screen = TEMP;

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

    gte_SetRotMatrix(EYE);
    gte_SetTransMatrix(EYE);

    screen = TEMP;

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

    world = WORLD;
    gte_SetRotMatrix(world);

    out = TEMP;

    obj = objs->objs;
    for (; n_models > 0; n_models--)
    {
        parent = TEMP + obj->model->parent;

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

    out = TEMP;
    obj = objs->objs;
    world = WORLD2;
    rots = objs->rots;
    adjust = objs->adjust;
    waist_rot = objs->waist_rot;
    model = obj->model;
    root = ROOT;

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
        gte_CompMatrix( WORLD, root, root );
    }
    else
    {
        *world = *WORLD;
        *WORLD = DG_ZeroMatrix;
    }

    for ( i = n_models; i > 0; i-- )
    {
        model = obj->model;
        parent = TEMP + model->parent;

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
        out = TEMP;
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

    *WORLD = objs->world;

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

    queue = chanl->queue;

    *EYE = chanl->eye_inv;
    DG_AdjustOverscan(EYE);

    for (i = chanl->objs_index; i > 0; i--)
    {
        DG_ScreenObjs(*queue++);
    }
}
