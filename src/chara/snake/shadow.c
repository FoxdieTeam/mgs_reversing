#include "shadow.h"
#include "Game/object.h"
#include "psyq.h"
#include "map/map.h"

typedef struct _Shadow_Scratch
{
    SVECTOR iter[4];
    SVECTOR rot_in;
    VECTOR  rot_out;
    MATRIX  mtx;
} Shadow_Scratch;

extern MATRIX DG_ZeroMatrix_8009D430;

void shadow_act_helper_8005FD28(Actor_Shadow *pActor)
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
    short *iter2 = pActor->field_94.objs_offsets;

    int iters = 4;

    do
    {
        pMatrix = &pActor->field_24_pObj->objs->objs[*iter2].world;
        iter1->vx = pMatrix->t[0];

        pMatrix = &pActor->field_24_pObj->objs->objs[*iter2].world;
        iter1->vy = pMatrix->t[1];

        pMatrix = &pActor->field_24_pObj->objs->objs[*iter2].world;
        iter1->vz = pMatrix->t[2];

        iters--;
        iter1++;
        iter2++;
    } while (0 < iters);

    pScratch->mtx = pActor->field_24_pObj->objs->world;

    pScratch->mtx.t[0] = pActor->field_24_pObj->objs[0].objs[0].world.t[0];
    lVar9 = pScratch->mtx.t[0];

    pScratch->mtx.t[1] = pActor->field_24_pObj->objs[0].objs[0].world.t[1];
    lVar5 = pScratch->mtx.t[1];

    pScratch->mtx.t[2] = pActor->field_24_pObj->objs[0].objs[0].world.t[2];
    lVar4 = pScratch->mtx.t[2];

    DG_TransposeMatrix_8001EAD8(&pScratch->mtx, &pScratch->mtx);
    SetRotMatrix_80093218(&pScratch->mtx);

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

        ApplyRotMatrix_80092DA8(&pScratch->rot_in, &pScratch->rot_out);

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

    pWorld = &pActor->field_28_obj.objs[0].world;
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

void shadow_act_helper_80060028(Actor_Shadow *pActor)
{
    DG_OBJS *objs = pActor->field_28_obj.objs;
    RotMatrixY_80093BC8(pActor->field_20_ctrl->field_8_rotator.vy, &objs->world);
    objs->world.t[0] = pActor->field_24_pObj->objs->world.t[0];
    objs->world.t[2] = pActor->field_24_pObj->objs->world.t[2];
    objs->world.t[1] = pActor->field_20_ctrl->field_78_levels[0];

    if ((pActor->field_20_ctrl->field_0_mov.vy - pActor->field_20_ctrl->field_78_levels[0]) < 450)
    {
        objs->objs[0].raise = -500;
    }
    else
    {
        objs->objs[0].raise = GV_NearExp8_800263E4(objs->objs[0].raise, 150);
    }
}

void shadow_act_800600E4(Actor_Shadow *pActor)
{
    if ((pActor->field_24_pObj->objs->flag & DG_FLAG_INVISIBLE) || !pActor->field_90_bEnable)
    {
        DG_InvisibleObjs(pActor->field_28_obj.objs);
    }
    else
    {
        DG_VisibleObjs(pActor->field_28_obj.objs);
        shadow_act_helper_8005FD28(pActor);
        shadow_act_helper_80060028(pActor);
        DG_GroupObjs(pActor->field_28_obj.objs, pActor->field_24_pObj->map_name);
    }
}

void shadow_kill_80060190(Actor_Shadow *pActor)
{
    GM_FreeObject_80034BF8(&pActor->field_28_obj);
}

extern char aKage[];     // = "kage"
extern char aShadow_0[]; // = "shadow"

int shadow_loader_800601B0(Actor_Shadow *pActor, CONTROL *pCtrl, OBJECT *pObj, Shadow_94 field_94)
{
    int map_name;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)&pActor->field_28_obj, GV_StrCode_80016CCC(aKage), 0x16d, 0);
    GM_ConfigObjectLight_80034C44(&pActor->field_28_obj, &pActor->field_4C_mtx);

    map_name = pObj->map_name;

    pActor->field_28_obj.objs->group_id = map_name;
    pActor->field_4C_mtx.m[1][1] = -0x1000;
    pActor->field_6E = 0x480;
    pActor->field_74 = 0x480;
    pActor->field_7A = 0x480;
    pActor->field_4C_mtx.t[0] = 0;
    pActor->field_4C_mtx.t[1] = 0;
    pActor->field_4C_mtx.t[2] = 0;
    pActor->field_28_obj.objs->objs->model->flags_0 |= 2;
    *pActor->field_28_obj.objs->objs->model->materialOffset_50 = GV_StrCode_80016CCC(aShadow_0);
    pActor->field_20_ctrl = pCtrl;
    pActor->field_24_pObj = pObj;
    pActor->field_94 = field_94;
    pActor->field_8C = 0x2c484848;
    pActor->field_90_bEnable = 1;
    return 0;
}

extern const char aShadowC[]; // = "shadow.c"

Actor_Shadow *shadow_init_800602CC(CONTROL *pCtrl, OBJECT *pObj, Shadow_94 field_94)
{
    Actor_Shadow *pActor;

    pActor = (Actor_Shadow *)GV_NewActor_800150E4(5, sizeof(Actor_Shadow));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)shadow_act_800600E4,
                                  (TActorFunction)shadow_kill_80060190, aShadowC);
        if (shadow_loader_800601B0(pActor, pCtrl, pObj, field_94) >= 0)
        {
            return pActor;
        }
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
    return NULL;
}

Actor_Shadow * shadow_init2_80060384(CONTROL *pCtrl, OBJECT *pObj, Shadow_94 field_94, int **field_90_bEnable)
{
    Actor_Shadow *pActor;

    pActor = shadow_init_800602CC(pCtrl, pObj, field_94);
    if (pActor && field_90_bEnable)
    {
        *field_90_bEnable = &pActor->field_90_bEnable;
    }
    return pActor;
}
