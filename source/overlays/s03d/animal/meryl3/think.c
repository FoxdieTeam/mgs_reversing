#include "meryl3.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

static SVECTOR aimpos = {4000, 0, 500};
static SVECTOR aimpos2 = {5000, 0, 500};

/*---------------------------------------------------------------------------*/

extern int s03d_dword_800DC2F8;

/*---------------------------------------------------------------------------*/

static int GetDir(SVECTOR *from, SVECTOR *to)
{
    SVECTOR vec;

    GV_SubVec3(to, from, &vec);
    vec.vy = 0;

    return GV_VecDir2(&vec);
}

static int LockOn(Work *work, int shake)
{
    CONTROL *control;
    int      dir;

    control = &work->control;
    dir = GetDir(&control->mov, &aimpos);

    GM_GetHomingTarget2(&work->body.objs->objs[6].world, dir, &work->trg_yaw,
                        &work->trg_pitch, control->map->index, 6000, 4096);

    if (work->trg_yaw < 0)
    {
        work->trg_yaw = dir + GV_RandS(shake);
        return 0;
    }
    else
    {
        work->trg_yaw += GV_RandS(shake);
        return 1;
    }
}

static void Think3_Phase0(Work *work)
{
    work->pad.press |= PAD_L1;
    work->trg_yaw = work->player_dir;

    if (s03d_dword_800DC2F8 == 0 || s03d_dword_800DC2F8 == 4)
    {
        work->think3 = 1;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

static void Think3_Phase1(Work *work)
{
    if (s03d_dword_800DC2F8 == 2)
    {
        work->think3 = 0;
        work->count3 = 0;
    }
    else if (s03d_dword_800DC2F8 == 6)
    {
        LockOn(work, 2);
        work->field_970 = 90;
        work->think3 = 4;
        work->count3 = 0;
    }
    else
    {
        if (work->field_990 < 300)
        {
            if (LockOn(work, 256))
            {
                work->pad.press |= PAD_L2;
            }
            else
            {
                work->pad.press |= PAD_L1;
            }
        }

        work->count3++;
    }
}

static void Think3_Phase2(Work *work)
{
    if (s03d_dword_800DC2F8 == 14)
    {
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (LockOn(work, 8))
    {
        work->pad.press |= PAD_L2;

        if ((work->field_990 % 64) == 0)
        {
            work->field_970 = GV_RandU(8) + 14;
            work->think3 = 3;
            work->count3 = 0;
            return;
        }
    }
    else
    {
        work->pad.press |= PAD_L2;
    }

    work->count3++;
}

static void Think3_Phase3(Work *work)
{
    work->pad.press |= PAD_L2;

    if (work->field_970 < work->count3)
    {
        work->think3 = 2;
        work->count3 = 0;
        return;
    }

    if ((work->count3 % 3) == 0)
    {
        work->pad.press |= PAD_R2;
    }

    work->count3++;
}

static void Think3_Phase4(Work *work)
{
    work->pad.press |= PAD_L2;

    if (work->field_970 < work->count3)
    {
        work->think3 = 5;
        work->count3 = 0;
        return;
    }

    if ((work->count3 % 10) == 0 && LockOn(work, 8))
    {
        GV_DiffDirAbs(work->trg_yaw, work->player_dir);
    }

    if ((work->count3 % 3) == 0)
    {
        work->pad.press |= PAD_R2;
    }

    work->count3++;
}

static void Think3_Phase5(Work *work)
{
    if (work->count3 < 4)
    {
        work->pad.press |= PAD_R1;
    }

    if (s03d_dword_800DC2F8 == 8)
    {
        work->think3 = 2;
    }

    work->count3++;
}

static void Think3_Phase6(Work *work)
{
    SVECTOR dir;

    GV_SubVec3(&aimpos2, &work->control.mov, &dir);
    dir.vy = 0;

    work->pad.dir = GV_VecDir2(&dir);
    if (GV_VecLen3(&dir) < 500)
    {
        work->think3 = 7;
        work->count3 = 0;
        return;
    }

    work->count3++;
}

static void Think2_Phase0(Work *work)
{
    switch (work->think3)
    {
    case 0:
        Think3_Phase0(work);
        break;
    case 1:
        Think3_Phase1(work);
        break;
    case 2:
        Think3_Phase2(work);
        break;
    case 3:
        Think3_Phase3(work);
        break;
    case 4:
        Think3_Phase4(work);
        break;
    case 5:
        Think3_Phase5(work);
        break;
    case 6:
        Think3_Phase6(work);
        break;
    case 7:
        break;
    }
}

static void Think1_Phase0(Work *work)
{
    switch (work->think2)
    {
    case 0:
        Think2_Phase0(work);
        break;
    }
}

void Meryl3Think(Work *work)
{
    work->pad.dir = -1;
    work->pad.press = 0;

    switch (work->think1)
    {
    case 0:
        Think1_Phase0(work);
        break;
    }

    work->count1++;
}
