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
static void ActM1E1(LPMGSDEMOACT lpAct, LPMGSDEMOSCENEMOTION lpSMotion, LPMGSDEMOSCENE lpScene, LPMGSDEMOMODEL lpModel);
static void ActMi24Hind(LPMGSDEMOACT lpAct, LPMGSDEMOSCENEMOTION lpSMotion, LPMGSDEMOSCENE lpScene, LPMGSDEMOMODEL lpModel);

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
            if((lpModel->lpData = GV_Malloc(sizeof(MODELM1E1))) == NULL)
                return 0;
            memset(lpModel->lpData, 0x00, sizeof(MODELM1E1));

            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[0][0],
                GV_StrCode("m1e1cl1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[0][1],
                GV_StrCode("m1e1cl2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[0][2],
                GV_StrCode("m1e1cl3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[1][0],
                GV_StrCode("m1e1cr1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[1][1],
                GV_StrCode("m1e1cr2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&((LPMODELM1E1)lpModel->lpData)->object[1][2],
                GV_StrCode("m1e1cr3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);

            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[0][0]);
            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[0][1]);
            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[0][2]);
            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[1][0]);
            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[1][1]);
            GM_ConfigObjectJoint(&((LPMODELM1E1)lpModel->lpData)->object[1][2]);

            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[0][0], lpModel->light);
            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[0][1], lpModel->light);
            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[0][2], lpModel->light);
            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[1][0], lpModel->light);
            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[1][1], lpModel->light);
            GM_ConfigObjectLight(&((LPMODELM1E1)lpModel->lpData)->object[1][2], lpModel->light);

            ((LPMODELM1E1)lpModel->lpData)->field_560 = 83;
        }
        else if((lpScene->nStrCode == GV_StrCode("hind"))
            || (lpScene->nStrCode == IDMODEL_MI24HINDDEMO))
        {
            if((lpModel->lpData = GV_Malloc(sizeof(MODELMI24HIND))) == NULL)
                return 0;
            memset(lpModel->lpData, 0x00, sizeof(MODELMI24HIND));
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
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[0][0]);
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[0][1]);
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[0][2]);
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[1][0]);
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[1][1]);
                GM_FreeObject(&((LPMODELM1E1)lpModel->lpData)->object[1][2]);
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
                if (((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_18 == 0)
                    lpfnEffect(1, ((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_14);
                else
                    lpfnEffect(3, ((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_14);
            }
            break;

        case EFFECT_FADEOUT:
            if ((lpfnEffect = GM_GetCharaID(DEMOID_FADEOUT)) != NULL)
            {
                if (((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_18 == 0)
                    lpEAct->lpActor = lpfnEffect(0,
                        ((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_14);
                else
                    lpEAct->lpActor = lpfnEffect(2,
                        ((LPEFFECTFADEINOUT)lpEffect->byBuffer)->field_14);
            }
            break;
        }
        break;

    case EFFECT_TEXT:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_TEXT)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTTEXT)lpEffect->byBuffer)->field_18,
                ((LPEFFECTTEXT)lpEffect->byBuffer)->field_1A,
                0,
                ((LPEFFECTTEXT)lpEffect->byBuffer)->field_14,
                ((LPEFFECTTEXT)lpEffect->byBuffer)->field_1C);
        }
        break;

    case EFFECT_SURPRISEDMARK:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SURPRISEDMARK)) != NULL)
        {
            if (((LPEFFECTSURPRISEDMARK)lpEffect->byBuffer)->field_14 == 0)
                lpfnEffect(&mat1, 2);
            else
                lpfnEffect(&mat1, 0);
        }
        break;

    case EFFECT_QUESTIONMARK:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_QUESTIONMARK)) != NULL)
        {
            if (((LPEFFECTQUESTIONMARK)lpEffect->byBuffer)->field_14 == 0)
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
        if (((LPEFFECTBLOOD)lpEffect->byBuffer)->field_14 != 4)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOOD)) != NULL)
            {
                lpfnEffect(&mat2, ((LPEFFECTBLOOD)lpEffect->byBuffer)->field_14);
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
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_14,
                &mat2,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_18,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_1A,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_1E,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_20,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_22,
                ((LPEFFECTBULLET)lpEffect->byBuffer)->field_24);
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
            if ((((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_14 >= 4)
                && (((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_14 <= 7))
            {
                lpfnEffect(&svectMove,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_14,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_1C);
            }
            else
            {
                lpEAct->lpActor = lpfnEffect(&svectMove,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_14,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTBLOODCIRCLE)lpEffect->byBuffer)->field_1C);
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
            if (lpScene->nID == ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_14)
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
                && (lpEActL->effect.field_14_type == ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_14))
            {
                if (lpEActL->lpActor)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
        }

        if (((LPEFFECTSHADOW)lpEffect->byBuffer)->field_20 != 1)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SHADOW)) != NULL)
            {
                lpEAct->lpActor =
                    lpfnEffect(
                        &lpModel->object,
                        ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_18,
                        &lpEAct->nParam1,
                        &lpEAct->nParam2,
                        ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_22 & 0xFF,
                        ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_24 & 0xFF,
                        ((LPEFFECTSHADOW)lpEffect->byBuffer)->field_26 & 0xFF);
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
            lpEAct->lpActor = lpfnEffect(&mat2,
                ((LPEFFECTFOOTPRINTS)lpEffect->byBuffer)->field_14, svectMove.vy);
        }
        break;

    case EFFECT_MESSAGE:
        memset(&gvMessage, 0x00, sizeof(gvMessage));
        gvMessage.address = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->address;
        gvMessage.message[0] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[0];
        gvMessage.message[1] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[1];
        gvMessage.message[2] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[2];
        gvMessage.message[3] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[3];
        gvMessage.message[4] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[4];
        gvMessage.message[5] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[5];
        gvMessage.message[6] = ((LPEFFECTMESSAGE)lpEffect->byBuffer)->message[6];
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
        if (((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BUBBLE)) != NULL)
            {
                lpfnEffect(&svectMove,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_20,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_24,
                    &lpAct->bEffectBubbleStop,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_26,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_28,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_2A);
            }
        }
        else if (((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_14 == 1)
        {
            svec3.vx = ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_16;
            svec3.vy = ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_18;
            svec3.vz = ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_1A;

            if ((lpfnEffect = GM_GetCharaID(DEMOID_BUBBLE2)) != NULL)
            {
                lpfnEffect(&svectMove, &svec3,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_1C,
                    &lpAct->bEffectBubbleStop,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_26,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_28,
                    ((LPEFFECTBUBBLE)lpEffect->byBuffer)->field_2A);
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
            if (((LPEFFECTSCOPE)lpEffect->byBuffer)->field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SCOPE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(
                        &lpAct->modelEffect.control,
                        &lpAct->modelEffect.object, 0);
                }
            }
            break;

        case EFFECT_DARKVISIBLEGOGGLE:
            if (((LPEFFECTDARKVISIBLEGOGGLE)lpEffect->byBuffer)->field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_DARKVISIBLEGOGGLE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(
                        &lpAct->modelEffect.control,
                        &lpAct->modelEffect.object, 0);

                    if (((LPEFFECTDARKVISIBLEGOGGLE)lpEffect->byBuffer)->field_16 != 0)
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
            if (((LPEFFECTIRRAYSGOGGLE)lpEffect->byBuffer)->field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_IRRAYSGOGGLE)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(
                        &lpAct->modelEffect.control,
                        &lpAct->modelEffect.object, 0);

                    if (((LPEFFECTIRRAYSGOGGLE)lpEffect->byBuffer)->field_16 != 0)
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
            if (((LPEFFECTGUSMASK)lpEffect->byBuffer)->field_14 != 1)
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
            if (lpScene->nID == ((LPEFFECTOPTICSCAMOUFLAGE)lpEffect->byBuffer)->field_18)
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
                && (lpEActL->effect.field_18_xy == ((LPEFFECTOPTICSCAMOUFLAGE)lpEffect->byBuffer)->field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if ((((LPEFFECTOPTICSCAMOUFLAGE)lpEffect->byBuffer)->field_14 != 1)
            && (lpEffect->nEffectID == EFFECT_OPTICSCAMOUFLAGE))
        {
            if (((LPEFFECTOPTICSCAMOUFLAGE)lpEffect->byBuffer)->field_1C == 0)
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
            if (lpScene->nID == ((LPEFFECTENVIRONMENTMAPPING)lpEffect->byBuffer)->field_18)
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
                && (lpEActL->effect.field_18_xy == ((LPEFFECTENVIRONMENTMAPPING)lpEffect->byBuffer)->field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }
        if (((LPEFFECTENVIRONMENTMAPPING)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_ENVIRONMENTMAPPING)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpModel->object,
                    ((LPEFFECTENVIRONMENTMAPPING)lpEffect->byBuffer)->field_1C);
            }
        }
        break;

    case EFFECT_PLASMA:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
        {
            if (lpScene->nID == ((LPEFFECTPLASMA)lpEffect->byBuffer)->field_14)
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
                ((LPEFFECTPLASMA)lpEffect->byBuffer)->field_18,
                ((LPEFFECTPLASMA)lpEffect->byBuffer)->field_1A,
                ((LPEFFECTPLASMA)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTPLASMA)lpEffect->byBuffer)->field_20);
        }
        break;

    case EFFECT_WINDCIRCLE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_WINDCIRCLE)) != NULL)
        {
            lpfnEffect(&mat2, ((LPEFFECTWINDCIRCLE)lpEffect->byBuffer)->field_14);
        }
        break;

    case EFFECT_SEPIA:
        KillEffect(lpAct, EFFECT_SEPIA);
        if (((LPEFFECTSEPIA)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SEPIA)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(
                    ((LPEFFECTSEPIA)lpEffect->byBuffer)->field_16,
                    ((LPEFFECTSEPIA)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTSEPIA)lpEffect->byBuffer)->field_1A);
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
// clang-format off
        svectMove.vx = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectMove.vx;
        svectMove.vy = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectMove.vy;
        svectMove.vz = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectMove.vz;
        svectRotate.vx = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectRotate.vx;
        svectRotate.vy = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectRotate.vy;
        svectRotate.vz = ((LPEFFECTMETALGEARLASER)
            lpEffect->byBuffer)->svectRotate.vz;
// clang-format on
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
        if (((LPEFFECTUNSHAPEVIEW)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_UNSHAPEVIEW)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(
                    ((LPEFFECTUNSHAPEVIEW)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTUNSHAPEVIEW)lpEffect->byBuffer)->field_1C);
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
        if (((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_20 == 1)
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
                if ((((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_14 >= 2)
                    && (((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_14 <= 5))
                {
                    lpfnEffect(&svectMove,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_14 + 2,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_18,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_1C);
                }
                else
                {
                    lpEAct->lpActor = lpfnEffect(&svectMove,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_14 + 2,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_18,
                        ((LPEFFECTURINATIONCIRCLE)lpEffect->byBuffer)->field_1C);
                }
            }
        }
        break;

    case EFFECT_PLASMA2:
        svec3.vx = ((LPEFFECTPLASMA2)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTPLASMA2)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTPLASMA2)lpEffect->byBuffer)->field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_PLASMA2)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3, ((LPEFFECTPLASMA2)lpEffect->byBuffer)->field_1C);
        }
        break;

    case EFFECT_BLUR:
        KillEffect(lpAct, EFFECT_BLUR);
        if (((LPEFFECTBLUR)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_BLUR)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(
                    ((LPEFFECTBLUR)lpEffect->byBuffer)->field_16,
                    ((LPEFFECTBLUR)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTBLUR)lpEffect->byBuffer)->field_1A);
            }
        }
        break;

    case EFFECT_STEAMSMOKE:
        svec3.vx = ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_18;
        if (((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_1A != 4)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMSMOKE)) != NULL)
            {
                ((VOIDCHARA)lpfnEffect)(&svectMove, &svec3,
                    ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_1A);
            }
        }
        else
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMSMOKE2)) != NULL)
            {
                ((VOIDCHARA)lpfnEffect)(&svectMove, &svec3,
                    ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_1C & 0xFF,
                    ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_1E & 0xFF,
                    ((LPEFFECTSTEAMSMOKE)lpEffect->byBuffer)->field_20 & 0xFF);
            }
        }
        break;

    case EFFECT_MONOTONE:
        KillEffect(lpAct, EFFECT_MONOTONE);

        if (((LPEFFECTMONOTONE)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_MONOTONE)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_RIFLESIGHT:
        KillEffect(lpAct, EFFECT_RIFLESIGHT);

        if (((LPEFFECTRIFLESIGHT)lpEffect->byBuffer)->field_14 == 0)
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

        ((LPMODELM1E1)lpModel->lpData)->object[0][0].objs = ((LPEFFECTMI24HIND)lpEffect->byBuffer)->lpObjs;
        ((LPMODELM1E1)lpModel->lpData)->object[0][0].flag = ((LPEFFECTMI24HIND)lpEffect->byBuffer)->nFlags;
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
            if ((((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_14 >= 0)
                && (((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_14 <= 3))
            {
                lpfnEffect(&svectMove,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_14 + 4,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_1C);
            }
            else
            {
                lpEAct->lpActor = lpfnEffect(&svectMove,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_14 + 4,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_18,
                    ((LPEFFECTURINATIONCIRCLE2)lpEffect->byBuffer)->field_1C);
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
            if (((LPEFFECTSIGHT)lpEffect->byBuffer)->field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SIGHT)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(
                        ((LPEFFECTSIGHT)lpEffect->byBuffer)->field_1C,
                        &((LPEFFECTSIGHT)lpEffect->byBuffer)->field_16);
                }
            }
        }
        else if (((LPEFFECTSIGHT)lpEffect->byBuffer)->field_14 != 0)
        {
            if (lpEActL->effect.field_1C_zpad != ((LPEFFECTSIGHT)lpEffect->byBuffer)->field_1C)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
                if ((lpfnEffect = GM_GetCharaID(DEMOID_SIGHT)) != NULL)
                {
                    lpEAct->lpActor = lpfnEffect(
                        ((LPEFFECTSIGHT)lpEffect->byBuffer)->field_1C,
                        &((LPEFFECTSIGHT)lpEffect->byBuffer)->field_16);
                }
            }
            else
            {
                // TODO: I can't make sense of it (field_28 is used as an int in other places...)
                struct copier
                {
                    short a, b;
                };
                *(struct copier *)((char *)&lpEActL->effect.field_14_type + 2) = *(struct copier *)&((LPEFFECTSIGHT)lpEffect->byBuffer)->field_16;
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
            if (lpScene->nID == ((LPEFFECTNINJASWORD)lpEffect->byBuffer)->field_14)
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
                (lpEActL->effect.field_14_type == ((LPEFFECTNINJASWORD)lpEffect->byBuffer)->field_14))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }
        if (((LPEFFECTNINJASWORD)lpEffect->byBuffer)->field_18 != 1)
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

        if (((LPEFFECTSUBMARINEROOM)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SUBMARINEROOM)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_BLACKSMOKE2:
        svec3.vx = ((LPEFFECTBLACKSMOKE2)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTBLACKSMOKE2)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTBLACKSMOKE2)lpEffect->byBuffer)->field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLACKSMOKE2)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3,
                ((LPEFFECTBLACKSMOKE2)lpEffect->byBuffer)->field_1A,
                ((LPEFFECTBLACKSMOKE2)lpEffect->byBuffer)->field_1C);
        }
        break;

    case EFFECT_BLASTLINE:
        svec3.vx = ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLASTLINE)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_22,
                ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTBLASTLINE)lpEffect->byBuffer)->field_20,
                &svectMove, &svec3);
        }
        break;

    case EFFECT_SMOKELINE:
        svec3.vx = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_18;
        svec4.vx = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_1A;
        svec4.vy = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_1C;
        svec4.vz = ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_1E;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SMOKELINE)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_26,
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_20,
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_24,
                &svectMove, &svec3, &svec4,
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_28 & 0xFF,
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_2A & 0xFF,
                ((LPEFFECTSMOKELINE)lpEffect->byBuffer)->field_2C & 0xFF);
        }
        break;

    case EFFECT_SHELLSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_SHELLSMOKE)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTSHELLSMOKE)lpEffect->byBuffer)->field_14,
                &svectMove, &svectRotate);
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
        svec3.vx = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_24;
        svec3.vy = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_26;
        svec3.vz = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_28;
        svec4.vx = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_2A;
        svec4.vy = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_2C;
        svec4.vz = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_2E;
        if (((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_30 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_ENVIRONMENTLIGHT)) != NULL)
            {
                lpfnEffect(
                    ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_14,
                    ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_18,
                    &svec3, &svec4,
                    ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_1C,
                    ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_20);
            }
        }
        else
        {
            memset(&gvMessage, 0x00, sizeof(gvMessage));
            gvMessage.address = ((LPEFFECTENVIRONMENTLIGHT)lpEffect->byBuffer)->field_14;
            gvMessage.message[0] = HASH_KILL;
            gvMessage.message_len = 1;
            GV_SendMessage(&gvMessage);
        }
        break;

    case EFFECT_CRASHSMOKE:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CRASHSMOKE)) != NULL)
        {
            lpfnEffect(&svectMove, &svectRotate,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_18,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_1E,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_20,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_22 & 0xFF,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_24 & 0xFF,
                ((LPEFFECTCRASHSMOKE)lpEffect->byBuffer)->field_26 & 0xFF);
        }
        break;

    case EFFECT_CELOFAN:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CELOFAN)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_14,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_18,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_1E,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_20,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_22,
                &((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_24,
                &((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_28,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_2C,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_2E,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_30,
                ((LPEFFECTCELOFAN)lpEffect->byBuffer)->field_32);
        }
        break;

    case EFFECT_INVERSLIGHT:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_INVERSLIGHT)) != NULL)
        {
            ((VOIDCHARA)lpfnEffect)(&svectMove);
        }
        break;

    case EFFECT_SPACK:
        switch (((LPEFFECTSPACK)lpEffect->byBuffer)->field_14)
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
        svec3.vx = ((LPEFFECTSTEAMEXPLOSION)lpEffect->byBuffer)->field_14;
        svec3.vy = ((LPEFFECTSTEAMEXPLOSION)lpEffect->byBuffer)->field_16;
        svec3.vz = ((LPEFFECTSTEAMEXPLOSION)lpEffect->byBuffer)->field_18;
        if ((lpfnEffect = GM_GetCharaID(DEMOID_STEAMEXPLOSION)) != NULL)
        {
            lpfnEffect(&svectMove, &svec3);
        }
        break;

    case EFFECT_INVERSLIGHT2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_INVERSLIGHT2)) != NULL)
        {
            lpfnEffect(&svectMove,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_14,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_18,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_20,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_22,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_24,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_26,
                ((LPEFFECTINVERSLIGHT2)lpEffect->byBuffer)->field_28);
        }
        break;

    case EFFECT_CELOFAN2:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_CELOFAN2)) != NULL)
        {
            lpfnEffect(
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_14,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_18,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_1E,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_20,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_22,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_24,
                &((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_26,
                &((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_2A,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_2E,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_30,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_32,
                ((LPEFFECTCELOFAN2)lpEffect->byBuffer)->field_34);
        }
        break;

    case EFFECT_NINJALASER:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
        {
            if (lpScene->nID == ((LPEFFECTNINJALASER)lpEffect->byBuffer)->field_18)
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
                ((LPEFFECTNINJALASER)lpEffect->byBuffer)->field_14,
                ((LPEFFECTNINJALASER)lpEffect->byBuffer)->field_16);
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

        if (((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_14 == 0)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }

            if ((lpfnEffect = GM_GetCharaID(DEMOID_GUSEFFECT)) != NULL)
            {
                svec3.vx = ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_16;
                svec3.vy = ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_18;
                svec3.vz = ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_1A;
                lpEAct->lpActor = lpfnEffect(&svec3,
                    ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_1E,
                    ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_1C + 1);
            }
        }
        else if (((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_14 == 1)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                GV_DestroyOtherActor(lpEActL->lpActor);
                lpEActL->lpActor = NULL;
            }
        }
        else if (((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_14 == 2)
        {
            if (lpEActL != (LPMGSDEMOEFFECTACT)&lpAct->lpEffectPrevious)
            {
                memset(&gvMessage, 0x00, sizeof(gvMessage));
                gvMessage.address = 0x3B8E;
                if (((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_20 == 0)
                    gvMessage.message[0] = HASH_ON2;
                else
                    gvMessage.message[0] = HASH_OFF2;
                gvMessage.message[1] = ((LPEFFECTGUSEFFECT)lpEffect->byBuffer)->field_22;
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
            if (lpScene->nID == ((LPEFFECTSUBMARINEWATER)lpEffect->byBuffer)->field_18)
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
                (lpEActL->effect.field_18_xy == ((LPEFFECTSUBMARINEWATER)lpEffect->byBuffer)->field_18))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (((LPEFFECTSUBMARINEWATER)lpEffect->byBuffer)->field_14 != 1)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_SUBMARINEWATER)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect(&lpModel->object, &lpModel->control.rot);
            }
        }
        break;

    case EFFECT_PADVIBRATION:
    case EFFECT_PADVIBRATION2:
        if (((LPEFFECTPADVIBRATION)lpEffect->byBuffer)->field_14 != 0)
        {
            GM_PadVibration = 1;
        }
        if (((LPEFFECTPADVIBRATION)lpEffect->byBuffer)->field_16 != 0)
        {
            GM_PadVibration2 = ((LPEFFECTPADVIBRATION)lpEffect->byBuffer)->field_18;
        }
        break;

    case EFFECT_GHOST:
        KillEffect(lpAct, EFFECT_GHOST);
        if (((LPEFFECTGHOST)lpEffect->byBuffer)->field_14 == 0)
        {
            if ((lpfnEffect = GM_GetCharaID(DEMOID_GHOST)) != NULL)
            {
                lpEAct->lpActor = lpfnEffect();
            }
        }
        break;

    case EFFECT_LIGHT:
        DG_SetTmpLight(&svectMove,
            ((LPEFFECTLIGHT)lpEffect->byBuffer)->nBrightness,
            ((LPEFFECTLIGHT)lpEffect->byBuffer)->nRadius);
        break;

    case EFFECT_FAMASLIGHT:
        lpModel = lpAct->lpModel;
        lpScene = lpAct->lpDemo->lpScene;

        for (i = 0; i < lpAct->lpDemo->nSceneCount; i++, lpScene++, lpModel++)
        {
            if (lpScene->nID == ((LPEFFECTFAMASLIGHT)lpEffect->byBuffer)->field_14)
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
                (lpEActL->effect.field_14_type == ((LPEFFECTFAMASLIGHT)lpEffect->byBuffer)->field_14))
            {
                if (lpEActL->lpActor != NULL)
                {
                    GV_DestroyOtherActor(lpEActL->lpActor);
                    lpEActL->lpActor = NULL;
                }
            }
            lpEActL = lpEActL->lpNext;
        }

        if (((LPEFFECTFAMASLIGHT)lpEffect->byBuffer)->field_18 != 1)
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
            if (lpScene->nID == ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_18)
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
            if (((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_14 != 1)
            {
                if ((lpfnEffect = GM_GetCharaID(DEMOID_HUMANSHADOW)) != NULL)
                {
                    lpEAct->svect1.vx = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_1E;
                    lpEAct->svect1.vy = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_20;
                    lpEAct->svect1.vz = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_22;

                    if (((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_1C == 0)
                    {
                        lpEAct->svect1.pad = 0;
                    }
                    else
                    {
                        lpEAct->svect1.pad = -1;
                    }

                    lpEAct->lpActor = lpfnEffect(lpModel,
                        &lpModel->object, &lpEAct->svect1.vx, lpScene->nCacheID);
                }
            }
        }
        else if (((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_14 == 1)
        {
            GV_DestroyOtherActor(lpEActL->lpActor);
            lpEActL->lpActor = NULL;
        }
        else
        {
            lpEActL->svect1.vx = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_1E;
            lpEActL->svect1.vy = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_20;
            lpEActL->svect1.vz = ((LPEFFECTHUMANSHADOW)lpEffect->byBuffer)->field_22;
        }
        break;

    case EFFECT_BLOODHAZARD:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOODHAZARD)) != NULL)
        {
            lpEAct->lpActor = lpfnEffect(&mat2,
                ((LPEFFECTBLOODHAZARD)lpEffect->byBuffer)->field_14,
                ((LPEFFECTBLOODHAZARD)lpEffect->byBuffer)->field_16,
                ((LPEFFECTBLOODHAZARD)lpEffect->byBuffer)->field_18,
                ((LPEFFECTBLOODHAZARD)lpEffect->byBuffer)->field_1A);
        }
        break;

    case EFFECT_BLOODDRIP:
        if ((lpfnEffect = GM_GetCharaID(DEMOID_BLOODDRIP)) != NULL)
        {
            lpfnEffect(&svectMove,
                ((LPEFFECTBLOODDRIP)lpEffect->byBuffer)->field_14,
                ((LPEFFECTBLOODDRIP)lpEffect->byBuffer)->field_16);
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

        if (((LPEFFECTMGCROOMDISPLAY)lpEffect->byBuffer)->field_14 == 0)
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
            lpfnEffect(
                ((LPEFFECTTEXT2)lpEffect->byBuffer)->field_18,
                ((LPEFFECTTEXT2)lpEffect->byBuffer)->field_1A,
                0,
                ((LPEFFECTTEXT2)lpEffect->byBuffer)->field_14,
                ((LPEFFECTTEXT2)lpEffect->byBuffer)->field_1C,
                ((LPEFFECTTEXT2)lpEffect->byBuffer)->field_20);
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
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[0][0].objs);
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[0][1].objs);
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[0][2].objs);
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[1][0].objs);
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[1][1].objs);
            DG_InvisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[1][2].objs);
        }
    }
    else
    {
        DG_VisibleObjs(lpModel->object.objs);

        if((lpScene->nStrCode == GV_StrCode("m1e1"))
            || (lpScene->nStrCode == IDMODEL_M1E1DEMO))
        {
            DG_VisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[0][((LPMODELM1E1)lpModel->lpData)->nIndex[0]].objs);
            DG_VisibleObjs(((LPMODELM1E1)lpModel->lpData)->object[1][((LPMODELM1E1)lpModel->lpData)->nIndex[1]].objs);
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
                ActM1E1(lpAct, lpSMotion, lpScene, lpModel);
            }
            else if((lpScene->nStrCode == GV_StrCode("hind"))
                || (lpScene->nStrCode == IDMODEL_MI24HINDDEMO))
            {
                ActMi24Hind(lpAct, lpSMotion, lpScene, lpModel);
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
static void ActM1E1(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion,
    LPMGSDEMOSCENE       lpScene,
    LPMGSDEMOMODEL       lpModel)
{
    int         i;
    LPMODELM1E1 lpM1E1;
    int         tmp1;
    SVECTOR     svect1;
    SVECTOR     svect2;
    SVECTOR     svectSmoke[10];

    lpM1E1 = (LPMODELM1E1)lpModel->lpData;

    for(i = 0; i < 3; i++)
    {
        GM_ActMotion(&lpM1E1->object[0][i]);
        GM_ActMotion(&lpM1E1->object[1][i]);
    }

    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);
    DG_RotatePos(lpModel->object.rots);

    M1E1GetCaterpillerVertex(
        &((LPMODELM1E1)lpModel->lpData)->object[0][0],
        &((LPMODELM1E1)lpModel->lpData)->object[1][0], svectSmoke, TRUE);

    for(i = 0; i < 10; i++)
    {
        svectSmoke[i].vy = svectSmoke[i].vy + 300;
    }

    DG_PutVector(svectSmoke, svectSmoke, 10);

    memset(&svect1, 0x00, sizeof(SVECTOR));
    svect1.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_PutVector(&svect1, &svect1, 1);

    svect2.vx = svect1.vx - lpM1E1->field_564[0].vx;
    svect2.vy = svect1.vy - lpM1E1->field_564[0].vy;
    svect2.vz = svect1.vz - lpM1E1->field_564[0].vz;

    tmp1 = magic_calc(&svect2, lpModel);

    if(abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&svectSmoke[rand() % 5]);
        DG_InvisibleObjs(lpM1E1->object[0][lpM1E1->nIndex[0]].objs);
        if(tmp1 > 0)
            lpM1E1->nIndex[0]++;
        else
            lpM1E1->nIndex[0]--;

        if(lpM1E1->nIndex[0] < 0)
            lpM1E1->nIndex[0] = 2;

        if(lpM1E1->nIndex[0] >= 3)
            lpM1E1->nIndex[0] = 0;

        DG_VisibleObjs(lpM1E1->object[0][lpM1E1->nIndex[0]].objs);
        lpM1E1->field_564[0] = svect1;
    }

    memset(&svect1, 0x00, sizeof(SVECTOR));
    svect1.vx = lpM1E1->object[1][0].objs->objs[0].model->lx + ((lpM1E1->object[1][0].objs->objs[0].model->ux - lpM1E1->object[1][0].objs->objs[0].model->lx) / 2);
    DG_SetPos2(&lpModel->control.mov, &lpModel->control.rot);

    DG_PutVector(&svect1, &svect1, 1);
    svect2.vx = svect1.vx - lpM1E1->field_564[1].vx;
    svect2.vy = svect1.vy - lpM1E1->field_564[1].vy;
    svect2.vz = svect1.vz - lpM1E1->field_564[1].vz;

    tmp1 = magic_calc(&svect2, lpModel);

    if(abs(tmp1) >= lpM1E1->field_560)
    {
        AN_CaterpillerSmoke(&svectSmoke[(rand() % 5) + 5]);
        DG_InvisibleObjs(lpM1E1->object[1][lpM1E1->nIndex[1]].objs);
        if(tmp1 > 0)
            lpM1E1->nIndex[1]++;
        else
            lpM1E1->nIndex[1]--;

        if(lpM1E1->nIndex[1] < 0)
            lpM1E1->nIndex[1] = 2;

        if(lpM1E1->nIndex[1] >= 3)
            lpM1E1->nIndex[1] = 0;

        DG_VisibleObjs(lpM1E1->object[1][lpM1E1->nIndex[1]].objs);
        lpM1E1->field_564[1] = svect1;
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
static void ActMi24Hind(
    LPMGSDEMOACT         lpAct,
    LPMGSDEMOSCENEMOTION lpSMotion,
    LPMGSDEMOSCENE       lpScene,
    LPMGSDEMOMODEL       lpModel)
{
    LPMODELMI24HIND lpHind = (LPMODELMI24HIND)lpModel->lpData;

    if((lpHind->field_8 -= lpHind->field_0) < 0)
        lpHind->field_8 += 4096;

    if((lpHind->field_C -= lpHind->field_4) < 0)
        lpHind->field_C += 4096;

    lpModel->object.rots[1].vy = lpHind->field_8;
    lpModel->object.rots[2].vx = lpHind->field_C;
}
