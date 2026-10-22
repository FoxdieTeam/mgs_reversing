#include "game/game.h"

#include "../jeep_system.h"

#include "jeep_emy.h"

void s19b_jbullet_800C63DC(Work *work)
{
    if (work->player_dist < 6000)
    {
        work->ai_state = 1;
    }
    else
    {
        work->input_dir = work->control.rot.vy;
    }
}

void s19b_jbullet_800C6404(Work *work)
{
    work->input = 256;
    work->ai_state = 2;
    work->ai_mode = 1;
    work->input_dir = work->player_dir;
}

void s19b_jbullet_800C6428(Work *work)
{
    work->ai_state = 3;
    work->ai_time = GV_RandU(32);
}

void s19b_jbullet_800C645C(Work *work)
{
    work->input |= 1;

    if (work->ai_time > 15)
    {
        work->ai_state = 3;
        work->ai_time = 0;
    }
    else
    {
        work->input_dir = work->player_dir;
        work->ai_time++;
    }
}

void s19b_jbullet_800C649C(Work *work)
{
    if ((work->ai_time > 30) && (GV_RandU(8) == 0))
    {
        work->ai_time = 0;
    }

    if (work->ai_time == 6)
    {
        work->input |= 2;
    }

    work->input |= 1;
    work->input_dir = work->player_dir;
    work->ai_time++;
}

void s19b_jbullet_800C6524(Work *work)
{
    switch (work->ai_state)
    {
    case 0:
        s19b_jbullet_800C63DC(work);
        break;
    case 1:
        s19b_jbullet_800C6404(work);
        break;
    }

    if (Takabe_JeepSystem.field_7C != 0)
    {
        work->ai_mode = 1;
        work->ai_state = 2;
    }

    work->ai_time = GV_RandU(32);
}

void s19b_jbullet_800C65A8(Work *work)
{
    SVECTOR diff;
    int     dir;

    switch (work->ai_state)
    {
    case 0:
        s19b_jbullet_800C6428(work);
        break;
    case 2:
        s19b_jbullet_800C645C(work);
        break;
    case 3:
        s19b_jbullet_800C649C(work);
        break;
    }

    GV_SubVec3(&work->goal_pos, &work->control.mov, &diff);
    diff.vy = 0;
    dir = GV_VecDir2(&diff);
    if (GV_VecLen3(&diff) > 250)
    {
        work->input = 4;
        work->input_dir = dir;
    }
}

void s19b_jbullet_800C666C(Work *work)
{
    switch (work->ai_mode)
    {
    case 0:
        s19b_jbullet_800C6524(work);
        break;
    case 1:
        s19b_jbullet_800C65A8(work);
        break;
    }
}

void s19b_jbullet_800C66BC(Work *work)
{
    work->input_dir = -1;
    work->input = 0;

    if (work->field_944 == 0)
    {
        s19b_jbullet_800C666C(work);
    }

    work->field_954++;
    work->input |= GV_PadData[1].press;

    if (GV_PadData[1].dir >= 0)
    {
        work->input_dir = GV_PadData[1].dir;
    }
}
