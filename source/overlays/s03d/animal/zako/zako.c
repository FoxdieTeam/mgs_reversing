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
#include "enemy/glight.h"
#include "chara/snake/shadow.h"
#include "okajima/blood.h"
#include "bullet/tenage.h"
#include "okajima/bullet.h"

extern int s03d_dword_800C39B0;
extern int s03d_dword_800C39B8;
extern int s03d_dword_800C39C0;
extern int s03d_dword_800C39C8;

extern int s03d_dword_800DC2F8;
extern SVECTOR s03d_dword_800C39A8;
int  s03d_800CCE3C(Work *work, int name, int where);

// rdata of zako.c: 3 strings of s03d_800CCE3C
const char s03d_dword_800DB3C4[] = {'i', 'p', 'p', 'a'};
const char s03d_dword_800DB3C8[] = {'n', 'h', 'e', 'i'};
const char s03d_dword_800DB3CC[] = {0x0, 0x0, 0x0, 0x0};

const char s03d_dword_800DB3D0[] = {'e', 'n', 'e', 'm'};
const char s03d_dword_800DB3D4[] = {'y', 0x0, 0x0, 0x0};

const char s03d_dword_800DB3D8[] = {'f', 'a', 'm', 'a'};
const char s03d_dword_800DB3DC[] = {'s', 0x0, 0x0, 0x0};

void s03d_800D153C(Work *work);
void ZakoCom_800D4050(int idx);
int  ZakoCom_800D3FF4(Work *work);
int  ZakoCom_800D4038(void);
int  Zako_800D0EF0(Work *work, int index);
void s03d_800CCC54(Work *work);
void s03d_800CD054(Work *work);

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

    if (s03d_dword_800DC2F8 == 13 && ZAKOCOM_MGR->entries[work->param.index].field_4 == 1)
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
    ZakoCom_800D4050(work->param.index);
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

void s03d_800CD1C4(Work *work, int name, int where)
{
    char *opt;
    int   i;

    s03d_800CCE3C(work, name, where);
    work->param.index = ZakoCom_800D3FF4(work);
    if (work->param.index < 0)
    {
        fprintf(0, "Err not enough work !!\n");
    }

    work->field_B04 = ZakoCom_800D4038();
    work->param.roots[0] = 0;
    work->param.c_root = 0;
    opt = GCL_GetOption('r');
    if (opt)
    {
        if (Zako_800CD16C(opt, work->param.roots) >= 4)
        {
            fprintf(0, "Err Err Err Change Root Num Over !!\n");
        }
    }

    switch (work->param.index)
    {
    case 0:
        work->field_B64 = 3000;
        break;
    case 1:
        work->field_B64 = 4000;
        break;
    case 2:
        work->field_B64 = 7000;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        work->field_B64 = 8000;
        break;
    }

    work->param.life = 192;
    opt = GCL_GetOption('l');
    if (opt)
    {
        work->param.life = GCL_StrToInt(opt);
    }

    work->param.faint = 255;
    opt = GCL_GetOption('f');
    if (opt)
    {
        work->param.faint = GCL_StrToInt(opt);
    }

    work->param.damage = 40;
    opt = GCL_GetOption('z');
    if (opt)
    {
        work->param.damage = GCL_StrToInt(opt);
    }

    work->param.blood = 'A';
    opt = GCL_GetOption('b');
    if (opt)
    {
        work->param.blood = GCL_StrToInt(opt);
    }

    work->param.defends[work->param.c_root] = 255;
    opt = GCL_GetOption('n');
    if (opt)
    {
        if (Zako_800CD16C(opt, work->param.defends) >= 4)
        {
            fprintf(0, "Err Err Err Change Defend Num Over !!\n");
        }
    }

    work->param.area = 'A';
    opt = GCL_GetOption('a');
    if (opt)
    {
        work->param.area = GCL_StrToInt(opt);
    }

    if (work->param.area == 'S')
    {
        Zako_800D0EF0(work, 1);
    }

    fprintf(0, "Life=%d Faint=%d Blood=%c Area=%c \n", work->param.life, work->param.faint, work->param.blood, work->param.area);

    if (s03d_800CD0C8(work) < 0)
    {
        fprintf(1, "watchar.c : action point Err\n");
    }

    work->target = GM_AllocTarget();
    if (work->target)
    {
        Zako_800CCCF4(work);
    }

    work->field_AC8 = 0;
    work->field_ACA = 0;
    work->field_ACC = 0;
    work->field_ACE = 0;
    work->field_AD0 = 0;
    work->field_AD4 = 0;

    work->field_B48 = work->nodes[0];
    work->field_B5C = HZD_GetAddress(work->control.map->hzd, &work->field_B48, -1);

    work->vision.range = 512;
    work->vision.length = 4000;
    work->field_B28 = 0;
    work->vision.facedir = 0;
    work->field_AE8 = 0;
    work->field_AE4 = 0;
    work->field_B60 = GM_CurrentMap;
    work->field_B34 = s03d_dword_800C39A8;
    work->field_AF0 = 0;
    work->control.mov = work->nodes[0];
    work->field_AF6 = 0;
    work->field_AF8 = 0;
    work->field_B00 = 1;
    work->field_BA0 = 0;

    for (i = 0; i < 8; i++)
    {
        work->modetime[i] = 0;
    }

    work->modetime[7] = 0x17;
    work->modetime[4] = 0xFF;

    GM_ConfigControlRadarparam(&work->control, 0, 512, 4000, 0);

    work->field_B40 = work->nodes[0];
    work->field_B54 = GM_CurrentMap;
    work->field_B50 = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);
    work->field_B58 = work->field_B74 = work->field_B50;
    work->field_B80 = work->field_B40;
}

void *s03d_800CD5A0(int name, int where)
{
    Work *work;

    work = GV_NewActor(4, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s03d_800CCC54, s03d_800CD054, "zako.c");
        s03d_800CD1C4(work, name, where);
    }
    return work;
}

