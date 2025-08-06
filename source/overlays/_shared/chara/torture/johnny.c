#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/camera.h"
#include "game/game.h"
#include "game/homing.h"
#include "linkvar.h"
#include "game/vibrate.h"
#include "chara/snake/shadow.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/sna_hzd.h"
#include "okajima/blood.h"
#include "overlays/_shared/okajima/hiyoko.h"
#include "sd/g_sound.h"
#include "strcode.h"

struct JohnnyWork;
typedef void (*TJohnnyFunc)(struct JohnnyWork *work, int action);

typedef struct JohnnyWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    MOTION_SEGMENT oar1[17];
    MOTION_SEGMENT oar2[17];
    SVECTOR        rots[16];
    SVECTOR        adjust[16];
    MATRIX         light[2];
    char           pad7D8[0x48];
    TARGET        *target;
    HOMING        *homing;
    GV_ACT        *jfamas;
    GV_ACT        *gunlight;
    int           *gunlight_pvisible;
    int            jfamas_trigger;
    GV_ACT        *shadow;
    int            unk83C[5];
    SVECTOR        unk850[5][16];
    SVECTOR       *unkAD0;
    int            unkAD4;
    int            unkAD8;
    SnaAutoMove    sna_auto_move;
    SVECTOR        unkAFC;
    SVECTOR        unkB04;
    int            unkB0C;
    int            unkB10;
    int            unkB14;
    int            unkB18;
    int            unkB1C;
    char           padB20[4];
    int            unkB24;
    char           padB28[4];
    int            player_status;
    SVECTOR        unkB30;
    TJohnnyFunc    unkB38;
    int            unkB3C;
    char           padB40[4];
    TJohnnyFunc    unkB44;
    TJohnnyFunc    unkB48;
    short          unkB4C;
    short          unkB4E;
    short          unkB50;
    short          unkB52;
    short          unkB54;
    short          unkB56;
    short          unkB58;
    short          unkB5A;
    short          unkB5C;
    short          unkB5E;
    SVECTOR        unkB60;
    int            unkB68;
    unsigned short unkB6C;
    unsigned short unkB6E;
    unsigned short unkB70;
    unsigned short unkB72;
    int            unkB74;
    int            unkB78[0x12];
    int            unkBC0[8];
    int            unkBE0;
    int            unkBE4;
} JohnnyWork;

#define EXEC_LEVEL  GV_ACTOR_LEVEL5

#define SEGMENT_ATR (0)

#define TARGET_FLAG ( TARGET_POWER | TARGET_CAPTURE | TARGET_PUSH | TARGET_TOUCH | TARGET_SEEK )

unsigned char johnny_vibration1_800C32C0[] = {0xFF, 0x0A, 0x00, 0x00};
unsigned char johnny_vibration2_800C32C4[] = {0xFF, 0x04, 0x00, 0x00};

int s03c_dword_800C32C8 = 0x00000000;

SVECTOR s03c_dword_800C32CC = {0, 0, 7000};
SVECTOR s03c_dword_800C32D4 = {0, 0, 100};
SVECTOR s03c_dword_800C32DC = {64512, 0, 0};
SVECTOR s03c_dword_800C32E4 = {0, 0, 3500, 0};
SVECTOR s03c_dword_800C32EC = {0, 0, 300};
SVECTOR s03c_dword_800C32F4 = {300, 750, 300};

extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern GM_CAMERA        GM_Camera;

extern int s03c_dword_800C33D8;

void sub_80060644(SnaAutoMove *pAutoMove);

void    AN_Fog(SVECTOR *svec);
void    AN_Sleep( SVECTOR *svec );
void    s03b_boxall_800C9328(void);
void    s03b_boxall_800C9404(void);
void    s03b_boxall_800C96E8(void);
void    s03b_boxall_800C974C(void);
void    s03b_boxall_800C93F0(int, int);
void    s03b_boxall_800C969C(int, int);
int     s03b_boxall_800C93AC(int arg0);
int     s03b_boxall_800C95EC(void);
void   *NewGunLight_800D3AD4(MATRIX *world, int **pvisible);
void   *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *trigger);
void   *NewFadeIo_800C4224(int name, int where);
void   *AN_Unknown_800CA1EC(MATRIX *mat, int mark);

void s03c_johnny_800C6FC0(JohnnyWork *work, int arg1);
void s03c_johnny_800C7A64(JohnnyWork *work, int action);
void Johnny_800C7160(JohnnyWork *work, int arg1);
void Johnny_800C7804(JohnnyWork *work, int arg1);
void s03c_johnny_800C7BF8(JohnnyWork *work, int action);
void s03c_johnny_800C7F78(JohnnyWork *work, int action);

static inline void ClearAdjust(JohnnyWork *work)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        work->adjust[i] = DG_ZeroVector;
    }
}

static inline void SetAction(JohnnyWork *work, int action)
{
    if (work->object.action != action)
    {
        GM_ConfigObjectAction(&work->object, action, 0, 4);
    }
}

int Johnny_800C4194(JohnnyWork *work)
{
    SVECTOR player_pos;
    SVECTOR control_mov;

    player_pos = GM_PlayerPosition;
    control_mov = work->control.mov;
    if (HZD_LineCheck(work->control.map->hzd, &player_pos, &control_mov, ( HZD_CHECK_DYNSEG | HZD_CHECK_SEG ), SEGMENT_ATR) == 0)
    {
        return -1;
    }

    HZD_LineNearVec(&control_mov);
    GV_SubVec3(&control_mov, &player_pos, &player_pos);
    return GV_VecLen3(&player_pos);
}

void s03c_johnny_800C5520(JohnnyWork *work, int arg1);
void Johnny_800C588C(JohnnyWork *work, int arg1);

void s03c_johnny_800C424C(JohnnyWork *work, TJohnnyFunc func)
{
    if (work->unkB1C & 0x100000)
    {
        return;
    }

    if (work->unkB38 != s03c_johnny_800C5520 && work->unkB38 != Johnny_800C588C && GM_StreamStatus() == -1 &&
        GV_Time % 320 == 0)
    {
        work->unkB44 = func;
        work->unkB38 = s03c_johnny_800C5520;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C430C(JohnnyWork *work)
{
    SVECTOR svec1, svec2;

    work->unkAD4 = 0;

    svec2 = work->control.mov;
    svec2.vy = 0;

    GV_SubVec3(work->unkAD0, &svec2, &svec1);
    work->control.turn.vy = GV_VecDir2(&svec1);

    if (GV_VecLen3(&svec1) < 320)
    {
        work->unkAD4 = 1;
    }
}

int Johnny_800C4388(JohnnyWork *work, int hash)
{
    int             i;
    unsigned short *triggers;

    if (work->unkB5C != 0)
    {
        return 1;
    }

    triggers = work->control.event.triggers;

    for (i = work->control.event.n_triggers; i > 0; i--, triggers++)
    {
        if (*triggers == hash)
        {
            return 1;
        }
    }
    return 0;
}

int Johnny_800C43D0(unsigned short hash)
{
    int             i;
    unsigned short *triggers;

    triggers = GM_PlayerControl->event.triggers;

    for (i = GM_PlayerControl->event.n_triggers; i > 0; i--, triggers++)
    {
        if (*triggers == hash)
        {
            return 1;
        }
    }
    return 0;
}

void Johnny_800C4418(JohnnyWork *work)
{
    int             i;
    int             new_unkB24;
    unsigned short *triggers;

    new_unkB24 = 0;

    triggers = GM_PlayerControl->event.triggers;
    for (i = GM_PlayerControl->event.n_triggers; i > 0; i--, triggers++)
    {
        if (*triggers == 0x41A5)
        {
            new_unkB24 |= 2;
        }
        if (*triggers == 0x6599)
        {
            new_unkB24 |= 8;
        }
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        new_unkB24 |= 1;
    }

    if ((new_unkB24 & 1) != (work->unkB24 & 1))
    {
        if (new_unkB24 & 1)
        {
            if (work->unkB1C & 0x20)
            {
                work->unkB1C |= 0x40;
            }
            else
            {
                work->unkB1C |= 0x10;
            }
        }
        else
        {
            if (!(work->unkB1C & 0x20))
            {
                work->unkB1C |= 0x40000000;
            }
            work->unkB1C &= ~0x10;
            work->unkB1C &= ~0x40;
        }
    }

    work->unkB24 = new_unkB24;
}

void Johnny_800C44F8(JohnnyWork *work)
{
    if ((work->player_status & PLAYER_KETCHUP) != (GM_PlayerStatus & PLAYER_KETCHUP))
    {
        if (GM_PlayerStatus & PLAYER_KETCHUP)
        {
            if (work->unkB1C & 0x20)
            {
                if (!(work->unkB1C & 2))
                {
                    work->unkB1C |= 0x100;
                }
            }
            else
            {
                work->unkB1C |= 2;
            }
        }
        else
        {
            if (!(work->unkB1C & 0x20))
            {
                work->unkB1C |= 2;
            }
            work->unkB1C &= ~0x100;
        }
    }
    work->player_status = GM_PlayerStatus;
}

void Johnny_800C4588(JohnnyWork *work)
{
    work->unkB48 = work->unkB38;
    work->unkB38 = s03c_johnny_800C7F78;
    work->unkB4E = 0;
    work->unkB4C = 0;
    work->unkB3C = 0;
}

void Johnny_800C794C(JohnnyWork *work, int arg1);

void s03c_johnny_800C45AC(JohnnyWork* work)
{
    int fB24;

    fB24 = work->unkB24;

    if (work->unkB70 == 2 && !(work->unkB1C & 0x2))
    {
        if (!(work->unkB1C & 0x20) && GM_Items[IT_Ketchup] == -1 && !(GM_PlayerStatus & PLAYER_KETCHUP))
        {
            work->unkB1C |= 0x80002;
        }
    }

    if (fB24 & 0x1)
    {
        if (work->unkB1C & 0x40)
        {
            s03b_boxall_800C9328();
            GM_SeSet2(0, 63, SE_EXCLAMATION);
            s03b_boxall_800C93F0(work->unkB78[6], 4);
            work->unkB0C = 6;
            work->unkB10 = 0;
        }
    }
    else if (work->unkB1C & 0x100)
    {
        Johnny_800C4588(work);
        work->unkB48 = Johnny_800C794C;
    }

    else if (work->unkB1C & 0x2 && GM_PlayerStatus & PLAYER_KETCHUP && !(work->unkB1C & 0x80000))
    {
        work->unkB1C |= 0x08000000;
        Johnny_800C4588(work);
        work->unkB1C |= 0x80000;
    }
}

int Johnny_800C470C(JohnnyWork *work)
{
    return (work->unkB24 & 1) ^ 1;
}

void Johnny_800C4720(JohnnyWork *work, int arg1)
{
    work->unkAD0 = work->unk850[arg1];
}

void Johnny_800C4734(JohnnyWork *work)
{
    SVECTOR  svec;
    SVECTOR *adjust;
    int      to;

    GV_SubVec3(&s03c_dword_800C32CC, &work->control.mov, &svec);
    to = (GV_VecDir2(&svec) - work->control.rot.vy) & 0xFFF;
    if (to > 2048)
    {
        to -= 4096;
    }
    if (to > 768)
    {
        to = 768;
    }
    if (to < -768)
    {
        to = -768;
    }

    adjust = work->adjust;
    adjust[6].vy = GV_NearExp4(adjust[6].vy, to);
}

void Johnny_800C47C4(JohnnyWork *work)
{
    SVECTOR pos;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &pos);
    work->control.turn.vy = GV_VecDir2(&pos);
}

int Johnny_800C4804(JohnnyWork *work)
{
    SVECTOR diff;
    SVECTOR mov;

    mov = work->control.mov;
    mov.vy = GM_PlayerPosition.vy;

    GV_SubVec3(&GM_PlayerPosition, &mov, &diff);
    return GV_VecLen3(&diff);
}

int Johnny_800C4860(JohnnyWork *work)
{
    SVECTOR svec;
    int     vecdir;
    int     rotvy;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &svec);
    vecdir = GV_VecDir2(&svec);
    rotvy = work->control.rot.vy & 0xFFF;

    if (rotvy > 480 && rotvy < 3615)
    {
        if (rotvy - 480 < vecdir && vecdir < rotvy + 480)
        {
            return 1;
        }

        return 0;
    }

    if (rotvy < 480)
    {
        if (vecdir < rotvy + 480 || ((rotvy - 480) & 0xFFF) < vecdir)
        {
            return 1;
        }

        return 0;
    }

    if (rotvy - 480 < vecdir || vecdir < ((rotvy + 480) & 0xFFF))
    {
        return 1;
    }

    return 0;
}

void Johnny_800C4934(JohnnyWork *work)
{
    SVECTOR  svec1;
    SVECTOR  svec2;
    SVECTOR  svec3;
    SVECTOR  svec4;
    SVECTOR *adjust;
    int      vecdir;

    svec2.vx = GM_PlayerBody->objs->objs[5].world.t[0];
    svec2.vy = GM_PlayerBody->objs->objs[5].world.t[1];
    svec2.vz = GM_PlayerBody->objs->objs[5].world.t[2];

    svec3.vx = work->object.objs->objs[9].world.t[0];
    svec3.vy = work->object.objs->objs[9].world.t[1];
    svec3.vz = work->object.objs->objs[9].world.t[2];

    GV_SubVec3(&svec2, &svec3, &svec1);

    svec4.vz = SquareRoot0(svec1.vx * svec1.vx + svec1.vz * svec1.vz);
    svec4.vx = svec1.vy;

    vecdir = -GV_VecDir2(&svec4);
    if (vecdir < -2048)
    {
        vecdir += 4096;
    }

    adjust = work->adjust;

    adjust[2].vx = GV_NearExp4(adjust[2].vx, vecdir);
    adjust[6].vx = GV_NearExp4(adjust[6].vx, vecdir);
    adjust[7].vx = GV_NearExp4(adjust[7].vx, vecdir);
    adjust[6].vy = 0;
}

void Johnny_800C4A64(JohnnyWork *work)
{
    TARGET *target;

    target = work->target;
    target->damaged &= ~TARGET_PUSH;
    GM_PushTarget(target);
}

void JohnnyExecProc_800C4A98(JohnnyWork *work, int arg)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    args.argv = argv;
    argv[0] = arg;

    GCL_ExecProc(work->unkBC0[2], &args);
}

void JohnnySendEnter_800C4AD0(JohnnyWork *work, int hash)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message[0] = GV_StrCode("入る"); // 入る = enter (HASH_ENTER)
    msg.message[1] = work->control.name;
    msg.message_len = 2;

    GV_SendMessage(&msg);
    if (hash == GV_StrCode("rou_tobira"))
    {
        work->unkB5C = 1;
        JohnnyExecProc_800C4A98(work, 1);
    }
    else
    {
        work->unkB5E = 1;
    }
}

void JohnnySendLeave_800C4B58(JohnnyWork *work, int hash)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message[0] = GV_StrCode("出る"); // 出る = leave (HASH_LEAVE)
    msg.message[1] = work->control.name;
    msg.message_len = 2;

    GV_SendMessage(&msg);
    if (hash == GV_StrCode("rou_tobira"))
    {
        work->unkB5C = 0;
        JohnnyExecProc_800C4A98(work, 0);
    }
    else
    {
        work->unkB5E = 0;
    }
}

void Johnny_800C4BDC(JohnnyWork *work, int a1, int a2, TJohnnyFunc func)
{
    work->unkB58 = a1;
    work->unkB5A = a2;
    work->unkB44 = func;
}

void Johnny_800C4BEC(JohnnyWork *work, int index)
{
    MATRIX rot;

    DG_SetPos(&work->object.objs->objs[index].world);
    DG_MovePos(&s03c_dword_800C32D4);
    DG_RotatePos(&s03c_dword_800C32DC);
    ReadRotMatrix(&rot);
    NewBlood(&rot, 1);
}

int Johnny_800C4C54(JohnnyWork *work)
{
    unsigned short unkB70;

    unkB70 = work->unkB70;
    if (work->unkB6C >= 5)
    {
        work->unkB70 = 3;
        return 1;
    }

    switch (unkB70)
    {
    case 0:
        return 0;

    case 2:
        if (!(work->unkB1C & 2))
        {
            return 0;
        }

    default:
        if (unkB70 != 1)
        {
            // FIXME: this is probably just "case 1:", but
            // couldn't find a way to match it with it.
            return (work->unkB1C & 2) > 0;
        }
        return 1;
    }
}

void Johnny_800C4CCC(JohnnyWork *work)
{
    GCL_ARGS args;
    long     argv[4];

    if (work->unkB68 >= 0)
    {
        args.argc = 4;
        args.argv = argv;

        if (work->unkB70 < 3 && (work->unkB1C & 2))
        {
            work->unkB70 = 3;
        }

        argv[0] = work->unkB70;
        argv[1] = work->unkB1C & 1;
        argv[2] = work->unkB0C == 3;
        argv[3] = (work->unkB1C & 0x1000) > 0;

        GCL_ExecProc(work->unkBC0[0], &args);
        GV_DestroyActor(&work->actor);
    }
}

void JohnnyExecProc_800C4D8C(JohnnyWork *work)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    args.argv = argv;
    argv[0] = s03c_dword_800C32C8;

    GCL_ExecProc(work->unkBC0[6], &args);
}

void Johnny_800C4DCC(JohnnyWork *work)
{
    if (!(work->unkB1C & 8))
    {
        return;
    }
    work->unkB1C &= ~8;

    if (work->unkB14 < 0)
    {
        Johnny_800C4CCC(work);
        return;
    }

    if (work->unkB1C & 0x2000)
    {
        work->unkB1C = work->unkB1C & ~0x2000;
        if (Johnny_800C4C54(work) != 0)
        {
            Johnny_800C4CCC(work);
            return;
        }
        work->unkB10 = 0;
        work->unkB0C = work->unkB14;
    }
    else
    {
        work->unkB0C = work->unkB14;
        work->unkB10 = 0;
    }
}

void Johnny_800C4E5C(JohnnyWork *work)
{
    if (work->unkB72 != 0)
    {
        if (--work->unkB72 == 0)
        {
            GM_SeSet(&work->unkB04, SE_DOOR_CLOSE3);
        }
    }
}

void Johnny_800C4E9C(JohnnyWork *work)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR svec;
    MATRIX *world;

    world = &work->object.objs->objs[6].world;
    ReadRotMatrix(&mat1);
    DG_TransposeMatrix(&mat1, &mat2);
    MulMatrix0(&mat2, world, &mat2);
    DG_MatrixRotZYX(&mat2, &svec);
    SetRotMatrix(&mat1);
    work->control.radar_cone.dir = svec.vy + work->control.rot.vy;
}

void Johnny_800C4F24(JohnnyWork *work, int arg1)
{
    if (arg1 != 0)
    {
        if (!(work->unkB1C & 0x10000000))
        {
            GM_EnemyWatchCount++;
        }
        work->unkB1C |= 0x10000000;
        GM_AlertModeSet(3);
        return;
    }
    work->unkB1C &= ~0x10000000;
    GM_AlertModeSet(0);
    GM_AlertLevel = 0;
}

void Johnny_800C4FAC(JohnnyWork *work)
{
    CONTROL *control;
    int      frame;

    frame = work->motion.info1.frame;
    control = &work->control;

    switch (work->object.action)
    {
    case 1:
        if (frame == 0)
        {
            sub_80032BC4(&control->mov, 160, 1500);
        }
        if (frame == 12)
        {
            sub_80032BC4(&control->mov, 161, 1500);
        }
        break;

    case 2:
    case 33:
        if (frame == 0)
        {
            sub_80032BC4(&control->mov, 160, 1500);
        }
        if (frame == 8)
        {
            sub_80032BC4(&control->mov, 161, 1500);
        }
        break;
    }
}

void Johnny_800C7428(JohnnyWork *work, int action);
void Johnny_800C6C10(JohnnyWork *work, int action);

void s03c_johnny_800C5064(JohnnyWork *work)
{
    if (Johnny_800C4388(work, 0x41A5) != 0 || work->unkB5C == 1)
    {
        work->unkB38 = Johnny_800C7428;
    }
    else
    {
        work->unkB48 = Johnny_800C6C10;
        work->unkB38 = s03c_johnny_800C7F78;
    }
    work->unkB4E = 0;
    work->unkB4C = 0;
    work->unkB3C = 0;
}

void Johnny_800C50D0(JohnnyWork *work)
{
    if (!(work->unkB1C & 0x10) || !(GM_PlayerStatus & PLAYER_INTRUDE))
    {
        work->unkB74 = 0;
        return;
    }
    if (work->unkB74 < 0)
    {
        return;
    }
    if (work->unkB74 >= 24)
    {
        return;
    }
    work->unkB74++;
}

// Similar to sna_act_unk2_80051170
// arg type could be different
void Johnny_800C5124(TARGET *target)
{
    target->a_mode = 0;
    target->field_28 = 0;
    target->damaged &= ~(TARGET_TOUCH | TARGET_POWER | TARGET_CAPTURE);
    target->field_2C_vec = DG_ZeroVector;
}

void Johnny_800C8400(JohnnyWork *work, int action);
void Johnny_800C854C(JohnnyWork *work, int action);
void Johnny_800C8654(JohnnyWork *work, int action);
void Johnny_800C8B14(JohnnyWork *work, int action);
void Johnny_800C9144(JohnnyWork *work, int action);

void s03c_johnny_800C5168(JohnnyWork *work)
{
    TARGET *target;
    int     a_mode;

    if (work->unkB1C & 0x1000)
    {
        return;
    }

    if (work->unkB1C < 0)
    {
        Johnny_800C5124(work->target);
        return;
    }

    target = work->target;
    a_mode = target->a_mode;

    if (target->damaged & 0x4)
    {
        if (!(work->unkB1C & 0x200))
        {
            if (a_mode == 3)
            {
                work->unkB38 = Johnny_800C8400;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;

                GM_SeSet(&work->control.mov, SE_PUNCH_HIT);
                GM_SeSet(&work->control.mov, 141);

                AN_Fog(&work->control.mov);

                if (target->field_2A <= 0)
                {
                    work->unkB38 = Johnny_800C9144;
                    work->unkB4E = 0;
                    work->unkB4C = 0;
                    work->unkB3C = 0;
                }
            }
            else if (a_mode == 4)
            {
                work->unkB38 = Johnny_800C8400;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;

                GM_SeSet(&work->control.mov, SE_KICK_HIT);
                GM_SeSet(&work->control.mov, 142);

                AN_Fog(&work->control.mov);

                if (target->field_2A <= 0)
                {
                    work->unkB38 = Johnny_800C9144;
                    work->unkB4E = 0;
                    work->unkB4C = 0;
                    work->unkB3C = 0;
                }
            }
            else if (a_mode == 1)
            {
                work->unkB38 = Johnny_800C8400;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;

                work->unkB1C |= 0x400;

                AN_Fog(&work->control.mov);
                GM_SeSet(&work->control.mov, 141);
            }
            else
            {
                work->unkB30 = target->field_2C_vec;

                work->unkB38 = Johnny_800C854C;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;

                work->unkB30.vx *= 4;
                work->unkB30.vz *= 4;

                AN_Fog(&work->control.mov);
                GM_SeSet(&work->control.mov, 142);
            }
        }
        else
        {
            Johnny_800C4BEC(work, 6);
        }

        Johnny_800C5124(target);

        work->unkB1C &= ~0x800;
        UnsetTargetClass( work->target, TARGET_DOWN );

        s03b_boxall_800C9328();
    }
    else if (target->damaged & 0x2)
    {
        if (a_mode == 36)
        {
            target->class |= TARGET_DOWN;

            work->unkB38 = Johnny_800C8654;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;

            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            Johnny_800C5124(target);
            s03b_boxall_800C9328();
        }
        else if (!(work->unkB1C & 0x800))
        {
            target->class |= TARGET_DOWN;

            GM_SeSet(&work->control.mov, 143);

            work->unkBE4 = 0;
            work->unkB38 = Johnny_800C8B14;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;

            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            s03b_boxall_800C9328();
        }
    }
}

void Johnny_800C54A8(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        SetAction(work, 0);
        Johnny_800C47C4(work);
    }

    if (arg1 == 60)
    {
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB38 = work->unkB44;
    }
}

void s03c_johnny_800C5520(JohnnyWork *work, int action)
{
    int index;

    if (action == 0)
    {
        index = (work->unkB1C & 0x4000) ? 10 : 0;

        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[index], 4);

        work->unkBE0 = work->unkB78[index];

        SetAction(work, 0);

        GM_ConfigMotionAdjust(&work->object, work->adjust);
    }

    switch (work->unkB4C)
    {
    case 0:
        if (work->unkBE0 == work->unkB78[10])
        {
            if (GM_StreamStatus() == 2)
            {
                SetAction(work, 15);
                work->unkB4C = 1;
            }
        }
        else if (GM_StreamStatus() == 2 && ++work->unkB4E == 42)
        {
            SetAction(work, 15);
            work->unkB4C = 1;
            work->unkB4E = 0;
        }
        break;

    case 1:
        if (work->object.action == 15 && work->object.is_end != 0)
        {
            if (work->unkB1C & 0x4000)
            {
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;
                work->unkB38 = work->unkB44;

                GM_ConfigMotionAdjust(&work->object, NULL);
                ClearAdjust(work);
            }
            else
            {
                GM_ConfigObjectAction(&work->object, 0, 0, 4);
                work->unkB4C = 2;
            }
        }
        break;

    case 2:
        if (GM_StreamStatus() == -1)
        {
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB38 = work->unkB44;
            work->unkB1C |= 0x4000;

            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);
        }
        break;
    }
}

void s03c_johnny_800C5A7C(JohnnyWork *work, int arg1);

void Johnny_800C57D0(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.turn.vy = 3072;
        work->unkB74 = -1;
        work->unkB1C |= 0x20;
        SetAction(work, (GV_Time & 1) ? 10 : 11);
    }
    if (arg1 == 24)
    {
        GM_SeSet2(0, 0x3F, 0x92);
    }

    if (work->object.is_end != 0)
    {
        work->unkB38 = s03c_johnny_800C5A7C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C588C(JohnnyWork *work, int arg1)
{
    SVECTOR svec;
    int     status;

    if (arg1 == 0)
    {
        GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &svec);
        work->control.turn.vy = GV_VecDir2(&svec);

        SetAction(work, 0);

        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[12], 4);
    }
    if (arg1 > 16)
    {
        status = GM_StreamStatus();
        if (status == -1)
        {
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB74 = status;
            work->unkB38 = work->unkB44;
        }
    }
}

void s03c_johnny_800C594C(JohnnyWork *work)
{
    int index;

    if (GM_StreamStatus() == -1 && GM_NoisePower != 0)
    {
        index = (GV_Time & 0x1) ? 14 : 16;
        s03b_boxall_800C93AC(work->unkB78[index]);
    }
}

void Johnny_800C59B8(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.turn.vy = 3072;
        SetAction(work, 0);
    }
    GV_NearExp2V(&work->control.mov.vx, &work->unkAFC.vx, 3);
    if ((work->unkB74 ^ (0x10 | 0x8)) == 0)
    {
        work->unkB44 = Johnny_800C59B8;
        work->unkB38 = Johnny_800C588C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    else if (arg1 == 90)
    {
        work->unkB44 = Johnny_800C59B8;
        work->unkB38 = Johnny_800C54A8;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    else
    {
        s03c_johnny_800C594C(work);
    }
}

void s03c_johnny_800C5A7C(JohnnyWork *work, int action)
{
    SVECTOR pos;

    if (action == 0)
    {
        work->unkB1C |= 0x20;
        work->control.radar_atr &= ~RADAR_SIGHT;
        SetAction(work, 12);
        work->unkB74 = -1;
    }

    if (!(work->unkB1C & 0x10000) && ((action % 100) == 0))
    {
        pos.vx = work->object.objs->objs[6].world.t[0];
        pos.vy = work->object.objs->objs[6].world.t[1];
        pos.vz = work->object.objs->objs[6].world.t[2];
        AN_Sleep(&pos);
    }

    switch (work->unkB4C)
    {
    case 0:
        if (!(action & 0x3F))
        {
            GM_SeSet2(0, 63, 147);
        }

        if (action == 348)
        {
            work->unkB4C = 1;
            SetAction(work, 13);
        }
        break;

    case 1:
        if (work->object.is_end != 0)
        {
            work->unkB1C |= 0x10000;

            SetAction(work, 0);
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);

            if (!(work->unkB1C & 0x2000000))
            {
                s03b_boxall_800C93AC(work->unkB78[3]);
                work->unkB4C = 2;
                work->unkB1C |= 0x2000000;
            }
            else
            {
                work->unkB14 = 2;
                work->unkB1C |= 0x8;
                work->control.radar_atr |= RADAR_SIGHT;
                work->unkB1C &= ~0x10000;
            }

            work->unkB1C &= ~0x20;
        }
        break;

    case 2:
        if (action == 511)
        {
            SetAction(work, 10);
        }

        if ((work->object.action == 10) && (work->object.is_end != 0))
        {
            GM_ConfigObjectAction(&work->object, 0, 0, 4);
        }

        if ((action >= 512) && (GM_StreamStatus() == -1))
        {
            work->unkB4C = 3;
            s03b_boxall_800C93AC(work->unkB78[4]);
            SetAction(work, 11);
        }
        break;

    case 3:
        if ((work->object.action == 11) && (work->object.is_end != 0))
        {
            GM_ConfigObjectAction(&work->object, 0, 0, 4);
        }

        if ((work->object.action == 0) && (GM_StreamStatus() == -1))
        {
            work->unkB14 = 2;
            work->unkB1C |= 0x8;
            work->control.radar_atr |= RADAR_SIGHT;
            work->unkB1C &= ~0x10000;
        }
        break;
    }
}

void Johnny_800C92E0(JohnnyWork *work, int arg1);

void s03c_johnny_800C5DE4(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        GM_ConfigMotionAdjust(&work->object, work->adjust);
        work->unkAD0++;
        SetAction(work, 1);
    }

    Johnny_800C4734(work);
    Johnny_800C430C(work);

    if (work->unkAD4 != 0)
    {
        if (((work->unkAD0->pad & 0xC00) >> 10) == 2)
        {
            if (work->unkB4C == 0)
            {
                GM_ConfigMotionAdjust(&work->object, NULL);
                ClearAdjust(work);

                if (work->unkB6E == 1 || (work->unkB1C & 0x400000) != 0)
                {
                    work->unkB14 = 0;
                    work->unkB1C |= 0x8;
                }
                else
                {
                    work->unkB38 = Johnny_800C92E0;
                    work->unkB4E = 0;
                    work->unkB4C = 0;
                    work->unkB3C = 0;
                    return;
                }
                work->unkB4C = 1;
            }
        }
        else
        {
            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            work->unkB44 = s03c_johnny_800C5DE4;

            if (work->unkB1C & 0x20000000)
            {
                work->unkB38 = s03c_johnny_800C5520;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;
                work->unkB1C &= ~0x20000000;
                return;
            }

            if ((work->unkB74 ^ 0x18) == 0)
            {
                work->unkB44 = s03c_johnny_800C5DE4;
                work->unkB38 = Johnny_800C588C;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;
                return;
            }

            if (GV_RandS(128) > 0 || (work->unkB1C & 0x100000) != 0 || GM_StreamStatus() != -1)
            {
                work->unkB38 = Johnny_800C54A8;
            }
            else
            {
                work->unkB38 = s03c_johnny_800C5520;
            }

            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
    }

    s03c_johnny_800C594C(work);
}

void Johnny_800C6268(JohnnyWork *work, int action);

void Johnny_800C6054(JohnnyWork *work, int action)
{
    int index;

    if (action == 0)
    {
        work->unkB74 = -1;
        work->unkB1C |= 0x20;

        SetAction(work, 31);

        index = !(work->unkB1C & 0x800000) ? 1 : 2;
        work->unkB1C |= 0x800000;
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[index], 4);
        GM_SeSet2(0, 0x3F, 0xB4);
    }
    if (work->unkB4C == 0)
    {
        if (work->object.is_end != 0)
        {
            SetAction(work, 32);
            work->unkB4C = 1;
        }
    }
    else if (GM_StreamStatus() == -1)
    {
        work->unkB38 = Johnny_800C6268;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C6170(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        SetAction(work, 0);
        work->control.radar_atr &= ~RADAR_SIGHT;
    }
    if (arg1 == 300 && work->unkB4C == 0)
    {
        work->unkB14 = 4;
        work->unkB4C = 1;
        work->unkB1C |= 0x2000 | 0x8;
    }
}

void Johnny_800C64B0(JohnnyWork *work, int action);

void Johnny_800C6204(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->unkB1C |= 0x20;
        SetAction(work, 0);
        work->unkB38 = Johnny_800C64B0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C6268(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C |= 0x20;
        work->unkAD0++;
        SetAction(work, 33);
    }

    Johnny_800C430C(work);

    if (work->unkAD4 != 0)
    {
        if (((work->unkAD0->pad & 0xC00) >> 10) == 2)
        {
            work->unkB38 = Johnny_800C6170;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            work->unkAD0++;
        }
    }
}

void Johnny_800C631C(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->control.turn.vy = 0;
        SetAction(work, 10);
        s03b_boxall_800C93AC(work->unkB78[5]);
    }
    if (work->object.is_end != 0)
    {
        if (work->object.action == 10)
        {
            GM_ConfigObjectAction(&work->object, 0, 0, 4);
            work->unkB4C++;
        }
    }
    if (work->object.action == 0 && GM_StreamStatus() == -1)
    {
        work->unkB4C++;
    }
    if (work->unkB4C == 2)
    {
        work->unkB38 = Johnny_800C64B0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x1000000;
    }
}

void Johnny_800C6418(JohnnyWork *work, int action)
{
    work->unkB1C |= 0x20;
    SetAction(work, 0);
    work->control.mov.vx = 6000;
    work->control.mov.vz = 750;
    work->control.rot.vy = 1024;
    work->control.turn.vy = 1024;
    work->unkB38 = Johnny_800C64B0;
    work->unkB4E = 0;
    work->unkB4C = 0;
    work->unkB3C = 0;
    work->unkAD0 += 2;
    work->unkB1C |= 0x1000000;
}

void Johnny_800C64B0(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C |= 0x20;
        work->unkAD0++;

        SetAction(work, 1);

        if (!(work->unkB1C & 0x1000000))
        {
            GM_SeSet2(0, 0x3F, 0xB3);
            GM_SeSet2(0, 0x3F, 0xB6);
        }
    }

    if (Johnny_800C4388(work, 0x5CBD))
    {
        work->unkB1C &= ~0x20;
    }

    Johnny_800C430C(work);

    if (work->unkAD4 != 0)
    {
        if (((work->unkAD0->pad & 0xC00) >> 10) == 2)
        {
            if (work->unkB4C == 0)
            {
                work->unkB14 = 0;
                work->unkB1C &= ~0x1000000;
                work->unkB1C |= 0x8;
            }
        }
        else if (((work->unkAD0->pad & 0xE0) >> 5) == 4)
        {
            work->unkB38 = Johnny_800C631C;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            work->unkAD0++;
        }
    }
}

void s03c_johnny_800C69D8(JohnnyWork *work, int arg1);

void Johnny_800C65F8(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        SetAction(work, 6);
        work->control.turn.vy = (work->unkAD0->pad & 0x1F) * 512;
        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 3);
    }
    if (Johnny_800C470C(work) != 0)
    {
        s03c_johnny_800C5064(work);
    }
    else if (work->object.is_end != 0)
    {
        work->unkB38 = s03c_johnny_800C69D8;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C66A4(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C &= ~0x80000000;
        GM_ConfigMotionAdjust(&work->object, NULL);
        ClearAdjust(work);

        work->control.turn.vy = (work->unkAD0->pad & 0x1F) * 512;

        SetAction(work, 34);
    }

    if (work->object.is_end != 0 && work->unkB4C == 0)
    {
        SetAction(work, 38);
        work->unkB4C = 1;
    }

    if (work->unkB4C != 0)
    {
        if (Johnny_800C4860(work)|| action == 240 || (work->unkB24 & 0x2) == 0)
        {
            work->unkB38 = Johnny_800C7428;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else if (work->object.is_end != 0)
        {
            work->control.mov = *work->unkAD0;
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 3);
        }
    }
}

void Johnny_800C6850(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->unkB1C |= 0x80000000;

        if (work->unkB5A == 0)
        {
            JohnnySendLeave_800C4B58(work, work->unkB58);
            work->unkB72 = 16;
        }

        SetAction(work, 35);
        GM_SeSet2(0, 0x3F, 0xB5);
    }
    if (work->object.is_end != 0)
    {
        if (work->unkB5A == 1)
        {
            JohnnySendEnter_800C4AD0(work, work->unkB58);
            work->unkB72 = 16;
        }
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB38 = work->unkB44;
    }
}

void Johnny_800C6918(JohnnyWork *work, int arg1)
{
    OBJECT *object;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        object = &work->object;
        GM_ConfigMotionAdjust(object, work->adjust);
        SetAction(work, 2);
        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd,
                                             work->unk850[3]);
    }
    Johnny_800C4734(work);
    if (sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control) < 0)
    {
        Johnny_800C4720(work, 3);
        work->unkB38 = Johnny_800C65F8;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C69D8(JohnnyWork *work, int action)
{
    int action1, action2;

    if (action == 0)
    {
        work->unkB1C |= 0x80000000;
        GM_ConfigMotionAdjust(&work->object, work->adjust);
        SetAction(work, 2);
        work->unkAD0++;
    }

    Johnny_800C4734(work);

    if (Johnny_800C470C(work))
    {
        GM_ConfigMotionAdjust(&work->object, NULL);
        ClearAdjust(work);

        s03c_johnny_800C5064(work);
        return;
    }

    Johnny_800C430C(work);

    if (work->unkAD4 != 0)
    {
        action1 = (work->unkAD0->pad & 0xC00) >> 10;
        action2 = (work->unkAD0->pad & 0xE0) >> 5;

        if (action1 == 2)
        {
            work->unkB38 = s03c_johnny_800C66A4;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else if (action2 == 1)
        {
            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            work->unkB38 = Johnny_800C65F8;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else if (action2 == 2)
        {
            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            work->control.turn.vy = -1024;
            Johnny_800C4BDC(work, GV_StrCode("rou_tobira"), 1, s03c_johnny_800C69D8);

            work->unkB38 = Johnny_800C6850;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            work->unkAD0++;
        }
    }
}

void Johnny_800C6C10(JohnnyWork *work, int action)
{
    OBJECT *object;
    int     unkB1C;

    if (action == 0)
    {
        object = &work->object;

        work->control.radar_atr &= ~RADAR_UNK4;

        work->unkB1C |= 0x80000000;

        GM_ConfigMotionAdjust(object, work->adjust);
        SetAction(work, 1);
        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd,
                                             work->unk850[0]);

        unkB1C = work->unkB1C;

        work->unkB1C &= ~0x40;

        if (unkB1C & 0x100)
        {
            work->unkB1C &= ~0x100;
            work->unkB1C |= 2;
        }

        GM_GameStatus &= ~STATE_PADRELEASE;

        Johnny_800C4F24(work, 0);
    }

    Johnny_800C4734(work);
    sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

    if (sub_800606E4(&work->sna_auto_move, &work->control.mov, 250))
    {
        GM_ConfigMotionAdjust(&work->object, NULL);
        ClearAdjust(work);

        work->unkB14 = 2;
        work->unkB1C |= 8;
    }
}

void s03c_johnny_800C6D84(JohnnyWork *work, int action)
{
    SVECTOR pos;
    SVECTOR diff;
    int     len;

    if ((work->unkB24 & 0x8) && !(work->target->class & TARGET_DOWN))
    {
        work->unkB38 = s03c_johnny_800C7A64;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return;
    }

    len = Johnny_800C4804(work);
    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        pos.vx = -700;
        pos.vz = 8000;
        pos.vy = work->control.mov.vy;

        GV_SubVec3(&pos, &work->control.mov, &diff);
        len = GV_VecLen3(&diff);
    }

    if (action == 0)
    {
        work->unkB1C &= ~0x80000000;

        SetAction(work, 2);

        if ((len < 2500) && ((GM_PlayerStatus & PLAYER_INTRUDE) || (Johnny_800C4194(work) < 0)))
        {
            work->unkB44 = s03c_johnny_800C6D84;
            work->unkB38 = Johnny_800C7160;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            return;
        }

        Johnny_800C4F24(work, 1);
        work->sna_auto_move.field_0_ivec.vz = -1;
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        pos.vx = -700;
        pos.vz = 8000;
        pos.vy = 0;

        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &pos);
    }
    else
    {
        sub_80060644(&work->sna_auto_move);
    }

    sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

    if ((len < 1500) && ((GM_PlayerStatus & PLAYER_INTRUDE) || (Johnny_800C4194(work) < 0)))
    {
        work->unkB44 = s03c_johnny_800C6D84;
        work->unkB38 = Johnny_800C7160;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }

    if ((work->unkB70 != 4) && (work->unkB24 & 2))
    {
        work->unkB38 = s03c_johnny_800C6FC0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C6FC0(JohnnyWork *work, int action)
{
    SVECTOR diff;
    int     len;

    if (action == 0)
    {
        work->unkB1C &= ~0x80000000;

        SetAction(work, 2);

        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &work->unkB04);
        Johnny_800C4F24(work, 1);
    }

    sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

    if (sub_800606E4(&work->sna_auto_move, &work->control.mov, 450))
    {
        GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
        len = GV_VecLen3(&diff);

        if ((work->unkB24 & 0x2) && (len > 1500))
        {
            work->control.turn.vy = -1024;
            Johnny_800C4BDC(work, GV_StrCode("rou_tobira"), 0, Johnny_800C6C10);
            work->unkB38 = Johnny_800C6850;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            GM_GameStatus |= STATE_PADRELEASE;
        }
        else
        {
            work->unkB38 = s03c_johnny_800C6D84;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
    }
    else if ((action == 24) && (work->unkB24 & 0x2))
    {
        work->unkB44 = s03c_johnny_800C6FC0;
        work->unkB38 = Johnny_800C7160;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C7160(JohnnyWork *work, int arg1)
{
    int action;
    int trigger;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;

        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            work->unkB4E = 1;
            action = 41;
            GM_ConfigMotionAdjust(&work->object, work->adjust);
        }
        else
        {
            action = 8;
            GM_ConfigMotionAdjust(&work->object, work->adjust);
        }

        SetAction(work, action);
        Johnny_800C4F24(work, 1);
    }

    Johnny_800C47C4(work);

    if (work->unkB4E == 1)
    {
        work->adjust[3].vx = -work->adjust[2].vx;
        work->control.turn.vy += 320;
    }

    Johnny_800C4934(work);

    trigger = 1;

    if (arg1 == 4)
    {
        work->unkB4C = 1;

        if (work->unkB4E == 0)
        {
            SetAction(work, 9);
        }
    }

    if (work->object.action == 41)
    {
        if (arg1 == 16 || arg1 == 22 || arg1 == 28)
        {
            trigger |= 2;
        }
    }
    else if (arg1 != 12 && arg1 != 17)
    {
        if (arg1 == 22)
        {
            trigger |= 2;
        }
    }
    else
    {
        trigger |= 2;
    }

    if (work->object.is_end != 0 && work->unkB4C == 1)
    {
        if (GM_PlayerStatus & PLAYER_INTRUDE)
        {
            work->unkB38 = Johnny_800C7160;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB38 = work->unkB44;
        }
    }
    else
    {
        work->jfamas_trigger = trigger;
    }
}

void Johnny_800C7378(JohnnyWork *work, int arg1)
{
    OBJECT *object;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        object = &work->object;
        GM_ConfigMotionAdjust(object, work->adjust);
        SetAction(work, 8);
        Johnny_800C4F24(work, 1);
    }
    if (arg1 == 32)
    {
        work->unkB38 = Johnny_800C7160;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    Johnny_800C47C4(work);
}

void Johnny_800C7428(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C &= ~0x80000000;
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[13], 4);
        GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
        NewPadVibration(johnny_vibration1_800C32C0, 2);
        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        SetAction(work, 5);
        work->unkB1C &= ~0x40000000;
    }

    Johnny_800C47C4(work);

    if (work->object.is_end != 0)
    {
        if (Johnny_800C4388(work, 0x41A5) != 0)
        {
            work->unkB44 = s03c_johnny_800C6FC0;
            if (work->unkB24 & 2)
            {
                work->unkB38 = Johnny_800C7378;
            }
            else
            {
                work->unkB38 = s03c_johnny_800C6FC0;
            }
        }
        else
        {
            work->unkB38 = Johnny_800C6C10;
        }
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C753C(JohnnyWork *work, int action)
{
    SVECTOR mov;

    if (action == 0)
    {
        work->unkB1C |= 0x80000000;
        s03b_boxall_800C9328();

        SetAction(work, 2);

        switch (work->unkB50)
        {
        case 0:
            sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &s03c_dword_800C32E4);
            break;

        case 1:
            sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &work->unkB04);
            break;

        case 2:
            if (GM_PlayerStatus & PLAYER_INTRUDE)
            {
                mov.vx = -750;
                mov.vz = 8000;
                mov.vy = 0;

                sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &mov);
            }
            else
            {
                work->sna_auto_move.field_0_ivec.vz = -1;
                sub_80060644(&work->sna_auto_move);
            }
            break;
        }
    }

    if (!(GM_PlayerStatus & PLAYER_KETCHUP))
    {
        work->unkB50 = 0;

        work->unkB1C |= 0x2;
        work->unkB1C &= ~0x100;

        NewPadVibration(johnny_vibration1_800C32C0, 2);

        work->unkB1C |= 0x80002;
        work->unkB1C &= ~0x100;

        if (Johnny_800C4388(work, 0x41A5))
        {
            work->unkB44 = s03c_johnny_800C6FC0;

            if (work->unkB24 & 0x2)
            {
                work->unkB38 = Johnny_800C7378;
                work->unkB4E = 0;
                work->unkB4C = 0;
                work->unkB3C = 0;
                return;
            }

            work->unkB38 = s03c_johnny_800C6FC0;
        }
        else
        {
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
            GM_SeSet2(0, 63, SE_EXCLAMATION);

            s03b_boxall_800C9328();
            s03b_boxall_800C93F0(work->unkB78[8], 4);

            NewPadVibration(johnny_vibration1_800C32C0, 2);

            GCL_ExecProc(work->unkBC0[4], NULL);
            work->unkB38 = Johnny_800C6C10;
        }

        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return;
    }

    sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

    if (sub_800606E4(&work->sna_auto_move, &work->control.mov, 500))
    {
        work->unkB50++;

        if (work->unkB50 == 2)
        {
            work->control.turn.vy = -1024;
            Johnny_800C4BDC(work, GV_StrCode("rou_tobira"), 1, s03c_johnny_800C753C);
            work->unkB38 = Johnny_800C6850;
        }
        else if (work->unkB50 == 3)
        {
            work->unkB38 = Johnny_800C7804;
        }
        else
        {
            work->unkB38 = Johnny_800C794C;
        }

        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C7804(JohnnyWork *work, int arg1)
{
    SVECTOR svec;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        SetAction(work, 0);

        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 3);

        work->unkB60 = GM_PlayerPosition;
        work->unkB60.pad = GM_PlayerControl->turn.vy;
    }

    GV_SubVec3(&GM_PlayerPosition, &work->unkB60, &svec);

    if (GV_VecLen3(&svec) < 5)
    {
        if (ABS(work->unkB60.pad - GM_PlayerControl->turn.vy) >= 5)
        {
            work->unkB38 = Johnny_800C794C;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
    }
    else
    {
        work->unkB38 = Johnny_800C794C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }

    if (arg1 == 64)
    {
        work->unkB38 = Johnny_800C794C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C794C(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        SetAction(work, 5);
    }
    Johnny_800C47C4(work);
    if (work->object.is_end != 0)
    {
        if (work->unkB50 == 3)
        {
            work->unkB50 = 0;
            work->unkB44 = &s03c_johnny_800C6FC0;
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
            GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
            NewPadVibration(johnny_vibration1_800C32C0, 2);
            GCL_ExecProc(work->unkBC0[4], NULL);
            work->unkB38 = Johnny_800C7378;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB1C |= 0x80000 | 0x2;
            work->unkB1C &= ~0x100;
        }
        else
        {
            work->unkB38 = &s03c_johnny_800C753C;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
    }
}

void s03c_johnny_800C7A64(JohnnyWork *work, int action)
{
    SVECTOR diff;
    int     len;

    if (action == 0)
    {
        work->unkB1C |= 0x80000000;

        s03b_boxall_800C9328();
        s03b_boxall_800C969C(1, 30000);

        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;

        SetAction(work, 2);

        work->sna_auto_move.field_0_ivec.vz = -1;
    }

    switch (work->unkB4C)
    {
    case 0:
        sub_80060644(&work->sna_auto_move);
        sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

        len = Johnny_800C4804(work);
        if (len < 5000)
        {
            GV_SubVec3(&work->control.mov, &GM_PlayerPosition, &diff);
            GM_PlayerControl->turn.vy = GV_VecDir2(&diff);
        }

        if ((len < 1500) && (Johnny_800C4194(work) < 0))
        {
            SetAction(work, 8);
            work->unkB4C = 1;
        }
        break;

    case 1:
        Johnny_800C47C4(work);

        if (++work->unkB4E == 32)
        {
            work->unkB38 = s03c_johnny_800C7BF8;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        break;
    }
}

void s03c_johnny_800C7BF8(JohnnyWork *work, int action)
{
    SVECTOR diff;
    SVECTOR pos;
    SVECTOR campos;
    int     len;

    if (action == 0)
    {
        work->unkB1C |= 0x80000000;
        work->target->class = TARGET_AVAIL;

        s03b_boxall_800C9328();
        SetAction(work, 31);
        GM_SeSet2(0, 63, 180);
    }

    if (action == 4)
    {
        s03b_boxall_800C93AC(work->unkB78[2]);
    }

    switch (work->unkB4C)
    {
    case 0:
        if (work->object.is_end != 0)
        {
            SetAction(work, 32);
            work->unkB4C = 1;
        }
        break;

    case 1:
        if (GM_StreamStatus() == -1)
        {
            SetAction(work, 33);

            pos.vx = 6500;
            pos.vy = 0;
            pos.vz = -1500;

            sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd, &pos);
            work->unkB4C = 2;
        }
        break;

    case 2:
    case 3:
        DG_InvisibleObjs(GM_PlayerBody->objs);

        GM_Camera.first_person = 1;

        gUnkCameraStruct_800B77B8.eye = GM_PlayerPosition;
        gUnkCameraStruct_800B77B8.eye.vy += 500;

        gUnkCameraStruct_800B77B8.rotate2.vz = 0;
        gUnkCameraStruct_800B77B8.rotate2.vx = 0;

        campos.vx = 5500;
        campos.vz = 750;
        campos.vy = 0;

        GV_SubVec3(&campos, &GM_PlayerPosition, &diff);
        gUnkCameraStruct_800B77B8.rotate2.vy = GV_VecDir2(&diff);

        if (work->unkB4C == 2)
        {
            sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);
            len = sna_act_unk_helper2_helper3_80060684(&work->sna_auto_move, &work->control.mov);

            if (len < 500)
            {
                work->control.radar_atr &= ~RADAR_SIGHT;
                SetAction(work, 0);
                work->unkB4C = 3;
            }
        }
        else if (++work->unkB4E == 32)
        {
            GM_Camera.first_person = 0;
            work->unkB4C = 4;
            work->unkB4E = 0;
        }
        break;

    case 4:
        if (++work->unkB4E == 6)
        {
            DG_VisibleObjs(GM_PlayerBody->objs);
            s03b_boxall_800C96E8();
            JohnnyExecProc_800C4D8C(work);
            Johnny_800C4F24(work, 0);
            GCL_ExecProc(work->unkBC0[5], 0);
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );
            work->unkB4C = 5;
        }
        break;

    case 5:
        if ((GM_StreamStatus() == -1) && Johnny_800C43D0(0xAE93) && (GM_PlayerStatus & PLAYER_CHECK_WALL))
        {
            s03b_boxall_800C93F0(work->unkB78[17], 4);
        }
        break;
    }

}

void s03c_johnny_800C7F78(JohnnyWork *work, int action)
{
    SVECTOR sp10;
    SVECTOR diff;
    MATRIX  sp20;
    MATRIX  sp40;
    GV_MSG  msg;

    if (action == 0)
    {
        work->unkB1C |= 0x80000000;

        SetAction(work, 0);

        GM_ConfigMotionAdjust(&work->object, NULL);
        ClearAdjust(work);

        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        GM_SeSet2(0, 63, SE_EXCLAMATION);

        NewPadVibration(johnny_vibration1_800C32C0, 2);
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
    }

    DG_VisibleObjs(GM_PlayerBody->objs);
    Johnny_800C47C4(work);

    if (work->control.mov.vx >= -2700)
    {
        sp10.vx = -350;
        sp10.vy = 1000;
        sp10.vz = -750;
    }
    else
    {
        sp10.vx = 450;
        sp10.vy = 1000;
        sp10.vz = -750;
    }

    ReadRotMatrix(&sp20);
    DG_MovePos(&sp10);

    ReadRotMatrix(&sp40);
    DG_SetPos(&sp20);

    GM_Camera.first_person = 1;

    gUnkCameraStruct_800B77B8.eye.vx = sp40.t[0];
    gUnkCameraStruct_800B77B8.eye.vy = sp40.t[1];
    gUnkCameraStruct_800B77B8.eye.vz = sp40.t[2];

    GV_SubVec3(&GM_PlayerPosition, &gUnkCameraStruct_800B77B8.eye, &diff);

    gUnkCameraStruct_800B77B8.rotate2.vx = 320;
    gUnkCameraStruct_800B77B8.rotate2.vz = 0;
    gUnkCameraStruct_800B77B8.rotate2.vy = GV_VecDir2(&diff);

    if (work->unkB1C & 0x4000000)
    {
        if (action == 64)
        {
            msg.address = GV_StrCode("スネーク");
            msg.message_len = 6;
            msg.message[0] = GV_StrCode("run_move");
            msg.message[1] = -250;
            msg.message[2] = 0;
            msg.message[3] = GM_PlayerPosition.vz;
            msg.message[4] = 500;
            msg.message[5] = 0x201;
            GV_SendMessage(&msg);
        }

        if ((action > 64) && !(GM_PlayerStatus & PLAYER_ACT_ONLY))
        {
            work->unkB1C &= ~0x4000000;

            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );
            GM_Camera.first_person = 0;

            if ((work->unkB48 == Johnny_800C64B0) || (work->unkB48 == s03c_johnny_800C5DE4))
            {
                work->unkAD0--;
            }

            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB38 = work->unkB48;
        }
    }
    else if (work->unkB1C & 0x40000000)
    {
        if ((work->unkB48 == Johnny_800C6C10) && (action == 0))
        {
            s03b_boxall_800C9328();
            s03b_boxall_800C93F0(work->unkB78[13], 4);
        }

        if ((action == 65) || s03b_boxall_800C95EC())
        {
            s03b_boxall_800C9328();

            GM_Camera.first_person = 0;
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );

            if ((work->unkB48 == Johnny_800C64B0) || (work->unkB48 == s03c_johnny_800C5DE4))
            {
                work->unkAD0--;
            }

            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB38 = work->unkB48;
            work->unkB1C &= ~0x40000000;
        }
    }
    else if (work->unkB1C & 0x8000000)
    {
        if (action == 0)
        {
            s03b_boxall_800C9328();
            s03b_boxall_800C93F0(work->unkB78[8], 4);
            GCL_ExecProc(work->unkBC0[4], NULL);
        }

        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;

        if (action == 100)
        {
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );
            GM_Camera.first_person = 0;

            if ((work->unkB48 == Johnny_800C64B0) || (work->unkB48 == s03c_johnny_800C5DE4))
            {
                work->unkAD0--;
            }

            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            work->unkB38 = work->unkB48;
        }
    }
    else
    {
        if (action == 0)
        {
            s03b_boxall_800C9328();
            s03b_boxall_800C93F0(work->unkB78[7], 4);
        }

        if (action == 32)
        {
            GM_Camera.first_person = 0;
            work->unkB0C = 7;
            work->unkB10 = 0;
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_PAUSE_ONLY );
        }
    }
}

void Johnny_800C8400(JohnnyWork *work, int action)
{
    int new_action;

    if (action == 0)
    {
        if (work->unkB1C & 0x400)
        {
            work->unkB1C |= 0x200;
            work->unkB1C &= ~0x400;
        }

        if (GV_Time & 1)
        {
            new_action = 16;
        }
        else
        {
            new_action = 17;
        }

        SetAction(work, new_action);
    }
    if (work->object.is_end != 0)
    {
        work->unkB1C &= ~0x200;

        if (work->target->field_26_hp <= 0)
        {
            work->unkB38 = Johnny_800C9144;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            return;
        }

        if (work->unkB70 != 4 && (work->unkB24 & 2))
        {
            work->unkB38 = s03c_johnny_800C6FC0;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            work->unkB38 = s03c_johnny_800C6D84;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }

        if (!(work->unkB1C & 0x10000000))
        {
            GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
            NewPadVibration(johnny_vibration1_800C32C0, 2);
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        }
    }
}

void Johnny_800C873C(JohnnyWork *work, int action);
void Johnny_800C8FE4(JohnnyWork *work, int action);

void Johnny_800C854C(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C |= 0x200;
        SetAction(work, 20);
        work->target->field_26_hp--;
    }

    if (action < 12)
    {
        work->control.turn.vy += 170;
    }

    if (work->object.is_end != 0)
    {
        work->unkB50 = 1;
        if (work->target->field_26_hp > 0)
        {
            work->unkB38 = Johnny_800C873C;
        }
        else
        {
            work->unkB38 = Johnny_800C8FE4;
        }
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    else
    {
        if (action > 16)
        {
            GV_NearExp8V(&work->unkB30.vx, &DG_ZeroVector.vx, 3);
        }
        work->control.step.vx = work->unkB30.vx;
        work->control.step.vz = work->unkB30.vz;
    }
}

void Johnny_800C8654(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        SetAction(work, 19);
        work->control.turn.vy = GM_PlayerControl->turn.vy + 2048;
        work->target->field_26_hp--;
    }
    if (action == 20)
    {
        GM_SeSet(&work->control.mov, 0x8D);
        GM_SeSet(&work->control.mov, SE_HIT_FLOOR);
    }
    if (work->object.is_end != 0)
    {
        work->unkB50 = 2;
        if (work->target->field_26_hp > 0)
        {
            work->unkB38 = Johnny_800C873C;
        }
        else
        {
            work->unkB38 = Johnny_800C8FE4;
        }
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C88C8(JohnnyWork *work, int action);

void Johnny_800C873C(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->control.radar_atr &= ~RADAR_SIGHT;
        work->unkB1C |= 0x200;
        SetTargetClass( work->target, TARGET_DOWN );
        SetAction(work, (work->unkB50 == 1) ? 23 : 24);
    }

    if (work->unkB24 & 8)
    {
        work->target->field_2A = 0;
    }

    if (work->target->field_2A <= 0)
    {
        if (work->unkB4E == 0)
        {
            work->homing->flag = 0;
            Johnny_800C4F24(work, 0);
            GCL_ExecProc(work->unkBC0[5], NULL);
            GCL_ExecProc(work->unkBC0[3], NULL);
            work->unkB4E = 1;
            NewHiyoko_800D0210(&work->object.objs->objs[6].world, -1);
            UnsetTargetClass( work->target, TARGET_FLAG );
            work->unkB1C |= 0x80000000;
        }
        if (++work->unkB4C == 36)
        {
            JohnnyExecProc_800C4D8C(work);
        }
    }
    else if (action == 48)
    {
        work->unkB38 = s03c_johnny_800C88C8;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void s03c_johnny_800C88C8(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        action = (work->unkB50 == 1) ? 25 : 26;
        work->unkB50 = 0;

        SetAction(work, action);
    }

    if (work->unkB24 & 0x8)
    {
        s03b_boxall_800C969C(1, 30000);
        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY;
    }

    if (work->object.is_end != 0)
    {
        UnsetTargetClass( work->target, TARGET_DOWN );
        work->unkB1C &= ~0x200;

        if (work->unkB24 & 0x8)
        {
            work->unkB38 = s03c_johnny_800C7A64;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else if ((work->unkB70 != 4) && (work->unkB24 & 0x2))
        {
            work->unkB38 = s03c_johnny_800C6FC0;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
        else
        {
            work->unkB38 = s03c_johnny_800C6D84;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }

        if (!(work->unkB1C & 0x10000000))
        {
            GM_SeSet2(0, 63, SE_EXCLAMATION);
            NewPadVibration(johnny_vibration1_800C32C0, 2);
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        }

        work->control.radar_atr |= RADAR_SIGHT;
    }
}

void Johnny_800C8C34(JohnnyWork *work, int action);
void Johnny_800C8E84(JohnnyWork *work, int action);
void Johnny_800C8CD4(JohnnyWork *work, int action);
void Johnny_800C8D58(JohnnyWork *work, int action);

int s03c_johnny_800C8A2C(JohnnyWork *work, int action)
{
    if (!(work->target->damaged & 2))
    {
        work->unkB38 = Johnny_800C8C34;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return 1;
    }

    if (GM_PlayerAction == action)
    {
        return 0;
    }

    switch (GM_PlayerAction)
    {
    case 7:
        work->unkB38 = Johnny_800C8B14;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        break;

    case 38:
        work->unkB38 = Johnny_800C8CD4;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return 1;

    case 39:
        work->unkB38 = Johnny_800C8D58;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return 1;

    case 13:
        work->unkB38 = Johnny_800C8E84;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return 1;
    }

    return 0;
}

void Johnny_800C8B14(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        SetAction(work, 27);
        work->unkB1C |= 0x800;
        work->control.turn.vy = GM_PlayerControl->turn.vy;
    }

    if (++work->unkBE4 > 50)
    {
        SetAction(work, 42);

        if (!(work->unkBE4 & 7))
        {
            NewPadVibration(johnny_vibration2_800C32C4, 2);
        }
    }
    if (s03c_johnny_800C8A2C(work, 7) == 0 && (work->unkB24 & 8))
    {
        work->target->field_42 = 0;
        work->target->field_2A = 0;
        GM_SeSet(&work->control.mov, 0x8E);
        work->unkB38 = Johnny_800C8C34;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
}

void Johnny_800C8C34(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        SetAction(work, 30);
    }
    if (action == 12)
    {
        GM_SeSet(&work->control.mov, SE_HIT_FLOOR);
    }
    if (work->object.is_end != 0)
    {
        work->unkB50 = 2;
        work->unkB38 = Johnny_800C873C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C &= ~0x800;
    }
}

void Johnny_800C8CD4(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        GM_SeSet(&work->control.mov, 0x8F);
        SetAction(work, 28);
        work->unkBE4 = 0;
    }
    if (work->object.is_end)
    {
        work->unkB38 = Johnny_800C8B14;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    s03c_johnny_800C8A2C(work, 38);
}

void Johnny_800C8D58(JohnnyWork *work, int action)
{
    SVECTOR svec;

    if (action == 0)
    {
        work->control.radar_atr &= ~RADAR_SIGHT;
        GM_SeSet(&work->control.mov, 0x8E);
        GM_SeSet(&work->control.mov, 0x90);
        SetAction(work, 29);
        work->target->field_26_hp -= 255;
        GM_TotalEnemiesKilled++;
    }
    if (action > 48 && action < 60)
    {
        svec.vx = svec.vy = 0;
        svec.vz = 96;
        DG_RotVector(&svec, &work->control.step, 1);
    }
    if (action == 55)
    {
        GM_SeSet(&work->control.mov, SE_HIT_FLOOR);
    }
    if (work->object.is_end != 0)
    {
        work->unkB50 = 2;
        work->unkB38 = Johnny_800C8FE4;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C &= ~0x800;
    }
}

void Johnny_800C8E84(JohnnyWork *work, int action)
{
    SVECTOR  svec;
    MATRIX   mat;
    CONTROL *control;

    if (action == 0)
    {
        SetAction(work, 27);
    }

    if (++work->unkBE4 > 50)
    {
        SetAction(work, 42);

        if (!(work->unkBE4 & 7))
        {
            NewPadVibration(johnny_vibration2_800C32C4, 2);
        }
    }
    if (s03c_johnny_800C8A2C(work, 13) == 0)
    {
        work->control.turn.vy = GM_PlayerControl->turn.vy;

        DG_SetPos2(&GM_PlayerControl->mov, &GM_PlayerControl->rot);
        DG_MovePos(&s03c_dword_800C32EC);

        ReadRotMatrix(&mat);

        control = &work->control;
        svec.vx = mat.t[0];
        svec.vy = mat.t[1];
        svec.vz = mat.t[2];

        GV_SubVec3(&svec, &control->mov, &work->control.step);

        if (work->unkB24 & 8)
        {
            work->target->field_42 = 0;
            work->target->field_2A = 0;

            GM_SeSet(&control->mov, 0x8E);

            work->unkB38 = Johnny_800C8C34;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }
    }
}

void Johnny_800C8FE4(JohnnyWork *work, int action)
{
    int action_flag;

    if (action == 0)
    {
        work->homing->flag = 0;
        work->control.radar_atr &= ~RADAR_SIGHT;

        if (work->unkB50 == 1)
        {
            action_flag = 23;
        }
        else
        {
            action_flag = 24;
        }

        work->unkB50 = 0;

        SetAction(work, action_flag);
        GM_ConfigControlAttribute(&work->control, 0);

        SetTargetClass( work->target, TARGET_DOWN );

        Johnny_800C4F24(work, 0);
        GCL_ExecProc(work->unkBC0[5], NULL);

        work->unkB1C |= 0x1000;
        work->homing->flag = 0;
    }
    if (action & 2)
    {
        DG_InvisibleObjs(work->object.objs);
        *work->gunlight_pvisible = 0;
    }
    else
    {
        DG_VisibleObjs(work->object.objs);
        *work->gunlight_pvisible = 1;
    }

    if (action == 36)
    {
        work->unkB1C |= 0x1000;
        GCL_ExecProc(work->unkBC0[3], NULL);
        JohnnyExecProc_800C4D8C(work);
        GM_GameStatus &= ~STATE_PADRELEASE;
        GV_DestroyActor(&work->actor);
    }
}

void Johnny_800C9144(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->homing->flag = 0;
        work->control.radar_atr &= ~RADAR_SIGHT;

        SetAction(work, 39);
        UnsetTargetClass( work->target, TARGET_FLAG ) ;
        SetTargetClass( work->target, TARGET_DOWN ) ;
    }

    if (action == 36)
    {
        JohnnyExecProc_800C4D8C(work);
    }

    switch (work->unkB4C)
    {
    case 0:
        if (action == 22)
        {
            GM_SeSetMode(&work->control.mov, SE_ENEMY_COLLAPSE, GM_SEMODE_BOMB);
        }

        if (action == 44)
        {
            GM_SeSetMode(&work->control.mov, SE_HIT_FLOOR, GM_SEMODE_BOMB);
        }

        if (work->object.is_end != 0)
        {
            Johnny_800C4F24(work, 0);
            GCL_ExecProc(work->unkBC0[5], NULL);

            SetAction(work, 40);

            work->unkB4C++;
            NewHiyoko_800D0210(&work->object.objs->objs[6].world, -1);
        }
        break;

    case 1:
        if (++work->unkB4E == 32)
        {
            work->unkB1C |= 0x1000;
            GCL_ExecProc(work->unkBC0[3], NULL);
        }
        break;
    }
}

void Johnny_800C949C(JohnnyWork *work, int arg1);

void Johnny_800C92E0(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        s03b_boxall_800C969C(0, 30000);
        SetAction(work, 0);
        work->unkB1C |= 0x20;
        GM_GameStatus |= STATE_PADRELEASE;
        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.map->hzd,
                                             &work->unkB04);
    }
    if (arg1 == 8)
    {
        GM_SeSetMode(&work->control.mov, 0xC2, GM_SEMODE_BOMB);
    }
    if (arg1 >= 48)
    {
        if (arg1 == 48)
        {
            SetAction(work, 1);
            s03b_boxall_800C93AC(work->unkB78[9]);
            GM_ConfigMotionAdjust(&work->object, work->adjust);
        }
        switch (work->unkB4C)
        {
        case 0:
            sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);
            if (sna_act_unk_helper2_helper3_80060684(&work->sna_auto_move, &work->control.mov) < 500)
            {
                work->unkB4C++;
            }
            break;
        case 1:
            SetAction(work, 0);
            work->unkB4C++;
            break;
        case 2:
            work->control.turn.vy = -1024;
            work->unkB38 = Johnny_800C949C;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
            break;
        }
    }
}

void Johnny_800C949C(JohnnyWork *work, int arg1)
{
    SVECTOR svec;

    s03b_boxall_800C974C();
    if (arg1 == 0)
    {
        if (GM_PlayerStatus & PLAYER_KETCHUP)
        {
            work->unkB1C |= 2;
        }

        work->control.turn.vy = 0;

        SetAction(work, 36);

        GV_SubVec3(&work->control.mov, &GM_PlayerPosition, &svec);
        GM_PlayerControl->turn.vy = GV_VecDir2(&svec);
    }
    if (arg1 == 24)
    {
        GCL_ExecProc(work->unkBC0[1], NULL);
    }
    switch (work->unkB4C)
    {
    case 0:
        if (GM_StreamStatus() == -1)
        {
            GM_ConfigMotionAdjust(&work->object, NULL);
            ClearAdjust(work);

            NewFadeIo_800C4224(0, 32);
            s03b_boxall_800C96E8();
            work->unkB4C++;
        }
        break;
    case 1:
        if (++work->unkB4E == 80)
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            Johnny_800C4CCC(work);
        }
        break;
    }
}

void Johnny_800C9644(JohnnyWork *work)
{
    int     i;
    int     message_len;
    GV_MSG *msgs;

    if (work->control.n_messages == 0)
    {
        return;
    }

    msgs = &work->control.messages[work->control.n_messages] - 1;
    for (i = work->control.n_messages; i > 0; i--, msgs--)
    {
        message_len = msgs->message_len;
        if (message_len >= 2 && msgs->message[0] == 0x10BA)
        {
            if (msgs->message[1] == HASH_ON)
            {
                work->unkB1C &= ~0x100000;
            }
            else if (msgs->message[1] == HASH_OFF)
            {
                work->unkB1C |= 0x100000;
            }
        }
    }
}

void Johnny_800C96F4(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB1C |= 0x80000000;
        if ((work->unkB1C & 0x400000) && work->unkB54 == 1)
        {
            work->unkB54 = 0;
            work->unkB38 = Johnny_800C92E0;
        }
        else
        {
            work->unkB38 = Johnny_800C59B8;
        }
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    if (work->unkB38 != Johnny_800C92E0 && work->unkB38 != Johnny_800C949C && work->unkB38 != s03c_johnny_800C7F78 &&
        work->unkB38 != Johnny_800C6850)
    {
        s03c_johnny_800C45AC(work);
        if (work->unkB38 != s03c_johnny_800C7F78)
        {
            if (work->unkB1C & 0x40000000)
            {
                work->unkB1C &= ~0x40000000; // Why not do it unconditionally!?
            }
            s03c_johnny_800C424C(work, Johnny_800C59B8);
            if (work->unkB38 != s03c_johnny_800C5520 && work->unkB38 != Johnny_800C588C && field_B10 >= 480 &&
                GM_StreamStatus() == -1)
            {
                work->unkB10 = 0;
                if (work->unkB1C & 0x400000)
                {
                    work->unkB1C |= 8;
                    work->unkB14 = 2;
                    work->unkB54++;
                }
                else if (work->unkB1C & 4)
                {
                    work->unkB1C |= 8;
                    work->unkB14 = 1;
                    work->unkB1C &= ~4;
                }
                else
                {
                    work->unkB1C |= 8;
                    work->unkB14 = 3;
                    work->unkB1C |= 4;
                }
            }
        }
    }
}

void Johnny_800C98B0(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB38 = Johnny_800C57D0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
    }
}

void Johnny_800C98E4(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB38 = s03c_johnny_800C5DE4;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
        Johnny_800C4720(work, 0);
    }
    if (work->unkB38 != s03c_johnny_800C7F78)
    {
        s03c_johnny_800C45AC(work);
        if (work->unkB38 != s03c_johnny_800C7F78)
        {
            if (work->unkB1C & 0x40000000)
            {
                work->unkB1C &= ~0x40000000; // Why not do it unconditionally!?
            }
        }
    }
}

void Johnny_800C998C(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB38 = Johnny_800C6054;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
        Johnny_800C4720(work, 1);
    }
}

void s03c_johnny_800C99D8(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->unkB1C |= 0x80000000;

        work->unkB38 = Johnny_800C6204;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;

        work->unkB1C |= 0x24;
        work->control.radar_atr |= RADAR_SIGHT;

        if (s03c_dword_800C33D8 == 1)
        {
            s03c_dword_800C33D8 = 0;
            work->unkB38 = Johnny_800C6418;
            work->unkB4E = 0;
            work->unkB4C = 0;
            work->unkB3C = 0;
        }

        Johnny_800C4720(work, 2);
    }

    if ((work->unkB70 == 4) && !(work->unkB24 & 0x2))
    {
        work->unkB14 = 8;
        work->unkB1C |= 0x8;
    }
    else if (!(work->unkB1C & 0x20))
    {
        if (work->unkB70 == 4)
        {
            work->unkB1C &= ~0x80000000;
            work->unkB1C |= 0x8;
            work->unkB14 = 8;
        }
        else if (work->unkB38 != s03c_johnny_800C7F78)
        {
            s03c_johnny_800C45AC(work);

            if ((work->unkB38 != s03c_johnny_800C7F78) && (work->unkB1C & 0x40000000))
            {
                work->unkB1C &= ~0x40000000;
            }
        }
    }
}

void Johnny_800C9B3C(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB1C |= 0x80000000 | 0x4;
        Johnny_800C4720(work, 2);
        work->unkB0C = 4;
        work->unkB38 = Johnny_800C64B0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkAD0 += 2;
        work->unkB1C |= 0x20;
    }
}

void Johnny_800C9BB4(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        s03c_dword_800C32C8 = 1;
        work->unkB38 = Johnny_800C6918;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
        work->control.radar_atr |= RADAR_UNK4;
    }
    work->jfamas_trigger = 0;
    s03c_johnny_800C5168(work);
    Johnny_800C4A64(work);
}

void Johnny_800C9C2C(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        s03c_dword_800C32C8 = 2;
        work->unkB38 = Johnny_800C794C;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB50 = 0;
        work->control.radar_atr |= RADAR_UNK4;
        work->unkB1C |= 0x80000000;
    }
    work->jfamas_trigger = 0;
    s03c_johnny_800C5168(work);
    Johnny_800C4A64(work);
}

void Johnny_800C9CA8(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        s03c_dword_800C32C8 = 3;
        work->control.radar_atr |= RADAR_UNK4;
        work->unkB1C &= ~0x80000000;
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[13], 4);
        NewPadVibration(johnny_vibration1_800C32C0, 2);
        GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        work->unkB38 = s03c_johnny_800C6D84;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
    }
    work->jfamas_trigger = 0;
    s03c_johnny_800C5168(work);
    Johnny_800C4A64(work);
}

void Johnny_800C9D64(JohnnyWork *work)
{
    int         field_B10;
    int         field_B3C;
    TJohnnyFunc field_B38;
    int         status;

    Johnny_800C9644(work);
    Johnny_800C4418(work);
    Johnny_800C44F8(work);
    Johnny_800C4DCC(work);
    Johnny_800C4E5C(work);
    Johnny_800C50D0(work);
    s03b_boxall_800C9404();
    if (work->object.objs->adjust)
    {
        sna_act_helper2_helper2_80033054(GV_StrCode("ジョニー"), &work->adjust[6]); // ジョニー = Joni = Johnny
    }
    if (work->unkB1C & 0x10000000)
    {
        GM_AlertLevel = 0xFF;
    }
    field_B10 = work->unkB10;
    if (work->unkB10 < 16000)
    {
        work->unkB10++;
    }
    switch (work->unkB0C)
    {
    case 0:
        Johnny_800C96F4(work, field_B10);
        break;
    case 1:
        Johnny_800C98B0(work, field_B10);
        break;
    case 2:
        Johnny_800C98E4(work, field_B10);
        break;
    case 3:
        Johnny_800C998C(work, field_B10);
        break;
    case 4:
        s03c_johnny_800C99D8(work, field_B10);
        break;
    case 5:
        Johnny_800C9B3C(work, field_B10);
        break;
    case 6:
        Johnny_800C9BB4(work, field_B10);
        break;
    case 7:
        Johnny_800C9C2C(work, field_B10);
        break;
    case 8:
        Johnny_800C9CA8(work, field_B10);
        break;
    }
    field_B38 = work->unkB38;
    field_B3C = work->unkB3C;
    status = GM_StreamStatus();
    if (status == -1 || status == 2)
    {
        work->unkB3C++;
    }
    if (work->unkB3C == 0)
    {
        work->unkB3C = 1;
    }
    field_B38(work, field_B3C);
    Johnny_800C4E9C(work);
    Johnny_800C4FAC(work);
    if (!(work->unkB1C & 2) && GM_KetchupFlag == 0)
    {
        work->unkB1C |= 2;
        GM_KetchupFlag = -1;
    }
}

void JohnnyAct_800C9F7C(JohnnyWork *work)
{
    CONTROL *control;

    GM_ActMotion(&work->object);
    control = &work->control;
    GM_ActControl(control);
    GM_ActObject(&work->object);
    GM_MoveTarget(work->target, &control->mov);
    DG_GetLightMatrix2(&control->mov, work->light);
    work->control.height = work->object.height;
    work->sna_auto_move.field_0_ivec.vx = HZD_GetAddress(
        work->control.map->hzd, &control->mov, work->sna_auto_move.field_0_ivec.vx);
    Johnny_800C9D64(work);
    if (work->unkB30.vy < 0 && work->control.level_flag != 0)
    {
        work->unkB30.vy = 0;
    }
    work->unkB30.vy -= 32;
    work->control.step.vy += work->unkB30.vy;
}

void JohnnyDie_800CA048(JohnnyWork *work)
{
    GV_ACT *shadow;
    GV_ACT *jfamas;
    GV_ACT *gunlight;

    GM_FreeHomingTarget(work->homing);
    shadow = work->shadow;
    if (shadow != NULL)
    {
        GV_DestroyOtherActor(shadow);
    }
    jfamas = work->jfamas;
    if (jfamas != NULL)
    {
        GV_DestroyOtherActor(jfamas);
    }
    gunlight = work->gunlight;
    if (gunlight != NULL)
    {
        GV_DestroyOtherActor(gunlight);
    }
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
    s03b_boxall_800C9328();
}

int JohnnyConfigTarget_800CA0E0(JohnnyWork *work)
{
    TARGET *target;

    work->target = target = GM_AllocTarget();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x9F, 2, &s03c_dword_800C32F4);
    GM_Target_8002DCCC(target, 1, -1, 0xC0, 0xA, &DG_ZeroVector);
    work->homing = GM_AllocHomingTarget(&work->object.objs->objs[6].world, &work->control);
    work->homing->flag = 1;
    return 0;
}

// Duplicate of s03b_revolver_800C8DD0
int Johnny_800CA184(HZD_PAT *route, int *n_out, SVECTOR *out)
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

int Johnny_800CA1E8(JohnnyWork *work)
{
    HZD_PAT *routes;
    int     *n_out;
    int      n_routes;
    int      i;

    n_out = work->unk83C;
    n_routes = work->control.map->hzd->header->n_routes;
    routes = work->control.map->hzd->header->routes;
    for (i = 0; i < n_routes; routes++, n_out++, i++)
    {
        if (Johnny_800CA184(routes, n_out, work->unk850[i]) < 0)
        {
            return -1;
        }
    }

    work->unkAFC = work->unk850[0][0];
    work->unkB04 = work->unk850[4][0];
    work->unkAD0 = work->unk850[0];
    work->unkB60 = work->unk850[0][0];
    work->unkAD8 = 0;
    work->unkAD4 = 0;
    return 0;
}

void Johnny_800CA304(JohnnyWork *work)
{
    char *option;

    work->jfamas = NewJFamas_800CAFAC(&work->control, &work->object, 4, &work->jfamas_trigger);
    work->gunlight = NewGunLight_800D3AD4(&work->object.objs->objs[4].world, &work->gunlight_pvisible);
    work->unkB5A = 0;
    work->unkB58 = 0;
    work->unkB5E = 0;
    work->unkB5C = 0;

    option = GCL_GetOption('m');
    if (option != NULL)
    {
        work->unkB0C = GCL_StrToInt(option);
    }
    else
    {
        work->unkB0C = 0;
    }

    work->unkB14 = 0;
    work->unkB10 = 0;
    work->unkB18 = 0;
    work->unkB1C = 0;
    if (work->unkB0C == 4)
    {
        work->unkB1C = 0x20;
    }

    option = GCL_GetOption('f');
    if (option != NULL)
    {
        work->unkB70 = GCL_StrToInt(option);
        if (work->unkB70 == 3)
        {
            work->unkB1C |= 2;
        }
    }

    option = GCL_GetOption('b');
    if (option != NULL)
    {
        if (GCL_StrToInt(option) == 1)
        {
            work->unkB1C |= 1;
        }
    }

    option = GCL_GetOption('c');
    if (option != NULL)
    {
        work->unkB6C = GCL_StrToInt(option);
    }
    else
    {
        work->unkB6C = 0;
    }

    option = GCL_GetOption('s');
    if (option != NULL)
    {
        work->unkB6E = GCL_StrToInt(option);
    }
    else
    {
        work->unkB6E = 0;
    }

    if (work->unkB6C == 1)
    {
        if (work->unkB6E == 0)
        {
            work->unkB1C |= 0x400000;
        }
    }
    else
    {
        work->unkB1C |= 0x4000;
    }

    if (work->unkB6C >= 3U)
    {
        work->unkB1C |= 0x2000000;
    }

    if (work->unkB70 >= 2U)
    {
        work->unkB1C |= 0x800000 | 0x4000;
    }

    work->unkB24 = 0;
    work->unkB38 = NULL;
    work->unkB3C = 0;
    work->unkB44 = 0;
    work->unkB4E = 0;
    work->unkB4C = 0;
    work->unkB52 = 0;
    work->unkB50 = 0;
    work->unkB56 = 0;
    work->unkB54 = 0;
    work->unkB74 = 0;
    work->unkB1C |= 0x20000000;
    work->player_status = GM_PlayerStatus & ~STATE_SHOW_RADAR;
    work->unkB30 = DG_ZeroVector;
    sub_80060548(&work->sna_auto_move, work->control.map->hzd, &work->control.mov);
}

void Johnny_800CA574(JohnnyWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('v'))
    {
        return;
    }

    i = 0;
    out = work->unkB78;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 18)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

void Johnny_800CA5EC(JohnnyWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('e'))
    {
        return;
    }

    i = 0;
    out = work->unkBC0;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 8)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

int JohnnyGetResources_800CA664(JohnnyWork *work, int scriptData, int scriptBinds)
{
    SVECTOR     indices;
    CONTROL    *control;
    OBJECT     *object;
    RADAR_CONE *cone;

    control = &work->control;
    if (GM_InitControl(control, scriptData, scriptBinds) >= 0)
    {
        GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
        GM_ConfigControlHazard(control, control->mov.vy, 450, 450);
        control->exclude_flag = 2;
        GM_ConfigControlAttribute(control, 5);

        cone = &work->control.radar_cone;
        cone->len = 6000;
        cone->ang = 1024;

        object = &work->object;
        GM_InitObject(object, GV_StrCode("johnny"), 0x32D, GV_StrCode("joh_03c"));
        GM_ConfigObjectJoint(object);
        GM_ConfigMotionControl(object, &work->motion, GV_StrCode("joh_03c"), work->oar1, work->oar2,
                               control, work->rots);
        GM_ConfigObjectLight(object, work->light);
        GM_ConfigObjectAction(object, 0, 0, 0);
        GM_ConfigControlTrapCheck(control);
        if (JohnnyConfigTarget_800CA0E0(work) >= 0 && Johnny_800CA1E8(work) >= 0)
        {
            Johnny_800CA574(work);
            Johnny_800CA5EC(work);
            Johnny_800CA304(work);

            indices.vx = 0;
            indices.vy = 6;
            indices.vz = 12;
            indices.pad = 15;
            work->shadow = NewShadow_800602CC(control, object, indices);
            if (work->shadow != NULL)
            {
                s03b_boxall_800C9328();
                return 0;
            }
        }
    }
    return -1;
}

void *NewJohnny_800CA838(int scriptData, int scriptBinds)
{
    JohnnyWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(JohnnyWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, JohnnyAct_800C9F7C, JohnnyDie_800CA048, "johnny.c");
    if (JohnnyGetResources_800CA664(work, scriptData, scriptBinds) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }
    return (void *)work;
}
