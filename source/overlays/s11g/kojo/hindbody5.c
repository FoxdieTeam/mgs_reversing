#include "mgstype.h"
#include "game/game.h"
#include "hind.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "bullet/blast.h"
#include "okajima/blurpure.h"
#include "takabe/cinema.h"
#include "takabe/fadeio.h"
#include "takabe/spark2.h"

void s11g_hind_800D5E44(HindWork *work, int a1);
void s11g_hind_800D5E54(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D619C(HindWork *work, int index);
void s11g_hind_800D61F8(HindWork *work);
void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len);
void s11g_hind_800D60D8(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D6260(long *vec, long *pos, long *old, int len);
void s11g_hind_800D648C(SVECTOR *a, SVECTOR *b, int len);
void s11g_hind_800D5FB4(HindWork *work, int a1);
void s11g_hind_800D60F0(HindWork *work);
void s11g_hind_800D66F0(HindWork *work);
int  s11g_hind_800D5CD8(SVECTOR *from, SVECTOR *to, SVECTOR *out);
void Function_800D63A4(SVECTOR *vec, SVECTOR *pos, int len);
void s11g_hind_800D6848(HindWork *work);
void s11g_hind_800D7644(HindWork *work);
void AN_Blast_Rand(SVECTOR *pos);
void *NewBlastoff(SVECTOR *arg0, int arg1, int arg2, int *arg3);

extern int amissile_alive_8009F490;
void s11g_hind_800D9344(HindWork *work);
void s11g_hind_800D96B0(HindWork *work);
void s11g_hind_800D9B80(HindWork *work);
void s11g_hind_800DA7C4(HindWork *work);

/*
 * The hind's movement code is one source file in the original (hindbody2.c +
 * hindbody5.c). s11g_hind_800DAAC8 is kept in its own file only because it
 * does not match yet; merge it back into hindbody2.c once it does.
 */

#if 0 /* NON_MATCHING: only the "range = dist / 8" shift is scheduled differently
         (2 instructions swapped). sched treats that sra as a register birth
         (REG_N_SETS == 1) and moves it next to the GV_RandU call; in the
         original the quotient register must be set more than once (it is
         s0, while its dist + 7 temporary is v0). Reusing range for another
         value fixes the schedule but then the temporary is allocated s0. */
void s11g_hind_800DAAC8(HindWork *work)
{
    SVECTOR  rot;
    SVECTOR  turn;
    SVECTOR  vec;
    SVECTOR  pos;
    SVECTOR  tmp;
    SVECTOR  tmp2;
    long     sp40;
    long     sp44;
    int      time;
    int      dist;
    int      delta;
    int      dx, dz;
    int      range;

    work->field_5D4 = 0;
    work->field_5F4 = (work->field_5F4 + 4096) & 0xFFF;

    work->field_62C.vx = GM_PlayerPosition.vx;
    work->field_62C.vy = GM_PlayerPosition.vy;
    work->field_62C.vz = GM_PlayerPosition.vz;

    work->field_5E0++;
    work->field_5E4--;
    work->field_5EC--;

    if (work->field_8FC > 0)
    {
        work->field_8FC--;
    }

    if (work->field_434 < work->field_430 / 3 && !(GV_Time & 3))
    {
        s11g_hind_800D66F0(work);
    }

    if (work->field_5C4 != 4 && work->field_658 == 0 && work->control.mov.vy > 9000)
    {
        if (work->field_8FC == 0)
        {
            work->field_8FC = -1;
            work->field_658 = 1;
            work->field_5C4 = 0;
            work->field_5C8 = 0;
        }
        else if (work->field_434 < (work->field_430 * 2) / 3 && work->field_8FC > 0)
        {
            s11g_hind_800D5E54(0, &work->field_964, 129);
            work->field_8FC = -1;
            work->field_658 = 1;
            work->field_5C4 = 0;
            work->field_5C8 = 0;
        }
    }

    switch (work->field_658)
    {
    case 0:
        if (work->field_5C4 != 4 && work->field_64C != 0)
        {
            work->field_5CC = work->field_5C4;
            work->field_5D0 = work->field_5C8;
            work->field_5C4 = 4;
            work->field_5C8 = 0;
        }

        switch (work->field_5C4)
        {
        case 0:
            s11g_hind_800DA7C4(work);
            break;
        case 1:
            s11g_hind_800D9B80(work);
            break;
        case 2:
            s11g_hind_800D96B0(work);
            break;
        case 4:
            s11g_hind_800D9344(work);
            break;
        }
        break;

    case 1:
        if (work->field_5C4 == 0)
        {
            s11g_hind_800D6848(work);
        }
        break;

    case 2:
        if (work->field_5C4 == 0)
        {
            s11g_hind_800D7644(work);
        }
        break;

    case 3:
        work->field_A74 = 1;
        GV_DestroyActor(&work->actor);
        break;
    }

    time = work->field_5E0;
    work->field_5FC.vx += rsin(time * 23) - rsin((time - 1) * 23);
    work->field_5FC.vz += rsin(time * 32) - rsin((time - 1) * 32);

    if (amissile_alive_8009F490 == 1)
    {
        work->field_93C = 1;
    }
    else if (work->field_658 == 0 && work->field_60C.vy > 0)
    {
        if (work->field_5FC.vy > 20000)
        {
            work->field_5FC.vy = 20000;
        }

        if (gUnkCameraStruct2_800B7868.position.vy < 10000)
        {
            if (work->field_93C == 0)
            {
                work->field_93C = 1;
                work->field_5FC.vy += 5000;
                work->field_4BC.vy = work->field_5FC.vy;
            }

            work->field_5FC.vy -= (work->field_5FC.vy - 15000) / 16;
        }
        else
        {
            if (work->field_93C == 1)
            {
                work->field_93C = 0;
                work->field_5FC.vy -= 5000;
                work->field_4BC.vy = work->field_5FC.vy;
            }

            work->field_5FC.vy -= (work->field_5FC.vy - 10000) / 16;
        }
    }

    if (GM_GameStatus & STATE_CAM_CHANGE)
    {
        pos.vx = (gUnkCameraStruct2_800B7868.position.vx * 31 + work->field_4BC.vx) / 32;
        pos.vy = gUnkCameraStruct2_800B7868.position.vy;
        pos.vz = (gUnkCameraStruct2_800B7868.position.vz * 31 + work->field_4BC.vz) / 32;
    }
    else
    {
        pos.vx = (GM_PlayerPosition.vx * 31 + work->field_4BC.vx) / 32;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = (GM_PlayerPosition.vz * 31 + work->field_4BC.vz) / 32;
    }

    dist = SquareRoot0(pos.vx * pos.vx + pos.vy * pos.vy + pos.vz * pos.vz);
    work->field_964 = pos;

    delta = dist - work->field_8C8;
    work->field_8C8 = dist;

    if (work->field_900 != 0)
    {
        s11g_hind_800D6260(&work->field_4BC.vx, &work->field_5FC.vx, &sp40, 4);
        vec.vx = sp40 / 2;
        s11g_hind_800D6260(&work->field_4BC.vy, &work->field_5FC.vy, &sp44, 4);
        vec.vy = 0;
        s11g_hind_800D6260(&work->field_4BC.vz, &work->field_5FC.vz, &sp40, 4);
        vec.vz = -sp40 / 2;
    }
    else
    {
        s11g_hind_800D6260(&work->field_4BC.vx, &work->field_5FC.vx, &sp40, 32);
        vec.vx = sp40 / 2;
        s11g_hind_800D6260(&work->field_4BC.vy, &work->field_5FC.vy, &sp44, 16);
        vec.vy = 0;
        s11g_hind_800D6260(&work->field_4BC.vz, &work->field_5FC.vz, &sp40, 32);
        vec.vz = -sp40 / 2;
    }

    if (vec.vx > 128)
    {
        vec.vx = 128;
    }
    else if (vec.vx < -128)
    {
        vec.vx = -128;
    }

    if (vec.vz > 128)
    {
        vec.vz = 128;
    }
    else if (vec.vz < -128)
    {
        vec.vz = -128;
    }

    dz = (work->field_62C.vz - work->field_4BC.vz) >> 1;
    dx = (work->field_62C.vx - work->field_4BC.vx) >> 1;

    rot.vx = 0;
    rot.vy = work->control.rot.vy;
    rot.vz = 0;

    DG_SetPos2(&DG_ZeroVector, &rot);
    DG_PutVector(&vec, &vec, 1);

    turn.vx = vec.vz;
    turn.vy = ratan2(dx, dz) & 0xFFF;
    turn.vz = vec.vx;

    switch (work->field_5C4)
    {
    case 0:
        s11g_hind_800D648C(&work->control.turn, &turn, 64);
        break;
    case 1:
        s11g_hind_800D648C(&work->control.turn, &turn, 16);
        break;
    case 2:
        s11g_hind_800D648C(&work->control.turn, &turn, 32);
        break;
    case 4:
        switch (work->field_5C8)
        {
        case 4:
            tmp = turn;
            tmp.vy += ((work->field_5E4 / 10) * 2 - 1) * 256;
            s11g_hind_800D648C(&work->control.turn, &tmp, 32);
            /* fallthrough */
        case 5:
            tmp2 = turn;
            tmp2.vy -= ((work->field_5E4 / 10) * 2 - 1) * 128;
            s11g_hind_800D648C(&work->control.turn, &tmp2, 32);
            break;
        }
        break;
    }

    if (work->field_900 != 0)
    {
        if (!(GV_Time & 15) || GV_RandU(16) == 0)
        {
            range = dist / 8;

            tmp = work->control.mov;
            tmp.vx += GV_RandU(32768) % range;
            tmp.vy += (GV_RandU(32768) % range) / 4;
            tmp.vz += GV_RandU(32768) % (dist / 8);
            AN_Blast_Rand(&tmp);

            GM_SeSet2(0, 63, 176);
            GM_SeSet2(0, 63, 41);

            if (GV_RandU(2))
            {
                GM_SeSet2(0, 63, 39);
            }

            if (GV_RandU(2))
            {
                GM_SeSet2(0, 63, 40);
            }

            work->control.turn.vx += GV_RandS(512);
            work->control.turn.vy += GV_RandS(512);
            work->field_948 = 255;
        }

        GM_PadVibration = GV_RandU(2);
        GM_PadVibration2 = work->field_948;
        work->field_948 -= 8;
        s11g_hind_800D648C(&work->control.turn, &turn, 16);
    }

    if (work->field_95C > 0 && --work->field_95C == 0)
    {
        s11g_hind_800D5E54(0, &pos, work->field_960);
    }

    if (work->field_940 == -1)
    {
        work->field_940 = 1;

        if (GM_GameOverTimer == 0)
        {
            GM_SetSong(0x01000002);
        }
    }

    if (GM_Vitality != 0 && GM_GameOverTimer == 0)
    {
        if (work->field_940 == 0 && work->control.mov.vy > 0)
        {
            work->field_940 = 1;
            GM_SetSong(0x01FFFF03);

            if (GM_GameOverTimer == 0)
            {
                GM_SetSong(0xFF0000FE);
            }

            work->field_944 = 30;
        }
        else if (work->field_940 == 1 && work->control.mov.vy < 0)
        {
            work->field_940 = 0;
            s11g_hind_800D5E54(0, &work->control.mov, 200);
            GM_SeSet2(0, 127, 204);

            if (GM_GameOverTimer == 0)
            {
                GM_SetSong(0x01FFFF09);
            }
        }
    }

    if (work->field_8CC == 2)
    {
        work->field_8CC = 3;
        s11g_hind_800D60D8(work->field_8C8, &pos, 182);
    }
    else if (work->field_8CC == 3)
    {
        work->field_8CC = 4;
        s11g_hind_800D60D8(work->field_8C8, &pos, 183);
    }
    else if (work->field_8CC == 4)
    {
        work->field_8CC = 5;
        s11g_hind_800D60D8(work->field_8C8, &pos, 184);
    }

    if (work->field_658 >= 2)
    {
        if ((mts_get_tick_count() - work->last_time) >= 12)
        {
            work->last_time = mts_get_tick_count();

            if (work->nMissileDemoMode2 != 11)
            {
                s11g_hind_800D60D8(work->field_8C8, &pos, 186);
            }
            else
            {
                GM_SeSet2(0, 127, 186);
            }
        }
    }
    else if ((mts_get_tick_count() - work->last_time) >= 8)
    {
        work->last_time = mts_get_tick_count();

        switch (work->field_8CC)
        {
        case 0:
            s11g_hind_800D60D8(work->field_8C8, &pos, 181);
            break;
        case 1:
            s11g_hind_800D60D8(work->field_8C8, &pos, 181);

            if (ABS(work->field_4BC.vx) < 10000 && ABS(work->field_4BC.vz) < 10000)
            {
                work->field_8CC = 2;
                GM_SeSet2(0, 127, 179);
            }
            break;
        case 5:
            s11g_hind_800D60D8(work->field_8C8, &pos, 185);

            if (delta == 0)
            {
                work->field_8CC = 0;
            }
            break;
        }
    }

    if ((mts_get_tick_count() - work->last_time2) >= 4)
    {
        work->last_time2 = mts_get_tick_count();

        if (work->field_5D4 == 1)
        {
            s11g_hind_800D60D8(work->field_8C8, &pos, 177);
        }
    }

    if (work->field_8D0 == 1)
    {
        work->field_8D0 = 0;
        s11g_hind_800D60D8(work->field_8C8, &pos, 176);
    }

    if (work->field_8D4 == 1)
    {
        work->field_8D4 = 0;
        s11g_hind_800D60D8(0, &pos, 180);
    }

    work->body.rots[1].vy -= work->field_4B4;
    work->body.rots[2].vx -= work->field_4B8;
}
#endif
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DAAC8.s")
