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

SVECTOR ZAKO_NO_POINT = {30000, 30000, 30000};
SVECTOR ZAKO_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO_ATTACK_SIZE = {400, 500, 400};
SVECTOR ZAKO_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO_TOUCH_FORCE = {0, 0, 0};

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
    if (work->visible != 0)
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

    if (ZakoGameFlag == 13 && ZakoCommand.watchers[work->param.index].field_4 == 1)
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

    GM_SetTarget(t, TARGET_FLAG, ENEMY_SIDE, &ZAKO_TARGET_SIZE);
    GM_SetPowerTarget(t, POWER_DECREASE, -1, b14, b16, &ZAKO_TARGET_FORCE);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_SetC4Target(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->attack, TARGET_POWER, PLAYER_SIDE, &ZAKO_ATTACK_SIZE);
    GM_SetPowerTarget(&work->attack, POWER_CONST | POWER_EXPLODE, 5, 0, 3, &ZAKO_ATTACK_FORCE);
}
void Zako_800CCDE0(Work *work)
{
    ACT *act;

    act = &work->act;
    GV_ZeroMemory(act, sizeof(ACT));
    act->field_00 = 0;
    act->r_sphere = 450;
    act->field_1C = 1;
    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

int s03d_800CCE3C(Work *work, int name, int where)
{
    SVECTOR  indices;
    CONTROL *control;
    OBJECT  *body;
    OBJECT  *weapon;
    int      i;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlAttribute(control, RADAR_VISIBLE | RADAR_SIGHT);
    GM_ConfigControlInterp(control, 4);

    body = &work->body;
    weapon = &work->weapon;

    GM_InitObject(body, GV_StrCode("ippanhei"), 0x32D, GV_StrCode("enemy"));
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("enemy"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);

    work->models[1] = work->body.objs->def;
    work->models[0] = GV_GetCache(GV_CacheID(0xC37, 'k'));
    work->lod = 1;

    work->hom = GM_SetHomingTarget(&work->body.objs->objs[6].world, control);

    GM_InitObject(weapon, GV_StrCode("famas"), 0x6D, 0);
    GM_ConfigObjectLight(weapon, work->light);
    GM_ConfigObjectRoot(weapon, body, 4);

    for (i = 0; i < 0; i++)
    {
        work->putchar[i] = NULL;
    }

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow2(control, body, indices, &work->enable_shadow);
    work->glight = NewGunLight(&body->objs->objs[4].world, &work->enable_glight);

    Zako_800D0EF0(work, 0);
    Zako_800CCDE0(work);
    return 0;
}

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

    work->n_dead = ZakoCom_800D4038();
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
        work->chase_dis = 3000;
        break;
    case 1:
        work->chase_dis = 4000;
        break;
    case 2:
        work->chase_dis = 7000;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        work->chase_dis = 8000;
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

    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->think4 = 0;
    work->count3 = 0;
    work->field_AD4 = 0;

    work->target_pos = work->nodes[0];
    work->target_addr = HZD_GetAddress(work->control.map->hzd, &work->target_pos, -1);

    work->vision.range = 512;
    work->vision.length = 4000;
    work->alert_level = 0;
    work->vision.facedir = 0;
    work->pad.sound = 0;
    work->pad.time = 0;
    work->target_map = GM_CurrentMap;
    work->player_pos = ZAKO_NO_POINT;
    work->subweapon = 0;
    work->control.mov = work->nodes[0];
    work->field_AF6 = 0;
    work->field_AF8 = 0;
    work->visible = 1;
    work->field_BA0 = 0;

    for (i = 0; i < 8; i++)
    {
        work->modetime[i] = 0;
    }

    work->modetime[7] = 0x17;
    work->modetime[4] = 0xFF;

    GM_ConfigControlRadarparam(&work->control, 0, 512, 4000, 0);

    work->start_pos = work->nodes[0];
    work->start_map = GM_CurrentMap;
    work->start_addr = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);
    work->last_addr = work->next_addr = work->start_addr;
    work->next_pos = work->start_pos;
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

