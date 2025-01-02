#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"

typedef struct M1E1Work
{
    GV_ACT  actor;
    CONTROL control;
    MATRIX  field_9C_light_matrices[2];
    OBJECT  field_DC;
    OBJECT  field_1C0[3];
    OBJECT  field_46C[3];
    TARGET *field_718_targets[10];
    int     field_740;
    char    field_744[0x61C];
    int     field_D60;
    int     field_D64;
    int     field_D68;
    int     field_D6C;
    char    field_D70[0x1C];
    int     field_D8C;
    char    field_D90[0xD0];
    int     field_E60;
    int     field_E64;
    int     field_E68;
    int     field_E6C;
    int     field_E70;
    int     field_E74;
    int     field_E78;
    int     field_E7C;
    int     field_E80;
    int     field_E84;
    int     field_E88;
    SVECTOR field_E8C;
    SVECTOR field_E94;
    char    field_E9C[0xC4];
    int     field_F60;
    int     field_F64;
    int     field_F68;
    int     field_F6C;
    int     field_F70;
    int     field_F74;
} M1E1Work;

void demothrd_2_8007DA94(SVECTOR *pPosition, SVECTOR *pRotation);
void AN_CaterpillerSmoke_8007DA28(SVECTOR *pos); // todo: split demo.c

void M1E1Caterpiller(M1E1Work *work)
{
    SVECTOR sp10;
    SVECTOR sp18;
    SVECTOR rotation;
    int     diff;
    int     f70;
    int     length;
    DG_MDL *pMdl;
    DG_MDL *pMdl2;

    diff = work->field_D60 - work->field_D8C;
    f70 = 2;

    if (diff > 0)
    {
        f70 += ((diff - (work->field_D68 - work->field_D8C)) * 5) / diff;
    }

    if ((GV_Time & 1) == 0)
    {
        DG_SetPos2(&work->control.mov, &work->control.turn);
        rotation = work->control.turn;

        while (rotation.vy < -2048)
        {
            rotation.vy += 4096;
        }

        while (rotation.vy > 2048)
        {
            rotation.vy -= 4096;
        }

        memset(&sp10, 0, 8);

        pMdl = work->field_1C0[0].objs->objs[0].model;
        sp10.vx = pMdl->min.vx + (pMdl->max.vx - pMdl->min.vx) / 2;

        DG_PutVector(&sp10, &sp10, 1);

        if (work->field_740 == 1)
        {
            work->field_E8C = sp10;
        }

        sp18.vx = sp10.vx - work->field_E8C.vx;
        sp18.vy = sp10.vy - work->field_E8C.vy;
        sp18.vz = sp10.vz - work->field_E8C.vz;

        length = SquareRoot0(sp18.vx * sp18.vx + sp18.vy * sp18.vy + sp18.vz * sp18.vz);
        length = (length * (1024 - abs(ratan2(sp18.vx, sp18.vz) - rotation.vy))) >> 10;

        if (abs(length) < work->field_E84)
        {
            return;
        }

        rotation = work->control.rot;
        rotation.vy += 2048;

        if (length > 0)
        {
            if (work->field_E7C != 1 && work->field_F60 == 0)
            {
                work->field_F60 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[4]->center, &rotation);
            }

            work->field_E7C = 1;
        }
        else
        {
            if (work->field_E7C != -1 && work->field_F60 == 0)
            {
                work->field_F60 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[0]->center, &work->control.rot);
            }

            work->field_E7C = -1;
        }

        AN_CaterpillerSmoke_8007DA28(&work->field_718_targets[rand() % 5]->center);
        DG_InvisibleObjs(work->field_1C0[work->field_E74].objs);

        work->field_E74 += work->field_E7C;

        if (work->field_E74 < 0)
        {
            work->field_E74 = 2;
        }

        if (work->field_E74 > 2)
        {
            work->field_E74 = 0;
        }

        DG_VisibleObjs(work->field_1C0[work->field_E74].objs);

        work->field_E8C = sp10;

        if ((f70 >= 3) && (work->field_F70 <= 0))
        {
            if (work->field_F74 == 0)
            {
                sub_80032B40(&work->control.mov, 182, work->field_E60);
            }
            else
            {
                sub_80032B40(&work->control.mov, 190, work->field_E60);
            }

            work->field_F70 = f70;
            work->field_F74 = 30;
        }
    }
    else
    {
        memset(&sp10, 0, 8);

        pMdl2 = work->field_46C[0].objs->objs[0].model;
        sp10.vx = pMdl2->min.vx + (pMdl2->max.vx - pMdl2->min.vx) / 2;

        DG_SetPos2(&work->control.mov, &work->control.turn);
        DG_PutVector(&sp10, &sp10, 1);

        if (work->field_740 == 1)
        {
            work->field_E94 = sp10;
        }

        sp18.vx = sp10.vx - work->field_E94.vx;
        sp18.vy = sp10.vy - work->field_E94.vy;
        sp18.vz = sp10.vz - work->field_E94.vz;

        length = SquareRoot0(sp18.vx * sp18.vx + sp18.vy * sp18.vy + sp18.vz * sp18.vz);
        length = (length * (1024 - abs(ratan2(sp18.vx, sp18.vz) - rotation.vy))) >> 10;

        if (abs(length) < work->field_E84)
        {
            return;
        }

        rotation = work->control.rot;
        rotation.vy += 2048;

        if (length > 0)
        {
            if (work->field_E80 != 1 && work->field_F64 == 0)
            {
                work->field_F64 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[9]->center, &rotation);
            }

            work->field_E80 = 1;
        }
        else
        {
            if (work->field_E80 != -1 && work->field_F64 == 0)
            {
                work->field_F64 = 6;
                demothrd_2_8007DA94(&work->field_718_targets[5]->center, &work->control.rot);
            }

            work->field_E80 = -1;
        }

        AN_CaterpillerSmoke_8007DA28(&work->field_718_targets[(rand() % 5) + 5]->center);
        DG_InvisibleObjs(work->field_46C[work->field_E78].objs);

        work->field_E78 += work->field_E7C;

        if (work->field_E78 < 0)
        {
            work->field_E78 = 2;
        }

        if (work->field_E78 > 2)
        {
            work->field_E78 = 0;
        }

        DG_VisibleObjs(work->field_46C[work->field_E78].objs);

        work->field_E94 = sp10;

        if ((f70 >= 3) && (work->field_F70 <= 0))
        {
            if (work->field_F74 == 0)
            {
                sub_80032B40(&work->control.mov, 182, work->field_E60);
            }
            else
            {
                sub_80032B40(&work->control.mov, 190, work->field_E60);
            }

            work->field_F70 = f70;
            work->field_F74 = 30;
        }
    }
}

void M1E1GetCaterpillerVertex(OBJECT *pE1, OBJECT *pE2, SVECTOR *pSmokeVecs, int a4)
{
    DG_MDL *model; // $v0
    int vx; // $v1
    DG_MDL *v8; // $v0
    int v9; // $v1

    model = pE1->objs->objs[0].model;
    vx = model->min.vx;
    if ( a4 == 1 )
    {
        vx += (model->max.vx - vx) >> 1;
    }

    pSmokeVecs[0].vx = vx;
    pSmokeVecs[0].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[0].vz = 2 * pE1->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[1].vx = vx;
    pSmokeVecs[1].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[1].vz = pE1->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[2].vx = vx;
    pSmokeVecs[2].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[2].vz = 0;

    pSmokeVecs[3].vx = vx;
    pSmokeVecs[3].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[3].vz = pE1->objs->objs[0].model->min.vz / 3;

    pSmokeVecs[4].vx = vx;
    pSmokeVecs[4].vy = pE1->objs->objs[0].model->min.vy;
    pSmokeVecs[4].vz = (2 * pE1->objs->objs[0].model->min.vz) / 3;

    v8 = pE2->objs->objs[0].model;
    v9 = v8->max.vx;
    if ( a4 == 1 )
    {
        v9 += (v8->min.vx - v9) >> 1;
    }

    pSmokeVecs[5].vx = v9;
    pSmokeVecs[5].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[5].vz = 2 * pE2->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[6].vx = v9;
    pSmokeVecs[6].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[6].vz = pE2->objs->objs[0].model->max.vz / 3;

    pSmokeVecs[7].vx = v9;
    pSmokeVecs[7].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[7].vz = 0;

    pSmokeVecs[8].vx = v9;
    pSmokeVecs[8].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[8].vz = pE2->objs->objs[0].model->min.vz / 3;

    pSmokeVecs[9].vx = v9;
    pSmokeVecs[9].vy = pE2->objs->objs[0].model->min.vy;
    pSmokeVecs[9].vz = 2 * pE2->objs->objs[0].model->min.vz / 3;
}
