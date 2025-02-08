#include "wolf2.h"

SVECTOR wolf2_800C3560 = {0, 0, 100};
SVECTOR wolf2_800C3568 = {-1024, 0, 0};

void   NewBlood( MATRIX *, int );
void * NewDBloods_800D5B70( SVECTOR *, int, int, int );

void wolf2_PlayVoice(Wolf2Work *work, int index)
{
    if (work->voices[0] != -1 && GM_StreamStatus() == -1)
    {
        GM_VoxStream(work->voices[index], 0);
    }
}

void wolf2_ClearAdjust(Wolf2Work *work, int count)
{
    SVECTOR *adjust;
    int      i;

    adjust = work->adjust;
    for (i = 0; i < count; i++)
    {
        *adjust++ = DG_ZeroVector;
    }
}

// put.c
void wolf2_PutBlood(Wolf2Work *work, int unit, int count)
{
    MATRIX  world;
    SVECTOR pos;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&wolf2_800C3560);

    wolf2_800C3568.vx += GV_RandS(128);
    wolf2_800C3568.vy += GV_RandS(128);
    wolf2_800C3568.vz += GV_RandS(512);
    DG_RotatePos(&wolf2_800C3568);

    ReadRotMatrix(&world);
    NewBlood(&world, count);

    pos.vx = world.t[0];
    pos.vy = -30000;
    pos.vz = world.t[2];
    NewDBloods_800D5B70(&pos, 0, GV_RandU(256) + 256, 60);
}

void wolf2_SetAction(Wolf2Work *work, int action)
{
    work->f688 = action;
    GM_ConfigObjectAction(&work->body, action, 0, 4);
}

void wolf2_800D3704(Wolf2Work *work, int action, int arg2)
{
    if (work->f688 != action)
    {
        work->f688 = action;
        GM_ConfigObjectAction(&work->body, action, 0, 4);
        return;
    }

    if (work->body.is_end == 1)
    {
        work->f690 = arg2;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12a/s12a_wolf2_800D375C.s")

void wolf2_800D3D54(Wolf2Work *work)
{
    work->f6A4 = 0;
    work->f6A0 = 0;
    work->f6A8 = 0;
    work->f69C = 0;
    work->f6AC = 0;
    work->f690 = 0;
    work->f688 = 6;

    GM_ConfigMotionAdjust(&work->body, work->adjust);

    wolf2_ClearAdjust(work, 16);
    wolf2_SetAction(work, 0);

    LSTORE(0, &work->lsight_verts[4].vz); // ???
}
