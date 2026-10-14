#include <stdlib.h>
#include "mgrex.h"

extern int GM_GameOverTimer;
int sna_ration_available_8004FB4C(void);

int  s17a_800DE7B4(SVECTOR *pos, int dir, SVECTOR *ofs, int rot);
int  s17a_800DE8CC(MGREX_WORK *work, SVECTOR *ofs, int rot);
int  s17a_800DE900(SVECTOR *from, VECTOR *to, SVECTOR *out, int dist);
int  s17a_800DEBB4(MGREX_WORK *work, int action, int arg2);
void s17a_800DEBEC(MGREX_WORK *work, int action, int time);
void s17a_800DEC6C(MGREX_WORK *work);
void s17a_800DECA8(MGREX_WORK *work);
void s17a_800E085C(SVECTOR *from, SVECTOR *to, MATRIX *mat);

/* Metal Gear REX: movement decisions, motion state machine and weapons
 * (the original file name is unknown) */

SVECTOR mgrex_turn_ofs[13] = {
    {-320, 0, -780, 113},
    {-780, 0, -1490, 227},
    {-1360, 0, -1970, 341},
    {-2040, 0, -1960, 455},
    {-2100, 0, -1550, 568},
    {-1910, 0, -1200, 682},
    {320, 0, -860, -113},
    {790, 0, -1530, -227},
    {1380, 0, -1970, -341},
    {2050, 0, -1960, -455},
    {1620, 0, -1610, -568},
    {2430, 0, -1460, -682},
    {0, 0, 5000, 0}
};
SVECTOR mgrex_walk_ofs = {0, 0, -5000, 0};
int mgrex_turn_flag = 0;
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

const SVECTOR mgrex_front = {0, 0, 20000, 0};
const SVECTOR mgrex_right = {20000, 0, 0, 0};
const SVECTOR mgrex_left = {-20000, 0, 0, 0};
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



void s17a_800DD910(MGREX_WORK *work)
{
    SVECTOR *ofs;
    int      ang, dist, lim;
    int      turning;
    int      action;

    if (work->f1960 == 0)
    {
        return;
    }

    ang = work->f1A38;
    dist = work->f1A34;
    rcos(ang);

    lim = 568;
    turning = work->f1A58;
    action = abs(ang);
    if (turning == 0)
    {
        lim = 113;
    }

    if (action >= lim)
    {
        work->f1A58 = 0;

        if (ang > 0)
        {
            if (ang > 682)
            {
                action = 0x19;
                ofs = &mgrex_turn_ofs[5];
            }
            else if (ang > 568)
            {
                action = 0x18;
                ofs = &mgrex_turn_ofs[4];
            }
            else if (ang > 455)
            {
                action = 0x17;
                ofs = &mgrex_turn_ofs[3];
            }
            else if (ang > 341)
            {
                action = 0x16;
                ofs = &mgrex_turn_ofs[2];
            }
            else if (ang > 227)
            {
                action = 0x15;
                ofs = &mgrex_turn_ofs[1];
            }
            else
            {
                action = 0x14;
                ofs = &mgrex_turn_ofs[0];
            }
        }
        else if (ang < -682)
        {
            action = 0x1F;
            ofs = &mgrex_turn_ofs[11];
        }
        else if (ang < -568)
        {
            action = 0x1E;
            ofs = &mgrex_turn_ofs[10];
        }
        else if (ang < -455)
        {
            action = 0x1D;
            ofs = &mgrex_turn_ofs[9];
        }
        else if (ang < -341)
        {
            action = 0x1C;
            ofs = &mgrex_turn_ofs[8];
        }
        else if (ang < -227)
        {
            action = 0x1B;
            ofs = &mgrex_turn_ofs[7];
        }
        else
        {
            action = 0x1A;
            ofs = &mgrex_turn_ofs[12];
        }

        if (s17a_800DE8CC(work, ofs, ofs->pad) == 0 || dist > 17000)
        {
            s17a_800DEBB4(work, 3, action);
            return;
        }

        if (ang > 1024 && mgrex_turn_flag == 0)
        {
            ofs = &mgrex_turn_ofs[11];
            if (s17a_800DE8CC(work, ofs, ofs->pad) == 0)
            {
                s17a_800DEBB4(work, 3, 0x1F);
                mgrex_turn_flag = 1;
                return;
            }
        }

        if (ang < 1024 && mgrex_turn_flag == 0)
        {
            ofs = &mgrex_turn_ofs[5];
            if (s17a_800DE8CC(work, ofs, ofs->pad) == 0)
            {
                s17a_800DEBB4(work, 3, 0x19);
                mgrex_turn_flag = 1;
                return;
            }
        }

        mgrex_turn_flag = 0;

        if (s17a_800DE8CC(work, &mgrex_turn_ofs[12], 0) == 0)
        {
            s17a_800DEBB4(work, 1, 0);
        }
        else if (work->f1950 == 2)
        {
            s17a_800DEBB4(work, 1, 0);
        }
        else
        {
            s17a_800DEBB4(work, 2, 0);
        }
    }
    else if (dist < 10000 && !(work->f1980 == 1 && work->f1950 == 1))
    {
        work->f1A58 = 0;

        if (s17a_800DE8CC(work, &mgrex_walk_ofs, 0) == 0)
        {
            s17a_800DEBB4(work, 2, 0);
        }
        else
        {
            MATRIX   mat;
            SVECTOR  pos;
            SVECTOR  dirs[3];
            VECTOR   v[3];
            SVECTOR  out;
            long     flag;
            int      right, left;
            int      d0, d1, d2;

            right = 0;
            left = 0;

            dirs[0] = mgrex_front;
            dirs[1] = mgrex_right;
            dirs[2] = mgrex_left;

            ReadRotMatrix(&mat);
            pos.vx = mat.t[0];
            pos.vy = mat.t[1];
            pos.vz = mat.t[2];

            RotTrans(&dirs[0], &v[0], &flag);
            RotTrans(&dirs[1], &v[1], &flag);
            RotTrans(&dirs[2], &v[2], &flag);

            v[0].vx *= 4;
            v[0].vy *= 4;
            v[0].vz *= 4;
            v[1].vx *= 4;
            v[1].vy *= 4;
            v[1].vz *= 4;
            v[2].vx *= 4;
            v[2].vy *= 4;
            v[2].vz *= 4;

            d0 = s17a_800DE900(&pos, &v[0], &out, 80000);
            d1 = s17a_800DE900(&pos, &v[1], &out, 80000);
            d2 = s17a_800DE900(&pos, &v[2], &out, 80000);

            if (d1 > d2)
            {
                right = d1 > d0;
            }
            else if (d2 > d0)
            {
                left = 1;
            }

            if (right)
            {
                s17a_800DEBB4(work, 3, 0x16);
            }
            else if (left)
            {
                s17a_800DEBB4(work, 3, 0x1C);
            }
            else if (work->f1950 == 1)
            {
                s17a_800DEBB4(work, 2, 0);
            }
            else
            {
                s17a_800DEBB4(work, 1, 0);
            }
        }
    }
    else if (dist > 25000)
    {
        if (s17a_800DE8CC(work, &mgrex_turn_ofs[12], 0) == 0)
        {
            s17a_800DEBB4(work, 1, 0);
        }
        else
        {
            MATRIX  mat;
            SVECTOR pos;
            SVECTOR dirs[2];
            VECTOR  v[2];
            SVECTOR out;
            long    flag;
            int     d0, d1;

            dirs[0] = mgrex_right;
            dirs[1] = mgrex_left;
            work->f1A58 = 1;

            ReadRotMatrix(&mat);
            pos.vx = mat.t[0];
            pos.vy = mat.t[1];
            pos.vz = mat.t[2];

            RotTrans(&dirs[0], &v[0], &flag);
            RotTrans(&dirs[1], &v[1], &flag);

            v[0].vx *= 4;
            v[0].vy *= 4;
            v[0].vz *= 4;
            v[1].vx *= 4;
            v[1].vy *= 4;
            v[1].vz *= 4;

            d0 = s17a_800DE900(&pos, &v[0], &out, 80000);
            d1 = s17a_800DE900(&pos, &v[1], &out, 80000);

            if (d1 < d0)
            {
                s17a_800DEBB4(work, 3, 0x16);
            }
            else
            {
                s17a_800DEBB4(work, 3, 0x1C);
            }
        }
    }
    else
    {
        work->f1A58 = 0;
        s17a_800DEBB4(work, 0, 0);
    }
}

void s17a_800DDFC4(MGREX_WORK *work)
{
    SVECTOR target;
    VECTOR  d;
    int     dist, ang;
    int     dir;

    dir = 0;

    if (work->f1960 == 0)
    {
        return;
    }

    if (work->f1950 != 0)
    {
        s17a_800DEBB4(work, 0, 0);
        return;
    }

    if (work->f720 == 1)
    {
        target = work->f688;
    }
    else if (work->f720 == 2)
    {
        target = work->f6A8;
    }

    d.vx = (target.vx - work->control.mov.vx) >> 2;
    d.vy = (target.vy - work->control.mov.vy) >> 2;
    d.vz = (target.vz - work->control.mov.vz) >> 2;
    dist = SquareRoot0(d.vx * d.vx + d.vz * d.vz) * 4;

    ang = ratan2(d.vx, d.vz) - work->f1A3C;
    ang &= 0xFFF;
    if (ang < -2048)
    {
        ang += 4096;
    }
    if (ang > 2048)
    {
        ang -= 4096;
    }

    if (work->f724 == 0)
    {
        if (abs(ang) < 1024)
        {
            work->f724 = 1;
        }
        else
        {
            work->f724 = 2;
        }
    }

    if (dist <= 5000)
    {
        work->f724 = 9;
    }
    else if (dist <= 15000)
    {
        if (work->f724 == 3)
        {
            work->f724 = 5;
        }
        else if (work->f724 == 4)
        {
            work->f724 = 6;
        }
    }

    if (work->f720 == 1)
    {
        if (work->f688.pad == 0)
        {
            work->f724 = 9;
        }

        if (work->f690.pad == 0)
        {
            work->f724 = -1;
        }
    }
    else if (work->f720 == 2)
    {
        if (work->f6A8.pad == 0)
        {
            work->f724 = 9;
        }

        if (work->f6B0.pad == 0)
        {
            work->f724 = -1;
        }
    }

    if (work->f724 == 3 || work->f724 == 7)
    {
        s17a_800DEBB4(work, 1, 0);
    }
    else if (work->f724 == 4 || work->f724 == 8)
    {
        s17a_800DEBB4(work, 2, 0);
    }
    else if (work->f724 == 1 || work->f724 == 2 || work->f724 == 5 || work->f724 == 6 || work->f724 == 9)
    {
        if (work->f724 == 2 || work->f724 == 6)
        {
            ang = (ang + 2048) & 0xFFF;
            if (ang > 2048)
            {
                ang -= 4096;
            }
        }
        else if (work->f724 == 9)
        {
            if (work->f720 == 1)
            {
                dir = work->f690.vy;
            }
            else if (work->f720 == 2)
            {
                dir = work->f6B0.vy;
            }

            ang = (short)(dir - work->f1A3C) & 0xFFF;
            if (ang > 2048)
            {
                ang -= 4096;
            }
        }

        if (ang > 568)
        {
            s17a_800DEBB4(work, 3, 0x19);
        }
        else if (ang > 455)
        {
            s17a_800DEBB4(work, 3, 0x18);
        }
        else if (ang > 341)
        {
            s17a_800DEBB4(work, 3, 0x17);
        }
        else if (ang > 227)
        {
            s17a_800DEBB4(work, 3, 0x16);
        }
        else if (ang > 170)
        {
            s17a_800DEBB4(work, 3, 0x15);
        }
        else if (ang > 113)
        {
            s17a_800DEBB4(work, 3, 0x14);
        }
        else if (ang < -568)
        {
            s17a_800DEBB4(work, 3, 0x1F);
        }
        else if (ang < -455)
        {
            s17a_800DEBB4(work, 3, 0x1E);
        }
        else if (ang < -341)
        {
            s17a_800DEBB4(work, 3, 0x1D);
        }
        else if (ang < -227)
        {
            s17a_800DEBB4(work, 3, 0x1C);
        }
        else if (ang < -170)
        {
            s17a_800DEBB4(work, 3, 0x1B);
        }
        else if (ang < -113)
        {
            s17a_800DEBB4(work, 3, 0x1A);
        }
        else
        {
            if (work->f724 == 1)
            {
                work->f724 = 3;
            }
            else if (work->f724 == 2)
            {
                work->f724 = 4;
            }
            else if (work->f724 == 5)
            {
                work->f724 = 7;
            }
            else if (work->f724 == 6)
            {
                work->f724 = 8;
            }
            else if (work->f724 == 9)
            {
                work->f724 = -1;
            }

            s17a_800DEBB4(work, 0, 0);
        }
    }
}

void s17a_800DE43C(MGREX_WORK *work)
{
    SVECTOR target;
    VECTOR  d;
    int     dist, ang;
    int     dir;

    dir = 0;

    if (work->f1960 == 0)
    {
        return;
    }

    if (work->f720 == 1)
    {
        target = work->f688;
    }
    else if (work->f720 == 2)
    {
        target = work->f6A8;
    }

    d.vx = (target.vx - work->control.mov.vx) >> 2;
    d.vy = (target.vy - work->control.mov.vy) >> 2;
    d.vz = (target.vz - work->control.mov.vz) >> 2;
    dist = SquareRoot0(d.vx * d.vx + d.vz * d.vz) * 4;

    ang = ratan2(d.vx, d.vz) - work->f1A3C;
    ang &= 0xFFF;
    if (ang < -2048)
    {
        ang += 4096;
    }
    if (ang > 2048)
    {
        ang -= 4096;
    }

    if (work->f724 == 0)
    {
        if (abs(ang) < 1024)
        {
            work->f724 = 1;
        }
        else
        {
            work->f724 = 2;
        }
    }

    if (dist <= 5000)
    {
        work->f724 = 9;
    }
    else if (dist <= 15000)
    {
        if (work->f724 == 3)
        {
            work->f724 = 5;
        }
        else if (work->f724 == 4)
        {
            work->f724 = 6;
        }
    }

    if (work->f720 == 1)
    {
        if (work->f688.pad == 0)
        {
            work->f724 = 9;
        }

        if (work->f690.pad == 0)
        {
            work->f724 = -1;
        }
    }
    else if (work->f720 == 2)
    {
        if (work->f6A8.pad == 0)
        {
            work->f724 = 9;
        }

        if (work->f6B0.pad == 0)
        {
            work->f724 = -1;
        }
    }

    if (work->f724 == 3 || work->f724 == 7)
    {
        s17a_800DEBB4(work, 10, 0);
    }
    else if (work->f724 == 4 || work->f724 == 8)
    {
        s17a_800DEBB4(work, 11, 0);
    }
    else if (work->f724 == 1 || work->f724 == 2 || work->f724 == 5 || work->f724 == 6 || work->f724 == 9)
    {
        if (work->f724 == 2 || work->f724 == 6)
        {
            ang = (ang + 2048) & 0xFFF;
            if (ang > 2048)
            {
                ang -= 4096;
            }
        }
        else if (work->f724 == 9)
        {
            if (work->f720 == 1)
            {
                dir = work->f690.vy;
            }
            else if (work->f720 == 2)
            {
                dir = work->f6B0.vy;
            }

            ang = (short)(dir - work->f1A3C) & 0xFFF;
            if (ang > 2048)
            {
                ang -= 4096;
            }
        }

        if (ang > 113)
        {
            s17a_800DEBB4(work, 3, 0x2A);
        }
        else if (ang < -113)
        {
            s17a_800DEBB4(work, 3, 0x2B);
        }
        else
        {
            if (work->f724 == 1)
            {
                work->f724 = 3;
            }
            else if (work->f724 == 2)
            {
                work->f724 = 4;
            }
            else if (work->f724 == 5)
            {
                work->f724 = 7;
            }
            else if (work->f724 == 6)
            {
                work->f724 = 8;
            }
            else if (work->f724 == 9)
            {
                work->f724 = -1;
            }

            s17a_800DEBB4(work, 0, 0);
        }
    }
}

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

