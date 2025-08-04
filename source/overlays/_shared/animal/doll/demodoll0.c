#include "doll.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "chara/snake/sna_init.h"
#include "game/jimctrl.h"

short s01a_dword_800C3CE4[] = {
    0x0000, 0x0001, 0x0002, 0x0003,
    0x0004, 0x0005, 0x0006, 0x0007,
    0x0008, 0x0009, 0x000A, 0x000B,
    0x000C, 0x000D, 0x000E,
};

void AN_Breath(MATRIX *world);

void Demodoll_800DD860(DollWork *work, int);
void Demodoll_800DDB18(DollWork *work, int);
void Demodoll_800DDD14(DollWork *work, int);
void Demodoll_800DEA04(DollWork *work);

int Demodoll_800DD6A8(DollWork *work)
{
    if ((work->fBFC & 0x1FFF) != 0)
    {
        work->fBD0 = Demodoll_800DDB18;
        work->fBD8 = 0;

        work->control.turn.vz = 0;
        work->control.turn.vx = 0;

        return 1;
    }

    return 0;
}

void Demodoll_800DD6E0(DollWork *work)
{
    int dy;
    int ang;

    dy = GM_PlayerBody->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1];
    ang = (ratan2(work->fE0C, dy) & 0xFFF) - 1024;

    work->adjust[2].vx = ang;
    work->adjust[6].vx = ang;

    if (ang < 0)
    {
        work->adjust[7].vx = ang * 3;
    }
    else
    {
        work->adjust[7].vx = (ang * 3) / 2;
    }
}

void Demodoll_800DD75C(DollWork *work)
{
}

void Demodoll_800DD764(DollWork *work)
{
    sna_act_helper2_helper2_80033054(work->control.name, &work->adjust[work->fE3C]);
}

void Demodoll_800DD798(DollWork *work, int arg1)
{
    CONTROL *control;

    control = &work->control;

    if (arg1 == 0)
    {
        work->fBE0 = 0;
        GM_ConfigObjectAction(&work->body, s01a_dword_800C3CE4[0], 0, 4);
    }

    if (Demodoll_800DD6A8(work))
    {
        if (work->fC0A >= 0)
        {
            control->turn.vy = work->fC0A;
        }
    }
    else
    {
        if (work->fC0A >= 0)
        {
            work->fBD0 = Demodoll_800DD860;
            work->fBD8 = 0;

            work->control.turn.vz = 0;
            work->control.turn.vx = 0;

            control->turn.vy = work->fC0A;
        }

        work->control.step = DG_ZeroVector;
    }
}

void Demodoll_800DD860(DollWork *work, int arg1)
{
    CONTROL    *control;
    int         saved_vy;
    int         action;
    DollMotion *motion;
    int         i;

    control = &work->control;
    saved_vy = work->fC0A;

    if (arg1 == 0)
    {
        if (work->fDFC == 0)
        {
            work->fBE0 = 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
        else if (work->fDFE < 0)
        {
            work->fBE0 = 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
        else
        {
            work->fBE0 = work->fDFE + 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
    }

    if (work->fBE0 == 1)
    {
        if (work->fDFC != 0)
        {
            work->fBE0 = work->fDFE + 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction(&work->body, action, 0, 4);
        }
    }
    else if (work->fDFC == 0)
    {
        work->fBE0 = 1;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    if (saved_vy < 0)
    {
        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    control->turn.vy = saved_vy;

    motion = &work->fC48[work->fBE0];
    for (i = 0; i < motion->index; i++)
    {
        if (motion->entries[i].vx == work->m_ctrl.info1.frame)
        {
            if (work->fE00[1] != 0)
            {
                GM_SeSetMode(&work->control.mov, motion->entries[i].vy, motion->entries[i].vz);
            }

            if (motion->entries[i].pad != 0)
            {
                work->fE00[0] = motion->entries[i].pad;
            }
        }
    }
}

int Demodoll_800DDA40(int arg0)
{
    if (arg0 & 0x1)
    {
        return 2;
    }

    if (arg0 & 0x2)
    {
        return 3;
    }

    if (arg0 & 0x4)
    {
        return 4;
    }

    if (arg0 & 0x8)
    {
        return 5;
    }

    if (arg0 & 0x10)
    {
        return 6;
    }

    if (arg0 & 0x20)
    {
        return 7;
    }

    if (arg0 & 0x40)
    {
        return 8;
    }

    if (arg0 & 0x80)
    {
        return 9;
    }

    if (arg0 & 0x100)
    {
        return 10;
    }

    if (arg0 & 0x200)
    {
        return 11;
    }

    if (arg0 & 0x400)
    {
        return 12;
    }

    if (arg0 & 0x800)
    {
        return 13;
    }

    if (arg0 & 0x1000)
    {
        return 14;
    }

    return -1;
}

void Demodoll_800DDB18(DollWork *work, int arg1)
{
    int         fBFC;
    int         index;
    int         action;
    DollMotion *motion;
    int         i;

    fBFC = work->fBFC;

    index = Demodoll_800DDA40(fBFC);
    if (index > 0 && index != work->fBE0)
    {
        work->fBE0 = index;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    if ((fBFC & 0x1FFF) == 0)
    {
        work->fBE0 = 0;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction(&work->body, action, 0, 4);

        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    if (work->body.is_end != 0)
    {
        work->fBE4 = 1;
        return;
    }

    motion = &work->fC48[work->fBE0];
    for (i = 0; i < motion->index; i++)
    {
        if (motion->entries[i].vx == work->m_ctrl.info1.frame)
        {
            if (work->fE00[1] != 0)
            {
                GM_SeSetMode(&work->control.mov, motion->entries[i].vy, motion->entries[i].vz);
            }

            if (motion->entries[i].pad != 0)
            {
                work->fE00[0] = motion->entries[i].pad;
            }
        }
    }
}

void Demodoll_800DDC7C(DollWork *work, int arg1)
{
    int fBFC;
    int action;

    fBFC = work->fBFC;

    if (arg1 == 0)
    {
        work->fBE0 = 0;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }

    Demodoll_800DD6E0(work);

    if (!(fBFC & 0x1))
    {
        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else if (fBFC & 0x2)
    {
        work->fBD0 = Demodoll_800DDD14;
        work->fBD8 = 0;

        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        work->control.turn.vy = work->fE08;
    }
}

void Demodoll_800DDD14(DollWork *work, int arg1)
{
    int action;

    if (arg1 == 0)
    {
        work->fBE0 = 0;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction(&work->body, action, 0, 4);

        Demodoll_800DD75C(work);
    }

    Demodoll_800DD6E0(work);

    work->fBD0 = Demodoll_800DDC7C;
    work->fBD8 = 0;

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->control.turn.vy = work->fE08;
}

void Demodoll_800DDD84(DollWork *work)
{
    CONTROL *control;
    OBJECT  *body;
    DollFunc cb;
    int      arg;

    control = &work->control;
    body = &work->body;

    cb = work->fBD0;
    arg = work->fBD8++;

    work->fBE4 = 0;
    work->fE00[0] = 0;

    if (cb == NULL)
    {
        cb = Demodoll_800DD798;
        work->fBD0 = Demodoll_800DD798;
    }

    cb(work, arg);

    Demodoll_800DD764(work);

    if ((work->fE3E != 0) && ((GV_Time % 64) == (work->fE3E * 16)))
    {
        AN_Breath(&body->objs->objs[work->fE3C].world);
    }

    control->height = body->height;
    control->step_size = -1;

    if (work->fA78 < 0 && control->level_flag != 0)
    {
        work->fA78 = 0;
    }

    work->fA78 -= 16;
    control->step.vy = work->fA78;
}

void Demodoll_800DDEAC(DollWork *work)
{
    work->fBD0 = Demodoll_800DDB18;
    work->fBD8 = 0;

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void Demodoll_800DDEC8(DollWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;

    work->fE08 = GV_VecDir2(&diff);
    work->fE0C = GV_VecLen3(&diff);
}

void Demodoll_800DDF18(DollWork *work)
{
    Demodoll_800DDEC8(work);
    Demodoll_800DEA04(work);
    Demodoll_800DDD84(work);
}
