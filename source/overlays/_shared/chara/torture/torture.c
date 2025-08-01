#include "common.h"
#include "chara/snake/sna_init.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/camera.h"
#include "game/control.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/object.h"
#include "game/over.h"
#include "game/vibrate.h"
#include "sd/g_sound.h"

struct _TortureWork;
typedef void (*TTortureFn)(struct _TortureWork *, int);

typedef struct _TortureWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT anims[34];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    char           pad[0x24];
    short          f7FC;
    short          f7FE;
    short          f800;
    short          f802;
    short          f804;
    short          f806;
    TTortureFn     f808;
    int            f80C;
    int            f810;
    int            f814;
    short          f818;
    short          f81A;
    short          f81C;
    short          f81E;
    short          f820;
    short          f822;
    SVECTOR        f824;
    SVECTOR        f82C;
    GV_PAD        *f834;
    int            f838;
    int            f83C;
    int            f840;
    int            f844;
    unsigned short f848;
    unsigned short f84A;
    unsigned short f84C;
    char           pad4[0x2];
    MENU_BAR_CONF  time_conf;
    unsigned short f85C;
    unsigned short f85E;
    unsigned short f860[2][6];
    int            f878;
    int            f87C[8];
    SVECTOR        f89C;
    short          f8A4;
    short          f8A6;
    short          f8A8;
    short          f8AA;
    SVECTOR        f8AC;
    short          f8B4;
    short          f8B6;
    int            f8B8;
    SVECTOR        f8BC[8];
    GV_ACT        *f8FC;
    GV_ACT        *f900;
} TortureWork;

extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern GM_Camera       GM_Camera_800B77E8;

extern char s03b_dword_800C329C[];
extern char s03b_dword_800C32AC[];
extern char s03b_dword_800C32B8[];
extern char s03b_dword_800C32C4[];
extern char s03b_dword_800C32D0[];
extern char s03b_dword_800C32D8[];

extern char s03b_dword_800D32F0[16];

void *NewFadeIo_800C4224(int name, int where);
void *NewPlasma_800CD1A4(OBJECT *, int, int, int, int, int);
void *NewInfo_800CA534(unsigned short name1, unsigned short name2, int *abe);
void *NewBlur_800CD530(int, int, int);

void InfoKill_800CA5D0(void);

void s03b_boxall_800C9328(void);
int s03b_boxall_800C93AC(int arg0);
void s03b_boxall_800C93F0(int, int);
void s03b_boxall_800C9404(void);
int  s03b_boxall_800C95EC(void);
int  s03b_boxall_800C9654(int);
void s03b_boxall_800C969C(int, int);
void s03b_boxall_800C96E8(void);
void s03b_boxall_800C974C(void);

void s03b_torture_800C4C48(TortureWork *work, int);
void s03b_torture_800C5AF8(TortureWork *work, int);
void s03b_torture_800C5E48(TortureWork *work, int);

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define BODY_FLAG  ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE )

void s03b_torture_800C3E80(TortureWork *work)
{
    int index;

    index = work->f80C;
    work->f80C++;
    work->f808(work, index);
}

void s03b_torture_800C3EB8(TortureWork *work)
{
    int f802;
    int index;

    f802 = work->f802;
    if (f802 & 0x2)
    {
        index = work->f810;
        work->f810++;
        s03b_torture_800C5E48(work, index);
    }
}

void s03b_torture_800C3EF8(TortureWork *work)
{
    if (work->f814 == 0)
    {
        return;
    }

    if (work->f814 > 0)
    {
        if (GM_Camera_800B77E8.first_person == 0 && --work->f814 == 0)
        {
            DG_VisibleObjs(work->body.objs);
        }
    }
    else
    {
        if (GM_Camera_800B77E8.first_person != 0 && ++work->f814 == 0)
        {
            DG_InvisibleObjs(work->body.objs);
        }
    }
}

int s03b_torture_800C3F7C(GV_PAD *pad)
{
    char *analog;
    int   i;
    char  adjust;

    if (pad->analog == 0)
    {
        return 0;
    }

    if ((pad->status & (PAD_LEFT | PAD_DOWN | PAD_RIGHT | PAD_UP)) == 0)
    {
        return 0;
    }

    analog = &pad->right_dx;
    for (i = 0; i < 4; i++)
    {
        adjust = *analog - 64;
        if (adjust > 128)
        {
            return 1;
        }

        analog++;
    }

    return 0;
}

void s03b_torture_800C3FE4(TortureWork *work)
{
    short         status;
    unsigned char ldy;
    GV_PAD       *pad;

    int  delta;
    int  f800, f802;
    char tmp1, tmp2;

    f800 = work->f800;
    if (!(f800 & 1))
    {
        work->control.turn.vy = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = work->f806;
        work->control.rot = work->control.turn;
        work->f82C = work->control.rot;
        return;
    }

    f802 = work->f802;
    if (!(f802 & 0x4000))
    {
        pad = work->f834;
        status = pad->status;
        ldy = pad->left_dy;

        GM_CheckShukanReverse(&status);
        GM_CheckShukanReverseAnalog(&ldy);

        if (pad->press & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT))
        {
            GM_SeSetMode(&work->control.mov, 186, GM_SEMODE_BOMB);
        }

        if (s03b_torture_800C3F7C(pad))
        {
            delta = work->f806;
            if (status & PAD_UP)
            {
                tmp1 = 64 - ldy;
                delta -= 10 * tmp1;
            }
            else if (status & PAD_DOWN)
            {
                tmp2 = 64 + ldy;
                delta += 10 * tmp2;
            }
            work->f82C.vx = delta;

            delta = 0;
            if (status & PAD_LEFT)
            {
                tmp1 = 64 - pad->left_dx;
                delta = tmp1 * 5;
            }
            else if (status & PAD_RIGHT)
            {
                tmp2 = 64 + pad->left_dx;
                delta = -(tmp2 * 5);
            }
            work->f82C.vy = delta;
        }
        else
        {
            delta = work->f806;
            if (status & PAD_UP)
            {
                delta -= 640;
            }
            else if (status & PAD_DOWN)
            {
                delta += 640;
            }
            work->f82C.vx = delta;

            delta = 0;
            if (status & PAD_LEFT)
            {
                delta = 320;
            }
            else if (status & PAD_RIGHT)
            {
                delta = -320;
            }
            work->f82C.vy = delta;
        }

        if (work->f82C.vx < -1000)
        {
            work->f82C.vx = -1000;
        }
    }
}

void s03b_torture_800C421C(TortureWork *work)
{
    work->f800 |= 0x1;

    if (GM_Camera_800B77E8.first_person <= 0)
    {
        GM_Camera_800B77E8.first_person = 1;
        work->f814 = -4;
    }
    else
    {
        work->f814 = -1;
    }
}

void s03b_torture_800C4260(TortureWork *work)
{
    work->f800 &= ~0x1;
    GM_Camera_800B77E8.first_person = 0;
    work->f814 = 4;
}

void s03b_torture_800C4284(TortureWork *work)
{
    int f802;
    int f800;

    f802 = work->f802;
    if ((f802 & 0x2000) || (((f802 & 0x1) == 0) && (work->f834->status & PAD_TRIANGLE)))
    {
        f800 = work->f800;
        if ((f800 & 0x1) == 0)
        {
            s03b_torture_800C421C(work);
        }
    }
    else
    {
        f800 = work->f800;
        if (f800 & 0x1)
        {
            s03b_torture_800C4260(work);
        }
    }
}

int s03b_torture_800C4314(TortureWork *work)
{
    int f800;

    f800 = work->f800;
    if ((f800 & 0x4) || (work->f834->press & PAD_SELECT) == 0)
    {
        return 0;
    }

    work->f7FC = 6;
    work->f7FE = 0;
    return 1;
}

void s03b_torture_800C435C(TortureWork *work, int vx)
{
    GV_MSG msg;
    int    f802;

    f802 = work->f802;
    if (f802 & 0x8)
    {
        msg.address = GV_StrCode("拷問台");
        msg.message_len = 2;
        msg.message[0] = GV_StrCode("turn");

        if (abs(vx) >= 2048)
        {
            msg.message[1] = work->control.rot.vx;
        }
        else
        {
            msg.message[1] = vx;
        }

        GV_SendMessage(&msg);
    }
}

void s03b_torture_800C43F0(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("拷問台");
    msg.message_len = 1;
    msg.message[0] = GV_StrCode("leave");

    GV_SendMessage(&msg);
}

void s03b_torture_800C4438(TortureWork *work, int message)
{
    GV_MSG msg;

    msg.address = GV_StrCode("リキッド");
    msg.message_len = 1;
    msg.message[0] = message;

    GV_SendMessage(&msg);
}

void s03b_torture_800C447C(TortureWork *work, int arg1, int arg2)
{
    GV_MSG msg;

    msg.address = GV_StrCode("オセロット");
    msg.message_len = 2;
    msg.message[0] = arg1;
    msg.message[1] = arg2;

    GV_SendMessage(&msg);
}

void s03b_torture_800C44D0(TortureWork *work, int arg1, int arg2)
{
    int max, now;

    max = work->f860[0][work->f85C];

    if (arg2 < 0)
    {
        now = arg1 * 4;

        if (now > max)
        {
            now = max;
        }

        max = now;
    }
    else if (arg2 == 0)
    {
        now = max - arg1;

        if (max == now)
        {
            now = max - 1;
        }
    }
    else
    {
        now = 0;
    }

    max *= 5;
    now *= 5;

    if (max > 1024)
    {
        work->time_conf.right[1] = (0x10000 / max) + 63;
        work->time_conf.right[2] = (0xFC00 / max) - 64;
    }

    MENU_DrawBar2(28, now, now, max, &work->time_conf);
}

int s03b_torture_800C45E4(TortureWork *work)
{
    MENU_BAR_CONF *conf;

    memcpy(s03b_dword_800D32F0, "Time", 5);

    conf = &work->time_conf;
    conf->name = s03b_dword_800D32F0;
    // Set the left and right RGB values for the torture time bar gradient
    conf->left[0] = 31;
    conf->left[1] = 63;
    conf->left[2] = 192;

    conf->right[0] = 31;
    conf->right[1] = 127;
    conf->right[2] = 255;

    conf->height = 1;
    return 0;
}

void s03b_torture_800C4654(TortureWork *work)
{
    int     n_msgs;
    GV_MSG *msg;

    if (work->control.field_56 == 0)
    {
        return;
    }

    n_msgs = work->control.field_56;
    msg = &work->control.field_5C_mesg[n_msgs] - 1;

    for (; n_msgs > 0; n_msgs--, msg--)
    {
        if (msg->message[0] == 4)
        {
            work->f802 |= 0x4;
        }
    }
}

void s03b_torture_800C46B8(TortureWork *work, int arg1)
{
    if (arg1 == 0)
    {
        NewFadeIo_800C4224(0, 28);
        s03b_boxall_800C9328();

        work->f820 = 0;

        if (work->f8FC != NULL)
        {
            GV_DestroyOtherActor(work->f8FC);
        }

        work->f8FC = NULL;
    }

    if (arg1 == 32)
    {
        GM_Camera_800B77E8.first_person = 0;

        if (work->f83C >= 0)
        {
            GCL_ExecProc(work->f83C, NULL);
        }
    }
}

// TODO: This is wrong.
// All other accesses to f802 are doing weird things (lh vs lhu),
// but we have been working around it by assigning them to ints.
static inline char s03b_torture_helper_800C4740(TortureWork *work)
{
    return LLOAD(&work->f802) >> 8;
}

void s03b_torture_800C4740(TortureWork *work)
{
    int status;
    int vox_stream;
    int f802;

    s03b_boxall_800C974C();

    if (GV_PadData[2].press & PAD_CROSS)
    {
        work->f808 = s03b_torture_800C46B8;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        return;
    }

    switch(work->f818)
    {
    case 0:
        if (work->f81A == 0)
        {
            s03b_boxall_800C969C(1, 60000);
        }

        if (work->f8FC == 0)
        {
            work->f8FC = NewBlur_800CD530(1, 0, 0);
        }

        if (++work->f81A == 200)
        {
            work->f81A = 0;
            work->f818++;
        }
        break;

    case 1:
        s03b_boxall_800C93AC(work->f87C[work->f820 + 3]);
        work->f818 = 2;
        work->f820++;
        break;

    case 2:
        if (s03b_boxall_800C95EC())
        {
            if (work->f820 == 4)
            {
                s03b_boxall_800C96E8();
                work->f802 |= 0x4;
            }
            else
            {
                work->f818 = 3;
            }
        }
        break;

    case 3:
        if ((work->f802 & 0x700) != 0x700)
        {
            work->f81A = 150;
            work->f818 = 4;
        }
        else
        {
            s03b_torture_800C4438(work, work->f820 - 1);
            work->f81A = 0;
            work->f818 = 1;
        }
        break;

    case 4:
        if (work->f81A-- == 1)
        {
            work->f818 = 1;
            s03b_torture_800C4438(work, work->f820 - 1);
            break;
        }

        status = work->f834->status;
        if (status == 0)
        {
            break;
        }

        vox_stream = -1;
        if ((status & 0xf000) != 0 && (f802 = work->f802, (s03b_torture_helper_800C4740(work) & 0x1) == 0))
        {
            work->f802 |= 0x100;
            vox_stream = work->f87C[2];
        }
        else if ((status & 0xf) != 0 && (f802 = work->f802, (f802 & 0x200) == 0))
        {
            work->f802 |= 0x200;
            vox_stream = work->f87C[0];
        }
        else if ((status & 0xe0) != 0 && (f802 = work->f802, (f802 & 0x400) == 0))
        {
            work->f802 |= 0x400;
            vox_stream = work->f87C[1];
        }

        if (vox_stream >= 0)
        {
            s03b_boxall_800C93AC(vox_stream);
            work->f818 = 5;
        }
        break;

    case 5:
        if (s03b_boxall_800C95EC())
        {
            work->f81A -= 200;
            if (work->f81A < 1)
            {
                s03b_torture_800C4438(work, work->f820 - 1);
                work->f81A = 0;
                work->f818 = 1;
            }
            else
            {
                work->f818 = 4;
            }
        }
        break;
    }
}

void s03b_torture_800C4A08(TortureWork *work)
{
    if (work->f848 == 0)
    {
        s03b_torture_800C4740(work);
    }
    else if (++work->f81A == 90)
    {
        work->f802 |= 0x4;
    }
}

void s03b_torture_800C4A70(TortureWork *work)
{
    s03b_torture_800C4654(work);
}

void s03b_torture_800C4A90(TortureWork *work)
{
    s03b_torture_800C4A70(work);
}

void s03b_torture_800C4AB0(TortureWork *work, int arg1)
{
    OBJECT *body;
    int     i;
    int     rnd;

    if (arg1 == 0)
    {
        body = &work->body;
        GM_ConfigMotionAdjust(body, work->adjust);

        GM_GameStatus |= STATE_PADRELEASE;

        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->f87C[2], 4);
        GM_SetSound(0xff0000fe, SD_ASYNC);
        s03b_boxall_800C969C(0, 10000);

        if (work->body.action != 2)
        {
            GM_ConfigObjectAction(body, 2, 0, 4);
        }
    }

    if (s03b_boxall_800C9654(work->f87C[2]))
    {
        work->f808 = s03b_torture_800C4C48;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
    }

    if (work->body.is_end != 0 && work->body.action == 2)
    {
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }

    if ((work->f800 & 0x2) != 0 && (arg1 & 0xF) == 0)
    {
        for (i = 0; i < work->f8B8; i++)
        {
            rnd = GV_RandU(64) % 15;
            NewPlasma_800CD1A4(&work->body, rnd, rnd + 1, 16, 0, 1000);
        }
    }
}

void s03b_torture_800C4C48(TortureWork *work, int arg1)
{
    GCL_ARGS args;
    long     data[1];

    if (arg1 == 0)
    {
        s03b_torture_800C447C(work, GV_StrCode("mode"), 4);

        args.argc = 1;
        args.argv = data;
        data[0] = 0;
        GCL_ExecProc(work->f840, &args);
    }

    s03b_torture_800C4654(work);

    if (arg1 == 300)
    {
        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 15);
        }

        args.argc = 1;
        args.argv = data;
        data[0] = 11;
        GCL_ExecProc(work->f840, &args);
    }

    if (arg1 >= 330)
    {
        if (arg1 == 330)
        {
            work->f802 |= 0x8;
            NewPadVibration(s03b_dword_800C32B8, 1);
            NewPadVibration(s03b_dword_800C32C4, 2);
            GM_SeSet(&work->control.mov, 176);
        }

        work->control.turn.vx = (arg1 - 330) * -7;
        if (work->control.turn.vx < -760)
        {
            if (work->f818 == 0)
            {
                work->f818 = 1;
            }

            work->control.turn.vx = -760;
        }

        work->f806 = work->control.turn.vx;
        work->f82C.vx = work->f806;
    }

    if (arg1 == 420)
    {
        GM_Camera_800B77E8.first_person = 2;
        work->f802 |= 0x6000;
    }

    if (arg1 == 490)
    {
        GM_SeSet2(0, 63, 182);
    }
}

void s03b_torture_800C4DF0(TortureWork *work, int arg1)
{
    if (arg1 == 0)
    {
        NewFadeIo_800C4224(1, 128);

        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 1);
        }

        work->f806 = -760;
        work->control.rot.vx = -760;
        work->control.turn.vx = -760;
        work->f802 |= 0x2000;
    }

    s03b_torture_800C4A08(work);
}

void s03b_torture_800C4E64(TortureWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->f802 |= 0x2000;

        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 4);
        }

        NewPadVibration(s03b_dword_800C32B8, 1);
        NewPadVibration(s03b_dword_800C32C4, 2);

        GM_SeSet(&work->control.mov, 176);

        GM_GameStatus |= STATE_NOSLOW;
    }

    work->f806 = (arg1 * 7) - 760;
    if (work->f806 > 0)
    {
        if (work->f818 == 0)
        {
            work->f818 = 1;

            if (work->f848 != 0)
            {
                NewFadeIo_800C4224(0, 28);
            }
        }

        work->f806 = 0;
    }

    work->control.turn.vx = work->f806;
}

void s03b_torture_800C4F54(TortureWork *work, int arg1)
{
    if (arg1 == 0)
    {
        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 4);
        }

        NewPadVibration(s03b_dword_800C32B8, 1);
        NewPadVibration(s03b_dword_800C32C4, 2);

        GM_SeSet(&work->control.mov, 176);
    }

    work->f806 = arg1 * -7;
    if (work->f806 < -760)
    {
        if (work->f818 == 0)
        {
            work->f818 = 1;
        }

        work->f806 = -760;
    }

    work->control.turn.vx = work->f806;

    if (arg1 == 90)
    {
        work->f802 |= 0x2000;
        GM_Camera_800B77E8.first_person = 2;
    }

    if (arg1 == 200)
    {
        work->f900 = NewFadeIo_800C4224(0, 32);
    }

    if (arg1 == 160)
    {
        GM_GameStatus |= STATE_PADRELEASE;
        GM_SeSet2(0, 63, 182);
    }

    if (arg1 == 250)
    {
        work->f802 |= 0x4;
    }
}

void s03b_torture_800C50A8(TortureWork *work, int arg1)
{
    GV_MSG   msg;
    CONTROL *control;
    int      which;
    int      dir;

    if (arg1 == 0)
    {
        control = &work->control;

        GM_GameStatus |= STATE_PADRELEASE;

        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 4);
        }

        GM_Camera_800B77E8.first_person = 2;
        work->f802 |= 0x6000;

        GM_ConfigControlHazard(control, control->mov.vy, -2, -2);

        control->mov.vx = -2000;
        control->mov.vy = 450;
        control->mov.vz = -1000;

        control->step = DG_ZeroVector;

        control->turn.vx = 320;
        control->rot.vx = 320;

        control->turn.vz = 0;
        control->rot.vz = 0;

        control->turn.vy = 2048;
        control->rot.vy = 2048;

        s03b_torture_800C447C(work, GV_StrCode("mode"), 3);

        work->f820 = 0xB7;
        work->f802 |= 0x8;

        s03b_torture_800C435C(work, -1023);

        work->f802 &= ~0x8;
        work->f82C = control->rot;
    }

    if (arg1 == 1)
    {
        msg.address = 0x62FE;
        msg.message_len = arg1;
        msg.message[0] = 0x71F1;
        GV_SendMessage(&msg);

        work->f802 &= ~0x8;
    }

    which = work->f818 & 0x1;

    if (work->f818 == 10)
    {
        NewFadeIo_800C4224(0, 64);
    }

    if (work->f818 == 12)
    {
        work->f802 |= 0x4;
        return;
    }

    switch (which)
    {
    case 0:
        if (work->f81A == 0)
        {
            if (work->f820 == 183)
            {
                NewPadVibration(s03b_dword_800C329C, 1);
                NewPadVibration(s03b_dword_800C32AC, 2);
            }

            GM_SeSet(&work->control.mov, work->f820);

            if (++work->f820 == 186)
            {
                work->f820 = 183;
            }
        }

        work->control.step.vz = 32;

        dir = (GV_Clock != 0) ? -1 : 1;
        gUnkCameraStruct_800B77B8.eye.vy += dir * GV_RandU(8);

    case 1:
        if (++work->f81A == 16)
        {
            work->f81A = 0;
            work->f818++;
        }
        break;
    }

    if (arg1 > 60 && work->f82C.vx > 0)
    {
        work->f82C.vx -= 6;
    }

    if (arg1 > 148)
    {
        GM_Camera_800B77E8.zoom -= 6;
    }
}

void s03b_torture_800C53C8(TortureWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->f802 &= ~0x2000;

        if (work->body.action != 0)
        {
            GM_ConfigObjectAction(&work->body, 0, 0, 4);
        }

        work->f806 = 0;
    }

    s03b_torture_800C4A90(work);
}

void s03b_torture_800C5CC8(TortureWork *work, int arg1);
void s03b_torture_800C59FC(TortureWork *work, int arg1);

void s03b_torture_800C5420(TortureWork *work, int arg1)
{
    int abe[2];
    int var_v1;
    int temp_a0;
    int randval;
    int temp_s2;
    int var_a1;
    int action;
    int var_s0;
    int var_v0_2;
    int tmp;

    if (arg1 == 0)
    {
        work->f806 = 0;
        work->f802 &= ~0x2000;

        s03b_torture_800C447C(work, HASH_MOTION, 9);

        work->f8AC = work->f89C;
        work->f8AC.vz = 0;

        GCL_ExecProc(work->f844, NULL);

        GM_CameraSetTrack_80030980(work->f89C.vz);
        GM_CameraSetRotation_80030938(&work->f8AC);

        gUnkCameraStruct_800B77B8.eye.vx = work->body.objs->objs[6].world.t[0];
        gUnkCameraStruct_800B77B8.eye.vy = work->body.objs->objs[6].world.t[1];
        gUnkCameraStruct_800B77B8.eye.vz = work->body.objs->objs[6].world.t[2];

        sub_8003081C();

        work->f81C = 0;
    }

    temp_s2 = work->f85C == 0 ? 32 : 0;

    if (arg1 == temp_s2 + 32)
    {
        if (work->f85C == 0)
        {
            abe[0] = 1;
            abe[1] = 0;
            NewInfo_800CA534(GV_StrCode("gou_bg"), GV_StrCode("goumon"), abe);
        }
        GM_SeSet2(0, 0x3F, 0xB4);
    }
    else if (arg1 == temp_s2 + 42 || arg1 == temp_s2 + 64)
    {
        GM_SeSet2(0, 0x3F, 0xB4);
    }

    if (arg1 == temp_s2 + 108)
    {
        GM_SeSet2(0, 0x3F, 0xB2);
    }

    var_v0_2 = arg1 - 136;
    var_a1 = var_v0_2 - temp_s2;
    if (var_a1 < 0)
    {
        s03b_torture_800C44D0(work, arg1, -1);
    }
    else
    {
        s03b_torture_800C44D0(work, var_a1, 0);
    }

    if (arg1 >= temp_s2 + 136)
    {
        work->f800 |= 2;

        if (!(arg1 & 0xF))
        {
            for (var_s0 = 0; var_s0 < work->f8B8; var_s0++)
            {
                randval = GV_RandU(64) % 15;
                NewPlasma_800CD1A4(&work->body, randval, randval + 1, 16, 0, 1000);
            }
        }

        if (arg1 == temp_s2 + 136)
        {
            work->f84C = work->f860[0][work->f85C] + 64;
            work->f802 |= 2;
            GM_SeSet(&work->control.mov, 128);

            work->control.mov = work->f824;

            if (GV_Clock)
            {
                action = 1;
            }
            else
            {
                action = 7;
            }

            if (work->body.action != action)
            {
                GM_ConfigObjectAction(&work->body, action, 0, 4);
            }
        }

        temp_a0 = temp_s2 + 136;
        if (arg1 - temp_a0 == (arg1 - temp_a0) / 30 * 30)
        {
            work->f804 -= work->f860[1][work->f85C];
        }

        if (arg1 == temp_s2 + 136 + work->f860[0][work->f85C])
        {
            GM_SetSound(0xff0000fe, SD_ASYNC);
            work->f800 = (unsigned short)work->f800 & ~0x2;
            if (work->f804 <= 0)
            {
                work->f810 = 0;
                work->f808 = s03b_torture_800C5CC8;
                work->f81A = 0;
                work->f818 = 0;
                work->f80C = 0;
                work->f802 = (unsigned short)work->f802 & ~0x2;
                return;
            }
            work->f808 = s03b_torture_800C59FC;
            work->f81A = 0;
            work->f818 = 0;
            work->f80C = 0;
            return;
        }
        GM_PadVibration2 = GV_RandU(64) + 192;
        if (work->f81A == 0)
        {
            GM_SeSet2(0, 0x3F, 177);
            work->f81A = (GV_RandU(4096) % 11) + 2;
        }
        else
        {
            work->f81A--;
        }

        switch (work->f818)
        {
        case 0:
            tmp = (work->f8A6 - work->f89C.vy) / work->f8B6;
            var_v1 = work->f8AC.vy + tmp;
            if (var_v1 > work->f8A6)
            {
                var_v1 = work->f8A6;
                work->f818++;
            }
            work->f8AC.vy = var_v1;
            break;
        case 1:
            if (++work->f81C == 32)
            {
                work->f81C = 0;
                work->f818++;
            }
            break;
        case 2:
            tmp = (work->f89C.vy - work->f8A6) / work->f8B6;
            var_v1 = work->f8AC.vy + tmp;
            if (work->f89C.vy > var_v1)
            {
                var_v1 = work->f89C.vy;
                work->f818++;
            }

            work->f8AC.vy = var_v1;
            break;
        case 3:
            if (++work->f81C == 32)
            {
                work->f818 = 0;
                work->f81C = 0;
            }
            break;
        }
        GM_CameraSetRotation_80030938(&work->f8AC);
        if (work->body.is_end != 0)
        {
            work->control.mov = work->f824;
        }
    }
}

void s03b_torture_800C59FC(TortureWork *work, int arg1)
{
    char pad[0x20];

    int f85E;

    if (arg1 == 0)
    {
        s03b_torture_800C447C(work, HASH_MOTION, 7);

        if (work->body.action != 2)
        {
            GM_ConfigObjectAction(&work->body, 2, 0, 4);
        }

        GM_SeSet(&work->control.mov, 181);
    }

    s03b_torture_800C44D0(work, 0, 1);

    if (arg1 < 8)
    {
        GV_NearExp4V((short *)&work->control.mov, (short *)&work->f824, 3);
    }

    if (work->body.is_end != 0)
    {
        work->f85C++;

        if (work->f85C > 0)
        {
            // Identical cases
            f85E = work->f85E;
            if (work->f85C != f85E)
            {
                s03b_torture_800C447C(work, HASH_MOTION, 7);
                s03b_torture_800C447C(work, HASH_VOICE, work->f85C + 2);
            }
        }
        else
        {
            // Identical cases
            f85E = work->f85E;
            if (work->f85C != f85E)
            {
                s03b_torture_800C447C(work, HASH_MOTION, 7);
                s03b_torture_800C447C(work, HASH_VOICE, work->f85C + 2);
            }
        }

        work->f808 = s03b_torture_800C5AF8;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
    }
}

void s03b_torture_800C5AF8(TortureWork *work, int arg1)
{
    GCL_ARGS args;
    long     data;
    int      f85E;
    int      f802;
    int      f81A;

    f85E = work->f85E;
    if (arg1 == 0)
    {
        if (work->body.action != 6)
        {
            GM_ConfigObjectAction(&work->body, 6, 0, 15);
        }

        work->f806 = 0;

        if (work->f840 >= 0)
        {
            args.argc = 1;
            args.argv = &data;

            if (work->f85C == f85E)
            {
                data = 0;
            }
            else
            {
                data = work->f85C;
            }

            GCL_ExecProc(work->f840, &args);
        }
    }

    if (work->f85C != f85E)
    {
        if (work->f818 == 0)
        {
            f802 = work->f802;
            if ((f802 & 0x2) == 0)
            {
                f81A = work->f81A;
                if (f81A == 1)
                {
                    GV_RandU(16);

                    s03b_torture_800C447C(work, HASH_OPERATION, 0);
                    s03b_torture_800C447C(work, HASH_VOICE, work->f85C + 8);

                    work->f818 = f81A;
                }
            }
        }

        if (s03b_boxall_800C95EC())
        {
            work->f81A++;
        }

        if (work->f81A == 2)
        {
            work->f808 = s03b_torture_800C5420;
            work->f81A = 0;
            work->f818 = 0;
            work->f80C = 0;
        }
    }
    else if (work->f818 == 0)
    {
        f802 = work->f802;
        if ((f802 & 0x2) == 0)
        {
            work->f800 |= 0x4;

            GM_GameStatus |= STATE_LIFEBAR_OFF;
            InfoKill_800CA5D0();

            s03b_torture_800C447C(work, HASH_MODE, 2);

            work->f818 = 1;
        }

        if (work->f818 != 0)
        {
            s03b_torture_800C4654(work);
        }
    }
    else
    {
        s03b_torture_800C4654(work);
    }
}

void s03b_torture_800C5CC8(TortureWork *work, int arg1)
{
    char pad[32];

    if (arg1 == 0)
    {
        NewPadVibration(s03b_dword_800C32D0, 1);
        NewPadVibration(s03b_dword_800C32D8, 2);

        GM_GameStatus |= STATE_PADRELEASE;
        GM_SeSet2(0, 63, SE_PLAYEROUT);

        if (work->body.action != 4)
        {
            GM_ConfigObjectAction(&work->body, 4, 0, 4);
        }

        work->f802 |= 0x10;
    }

    if (arg1 < 8)
    {
        GV_NearExp4V((short *)&work->control.mov, (short *)&work->f824, 3);
    }

    switch (work->f818)
    {
    case 0:
        if (work->body.is_end != 0)
        {
            work->f818++;

            if (work->body.action != 5)
            {
                GM_ConfigObjectAction(&work->body, 5, 0, 4);
            }
        }
        break;

    case 1:
        if (++work->f81A == 32)
        {
            work->f818++;

            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_CallSystemCallbackProc(0, 0);

            GM_GameStatus |= STATE_MENU_OFF | STATE_PAUSE_OFF | STATE_RADIO_OFF;
            NewGameOver(FALSE);
        }
        break;
    }
}

void s03b_torture_800C5E48(TortureWork *work, int arg1)
{
    if (work->f834->press & PAD_CIRCLE)
    {
        work->f804 += work->f84A;
    }

    if (work->f804 > GM_SnakeMaxHealth)
    {
        work->f804 = GM_SnakeMaxHealth;
    }

    if (arg1 == work->f84C)
    {
        work->f810 = 0;
        work->f802 &= ~0x2;
    }
}

void s03b_torture_800C5EC4(TortureWork *work)
{
    GV_MSG *msg;
    int     i;
    int     n_msgs;
    int     f802;

    f802 = work->f802;
    if (f802 & 0x40)
    {
        return;
    }

    if (work->control.field_56 == 0)
    {
        return;
    }

    n_msgs = work->control.field_56;
    msg = &work->control.field_5C_mesg[n_msgs] - 1;

    for (; n_msgs > 0; n_msgs--, msg--)
    {
        switch (msg->message[0])
        {
        case 0xE530:
            work->f85C = 0;
            work->f85E = msg->message[1];
            work->f802 |= 0x40;
            break;
        case 0xF999:
            for (i = 1; i < msg->message_len; i++)
            {
                work->f860[0][i - 1] = msg->message[i];
            }
            work->f802 |= 0x40;
            break;
        case 0xE314:
            for (i = 1; i < msg->message_len; i++)
            {
                work->f860[1][i - 1] = msg->message[i];
            }
            work->f802 |= 0x40;
            break;
        case 0xFE25:
            work->f84A = msg->message[1];
            work->f802 |= 0x40;
            break;
        }
    }
}

void s03b_torture_800C6024(TortureWork *work)
{
    int f802;

    if (work->f7FE == 0)
    {
        work->f808 = s03b_torture_800C4DF0;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        work->f802 |= 0x8;
    }

    f802 = work->f802;
    if (f802 & 0x4)
    {
        work->f802 &= ~0x4;
        work->f7FC = 1;
        work->f7FE = 0;
    }
}

void s03b_torture_800C6080(TortureWork *work)
{
    int comp;

    if (work->f7FE < 2)
    {
        if (work->f8FC)
        {
            GV_DestroyOtherActor(work->f8FC);
            work->f8FC = NULL;
        }

        work->f808 = s03b_torture_800C4E64;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        work->f802 |= 0x8;
    }

    if (work->f848 == 0 && work->f7FE == 120)
    {
        NewFadeIo_800C4224(0, 28);
    }

    comp = (work->f848 == 0) ? 150 : 180;
    if (work->f7FE == comp)
    {
        if (work->f848 == 0 && work->f83C >= 0)
        {
            GM_Camera_800B77E8.first_person = 0;
            GCL_ExecProc(work->f83C, NULL);
            GV_DestroyActor(&work->actor);
            GM_GameStatus &= ~STATE_NOSLOW;
        }
        else
        {
            work->f7FC = 2;
            work->f7FE = 0;
            work->f802 &= ~0x8;
        }
    }
}

void s03b_torture_800C61A4(TortureWork *work)
{
    int f802;

    if (work->f7FE < 2)
    {
        work->f808 = s03b_torture_800C4F54;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        work->f802 |= 0x8;
    }

    f802 = work->f802;
    if (f802 & 4)
    {
        work->f802 &= ~0xC;
        work->f7FC = 7;
        work->f7FE = 0;
    }
}

void s03b_torture_800C6204(TortureWork *work)
{
    int f802;

    if (work->f7FE < 2)
    {
        s03b_torture_800C43F0();
        work->f808 = s03b_torture_800C50A8;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        GM_GameStatus |= STATE_NOSLOW;
    }

    f802 = work->f802;
    if (f802 & 0x4)
    {
        work->f802 &= ~0x4;

        GM_GameStatus &= ~STATE_NOSLOW;
        GM_GameStatus &= ~STATE_PADRELEASE;

        if (work->f83C >= 0)
        {
            GCL_ExecProc(work->f83C, NULL);
            GV_DestroyActor(&work->actor);
        }
    }
}

void s03b_torture_800C62C4(TortureWork *work)
{
    int f802;

    if (work->f7FE < 2)
    {
        work->f808 = s03b_torture_800C53C8;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        GM_GameStatus |= STATE_NOSLOW;
    }

    if (work->f7FE == 0x1E)
    {
        s03b_torture_800C4260(work);
    }

    f802 = work->f802;
    if (f802 & 0x4)
    {
        work->f802 &= ~0x4;
        work->f7FC = 3;
        work->f7FE = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
        GM_GameStatus &= ~STATE_NOSLOW;
    }
}

void Torture_800C6380(TortureWork *work)
{
    int f802;

    if (work->f7FE < 2)
    {
        work->f808 = s03b_torture_800C5420;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
    }

    if (!s03b_torture_800C4314(work))
    {
        f802 = work->f802;
        if (f802 & 0x4)
        {
            work->f802 &= ~0x4;
            work->f820 = 0;
            work->f7FC = 5;
            work->f7FE = 0;
        }
    }
}

void Torture_800C6400(TortureWork *work)
{
    int f802;

    if (work->f7FE < 2)
    {
        InfoKill_800CA5D0();
        work->f808 = s03b_torture_800C4AB0;
        work->f81A = 0;
        work->f818 = 0;
        work->f80C = 0;
        GM_GameStatus |= STATE_PADRELEASE | STATE_LIFEBAR_OFF;
        work->f802 |= 0x8;
    }

    f802 = work->f802;
    if (f802 & 0x4)
    {
        work->f7FC = 7;
        work->f7FE = 0;
        work->f83C = work->f838;
        work->f802 &= ~0xC;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
}

void Torture_800C64BC(TortureWork *work)
{
    s03b_torture_800C5EC4(work);

    switch (work->f7FC)
    {
    case 0:
        s03b_torture_800C6024(work);
        break;

    case 1:
        s03b_torture_800C6080(work);
        break;

    case 2:
        s03b_torture_800C62C4(work);
        break;

    case 3:
        Torture_800C6380(work);

        if (work->f7FC == 6)
        {
            work->f7FE = 1;
            work->f802 &= ~0x4;
            goto next;
        }
        break;

    case 4:
        break;

    case 5:
        s03b_torture_800C61A4(work);
        break;

    case 6:
    next:
        Torture_800C6400(work);
        break;

    case 7:
        s03b_torture_800C6204(work);
        break;
    }

    if (work->f7FE < 16000)
    {
        work->f7FE++;
    }

    s03b_boxall_800C9404();

    sna_act_helper2_helper2_80033054(GV_StrCode("スネーク"), &work->adjust[6]);

    s03b_torture_800C435C(work, 4000);
    s03b_torture_800C3EF8(work);
    s03b_torture_800C3E80(work);
    s03b_torture_800C3EB8(work);
    s03b_torture_800C4284(work);
    s03b_torture_800C3FE4(work);
}

void TortureAct_800C6600(TortureWork *work)
{
    UnkCameraStruct *cam;
    int              f800;

    GV_PadMask &= ~0x800;
    GM_GameStatus |= STATE_PADMASK;

    GM_ActMotion(&work->body);

    work->control.mov.vy += work->body.height - work->control.height;

    GM_ActControl(&work->control);
    GM_ActObject(&work->body);

    DG_GetLightMatrix(&work->control.mov, work->light);

    GM_PlayerPosition = work->control.mov;

    cam = &gUnkCameraStruct_800B77B8;
    cam->eye.vx = work->body.objs->objs[6].world.t[0];
    cam->eye.vy = work->body.objs->objs[6].world.t[1];
    cam->eye.vz = work->body.objs->objs[6].world.t[2];

    GM_SnakeCurrentHealth = (work->f804 > 0) ? work->f804 : 0;

    work->control.height = work->body.height;

    Torture_800C64BC(work);

    f800 = work->f800;
    if (f800 & 0x1)
    {
        GV_NearExp2PV((short *)&cam->rotate2, (short *)&work->f82C, 3);
    }
    else
    {
        cam->rotate2 = work->control.rot;
    }
}

void TortureDie_800C6774(TortureWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);

    GM_PlayerStatus &= ~PLAYER_MENU_DISABLE;

    s03b_boxall_800C96E8();
    s03b_boxall_800C9328();

    GM_SnakeCurrentHealth = GM_SnakeMaxHealth;

    if (GM_PlayerControl == &work->control)
    {
        GM_PlayerControl = NULL;
    }

    if (GM_PlayerBody == &work->body)
    {
        GM_PlayerBody = NULL;
    }
}

void Torture_800C6814(TortureWork *work)
{
    int   params[7];
    int  *iter;
    char *res;

    if (!GCL_GetOption('b'))
    {
        return;
    }

    iter = params;
    while ((res = GCL_GetParamResult()))
    {
        *iter++ = GCL_StrToInt(res);
    }

    work->f89C.vx = params[1];
    work->f89C.vy = params[2];
    work->f89C.vz = params[0];
    work->f8A4 = params[3];
    work->f8A6 = params[4];
    work->f8B4 = params[5];
    work->f8B6 = params[6];

    if (GCL_GetOption('z'))
    {
        work->f844 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f844 = -1;
    }
}

void Torture_800C68E8(TortureWork *work)
{
    int      count;
    SVECTOR *iter;

    if (!GCL_GetOption('x'))
    {
        return;
    }

    count = 0;
    iter = work->f8BC;
    while (GCL_GetParamResult())
    {
        GCL_StrToSV(GCL_GetParamResult(), iter);
        iter++;
        count++;
    }

    work->f8B8 = count;
}

void Torture_800C695C(TortureWork *work)
{
    char *opt;

    work->f7FE = 0;
    work->f800 = 0;
    work->f802 = 0;
    work->f804 = GM_SnakeMaxHealth;
    work->f810 = 0;
    work->f814 = 0;
    work->f81A = 0;
    work->f818 = 0;
    work->f822 = 0;
    work->f820 = 0;
    work->f824 = work->control.mov;
    work->f834 = &GV_PadData[2];
    work->f82C = work->control.rot;
    work->f8FC = NULL;
    work->f900 = NULL;

    opt = GCL_GetOption('m');
    if (opt != NULL)
    {
        work->f7FC = GCL_StrToInt(opt);
    }
    else
    {
        work->f7FC = 0;
    }

    if (work->f7FC < 2)
    {
        GM_Camera_800B77E8.first_person = 2;
        work->f802 |= 0x2000;
    }
    else
    {
        GM_Camera_800B77E8.first_person = 0;
    }

    opt = GCL_GetOption('c');
    if (opt != NULL)
    {
        work->f848 = GCL_StrToInt(opt);
    }
    else
    {
        work->f848 = 0;
    }

    opt = GCL_GetOption('f');
    if (opt != NULL && GCL_StrToInt(opt) != 0)
    {
        work->f802 |= 0x80;
    }
}

void Torture_800C6AB0(TortureWork *work)
{
    int   count;
    int  *iter;
    char *res;

    if (GCL_GetOption('v'))
    {
        count = 0;
        iter = work->f87C;
        while ((res = GCL_GetParamResult()))
        {
            if (count == 8)
            {
                break;
            }

            *iter++ = GCL_StrToInt(res);
            count++;
        }

        work->f878 = count;
    }
    else
    {
        work->f878 = 0;
    }
}

int TortureGetResources_800C6B3C(TortureWork *work, int name, int map)
{
    CONTROL *control;
    char    *pos;
    char    *dir;
    OBJECT  *body;
    int      model;
    int      motion;
    int      oar;
    int      proc;

    control = &work->control;
    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);

    GM_ConfigControlHazard(control, control->mov.vy, -2, -2);
    GM_ConfigControlAttribute(control, RADAR_VISIBLE);

    body = &work->body;

    model = GV_StrCode("sne_nude");
    motion = GV_StrCode("sne_03b");
    GM_InitObject(body, model, BODY_FLAG, motion);
    GM_ConfigObjectJoint(body);

    oar = GV_StrCode("sne_03b");
    GM_ConfigMotionControl(body, &work->m_ctrl, oar, &work->anims[0], &work->anims[17], control, work->rots);
    GM_ConfigMotionAdjust(body, work->adjust);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);

    if (GCL_GetOption('e'))
    {
        work->f83C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f83C = -1;
    }

    if (GCL_GetOption('s'))
    {
        work->f838 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f838 = -1;
    }

    if (GCL_GetOption('a'))
    {
        work->f840 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f840 = -1;
    }

    Torture_800C68E8(work);
    Torture_800C6814(work);
    Torture_800C6AB0(work);
    s03b_torture_800C45E4(work);
    Torture_800C695C(work);

    GM_PlayerControl = control;
    GM_PlayerBody = body;

    gUnkCameraStruct_800B77B8.rotate2 = control->rot;
    gUnkCameraStruct_800B77B8.eye = control->mov;

    work->body.objs->objs[6].world.t[0] = gUnkCameraStruct_800B77B8.eye.vx;
    work->body.objs->objs[6].world.t[1] = gUnkCameraStruct_800B77B8.eye.vy;
    work->body.objs->objs[6].world.t[2] = gUnkCameraStruct_800B77B8.eye.vz;

    GM_AlertMode = 10;
    GM_PlayerStatus |= PLAYER_MENU_DISABLE;

    s03b_boxall_800C9328();

    GM_ActMotion(body);

    work->control.height = work->body.height;

    GM_ActControl(control);
    GM_ActObject(body);

    proc = GCL_StrToInt(GCL_GetOption('n'));
    GCL_ExecProc(proc, NULL);

    GV_PadMask = ~0x810;
    GM_GameStatus |= STATE_PADMASK;

    return 0;
}

void *NewTorture_800C6E1C(int name, int where)
{
    TortureWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(TortureWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, TortureAct_800C6600, TortureDie_800C6774, "torture.c");

        if (TortureGetResources_800C6B3C(work, name, where) >= 0)
        {
            return (void *)work;
        }

        GV_DestroyActor(&work->actor);
    }

    return NULL;
}
