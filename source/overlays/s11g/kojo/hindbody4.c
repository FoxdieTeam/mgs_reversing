#include "mgstype.h"
#include "game/game.h"
#include "hind.h"

/*
 * The hind's movement code is one source file in the original (hindbody2.c ..
 * hindbody5.c). It is split here only because s11g_hind_800DA534 and
 * s11g_hind_800DAAC8 do not match yet: this way the matching parts are plain C
 * and can be shared by s11b, s11h and s11g. Merge the files back into
 * hindbody2.c once those two functions match.
 */

void s11g_hind_800D61F8(HindWork *work);
void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len);
void s11g_hind_800DA534(HindWork *work);

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
