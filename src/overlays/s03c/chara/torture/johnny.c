#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "libgcl/hash.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/homing_target.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Game/vibrate.h"
#include "chara/snake/shadow.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/sna_hzd.h"
#include "Okajima/blood.h"
#include "unknown.h"
#include "common.h"
#include "overlays/s03a/Okajima/hiyoko.h"

struct JohnnyWork;
typedef void (*TJohnnyFunc)(struct JohnnyWork *work, int action);

typedef struct JohnnyWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    OAR_RECORD     oar1[0x11];
    OAR_RECORD     oar2[0x11];
    SVECTOR        rots[16];
    SVECTOR        rots2[16];
    MATRIX         light[2];
    char           pad7D8[0x48];
    TARGET        *target;
    HOMING        *homing;
    GV_ACT        *jfamas;
    GV_ACT        *gunlight;
    int           *gunlight_pvisible;
    int            jfamas_trigger;
    ShadowWork    *shadow;
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

#define EXEC_LEVEL 5

unsigned char johnny_vibration1_800C32C0[] = {0xFF, 0x0A, 0x00, 0x00};
unsigned char johnny_vibration2_800C32C4[] = {0xFF, 0x04, 0x00, 0x00};

int s03c_dword_800C32C8 = 0x00000000;

SVECTOR s03c_dword_800C32CC = {0, 0, 7000};
SVECTOR s03c_dword_800C32D4 = {0, 0, 100};
SVECTOR s03c_dword_800C32DC = {64512, 0, 0};

int s03c_dword_800C32E4 = 0x00000000;
int s03c_dword_800C32E8 = 0x00000DAC;

SVECTOR s03c_dword_800C32EC = {0, 0, 300};
SVECTOR s03c_dword_800C32F4 = {300, 750, 300};

extern SVECTOR          DG_ZeroVector_800AB39C;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern int              GM_AlertLevel_800ABA18;
extern int              GV_Time_800AB330;
extern int              GM_PlayerAction_800ABA40;
extern OBJECT          *GM_PlayerBody_800ABA20;

void    s03b_boxall_800C9328(void);
void    s03b_boxall_800C9404(void);
void    s03b_boxall_800C96E8(void);
void    s03b_boxall_800C974C(void);
void    s03b_boxall_800C93F0(int, int);
void    s03b_boxall_800C969C(int, int);
int     s03b_boxall_800C93AC(int arg0);
GV_ACT *NewGunLight_800D3AD4(MATRIX *world, int **pvisible);
GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *trigger);
GV_ACT *NewFadeIo_800C4224(int name, int where);
void   *AN_Unknown_800CA1EC(MATRIX *mat, int mark);

void s03c_johnny_800C7F78(JohnnyWork *work, int action);

int Johnny_800C4194(JohnnyWork *work)
{
    SVECTOR player_pos;
    SVECTOR control_mov;

    player_pos = GM_PlayerPosition_800ABA10;
    control_mov = work->control.field_0_mov;
    if (sub_80028454(work->control.field_2C_map->field_8_hzd, &player_pos, &control_mov, 0xC, 0) == 0)
    {
        return -1;
    }

    sub_80028890(&control_mov);
    GV_SubVec3_80016D40(&control_mov, &player_pos, &player_pos);
    return GV_VecLen3_80016D80(&player_pos);
}

void s03c_johnny_800C5520(JohnnyWork *work, int arg1);
void Johnny_800C588C(JohnnyWork *work, int arg1);

void s03c_johnny_800C424C(JohnnyWork *work, TJohnnyFunc func)
{
    if (work->unkB1C & 0x100000)
    {
        return;
    }

    if (work->unkB38 != s03c_johnny_800C5520 && work->unkB38 != Johnny_800C588C && GM_StreamStatus_80037CD8() == -1 &&
        GV_Time_800AB330 % 320 == 0)
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

    svec2 = work->control.field_0_mov;
    svec2.vy = 0;

    GV_SubVec3_80016D40(work->unkAD0, &svec2, &svec1);
    work->control.field_4C_turn.vy = GV_VecDir2_80016EF8(&svec1);

    if (GV_VecLen3_80016D80(&svec1) < 320)
    {
        work->unkAD4 = 1;
    }
}

int Johnny_800C4388(JohnnyWork *work, int hash)
{
    int             i;
    unsigned short *field_8_array;

    if (work->unkB5C != 0)
    {
        return 1;
    }

    field_8_array = work->control.field_10_events.field_8_array;

    for (i = work->control.field_10_events.field_6_count; i > 0; i--, field_8_array++)
    {
        if (*field_8_array == hash)
        {
            return 1;
        }
    }
    return 0;
}

int Johnny_800C43D0(unsigned short hash)
{
    int             i;
    unsigned short *field_8_array;

    field_8_array = GM_PlayerControl_800AB9F4->field_10_events.field_8_array;

    for (i = GM_PlayerControl_800AB9F4->field_10_events.field_6_count; i > 0; i--, field_8_array++)
    {
        if (*field_8_array == hash)
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
    unsigned short *field_8_array;

    new_unkB24 = 0;

    field_8_array = GM_PlayerControl_800AB9F4->field_10_events.field_8_array;
    for (i = GM_PlayerControl_800AB9F4->field_10_events.field_6_count; i > 0; i--, field_8_array++)
    {
        if (*field_8_array == 0x41A5)
        {
            new_unkB24 |= 2;
        }
        if (*field_8_array == 0x6599)
        {
            new_unkB24 |= 8;
        }
    }

    if (GM_PlayerStatus_800ABA50 & 2)
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
    if ((work->player_status & PLAYER_UNK100000) != (GM_PlayerStatus_800ABA50 & PLAYER_UNK100000))
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_UNK100000)
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
    work->player_status = GM_PlayerStatus_800ABA50;
}

void s03c_johnny_800C4588(JohnnyWork* work) {
    
    TJohnnyFunc temp_v1;

    temp_v1 = work->unkB38;
    work->unkB38 = (TJohnnyFunc)s03c_johnny_800C7F78;
    
    work->unkB4E = 0;
    work->unkB4C = 0;
    work->unkB3C = 0;
    
    work->unkB48 = temp_v1;
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C45AC.s")
void s03c_johnny_800C45AC(JohnnyWork *work);

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
    SVECTOR *rots2;
    int      to;

    GV_SubVec3_80016D40(&s03c_dword_800C32CC, &work->control.field_0_mov, &svec);
    to = (GV_VecDir2_80016EF8(&svec) - work->control.field_8_rot.vy) & 0xFFF;
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

    rots2 = work->rots2;
    rots2[6].vy = GV_NearExp4_800263B0(rots2[6].vy, to);
}

void Johnny_800C47C4(JohnnyWork *work)
{
    SVECTOR pos;

    GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &work->control.field_0_mov, &pos);
    work->control.field_4C_turn.vy = GV_VecDir2_80016EF8(&pos);
}

int Johnny_800C4804(JohnnyWork *work)
{
    SVECTOR svec1, mov;

    mov = work->control.field_0_mov;
    mov.vy = GM_PlayerPosition_800ABA10.vy;
    GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &mov, &svec1);
    return GV_VecLen3_80016D80(&svec1);
}

int Johnny_800C4860(JohnnyWork *work)
{
    SVECTOR svec;
    int     vecdir;
    int     rotvy;

    GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &work->control.field_0_mov, &svec);
    vecdir = GV_VecDir2_80016EF8(&svec);
    rotvy = work->control.field_8_rot.vy & 0xFFF;

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

void s03c_johnny_800C4934(JohnnyWork *work)
{
    SVECTOR  svec1;
    SVECTOR  svec2;
    SVECTOR  svec3;
    SVECTOR  svec4;
    SVECTOR *rots2;
    int      vecdir;

    svec2.vx = GM_PlayerBody_800ABA20->objs->objs[5].world.t[0];
    svec2.vy = GM_PlayerBody_800ABA20->objs->objs[5].world.t[1];
    svec2.vz = GM_PlayerBody_800ABA20->objs->objs[5].world.t[2];

    svec3.vx = work->object.objs->objs[9].world.t[0];
    svec3.vy = work->object.objs->objs[9].world.t[1];
    svec3.vz = work->object.objs->objs[9].world.t[2];

    GV_SubVec3_80016D40(&svec2, &svec3, &svec1);

    svec4.vz = SquareRoot0(svec1.vx * svec1.vx + svec1.vz * svec1.vz);
    svec4.vx = svec1.vy;

    vecdir = -GV_VecDir2_80016EF8(&svec4);
    if (vecdir < -2048)
    {
        vecdir += 4096;
    }

    rots2 = work->rots2;

    rots2[2].vx = GV_NearExp4_800263B0(rots2[2].vx, vecdir);
    rots2[6].vx = GV_NearExp4_800263B0(rots2[6].vx, vecdir);
    rots2[7].vx = GV_NearExp4_800263B0(rots2[7].vx, vecdir);
    rots2[6].vy = 0;
}

void Johnny_800C4A64(JohnnyWork *work)
{
    TARGET *target;

    target = work->target;
    target->field_6_flags &= ~TARGET_PUSH;
    sub_8002DA14(target);
}

void JohnnyExecProc_800C4A98(JohnnyWork *work, int arg)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    args.argv = argv;
    argv[0] = arg;

    GCL_ExecProc_8001FF2C(work->unkBC0[2], &args);
}

void JohnnySendEnter_800C4AD0(JohnnyWork *work, int hash)
{
    GV_MSG msg;

    msg.address = hash;
    msg.message[0] = GV_StrCode_80016CCC("入る"); // 入る = enter (HASH_ENTER)
    msg.message[1] = work->control.field_30_scriptData;
    msg.message_len = 2;

    GV_SendMessage_80016504(&msg);
    if (hash == GV_StrCode_80016CCC("rou_tobira"))
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
    msg.message[0] = GV_StrCode_80016CCC("出る"); // 出る = leave (HASH_LEAVE)
    msg.message[1] = work->control.field_30_scriptData;
    msg.message_len = 2;

    GV_SendMessage_80016504(&msg);
    if (hash == GV_StrCode_80016CCC("rou_tobira"))
    {
        work->unkB5C = 0;
        JohnnyExecProc_800C4A98(work, 0);
    }
    else
    {
        work->unkB5E = 0;
    }
}

const char s03c_dword_800D7554[] = {0x0, 0x0, 0x0, 0x0};
const int  s03c_dword_800D7558 = 0x800C7CB0;
const int  s03c_dword_800D755C = 0x800C7CEC;
const int  s03c_dword_800D7560 = 0x800C7D54;
const int  s03c_dword_800D7564 = 0x800C7D54;
const int  s03c_dword_800D7568 = 0x800C7E94;
const int  s03c_dword_800D756C = 0x800C7F1C;
const char s03c_dword_800D7570[] = {0xa5, 0xb9, 0xa5, 0xcd};
const char s03c_dword_800D7574[] = {0xa1, 0xbc, 0xa5, 0xaf};
const char s03c_dword_800D7578[] = {0x0, 0x0, 0x0, 0x0};
const char s03c_aRunmove_800D757C[] = "run_move";

void Johnny_800C4BDC(JohnnyWork *work, int a1, int a2, TJohnnyFunc func)
{
    work->unkB58 = a1;
    work->unkB5A = a2;
    work->unkB44 = func;
}

void Johnny_800C4BEC(JohnnyWork *work, int index)
{
    MATRIX rot;

    DG_SetPos_8001BC44(&work->object.objs->objs[index].world);
    DG_MovePos_8001BD20(&s03c_dword_800C32D4);
    DG_RotatePos_8001BD64(&s03c_dword_800C32DC);
    ReadRotMatrix(&rot);
    NewBlood_80072728(&rot, 1);
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

        GCL_ExecProc_8001FF2C(work->unkBC0[0], &args);
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void JohnnyExecProc_800C4D8C(JohnnyWork *work)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    args.argv = argv;
    argv[0] = s03c_dword_800C32C8;

    GCL_ExecProc_8001FF2C(work->unkBC0[6], &args);
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
            GM_SeSet_80032858(&work->unkB04, 0x58);
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
    DG_TransposeMatrix_8001EAD8(&mat1, &mat2);
    MulMatrix0(&mat2, world, &mat2);
    DG_MatrixRotZYX_8001E92C(&mat2, &svec);
    SetRotMatrix(&mat1);
    work->control.field_3C.vx = svec.vy + work->control.field_8_rot.vy;
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
        GM_AlertModeSet_8002EA68(3);
        return;
    }
    work->unkB1C &= ~0x10000000;
    GM_AlertModeSet_8002EA68(0);
    GM_AlertLevel_800ABA18 = 0;
}

void Johnny_800C4FAC(JohnnyWork *work)
{
    CONTROL *control;
    int      frame;

    frame = work->motion.field_04_info1.field_2_footstepsFrame;
    control = &work->control;

    switch (work->object.action_flag)
    {
    case 1:
        if (frame == 0)
        {
            sub_80032BC4(&control->field_0_mov, 160, 1500);
        }
        if (frame == 12)
        {
            sub_80032BC4(&control->field_0_mov, 161, 1500);
        }
        break;

    case 2:
    case 33:
        if (frame == 0)
        {
            sub_80032BC4(&control->field_0_mov, 160, 1500);
        }
        if (frame == 8)
        {
            sub_80032BC4(&control->field_0_mov, 161, 1500);
        }
        break;
    }
}

void Johnny_800C7428(JohnnyWork *work, int action);
void Johnny_800C6C10(JohnnyWork *work, int action);
void s03c_johnny_800C7F78(JohnnyWork *work, int action);

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
    if (!(work->unkB1C & 0x10) || !(GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON_DUCT))
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
    target->field_3E = 0;
    target->field_28 = 0;
    target->field_6_flags &= ~(TARGET_TOUCH | TARGET_POWER | TARGET_CAPTURE);
    target->field_2C_vec = DG_ZeroVector_800AB39C;
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5168.s")
void s03c_johnny_800C5168(JohnnyWork *work);

void Johnny_800C54A8(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5520.s")
void s03c_johnny_800C5520(JohnnyWork *work, int arg1);

void s03c_johnny_800C5A7C(JohnnyWork *work, int arg1);

void Johnny_800C57D0(JohnnyWork *work, int arg1)
{
    int action_flag;

    if (arg1 == 0)
    {
        work->control.field_4C_turn.vy = 3072;
        work->unkB74 = -1;
        work->unkB1C |= 0x20;

        if (GV_Time_800AB330 & 1)
        {
            action_flag = 10;
        }
        else
        {
            action_flag = 11;
        }

        if (work->object.action_flag != action_flag)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, action_flag, 0, 4);
        }
    }
    if (arg1 == 24)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x92);
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
        GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &work->control.field_0_mov, &svec);
        work->control.field_4C_turn.vy = GV_VecDir2_80016EF8(&svec);
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[12], 4);
    }
    if (arg1 > 16)
    {
        status = GM_StreamStatus_80037CD8();
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C594C.s")
void s03c_johnny_800C594C(JohnnyWork *work);

void Johnny_800C59B8(JohnnyWork *work, int arg1)
{
    if (arg1 == 0)
    {
        work->control.field_4C_turn.vy = 3072;
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
    }
    GV_NearExp2V_8002667C(&work->control.field_0_mov.vx, &work->unkAFC.vx, 3);
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5A7C.s")
void s03c_johnny_800C5A7C(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5DE4.s")
void s03c_johnny_800C5DE4(JohnnyWork *work, int arg1);

void Johnny_800C6268(JohnnyWork *work, int action);

void Johnny_800C6054(JohnnyWork *work, int action)
{
    int index;

    if (action == 0)
    {
        work->unkB74 = -1;
        work->unkB1C |= 0x20;
        if (work->object.action_flag != 31)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 31, 0, 4);
        }
        index = !(work->unkB1C & 0x800000) ? 1 : 2;
        work->unkB1C |= 0x800000;
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[index], 4);
        GM_SeSet2_80032968(0, 0x3F, 0xB4);
    }
    if (work->unkB4C == 0)
    {
        if (work->object.is_end != 0)
        {
            if (work->object.action_flag != 32)
            {
                GM_ConfigObjectAction_80034CD4(&work->object, 32, 0, 4);
            }
            work->unkB4C = 1;
        }
    }
    else if (GM_StreamStatus_80037CD8() == -1)
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
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
        work->control.field_3A_radar_atr &= ~RADAR_SIGHT;
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
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
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
        if (work->object.action_flag != 33)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 33, 0, 4);
        }
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
        work->control.field_4C_turn.vy = 0;
        if (work->object.action_flag != 10)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 10, 0, 4);
        }
        s03b_boxall_800C93AC(work->unkB78[5]);
    }
    if (work->object.is_end != 0)
    {
        if (work->object.action_flag == 10)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
            work->unkB4C++;
        }
    }
    if (work->object.action_flag == 0 && GM_StreamStatus_80037CD8() == -1)
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

void Johnny_800C6418(JohnnyWork *work)
{
    work->unkB1C |= 0x20;
    if (work->object.action_flag != 0)
    {
        GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
    }
    work->control.field_0_mov.vx = 6000;
    work->control.field_0_mov.vz = 750;
    work->control.field_8_rot.vy = 1024;
    work->control.field_4C_turn.vy = 1024;
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
        if (work->object.action_flag != 1)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 1, 0, 4);
        }

        if (!(work->unkB1C & 0x1000000))
        {
            GM_SeSet2_80032968(0, 0x3F, 0xB3);
            GM_SeSet2_80032968(0, 0x3F, 0xB6);
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
        if (work->object.action_flag != 6)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 6, 0, 4);
        }
        work->control.field_4C_turn.vy = (work->unkAD0->pad & 0x1F) * 512;
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C66A4.s")

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
        if (work->object.action_flag != 35)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 35, 0, 4);
        }
        GM_SeSet2_80032968(0, 0x3F, 0xB5);
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
        GM_ConfigMotionAdjust_80035008(object, work->rots2);
        if (work->object.action_flag != 2)
        {
            GM_ConfigObjectAction_80034CD4(object, 2, 0, 4);
        }
        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.field_2C_map->field_8_hzd,
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C69D8.s")
void s03c_johnny_800C69D8(JohnnyWork *work, int arg1);

void Johnny_800C6C10(JohnnyWork *work, int action)
{
    OBJECT *object;
    int     unkB1C;
    int     i;

    if (action == 0)
    {
        object = &work->object;

        work->control.field_3A_radar_atr &= ~RADAR_UNK4;

        work->unkB1C |= 0x80000000;

        GM_ConfigMotionAdjust_80035008(object, work->rots2);

        if (work->object.action_flag != 1)
        {
            GM_ConfigObjectAction_80034CD4(object, 1, 0, 4);
        }

        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.field_2C_map->field_8_hzd,
                                             work->unk850[0]);

        unkB1C = work->unkB1C;

        work->unkB1C &= ~0x40;

        if (unkB1C & 0x100)
        {
            work->unkB1C &= ~0x100;
            work->unkB1C |= 2;
        }

        GM_GameStatus_800AB3CC &= ~0x10000000;

        Johnny_800C4F24(work, 0);
    }

    Johnny_800C4734(work);
    sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);

    if (sub_800606E4(&work->sna_auto_move, &work->control.field_0_mov, 250))
    {
        GM_ConfigMotionAdjust_80035008(&work->object, NULL);

        for (i = 0; i < 16; i++)
        {
            work->rots2[i] = DG_ZeroVector_800AB39C;
        }

        work->unkB14 = 2;
        work->unkB1C |= 8;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6D84.s")
void s03c_johnny_800C6D84(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6FC0.s")
void s03c_johnny_800C6FC0(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7160.s")
void s03c_johnny_800C7160(JohnnyWork *work, int arg1);

void Johnny_800C7378(JohnnyWork *work, int arg1)
{
    OBJECT *object;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        object = &work->object;
        GM_ConfigMotionAdjust_80035008(object, work->rots2);
        if (work->object.action_flag != 8)
        {
            GM_ConfigObjectAction_80034CD4(object, 8, 0, 4);
        }
        Johnny_800C4F24(work, 1);
    }
    if (arg1 == 32)
    {
        work->unkB38 = s03c_johnny_800C7160;
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
        GM_SeSet2_80032968(0, 0x3F, 0x53);
        NewPadVibration_8005D58C(johnny_vibration1_800C32C0, 2);
        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
        if (work->object.action_flag != 5)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 5, 0, 4);
        }
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C753C.s")
void s03c_johnny_800C753C(JohnnyWork *work, int arg1);

void Johnny_800C794C(JohnnyWork *work, int arg1);

void Johnny_800C7804(JohnnyWork *work, int arg1)
{
    SVECTOR svec;

    if (arg1 == 0)
    {
        work->unkB1C &= ~0x80000000;
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }

        AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 3);

        work->unkB60 = GM_PlayerPosition_800ABA10;
        work->unkB60.pad = GM_PlayerControl_800AB9F4->field_4C_turn.vy;
    }

    GV_SubVec3_80016D40(&GM_PlayerPosition_800ABA10, &work->unkB60, &svec);

    if (GV_VecLen3_80016D80(&svec) < 5)
    {
        if (ABS(work->unkB60.pad - GM_PlayerControl_800AB9F4->field_4C_turn.vy) >= 5)
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
        if (work->object.action_flag != 5)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 5, 0, 4);
        }
    }
    Johnny_800C47C4(work);
    if (work->object.is_end != 0)
    {
        if (work->unkB50 == 3)
        {
            work->unkB50 = 0;
            work->unkB44 = &s03c_johnny_800C6FC0;
            AN_Unknown_800CA1EC(&work->object.objs->objs[6].world, 0);
            GM_SeSet2_80032968(0, 0x3F, 0x53);
            NewPadVibration_8005D58C(johnny_vibration1_800C32C0, 2);
            GCL_ExecProc_8001FF2C(work->unkBC0[4], NULL);
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7A64.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7F64.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7F78.s")

void Johnny_800C9144(JohnnyWork *work, int action);

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

        if (GV_Time_800AB330 & 1)
        {
            new_action = 16;
        }
        else
        {
            new_action = 17;
        }
        if (work->object.action_flag != new_action)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, new_action, 0, 4);
        }
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
            GM_SeSet2_80032968(0, 0x3F, 0x53);
            NewPadVibration_8005D58C(johnny_vibration1_800C32C0, 2);
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
        if (work->object.action_flag != 20)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 20, 0, 4);
        }
        work->target->field_26_hp--;
    }

    if (action < 12)
    {
        work->control.field_4C_turn.vy += 170;
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
            GV_NearExp8V_80026734(&work->unkB30.vx, &DG_ZeroVector_800AB39C.vx, 3);
        }
        work->control.field_44_step.vx = work->unkB30.vx;
        work->control.field_44_step.vz = work->unkB30.vz;
    }
}

void Johnny_800C8654(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        if (work->object.action_flag != 19)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 19, 0, 4);
        }
        work->control.field_4C_turn.vy = GM_PlayerControl_800AB9F4->field_4C_turn.vy + 2048;
        work->target->field_26_hp--;
    }
    if (action == 20)
    {
        GM_SeSet_80032858(&work->control.field_0_mov, 0x8D);
        GM_SeSet_80032858(&work->control.field_0_mov, 0x33);
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
    int action_flag;

    if (action == 0)
    {
        work->control.field_3A_radar_atr &= ~RADAR_SIGHT;
        work->unkB1C |= 0x200;
        work->target->class |= TARGET_DOWN;

        if (work->unkB50 == 1)
        {
            action_flag = 23;
        }
        else
        {
            action_flag = 24;
        }

        if (work->object.action_flag != action_flag)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, action_flag, 0, 4);
        }
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
            GCL_ExecProc_8001FF2C(work->unkBC0[5], NULL);
            GCL_ExecProc_8001FF2C(work->unkBC0[3], NULL);
            work->unkB4E = 1;
            NewHiyoko_800D0210(&work->object.objs->objs[6].world, -1);
            work->target->class &= ~TARGET_FLAG;
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C88C8.s")

void Johnny_800C8C34(JohnnyWork *work, int action);
void Johnny_800C8B14(JohnnyWork *work, int action);
void Johnny_800C8E84(JohnnyWork *work, int action);
void Johnny_800C8CD4(JohnnyWork *work, int action);
void Johnny_800C8D58(JohnnyWork *work, int action);

int s03c_johnny_800C8A2C(JohnnyWork *work, int action)
{
    if (!(work->target->field_6_flags & 2))
    {
        work->unkB38 = Johnny_800C8C34;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        return 1;
    }

    if (GM_PlayerAction_800ABA40 == action)
    {
        return 0;
    }

    switch (GM_PlayerAction_800ABA40)
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
        if (work->object.action_flag != 27)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 27, 0, 4);
        }
        work->unkB1C |= 0x800;
        work->control.field_4C_turn.vy = GM_PlayerControl_800AB9F4->field_4C_turn.vy;
    }

    if (++work->unkBE4 > 50)
    {
        if (work->object.action_flag != 42)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 42, 0, 4);
        }
        if (!(work->unkBE4 & 7))
        {
            NewPadVibration_8005D58C(johnny_vibration2_800C32C4, 2);
        }
    }
    if (s03c_johnny_800C8A2C(work, 7) == 0 && (work->unkB24 & 8))
    {
        work->target->field_42 = 0;
        work->target->field_2A = 0;
        GM_SeSet_80032858(&work->control.field_0_mov, 0x8E);
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
        if (work->object.action_flag != 30)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 30, 0, 4);
        }
    }
    if (action == 12)
    {
        GM_SeSet_80032858(&work->control.field_0_mov, 0x33);
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
        GM_SeSet_80032858(&work->control.field_0_mov, 0x8F);
        if (work->object.action_flag != 28)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 28, 0, 4);
        }
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
        work->control.field_3A_radar_atr &= ~RADAR_SIGHT;
        GM_SeSet_80032858(&work->control.field_0_mov, 0x8E);
        GM_SeSet_80032858(&work->control.field_0_mov, 0x90);
        if (work->object.action_flag != 29)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 29, 0, 4);
        }
        work->target->field_26_hp -= 255;
        GM_TotalEnemiesKilled++;
    }
    if (action > 48 && action < 60)
    {
        svec.vx = svec.vy = 0;
        svec.vz = 96;
        DG_RotVector_8001BE98(&svec, &work->control.field_44_step, 1);
    }
    if (action == 55)
    {
        GM_SeSet_80032858(&work->control.field_0_mov, 0x33);
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
        if (work->object.action_flag != 27)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 27, 0, 4);
        }
    }

    if (++work->unkBE4 > 50)
    {
        if (work->object.action_flag != 42)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 42, 0, 4);
        }

        if (!(work->unkBE4 & 7))
        {
            NewPadVibration_8005D58C(johnny_vibration2_800C32C4, 2);
        }
    }
    if (s03c_johnny_800C8A2C(work, 13) == 0)
    {
        work->control.field_4C_turn.vy = GM_PlayerControl_800AB9F4->field_4C_turn.vy;

        DG_SetPos2_8001BC8C(&GM_PlayerControl_800AB9F4->field_0_mov, &GM_PlayerControl_800AB9F4->field_8_rot);
        DG_MovePos_8001BD20(&s03c_dword_800C32EC);

        ReadRotMatrix(&mat);

        control = &work->control;
        svec.vx = mat.t[0];
        svec.vy = mat.t[1];
        svec.vz = mat.t[2];

        GV_SubVec3_80016D40(&svec, &control->field_0_mov, &work->control.field_44_step);

        if (work->unkB24 & 8)
        {
            work->target->field_42 = 0;
            work->target->field_2A = 0;

            GM_SeSet_80032858(&control->field_0_mov, 0x8E);

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
        work->control.field_3A_radar_atr &= ~RADAR_SIGHT;

        if (work->unkB50 == 1)
        {
            action_flag = 23;
        }
        else
        {
            action_flag = 24;
        }

        work->unkB50 = 0;

        if (work->object.action_flag != action_flag)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, action_flag, 0, 4);
        }
        GM_ConfigControlAttribute_8002623C(&work->control, 0);

        work->target->class |= TARGET_DOWN;

        Johnny_800C4F24(work, 0);
        GCL_ExecProc_8001FF2C(work->unkBC0[5], NULL);

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
        GCL_ExecProc_8001FF2C(work->unkBC0[3], NULL);
        JohnnyExecProc_800C4D8C(work);
        GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void Johnny_800C9144(JohnnyWork *work, int action)
{
    if (action == 0)
    {
        work->homing->flag = 0;
        work->control.field_3A_radar_atr &= ~RADAR_SIGHT;

        if (work->object.action_flag != 39)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 39, 0, 4);
        }

        work->target->class &= ~TARGET_FLAG;
        work->target->class |= TARGET_DOWN;
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
            GM_Sound_800329C4(&work->control.field_0_mov, 0x51, 1);
        }

        if (action == 44)
        {
            GM_Sound_800329C4(&work->control.field_0_mov, 0x33, 1);
        }

        if (work->object.is_end != 0)
        {
            Johnny_800C4F24(work, 0);
            GCL_ExecProc_8001FF2C(work->unkBC0[5], NULL);
            if (work->object.action_flag != 40)
            {
                GM_ConfigObjectAction_80034CD4(&work->object, 40, 0, 4);
            }

            work->unkB4C++;
            NewHiyoko_800D0210(&work->object.objs->objs[6].world, -1);
        }
        break;

    case 1:
        if (++work->unkB4E == 32)
        {
            work->unkB1C |= 0x1000;
            GCL_ExecProc_8001FF2C(work->unkBC0[3], NULL);
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
        if (work->object.action_flag != 0)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
        }
        work->unkB1C |= 0x20;
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
        sna_act_unk_helper2_helper2_800605DC(&work->sna_auto_move, work->control.field_2C_map->field_8_hzd,
                                             &work->unkB04);
    }
    if (arg1 == 8)
    {
        GM_Sound_800329C4(&work->control.field_0_mov, 0xC2, 1);
    }
    if (arg1 >= 48)
    {
        if (arg1 == 48)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction_80034CD4(&work->object, 1, 0, 4);
            }
            s03b_boxall_800C93AC(work->unkB78[9]);
            GM_ConfigMotionAdjust_80035008(&work->object, work->rots2);
        }
        switch (work->unkB4C)
        {
        case 0:
            sna_unk_helper2_helper_8006070C(&work->sna_auto_move, &work->control);
            if (sna_act_unk_helper2_helper3_80060684(&work->sna_auto_move, &work->control.field_0_mov) < 500)
            {
                work->unkB4C++;
            }
            break;
        case 1:
            if (work->object.action_flag != 0)
            {
                GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 4);
            }
            work->unkB4C++;
            break;
        case 2:
            work->control.field_4C_turn.vy = -1024;
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
    int     i;

    s03b_boxall_800C974C();
    if (arg1 == 0)
    {
        if (GM_PlayerStatus_800ABA50 & PLAYER_UNK100000)
        {
            work->unkB1C |= 2;
        }
        work->control.field_4C_turn.vy = 0;
        if (work->object.action_flag != 36)
        {
            GM_ConfigObjectAction_80034CD4(&work->object, 36, 0, 4);
        }
        GV_SubVec3_80016D40(&work->control.field_0_mov, &GM_PlayerPosition_800ABA10, &svec);
        GM_PlayerControl_800AB9F4->field_4C_turn.vy = GV_VecDir2_80016EF8(&svec);
    }
    if (arg1 == 24)
    {
        GCL_ExecProc_8001FF2C(work->unkBC0[1], NULL);
    }
    switch (work->unkB4C)
    {
    case 0:
        if (GM_StreamStatus_80037CD8() == -1)
        {
            GM_ConfigMotionAdjust_80035008(&work->object, NULL);
            for (i = 0; i < 16; i++)
            {
                work->rots2[i] = DG_ZeroVector_800AB39C;
            }
            NewFadeIo_800C4224(0, 32);
            s03b_boxall_800C96E8();
            work->unkB4C++;
        }
        break;
    case 1:
        if (++work->unkB4E == 80)
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
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

    if (work->control.field_56 == 0)
    {
        return;
    }

    msgs = &work->control.field_5C_mesg[work->control.field_56] - 1;
    for (i = work->control.field_56; i > 0; i--, msgs--)
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
                GM_StreamStatus_80037CD8() == -1)
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C99D8.s")
void s03c_johnny_800C99D8(JohnnyWork *work, int field_B10);

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
        work->control.field_3A_radar_atr |= RADAR_UNK4;
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
        work->control.field_3A_radar_atr |= RADAR_UNK4;
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
        work->control.field_3A_radar_atr |= RADAR_UNK4;
        work->unkB1C &= ~0x80000000;
        s03b_boxall_800C9328();
        s03b_boxall_800C93F0(work->unkB78[13], 4);
        NewPadVibration_8005D58C(johnny_vibration1_800C32C0, 2);
        GM_SeSet2_80032968(0, 0x3F, 0x53);
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
        sna_act_helper2_helper2_80033054(GV_StrCode_80016CCC("ジョニー"), &work->rots2[6]); // ジョニー = Joni = Johnny
    }
    if (work->unkB1C & 0x10000000)
    {
        GM_AlertLevel_800ABA18 = 0xFF;
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
    status = GM_StreamStatus_80037CD8();
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

    GM_ActMotion_80034A7C(&work->object);
    control = &work->control;
    GM_ActControl_80025A7C(control);
    GM_ActObject_80034AF4(&work->object);
    GM_Target_SetVector_8002D500(work->target, &control->field_0_mov);
    DG_GetLightMatrix2_8001A5D8(&control->field_0_mov, work->light);
    work->control.field_32_height = work->object.field_18;
    work->sna_auto_move.field_0_ivec.vx = HZD_GetAddress_8005C6C4(
        work->control.field_2C_map->field_8_hzd, &control->field_0_mov, work->sna_auto_move.field_0_ivec.vx);
    Johnny_800C9D64(work);
    if (work->unkB30.vy < 0 && work->control.field_57 != 0)
    {
        work->unkB30.vy = 0;
    }
    work->unkB30.vy -= 32;
    work->control.field_44_step.vy += work->unkB30.vy;
}

void JohnnyDie_800CA048(JohnnyWork *work)
{
    ShadowWork *shadow;
    GV_ACT     *jfamas;
    GV_ACT     *gunlight;

    HomingTarget_Free_80032CFC(work->homing);
    shadow = work->shadow;
    if (shadow != NULL)
    {
        GV_DestroyOtherActor_800151D8(&shadow->field_0_actor);
    }
    jfamas = work->jfamas;
    if (jfamas != NULL)
    {
        GV_DestroyOtherActor_800151D8(jfamas);
    }
    gunlight = work->gunlight;
    if (gunlight != NULL)
    {
        GV_DestroyOtherActor_800151D8(gunlight);
    }
    GM_FreeTarget_8002D4B0(work->target);
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);
    s03b_boxall_800C9328();
}

int JohnnyConfigTarget_800CA0E0(JohnnyWork *work)
{
    TARGET *target;

    work->target = target = GM_AllocTarget_8002D400();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget_8002DC74(target, 0x9F, 2, &s03c_dword_800C32F4);
    GM_Target_8002DCCC(target, 1, -1, 0xC0, 0xA, &DG_ZeroVector_800AB39C);
    work->homing = HomingTarget_Alloc_80032C8C(&work->object.objs->objs[6].world, &work->control);
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
    n_routes = work->control.field_2C_map->field_8_hzd->f00_header->n_routes;
    routes = work->control.field_2C_map->field_8_hzd->f00_header->routes;
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

    option = GCL_GetOption_80020968('m');
    if (option != NULL)
    {
        work->unkB0C = GCL_StrToInt_800209E8(option);
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

    option = GCL_GetOption_80020968('f');
    if (option != NULL)
    {
        work->unkB70 = GCL_StrToInt_800209E8(option);
        if (work->unkB70 == 3)
        {
            work->unkB1C |= 2;
        }
    }

    option = GCL_GetOption_80020968('b');
    if (option != NULL)
    {
        if (GCL_StrToInt_800209E8(option) == 1)
        {
            work->unkB1C |= 1;
        }
    }

    option = GCL_GetOption_80020968('c');
    if (option != NULL)
    {
        work->unkB6C = GCL_StrToInt_800209E8(option);
    }
    else
    {
        work->unkB6C = 0;
    }

    option = GCL_GetOption_80020968('s');
    if (option != NULL)
    {
        work->unkB6E = GCL_StrToInt_800209E8(option);
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
    work->player_status = GM_PlayerStatus_800ABA50 & ~GAME_FLAG_BIT_21;
    work->unkB30 = DG_ZeroVector_800AB39C;
    sub_80060548(&work->sna_auto_move, work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov);
}

void Johnny_800CA574(JohnnyWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('v'))
    {
        return;
    }

    i = 0;
    out = work->unkB78;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 18)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

void Johnny_800CA5EC(JohnnyWork *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('e'))
    {
        return;
    }

    i = 0;
    out = work->unkBC0;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 8)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

int JohnnyGetResources_800CA664(JohnnyWork *work, int scriptData, int scriptBinds)
{
    SVECTOR  indices;
    CONTROL *control;
    OBJECT  *object;
    SVECTOR *control_field3C;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, scriptData, scriptBinds) >= 0)
    {
        GM_ConfigControlString_800261C0(control, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));
        GM_ConfigControlHazard_8002622C(control, control->field_0_mov.vy, 450, 450);
        control->field_59 = 2;
        GM_ConfigControlAttribute_8002623C(control, 5);
        control_field3C = &work->control.field_3C;
        control_field3C->vy = 6000;
        control_field3C->vz = 1024;

        object = &work->object;
        GM_InitObject_80034A18(object, GV_StrCode_80016CCC("johnny"), 0x32D, GV_StrCode_80016CCC("joh_03c"));
        GM_ConfigObjectJoint_80034CB4(object);
        GM_ConfigMotionControl_80034F08(object, &work->motion, GV_StrCode_80016CCC("joh_03c"), work->oar1, work->oar2,
                                        control, work->rots);
        GM_ConfigObjectLight_80034C44(object, work->light);
        GM_ConfigObjectAction_80034CD4(object, 0, 0, 0);
        GM_ConfigControlTrapCheck_80026308(control);
        if (JohnnyConfigTarget_800CA0E0(work) >= 0 && Johnny_800CA1E8(work) >= 0)
        {
            Johnny_800CA574(work);
            Johnny_800CA5EC(work);
            Johnny_800CA304(work);

            indices.vx = 0;
            indices.vy = 6;
            indices.vz = 12;
            indices.pad = 15;
            work->shadow = shadow_init_800602CC(control, object, indices);
            if (work->shadow != NULL)
            {
                s03b_boxall_800C9328();
                return 0;
            }
        }
    }
    return -1;
}

GV_ACT *NewJohnny_800CA838(int scriptData, int scriptBinds)
{
    JohnnyWork *work;

    work = (JohnnyWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(JohnnyWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)JohnnyAct_800C9F7C, (TActorFunction)JohnnyDie_800CA048,
                              "johnny.c");
    if (JohnnyGetResources_800CA664(work, scriptData, scriptBinds) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }
    return &work->actor;
}
