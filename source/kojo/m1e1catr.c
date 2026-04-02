#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "m1e1.h"

void demothrd_2_8007DA94(SVECTOR *pPosition, SVECTOR *pRotation);
void AN_CaterpillerSmoke(SVECTOR *pos); // todo: split demo.c

void M1E1Caterpiller(M1E1Work *lpAct)
{
    SVECTOR svect1;
    SVECTOR svect2;
    SVECTOR svect3;
    int     diff;
    int     nSound;
    int     nLength;
    DG_MDL *model;
    DG_MDL *model2;

    diff = lpAct->field_D60 - lpAct->field_D8C;
    nSound = 2;

    if (diff > 0)
    {
        nSound += ((diff - (lpAct->field_D68 - lpAct->field_D8C)) * 5) / diff;
    }

    if ((GV_Time & 1) == 0)
    {
        DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
        svect3 = lpAct->control.turn;

        while (svect3.vy < -2048)
        {
            svect3.vy += 4096;
        }

        while (svect3.vy > 2048)
        {
            svect3.vy -= 4096;
        }

        memset(&svect1, 0, 8);

        model = lpAct->field_1C0[0].objs->objs[0].model;
        svect1.vx = model->min.vx + (model->max.vx - model->min.vx) / 2;

        DG_PutVector(&svect1, &svect1, 1);

        if (lpAct->bInitialize == TRUE)
        {
            lpAct->svectLeftCater = svect1;
        }

        svect2.vx = svect1.vx - lpAct->svectLeftCater.vx;
        svect2.vy = svect1.vy - lpAct->svectLeftCater.vy;
        svect2.vz = svect1.vz - lpAct->svectLeftCater.vz;

        nLength = SquareRoot0(svect2.vx * svect2.vx
            + svect2.vy * svect2.vy + svect2.vz * svect2.vz);
        nLength = (nLength * (1024 - abs(ratan2(svect2.vx, svect2.vz) - svect3.vy))) >> 10;

        if (abs(nLength) < lpAct->nCaterLength)
        {
            return;
        }

        svect3 = lpAct->control.rot;
        svect3.vy += 2048;

        if (nLength > 0)
        {
            if (lpAct->nLeftCaterDirection != 1 && lpAct->nLeftCaterSmokeTCount == 0)
            {
                lpAct->nLeftCaterSmokeTCount = 6;
                demothrd_2_8007DA94(&lpAct->field_718_targets[4]->center, &svect3);
            }

            lpAct->nLeftCaterDirection = 1;
        }
        else
        {
            if (lpAct->nLeftCaterDirection != -1 && lpAct->nLeftCaterSmokeTCount == 0)
            {
                lpAct->nLeftCaterSmokeTCount = 6;
                demothrd_2_8007DA94(&lpAct->field_718_targets[0]->center, &lpAct->control.rot);
            }

            lpAct->nLeftCaterDirection = -1;
        }

        AN_CaterpillerSmoke(&lpAct->field_718_targets[rand() % 5]->center);
        DG_InvisibleObjs(lpAct->field_1C0[lpAct->field_E74].objs);

        lpAct->field_E74 += lpAct->nLeftCaterDirection;

        if (lpAct->field_E74 < 0)
        {
            lpAct->field_E74 = 2;
        }

        if (lpAct->field_E74 > 2)
        {
            lpAct->field_E74 = 0;
        }

        DG_VisibleObjs(lpAct->field_1C0[lpAct->field_E74].objs);

        lpAct->svectLeftCater = svect1;

        if ((nSound >= 3) && (lpAct->nCaterSoundTCount <= 0))
        {
            if (lpAct->nCaterSoundStartTCount == 0)
            {
                GM_SeSetPan(&lpAct->control.mov, 182, lpAct->nSoundVolume);
            }
            else
            {
                GM_SeSetPan(&lpAct->control.mov, 190, lpAct->nSoundVolume);
            }

            lpAct->nCaterSoundTCount = nSound;
            lpAct->nCaterSoundStartTCount = 30;
        }
    }
    else
    {
        memset(&svect1, 0, 8);

        model2 = lpAct->field_46C[0].objs->objs[0].model;
        svect1.vx = model2->min.vx + (model2->max.vx - model2->min.vx) / 2;

        DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
        DG_PutVector(&svect1, &svect1, 1);

        if (lpAct->bInitialize == TRUE)
        {
            lpAct->svectRightCater = svect1;
        }

        svect2.vx = svect1.vx - lpAct->svectRightCater.vx;
        svect2.vy = svect1.vy - lpAct->svectRightCater.vy;
        svect2.vz = svect1.vz - lpAct->svectRightCater.vz;

        nLength = SquareRoot0(svect2.vx * svect2.vx
            + svect2.vy * svect2.vy + svect2.vz * svect2.vz);
        nLength = (nLength * (1024 - abs(ratan2(svect2.vx, svect2.vz) - svect3.vy))) >> 10;

        if (abs(nLength) < lpAct->nCaterLength)
        {
            return;
        }

        svect3 = lpAct->control.rot;
        svect3.vy += 2048;

        if (nLength > 0)
        {
            if (lpAct->nRightCaterDirection != 1 && lpAct->nRightCaterSmokeTCount == 0)
            {
                lpAct->nRightCaterSmokeTCount = 6;
                demothrd_2_8007DA94(&lpAct->field_718_targets[9]->center, &svect3);
            }

            lpAct->nRightCaterDirection = 1;
        }
        else
        {
            if (lpAct->nRightCaterDirection != -1 && lpAct->nRightCaterSmokeTCount == 0)
            {
                lpAct->nRightCaterSmokeTCount = 6;
                demothrd_2_8007DA94(&lpAct->field_718_targets[5]->center, &lpAct->control.rot);
            }

            lpAct->nRightCaterDirection = -1;
        }

        AN_CaterpillerSmoke(&lpAct->field_718_targets[(rand() % 5) + 5]->center);
        DG_InvisibleObjs(lpAct->field_46C[lpAct->field_E78].objs);

        lpAct->field_E78 += lpAct->nLeftCaterDirection;

        if (lpAct->field_E78 < 0)
        {
            lpAct->field_E78 = 2;
        }

        if (lpAct->field_E78 > 2)
        {
            lpAct->field_E78 = 0;
        }

        DG_VisibleObjs(lpAct->field_46C[lpAct->field_E78].objs);

        lpAct->svectRightCater = svect1;

        if ((nSound >= 3) && (lpAct->nCaterSoundTCount <= 0))
        {
            if (lpAct->nCaterSoundStartTCount == 0)
            {
                GM_SeSetPan(&lpAct->control.mov, 182, lpAct->nSoundVolume);
            }
            else
            {
                GM_SeSetPan(&lpAct->control.mov, 190, lpAct->nSoundVolume);
            }

            lpAct->nCaterSoundTCount = nSound;
            lpAct->nCaterSoundStartTCount = 30;
        }
    }
}

void M1E1GetCaterpillerVertex(OBJECT *obj1, OBJECT *obj2, SVECTOR *pos, int a4)
{
    DG_MDL *model;
    int vx;

    /* left caterpillar */
    model = obj1->objs->objs[0].model;
    vx = model->min.vx;
    if ( a4 == 1 )
    {
        vx += (model->max.vx - vx) >> 1;
    }

    pos[0].vx = vx;
    pos[0].vy = obj1->objs->objs[0].model->min.vy;
    pos[0].vz = 2 * obj1->objs->objs[0].model->max.vz / 3;

    pos[1].vx = vx;
    pos[1].vy = obj1->objs->objs[0].model->min.vy;
    pos[1].vz = obj1->objs->objs[0].model->max.vz / 3;

    pos[2].vx = vx;
    pos[2].vy = obj1->objs->objs[0].model->min.vy;
    pos[2].vz = 0;

    pos[3].vx = vx;
    pos[3].vy = obj1->objs->objs[0].model->min.vy;
    pos[3].vz = obj1->objs->objs[0].model->min.vz / 3;

    pos[4].vx = vx;
    pos[4].vy = obj1->objs->objs[0].model->min.vy;
    pos[4].vz = (2 * obj1->objs->objs[0].model->min.vz) / 3;

    /* right caterpillar */
    model = obj2->objs->objs[0].model;
    vx = model->max.vx;
    if ( a4 == 1 )
    {
        vx += (model->min.vx - vx) >> 1;
    }

    pos[5].vx = vx;
    pos[5].vy = obj2->objs->objs[0].model->min.vy;
    pos[5].vz = 2 * obj2->objs->objs[0].model->max.vz / 3;

    pos[6].vx = vx;
    pos[6].vy = obj2->objs->objs[0].model->min.vy;
    pos[6].vz = obj2->objs->objs[0].model->max.vz / 3;

    pos[7].vx = vx;
    pos[7].vy = obj2->objs->objs[0].model->min.vy;
    pos[7].vz = 0;

    pos[8].vx = vx;
    pos[8].vy = obj2->objs->objs[0].model->min.vy;
    pos[8].vz = obj2->objs->objs[0].model->min.vz / 3;

    pos[9].vx = vx;
    pos[9].vy = obj2->objs->objs[0].model->min.vy;
    pos[9].vz = 2 * obj2->objs->objs[0].model->min.vz / 3;
}
