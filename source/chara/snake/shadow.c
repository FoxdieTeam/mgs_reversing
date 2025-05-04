#include "shadow.h"

#include "common.h"
#include "game/object.h"
#include "game/map.h"

typedef struct ShadowWork
{
    GV_ACT         actor;
    CONTROL       *control;
    OBJECT        *parent;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    int            field_8C;
    int            enabled;
    SVECTOR        indices;
} ShadowWork;

typedef struct _Shadow_Scratch
{
    SVECTOR iter[4];
    SVECTOR rot_in;
    VECTOR  rot_out;
    MATRIX  mtx;
} Shadow_Scratch;

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define SHADOW_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

void ShadowRotate_8005FD28(ShadowWork *work)
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
        pMatrix = &work->parent->objs->objs[*iter2].world;
        iter1->vx = pMatrix->t[0];

        pMatrix = &work->parent->objs->objs[*iter2].world;
        iter1->vy = pMatrix->t[1];

        pMatrix = &work->parent->objs->objs[*iter2].world;
        iter1->vz = pMatrix->t[2];

        iters--;
        iter1++;
        iter2++;
    } while (0 < iters);

    pScratch->mtx = work->parent->objs->world;

    pScratch->mtx.t[0] = work->parent->objs[0].objs[0].world.t[0];
    lVar9 = pScratch->mtx.t[0];

    pScratch->mtx.t[1] = work->parent->objs[0].objs[0].world.t[1];
    lVar5 = pScratch->mtx.t[1];

    pScratch->mtx.t[2] = work->parent->objs[0].objs[0].world.t[2];
    lVar4 = pScratch->mtx.t[2];

    DG_TransposeMatrix(&pScratch->mtx, &pScratch->mtx);
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

    pWorld = &work->object.objs[0].world;
    *pWorld = DG_ZeroMatrix;

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

void ShadowMove_80060028(ShadowWork *work)
{
    DG_OBJS *objs = work->object.objs;
    RotMatrixY(work->control->rot.vy, &objs->world);
    objs->world.t[0] = work->parent->objs->world.t[0];
    objs->world.t[2] = work->parent->objs->world.t[2];
    objs->world.t[1] = work->control->levels[0];

    if ((work->control->mov.vy - work->control->levels[0]) < 450)
    {
        objs->objs[0].raise = -500;
    }
    else
    {
        objs->objs[0].raise = GV_NearExp8(objs->objs[0].raise, 150);
    }
}

void ShadowAct_800600E4(ShadowWork *work)
{
    if ((work->parent->objs->flag & DG_FLAG_INVISIBLE) || !work->enabled)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
        ShadowRotate_8005FD28(work);
        ShadowMove_80060028(work);
        DG_GroupObjs(work->object.objs, work->parent->map_name);
    }
}

void ShadowDie_80060190(ShadowWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

int ShadowGetResources_800601B0(ShadowWork *work, CONTROL *control, OBJECT *parent, SVECTOR indices)
{
    GM_InitObjectNoRots(&work->object, GV_StrCode("kage"), SHADOW_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->object, work->light);

    DG_GroupObjs(work->object.objs, parent->map_name);

    work->light[0].m[1][1] = -0x1000;
    work->light[1].m[0][1] = 0x480;
    work->light[1].m[1][1] = 0x480;
    work->light[1].m[2][1] = 0x480;
    work->light[0].t[0] = 0;
    work->light[0].t[1] = 0;
    work->light[0].t[2] = 0;

    work->object.objs->objs->model->flags |= DG_MODEL_TRANS;
    work->object.objs->objs->model->materials[0] = GV_StrCode("shadow");

    work->control = control;
    work->parent = parent;
    work->indices = indices;
    work->field_8C = 0x2c484848;
    work->enabled = 1;

    return 0;
}

void *NewShadow_800602CC(CONTROL *control, OBJECT *parent, SVECTOR indices)
{
    ShadowWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(ShadowWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, ShadowAct_800600E4, ShadowDie_80060190, "shadow.c");
        if (ShadowGetResources_800601B0(work, control, parent, indices) >= 0)
        {
            return (void *)work;
        }
        GV_DestroyActor(&work->actor);
    }
    return NULL;
}

void *NewShadow2_80060384(CONTROL *control, OBJECT *pObj, SVECTOR indices, int **enabled)
{
    ShadowWork *work;

    work = (ShadowWork *)NewShadow_800602CC(control, pObj, indices);
    if (work && enabled)
    {
        *enabled = &work->enabled;
    }

    return (void *)work;
}
