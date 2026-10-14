#include "mgstype.h"
#include "game/game.h"

#include "jeep2.h"

#include "jeep_system.h"

extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void *NewJeepLamp2(MATRIX *root);
extern void  s19b_jeep2_800D6AD8(Jeep2Work *work);
extern int   s19b_jeep_gls_800CEDFC(int arg0, int arg1);
extern int   s19b_spark2_m_800D9C90(CONTROL *control, VECTOR *pos, int *unused, SVECTOR *out);
extern int   s19b_spark2_m_800D9EC0(SVECTOR *pos, SVECTOR *rot, SVECTOR *cur, SVECTOR *prev);
extern void  s19b_spark2_m_800DA0B4(POLY_FT4 *poly, int arg1, SVECTOR *from, SVECTOR *to);
extern VECTOR  s19b_dword_800C3A84;
extern SVECTOR s19b_dword_800C3A7C;

void s19b_jeep2_800D667C(Jeep2Work *work)
{
    CONTROL *control;
    TARGET  *target;
    SVECTOR  out;
    SVECTOR  pos;
    SVECTOR  rot;

    work->old_pos = work->pos;
    work->pos.vx += work->speed.vx;
    work->pos.vz += work->speed.vz;

    control = &work->control;
    control->mov.vx = work->pos.vx - Takabe_JeepSystem.world_pos.vx;
    control->mov.vz = work->pos.vz - Takabe_JeepSystem.world_pos.vz;

    if (work->liq_hit != 0)
    {
        if (work->field_3C0 == 0)
        {
            work->target_velocity -= work->target_velocity / 4;
        }
        work->flags |= 1;
        if (work->shake == 0)
        {
            work->shake = 20;
        }
    }
    else
    {
        work->flags &= ~1;
    }
    work->liq_hit = 0;

    if (work->shake != 0)
    {
        work->shake--;
    }

    work->state(work);

    if (s19b_jeep_gls_800CEDFC(control->mov.vz, -8000) == 31)
    {
        GV_DestroyActor(work);
        return;
    }

    work->flags &= ~0xC;

    target = work->target;
    if (target->damaged & 8)
    {
        control->mov.vx += target->offset.vx;
        control->mov.vz += target->offset.vz;
        work->pos.vx += target->offset.vx;
        work->pos.vy += target->offset.vy;

        if (work->steer_func != s19b_jeep_liq_800D7D68)
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
            if (work->se_timer == 0 && target->offset.vx >= 41)
            {
                work->se_timer = 15;
                GM_SeSet(&control->mov, 0xB0);
            }
        }
    }

    target->damaged &= ~8;
    target->offset = DG_ZeroVector;

    if (work->se_timer != 0)
    {
        work->se_timer--;
    }

    s19b_spark2_m_800D9C90(control, &work->pos, &work->velocity, &out);
    s19b_spark2_m_800D9EC0(&control->mov, &work->rot, &work->speed, &work->old_speed);
    s19b_spark2_m_800DA0B4((POLY_FT4 *)&work->jeep_t.rots[0], work->old_velocity, &work->rot,
                           &work->old_rot);

    control->turn = work->rot;
    control->turn.vx = 0;

    pos = control->mov;
    pos.vy += 250;
    DG_GetLightMatrix(&pos, &work->light[0]);

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
    GV_DestroyActor(work->liquid);
}
extern SVECTOR s19b_dword_800C3A94;

void s19b_jeep2_800D6AD8(Jeep2Work *work)
{
    TARGET *target = GM_AllocTarget();

    work->target = target;
    GM_SetTarget(target, TARGET_PUSH, NO_SIDE, &s19b_dword_800C3A94);
}
int s19b_jeep2_800D6B18(Jeep2Work *work, int name, int where)
{
    CONTROL        *control = &work->control;
    SVECTOR        *rot;
    OBJECT         *obj;
    OBJECT_NO_ROTS *nr;
    SVECTOR         vec;
    short           z;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    rot = &control->rot;
    obj = &work->jeep_t;

    work->control.mov = work->control.rot = work->control.turn = DG_ZeroVector;
    work->control.step = DG_ZeroVector;
    control->rot.vy  = 0x800;
    control->turn.vy = 0x800;

    GM_InitObject(&work->jeep_b, 0x26C7, 0x2D, 0);
    GM_InitObject(obj, 0x26D9, 0x2D, 0);
    GM_ConfigObjectJoint(&work->jeep_b);
    GM_ConfigObjectJoint(obj);
    GM_ConfigObjectLight(&work->jeep_b, &work->light[0]);
    GM_ConfigObjectLight(obj, &work->light[0]);

    nr = &work->gun;
    GM_InitObjectNoRots(nr, 0x3FA9, 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)nr, &work->light[0]);

    nr = &work->fhl;
    GM_InitObjectNoRots(nr, 0x3A07, 0x16D, 0);
    nr->objs->root = &work->jeep_b.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    nr = &work->hl;
    GM_InitObjectNoRots(nr, 0xDA10, 0x16D, 0);
    nr->objs->root = &work->jeep_b.objs->world;
    GM_ConfigObjectLight((OBJECT *)nr, &work->light2);

    work->light2.t[0] = 0x80;
    work->light2.t[1] = 0x80;
    work->light2.t[2] = 0x80;

    s19b_jeep2_800D6AD8(work);

    work->rot = work->control.rot;

    work->pos = Takabe_JeepSystem.world_pos;
    work->pos.vz += 20000;
    work->old_pos = work->pos;
    work->old_pos.vz += 400;

    work->old_speed = work->speed = work->field_380 = DG_ZeroVector;
    work->speed.vz = -400;
    work->old_speed.vz = -0x800;

    work->target_velocity = 0x1A9;
    work->velocity = 0x1A9;
    work->lateral = 0;
    work->lateral_target = 0;
    work->flags = 0;
    work->shake = 0;

    z = work->pos.vz - Takabe_JeepSystem.world_pos.vz;
    control->mov.vz = z;
    s19b_jeep_gls_800CEC24(z, &vec);
    control->mov.vx = vec.vx;
    work->pos.vx = vec.vx + Takabe_JeepSystem.world_pos.vx;
    control->mov.vy = vec.vy;

    work->state = s19b_jeep_liq_800D76B0;
    work->speed_func = s19b_jeep_liq_800D7ACC;
    work->steer_func = s19b_jeep_liq_800D7BB0;
    work->time = 0;
    work->step = 0;
    work->field_3D4 = 0;
    work->field_3D8 = 0;
    work->sub_time = 0;
    work->sub_step = 0;
    work->field_3EC = 0;
    work->field_3F0 = 0;
    work->field_3F4 = 0;
    work->mode_func = s19b_jeep_liq_800D81A8;

    work->liquid = s19b_spark2_m_800D8670(control, &work->jeep_b.objs->world, &work->liq_hit);
    NewJeepLamp2(&work->jeep_b.objs->world);

    Takabe_JeepSystem.active2  = 1;
    Takabe_JeepSystem.control2 = control;
    Takabe_JeepSystem.rot2 = rot;
    Takabe_JeepSystem.liq_flags = 0x10000;
    Takabe_JeepSystem.body2 = &work->jeep_b;
    return 0;
}

extern void s19b_jeep2_800D667C(Jeep2Work *work);
extern int  s19b_jeep2_800D6B18(Jeep2Work *work, int arg0, int arg1);
const char s19b_aJeepc_800DDE44[] = "jeep2.c";

void *s19b_jeep2_800D6F24(int name, int where)
{
    Jeep2Work *work = GV_NewActor(GV_ACTOR_USER, 0x3FC);

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep2_800D667C, s19b_jeep2_800D6A70,
                         s19b_aJeepc_800DDE44);
        if (s19b_jeep2_800D6B18(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
