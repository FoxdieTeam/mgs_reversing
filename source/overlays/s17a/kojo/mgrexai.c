#include <stdlib.h>
#include "mgrex.h"

extern int GM_GameOverTimer;
int sna_ration_available_8004FB4C(void);

/* Metal Gear REX: movement decisions, motion state machine and weapons
 * (the original file name is unknown) */

int s17a_dword_800C5248 = 0x0000FEC0;
int s17a_dword_800C524C = 0x0071FCF4;
int s17a_dword_800C5250 = 0x0000FCF4;
int s17a_dword_800C5254 = 0x00E3FA2E;
int s17a_dword_800C5258 = 0x0000FAB0;
int s17a_dword_800C525C = 0x0155F84E;
int s17a_dword_800C5260 = 0x0000F808;
int s17a_dword_800C5264 = 0x01C7F858;
int s17a_dword_800C5268 = 0x0000F7CC;
int s17a_dword_800C526C = 0x0238F9F2;
int s17a_dword_800C5270 = 0x0000F88A;
int s17a_dword_800C5274 = 0x02AAFB50;
int s17a_dword_800C5278 = 0x00000140;
int s17a_dword_800C527C = 0xFF8FFCA4;
int s17a_dword_800C5280 = 0x00000316;
int s17a_dword_800C5284 = 0xFF1DFA06;
int s17a_dword_800C5288 = 0x00000564;
int s17a_dword_800C528C = 0xFEABF84E;
int s17a_dword_800C5290 = 0x00000802;
int s17a_dword_800C5294 = 0xFE39F858;
int s17a_dword_800C5298 = 0x00000654;
int s17a_dword_800C529C = 0xFDC8F9B6;
int s17a_dword_800C52A0 = 0x0000097E;
int s17a_dword_800C52A4 = 0xFD56FA4C;
int s17a_dword_800C52A8 = 0x00000000;
int s17a_dword_800C52AC = 0x00001388;
int s17a_dword_800C52B0 = 0x00000000;
int s17a_dword_800C52B4 = 0x0000EC78;
int s17a_dword_800C52B8 = 0x00000000;
SVECTOR mgrex_bound_points[5] = {
    {0, 0, 8000, 0},
    {5000, 0, 0, 0},
    {-5000, 0, 0, 0},
    {2000, 0, -5000, 0},
    {-2000, 0, -5000, 0}
};
int s17a_dword_800C52E4 = 0x00000FA0;
int s17a_dword_800C52E8 = 0x00001964;
int s17a_dword_800C52EC = 0x0000F060;
int s17a_dword_800C52F0 = 0x00001964;
int s17a_dword_800C52F4 = 0x03E80FA0;
int s17a_dword_800C52F8 = 0x00000FA0;
int s17a_dword_800C52FC = 0x00000000;
int s17a_dword_800C5300 = 0xFFFFF000;
int s17a_dword_800C5304 = 0x00000000;
int s17a_dword_800C5308 = 0x00000000;
int s17a_dword_800C530C = 0x00C8FE00;
int s17a_dword_800C5310 = 0x00000000;
int s17a_dword_800C5314 = 0xFF38FE00;
int s17a_dword_800C5318 = 0x00000000;
int s17a_dword_800C531C = 0xFE4E0190;
int s17a_dword_800C5320 = 0x000013EA;
int s17a_dword_800C5324 = 0xFC92FE70;
int s17a_dword_800C5328 = 0x0000154A;
int s17a_dword_800C532C = 0xFAD60190;
int s17a_dword_800C5330 = 0x000016AA;
int s17a_dword_800C5334 = 0xFE4EFE70;
int s17a_dword_800C5338 = 0x000013EA;
int s17a_dword_800C533C = 0xFC920190;
int s17a_dword_800C5340 = 0x0000154A;
int s17a_dword_800C5344 = 0xFAD6FE70;
int s17a_dword_800C5348 = 0x000016AA;
VECTOR mgrex_up = {0, -4096, 0, 0};

const int s17a_dword_800E5C84 = 0x00000000;
const int s17a_dword_800E5C88 = 0x00004E20;
const int s17a_dword_800E5C8C = 0x00004E20;
const int s17a_dword_800E5C90 = 0x00000000;
const int s17a_dword_800E5C94 = 0x0000B1E0;
const int s17a_dword_800E5C98 = 0x00000000;
const int s17a_dword_800E5C9C = 0x800DEDA8;
const int s17a_dword_800E5CA0 = 0x800DEDE8;
const int s17a_dword_800E5CA4 = 0x800DEE80;
const int s17a_dword_800E5CA8 = 0x800DEF24;
const int s17a_dword_800E5CAC = 0x800DF000;
const int s17a_dword_800E5CB0 = 0x800DF058;
const int s17a_dword_800E5CB4 = 0x800DF09C;
const int s17a_dword_800E5CB8 = 0x800DF0DC;
const int s17a_dword_800E5CBC = 0x800DF124;
const int s17a_dword_800E5CC0 = 0x800DF178;
const int s17a_dword_800E5CC4 = 0x800DF1B8;
const int s17a_dword_800E5CC8 = 0x800DF268;
const int s17a_dword_800E5CCC = 0x800DF328;
const int s17a_dword_800E5CD0 = 0x800DF360;
const char s17a_dword_800E5CD4[] = "l_hatch2";

#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DD910.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DDFC4.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DE43C.s")
typedef struct _MGREX_BOUND_SCRATCH
{
    SVECTOR points[5];
    MATRIX  mat;
} MGREX_BOUND_SCRATCH;

int s17a_800DE7B4(SVECTOR *pos, int dir, SVECTOR *ofs, int rot)
{
    MGREX_BOUND_SCRATCH *scratch;
    SVECTOR             *points;
    int                  ret, i;
    int                  x, z;

    scratch = (MGREX_BOUND_SCRATCH *)getScratchAddr(0);

    scratch->mat = DG_ZeroMatrix;
    scratch->mat.t[0] = pos->vx;
    scratch->mat.t[2] = pos->vz;
    RotMatrixY(dir + rot, &scratch->mat);

    DG_SetPos(&scratch->mat);
    DG_MovePos(ofs);
    DG_PutVector(mgrex_bound_points, scratch->points, 5);

    ret = 0;
    points = scratch->points;
    for (i = 5; i > 0; i--, points++)
    {
        x = points->vx;
        z = points->vz;

        if (x > 13000)
        {
            ret = -1;
        }

        if (x < -13000)
        {
            ret = -1;
        }

        if (z > 25000)
        {
            ret = -1;
        }

        if (z < -25000)
        {
            ret = -1;
        }
    }

    return ret;
}

int s17a_800DE8CC(MGREX_WORK *work, SVECTOR *ofs, int rot)
{
    return s17a_800DE7B4(&work->control.mov, work->control.rot.vy, ofs, rot);
}

int s17a_800DE900(SVECTOR *from, VECTOR *to, SVECTOR *out, int dist)
{
    VECTOR v;
    VECTOR d;
    int    clip;
    int    x;

    clip = 0;
    v = *to;

    x = v.vx;
    if (x < -13000)
    {
        clip = -13000;
        goto clip_x;
    }

    if (x > 13000)
    {
        clip = 13000;
clip_x:
        v.vx = clip;
        clip = (clip - from->vx) >> 4;
        x = (x - from->vx) >> 4;
        v.vy = ((v.vy - from->vy) * clip) / x + from->vy;
        v.vz = ((v.vz - from->vz) * clip) / x + from->vz;
        clip = 1;
    }

    x = v.vz;
    if (x < -25000)
    {
        clip = -25000;
        goto clip_z;
    }

    if (x > 25000)
    {
        clip = 25000;
clip_z:
        v.vz = clip;
        clip = (clip - from->vz) >> 4;
        x = (x - from->vz) >> 4;
        v.vy = ((v.vy - from->vy) * clip) / x + from->vy;
        v.vx = ((v.vx - from->vx) * clip) / x + from->vx;
        clip = 1;
    }

    if (clip == 1 || dist == -1)
    {
        d.vx = (v.vx - from->vx) >> 4;
        d.vy = (v.vy - from->vy) >> 4;
        d.vz = (v.vz - from->vz) >> 4;
        Square0(&d, &d);
        dist = SquareRoot0(d.vx + d.vy + d.vz) * 16;
    }

    out->vx = v.vx;
    out->vy = v.vy;
    out->vz = v.vz;
    return dist;
}

int s17a_800DEBB4(MGREX_WORK *work, int action, int arg2)
{
    if (work->f1960 == 1 && work->f1954 != action)
    {
        work->f1954 = action;
        work->f1958 = arg2;
        work->f1960 = 0;
        return 1;
    }

    return 0;
}

void s17a_800DEBEC(MGREX_WORK *work, int action, int time)
{
    if (work->body.action != action)
    {
        work->f70C = action;
        GM_ConfigObjectAction(&work->body, action, 0, time);
        GM_ConfigObjectAction(&work->leg_l, action, 0, time);
        GM_ConfigObjectAction(&work->leg_r, action, 0, time);
    }
}

void s17a_800DEC6C(MGREX_WORK *work)
{
    if (work->body.m_ctrl->info1.field_14 == 1)
    {
        work->body.m_ctrl->info1.field_14 = 0;
        work->leg_l.m_ctrl->info1.field_14 = 0;
        work->leg_r.m_ctrl->info1.field_14 = 0;
    }
}

void s17a_800DECA8(MGREX_WORK *work)
{
    if (*(int *)&work->body.m_ctrl->info1 != 1)
    {
        work->body.m_ctrl->info1.field_14 = 1;
        work->leg_l.m_ctrl->info1.field_14 = 1;
        work->leg_r.m_ctrl->info1.field_14 = 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DECE4.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DF3E8.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DF720.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DFAE8.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800DFF74.s")
#pragma INCLUDE_ASM("asm/overlays/s17a/s17a_800E0328.s")
int s17a_800E0710(MGREX_WORK *work)
{
    SVECTOR pos;
    MATRIX *world;
    TARGET *target1;
    TARGET *target2;
    int     power;

    if (work->f1950 == 0 && work->f1960 == 1)
    {
        work->f6FC = 2;
        work->target3->class = 8;
        work->target4->class = 8;
        s17a_800DEBB4(work, 0, 0);
        return -1;
    }

    if (work->f1A60 == 0)
    {
        work->f1A60 = 1;
    }

    world = &work->leg_l.objs->objs[8].world;
    work->f1A64--;
    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];
    target1 = &work->target1;
    GM_MoveTarget(target1, &pos);

    world = &work->leg_r.objs->objs[8].world;
    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];
    target2 = &work->target2;
    GM_MoveTarget(target2, &pos);

    power = GM_PowerTarget(target1);
    power += GM_PowerTarget(target2);
    if (power)
    {
        if (GM_GameOverTimer == 0 && !sna_ration_available_8004FB4C())
        {
            work->f1A64 = -1;
        }
    }

    return 0;
}

void s17a_800E085C(SVECTOR *from, SVECTOR *to, MATRIX *mat)
{
    VECTOR dir;
    VECTOR up;
    VECTOR side;

    mat->t[0] = from->vx;
    mat->t[1] = from->vy;
    mat->t[2] = from->vz;

    dir.vx = to->vx - from->vx;
    dir.vy = to->vy - from->vy;
    dir.vz = to->vz - from->vz;

    OuterProduct12(&mgrex_up, &dir, &side);
    VectorNormal(&side, &side);
    VectorNormal(&dir, &dir);
    OuterProduct12(&dir, &side, &up);

    mat->m[0][0] = side.vx;
    mat->m[0][1] = up.vx;
    mat->m[0][2] = dir.vx;
    mat->m[1][0] = side.vy;
    mat->m[1][1] = up.vy;
    mat->m[1][2] = dir.vy;
    mat->m[2][0] = side.vz;
    mat->m[2][1] = up.vz;
    mat->m[2][2] = dir.vz;
}

