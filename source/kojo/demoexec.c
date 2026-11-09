/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 
 */

/******************************************************************************
 * included
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"
#include "strcode.h"
#include "charaid.h"

#include "bullet/blast.h"
extern BLAST_DATA blast_data_8009F4B8[8];

#include "demo.h"
#include "demo_.h"
#include "common.h"
#include "kojo/m1e1.h"  // for M1E1GetCaterpillerVertex

/******************************************************************************
 * definitions and typedefs and structures
 */

#define BODY_FLAG ( DG_FLAG_SHADE | DG_FLAG_TRANS | DG_FLAG_TEXT )

/******************************************************************************
 * functions
 */

static BOOL ShowEffect(LPMGSDEMOACT lpAct, DMO_DATA_0x36* lpEffect, LPMGSDEMOEFFECTACT lpEAct);
static void KillEffect(LPMGSDEMOACT lpAct, int nEffectID);
static BOOL ShowEffectExecute(LPMGSDEMOACT lpAct, LPMGSDEMOFRAME lpDFrame, LPMGSDEMOEFFECTACT lpEAct);
static BOOL ShowEffectStop(LPMGSDEMOACT lpAct, LPMGSDEMOFRAME lpDFrame);
static BOOL ShowScene(LPMGSDEMOACT lpAct, LPMGSDEMOSCENEMOTION lpSMotion);
static void demothrd_m1e1_8007D404(LPMGSDEMOACT lpAct, LPMGSDEMOSCENEMOTION lpSMotion, LPMGSDEMOSCENE lpScene, LPMGSDEMOMODEL lpModel);
static void demothrd_hind_8007D9C8(LPMGSDEMOACT lpAct, LPMGSDEMOSCENEMOTION lpSMotion, LPMGSDEMOSCENE lpScene, LPMGSDEMOMODEL lpModel);

/* in anime/effect/m1e1.c */
extern void AN_CaterpillerSmoke(SVECTOR *pos);
extern void AN_CaterpillerSmoke2(SVECTOR *pos, SVECTOR *rot);
extern void sub_8007DC24(SVECTOR *pos);
extern void sub_8007DD80(short param_1, SVECTOR *pos);
extern void sub_8007DF10(SVECTOR *rot, SVECTOR *trans);
extern void sub_8007E0AC(int y, SVECTOR *pos);

/* in demoscrn.c */
extern void DemoScreenChanl(DG_CHANL *chanl, int idx);

/******************************************************************************
 * publics
 */

BOOL CreateDemo(
    LPMGSDEMOACT lpAct,
    LPMGSDEMO    lpDemo)
{
    MGSDEMOSTAGE *maps;
    MGSDEMOSCENE *models;
    MGSDEMOSTAGE *map;
    int         i;
    MGSDEMOMODEL *model;
    MGSDEMOSCENE *model_file;
    MATRIX     *light;

    lpAct->lpfnDGScreenChanl = DG_SetChanlSystemUnits(DG_SCREEN_CHANL, DemoScreenChanl);
    lpAct->nGameStatus = GM_GameStatus;
    lpAct->old_camera = GM_Camera;
    lpAct->nItemSave = GM_Item;
    lpAct->nWeaponSave = GM_Weapon;

    OFFSET_TO_PTR(lpDemo, &lpDemo->lpStage);
    OFFSET_TO_PTR(lpDemo, &lpDemo->lpScene);

    InitChain(&lpAct->chain);

    lpAct->lpDemo = GV_Malloc(sizeof(MGSDEMO));
    if (!lpAct->lpDemo)
    {
        return 0;
    }

    *lpAct->lpDemo = *lpDemo;
    lpAct->lpDemo->lpStage = NULL;
    lpAct->lpDemo->lpScene = NULL;

    maps = GV_Malloc((sizeof(MGSDEMOSTAGE) * lpDemo->nStageCount) | 1);
    lpAct->lpDemo->lpStage = maps;
    if (!maps)
    {
        return 0;
    }

    models = GV_Malloc((sizeof(MGSDEMOSCENE) * lpDemo->nSceneCount) | 1);
    lpAct->lpDemo->lpScene = models;
    if (!models)
    {
        return 0;
    }

    memcpy(lpAct->lpDemo->lpStage, lpDemo->lpStage, sizeof(MGSDEMOSTAGE) * lpAct->lpDemo->nStageCount);
    memcpy(lpAct->lpDemo->lpScene, lpDemo->lpScene, sizeof(MGSDEMOSCENE) * lpAct->lpDemo->nSceneCount);

    map = lpAct->lpDemo->lpStage;
    for (i = 0; i < lpAct->lpDemo->nStageCount; i++)
    {
        if (!GV_GetCache(map->nCacheID))
        {
            printf("Noload model ( Stage )\n");
            return 0;
        }

        map++;
    }

    lpAct->lpModel = GV_Malloc((sizeof(MGSDEMOMODEL) * lpAct->lpDemo->nSceneCount) | 1);
    if (!lpAct->lpModel)
    {
        return 0;
    }

    memset(lpAct->lpModel, 0, sizeof(MGSDEMOMODEL) * lpAct->lpDemo->nSceneCount);

    model_file = lpAct->lpDemo->lpScene;
    model = lpAct->lpModel;
    for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, model_file++, model++)
    {
        if (!GV_GetCache(model_file->nCacheID))
        {
            printf("Noload model ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        if (GM_InitControl(&model->control, model_file->nName, lpAct->nMap) < 0)
        {
            printf("Error init control ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        model->control.r_sphere = 0;
        model->control.interp = 0;

        if (model_file->dwStyle & 0x1)
        {
            GM_InitObject(&model->object, model_file->nStrCode, BODY_FLAG | DG_FLAG_ONEPIECE | DG_FLAG_PAINT, 0);
            continue;
        }

        if ((model_file->nStrCode == IDMODEL_16O4A)
            || (model_file->nStrCode == IDMODEL_16O5A)
            || (model_file->nStrCode == IDMODEL_16O6A)
            || (model_file->nStrCode == IDMODEL_16O7A)
            || (model_file->nStrCode == IDMODEL_16O8A)
            || (model_file->nStrCode == IDMODEL_16O9A)
            || (model_file->nStrCode == IDMODEL_16O10A)
            || (model_file->nStrCode == IDMODEL_16O4B)
            || (model_file->nStrCode == IDMODEL_16O5B)
            || (model_file->nStrCode == IDMODEL_16O6B)
            || (model_file->nStrCode == IDMODEL_16O7B)
            || (model_file->nStrCode == IDMODEL_16O8B)
            || (model_file->nStrCode == IDMODEL_16O9B)
            || (model_file->nStrCode == IDMODEL_16O10B)
            || (model_file->nStrCode == IDMODEL_16O4C)
            || (model_file->nStrCode == IDMODEL_16O5C)
            || (model_file->nStrCode == IDMODEL_16O6C)
            || (model_file->nStrCode == IDMODEL_16O7C)
            || (model_file->nStrCode == IDMODEL_16O8C)
            || (model_file->nStrCode == IDMODEL_16O9C)
            || (model_file->nStrCode == IDMODEL_16O10C))
        {
            GM_InitObject(&model->object, model_file->nStrCode, BODY_FLAG & ~DG_FLAG_SHADE, 0);
        }
        else if (model_file->nStrCode == IDMODEL_02A_R8)
        {
            model->light[0].t[0] = 100;
            model->light[0].t[1] = 110;
            model->light[0].t[2] = 110;

            GM_InitObject(&model->object, model_file->nStrCode, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else if ((model_file->nStrCode == GV_StrCode("mgrexw"))
            || (model_file->nStrCode == GV_StrCode("mgrexll"))
            || (model_file->nStrCode == GV_StrCode("mgrexrl"))
            || (model_file->nStrCode == GV_StrCode("pit_t"))
            || (model_file->nStrCode == GV_StrCode("pit_u"))
            || (model_file->nStrCode == GV_StrCode("pit_liq"))
            || (model_file->nStrCode == GV_StrCode("radar_f1"))
            || (model_file->nStrCode == GV_StrCode("radar_f2"))
            || (model_file->nStrCode == GV_StrCode("radar_f3"))
            || (model_file->nStrCode == GV_StrCode("l_hatch1"))
            || (model_file->nStrCode == GV_StrCode("l_hatch2"))
            || (model_file->nStrCode == GV_StrCode("l_hatch3"))
            || (model_file->nStrCode == GV_StrCode("l_hatch4"))
            || (model_file->nStrCode == GV_StrCode("r_hatch1"))
            || (model_file->nStrCode == GV_StrCode("r_hatch2"))
            || (model_file->nStrCode == GV_StrCode("r_hatch3"))
            || (model_file->nStrCode == GV_StrCode("r_hatch4")))
        {
            model->light[0].t[0] = 64;
            model->light[0].t[1] = 64;
            model->light[0].t[2] = 64;

            GM_InitObject(&model->object, model_file->nStrCode, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else
        {
            GM_InitObject(&model->object, model_file->nStrCode, BODY_FLAG, 0);
        }

        light = model->light;

        GM_ConfigObjectJoint(&model->object);
        GM_ConfigObjectLight(&model->object, light);

        DG_InvisibleObjs(model->object.objs);

        if (model_file->nStrCode == GV_StrCode("m1e1") || model_file->nStrCode == IDMODEL_M1E1DEMO)
        {
            model->lpData = GV_Malloc(sizeof(MGSDEMOM1E1));
            if (!model->lpData)
            {
                return 0;
            }

            memset(model->lpData, 0, sizeof(MGSDEMOM1E1));

            GM_InitObject(&model->lpData->object[0][0], GV_StrCode("m1e1cl1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->lpData->object[0][1], GV_StrCode("m1e1cl2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->lpData->object[0][2], GV_StrCode("m1e1cl3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->lpData->object[1][0], GV_StrCode("m1e1cr1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->lpData->object[1][1], GV_StrCode("m1e1cr2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->lpData->object[1][2], GV_StrCode("m1e1cr3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);

            GM_ConfigObjectJoint(&model->lpData->object[0][0]);
            GM_ConfigObjectJoint(&model->lpData->object[0][1]);
            GM_ConfigObjectJoint(&model->lpData->object[0][2]);
            GM_ConfigObjectJoint(&model->lpData->object[1][0]);
            GM_ConfigObjectJoint(&model->lpData->object[1][1]);
            GM_ConfigObjectJoint(&model->lpData->object[1][2]);

            GM_ConfigObjectLight(&model->lpData->object[0][0], light);
            GM_ConfigObjectLight(&model->lpData->object[0][1], light);
            GM_ConfigObjectLight(&model->lpData->object[0][2], light);
            GM_ConfigObjectLight(&model->lpData->object[1][0], light);
            GM_ConfigObjectLight(&model->lpData->object[1][1], light);
            GM_ConfigObjectLight(&model->lpData->object[1][2], light);

            model->lpData->field_560 = 83;
        }
        else if (model_file->nStrCode == GV_StrCode("hind") || model_file->nStrCode == IDMODEL_MI24HINDDEMO)
        {
            model->lpData = GV_Malloc(sizeof(MGSDEMOHIND));
            if (!model->lpData)
            {
                return 0;
            }

            memset(model->lpData, 0, sizeof(MGSDEMOHIND));
        }
    }

    if (!GV_GetCache(IDMODEL_CACHEEFFECT))
    {
        printf("Noload model ( null.kmd )\n");
        return 0;
    }

    if (GM_InitControl(&lpAct->control, 0, lpAct->nMap) < 0)
    {
        printf("Error init control ( null.kmd )\n");
        return 0;
    }

    lpAct->control.r_sphere = 0;
    lpAct->control.interp = 0;

    GM_InitObject(&lpAct->object, IDMODEL_EFFECT, BODY_FLAG, 0);

    GM_ConfigObjectJoint(&lpAct->object);
    GM_ConfigObjectLight(&lpAct->object, lpAct->light);

    DG_InvisibleObjs(lpAct->object.objs);

    GM_GameStatus |= STATE_DEMO;
    return 1;
}

BOOL DestroyDemo(
    LPMGSDEMOACT lpAct)
{
    MGSDEMOEFFECTACT *node;
    MGSDEMOSCENE *model_file;
    MGSDEMOMODEL *model;
    int         i;

    if (lpAct->dwStyle & 0x2)
    {
        GM_GameStatus |= STATE_DEMO_VERBOSE;
    }

    for (node = lpAct->chain.lpNext; node != &lpAct->chain; node = lpAct->chain.lpNext)
    {
        if (node->lpActor)
        {
            GV_DestroyOtherActor(node->lpActor);
        }

        if (node->lpActor2)
        {
            GV_DestroyOtherActor(node->lpActor2);
        }

        DeleteChain(&lpAct->chain, node);
        GV_Free(node);
    }

    if (lpAct->lpModel)
    {
        model_file = lpAct->lpDemo->lpScene;
        model = lpAct->lpModel;
        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, model_file++, model++)
        {
            GM_FreeObject(&model->object);

            if (model->lpData)
            {
                if (model_file->nStrCode == GV_StrCode("m1e1") || model_file->nStrCode == IDMODEL_M1E1DEMO)
                {
                    GM_FreeObject(&model->lpData->object[0][0]);
                    GM_FreeObject(&model->lpData->object[0][1]);
                    GM_FreeObject(&model->lpData->object[0][2]);
                    GM_FreeObject(&model->lpData->object[1][0]);
                    GM_FreeObject(&model->lpData->object[1][1]);
                    GM_FreeObject(&model->lpData->object[1][2]);
                }

                GV_Free(model->lpData);
            }
        }

        GM_FreeControl(&model->control);
        GV_Free(lpAct->lpModel);
    }

    GM_FreeObject(&lpAct->object);
    GM_FreeControl(&lpAct->control);

    if (lpAct->lpDemo)
    {
        if (lpAct->lpDemo->lpStage)
        {
            GV_Free(lpAct->lpDemo->lpStage);
        }

        if (lpAct->lpDemo->lpScene)
        {
            GV_Free(lpAct->lpDemo->lpScene);
        }

        GV_Free(lpAct->lpDemo);
    }

    GM_GameStatus &= ~STATE_DEMO;
    DG_SetChanlSystemUnits(DG_SCREEN_CHANL, lpAct->lpfnDGScreenChanl);
    GM_GameStatus = lpAct->nGameStatus;
    GM_Camera = lpAct->old_camera;
    GM_Item = lpAct->nItemSave;
    GM_Weapon = lpAct->nWeaponSave;
    return 1;
}

BOOL FrameRunDemo(
    LPMGSDEMOACT   lpAct,
    LPMGSDEMOFRAME lpDFrame)
{
    SVECTOR   diff;
    SVECTOR   rot;
    VECTOR    trans;
    int       radius;
    MGSDEMOEFFECTACT *node;
    MGSDEMOEFFECT *lpEffect;
    int       i;
    MGSDEMOEFFECTACT *iter;
    MGSDEMOSCENEMOTION *lpSMotion;

    OFFSET_TO_PTR(lpDFrame, &lpDFrame->lpEffect);
    OFFSET_TO_PTR(lpDFrame, &lpDFrame->lpSMotion);

    lpAct->control.mov.vx = lpDFrame->svectCamera_x;
    lpAct->control.mov.vy = lpDFrame->svectCamera_y;
    lpAct->control.mov.vz = lpDFrame->svectCamera_z;

    diff.vx = (lpDFrame->svectTarget_x - lpDFrame->svectCamera_x) >> 2;
    diff.vx = (lpDFrame->svectTarget_y - lpDFrame->svectCamera_y) >> 2;
    diff.vx = (lpDFrame->svectTarget_z - lpDFrame->svectCamera_z) >> 2;

    radius = SquareRoot0(diff.vx  * diff.vx  + diff.vz * diff.vz);
    lpAct->control.rot.vx = ratan2(diff.vy, radius);
    lpAct->control.rot.vy = ratan2(diff.vx, diff.vz);
    lpAct->control.rot.vz = lpDFrame->nZRotate;

    GM_ActControl(&lpAct->control);
    GM_ActObject2(&lpAct->object);
    DG_GetLightMatrix(&lpAct->control.mov, lpAct->light);

    lpAct->field_268 = 0;
    lpAct->field_26C = 0;

    for (node = lpAct->chain.lpNext; node != &lpAct->chain; node = node->lpNext)
    {
        node->bCheck = 0;
    }

    lpEffect = lpDFrame->lpEffect;
    for ( i = 0; i < lpDFrame->nEffectCount; i++, lpEffect++ )
    {
        node = lpAct->chain.lpNext;

        if ( node != &lpAct->chain )
        {
            do
            {
                if (node->effect.field_0 == lpEffect->field_0)
                {
                    node->bCheck = 1;
                    break;
                }

                node = node->lpNext;
            }
            while (node != &lpAct->chain);

            if ( node->effect.field_0 == lpEffect->field_0 )
            {
                continue;
            }
        }

        node = GV_Malloc(sizeof(MGSDEMOEFFECTACT));
        if ( !node )
        {
            return 1;
        }

        memset(node, 0, sizeof(MGSDEMOEFFECTACT));
        NextChain(&lpAct->chain, node);
        node->bCheck = 1;

        node->effect = *lpEffect;

        // This function uses offset 0x34 of chara despite it seemingly only being 0x34 bytes in size
        if ( !ShowEffect(lpAct, (DMO_DATA_0x36 *)lpEffect, node) )
        {
            return 0;
        }
    }

    for ( iter = lpAct->chain.lpNext; iter != &lpAct->chain; )
    {
        node = iter;
        iter = node->lpNext;

        if ( node->bCheck != 1 && !node->lpActor )
        {
            DeleteChain(&lpAct->chain, node);
            GV_Free(node);
        }
    }

    for ( node = lpAct->chain.lpNext; node != &lpAct->chain; node = node->lpNext )
    {
        if ( !ShowEffectExecute(lpAct, lpDFrame, node) )
        {
            return 0;
        }
    }

    ShowEffectStop(lpAct, lpDFrame);

    lpSMotion = lpDFrame->lpSMotion;
    for ( i = 0; i < lpDFrame->nSMotionCount; i++, lpSMotion++ )
    {
        if ( !ShowScene(lpAct, lpSMotion) )
        {
            return 0;
        }
    }

    gUnkCameraStruct2_800B7868.position.vx = lpDFrame->svectCamera_x;
    gUnkCameraStruct2_800B7868.position.vy = lpDFrame->svectCamera_y;
    gUnkCameraStruct2_800B7868.position.vz = lpDFrame->svectCamera_z;

    gUnkCameraStruct2_800B7868.target.vx = lpDFrame->svectTarget_x;
    gUnkCameraStruct2_800B7868.target.vy = lpDFrame->svectTarget_y;
    gUnkCameraStruct2_800B7868.target.vz = lpDFrame->svectTarget_z;

    DG_Chanl(0)->screen = lpDFrame->nScreen;

    diff.vx = lpDFrame->svectTarget_x - lpDFrame->svectCamera_x;
    diff.vy = lpDFrame->svectTarget_y - lpDFrame->svectCamera_y;
    diff.vz = lpDFrame->svectTarget_z - lpDFrame->svectCamera_z;

    radius = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);
    rot.vx = -ratan2(diff.vy, radius);
    rot.vy = ratan2(diff.vx, diff.vz);
    rot.vz = 2048;

    diff.vx = lpDFrame->svectCamera_x;
    diff.vy = lpDFrame->svectCamera_y;
    diff.vz = lpDFrame->svectCamera_z;

    DG_SetPos2(&diff, &rot);
    memset(&rot, 0, 8);

    rot.vz = lpDFrame->nZRotate;
    DG_RotatePos(&rot);
    ReadRotMatrix(&DG_Chanl(0)->eye);

    DG_TransposeMatrix(&DG_Chanl(0)->eye, &DG_Chanl(0)->eye_inv);

    trans.vx = -DG_Chanl(0)->eye.t[0];
    trans.vy = -DG_Chanl(0)->eye.t[1];
    trans.vz = -DG_Chanl(0)->eye.t[2];

    ApplyMatrixLV(&DG_Chanl(0)->eye_inv, &trans, (VECTOR *)DG_Chanl(0)->eye_inv.t);
    return 1;
}

/******************************************************************************
 * statics
 */

static BOOL ShowEffect(
    LPMGSDEMOACT       lpAct,
    DMO_DATA_0x36*     lpEffect,
    LPMGSDEMOEFFECTACT lpEAct)
{
    // TODO: Some funcptr calls are first cast to VoidMakeChara. This is a hack
    // to prevent those cases from being merged (GCC "cross jump" optimization).
    typedef void (*VoidMakeChara)();

    int     levels[2];
    GV_MSG  msg;
    SVECTOR svec1, svec2, svec3, svec4;
    MATRIX  mat1, mat2;
    MGSDEMOEFFECTACT *lpEActL;

    void *(*funcptr)();

    MGSDEMOSCENE *lpScene;
    MGSDEMOMODEL *pModel;
    int              hzdret;
    int              i;

    svec1.vx = lpEffect->field_E_vec2.vx;
    svec1.vy = lpEffect->field_E_vec2.vy;
    svec1.vz = lpEffect->field_E_vec2.vz;
    svec2.vx = lpEffect->field_8_vec1.vx;
    svec2.vy = lpEffect->field_8_vec1.vy;
    svec2.vz = lpEffect->field_8_vec1.vz;

    DG_SetPos2(&svec1, &DG_ZeroVector);
    ReadRotMatrix(&mat1);
    DG_SetPos2(&svec1, &svec2);
    ReadRotMatrix(&mat2);

    switch (lpEffect->field_4_type)
    {
    case EFFECT_EXPLOSION:
        funcptr = GM_GetCharaID(DEMOID_EXPLOSION);
        if (funcptr != NULL)
        {
            funcptr(&mat1, &blast_data_8009F4B8[3]);
        }
        break;

    case EFFECT_SMOKE:
        funcptr = GM_GetCharaID(DEMOID_SMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_FADEIN:
    case EFFECT_FADEOUT:
        KillEffect(lpAct, EFFECT_FADEOUT);

        switch (lpEffect->field_4_type)
        {
        case EFFECT_FADEIN:
            funcptr = GM_GetCharaID(DEMOID_FADEIN);
            if (funcptr != NULL)
            {
                if (lpEffect->data.variant_0x3.field_18 == 0)
                {
                    funcptr(1, lpEffect->data.variant_0x3.field_14);
                }
                else
                {
                    funcptr(3, lpEffect->data.variant_0x3.field_14);
                }
            }
            break;

        case EFFECT_FADEOUT:
            funcptr = GM_GetCharaID(DEMOID_FADEOUT);
            if (funcptr != NULL)
            {
                if (lpEffect->data.variant_0x4.field_18 == 0)
                {
                    lpEAct->lpActor = funcptr(0, lpEffect->data.variant_0x4.field_14);
                }
                else
                {
                    lpEAct->lpActor = funcptr(2, lpEffect->data.variant_0x4.field_14);
                }
            }
            break;
        }
        break;

    case EFFECT_TEXT:
        funcptr = GM_GetCharaID(DEMOID_TEXT);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x5.field_18,
                    lpEffect->data.variant_0x5.field_1A,
                    0,
                    lpEffect->data.variant_0x5.field_14,
                    lpEffect->data.variant_0x5.field_1C);
        }
        break;

    case EFFECT_SURPRISEDMARK:
        funcptr = GM_GetCharaID(DEMOID_SURPRISEDMARK);
        if (funcptr != NULL)
        {
            if (lpEffect->data.variant_0x6.field_14 == 0)
            {
                funcptr(&mat1, 2);
            }
            else
            {
                funcptr(&mat1, 0);
            }
        }
        break;

    case EFFECT_QUESTIONMARK:
        funcptr = GM_GetCharaID(DEMOID_QUESTIONMARK);
        if (funcptr != NULL)
        {
            if (lpEffect->data.variant_0x7.field_14 == 0)
            {
                funcptr(&mat1, 3);
            }
            else
            {
                funcptr(&mat1, 1);
            }
        }
        break;

    case EFFECT_SLEEPMARK:
        funcptr = GM_GetCharaID(DEMOID_SLEEPMARK);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_BLOOD:
        if (lpEffect->data.variant_0x9.field_14 != 4)
        {
            funcptr = GM_GetCharaID(DEMOID_BLOOD);
            if (funcptr != NULL)
            {
                funcptr(&mat2, lpEffect->data.variant_0x9.field_14);
            }
        }
        else
        {
            funcptr = GM_GetCharaID(DEMOID_BLOOD2);
            if (funcptr != NULL)
            {
                funcptr(&mat2, 0xFF);
            }
        }
        break;
    case EFFECT_BULLET:
        funcptr = GM_GetCharaID(DEMOID_BULLET);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0xA.field_14,
                    &mat2,
                    lpEffect->data.variant_0xA.field_18,
                    lpEffect->data.variant_0xA.field_1A,
                    lpEffect->data.variant_0xA.field_1C,
                    lpEffect->data.variant_0xA.field_1E,
                    lpEffect->data.variant_0xA.field_20,
                    lpEffect->data.variant_0xA.field_22,
                    lpEffect->data.variant_0xA.field_24);
        }
        break;
    case EFFECT_MISSILESMOKE:
        funcptr = GM_GetCharaID(DEMOID_MISSILESMOKE);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case EFFECT_BLOODCIRCLE:
        funcptr = GM_GetCharaID(DEMOID_BLOODCIRCLE);
        if (funcptr != NULL)
        {
            if (lpEffect->data.variant_0xC.field_14 >= 4 && lpEffect->data.variant_0xC.field_14 <= 7)
            {
                funcptr(&svec1,
                        lpEffect->data.variant_0xC.field_14,
                        lpEffect->data.variant_0xC.field_18,
                        lpEffect->data.variant_0xC.field_1C);
            }
            else
            {
                lpEAct->lpActor = funcptr(&svec1,
                                        lpEffect->data.variant_0xC.field_14,
                                        lpEffect->data.variant_0xC.field_18,
                                        lpEffect->data.variant_0xC.field_1C);
            }
        }
        break;

    case EFFECT_BREATH:
        funcptr = GM_GetCharaID(DEMOID_BREATH);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case EFFECT_SHADOW:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0xE.field_14)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        for (lpEActL = lpAct->chain.lpNext; lpEActL != &lpAct->chain; lpEActL = lpEActL->lpNext)
        {
            if (lpEActL->effect.field_4_type == 0xE && lpEActL->effect.field_14_type == lpEffect->data.variant_0xE.field_14)
            {
                if (lpEActL->lpActor)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
        }

        if (lpEffect->data.variant_0xE.field_20 != 1)
        {
            funcptr = GM_GetCharaID(DEMOID_SHADOW);
            if (funcptr != NULL)
            {
                lpEAct->lpActor =
                    funcptr(&pModel->object,
                            lpEffect->data.variant_0xE.field_18,
                            &lpEAct->nParam1,
                            &lpEAct->nParam2,
                            lpEffect->data.variant_0xE.field_22 & 0xFF,
                            lpEffect->data.variant_0xE.field_24 & 0xFF,
                            lpEffect->data.variant_0xE.field_26 & 0xFF);
            }
        }
        break;

    case EFFECT_FOOTPRINTS:
        svec1.vy += 0x64;
        hzdret = HZD_LevelHazardCheck(lpAct->control.map->hzd, &svec1, HZD_CHK_F_FLOOR);

        do {} while (0);
        HZD_GetLevelHeight(levels);

        if (hzdret & 1)
        {
            svec1.vy = levels[0];
        }

        else if (hzdret & 2)
        {
            svec1.vy = levels[1];
        }
        else
        {
            svec1.vy = lpEffect->field_E_vec2.vy;
        }

        funcptr = GM_GetCharaID(DEMOID_FOOTPRINTS);
        if (funcptr != NULL)
        {
            lpEAct->lpActor = funcptr(&mat2, lpEffect->data.variant_0xF.field_14, svec1.vy);
        }
        break;

    case EFFECT_MESSAGE:
        memset(&msg, 0, sizeof(msg));
        msg.address = lpEffect->data.variant_0x10.address;
        msg.message[0] = lpEffect->data.variant_0x10.message[0];
        msg.message[1] = lpEffect->data.variant_0x10.message[1];
        msg.message[2] = lpEffect->data.variant_0x10.message[2];
        msg.message[3] = lpEffect->data.variant_0x10.message[3];
        msg.message[4] = lpEffect->data.variant_0x10.message[4];
        msg.message[5] = lpEffect->data.variant_0x10.message[5];
        msg.message[6] = lpEffect->data.variant_0x10.message[6];
        msg.message_len = 7;
        GV_SendMessage(&msg);
        break;

    case EFFECT_NINJAEYE:
        funcptr = GM_GetCharaID(DEMOID_NINJAEYE);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&mat2);
        }
        break;

    case EFFECT_BUBBLE:
        if (lpEffect->data.variant_0x12.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_BUBBLE);
            if (funcptr != NULL)
            {
                funcptr(&svec1,
                        lpEffect->data.variant_0x12.field_20,
                        lpEffect->data.variant_0x12.field_24,
                        &lpAct->field_26C,
                        lpEffect->data.variant_0x12.field_26,
                        lpEffect->data.variant_0x12.field_28,
                        lpEffect->data.variant_0x12.field_2A);
            }
        }
        else if (lpEffect->data.variant_0x12.field_14 == 1)
        {
            svec3.vx = lpEffect->data.variant_0x12.field_16;
            svec3.vy = lpEffect->data.variant_0x12.field_18;
            svec3.vz = lpEffect->data.variant_0x12.field_1A;

            funcptr = GM_GetCharaID(DEMOID_BUBBLE2);
            if (funcptr != NULL)
            {
                funcptr(&svec1, &svec3,
                        lpEffect->data.variant_0x12.field_1C,
                        &lpAct->field_26C,
                        lpEffect->data.variant_0x12.field_26,
                        lpEffect->data.variant_0x12.field_28,
                        lpEffect->data.variant_0x12.field_2A);
            }
        }
        else
        {
            lpAct->field_26C = 1;
        }
        break;

    case EFFECT_SCOPE:
    case EFFECT_DARKVISIBLEGOGGLE:
    case EFFECT_IRRAYSGOGGLE:
    case EFFECT_GUSMASK:
        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if (lpEActL->effect.field_4_type == EFFECT_SCOPE ||
                lpEActL->effect.field_4_type == EFFECT_DARKVISIBLEGOGGLE ||
                lpEActL->effect.field_4_type == EFFECT_IRRAYSGOGGLE ||
                lpEActL->effect.field_4_type == EFFECT_GUSMASK)
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    if (lpEActL->lpActor2 != NULL)
                    {
                        GV_DestroyOtherActor(lpEActL->lpActor2);
                    }
                    lpEActL->lpActor = NULL;
                    lpEActL->lpActor2 = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        switch (lpEffect->field_4_type)
        {
        case EFFECT_SCOPE:
            if (lpEffect->data.variant_0x13.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_SCOPE);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(&lpAct->control, &lpAct->object, 0);
                }
            }
            break;

        case EFFECT_DARKVISIBLEGOGGLE:
            if (lpEffect->data.variant_0x14.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_DARKVISIBLEGOGGLE);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(&lpAct->control, &lpAct->object, 0);
                    if (lpEffect->data.variant_0x14.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID(DEMOID_DARKVISIBLEGOGGLE2);
                        if (funcptr != NULL)
                        {
                            lpEAct->lpActor2 = funcptr(5);
                        }
                    }
                }
            }
            break;

        case EFFECT_IRRAYSGOGGLE:
            if (lpEffect->data.variant_0x15.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_IRRAYSGOGGLE);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(&lpAct->control, &lpAct->object, 0);
                    if (lpEffect->data.variant_0x15.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID(DEMOID_IRRAYSGOGGLE2);
                        if (funcptr != NULL)
                        {
                            lpEAct->lpActor2 = funcptr(6);
                        }
                    }
                }
            }
            break;

        case EFFECT_GUSMASK:
            if (lpEffect->data.variant_0x1E.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_GUSMASK);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr();
                }
            }
            break;
        }
        break;

    case EFFECT_GUNSMOKE:
        funcptr = GM_GetCharaID(DEMOID_GUNSMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_OPTICSCAMOUFLAGE:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x17.field_18)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if ((lpEActL->effect.field_4_type == 0x17) && (lpEActL->effect.field_18_xy == lpEffect->data.variant_0x17.field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (lpEffect->data.variant_0x17.field_14 != 1 && lpEffect->field_4_type == 0x17)
        {
            if (lpEffect->data.variant_0x17.field_1C == 0)
            {
                funcptr = GM_GetCharaID(DEMOID_OPTICSCAMOUFLAGE);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(&lpAct->control, &pModel->object, 0);
                }
            }
            else
            {
                funcptr = GM_GetCharaID(DEMOID_OPTICSCAMOUFLAGE2);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(&lpAct->control, &pModel->object, 0);
                }
            }
        }
        break;

    case EFFECT_ENVIRONMENTMAPPING:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x18.field_18)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if ((lpEActL->effect.field_4_type == 0x18) && (lpEActL->effect.field_18_xy == lpEffect->data.variant_0x18.field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }
        if (lpEffect->data.variant_0x18.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_ENVIRONMENTMAPPING);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(&pModel->object, lpEffect->data.variant_0x18.field_1C);
            }
        }
        break;

    case EFFECT_PLASMA:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x19.field_14)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        funcptr = GM_GetCharaID(DEMOID_PLASMA);
        if (funcptr != NULL)
        {
            funcptr(&pModel->object,
                    lpEffect->data.variant_0x19.field_18,
                    lpEffect->data.variant_0x19.field_1A,
                    lpEffect->data.variant_0x19.field_1C,
                    lpEffect->data.variant_0x19.field_20);
        }
        break;

    case EFFECT_WINDCIRCLE:
        funcptr = GM_GetCharaID(DEMOID_WINDCIRCLE);
        if (funcptr != NULL)
        {
            funcptr(&mat2, lpEffect->data.variant_0x1A.field_14);
        }
        break;

    case EFFECT_SEPIA:
        KillEffect(lpAct, EFFECT_SEPIA);
        if (lpEffect->data.variant_0x1B.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_SEPIA);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(lpEffect->data.variant_0x1B.field_16,
                                        lpEffect->data.variant_0x1B.field_18,
                                        lpEffect->data.variant_0x1B.field_1A);
            }
        }
        break;

    case EFFECT_METALGEARLASER:
        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain && (lpEActL->effect.field_4_type != 0x1C || lpEActL->lpActor == NULL))
        {
            lpEActL = lpEActL->lpNext;
        }
        svec1.vx = lpEffect->data.variant_0x1C.field_14;
        svec1.vy = lpEffect->data.variant_0x1C.field_16;
        svec1.vz = lpEffect->data.variant_0x1C.field_18;
        svec2.vx = lpEffect->data.variant_0x1C.field_1A;
        svec2.vy = lpEffect->data.variant_0x1C.field_1C;
        svec2.vz = lpEffect->data.variant_0x1C.field_1E;
        if (lpEActL == &lpAct->chain)
        {
            funcptr = GM_GetCharaID(DEMOID_METALGEARLASER);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(&lpEAct->matrix);
                lpEActL = lpEAct;
            }
            else
            {
                break;
            }
        }
        DG_SetPos2(&svec1, &svec2);
        ReadRotMatrix(&lpEActL->matrix);
        break;

    case EFFECT_UNSHAPEVIEW:
        KillEffect(lpAct, EFFECT_UNSHAPEVIEW);
        if (lpEffect->data.variant_0x1D.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_UNSHAPEVIEW);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(lpEffect->data.variant_0x1D.field_18,
                                         lpEffect->data.variant_0x1D.field_1C);
            }
        }
        break;

    case EFFECT_STOP:
        lpEActL = lpAct->chain.lpNext;
        lpAct->field_268 = 1;
        lpAct->field_26C = 1;
        while (lpEActL != &lpAct->chain)
        {
            if (lpEActL->lpActor != NULL)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                if (lpEActL->lpActor2 != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor2);
                }
                lpEActL->lpActor = NULL;
                lpEActL->lpActor2 = NULL;
            }
            lpEActL = lpEActL->lpNext;
        }
        break;

    case EFFECT_URINATIONCIRCLE:    /* 失禁 */
        if (lpEffect->data.variant_0x20.field_20 == 1)
        {
            lpEActL = lpAct->chain.lpNext;
            while (lpEActL != &lpAct->chain)
            {
                if (lpEActL->effect.field_4_type == EFFECT_URINATIONCIRCLE)
                {
                    if (lpEActL->lpActor != NULL)
                    {
                        GV_DestroyOtherActor(lpEActL->lpActor);
                        lpEActL->lpActor = NULL;
                    }
                }
                lpEActL = lpEActL->lpNext;
            }
        }
        else
        {
            funcptr = GM_GetCharaID(DEMOID_URINATIONCIRCLE);
            if (funcptr != NULL)
            {
                if (lpEffect->data.variant_0x20.field_14 >= 2 && lpEffect->data.variant_0x20.field_14 <= 5)
                {
                    funcptr(&svec1,
                            lpEffect->data.variant_0x20.field_14 + 2,
                            lpEffect->data.variant_0x20.field_18,
                            lpEffect->data.variant_0x20.field_1C);
                }
                else
                {
                    lpEAct->lpActor = funcptr(&svec1,
                                        lpEffect->data.variant_0x20.field_14 + 2,
                                        lpEffect->data.variant_0x20.field_18,
                                        lpEffect->data.variant_0x20.field_1C);
                }
            }
        }
        break;

    case EFFECT_PLASMA2:
        svec3.vx = lpEffect->data.variant_0x21.field_14;
        svec3.vy = lpEffect->data.variant_0x21.field_16;
        svec3.vz = lpEffect->data.variant_0x21.field_18;
        funcptr = GM_GetCharaID(DEMOID_PLASMA2);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3, lpEffect->data.variant_0x21.field_1C);
        }
        break;

    case EFFECT_BLUR:
        KillEffect(lpAct, EFFECT_BLUR);
        if (lpEffect->data.variant_0x22.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_BLUR);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(lpEffect->data.variant_0x22.field_16,
                                         lpEffect->data.variant_0x22.field_18,
                                         lpEffect->data.variant_0x22.field_1A);
            }
        }
        break;

    case EFFECT_STEAMSMOKE:
        svec3.vx = lpEffect->data.variant_0x23.field_14;
        svec3.vy = lpEffect->data.variant_0x23.field_16;
        svec3.vz = lpEffect->data.variant_0x23.field_18;
        if (lpEffect->data.variant_0x23.field_1A != 4)
        {
            funcptr = GM_GetCharaID(DEMOID_STEAMSMOKE);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3, lpEffect->data.variant_0x23.field_1A);
            }
        }
        else
        {
            funcptr = GM_GetCharaID(DEMOID_STEAMSMOKE2);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3,
                                         lpEffect->data.variant_0x23.field_1C & 0xFF,
                                         lpEffect->data.variant_0x23.field_1E & 0xFF,
                                         lpEffect->data.variant_0x23.field_20 & 0xFF);
            }
        }
        break;

    case EFFECT_MONOTONE:
        KillEffect(lpAct, EFFECT_MONOTONE);

        if (lpEffect->data.variant_0x24.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_MONOTONE);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr();
            }
        }
        break;

    case EFFECT_RIFLESIGHT:
        KillEffect(lpAct, EFFECT_RIFLESIGHT);

        if (lpEffect->data.variant_0x25.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_RIFLESIGHT);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr();
            }
        }
        break;

    case EFFECT_MI24HIND:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nStrCode == GV_StrCode("hind"))
            {
                break;
            }
            if (lpScene->nStrCode == IDMODEL_MI24HINDDEMO)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        pModel->lpData->object[0][0].objs = lpEffect->data.variant_0x26.field_14;
        pModel->lpData->object[0][0].flag = lpEffect->data.variant_0x26.field_18;
        break;

    case EFFECT_BLACKSMOKE:
        funcptr = GM_GetCharaID(DEMOID_BLACKSMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_URINATIONCIRCLE2:
        funcptr = GM_GetCharaID(DEMOID_URINATIONCIRCLE2);
        if (funcptr != NULL)
        {
            if (lpEffect->data.variant_0x28.field_14 >= 0 && lpEffect->data.variant_0x28.field_14 <= 3)
            {
                funcptr(&svec1, lpEffect->data.variant_0x28.field_14 + 4, lpEffect->data.variant_0x28.field_18,
                        lpEffect->data.variant_0x28.field_1C);
            }
            else
            {
                lpEAct->lpActor = funcptr(&svec1,
                                         lpEffect->data.variant_0x28.field_14 + 4,
                                         lpEffect->data.variant_0x28.field_18,
                                         lpEffect->data.variant_0x28.field_1C);
            }
        }
        break;

    case EFFECT_SIGHT:
        lpEActL = lpAct->chain.lpNext;

        if (lpEActL != &lpAct->chain)
        {
            while ((lpEActL->effect.field_4_type != EFFECT_SIGHT) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == &lpAct->chain)
                {
                    break;
                }
            }
        }

        if (lpEActL == &lpAct->chain)
        {
            if (lpEffect->data.variant_0x29.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_SIGHT);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(lpEffect->data.variant_0x29.field_1C,
                                            &lpEffect->data.variant_0x29.field_16);
                }
            }
        }
        else if (lpEffect->data.variant_0x29.field_14 != 0)
        {
            if (lpEActL->effect.field_1C_zpad != lpEffect->data.variant_0x29.field_1C)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
                funcptr = GM_GetCharaID(DEMOID_SIGHT);
                if (funcptr != NULL)
                {
                    lpEAct->lpActor = funcptr(lpEffect->data.variant_0x29.field_1C,
                                            &lpEffect->data.variant_0x29.field_16);
                }
            }
            else
            {
                // TODO: I can't make sense of it (field_28 is used as an int in other places...)
                struct copier
                {
                    short a, b;
                };
                *(struct copier *)((char *)&lpEActL->effect.field_14_type + 2) = *(struct copier *)&lpEffect->data.variant_0x29.field_16;
            }
        }
        else
        {
            GV_DestroyOtherActor(lpEActL->lpActor);
            lpEActL->lpActor = NULL;
        }
        break;

    case EFFECT_NINJASWORD:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x2A.field_14)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if ((lpEActL->effect.field_4_type == EFFECT_NINJASWORD) &&
                (lpEActL->effect.field_14_type == lpEffect->data.variant_0x2A.field_14))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }
        if (lpEffect->data.variant_0x2A.field_18 != 1)
        {
            funcptr = GM_GetCharaID(DEMOID_NINJASWORD);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(&pModel->object.objs->objs[4]);
            }
        }
        break;

    case EFFECT_SUBMARINEROOM:
        lpEActL = lpAct->chain.lpNext;

        while (lpEActL != &lpAct->chain)
        {
            if (lpEActL->effect.field_4_type == EFFECT_SUBMARINEROOM)
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (lpEffect->data.variant_0x2B.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_SUBMARINEROOM);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr();
            }
        }
        break;

    case EFFECT_BLACKSMOKE2:
        svec3.vx = lpEffect->data.variant_0x2C.field_14;
        svec3.vy = lpEffect->data.variant_0x2C.field_16;
        svec3.vz = lpEffect->data.variant_0x2C.field_18;
        funcptr = GM_GetCharaID(DEMOID_BLACKSMOKE2);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3,
                    lpEffect->data.variant_0x2C.field_1A,
                    lpEffect->data.variant_0x2C.field_1C);
        }
        break;

    case EFFECT_BLASTLINE:
        svec3.vx = lpEffect->data.variant_0x2D.field_14;
        svec3.vy = lpEffect->data.variant_0x2D.field_16;
        svec3.vz = lpEffect->data.variant_0x2D.field_18;
        funcptr = GM_GetCharaID(DEMOID_BLASTLINE);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x2D.field_22,
                    lpEffect->data.variant_0x2D.field_1C,
                    lpEffect->data.variant_0x2D.field_20,
                    &svec1, &svec3);
        }
        break;

    case EFFECT_SMOKELINE:
        svec3.vx = lpEffect->data.variant_0x2E.field_14;
        svec3.vy = lpEffect->data.variant_0x2E.field_16;
        svec3.vz = lpEffect->data.variant_0x2E.field_18;
        svec4.vx = lpEffect->data.variant_0x2E.field_1A;
        svec4.vy = lpEffect->data.variant_0x2E.field_1C;
        svec4.vz = lpEffect->data.variant_0x2E.field_1E;
        funcptr = GM_GetCharaID(DEMOID_SMOKELINE);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x2E.field_26, lpEffect->data.variant_0x2E.field_20, lpEffect->data.variant_0x2E.field_24,
                    &svec1, &svec3, &svec4, lpEffect->data.variant_0x2E.field_28 & 0xFF,
                    lpEffect->data.variant_0x2E.field_2A & 0xFF, lpEffect->data.variant_0x2E.field_2C & 0xFF);
        }
        break;

    case EFFECT_SHELLSMOKE:
        funcptr = GM_GetCharaID(DEMOID_SHELLSMOKE);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x2F.field_14, &svec1, &svec2);
        }
        break;

    case EFFECT_CATERPILLERSMOKE:
        funcptr = GM_GetCharaID(DEMOID_CATERPILLERSMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec2, &svec1);
        }
        break;

    case EFFECT_CROWEYE:
        funcptr = GM_GetCharaID(DEMOID_CROWEYE);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_OCEROTTEBULLETFIRE:
        funcptr = GM_GetCharaID(DEMOID_OCEROTTEBULLETFIRE);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case EFFECT_OCEROTTEBULLETSMOKE:
        funcptr = GM_GetCharaID(DEMOID_OCEROTTEBULLETSMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case EFFECT_ENVIRONMENTLIGHT:
        svec3.vx = lpEffect->data.variant_0x34.field_24;
        svec3.vy = lpEffect->data.variant_0x34.field_26;
        svec3.vz = lpEffect->data.variant_0x34.field_28;
        svec4.vx = lpEffect->data.variant_0x34.field_2A;
        svec4.vy = lpEffect->data.variant_0x34.field_2C;
        svec4.vz = lpEffect->data.variant_0x34.field_2E;
        if (lpEffect->data.variant_0x34.field_30 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_ENVIRONMENTLIGHT);
            if (funcptr != NULL)
            {
                funcptr(lpEffect->data.variant_0x34.field_14, lpEffect->data.variant_0x34.field_18, &svec3, &svec4,
                        lpEffect->data.variant_0x34.field_1C, lpEffect->data.variant_0x34.field_20);
            }
        }
        else
        {
            memset(&msg, 0, sizeof(msg));
            msg.address = lpEffect->data.variant_0x34.field_14;
            msg.message[0] = HASH_KILL;
            msg.message_len = 1;

            GV_SendMessage(&msg);
        }
        break;

    case EFFECT_CRASHSMOKE:
        funcptr = GM_GetCharaID(DEMOID_CRASHSMOKE);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec2, lpEffect->data.variant_0x35.field_18, lpEffect->data.variant_0x35.field_1C,
                    lpEffect->data.variant_0x35.field_1E, lpEffect->data.variant_0x35.field_20,
                    lpEffect->data.variant_0x35.field_22 & 0xFF, lpEffect->data.variant_0x35.field_24 & 0xFF,
                    lpEffect->data.variant_0x35.field_26 & 0xFF);
        }
        break;

    case EFFECT_CELOFAN:
        funcptr = GM_GetCharaID(DEMOID_CELOFAN);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x37.field_14, lpEffect->data.variant_0x37.field_18, lpEffect->data.variant_0x37.field_1C,
                    lpEffect->data.variant_0x37.field_1E, lpEffect->data.variant_0x37.field_20, lpEffect->data.variant_0x37.field_22,
                    &lpEffect->data.variant_0x37.field_24, &lpEffect->data.variant_0x37.field_28, lpEffect->data.variant_0x37.field_2C,
                    lpEffect->data.variant_0x37.field_2E, lpEffect->data.variant_0x37.field_30, lpEffect->data.variant_0x37.field_32);
        }
        break;

    case EFFECT_INVERSLIGHT:
        funcptr = GM_GetCharaID(DEMOID_INVERSLIGHT);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;

    case EFFECT_SPACK:
        switch (lpEffect->data.variant_0x39.field_14)
        {
        case 0:
            funcptr = GM_GetCharaID(DEMOID_SPACK);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&mat2);
            }
            break;

        case 1:
            funcptr = GM_GetCharaID(DEMOID_SPACK2);
            if (funcptr != 0)
            {
                funcptr(&mat2, 0);
            }
            break;

        case 2:
            funcptr = GM_GetCharaID(DEMOID_SPACK2);
            if (funcptr != 0)
            {
                funcptr(&mat2, 1);
            }
            break;
        }
        break;

    case EFFECT_STEAMEXPLOSION:
        svec3.vx = lpEffect->data.variant_0x3A.field_14;
        svec3.vy = lpEffect->data.variant_0x3A.field_16;
        svec3.vz = lpEffect->data.variant_0x3A.field_18;
        funcptr = GM_GetCharaID(DEMOID_STEAMEXPLOSION);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3);
        }
        break;
    case EFFECT_INVERSLIGHT2:
        funcptr = GM_GetCharaID(DEMOID_INVERSLIGHT2);
        if (funcptr != NULL)
        {
            funcptr(&svec1, lpEffect->data.variant_0x3B.field_14, lpEffect->data.variant_0x3B.field_18,
                    lpEffect->data.variant_0x3B.field_1C, lpEffect->data.variant_0x3B.field_20, lpEffect->data.variant_0x3B.field_22,
                    lpEffect->data.variant_0x3B.field_24, lpEffect->data.variant_0x3B.field_26, lpEffect->data.variant_0x3B.field_28);
        }
        break;
    case EFFECT_CELOFAN2:
        funcptr = GM_GetCharaID(DEMOID_CELOFAN2);
        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x3C.field_14, lpEffect->data.variant_0x3C.field_18, lpEffect->data.variant_0x3C.field_1C,
                    lpEffect->data.variant_0x3C.field_1E, lpEffect->data.variant_0x3C.field_20, lpEffect->data.variant_0x3C.field_22,
                    lpEffect->data.variant_0x3C.field_24, &lpEffect->data.variant_0x3C.field_26, &lpEffect->data.variant_0x3C.field_2A,
                    lpEffect->data.variant_0x3C.field_2E, lpEffect->data.variant_0x3C.field_30, lpEffect->data.variant_0x3C.field_32,
                    lpEffect->data.variant_0x3C.field_34);
        }
        break;

    case EFFECT_NINJALASER:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x3D.field_18)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        funcptr = GM_GetCharaID(DEMOID_NINJALASER);
        if (funcptr != NULL)
        {
            funcptr(&pModel->object.objs[6].world.m[1][1], lpEffect->data.variant_0x3D.field_14,
                    lpEffect->data.variant_0x3D.field_16);
        }
        break;

    case EFFECT_GUSEFFECT:
        lpEActL = lpAct->chain.lpNext;

        if (lpEActL != &lpAct->chain)
        {
            while ((lpEActL->effect.field_4_type != EFFECT_GUSEFFECT) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == &lpAct->chain)
                {
                    break;
                }
            }
        }

        if (lpEffect->data.variant_0x3E.field_14 == 0)
        {
            if (lpEActL != &lpAct->chain)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }

            funcptr = GM_GetCharaID(DEMOID_GUSEFFECT);
            if (funcptr != NULL)
            {
                svec3.vx = lpEffect->data.variant_0x3E.field_16;
                svec3.vy = lpEffect->data.variant_0x3E.field_18;
                svec3.vz = lpEffect->data.variant_0x3E.field_1A;
                lpEAct->lpActor =
                    funcptr(&svec3, lpEffect->data.variant_0x3E.field_1E, lpEffect->data.variant_0x3E.field_1C + 1);
            }
        }
        else if (lpEffect->data.variant_0x3E.field_14 == 1)
        {
            if (lpEActL != &lpAct->chain)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }
        }
        else if (lpEffect->data.variant_0x3E.field_14 == 2)
        {
            if (lpEActL != &lpAct->chain)
            {
                memset(&msg, 0, sizeof(msg));
                msg.address = 0x3B8E;
                if (lpEffect->data.variant_0x3E.field_20 == 0)
                {
                    msg.message[0] = HASH_ON2;
                }
                else
                {
                    msg.message[0] = HASH_OFF2;
                }
                msg.message[1] = lpEffect->data.variant_0x3E.field_22;
                msg.message_len = 2;

                GV_SendMessage(&msg);
            }
        }
        break;

    case EFFECT_SUBMARINEWATER:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x3F.field_18)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if ((lpEActL->effect.field_4_type == EFFECT_SUBMARINEWATER) &&
                (lpEActL->effect.field_18_xy == lpEffect->data.variant_0x3F.field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (lpEffect->data.variant_0x3F.field_14 != 1)
        {
            funcptr = GM_GetCharaID(DEMOID_SUBMARINEWATER);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(&pModel->object, &pModel->control.rot);
            }
        }
        break;

    case EFFECT_PADVIBRATION:
    case EFFECT_PADVIBRATION2:
        if (lpEffect->data.variant_0x36.field_14 != 0)
        {
            GM_PadVibration = 1;
        }
        if (lpEffect->data.variant_0x36.field_16 != 0)
        {
            GM_PadVibration2 = lpEffect->data.variant_0x36.field_18;
        }
        break;

    case EFFECT_GHOST:
        KillEffect(lpAct, EFFECT_GHOST);
        if (lpEffect->data.variant_0x41.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_GHOST);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr();
            }
        }
        break;

    case EFFECT_LIGHT:
        DG_SetTmpLight(&svec1, lpEffect->data.variant_0x42.field_14, lpEffect->data.variant_0x42.field_16);
        break;

    case EFFECT_FAMASLIGHT:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x43.field_14)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;

        while (lpEActL != &lpAct->chain)
        {
            if ((lpEActL->effect.field_4_type == EFFECT_FAMASLIGHT) &&
                (lpEActL->effect.field_14_type == lpEffect->data.variant_0x43.field_14))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (lpEffect->data.variant_0x43.field_18 != 1)
        {
            funcptr = GM_GetCharaID(DEMOID_FAMASLIGHT);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr(pModel->object.objs + 1);
            }
        }
        break;

    case EFFECT_HUMANSHADOW:
        pModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, pModel++)
        {
            if (lpScene->nID == lpEffect->data.variant_0x44.field_18)
            {
                break;
            }
        }

        if (i >= lpAct->lpDemo->nSceneCount)
        {
            break;
        }

        lpEActL = lpAct->chain.lpNext;

        if (lpEActL != &lpAct->chain)
        {
            while ((lpEActL->effect.field_4_type != EFFECT_HUMANSHADOW) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == &lpAct->chain)
                {
                    break;
                }
            }
        }

        if (lpEActL == &lpAct->chain)
        {
            if (lpEffect->data.variant_0x44.field_14 != 1)
            {
                funcptr = GM_GetCharaID(DEMOID_HUMANSHADOW);

                if (funcptr != NULL)
                {
                    lpEAct->svect1.vx = lpEffect->data.variant_0x44.field_1E;
                    lpEAct->svect1.vy = lpEffect->data.variant_0x44.field_20;
                    lpEAct->svect1.vz = lpEffect->data.variant_0x44.field_22;

                    if (lpEffect->data.variant_0x44.field_1C == 0)
                    {
                        lpEAct->svect1.pad = 0;
                    }
                    else
                    {
                        lpEAct->svect1.pad = -1;
                    }

                    lpEAct->lpActor =
                        funcptr(pModel, &pModel->object, &lpEAct->svect1.vx, lpScene->nCacheID);
                }
            }
        }
        else if (lpEffect->data.variant_0x44.field_14 == 1)
        {
            GV_DestroyOtherActor(lpEActL->lpActor);
            lpEActL->lpActor = NULL;
        }
        else
        {
            lpEActL->svect1.vx = lpEffect->data.variant_0x44.field_1E;
            lpEActL->svect1.vy = lpEffect->data.variant_0x44.field_20;
            lpEActL->svect1.vz = lpEffect->data.variant_0x44.field_22;
        }
        break;

    case EFFECT_BLOODHAZARD:
        funcptr = GM_GetCharaID(DEMOID_BLOODHAZARD);
        if (funcptr != NULL)
        {
            lpEAct->lpActor = funcptr(&mat2,
                                    lpEffect->data.variant_0x45.field_14,
                                    lpEffect->data.variant_0x45.field_16,
                                    lpEffect->data.variant_0x45.field_18,
                                    lpEffect->data.variant_0x45.field_1A);
        }
        break;

    case EFFECT_BLOODDRIP:
        funcptr = GM_GetCharaID(DEMOID_BLOODDRIP);
        if (funcptr != NULL)
        {
            funcptr(&svec1, lpEffect->data.variant_0x46.field_14, lpEffect->data.variant_0x46.field_16);
        }
        break;

    case EFFECT_NINJAGROUND:
        funcptr = GM_GetCharaID(DEMOID_NINJAGROUND);
        if (funcptr != NULL)
        {
            funcptr(&mat2, 400, 400, 400, 10);
        }
        break;

    case EFFECT_BOMBLIGHT:
        funcptr = GM_GetCharaID(DEMOID_BOMBLIGHT);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;

    case EFFECT_MGCROOMDISPLAY:
        lpEActL = lpAct->chain.lpNext;
        while (lpEActL != &lpAct->chain)
        {
            if (lpEActL->effect.field_4_type == EFFECT_MGCROOMDISPLAY)
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (lpEffect->data.variant_0x49.field_14 == 0)
        {
            funcptr = GM_GetCharaID(DEMOID_MGCROOMDISPLAY);
            if (funcptr != NULL)
            {
                lpEAct->lpActor = funcptr();
            }
        }
        break;

    case EFFECT_TEXT2:
        funcptr = GM_GetCharaID(DEMOID_TEXT2);

        if (funcptr != NULL)
        {
            funcptr(lpEffect->data.variant_0x4A.field_18, lpEffect->data.variant_0x4A.field_1A, 0,
                    lpEffect->data.variant_0x4A.field_14, lpEffect->data.variant_0x4A.field_1C, lpEffect->data.variant_0x4A.field_20);
        }
        break;
    }

    return 1;
}

static void KillEffect(
    LPMGSDEMOACT lpAct,
    int          nEffectID)
{
    MGSDEMOEFFECTACT *pSubIter; // $s0
    MGSDEMOEFFECTACT *pCur; // $a0
    MGSDEMOEFFECTACT *pCur_; // $s1
    GV_ACT *pPrevious; // $a0
    GV_ACT *pNext; // $a0

    pSubIter = lpAct->chain.lpNext;
    pCur = &lpAct->chain;
    if ( pSubIter != pCur )
    {
        pCur_ = pCur;
        do
        {
            if ( pSubIter->effect.field_4_type == nEffectID )
            {
                pPrevious = pSubIter->lpActor;
                if ( pPrevious )
                {
                    GV_DestroyOtherActor(pPrevious);
                    pNext = pSubIter->lpActor2;
                    if ( pNext )
                    {
                        GV_DestroyOtherActor(pNext);
                    }
                    pSubIter->lpActor = NULL;
                    pSubIter->lpActor2 = NULL;
                }
            }
            pSubIter = pSubIter->lpNext;
        }
        while ( pSubIter != pCur_ );
    }
}

static BOOL ShowEffectExecute(
    LPMGSDEMOACT       lpAct,
    LPMGSDEMOFRAME     lpDFrame,
    LPMGSDEMOEFFECTACT lpEAct)
{
    MGSDEMOSCENEMOTION *lpSMotion;
    int i;
    HZD_VEC vec2;
    SVECTOR vecPos;

    if (lpEAct->effect.field_4_type == EFFECT_SHADOW)
    {
        lpSMotion = lpDFrame->lpSMotion;
        {
            for (i = 0; i < lpDFrame->nSMotionCount; i++)
            {
                if (lpSMotion->nSceneID == lpEAct->effect.field_14_type)
                {
                    break;
                }
                ++lpSMotion;
            }

            if (i < lpDFrame->nSMotionCount)
            {
                vecPos.vx = lpSMotion->svectMove_x;
                vecPos.vy = lpSMotion->svectMove_y;
                vecPos.vz = lpSMotion->svectMove_z;
                i = HZD_LevelHazardCheck(lpAct->control.map->hzd, &vecPos, HZD_CHK_F_FLOOR);
                HZD_GetLevelHeight((int *)&vec2);
                lpEAct->nParam1 = lpSMotion->svectRotate_y;
                if ((i & 1) != 0)
                {
                    lpEAct->nParam2 = vec2.x + 50;
                }
                else if ((i & 2) != 0)
                {
                    lpEAct->nParam2 = vec2.y + 50;
                }
                else
                {
                    lpEAct->nParam2 = lpSMotion->svectMove_y + 50;
                }
            }
        }
    }
    return 1;
}

static BOOL ShowEffectStop(
    LPMGSDEMOACT   lpAct,
    LPMGSDEMOFRAME lpDFrame)
{
    MGSDEMOEFFECT *lpEffect;
    int i;
    MGSDEMOEFFECTACT *pNext;
    MGSDEMOEFFECTACT *new_var;
    MGSDEMOEFFECTACT *new_var2;
    MGSDEMOEFFECTACT *root;

    lpEffect = lpDFrame->lpEffect;
    for (i = 0; i < lpDFrame->nEffectCount; ++lpEffect)
    {
        ++i;
        if (lpEffect->field_4_type == EFFECT_METALGEARLASER)
        {
            return 1;
        }
    }

    pNext = lpAct->chain.lpNext;
    new_var = &lpAct->chain;
    if (pNext != new_var)
    {
        if (pNext->effect.field_4_type != EFFECT_METALGEARLASER)
        {
            new_var2 = new_var;
            root = &lpAct->chain;
            while (1)
            {
                pNext = pNext->lpNext;
                if (pNext == new_var2)
                {
                    break;
                }
                if (pNext->effect.field_4_type == EFFECT_METALGEARLASER)
                {
                    root = &lpAct->chain;
                    break;
                }
            }
        }
    }
    if (pNext != (&lpAct->chain))
    {
        GV_DestroyOtherActor(pNext->lpActor);
        root = &lpAct->chain;
        pNext->lpActor = NULL;
        DeleteChain(root, pNext);
        GV_Free(pNext);
    }
    return 1;
}

static BOOL ShowScene(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion)
{
    MGSDEMOSCENE *lpScene;
    MGSDEMOMODEL *lpModel;
    int         i;
    short      *lpsvectRotate;

    OFFSET_TO_PTR(lpSMotion, &lpSMotion->lpsvectRotate);

    lpScene = lpAct->lpDemo->lpScene;
    lpModel = lpAct->lpModel;
    for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
    {
        if (lpScene->nID == lpSMotion->nSceneID)
        {
            break;
        }
    }

    if (i >= lpAct->lpDemo->nSceneCount)
    {
        return 0;
    }

    if (!lpSMotion->bPreview)
    {
        DG_InvisibleObjs(lpModel->object.objs);

        if (lpScene->nStrCode == GV_StrCode("m1e1") || lpScene->nStrCode == IDMODEL_M1E1DEMO)
        {
            DG_InvisibleObjs(lpModel->lpData->object[0][0].objs);
            DG_InvisibleObjs(lpModel->lpData->object[0][1].objs);
            DG_InvisibleObjs(lpModel->lpData->object[0][2].objs);
            DG_InvisibleObjs(lpModel->lpData->object[1][0].objs);
            DG_InvisibleObjs(lpModel->lpData->object[1][1].objs);
            DG_InvisibleObjs(lpModel->lpData->object[1][2].objs);
        }
    }
    else
    {
        DG_VisibleObjs(lpModel->object.objs);

        if (lpScene->nStrCode == GV_StrCode("m1e1") || lpScene->nStrCode == IDMODEL_M1E1DEMO)
        {
            DG_VisibleObjs(lpModel->lpData->object[0][lpModel->lpData->field_558_idx[0]].objs);
            DG_VisibleObjs(lpModel->lpData->object[1][lpModel->lpData->field_558_idx[1]].objs);
        }

        lpModel->control.mov.vx = lpSMotion->svectMove_x;
        lpModel->control.mov.vy = lpSMotion->svectMove_y;
        lpModel->control.mov.vz = lpSMotion->svectMove_z;
        lpModel->control.rot.vx = lpSMotion->svectRotate_x;
        lpModel->control.rot.vy = lpSMotion->svectRotate_y;
        lpModel->control.rot.vz = lpSMotion->svectRotate_z;

        if (lpScene->dwStyle & 0x1)
        {
            GM_ActControl(&lpModel->control);
            GM_ActObject2(&lpModel->object);
        }
        else
        {
            lpsvectRotate = lpSMotion->lpsvectRotate;
            for (i = 0; i < lpSMotion->nRotateCount; i++, lpsvectRotate += 3)
            {
                lpModel->object.rots[i].vx = lpsvectRotate[0];
                lpModel->object.rots[i].vy = lpsvectRotate[1];
                lpModel->object.rots[i].vz = lpsvectRotate[2];
            }

            if (lpScene->nStrCode == GV_StrCode("m1e1") || lpScene->nStrCode == IDMODEL_M1E1DEMO)
            {
                demothrd_m1e1_8007D404(lpAct, lpSMotion, lpScene, lpModel);
            }
            else if (lpScene->nStrCode == GV_StrCode("hind") || lpScene->nStrCode == IDMODEL_MI24HINDDEMO)
            {
                demothrd_hind_8007D9C8(lpAct, lpSMotion, lpScene, lpModel);
            }

            GM_ActMotion(&lpModel->object);
            GM_ActControl(&lpModel->control);
            GM_ActObject(&lpModel->object);
            DG_GetLightMatrix(&lpModel->control.mov, lpModel->light);
        }
    }

    return 1;
}

static inline int magic_calc(SVECTOR* svect1, LPMGSDEMOMODEL lpModel)
{
    int distance1 = SquareRoot0(((svect1->vx * svect1->vx) + (svect1->vy * svect1->vy)) + (svect1->vz * svect1->vz));

    int rTan1 = ratan2(svect1->vx, svect1->vz);
    int tmp4 = rTan1;
    tmp4 -= lpModel->control.rot.vy + lpModel->object.rots[0].vy;
    tmp4 = abs(tmp4);
    return (distance1 * (1024 - tmp4)) / 1024;
}

static void demothrd_m1e1_8007D404(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion,
    LPMGSDEMOSCENE       lpScene,
    LPMGSDEMOMODEL       lpModel)
{
    LPMGSDEMOM1E1 lpM1E1;
    int tmp1;
    int i;
    SVECTOR vec;
    SVECTOR vecTmp;
    SVECTOR smokeVecs[10];

    lpM1E1 = lpModel->lpData;
    for (i = 0; i < 3; i++)
    {
        GM_ActMotion(&lpM1E1->object[0][i]);
        GM_ActMotion(&lpM1E1->object[1][i]);
    }

    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);
    DG_RotatePos(lpModel->object.rots);

    M1E1GetCaterpillerVertex(&lpModel->lpData->object[0][0], &lpModel->lpData->object[1][0], smokeVecs, 1);
    for (i = 0; i < 10; i++)
    {
        smokeVecs[i].vy = smokeVecs[i].vy + 300;
    }

    DG_PutVector(smokeVecs, smokeVecs, 10);

    memset(&vec, 0, sizeof(SVECTOR));
    vec.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_PutVector(&vec, &vec, 1);

    vecTmp.vx = vec.vx - lpM1E1->field_564[0].vx;
    vecTmp.vy = vec.vy - lpM1E1->field_564[0].vy;
    vecTmp.vz = vec.vz - lpM1E1->field_564[0].vz;

    tmp1 = magic_calc(&vecTmp, lpModel);

    if (abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[rand() % 5]);
        DG_InvisibleObjs(lpM1E1->object[0][lpM1E1->field_558_idx[0]].objs);
        if (tmp1 > 0)
        {
            lpM1E1->field_558_idx[0]++;
        }
        else
        {
            lpM1E1->field_558_idx[0]--;
        }
        if (lpM1E1->field_558_idx[0] < 0)
        {
            lpM1E1->field_558_idx[0] = 2;
        }
        if (lpM1E1->field_558_idx[0] >= 3)
        {
            lpM1E1->field_558_idx[0] = 0;
        }
        DG_VisibleObjs(lpM1E1->object[0][lpM1E1->field_558_idx[0]].objs);
        lpM1E1->field_564[0] = vec;
    }

    memset(&vec, 0, sizeof(SVECTOR));
    vec.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);

    DG_PutVector(&vec, &vec, 1);
    vecTmp.vx = vec.vx - lpM1E1->field_564[1].vx;
    vecTmp.vy = vec.vy - lpM1E1->field_564[1].vy;
    vecTmp.vz = vec.vz - lpM1E1->field_564[1].vz;

    tmp1 = magic_calc(&vecTmp, lpModel);

    if (abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[(rand() % 5) + 5]);
        DG_InvisibleObjs(lpM1E1->object[1][lpM1E1->field_558_idx[1]].objs);
        if (tmp1 > 0)
        {
            lpM1E1->field_558_idx[1]++;
        }
        else
        {
            lpM1E1->field_558_idx[1]--;
        }
        if (lpM1E1->field_558_idx[1] < 0)
        {
            lpM1E1->field_558_idx[1] = 2;
        }
        if (lpM1E1->field_558_idx[1] >= 3)
        {
            lpM1E1->field_558_idx[1] = 0;
        }
        DG_VisibleObjs(lpM1E1->object[1][lpM1E1->field_558_idx[1]].objs);
        lpM1E1->field_564[1] = vec;
    }
    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);
    DG_RotatePos(lpModel->object.rots);
    for (i = 0; i < 3; i++)
    {
        GM_ActObject(&lpM1E1->object[0][i]);
        GM_ActObject(&lpM1E1->object[1][i]);
    }
}

static void demothrd_hind_8007D9C8(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion,
    LPMGSDEMOSCENE       lpScene,
    LPMGSDEMOMODEL       lpModel)
{
    LPMGSDEMOHIND lpHind = (LPMGSDEMOHIND)lpModel->lpData;

    lpHind->field_8 -= lpHind->field_0;
    if ( lpHind->field_8 < 0 )
    {
        lpHind->field_8 += 4096;
    }

    lpHind->field_C -= lpHind->field_4;
    if ( lpHind->field_C < 0 )
    {
        lpHind->field_C += 4096;
    }

    lpModel->object.rots[1].vy = lpHind->field_8;
    lpModel->object.rots[2].vx = lpHind->field_C;
}
