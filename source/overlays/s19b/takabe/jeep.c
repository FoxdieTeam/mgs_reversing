#include "mgstype.h"
#include <libgte.h>
#include <rand.h>
#include "game/game.h"
#include "game/vibrate.h"
#include "jeep_system.h"
#include "jeep.h"


extern SVECTOR s19b_dword_800C39BC;
extern SVECTOR s19b_dword_800C39C4;

void s19b_jeep_800D2170(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2, short *arg3)
{
    arg3[0] = arg0->vx;
    arg3[1] = arg1->vx;
    arg3[2] = arg2->vx;
    arg3[3] = arg0->vy;
    arg3[4] = arg1->vy;
    arg3[5] = arg2->vy;
    arg3[6] = arg0->vz;
    arg3[7] = arg1->vz;
    arg3[8] = arg2->vz;
}

void s19b_jeep_800D21DC(int ang, MATRIX *mat, SVECTOR *out)
{
    SVECTOR vec;
    VECTOR  sqr;
    int     y;

    sqr.vx = 4096 - ang;
    sqr.vz = ang;

    gte_ldlvl(&sqr);
    gte_sqr12();
    y = ang * (4096 - ang);
    y >>= 11;
    gte_stlvnl(&sqr);

    vec.vy = y;
    vec.vx = sqr.vx;
    vec.vz = sqr.vz;
    ApplyMatrixSV(mat, &vec, out);
}

extern VECTOR s19b_dword_800DDD7C;
extern u_char s19b_dword_800C3990[];
extern u_char s19b_dword_800C3994[];

extern int  s19b_spark2_m_800D9C90(SVECTOR *mov, VECTOR *pos, int *param, SVECTOR *out);
extern int  s19b_spark2_m_800D9EC0(SVECTOR *mov, SVECTOR *rot, SVECTOR *speed, SVECTOR *out);
extern void s19b_spark2_m_800DA0B4(SVECTOR *rots, int param, SVECTOR *rot, SVECTOR *out);
extern void s19b_jeep_800D3928(JeepWork *work);
extern void *NewPadVibration(u_char *table, int dir);

void s19b_jeep_800D2258(JeepWork *work)
{
    CONTROL *control;
    TARGET  *target;
    SVECTOR  light_pos;
    /* FIXME: the scale vector and the rotation passed to DG_SetPos2 are one object in the original stack frame;
       they were probably declared in a local scope */
    union { VECTOR scale; SVECTOR rot; } u;
    VECTOR   scale2;
    int      flags;
    int      next_z;

    GM_CurrentMap = work->map;
    flags = 0;
    Takabe_JeepSystem.offset = DG_ZeroVector;

    control = &work->control;
    control->mov.vx = work->pos.vx - Takabe_JeepSystem.world_pos.vx;
    control->mov.vz = work->pos.vz - Takabe_JeepSystem.world_pos.vz;

    target = work->target;

    if (target->damaged & TARGET_PUSH)
    {
        control->mov.vx += target->offset.vx;
        control->mov.vz += target->offset.vz;
        work->pos.vx += target->offset.vx;
        work->pos.vy += target->offset.vy;
        Takabe_JeepSystem.offset.vx -= target->offset.vx;
        Takabe_JeepSystem.offset.vz -= target->offset.vz;

        if (work->func_3F8 != s19b_jeep_800D3928)
        {
            work->field_3D0 += work->field_3D0 / 16;
            work->field_3D4 -= work->field_3D4 / 4;
            work->vibrate_timer = 5;
            NewPadVibration(s19b_dword_800C3990, 1);
            NewPadVibration(s19b_dword_800C3994, 0);
        }
        else
        {
            work->field_3D4 -= work->field_3D4 / 128;
            work->field_3CA -= 20;
            if (work->field_3CA < -0x3B6)
            {
                work->field_3CA = -0x3B6;
            }

            if (work->field_3E4 == 0)
            {
                Takabe_JeepSystem.flags_50 |= 0x20200;
            }

            work->field_3E4 = 5;
        }

        flags |= 2;
    }

    target->damaged &= ~TARGET_PUSH;

    flags |= s19b_spark2_m_800D9C90(&control->mov, &work->pos, &work->field_3D0, &Takabe_JeepSystem.offset);

    if (flags & 1)
    {
        GM_PadVibration = 1;
    }

    if (flags == 2)
    {
        work->field_3C8 += target->offset.vx;
    }

    Takabe_JeepSystem.offset.vy = -s19b_spark2_m_800D9EC0(&control->mov, &work->rot, &work->speed, &work->field_3B0);
    s19b_spark2_m_800DA0B4(work->tyres.rots, work->field_3E8, &work->rot, &work->field_3C0);

    work->tyres.objs->rots[3].vy = -work->field_3EC;
    work->tyres.objs->rots[4].vy = -work->field_3EC;

    control->turn = work->rot;
    control->turn.vx = 0;

    light_pos = control->mov;
    light_pos.vy += 250;
    DG_GetLightMatrix(&light_pos, work->light);

    GM_ActControl(control);

    GM_ActObject2(&work->body);
    RotMatrixX(work->rot.vx, &work->body.objs->world);
    u.scale = s19b_dword_800DDD7C;
    ScaleMatrix(&work->body.objs->world, &u.scale);

    u.rot.vx = control->rot.vx;
    u.rot.vy = control->rot.vy;
    u.rot.vz = 0;
    DG_SetPos2(&control->mov, &u.rot);

    GM_ActObject2(&work->tyres);
    RotMatrixX(work->rot.vx, &work->tyres.objs->world);
    scale2 = s19b_dword_800DDD7C;
    ScaleMatrix(&work->tyres.objs->world, &scale2);

    GM_ActObject2((OBJECT *)&work->front_headlights);
    GM_ActObject2((OBJECT *)&work->headlights);

    work->field_3E8 = work->field_3D0;
    work->func_3F8(work);

    work->old_pos.vx = work->pos.vx;
    work->pos.vx += work->speed.vx;
    Takabe_JeepSystem.offset.vx -= work->pos.vx - work->old_pos.vx;
    Takabe_JeepSystem.world_pos.vx = work->old_pos.vx;

    next_z = work->pos.vz + work->speed.vz;
    if (next_z < work->old_pos.vz)
    {
        if (work->pos.vz < work->old_pos.vz)
        {
            work->old_pos.vz = work->pos.vz;
        }

        work->pos.vz = next_z;
        Takabe_JeepSystem.offset.vz -= work->pos.vz - work->old_pos.vz;
        Takabe_JeepSystem.world_pos.vz = work->old_pos.vz;
    }
    else
    {
        work->pos.vz = next_z;
    }

    GM_MoveTarget(work->target, &control->mov);
    GM_PushTarget(work->target);

    if (work->vibrate_timer != 0)
    {
        work->vibrate_timer--;
        Takabe_JeepSystem.flags_50 |= 2;
        Takabe_JeepSystem.flags |= 2;
    }

    if (work->field_3E4 != 0)
    {
        if (--work->field_3E4 == 0)
        {
            Takabe_JeepSystem.flags_50 &= ~0x20200;
        }
    }
}

void s19b_jeep_800D2790(JeepWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->tyres);
    GM_FreeObject((OBJECT *)&work->front_headlights);
    GM_FreeObject((OBJECT *)&work->headlights);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->mrl);
    GM_SetSound(0xFF0000FE, 0);
}

void s19b_jeep_800D2800(JeepWork *work)
{
    TARGET *trg;

    trg = work->target = GM_AllocTarget();
    GM_SetTarget(trg, TARGET_PUSH, PLAYER_SIDE, &s19b_dword_800C39BC);

    trg = &work->target2;
    GM_SetTarget(trg, TARGET_POWER, PLAYER_SIDE, &s19b_dword_800C39C4);
    GM_SetPowerTarget(trg, POWER_DECREASE | POWER_EXPLODE, 2, 8, 0, &DG_ZeroVector);
}

extern JeepWork *s19b_dword_800DE64C;

extern void s19b_jeep_800D2E78(JeepWork *work);
extern GV_ACT *s19b_jeep_mrl_800D40D4(CONTROL *control, MATRIX *root, int param);
extern void *NewJeepSnake(CONTROL *control, MATRIX *root);
extern void NewJeepLamp2(MATRIX *root);

int s19b_jeep_800D2880(JeepWork *work, int name, int map)
{
    CONTROL         *control;
    OBJECT          *body;
    OBJECT          *top;
    OBJECT_NO_ROTS  *obj;
    SVECTOR         *rot;

    control = &work->control;

    if (GM_InitControl(control, name, map) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    body = &work->body;
    rot = &control->rot;
    top = &work->tyres;

    control->mov = control->rot = control->turn = DG_ZeroVector;
    control->step = DG_ZeroVector;
    control->rot.vy = 0x800;
    control->turn.vy = 0x800;

    GM_InitObject(body, 0x26C7, 0x2D, 0);
    GM_ConfigObjectJoint(body);
    GM_InitObject(top, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(top);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectLight(top, work->light);

    obj = &work->front_headlights;
    GM_InitObjectNoRots(obj, 0x3A07, 0x16D, 0);
    obj->objs->root = &body->objs->world;
    GM_ConfigObjectLight((OBJECT *)obj, &work->light2);

    obj = &work->headlights;
    GM_InitObjectNoRots(obj, 0xDA10, 0x16D, 0);
    obj->objs->root = &body->objs->world;
    GM_ConfigObjectLight((OBJECT *)obj, &work->light2);

    work->light2.t[0] = 0x80;
    work->light2.t[1] = 0x80;
    work->light2.t[2] = 0x80;

    s19b_jeep_800D2800(work);

    work->map = map;
    work->rot = *rot;

    work->pos.vx = 0;
    work->pos.vy = 0;
    work->pos.vz = 0;
    work->old_pos = work->pos;
    Takabe_JeepSystem.world_pos = work->old_pos;

    work->field_3B0 = work->speed = work->field_3A8 = DG_ZeroVector;
    work->speed.vz = -400;
    work->field_3B0.vz = -0x800;
    work->field_3C8 = 0;
    work->field_3CA = 0;

    Takabe_JeepSystem.offset.vx = -work->speed.vx;
    Takabe_JeepSystem.offset.vy = -work->speed.vy;
    Takabe_JeepSystem.offset.vz = -work->speed.vz;
    Takabe_JeepSystem.pos = Takabe_JeepSystem.offset;

    work->field_3E8 = work->field_3D0 = work->field_3D4 = 400;
    work->field_3CC = 0;
    work->field_3EC = 0;
    work->func_3F8 = s19b_jeep_800D2E78;
    work->field_3DC = 0;
    work->vibrate_timer = 0;

    work->mrl = s19b_jeep_mrl_800D40D4(control, &body->objs->world, Takabe_JeepSystem.field_48);
    s19b_dword_800DE64C = work;
    NewJeepSnake(control, &body->objs->world);

    Takabe_JeepSystem.control = control;
    Takabe_JeepSystem.rot = rot;
    Takabe_JeepSystem.body = body;
    Takabe_JeepSystem.flags_50 |= 0x10000;

    NewJeepLamp2(&body->objs->world);
    GM_SeSet(NULL, 0xC0);
    return 0;
}

extern const char s19b_aJeepc_800DDD8C[]; // = "jeep.c"

void *NewJeep(int arg0, int arg1)
{
    JeepWork *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(JeepWork));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_800D2258, s19b_jeep_800D2790, s19b_aJeepc_800DDD8C);

        if (s19b_jeep_800D2880(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

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


void s19b_jeep_800D2E78(JeepWork *work);
void s19b_jeep_800D2F54(JeepWork *work);
void s19b_jeep_800D32C4(JeepWork *work);
void s19b_jeep_800D36A4(JeepWork *work);
void s19b_jeep_800D37D0(JeepWork *work);
void s19b_jeep_800D3928(JeepWork *work);
void s19b_jeep_800D3CA8(JeepWork *work, int arg1);
void s19b_jeep_800D3A54(SVECTOR *pos, short *dir, int angle, int len);
int  s19b_jeep_800D39F0(void);

void s19b_jeep_800D2CE8(JeepWork *work)
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

void s19b_jeep_800D2D3C(JeepWork *work)
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

void s19b_jeep_800D2E78(JeepWork *work)
{
    s19b_jeep_800D2CE8(work);
    s19b_jeep_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = ((rand() * 1200) >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);

    if (Takabe_JeepSystem.field_40 == 0)
    {
    }
    else if (Takabe_JeepSystem.field_40 == 1)
    {
        work->func_3F8 = s19b_jeep_800D2F54;
    }
    else if (Takabe_JeepSystem.field_40 == 3)
    {
        work->func_3F8 = s19b_jeep_800D2F54;
    }
    else if (Takabe_JeepSystem.field_40 == 6)
    {
        work->func_3F8 = s19b_jeep_800D36A4;
    }
    else if (Takabe_JeepSystem.field_40 == 7)
    {
        work->func_3F8 = s19b_jeep_800D37D0;
    }
}

void s19b_jeep_800D2F54(JeepWork *work)
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
        s19b_jeep_800D2D3C(work);
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
            s19b_jblood_800C850C(&work->tyres.objs->objs[1].world, &work->body.objs->world);
            s19b_jblood_800C850C(&work->tyres.objs->objs[2].world, &work->body.objs->world);
        }
        work->field_3E8 = 0;
        work->field_3EC = GV_NearSpeed(work->field_3EC, -400, 20);
        if (work->speed.vx == 0 && work->speed.vz == 0)
        {
            work->field_3DC = 3;
            Takabe_JeepSystem.flags_50 &= ~0x20020;
            Takabe_JeepSystem.flags_50 &= ~0x10000;
            work->field_3CC = 0;
        }
        break;
    case 3:
        work->field_3CC++;
        work->field_3EC = GV_NearSpeed(work->field_3EC, -300, 10);
        if (s19b_jeep_800D39F0() == 1)
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
            work->func_3F8 = s19b_jeep_800D32C4;
            work->field_3DC = 0;
        }
        break;
    case 5:
        s19b_jeep_800D2D3C(work);
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

void s19b_jeep_800D32C4(JeepWork *work)
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
        s19b_jeep_800D3A54(&vec, &work->rot.vy, work->field_3EC, work->field_3D0);
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
        s19b_jeep_800D3A54(&vec, &work->rot.vy, work->field_3EC, work->field_3D0);
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
            Takabe_JeepSystem.flags_50 = (Takabe_JeepSystem.flags_50 & ~0x20020) | 0x200;
        }
        break;
    case 3:
        s19b_jeep_800D2D3C(work);
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
            s19b_jblood_800C850C(&work->tyres.objs->objs[1].world, &work->body.objs->world);
            s19b_jblood_800C850C(&work->tyres.objs->objs[2].world, &work->body.objs->world);
        }
        break;
    case 4:
        s19b_jeep_800D2D3C(work);
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
        work->func_3F8 = s19b_jeep_800D2E78;
        work->field_3DC = 0;
    }
    s19b_jeep_800D3CA8(work, 0);
}

void s19b_jeep_800D36A4(JeepWork *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_800D2CE8(work);
    s19b_jeep_800D2D3C(work);

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
            work->func_3F8 = s19b_jeep_800D2E78;
            work->field_3DC = 0;
        }
        break;
    }
}

void s19b_jeep_800D37D0(JeepWork *work)
{
    CONTROL *ctl = &work->control;

    s19b_jeep_800D2CE8(work);
    s19b_jeep_800D2D3C(work);

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
            work->func_3F8 = s19b_jeep_800D3928;
            work->field_3DC = 0;
        }
        break;
    }
}

void s19b_jeep_800D3928(JeepWork *work)
{
    s19b_jeep_800D2CE8(work);
    s19b_jeep_800D2D3C(work);
    if ((work->field_3CC & 0x3F) == 0)
    {
        work->field_3CA = ((rand() * 60) >> 15) - 0x258;
    }
    work->field_3C8 = GV_NearSpeed(work->field_3C8, work->field_3CA, 0x1E);
}

int s19b_jeep_800D399C(void)
{
    return s19b_dword_800DE64C->field_3D0;
}
int s19b_jeep_800D39B4(SVECTOR *dst)
{
    *dst = s19b_dword_800DE64C->control.mov;
    return s19b_dword_800DE64C->field_3C8;
}

int s19b_jeep_800D39F0(void)
{
    CONTROL **where = GM_WhereList;
    MAP      *map   = (*where)->map;
    int       count = 0;
    int       n;

    for (n = GM_N_WhereList; n > 0; n--)
    {
        CONTROL *control = *where;
        if ((control->radar_atr & RADAR_VISIBLE) && control->map == map)
        {
            count++;
        }
        where++;
    }
    return count;
}


/* moves pos by len in the direction *dir, then turns *dir by angle (cf. s19a_800D9BBC) */
void s19b_jeep_800D3A54(SVECTOR *pos, short *dir, int angle, int len)
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

void s19b_jeep_800D3CA8(JeepWork *work, int arg1)
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
