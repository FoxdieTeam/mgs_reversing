#include <stdlib.h>
#include "linkvar.h"
#include "takabe/windcrcl.h"
#include "okajima/bullet.h"
#include "mgrex.h"

extern int     GM_GameOverTimer;
extern SVECTOR GM_PlayerPosition;
extern TARGET  s17a_dword_800E5E60;
int sna_ration_available_8004FB4C(void);

int  s17a_800DE7B4(SVECTOR *pos, int dir, SVECTOR *ofs, int rot);
int  s17a_800DE8CC(MGREX_WORK *work, SVECTOR *ofs, int rot);
int  s17a_800DE900(SVECTOR *from, VECTOR *to, SVECTOR *out, int dist);
int  s17a_800DEBB4(MGREX_WORK *work, int action, int arg2);
void s17a_800DEBEC(MGREX_WORK *work, int action, int time);
void s17a_800DEC6C(MGREX_WORK *work);
void s17a_800DECA8(MGREX_WORK *work);
void s17a_800E085C(SVECTOR *from, SVECTOR *to, MATRIX *mat);

void *NewMgLaser(MATRIX *root, int side, int power, int time);
void *NewHomingMissile(MATRIX *world, SVECTOR *aim, int side);
void *NewMgHatch(MATRIX *world);

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
SVECTOR mgrex_feet[2] = {
    {4000, 0, 6500, 0},
    {-4000, 0, 6500, 0}
};
SVECTOR mgrex_stomp_size = {4000, 1000, 4000, 0};
VECTOR mgrex_laser_up = {0, -4096, 0, 0};
SVECTOR mgrex_missile_rot_l = {-512, 200, 0, 0};
SVECTOR mgrex_missile_rot_r = {-512, -200, 0, 0};
SVECTOR mgrex_missile_ofs_l[3] = {
    {400, -434, 5098, 0},
    {-400, -878, 5450, 0},
    {400, -1322, 5802, 0}
};
SVECTOR mgrex_missile_ofs_r[3] = {
    {-400, -434, 5098, 0},
    {400, -878, 5450, 0},
    {-400, -1322, 5802, 0}
};
VECTOR mgrex_up = {0, -4096, 0, 0};

const SVECTOR mgrex_front = {0, 0, 20000, 0};
const SVECTOR mgrex_right = {20000, 0, 0, 0};
const SVECTOR mgrex_left = {-20000, 0, 0, 0};



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

int s17a_800DECE4(MGREX_WORK *work)
{
    int action;
    int time;

    time = 2;
    action = work->body.action;

    if (action != 0 && action != 0x2F && action != 0x31)
    {
        if (action == 0xD)
        {
            if (work->body.m_ctrl->info1.frame != 24 && !work->body.is_end)
            {
                return 0;
            }
        }
        else if (action == 0xE)
        {
            if (work->body.m_ctrl->info1.frame != 23 && !work->body.is_end)
            {
                return 0;
            }
        }
        else if (!work->body.is_end)
        {
            return 0;
        }
    }

    switch (work->f1950)
    {
    case 0:
        s17a_800DEBEC(work, 0, time);
        if (work->f1954 != 0)
        {
            work->f1950 = work->f1954;
            work->f195C = 0;
            work->f1960 = 0;
        }
        else
        {
            work->f195C = 1;
            work->f1960 = 1;
        }
        break;

    case 1:
        if (work->f1954 != 1)
        {
            if (work->body.action == 1 || work->body.action == 2)
            {
                s17a_800DEBEC(work, 5, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
            else
            {
                s17a_800DEBEC(work, 4, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 1, time);
            work->f195C = 1;
            work->f1960 = 1;
            break;
        }

        if (work->body.action == 1 || work->body.action == 2)
        {
            s17a_800DEBEC(work, 3, time);
        }
        else
        {
            s17a_800DEBEC(work, 2, time);
        }
        break;

    case 2:
        if (work->f1954 != 2)
        {
            if (work->body.action == 0xF || work->body.action == 0x11)
            {
                s17a_800DEBEC(work, 0x12, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
            else
            {
                s17a_800DEBEC(work, 0x13, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0xF, time);
            work->f195C = 1;
            work->f1960 = 1;
            break;
        }

        if (work->body.action == 0xF || work->body.action == 0x11)
        {
            s17a_800DEBEC(work, 0x10, 0);
        }
        else
        {
            s17a_800DEBEC(work, 0x11, 0);
        }
        break;

    case 3:
        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, work->f1958, time);
            GM_SeSetMode(&work->control.mov, 0xBC, 1);
            work->f195C = 1;
            work->f1960 = 0;
            break;
        }

        work->control.rot.vy += work->body_rots[0].vy;
        work->control.turn.vy += work->body_rots[0].vy;

        if (work->control.rot.vy < -2048)
        {
            work->control.rot.vy += 4096;
        }

        if (work->control.rot.vy > 2048)
        {
            work->control.rot.vy -= 4096;
        }

        if (work->control.turn.vy < -2048)
        {
            work->control.turn.vy += 4096;
        }

        if (work->control.turn.vy > 2048)
        {
            work->control.turn.vy -= 4096;
        }

        s17a_800DEBEC(work, 0, 0);
        work->f1954 = 0;
        work->f1950 = 0;
        work->f195C = 0;
        break;

    case 4:
        if (work->f1954 != 4)
        {
            s17a_800DEBEC(work, 9, time);
            GM_SeSetMode(&work->control.mov, 0xBF, 1);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 6, time);
            GM_SeSetMode(&work->control.mov, 0xBD, 1);
            work->f195C = 1;
            break;
        }

        s17a_800DEBEC(work, 8, time);
        work->f1960 = 1;
        break;

    case 5:
        if (work->f1954 != 5)
        {
            s17a_800DEBEC(work, 0xC, time);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0xA, time);
            work->f195C = 1;
            break;
        }

        s17a_800DEBEC(work, 0xB, time);
        work->f1960 = 1;
        break;

    case 6:
        if (work->f1954 != 6)
        {
            s17a_800DEBEC(work, 0, time);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0, time);
            work->f195C = 1;
            break;
        }

        s17a_800DEBEC(work, 0, time);
        work->f1960 = 1;
        break;

    case 7:
        if (work->f1954 != 7)
        {
            s17a_800DECA8(work);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0xD, time);
            work->f195C = 1;
            break;
        }

        s17a_800DEC6C(work);
        work->f1960 = 1;
        break;

    case 8:
        if (work->f1954 != 8)
        {
            s17a_800DECA8(work);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0xE, time);
            work->f195C = 1;
            break;
        }

        s17a_800DEC6C(work);
        work->f1960 = 1;
        break;

    case 9:
        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0x2C, time);
            work->f195C = 1;
            work->f1960 = 0;
            work->f1954 = 0;
            break;
        }

        s17a_800DEBEC(work, 0, time);
        work->f195C = 0;
        work->f1960 = 0;
        work->f1950 = work->f1954;
        break;

    case 10:
        if (work->f1954 != 10)
        {
            if (work->body.action == 0x20 || work->body.action == 0x21)
            {
                s17a_800DEBEC(work, 0x24, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
            else
            {
                s17a_800DEBEC(work, 0x23, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
        }

        GM_SeSetMode(&work->control.mov, 0xB4, 1);

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0x20, time);
            work->f195C = 1;
            work->f1960 = 1;
            break;
        }

        if (work->body.action == 0x20 || work->body.action == 0x21)
        {
            s17a_800DEBEC(work, 0x22, time);
        }
        else
        {
            s17a_800DEBEC(work, 0x21, time);
        }
        break;

    case 11:
        if (work->f1954 != 11)
        {
            if (work->body.action == 0x25 || work->body.action == 0x27)
            {
                s17a_800DEBEC(work, 0x28, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
            else
            {
                s17a_800DEBEC(work, 0x29, time);
                work->f195C = 0;
                work->f1960 = 0;
                work->f1950 = work->f1954;
                break;
            }
        }

        GM_SeSetMode(&work->control.mov, 0xB4, 1);

        if (work->f195C != 1)
        {
            s17a_800DEBEC(work, 0x25, time);
            work->f195C = 1;
            work->f1960 = 1;
            break;
        }

        if (work->body.action == 0x25 || work->body.action == 0x27)
        {
            s17a_800DEBEC(work, 0x26, 0);
        }
        else
        {
            s17a_800DEBEC(work, 0x27, 0);
        }
        break;

    case 12:
        if (work->f1954 != 12)
        {
            s17a_800DEBEC(work, 0x30, time);
            GM_SeSetMode(&work->control.mov, 0xBF, 1);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            work->f195C = 1;
        }

        s17a_800DEBEC(work, 0x2F, 0);
        work->f1960 = 1;
        break;

    case 13:
        if (work->f1954 != 13)
        {
            s17a_800DEBEC(work, 0, time);
            GM_SeSetMode(&work->control.mov, 0xBF, 1);
            work->f195C = 0;
            work->f1960 = 0;
            work->f1950 = work->f1954;
            break;
        }

        if (work->f195C != 1)
        {
            work->f195C = 1;
        }

        s17a_800DEBEC(work, 0x31, 0);
        work->f1960 = 1;
        break;

    }

    return 0;
}

int s17a_800DF3E8(MGREX_WORK *work)
{
    SVECTOR target;
    SVECTOR feet[2];
    SVECTOR d;
    int     d0, d1;
    int     dist, dir;

    if (work->f1988 == 0)
    {
        target = GM_PlayerPosition;
    }
    else
    {
        target = work->player_pos;
    }

    if (work->f1960 != 1)
    {
        return -1;
    }

    if (work->f6FC >= 3 && work->f6FC <= 6)
    {
        return -1;
    }

    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(mgrex_feet, feet, 2);

    d.vx = (target.vx - feet[0].vx) >> 2;
    d.vy = 0;
    d.vz = (target.vz - feet[0].vz) >> 2;
    d0 = GV_VecLen3(&d) * 4;

    d.vx = (target.vx - feet[1].vx) >> 2;
    d.vy = 0;
    d.vz = (target.vz - feet[1].vz) >> 2;
    d1 = GV_VecLen3(&d) * 4;

    if (d0 < 2500 || d1 < 2500)
    {
        if (d0 < d1)
        {
            s17a_800DEBB4(work, 7, 0);
        }
        else
        {
            s17a_800DEBB4(work, 8, 0);
        }

        work->f1A64 = 26;
        work->f700 = 4;
        work->f1A60 = 0;
        work->f6FC = 6;
        return 0;
    }

    if (work->timers[3] == 0 && work->f1A5C == 0)
    {
        dist = work->f1A34;
        dir = work->f1A38;
        if ((dist > 3000 && dist < 15000) && abs(dir) < 113)
        {
            s17a_800DEBB4(work, 5, 0);
            work->f1A60 = 0;

            work->f1A64 = (GM_GameLevel <= 0) ? 40 : 25;

            work->f700 = 2;
            work->f6FC = 4;
            return 0;
        }
    }

    if (work->timers[1] == 0 && work->f1A5C == 0)
    {
        dist = work->f1A34;
        dir = work->f1A38;
        if ((dist > 13000 && dist < 20000) && abs(dir) < 113)
        {
            s17a_800DEBB4(work, 6, 0);
            work->f700 = 1;
            work->f1A60 = 0;
            work->f6FC = 5;
            work->f1A64 = work->f5F0 * 2;
            return 0;
        }
    }

    if (work->timers[4] == 0 || work->f1A5C != 0)
    {
        dist = work->f1A34;
        dir = work->f1A38;
        if ((dist > 15000 && dist < 25000) && abs(dir) < 227)
        {
            s17a_800DEBB4(work, 4, 0);
            work->f1A64 = 120;
            work->f1A60 = 0;
            work->f700 = 3;
            work->f6FC = 3;
            return 0;
        }
    }

    work->f6FC = 2;
    return 0;
}

int s17a_800DF720(MGREX_WORK *work)
{
    SVECTOR pos;
    MATRIX  mat;
    TARGET *target;
    MATRIX *world;
    int     vital;
    int     power;

    if (work->f1A64 == 0)
    {
        work->f6FC = 2;
        s17a_800DEBB4(work, 0, 0);
        return -1;
    }

    if ((work->f1950 != 7 && work->f1950 != 8) || work->f1960 != 1)
    {
        if (work->f1A60 == 0)
        {
            if (work->body.action == 0xD)
            {
                work->target3->class &= ~8;
            }
            else if (work->body.action == 0xE)
            {
                work->target4->class &= ~8;
            }

            return 0;
        }

        work->f6FC = 2;
        s17a_800DEBB4(work, 0, 0);
        return -1;
    }

    if (work->f1950 == 7)
    {
        target = &work->target1;
        world = &work->leg_l.objs->objs[8].world;
    }
    else
    {
        target = &work->target2;
        world = &work->leg_r.objs->objs[8].world;
    }

    if (work->f1A60 == 0)
    {
        work->f1A60 = 1;
    }

    if (--work->f1A64 >= 25)
    {
        pos.vx = world->t[0];
        pos.vy = world->t[1];
        pos.vz = world->t[2];
        GM_MoveTarget(target, &pos);

        vital = target->vital;
        power = GM_PowerTarget(target);
        target->vital = vital;
    }
    else
    {
        power = 0;
    }

    if (power && GM_GameOverTimer == 0)
    {
        work->f1A60 = 2;
    }

    if (work->f1A64 == 25)
    {
        SetRotMatrix(&DG_ZeroMatrix);

        if (work->f1950 == 7)
        {
            SetTransMatrix(&work->leg_l.objs->objs[8].world);
        }
        else
        {
            SetTransMatrix(&work->leg_r.objs->objs[8].world);
        }

        ReadRotMatrix(&mat);
        mat.t[1] = 0;
        NewWindcrcl_800CF6BC(&mat, 4000);
        return 0;
    }

    if (work->f1A64 == 24)
    {
        work->target3->class |= 8;
        work->target4->class |= 8;

        if (work->f1A60 == 2)
        {
            work->f1A64 = -1;
        }

        if (GM_GameLevel > 0)
        {
            GM_SetTarget(&s17a_dword_800E5E60, 4, 0, &mgrex_stomp_size);
            GM_SetPowerTarget(&s17a_dword_800E5E60, 1, -1, 0, 0, &DG_ZeroVector);
            s17a_dword_800E5E60.center.vx = world->t[0];
            s17a_dword_800E5E60.center.vy = world->t[1];
            s17a_dword_800E5E60.center.vz = world->t[2];
            GM_PowerTarget(&s17a_dword_800E5E60);
        }

        return 0;
    }

    if (work->f1A64 == -20 || work->f1A64 == -60 || work->f1A64 == -70)
    {
        if (work->f1950 == 7)
        {
            if (work->leg_l.action2 != 0x2D)
            {
                GM_ConfigObjectOverride(&work->leg_l, 0x2D, 0, 4, 0xF00);
            }
        }
        else if (work->leg_r.action2 != 0x2E)
        {
            GM_ConfigObjectOverride(&work->leg_r, 0x2E, 0, 4, 0xF00);
        }

        return 0;
    }

    if (work->f1A64 == -100)
    {
        if (GM_GameOverTimer == 0)
        {
            work->f1A64 = 3;
        }

        return 0;
    }

    if (work->f1950 == 7)
    {
        if (work->leg_l.time2 != 0)
        {
            work->leg_l.action2 = 0;
            work->leg_l.m_ctrl->info1.mask = 0;
            work->leg_l.m_ctrl->info2.mask = 0xFFFF;
        }
    }
    else if (work->leg_r.time2 != 0)
    {
        work->leg_r.action2 = 0;
        work->leg_r.m_ctrl->info1.mask = 0;
        work->leg_r.m_ctrl->info2.mask = 0xFFFF;
    }

    return 0;
}

typedef struct _MGREX_LASER_SCRATCH
{
    MATRIX rot;
    VECTOR dir;
    VECTOR up;
    VECTOR side;
    MATRIX world;
    MATRIX local;
} MGREX_LASER_SCRATCH;

int s17a_800DFAE8(MGREX_WORK *work)
{
    SVECTOR              target;
    SVECTOR              ofs;
    MGREX_LASER_SCRATCH *scratch;
    MATRIX              *world;
    int                  x, y, z;
    int                  yaw, pitch;
    int                  dir, speed;

    target = work->player_pos;
    target.vy = 0;

    if (work->f1A60 == 0)
    {
        ofs = DG_ZeroVector;
        DG_SetPos2(&target, &work->control.rot);

        if (work->f1A38 > 0)
        {
            ofs.vx = -6000;
            ofs.vz = 0;
            work->f1A70 = 200;
            work->f1A74 = work->f1A3C + 1024;
        }
        else
        {
            ofs.vx = 6000;
            ofs.vz = 0;
            work->f1A70 = 200;
            work->f1A74 = work->f1A3C - 1024;
        }

        DG_PutVector(&ofs, &work->f1A68, 1);
        work->f1A78 = NULL;
        work->f1A60 = 1;
    }

    scratch = (MGREX_LASER_SCRATCH *)getScratchAddr(0);

    world = &work->body.objs->objs[9].world;
    scratch->dir.vx = (work->f1A68.vx - world->t[0]) >> 2;
    scratch->dir.vy = (work->f1A68.vy - world->t[1]) >> 2;
    scratch->dir.vz = (work->f1A68.vz - world->t[2]) >> 2;

    OuterProduct12(&mgrex_laser_up, &scratch->dir, &scratch->side);
    VectorNormal(&scratch->side, &scratch->side);
    VectorNormal(&scratch->dir, &scratch->dir);
    OuterProduct12(&scratch->dir, &scratch->side, &scratch->up);

    scratch->rot.m[0][0] = scratch->side.vx;
    scratch->rot.m[0][1] = scratch->up.vx;
    scratch->rot.m[0][2] = scratch->dir.vx;
    scratch->rot.m[1][0] = scratch->side.vy;
    scratch->rot.m[1][1] = scratch->up.vy;
    scratch->rot.m[1][2] = scratch->dir.vy;
    scratch->rot.m[2][0] = scratch->side.vz;
    scratch->rot.m[2][1] = scratch->up.vz;
    scratch->rot.m[2][2] = scratch->dir.vz;
    scratch->rot.t[0] = world->t[0];
    scratch->rot.t[1] = world->t[1];
    scratch->rot.t[2] = world->t[2];

    scratch->world = work->body.objs->objs[0].world;
    DG_TransposeMatrix(&scratch->world, &scratch->world);
    MulMatrix0(&scratch->world, &scratch->rot, &scratch->local);

    x = scratch->local.m[0][2];
    z = scratch->local.m[2][2];
    y = scratch->local.m[1][2];

    yaw = ratan2(x, z) & 0xFFF;
    pitch = ratan2(-y, SquareRoot0(x * x + z * z)) & 0xFFF;

    if (pitch > 2048)
    {
        pitch -= 4096;
    }

    if (yaw > 2048)
    {
        yaw -= 4096;
    }

    work->f794.vx = pitch;
    work->f794.vy = yaw;
    work->f794.vz = 0;

    if (work->f1A64 != 0)
    {
        if (work->f1950 == 5 && work->f1960 == 1)
        {
            goto fire;
        }

        if (work->f1A60 == 1)
        {
            work->f1A74 = ratan2(work->player_pos.vx - work->f1A68.vx, work->player_pos.vz - work->f1A68.vz);
            return 0;
        }
    }

    work->f6FC = 2;
    work->f794 = DG_ZeroVector;
    work->f794.pad = 0;
    work->timers[3] = work->f628;
    return -1;

fire:
    dir = work->f1A74;
    speed = work->f1A70;
    work->f1A60 = 2;

    work->f1A68.vx += (rsin(dir) * speed) / 4096;
    work->f1A68.vz += (rcos(dir) * speed) / 4096;
    work->f794.pad = 1;

    if (GM_GameLevel <= 0)
    {
        work->f1A70 = GV_NearSpeed(work->f1A70, 300, 20);
    }
    else
    {
        work->f1A70 = GV_NearSpeed(work->f1A70, 600, 40);
    }

    if (work->f1A78 == NULL)
    {
        work->f1A78 = NewMgLaser(&work->body.objs->objs[9].world, 2, work->f644, work->f1A64 - 1);
    }

    work->f1A64--;
    return 0;
}

int s17a_800DFF74(MGREX_WORK *work)
{
    SVECTOR ofs;
    SVECTOR rot;
    SVECTOR from;
    SVECTOR to;
    MATRIX  mat;
    int     dir, speed;
    int     dx, dz;

    if (work->f1A64 == 0)
    {
        goto fail;
    }

    if (work->f1950 != 6 || work->f1960 != 1)
    {
        if (work->f1A60 == 0)
        {
            return 0;
        }

fail:
        work->f6FC = 2;
        work->timers[1] = work->f5F4;
        return -1;
    }

    if (work->f1A60 == 0)
    {
        rot = DG_ZeroVector;
        rot.vy = work->f1A38 + work->f1A3C;
        DG_SetPos2(&work->control.mov, &rot);

        ofs = DG_ZeroVector;
        ofs.vz = work->f1A34 - 5000;
        DG_PutVector(&ofs, &work->f1A68, 1);

        work->f1A70 = (GM_GameLevel <= 0) ? 200 : 400;
        work->f1A74 = rot.vy;
        work->f1A60 = 1;
        work->f1A68.vy = work->player_pos.vy;
        work->f604 = work->body_adjust[2].vy;
    }

    if (work->f1A60 == 1)
    {
        DG_SetPos(&work->body.objs->objs[2].world);

        if (work->f1A64 & 1)
        {
            DG_PutVector(&work->f6B8, &from, 1);
            to = DG_ZeroVector;
            to.vx = (GM_GameLevel > 0) ? 0 : 800;
        }
        else
        {
            DG_PutVector(&work->f6C0, &from, 1);
            to = DG_ZeroVector;
            to.vx = (GM_GameLevel > 0) ? 0 : -800;
        }

        DG_SetPos2(&work->f1A68, &work->control.rot);
        DG_PutVector(&to, &to, 1);
        s17a_800E085C(&from, &to, &mat);
        RotMatrixY(work->body_adjust[2].vy - work->f604, &mat);
        GM_SeSetMode(&from, 0xC4, 1);
        NewBulletEx(0x520, &mat, 2, 1, 0, work->f614, work->f618, work->f61C, work->f620);

        work->f1A64--;

        if (work->f1A60 == 1)
        {
            dir = work->f1A74;
            speed = work->f1A70;
            work->f1A68.vx += (rsin(dir) * speed) / 4096;
            work->f1A68.vz += (rcos(dir) * speed) / 4096;

            dx = GM_PlayerPosition.vx - work->f1A68.vx;
            dz = GM_PlayerPosition.vz - work->f1A68.vz;
            if (abs(dx) < 5000 && abs(dz) < 5000)
            {
                s17a_dword_800E5E30 = 45;
            }
        }
    }

    work->f1A60++;
    if (work->f1A60 >= (work->f5F8 + 1) / 2)
    {
        work->f1A60 = 1;
    }

    return 0;
}

#define MGREX_HATCH_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_AMBIENT )

int s17a_800E0328(MGREX_WORK *work)
{
    MATRIX   world;
    MATRIX   rot;
    SVECTOR  ang;
    SVECTOR *rotv;
    SVECTOR *ofs;
    MATRIX  *root;

    if (work->f1A64 == 0)
    {
        goto fail;
    }

    if (work->f1950 != 4 || work->f1960 != 1)
    {
        if (work->f1A60 == 0)
        {
            return 0;
        }

fail:
        work->f6FC = 2;
        work->timers[4] = 60;
        return -1;
    }

    if (work->f1A60 == 0)
    {
        work->f1A68 = work->player_pos;

        if (work->f1A38 > 0)
        {
            work->f1A60 = 1;
            if (++work->f1978 >= 3)
            {
                work->f1978 = 0;
            }
        }
        else
        {
            work->f1A60 = 2;
            if (++work->f197C >= 3)
            {
                work->f197C = 0;
            }
        }
    }

    if (work->f1A64 == 110 || work->f1A64 == 100 || work->f1A64 == 80 || work->f1A64 == 60)
    {
        if (work->f1A60 == 1)
        {
            rotv = &mgrex_missile_rot_l;
            root = &work->leg_l.objs->objs[1].world;
            ofs = &mgrex_missile_ofs_l[work->f1978];
        }
        else
        {
            rotv = &mgrex_missile_rot_r;
            root = &work->leg_r.objs->objs[1].world;
            ofs = &mgrex_missile_ofs_r[work->f197C];
        }

        if (work->f1A64 == 110)
        {
            if (work->f1A60 == 1)
            {
                if (work->hatch_l_model < 3)
                {
                    GM_FreeObject((OBJECT *)&work->hatch_l);
                    GM_InitObjectNoRots(&work->hatch_l, GV_StrCode("l_hatch2") + work->hatch_l_model, MGREX_HATCH_FLAG, 0);
                    GM_ConfigObjectLight((OBJECT *)&work->hatch_l, work->light);
                    GM_ConfigObjectRoot((OBJECT *)&work->hatch_l, &work->leg_l, 1);

                    ang = *rotv;
                    if (work->hatch_l_model != 0)
                    {
                        ang.vy = 400;
                    }
                    else
                    {
                        ang.vy = -400;
                    }

                    RotMatrix_gte(&ang, &rot);

                    DG_SetPos(root);
                    DG_MovePos(ofs);
                    ReadRotMatrix(&world);
                    MulMatrix0(&world, &rot, &world);
                    NewMgHatch(&world);

                    work->hatch_l_model++;
                }
            }
            else if (work->hatch_r_model < 3)
            {
                GM_FreeObject((OBJECT *)&work->hatch_r);
                GM_InitObjectNoRots(&work->hatch_r, GV_StrCode("l_hatch2") + work->hatch_r_model, MGREX_HATCH_FLAG, 0);
                GM_ConfigObjectLight((OBJECT *)&work->hatch_r, work->light);
                GM_ConfigObjectRoot((OBJECT *)&work->hatch_r, &work->leg_r, 1);

                ang = *rotv;
                if (work->hatch_r_model != 0)
                {
                    ang.vy = -400;
                }
                else
                {
                    ang.vy = 400;
                }

                RotMatrix_gte(&ang, &rot);

                DG_SetPos(root);
                DG_MovePos(ofs);
                ReadRotMatrix(&world);
                MulMatrix0(&world, &rot, &world);
                NewMgHatch(&world);

                work->hatch_r_model++;
            }
        }
        else
        {
            RotMatrix_gte(rotv, &rot);

            DG_SetPos(root);
            DG_MovePos(ofs);
            ReadRotMatrix(&world);
            MulMatrix0(&world, &rot, &world);
            NewHomingMissile(&world, &work->player_pos, 2);
        }
    }

    work->f1A64--;
    return 0;
}

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

