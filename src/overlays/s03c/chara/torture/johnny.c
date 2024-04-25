#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/homing_target.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "chara/snake/shadow.h"
#include "chara/snake/sna_init.h"
#include "chara/snake/sna_hzd.h"

struct JohnnyWork;
typedef void (*TJohnnyFunc)(struct JohnnyWork *work, int arg1);

typedef struct JohnnyWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    OAR_RECORD     oar1[0x11];
    OAR_RECORD     oar2[0x11];
    SVECTOR        rots[0x20];
    MATRIX         light[2];
    char           pad7D8[0x48];
    TARGET        *target;
    HOMING        *homing;
    GV_ACT        *jfamas;
    GV_ACT        *gunlight;
    int           *gunlight_pvisible;
    int            jfamas_trigger;
    ShadowWork    *shadow;
    char           pad83C[0x2A0];
    SnaAutoMove    sna_auto_move;
    char           padAFC[0x10];
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
    int            unkB44;
    char           padB48[4];
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
    char           padB60[0xC];
    unsigned short unkB6C;
    unsigned short unkB6E;
    unsigned short unkB70;
    char           padB72[2];
    int            unkB74;
    int            unkB78[0x12];
    int            unkBC0[8];
    char           padBE0[8];
} JohnnyWork;

#define EXEC_LEVEL 5

int s03c_dword_800C32C0 = 0x00000AFF;
int s03c_dword_800C32C4 = 0x000004FF;
int s03c_dword_800C32C8 = 0x00000000;
int s03c_dword_800C32CC = 0x00000000;
int s03c_dword_800C32D0 = 0x00001B58;
int s03c_dword_800C32D4 = 0x00000000;
int s03c_dword_800C32D8 = 0x00000064;
int s03c_dword_800C32DC = 0x0000FC00;
int s03c_dword_800C32E0 = 0x00000000;
int s03c_dword_800C32E4 = 0x00000000;
int s03c_dword_800C32E8 = 0x00000DAC;
int s03c_dword_800C32EC = 0x00000000;
int s03c_dword_800C32F0 = 0x0000012C;

SVECTOR s03c_dword_800C32F4 = {300, 750, 300};

const char s03c_dword_800D7538[] = {0xc6, 0xfe, 0xa4, 0xeb};
const char s03c_dword_800D753C[] = {0x0, 0x0, 0x0, 0x0};
const char s03c_aRoutobira_800D7540[] = "rou_tobira";
const char s03c_dword_800D754C[] = {0xbd, 0xd0, 0xa4, 0xeb};
const char s03c_dword_800D7550[] = {0x0, 0x0, 0x0, 0x0};
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

extern SVECTOR          DG_ZeroVector_800AB39C;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              GM_AlertLevel_800ABA18;

void    s03b_boxall_800C9328(void);
void    s03b_boxall_800C9404(void);
GV_ACT *NewGunLight_800D3AD4(MATRIX *world, int **pvisible);
GV_ACT *NewJFamas_800CAFAC(CONTROL *control, OBJECT *parent, int num_parent, int *trigger);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4194.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C424C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C430C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4388.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C43D0.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4418.s")
void s03c_johnny_800C4418(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C44F8.s")
void s03c_johnny_800C44F8(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4588.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C45AC.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C470C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4720.s")
void s03c_johnny_800C4720(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4734.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C47C4.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4804.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4860.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4934.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4A64.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4A98.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4AD0.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4B58.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4BDC.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4BEC.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4C54.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4CCC.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4D8C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4DCC.s")
void s03c_johnny_800C4DCC(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4E5C.s")
void s03c_johnny_800C4E5C(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4E9C.s")
void s03c_johnny_800C4E9C(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4F24.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C4FAC.s")
void s03c_johnny_800C4FAC(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5064.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C50D0.s")
void s03c_johnny_800C50D0(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5124.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5168.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C54A8.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5520.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C57D0.s")
void s03c_johnny_800C57D0(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C588C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C594C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C59B8.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5A7C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C5DE4.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6054.s")
void s03c_johnny_800C6054(JohnnyWork *work, int arg1);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6170.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6204.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6268.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C631C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6418.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C64B0.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C65F8.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C66A4.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6850.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6918.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C69D8.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6C10.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6D84.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C6FC0.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7160.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7378.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7428.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C753C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7804.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C794C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7A64.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7F64.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C7F78.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8400.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C854C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8654.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C873C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C88C8.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8A2C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8B14.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8C34.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8CD4.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8D58.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8E84.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C8FE4.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9144.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C92E0.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C949C.s")
#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9644.s")
void s03c_johnny_800C9644(JohnnyWork *work);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C96F4.s")
void s03c_johnny_800C96F4(JohnnyWork *work, int field_B10);

void Johnny_800C98B0(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB38 = s03c_johnny_800C57D0;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C98E4.s")
void s03c_johnny_800C98E4(JohnnyWork *work, int field_B10);

void Johnny_800C998C(JohnnyWork *work, int field_B10)
{
    if (field_B10 == 0)
    {
        work->unkB38 = s03c_johnny_800C6054;
        work->unkB4E = 0;
        work->unkB4C = 0;
        work->unkB3C = 0;
        work->unkB1C |= 0x80000000;
        s03c_johnny_800C4720(work, 1);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C99D8.s")
void s03c_johnny_800C99D8(JohnnyWork *work, int field_B10);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9B3C.s")
void s03c_johnny_800C9B3C(JohnnyWork *work, int field_B10);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9BB4.s")
void s03c_johnny_800C9BB4(JohnnyWork *work, int field_B10);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9C2C.s")
void s03c_johnny_800C9C2C(JohnnyWork *work, int field_B10);

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800C9CA8.s")
void s03c_johnny_800C9CA8(JohnnyWork *work, int field_B10);

void Johnny_800C9D64(JohnnyWork *work)
{
    int         field_B10;
    int         field_B3C;
    TJohnnyFunc field_B38;
    int         status;

    s03c_johnny_800C9644(work);
    s03c_johnny_800C4418(work);
    s03c_johnny_800C44F8(work);
    s03c_johnny_800C4DCC(work);
    s03c_johnny_800C4E5C(work);
    s03c_johnny_800C50D0(work);
    s03b_boxall_800C9404();
    if (work->object.objs->adjust)
    {
        sna_act_helper2_helper2_80033054(GV_StrCode_80016CCC("ジョニー"), &work->rots[22]); // ジョニー = Joni = Johnny
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
        s03c_johnny_800C96F4(work, field_B10);
        break;
    case 1:
        Johnny_800C98B0(work, field_B10);
        break;
    case 2:
        s03c_johnny_800C98E4(work, field_B10);
        break;
    case 3:
        Johnny_800C998C(work, field_B10);
        break;
    case 4:
        s03c_johnny_800C99D8(work, field_B10);
        break;
    case 5:
        s03c_johnny_800C9B3C(work, field_B10);
        break;
    case 6:
        s03c_johnny_800C9BB4(work, field_B10);
        break;
    case 7:
        s03c_johnny_800C9C2C(work, field_B10);
        break;
    case 8:
        s03c_johnny_800C9CA8(work, field_B10);
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
    s03c_johnny_800C4E9C(work);
    s03c_johnny_800C4FAC(work);
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

#pragma INCLUDE_ASM("asm/overlays/s03c/s03c_johnny_800CA1E8.s")
int s03c_johnny_800CA1E8(JohnnyWork *work);

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
        if (JohnnyConfigTarget_800CA0E0(work) >= 0 && s03c_johnny_800CA1E8(work) >= 0)
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
