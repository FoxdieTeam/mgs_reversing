#include "wolf2.h"

SVECTOR wolf2_800C3560 = {0, 0, 100};
SVECTOR wolf2_800C3568 = {-1024, 0, 0};

extern SVECTOR wolf2_800DD6C8;

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

void s12a_wolf2_800D375C(Wolf2Work *work)
{
    GCL_ARGS args;
    u_long   data[1];
    int      proc_id;

    proc_id = work->f784;
    data[0] = 0;

    if (proc_id >= 0)
    {
        data[0] = work->f7A4;

        args.argc = 1;
        args.argv = data;

        GCL_ForceExecProc(work->f784, &args);
    }
}

void s12a_wolf2_800D37A8(Wolf2Work *work)
{
    TARGET *target;

    target = work->f65C;

    wolf2_800DD6C8 = work->control.mov;

    switch(work->f690)
    {
    case 0:
        wolf2_800D3704(work, 0, 0);
        break;

    case 2:
        wolf2_800D3704(work, 1, 0);
        break;

    case 3:
        wolf2_800D3704(work, 2, 1);
        break;

    case 4:
        wolf2_800D3704(work, 3, 1);
        break;

    case 1:
        if (work->f6B0 == 0)
        {
            switch (work->f770)
            {
            case 0:
                wolf2_PlayVoice(work, 0);
                break;

            case 1:
                wolf2_PlayVoice(work, 1);
                break;

            case 2:
                wolf2_PlayVoice(work, 2);
                break;

            case 3:
                wolf2_PlayVoice(work, 3);
                break;
            }

            if (++work->f770 > 3)
            {
                work->f770 = 0;
            }
        }
        else
        {
            switch (work->f774)
            {
            case 0:
                wolf2_PlayVoice(work, 4);
                break;

            case 1:
                wolf2_PlayVoice(work, 5);
                break;

            case 2:
                wolf2_PlayVoice(work, 6);
                break;
            }

            if (++work->f774 > 2)
            {
                work->f774 = 0;
            }
        }

        work->f690 = 0;
        break;

    case 5:
        wolf2_800D3704(work, 4, 6);
        work->f6A0 = 90;
        return;

    case 6:
        if (--work->f6A0 > 0)
        {
            wolf2_800D3704(work, 5, 6);
        }
        else
        {
            work->f778 = 1;
            work->f690 = 7;
        }
        return;

    case 7:
        wolf2_800D3704(work, 5, 7);
        break;
    }

    if (work->f6AC == 0)
    {
        if ((target->damaged & TARGET_POWER) && target->a_mode != 2)
        {
            work->f7A4 -= work->f65C->field_28 / 4;

            s12a_wolf2_800D375C(work);
            work->f6B0 = 0;
            wolf2_ClearAdjust(work, 16);
            work->f6A8 = 0;
            work->f6A4 = 0;

            wolf2_PutBlood(work, GV_RandU(8), 2);

            if (work->f7A4 < 1)
            {
                work->f690 = 5;

                if (work->f770 != -1)
                {
                    GM_SeSet2(0, 63, 134);
                    work->f770 = -1;
                }

                if (work->f78C != -1)
                {
                    GCL_ForceExecProc(work->f78C, NULL);
                }

                GM_GameOver();
            }
            else
            {
                work->f6AC = 1;

                GM_SeSet2(0, 63, 133);

                switch (GV_RandU(4))
                {
                case 0:
                case 1:
                    work->f690 = 3;
                    break;

                case 2:
                case 3:
                    work->f690 = 4;
                    break;
                }
            }
        }
        else if ((work->f660->damaged & TARGET_POWER) || target->a_mode == 2)
        {
            work->f6B0 = 1;

            if (target->a_mode == 2)
            {
                work->f7A4 -= work->f65C->field_28 / 4;
            }
            else
            {
                work->f7A4 -= work->f660->field_28 / 8;
            }

            s12a_wolf2_800D375C(work);
            wolf2_PutBlood(work, GV_RandU(8), 2);

            if (work->f7A4 < 1)
            {
                work->f690 = 5;

                if (work->f770 != -1)
                {
                    GM_SeSet2(0, 63, 134);
                    work->f770 = -1;
                }

                if (work->f78C != -1)
                {
                    GCL_ForceExecProc(work->f78C, NULL);
                }

                GM_GameOver();
            }
            else
            {
                work->f6AC = 1;
                GM_SeSet2(0, 63, 133);

                switch (GV_RandU(4))
                {
                case 0:
                case 1:
                    work->f690 = 3;
                    break;

                case 2:
                case 3:
                    work->f690 = 4;
                    break;
                }
            }
        }
    }

    work->f65C->damaged &= ~TARGET_POWER;
    work->f65C->field_28 = 0;
    work->f65C->field_26_hp = 1024;
    work->f65C->a_mode = 0;

    work->f660->damaged &= ~TARGET_POWER;
    work->f660->field_28 = 0;
    work->f660->field_26_hp = 1024;
    work->f660->a_mode = 0;

    if (work->f6AC == 1 && GM_StreamStatus() == 2)
    {
        work->f6AC = 2;
    }
    else if (work->f6AC == 2 && GM_StreamStatus() == -1)
    {
        work->f6AC = 0;

        work->f65C->damaged &= ~TARGET_POWER;
        work->f660->damaged &= ~TARGET_POWER;

        if (work->f6B0 == 1 && work->f788 != -1)
        {
            GCL_ForceExecProc(work->f788, NULL);
        }
    }
}

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

    work->f778 = 0;
}
