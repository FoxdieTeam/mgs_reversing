#include "shadow.h"
#include "Game/object.h"
#include "psyq.h"
#include "Game/map.h"

typedef struct _Shadow_Scratch
{
    SVECTOR iter[4];
    SVECTOR rot_in;
    VECTOR  rot_out;
    MATRIX  mtx;
} Shadow_Scratch;

extern MATRIX DG_ZeroMatrix_8009D430;

void shadow_act_helper_8005FD28(ShadowWork *work)
{
    MATRIX *pWorld;
    MATRIX *pMatrix;

    int lVar9;
    int lVar5;
    int lVar4;

    int sVar6;
    int sVar7;

    int iVar12;

    SVECTOR *psVar14;

    int iVar15;
    int iVar16;
    int iVar17;

    Shadow_Scratch *pScratch = (Shadow_Scratch *)getScratchAddr(0);

    SVECTOR *iter1 = pScratch->iter;
    short *iter2 = (short *)&work->indices;

    int iters = 4;

    do
    {
        pMatrix = &work->field_24_pObj->objs->objs[*iter2].world;
        iter1->vx = pMatrix->t[0];

        pMatrix = &work->field_24_pObj->objs->objs[*iter2].world;
        iter1->vy = pMatrix->t[1];

        pMatrix = &work->field_24_pObj->objs->objs[*iter2].world;
        iter1->vz = pMatrix->t[2];

        iters--;
        iter1++;
        iter2++;
    } while (0 < iters);

    pScratch->mtx = work->field_24_pObj->objs->world;

    pScratch->mtx.t[0] = work->field_24_pObj->objs[0].objs[0].world.t[0];
    lVar9 = pScratch->mtx.t[0];

    pScratch->mtx.t[1] = work->field_24_pObj->objs[0].objs[0].world.t[1];
    lVar5 = pScratch->mtx.t[1];

    pScratch->mtx.t[2] = work->field_24_pObj->objs[0].objs[0].world.t[2];
    lVar4 = pScratch->mtx.t[2];

    DG_TransposeMatrix_8001EAD8(&pScratch->mtx, &pScratch->mtx);
    SetRotMatrix(&pScratch->mtx);

    psVar14 = pScratch->iter;

    iVar17 = -32000;
    iVar15 = -32000;
    iVar16 = 32000;
    iVar12 = 32000;

    iters = 4;

    do
    {
        pScratch->rot_in.vx = psVar14->vx - lVar9;
        pScratch->rot_in.vy = psVar14->vy - lVar5;
        pScratch->rot_in.vz = psVar14->vz - lVar4;

        ApplyRotMatrix(&pScratch->rot_in, &pScratch->rot_out);

        if (iVar15 < pScratch->rot_out.vx)
        {
            iVar15 = pScratch->rot_out.vx;
        }

        if (iVar12 > pScratch->rot_out.vx)
        {
            iVar12 = pScratch->rot_out.vx;
        }

        if (iVar17 < pScratch->rot_out.vz)
        {
            iVar17 = pScratch->rot_out.vz;
        }

        if (iVar16 > pScratch->rot_out.vz)
        {
            iVar16 = pScratch->rot_out.vz;
        }

        psVar14++;
        iters--;
    } while (iters > 0);

    sVar6 = (iVar15 - iVar12) / 2;
    sVar7 = (iVar17 - iVar16) / 2;

    pWorld = &work->field_28_obj.objs[0].world;
    *pWorld = DG_ZeroMatrix_8009D430;

    if (sVar7 >= 0x1f5)
    {
        sVar6 += 100;
    }
    else
    {
        sVar6 += 200;
        sVar7 += 200;
    }

    pWorld->m[0][0] = sVar6;
    pWorld->m[2][2] = sVar7;
}

void shadow_act_helper_80060028(ShadowWork *work)
{
    DG_OBJS *objs = work->field_28_obj.objs;
    RotMatrixY(work->control->rot.vy, &objs->world);
    objs->world.t[0] = work->field_24_pObj->objs->world.t[0];
    objs->world.t[2] = work->field_24_pObj->objs->world.t[2];
    objs->world.t[1] = work->control->levels[0];

    if ((work->control->mov.vy - work->control->levels[0]) < 450)
    {
        objs->objs[0].raise = -500;
    }
    else
    {
        objs->objs[0].raise = GV_NearExp8_800263E4(objs->objs[0].raise, 150);
    }
}

void shadow_act_800600E4(ShadowWork *work)
{
    if ((work->field_24_pObj->objs->flag & DG_FLAG_INVISIBLE) || !work->field_90_bEnable)
    {
        DG_InvisibleObjs(work->field_28_obj.objs);
    }
    else
    {
        DG_VisibleObjs(work->field_28_obj.objs);
        shadow_act_helper_8005FD28(work);
        shadow_act_helper_80060028(work);
        DG_GroupObjs(work->field_28_obj.objs, work->field_24_pObj->map_name);
    }
}

void shadow_kill_80060190(ShadowWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->field_28_obj);
}

int shadow_loader_800601B0(ShadowWork *work, CONTROL *pCtrl, OBJECT *pObj, SVECTOR indices)
{
    int map_name;

    GM_InitObjectNoRots_800349B0(&work->field_28_obj, GV_StrCode_80016CCC("kage"), 0x16d, 0);
    GM_ConfigObjectLight_80034C44((OBJECT *)&work->field_28_obj, work->field_4C_mtx);

    map_name = pObj->map_name;

    work->field_28_obj.objs->group_id = map_name;
    work->field_4C_mtx[0].m[1][1] = -0x1000;
    work->field_4C_mtx[1].m[0][1] = 0x480;
    work->field_4C_mtx[1].m[1][1] = 0x480;
    work->field_4C_mtx[1].m[2][1] = 0x480;
    work->field_4C_mtx[0].t[0] = 0;
    work->field_4C_mtx[0].t[1] = 0;
    work->field_4C_mtx[0].t[2] = 0;
    work->field_28_obj.objs->objs->model->flags_0 |= 2;
    *work->field_28_obj.objs->objs->model->materialOffset_50 = GV_StrCode_80016CCC("shadow");
    work->control = pCtrl;
    work->field_24_pObj = pObj;
    work->indices = indices;
    work->field_8C = 0x2c484848;
    work->field_90_bEnable = 1;
    return 0;
}

ShadowWork *shadow_init_800602CC(CONTROL *pCtrl, OBJECT *pObj, SVECTOR indices)
{
    ShadowWork *work;

    work = (ShadowWork *)GV_NewActor_800150E4(5, sizeof(ShadowWork));
    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)shadow_act_800600E4,
                                  (TActorFunction)shadow_kill_80060190, "shadow.c");
        if (shadow_loader_800601B0(work, pCtrl, pObj, indices) >= 0)
        {
            return work;
        }
        GV_DestroyActor_800151C8(&work->field_0_actor);
    }
    return NULL;
}

ShadowWork * shadow_init2_80060384(CONTROL *pCtrl, OBJECT *pObj, SVECTOR indices, int **field_90_bEnable)
{
    ShadowWork *work;

    work = shadow_init_800602CC(pCtrl, pObj, indices);
    if (work && field_90_bEnable)
    {
        *field_90_bEnable = &work->field_90_bEnable;
    }
    return work;
}
