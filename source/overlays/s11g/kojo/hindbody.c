#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "kojo/demo.h"
#include "hind.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "mts/mts.h"
#include "okajima/spark.h"
#include "takabe/cinema.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern GM_CAMERA        GM_Camera;

void AN_Smoke_800CE164(SVECTOR *pos, SVECTOR *speed, int index, int script);

void s11g_hind_800D46B8(SVECTOR *pos, int se_id)
{
    GM_SeSetMode(pos, se_id, GM_SEMODE_BOMB);
}

void s11g_hind_800D46D8(HindWork *work, int index)
{
    if (work->field_94C != 1 && work->field_930 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->vox_ids[index], 0);
        }
    }
}

void s11g_hind_800D4744(HindWork *work)
{
    if (work->field_94C != 1 && work->field_930 == 0)
    {
        work->field_5F0 = 90;
        NewCinemaScreen(90, 0);

        work->field_A70 = work->body.objs->def->model[2].vertices;
        work->body.objs->def->model[2].vertices = work->field_970;

        work->last_item = GM_CurrentItemId;
        work->last_weapon = GM_CurrentWeaponId;

        if (GM_CurrentItemId == IT_Scope  ||
            GM_CurrentItemId == IT_Camera ||
            GM_CurrentItemId == IT_NVG    ||
            GM_CurrentItemId == IT_ThermG)
        {
            GM_CurrentItemId = IT_None;
        }

        if (GM_CurrentWeaponId == WP_Rifle ||
            GM_CurrentWeaponId == WP_Stinger)
        {
            GM_CurrentWeaponId = WP_None;
        }

        switch (work->field_8C4++ % 4)
        {
        case 0:
            s11g_hind_800D46D8(work, 0);
            break;
        case 1:
            s11g_hind_800D46D8(work, 1);
            break;
        case 2:
            s11g_hind_800D46D8(work, 2);
            break;
        case 3:
            s11g_hind_800D46D8(work, 3);
            break;
        }

        if (work->control.mov.vx <= 0)
        {
            work->field_5D8 = 1;
        }
        else
        {
            work->field_5D8 = -1;
        }
    }
}

void s11g_hind_800D48E8(HindWork *work)
{
    work->field_62C.vx = GM_PlayerPosition.vx + GV_RandS(2) * 500;
    work->field_62C.vy = GM_PlayerPosition.vy + GV_RandS(2) * 500;
    work->field_62C.vz = GM_PlayerPosition.vz + GV_RandS(2) * 500;
}

int s11g_hind_800D4990(HindWork *work)
{
    SVECTOR midpoint;

    midpoint.vx = (GM_PlayerPosition.vx + work->field_63C.vx) / 2;
    midpoint.vy = (GM_PlayerPosition.vy + work->field_63C.vy) / 2;
    midpoint.vz = (GM_PlayerPosition.vz + work->field_63C.vz) / 2;

    return HZD_LineCheck(work->control.map->hzd, &GM_PlayerPosition, &midpoint, ( HZD_CHECK_SEG | HZD_CHECK_FLR ), HZD_SEG_NO_PLAYER) != 0;
}

void s11g_hind_800D4A24(long *vec, long *pos, long *old, int len)
{
    int interp;

    interp = (*vec * (len - 1) + *pos) / len;
    *old = *vec - interp;
    *vec = interp;
}

void s11g_hind_800D4A80(VECTOR *vec, VECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void s11g_hind_800D4B68(SVECTOR *vec, SVECTOR *pos, int len)
{
    SVECTOR diff;
    int     interp;

    interp = len - 1;

    vec->vx &= 0xFFF;
    vec->vy &= 0xFFF;
    vec->vz &= 0xFFF;

    pos->vx &= 0xFFF;
    pos->vy &= 0xFFF;
    pos->vz &= 0xFFF;

    diff.vx = pos->vx - vec->vx;
    diff.vy = pos->vy - vec->vy;
    diff.vz = pos->vz - vec->vz;

    if (diff.vx >= 2048)
    {
        vec->vx += 4096;
    }

    if (diff.vy >= 2048)
    {
        vec->vy += 4096;
    }

    if (diff.vz >= 2048)
    {
        vec->vz += 4096;
    }

    if (diff.vx <= -2048)
    {
        pos->vx += 4096;
    }

    if (diff.vy <= -2048)
    {
        pos->vy += 4096;
    }

    if (diff.vz <= -2048)
    {
        pos->vz += 4096;
    }

    vec->vx = (vec->vx * interp + pos->vx) / len;
    vec->vy = (vec->vy * interp + pos->vy) / len;
    vec->vz = (vec->vz * interp + pos->vz) / len;
}

void s11g_hind_800D4DD0(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        /* fallthrough */
    case 1:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_5C8 = 2;
            work->field_5E4 = GV_RandU(16) + 60;
            work->field_60C = work->field_4BC;
            work->field_60C.vy = 20000;
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 64);
        }
        else
        {
            work->field_8CC = 1;
            work->field_5C8 = 3;
            work->field_5E4 = GV_RandU(32) + 90;
            work->field_5E8 = GV_RandU(2);

            if (work->field_60C.vx < 0)
            {
                work->field_60C.vx = GV_RandU(16384) + 55000;
                work->field_60C.vy = GV_RandU(4096) + 20000;
                work->field_60C.vz = 8000 - GV_RandU(4096);
            }
            else
            {
                work->field_60C.vx = -(GV_RandU(16384) + 55000);
                work->field_60C.vy = 20000;
                work->field_60C.vz = 12000 - GV_RandU(4096);
            }

            work->field_61C = work->field_60C;
        }
        break;
    case 3:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            if (work->field_5E8 < 0)
            {
                work->field_5C8 = 4;
                work->field_5E4 = GV_RandU(128) + 128;

                if (work->field_60C.vx < 0)
                {
                    work->field_60C.vx = -20000;
                }

                if (work->field_60C.vx > 0)
                {
                    work->field_60C.vx = 20000;
                }

                work->field_60C.vy = 7000;
                work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(4096);
                if (work->field_60C.vz > 12000)
                {
                    work->field_60C.vz = 12000 - GV_RandS(4096);
                }
            }
            else
            {
                work->field_5C8 = 3;
                work->field_5E4 = GV_RandU(16) + 10;
                work->field_60C.vx = work->field_61C.vx + GV_RandS(8192);
                work->field_60C.vy = work->field_61C.vy + GV_RandS(8192);
                work->field_60C.vz = work->field_61C.vz + GV_RandS(8192);
            }

            work->field_5E8--;
        }
        break;
    case 4:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

void s11g_hind_800D50F0(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        /* fallthrough */
    case 1:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_5C8 = 2;
            work->field_5E4 = GV_RandU(16) + 60;
            work->field_60C = work->field_4BC;
            work->field_60C.vy = 20000;
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 64);
        }
        else
        {
            work->field_5C8 = 3;
            work->field_5E4 = GV_RandU(32) + 150;
            work->field_5E8 = (GV_RandU(4) * 2) + 8;
            work->field_60C.vx = GV_RandS(4096) + 2000;
            work->field_60C.vy = GV_RandU(1024) + 9000;
            work->field_60C.vz = GV_RandS(2048) - 15000;
        }
        break;
    case 3:
        if ((work->field_5D4 == 1) && (GM_PlayerStatus & PLAYER_INVINCIBLE))
        {
            work->field_5D4 = 0;
            work->field_5C4 = 0;
            work->field_5C8 = 0;
            s11g_hind_800D4744(work);
        }
        else if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            switch (work->field_8C0++ % 4)
            {
            case 0:
                s11g_hind_800D46D8(work, 4);
                break;
            case 1:
                s11g_hind_800D46D8(work, 5);
                break;
            case 2:
                s11g_hind_800D46D8(work, 6);
                break;
            case 3:
                s11g_hind_800D46D8(work, 7);
                break;
            }

            if (GV_RandU(4) != 0)
            {
                if (!(work->field_5E8 & 1) && (work->field_5EC < 0))
                {
                    s11g_hind_800D48E8(work);
                    work->field_5D4 = 1;
                }
                else
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(8) + 8;
                }

                work->field_5C8 = 3;
                work->field_5E4 = GV_RandU(32) + 150;
                work->field_60C.vx = GV_RandS(4096) + 2000;
                work->field_60C.vy = GV_RandU(4096) + 12000;
                work->field_60C.vz = GV_RandS(2048) - 2000;
            }
            else
            {
                work->field_5D4 = 0;
                work->field_954 = GV_RandU(8) + 8;
                work->field_5C4 = 0;
                work->field_5C8 = 0;
            }

            work->field_5E8--;
        }
        break;
    }
}

void s11g_hind_800D5420(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 1;
        work->field_5E4 = 8;
        work->field_60C = work->field_4BC;
        work->field_61C = work->field_4BC;
        work->field_5E8 = GV_RandU(4) + 4;
        s11g_hind_800D48E8(work);
        /* fallthrough */
    case 1:
        if ((work->field_5D4 == 1) && (GM_PlayerStatus & PLAYER_DAMAGED) && (work->field_5EC < 0))
        {
            work->field_5D4 = 0;
            work->field_954 = GV_RandU(2) + 4;
            work->field_5E4 = -1;
            work->field_5E8 = -1;
            work->field_5EC = 60;
            s11g_hind_800D4744(work);
        }

        if (work->field_5E4 <= 0)
        {
            work->field_61C.vy += 1500;
            if (work->field_61C.vy > 8000)
            {
                work->field_61C.vy = GV_RandS(4096) + 5000;
            }

            if ((work->field_5E8 < 0) || s11g_hind_800D4990(work))
            {
                if (GV_RandU(2) == 0)
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(4) + 4;

                    if (GV_RandU(8) == 0)
                    {
                        switch (GV_RandU(8))
                        {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                            s11g_hind_800D46D8(work, 11);
                            break;
                        case 6:
                            s11g_hind_800D46D8(work, 12);
                            break;
                        case 7:
                            s11g_hind_800D46D8(work, 16);
                            break;
                        }
                    }

                    if (GV_RandU(8))
                    {
                        work->field_5C4 = 0;
                        work->field_5C8 = 0;
                    }
                    else
                    {
                        work->field_5C4 = 1;
                        work->field_5C8 = 0;
                    }
                }
                else
                {
                    switch (GV_RandU(4))
                    {
                    case 0:
                        s11g_hind_800D46D8(work, 10);
                        break;
                    case 1:
                        s11g_hind_800D46D8(work, 9);
                        break;
                    }

                    work->field_5C8 = 2;
                    work->field_5E4 = GV_RandU(32) + 60;
                    work->field_60C.vx = work->field_61C.vx;
                    work->field_60C.vy = work->field_61C.vy + GV_RandU(4096);
                    work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
                    if (work->field_60C.vz > 12000)
                    {
                        work->field_60C.vz = 12000 - GV_RandS(4096);
                    }
                }
            }
            else
            {
                if (!(work->field_5E8 & 0x1) && (work->field_5EC < 0))
                {
                    s11g_hind_800D48E8(work);
                    work->field_5D4 = 1;
                }
                else
                {
                    work->field_5D4 = 0;
                    work->field_954 = GV_RandU(4) + 4;
                }

                work->field_5C8 = 1;
                work->field_5E4 = GV_RandU(32) + 60;
                work->field_60C.vx = work->field_61C.vx;
                work->field_60C.vy = work->field_61C.vy + GV_RandS(2048);
                work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
                if (work->field_60C.vz > 12000)
                {
                    work->field_60C.vz = 12000 - GV_RandS(4096);
                }
            }

            work->field_5E8--;
        }
        else
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
        }
        break;
    case 2:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D4A80(&work->field_5FC, &work->field_60C, 128);
            return;
        }
        else
        {
            work->field_5C8 = 1;
            work->field_5E4 = GV_RandU(32) + 60;
            work->field_5E8 = GV_RandU(2) + 2;
            work->field_60C.vx = work->field_61C.vx;
            work->field_60C.vy = work->field_61C.vy - GV_RandU(8192);
            work->field_60C.vz = GM_PlayerPosition.vz + GV_RandS(8192);
            if (work->field_60C.vz > 12000)
            {
                work->field_60C.vz = 12000 - GV_RandS(4096);
            }
        }
        break;
    }
}

void s11g_hind_800D5820(HindWork *work)
{
    SVECTOR rot;
    SVECTOR sp18;
    SVECTOR turn;
    SVECTOR pos;
    int     dx, dz;
    long    sp30;
    long    sp34;
    int     time;

    if (work->field_938 == 1)
    {
        s11g_hind_800D46D8(work, 8);
        GV_DestroyActor(&work->actor);
    }

    work->field_62C.vx = GM_PlayerPosition.vx;
    work->field_62C.vy = GM_PlayerPosition.vy;
    work->field_62C.vz = GM_PlayerPosition.vz;

    work->field_5E0++;
    work->field_5E4--;
    work->field_5EC--;

    work->field_8BC = GM_StreamStatus();

    switch (work->field_5C4)
    {
    case 0:
        s11g_hind_800D4DD0(work);
        break;
    case 1:
        s11g_hind_800D50F0(work);
        break;
    case 2:
        s11g_hind_800D5420(work);
        break;
    }

    time = work->field_5E0;
    work->field_5FC.vy += (rsin(time * 64) - rsin((time - 1) * 64)) / 2;
    work->field_5FC.vx += rsin(time * 23) - rsin((time - 1) * 23);
    work->field_5FC.vz += rsin(time * 32) - rsin((time - 1) * 32);

    if (GM_GameStatus & STATE_BEHIND_CAMERA)
    {
        pos.vx = (gUnkCameraStruct2_800B7868.eye.vx * 7 + work->field_4BC.vx) / 8;
        pos.vy = gUnkCameraStruct2_800B7868.eye.vy;
        pos.vz = (gUnkCameraStruct2_800B7868.eye.vz * 7 + work->field_4BC.vz) / 8;
    }
    else
    {
        pos.vx = (GM_PlayerPosition.vx * 7 + work->field_4BC.vx) / 8;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = (GM_PlayerPosition.vz * 7 + work->field_4BC.vz) / 8;
    }

    s11g_hind_800D4A24(&work->field_4BC.vx, &work->field_5FC.vx, &sp30, 40);
    turn.vx = sp30;

    s11g_hind_800D4A24(&work->field_4BC.vy, &work->field_5FC.vy, &sp34, 26);
    turn.vy = 0;

    s11g_hind_800D4A24(&work->field_4BC.vz, &work->field_5FC.vz, &sp30, 40);
    turn.vz = -sp30;

    dx = (GM_PlayerPosition.vx - work->field_4BC.vx) >> 1;
    dz = (GM_PlayerPosition.vz - work->field_4BC.vz) >> 1;

    sp18.vy = ratan2(dx, dz) & 0xFFF;
    sp18.vx = 0;
    sp18.vz = 0;

    s11g_hind_800D4B68(&work->control.turn, &sp18, 128);

    rot.vx = 0;
    rot.vy = work->control.rot.vy;
    rot.vz = 0;

    DG_SetPos2(&DG_ZeroVector, &rot);
    DG_PutVector(&turn, &turn, 1);

    work->control.turn.vx = turn.vz;
    work->control.turn.vz = turn.vx;

    work->body.rots[1].vy -= work->field_4B4;
    if (work->body.rots[1].vy < 0)
    {
        work->body.rots[1].vy += 4096;
    }

    work->body.rots[2].vx -= work->field_4B8;
    if (work->body.rots[2].vx < 0)
    {
        work->body.rots[2].vx += 4096;
    }

    if ((mts_get_tick_count() - work->last_time) >= 8)
    {
        work->last_time = mts_get_tick_count();

        if (work->field_930 == 0)
        {
            if (work->field_5F0 > 0)
            {
                GM_SeSet2(0, 63, 181);
            }
            else
            {
                switch (work->field_8CC)
                {
                case 0:
                    s11g_hind_800D46B8(&pos, 181);
                    break;
                case 1:
                    work->field_8CC = 2;
                    GM_SeSet2(0, 127, 0xB3);
                    s11g_hind_800D46B8(&pos, 181);
                    break;
                case 2:
                    work->field_8CC = 3;
                    s11g_hind_800D46B8(&pos, 182);
                    break;
                case 3:
                    work->field_8CC = 4;
                    s11g_hind_800D46B8(&pos, 183);
                    break;
                case 4:
                    work->field_8CC = 0;
                    s11g_hind_800D46B8(&pos, 184);
                    break;
                }
            }
        }
        else
        {
            GM_SeSet2(0, 8, 181);
        }
    }

    if (work->field_958 == 0 && (mts_get_tick_count() - work->last_time2) >= 4)
    {
        work->last_time2 =  mts_get_tick_count();

        if (work->field_930 == 0 && work->field_5D4 == 1)
        {
            s11g_hind_800D46B8(&pos, 177);
        }
    }
}

int s11g_hind_800D5CD8(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    int dx, dy, dz;
    int len;
    int height;

    dx = (from->vx - to->vx) / 16;
    dy = (from->vy - to->vy) / 16;
    dz = (from->vz - to->vz) / 16;

    len = SquareRoot0(dx * dx + dy * dy + dz * dz) * 16;
    height = to->vy - from->vy;

    out->vy = ratan2(to->vx - from->vx, to->vz - from->vz) & 0xFFF;
    out->vx = ratan2(len, height) & 0xFFF;
    out->vz = 0;

    return len;
}

void s11g_hind_800D5DE4(SVECTOR *out, int *yaw)
{
    MATRIX *eye;

    eye = &DG_Chanl(0)->eye;
    out->vx = eye->t[0];
    out->vy = eye->t[1];
    out->vz = eye->t[2];
    *yaw = ratan2(eye->m[0][2], eye->m[2][2]);
}

void s11g_hind_800D5E44(HindWork *work, int a1)
{
    work->field_95C = 30;
    work->field_960 = a1;
}

void s11g_hind_800D5E54(int arg0, SVECTOR *arg1, int se_id)
{
    SVECTOR sp10;
    SVECTOR pos;
    int     yaw;
    short   ang;
    int     vol;
    int     pan;

    if (!(GM_GameStatus & (GAME_FLAG_BIT_07 | STATE_BEHIND_CAMERA)) && !GM_Camera.first_person)
    {
        s11g_hind_800D5CD8(&GM_PlayerPosition, arg1, &sp10);
        ang = sp10.vy + 1024;
        sp10.vy = ang - gUnkCameraStruct2_800B7868.rotate.vy;
    }
    else
    {
        s11g_hind_800D5DE4(&pos, &yaw);
        s11g_hind_800D5CD8(&pos, arg1, &sp10);
        ang = sp10.vy + 1024;
        sp10.vy = ang - yaw;
    }

    sp10.vy &= 0xFFF;

    pan = (rcos(sp10.vy) * 31) / 4096;
    if (pan < 0)
    {
        pan += 255;
    }

    vol = 63;
    if (arg0 > 4000)
    {
        vol = 63 - ((arg0 - 4000) * 63) / 8000;
    }

    if (vol < 20)
    {
        vol = 20;
    }

    GM_SeSet2(pan, vol, se_id);
}

void s11g_hind_800D60D8(int arg0, SVECTOR *arg1, int se_id)
{
    s11g_hind_800D5E54(arg0, arg1, se_id);
}

void s11g_hind_800D5FB4(HindWork *work, int a1)
{
    MATRIX  matrix;
    SVECTOR rotation;
    VECTOR  scale;

    if (a1 == 0)
    {
        rotation.vx = GV_RandS(512) + 1024;
        rotation.vy = GV_RandS(512);
        rotation.vz = GV_RandS(512);

        scale.vx = work->field_670 * 7;
        scale.vy = work->field_670 * 7;
        scale.vz = work->field_670 * 7;
    }
    else
    {
        rotation.vx = 1024;
        rotation.vy = 0;
        rotation.vz = 0;

        scale.vx = work->field_670 * 4;
        scale.vy = work->field_670 * 4;
        scale.vz = work->field_670 * 4;
    }

    rotation.vx += work->field_788.vx;
    rotation.vy += work->field_788.vy;
    rotation.vz += work->field_788.vz;

    RotMatrixYXZ(&rotation, &matrix);

    matrix.t[0] = work->field_7D8.vx;
    matrix.t[1] = work->field_7D8.vy;
    matrix.t[2] = work->field_7D8.vz;

    ScaleMatrix(&matrix, &scale);
    NewSpark(&matrix, 0);

}

void s11g_hind_800D60F0(HindWork *work)
{
    int dx, dz;
    int len;
    int height;

    dx = (work->field_790.vx - work->field_760.vx) >> 1;
    dz = (work->field_790.vz - work->field_760.vz) >> 1;
    work->field_788.vy = ratan2(dx, dz) & 0xFFF;

    len = SquareRoot0(dz * dz + dx * dx);
    height = (work->field_790.vy - work->field_760.vy) >> 1;

    work->field_788.vx = (ratan2(len, height) - 1024) & 0xFFF;
    work->field_788.vz = 0;
}

void s11g_hind_800D619C(HindWork *work, int index)
{
    if (work->field_94C != 1)
    {
        if (GM_StreamStatus() == -1)
        {
            GM_VoxStream(work->vox_ids[index], 0);
        }
    }
}

void s11g_hind_800D61F8(HindWork *work)
{
    work->field_65C.vx = GV_RandS(128);
    work->field_65C.vy = GV_RandS(128);
    work->field_65C.vz = GV_RandS(128);

    work->field_664.vx = GV_RandS(512);
    work->field_664.vy = GV_RandS(512);
    work->field_664.vz = GV_RandS(512);
}

void s11g_hind_800D6260(int *vec, int *pos, int *old, int len)
{
    int interp;

    interp = (*vec * (len - 1) + *pos) / len;
    *old = *vec - interp;
    *vec = interp;
}

void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void Function_800D63A4(SVECTOR *vec, SVECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void s11g_hind_800D648C(SVECTOR *a, SVECTOR *b, int len)
{
    SVECTOR diff;
    int     scale;

    a->vx &= 0xFFF;
    a->vy &= 0xFFF;
    a->vz &= 0xFFF;

    b->vx &= 0xFFF;
    b->vy &= 0xFFF;
    b->vz &= 0xFFF;

    diff.vx = b->vx - a->vx;
    diff.vy = b->vy - a->vy;
    diff.vz = b->vz - a->vz;

    if (diff.vx >= 2048)
    {
        a->vx += 4096;
    }

    if (diff.vy >= 2048)
    {
        a->vy += 4096;
    }

    if (diff.vz >= 2048)
    {
        a->vz += 4096;
    }

    if (diff.vx <= -2048)
    {
        b->vx += 4096;
    }

    if (diff.vy <= -2048)
    {
        b->vy += 4096;
    }

    if (diff.vz <= -2048)
    {
        b->vz += 4096;
    }

    scale = len - 1;
    a->vy = (a->vy * scale + b->vy) / len;

    len = 8;
    scale = len - 1;
    a->vx = (a->vx * scale + b->vx) / len;
    a->vz = (a->vz * scale + b->vz) / len;
}

void s11g_hind_800D66F0(HindWork *work)
{
    SVECTOR pos;
    SVECTOR speed;

    pos.vx = (GV_RandS(2048) * work->field_66C) / 4096;
    pos.vy = (GV_RandS(2048) * work->field_66C) / 4096;
    pos.vz = (GV_RandS(4096) * work->field_66C) / 4096;

    DG_SetPos2(&DG_ZeroVector, &work->control.rot);
    DG_PutVector(&pos, &pos, 1);
    GV_AddVec3(&pos, &work->field_63C, &pos);

    speed = DG_ZeroVector;

    if (work->field_66C < 819)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 0);
    }
    else if (work->field_66C < 1024)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 1);
    }
    else if (work->field_66C < 1365)
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 2);
    }
    else
    {
        AN_Smoke_800CE164(&pos, &speed, 1, 3);
    }
}

const int s11g_dword_800DD190 = 0x800D68E0;
const int s11g_dword_800DD194 = 0x800D68F0;
const int s11g_dword_800DD198 = 0x800D69E4;
const int s11g_dword_800DD19C = 0x800D7628;
const int s11g_dword_800DD1A0 = 0x800D7628;
const int s11g_dword_800DD1A4 = 0x800D7020;
const int s11g_dword_800DD1A8 = 0x800D70A8;
const int s11g_dword_800DD1AC = 0x800D724C;
const int s11g_dword_800DD1B0 = 0x800D743C;
const int s11g_dword_800DD1B4 = 0x800D7628;
const int s11g_dword_800DD1B8 = 0x800D7628;
const int s11g_dword_800DD1BC = 0x800D7628;
const int s11g_dword_800DD1C0 = 0x800D7628;
const int s11g_dword_800DD1C4 = 0x800D7628;
const int s11g_dword_800DD1C8 = 0x800D7628;
const int s11g_dword_800DD1CC = 0x800D7628;
const int s11g_dword_800DD1D0 = 0x800D7628;
const int s11g_dword_800DD1D4 = 0x800D6A54;
const int s11g_dword_800DD1D8 = 0x800D6BE0;
const int s11g_dword_800DD1DC = 0x800D7628;
const int s11g_dword_800DD1E0 = 0x800D7628;
const int s11g_dword_800DD1E4 = 0x800D6D40;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D6848.s")

const int s11g_dword_800DD1E8 = 0x800D7700;
const int s11g_dword_800DD1EC = 0x800D776C;
const int s11g_dword_800DD1F0 = 0x800D7868;
const int s11g_dword_800DD1F4 = 0x800D9260;
const int s11g_dword_800DD1F8 = 0x800D9260;
const int s11g_dword_800DD1FC = 0x800D7FB4;
const int s11g_dword_800DD200 = 0x800D80D8;
const int s11g_dword_800DD204 = 0x800D827C;
const int s11g_dword_800DD208 = 0x800D8458;
const int s11g_dword_800DD20C = 0x800D8D58;
const int s11g_dword_800DD210 = 0x800D90B4;
const int s11g_dword_800DD214 = 0x800D9260;
const int s11g_dword_800DD218 = 0x800D9260;
const int s11g_dword_800DD21C = 0x800D9260;
const int s11g_dword_800DD220 = 0x800D9260;
const int s11g_dword_800DD224 = 0x800D9260;
const int s11g_dword_800DD228 = 0x800D9260;
const int s11g_dword_800DD22C = 0x800D78D8;
const int s11g_dword_800DD230 = 0x800D7A68;
const int s11g_dword_800DD234 = 0x800D9260;
const int s11g_dword_800DD238 = 0x800D9260;
const int s11g_dword_800DD23C = 0x800D7C3C;
const int s11g_dword_800DD240 = 0x800D96F0;
const int s11g_dword_800DD244 = 0x800D9B70;
const int s11g_dword_800DD248 = 0x800D9B70;
const int s11g_dword_800DD24C = 0x800D9B70;
const int s11g_dword_800DD250 = 0x800D974C;
const int s11g_dword_800DD254 = 0x800D9858;
const int s11g_dword_800DD258 = 0x800D9A74;
const int s11g_dword_800DD25C = 0x800D9B40;
const int s11g_dword_800DD260 = 0x800D9BC4;
const int s11g_dword_800DD264 = 0x800DA520;
const int s11g_dword_800DD268 = 0x800DA520;
const int s11g_dword_800DD26C = 0x800DA520;
const int s11g_dword_800DD270 = 0x800D9C08;
const int s11g_dword_800DD274 = 0x800D9D74;
const int s11g_dword_800DD278 = 0x800D9FD8;
const int s11g_dword_800DD27C = 0x800DA0E0;
const int s11g_dword_800DD280 = 0x800DA2B4;
const int s11g_dword_800DD284 = 0x00000000;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D7644.s")
