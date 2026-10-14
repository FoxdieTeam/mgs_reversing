#include "zako.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "mgstype.h"
#include "game/game.h"
#include "game/item.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "anime/animconv/anime.h"
#include "enemy/l_sight.h"
#include "enemy/asiato.h"
#include "okajima/blood.h"
#include "bullet/tenage.h"
#include "okajima/bullet.h"

extern int s03d_dword_800C39B0;
extern int s03d_dword_800C39B8;
extern int s03d_dword_800C39C0;
extern int s03d_dword_800C39C8;

extern int s03d_dword_800DC2F8;

void s03d_800D153C(Work *work);
void ZakoCom_800D4050(int idx);

void Zako_800CCAB0(DG_OBJS *objs, DG_DEF *def)
{
    DG_OBJ *obj;
    int i;

    DG_FreeObjsPacket(objs, 0);
    DG_FreeObjsPacket(objs, 1);

    objs->def = def;
    obj = objs->objs;
    for (i = 0; i < 16; i++)
    {
        obj->model = &def->models[i];
        obj->n_packs = def->models[i].n_faces;
        obj++;
    }
}

void s03d_800CCB2C(Work *work)
{
    if (work->field_B00 != 0)
    {
        if ( GM_GameStatus & STATE_CAM_CHANGE || GM_Camera.first_person )
        {
            if (work->lod != 1)
            {
                work->lod = 1;
                Zako_800CCAB0(work->body.objs, work->models[1]);
            }
        }
        else
        {
            if (work->lod != 0)
            {
                work->lod = 0;
                Zako_800CCAB0(work->body.objs, work->models[0]);
            }
        }

        DG_VisibleObjs(work->body.objs);
        DG_VisibleObjs(work->weapon.objs);
        *work->enable_shadow = 1;
        *work->enable_glight = 1;
    }
    else
    {
        DG_InvisibleObjs(work->body.objs);
        DG_InvisibleObjs(work->weapon.objs);
        *work->enable_shadow = 0;
        *work->enable_glight = 0;
    }
}

void s03d_800CCC54(Work *work)
{
    CONTROL *control;

    control = &work->control;

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    DG_GetLightMatrix2(&control->mov, work->light);

    s03d_800D153C(work);
    GM_MoveTarget(work->target, &control->mov);

    if (s03d_dword_800DC2F8 == 13 && ZAKOCOM_MGR->entries[work->param.fAF8].field_4 == 1)
    {
        GV_DestroyActor(work);
    }

    s03d_800CCB2C(work);
}

void Zako_800CCCF4(Work *work)
{
    TARGET *t = work->target;
    int     b14 = work->param.life;
    int     b16 = work->param.faint;

    GM_SetTarget(t, 0x9E, 2, (SVECTOR *)&s03d_dword_800C39B0);
    GM_SetPowerTarget(t, 1, -1, b14, b16, (SVECTOR *)&s03d_dword_800C39B8);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_SetC4Target(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->attack, 4, 1, (SVECTOR *)&s03d_dword_800C39C0);
    GM_SetPowerTarget(&work->attack, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
}
void Zako_800CCDE0(Work *work)
{
    short *p = (short *)&work->act.field_00;

    GV_ZeroMemory(p, 0x20);
    work->act.field_00 = 0;
    p[0x0D] = 0x1C2;
    p[0x0E] = 1;
    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCE3C.s")

void s03d_800CD054(Work *work)
{
    ZakoCom_800D4050(work->param.fAF8);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->glight);
    GV_DestroyActor(work->shadow);
    GM_ResetHomingTarget(work->hom);
}

int s03d_800CD0C8(Work *work)
{
    PARAM   *param;
    HZD_PAT *patrol;
    HZD_PTP *points;
    int      i;

    param = &work->param;

    patrol = work->control.map->hzd->def->routes;
    patrol += param->roots[param->c_root];

    work->n_nodes = patrol->n_points;

    if (work->n_nodes <= 0)
    {
        return -1;
    }

    points = patrol->points;
    for (i = 0; i < work->n_nodes; i++)
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    return 0;
}

int Zako_800CD16C(char *opt, char *out)
{
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != NULL)
    {
        *out++ = GCL_StrToInt(str);
        count++;
    }
    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD1C4.s")

