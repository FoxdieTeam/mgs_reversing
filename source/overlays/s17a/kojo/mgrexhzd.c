#include <stdlib.h>
#include "linkvar.h"
#include "mgrex.h"

/* Metal Gear REX: hazards (walls, nikita hit boxes, radar search) */

typedef struct _MGREX_HITBOX
{
    SVECTOR pos;
    SVECTOR size;
    SVECTOR rot;
    int     joint;
} MGREX_HITBOX;

typedef struct _MGREX_HITWORK
{
    SVECTOR *size;
    MATRIX   mat;
} MGREX_HITWORK;

typedef struct _MGREX_HITSCRATCH
{
    VECTOR        pos;
    MGREX_HITWORK boxes[11];
} MGREX_HITSCRATCH;

extern int      amissile_alive_8009F490;
extern SVECTOR  svector_8009F494;
extern int      dword_8009F49C;
extern int      GM_GameStatus;
extern CONTROL *GM_PlayerControl;
extern SVECTOR  GM_PlayerPosition;

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out);
int  s17a_800DE900(SVECTOR *a0, VECTOR *a1, SVECTOR *a2, int a3);

void s17a_800E3BA8(MGREX_WORK *work, int arg1);
void s17a_800E46F8(MGREX_WORK *work);
void s17a_800E4A58(MGREX_WORK *work, SVECTOR *pos);
int  s17a_800E4B0C(int from, int to, int step);

extern MGREX_HITBOX mgrex_hitbox_leg_l[2];
extern MGREX_HITBOX mgrex_hitbox_leg_r[2];
extern MGREX_HITBOX mgrex_hitbox_body[7];
extern SVECTOR mgrex_wall_body1[8];
extern SVECTOR mgrex_wall_body2[4];
extern SVECTOR mgrex_wall_body3[5];
extern SVECTOR mgrex_wall_body4[4];
extern SVECTOR mgrex_wall_leg_l1[4];
extern SVECTOR mgrex_wall_leg_l2[4];
extern SVECTOR mgrex_wall_leg_r1[4];
extern SVECTOR mgrex_wall_leg_r2[4];
extern SVECTOR mgrex_wall_foot_l[4];
extern SVECTOR mgrex_wall_foot_r[4];
extern SVECTOR mgrex_radar_rot1;
extern SVECTOR mgrex_radar_rot2;
extern SVECTOR mgrex_search_points[14];

/* Long line hazard check, split into 20000 unit steps */
int MGRexOnlineHazardCheck(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int chk_flag, int seg_flag)
{
    SVECTOR p0, p1, step;
    int     dx, dy, dz;
    int     len, n, i, dist;

    dx = (to->vx - from->vx) / 4;
    dy = (to->vy - from->vy) / 4;
    dz = (to->vz - from->vz) / 4;

    len = SquareRoot0(dx * dx + dy * dy + dz * dz) * 4;
    n = len / 20000 + 1;

    step.vx = dx / n;
    step.vy = dy / n;
    step.vz = dz / n;

    dist = 0;
    p0 = *from;
    p1 = *from;
    p1.vx += step.vx;
    p1.vy += step.vy;
    p1.vz += step.vz;

    for (i = 0; i < n; i++)
    {
        dist += 20000;
        if (len < dist)
        {
            p1 = *to;
        }

        if (HZD_OnlineHazardCheck(hzd, &p0, &p1, chk_flag, seg_flag))
        {
            return 1;
        }

        p0.vx += step.vx;
        p0.vy += step.vy;
        p0.vz += step.vz;
        p1.vx += step.vx;
        p1.vy += step.vy;
        p1.vz += step.vz;
    }

    return 0;
}

int s17a_800E3248(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int chk_flag, int seg_flag)
{
    if (GM_PlayerPosition.vx >= -16000 && GM_PlayerPosition.vx <= 16000 &&
        GM_PlayerPosition.vy >= 0 &&
        GM_PlayerPosition.vz >= -28000 && GM_PlayerPosition.vz <= 27000)
    {
        return 0;
    }

    return MGRexOnlineHazardCheck(hzd, from, to, chk_flag, seg_flag);
}

/* Nikita missile against REX hit boxes */
void s17a_800E32B4(MGREX_WORK *work)
{
    MGREX_HITSCRATCH *scratch;
    MGREX_HITWORK    *hit;
    MGREX_HITBOX     *box;
    DG_OBJS          *objs;
    MATRIX           *world;
    int               sx, sy, sz;
    int               i, n;

    scratch = (MGREX_HITSCRATCH *)getScratchAddr(0);
    dword_8009F49C = 0;
    if (!amissile_alive_8009F490)
    {
        return;
    }

    n = 0;

    hit = scratch->boxes;
    box = mgrex_hitbox_leg_l;
    objs = work->leg_l.objs;
    for (i = 0; i < 2; i++, hit++, box++)
    {
        world = &objs->objs[box->joint].world;
        RotMatrix_gte(&box->rot, &hit->mat);
        hit->mat.t[0] = hit->mat.t[1] = hit->mat.t[2] = 0;
        CompMatrix(world, &hit->mat, &hit->mat);
        DG_SetPos(&hit->mat);
        DG_MovePos(&box->pos);
        ReadRotMatrix(&hit->mat);
        hit->size = &box->size;
        n++;
    }

    box = mgrex_hitbox_leg_r;
    objs = work->leg_r.objs;
    for (i = 0; i < 2; i++, hit++, box++)
    {
        world = &objs->objs[box->joint].world;
        RotMatrix_gte(&box->rot, &hit->mat);
        hit->mat.t[0] = hit->mat.t[1] = hit->mat.t[2] = 0;
        CompMatrix(world, &hit->mat, &hit->mat);
        DG_SetPos(&hit->mat);
        DG_MovePos(&box->pos);
        ReadRotMatrix(&hit->mat);
        hit->size = &box->size;
        n++;
    }

    box = mgrex_hitbox_body;
    objs = work->body.objs;
    for (i = 0; i < 7; i++, hit++, box++)
    {
        world = &objs->objs[box->joint].world;
        RotMatrix_gte(&box->rot, &hit->mat);
        hit->mat.t[0] = hit->mat.t[1] = hit->mat.t[2] = 0;
        CompMatrix(world, &hit->mat, &hit->mat);
        DG_SetPos(&hit->mat);
        DG_MovePos(&box->pos);
        ReadRotMatrix(&hit->mat);
        hit->size = &box->size;
        n++;
    }

    hit = scratch->boxes;
    for (i = n; i > 0; hit++, i--)
    {
        DG_TransposeMatrix(&hit->mat, &hit->mat);
        scratch->pos.vx = svector_8009F494.vx - hit->mat.t[0];
        scratch->pos.vy = svector_8009F494.vy - hit->mat.t[1];
        scratch->pos.vz = svector_8009F494.vz - hit->mat.t[2];
        ApplyMatrixLV(&hit->mat, &scratch->pos, &scratch->pos);

        sx = hit->size->vx;
        sy = hit->size->vy;
        sz = hit->size->vz;
        if (scratch->pos.vx < sx && -sx < scratch->pos.vx &&
            scratch->pos.vy < sy && -sy < scratch->pos.vy &&
            scratch->pos.vz < sz && -sz < scratch->pos.vz)
        {
            dword_8009F49C = 1;
            if (GM_GameLevel > 0)
            {
                s17a_800E3BA8(work, 2);
                work->player_pos = GM_PlayerControl->mov;
            }
        }
    }
}

void s17a_800E3678(HZD_SEG *seg, SVECTOR *buf, SVECTOR *src, int n)
{
    int      i;
    SVECTOR *dst;

    dst = buf;
    for (i = n; i > 0; i--)
    {
        *dst++ = *src++;
    }

    DG_PutVector(buf, buf, n);

    dst = buf;
    src = buf + 1;
    for (i = n; i > 0; i--)
    {
        if (i == 1)
        {
            src = buf;
        }

        seg->p1.x = dst->vx;
        seg->p1.z = dst->vz;
        seg->p1.y = dst->pad;
        seg->p1.h = 2000;
        seg->p2.x = src->vx;
        seg->p2.z = src->vz;
        seg->p2.y = src->pad;
        seg->p2.h = 2000;

        dst++;
        src++;
        seg++;
    }
}

void s17a_800E377C(HZD_SEG *segs, HZD_SEG *dst, int n)
{
    for (; n > 0; n--)
    {
        HZD_SetDynamicSegment(segs, dst);
        segs++;
        dst++;
    }
}

void s17a_800E37D4(MGREX_WORK *work, HZD_SEG *segs)
{
    DG_SetPos(&work->body.objs->objs[2].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_body1, 8);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 8);
    segs += 8;

    DG_SetPos(&work->body.objs->objs[4].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_body2, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->body.objs->objs[6].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_body3, 5);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 5);
    segs += 5;

    DG_SetPos(&work->body.objs->objs[8].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_body4, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->leg_l.objs->objs[1].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_leg_l1, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->leg_l.objs->objs[7].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_leg_l2, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->leg_r.objs->objs[1].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_leg_r1, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->leg_r.objs->objs[7].world);
    s17a_800E3678((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_leg_r2, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
}

void s17a_800E39FC(HZD_SEG *seg, SVECTOR *buf, SVECTOR *src, int n)
{
    int      i;
    SVECTOR *dst;

    dst = buf;
    for (i = n; i > 0; i--)
    {
        *dst++ = *src++;
    }

    DG_PutVector(buf, buf, n);

    dst = buf;
    src = buf + 1;
    for (i = n; i > 0; i--)
    {
        if (i == 1)
        {
            src = buf;
        }

        seg->p1.x = dst->vx;
        seg->p1.z = dst->vz;
        seg->p1.y = dst->vy;
        seg->p1.h = 3000;
        seg->p2.x = src->vx;
        seg->p2.z = src->vz;
        seg->p2.y = src->vy;
        seg->p2.h = 3000;

        dst++;
        src++;
        seg++;
    }
}

void s17a_800E3B00(MGREX_WORK *work, HZD_SEG *segs)
{
    DG_SetPos(&work->leg_l.objs->objs[8].world);
    s17a_800E39FC((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_foot_l, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
    segs += 4;

    DG_SetPos(&work->leg_r.objs->objs[8].world);
    s17a_800E39FC((HZD_SEG *)getScratchAddr(0x10), (SVECTOR *)getScratchAddr(0), mgrex_wall_foot_r, 4);
    s17a_800E377C((HZD_SEG *)getScratchAddr(0x10), segs, 4);
}

void s17a_800E3BA8(MGREX_WORK *work, int arg1)
{
    SVECTOR pos;
    int     se;

    if (arg1 == 2 && work->f1980 != arg1 && work->mode >= 3)
    {
        if (GV_RandU(2))
        {
            se = 0x80;
        }
        else
        {
            se = 0x81;
        }

        pos.vx = work->pit_liq.objs->objs[1].world.t[0];
        pos.vy = work->pit_liq.objs->objs[1].world.t[1];
        pos.vz = work->pit_liq.objs->objs[1].world.t[2];
        GM_SeSetMode(&pos, se, 1);
    }

    work->f1980 = arg1;
    work->f1984 = 255;

    if (work->f1988 != 0 && work->f1980 == 2)
    {
        work->f1980 = 1;
        work->f1984 = 255;
    }
}

/* Radar search */
void s17a_800E3C7C(MGREX_WORK *work)
{
    MATRIX   rot;
    SVECTOR  pos;
    SVECTOR  radar;
    VECTOR   sq;
    VECTOR   v;
    SVECTOR  pt;
    VECTOR   d;
    VECTOR   sq2;
    MATRIX  *parent;
    MATRIX  *world;
    CONTROL *control;
    int      found;
    int      x, y, z;
    int      len;
    int      px, py, pz;
    int      cx, cy, cz;
    int      dx, dy, dz;
    int      yaw, pitch, dist, dir;
    int      ang, target;

    found = 0;

    if (work->f1988)
    {
        work->f1988--;
        work->f1980 = 1;
        work->f1984 = 255;
    }

    parent = &work->radar_parent->world;
    pos.vx = rot.t[0] = parent->t[0];
    pos.vy = rot.t[1] = parent->t[1];
    pos.vz = rot.t[2] = parent->t[2];

    if (work->mode < 3)
    {
        RotMatrix_gte(&mgrex_radar_rot1, &rot);
        if (GM_GameStatus & 1)
        {
            work->f1988 = 1;
        }
    }
    else
    {
        RotMatrix_gte(&mgrex_radar_rot2, &rot);
        if (GM_GameStatus & 2)
        {
            work->f1988 = 90;
        }
    }

    MulMatrix2(parent, &rot);

    x = rot.m[0][2];
    z = rot.m[2][2];
    y = rot.m[1][2];
    radar.vy = ratan2(x, z);
    radar.vx = ratan2(-y, SquareRoot0(x * x + z * z));
    radar.pad = 30000;

    if (work->f1988 == 0)
    {
        s01a_800E2364(&rot, &GM_PlayerControl->mov, &v);
        v.vx >>= 2;
        v.vy >>= 2;
        v.vz >>= 2;
        Square0(&v, &sq);

        yaw = ratan2(v.vx, v.vz) & 0xFFF;
        pitch = ratan2(-v.vy, SquareRoot0(sq.vx + sq.vz)) & 0xFFF;
        len = SquareRoot0(sq.vx + sq.vy + sq.vz) * 4;

        if (yaw >= 2048)
        {
            yaw -= 4096;
        }

        if (pitch >= 2048)
        {
            pitch -= 4096;
        }

        work->f1A5C = 0;

        if (abs(yaw) < work->f5B0 / 2 && abs(pitch) < work->f5B4 / 2 && len < 30000)
        {
            if (!MGRexOnlineHazardCheck(work->control.map->hzd, &pos, &GM_PlayerControl->mov, 15, 2))
            {
                work->player_pos = GM_PlayerControl->mov;
                s17a_800E3BA8(work, 2);
                found = 1;
            }
            else if (work->mode < 3)
            {
                HZD_GetOnlinePoint(&pt);

                px = (GM_PlayerControl->mov.vx - pt.vx) >> 2;
                py = (GM_PlayerControl->mov.vy - pt.vy) >> 2;
                pz = (GM_PlayerControl->mov.vz - pt.vz) >> 2;

                if (px * px + py * py + pz * pz <= 0x22550)
                {
                    work->player_pos = GM_PlayerControl->mov;
                    s17a_800E3BA8(work, 2);
                    found = 1;
                    work->f1A5C = found;
                }
            }
        }

        control = &work->control2;
        GM_ConfigControlAttribute(control, 5);
        GM_ConfigControlRadarparam(control, radar.vy, radar.pad, work->f5B0, 0);
        work->control2.mov = pos;
        work->control2.mov.vy = GM_PlayerControl->mov.vy;
    }
    else
    {
        control = &work->control2;
        GM_ConfigControlAttribute(control, 1);
        GM_ConfigControlRadarparam(control, radar.vy, 1000, work->f5B0, 0);
        work->control2.mov = pos;
        work->control2.mov.vy = GM_PlayerControl->mov.vy;
    }

    world = &work->body.objs->objs[4].world;
    dir = work->f1A3C;
    d.vx = (work->player_pos.vx - world->t[0]) >> 2;
    d.vy = (work->player_pos.vy - world->t[1]) >> 2;
    d.vz = (work->player_pos.vz - world->t[2]) >> 2;
    Square0(&d, &sq2);

    dist = SquareRoot0(sq2.vx + sq2.vz) * 4;
    ang = ratan2(d.vx, d.vz) & 0xFFF;
    ang = (ang - dir) & 0xFFF;
    if (ang >= 2048)
    {
        ang -= 4096;
    }

    work->f1A38 = ang;
    work->f1A34 = dist;

    switch (work->f1980)
    {
    case 0:
        if (work->f1950 == 0)
        {
            if ((work->f1A4C & 0xFF) > 128)
            {
                target = work->f1A3C + 300;
            }
            else
            {
                target = work->f1A3C - 300;
            }

            work->f1A44.vy = GV_NearSpeed(work->f1A44.vy, target, 5);

            cx = (work->player_pos.vx - pos.vx) / 4;
            cy = (work->player_pos.vy - pos.vy) / 4;
            cz = (work->player_pos.vz - pos.vz) / 4;
            work->f1A44.vx = ratan2(-cy, SquareRoot0(cx * cx + cz * cz));
            work->f1A44.vz = 0;

            if (--work->f1A4C <= 0)
            {
                if (work->f1A50 == -1)
                {
                    s17a_800E4A58(work, &work->player_pos);
                }
                else
                {
                    work->f1A50 += work->f1A54;
                    if (work->f1A50 < 0)
                    {
                        work->f1A50 = 13;
                    }
                    else if (work->f1A50 >= 14)
                    {
                        work->f1A50 = 0;
                    }
                }

                work->player_pos = mgrex_search_points[work->f1A50];
                work->f1A4C = 256;
            }
        }
        else
        {
            work->f1A44.vy = work->f1A3C;
        }
        break;

    case 1:
        if (work->f1950 == 0)
        {
            if ((work->f1A4C & 0xFF) > 128)
            {
                target = work->f1A3C + 300;
            }
            else
            {
                target = work->f1A3C - 300;
            }

            work->f1A44.vy = GV_NearSpeed(work->f1A44.vy, target, 5);
            work->f1A44.vx = 300;

            if (--work->f1A4C <= 0)
            {
                work->f1A4C = 255;
            }
        }
        else
        {
            work->f1A44.vy = work->f1A3C;
        }

        if (--work->f1984 < 0)
        {
            work->f1980 = 0;
            work->f1984 = 0;
        }

        work->f1A50 = -1;
        break;

    case 2:
        dx = (work->player_pos.vx - pos.vx) / 4;
        dy = (work->player_pos.vy - pos.vy) / 4;
        dz = (work->player_pos.vz - pos.vz) / 4;

        yaw = ratan2(dx, dz);
        work->f1A44.vx = ratan2(-dy, SquareRoot0(dx * dx + dz * dz));
        work->f1A44.vy = yaw;
        work->f1A44.vz = 0;

        work->control2.radar_atr |= 0x1000;
        work->player_pos = GM_PlayerControl->mov;

        if (!found)
        {
            work->f1984--;
        }

        if (--work->f1984 < 0 && work->f6FC == 2)
        {
            s17a_800E3BA8(work, 1);
        }

        work->f1A50 = -1;
        break;

    default:
        break;
    }

    s17a_800E46F8(work);
}

void s17a_800E44C0(MGREX_WORK *work)
{
    MATRIX  mat;
    SVECTOR pos;
    SVECTOR ofs;
    VECTOR  out;
    int     dist;

    if (work->f794.pad == 0)
    {
        work->f1994.vx = s17a_800E4B0C(work->f1994.vx, work->f794.vx, 40);
        work->f1994.vy = s17a_800E4B0C(work->f1994.vy, work->f794.vy, 40);
        work->f1994.vz = s17a_800E4B0C(work->f1994.vz, work->f794.vz, 40);
    }
    else
    {
        work->f1994 = work->f794;
    }

    work->body_rots[9] = work->f1994;
    work->body_rots[9].vx -= 170;

    if (work->mode < 3)
    {
        work->body_rots[6] = work->f198C;
    }
    else
    {
        work->pit_liq.rots[1].vx = work->f198C.vx;
        work->pit_liq.rots[1].vy = work->f198C.vy;
    }

    work->body_adjust[2].vx = work->f199C.vx;
    work->body_adjust[2].vy = work->f199C.vy;

    if (work->mode != 0)
    {
        DG_SetPos(&work->body.objs->objs[7].world);
        ReadRotMatrix(&mat);

        pos.vx = mat.t[0];
        pos.vy = mat.t[1];
        pos.vz = mat.t[2];

        ofs = DG_ZeroVector;
        ofs.vx = -4788;
        ofs.vz = 13155;
        ApplyRotMatrix(&ofs, &out);

        out.vx += pos.vx;
        out.vy += pos.vy;
        out.vz += pos.vz;

        dist = s17a_800DE900(&pos, &out, &ofs, 14000);
        work->f19A4.vx = s17a_800E4B0C(work->f19A4.vx, -ratan2(SquareRoot0(0xA509849 - dist * dist), dist), 40);
        work->f19A4.vy = s17a_800E4B0C(work->f19A4.vy, -228, 5);
        work->f19A4.vz = 0;
    }
}

void s17a_800E46F8(MGREX_WORK *work)
{
    MATRIX mat;
    MATRIX rot;
    VECTOR v;
    VECTOR sq;
    MATRIX m2;
    int    x, y, z;
    int    yaw, pitch;

    RotMatrixZYX_gte(&work->f1A44, &rot);

    if (work->mode < 3)
    {
        mat = work->body.objs->objs[5].world;
    }
    else
    {
        mat = work->pit_liq.objs->objs[0].world;
    }

    DG_TransposeMatrix(&mat, &mat);
    MulMatrix2(&mat, &rot);

    x = rot.m[0][2];
    z = rot.m[2][2];
    y = rot.m[1][2];

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

    if (yaw < -300)
    {
        yaw = -300;
    }
    else if (yaw > 300)
    {
        yaw = 300;
    }

    if (pitch < -300)
    {
        pitch = -300;
    }
    else if (pitch > 300)
    {
        pitch = 300;
    }

    if (work->f198C.vy != yaw)
    {
        work->f1ACC |= 4;
    }

    work->f198C.vx = s17a_800E4B0C(work->f198C.vx, pitch, 30);
    work->f198C.vy = s17a_800E4B0C(work->f198C.vy, yaw, 30);
    work->f198C.vz = s17a_800E4B0C(work->f198C.vz, 0, 30);

    m2 = DG_ZeroMatrix;
    RotMatrixY(work->f1A3C, &m2);
    m2.t[0] = work->body.objs->objs[1].world.t[0];
    m2.t[1] = work->body.objs->objs[1].world.t[1];
    m2.t[2] = work->body.objs->objs[1].world.t[2];

    s01a_800E2364(&m2, &work->player_pos, &v);
    Square0(&v, &sq);

    yaw = ratan2(v.vx, v.vz) & 0xFFF;
    pitch = ratan2(-v.vy, SquareRoot0(sq.vx + sq.vz)) & 0xFFF;

    if (pitch > 2048)
    {
        pitch -= 4096;
    }

    if (yaw > 2048)
    {
        yaw -= 4096;
    }

    if (yaw < -300)
    {
        yaw = -300;
    }
    else if (yaw > 300)
    {
        yaw = 300;
    }

    if (pitch < 0)
    {
        pitch = 0;
    }
    else if (pitch > 150)
    {
        pitch = 150;
    }

    work->f199C.vx = s17a_800E4B0C(work->f199C.vx, pitch, 30);
    work->f199C.vy = s17a_800E4B0C(work->f199C.vy, yaw, 30);
}

void s17a_800E4A58(MGREX_WORK *work, SVECTOR *pos)
{
    SVECTOR *point;
    int      x, z;
    int      i, best, min, d, dx, dz;

    best = 0;
    min = 0x7FFFFFFF;
    point = mgrex_search_points;
    x = pos->vx;
    z = pos->vz;

    for (i = 0; i < 14; i++, point++)
    {
        dx = (x - point->vx) >> 2;
        dz = (z - point->vz) >> 2;
        d = dx * dx + dz * dz;
        if (d <= min)
        {
            min = d;
            best = i;
        }
    }

    work->f1A50 = best;

    work->f1A54 = (GV_RandU(2) & 1) ? 1 : -1;
}

int s17a_800E4B0C(int from, int to, int step)
{
    int next;
    int diff;

    diff = to - from;
    diff &= 0xFFF;
    if (diff >= 2048)
    {
        diff -= 4096;
    }

    to = from + diff;

    if (from < to)
    {
        next = from + step;
        if (next >= to)
        {
            return to;
        }
    }
    else
    {
        next = from - step;
        if (next <= to)
        {
            return to;
        }
    }

    return next;
}

/* Data */

MGREX_HITBOX mgrex_hitbox_leg_l[2] = {
    {{0, -550, 1900}, {1000, 1000, 3500}, {135, 0, 0}, 1},
    {{-63, -1700, 1900}, {1000, 1000, 3500}, {210, 0, 0}, 4}
};

MGREX_HITBOX mgrex_hitbox_leg_r[2] = {
    {{0, -550, 1900}, {1000, 1000, 3500}, {135, 0, 0}, 1},
    {{63, -1700, 1900}, {1000, 1000, 3500}, {210, 0, 0}, 4}
};

MGREX_HITBOX mgrex_hitbox_body[7] = {
    {{0, 6700, -700}, {1000, 1000, 3100}, {230, 0, 0}, 0},
    {{0, 750, -2300}, {3200, 1350, 2000}, {125, 0, 0}, 2},
    {{0, 1200, 1000}, {700, 500, 2000}, {125, 0, 0}, 2},
    {{0, -425, 1900}, {650, 550, 2400}, {150, 0, 0}, 3},
    {{0, 800, -1000}, {2500, 1000, 2500}, {0, 0, 0}, 4},
    {{640, 0, 900}, {1000, 1000, 2200}, {0, 0, 0}, 6},
    {{0, 0, 5400}, {1000, 1000, 7750}, {0, 0, 0}, 8}
};

SVECTOR mgrex_wall_body1[8] = {
    {-3500, 0, -3600, 3000},
    {-3500, 0, -600, 3000},
    {-1000, 0, 400, 3000},
    {-500, 0, 3900, 3000},
    {500, 0, 3900, 3000},
    {1000, 0, 400, 3000},
    {3500, 0, -600, 3000},
    {3200, 0, -3600, 3000}
};

SVECTOR mgrex_wall_body2[4] = {
    {-2000, 0, -3700, 3000},
    {-2000, 0, 2300, 3000},
    {2000, 0, 2300, 3000},
    {2000, 0, -3700, 3000}
};

SVECTOR mgrex_wall_body3[5] = {
    {-500, 0, -1000, 3000},
    {-500, 0, 3500, 3000},
    {2000, 0, 3500, 3000},
    {2500, 0, 2500, 3000},
    {1000, 0, -1000, 3000}
};

SVECTOR mgrex_wall_body4[4] = {
    {-850, 0, -3000, 3000},
    {-350, 0, 14000, 3000},
    {150, 0, 14000, 3000},
    {650, 0, -3000, 3000}
};

SVECTOR mgrex_wall_leg_l1[4] = {
    {-1050, 0, -1500, 3000},
    {-1050, -2000, 6000, 3000},
    {950, -2000, 6000, 3000},
    {950, 0, -1500, 3000}
};

SVECTOR mgrex_wall_leg_l2[4] = {
    {-1050, -2000, -3500, 1000},
    {-1050, -3000, 4000, 1000},
    {950, -3000, 4000, 1000},
    {950, -2000, -3500, 1000}
};

SVECTOR mgrex_wall_leg_r1[4] = {
    {1050, 1000, -1500, 3000},
    {1050, -2000, 6000, 3000},
    {-950, -2000, 6000, 3000},
    {-950, 1000, -1500, 3000}
};

SVECTOR mgrex_wall_leg_r2[4] = {
    {1050, -2000, -3500, 1000},
    {1050, -3000, 4000, 1000},
    {-950, -3000, 4000, 1000},
    {-950, -2000, -3500, 1000}
};

SVECTOR mgrex_wall_foot_l[4] = {
    {500, -200, 500},
    {-500, -200, 500},
    {-500, -200, -1500},
    {500, -200, -1500}
};

SVECTOR mgrex_wall_foot_r[4] = {
    {500, -200, 500},
    {-500, -200, 500},
    {-500, -200, -1500},
    {500, -200, -1500}
};

SVECTOR mgrex_radar_rot1 = {0, 0, 0, 0};
SVECTOR mgrex_radar_rot2 = {0, 0, 0, 0};

SVECTOR mgrex_search_points[14] = {
    {16500, 0, 27000},
    {16500, 0, 18000},
    {16500, 0, 7500},
    {16500, 0, -1500},
    {16500, 0, -12000},
    {16500, 0, -21000},
    {9000, 0, -27000},
    {-9000, 0, -27000},
    {-16500, 0, -21000},
    {-16500, 0, -12000},
    {-16500, 0, -1500},
    {-16500, 0, 7500},
    {-16500, 0, 18000},
    {-16500, 0, 27000}
};
