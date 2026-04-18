#include "game/game.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x40];
    OBJECT  *body;
    char     pad4[0x18];
    int      field_7C;
    MATRIX   world;
} JEEP_SYSTEM;

extern JEEP_SYSTEM s19b_dword_800DE658; /* Takabe_JeepSystem */

/* TODO: Commonise */
struct _Work;
typedef void (*JBULLET_FN)(struct _Work *, int);

typedef struct _Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[16 + 1];
    MOTION_SEGMENT m_segs2[16 + 1];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    OBJECT         weapon;
    int            lod;
    DG_DEF        *models[2];
    TARGET        *target1;
    TARGET        *target2;
    HOMING        *hom;
    int            field_8D4;
    char           pad1[0x8];
    int            field_8E0;
    SVECTOR        field_8E4;
    SVECTOR        field_8EC;
    SVECTOR        field_8F4;
    int            field_8FC;
    SVECTOR        field_900[4];
    JBULLET_FN     field_920;
    char           pad2[0x4];
    int            field_928;
    char           pad3[0x4];
    int            field_930;
    int            field_934;
    int            field_938;
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
    int            field_954;
    char           pad4[0xC];
    int            field_964;
    int            field_968;
    char           pad5[0x28];
} Work;

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

    if (s19b_dword_800DE658.field_7C != 0)
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
