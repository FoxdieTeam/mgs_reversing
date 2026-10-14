#include "mgstype.h"
#include "game/game.h"
#include "jeep_system.h"

typedef struct _Jeep2Work Jeep2Work;

typedef void (*Jeep2Func)(Jeep2Work *);

struct _Jeep2Work
{
    /* +0x000 */ GV_ACT         actor;
    /* +0x020 */ GV_ACT        *liq;
    /* +0x024 */ CONTROL        control;
    /* +0x0A0 */ TARGET        *target;
    /* +0x0A4 */ OBJECT         jeep_b;
    /* +0x188 */ OBJECT         jeep_t;
    /* +0x26C */ OBJECT_NO_ROTS gun;
    /* +0x290 */ MATRIX         light[2];
    /* +0x2D0 */ OBJECT_NO_ROTS fhl;
    /* +0x2F4 */ OBJECT_NO_ROTS hl;
    /* +0x318 */ MATRIX         light2;
    /* +0x338 */ char           pad_338[0x20];
    /* +0x358 */ VECTOR         pos;
    /* +0x368 */ VECTOR         old_pos;
    /* +0x378 */ SVECTOR        speed;
    /* +0x380 */ SVECTOR        field_380;
    /* +0x388 */ SVECTOR        field_388;
    /* +0x390 */ SVECTOR        rot;
    /* +0x398 */ SVECTOR        field_398;
    /* +0x3A0 */ int            field_3A0;
    /* +0x3A4 */ int            field_3A4;
    /* +0x3A8 */ int            field_3A8;
    /* +0x3AC */ int            field_3AC;
    /* +0x3B0 */ int            field_3B0;
    /* +0x3B4 */ int            flags;
    /* +0x3B8 */ int            timer;
    /* +0x3BC */ int            se_timer;
    /* +0x3C0 */ int            field_3C0;
    /* +0x3C4 */ int            hit;
    /* +0x3C8 */ int            field_3C8;
    /* +0x3CC */ int            field_3CC;
    /* +0x3D0 */ Jeep2Func      func_3D0;
    /* +0x3D4 */ int            field_3D4;
    /* +0x3D8 */ int            field_3D8;
    /* +0x3DC */ Jeep2Func      func_3DC;
    /* +0x3E0 */ int            field_3E0;
    /* +0x3E4 */ int            field_3E4;
    /* +0x3E8 */ Jeep2Func      func_3E8;
    /* +0x3EC */ int            field_3EC;
    /* +0x3F0 */ int            field_3F0;
    /* +0x3F4 */ int            field_3F4;
    /* +0x3F8 */ Jeep2Func      func_3F8;
};

extern VECTOR  s19b_dword_800C3A84;
extern SVECTOR s19b_dword_800C3A7C;

extern int  s19b_jeep_gls_800CEDFC(int z, int limit);
extern void s19b_jeep_gls_800CEC24(int z, SVECTOR *out);
extern void s19b_spark2_m_800D9C90(SVECTOR *mov, VECTOR *pos, int *param, SVECTOR *out);
extern void s19b_spark2_m_800D9EC0(SVECTOR *mov, SVECTOR *rot, SVECTOR *speed, SVECTOR *out);
extern void s19b_spark2_m_800DA0B4(SVECTOR *rots, int param, SVECTOR *rot, SVECTOR *out);
extern GV_ACT *s19b_spark2_m_800D8670(CONTROL *control, MATRIX *root, int *hit);
extern void s19b_jeep_liq_800D76B0(Jeep2Work *work);
extern void s19b_jeep_liq_800D7ACC(Jeep2Work *work);
extern void s19b_jeep_liq_800D7BB0(Jeep2Work *work);
extern void s19b_jeep_liq_800D7D68(Jeep2Work *work);
extern void s19b_jeep_liq_800D81A8(Jeep2Work *work);
extern void NewJeepLamp2(MATRIX *root);

void s19b_jeep2_800D667C(Jeep2Work *work)
{
    CONTROL *control;
    TARGET  *target;
    SVECTOR  out;
    SVECTOR  light_pos;
    SVECTOR  rot;

    control = &work->control;

    work->old_pos = work->pos;
    work->pos.vx += work->speed.vx;
    work->pos.vz += work->speed.vz;

    control->mov.vx = work->pos.vx - Takabe_JeepSystem.world_pos.vx;
    control->mov.vz = work->pos.vz - Takabe_JeepSystem.world_pos.vz;

    if (work->hit != 0)
    {
        if (work->field_3C0 == 0)
        {
            work->field_3B0 -= work->field_3B0 / 4;
        }

        work->flags |= 1;

        if (work->timer == 0)
        {
            work->timer = 20;
        }
    }
    else
    {
        work->flags &= ~1;
    }

    work->hit = 0;

    if (work->timer != 0)
    {
        work->timer--;
    }

    work->func_3D0(work);

    if (s19b_jeep_gls_800CEDFC(control->mov.vz, -8000) == 31)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    target = work->target;
    work->flags &= ~(4 | 8);

    if (target->damaged & TARGET_PUSH)
    {
        control->mov.vx += target->offset.vx;
        control->mov.vz += target->offset.vz;
        work->pos.vx += target->offset.vx;
        work->pos.vy += target->offset.vy;

        if (work->func_3E8 != s19b_jeep_liq_800D7D68)
        {
            work->flags |= 8;
            if (work->se_timer == 0)
            {
                work->se_timer = 15;
                GM_SeSet(&control->mov, 0xB0);
            }
        }
        else
        {
            work->flags |= 4;
            if (work->field_3C0 == 0)
            {
                work->rot.vy = GV_NearExp2(work->rot.vy, 0x800);
            }

            if (work->se_timer == 0 && target->offset.vx > 40)
            {
                work->se_timer = 15;
                GM_SeSet(&control->mov, 0xB0);
            }
        }
    }

    target->damaged &= ~TARGET_PUSH;
    target->offset = DG_ZeroVector;

    if (work->se_timer != 0)
    {
        work->se_timer--;
    }

    s19b_spark2_m_800D9C90(&control->mov, &work->pos, &work->field_3A8, &out);
    s19b_spark2_m_800D9EC0(&control->mov, &work->rot, &work->speed, &work->field_388);
    s19b_spark2_m_800DA0B4(work->jeep_t.rots, work->field_3AC, &work->rot, &work->field_398);

    control->turn = work->rot;
    control->turn.vx = 0;

    light_pos = control->mov;
    light_pos.vy += 250;
    DG_GetLightMatrix(&light_pos, work->light);

    GM_ActControl(control);

    GM_ActObject2(&work->jeep_b);
    RotMatrixX(work->rot.vx, &work->jeep_b.objs->world);
    ScaleMatrix(&work->jeep_b.objs->world, &s19b_dword_800C3A84);

    rot.vx = control->rot.vx;
    rot.vy = control->rot.vy;
    rot.vz = 0;
    DG_SetPos2(&control->mov, &rot);

    GM_ActObject2(&work->jeep_t);
    RotMatrixX(work->rot.vx, &work->jeep_t.objs->world);
    ScaleMatrix(&work->jeep_t.objs->world, &s19b_dword_800C3A84);

    GM_ActObject2((OBJECT *)&work->fhl);
    GM_ActObject2((OBJECT *)&work->hl);

    DG_SetPos(&work->jeep_b.objs->world);
    DG_MovePos(&s19b_dword_800C3A7C);

    GM_ActObject2((OBJECT *)&work->gun);

    GM_MoveTarget(work->target, &control->mov);
}

void s19b_jeep2_800D6A70(Jeep2Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->jeep_b);
    GM_FreeObject(&work->jeep_t);
    GM_FreeObject((OBJECT *)&work->gun);
    GM_FreeObject((OBJECT *)&work->fhl);
    GM_FreeObject((OBJECT *)&work->hl);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->liq);
}

extern int s19b_dword_800C3A94;

void s19b_jeep2_800D6AD8(Jeep2Work *work)
{
    TARGET *target = GM_AllocTarget();

    work->target = target;
    GM_SetTarget(target, TARGET_PUSH, NO_SIDE, (SVECTOR *)&s19b_dword_800C3A94);
}

int s19b_jeep2_800D6B18(Jeep2Work *work, int name, int where)
{
    CONTROL         *control;
    OBJECT          *body;
    OBJECT          *top;
    OBJECT_NO_ROTS  *obj;
    SVECTOR         *rot;
    SVECTOR          vec;
    short            z;

    control = &work->control;

    if (GM_InitControl(control, name, where) < 0)
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
    GM_InitObject(top, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectJoint(top);

    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectLight(top, work->light);

    obj = &work->gun;
    GM_InitObjectNoRots(obj, 0x3FA9, 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->light);

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

    s19b_jeep2_800D6AD8(work);

    work->rot = *rot;

    work->pos = Takabe_JeepSystem.world_pos;
    work->pos.vz += 20000;
    work->old_pos = work->pos;
    work->old_pos.vz += 400;

    work->speed = work->field_380 = DG_ZeroVector;
    work->field_388 = work->speed;
    work->speed.vz = -400;
    work->field_388.vz = -0x800;

    work->field_3A8 = work->field_3B0 = 0x1A9;
    work->field_3A0 = 0;
    work->field_3A4 = 0;
    work->flags = 0;
    work->timer = 0;

    z = work->pos.vz - Takabe_JeepSystem.world_pos.vz;
    control->mov.vz = z;
    s19b_jeep_gls_800CEC24(z, &vec);
    control->mov.vx = vec.vx;
    work->pos.vx = vec.vx + Takabe_JeepSystem.world_pos.vx;
    control->mov.vy = vec.vy;

    work->func_3D0 = s19b_jeep_liq_800D76B0;
    work->func_3DC = s19b_jeep_liq_800D7ACC;
    work->func_3E8 = s19b_jeep_liq_800D7BB0;
    work->field_3C8 = 0;
    work->field_3CC = 0;
    work->field_3D4 = 0;
    work->field_3D8 = 0;
    work->field_3E0 = 0;
    work->field_3E4 = 0;
    work->field_3EC = 0;
    work->field_3F0 = 0;
    work->field_3F4 = 0;
    work->func_3F8 = s19b_jeep_liq_800D81A8;

    work->liq = s19b_spark2_m_800D8670(control, &body->objs->world, &work->hit);
    NewJeepLamp2(&body->objs->world);

    Takabe_JeepSystem.active2 = 1;
    Takabe_JeepSystem.control2 = control;
    Takabe_JeepSystem.rot2 = rot;
    Takabe_JeepSystem.flags_54 = 0x10000;
    Takabe_JeepSystem.body2 = body;
    return 0;
}

extern const char s19b_aJeepc_800DDE44[];

void *s19b_jeep2_800D6F24(int arg0, int arg1)
{
    Jeep2Work *work = GV_NewActor(GV_ACTOR_USER, 0x3FC);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep2_800D667C, s19b_jeep2_800D6A70,
                         s19b_aJeepc_800DDE44);
        if (s19b_jeep2_800D6B18(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return work;
}
