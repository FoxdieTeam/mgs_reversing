#include "common.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/shadow.h"
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"

typedef struct RevolverWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         field_9C;
    MOTION_CONTROL field_180;
    MOTION_SEGMENT field_1D0;
    char           pad_1F4[0x264];
    MOTION_SEGMENT field_458;
    char           pad_47C[0x264];
    SVECTOR        field_6E0;
    char           pad_6E8[0x80];
    SVECTOR        field_768;
    char           pad_770[0x30];
    SVECTOR        field_7A0;
    char           pad_7A8[0x48];
    MATRIX         field_7F0_light[2];
    GV_ACT        *shadow;
    int            field_834;
    SVECTOR        field_838[16];
    SVECTOR       *field_8B8;
    int            field_8BC;
    SVECTOR        field_8C0;
    int            field_8C8;
    int            field_8CC;
    int            field_8D0[27];
    int            field_93C;
    int            field_940;
    int            field_944;
    int            field_948;
    int            field_94C;
    int            field_950;
    int            field_954;
    int            field_958;
    int            field_95C;
    int            field_960;
    short         *field_964;
    char           pad_968[0x2];
    short          field_96A;
    short          field_96C;
    char           pad_96E[0x2];
    short         *field_970;
    int            field_974[12];
    SVECTOR        field_9A4;
    SVECTOR        field_9AC;
    short          field_9B4;
    short          field_9B6;
} RevolverWork;

#define EXEC_LEVEL 5

extern short s03b_dword_800C32E4[];
extern int   s03b_dword_800C32FC[];
extern char *s03b_dword_800C3334[];

// Array at s03b_dword_800C3334
const char s03b_aEnd_800D2F24[] = "end";
const char s03b_aV_800D2F28[] = "v26";
const char s03b_aV_800D2F2C[] = "v25";
const char s03b_aV_800D2F30[] = "v22";
const char s03b_aV_800D2F34[] = "v21";
const char s03b_aV_800D2F38[] = "v23";
const char s03b_aV_800D2F3C[] = "v20";
const char s03b_aV_800D2F40[] = "v19";
const char s03b_aV_800D2F44[] = "v18";
const char s03b_aV_800D2F48[] = "v17";
const char s03b_aV_800D2F4C[] = "v24";
const char s03b_aV_800D2F50[] = "v2";
const char s03b_aV_800D2F54[] = "v1";
const char s03b_aV_800D2F58[] = "v0";

extern int     GV_PadMask;
extern SVECTOR DG_ZeroVector;
extern int     GM_GameStatus;
extern GV_PAD  GV_PadData_800B05C0[4];

GV_ACT *NewFadeIo_800C4224(int name, int where);

// Those functions are not actually in boxall, info
// those are some helper functions (not sure if part of revolver.c)
int  s03b_boxall_800C9328(void);
int s03b_boxall_800C93AC(int arg0);
int  s03b_boxall_800C95EC(void);
int  s03b_boxall_800C95FC(void);
int  s03b_boxall_800C961C(int);
int  s03b_boxall_800C9654(int);
int  s03b_boxall_800C968C(void);
void s03b_boxall_800C969C(int, int);
void s03b_boxall_800C96E8(void);
void s03b_boxall_800C974C(void);

void s03b_800CA868(void);

int Revolver_800C8710(RevolverWork *work, int arg1);
int Revolver_800C8794(RevolverWork *, int);
int Revolver_800C884C(RevolverWork *, int);
int Revolver_800C8910(RevolverWork *, int);

void RevolverSendMessage_800C7170(int hash, short *message)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message_len = 2;
    msg.message[0] = message[1];
    msg.message[1] = message[2];

    GV_SendMessage(&msg);
}

void RevolverSendMessage_800C71B0(int hash, int message)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message_len = 2;
    msg.message[0] = 0x937A;
    msg.message[1] = message;
    GV_SendMessage(&msg);
}

int s03b_revolver_800C71E8(int hash, short *messages, int arg2)
{
    int   count;
    short mes;

    if (messages[0] < 0)
    {
        return 0;
    }

    count = 0;
    mes = messages[1];
    if (mes >= arg2)
    {
        while (1)
        {
            if (mes == arg2)
            {
                RevolverSendMessage_800C71B0(hash, messages[0]);
                messages += 2;
                count += 2;
            }

            if (messages[0] < 0 || arg2 < messages[1] || arg2 > messages[1])
            {
                break;
            }

            mes = messages[1];
        }
    }

    return count;
}

void s03b_revolver_800C72A4(RevolverWork *work, int arg1)
{
    short *messages;
    int    hash;

    messages = work->field_964;
    hash = work->control.name;

    while ((unsigned short)messages[1] != 0x385E || arg1 == 0)
    {
        if (messages[0] == arg1)
        {
            RevolverSendMessage_800C7170(hash, messages);
            work->field_964 += 4;
            work->field_960++;
        }
        else if (messages[0] < 0 && (work->field_948 & (unsigned short)messages[3]) != 0)
        {
            RevolverSendMessage_800C7170(hash, messages);
            work->field_964 += 4;
        }
        else
        {
            break;
        }

        messages = work->field_964;
    }
}

int s03b_revolver_800C7384(RevolverWork *work, int index)
{
    int entry;
    int name;

    entry = s03b_dword_800C32FC[index];

    name = GV_StrCode(s03b_dword_800C3334[index]);
    work->field_970 = GV_GetCache(GV_CacheID(name, 'l'));

    s03b_boxall_800C93AC(work->field_8D0[entry]);
    work->field_93C = work->field_8D0[entry];

    if (work->field_9C.action_flag != 0)
    {
        GM_ConfigObjectAction(&work->field_9C, 0, 0, 4);
    }

    return 0;
}

int s03b_revolver_800C742C(RevolverWork *work, int arg1, int arg2, int arg3)
{
    int temp_a1;

    if (arg1 == 0)
    {
        work->field_954 = 0;
        work->field_96C = 0;
    }

    temp_a1 = work->field_954++;
    switch (work->field_96C)
    {
    case 0:
    case 1:
        if (Revolver_800C884C(work, temp_a1))
        {
            work->field_954 = 0;
            work->field_96C++;
        }
        break;

    case 2:
        if (Revolver_800C8910(work, temp_a1))
        {
            work->field_954 = 0;
            work->field_96C++;
        }
        break;

    case 3:
        if (Revolver_800C8794(work, temp_a1))
        {
            work->field_954 = 0;
            work->field_96C++;
        }
        break;
    }

    if (arg1 == arg3 && arg2 >= 0)
    {
        printf("voice %d\n", work->field_8D0[arg2]);
        s03b_boxall_800C93AC(work->field_8D0[arg2]);
    }

    if (arg2 >= 0)
    {
        if (!s03b_boxall_800C9654(work->field_8D0[arg2]))
        {
            return 0;
        }
    }
    else if (arg1 != arg3)
    {
        return 0;
    }

    work->field_948 &= ~0x200;
    return 1;
}

void s03b_revolver_800C7574(RevolverWork *work, int arg1)
{
    short messages[4];

    int iVar5;
    int uVar7;
    int iVar4;

    int status;

    int iVar6;
    int new_var, new_var3;

    iVar5 = work->field_96A;
    uVar7 = work->field_948;
    iVar4 = work->field_950;

    status = GM_StreamStatus_80037CD8();

    if (status == -1 || status == 2)
    {
        work->field_950++;
    }

    if (work->field_950 == 0)
    {
        work->field_950 = 1;
    }

    iVar6 = work->field_958;

    if (status == 2)
    {
        work->field_958++;
    }

    if ((GV_PadData_800B05C0[2].press & PAD_CROSS) != 0)
    {
        work->field_944 = 5;

        work->field_9A4.vx = -3250;
        work->field_9A4.vy = 788;
        work->field_9A4.vz = -1125;

        work->field_94C = 0;
        work->field_9AC = DG_ZeroVector;
        work->field_9B4 = 10;
        work->field_9B6 = 1;
        return;
    }

    switch(iVar5)
    {
    case 0:
        if (iVar4 == 0)
        {
            work->field_958 = -1;
            iVar6 = work->field_958;

            s03b_boxall_800C969C(0, 60000);
            s03b_revolver_800C7384(work, 0);

            work->field_948 &= ~0x100;
            GCL_ExecProc(work->field_974[11], 0);
        }

        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[0], 0);
        }
        goto check;

    case 1:
        goto check;

    case 3:
        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[1], 0);
        }
        goto check;

    case 4:
        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[9], 0);
        }
        goto check;

    case 5:
        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[10], 0);
        }

check:
        new_var = 3;
        new_var3 = 4;
        if ((uVar7 & 0x2) != 0)
        {
            if (iVar5 == 0)
            {
                s03b_revolver_800C7384(work, 1);
            }
            else if (iVar5 == new_var)
            {
                s03b_revolver_800C7384(work, 11);
            }
            else if (iVar5 == new_var3)
            {
                s03b_revolver_800C7384(work, 12);
            }


            work->field_950 = 0;
            work->field_958 = -1;
            iVar6 = work->field_958;

            work->field_96A++;
        }

        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar6);
        break;

    case 2:
         if ((GM_TotalHours * 3600 + GM_TotalSeconds) - (GM_LastSaveHours * 3600 + GM_LastSaveSeconds) < 0
             || (GM_TotalHours * 3600 + GM_TotalSeconds) - (GM_LastSaveHours * 3600 + GM_LastSaveSeconds) > 1800)
        {
            s03b_revolver_800C7384(work, 2);
            work->field_96A = 3;
        }
        else
        {
            s03b_revolver_800C7384(work, 11);
            work->field_96A = 4;
        }

        work->field_950 = 0;
        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar6);
        break;

    case 6:
        if (Revolver_800C8710(work, iVar4))
        {
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 7:
        if (s03b_revolver_800C742C(work, iVar4, 8, 48))
        {
            NewFadeIo_800C4224(0, 16);
            s03b_boxall_800C96E8();

            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 8:
        if (iVar4 == 18)
        {
            messages[1] = GV_StrCode(s03b_aEnd_800D2F24);
            messages[2] = 0;
            RevolverSendMessage_800C7170(GV_StrCode("ch_progcam"), messages);
        }
        else if (iVar4 == 28)
        {
            messages[1] = 0x71f1;
            messages[2] = 0;
            RevolverSendMessage_800C7170(0x62fe, messages);
            work->field_948 |= 0x100;
        }
        break;

    default:
        break;
    }
}

void s03b_revolver_800C7958(RevolverWork *work, int arg1)
{
    short messages[4];
    int   iVar4;
    int   iVar3;
    int   uVar6;
    int   status;
    int   iVar5;
    int   index;

    iVar4 = work->field_96A;
    iVar3 = work->field_950;
    uVar6 = work->field_948;
    status = GM_StreamStatus_80037CD8();

    if (status == -1 || status == 2)
    {
        work->field_950++;
    }

    if (work->field_950 == 0)
    {
        work->field_950 = 1;
    }

    iVar5 = work->field_958;

    if (status == 2)
    {
        work->field_958++;
    }

    if (iVar4 > 1 && (GV_PadData_800B05C0[2].press & PAD_CROSS) != 0)
    {
        work->field_944 = 5;

        work->field_9A4.vx = -3250;
        work->field_9A4.vy = 788;
        work->field_9A4.vz = -1125;

        work->field_94C = 0;
        work->field_9AC = DG_ZeroVector;
        work->field_9B4 = 10;
        work->field_9B6 = 1;
        return;
    }

    switch(iVar4)
    {
    case 0:
        if (iVar3 == 0)
        {
            s03b_boxall_800C969C(0, 60000);
        }

        if (iVar3 == 120)
        {
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 1:
        if (iVar3 == 0)
        {
            work->field_958 = -1;
            iVar5 =  work->field_958;
            s03b_revolver_800C7384(work, 9);
            work->field_948 &= ~0x100;
        }
        goto check;

    case 2:
        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[3], 0);

            messages[1] = 0x71f1;
            messages[2] = 0;
            RevolverSendMessage_800C7170(0x62fe, messages);
        }
        goto check;

    case 3:
        if (work->field_940 > 1)
        {
            index = 3;
        }
        else
        {
            index = 4;
        }

        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[index], 0);

            if (index == 3)
            {
                messages[1] = 0x71f1;
                messages[2] = 0;
                RevolverSendMessage_800C7170(0x62fe, messages);
            }
        }

check:
        if ((uVar6 & 2) != 0)
        {
            if (iVar4 == 1)
            {
                s03b_revolver_800C7384(work, 0);
            }
            else if (iVar4 == 2)
            {
                s03b_revolver_800C7384(work, 10);
            }

            work->field_96A++;
            work->field_950 = 0;

            work->field_958 = -1;
            iVar5 = work->field_958;

            if (work->field_940 > 1 && iVar4 == 1)
            {
                work->field_96A++;
            }
        }

        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar5);
        break;

    case 4:
        if (iVar3 == 0)
        {
            GCL_ExecProc(work->field_974[5], 0);
        }

        if (Revolver_800C8710(work, iVar3))
        {
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 5:
        if (s03b_revolver_800C742C(work, iVar3, 8, 48))
        {
            NewFadeIo_800C4224(0, 16);
            s03b_boxall_800C96E8();
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 6:
        if (iVar3 == 18)
        {
            messages[1] = GV_StrCode(s03b_aEnd_800D2F24);
            messages[2] = 0;
            RevolverSendMessage_800C7170(GV_StrCode("ch_progcam"), messages);
        }
        else if (iVar3 == 28)
        {
            messages[1] = 0x71f1;
            messages[2] = 0;
            RevolverSendMessage_800C7170(0x62fe, messages);
            work->field_948 |= 0x100;
        }
        break;
    }
}

void s03b_revolver_800C7D04(RevolverWork *work, int arg1)
{
    short message[4];

    s03b_boxall_800C974C();

    if (arg1 == 0)
    {
        work->field_950 = 0;
        work->field_96A = 0;
        GM_GameStatus |= STATE_PADMASK;
        GV_PadMask = (GV_PadMask & ~0xF810) | 0x40;
    }

    if (work->field_940 == 0)
    {
        s03b_revolver_800C7574(work, arg1);
    }
    else
    {
        s03b_revolver_800C7958(work, arg1);
    }

    if (work->field_948 & 0x100)
    {
        message[1] = 4;
        message[2] = 0;
        RevolverSendMessage_800C7170(GV_StrCode("スネーク"), message);

        GM_GameStatus &= ~STATE_PADRELEASE;

        message[1] = 0x491D;
        message[2] = 1;
        RevolverSendMessage_800C7170(work->control.name, message);

        work->field_948 &= ~0x100;

        GV_PadMask = ~0x800;
        GM_GameStatus |= STATE_PADMASK;
    }
}

void Revolver_800C7E2C(RevolverWork *work, int arg1)
{
    work->control.mov = *work->field_8B8;
    if (work->field_948 & 0x200)
    {
        s03b_revolver_800C742C(work, arg1, -1, 0x80);
    }
}

void s03b_revolver_800C7E88(RevolverWork *work, int arg1)
{
    short messages[4];
    int   uVar8;
    int   uVar1;
    int   iVar7;
    int   status;
    int   iVar6;

    s03b_boxall_800C974C();

    if (arg1 == 0)
    {
        GM_GameStatus |= STATE_PADMASK;
        GV_PadMask &= ~0xf810;
        s03b_boxall_800C969C(0, 60000);
        work->field_950 = 0;
        work->field_96A = 0;
        work->field_9B6 = 0;
    }

    if ((GV_PadData_800B05C0[2].press & PAD_CROSS) != 0)
    {
        s03b_boxall_800C9328();
        GM_GameStatus |= STATE_PADRELEASE;

        if (work->field_8C8 > -1)
        {
            GCL_ExecProc(work->field_8C8, 0);
        }

        work->field_9B6 = 1;
        return;
    }

    if (work->field_9B6 == 1)
    {
        return;
    }

    uVar8 = work->field_948;
    uVar1 = work->field_96A;
    iVar7 = work->field_950;
    status = GM_StreamStatus_80037CD8();

    if (status == -1 || status == 2)
    {
        work->field_950++;
    }

    if (work->field_950 == 0)
    {
        work->field_950 = 1;
    }

    iVar6 = work->field_958;

    if (status == 2)
    {
        work->field_958++;
    }

    switch(uVar1)
    {
    case 0:
        if (Revolver_800C8710(work, iVar7))
        {
            work->control.turn.vy = 1800;
            work->field_958 = -1;
            s03b_revolver_800C7384(work, 4);
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 1:
        if ((uVar8 & 2) != 0)
        {
            if (work->field_940 < 3)
            {
                s03b_revolver_800C7384(work, work->field_940 + 5);
                work->field_950 = 0;
                work->field_96A++;
            }
            else
            {
                work->field_950 = 0;
                work->field_96A += 2;
            }

            work->field_958 = -1;
            iVar6 = work->field_958;
        }

        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar6);
        break;

    case 2:
        if (s03b_boxall_800C961C(work->field_93C))
        {
            GCL_ExecProc(work->field_974[work->field_940 + 6], 0);
        }

        if ((uVar8 & 2) != 0)
        {
            work->field_950 = 0;
            work->field_958 = -1;
            iVar6 = work->field_958;
            work->field_96A++;
            NewFadeIo_800C4224(0, 12);
        }

        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar6);
        break;

    case 3:
        if (Revolver_800C8710(work, iVar7))
        {
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 4:
        if (s03b_revolver_800C742C(work, iVar7, -1, 48))
        {
            work->field_950 = 0;
            GM_GameStatus &= ~STATE_PADRELEASE;
            work->field_96A++;
        }

        if (iVar7 == 0)
        {
            messages[1] = GV_StrCode(s03b_aEnd_800D2F24);
            messages[2] = 0;
            RevolverSendMessage_800C7170(GV_StrCode("ch_progcam"), messages);
        }
        else if (iVar7 == 8)
        {
            messages[1] = 0x71f1;
            messages[2] = 0;
            RevolverSendMessage_800C7170(0x62fe, messages);

            messages[1] = 4;
            messages[2] = 0;
            RevolverSendMessage_800C7170(GV_StrCode("スネーク"), messages);
        }
        break;
    }
}

void s03b_revolver_800C81EC(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->field_964 = s03b_dword_800C32E4;
        work->field_95C = 3;
        work->field_960 = 0;
        GM_GameStatus |= STATE_PADRELEASE;
    }

    if (work->field_960 == work->field_95C)
    {
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else
    {
        s03b_revolver_800C72A4(work, arg1);
    }
}

void s03b_revolver_800C826C(RevolverWork *work, int arg1)
{
    short messages[4];
    int   uVar1;
    int   iVar4;
    int   status;
    int   iVar2;

    s03b_boxall_800C974C();

    if (arg1 == 0)
    {
        GM_GameStatus |= STATE_PADRELEASE;
        s03b_boxall_800C969C(0, 60000);
        work->field_950 = 0;
        work->field_96A = 0;
    }

    uVar1 = work->field_96A;
    iVar4 = work->field_950;
    status = GM_StreamStatus_80037CD8();

    if (status == -1 || status == 2)
    {
        work->field_950++;
    }

    if (work->field_950 == 0)
    {
        work->field_950 = 1;
    }

    iVar2 = work->field_958;
    if (status == 2)
    {
        work->field_958++;
    }

    switch(uVar1)
    {
    case 0:
        if (Revolver_800C8710(work, iVar4))
        {
            work->field_958 = -1;
            s03b_revolver_800C7384(work, 8);
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 1:
        if (iVar4 == 254)
        {
            work->field_950 = 0;
            work->field_96A++;
        }

        work->field_970 += s03b_revolver_800C71E8(work->control.name, work->field_970, iVar2);
        break;

    case 2:
        if (s03b_revolver_800C742C(work, iVar4, -1, 48))
        {
            work->field_950 = 0;
            work->field_96A++;
        }
        break;

    case 3:
        if (GM_StreamStatus_80037CD8() == -1)
        {
            work->field_950 = 0;
            work->field_96A++;
            NewFadeIo_800C4224(0, 28);
        }
        break;

    case 4:
        if (iVar4 == 34)
        {
            messages[1] = 0x71f1;
            messages[2] = 0;
            RevolverSendMessage_800C7170(0x62fe, messages);
        }
        else if (iVar4 == 28)
        {
            messages[1] = 4;
            messages[2] = 0;
            RevolverSendMessage_800C7170(GV_StrCode("スネーク"), messages);
            s03b_boxall_800C96E8();
        }
        break;
    }
}

void Revolver_800C8488(RevolverWork *work, int mode)
{
    short message[3];
    int   field_9B4;

    if (mode == 0)
    {
        NewFadeIo_800C4224(0, 28);
        s03b_boxall_800C9328();
        s03b_boxall_800C96E8();
    }

    if (mode == 32)
    {
        message[1] = GV_StrCode(s03b_aEnd_800D2F24);
        message[2] = 0;
        RevolverSendMessage_800C7170(GV_StrCode("ch_progcam"), message);

        message[1] = 4;
        message[2] = 0;
        RevolverSendMessage_800C7170(GV_StrCode("スネーク"), message);

        message[1] = 0x491D;
        message[2] = work->field_9B6;
        RevolverSendMessage_800C7170(work->control.name, message);

        work->field_948 &= ~0x100;

        message[1] = 0x71F1;
        message[2] = 0;
        RevolverSendMessage_800C7170(0x62FE, message);

        work->control.mov = work->field_9A4;
        work->control.turn = work->field_9AC;

        field_9B4 = work->field_9B4;
        if (work->field_9C.action_flag != field_9B4)
        {
            GM_ConfigObjectAction(&work->field_9C, work->field_9B4, 0, 4);
        }

        GM_GameStatus = (GM_GameStatus & ~STATE_PADRELEASE) | STATE_PADMASK;
        GV_PadMask = ~0x800;
    }
}

void s03b_revolver_800C8600(RevolverWork *work)
{
    int iVar1;
    int uVar2;

    uVar2 = work->field_94C;
    iVar1 = s03b_boxall_800C968C();

    if (iVar1 == -1 || iVar1 == 2)
    {
        work->field_94C++;
    }

    if (work->field_94C == 0)
    {
        work->field_94C = 1;
    }

    switch(work->field_944)
    {
    case 0:
        s03b_revolver_800C7D04(work, uVar2);
        break;

    case 1:
        Revolver_800C7E2C(work, uVar2);
        break;

    case 2:
        s03b_revolver_800C7E88(work, uVar2);
        break;

    case 3:
        s03b_revolver_800C81EC(work, uVar2);
        break;

    case 4:
        s03b_revolver_800C826C(work, uVar2);
        break;

    case 5:
        Revolver_800C8488(work, uVar2);
        break;
    }
}

int Revolver_800C8710(RevolverWork *work, int arg1)
{
    if (arg1 == 0 && work->field_9C.action_flag != 12)
    {
        GM_ConfigObjectAction(&work->field_9C, 12, 0, 4);
    }
    if (work->field_9C.is_end)
    {
        work->control.turn.vy += 2048;
        work->control.rot.vy = work->control.turn.vy;
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction(&work->field_9C, 0, 0, 0);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C8794(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.turn.vy = 0;
        if (work->field_9C.action_flag != 8)
        {
            GM_ConfigObjectAction(&work->field_9C, 8, 0, 4);
        }
    }

    GV_NearExp4V(&work->control.mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 24)
    {
        GM_SeSet_80032858(&work->control.mov, 179);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C884C(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.turn.vy = 0;
        if (work->field_9C.action_flag != 9)
        {
            GM_ConfigObjectAction(&work->field_9C, 9, 0, 4);
        }
    }

    GV_NearExp4V(&work->control.mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 10 || arg1 == 44)
    {
        GM_SeSet_80032858(&work->control.mov, 180);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

int Revolver_800C8910(RevolverWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.turn.vy = 0;
        if (work->field_9C.action_flag != 10)
        {
            GM_ConfigObjectAction(&work->field_9C, 10, 0, 4);
        }
    }

    GV_NearExp4V(&work->control.mov.vx, &work->field_8B8->vx, 3);
    if (arg1 == 32)
    {
        GM_SeSet_80032858(&work->control.mov, 180);
    }

    if (work->field_9C.is_end)
    {
        if (work->field_9C.action_flag != 0)
        {
            GM_ConfigObjectAction(&work->field_9C, 0, 0, 4);
        }
        return 1;
    }

    return 0;
}

void s03b_revolver_800C89C8(RevolverWork *work)
{
    int     n_msgs;
    GV_MSG *msg;
    int     i;
    int     flag;
    int     len;
    int     code;
    int     action;

    n_msgs = work->control.field_56;
    if (n_msgs == 0)
    {
        return;
    }

    msg = &work->control.field_5C_mesg[n_msgs] - 1;
    for (i = n_msgs; i > 0; i--, msg--)
    {
        flag = 1;
        len = msg->message_len;

        if (len < 2)
        {
            continue;
        }

        code = msg->message[0];
        action = msg->message[1];

        switch (code)
        {
        case 0x937A:
            work->field_9C.action_flag = -1;

            if (action != -1)
            {
                GM_ConfigObjectAction(&work->field_9C, action, 0, 4);
            }
            break;

        case 0x4B5D:
            work->field_8B8 = &work->field_838[action];

            if (work->field_9C.action_flag != flag)
            {
                GM_ConfigObjectAction(&work->field_9C, 1, 0, 4);
            }

            work->field_948 |= 0x20;
            break;

        case 0x385E:
            s03b_boxall_800C93AC(work->field_8D0[action]);
            break;

        case 0xE2E9:
            work->control.turn.vy = action;
            break;

        case 0x491D:
            work->field_944 = action;
            work->field_94C = 0;
            break;

        case 0x4F34:
            work->field_94C = 0;
            work->field_948 |= 0x200;
            break;
        }
    }
}

void Revolver_800C8B5C(RevolverWork *work)
{
    SVECTOR svec2, svec1;

    work->field_948 &= ~0x7;
    if (work->field_9C.is_end)
    {
        work->field_948 |= 4;
    }

    if ((work->field_948 & 0x10) && s03b_boxall_800C95EC())
    {
        work->field_948 = (work->field_948 | 0x2) & ~0x10;
    }

    if (s03b_boxall_800C95FC())
    {
        GM_ConfigMotionAdjust_80035008(&work->field_9C, &work->field_768);
        work->field_948 |= 0x10;
    }

    sna_act_helper2_helper2_80033054(GV_StrCode("オセロット"), &work->field_7A0);

    if (work->field_948 & 0x20)
    {
        svec1 = work->control.mov;
        svec1.vy = 0;
        GV_SubVec3(work->field_8B8, &svec1, &svec2);
        work->control.turn.vy = GV_VecDir2(&svec2);
        if (GV_VecLen3(&svec2) < 0x80)
        {
            work->field_948 = (work->field_948 | 1) & ~0x20;
            if (work->field_9C.action_flag != 0)
            {
                GM_ConfigObjectAction(&work->field_9C, 0, 0, 4);
            }
        }
    }
}

void Revolver_800C8CA8(RevolverWork *work)
{
    s03b_800CA868();
    s03b_revolver_800C89C8(work);
    Revolver_800C8B5C(work);
    s03b_revolver_800C8600(work);
}

void RevolverAct_800C8CE4(RevolverWork *work)
{
    GM_ActMotion(&work->field_9C);
    GM_ActControl(&work->control);
    GM_ActObject(&work->field_9C);

    DG_GetLightMatrix(&work->control.mov, work->field_7F0_light);

    work->control.height = work->field_9C.field_18;

    Revolver_800C8CA8(work);

    if (work->field_8C0.vy < 0 && work->control.field_57 != 0)
    {
        work->field_8C0.vy = 0;
    }
    work->field_8C0.vy -= 32;

    work->control.step.vy += work->field_8C0.vy;
}

void RevolverDie_800C8D8C(RevolverWork *work)
{
    GV_DestroyOtherActor(work->shadow);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_9C);
    s03b_boxall_800C9328();
}

int s03b_revolver_800C8DD0(HZD_PAT *route, int *n_out, SVECTOR *out)
{
    int      n_points;
    HZD_PTP *points;

    n_points = *n_out = route->n_points;
    points = route->points;

    while (--n_points >= 0)
    {
        out->vx = points->x;
        out->vy = points->y;
        out->vz = points->z;
        out->pad = points->command;

        points++;
        out++;
    }

    return 0;
}

int Revolver_800C8E34(RevolverWork *work)
{
    HZD_PAT *routes;
    int      route_idx;
    char    *opt;

    opt = GCL_GetOption('r');
    route_idx = 0;
    if (opt)
    {
        route_idx = GCL_StrToInt(GCL_GetParamResult());
    }

    routes = work->control.map->hzd->f00_header->routes;
    routes += route_idx; // Why?

    if (s03b_revolver_800C8DD0(routes, &work->field_834, work->field_838) < 0)
    {
        return -1;
    }

    work->field_8B8 = work->field_838;
    work->field_8BC = 0;
    return 0;
}

void s03b_revolver_800C8EC0(RevolverWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (GCL_GetOption('v'))
    {
        i = 0;
        out = work->field_8D0;
        while ((res = GCL_GetParamResult()))
        {
            if (i == 27)
            {
                break;
            }

            *out++ = GCL_StrToInt(res);
            i++;
        }

        work->field_8CC = i;
    }
    else
    {
        work->field_8CC = 0;
    }
}

void s03b_revolver_800C8F4C(RevolverWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('a'))
    {
        return;
    }

    i = 0;
    out = work->field_974;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 12)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

void Revolver_800C8FC4(RevolverWork *work)
{
    work->field_964 = NULL;
    work->field_95C = 0;
    work->field_960 = 0;
}

int RevolverGetResources_800C8FD4(RevolverWork *work, int arg1, int arg2)
{
    SVECTOR  indices;
    OBJECT  *object;
    short    motion;
    CONTROL *control;

    if (GCL_GetOption('o'))
    {
        motion = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        motion = GV_StrCode("rev03bd");
    }

    if (GCL_GetOption('m'))
    {
        GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        GV_StrCode("rev_v_ct");
    }

    control = &work->control;

    if (GM_InitControl(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, control->mov.vy, -1, -1);
    control->field_59 = 2;
    GM_ConfigControlAttribute(control, 1);

    object = &work->field_9C;

    GM_InitObject(object, GV_StrCode("rev_v_ct"), BODY_FLAG2, motion);
    GM_ConfigObjectJoint(object);
    GM_ConfigMotionControl_80034F08(object, &work->field_180, motion, &work->field_1D0, &work->field_458, control,
                                    &work->field_6E0);
    GM_ConfigObjectLight(object, work->field_7F0_light);
    GM_ConfigObjectAction(object, 0, 0, 0);

    if (Revolver_800C8E34(work) < 0)
    {
        return -1;
    }

    s03b_revolver_800C8EC0(work);
    s03b_revolver_800C8F4C(work);
    Revolver_800C8FC4(work);

    work->field_8C0 = DG_ZeroVector;
    work->field_944 = 0;
    work->field_948 = 0;
    work->field_94C = 0;
    work->field_958 = -1;

    if (GCL_GetOption('e') != 0)
    {
        work->field_8C8 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_8C8 = -1;
    }

    if (GCL_GetOption('c') != 0)
    {
        work->field_940 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_940 = 0;
    }

    if (GCL_GetOption('f') && GCL_StrToInt(GCL_GetParamResult()))
    {
        work->field_948 |= 0x400;
    }

    indices.vx = 0;
    indices.vy = 7;
    indices.vz = 13;
    indices.pad = 16;

    work->shadow = NewShadow_800602CC(control, object, indices);
    if (work->shadow == NULL)
    {
        return -1;
    }

    return 0;
}

GV_ACT *NewRevolver_800C929C(int arg0, int arg1)
{
    RevolverWork *work;

    work = (RevolverWork *)GV_NewActor(EXEC_LEVEL, sizeof(RevolverWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)RevolverAct_800C8CE4, (TActorFunction)RevolverDie_800C8D8C,
                     "revolver.c");
    if (RevolverGetResources_800C8FD4(work, arg0, arg1) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return &work->actor;
}
