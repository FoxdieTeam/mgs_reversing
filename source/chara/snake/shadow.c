#include "shadow.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define SHADOW_FLAG     ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND  | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL       *root_ctrl;
    OBJECT        *root_obj;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    int            color;       // Unused
    int            enabled;
    SVECTOR        units;
} Work;

typedef struct _SCRPAD_DATA
{
    SVECTOR iter[4];
    SVECTOR rot_in;
    VECTOR  rot_out;
    MATRIX  mtx;
} SCRPAD_DATA;

/*---------------------------------------------------------------------------*/

static void RotateShadow(Work *work)
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

    SCRPAD_DATA *pScratch = (SCRPAD_DATA *)getScratchAddr(0);

    SVECTOR *iter1 = pScratch->iter;
    short *iter2 = (short *)&work->units;

    int i;

    for (i = 4; i > 0; i--, iter1++, iter2++)
    {
        pMatrix = &work->root_obj->objs->objs[*iter2].world;
        iter1->vx = pMatrix->t[0];

        pMatrix = &work->root_obj->objs->objs[*iter2].world;
        iter1->vy = pMatrix->t[1];

        pMatrix = &work->root_obj->objs->objs[*iter2].world;
        iter1->vz = pMatrix->t[2];
    }

    pScratch->mtx = work->root_obj->objs->world;

    pScratch->mtx.t[0] = work->root_obj->objs[0].objs[0].world.t[0];
    lVar9 = pScratch->mtx.t[0];

    pScratch->mtx.t[1] = work->root_obj->objs[0].objs[0].world.t[1];
    lVar5 = pScratch->mtx.t[1];

    pScratch->mtx.t[2] = work->root_obj->objs[0].objs[0].world.t[2];
    lVar4 = pScratch->mtx.t[2];

    DG_TransposeMatrix(&pScratch->mtx, &pScratch->mtx);
    SetRotMatrix(&pScratch->mtx);

    psVar14 = pScratch->iter;

    iVar17 = -32000;
    iVar15 = -32000;
    iVar16 = 32000;
    iVar12 = 32000;

    for (i = 4; i > 0; i--)
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
    }

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

static void MoveShadow(Work *work)
{
    DG_OBJS *objs = work->object.objs;

    RotMatrixY(work->root_ctrl->rot.vy, &objs->world);
    objs->world.t[0] = work->root_obj->objs->world.t[0];
    objs->world.t[2] = work->root_obj->objs->world.t[2];
    objs->world.t[1] = work->root_ctrl->levels[0];

    if ((work->root_ctrl->mov.vy - work->root_ctrl->levels[0]) < 450)
    {
        objs->objs[0].raise = -500;
    }
    else
    {
        objs->objs[0].raise = GV_NearExp8(objs->objs[0].raise, 150);
    }
}

static void Act(Work *work)
{
    if ((work->root_obj->objs->flag & DG_FLAG_INVISIBLE) || !work->enabled)
    {
        DG_InvisibleObjs(work->object.objs);
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
        RotateShadow(work);
        MoveShadow(work);
        DG_GroupObjs(work->object.objs, work->root_obj->map_name);
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);
}

static int GetResources(Work *work, CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units)
{
    GM_InitObjectNoRots(&work->object, GV_StrCode("kage"), SHADOW_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)&work->object, work->light);

    DG_GroupObjs(work->object.objs, root_obj->map_name);

    work->light[0].m[1][1] = -0x1000;
    work->light[1].m[0][1] = 0x480;
    work->light[1].m[1][1] = 0x480;
    work->light[1].m[2][1] = 0x480;
    work->light[0].t[0] = 0;
    work->light[0].t[1] = 0;
    work->light[0].t[2] = 0;

    work->object.objs->objs->model->flag |= DG_MODEL_TRANS;
    work->object.objs->objs->model->texids[0] = GV_StrCode("shadow");

    work->root_ctrl = root_ctrl;
    work->root_obj = root_obj;
    work->units = units;
    work->color = MAKE_RGBA(72, 72, 72, GPU_CODE_POLY_FT4);
    work->enabled = TRUE;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewHumanShadow(CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "shadow.c");
        if (GetResources(work, root_ctrl, root_obj, units) >= 0)
        {
            return (void *)work;
        }
        GV_DestroyActor(&work->actor);
    }
    return NULL;
}

void *NewHumanShadow2(CONTROL *root_ctrl, OBJECT *root_obj, SVECTOR units, int **enabled)
{
    Work *work;

    work = (Work *)NewHumanShadow(root_ctrl, root_obj, units);
    if (work != NULL && enabled != NULL)
    {
        *enabled = &work->enabled;
    }
    return (void *)work;
}
