/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : M1E1 カタピラ
 */

/******************************************************************************
 * included
 */

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

#include "common.h"
#include "m1e1.h"

// in anime/effect/m1e1.c
extern void AN_CaterpillerSmoke(SVECTOR *pos);
extern void AN_CaterpillerSmoke2(SVECTOR *pos, SVECTOR *rot);

/******************************************************************************
 * definitions and typedefs and structures
 */

#define SE_M1E1_CATERPILLERDEAD1    (182)
#define SE_M1E1_CATERPILLERDEAD2    (190)
#define M1E1_SOUNDCATERPILLERDEAD1  (30)

/******************************************************************************
 * publics
 */

void M1E1Caterpiller(
    LPM1E1ACTOR lpAct)
{
    SVECTOR svect1;
    SVECTOR svect2;
    SVECTOR svect3;
    int     diff;
    int     nSound;
    int     nLength;
    DG_MDL *model1;
    DG_MDL *model2;

    diff = lpAct->field_D60 - lpAct->field_D8C;
    nSound = 2;

    if(diff > 0)
        nSound += ((diff - (lpAct->field_D68 - lpAct->field_D8C)) * 5) / diff;

    if((GV_Time & 1) == 0)
    {
        DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
        svect3 = lpAct->control.turn;

        while(svect3.vy < -2048)
            svect3.vy += 4096;

        while(svect3.vy > 2048)
            svect3.vy -= 4096;

        memset(&svect1, 0x00, sizeof(svect1));

        model1 = lpAct->field_1C0[0].objs->objs[0].model;
        svect1.vx = model1->lx + (model1->ux - model1->lx) / 2;

        DG_PutVector(&svect1, &svect1, 1);

// clang-format off
        if(lpAct->bInitialize == TRUE)
            lpAct->svectLeftCater = svect1;

        svect2.vx = svect1.vx - lpAct->svectLeftCater.vx;
        svect2.vy = svect1.vy - lpAct->svectLeftCater.vy;
        svect2.vz = svect1.vz - lpAct->svectLeftCater.vz;

        nLength = (SquareRoot0(svect2.vx * svect2.vx
            + svect2.vy * svect2.vy + svect2.vz * svect2.vz)
            * (1024 - abs(ratan2(svect2.vx, svect2.vz) - svect3.vy))) >> 10;

        if(abs(nLength) >= lpAct->nCaterLength)
        {
            svect3 = lpAct->control.rot;
            svect3.vy += 2048;

            if(nLength > 0)
            {
                if((lpAct->nLeftCaterDirection != 1)
                    && (lpAct->nLeftCaterSmokeTCount == 0))
// clang-format on
                {
                    lpAct->nLeftCaterSmokeTCount = 6;
                    AN_CaterpillerSmoke2(&lpAct->lpTarget[4]->center, &svect3);
                }
                lpAct->nLeftCaterDirection = 1;
            }
            else
            {
                if ((lpAct->nLeftCaterDirection != -1)
                    && (lpAct->nLeftCaterSmokeTCount == 0))
                {
                    lpAct->nLeftCaterSmokeTCount = 6;
                    AN_CaterpillerSmoke2(&lpAct->lpTarget[0]->center, &lpAct->control.rot);
                }
                lpAct->nLeftCaterDirection = -1;
            }

            AN_CaterpillerSmoke(&lpAct->lpTarget[rand() % 5]->center);
            DG_InvisibleObjs(lpAct->field_1C0[lpAct->field_E74].objs);

            lpAct->field_E74 += lpAct->nLeftCaterDirection;

            if(lpAct->field_E74 < 0)
                lpAct->field_E74 = 2;

            if(lpAct->field_E74 > 2)
                lpAct->field_E74 = 0;

            DG_VisibleObjs(lpAct->field_1C0[lpAct->field_E74].objs);

            lpAct->svectLeftCater = svect1;
// clang-format off
            if((nSound > 2) && (lpAct->nCaterSoundTCount <= 0))
            {
                if(lpAct->nCaterSoundStartTCount == 0)
                    GM_SeSetPan(&lpAct->control.mov,
                        SE_M1E1_CATERPILLERDEAD1, lpAct->nSoundVolume);
                else
                    GM_SeSetPan(&lpAct->control.mov,
                        SE_M1E1_CATERPILLERDEAD2, lpAct->nSoundVolume);

                lpAct->nCaterSoundTCount = nSound;
                lpAct->nCaterSoundStartTCount = M1E1_SOUNDCATERPILLERDEAD1;
            }
        }
    }
    else    /* 2 回に 1 回実行 */
    {
// clang-format on
        memset(&svect1, 0x00, sizeof(svect1));

        model2 = lpAct->field_46C[0].objs->objs[0].model;
        svect1.vx = model2->lx + (model2->ux - model2->lx) / 2;

        DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
        DG_PutVector(&svect1, &svect1, 1);

        if(lpAct->bInitialize == TRUE)
            lpAct->svectRightCater = svect1;

        svect2.vx = svect1.vx - lpAct->svectRightCater.vx;
        svect2.vy = svect1.vy - lpAct->svectRightCater.vy;
        svect2.vz = svect1.vz - lpAct->svectRightCater.vz;

        nLength = (SquareRoot0(svect2.vx * svect2.vx
            + svect2.vy * svect2.vy + svect2.vz * svect2.vz)
            * (1024 - abs(ratan2(svect2.vx, svect2.vz) - svect3.vy))) >> 10;

        if(abs(nLength) >= lpAct->nCaterLength)
        {
            svect3 = lpAct->control.rot;
            svect3.vy += 2048;

            if(nLength > 0)
            {
                if((lpAct->nRightCaterDirection != 1)
                    && (lpAct->nRightCaterSmokeTCount == 0))
                {
                    lpAct->nRightCaterSmokeTCount = 6;
                    AN_CaterpillerSmoke2(&lpAct->lpTarget[9]->center, &svect3);
                }
                lpAct->nRightCaterDirection = 1;
            }
            else
            {
                if((lpAct->nRightCaterDirection != -1)
                    && (lpAct->nRightCaterSmokeTCount == 0))
                {
                    lpAct->nRightCaterSmokeTCount = 6;
                    AN_CaterpillerSmoke2(&lpAct->lpTarget[5]->center, &lpAct->control.rot);
                }
                lpAct->nRightCaterDirection = -1;
            }

            AN_CaterpillerSmoke(&lpAct->lpTarget[(rand() % 5) + 5]->center);
            DG_InvisibleObjs(lpAct->field_46C[lpAct->field_E78].objs);

            lpAct->field_E78 += lpAct->nLeftCaterDirection;

            if(lpAct->field_E78 < 0)
                lpAct->field_E78 = 2;

            if(lpAct->field_E78 > 2)
                lpAct->field_E78 = 0;

            DG_VisibleObjs(lpAct->field_46C[lpAct->field_E78].objs);

            lpAct->svectRightCater = svect1;

            if((nSound > 2) && (lpAct->nCaterSoundTCount <= 0))
            {
                if(lpAct->nCaterSoundStartTCount == 0)
                    GM_SeSetPan(&lpAct->control.mov,
                        SE_M1E1_CATERPILLERDEAD1, lpAct->nSoundVolume);
                else
                    GM_SeSetPan(&lpAct->control.mov,
                        SE_M1E1_CATERPILLERDEAD2, lpAct->nSoundVolume);

                lpAct->nCaterSoundTCount = nSound;
                lpAct->nCaterSoundStartTCount = M1E1_SOUNDCATERPILLERDEAD1;
            }
        }
    }
}

void M1E1GetCaterpillerVertex(
    OBJECT*  obj1,
    OBJECT*  obj2,
    SVECTOR* svectPos,
    BOOL     arg3)
{
    DG_MDL* lpModel;
    int     vx;

    /* left caterpillar */
    lpModel = obj1->objs->objs[0].model;
    vx = lpModel->lx;
    if(arg3 == TRUE)
        vx += (lpModel->ux - vx) >> 1;

    svectPos[0].vx = vx;
    svectPos[0].vy = obj1->objs->objs[0].model->ly;
    svectPos[0].vz = 2 * obj1->objs->objs[0].model->uz / 3;

    svectPos[1].vx = vx;
    svectPos[1].vy = obj1->objs->objs[0].model->ly;
    svectPos[1].vz = obj1->objs->objs[0].model->uz / 3;

    svectPos[2].vx = vx;
    svectPos[2].vy = obj1->objs->objs[0].model->ly;
    svectPos[2].vz = 0;

    svectPos[3].vx = vx;
    svectPos[3].vy = obj1->objs->objs[0].model->ly;
    svectPos[3].vz = obj1->objs->objs[0].model->lz / 3;

    svectPos[4].vx = vx;
    svectPos[4].vy = obj1->objs->objs[0].model->ly;
    svectPos[4].vz = (2 * obj1->objs->objs[0].model->lz) / 3;

    /* right caterpillar */
    lpModel = obj2->objs->objs[0].model;
    vx = lpModel->ux;
    if(arg3 == TRUE)
        vx += (lpModel->lx - vx) >> 1;

    svectPos[5].vx = vx;
    svectPos[5].vy = obj2->objs->objs[0].model->ly;
    svectPos[5].vz = 2 * obj2->objs->objs[0].model->uz / 3;

    svectPos[6].vx = vx;
    svectPos[6].vy = obj2->objs->objs[0].model->ly;
    svectPos[6].vz = obj2->objs->objs[0].model->uz / 3;

    svectPos[7].vx = vx;
    svectPos[7].vy = obj2->objs->objs[0].model->ly;
    svectPos[7].vz = 0;

    svectPos[8].vx = vx;
    svectPos[8].vy = obj2->objs->objs[0].model->ly;
    svectPos[8].vz = obj2->objs->objs[0].model->lz / 3;

    svectPos[9].vx = vx;
    svectPos[9].vy = obj2->objs->objs[0].model->ly;
    svectPos[9].vz = 2 * obj2->objs->objs[0].model->lz / 3;
}
