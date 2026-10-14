#include "game/game.h"
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

/* NON_MATCHING: the draft below is instruction-identical except that gcc folds
 * "flags |= 2" (flags is 0 there) into a constant load, which changes the
 * register allocation (flags/target swap s0/s1). The original keeps the ori. */
#if 0
extern VECTOR s19b_dword_800DDD7C;
extern u_char s19b_dword_800C3990[];
extern u_char s19b_dword_800C3994[];

extern int  s19b_spark2_m_800D9C90(SVECTOR *mov, VECTOR *pos, int *param, SVECTOR *out);
extern int  s19b_spark2_m_800D9EC0(SVECTOR *mov, SVECTOR *rot, SVECTOR *speed, SVECTOR *out);
extern void s19b_spark2_m_800DA0B4(SVECTOR *rots, int param, SVECTOR *rot, SVECTOR *out);
extern void s19b_jeep_mrl_800D3928(JeepWork *work);
extern void *NewPadVibration(u_char *table, int dir);

void s19b_jeep_800D2258(JeepWork *work)
{
    CONTROL *control;
    TARGET  *target;
    SVECTOR  light_pos;
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

        if (work->func_3F8 != s19b_jeep_mrl_800D3928)
        {
            work->field_3D0 += work->field_3D0 / 16;
            work->field_3D4 -= work->field_3D4 / 4;
            work->vibrate_timer = 5;
            NewPadVibration(s19b_dword_800C3990, 1);
            NewPadVibration(s19b_dword_800C3994, 0);
            flags |= 2;
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
            flags |= 2;
        }
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
    s19b_spark2_m_800DA0B4(work->jeep_t.rots, work->field_3E8, &work->rot, &work->field_3C0);

    work->jeep_t.objs->rots[3].vy = -work->field_3EC;
    work->jeep_t.objs->rots[4].vy = -work->field_3EC;

    control->turn = work->rot;
    control->turn.vx = 0;

    light_pos = control->mov;
    light_pos.vy += 250;
    DG_GetLightMatrix(&light_pos, work->light);

    GM_ActControl(control);

    GM_ActObject2(&work->jeep_b);
    RotMatrixX(work->rot.vx, &work->jeep_b.objs->world);
    u.scale = s19b_dword_800DDD7C;
    ScaleMatrix(&work->jeep_b.objs->world, &u.scale);

    u.rot.vx = control->rot.vx;
    u.rot.vy = control->rot.vy;
    u.rot.vz = 0;
    DG_SetPos2(&control->mov, &u.rot);

    GM_ActObject2(&work->jeep_t);
    RotMatrixX(work->rot.vx, &work->jeep_t.objs->world);
    scale2 = s19b_dword_800DDD7C;
    ScaleMatrix(&work->jeep_t.objs->world, &scale2);

    GM_ActObject2((OBJECT *)&work->fhl);
    GM_ActObject2((OBJECT *)&work->hl);

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
#endif

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_800D2258.s")
void s19b_jeep_800D2258(JeepWork *work);

void s19b_jeep_800D2790(JeepWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->jeep_b);
    GM_FreeObject(&work->jeep_t);
    GM_FreeObject((OBJECT *)&work->fhl);
    GM_FreeObject((OBJECT *)&work->hl);
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

extern void s19b_jeep_mrl_800D2E78(JeepWork *work);
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

    body = &work->jeep_b;
    rot = &control->rot;
    top = &work->jeep_t;

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

    obj = &work->fhl;
    GM_InitObjectNoRots(obj, 0x3A07, 0x16D, 0);
    obj->objs->root = &body->objs->world;
    GM_ConfigObjectLight((OBJECT *)obj, &work->light2);

    obj = &work->hl;
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
    work->func_3F8 = s19b_jeep_mrl_800D2E78;
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
