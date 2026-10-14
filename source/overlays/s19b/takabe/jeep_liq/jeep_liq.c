#include "jeep_liq.h"
#include "../jeep2.h"

#include <rand.h>
#include "mgstype.h"
#include "game/game.h"
#include "psxdefs.h"



extern int   s19b_jeep_800D399C(void);
extern int   s19b_jeep_liq_800D771C(int center, int from, int to);
extern void  s19b_jeep_liq_800D6FB8(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7114(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7200(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7330(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7468(Jeep2Work *work);
extern void  s19b_jeep_liq_800D76F8(Jeep2Work *work, Jeep2Func func);
extern void  s19b_jeep_liq_800D7B3C(Jeep2Work *work, Jeep2Func func);
extern void  s19b_jeep_liq_800D7BB0(Jeep2Work *work);
extern void  s19b_jeep_liq_800D8044(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7A5C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7860(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7CBC(Jeep2Work *work);
extern void  s19b_jlamp_800D0A20(int arg0);
extern void  s19b_jeep_liq_800D77F0(Jeep2Work *work);
extern void  s19b_jeep_liq_800D797C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7C0C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D8014(Jeep2Work *work, Jeep2Func func);
extern void  s19b_jeep_liq_800D8118(Jeep2Work *work);
extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void  sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);
extern int   s19b_jeep_gls_800CEDFC(int arg0, int arg1);

void s19b_jeep_liq_800D6FB8(Jeep2Work *work)
{
    SVECTOR *pos = &work->control.mov;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->velocity;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->rot);
    DG_RotVector(&rot, &rot, 1);
    work->speed.vx = rot.vx;
    work->speed.vz = rot.vz;
    s19b_jeep_gls_800CEC24(pos->vz - 0x640, &vec);
    GV_SubVec3(&vec, pos, &vec);
    vec.vx += work->lateral;
    vec.vx += rsin(work->time << 5) * 50 >> 12;
    vec.vx += (rsin(work->time << 7) << 1) * work->shake >> 12;
    work->rot.vy = GV_VecDir2(&vec);
    work->time++;
    work->old_velocity = work->velocity;
}
void s19b_jeep_liq_800D7114(Jeep2Work *work)
{
    int state;

    work->speed_func(work);
    work->steer_func(work);
    work->mode_func(work);
    s19b_jeep_liq_800D6FB8(work);

    state = Takabe_JeepSystem.seg_event;
    if (state != 0)
    {
        if (state == 6)
        {
            work->state = s19b_jeep_liq_800D7200;
        }
        else if (state == 7)
        {
            work->state = s19b_jeep_liq_800D7330;
        }
        else if (state == 8)
        {
            work->state = s19b_jeep_liq_800D7468;
        }
    }
    if (work->state != s19b_jeep_liq_800D7114)
    {
        work->field_3EC = 0;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D77F0);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7BB0);
        s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8044);
        work->step = 0;
    }
}
void s19b_jeep_liq_800D7200(Jeep2Work *work)
{
    SVECTOR *pos = &work->control.mov;

    switch (work->step)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 10)
        {
            work->step = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D7860(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7CBC(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 12)
        {
            work->step = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D77F0(work);
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 650, 50);
        if (work->lateral == 650)
        {
            work->state = s19b_jeep_liq_800D7114;
            work->lateral_target = 650;
            work->step = 0;
        }
        break;
    }
}
void s19b_jeep_liq_800D7330(Jeep2Work *work)
{
    SVECTOR *pos = &work->control.mov;

    switch (work->step)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 750, 50);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 2000) == 11)
        {
            work->step = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7C0C(work);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 3000) == 13)
        {
            work->step = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 750, 50);
        if (work->lateral == 750)
        {
            work->state = s19b_jeep_liq_800D7114;
            s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8118);
            work->step = 0;
        }
        break;
    }
}
void s19b_jeep_liq_800D7468(Jeep2Work *work)
{
    SVECTOR *pos = &work->control.mov;
    SVECTOR  rot;
    SVECTOR  vec;

    switch (work->step)
    {
    case 0:
        work->time = 0;
        work->step = 1;
        work->field_3C0 = 1;
        Takabe_JeepSystem.liq_flags |= 0x20000;
        GM_GameStatus |= 0x104A2000;
        s19b_jlamp_800D0A20(1);
        /* fallthrough */
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 500, 30);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 22000) == 14)
        {
            work->step = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D6FB8(work);
        work->lateral = GV_NearSpeed(work->lateral, 250, 30);
        work->velocity = GV_NearSpeed(work->velocity, 500, 3);
        if (s19b_jeep_gls_800CEDFC(pos->vz, 6000) == 14)
        {
            work->step = 3;
            work->field_380 = work->speed;
        }
        break;
    case 3:
        memset(&vec, 0, 8);
        vec.vz = work->velocity;
        rot = vec;
        DG_SetPos2(&DG_ZeroVector, &work->rot);
        DG_RotVector(&rot, &rot, 1);
        work->field_380.vx = GV_NearExp8(work->field_380.vx, 0);
        work->field_380.vz = GV_NearExp8(work->field_380.vz, 0);
        work->speed.vx = rot.vx + work->field_380.vx;
        work->speed.vz = rot.vz + work->field_380.vz;
        work->rot.vy = GV_NearExp8(work->rot.vy, 0xC00);
        work->velocity = GV_NearExp4(work->velocity, 0);
        work->old_velocity = 0;
        if (work->speed.vx == 0 && work->speed.vz == 0)
        {
            work->step = 4;
        }
        break;
    case 4:
        break;
    }
    work->time++;
}
void s19b_jeep_liq_800D76B0(Jeep2Work *work)
{
    work->speed_func(work);
    work->lateral = 0;
    work->mode_func(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(Jeep2Work *work, Jeep2Func func)
{
    if (work->speed_func != func)
    {
        work->speed_func = func;
        work->field_3D8 = 0;
        work->field_3D4 = 0;
    }
}

int s19b_jeep_liq_800D771C(int center, int from, int to)
{
    int diff = to - from;
    int base = s19b_jeep_800D399C();

    if (diff >= 0)
    {
        if (diff > 3000)
        {
            center = GV_NearSpeed(center, base + 100, 15);
        }
        else if (diff > 750)
        {
            center = GV_NearSpeed(center, base + 50, 8);
        }
        else if (diff > 93)
        {
            center = GV_NearSpeed(center, base + 15, 3);
        }
    }
    else
    {
        if (diff < -3000)
        {
            center = GV_NearSpeed(center, base - 100, 15);
        }
        else if (diff < -750)
        {
            center = GV_NearSpeed(center, base - 50, 8);
        }
        else if (diff < -93)
        {
            center = GV_NearSpeed(center, base - 15, 3);
        }
    }
    return center;
}
void s19b_jeep_liq_800D77F0(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_800D399C();
    work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, 0x753, v);
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}
void s19b_jeep_liq_800D7860(Jeep2Work *work)
{
    int s1 = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    int a1 = s19b_jeep_800D399C();

    if (work->field_3D4 == 0)
    {
        if (work->flags & 8)
        {
            int v1 = work->velocity - 0x32;
            int v0;
            work->velocity = v1;
            v0 = v1 - v1 / 16;
            work->velocity = v0;
            work->target_velocity = v0;
            work->field_3D4 = 0x3c;
            Takabe_JeepSystem.liq_flags |= 2;
        }
        else if (s1 >= 0x5dd)
        {
            work->target_velocity = GV_NearSpeed(work->target_velocity, a1 + 0x32, 7);
            Takabe_JeepSystem.liq_flags |= 0x1000;
        }
    }
    else
    {
        work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, 0xbb8, s1);
        work->field_3D4--;
    }
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}
void s19b_jeep_liq_800D797C(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_800D399C();
    work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, 0, v);
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}
void s19b_jeep_liq_800D79EC(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_800D399C();
    work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, -0x177, v);
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}
void s19b_jeep_liq_800D7A5C(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_800D399C();
    work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, 0xbb8, v);
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}
void s19b_jeep_liq_800D7ACC(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_800D399C();
    work->target_velocity = s19b_jeep_liq_800D771C(work->target_velocity, 0x1194, v);
    work->velocity = GV_NearSpeed(work->velocity, work->target_velocity, 5);
}

void s19b_jeep_liq_800D7B3C(Jeep2Work *work, Jeep2Func func)
{
    if (work->steer_func != func)
    {
        work->steer_func = func;
        work->sub_step = 0;
        work->sub_time = 0;
    }
}

int s19b_jeep_liq_800D7B60(int center, int range)
{
    return (rand() * range >> 15) - range / 2 + center;
}
void s19b_jeep_liq_800D7BB0(Jeep2Work *work)
{
    if (++work->sub_time == 0x1e)
    {
        work->lateral_target = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->sub_time = 0;
    }
    work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x1e);
}
void s19b_jeep_liq_800D7C0C(Jeep2Work *work)
{
    int n = work->sub_time + 1;
    work->sub_time = n;

    switch (work->sub_step)
    {
    case 0:
        work->lateral_target = 0x546;
        work->lateral = GV_NearSpeed(work->lateral, 0x546, 0x32);
        if (work->sub_time == 0x28)
        {
            work->sub_step = 1;
            work->sub_time = 0x13;
        }
        break;
    case 1:
        if (n == 0x14)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(0x4e2, 0xfa);
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7CBC(Jeep2Work *work)
{
    int n = work->sub_time + 1;
    work->sub_time = n;

    switch (work->sub_step)
    {
    case 0:
        work->lateral_target = 0x5dc;
        if (work->sub_time == 0x28)
        {
            work->sub_step = 1;
            work->sub_time = 0x13;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x32);
        break;
    case 1:
        if (n == 0x14)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(0x5dc, 0xfa);
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7D68(Jeep2Work *work)
{
    int n = work->sub_time + 1;
    work->sub_time = n;

    switch (work->sub_step)
    {
    case 0:
        if (n == 1)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(0x2ee, 0x190);
        }
        else if (n == 0x1e)
        {
            work->sub_step = 1;
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x32);
        break;
    case 1:
        if (n == 1)
        {
            work->lateral_target = -0x226;
        }
        else if (n == 0x3c)
        {
            work->sub_step = 0;
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x64);
        break;
    }
}
void s19b_jeep_liq_800D7E2C(Jeep2Work *work)
{
    int n = work->sub_time + 1;
    work->sub_time = n;

    switch (work->sub_step)
    {
    case 0:
        if (n == 1)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(-0x2ee, 0x96);
        }
        else if (n == 0x3c)
        {
            work->sub_step = 1;
            work->sub_time = 0;
        }
        {
            int r = GV_NearSpeed(work->lateral, work->lateral_target, 0x4b);
            work->lateral = r;
            if (r == work->lateral_target)
            {
                Takabe_JeepSystem.liq_flags |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(-0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->sub_step = 1;
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D7F20(Jeep2Work *work)
{
    int n = work->sub_time + 1;
    work->sub_time = n;

    switch (work->sub_step)
    {
    case 0:
        if (n == 1)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(0x2ee, 0x96);
            work->sub_time = 0;
        }
        else if (n == 0x3c)
        {
            work->sub_step = 1;
            work->sub_time = 0;
        }
        {
            int r = GV_NearSpeed(work->lateral, work->lateral_target, 0x4b);
            work->lateral = r;
            if (r == work->lateral_target)
            {
                Takabe_JeepSystem.liq_flags |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->lateral_target = s19b_jeep_liq_800D7B60(0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->sub_step = 1;
            work->sub_time = 0;
        }
        work->lateral = GV_NearSpeed(work->lateral, work->lateral_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D8014(Jeep2Work *work, Jeep2Func func)
{
    if (work->mode_func != func)
    {
        work->mode_func = func;
        work->sub_step = 0;
        work->sub_time = 0;
        work->flags &= ~2;
    }
}
extern u_char s19b_dword_800C3A9C[];
extern int s19b_jeep_800D39B4(SVECTOR *dst);

void s19b_jeep_liq_800D8044(Jeep2Work *work)
{
    SVECTOR sp10;

    s19b_jeep_800D39B4(&sp10);
    if (Takabe_JeepSystem.has_homing_target != 0 && work->field_3F0 >= 0x15)
    {
        work->field_3F0 = 0;
        if (work->lateral > 0)
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7E2C);
        }
        else
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
        }
        Takabe_JeepSystem.liq_flags |= 0x1000;
        GM_SeSet(&work->control.mov, s19b_dword_800C3A9C[GV_RandU(4)]);
    }
    else
    {
        work->field_3F0++;
    }
}
void s19b_jeep_liq_800D8118(Jeep2Work *work)
{
    SVECTOR dst;
    int     d;

    s19b_jeep_800D39B4(&dst);
    d = work->control.mov.vz - dst.vz;
    if (d < 0)
    {
        work->field_3EC = 5;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7D68);
    }
    else
    {
        work->field_3EC = 2;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
    }
}
extern void s19b_jeep_liq_800D7114(Jeep2Work *work);

void s19b_jeep_liq_800D81A8(Jeep2Work *work)
{
    int n = work->field_3F0;
    work->field_3F0 = n + 1;
    if (n == 0)
    {
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_RADAR_OFF | STATE_PADRELEASE;
        s19b_jlamp_800D0A20(0);
    }
    else if (n >= 0x150)
    {
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_RADAR_OFF | STATE_PADRELEASE);
        s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8044);
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D77F0);
        work->state = s19b_jeep_liq_800D7114;
    }
}
const SVECTOR s19b_dword_800DDE60 = {0x15E, 0x3CF, -0x15E, 0};

void s19b_jeep_liq_800D8250(Work *work)
{
    OBJECT  *body = &work->body;
    CONTROL *ctl = &work->control;
    DG_OBJS *objs;
    SVECTOR *jpos = &Takabe_JeepSystem.liq_pos;
    SVECTOR  pos = s19b_dword_800DDE60;

    GM_ActMotion(body);
    ctl->rot = ctl->turn = DG_ZeroVector;
    ctl->mov = pos;
    GM_ActControl(ctl);
    GM_ActObject(body);
    objs = body->objs;
    CompMatrix(work->root_mat, &objs->world, &objs->world);
    DG_GetLightMatrix(&ctl->mov, &work->light[0]);
    ctl->mov.vx = objs->world.t[0];
    ctl->mov.vy = objs->world.t[1];
    ctl->mov.vz = objs->world.t[2];
    jpos->vx = body->objs->objs[6].world.t[0];
    jpos->vy = body->objs->objs[6].world.t[1];
    jpos->vz = body->objs->objs[6].world.t[2];
    GM_MoveTarget(work->target, &ctl->mov);
    s19b_spark2_m_800D964C(work);
    sna_act_helper2_helper2_80033054(0x7BF2, &work->head_adjust);
    work->adjust[6].vx = work->head_adjust.vx;
    if ((work->field_940 & 3) == 1)
    {
        body->objs->flag |= 0x80;
    }
    else
    {
        body->objs->flag &= ~0x80;
    }
}
int s19b_jeep_liq_800D8420(Work *work, int name)
{
    CONTROL *ctl = &work->control;
    OBJECT  *body;
    OBJECT  *gun;
    HOMING  *homing;

    if (GM_InitControl(ctl, name, GM_CurrentMap) < 0)
    {
        return -1;
    }
    ctl->mov = work->root_ctrl->mov;
    ctl->rot = work->root_ctrl->rot;
    GM_ConfigControlAttribute(ctl, 5);
    GM_ConfigControlInterp(ctl, 4);

    body = &work->body;
    gun = &work->gun;
    GM_InitObject(body, GV_StrCode("liquid"), 0x2D, GV_StrCode("lqd_19b"));
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode("lqd_19b"), work->m_segs1, work->m_segs2, ctl,
                           work->rots);
    GM_ConfigObjectLight(body, &work->light[0]);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ConfigMotionAdjust(body, work->adjust);
    GM_InitObject(gun, GV_StrCode("famas"), 0x6D, 0);
    GM_ConfigObjectLight(gun, &work->light[0]);
    GM_ConfigObjectRoot(gun, body, 4);
    work->target = GM_AllocTarget();
    homing = GM_SetHomingTarget(&work->body.objs->objs[5].world, ctl);
    work->homing = homing;
    if (homing != NULL)
    {
        homing->flag = 1;
    }
    Takabe_JeepSystem.liq_body = body;
    ctl->r_sphere = -2;
    work->ai_off = 0;
    work->ai_mode = 0;
    work->ai_state = 0;
    return 0;
}
void s19b_spark2_m_800D8620(Work *work)
{
    GM_FreeTarget(work->target);
    GM_ResetHomingTarget(work->homing);
    GM_FreeObject(&work->gun);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}
extern void s19b_jeep_liq_800D8250(Work *work);
extern int  s19b_jeep_liq_800D8420(Work *work, int name);
const char s19b_aJeepliqc_800DDE80[] = "jeep_liq.c";
const char s19b_dword_800DDE8C[] = "liqiud";

GV_ACT *s19b_spark2_m_800D8670(CONTROL *root_ctrl, MATRIX *root_mat, int *hit)
{
    Work *work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_liq_800D8250, s19b_spark2_m_800D8620,
                         s19b_aJeepliqc_800DDE80);
        work->root_ctrl = root_ctrl;
        work->root_mat = root_mat;
        work->hit = hit;
        if (s19b_jeep_liq_800D8420(work, GV_StrCode(s19b_dword_800DDE8C)) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return &work->actor;
}
