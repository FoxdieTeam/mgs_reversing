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

void M1E1Caterpiller(M1E1Work *work)
{
    SVECTOR sp10;
    SVECTOR sp18;
    SVECTOR rotation;
    int     diff;
    int     f70;
    int     length;
    DG_MDL *model;
    DG_MDL *model2;

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

        model = work->field_1C0[0].objs->objs[0].model;
        sp10.vx = model->min.vx + (model->max.vx - model->min.vx) / 2;

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

        AN_CaterpillerSmoke(&work->field_718_targets[rand() % 5]->center);
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

        model2 = work->field_46C[0].objs->objs[0].model;
        sp10.vx = model2->min.vx + (model2->max.vx - model2->min.vx) / 2;

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

        AN_CaterpillerSmoke(&work->field_718_targets[(rand() % 5) + 5]->center);
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
