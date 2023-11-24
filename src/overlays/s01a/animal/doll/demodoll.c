#include "doll.h"
#include "chara/snake/sna_init.h"
#include "Game/jimctrl.h"

extern int     GV_Time_800AB330;
extern SVECTOR DG_ZeroVector_800AB39C;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern OBJECT *GM_PlayerBody_800ABA20;

extern short s01a_dword_800C3CE4[];

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

void AN_Breath_800C3AA8(MATRIX *world);

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

        work->control.field_4C_turn.vz = 0;
        work->control.field_4C_turn.vx = 0;

        return 1;
    }

    return 0;
}

void Demodoll_800DD6E0(DollWork *work)
{
    int dy;
    int ang;

    dy = GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->body.objs->objs[6].world.t[1];
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
    sna_act_helper2_helper2_80033054(work->control.field_30_scriptData, &work->adjust[work->fE3C]);
}

void Demodoll_800DD798(DollWork *work, int arg1)
{
    CONTROL *control;

    control = &work->control;

    if (arg1 == 0)
    {
        work->fBE0 = 0;
        GM_ConfigObjectAction_80034CD4(&work->body, s01a_dword_800C3CE4[0], 0, 4);
    }

    if (Demodoll_800DD6A8(work))
    {
        if (work->fC0A >= 0)
        {
            control->field_4C_turn.vy = work->fC0A;
        }
    }
    else
    {
        if (work->fC0A >= 0)
        {
            work->fBD0 = Demodoll_800DD860;
            work->fBD8 = 0;

            work->control.field_4C_turn.vz = 0;
            work->control.field_4C_turn.vx = 0;

            control->field_4C_turn.vy = work->fC0A;
        }

        work->control.field_44_step = DG_ZeroVector_800AB39C;
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
            GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
        }
        else if (work->fDFE < 0)
        {
            work->fBE0 = 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
        }
        else
        {
            work->fBE0 = work->fDFE + 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
        }
    }

    if (work->fBE0 == 1)
    {
        if (work->fDFC != 0)
        {
            work->fBE0 = work->fDFE + 1;
            action = s01a_dword_800C3CE4[work->fBE0];
            GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
        }
    }
    else if (work->fDFC == 0)
    {
        work->fBE0 = 1;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
    }

    if (saved_vy < 0)
    {
        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.field_4C_turn.vz = 0;
        work->control.field_4C_turn.vx = 0;
        return;
    }

    control->field_4C_turn.vy = saved_vy;

    motion = &work->fC48[work->fBE0];
    for (i = 0; i < motion->index; i++)
    {
        if (motion->entries[i].vx == work->m_ctrl.field_04_info1.field_2_footstepsFrame)
        {
            if (work->fE00[1] != 0)
            {
                GM_Sound_800329C4(&work->control.field_0_mov, motion->entries[i].vy, motion->entries[i].vz);
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
        GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
    }

    if ((fBFC & 0x1FFF) == 0)
    {
        work->fBE0 = 0;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);

        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.field_4C_turn.vz = 0;
        work->control.field_4C_turn.vx = 0;
    }

    if (work->body.is_end != 0)
    {
        work->fBE4 = 1;
        return;
    }

    motion = &work->fC48[work->fBE0];
    for (i = 0; i < motion->index; i++)
    {
        if (motion->entries[i].vx == work->m_ctrl.field_04_info1.field_2_footstepsFrame)
        {
            if (work->fE00[1] != 0)
            {
                GM_Sound_800329C4(&work->control.field_0_mov, motion->entries[i].vy, motion->entries[i].vz);
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
        GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);
    }

    Demodoll_800DD6E0(work);

    if (!(fBFC & 0x1))
    {
        work->fBD0 = Demodoll_800DD798;
        work->fBD8 = 0;

        work->control.field_4C_turn.vz = 0;
        work->control.field_4C_turn.vx = 0;
    }
    else if (fBFC & 0x2)
    {
        work->fBD0 = Demodoll_800DDD14;
        work->fBD8 = 0;

        work->control.field_4C_turn.vz = 0;
        work->control.field_4C_turn.vx = 0;
    }
    else
    {
        work->control.field_4C_turn.vy = work->fE08;
    }
}

void Demodoll_800DDD14(DollWork *work, int arg1)
{
    int action;

    if (arg1 == 0)
    {
        work->fBE0 = 0;
        action = s01a_dword_800C3CE4[work->fBE0];
        GM_ConfigObjectAction_80034CD4(&work->body, action, 0, 4);

        Demodoll_800DD75C(work);
    }

    Demodoll_800DD6E0(work);

    work->fBD0 = Demodoll_800DDC7C;
    work->fBD8 = 0;

    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
    work->control.field_4C_turn.vy = work->fE08;
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

    if ((work->fE3E != 0) && ((GV_Time_800AB330 % 64) == (work->fE3E * 16)))
    {
        AN_Breath_800C3AA8(&body->objs->objs[work->fE3C].world);
    }

    control->field_32_height = body->field_18;
    control->field_36 = -1;

    if (work->fA78 < 0 && control->field_57 != 0)
    {
        work->fA78 = 0;
    }

    work->fA78 -= 16;
    control->field_44_step.vy = work->fA78;
}

void Demodoll_800DDEAC(DollWork *work)
{
    work->fBD0 = Demodoll_800DDB18;
    work->fBD8 = 0;

    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
}

void Demodoll_800DDEC8(DollWork *work)
{
    SVECTOR diff;

    GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &work->control.field_0_mov, &diff);
    diff.vy = 0;

    work->fE08 = GV_VecDir2_80016EF8(&diff);
    work->fE0C = GV_VecLen3_80016D80(&diff);
}

void Demodoll_800DDF18(DollWork *work)
{
    Demodoll_800DDEC8(work);
    Demodoll_800DEA04(work);
    Demodoll_800DDD84(work);
}

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
    work->fBB4 = HZD_GetAddress_8005C6C4(work->control.field_2C_map->field_8_hzd, &work->fBA0, -1);
    work->fBB8 = work->fBAC;

    fBA6 = work->fBA0.pad;
    if ((fBA6 & 0x1F) == 0x1F)
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

int Demodoll_800DE024(DollWork *work, int size)
{
    SVECTOR diff;
    int     dx, dz;

    dx = work->fBA0.vx - work->control.field_0_mov.vx;
    diff.vx = dx;

    dz = work->fBA0.vz - work->control.field_0_mov.vz;
    diff.vz = dz;

    if ((dx > -size) && (dx < size) && (dz > -size) && (dz < size))
    {
        return 1;
    }

    work->fC0A = GV_VecDir2_80016EF8(&diff);
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

    sp18 = control->field_0_mov;
    sp18.vy = 0;

    sp20 = work->fBA0;
    sp20.vy = 0;

    dx = sp20.vx - sp18.vx;
    sp10.vx = dx;

    dz = sp20.vz - sp18.vz;
    sp10.vz = dz;

    yaw = GV_VecDir2_80016EF8(&sp10);

    size = 250;
    if ((dx > -size) && (dx < size) && (dz > -size) && (dz < size))
    {
        dist = GV_DiffVec3_80016E84(&sp18, &sp20);
        GV_AddVec3_80016D00(&sp18, &control->field_44_step, &sp28);

        if (dist < GV_DiffVec3_80016E84(&sp28, &sp18))
        {
            control->field_0_mov = work->fBA0;
            control->field_44_step = DG_ZeroVector_800AB39C;
            return 1;
        }
    }

    if (GV_DiffDirAbs_8001706C(yaw, control->field_8_rot.vy) > 64)
    {
        control->field_4C_turn.vy = yaw;
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

    if (GM_StreamStatus_80037CD8() == -1)
    {
        work->fE38++;
        GM_VoxStream_80037E40(work->fE18[work->fE38], 0);
    }
    else
    {
        GM_StreamPlayStart_80037D1C();
    }
}

void Demodoll_800DE2E8(DollWork *work, int index)
{
    int proc;

    proc = work->fE60[index];
    if (proc >= 0)
    {
        GCL_ExecProc_8001FF2C(proc, NULL);
    }
}

int Demodoll_800DE320(DollWork *work)
{
    CONTROL *control;
    GV_MSG  *msg;
    int      n_msgs;

    control = &work->control;
    control->field_56 = GV_ReceiveMessage_80016620(control->field_30_scriptData, &control->field_5C_mesg);

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
        work->fC0A = work->control.field_8_rot.vy;

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
        work->fC0A = work->control.field_8_rot.vy;

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
        work->fC0A = work->control.field_8_rot.vy;
        Demodoll_800DDF84(work);
        return 0;
    }

    if (work->fC04 == 15)
    {
        work->fC08 = 0;
        work->fC0A = work->control.field_8_rot.vy;
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
            if (GM_StreamStatus_80037CD8() == -1)
            {
                work->fC08 = 0;
                return 1;
            }

            work->fBFC |= work->fC04;
            return 0;
        }

        if ((work->fE48[work->fC0E - 1] <= jimctrl_80038688()) || (GM_StreamStatus_80037CD8() == -1))
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
                work->control.field_4C_turn.vy = work->fC0A;
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
                work->control.field_4C_turn.vy = work->fC0A;
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
                    work->control.field_4C_turn.vy = work->fC0A;
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

    if (work->fDF8 != 0 && GM_StreamStatus_80037CD8() == -1)
    {
        if (work->fE18[work->fE38 + 1] != 0)
        {
            work->fE38++;
            GM_VoxStream_80037E40(work->fE18[work->fE38], 0x40000000);
        }
    }
}
