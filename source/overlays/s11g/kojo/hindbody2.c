#include "common.h"
#include "linkvar.h"
#include "game/game.h"
#include "hind.h"

void s11g_hind_800D5E44(HindWork *work, int a1);
void s11g_hind_800D619C(HindWork *work, int index);
void s11g_hind_800D61F8(HindWork *work);
void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len);

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

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D96B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D9B80.s")

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

    switch (GM_DifficultyFlag)
    {
    default:
    case DIFFICULTY_EASY:
    case DIFFICULTY_NORMAL:
        if ((work->field_5E8 < 10) && ((work->field_5E8 & 3) == 0))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 64;
        break;
    case DIFFICULTY_HARD:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 70;
        break;
    case DIFFICULTY_EXTREME:
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

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DAAC8.s")
