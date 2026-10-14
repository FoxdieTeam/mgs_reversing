#include "mgstype.h"
#include "game/game.h"
#include "hind.h"
#include "mts/mts.h"

void s11g_hind_800D5E44(HindWork *work, int a1);
void s11g_hind_800D5E54(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D619C(HindWork *work, int index);
void s11g_hind_800D61F8(HindWork *work);
void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len);
void s11g_hind_800D60D8(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D6260(long *vec, long *pos, long *old, int len);
void s11g_hind_800D648C(SVECTOR *a, SVECTOR *b, int len);
void s11g_hind_800D66F0(HindWork *work);
void s11g_hind_800D6848(HindWork *work);
void s11g_hind_800D7644(HindWork *work);
void AN_Blast_Rand(SVECTOR *pos);

extern int amissile_alive_8009F490;

void s11g_hind_800D9344(HindWork *work)
{
    VECTOR  sp10;
    SVECTOR sp20;

    switch (work->field_5C8)
    {
    case 0:
        if ((work->field_430 * 7) / 8 < work->field_434)
        {
            s11g_hind_800D5E44(work, (GV_RandU(4096) % 2) + 130);
        }
        else
        {
            switch (work->field_8C4++ % 3)
            {
            case 0:
                s11g_hind_800D619C(work, 25);
                break;
            case 1:
                s11g_hind_800D619C(work, 26);
                break;
            case 2:
                s11g_hind_800D619C(work, 27);
                break;
            }
        }

        work->field_5C8 = 4;
        work->field_5E4 = GV_RandU(8) + 32;
        work->field_8D0 = 1;

        sp20.vx = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);
        sp20.vy = (-1000 - GV_RandU(4096));
        sp20.vz = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);

        work->field_60C.vx += sp20.vx;
        work->field_60C.vy += sp20.vy;
        work->field_60C.vz += sp20.vz;
        work->field_5F4 += GV_RandS(256);
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            sp10.vx = work->field_60C.vx - work->field_5FC.vx;
            sp10.vz = work->field_60C.vz - work->field_5FC.vz;
            SquareRoot0(sp10.vx * sp10.vx + sp10.vz * sp10.vz);
            s11g_hind_800D62BC(&work->field_60C, &work->field_5FC, 32);
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_60C = work->field_4BC;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_64C = 0;

            if (work->field_5C4 == 2)
            {
                work->field_5C8 = 6;
                work->field_5E4 = 0;
            }
            else if (work->field_5CC == 1 && work->field_5D0 == 5)
            {
                work->field_5C4 = work->field_5CC;
                work->field_5C8 = work->field_5D0;
                work->field_5E4 = 5;
            }
            else
            {
                work->field_5C8 = 0;
                work->field_5C4 = work->field_5CC;
            }
        }
        break;
    }
}

void s11g_hind_800D96B0(HindWork *work)
{
    int diff;

    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = GV_RandU(16) + 30;

        if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
        {
            work->field_60C.vy = 10000;
        }
        else
        {
            work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
        }
        /* fallthrough */
    case 4:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
            break;
        }

        work->field_5C8 = 5;
        work->field_5E4 = GV_RandU(16) + 20;
        work->field_5E8 = GV_RandU(2);

        work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 9000;
        work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 9000;

        if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
        {
            work->field_60C.vy = (work->field_60C.vy + 5000) / 2;
        }
        else
        {
            work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
        }

        s11g_hind_800D61F8(work);
        break;

    case 5:
        if (work->field_5E4 < 10)
        {
            work->field_5D4 = 1;
        }

        work->field_62C.vx = GM_PlayerPosition.vx + work->field_664.vx + work->field_65C.vx * work->field_5E4;
        work->field_62C.vy = GM_PlayerPosition.vy + work->field_664.vy + work->field_65C.vy * work->field_5E4;
        work->field_62C.vz = GM_PlayerPosition.vz + work->field_664.vz + work->field_65C.vz * work->field_5E4;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 40);
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(16) + 40;

            if (GV_RandU(2))
            {
                diff = GV_RandU(64) + 256;
                work->field_5F4 += diff;
            }
            else
            {
                diff = GV_RandU(64) + 256;
                work->field_5F4 -= diff;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096;

            if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
            {
                work->field_60C.vy = (work->field_60C.vy + 8000) / 2;
            }
            else
            {
                work->field_60C.vy = (work->field_60C.vy + 15000) / 2;
            }

            s11g_hind_800D61F8(work);
        }
        else
        {
            work->field_5C8 = 6;
            work->field_5E4 = GV_RandU(16) + 16;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_8CC = 1;
            work->field_5C8 = 7;
            work->field_5E4 = GV_RandU(32) + 70;
            work->field_5F4 += 2048;
            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 9000;
            work->field_60C.vy = 13000;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 9000;
        }
        break;

    case 7:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C4 = 1;
            work->field_5C8 = 0;
        }
        break;
    }
}
void s11g_hind_800D9B80(HindWork *work)
{
    int amount;
    int dir;
    int diff;

    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = 20;
        work->field_60C = work->field_4BC;
        work->field_60C.vy = 10000;
        work->field_5F8 = GV_RandU(2);
        /* fallthrough */
    case 4:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 8);
            break;
        }

        work->field_5F4 &= 0xFFF;

        if (work->field_5F4 > 256 && work->field_5F4 < 1792)
        {
            work->field_5C8 = 4;
            work->field_5E4 = 2;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                amount = 8;
                break;
            case GM_LEVEL_HARD:
                amount = 16;
                break;
            case GM_LEVEL_EXTREME:
                amount = 16;
                break;
            }

            work->field_5F4 = (work->field_5F4 < 1024) ? work->field_5F4 - amount : work->field_5F4 + amount;
            work->field_60C.vy = 13000;
        }
        else
        {
            work->field_5C8 = 5;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                work->field_5E4 = GV_RandU(32) + 70;
                work->field_5E8 = GV_RandU(4) * 4 + 4;
                break;
            case GM_LEVEL_HARD:
                work->field_5E4 = GV_RandU(16) + 20;
                work->field_5E8 = GV_RandU(2) + 3;
                break;
            case GM_LEVEL_EXTREME:
                work->field_5E4 = GV_RandU(16) + 20;
                work->field_5E8 = GV_RandU(2) + 2;
                break;
            }

            work->field_60C.vy = 13000;
        }

        work->field_60C.vx = rcos(work->field_5F4) * 8;
        work->field_60C.vz = rsin(work->field_5F4) * 8;
        break;

    case 5:
        if (work->field_5E4 > 0)
        {
            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 40);
                break;
            case GM_LEVEL_HARD:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
                break;
            case GM_LEVEL_EXTREME:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
                break;
            }
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 5;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                work->field_5E4 = GV_RandU(32) + 30;
                break;
            case GM_LEVEL_HARD:
                work->field_5E4 = GV_RandU(16) + 20;
                break;
            case GM_LEVEL_EXTREME:
                work->field_5E4 = GV_RandU(16) + 20;
                break;
            }

            if (work->field_5F4 > 256 && work->field_5F4 < 1792)
            {
                if (work->field_5F4 > 1024)
                {
                    work->field_5F8 = 1;
                }
                else
                {
                    work->field_5F8 = 0;
                }

                work->field_5E8 = GV_RandU(4) * 2 + 4;
            }
            else if (work->field_5F4 > 2560 && work->field_5F4 < 3587 && !(GV_Time & 63) && GV_RandU(2) == 0)
            {
                work->field_5E8 = GV_RandU(4) * 2 + 4;
                work->field_5F8 = 1 - work->field_5F8;
            }

            if (work->field_5F8 != 0)
            {
                work->field_5F4 += 256;
            }
            else
            {
                work->field_5F4 -= 256;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = (work->field_60C.vy - 15000) / 2;
        }
        else
        {
            work->field_5F4 &= 0xFFF;
            work->field_5E8 = GV_RandU(2);
            work->field_5E4 = GV_RandU(16) + 60;

            if (work->field_5F8 != 0)
            {
                work->field_5F4 += 256;
            }
            else
            {
                work->field_5F4 -= 256;
            }

            work->field_5C8 = 6;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
            break;
        }

        work->field_8D4 = 1;
        work->field_5C8 = 7;
        work->field_5E4 = GV_RandU(16) + 60;
        dir = work->field_5F4;

        if (work->field_5F8 != 0)
        {
            dir += GV_RandU(256);
        }
        else
        {
            dir -= GV_RandU(256);
        }

        if (work->field_5F4 <= 500 || work->field_5F4 >= 1600)
        {
            work->field_5F4 = dir;
        }

        work->field_60C.vx = (rcos(work->field_5F4) * 20000) / 4096;
        work->field_60C.vy = 10000;
        work->field_60C.vz = (rsin(work->field_5F4) * 20000) / 4096;
        break;

    case 7:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 4);
            break;
        }

        work->field_5C8 = 8;

        switch (GM_GameLevel)
        {
        default:
        case GM_LEVEL_EASY:
        case GM_LEVEL_NORMAL:
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5E8 = GV_RandU(2) + 2;
            break;
        case GM_LEVEL_HARD:
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5E8 = GV_RandU(2) + 1;
            break;
        case GM_LEVEL_EXTREME:
            work->field_5E4 = GV_RandU(4) + 32;
            work->field_5E8 = GV_RandU(2) + 1;
            break;
        }

        work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096;
        work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096;
        work->field_60C.vy = (work->field_60C.vy + 10000) / 2;

        switch (work->field_8C0++ % 4)
        {
        case 1:
            s11g_hind_800D619C(work, 23);
            break;
        case 0:
        case 2:
            s11g_hind_800D5E54(0, &work->field_964, 132);
            break;
        case 3:
            s11g_hind_800D619C(work, 24);
            break;
        }
        break;

    case 8:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            case GM_LEVEL_HARD:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            case GM_LEVEL_EXTREME:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            }
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 8;
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5F8 = GV_RandU(2);

            if (work->field_5F8 != 0)
            {
                diff = GV_RandS(128) - 512;
                work->field_5F4 -= diff;
            }
            else
            {
                diff = GV_RandS(128) - 512;
                work->field_5F4 += diff;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 5000;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 5000;

            if (work->field_60C.vz < 4000)
            {
                work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
            }
            else
            {
                work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
            }
        }
        else if (work->field_434 < work->field_430 / 5 && GV_RandU(4) < 3)
        {
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(32) + 30;
            work->field_5E8 = GV_RandU(4) * 4 + 4;
            work->field_5F4 &= 0xFFF;
            work->field_5F4 = (work->field_5F4 / 512) * 512 + 256;
            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA534.s")
void s11g_hind_800DA534(HindWork *work);

/*
TODO: This only matches when field_5F4 is volatile
void s11g_hind_800DA534(HindWork *work)
{
    int f5F4;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 5;
    work->field_5E4 = 100;
    work->field_5F8 = GV_RandU(2);
    do {} while (0);
    work->field_5F4 = (work->field_5F4 + 2048) & 0xFFF;

    f5F4 = work->field_5F4;
    if (f5F4 > 256 && f5F4 < 1792)
    {
        if (f5F4 < 1024)
        {
            work->field_5F4 = 256;
        }
        else
        {
            work->field_5F4 = 1792;
        }
    }

    work->field_60C.vx = rcos(work->field_5F4) * 43;
    work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
    work->field_60C.vz = rsin(work->field_5F4) * 43;
}
*/

void s11g_hind_800DA614(HindWork *work)
{
    int amount;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 6;
    work->field_5E4 = GV_RandU(8) + 16;

    switch (GM_GameLevel)
    {
    default:
    case GM_LEVEL_EASY:
    case GM_LEVEL_NORMAL:
        if ((work->field_5E8 < 10) && ((work->field_5E8 & 3) == 0))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 64;
        break;
    case GM_LEVEL_HARD:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 70;
        break;
    case GM_LEVEL_EXTREME:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 72;
        break;
    }

    if (work->field_5F8 != 0)
    {
        work->field_5F4 += amount;
    }
    else
    {
        work->field_5F4 -= amount;
    }

    work->field_60C.vx = rcos(work->field_5F4) * ((work->field_5E8 / 2) + 29);
    work->field_60C.vy = 32000;
    work->field_60C.vz = rsin(work->field_5F4) * ((work->field_5E8 / 2) + 29);
}

void s11g_hind_800DA7C4(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = 0;
        work->field_60C = work->field_4BC;
        work->field_60C.vy = 13000;
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 0;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
            work->field_5D4 = 1;
        }
        else if (((work->field_430 * 2) / 3) < work->field_434)
        {
            if (GV_DiffDirS(work->field_5F4, work->control.turn.vy) > 0)
            {
                work->field_5F8 = 1;
            }
            else
            {
                work->field_5F8 = 0;
            }

            work->field_5E8 = 24;
            s11g_hind_800DA614(work);
        }
        else
        {
            work->field_5C8 = 8;
            work->field_5E4 = GV_RandU(16) + 32;
            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = 25000;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_5F4 += (GV_RandS(126) + 700) * (GV_RandU(2) * 2 - 1);
            work->field_5F4 &= 0xFFF;
        }
        break;
    case 6:
        if (work->field_5E8 > 9)
        {
            work->field_62C = work->field_60C;
        }

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
        }
        else if (work->field_5E8 > 0)
        {
            s11g_hind_800DA614(work);
            work->field_5E8--;
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 10;
        }
        break;
    case 7:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_8CC = 1;
            s11g_hind_800DA534(work);
        }
        break;
    case 8:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

#if 0 /* NON_MATCHING: 2 instructions differ (scheduling of the "dist / 8" shift
         in the blast block: the original does not treat the quotient as a
         register birth, i.e. it is probably a reused variable) */
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
