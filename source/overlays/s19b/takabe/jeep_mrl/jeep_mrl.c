#include "mgstype.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"
#include "game/vibrate.h"
#include "../jeep_system.h"
#include "../jeep.h"
#include "takabe/meryl_jeep.h"

/* the jeep driven in the Meryl/Otacon scenes (same actor as jeep.c, only the part used here is described) */



extern JeepWork *s19b_dword_800DE64C;
extern int       s19b_dword_800DE648;
extern int       s19b_dword_800C39CC;

extern unsigned char s19b_dword_800C39A0[];
extern unsigned char s19b_dword_800C39B0[];
extern SVECTOR s19b_dword_800C39D0[];
extern unsigned char s19b_dword_800C399C[];
extern unsigned char s19b_dword_800C3994[];
extern SVECTOR s19b_dword_800C39E0;

extern int  s19b_jeep_gls_800CEDFC(int, int);
extern void s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void s19b_jlamp_800D0FE4(int);
extern void s19b_jblood_800C850C(MATRIX *world, MATRIX *world2);
extern void Voicesys_800CE2D0(void);
extern void Voicesys_800CE5F8(int, int);
extern void Voicesys_800CE6AC(int);


void s19b_jeep_mrl_800D2E78(JeepWork *work);
void s19b_jeep_mrl_800D2F54(JeepWork *work);
void s19b_jeep_mrl_800D32C4(JeepWork *work);
void s19b_jeep_mrl_800D36A4(JeepWork *work);
void s19b_jeep_mrl_800D37D0(JeepWork *work);
void s19b_jeep_mrl_800D3928(JeepWork *work);
void s19b_jeep_mrl_800D3CA8(JeepWork *work, int arg1);
void s19b_jeep_mrl_800D3A54(SVECTOR *pos, short *dir, int angle, int len);
int  s19b_jeep_mrl_800D39F0(void);

void s19b_jeep_mrl_800D2CE8(JeepWork *work)
{
    if (work->vibrate_timer == 0)
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
    }
    else
    {
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 10);
    }
}

void s19b_jeep_mrl_800D2D3C(JeepWork *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->field_3D0;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->rot);
    DG_RotVector(&rot, &rot, 1);
    work->speed.vx = rot.vx;
    work->speed.vz = rot.vz;
    s19b_jeep_gls_800CEC24(ctl->mov.vz - 0x640, &vec);
    GV_SubVec3(&vec, &ctl->mov, &vec);
    vec.vx += work->field_3C8;
    vec.vx += rsin(work->field_3CC << 5) * 50 >> 12;
    work->rot.vy = GV_VecDir2(&vec);
    work->field_3CC++;
    work->field_3D4 = GV_NearSpeed(work->field_3D4, 0x190, 0xa);
}

void s19b_jeep_mrl_800D2E78(JeepWork *work)
{
    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = (rand() * 1200 >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);

    if (Takabe_JeepSystem.field_40 == 0)
    {
    }
    else if (Takabe_JeepSystem.field_40 == 1)
    {
        work->func_3F8 = s19b_jeep_mrl_800D2F54;
    }
    else if (Takabe_JeepSystem.field_40 == 3)
    {
        work->func_3F8 = s19b_jeep_mrl_800D2F54;
    }
    else if (Takabe_JeepSystem.field_40 == 6)
    {
        work->func_3F8 = s19b_jeep_mrl_800D36A4;
    }
    else if (Takabe_JeepSystem.field_40 == 7)
    {
        work->func_3F8 = s19b_jeep_mrl_800D37D0;
    }
}

void s19b_jeep_mrl_800D2F54(JeepWork *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    switch (work->field_3DC)
    {
    case 0:
        work->field_3CC = 0;
        work->field_3DC = 5;
        /* fallthrough */
    case 1:
        s19b_jeep_mrl_800D2D3C(work);
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 250, 30);
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0xDAC) == 9)
        {
            work->field_3DC = 2;
            work->field_3A8 = work->speed;
            Takabe_JeepSystem.flags_50 |= 0x20020;
            GM_SeSet(&ctl->mov, 0xB6);
            NewPadVibration(s19b_dword_800C39B0, 2);
            GM_SetSound(0xFF0000FE, 0);
        }
        break;
    case 2:
        memset(&vec, 0, 8);
        vec.vz = work->field_3D0;
        rot = vec;
        DG_SetPos2(&DG_ZeroVector, &work->rot);
        DG_RotVector(&rot, &rot, 1);
        work->field_3A8.vx = GV_NearExp8(work->field_3A8.vx, 0);
        work->field_3A8.vz = GV_NearExp8(work->field_3A8.vz, 0);
        work->speed.vx = rot.vx + work->field_3A8.vx;
        work->speed.vz = rot.vz + work->field_3A8.vz;
        work->rot.vy = GV_NearExp8(work->rot.vy, 0xC00);
        work->field_3D0 = GV_NearExp4(work->field_3D0, 0);
        work->field_3E8 = 0;
        if ((unsigned int)(work->field_3D0 - 6) < 0x2C)
        {
            s19b_jblood_800C850C(&work->jeep_t.objs->objs[1].world, &work->jeep_b.objs->world);
            s19b_jblood_800C850C(&work->jeep_t.objs->objs[2].world, &work->jeep_b.objs->world);
        }
        work->field_3E8 = 0;
        work->field_3EC = GV_NearSpeed(work->field_3EC, -400, 20);
        if (work->speed.vx == 0 && work->speed.vz == 0)
        {
            work->field_3DC = 3;
            Takabe_JeepSystem.flags_50 &= 0xFFFDFFDF;
            Takabe_JeepSystem.flags_50 &= 0xFFFEFFFF;
            work->field_3CC = 0;
        }
        break;
    case 3:
        work->field_3CC++;
        work->field_3EC = GV_NearSpeed(work->field_3EC, -300, 10);
        if (s19b_jeep_mrl_800D39F0() == 1)
        {
            work->field_3DC = 4;
            work->field_3CC = 0;
            Voicesys_800CE6AC(1);
            Voicesys_800CE2D0();
            break;
        }
        if (work->field_3CC == 90)
        {
            Voicesys_800CE5F8(10, 2);
        }
        break;
    case 4:
        work->field_3CC++;
        if (work->field_3CC >= 61)
        {
            work->func_3F8 = s19b_jeep_mrl_800D32C4;
            work->field_3DC = 0;
        }
        break;
    case 5:
        s19b_jeep_mrl_800D2D3C(work);
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 250, 30);
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, 5);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x34BC) == 9)
        {
            Voicesys_800CE2D0();
            work->field_3DC = 1;
        }
        break;
    }
}

void s19b_jeep_mrl_800D32C4(JeepWork *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  vec;

    switch (work->field_3DC)
    {
    case 0:
        work->field_3DC = 1;
        work->field_3CC = 0;
        work->field_3EC = -300;
        Takabe_JeepSystem.flags_50 |= 0x20020;
        Takabe_JeepSystem.flags_50 |= 0x10000;
        GM_SeSet(&ctl->mov, 0xBB);
        NewPadVibration(s19b_dword_800C39A0, 2);
        /* fallthrough */
    case 1:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        vec = DG_ZeroVector;
        s19b_jeep_mrl_800D3A54(&vec, &work->rot.vy, work->field_3EC, work->field_3D0);
        work->speed.vx = vec.vx;
        work->speed.vz = vec.vz;
        work->field_3D0 = GV_NearSpeed(work->field_3D0, -250, 10);
        work->field_3EC = GV_NearSpeed(work->field_3EC, -400, 10);
        if ((work->rot.vy & 0xFFF) < 0x708)
        {
            work->field_3DC = 2;
        }
        break;
    case 2:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        vec = DG_ZeroVector;
        s19b_jeep_mrl_800D3A54(&vec, &work->rot.vy, work->field_3EC, work->field_3D0);
        work->speed.vx = vec.vx;
        work->speed.vz = vec.vz;
        work->field_3D0 = GV_NearSpeed(work->field_3D0, 0, 20);
        work->field_3EC = GV_NearSpeed(work->field_3EC, 0, 7);
        if (work->field_3D0 == 0)
        {
            work->field_3CC = 0;
            work->field_3DC = 5;
            GM_SeSet(&ctl->mov, 0xB4);
            NewPadVibration(s19b_dword_800C39A0, 2);
            Takabe_JeepSystem.flags_50 = (Takabe_JeepSystem.flags_50 & 0xFFFDFFDF) | 0x200;
        }
        break;
    case 3:
        s19b_jeep_mrl_800D2D3C(work);
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 1000, 50);
        work->field_3D0 = GV_NearSpeed(work->field_3D0, work->field_3D4, s19b_dword_800DE648);
        s19b_dword_800DE648 += 2;
        work->field_3EC = GV_NearSpeed(work->field_3EC, 50, 10);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, -0xCB2) == 9)
        {
            work->field_3DC = 4;
        }
        if (work->field_3D0 < 200)
        {
            s19b_jblood_800C850C(&work->jeep_t.objs->objs[1].world, &work->jeep_b.objs->world);
            s19b_jblood_800C850C(&work->jeep_t.objs->objs[2].world, &work->jeep_b.objs->world);
        }
        break;
    case 4:
        s19b_jeep_mrl_800D2D3C(work);
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 600, 50);
        work->field_3D0 = GV_NearSpeed(work->field_3D0, 400, 5);
        work->field_3EC = GV_NearSpeed(work->field_3EC, 0, 7);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, -6000) == 9)
        {
            work->field_3DC = -1;
        }
        work->field_3EC = GV_NearSpeed(work->field_3EC, 0, 20);
        break;
    case 5:
        work->field_3EC = GV_NearSpeed(work->field_3EC, 100, 30);
        work->field_3CC++;
        if (work->field_3CC >= 6)
        {
            work->field_3DC = 3;
            work->field_3C8 = 750;
            work->field_3D0 = 0;
            s19b_dword_800DE648 = 2;
            GM_SeSet(NULL, 0xC0);
        }
        break;
    }

    if (work->field_3DC == -1)
    {
        work->func_3F8 = s19b_jeep_mrl_800D2E78;
        work->field_3DC = 0;
    }
    s19b_jeep_mrl_800D3CA8(work, 0);
}

void s19b_jeep_mrl_800D36A4(JeepWork *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);

    switch (work->field_3DC)
    {
    case 0:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 2000) == 10)
        {
            work->field_3DC = 1;
            s19b_jlamp_800D0FE4(3);
            GM_SeSet(NULL, 0xC2);
        }
        break;
    case 1:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 1500, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 3000) == 12)
        {
            work->field_3DC = 2;
            s19b_jlamp_800D0FE4(1);
            GM_SeSet(NULL, 0xC2);
        }
        break;
    case 2:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, 750, 50);
        if (work->field_3C8 == 750)
        {
            work->func_3F8 = s19b_jeep_mrl_800D2E78;
            work->field_3DC = 0;
        }
        break;
    }
}

void s19b_jeep_mrl_800D37D0(JeepWork *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);

    switch (work->field_3DC)
    {
    case 0:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -750, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 2000) == 11)
        {
            work->field_3DC = 1;
            s19b_jlamp_800D0FE4(4);
        }
        break;
    case 1:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -1350, 50);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 3000) == 13)
        {
            work->field_3DC = 2;
            s19b_jlamp_800D0FE4(1);
        }
        if (++s19b_dword_800C39CC >= 10)
        {
            s19b_dword_800C39CC = 0;
            GM_SeSet(NULL, 0xC1);
        }
        break;
    case 2:
        work->field_3C8 = GV_NearSpeed(work->field_3C8, -750, 50);
        if (work->field_3C8 == -750)
        {
            work->func_3F8 = s19b_jeep_mrl_800D3928;
            work->field_3DC = 0;
        }
        break;
    }
}

void s19b_jeep_mrl_800D3928(JeepWork *work)
{
    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = (rand() * 60 >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);
}

int s19b_jeep_mrl_800D399C(void)
{
    return s19b_dword_800DE64C->field_3D0;
}
int s19b_jeep_mrl_800D39B4(SVECTOR *dst)
{
    *dst = s19b_dword_800DE64C->control.mov;
    return s19b_dword_800DE64C->field_3C8;
}

int s19b_jeep_mrl_800D39F0(void)
{
    CONTROL **where = GM_WhereList;
    MAP      *map   = (*where)->map;
    int       count = 0;
    int       n;

    for (n = GM_N_WhereList; n > 0; n--)
    {
        CONTROL *control = *where;
        if ((control->radar_atr & 1) && control->map == map)
        {
            count++;
        }
        where++;
    }
    return count;
}


/* moves pos by len in the direction *dir, then turns *dir by angle (cf. s19a_800D9BBC) */
void s19b_jeep_mrl_800D3A54(SVECTOR *pos, short *dir, int angle, int len)
{
    SVECTOR move2;
    SVECTOR move;
    SVECTOR front = {0, 0, 1125};
    SVECTOR ofs;
    MATRIX  world;
    long    flag;

    ofs = DG_ZeroVector;
    ofs.vz = len;

    world = DG_ZeroMatrix;
    RotMatrixY(*dir, &world);
    SetRotMatrix(&world);
    SetTransMatrix(&world);
    RotTransSV(&front, &front, &flag);
    RotTransSV(&ofs, &move, &flag);
    move.vx = move.vx * rcos(angle) / 4096;
    move.vz = move.vz * rcos(angle) / 4096;
    GV_AddVec3(pos, &move, pos);

    world = DG_ZeroMatrix;
    RotMatrixY(angle, &world);
    SetRotMatrix(&world);
    RotTransSV(&ofs, &move2, &flag);
    GV_AddVec3(&front, &move2, &move2);
    GV_SubVec3(&move2, &move, &front);

    *dir = ratan2(front.vx, front.vz);
}

void s19b_jeep_mrl_800D3CA8(JeepWork *work, int arg1)
{
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&s19b_dword_800C39D0[arg1], &work->target2.center, 1);
    work->target2.vital = 8;
    if (GM_PowerTarget(&work->target2) == 0)
    {
        return;
    }
    NewPadVibration(s19b_dword_800C399C, 1);
    NewPadVibration(s19b_dword_800C3994, 0);
}


/* the Meryl (or Otacon) sitting in the jeep; same actor as pkjp_mrl.c of s19a */

typedef void (*ACTION)(MerylJeepWork *, int);

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND )

#define SetState(work, func)                    \
{                                               \
    (work)->action = (func);                    \
    (work)->time = 0;                           \
    (work)->control.turn.vz = 0;                \
    (work)->control.turn.vx = 0;                \
}

void sna_act_helper2_helper2_80033054(int face, SVECTOR *rot);

static void ActionMain(MerylJeepWork *work);

static void Act(MerylJeepWork *work)
{
    CONTROL *control;
    OBJECT  *body;
    DG_OBJS *objs;

    control = &work->control;

    ActionMain(work);

    body = &work->body;
    GM_ActMotion(body);

    sna_act_helper2_helper2_80033054(work->face, &work->adjust[6]);
    work->adjust[6].vy = GV_NearSpeed(work->adjust[6].vy, work->head_rot, 200);

    control->turn = DG_ZeroVector;
    control->rot = control->turn;
    control->mov = s19b_dword_800C39E0;

    GM_ActControl(control);
    GM_ActObject(body);

    objs = work->body.objs;
    CompMatrix(work->root_mat, &objs->world, &objs->world);

    control->mov.vx = objs->world.t[0];
    control->mov.vy = objs->world.t[1];
    control->mov.vz = objs->world.t[2];

    DG_GetLightMatrix(&control->mov, work->light);

    Takabe_MerylHeadPos.vx = work->body.objs->objs[6].world.t[0];
    Takabe_MerylHeadPos.vy = work->body.objs->objs[6].world.t[1];
    Takabe_MerylHeadPos.vz = work->body.objs->objs[6].world.t[2];

    GM_MoveTarget(work->target, &control->mov);
}

static int GetResources(MerylJeepWork *work, int name, int which)
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    if (GM_InitControl(control, name, GM_CurrentMap) < 0)
    {
        return -1;
    }

    control->mov = work->root_ctrl->mov;
    control->rot = work->root_ctrl->rot;
    GM_ConfigControlInterp(control, 4);

    body = &work->body;
    if (which == 0)
    {
        GM_InitObject(body, GV_StrCode("meryl"), BODY_FLAG, GV_StrCode("mel_19b"));
        work->face = GV_StrCode("メリル");
        work->voice1 = 0x82;
        work->voice2 = 0x83;
        work->voice3 = 0x84;
        work->voice4 = 0x82;
    }
    else
    {
        GM_InitObject(body, GV_StrCode("otacom"), BODY_FLAG, GV_StrCode("mel_19b"));
        work->face = GV_StrCode("オタコン");
        work->voice1 = 0x85;
        work->voice2 = 0x86;
        work->voice3 = 0x87;
        work->voice4 = 0x85;
    }

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("mel_19b"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ActMotion(&work->body);
    GM_ConfigMotionAdjust(body, work->adjust);

    work->target = GM_AllocTarget();
    Takabe_JeepSystem.meryl_body = body;
    control->r_sphere = -2;
    return 0;
}

void s19b_jeep_mrl_800D4098(MerylJeepWork *work)
{
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

void *s19b_jeep_mrl_800D40D4(CONTROL *root_ctrl, MATRIX *root_mat, int which)
{
    MerylJeepWork *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(MerylJeepWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, s19b_jeep_mrl_800D4098, "jeep_mrl.c");

        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;

        if (GetResources(work, GV_StrCode("meryl"), which) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

static void StateIdle(MerylJeepWork *work, int time);
static void StateLook(MerylJeepWork *work, int time);
static void StateCrouch(MerylJeepWork *work, int time);
static void StateDuck1(MerylJeepWork *work, int time);
static void StateDuck2(MerylJeepWork *work, int time);
static void StateDuck3(MerylJeepWork *work, int time);
static void StateShout1(MerylJeepWork *work, int time);
static void StateShout2(MerylJeepWork *work, int time);
static void StateShout3(MerylJeepWork *work, int time);
static void StateDamage(MerylJeepWork *work, int time);

static int CheckFlags(MerylJeepWork *work)
{
    int flags = work->flags;

    if (flags & 0x2)
    {
        SetState(work, StateDamage);
        return 1;
    }

    if (flags & 0x1)
    {
        SetState(work, StateIdle);
        return 1;
    }

    if (flags & 0x20)
    {
        SetState(work, StateDuck1);
        return 1;
    }

    if (flags & 0x200)
    {
        SetState(work, StateShout1);
        return 1;
    }

    if (flags & 0x1000)
    {
        SetState(work, StateCrouch);
        return 1;
    }

    if ((flags & 0x10000) == 0)
    {
        SetState(work, StateLook);
        return 1;
    }

    return 0;
}

static void StateIdle(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    CheckFlags(work);
}

static void StateLook(MerylJeepWork *work, int time)
{
    SVECTOR diff;
    int     angle;

    if (time == 0)
    {
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    if ((Takabe_JeepSystem.flags & 1) && GV_RandU(0x100) < 0x14)
    {
        GM_SeSet(&work->control.mov, work->voice3);
    }

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);

    angle = (GM_PlayerControl->rot.vy - work->control.rot.vy) - work->root_ctrl->rot.vy;
    angle &= 0xFFF;
    if (angle & 0x800)
    {
        angle -= 0x1000;
    }
    if (angle < -0x400)
    {
        angle = -0x400;
    }
    if (angle > 0x400)
    {
        angle = 0x400;
    }
    work->head_rot = angle;

    if (work->flags & 0x10000)
    {
        work->head_rot = 0;
        if (CheckFlags(work) == 0)
        {
            SetState(work, StateIdle);
        }
    }
}

static void StateCrouch(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }

    if (work->flags & 0x10000)
    {
        SetState(work, StateIdle);
    }
}

static void StateDuck1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 7;
        GM_ConfigObjectAction(&work->body, 7, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetState(work, StateDuck2);
}

static void StateDuck2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 8;
        GM_ConfigObjectAction(&work->body, 8, 0, 0);
    }

    if (CheckFlags(work) != 0) return;
    if (work->flags & 0x20000) return;
    SetState(work, StateDuck3);
}

static void StateDuck3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 9;
        GM_ConfigObjectAction(&work->body, 9, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetState(work, StateIdle);
}

static void StateShout1(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 1;
        GM_ConfigObjectAction(&work->body, 1, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetState(work, StateShout2);
}

static void StateShout2(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 2;
        GM_ConfigObjectAction(&work->body, 2, 0, 0);
    }

    if (CheckFlags(work) != 0) return;
    if (work->flags & 0x20000) return;
    SetState(work, StateShout3);
}

static void StateShout3(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 3;
        GM_ConfigObjectAction(&work->body, 3, 0, 4);
    }

    if (CheckFlags(work) != 0) return;
    if (work->body.is_end == 0) return;
    SetState(work, StateIdle);
}

static void StateDamage(MerylJeepWork *work, int time)
{
    if (time == 0)
    {
        work->action_id = 13;
        GM_ConfigObjectAction(&work->body, 13, 0, 4);
        GM_SeSet(&work->control.mov, work->voice1);
    }

    if (work->body.is_end == 0) return;
    SetState(work, StateIdle);
}

static void ActionMain2(MerylJeepWork *work)
{
    ACTION action;
    int    time;

    time = work->time;
    action = work->action;
    work->time = time + 1;

    if (action == NULL)
    {
        action = StateIdle;
        work->action = action;
        work->action_id = 0;
        GM_ConfigObjectAction(&work->body, 0, 0, 4);
    }

    action(work, time);
}

static void ActionMain(MerylJeepWork *work)
{
    work->flags = Takabe_JeepSystem.flags_50;
    Takabe_JeepSystem.flags_50 &= 0xFFFF0000;
    ActionMain2(work);
}
