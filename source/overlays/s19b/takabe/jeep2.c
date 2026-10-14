#include "mgstype.h"
#include "game/game.h"
#include "jeep_system.h"
#include "jeep2.h"


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
    work->pos.vx += work->move.vx;
    work->pos.vz += work->move.vz;

    control->mov.vx = work->pos.vx - Takabe_JeepSystem.world_pos.vx;
    control->mov.vz = work->pos.vz - Takabe_JeepSystem.world_pos.vz;

    if (work->hit != 0)
    {
        if (work->field_3C0 == 0)
        {
            work->speed_target -= work->speed_target / 4;
        }

        work->flags |= 1;

        if (work->wobble == 0)
        {
            work->wobble = 20;
        }
    }
    else
    {
        work->flags &= ~1;
    }

    work->hit = 0;

    if (work->wobble != 0)
    {
        work->wobble--;
    }

    work->act_fn(work);

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

        if (work->side_fn != s19b_jeep_liq_800D7D68)
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

    s19b_spark2_m_800D9C90(&control->mov, &work->pos, &work->speed, &out);
    s19b_spark2_m_800D9EC0(&control->mov, &work->rot, &work->move, &work->field_388);
    s19b_spark2_m_800DA0B4(work->tyres.rots, work->speed_prev, &work->rot, &work->field_398);

    control->turn = work->rot;
    control->turn.vx = 0;

    light_pos = control->mov;
    light_pos.vy += 250;
    DG_GetLightMatrix(&light_pos, work->light);

    GM_ActControl(control);

    GM_ActObject2(&work->body);
    RotMatrixX(work->rot.vx, &work->body.objs->world);
    ScaleMatrix(&work->body.objs->world, &s19b_dword_800C3A84);

    rot.vx = control->rot.vx;
    rot.vy = control->rot.vy;
    rot.vz = 0;
    DG_SetPos2(&control->mov, &rot);

    GM_ActObject2(&work->tyres);
    RotMatrixX(work->rot.vx, &work->tyres.objs->world);
    ScaleMatrix(&work->tyres.objs->world, &s19b_dword_800C3A84);

    GM_ActObject2((OBJECT *)&work->front_headlights);
    GM_ActObject2((OBJECT *)&work->headlights);

    DG_SetPos(&work->body.objs->world);
    DG_MovePos(&s19b_dword_800C3A7C);

    GM_ActObject2((OBJECT *)&work->gun);

    GM_MoveTarget(work->target, &control->mov);
}

void s19b_jeep2_800D6A70(Jeep2Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->tyres);
    GM_FreeObject((OBJECT *)&work->gun);
    GM_FreeObject((OBJECT *)&work->front_headlights);
    GM_FreeObject((OBJECT *)&work->headlights);
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

    body = &work->body;
    rot = &control->rot;
    top = &work->tyres;

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

    s19b_jeep2_800D6AD8(work);

    work->rot = *rot;

    work->pos = Takabe_JeepSystem.world_pos;
    work->pos.vz += 20000;
    work->old_pos = work->pos;
    work->old_pos.vz += 400;

    work->move = work->field_380 = DG_ZeroVector;
    work->field_388 = work->move;
    work->move.vz = -400;
    work->field_388.vz = -0x800;

    work->speed = work->speed_target = 0x1A9;
    work->side = 0;
    work->side_target = 0;
    work->flags = 0;
    work->wobble = 0;

    z = work->pos.vz - Takabe_JeepSystem.world_pos.vz;
    control->mov.vz = z;
    s19b_jeep_gls_800CEC24(z, &vec);
    control->mov.vx = vec.vx;
    work->pos.vx = vec.vx + Takabe_JeepSystem.world_pos.vx;
    control->mov.vy = vec.vy;

    work->act_fn = s19b_jeep_liq_800D76B0;
    work->speed_fn = s19b_jeep_liq_800D7ACC;
    work->side_fn = s19b_jeep_liq_800D7BB0;
    work->frame = 0;
    work->phase = 0;
    work->speed_timer = 0;
    work->speed_fn_time = 0;
    work->side_count = 0;
    work->side_step = 0;
    work->mode = 0;
    work->shoot_count = 0;
    work->field_3F4 = 0;
    work->mode_fn = s19b_jeep_liq_800D81A8;

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
