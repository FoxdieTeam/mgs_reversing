#include "doll.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "chara/snake/sna_init.h"
#include "Game/jimctrl.h"

int s01a_dword_800C3D04[] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00000008, 0x00000010, 0x00000020, 0x00000040,
    0x00000080, 0x00000100, 0x00000200, 0x00000400,
    0x00000800, 0x00001000, 0x00000000, 0x0000000F,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0000001D, 0x0000001E, 0x0000001F,
};

void Demodoll_800DDF4C(DollWork *work)
{
    work->fBB4 = work->fBA8;
    work->fBA0 = work->fB98;
    work->fBB8 = work->fBAC;
}

void Demodoll_800DDF84(DollWork *work)
{
    int fB94;
    int fBA6;

    fB94 = work->fB94 + 1;
    if (fB94 >= work->fA90)
    {
        fB94 = 0;
    }

    work->fB94 = fB94;
    work->fBA0 = work->fA94[work->fB94];
    work->fBB4 = HZD_GetAddress(work->control.map->hzd, &work->fBA0, -1);
    work->fBB8 = work->fBAC;

    fBA6 = work->fBA0.pad;
    if ((fBA6 & 0x1F) == 0x1F)
    {
        GV_DestroyActor(&work->actor);
    }
}

int Demodoll_800DE024(DollWork *work, int size)
{
    SVECTOR diff;
    int     dx, dz;

    dx = work->fBA0.vx - work->control.mov.vx;
    diff.vx = dx;

    dz = work->fBA0.vz - work->control.mov.vz;
    diff.vz = dz;

    if ((dx > -size) && (dx < size) && (dz > -size) && (dz < size))
    {
        return 1;
    }

    work->fC0A = GV_VecDir2(&diff);
    work->fC1C++;

    return 0;
}

int Demodoll_800DE0AC(DollWork *work)
{
    SVECTOR  sp10;
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    CONTROL *control;
    int      dx, dz;
    int      yaw;
    int      size;
    int      dist;

    control = &work->control;

    sp18 = control->mov;
    sp18.vy = 0;

    sp20 = work->fBA0;
    sp20.vy = 0;

    dx = sp20.vx - sp18.vx;
    sp10.vx = dx;

    dz = sp20.vz - sp18.vz;
    sp10.vz = dz;

    yaw = GV_VecDir2(&sp10);

    size = 250;
    if ((dx > -size) && (dx < size) && (dz > -size) && (dz < size))
    {
        dist = GV_DiffVec3(&sp18, &sp20);
        GV_AddVec3(&sp18, &control->step, &sp28);

        if (dist < GV_DiffVec3(&sp28, &sp18))
        {
            control->mov = work->fBA0;
            control->step = DG_ZeroVector;
            return 1;
        }
    }

    if (GV_DiffDirAbs(yaw, control->rot.vy) > 64)
    {
        control->turn.vy = yaw;
    }
    else
    {
        work->fC0A = yaw;
    }

    work->fC1C++;

    return 0;
}

int Demodoll_800DE25C(DollWork *work)
{
    return 0;
}

void Demodoll_800DE264(DollWork *work, int index)
{
    printf(" %d = %d \n", index - 16, work->fE18[index - 16]);

    if (GM_StreamStatus() == -1)
    {
        work->fE38++;
        GM_VoxStream(work->fE18[work->fE38], 0);
    }
    else
    {
        GM_StreamPlayStart();
    }
}

void Demodoll_800DE2E8(DollWork *work, int index)
{
    int proc;

    proc = work->fE60[index];
    if (proc >= 0)
    {
        GCL_ExecProc(proc, NULL);
    }
}

int Demodoll_800DE320(DollWork *work)
{
    CONTROL *control;
    GV_MSG  *msg;
    int      n_msgs;

    control = &work->control;
    control->field_56 = GV_ReceiveMessage(control->name, &control->field_5C_mesg);

    msg = control->field_5C_mesg;
    n_msgs = control->field_56;

    while (n_msgs > 0)
    {
        if (msg->message[0] == work->fC0E)
        {
            return 1;
        }

        n_msgs--;
        msg++;
    }

    return 0;
}

int Demodoll_800DE390(DollWork *work)
{
    int temp_v1;
    int voice;
    int temp_a1;
    int proc;

loop:
    temp_v1 = work->fBA0.pad;

    voice = temp_v1 & 0x1F;
    temp_a1 = (temp_v1 & 0x300) >> 8;
    proc = (temp_v1 & 0xFC00) >> 10;

    work->fC08 = work->fC30[(temp_v1 & 0xE0) >> 5];

    if (work->fC08 == 32001)
    {
        work->fC0E = proc;
    }
    else if (work->fC08 == 32000)
    {
        work->fC0E = proc;
        work->fE44 = 0;
        work->fE40 = 0;
    }

    if (voice >= 16 && voice <= 25)
    {
        printf(" doll voice[%d]\n", voice);
        Demodoll_800DE264(work, voice);

        work->fC08 = 0;
        work->fC0A = work->control.rot.vy;

        Demodoll_800DDF84(work);

        if (!Demodoll_800DE024(work, 350))
        {
            return 0;
        }

        goto loop;
    }
    else if (voice == 30)
    {
        printf(" doll proc[%d]\n", proc);
        Demodoll_800DE2E8(work, proc);

        work->fC08 = 0;
        work->fC0A = work->control.rot.vy;

        Demodoll_800DDF84(work);

        if (!Demodoll_800DE024(work, 350))
        {
            return 0;
        }

        goto loop;
    }

    work->fC04 = s01a_dword_800C3D04[voice];

    if (work->fC04 == 29)
    {
        if (work->fDFC == 0)
        {
            work->fDFC = 1;
        }
        else
        {
            work->fDFC = 0;
        }

        work->fC08 = 0;
        Demodoll_800DDF84(work);
        return 0;
    }

    if ((work->fC04 == 0) && (work->fC08 == 31000))
    {
        work->fC08 = 0;
        work->fC0A = work->control.rot.vy;
        Demodoll_800DDF84(work);
        return 0;
    }

    if (work->fC04 == 15)
    {
        work->fC08 = 0;
        work->fC0A = work->control.rot.vy;
        return 0;
    }

    work->fC0A = work->fC40[temp_a1];
    return 1;
}

int Demodoll_800DE550(DollWork *work)
{
    if (work->fC08 == 32001)
    {
        if (Demodoll_800DE320(work))
        {
            work->fC0E = 0;
            work->fC08 = 0;
            return 1;
        }

        work->fBFC |= work->fC04;
        return 0;
    }
    else if (work->fC08 == 31000)
    {
        if (work->fBE4 != 0)
        {
            work->fC08 = 0;
            return 1;
        }

        work->fBFC |= work->fC04;
        return 0;
    }
    else if (work->fC08 == 32000)
    {
        if (work->fC0E == 0)
        {
            if (GM_StreamStatus() == -1)
            {
                work->fC08 = 0;
                return 1;
            }

            work->fBFC |= work->fC04;
            return 0;
        }

        if ((work->fE48[work->fC0E - 1] <= jimctrl_80038688()) || (GM_StreamStatus() == -1))
        {
            work->fC08 = 0;
            return 1;
        }

        work->fBFC |= work->fC04;
        return 0;
    }
    else if (work->fC08 > 0)
    {
        work->fBFC |= work->fC04;
        work->fC08--;
        return 0;
    }

    return 1;
}

int Demodoll_800DE670(DollWork *work)
{
    if (work->fC08 > 0)
    {
        work->fBFC |= work->fC04;
        work->fC08--;
    }

    return Demodoll_800DE024(work, 350) != 0;
}

int Demodoll_800DE6C4(DollWork *work)
{
    if (Demodoll_800DE0AC(work))
    {
        return 1;
    }

    work->fC1C++;
    return 0;
}

void Demodoll_800DE700(DollWork *work)
{
    work->fC1C++;
}

void Demodoll_800DE714(DollWork *work)
{
    if (work->fC1C >= 16)
    {
        work->fC18 = 3;
        work->fC1C = 0;
        return;
    }

    if (work->fC1C == 0 || work->fC1C == 3 || work->fC1C == 6)
    {
        work->fBFC |= 0x2;
    }

    work->fBFC |= 0x1;
    work->fC0A = work->fE08;
    work->fC1C++;
}

void Demodoll_800DE784(DollWork *work)
{
    switch (work->fC18)
    {
    case 0:
        if (!Demodoll_800DE670(work))
        {
            break;
        }

        if (Demodoll_800DE25C(work))
        {
            Demodoll_800DDF4C(work);
            work->fB94 = work->fA90 - 1;
            break;
        }

        if (Demodoll_800DE390(work))
        {
            work->fBFC |= work->fC04;

            if (work->fC0A >= 0)
            {
                work->control.turn.vy = work->fC0A;
            }

            work->fC18 = 2;
        }
        else if (work->fC04 == 15)
        {
            work->fC18 = 1;
        }

        work->fC1C = 0;
        break;

    case 1:
        if (!Demodoll_800DE6C4(work))
        {
            break;
        }

        Demodoll_800DDF84(work);

        if (!Demodoll_800DE024(work, 350))
        {
            work->fC18 = 0;
            work->fC1C = 0;
            break;
        }

        if (Demodoll_800DE390(work))
        {
            work->fBFC |= work->fC04;

            if (work->fC0A >= 0)
            {
                work->control.turn.vy = work->fC0A;
            }

            work->fC18 = 2;
        }
        else if (work->fC04 != 15)
        {
            work->fC18 = 0;
        }

        work->fC1C = 0;
        break;

    case 2:
        if (!Demodoll_800DE550(work))
        {
            break;
        }

        Demodoll_800DDF84(work);

        if (Demodoll_800DE024(work, 350))
        {
            if (Demodoll_800DE390(work))
            {
                work->fBFC |= work->fC04;

                if (work->fC0A >= 0)
                {
                    work->control.turn.vy = work->fC0A;
                    work->fC0A = -1;
                }
            }
            else if (work->fC04 != 15)
            {
                work->fC18 = 0;
            }
            else
            {
                work->fC18 = 1;
            }
        }
        else
        {
            work->fC18 = 0;
        }

        work->fC1C = 0;
        break;
    }
}

void Demodoll_800DE964(DollWork *work)
{
    switch (work->fC18)
    {
    case 3:
        Demodoll_800DE700(work);
        break;

    case 4:
        Demodoll_800DE714(work);
        break;
    }
}

void Demodoll_800DE9B4(DollWork *work)
{
    switch (work->fC14)
    {
    case 0:
        Demodoll_800DE784(work);
        break;

    case 1:
        Demodoll_800DE964(work);
        break;
    }
}

void Demodoll_800DEA04(DollWork *work)
{
    work->fC0A = -1;
    work->fBFC = 0;

    if (work->fC10 == 0)
    {
        Demodoll_800DE9B4(work);
    }

    work->fC20++;

    if (work->fDF8 != 0 && GM_StreamStatus() == -1)
    {
        if (work->fE18[work->fE38 + 1] != 0)
        {
            work->fE38++;
            GM_VoxStream(work->fE18[work->fE38], 0x40000000);
        }
    }
}
