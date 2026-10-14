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
extern int s03d_dword_800C3A90[];
extern int s03d_dword_800C3A64;
extern int s03d_dword_800C3A6C;
extern int s03d_dword_800C3A84;
extern int s03d_dword_800C3A88;
extern int s03d_dword_800C3A74;
extern int s03d_dword_800C3A7C;
extern short s03d_word_800C39F0[2];
extern int s03d_dword_800C39F4;
extern short s03d_word_800C3A00[2];
extern int s03d_dword_800C3A04;
extern int s03d_dword_800C3A08;
extern int s03d_dword_800C3A0C;
extern short s03d_word_800C39E0[4];
extern SVECTOR s03d_dword_800C3A44;
extern SVECTOR s03d_dword_800C3A4C;
extern SVECTOR s03d_dword_800C3A54;
extern int s03d_dword_800C39FC;
extern short s03d_word_800C3A38[2];
extern int s03d_dword_800DC2F4;
extern short s03d_word_800C3A3C[2];
extern short s03d_word_800C39E8[2];
extern short s03d_word_800C39EC[2];
extern int s03d_dword_800DC310;
extern SVECTOR s03d_dword_800C3B88;
extern int s03d_dword_800C3A5C;
extern SVECTOR s03d_dword_800C3AA0;
extern SVECTOR s03d_dword_800C3AA8;
extern short s03d_word_800C3A10[20];

extern int s03d_dword_800DC2F8;

// rdata of zako.c: starts at 0x800DB4B4 (the "zako.c" string before it belongs to the
// object linked in front, its padding byte is object padding)
const char s03d_dword_800DB4B4[] = {' ', 'm', 'e', 'r'};
const char s03d_dword_800DB4B8[] = {'y', 'l', ' ', 'K'};
const char s03d_dword_800DB4BC[] = {'I', 'L', 'L', 'E'};
const char s03d_dword_800DB4C0[] = {'D', ' ', '!', '!'};
const char s03d_dword_800DB4C4[] = {'!', ' ', '\n', 0x0};
const char s03d_dword_800DB4C8[] = {' ', 'S', 'N', 'A'};
const char s03d_dword_800DB4CC[] = {'K', 'E', ' ', 'K'};
const char s03d_dword_800DB4D0[] = {'I', 'L', 'L', 'E'};
const char s03d_dword_800DB4D4[] = {'D', ' ', '!', '!'};
const char s03d_dword_800DB4D8[] = {'!', ' ', '\n', 0x0};

const int s03d_dword_800DB4DC = 0x800CD840;
const int s03d_dword_800DB4E0 = 0x800CD8D8;
const int s03d_dword_800DB4E4 = 0x800CD7C8;
const int s03d_dword_800DB4E8 = 0x800CD828;
const int s03d_dword_800DB4EC = 0x800CD910;
const int s03d_dword_800DB4F0 = 0x800CD964;
const int s03d_dword_800DB4F4 = 0x800CD964;
const int s03d_dword_800DB4F8 = 0x800CD92C;
const int s03d_dword_800DB4FC = 0x800CD940;

void AN_Fog(SVECTOR *svec);
void AN_Sleep(SVECTOR *svec);
void *AN_Breath(MATRIX *world);
void *AN_HeadMark(MATRIX *world, int mark);

void s03d_800D05DC(Work *work, int arg);
void s03d_800D0698(Work *work, int arg);
void s03d_800D0754(Work *work, int arg);
void s03d_800D07DC(Work *work, int arg);
void s03d_800D085C(Work *work, int arg);
void s03d_800D08DC(Work *work, int arg);
void s03d_800D0958(Work *work, int arg);
void s03d_800D09D8(Work *work, int arg);
void s03d_800CE5B4(Work *work, int arg);
void s03d_800CE644(Work *work, int arg);
int s03d_800CDF94(Work *work);
void s03d_800CE318(Work *work, int arg);
void s03d_800CFB04(Work *work, int arg);
void s03d_800CF844(Work *work, int arg);
void s03d_800CFFF0(Work *work, int arg);
void s03d_800CF90C(Work *work, int arg);
void s03d_800CF114(Work *work);
void s03d_800CE8F4(Work *work, int arg);
void s03d_800CE9E8(Work *work, int arg);
void s03d_800CEB38(Work *work, int arg);
void s03d_800CECBC(Work *work, int arg);
void s03d_800CE2C0(Work *work, int arg1);
void s03d_800D01C4(struct _Work *work, int arg);
void s03d_800D0324(struct _Work *work, int arg);
void s03d_800CF68C(struct _Work *work, int arg);
void s03d_800CE12C(struct _Work *work, int arg);
void s03d_800CF548(struct _Work *work, int arg);
void s03d_800CEE3C(struct _Work *work, int arg);
void s03d_800CF194(struct _Work *work, int arg);
void Zako_800D0BEC(Work *work, int type);
void Zako_800D0B18(Work *work, int index, int count);
void Zako_800D0B88(Work *work);
int  s03d_800CDE1C(Work *work);
void s03d_800CE720(struct _Work *work, int arg);
int  Zako_800D0EF0(Work *work, int index);
int  Zako_800D0F38(Work *work, int value);
void s03d_800CDB5C(Work *work);
int  s03d_800CC4EC(Work *work, int arg);
void s03d_800CC984(Work *work);
int  s03d_800CD61C(Work *work);
int  s03d_800CD75C(Work *work);
int  s03d_800CD984(Work *work);
void s03d_800D041C(Work *work);
void s03d_800D14AC(Work *work);
void s03d_800D13F8(Work *work);
void s03d_800D3B5C(Work *work);
void s03d_800D153C(Work *work);
int  ZakoCom_800D4038(void);
void ZakoCom_800D4050(int idx);
extern const SVECTOR s03d_dword_800DB548;
extern const SVECTOR s03d_dword_800DB550;
extern const SVECTOR s03d_dword_800DB558;

static inline void SetMode(Work *work, ACTION action)
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, NULL);
}

static inline void SetMode2(Work *work, ACTION action)
{
    if (work->action2 == NULL)
    {
        work->action2 = action;
        work->time2 = 0;
    }
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, NULL);
}

static inline void UnsetMode(Work *work)
{
    GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
    work->action2 = NULL;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

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

int s03d_800CD61C(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & TARGET_CAPTURE)
    {
        if (t->a_mode == 0x24)
        {
            work->action = s03d_800CEE3C;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, 0);
            t->damaged = 0;
        }
        else
        {
            work->action = s03d_800CF194;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, 0);
            t->damaged = 0;
        }
        return 1;
    }
    return 0;
}
int Zako_800CD6A8(Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & 4)
    {
        if (t->a_mode == 1)
        {
            t->force = DG_ZeroVector;
            if (t->vital <= 0)
            {
                return 1;
            }
        }
        t->damage = 0;
        t->damaged = 0;
    }
    return 0;
}
int Zako_800CD720(SVECTOR *vec)
{
    int x = vec->vx;
    int y = vec->vy;
    int z = vec->vz;

    return ABS(x) + ABS(y) + ABS(z);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD75C.s")
int s03d_800CD984(Work *work)
{
    if (work->control.mov.vx < 0x1194)
    {
        return 0;
    }
    if (work->control.mov.vz >= 0xBB9 || !(GM_GameStatus & 2))
    {
        return 0;
    }

    work->action = s03d_800CF548;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, 0);
    return 1;
}
int Zako_800CDA04(Work *work)
{
    int a = s03d_800CD61C(work);
    int b = s03d_800CD75C(work);
    int c = s03d_800CD984(work);

    if (a | b | c)
    {
        work->target->class = 1;
        return 1;
    }
    return 0;
}
void Zako_800CDA70(Work *work)
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
void s03d_800CDB5C(Work *work)
{
    CONTROL *ctrl;
    HZD_ZON *zone;
    int      reset;

    ctrl = &work->control;
    work->field_B04 = ZakoCom_800D4038();
    work->field_B00 = 1;
    GM_ConfigControlAttribute(ctrl, RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP);
    Zako_800CDA70(work);

    if (s03d_dword_800DC2F8 < 4)
    {
        reset = work->param.fAF8 * 2 + 25;
        printf("aaa reset wait zone id = %d z=%d\n", work->param.fAF8, reset);
    }
    else
    {
        reset = ZAKOCOM_MGR->field_38[work->param.fAF8 % 2];
        printf("bbb reset fight zone id = %d z=%d\n", work->param.fAF8, reset);
    }

    zone = HZD_GetZone(ctrl->map->hzd, reset);
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;
    if (work->param.fAF8 == 2)
    {
        ctrl->mov.vz += 500;
    }

    ctrl->map = GM_GetMap(work->field_B54);

    work->field_AC8 = 0;
    work->field_ACA = 0;
    work->field_ACC = 0;
    work->field_ACE = 0;
    work->field_AD0 = 0;
    work->field_AD4 = work->n_nodes - 1;
    work->field_B5C = work->field_B50;
    work->field_B48 = work->field_B40;
    work->vision.range = 512;
    work->vision.length = 4000;
    work->field_B28 = 0;
    work->vision.facedir = 0;
    work->field_AE8 = 0;
    work->field_ADC = 1;
    work->field_BA0 = 0;
    work->field_B60 = work->field_B54;
    work->field_B80 = work->field_B40;
    work->field_B58 = work->field_B74 = work->field_B50;
}

const SVECTOR s03d_dword_800DB548 = {-200, 1000, 600, 0};
const SVECTOR s03d_dword_800DB550 = {5, 0, 100, 0};
const SVECTOR s03d_dword_800DB558 = {400, 1000, 400, 0};
const char s03d_dword_800DB560[] = {0x0, 0x0, 0x0, 0x0};

int Zako_800CDD40(int from, int to)
{
    int dir;

    if (to < 0)
    {
        return 0;
    }
    if (from < 0)
    {
        return 0;
    }
    dir = GV_DiffDirS(from, to);
    if ((unsigned int)(dir + 0x380) >= 0x701)
    {
        return 0;
    }
    if (dir >= 0)
    {
        return 1;
    }
    return 2;
}
void Zako_800CDD94(Work *work)
{
    int diff;
    int v;

    diff = GM_PlayerBody->objs->objs[6].world.t[1] -
           work->body.objs->objs[6].world.t[1];
    v = GV_NearExp8(work->adjust[2].vx, (ratan2(work->field_B90, diff) & 0xFFF) - 0x400);
    work->adjust[2].vx = v;
    work->adjust[6].vx = v;
    if (v < 0)
    {
        work->adjust[7].vx = v * 3;
    }
    else
    {
        work->adjust[7].vx = v * 3 / 2;
    }
}
int s03d_800CDE1C(Work *work)
{
    TARGET *target;
    SVECTOR svec;
    SVECTOR rp_shift;
    SVECTOR force;
    SVECTOR size;

    rp_shift = s03d_dword_800DB548;
    force    = s03d_dword_800DB550;
    size     = s03d_dword_800DB558;

    target = (TARGET *)((char *)work + 0x948);
    GM_SetTarget(target, 4, ENEMY_SIDE, &size);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_RotVector(&force, &svec, 1);
    GM_SetPowerTarget(target, POWER_ONCE, 2, 32, 1, &svec);
    DG_PutVector(&rp_shift, &target->center, 1);
    return GM_PowerTarget(target);
}
void Zako_800CDF2C(Work *work)
{
    TARGET *t = &work->attack;

    GM_SetPowerTarget(t, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDF94.s")
void s03d_800CE12C(Work *work, int arg)
{
    work->target->class |= 0x9E;
    if (ZAKOCOM_MGR->field_1C == 0)
    {
        work->target->class |= 0x40;
    }
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        work->act.motion1 = 0;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39E0[0], 0, 4);
    }
    if (Zako_800CDA04(work) || s03d_800CDF94(work))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = NULL;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        if (work->field_AE6 >= 0)
        {
            if (GV_DiffDirAbs(work->control.rot.vy, work->field_AE6) < 0x100)
            {
                if (work->field_ADC & 1)
                {
                    work->act.motion1 = 2;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C39E0[2], 0, 4);
                }
                else
                {
                    work->act.motion1 = 1;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C39E0[1], 0, 4);
                }
                work->action = s03d_800CE318;
                work->time = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                GM_ConfigMotionAdjust(&work->body, NULL);
            }
            else
            {
                work->control.turn.vy = work->field_AE6;
            }
        }
        work->vision.facedir = GV_NearExp4P(work->vision.facedir, work->control.rot.vy);
    }
}
void s03d_800CE2C0(Work *work, int arg1)
{
    int dir = GV_DiffDirS(arg1, work->control.rot.vy);

    if (dir > 128)
    {
        dir = 128;
    }
    else if (dir < -128)
    {
        dir = -128;
    }

    work->control.turn.vz = dir;
}
void s03d_800CE318(Work *work, int arg)
{
    CONTROL *ctrl;
    SVECTOR *vecs;
    int      dir, motion, touches, touch, touch2, size;

    work->target->class |= 0x9E;
    if (ZAKOCOM_MGR->field_1C == 0)
    {
        work->target->class |= 0x40;
    }
    work->vision.length = 0xFA0;

    if (Zako_800CDA04(work))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = NULL;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s03d_800CDF94(work))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = NULL;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    touch = -1;
    ctrl = &work->control;
    vecs = ctrl->vecs;
    dir = work->field_AE6;
    motion = work->act.motion1;

    if ((work->field_ADC & 1) && motion != 2)
    {
        work->act.motion1 = 2;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39E0[2], 0, 4);
    }

    if (dir < 0)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = NULL;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    touches = ctrl->n_touches;
    if (touches > 0)
    {
        touch = GV_VecDir2(vecs);
        if (touches > 1)
        {
            touch2 = GV_VecDir2(&ctrl->vecs[1]);
            if (GV_DiffDirAbs(dir, touch2) < GV_DiffDirAbs(dir, touch))
            {
                touch = touch2;
            }
        }
    }

    if (dir < 0)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = NULL;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    switch (Zako_800CDD40(dir, touch))
    {
    case 1:
        dir = (touch - 1024) & 4095;
        break;
    case 2:
        dir = (touch + 1024) & 4095;
        break;
    }

    if (work->body.objs->bound_mode == 0)
    {
        ctrl->rot.vy = dir;
    }
    ctrl->turn.vy = dir;

    size = 0;
    if (motion == 1)
    {
        size = 50;
    }
    else if (motion == 2)
    {
        size = 100;
    }

    ctrl->step.vx = size * rsin(dir) / 4096;
    ctrl->step.vz = size * rcos(dir) / 4096;
    s03d_800CE2C0(work, dir);
    work->vision.facedir = GV_NearExp4P(work->vision.facedir, work->control.rot.vy);
}
void s03d_800CE5B4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->act.field_14 = 3;
        work->act.motion1 = 0x1F;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[7], 0, 4);
    }
    if (Zako_800CDA04(work) == 0 && work->body.is_end)
    {
        work->field_AE0 = 0;
        work->action = s03d_800CF68C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CE644(Work *work, int arg)
{
    CONTROL *control = &work->control;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        work->act.motion1 = 0x10;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A00[0], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end || !(work->field_AD8 & 0x20))
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
    else
    {
        short vy = work->field_B94;
        control->step.vx = 0;
        control->step.vz = 0;
        control->turn.vy = vy;
    }
}
void s03d_800CE720(Work *work, int arg)
{
    int status;

    work->target->class |= 0x9E;
    status = work->field_AD8;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        if (status & 0x10000)
        {
            work->act.motion1 = 3;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39E0[3], 0, 4);
        }
        else
        {
            work->act.motion1 = 5;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39E8[1], 0, 4);
        }
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    if (work->param.fAF8 != 1 || !(GV_Time & 0x100))
    {
        Zako_800CDD94(work);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (!(status & 0x30000))
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
        return;
    }
    if (status & 0x40000)
    {
        work->action = s03d_800CE8F4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }
    if (status & 0x80000)
    {
        work->action = s03d_800CE9E8;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }
    if (status & 0x100000)
    {
        work->action = s03d_800CEB38;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }
    if (status & 0x200000)
    {
        work->action = s03d_800CECBC;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }
    if (work->param.fAF8 != 1 || !(GV_Time & 0x100))
    {
        if (work->field_AE6 >= 0)
        {
            work->control.turn.vy = work->field_AE6;
        }
    }
    else
    {
        work->control.turn.vy = work->field_B98;
    }
    work->vision.facedir = work->control.rot.vy;
}
void s03d_800CE8F4(Work *work, int arg)
{
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        if (work->field_AD8 & 0x10000)
        {
            work->act.motion1 = 4;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39E8[0], 0, 0);
        }
        else
        {
            work->act.motion1 = 6;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        }
        Zako_800D0EF0(work, 3);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    if (work->param.fAF8 != 1 || !(GV_Time & 0x100))
    {
        Zako_800CDD94(work);
    }
    if (!Zako_800CDA04(work))
    {
        work->action = s03d_800CE720;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800CE9E8(Work *work, int arg)
{
    SVECTOR *rot;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    rot = &work->control.rot;
    if (arg == 1 || arg == 7)
    {
        rot->vy = (*(unsigned short *)&rot->vy - 0x100) & 0xFFF;
    }
    if (arg == 3 || arg == 5)
    {
        rot->vy = (*(unsigned short *)&rot->vy + 0x100) & 0xFFF;
    }
    if (arg == 2 || arg == 4 || arg == 6)
    {
        work->act.motion1 = 6;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        Zako_800D0EF0(work, 3);
    }
    Zako_800CDD94(work);
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            work->action = s03d_800CE720;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        work->control.rot.vy = rot->vy;
    }
}
void s03d_800CEB38(Work *work, int arg)
{
    SVECTOR *pos;
    SVECTOR *step;
    SVECTOR *target;
    SVECTOR  out;
    SVECTOR  rot;
    SVECTOR  svec;
    int      dist;

    if (arg == 0)
    {
        work->act.motion1 = 7;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[1], 0, 4);
    }
    if (arg == 17)
    {
        GM_SeSet(&work->control.mov, 0x2C);
    }
    if (arg == 45)
    {
        if (work->param.fAF8 == 2)
        {
            pos = &s03d_dword_800C3A44;
        }
        else
        {
            pos = &s03d_dword_800C3A4C;
        }
        target = &work->field_B68;
        dist = GV_DiffVec3(pos, target);
        step = &s03d_dword_800C3A54;
        step->vz = dist / 8;
        GV_SubVec3(target, pos, &svec);
        rot.vx = 0;
        rot.vy = GV_VecDir2(&svec);
        rot.vz = 0;
        DG_SetPos2(pos, &rot);
        DG_RotVector(step, &out, 1);
        NewTenage3(pos, &out, 60, 0, 0x3b88, 0, 0);
    }
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            work->action = s03d_800CE720;
            work->time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        work->control.turn.vy = work->field_AE6;
    }
}
void s03d_800CECBC(Work *work, int arg)
{
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (arg == 0)
    {
        work->act.motion1 = 8;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39F0[0], 0, 0);
    }
    if (arg == 3 && s03d_800CDE1C(work))
    {
        GM_SeSet(&work->control.mov, 0x25);
    }
    work->control.turn.vy = work->field_B94;
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end)
    {
        work->action = s03d_800CE720;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CED94(Work *work, int arg)
{
    work->vision.length = 0;
    if (arg == 0)
    {
        work->act.motion1 = 0x13;
        GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C3A04)[1], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    work->target->class |= 0x9E;
    if (work->body.is_end)
    {
        work->field_8F8 = 1;
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CEE3C(Work *work, int arg)
{
    TARGET  *target;
    CONTROL *ctrl;
    int      diff;

    target = work->target;
    ctrl = &work->control;
    work->act.field_1C = 0;
    if (arg == 0)
    {
        work->act.field_14 = 6;
        work->act.motion1 = 0x1B;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[3], 0, 4);
    }
    if (arg >= 8 && arg <= 17)
    {
        Zako_800CDF2C(work);
    }
    if (work->act.motion1 == 0x1B)
    {
        if (arg == 22)
        {
            diff = ctrl->mov.vy - ctrl->levels[0];
            if (diff < 2000)
            {
                GM_SeSet(&ctrl->mov, 0x8D);
                GM_SeSet(&ctrl->mov, 0x33);
                Zako_800D0B18(work, 6, 0);
                GM_SetNoise(100, 4, &ctrl->mov);
            }
            else if (diff > 4000)
            {
                work->target->vital = 0;
                GM_SeSet(&ctrl->mov, 0x8E);
            }
        }
        if (work->body.is_end)
        {
            if (ctrl->grounded == 0)
            {
                work->act.motion1 = 0x24;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[12], 0, 4);
            }
            else
            {
                SetMode(work, s03d_800CF68C);
            }
        }
    }
    else if (ctrl->grounded)
    {
        GM_SeSet(&ctrl->mov, 0x8D);
        GM_SeSet(&ctrl->mov, 0x33);
        GM_SetNoise(100, 4, &ctrl->mov);
        Zako_800D0B18(work, 6, 1);
        if (work->target->vital <= 0)
        {
            SetMode(work, s03d_800D01C4);
        }
        else
        {
            SetMode(work, s03d_800CF68C);
        }
    }
    if (arg < 24)
    {
        ctrl->turn = *target->field_1C;
    }
    if (arg < 22)
    {
        work->control.hzd_height = -32767;
    }
}
void s03d_800CF114(Work *work)
{
    SVECTOR vec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector((SVECTOR *)&s03d_dword_800C3A5C, &vec, 1);
    GV_SubVec3(&vec, &work->control.mov, &work->control.step);
}
void s03d_800CF194(Work *work, int time)
{
    TARGET *target;
    int     motion;

    target = work->target;
    motion = work->act.motion1;

    work->act.field_1C = 0;

    if (time == 0)
    {
        work->field_AF6 = target->faint;
        GM_SeSet(&work->control.mov, 0x8F);
    }

    if (work->field_AF6 != target->faint)
    {
        GM_SeSet(&work->control.mov, 0x8F);
        work->field_AF6 = target->faint;
    }

    if (target->damaged & TARGET_POWER)
    {
        Zako_800D0B18(work, 5, 0);
        GM_SeSet(&work->control.mov, 0x8F);

        target->force = DG_ZeroVector;
        target->damage = 0;
        target->damaged = 0;

        if (target->vital <= 0)
        {
            if (target->a_mode == 1)
            {
                work->field_BA0 = 1;
            }

            work->act.field_14 = 5;
            target->side = ENEMY_SIDE;
            SetMode(work, s03d_800CFB04);
            target->captured = 0;
        }
    }

    switch (GM_PlayerAction)
    {
    case 7:
    case 13:
        if (motion != 23 && motion != 44)
        {
            target->side = 0;
            work->act.motion1 = 23;
            GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C3A0C)[1], 0, 4);
            work->field_AF8 = 0;
        }

        if (work->field_AF8 == 50 && target->faint > 0)
        {
            work->act.motion1 = 44;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A38[0], 0, 4);
        }

        if (motion == 44 && !(work->field_AF8 & 7))
        {
            s03d_dword_800DC2F4 = 4;
        }

        work->control.turn = GM_PlayerControl->rot;
        s03d_800CF114(work);
        work->field_AF8++;
        break;
    case 38:
        if (motion != 24)
        {
            target->side = 0;
            work->act.motion1 = 24;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[0], 0, 4);
        }

        work->control.turn = GM_PlayerControl->rot;
        s03d_800CF114(work);
        break;
    case 39:
        work->act.field_14 = 4;
        target->side = ENEMY_SIDE;
        target->vital = 0;
        SetMode(work, s03d_800CFB04);
        return;
    default:
        work->act.field_14 = 5;
        target->side = ENEMY_SIDE;
        SetMode(work, s03d_800CFB04);
        return;
    }

    if (work->field_B90 > 800)
    {
        target->captured = 0;
    }

    work->target->class |= TARGET_POWER | TARGET_SEEK;
}
void s03d_800CF4D4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->act.motion1 = 0x22;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[10], 0, 4);
    }
    if (work->body.is_end)
    {
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CF548(Work *work, int arg)
{
    SVECTOR *pos = &work->control.mov;
    int phase;
    work->act.field_1C = 0;
    work->vision.length = 0;
    if (arg == 0)
    {
        work->act.motion1 = 0x1C;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[4], 0, 4);
        work->target->faint = 0;
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    phase = 0xA;
    if (arg == phase)
    {
        work->act.field_14 = 1;
        work->act.motion1 = 0x21;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[9], 0, 4);
    }
    else
    {
        work->target->class |= 0x9E;
    }
    if (arg == phase + 0x18)
    {
        GM_SeSet(pos, 0x51);
    }
    if (arg == phase + 0x2E)
    {
        GM_SeSet(pos, 0x33);
    }
    if (arg >= phase + 0x32 && work->body.is_end)
    {
        work->action = s03d_800CF68C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CF68C(Work *work, int time)
{
    int x;

    if (time == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                work->act.motion1 = 37;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[13], 0, 4);
            }
            else
            {
                work->act.motion1 = 35;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[11], 0, 4);
            }
        }
        else
        {
            work->act.motion1 = 36;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[12], 0, 4);
        }

        if (work->target->faint <= 0)
        {
            x = work->control.mov.vx % 90;
        }
        else
        {
            x = work->control.mov.vx % 30;
        }
        if (x < 0)
        {
            x = -x;
        }
        work->field_AF6 = x + 10;
    }

    if (Zako_800CD6A8(work))
    {
        SetMode(work, s03d_800CF844);
    }
    else if (work->field_AF6 < time)
    {
        if (work->target->faint <= 0)
        {
            work->target->faint = work->param.faint;
        }
        SetMode(work, s03d_800CF90C);
    }
}
void s03d_800CF844(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            work->act.motion1 = 0x2A;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[18], 0, 4);
        }
        else
        {
            work->act.motion1 = 0x2B;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[19], 0, 4);
        }
        GM_SeSet(&work->control.mov, 0x36);
    }
    if (arg == 4)
    {
        Zako_800D0BEC(work, 0);
    }
    if (work->body.is_end)
    {
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CF90C(Work *work, int arg)
{
    work->act.field_1C = 0;
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->field_AF6 >= 0x96)
            {
                work->act.motion1 = 0x28;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[16], 0, 4);
            }
            else
            {
                work->act.motion1 = 0x26;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[14], 0, 4);
            }
        }
        else
        {
            if (work->field_AF6 >= 0x96)
            {
                work->act.motion1 = 0x29;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[17], 0, 4);
            }
            else
            {
                work->act.motion1 = 0x27;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[15], 0, 4);
            }
        }
    }
    if (work->body.is_end)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CFA04(Work *work, int arg)
{
    TARGET *t;
    work->act.field_1C = 0;
    work->target->class |= 0x9E;
    work->vision.length = 0xFA0;
    if (Zako_800CDA04(work))
    {
        return;
    }
    t = work->target;
    if (arg == 0)
    {
        work->act.motion1 = 0xF;
        GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C39FC)[1], 0, 4);
        GM_SeSet(&work->control.mov, 0x8D);
        if (t->a_mode == 3)
        {
            GM_SeSet(&work->control.mov, 0x34);
            Zako_800D0B88(work);
        }
        else
        {
            Zako_800D0B18(work, 5, 0);
        }
    }
    if (work->body.is_end)
    {
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CFB04(Work *work, int time)
{
    ACT     *act;
    CONTROL *control;

    act = &work->act;
    control = &work->control;
    control->step = work->target->force;

    if (act->field_14 != 1)
    {
        work->act.field_1C = 0;
    }

    if (time == 0)
    {
        switch (act->field_14)
        {
        case 0:
            GM_SeSet(&control->mov, SE_PUNCHIT1);
            work->act.motion1 = 30;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[6], 0, 4);
            GM_SeSet(&control->mov, SE_V_ENE_PUNCHED);
            Zako_800D0B18(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 1:
            work->act.motion1 = 33;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[9], 0, 4);
            if (work->target->vital <= 0)
            {
                if (GM_Weapon == WP_Rifle)
                {
                    Zako_800D0B18(work, 6, 2);
                }
                else
                {
                    Zako_800D0B18(work, 6, 1);
                }
            }
            else
            {
                Zako_800D0B18(work, 5, 0);
            }
            GM_SeSet(&control->mov, SE_V_ENE_PUNCHED);
            work->field_AF6 = 46;
            break;
        case 3:
            GM_SeSet(&control->mov, SE_EDMG01);
            work->act.motion1 = 31;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[7], 0, 4);
            Zako_800D0B18(work, 5, 0);
            work->field_AF6 = 17;
            break;
        case 2:
            GM_SeSet(&control->mov, SE_V_ENE_THROWN);
            work->act.motion1 = 32;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[8], 0, 4);
            Zako_800D0B18(work, 5, 0);
            work->field_AF6 = 22;
            break;
        case 4:
            GM_SeSet(&control->mov, SE_V_ENE_SNAPPED);
            work->act.motion1 = 25;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[1], 0, 4);
            work->field_AF6 = 67;
            break;
        case 5:
            work->act.motion1 = 26;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[2], 0, 4);
            work->field_AF6 = 15;
            break;
        }
    }

    switch (act->field_14)
    {
    case 0:
        if (time < 12)
        {
            control->turn.vy += 170;
        }
        if (time > 0 && time < 6)
        {
            Zako_800CDF2C(work);
        }
        if (time < 20)
        {
            work->control.hzd_height = -32767;
        }
        break;
    case 1:
        if (time == 24)
        {
            GM_SeSet(&control->mov, SE_ENEMY_COLLAPSE);
        }
        break;
    case 3:
        if (time > 0 && time < 15)
        {
            Zako_800CDF2C(work);
        }
        if (time < 15)
        {
            control->hzd_height = -32767;
        }
        break;
    case 2:
        if (time > 0 && time < 30)
        {
            Zako_800CDF2C(work);
        }
        if (time < 20)
        {
            control->hzd_height = -32767;
        }
        break;
    case 4:
    case 5:
        break;
    }

    if (time > 16 && control->grounded != 0)
    {
        control->step = DG_ZeroVector;
    }

    if (time == work->field_AF6)
    {
        if ((control->mov.vy - control->levels[0]) < 2000)
        {
            GM_SeSet(&control->mov, SE_HIT_FLOOR);
            GM_SetNoise(100, 4, &control->mov);
            Zako_800D0B18(work, 6, 0);
        }
        else if ((control->mov.vy - control->levels[0]) > 4000)
        {
            work->target->vital = 0;
            SetMode(work, s03d_800CFFF0);
            return;
        }
    }

    if (work->body.is_end)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;

        if (work->target->vital <= 0)
        {
            SetMode(work, s03d_800D01C4);
        }
        else
        {
            SetMode(work, s03d_800CF68C);
        }
    }
}
void s03d_800CFFF0(Work *work, int arg)
{
    CONTROL *ctrl = &work->control;

    work->act.field_1C = 0;
    ctrl->step = work->target->force;
    if (arg == 0 && work->act.field_14 != 2)
    {
        GM_SeSet(&ctrl->mov, SE_V_ENE_THROWN);
    }
    if (arg > 16 && ctrl->grounded)
    {
        ctrl->step = DG_ZeroVector;
    }
    if (work->act.motion1 < 35)
    {
        if (work->body.is_end)
        {
            if (work->act.field_14 < 3)
            {
                if (work->act.field_14 == 1)
                {
                    work->act.motion1 = 37;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[13], 0, 4);
                }
                else
                {
                    work->act.motion1 = 35;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[11], 0, 4);
                }
            }
            else
            {
                work->act.motion1 = 36;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[12], 0, 4);
            }
        }
    }
    else if (ctrl->grounded)
    {
        work->act.field_1C = 1;
        work->target->force = DG_ZeroVector;
        GM_SeSet(&ctrl->mov, SE_HIT_FLOOR);
        Zako_800D0B18(work, 6, 1);
        work->action = s03d_800D01C4;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800D01C4(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->act.field_14 < 3)
        {
            if (work->act.field_14 == 1)
            {
                work->act.motion1 = 0x2F;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A3C[1], 0, 4);
            }
            else
            {
                work->act.motion1 = 0x2D;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A38[1], 0, 4);
            }
        }
        else
        {
            work->act.motion1 = 0x2E;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A3C[0], 0, 4);
        }
        GM_ConfigControlAttribute(&work->control, 0);
        work->field_B28 = 0;
    }
    if (arg == 4)
    {
        int b04 = work->field_B04;

        printf("n_dead = %d \n", b04);
        if (b04 == 6 || b04 == 0xA || b04 == 0xE)
        {
            Zako_800D0BEC(work, 2);
        }
        if (b04 == 8 || b04 == 0xC)
        {
            Zako_800D0BEC(work, 0);
        }
    }
    if (arg & 2)
    {
        work->field_B00 = 0;
    }
    else
    {
        work->field_B00 = 1;
    }
    if (arg >= 9)
    {
        work->action = s03d_800D0324;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}

const char s03d_dword_800DB5A4[] = {'F', 'A', '-', 'M'};
const char s03d_dword_800DB5A8[] = {'A', 'S', '/', 'B'};
const char s03d_dword_800DB5AC[] = {'U', 'L', 'L', 'E'};
const char s03d_dword_800DB5B0[] = {'T', ' ', '*', ' '};
const char s03d_dword_800DB5B4[] = {'2', '5', 0x0, 0x0};

const char s03d_dword_800DB5B8[] = {'S', 'O', 'C', 'O'};
const char s03d_dword_800DB5BC[] = {'M', '/', 'B', 'U'};
const char s03d_dword_800DB5C0[] = {'L', 'L', 'E', 'T'};
const char s03d_dword_800DB5C4[] = {' ', '*', ' ', '1'};
const char s03d_dword_800DB5C8[] = {'2', 0x0, 0x0, 0x0};

const char s03d_dword_800DB5CC[] = {'R', 'A', 'T', 'I'};
const char s03d_dword_800DB5D0[] = {'O', 'N', 0x0, 0x0};


void s03d_800D0324(Work *work, int arg)
{
    if (arg == 0)
    {
        int *base = &s03d_dword_800DC310;
        work->field_B00 = 0;
        work->control.mov = s03d_dword_800C3B88;
        base[work->param.fAF8 * 4 + 0x90 / 4] = 1;
        if (work->field_BA0 == 0)
        {
            unsigned short *lv = (unsigned short *)linkvarbuf;
            lv[0x4F]++;
        }
    }
    {
        int *base = &s03d_dword_800DC310;
        if (base[work->param.fAF8 * 4 + 0x90 / 4] != 2)
        {
            return;
        }
        s03d_800CDB5C(work);
        work->action = s03d_800CE12C;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
int Zako_800D0408(Work *work)
{
    return work->control.mov.vx >= 0x1195;
}
void s03d_800D041C(Work *work)
{
    ACT     *act;
    CONTROL *control;
    ACTION   action;
    int      time;

    act = &work->act;
    control = &work->control;

    work->field_AEC = 0;
    work->vision.length = 0;
    work->target->class = TARGET_AVAIL;

    action = work->action;
    work->field_8F8 = 0;
    work->field_B9C = 0;

    control->height = work->body.height;
    control->hzd_height = control->levels[0] + 750;

    time = work->time++;

    if (action == NULL)
    {
        action = s03d_800CE12C;
        work->action = s03d_800CE12C;
    }

    action(work, time);

    action = work->action2;
    if (action != NULL)
    {
        time = work->time2++;
        action(work, time);
    }

    if (act->field_1C == 0)
    {
        control->r_sphere = GV_NearExp2(control->r_sphere, act->motion2);
    }
    else
    {
        control->r_sphere = -1;
    }

    if (work->target->class & TARGET_POWER)
    {
        work->hom->flag = 1;
    }
    else
    {
        work->hom->flag = 0;
    }

    if (ZAKOCOM_MGR->entries[work->param.fAF8].field_4 == 1)
    {
        work->hom->flag = 0;
    }

    if (Zako_800D0408(work) == 0)
    {
        work->hom->flag = 0;
        work->target->class = TARGET_AVAIL;
    }

    if (act->field_04 < 0 && control->grounded)
    {
        act->field_04 = 0;
    }

    act->field_04 -= 16;
    control->step.vy = act->field_04;

    work->field_BA2 = work->target->vital;
}
void s03d_800D05DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39F0[1], 0, 4, 0x3FE);
    }
    if (!(work->field_AD8 & 1))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy - (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy - 0x400) & 0xFFF;
    }
}
void s03d_800D0698(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39F4, 0, 4, 0x3FE);
    }
    if (!(work->field_AD8 & 2))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (*(unsigned short *)&work->control.rot.vy + 0x400) & 0xFFF;
    }
}
void s03d_800D0754(Work *work, int arg1)
{
    work->vision.length = 0x7D0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ((short *)&s03d_dword_800C39F4)[1], 0, 4, 0x3FE);
    }
    if (!(work->field_AD8 & 4))
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D07DC(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A0C, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D085C(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A08, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D08DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ((short *)&s03d_dword_800C3A08)[1], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D0958(Work *work, int arg1)
{
    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C3A00[1], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D09D8(Work *work, int arg1)
{
    SVECTOR pos;

    work->vision.length = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A04, 0, 4, 0x3FE);
        if (work->control.map->index == GM_PlayerMap && GV_RandU(12) >= 5)
        {
            work->field_AE8 = 0xF0;
        }
    }
    if (arg1 == 20)
    {
        pos = work->control.mov;
        pos.vy += 500;
        AN_Sleep(&pos);
    }
    if (work->field_AD8 & 0x1000)
    {
        work->action = s03d_800CED94;
        work->time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 == 0x82)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39E0[0], 0, 4, 0);
        work->action2 = 0;
        work->time2 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void Zako_800D0B18(Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3A64);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3A6C);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
}
void Zako_800D0B88(Work *work)
{
    MATRIX  m;
    SVECTOR sv;

    DG_SetPos(&work->body.objs->objs[1].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3A74);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3A7C);
    ReadRotMatrix(&m);
    sv.vx = *(short *)&m.t[0];
    sv.vy = *(short *)&m.t[1];
    sv.vz = *(short *)&m.t[2];
    AN_Fog(&sv);
}
void Zako_800D0BEC(Work *work, int type)
{
    SVECTOR   step = work->act.field_0C;
    SVECTOR  *pos = &work->control.mov;
    ITEM_INFO info;

    if (type >= 0)
    {
        if (type < 2)
        {
            info.type = 4;
            info.id = IT_Ration;
            info.num = 1;
            info.message = (const char *)s03d_dword_800C3A84;
        }
        else if (type < 4)
        {
            info.type = 2;
            info.id = WP_Socom;
            info.num = 0xC;
            info.message = (const char *)s03d_dword_800C3A88;
        }
    }
    info.time = 0x384;
    NewItemPut(pos, &step, &info);
}
void s03d_800D0C90(Work *work, int mark)
{
    if (work->control.map->index == GM_PlayerMap)
    {
        AN_HeadMark(&work->body.objs->objs[6].world, mark);
    }
}

void s03d_800D0CD4(Work *work)
{
    int action = work->act.motion1;
    int frame = work->m_ctrl.info1.frame;
    int l = 160 + (work->param.fAF8 % 4) * 2;
    int r = 160 + (work->param.fAF8 % 4) * 2 + 1;

    if (action == 1)
    {
        if (frame == 22)
        {
            GM_SeSet(&work->control.mov, r);
        }
        else if (frame == 11)
        {
            GM_SeSet(&work->control.mov, l);
        }
    }
    else if (action == 2)
    {
        if (frame == 16)
        {
            GM_SeSet(&work->control.mov, r);
        }
        else if (frame == 8)
        {
            GM_SeSet(&work->control.mov, l);
        }
    }
}

void s03d_800D0D6C(Work *work)
{
    if (ZAKOCOM_MGR->field_1C == 1)
    {
        return;
    }
    if (!(work->control.map->index == GM_PlayerMap))
    {
        return;
    }
    if (GV_Time % 64 == work->param.fAF8 * 16)
    {
        AN_Breath(&work->body.objs->objs[6].world);
    }
}

void s03d_800D0DF0(Work *work)
{
    if (work->vision.pad == 2)
    {
        NewLSight(&GM_PlayerPosition, &work->control.mov, 0x8F);
    }
}

void s03d_800D0E2C(Work *work)
{
    MATRIX  m;
    MATRIX *world;

    world = &work->body.objs->objs[4].world;
    DG_SetPos(world);
    DG_MovePos(&s03d_dword_800C3AA0);
    DG_RotatePos(&s03d_dword_800C3AA8);
    ReadRotMatrix(&m);
    NewBulletEx(0x100, &m, 2, 1, 0, 10, work->param.damage, 10000, 750);
    GM_SeSet(&work->control.mov, 0x2D);
    AN_BulletSmoke(world, 0);
    AN_FamasFlash(&m);
    Zako_800D0F38(work, (int)s03d_800D0E2C);
}
int Zako_800D0EF0(Work *work, int index)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_AA8[i] == 0)
        {
            work->field_AA8[i] = s03d_dword_800C3A90[index];
            return 1;
        }
    }
    return 0;
}
int Zako_800D0F38(Work *work, int value)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_AA8[i] == value)
        {
            work->field_AA8[i] = 0;
            return 1;
        }
    }
    return 0;
}
void Zako_800D0F6C(Work *work)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_AA8[i])
        {
            ((void (*)(Work *))work->field_AA8[i])(work);
        }
    }
}
void Zako_800D0FCC(Work *work)
{
    VISION            *vision = &work->vision;
    RADAR_SIGHT_PARAM *rp = &work->control.radar_param;

    rp->dir = vision->facedir;
    rp->dis = vision->length;
    rp->range = vision->range;
    rp->r = 0;
}

void Zako_800D0FF4(Work *work)
{
    if (work->field_B33 & 4)
    {
        if (work->target->damaged & 6)
        {
            work->field_B32 |= 4;
        }
        if (work->attack.damaged & 0x80)
        {
            work->vision.pad = 2;
        }
    }
}
int s03d_800D1054(HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2)
{
    int from;
    int to;

    from = HZD_GetAddress(hzd, pos, -1);
    to = HZD_GetAddress(hzd, pos2, -1);
    from &= 0xFF;
    to &= 0xFF;
    return HZD_ZoneDistance(hzd, from, to);
}

void s03d_800D10B4(Work *work)
{
    CONTROL *ctrl;
    int      dist;

    if (!(work->field_B33 & 1))
    {
        return;
    }

    ctrl = &work->control;
    if (ctrl->map->index != GM_PlayerMap)
    {
        return;
    }

    if (!GM_NoisePower)
    {
        return;
    }

    switch (GM_NoisePower)
    {
    case 5:
        if (GV_DiffVec3(&GM_NoisePosition, &ctrl->mov) < 500)
        {
            break;
        }
        return;
    case 200:
        if (GV_DiffVec3(&GM_NoisePosition, &ctrl->mov) < 4000)
        {
            break;
        }
        return;
    case 255:
        break;
    case 100:
        dist = GV_DiffVec3(&GM_NoisePosition, &ctrl->mov);
        fprintf(1, "noise dis  =%d,\n", dist);
        if (dist < 4000)
        {
            dist = s03d_800D1054(ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition);
            if (dist < 300)
            {
                work->field_B32 |= 1;
                GM_NoiseLength = 0;
                GM_NoisePower = 0;
            }
        }
        return;
    default:
        return;
    }
    work->field_B32 |= 1;
}

void s03d_800D123C(Work *work)
{
    if ((work->field_B33 & 2) && work->vision.pad == 2 && (GM_PlayerStatus & PLAYER_CB_BOX))
    {
        if (GV_DiffVec3(&work->field_B34, &GM_PlayerPosition) > 50 || work->field_B3C != GM_WhereList[0]->rot.vy)
        {
            if (ZAKOCOM_MGR->field_1C == 1)
            {
                return;
            }
            work->field_B34 = GM_PlayerPosition;
            work->field_B3C = GM_WhereList[0]->rot.vy;
            work->field_B32 |= 2;
        }
        work->vision.pad = 0;
    }
}

void s03d_800D1324(Work *work)
{
    CONTROL *ctrl;
    HZD_HDL *hzd;
    VISION  *vision;

    if (!(work->field_B33 & 0x10))
    {
        return;
    }

    if (work->field_ACA == 5)
    {
        return;
    }

    ctrl = &work->control;
    hzd = work->control.map->hzd;
    vision = &work->vision;
    if (!AsiatoCheck(hzd, &ctrl->mov))
    {
        return;
    }

    if (SearchNearAsiato(hzd, &ctrl->mov, vision->facedir, vision->range, vision->length) < 0)
    {
        return;
    }

    work->field_B32 |= 0x10;
    fprintf(1, " Asiato mikke!! [%d]\n", NearAsiato());
}
void Zako_800D13E8(Work *work)
{
    SVECTOR unused[2];

    (void)unused;
    work->field_B32 = 0;
}
void s03d_800D13F8(Work *work)
{
    switch (work->vision.pad)
    {
    case 0:
        if (work->field_B28 != 255 || !(GM_PlayerStatus & PLAYER_INTRUDE))
        {
            work->field_B28 -= 4;
        }
        break;
    case 1:
        work->field_B28--;
        break;
    case 2:
        work->field_B28++;
        break;
    }

    if (work->field_B28 < 0)
    {
        work->field_B28 = 0;
    }
    else if (work->field_B28 > 255)
    {
        work->field_B28 = 255;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D14AC.s")

void s03d_800D153C(Work *work)
{
    if (work->act.motion1 < 0x2D)
    {
        Zako_800D0FCC(work);
        s03d_800D14AC(work);
        Zako_800D13E8(work);
        s03d_800D13F8(work);
        s03d_800D3B5C(work);
        Zako_800D0F6C(work);
    }
    s03d_800D041C(work);
}

void s03d_800D15A8(Work *work)
{
    TARGET  *trg;
    CONTROL *ctrl;
    int      turn;
    int      last_set;

    trg = work->target;
    turn = 0;
    if (!(trg->damaged & TARGET_PUSH))
    {
        return;
    }

    GV_AddVec3(&trg->offset, &work->control.step, &work->control.step);
    trg->damaged &= ~TARGET_PUSH;

    last_set = work->act.motion1;
    if (last_set == 1 || last_set == 2)
    {
        if (trg->offset.pad != 0)
        {
            if (GV_Time & 0x100)
            {
                if (work->param.fAF8 & 1)
                {
                    turn = trg->offset.pad << 10;
                }
                else
                {
                    turn = (trg->offset.pad + 2) << 10;
                }
            }
            else
            {
                if (work->param.fAF8 & 1)
                {
                    turn = (trg->offset.pad + 2) << 10;
                }
                else
                {
                    turn = trg->offset.pad << 10;
                }
            }
            turn &= 0xFFF;
        }

        ctrl = &work->control;
        ctrl->turn.vy = turn;
        ctrl->r_sphere = GV_NearExp2(ctrl->r_sphere, work->act.motion2);
    }
}
