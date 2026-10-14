#include <rand.h>

#include "psxdefs.h"
#include "mgstype.h"
#include "game/game.h"
#include "jeep_liq.h"
#include "../jeep2.h"




extern int  s19b_dword_800C3AA0;
extern int  s19b_dword_800C3AA8;
extern int  s19b_dword_800C3AB0;
extern int  s19b_dword_800C3AB8;
extern int  s19b_dword_800C3AC0;
extern int  s19b_dword_800C3AC8;
extern int  s19b_dword_800DE650;

extern void *NewJeepBlood(MATRIX *world, int count, MATRIX *root);
extern void *NewJeepBullet(MATRIX *world, int side, int mode, int mode2);
extern void  s19b_jblood_800C7FB8(MATRIX *world);
extern void  ReadRotMatrix(MATRIX *m);

extern int   s19b_jeep_mrl_800D399C(void);
extern void  s19b_jeep_gls_800CEC24(int z, SVECTOR *out);
extern int   s19b_jeep_gls_800CEDFC(int z, int arg1);
extern void  s19b_jlamp_800D0A20(int arg0);

extern int   s19b_jeep_liq_800D771C(int cur, int center, int pos);
extern void  s19b_jeep_liq_800D76F8(Jeep2Work *work, Jeep2Func fn);
extern void  s19b_jeep_liq_800D7B3C(Jeep2Work *work, Jeep2Func fn);
extern void  s19b_jeep_liq_800D8014(Jeep2Work *work, Jeep2Func fn);
extern void  s19b_jeep_liq_800D77F0(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7860(Jeep2Work *work);
extern void  s19b_jeep_liq_800D797C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7A5C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7BB0(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7C0C(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7CBC(Jeep2Work *work);
extern void  s19b_jeep_liq_800D8044(Jeep2Work *work);
extern void  s19b_jeep_liq_800D8118(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7114(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7200(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7330(Jeep2Work *work);
extern void  s19b_jeep_liq_800D7468(Jeep2Work *work);

void s19b_jeep_liq_800D6FB8(Jeep2Work *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR  rot;
    SVECTOR  vec;

    memset(&vec, 0, 8);
    vec.vz = work->speed;
    rot = vec;
    DG_SetPos2(&DG_ZeroVector, &work->rot);
    DG_RotVector(&rot, &rot, 1);
    work->move.vx = rot.vx;
    work->move.vz = rot.vz;
    s19b_jeep_gls_800CEC24(ctl->mov.vz - 0x640, &vec);
    GV_SubVec3(&vec, &ctl->mov, &vec);
    vec.vx += work->side;
    vec.vx += rsin(work->frame << 5) * 50 >> 12;
    vec.vx += (rsin(work->frame << 7) << 1) * work->wobble >> 12;
    work->rot.vy = GV_VecDir2(&vec);
    work->frame++;
    work->speed_prev = work->speed;
}

void s19b_jeep_liq_800D7114(Jeep2Work *work)
{
    work->speed_fn();
    work->side_fn(work);
    work->mode_fn(work);
    s19b_jeep_liq_800D6FB8(work);

    if (Takabe_JeepSystem.field_40 != 0)
    {
        if (Takabe_JeepSystem.field_40 == 6)
        {
            work->act_fn = s19b_jeep_liq_800D7200;
        }
        else if (Takabe_JeepSystem.field_40 == 7)
        {
            work->act_fn = s19b_jeep_liq_800D7330;
        }
        else if (Takabe_JeepSystem.field_40 == 8)
        {
            work->act_fn = s19b_jeep_liq_800D7468;
        }
    }

    if (work->act_fn != s19b_jeep_liq_800D7114)
    {
        work->mode = 0;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D77F0);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7BB0);
        s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8044);
        work->phase = 0;
    }
}

void s19b_jeep_liq_800D7200(Jeep2Work *work)
{
    CONTROL *ctl = &work->control;
    int      side;

    switch (work->phase)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0x2EE, 0x32);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x7D0) == 10)
        {
            work->phase = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D7860(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7CBC(work);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0xBB8) == 12)
        {
            work->phase = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D77F0(work);
        s19b_jeep_liq_800D6FB8(work);
        side = GV_NearSpeed(work->side, 0x28A, 0x32);
        work->side = side;
        if (side == 0x28A)
        {
            work->act_fn = s19b_jeep_liq_800D7114;
            work->side_target = side;
            work->phase = 0;
        }
        break;
    }
}

void s19b_jeep_liq_800D7330(Jeep2Work *work)
{
    CONTROL *ctl = &work->control;

    switch (work->phase)
    {
    case 0:
        s19b_jeep_liq_800D7A5C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0x2EE, 0x32);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x7D0) == 11)
        {
            work->phase = 1;
        }
        break;
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        s19b_jeep_liq_800D7C0C(work);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0xBB8) == 13)
        {
            work->phase = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0x2EE, 0x32);
        if (work->side == 0x2EE)
        {
            work->act_fn = s19b_jeep_liq_800D7114;
            s19b_jeep_liq_800D8014(work, s19b_jeep_liq_800D8118);
            work->phase = 0;
        }
        break;
    }
}

void s19b_jeep_liq_800D7468(Jeep2Work *work)
{
    CONTROL *ctl = &work->control;
    SVECTOR rot;
    SVECTOR vec;

    switch (work->phase)
    {
    case 0:
        work->frame = 0;
        work->phase = 1;
        work->field_3C0 = 1;
        Takabe_JeepSystem.flags_54 |= 0x20000;
        GM_GameStatus |= STATE_PAUSE_ONLY | STATE_PADRELEASE;
        s19b_jlamp_800D0A20(1);
        /* fall through */
    case 1:
        s19b_jeep_liq_800D797C(work);
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0x1F4, 0x1E);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x55F0) == 14)
        {
            work->phase = 2;
        }
        break;
    case 2:
        s19b_jeep_liq_800D6FB8(work);
        work->side = GV_NearSpeed(work->side, 0xFA, 0x1E);
        work->speed = GV_NearSpeed(work->speed, 0x1F4, 3);
        if (s19b_jeep_gls_800CEDFC(ctl->mov.vz, 0x1770) == 14)
        {
            work->phase = 3;
            work->field_380 = work->move;
        }
        break;
    case 3:
        memset(&vec, 0, 8);
        vec.vz = work->speed;
        rot = vec;
        DG_SetPos2(&DG_ZeroVector, &work->rot);
        DG_RotVector(&rot, &rot, 1);
        work->field_380.vx = GV_NearExp8(work->field_380.vx, 0);
        work->field_380.vz = GV_NearExp8(work->field_380.vz, 0);
        work->move.vx = rot.vx + work->field_380.vx;
        work->move.vz = rot.vz + work->field_380.vz;
        work->rot.vy = GV_NearExp8(work->rot.vy, 0xC00);
        work->speed = GV_NearExp4(work->speed, 0);
        work->speed_prev = 0;
        if (work->move.vx == 0 && work->move.vz == 0)
        {
            work->phase = 4;
        }
        break;
    case 4:
        break;
    }
    work->frame++;
}

void s19b_jeep_liq_800D76B0(Jeep2Work *work)
{
    work->speed_fn();
    work->side = 0;
    work->mode_fn(work);
    s19b_jeep_liq_800D6FB8(work);
}

void s19b_jeep_liq_800D76F8(Jeep2Work *work, Jeep2Func arg1)
{
    if (work->speed_fn != arg1)
    {
        work->speed_fn = arg1;
        work->speed_fn_time = 0;
        work->speed_timer = 0;
    }
}

int s19b_jeep_liq_800D771C(int cur, int center, int pos)
{
    int d    = pos - center;
    int base = s19b_jeep_mrl_800D399C();

    if (d >= 0)
    {
        if (d > 0xBB8)
        {
            cur = GV_NearSpeed(cur, base + 0x64, 0xF);
        }
        else if (d > 0x2EE)
        {
            cur = GV_NearSpeed(cur, base + 0x32, 8);
        }
        else if (d > 0x5D)
        {
            cur = GV_NearSpeed(cur, base + 0xF, 3);
        }
    }
    else
    {
        if (d < -0xBB8)
        {
            cur = GV_NearSpeed(cur, base - 0x64, 0xF);
        }
        else if (d < -0x2EE)
        {
            cur = GV_NearSpeed(cur, base - 0x32, 8);
        }
        else if (d < -0x5D)
        {
            cur = GV_NearSpeed(cur, base - 0xF, 3);
        }
    }
    return cur;
}
void s19b_jeep_liq_800D77F0(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0x753, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7860(Jeep2Work *work)
{
    int s1 = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    int a1 = s19b_jeep_mrl_800D399C();

    if (work->speed_timer == 0)
    {
        if (work->flags & 8)
        {
            int v1 = work->speed - 0x32;
            int v0;
            work->speed = v1;
            v0 = v1 - v1 / 16;
            work->speed = v0;
            work->speed_target = v0;
            work->speed_timer = 0x3c;
            Takabe_JeepSystem.flags_54 |= 2;
        }
        else if (s1 >= 0x5dd)
        {
            work->speed_target = GV_NearSpeed(work->speed_target, a1 + 0x32, 7);
            Takabe_JeepSystem.flags_54 |= 0x1000;
        }
    }
    else
    {
        work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0xbb8, s1);
        work->speed_timer--;
    }
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D797C(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D79EC(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, -0x177, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7A5C(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0xbb8, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}
void s19b_jeep_liq_800D7ACC(Jeep2Work *work)
{
    int v = work->pos.vz - (Takabe_JeepSystem.world_pos.vz - Takabe_JeepSystem.offset.vz);
    s19b_jeep_mrl_800D399C();
    work->speed_target = s19b_jeep_liq_800D771C(work->speed_target, 0x1194, v);
    work->speed = GV_NearSpeed(work->speed, work->speed_target, 5);
}

void s19b_jeep_liq_800D7B3C(Jeep2Work *work, Jeep2Func arg1)
{
    if (work->side_fn != arg1)
    {
        work->side_fn = arg1;
        work->side_step = 0;
        work->side_count = 0;
    }
}

int s19b_jeep_liq_800D7B60(int center, int range)
{
    return (rand() * range >> 15) - range / 2 + center;
}
void s19b_jeep_liq_800D7BB0(Jeep2Work *work)
{
    if (++work->side_count == 0x1e)
    {
        work->side_target = s19b_jeep_liq_800D7B60(0, 0x4b0);
        work->side_count = 0;
    }
    work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
}
void s19b_jeep_liq_800D7C0C(Jeep2Work *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        work->side_target = 0x546;
        work->side = GV_NearSpeed(work->side, 0x546, 0x32);
        if (work->side_count == 0x28)
        {
            work->side_step = 1;
            work->side_count = 0x13;
        }
        break;
    case 1:
        if (n == 0x14)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x4e2, 0xfa);
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7CBC(Jeep2Work *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        work->side_target = 0x5dc;
        if (work->side_count == 0x28)
        {
            work->side_step = 1;
            work->side_count = 0x13;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x32);
        break;
    case 1:
        if (n == 0x14)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x5dc, 0xfa);
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x1e);
        break;
    }
}
void s19b_jeep_liq_800D7D68(Jeep2Work *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0x190);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x32);
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = -0x226;
        }
        else if (n == 0x3c)
        {
            work->side_step = 0;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x64);
        break;
    }
}
void s19b_jeep_liq_800D7E2C(Jeep2Work *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(-0x2ee, 0x96);
        }
        else if (n == 0x3c)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        {
            int r = GV_NearSpeed(work->side, work->side_target, 0x4b);
            work->side = r;
            if (r == work->side_target)
            {
                Takabe_JeepSystem.flags_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(-0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D7F20(Jeep2Work *work)
{
    int n = work->side_count + 1;
    work->side_count = n;

    switch (work->side_step)
    {
    case 0:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0x96);
            work->side_count = 0;
        }
        else if (n == 0x3c)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        {
            int r = GV_NearSpeed(work->side, work->side_target, 0x4b);
            work->side = r;
            if (r == work->side_target)
            {
                Takabe_JeepSystem.flags_54 |= 0x2000;
            }
        }
        break;
    case 1:
        if (n == 1)
        {
            work->side_target = s19b_jeep_liq_800D7B60(0x2ee, 0xfa);
        }
        else if (n == 0x1e)
        {
            work->side_step = 1;
            work->side_count = 0;
        }
        work->side = GV_NearSpeed(work->side, work->side_target, 0x19);
        break;
    }
}
void s19b_jeep_liq_800D8014(Jeep2Work *work, Jeep2Func arg1)
{
    if (work->mode_fn != arg1)
    {
        work->mode_fn = arg1;
        work->side_step = 0;
        work->side_count = 0;
        work->flags &= ~2;
    }
}
extern unsigned char s19b_dword_800C3A9C[];
extern int s19b_jeep_mrl_800D39B4(SVECTOR *dst);

void s19b_jeep_liq_800D8044(Jeep2Work *work)
{
    SVECTOR sp10;

    s19b_jeep_mrl_800D39B4(&sp10);
    if (Takabe_JeepSystem.has_homing_target != 0 && work->shoot_count >= 0x15)
    {
        work->shoot_count = 0;
        if (work->side > 0)
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7E2C);
        }
        else
        {
            s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
        }
        Takabe_JeepSystem.flags_54 |= 0x1000;
        GM_SeSet(&work->control.mov, s19b_dword_800C3A9C[GV_RandU(4)]);
    }
    else
    {
        work->shoot_count++;
    }
}
void s19b_jeep_liq_800D8118(Jeep2Work *work)
{
    SVECTOR dst;
    int     d;

    s19b_jeep_mrl_800D39B4(&dst);
    d = work->control.mov.vz - dst.vz;
    if (d < 0)
    {
        work->mode = 5;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7D68);
    }
    else
    {
        work->mode = 2;
        s19b_jeep_liq_800D76F8(work, s19b_jeep_liq_800D79EC);
        s19b_jeep_liq_800D7B3C(work, s19b_jeep_liq_800D7F20);
    }
}

void s19b_jeep_liq_800D81A8(Jeep2Work *work)
{
    int n = work->shoot_count;
    work->shoot_count = n + 1;
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
        work->act_fn = s19b_jeep_liq_800D7114;
    }
}
extern void s19b_spark2_m_800D964C(LiqWork *work);
extern void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec);

void s19b_jeep_liq_800D8250(LiqWork *work)
{
    SVECTOR  mov     = {350, 975, -350};
    OBJECT  *obj     = &work->obj;
    CONTROL *control = &work->control;
    DG_OBJS *objs;

    GM_ActMotion(obj);
    control->turn = DG_ZeroVector;
    control->rot  = control->turn;
    control->mov  = mov;
    GM_ActControl(control);
    GM_ActObject(obj);
    objs = work->obj.objs;
    CompMatrix(&work->jeep_objs->world, &objs->world, &objs->world);
    DG_GetLightMatrix(&control->mov, work->light);
    control->mov.vx = objs->world.t[0];
    control->mov.vy = objs->world.t[1];
    control->mov.vz = objs->world.t[2];
    Takabe_JeepLiqPos.vx = work->obj.objs->objs[6].world.t[0];
    Takabe_JeepLiqPos.vy = work->obj.objs->objs[6].world.t[1];
    Takabe_JeepLiqPos.vz = work->obj.objs->objs[6].world.t[2];
    GM_MoveTarget(work->target, &control->mov);
    s19b_spark2_m_800D964C(work);
    sna_act_helper2_helper2_80033054(0x7BF2, &work->sv_7B8);
    work->adjust[6].vx = work->sv_7B8.vx;
    if ((work->f940 & 3) == 1)
    {
        work->obj.objs->flag |= DG_FLAG_INVISIBLE;
    }
    else
    {
        work->obj.objs->flag &= ~DG_FLAG_INVISIBLE;
    }
}
#define LIQ_BODY_FLAG   (DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND)
#define LIQ_WEAPON_FLAG (LIQ_BODY_FLAG | DG_FLAG_ONEPIECE)

int s19b_jeep_liq_800D8420(LiqWork *work, int name)
{
    CONTROL *control = &work->control;
    OBJECT  *obj;
    OBJECT  *obj2;
    int      model;

    if (GM_InitControl(control, name, GM_CurrentMap) < 0)
    {
        return -1;
    }
    control->mov = work->jeep_control->mov;
    control->rot = work->jeep_control->rot;
    GM_ConfigControlAttribute(control, 5);
    GM_ConfigControlInterp(control, 4);

    obj  = &work->obj;
    obj2 = &work->obj2;
    model = GV_StrCode("liquid");
    GM_InitObject(obj, model, LIQ_BODY_FLAG, GV_StrCode("lqd_19b"));
    GM_ConfigObjectJoint(obj);
    GM_ConfigMotionControl(obj, &work->m_ctrl, GV_StrCode("lqd_19b"), work->m_segs1, work->m_segs2, control, work->rots);
    GM_ConfigObjectLight(obj, work->light);
    GM_ConfigObjectAction(obj, 0, 0, 0);
    GM_ConfigMotionAdjust(obj, work->adjust);

    GM_InitObject(obj2, GV_StrCode("famas"), LIQ_WEAPON_FLAG, 0);
    GM_ConfigObjectLight(obj2, work->light);
    GM_ConfigObjectRoot(obj2, obj, 4);

    work->target = GM_AllocTarget();
    work->homing = GM_SetHomingTarget(&work->obj.objs->objs[5].world, control);
    if (work->homing != NULL)
    {
        work->homing->flag = 1;
    }
    Takabe_JeepSystem.liq_obj = obj;
    control->r_sphere = -2;
    work->f90C = 0;
    work->f910 = 0;
    work->f914 = 0;
    return 0;
}

void s19b_spark2_m_800D8620(LiqWork *work)
{
    GM_FreeTarget(work->target);
    GM_ResetHomingTarget(work->homing);
    GM_FreeObject(&work->obj2);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->obj);
}

void *s19b_spark2_m_800D8670(CONTROL *arg0, DG_OBJS *arg1, int *arg2)
{
    LiqWork *work = GV_NewActor(GV_ACTOR_USER, sizeof(LiqWork));

    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_liq_800D8250, s19b_spark2_m_800D8620,
                         "jeep_liq.c");
        work->jeep_control = arg0;
        work->jeep_objs = arg1;
        work->jeep_flags = arg2;
        if (s19b_jeep_liq_800D8420(work, GV_StrCode("liqiud")) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return work;
}
