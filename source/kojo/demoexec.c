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

static BOOL ShowEffect(LPMGSDEMOACT lpAct, LPMGSDEMOEFFECT_ lpEffect, LPMGSDEMOEFFECTACT lpEAct);
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

/******************************************************************************
 */
BOOL CreateDemo(
    LPMGSDEMOACT lpAct,
    LPMGSDEMO    lpDemo)
{
    int            i;
    LPMGSDEMOSTAGE lpStage;
    LPMGSDEMOSCENE lpScene;
    LPMGSDEMOMODEL lpModel;

    lpAct->lpfnDGScreenChanl = DG_SetChanlSystemUnits(DG_SCREEN_CHANL, DemoScreenChanl);
    lpAct->nGameStatus = GM_GameStatus;
    lpAct->GMCameraSave = GM_Camera;
    lpAct->nItemSave = GM_Item;
    lpAct->nWeaponSave = GM_Weapon;

    OFFSET_TO_PTR(lpDemo, &lpDemo->lpStage);
    OFFSET_TO_PTR(lpDemo, &lpDemo->lpScene);

    InitChain(&lpAct->lpEffectPrevious);

    if((lpAct->lpDemo = (LPMGSDEMO)GV_Malloc(sizeof(MGSDEMO))) == NULL)
        return 0;

    memcpy(lpAct->lpDemo, lpDemo, sizeof(MGSDEMO));
    lpAct->lpDemo->lpStage = NULL;
    lpAct->lpDemo->lpScene = NULL;

    if((lpAct->lpDemo->lpStage = (LPMGSDEMOSTAGE)GV_Malloc(
        (sizeof(MGSDEMOSTAGE) * lpDemo->nStageCount) | 1)) == NULL)
        return 0;
    if((lpAct->lpDemo->lpScene = (LPMGSDEMOSCENE)GV_Malloc(
        (sizeof(MGSDEMOSCENE) * lpDemo->nSceneCount) | 1)) == NULL)
        return 0;

    memcpy(lpAct->lpDemo->lpStage,
        lpDemo->lpStage, sizeof(MGSDEMOSTAGE) * lpAct->lpDemo->nStageCount);
    memcpy(lpAct->lpDemo->lpScene,
        lpDemo->lpScene, sizeof(MGSDEMOSCENE) * lpAct->lpDemo->nSceneCount);

    for(i = 0, lpStage = lpAct->lpDemo->lpStage;
        i < lpAct->lpDemo->nStageCount; i++, lpStage++)
    {
        if(GV_GetCache(lpStage->nCacheID) == NULL)
        {
            printf("Noload model ( Stage )\n");
            return 0;
        }
    }

    if((lpAct->lpModel = (LPMGSDEMOMODEL)GV_Malloc(
        (sizeof(MGSDEMOMODEL) * lpAct->lpDemo->nSceneCount) | 1)) == NULL)
        return 0;
    memset(lpAct->lpModel, 0x00,
        sizeof(MGSDEMOMODEL) * lpAct->lpDemo->nSceneCount);

    for(i = 0, lpScene = lpAct->lpDemo->lpScene, lpModel = lpAct->lpModel;
        i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
    {
        if(GV_GetCache(lpScene->nCacheID) == NULL)
        {
            printf("Noload model ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        if(GM_InitControl(&lpModel->control, lpScene->nName, lpAct->nMap) < 0)
        {
            printf("Error init control ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        lpModel->control.r_sphere = 0;
        lpModel->control.interp = 0;

        if((lpScene->dwStyle & MGS_SCENETOSTAGE) != 0)
        {
            GM_InitObject(&lpModel->object, lpScene->nStrCode,
                BODY_FLAG | DG_FLAG_ONEPIECE | DG_FLAG_PAINT, 0);
            continue;
        }

        if((lpScene->nStrCode == IDMODEL_16O4A)
            || (lpScene->nStrCode == IDMODEL_16O5A)
            || (lpScene->nStrCode == IDMODEL_16O6A)
            || (lpScene->nStrCode == IDMODEL_16O7A)
            || (lpScene->nStrCode == IDMODEL_16O8A)
            || (lpScene->nStrCode == IDMODEL_16O9A)
            || (lpScene->nStrCode == IDMODEL_16O10A)
            || (lpScene->nStrCode == IDMODEL_16O4B)
            || (lpScene->nStrCode == IDMODEL_16O5B)
            || (lpScene->nStrCode == IDMODEL_16O6B)
            || (lpScene->nStrCode == IDMODEL_16O7B)
            || (lpScene->nStrCode == IDMODEL_16O8B)
            || (lpScene->nStrCode == IDMODEL_16O9B)
            || (lpScene->nStrCode == IDMODEL_16O10B)
            || (lpScene->nStrCode == IDMODEL_16O4C)
            || (lpScene->nStrCode == IDMODEL_16O5C)
            || (lpScene->nStrCode == IDMODEL_16O6C)
            || (lpScene->nStrCode == IDMODEL_16O7C)
            || (lpScene->nStrCode == IDMODEL_16O8C)
            || (lpScene->nStrCode == IDMODEL_16O9C)
            || (lpScene->nStrCode == IDMODEL_16O10C))
        {
            GM_InitObject(&lpModel->object, lpScene->nStrCode, BODY_FLAG & ~DG_FLAG_SHADE, 0);
        }
        else if(lpScene->nStrCode == IDMODEL_02A_R8)
        {
            lpModel->light[0].t[0] = 100;
            lpModel->light[0].t[1] = 110;
            lpModel->light[0].t[2] = 110;

            GM_InitObject(&lpModel->object, lpScene->nStrCode, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else if((lpScene->nStrCode == GV_StrCode("mgrexw"))
            || (lpScene->nStrCode == GV_StrCode("mgrexll"))
            || (lpScene->nStrCode == GV_StrCode("mgrexrl"))
            || (lpScene->nStrCode == GV_StrCode("pit_t"))
            || (lpScene->nStrCode == GV_StrCode("pit_u"))
            || (lpScene->nStrCode == GV_StrCode("pit_liq"))
            || (lpScene->nStrCode == GV_StrCode("radar_f1"))
            || (lpScene->nStrCode == GV_StrCode("radar_f2"))
            || (lpScene->nStrCode == GV_StrCode("radar_f3"))
            || (lpScene->nStrCode == GV_StrCode("l_hatch1"))
            || (lpScene->nStrCode == GV_StrCode("l_hatch2"))
            || (lpScene->nStrCode == GV_StrCode("l_hatch3"))
            || (lpScene->nStrCode == GV_StrCode("l_hatch4"))
            || (lpScene->nStrCode == GV_StrCode("r_hatch1"))
            || (lpScene->nStrCode == GV_StrCode("r_hatch2"))
            || (lpScene->nStrCode == GV_StrCode("r_hatch3"))
            || (lpScene->nStrCode == GV_StrCode("r_hatch4")))
        {
            lpModel->light[0].t[0] = 64;
            lpModel->light[0].t[1] = 64;
            lpModel->light[0].t[2] = 64;

            GM_InitObject(&lpModel->object, lpScene->nStrCode, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else
        {
            GM_InitObject(&lpModel->object, lpScene->nStrCode, BODY_FLAG, 0);
        }

        GM_ConfigObjectJoint(&lpModel->object);
        GM_ConfigObjectLight(&lpModel->object, lpModel->light);

        DG_InvisibleObjs(lpModel->object.objs);

        if((lpScene->nStrCode == GV_StrCode("m1e1")) || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
        {
            if((lpModel->lpData = GV_Malloc(sizeof(MGSDEMOM1E1))) == NULL)
                return 0;
            memset(lpModel->lpData, 0x00, sizeof(MGSDEMOM1E1));

            GM_InitObject(&lpModel->lpData->object[0][0], GV_StrCode("m1e1cl1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&lpModel->lpData->object[0][1], GV_StrCode("m1e1cl2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&lpModel->lpData->object[0][2], GV_StrCode("m1e1cl3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&lpModel->lpData->object[1][0], GV_StrCode("m1e1cr1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&lpModel->lpData->object[1][1], GV_StrCode("m1e1cr2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&lpModel->lpData->object[1][2], GV_StrCode("m1e1cr3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);

            GM_ConfigObjectJoint(&lpModel->lpData->object[0][0]);
            GM_ConfigObjectJoint(&lpModel->lpData->object[0][1]);
            GM_ConfigObjectJoint(&lpModel->lpData->object[0][2]);
            GM_ConfigObjectJoint(&lpModel->lpData->object[1][0]);
            GM_ConfigObjectJoint(&lpModel->lpData->object[1][1]);
            GM_ConfigObjectJoint(&lpModel->lpData->object[1][2]);

            GM_ConfigObjectLight(&lpModel->lpData->object[0][0], lpModel->light);
            GM_ConfigObjectLight(&lpModel->lpData->object[0][1], lpModel->light);
            GM_ConfigObjectLight(&lpModel->lpData->object[0][2], lpModel->light);
            GM_ConfigObjectLight(&lpModel->lpData->object[1][0], lpModel->light);
            GM_ConfigObjectLight(&lpModel->lpData->object[1][1], lpModel->light);
            GM_ConfigObjectLight(&lpModel->lpData->object[1][2], lpModel->light);

            lpModel->lpData->field_560 = 83;
        }
        else if((lpScene->nStrCode == GV_StrCode("hind"))
            || (lpScene->nStrCode == IDMODEL_MI24HINDDEMO))
        {
            if((lpModel->lpData = GV_Malloc(sizeof(MGSDEMOHIND))) == NULL)
                return 0;
            memset(lpModel->lpData, 0x00, sizeof(MGSDEMOHIND));
        }
    }

    if(GV_GetCache(IDMODEL_CACHEEFFECT) == NULL)
    {
        printf("Noload model ( null.kmd )\n");
        return 0;
    }

    if(GM_InitControl(&lpAct->modelEffect.control, 0, lpAct->nMap) < 0)
    {
        printf("Error init control ( null.kmd )\n");
        return 0;
    }

    lpAct->modelEffect.control.r_sphere = 0;
    lpAct->modelEffect.control.interp = 0;

    GM_InitObject(&lpAct->modelEffect.object, IDMODEL_EFFECT, BODY_FLAG, 0);

    GM_ConfigObjectJoint(&lpAct->modelEffect.object);
    GM_ConfigObjectLight(&lpAct->modelEffect.object, lpAct->modelEffect.light);

    DG_InvisibleObjs(lpAct->modelEffect.object.objs);

    GM_GameStatus |= STATE_DEMO;
    return 1;
}

/******************************************************************************
 */
BOOL DestroyDemo(
    LPMGSDEMOACT lpAct)
{
    int                i;
    LPMGSDEMOEFFECTACT lpEAct;
    LPMGSDEMOSCENE     lpScene;
    LPMGSDEMOMODEL     lpModel;

    if((lpAct->dwStyle & DMT_STATEVIEWLOAD) != 0)
        GM_GameStatus |= STATE_VIEW_LOAD;

    while((lpEAct = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        if(lpEAct->lpActor != NULL)
            GV_DestroyOtherActor(lpEAct->lpActor);
        if(lpEAct->lpActor2 != NULL)
            GV_DestroyOtherActor(lpEAct->lpActor2);

        DeleteChain(&lpAct->lpEffectPrevious, &lpEAct->lpPrevious);
        GV_Free(lpEAct);
    }

    if(lpAct->lpModel != NULL)
    {
        for(i = 0, lpScene = lpAct->lpDemo->lpScene, lpModel = lpAct->lpModel;
            i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
        {
            GM_FreeObject(&lpModel->object);

            if(lpModel->lpData == NULL)
                continue;

            if((lpScene->nStrCode == GV_StrCode("m1e1")) || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
            {
                GM_FreeObject(&lpModel->lpData->object[0][0]);
                GM_FreeObject(&lpModel->lpData->object[0][1]);
                GM_FreeObject(&lpModel->lpData->object[0][2]);
                GM_FreeObject(&lpModel->lpData->object[1][0]);
                GM_FreeObject(&lpModel->lpData->object[1][1]);
                GM_FreeObject(&lpModel->lpData->object[1][2]);
            }

            GV_Free(lpModel->lpData);
        }

        GM_FreeControl(&lpModel->control);
        GV_Free(lpAct->lpModel);
    }

    GM_FreeObject(&lpAct->modelEffect.object);
    GM_FreeControl(&lpAct->modelEffect.control);

    if(lpAct->lpDemo != NULL)
    {
        if(lpAct->lpDemo->lpStage != NULL) GV_Free(lpAct->lpDemo->lpStage);
        if(lpAct->lpDemo->lpScene != NULL) GV_Free(lpAct->lpDemo->lpScene);
        GV_Free(lpAct->lpDemo);
    }

    GM_GameStatus &= ~STATE_DEMO;
    DG_SetChanlSystemUnits(DG_SCREEN_CHANL, lpAct->lpfnDGScreenChanl);
    GM_GameStatus = lpAct->nGameStatus;
    GM_Camera     = lpAct->GMCameraSave;
    GM_Item       = lpAct->nItemSave;
    GM_Weapon     = lpAct->nWeaponSave;

    return 1;
}

/******************************************************************************
 */
BOOL FrameRunDemo(
    LPMGSDEMOACT   lpAct,
    LPMGSDEMOFRAME lpDFrame)
{
    SVECTOR   diff;
    SVECTOR   rot;
    VECTOR    trans;
    int       radius;

    int                  i;
    LPMGSDEMOEFFECT      lpEffect;
    LPMGSDEMOEFFECTACT   lpEAct;
    LPMGSDEMOEFFECTACT   lpEActN;
    LPMGSDEMOSCENEMOTION lpSMotion;

    OFFSET_TO_PTR(lpDFrame, &lpDFrame->lpEffect);
    OFFSET_TO_PTR(lpDFrame, &lpDFrame->lpSMotion);

    lpAct->modelEffect.control.mov.vx = lpDFrame->svectCamera.vx;
    lpAct->modelEffect.control.mov.vy = lpDFrame->svectCamera.vy;
    lpAct->modelEffect.control.mov.vz = lpDFrame->svectCamera.vz;

    diff.vx = (lpDFrame->svectTarget.vx - lpDFrame->svectCamera.vx) >> 2;
    diff.vx = (lpDFrame->svectTarget.vy - lpDFrame->svectCamera.vy) >> 2;
    diff.vx = (lpDFrame->svectTarget.vz - lpDFrame->svectCamera.vz) >> 2;

    radius = SquareRoot0(diff.vx  * diff.vx  + diff.vz * diff.vz);
    lpAct->modelEffect.control.rot.vx = ratan2(diff.vy, radius);
    lpAct->modelEffect.control.rot.vy = ratan2(diff.vx, diff.vz);
    lpAct->modelEffect.control.rot.vz = lpDFrame->nZRotate;

    GM_ActControl(&lpAct->modelEffect.control);
    GM_ActObject2(&lpAct->modelEffect.object);
    DG_GetLightMatrix(&lpAct->modelEffect.control.mov, lpAct->modelEffect.light);

    lpAct->bEffectStop = FALSE;
    lpAct->bEffectBubbleStop = FALSE;

    if((lpEAct = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        do
            lpEAct->bCheck = FALSE;
        while((lpEAct = (LPMGSDEMOEFFECTACT)lpEAct->lpNext)
            != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);
    }

    for(i = 0, lpEffect = lpDFrame->lpEffect;
        i < lpDFrame->nEffectCount; i++, lpEffect++ )
    {
        if((lpEAct = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
            != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            do
            {
                if(lpEAct->effect.nID == lpEffect->nID)
                {
                    lpEAct->bCheck = TRUE;
                    break;
                }
            }
            while((lpEAct = (LPMGSDEMOEFFECTACT)lpEAct->lpNext)
                != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);

            if(lpEAct->effect.nID == lpEffect->nID)
                continue;
        }

        if((lpEAct = (LPMGSDEMOEFFECTACT)
            GV_Malloc(sizeof(MGSDEMOEFFECTACT))) == NULL)
            return 1;
        memset(lpEAct, 0x00, sizeof(MGSDEMOEFFECTACT));

        NextChain(&lpAct->lpEffectPrevious, &lpEAct->lpPrevious);
        lpEAct->bCheck = TRUE;
        lpEAct->effect = *lpEffect;

        // TODO: Get rid of this cast.
        if(ShowEffect(lpAct, (LPMGSDEMOEFFECT_)lpEffect, lpEAct) == 0)
            return 0;
    }

    if((lpEActN = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        do
        {
            lpEAct = lpEActN;
            lpEActN = (LPMGSDEMOEFFECTACT)lpEAct->lpNext;

            if((lpEAct->bCheck == TRUE) || (lpEAct->lpActor != NULL))
                continue;

            DeleteChain(&lpAct->lpEffectPrevious, &lpEAct->lpPrevious);
            GV_Free(lpEAct);
        }
        while(lpEActN != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);
    }

    if((lpEAct = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        do
        {
            if(ShowEffectExecute(lpAct, lpDFrame, lpEAct) == 0)
                return 0;
        }
        while((lpEAct = (LPMGSDEMOEFFECTACT)lpEAct->lpNext)
            != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);
    }

    ShowEffectStop(lpAct, lpDFrame);

    lpSMotion = lpDFrame->lpSMotion;
    for(i = 0; i < lpDFrame->nSMotionCount; i++, lpSMotion++)
    {
        if(ShowScene(lpAct, lpSMotion) == 0)
            return 0;
    }

    gUnkCameraStruct2_800B7868.position.vx = lpDFrame->svectCamera.vx;
    gUnkCameraStruct2_800B7868.position.vy = lpDFrame->svectCamera.vy;
    gUnkCameraStruct2_800B7868.position.vz = lpDFrame->svectCamera.vz;

    gUnkCameraStruct2_800B7868.target.vx = lpDFrame->svectTarget.vx;
    gUnkCameraStruct2_800B7868.target.vy = lpDFrame->svectTarget.vy;
    gUnkCameraStruct2_800B7868.target.vz = lpDFrame->svectTarget.vz;

    DG_Chanl(0)->screen = lpDFrame->nScreen;

    diff.vx = lpDFrame->svectTarget.vx - lpDFrame->svectCamera.vx;
    diff.vy = lpDFrame->svectTarget.vy - lpDFrame->svectCamera.vy;
    diff.vz = lpDFrame->svectTarget.vz - lpDFrame->svectCamera.vz;

    radius = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);
    rot.vx = -ratan2(diff.vy, radius);
    rot.vy = ratan2(diff.vx, diff.vz);
    rot.vz = 2048;

    diff.vx = lpDFrame->svectCamera.vx;
    diff.vy = lpDFrame->svectCamera.vy;
    diff.vz = lpDFrame->svectCamera.vz;

    DG_SetPos2(&diff, &rot);
    memset(&rot, 0x00, sizeof(SVECTOR));

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

/******************************************************************************
 */
static BOOL ShowEffect(
    LPMGSDEMOACT       lpAct,
    LPMGSDEMOEFFECT_   lpEffect,
    LPMGSDEMOEFFECTACT lpEAct)
{
    // TODO: Some lpfnEffect calls are first cast to VOIDCHARA. This is a hack
    // to prevent those cases from being merged (GCC "cross jump" optimization).
    typedef void (*VOIDCHARA)();

    int     lFloor[2];
    GV_MSG  gvMessage;
    SVECTOR svectMove;
    SVECTOR svectRotate;
    SVECTOR svec3, svec4;
    MATRIX  mat1, mat2;

    void *(*lpfnEffect)();

    int                i;
    LPMGSDEMOEFFECTACT lpEActL;
    LPMGSDEMOSCENE     lpScene;
    LPMGSDEMOMODEL     lpModel;

    svectMove.vx = lpEffect->svectMove.vx;
    svectMove.vy = lpEffect->svectMove.vy;
    svectMove.vz = lpEffect->svectMove.vz;
    svectRotate.vx = lpEffect->svectRotate.vx;
    svectRotate.vy = lpEffect->svectRotate.vy;
    svectRotate.vz = lpEffect->svectRotate.vz;

    DG_SetPos2(&svectMove, &DG_ZeroVector);
    ReadRotMatrix(&mat1);
    DG_SetPos2(&svectMove, &svectRotate);
    ReadRotMatrix(&mat2);

    switch (lpEffect->nEffectID)
    {
    case EFFECT_EXPLOSION:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_EXPLOSION)) != NULL)
        {
            lpfnEffect(&mat1, &blast_data_8009F4B8[3]);
        }
        break;

    case EFFECT_SMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SMOKE)) != NULL)
        {
            lpfnEffect(&svectMove);
        }
        break;

    case EFFECT_FADEIN:
    case EFFECT_FADEOUT:
        KillEffect(lpAct, EFFECT_FADEOUT);

        switch (lpEffect->nEffectID)
        {
        case EFFECT_FADEIN:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_FADEIN)) != NULL)
            {
                if (lpEffect->data.variant_0x3.field_18 == 0)
                    lpfnEffect(1, lpEffect->data.variant_0x3.field_14);
                else
                    lpfnEffect(3, lpEffect->data.variant_0x3.field_14);
            }
            break;

        case EFFECT_FADEOUT:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_FADEOUT)) != NULL)
            {
                if (lpEffect->data.variant_0x4.field_18 == 0)
                    lpEAct->lpActor = lpfnEffect(0, lpEffect->data.variant_0x4.field_14);
                else
                    lpEAct->lpActor = lpfnEffect(2, lpEffect->data.variant_0x4.field_14);
            }
            break;
        }
        break;

    case EFFECT_TEXT:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_TEXT)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0x5.field_18,
                lpEffect->data.variant_0x5.field_1A,
                0,
                lpEffect->data.variant_0x5.field_14,
                lpEffect->data.variant_0x5.field_1C);
        }
        break;

    case EFFECT_SURPRISEDMARK:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SURPRISEDMARK)) != NULL)
        {
            if (lpEffect->data.variant_0x6.field_14 == 0)
                lpfnEffect(&mat1, 2);
            else
                lpfnEffect(&mat1, 0);
        }
        break;

    case EFFECT_QUESTIONMARK:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_QUESTIONMARK)) != NULL)
        {
            if (lpEffect->data.variant_0x7.field_14 == 0)
                lpfnEffect(&mat1, 3);
            else
                lpfnEffect(&mat1, 1);
        }
        break;

    case EFFECT_SLEEPMARK:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SLEEPMARK)) != NULL)
        {
            lpfnEffect(&svectMove);
        }
        break;

    case EFFECT_BLOOD:
        if (lpEffect->data.variant_0x9.field_14 != 4)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOOD)) != NULL)
            {
                lpfnEffect(&mat2, lpEffect->data.variant_0x9.field_14);
            }
        }
        else
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOOD2)) != NULL)
            {
                lpfnEffect(&mat2, 0xFF);
            }
        }
        break;
    case EFFECT_BULLET:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BULLET)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0xA.field_14,
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
        if ((lpfnEffect = GM_GetCharaID(DEMOID_MISSILESMOKE)) != NULL)
        {
            lpfnEffect(&mat2);
        }
        break;

    case EFFECT_BLOODCIRCLE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOODCIRCLE)) != NULL)
        {
            if (lpEffect->data.variant_0xC.field_14 >= 4 && lpEffect->data.variant_0xC.field_14 <= 7)
            {
                lpfnEffect(&svectMove,
                    lpEffect->data.variant_0xC.field_14,
                    lpEffect->data.variant_0xC.field_18,
                    lpEffect->data.variant_0xC.field_1C);
            }
            else
            {
                lpEAct->lpActor = lpfnEffect(&svectMove,
                                        lpEffect->data.variant_0xC.field_14,
                                        lpEffect->data.variant_0xC.field_18,
                                        lpEffect->data.variant_0xC.field_1C);
            }
        }
        break;

    case EFFECT_BREATH:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BREATH)) != NULL)
        {
            lpfnEffect(&mat2);
        }
        break;

    case EFFECT_SHADOW:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        for (lpEActL = lpAct->lpEffectNext;
            lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious;
            lpEActL = lpEActL->lpNext)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_SHADOW)
                && (lpEActL->effect.field_14_type == lpEffect->data.variant_0xE.field_14))
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SHADOW)) != NULL)
            {
                lpEAct->lpActor =
                    lpfnEffect(
                        &lpModel->object,
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
        svectMove.vy += 0x64;
        i = HZD_LevelHazardCheck(
            lpAct->modelEffect.control.map->hzd, &svectMove, HZD_CHK_F_FLOOR);
        do {} while (0);
        HZD_GetLevelHeight(lFloor);
             if (i & 1) svectMove.vy = lFloor[0];
        else if (i & 2) svectMove.vy = lFloor[1];
        else svectMove.vy = lpEffect->svectMove.vy;

        if ((lpfnEffect = GM_GetCharaID(DEMOID_FOOTPRINTS)) != NULL)
        {
            lpEAct->lpActor = lpfnEffect(&mat2, lpEffect->data.variant_0xF.field_14, svectMove.vy);
        }
        break;

    case EFFECT_MESSAGE:
        memset(&gvMessage, 0x00, sizeof(gvMessage));
        gvMessage.address = lpEffect->data.variant_0x10.address;
        gvMessage.message[0] = lpEffect->data.variant_0x10.message[0];
        gvMessage.message[1] = lpEffect->data.variant_0x10.message[1];
        gvMessage.message[2] = lpEffect->data.variant_0x10.message[2];
        gvMessage.message[3] = lpEffect->data.variant_0x10.message[3];
        gvMessage.message[4] = lpEffect->data.variant_0x10.message[4];
        gvMessage.message[5] = lpEffect->data.variant_0x10.message[5];
        gvMessage.message[6] = lpEffect->data.variant_0x10.message[6];
        gvMessage.message_len = 7;
        GV_SendMessage(&gvMessage);
        break;

    case EFFECT_NINJAEYE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_NINJAEYE)) != NULL)
        {
            ((VOIDCHARA)lpfnEffect)(&mat2);
        }
        break;

    case EFFECT_BUBBLE:
        if (lpEffect->data.variant_0x12.field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BUBBLE)) != NULL)
            {
                lpfnEffect(&svectMove,
                    lpEffect->data.variant_0x12.field_20,
                    lpEffect->data.variant_0x12.field_24,
                    &lpAct->bEffectBubbleStop,
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

            if ((lpfnEffect = GM_GetCharaID(DEMOID_BUBBLE2)) != NULL)
            {
                lpfnEffect(&svectMove, &svec3,
                    lpEffect->data.variant_0x12.field_1C,
                    &lpAct->bEffectBubbleStop,
                    lpEffect->data.variant_0x12.field_26,
                    lpEffect->data.variant_0x12.field_28,
                    lpEffect->data.variant_0x12.field_2A);
            }
        }
        else
        {
            lpAct->bEffectBubbleStop = TRUE;
        }
        break;

    case EFFECT_SCOPE:
    case EFFECT_DARKVISIBLEGOGGLE:
    case EFFECT_IRRAYSGOGGLE:
    case EFFECT_GUSMASK:
        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_SCOPE) ||
                (lpEActL->effect.nEffectID == EFFECT_DARKVISIBLEGOGGLE) ||
                (lpEActL->effect.nEffectID == EFFECT_IRRAYSGOGGLE) ||
                (lpEActL->effect.nEffectID == EFFECT_GUSMASK))
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

        switch (lpEffect->nEffectID)
        {
        case EFFECT_SCOPE:
            if (lpEffect->data.variant_0x13.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SCOPE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(&lpAct->modelEffect.control,
                                              &lpAct->modelEffect.object, 0);
                }
            }
            break;

        case EFFECT_DARKVISIBLEGOGGLE:
            if (lpEffect->data.variant_0x14.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_DARKVISIBLEGOGGLE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(&lpAct->modelEffect.control,
                                              &lpAct->modelEffect.object, 0);
                    if (lpEffect->data.variant_0x14.field_16 != 0)
                    {
                        if ((lpfnEffect = GM_GetCharaID(DEMOID_DARKVISIBLEGOGGLE2)) != NULL)
                        {
                            lpEAct->lpActor2 = lpfnEffect(5);
                        }
                    }
                }
            }
            break;

        case EFFECT_IRRAYSGOGGLE:
            if (lpEffect->data.variant_0x15.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_IRRAYSGOGGLE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(&lpAct->modelEffect.control,
                                              &lpAct->modelEffect.object, 0);
                    if (lpEffect->data.variant_0x15.field_16 != 0)
                    {
                        if ((lpfnEffect = GM_GetCharaID(DEMOID_IRRAYSGOGGLE2)) != NULL)
                        {
                            lpEAct->lpActor2 = lpfnEffect(6);
                        }
                    }
                }
            }
            break;

        case EFFECT_GUSMASK:
            if (lpEffect->data.variant_0x1E.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_GUSMASK)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect();
                }
            }
            break;
        }
        break;

    case EFFECT_GUNSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_GUNSMOKE)) != NULL)
        {
            lpfnEffect(&svectMove);
        }
        break;

    case EFFECT_OPTICSCAMOUFLAGE:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_OPTICSCAMOUFLAGE)
                && (lpEActL->effect.field_18_xy == lpEffect->data.variant_0x17.field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if ((lpEffect->data.variant_0x17.field_14 != 1)
            && (lpEffect->nEffectID == EFFECT_OPTICSCAMOUFLAGE))
        {
            if (lpEffect->data.variant_0x17.field_1C == 0)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_OPTICSCAMOUFLAGE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(&lpAct->modelEffect.control, &lpModel->object, 0);
                }
            }
            else
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_OPTICSCAMOUFLAGE2)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(&lpAct->modelEffect.control, &lpModel->object, 0);
                }
            }
        }
        break;

    case EFFECT_ENVIRONMENTMAPPING:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_ENVIRONMENTMAPPING)
                && (lpEActL->effect.field_18_xy == lpEffect->data.variant_0x18.field_18))
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_ENVIRONMENTMAPPING)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpModel->object, lpEffect->data.variant_0x18.field_1C);
            }
        }
        break;

    case EFFECT_PLASMA:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        if ((lpfnEffect = GM_GetCharaID(DEMOID_PLASMA)) != NULL)
        {
            lpfnEffect(&lpModel->object,
                lpEffect->data.variant_0x19.field_18,
                lpEffect->data.variant_0x19.field_1A,
                lpEffect->data.variant_0x19.field_1C,
                lpEffect->data.variant_0x19.field_20);
        }
        break;

    case EFFECT_WINDCIRCLE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_WINDCIRCLE)) != NULL)
        {
            lpfnEffect(&mat2, lpEffect->data.variant_0x1A.field_14);
        }
        break;

    case EFFECT_SEPIA:
        KillEffect(lpAct, EFFECT_SEPIA);
        if (lpEffect->data.variant_0x1B.field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SEPIA)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(lpEffect->data.variant_0x1B.field_16,
                                          lpEffect->data.variant_0x1B.field_18,
                                          lpEffect->data.variant_0x1B.field_1A);
            }
        }
        break;

    case EFFECT_METALGEARLASER:
        lpEActL = lpAct->lpEffectNext;
        while ((lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            && (lpEActL->effect.nEffectID != EFFECT_METALGEARLASER || lpEActL->lpActor == NULL))
        {
            lpEActL = lpEActL->lpNext;
        }

        svectMove.vx = lpEffect->data.variant_0x1C.svectMove.vx;
        svectMove.vy = lpEffect->data.variant_0x1C.svectMove.vy;
        svectMove.vz = lpEffect->data.variant_0x1C.svectMove.vz;
        svectRotate.vx = lpEffect->data.variant_0x1C.svectRotate.vx;
        svectRotate.vy = lpEffect->data.variant_0x1C.svectRotate.vy;
        svectRotate.vz = lpEffect->data.variant_0x1C.svectRotate.vz;

        if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_METALGEARLASER)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpEAct->matrix);
                lpEActL = lpEAct;
            }
            else
            {
                break;
            }
        }
        DG_SetPos2(&svectMove, &svectRotate);
        ReadRotMatrix(&lpEActL->matrix);
        break;

    case EFFECT_UNSHAPEVIEW:
        KillEffect(lpAct, EFFECT_UNSHAPEVIEW);
        if (lpEffect->data.variant_0x1D.field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_UNSHAPEVIEW)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(lpEffect->data.variant_0x1D.field_18,
                                          lpEffect->data.variant_0x1D.field_1C);
            }
        }
        break;

    case EFFECT_STOP:
        lpEActL = lpAct->lpEffectNext;
        lpAct->bEffectStop = TRUE;
        lpAct->bEffectBubbleStop = TRUE;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if (lpEActL->lpActor != NULL)
            {
// clang-format off
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
// clang-format on
        if (lpEffect->data.variant_0x20.field_20 == 1)
        {
            lpEActL = lpAct->lpEffectNext;
            while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                if (lpEActL->effect.nEffectID == EFFECT_URINATIONCIRCLE)
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_URINATIONCIRCLE)) != NULL)
            {
                if (lpEffect->data.variant_0x20.field_14 >= 2 && lpEffect->data.variant_0x20.field_14 <= 5)
                {
                    lpfnEffect(&svectMove,
                        lpEffect->data.variant_0x20.field_14 + 2,
                        lpEffect->data.variant_0x20.field_18,
                        lpEffect->data.variant_0x20.field_1C);
                }
                else
                {
                    lpEAct->lpActor = lpfnEffect(&svectMove,
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
        if ((lpfnEffect = GM_GetCharaID(DEMOID_PLASMA2)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3, lpEffect->data.variant_0x21.field_1C);
        }
        break;

    case EFFECT_BLUR:
        KillEffect(lpAct, EFFECT_BLUR);
        if (lpEffect->data.variant_0x22.field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BLUR)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(lpEffect->data.variant_0x22.field_16,
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMSMOKE)) != NULL)
            {
                ((VOIDCHARA)lpfnEffect)(&svectMove, &svec3, lpEffect->data.variant_0x23.field_1A);
            }
        }
        else
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMSMOKE2)) != NULL)
            {
                ((VOIDCHARA)lpfnEffect)(&svectMove, &svec3,
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_MONOTONE)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_RIFLESIGHT:
        KillEffect(lpAct, EFFECT_RIFLESIGHT);

        if (lpEffect->data.variant_0x25.field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_RIFLESIGHT)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_MI24HIND:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpModel->lpData->object[0][0].objs = lpEffect->data.variant_0x26.field_14;
        lpModel->lpData->object[0][0].flag = lpEffect->data.variant_0x26.field_18;
        break;

    case EFFECT_BLACKSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLACKSMOKE)) != NULL)
        {
            lpfnEffect(&svectMove);
        }
        break;

    case EFFECT_URINATIONCIRCLE2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_URINATIONCIRCLE2)) != NULL)
        {
            if (lpEffect->data.variant_0x28.field_14 >= 0 && lpEffect->data.variant_0x28.field_14 <= 3)
            {
                lpfnEffect(&svectMove, lpEffect->data.variant_0x28.field_14 + 4, lpEffect->data.variant_0x28.field_18,
                        lpEffect->data.variant_0x28.field_1C);
            }
            else
            {
                lpEAct->lpActor = lpfnEffect(&svectMove,
                                         lpEffect->data.variant_0x28.field_14 + 4,
                                         lpEffect->data.variant_0x28.field_18,
                                         lpEffect->data.variant_0x28.field_1C);
            }
        }
        break;

    case EFFECT_SIGHT:
        lpEActL = lpAct->lpEffectNext;

        if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            while ((lpEActL->effect.nEffectID != EFFECT_SIGHT) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
                {
                    break;
                }
            }
        }

        if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if (lpEffect->data.variant_0x29.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SIGHT)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(lpEffect->data.variant_0x29.field_1C,
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
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SIGHT)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(lpEffect->data.variant_0x29.field_1C,
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
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_NINJASWORD) &&
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_NINJASWORD)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpModel->object.objs->objs[4]);
            }
        }
        break;

    case EFFECT_SUBMARINEROOM:
        lpEActL = lpAct->lpEffectNext;

        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if (lpEActL->effect.nEffectID == EFFECT_SUBMARINEROOM)
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SUBMARINEROOM)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_BLACKSMOKE2:
        svec3.vx = lpEffect->data.variant_0x2C.field_14;
        svec3.vy = lpEffect->data.variant_0x2C.field_16;
        svec3.vz = lpEffect->data.variant_0x2C.field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLACKSMOKE2)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3,
                lpEffect->data.variant_0x2C.field_1A,
                lpEffect->data.variant_0x2C.field_1C);
        }
        break;

    case EFFECT_BLASTLINE:
        svec3.vx = lpEffect->data.variant_0x2D.field_14;
        svec3.vy = lpEffect->data.variant_0x2D.field_16;
        svec3.vz = lpEffect->data.variant_0x2D.field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLASTLINE)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0x2D.field_22,
                lpEffect->data.variant_0x2D.field_1C,
                lpEffect->data.variant_0x2D.field_20,
                &svectMove, &svec3);
        }
        break;

    case EFFECT_SMOKELINE:
        svec3.vx = lpEffect->data.variant_0x2E.field_14;
        svec3.vy = lpEffect->data.variant_0x2E.field_16;
        svec3.vz = lpEffect->data.variant_0x2E.field_18;
        svec4.vx = lpEffect->data.variant_0x2E.field_1A;
        svec4.vy = lpEffect->data.variant_0x2E.field_1C;
        svec4.vz = lpEffect->data.variant_0x2E.field_1E;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SMOKELINE)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0x2E.field_26,
                lpEffect->data.variant_0x2E.field_20,
                lpEffect->data.variant_0x2E.field_24,
                &svectMove, &svec3, &svec4,
                lpEffect->data.variant_0x2E.field_28 & 0xFF,
                lpEffect->data.variant_0x2E.field_2A & 0xFF,
                lpEffect->data.variant_0x2E.field_2C & 0xFF);
        }
        break;

    case EFFECT_SHELLSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SHELLSMOKE)) != NULL)
        {
            lpfnEffect(lpEffect->data.variant_0x2F.field_14, &svectMove, &svectRotate);
        }
        break;

    case EFFECT_CATERPILLERSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CATERPILLERSMOKE)) != NULL)
        {
            lpfnEffect(&svectRotate, &svectMove);
        }
        break;

    case EFFECT_CROWEYE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CROWEYE)) != NULL)
        {
            lpfnEffect(&svectMove);
        }
        break;

    case EFFECT_OCEROTTEBULLETFIRE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_OCEROTTEBULLETFIRE)) != NULL)
        {
            lpfnEffect(&mat2);
        }
        break;

    case EFFECT_OCEROTTEBULLETSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_OCEROTTEBULLETSMOKE)) != NULL)
        {
            lpfnEffect(&svectMove);
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_ENVIRONMENTLIGHT)) != NULL)
            {
                lpfnEffect(
                    lpEffect->data.variant_0x34.field_14,
                    lpEffect->data.variant_0x34.field_18,
                    &svec3, &svec4,
                    lpEffect->data.variant_0x34.field_1C,
                    lpEffect->data.variant_0x34.field_20);
            }
        }
        else
        {
            memset(&gvMessage, 0x00, sizeof(gvMessage));
            gvMessage.address = lpEffect->data.variant_0x34.field_14;
            gvMessage.message[0] = HASH_KILL;
            gvMessage.message_len = 1;
            GV_SendMessage(&gvMessage);
        }
        break;

    case EFFECT_CRASHSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CRASHSMOKE)) != NULL)
        {
            lpfnEffect(&svectMove, &svectRotate,
                lpEffect->data.variant_0x35.field_18,
                lpEffect->data.variant_0x35.field_1C,
                lpEffect->data.variant_0x35.field_1E,
                lpEffect->data.variant_0x35.field_20,
                lpEffect->data.variant_0x35.field_22 & 0xFF,
                lpEffect->data.variant_0x35.field_24 & 0xFF,
                lpEffect->data.variant_0x35.field_26 & 0xFF);
        }
        break;

    case EFFECT_CELOFAN:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CELOFAN)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0x37.field_14,
                lpEffect->data.variant_0x37.field_18,
                lpEffect->data.variant_0x37.field_1C,
                lpEffect->data.variant_0x37.field_1E,
                lpEffect->data.variant_0x37.field_20,
                lpEffect->data.variant_0x37.field_22,
                &lpEffect->data.variant_0x37.field_24,
                &lpEffect->data.variant_0x37.field_28,
                lpEffect->data.variant_0x37.field_2C,
                lpEffect->data.variant_0x37.field_2E,
                lpEffect->data.variant_0x37.field_30,
                lpEffect->data.variant_0x37.field_32);
        }
        break;

    case EFFECT_INVERSLIGHT:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_INVERSLIGHT)) != NULL)
        {
            ((VOIDCHARA)lpfnEffect)(&svectMove);
        }
        break;

    case EFFECT_SPACK:
        switch (lpEffect->data.variant_0x39.field_14)
        {
        case 0:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SPACK)) != NULL)
            {
                ((VOIDCHARA)lpfnEffect)(&mat2);
            }
            break;

        case 1:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SPACK2)) != NULL)
            {
                lpfnEffect(&mat2, 0);
            }
            break;

        case 2:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SPACK2)) != NULL)
            {
                lpfnEffect(&mat2, 1);
            }
            break;
        }
        break;

    case EFFECT_STEAMEXPLOSION:
        svec3.vx = lpEffect->data.variant_0x3A.field_14;
        svec3.vy = lpEffect->data.variant_0x3A.field_16;
        svec3.vz = lpEffect->data.variant_0x3A.field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMEXPLOSION)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3);
        }
        break;
    case EFFECT_INVERSLIGHT2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_INVERSLIGHT2)) != NULL)
        {
            lpfnEffect(&svectMove,
                lpEffect->data.variant_0x3B.field_14,
                lpEffect->data.variant_0x3B.field_18,
                lpEffect->data.variant_0x3B.field_1C,
                lpEffect->data.variant_0x3B.field_20,
                lpEffect->data.variant_0x3B.field_22,
                lpEffect->data.variant_0x3B.field_24,
                lpEffect->data.variant_0x3B.field_26,
                lpEffect->data.variant_0x3B.field_28);
        }
        break;
    case EFFECT_CELOFAN2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CELOFAN2)) != NULL)
        {
            lpfnEffect(
                lpEffect->data.variant_0x3C.field_14,
                lpEffect->data.variant_0x3C.field_18,
                lpEffect->data.variant_0x3C.field_1C,
                lpEffect->data.variant_0x3C.field_1E,
                lpEffect->data.variant_0x3C.field_20,
                lpEffect->data.variant_0x3C.field_22,
                lpEffect->data.variant_0x3C.field_24,
                &lpEffect->data.variant_0x3C.field_26,
                &lpEffect->data.variant_0x3C.field_2A,
                lpEffect->data.variant_0x3C.field_2E,
                lpEffect->data.variant_0x3C.field_30,
                lpEffect->data.variant_0x3C.field_32,
                lpEffect->data.variant_0x3C.field_34);
        }
        break;

    case EFFECT_NINJALASER:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        if ((lpfnEffect = GM_GetCharaID(DEMOID_NINJALASER)) != NULL)
        {
            lpfnEffect(&lpModel->object.objs[6].world.m[1][1],
                lpEffect->data.variant_0x3D.field_14,
                lpEffect->data.variant_0x3D.field_16);
        }
        break;

    case EFFECT_GUSEFFECT:
        lpEActL = lpAct->lpEffectNext;

        if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            while ((lpEActL->effect.nEffectID != EFFECT_GUSEFFECT) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
                {
                    break;
                }
            }
        }

        if (lpEffect->data.variant_0x3E.field_14 == 0)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }

            if ((lpfnEffect = GM_GetCharaID(DEMOID_GUSEFFECT)) != NULL)
            {
                svec3.vx = lpEffect->data.variant_0x3E.field_16;
                svec3.vy = lpEffect->data.variant_0x3E.field_18;
                svec3.vz = lpEffect->data.variant_0x3E.field_1A;
                lpEAct->lpActor = lpfnEffect(&svec3,
                                        lpEffect->data.variant_0x3E.field_1E,
                                        lpEffect->data.variant_0x3E.field_1C + 1);
            }
        }
        else if (lpEffect->data.variant_0x3E.field_14 == 1)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }
        }
        else if (lpEffect->data.variant_0x3E.field_14 == 2)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                memset(&gvMessage, 0x00, sizeof(gvMessage));
                gvMessage.address = 0x3B8E;
                if (lpEffect->data.variant_0x3E.field_20 == 0)
                    gvMessage.message[0] = HASH_ON2;
                else
                    gvMessage.message[0] = HASH_OFF2;
                gvMessage.message[1] = lpEffect->data.variant_0x3E.field_22;
                gvMessage.message_len = 2;
                GV_SendMessage(&gvMessage);
            }
        }
        break;

    case EFFECT_SUBMARINEWATER:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_SUBMARINEWATER) &&
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SUBMARINEWATER)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpModel->object, &lpModel->control.rot);
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_GHOST)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_LIGHT:
        DG_SetTmpLight(&svectMove,
            lpEffect->data.variant_0x42.nBrightness,
            lpEffect->data.variant_0x42.nRadius);
        break;

    case EFFECT_FAMASLIGHT:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;

        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if ((lpEActL->effect.nEffectID == EFFECT_FAMASLIGHT) &&
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_FAMASLIGHT)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(lpModel->object.objs + 1);
            }
        }
        break;

    case EFFECT_HUMANSHADOW:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
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

        lpEActL = lpAct->lpEffectNext;

        if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            while ((lpEActL->effect.nEffectID != EFFECT_HUMANSHADOW) || !lpEActL->lpActor)
            {
                lpEActL = lpEActL->lpNext;

                if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
                {
                    break;
                }
            }
        }

        if (lpEActL == (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if (lpEffect->data.variant_0x44.field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_HUMANSHADOW)) != NULL)
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
                        lpfnEffect(lpModel, &lpModel->object, &lpEAct->svect1.vx, lpScene->nCacheID);
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
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOODHAZARD)) != NULL)
        {
            lpEAct->lpActor = lpfnEffect(&mat2,
                lpEffect->data.variant_0x45.field_14,
                lpEffect->data.variant_0x45.field_16,
                lpEffect->data.variant_0x45.field_18,
                lpEffect->data.variant_0x45.field_1A);
        }
        break;

    case EFFECT_BLOODDRIP:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOODDRIP)) != NULL)
        {
            lpfnEffect(&svectMove,
                lpEffect->data.variant_0x46.field_14,
                lpEffect->data.variant_0x46.field_16);
        }
        break;

    case EFFECT_NINJAGROUND:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_NINJAGROUND)) != NULL)
        {
            lpfnEffect(&mat2, 400, 400, 400, 10);
        }
        break;

    case EFFECT_BOMBLIGHT:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BOMBLIGHT)) != NULL)
        {
            ((VOIDCHARA)lpfnEffect)(&svectMove);
        }
        break;

    case EFFECT_MGCROOMDISPLAY:
        lpEActL = lpAct->lpEffectNext;
        while (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
        {
            if (lpEActL->effect.nEffectID == EFFECT_MGCROOMDISPLAY)
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
            if ((lpfnEffect = GM_GetCharaID(DEMOID_MGCROOMDISPLAY)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_TEXT2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_TEXT2)) != NULL)
        {
            lpfnEffect(lpEffect->data.variant_0x4A.field_18,
                lpEffect->data.variant_0x4A.field_1A,
                0,
                lpEffect->data.variant_0x4A.field_14,
                lpEffect->data.variant_0x4A.field_1C,
                lpEffect->data.variant_0x4A.field_20);
        }
        break;
    }

    return 1;
}

/******************************************************************************
 */
static void KillEffect(
    LPMGSDEMOACT lpAct,
    int          nEffectID)
{
    LPMGSDEMOEFFECTACT lpEActL;

    if((lpEActL = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        do
        {
            if((lpEActL->effect.nEffectID == nEffectID) &&
                (lpEActL->lpActor != NULL))
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                if(lpEActL->lpActor2)
                    GV_DestroyOtherActor(lpEActL->lpActor2);
                lpEActL->lpActor = NULL;
                lpEActL->lpActor2 = NULL;
            }
        }
        while((lpEActL = (LPMGSDEMOEFFECTACT)lpEActL->lpNext)
            != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);
    }
}

/******************************************************************************
 */
static BOOL ShowEffectExecute(
    LPMGSDEMOACT       lpAct,
    LPMGSDEMOFRAME     lpDFrame,
    LPMGSDEMOEFFECTACT lpEAct)
{
    int                  i;
    int                  lFloor[2];
    SVECTOR              svect1;
    LPMGSDEMOSCENEMOTION lpSMotion;

    switch(lpEAct->effect.nEffectID)
    {
    case EFFECT_SHADOW:
        for(i = 0, lpSMotion = lpDFrame->lpSMotion;
            (i < lpDFrame->nSMotionCount) && (lpSMotion->nSceneID != lpEAct->effect.field_14_type);
            i++, lpSMotion++);
        if(i >= lpDFrame->nSMotionCount)
            break;

        svect1.vx = lpSMotion->svectMove.vx;
        svect1.vy = lpSMotion->svectMove.vy;
        svect1.vz = lpSMotion->svectMove.vz;
        i = HZD_LevelHazardCheck(
            lpAct->modelEffect.control.map->hzd, &svect1, HZD_CHK_F_FLOOR);
        HZD_GetLevelHeight(lFloor);

        lpEAct->nParam1 = lpSMotion->svectRotate.vy;
             if((i & 1) != 0) lpEAct->nParam2 = (short)lFloor[0] + 50;
        else if((i & 2) != 0) lpEAct->nParam2 = (short)lFloor[1] + 50;
        else lpEAct->nParam2 = lpSMotion->svectMove.vy + 50;
        break;
    }
    return 1;
}

/******************************************************************************
 */
static BOOL ShowEffectStop(
    LPMGSDEMOACT   lpAct,
    LPMGSDEMOFRAME lpDFrame)
{
    int                i;
    LPMGSDEMOEFFECT    lpEffect;
    LPMGSDEMOEFFECTACT lpEAct;

    for(i = 0, lpEffect = lpDFrame->lpEffect;
        i < lpDFrame->nEffectCount; i++, lpEffect++)
    {
        if(lpEffect->nEffectID == EFFECT_METALGEARLASER)
            return 1;
    }

    if ((lpEAct = (LPMGSDEMOEFFECTACT)lpAct->lpEffectNext)
        != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        do
        {
            if(lpEAct->effect.nEffectID == EFFECT_METALGEARLASER)
                break;
        }
        while((lpEAct = (LPMGSDEMOEFFECTACT)lpEAct->lpNext)
            != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious);
    }

    if(lpEAct != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
    {
        GV_DestroyOtherActor(lpEAct->lpActor);
        lpEAct->lpActor = NULL;

        DeleteChain(&lpAct->lpEffectPrevious, &lpEAct->lpPrevious);
        GV_Free(lpEAct);
    }

    return 1;
}

/******************************************************************************
 */
static BOOL ShowScene(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion)
{
    int            i;
    SVECTOREX*     lpsvectRotate;
    LPMGSDEMOMODEL lpModel;
    LPMGSDEMOSCENE lpScene;

    OFFSET_TO_PTR(lpSMotion, &lpSMotion->lpsvectRotate);

    for(i = 0, lpScene = lpAct->lpDemo->lpScene, lpModel = lpAct->lpModel;
        (i < lpAct->lpDemo->nSceneCount)
        && (lpScene->nID != lpSMotion->nSceneID); i++, lpScene++, lpModel++);

    if(i >= lpAct->lpDemo->nSceneCount)
        return 0;

    if(lpSMotion->bPreview == FALSE)
    {
        DG_InvisibleObjs(lpModel->object.objs);

        if((lpScene->nStrCode == GV_StrCode("m1e1"))
            || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
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

        if((lpScene->nStrCode == GV_StrCode("m1e1"))
            || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
        {
            DG_VisibleObjs(lpModel->lpData->object[0][lpModel->lpData->field_558_idx[0]].objs);
            DG_VisibleObjs(lpModel->lpData->object[1][lpModel->lpData->field_558_idx[1]].objs);
        }

        lpModel->control.mov.vx = lpSMotion->svectMove.vx;
        lpModel->control.mov.vy = lpSMotion->svectMove.vy;
        lpModel->control.mov.vz = lpSMotion->svectMove.vz;
        lpModel->control.rot.vx = lpSMotion->svectRotate.vx;
        lpModel->control.rot.vy = lpSMotion->svectRotate.vy;
        lpModel->control.rot.vz = lpSMotion->svectRotate.vz;

        if((lpScene->dwStyle & MGS_SCENETOSTAGE) != 0)
        {
            GM_ActControl(&lpModel->control);
            GM_ActObject2(&lpModel->object);
        }
        else
        {
            lpsvectRotate = lpSMotion->lpsvectRotate;
            for(i = 0; i < lpSMotion->nRotateCount; i++, lpsvectRotate++)
            {
                lpModel->object.rots[i].vx = lpsvectRotate->vx;
                lpModel->object.rots[i].vy = lpsvectRotate->vy;
                lpModel->object.rots[i].vz = lpsvectRotate->vz;
            }

            if((lpScene->nStrCode == GV_StrCode("m1e1"))
                || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
            {
                demothrd_m1e1_8007D404(lpAct, lpSMotion, lpScene, lpModel);
            }
            else if((lpScene->nStrCode == GV_StrCode("hind"))
                || (lpScene->nStrCode == IDMODEL_MI24HINDDEMO))
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

/******************************************************************************
 */
static inline int magic_calc(SVECTOR* svect1, LPMGSDEMOMODEL lpModel)
{
    int distance1 = SquareRoot0(((svect1->vx * svect1->vx) + (svect1->vy * svect1->vy)) + (svect1->vz * svect1->vz));

    int rTan1 = ratan2(svect1->vx, svect1->vz);
    int tmp4 = rTan1;
    tmp4 -= lpModel->control.rot.vy + lpModel->object.rots[0].vy;
    tmp4 = abs(tmp4);
    return (distance1 * (1024 - tmp4)) / 1024;
}

/******************************************************************************
 */
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
    for(i = 0; i < 3; i++)
    {
        GM_ActMotion(&lpM1E1->object[0][i]);
        GM_ActMotion(&lpM1E1->object[1][i]);
    }

    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);
    DG_RotatePos(lpModel->object.rots);

    M1E1GetCaterpillerVertex(&lpModel->lpData->object[0][0], &lpModel->lpData->object[1][0], smokeVecs, 1);
    for(i = 0; i < 10; i++)
    {
        smokeVecs[i].vy = smokeVecs[i].vy + 300;
    }

    DG_PutVector(smokeVecs, smokeVecs, 10);

    memset(&vec, 0x00, sizeof(SVECTOR));
    vec.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_PutVector(&vec, &vec, 1);

    vecTmp.vx = vec.vx - lpM1E1->field_564[0].vx;
    vecTmp.vy = vec.vy - lpM1E1->field_564[0].vy;
    vecTmp.vz = vec.vz - lpM1E1->field_564[0].vz;

    tmp1 = magic_calc(&vecTmp, lpModel);

    if(abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[rand() % 5]);
        DG_InvisibleObjs(lpM1E1->object[0][lpM1E1->field_558_idx[0]].objs);
        if(tmp1 > 0)
            lpM1E1->field_558_idx[0]++;
        else
            lpM1E1->field_558_idx[0]--;

        if(lpM1E1->field_558_idx[0] < 0)
            lpM1E1->field_558_idx[0] = 2;

        if(lpM1E1->field_558_idx[0] >= 3)
            lpM1E1->field_558_idx[0] = 0;

        DG_VisibleObjs(lpM1E1->object[0][lpM1E1->field_558_idx[0]].objs);
        lpM1E1->field_564[0] = vec;
    }

    memset(&vec, 0x00, sizeof(SVECTOR));
    vec.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);

    DG_PutVector(&vec, &vec, 1);
    vecTmp.vx = vec.vx - lpM1E1->field_564[1].vx;
    vecTmp.vy = vec.vy - lpM1E1->field_564[1].vy;
    vecTmp.vz = vec.vz - lpM1E1->field_564[1].vz;

    tmp1 = magic_calc(&vecTmp, lpModel);

    if(abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[(rand() % 5) + 5]);
        DG_InvisibleObjs(lpM1E1->object[1][lpM1E1->field_558_idx[1]].objs);
        if(tmp1 > 0)
            lpM1E1->field_558_idx[1]++;
        else
            lpM1E1->field_558_idx[1]--;

        if(lpM1E1->field_558_idx[1] < 0)
            lpM1E1->field_558_idx[1] = 2;

        if(lpM1E1->field_558_idx[1] >= 3)
            lpM1E1->field_558_idx[1] = 0;

        DG_VisibleObjs(lpM1E1->object[1][lpM1E1->field_558_idx[1]].objs);
        lpM1E1->field_564[1] = vec;
    }
    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);
    DG_RotatePos(lpModel->object.rots);
    for(i = 0; i < 3; i++)
    {
        GM_ActObject(&lpM1E1->object[0][i]);
        GM_ActObject(&lpM1E1->object[1][i]);
    }
}

/******************************************************************************
 */
static void demothrd_hind_8007D9C8(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion,
    LPMGSDEMOSCENE       lpScene,
    LPMGSDEMOMODEL       lpModel)
{
    LPMGSDEMOHIND lpHind = (LPMGSDEMOHIND)lpModel->lpData;

    lpHind->field_8 -= lpHind->field_0;
    if(lpHind->field_8 < 0)
        lpHind->field_8 += 4096;

    lpHind->field_C -= lpHind->field_4;
    if(lpHind->field_C < 0)
        lpHind->field_C += 4096;

    lpModel->object.rots[1].vy = lpHind->field_8;
    lpModel->object.rots[2].vx = lpHind->field_C;
}
