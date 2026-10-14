#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "okajima/bullet.h"
#include "../kojo/hind.h"

/* Aims the hind's gun (body joints 3 and 4) at its target and fires */
int s11g_blastoff_800DBF88(HindWork *work)
{
    MATRIX   mat;
    VECTOR   angle;
    VECTOR   angle2;
    SVECTOR  pos;
    SVECTOR  diff;
    SVECTOR  rot;
    SVECTOR  target;
    DG_MDL  *model;
    int      ret;
    int      len;
    int      damage;

    DG_SetPos(&work->body.objs->objs[0].world);

    pos.vx = work->body.objs->objs[3].model->tx;
    pos.vy = work->body.objs->objs[3].model->ty;
    pos.vz = work->body.objs->objs[3].model->tz;
    DG_MovePos(&pos);
    ReadRotMatrix(&mat);

    memset(&pos, 0, sizeof(SVECTOR));
    DG_PutVector(&pos, &pos, 1);

    diff.vx = (pos.vx - work->field_62C.vx) >> 2;
    diff.vy = (pos.vy - work->field_62C.vy) >> 2;
    diff.vz = (pos.vz - work->field_62C.vz) >> 2;
    angle.vy = ratan2(diff.vx, diff.vz);
    SquareRoot0(diff.vx * diff.vx + diff.vy * diff.vy + diff.vz * diff.vz);

    diff.vx = 0;
    diff.vy = 0;
    model = work->body.objs->objs[4].model;
    diff.vz = model->uz - model->lz;
    DG_MovePos(&diff);

    memset(&diff, 0, sizeof(SVECTOR));
    DG_PutVector(&diff, &diff, 1);

    diff.vx = pos.vx - diff.vx;
    diff.vz = pos.vz - diff.vz;
    diff.vy = pos.vy - diff.vy;
    angle2.vy = ratan2(diff.vx, diff.vz);

    rot.vx = 0;
    rot.vz = 0;
    rot.vy = angle.vy - angle2.vy;

    if (rot.vy < -2048)
    {
        rot.vy += 4096;
    }

    if (rot.vy > 2048)
    {
        rot.vy -= 4096;
    }

    DG_SetPos(&mat);
    DG_RotatePos(&rot);

    pos.vx = work->body.objs->objs[4].model->tx;
    pos.vy = work->body.objs->objs[4].model->ty;
    pos.vz = work->body.objs->objs[4].model->tz;
    DG_MovePos(&pos);

    memset(&pos, 0, sizeof(SVECTOR));
    DG_PutVector(&pos, &pos, 1);

    diff.vx = (pos.vx - work->field_62C.vx) >> 2;
    diff.vy = (pos.vy - work->field_62C.vy) >> 2;
    diff.vz = (pos.vz - work->field_62C.vz) >> 2;
    angle.vx = ratan2(diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));

    diff.vx = 0;
    diff.vy = 0;
    model = work->body.objs->objs[4].model;
    diff.vz = model->uz - model->lz;
    DG_MovePos(&diff);

    memset(&diff, 0, sizeof(SVECTOR));
    DG_PutVector(&diff, &diff, 1);

    diff.vx = pos.vx - diff.vx;
    diff.vy = pos.vy - diff.vy;
    diff.vz = pos.vz - diff.vz;
    angle2.vx = ratan2(diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));

    rot.vx = angle.vx - angle2.vx;

    if (ABS(rot.vx) > work->gun_max_pitch + work->gun_pitch_margin || ABS(rot.vy) > work->gun_max_yaw + work->gun_yaw_margin)
    {
        ret = 0;
        rot.vx = 0;
        rot.vy = 0;
    }
    else
    {
        ret = 1;
        rot.vx = MIN(rot.vx, work->gun_max_pitch);
        rot.vx = MAX(rot.vx, -work->gun_max_pitch);
        rot.vy = MIN(rot.vy, work->gun_max_yaw);
        rot.vy = MAX(rot.vy, -work->gun_max_yaw);
    }

    len = SquareRoot0(mat.m[0][0] * mat.m[0][0] + mat.m[1][0] * mat.m[1][0] + mat.m[2][0] * mat.m[2][0]);
    if (len == 0)
    {
        return 1;
    }

    angle.vz = angle.vy = angle.vx = 0x1000000 / len;
    ScaleMatrix(&mat, &angle);

    work->body.rots[3].vy = GV_NearExp2P(work->body.rots[3].vy, rot.vy);
    work->body.rots[4].vx = GV_NearExp2P(work->body.rots[4].vx, rot.vx);

    DG_SetPos(&mat);

    pos.vx = 0;
    pos.vy = work->body.rots[3].vy;
    pos.vz = 0;
    DG_RotatePos(&pos);

    pos.vx = work->body.objs->objs[4].model->tx;
    pos.vy = work->body.objs->objs[4].model->ty;
    pos.vz = work->body.objs->objs[4].model->tz;
    DG_MovePos(&pos);

    pos.vx = work->body.rots[4].vx;
    pos.vy = 0;
    pos.vz = 0;
    DG_RotatePos(&pos);

    pos.vx = 0;
    pos.vy = 0;
    model = work->body.objs->objs[4].model;
    pos.vz = model->uz - model->lz;
    DG_MovePos(&pos);
    ReadRotMatrix(&mat);

    if (work->field_930 == 0 && (work->mode == 2 || work->mode == 3))
    {
        if (work->field_5D4 == 1 && (GV_Time % work->gun_interval) == 0)
        {
            if (work->mode == 2)
            {
                if (--work->field_954 < 0)
                {
                    work->field_954 = GV_RandU(8) + 4;
                    work->field_958 = 1 - work->field_958;
                }

                if (work->field_958 != 0)
                {
                    return 1;
                }
            }

            work->gun_timer = work->gun_interval;

            target.vx = GM_PlayerPosition.vx + (work->field_63C.vx - GM_PlayerPosition.vx) / 4;
            target.vy = GM_PlayerPosition.vy + (work->field_63C.vy - GM_PlayerPosition.vy) / 4;
            target.vz = GM_PlayerPosition.vz + (work->field_63C.vz - GM_PlayerPosition.vz) / 4;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_VERYEASY:
            case GM_LEVEL_EASY:
                damage = 90;
                break;
            case GM_LEVEL_NORMAL:
            case GM_LEVEL_HARD:
                damage = 135;
                break;
            case GM_LEVEL_EXTREME:
                damage = 180;
                break;
            }

            NewBulletEx(0x220, &mat, 2, 1, 0, work->gun_size, damage, work->gun_length, work->gun_speed);
            return ret;
        }

        return 2;
    }

    return ret;
}
