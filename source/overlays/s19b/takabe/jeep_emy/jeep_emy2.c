#include "game/game.h"
#include "../jeep_system.h"
#include "jeep_emy.h"



/* TODO: Commonise */
struct _Work;


void s19b_jbullet_800C63DC(Work *work)
{
    if (work->field_968 < 6000)
    {
        work->field_94C = 1;
    }
    else
    {
        work->field_940 = work->control.rot.vy;
    }
}

void s19b_jbullet_800C6404(Work *work)
{
    work->field_93C = 256;
    work->field_94C = 2;
    work->field_948 = 1;
    work->field_940 = work->field_964;
}

void s19b_jbullet_800C6428(Work *work)
{
    work->field_94C = 3;
    work->field_950 = GV_RandU(32);
}

void s19b_jbullet_800C645C(Work *work)
{
    work->field_93C |= 1;

    if (work->field_950 > 15)
    {
        work->field_94C = 3;
        work->field_950 = 0;
    }
    else
    {
        work->field_940 = work->field_964;
        work->field_950++;
    }
}

void s19b_jbullet_800C649C(Work *work)
{
    if ((work->field_950 > 30) && (GV_RandU(8) == 0))
    {
        work->field_950 = 0;
    }

    if (work->field_950 == 6)
    {
        work->field_93C |= 2;
    }

    work->field_93C |= 1;
    work->field_940 = work->field_964;
    work->field_950++;
}

void s19b_jbullet_800C6524(Work *work)
{
    switch (work->field_94C)
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
        work->field_948 = 1;
        work->field_94C = 2;
    }

    work->field_950 = GV_RandU(32);
}

void s19b_jbullet_800C65A8(Work *work)
{
    SVECTOR diff;
    int     dir;

    switch (work->field_94C)
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

    GV_SubVec3(&work->field_8F4, &work->control.mov, &diff);
    diff.vy = 0;
    dir = GV_VecDir2(&diff);
    if (GV_VecLen3(&diff) > 250)
    {
        work->field_93C = 4;
        work->field_940 = dir;
    }
}

void s19b_jbullet_800C666C(Work *work)
{
    switch (work->field_948)
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
    work->field_940 = -1;
    work->field_93C = 0;

    if (work->field_944 == 0)
    {
        s19b_jbullet_800C666C(work);
    }

    work->field_954++;
    work->field_93C |= GV_PadData[1].press;

    if (GV_PadData[1].dir >= 0)
    {
        work->field_940 = GV_PadData[1].dir;
    }
}
