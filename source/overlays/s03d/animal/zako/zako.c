#include "zako.h"

#include <stdio.h>
#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "game/item.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "okajima/blood.h"

extern GM_CameraSystemWork GM_Camera;

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
extern int s03d_dword_800C39E0;
extern int s03d_dword_800C39FC;
extern short s03d_word_800C3A38[2];
extern short s03d_word_800C3A3C[2];
extern short s03d_word_800C39E8[2];
extern short s03d_word_800C39EC[2];
extern int s03d_dword_800DC310;
extern SVECTOR s03d_dword_800C3B88;
extern int s03d_dword_800C3A5C;
extern short s03d_word_800C3A10[20];
extern const SVECTOR s03d_dword_800DB548;
extern const SVECTOR s03d_dword_800DB550;
extern const SVECTOR s03d_dword_800DB558;

extern int s03d_dword_800DC2F8;

void AN_Fog(SVECTOR *svec);

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
        if ( GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA) || GM_Camera.first_person )
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
    GM_MoveTarget(work->field_8FC, &control->mov);

    if (s03d_dword_800DC2F8 == 13 && ZAKOCOM_MGR->entries[work->field_B08].field_4 == 1)
    {
        GV_DestroyActor(work);
    }

    s03d_800CCB2C(work);
}

void Zako_800CCCF4(Work *work)
{
    TARGET *t = work->field_8FC;
    int     b14 = work->field_B14;
    int     b16 = work->field_B16;

    GM_SetTarget(t, 0x9E, 2, (SVECTOR *)&s03d_dword_800C39B0);
    GM_SetPowerTarget(t, 1, -1, b14, b16, (SVECTOR *)&s03d_dword_800C39B8);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_TargetBody(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->field_900, 4, 1, (SVECTOR *)&s03d_dword_800C39C0);
    GM_SetPowerTarget(&work->field_900, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
}
void Zako_800CCDE0(Work *work)
{
    short *p = (short *)&work->field_8C8;

    GV_ZeroMemory(p, 0x20);
    work->field_8C8 = 0;
    p[0x0D] = 0x1C2;
    p[0x0E] = 1;
    work->field_8E8 = 0;
    work->field_8EC = 0;
    work->field_8F0 = 0;
    work->field_8F4 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CCE3C.s")

void s03d_800CD054(Work *work)
{
    ZakoCom_800D4050(work->field_B08);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->field_8FC);
    GV_DestroyActor(work->glight);
    GV_DestroyActor(work->shadow);
    GM_FreeHomingTarget(work->hom);
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CD0C8.s")

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
    TARGET *t = work->field_8FC;

    if (t->damaged & TARGET_CAPTURE)
    {
        if (t->a_mode == 0x24)
        {
            work->field_8E8 = s03d_800CEE3C;
            work->field_8F0 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, 0);
            t->damaged = 0;
        }
        else
        {
            work->field_8E8 = s03d_800CF194;
            work->field_8F0 = 0;
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
    TARGET *t = work->field_8FC;

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

    work->field_8E8 = s03d_800CF548;
    work->field_8F0 = 0;
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
        work->field_8FC->class = 1;
        return 1;
    }
    return 0;
}
void Zako_800CDA70(Work *work)
{
    TARGET *t = work->field_8FC;
    int     b14 = work->field_B14;
    int     b16 = work->field_B16;

    GM_SetTarget(t, 0x9E, 2, (SVECTOR *)&s03d_dword_800C39B0);
    GM_SetPowerTarget(t, 1, -1, b14, b16, (SVECTOR *)&s03d_dword_800C39B8);
    GM_SetCaptureTarget(t, -1, b16, NULL, NULL);
    GM_TargetBody(t, &work->body.objs->objs[1].world);
    GM_SetTarget(&work->field_900, 4, 1, (SVECTOR *)&s03d_dword_800C39C0);
    GM_SetPowerTarget(&work->field_900, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDB5C.s")
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
    TARGET *t = &work->field_900;

    GM_SetPowerTarget(t, 7, 5, 0, 3, (SVECTOR *)&s03d_dword_800C39C8);
    GM_MoveTarget(t, &work->control.mov);
    GM_PowerTarget(t);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CDF94.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE12C.s")
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE318.s")
void s03d_800CE5B4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->field_8DC = 3;
        work->field_8E0 = 0x1F;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[7], 0, 4);
    }
    if (Zako_800CDA04(work) == 0 && work->body.is_end)
    {
        work->field_AE0 = 0;
        work->field_8E8 = s03d_800CF68C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CE644(Work *work, int arg)
{
    CONTROL *control = &work->control;
    work->field_8FC->class |= 0x9E;
    work->field_B24 = 0xFA0;
    if (arg == 0)
    {
        work->field_8E0 = 0x10;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A00[0], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    if (work->body.is_end || !(work->field_AD8 & 0x20))
    {
        work->field_8E8 = s03d_800CE12C;
        work->field_8F0 = 0;
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CE720.s")
void s03d_800CE8F4(Work *work, int arg)
{
    work->field_8FC->class |= 0x9E;
    work->field_B24 = 0xFA0;
    if (arg == 0)
    {
        if (work->field_AD8 & 0x10000)
        {
            work->field_8E0 = 4;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39E8[0], 0, 0);
        }
        else
        {
            work->field_8E0 = 6;
            GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        }
        Zako_800D0EF0(work, 3);
        GM_ConfigMotionAdjust(&work->body, work->adjust);
    }
    if (work->field_B08 != 1 || !(GV_Time & 0x100))
    {
        Zako_800CDD94(work);
    }
    if (!Zako_800CDA04(work))
    {
        work->field_8E8 = s03d_800CE720;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800CE9E8(Work *work, int arg)
{
    SVECTOR *rot;
    work->field_8FC->class |= 0x9E;
    work->field_B24 = 0xFA0;
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
        work->field_8E0 = 6;
        GM_ConfigObjectAction(&work->body, s03d_word_800C39EC[0], 0, 0);
        Zako_800D0EF0(work, 3);
    }
    Zako_800CDD94(work);
    if (!Zako_800CDA04(work))
    {
        if (work->body.is_end)
        {
            work->field_8E8 = s03d_800CE720;
            work->field_8F0 = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            GM_ConfigMotionAdjust(&work->body, NULL);
        }
        work->control.rot.vy = rot->vy;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CEB38.s")
void s03d_800CECBC(Work *work, int arg)
{
    work->field_8FC->class |= 0x9E;
    work->field_B24 = 0xFA0;
    if (arg == 0)
    {
        work->field_8E0 = 8;
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
        work->field_8E8 = s03d_800CE720;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CED94(Work *work, int arg)
{
    work->field_B24 = 0;
    if (arg == 0)
    {
        work->field_8E0 = 0x13;
        GM_ConfigObjectAction(&work->body, ((short *)&s03d_dword_800C3A04)[1], 0, 4);
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    work->field_8FC->class |= 0x9E;
    if (work->body.is_end)
    {
        work->field_8F8 = 1;
        work->field_8E8 = s03d_800CE12C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CEE3C.s")
void s03d_800CF114(Work *work)
{
    SVECTOR vec;

    work->control.turn = GM_PlayerControl->rot;
    DG_SetPos2(&GM_PlayerPosition, &GM_PlayerControl->rot);
    DG_PutVector((SVECTOR *)&s03d_dword_800C3A5C, &vec, 1);
    GV_SubVec3(&vec, &work->control.mov, &work->control.step);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CF194.s")
void s03d_800CF4D4(Work *work, int arg)
{
    if (arg == 0)
    {
        work->field_8E0 = 0x22;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[10], 0, 4);
    }
    if (work->body.is_end)
    {
        work->field_8E8 = s03d_800D01C4;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CF548(Work *work, int arg)
{
    SVECTOR *pos = &work->control.mov;
    int phase;
    work->field_8E4 = 0;
    work->field_B24 = 0;
    if (arg == 0)
    {
        work->field_8E0 = 0x1C;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[4], 0, 4);
        work->field_8FC->faint = 0;
    }
    if (Zako_800CDA04(work))
    {
        return;
    }
    phase = 0xA;
    if (arg == phase)
    {
        work->field_8DC = 1;
        work->field_8E0 = 0x21;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[9], 0, 4);
    }
    else
    {
        work->field_8FC->class |= 0x9E;
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
        work->field_8E8 = s03d_800CF68C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CF68C.s")
void s03d_800CF844(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->field_8DC < 3)
        {
            work->field_8E0 = 0x2A;
            GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[18], 0, 4);
        }
        else
        {
            work->field_8E0 = 0x2B;
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
        work->field_8E8 = s03d_800D01C4;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CF90C(Work *work, int arg)
{
    work->field_8E4 = 0;
    if (arg == 0)
    {
        if (work->field_8DC < 3)
        {
            if (work->field_AF6 >= 0x96)
            {
                work->field_8E0 = 0x28;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[16], 0, 4);
            }
            else
            {
                work->field_8E0 = 0x26;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[14], 0, 4);
            }
        }
        else
        {
            if (work->field_AF6 >= 0x96)
            {
                work->field_8E0 = 0x29;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[17], 0, 4);
            }
            else
            {
                work->field_8E0 = 0x27;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[15], 0, 4);
            }
        }
    }
    if (work->body.is_end)
    {
        work->field_8E8 = s03d_800CE12C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800CFA04(Work *work, int arg)
{
    TARGET *t;
    work->field_8E4 = 0;
    work->field_8FC->class |= 0x9E;
    work->field_B24 = 0xFA0;
    if (Zako_800CDA04(work))
    {
        return;
    }
    t = work->field_8FC;
    if (arg == 0)
    {
        work->field_8E0 = 0xF;
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
        work->field_8E8 = s03d_800CE12C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CFB04.s")
void s03d_800CFFF0(Work *work, int arg)
{
    CONTROL *ctrl = &work->control;

    work->field_8E4 = 0;
    ctrl->step = work->field_8FC->force;
    if (arg == 0 && work->field_8DC != 2)
    {
        GM_SeSet(&ctrl->mov, SE_V_ENE_THROWN);
    }
    if (arg > 16 && ctrl->grounded)
    {
        ctrl->step = DG_ZeroVector;
    }
    if (work->field_8E0 < 35)
    {
        if (work->body.is_end)
        {
            if (work->field_8DC < 3)
            {
                if (work->field_8DC == 1)
                {
                    work->field_8E0 = 37;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[13], 0, 4);
                }
                else
                {
                    work->field_8E0 = 35;
                    GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[11], 0, 4);
                }
            }
            else
            {
                work->field_8E0 = 36;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A10[12], 0, 4);
            }
        }
    }
    else if (ctrl->grounded)
    {
        work->field_8E4 = 1;
        work->field_8FC->force = DG_ZeroVector;
        GM_SeSet(&ctrl->mov, SE_HIT_FLOOR);
        Zako_800D0B18(work, 6, 1);
        work->field_8E8 = s03d_800D01C4;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
void s03d_800D01C4(Work *work, int arg)
{
    if (arg == 0)
    {
        if (work->field_8DC < 3)
        {
            if (work->field_8DC == 1)
            {
                work->field_8E0 = 0x2F;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A3C[1], 0, 4);
            }
            else
            {
                work->field_8E0 = 0x2D;
                GM_ConfigObjectAction(&work->body, s03d_word_800C3A38[1], 0, 4);
            }
        }
        else
        {
            work->field_8E0 = 0x2E;
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
        work->field_8E8 = s03d_800D0324;
        work->field_8F0 = 0;
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

const char s03d_dword_800DB5D4[] = {'n', 'o', 'i', 's'};
const char s03d_dword_800DB5D8[] = {'e', ' ', 'd', 'i'};
const char s03d_dword_800DB5DC[] = {'s', ' ', ' ', '='};
const char s03d_dword_800DB5E0[] = {'%', 'd', ',', '\n'};
const char s03d_dword_800DB5E4[] = {0x0, 0x0, 0x0, 0x0};

const char s03d_dword_800DB5E8[] = {' ', 'A', 's', 'i'};
const char s03d_dword_800DB5EC[] = {'a', 't', 'o', ' '};
const char s03d_dword_800DB5F0[] = {'m', 'i', 'k', 'k'};
const char s03d_dword_800DB5F4[] = {'e', '!', '!', ' '};
const char s03d_dword_800DB5F8[] = {'[', '%', 'd', ']'};
const char s03d_dword_800DB5FC[] = {'\n', 0x0, 0xa9, ','};


void s03d_800D0324(Work *work, int arg)
{
    if (arg == 0)
    {
        int *base = &s03d_dword_800DC310;
        work->field_B00 = 0;
        work->control.mov = s03d_dword_800C3B88;
        base[work->field_B08 * 4 + 0x90 / 4] = 1;
        if (work->field_BA0 == 0)
        {
            unsigned short *lv = (unsigned short *)linkvarbuf;
            lv[0x4F]++;
        }
    }
    {
        int *base = &s03d_dword_800DC310;
        if (base[work->field_B08 * 4 + 0x90 / 4] != 2)
        {
            return;
        }
        s03d_800CDB5C(work);
        work->field_8E8 = s03d_800CE12C;
        work->field_8F0 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigMotionAdjust(&work->body, NULL);
    }
}
int Zako_800D0408(Work *work)
{
    return work->control.mov.vx >= 0x1195;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D041C.s")
void s03d_800D05DC(Work *work, int arg1)
{
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C39F0[1], 0, 4, 0x3FE);
    }
    if (!(work->field_AD8 & 1))
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->field_B20 = (*(unsigned short *)&work->control.rot.vy - (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->field_B20 = (*(unsigned short *)&work->control.rot.vy - 0x400) & 0xFFF;
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
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (arg1 < 4)
    {
        work->field_B20 = (*(unsigned short *)&work->control.rot.vy + (arg1 << 8)) & 0xFFF;
    }
    else
    {
        work->field_B20 = (*(unsigned short *)&work->control.rot.vy + 0x400) & 0xFFF;
    }
}
void s03d_800D0754(Work *work, int arg1)
{
    work->field_B24 = 0x7D0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, ((short *)&s03d_dword_800C39F4)[1], 0, 4, 0x3FE);
    }
    if (!(work->field_AD8 & 4))
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D07DC(Work *work, int arg1)
{
    work->field_B24 = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A0C, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D085C(Work *work, int arg1)
{
    work->field_B24 = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C3A08, 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
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
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800D0958(Work *work, int arg1)
{
    work->field_B24 = 0;
    if (arg1 == 0)
    {
        GM_ConfigObjectOverride(&work->body, s03d_word_800C3A00[1], 0, 4, 0x3FE);
    }
    if (work->body.time2)
    {
        GM_ConfigObjectOverride(&work->body, *(short *)&s03d_dword_800C39E0, 0, 4, 0);
        work->field_8EC = 0;
        work->field_8F4 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D09D8.s")
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
    SVECTOR   step = work->field_8D4;
    SVECTOR  *pos = &work->control.mov;
    Item_Info info;

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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D0C90.s")
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
    unsigned short    *src = &work->field_B20;
    RADAR_SIGHT_PARAM *rp = &work->control.radar_param;

    rp->dir = src[0];
    rp->dis = src[2];
    rp->range = src[1];
    rp->r = 0;
}

void Zako_800D0FF4(Work *work)
{
    if (work->field_B33 & 4)
    {
        if (work->field_8FC->damaged & 6)
        {
            work->field_B32 |= 4;
        }
        if (work->field_900.damaged & 0x80)
        {
            work->field_B26 = 2;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D1054.s")
void Zako_800D13E8(Work *work)
{
    SVECTOR unused[2];

    (void)unused;
    work->field_B32 = 0;
}
void s03d_800D13F8(Work *work)
{
    switch (work->field_B26)
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
    if (work->field_8E0 < 0x2D)
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

    trg = work->field_8FC;
    turn = 0;
    if (!(trg->damaged & TARGET_PUSH))
    {
        return;
    }

    GV_AddVec3(&trg->offset, &work->control.step, &work->control.step);
    trg->damaged &= ~TARGET_PUSH;

    last_set = work->field_8E0;
    if (last_set == 1 || last_set == 2)
    {
        if (trg->offset.pad != 0)
        {
            if (GV_Time & 0x100)
            {
                if (work->field_B08 & 1)
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
                if (work->field_B08 & 1)
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
        ctrl->r_sphere = GV_NearExp2(ctrl->r_sphere, work->field_8E2);
    }
}
