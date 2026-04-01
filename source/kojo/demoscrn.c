#include "libdg/libdg.h"

void DemoScreenModelsSingle(DG_OBJS *pObjs, int n_models)
{
    MATRIX *pMatrix;
    VECTOR *pVector;
    DG_OBJ *pObj;
    int     count;

    pMatrix = (MATRIX *)0x1F800020;
    pVector = (VECTOR *)0x1F800000;

    pMatrix->t[0] -= pVector[56].vx;
    pMatrix->t[1] -= pVector[56].vy;
    pMatrix->t[2] -= pVector[56].vz;

    gte_SetRotMatrix((MATRIX *)0x1F800000);
    gte_SetTransMatrix((MATRIX *)0x1F800000);

    ApplyRotMatrixLV((VECTOR *)0x1F800034, (VECTOR *)0x1F800054);

    gte_ldclmv(0x1F800020);
    gte_rtir();
    gte_stclmv(0x1F800040);

    gte_ldclmv(0x1F800022);
    gte_rtir();
    gte_stclmv(0x1F800042);

    gte_ldclmv(0x1F800024);
    gte_rtir();
    gte_stclmv(0x1F800044);

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        pObj->world = *(MATRIX *)0x1F800020;
        pObj->screen = *(MATRIX *)0x1F800040;
        pObj++;
    }
}

void DemoScreenModels(DG_OBJS* pObjs, int n_models)
{
    MATRIX *pMatrix;
    VECTOR *pVector;
    int     x, y, z;
    DG_OBJ *pObj;
    int     count;

    gte_SetRotMatrix((MATRIX *)0x1F800000);
    gte_SetTransMatrix((MATRIX *)0x1F800000);

    pMatrix = (MATRIX *)0x1F800040;
    pVector = (VECTOR *)0x1F800000;

    x = pVector[56].vx;
    y = pVector[56].vy;
    z = pVector[56].vz;

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        pMatrix->t[0] -= x;
        pMatrix->t[1] -= y;
        pMatrix->t[2] -= z;

        ApplyRotMatrixLV((VECTOR *)pMatrix->t, (VECTOR *)pObj->screen.t);

        gte_ldclmv(&pMatrix->m[0][0]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][0]);

        gte_ldclmv(&pMatrix->m[0][1]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][1]);

        gte_ldclmv(&pMatrix->m[0][2]);
        gte_rtir();
        gte_stclmv(&pObj->screen.m[0][2]);

        pObj++;
        pMatrix++;
    }
}

void DemoApplyMovs(DG_OBJS* pObjs, int n_models)
{
    SVECTOR *pMovs;
    MATRIX  *pMatrix;
    DG_OBJ  *pObj;
    int      count;

    pMovs = pObjs->movs;
    gte_SetRotMatrix(0x1F800020);

    pMatrix = (MATRIX *)0x1F800040;

    pObj = pObjs->objs;
    for (count = n_models; count > 0; count--)
    {
        gte_SetTransMatrix((MATRIX *)0x1F800040 + pObj->model->parent);
        gte_ldv0(pMovs);
        gte_rt();
        gte_ReadRotMatrix(pMatrix);
        gte_stlvnl((VECTOR *)pMatrix->t);

        pObj->world = *pMatrix;

        pMovs++;
        pObj++;
        pMatrix++;
    }
}

void DemoApplyRots(DG_OBJS *pObjs, int n_models)
{
    MATRIX  *pWorld;
    DG_OBJ  *pObj;
    MATRIX  *pSavedTransform;
    SVECTOR *pRots;
    SVECTOR *pWaistRot;
    SVECTOR *pAdjust;
    DG_MDL  *pMdl;
    MATRIX  *pWorkMatrix;
    int      count;
    MATRIX  *pParent;

    pWorld = (MATRIX *)0x1F800040;
    pObj = pObjs->objs;
    pSavedTransform = (MATRIX *)0x1F800360;
    pRots = pObjs->rots;
    pWaistRot = pObjs->waist_rot;
    pAdjust = pObjs->adjust;
    pMdl = pObj->model;
    pWorkMatrix = (MATRIX *)0x1F800340;

    if (pWaistRot)
    {
        RotMatrixZYX_gte(pWaistRot, pWorkMatrix);
    }
    else
    {
        RotMatrixZYX_gte(pObjs->rots, pWorkMatrix);
    }

    pWorkMatrix->t[0] = pMdl->pos.vx;
    pWorkMatrix->t[1] = pMdl->pos.vy;
    pWorkMatrix->t[2] = pMdl->pos.vz;

    if (pAdjust == NULL)
    {
        gte_CompMatrix(0x1F800020, pWorkMatrix, pWorkMatrix);

        for (count = n_models; count > 0; count--)
        {
            pMdl = pObj->model;
            pParent = (MATRIX *)0x1F800040 + pMdl->parent;

            RotMatrixZYX_gte(pRots, pWorld);

            pWorld->t[0] = pMdl->pos.vx;
            pWorld->t[1] = pMdl->pos.vy;
            pWorld->t[2] = pMdl->pos.vz;

            if (count == (n_models - 1))
            {
                gte_CompMatrix(pWorkMatrix, pWorld, pWorld);
            }
            else
            {
                gte_CompMatrix(pParent, pWorld, pWorld);
            }

            pObj->world = *pWorld;
            pObj++;
            pWorld++;
            pRots++;
        }
    }
    else
    {
        *pSavedTransform = *(MATRIX *)0x1F800020;
        *(MATRIX *)0x1F800020 = DG_ZeroMatrix;

        for (count = n_models; count > 0; count--)
        {
            pMdl = pObj->model;
            pParent = (MATRIX *)0x1F800040 + pMdl->parent;

            RotMatrixZYX_gte(pRots, pWorld);

            pWorld->t[0] = pMdl->pos.vx;
            pWorld->t[1] = pMdl->pos.vy;
            pWorld->t[2] = pMdl->pos.vz;

            if (count == (n_models - 1))
            {
                gte_CompMatrix(pWorkMatrix, pWorld, pWorld);
            }
            else
            {
                gte_CompMatrix(pParent, pWorld, pWorld);
            }

            if (pAdjust->vz != 0)
            {
                RotMatrixZ(pAdjust->vz, pWorld);
            }

            if (pAdjust->vx != 0)
            {
                RotMatrixX(pAdjust->vx, pWorld);
            }

            if (pAdjust->vy != 0)
            {
                RotMatrixY(pAdjust->vy, pWorld);
            }

            pObj++;
            pWorld++;
            pRots++;
            pAdjust++;
        }

        *(MATRIX *)0x1F800020 = *pSavedTransform;
        pWorld = (MATRIX *)0x1F800040;

        pObj = pObjs->objs;
        for (count = n_models; count > 0; count--)
        {
            gte_CompMatrix(0x1F800020, pWorld, pWorld);
            pObj->world = *pWorld;
            pObj++;
            pWorld++;
        }
    }
}

void DemoScreenObjs(DG_OBJS *pObjs)
{
    int n_models;

    n_models = pObjs->n_models;

    if (pObjs->root)
    {
        pObjs->world = *pObjs->root;
    }

    *(MATRIX *)getScratchAddr(8) = pObjs->world;

    if (pObjs->flag & DG_FLAG_ONEPIECE)
    {
        DemoScreenModelsSingle(pObjs, n_models);
        return;
    }

    if (pObjs->rots)
    {
        DemoApplyRots(pObjs, n_models);
    }
    else if (pObjs->movs)
    {
        DemoApplyMovs(pObjs, n_models);
    }

    DemoScreenModels(pObjs, n_models);
}

void DemoScreenChanl(DG_CHANL *chanl, int idx)
{
    typedef struct
    {
        MATRIX matrix;
        char   pad[0x360];
        int    translation[3];
    } SCREEN_SPAD;

    DG_OBJS    **ppObjs;
    SCREEN_SPAD *scrpad;
    int          count;

    ppObjs = chanl->queue;

    scrpad = (SCREEN_SPAD *)getScratchAddr(0);
    scrpad->matrix = chanl->eye_inv;
    scrpad->matrix.t[0] = scrpad->matrix.t[1] = scrpad->matrix.t[2] = 0;

    scrpad->translation[0] = chanl->eye.t[0];
    scrpad->translation[1] = chanl->eye.t[1];
    scrpad->translation[2] = chanl->eye.t[2];

    DG_AdjustOverscan(&scrpad->matrix);

    for (count = chanl->objs_index; count > 0; count--)
    {
        DemoScreenObjs(*ppObjs++);
    }
}
