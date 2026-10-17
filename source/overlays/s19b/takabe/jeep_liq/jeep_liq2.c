#include "psxdefs.h"
#include "mgstype.h"
#include "game/game.h"
#include "jeep_liq.h"

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
extern void  s19b_jeep_gls_800CEC24(int z, SVECTOR *out);

void s19b_spark2_m_800D8724(LiqWork *work, int arg1, int arg2)
{
    MATRIX  m;
    DG_OBJ *obj = &work->obj.objs->objs[arg1];

    DG_SetPos(&obj->world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AA0);
    DG_RotatePos((SVECTOR *)&s19b_dword_800C3AA8);
    ReadRotMatrix(&m);
    NewJeepBlood(&m, arg2, &obj->world);
}

extern void s19b_spark2_m_800D9148(LiqWork *work, int mode);
extern void s19b_spark2_m_800D91DC(LiqWork *work, int mode);
extern void s19b_spark2_m_800D9390(LiqWork *work, int mode);
extern void s19b_spark2_m_800D9434(LiqWork *work, int mode);
extern void s19b_spark2_m_800D94C8(LiqWork *work, int mode);

int s19b_spark2_m_800D87A4(LiqWork *work)
{
    TARGET *target = work->target;
    int     level;
    int     vital;

    if (target->damaged & 4)
    {
        target->force = DG_ZeroVector;
        GM_SeSet(&work->control.mov, SE_V_ENE_FOUND02);

        /* both arms spell out the same tail: cross-jumping merges it back */
        if (!(Takabe_JeepSystem.flags_54 & 0x20000))
        {
            work->state = s19b_spark2_m_800D9390;
            work->state_time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else
        {
            work->state = s19b_spark2_m_800D9434;
            work->state_time = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }

        target->damage = 0;
        target->damaged = 0;

        if (target->vital <= 0)
        {
            Takabe_JeepSystem.field_44++;
            vital = target->vital + 0xBF;
            level = GM_GameLevel;
            if (level > 0)
            {
                vital += level << 6;
            }
            target->vital = vital;
        }
        return 1;
    }

    if (work->cmd & 0x2000000)
    {
        work->state = s19b_spark2_m_800D94C8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }

    return 0;
}

int s19b_spark2_m_800D88D8(LiqWork *work)
{
    if (s19b_spark2_m_800D87A4(work) != 0)
    {
        work->target->class = 1;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8918(LiqWork *work)
{
    TARGET *target = work->target;
    int     level  = GM_GameLevel;
    int     vital;

    if (level > 0)
    {
        vital = (level << 6) + 0xBF;
    }
    else
    {
        vital = 0xBF;
    }

    GM_SetTarget(target, 20, 2, (SVECTOR *)&s19b_dword_800C3AB0);
    GM_SetPowerTarget(target, 1, -1, vital, 7, (SVECTOR *)&s19b_dword_800C3AB8);
}

extern void s19b_spark2_m_800D8BC8();
extern void s19b_spark2_m_800D8CEC();
extern void s19b_spark2_m_800D8E10();
extern void s19b_spark2_m_800D90A8();
extern void s19b_spark2_m_800D92C8();

int s19b_spark2_m_800D899C(LiqWork *work)
{
    int v = work->cmd;

    if (v & 0x1)
    {
        work->state = s19b_spark2_m_800D8BC8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x2)
    {
        work->state = s19b_spark2_m_800D8CEC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x4)
    {
        work->state = s19b_spark2_m_800D8E10;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x10)
    {
        work->state = s19b_spark2_m_800D90A8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (v & 0x04000000)
    {
        work->state = s19b_spark2_m_800D92C8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8A48(LiqWork *work)
{
    GV_NearExp4PV(&work->adjust[2], &work->sv_7A0, 3);
    GV_NearExp4PV(&work->adjust[6], &work->sv_7A8, 3);
}

void s19b_spark2_m_800D8A88(LiqWork *work)
{
    int v = work->player_dir - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AAC(LiqWork *work)
{
    int base = work->player_dir + 0xCC0;
    int v    = base - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8ACC(LiqWork *work)
{
    int base = work->player_dir + 0x340;
    int v    = base - work->jeep_control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AEC(LiqWork *work)
{
    MATRIX m;

    DG_SetPos(&work->obj.objs->objs[4].world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AC0);
    ReadRotMatrix(&m);
    NewJeepBullet(&m, 2, 1, 0);
    GM_SeSet(&work->control.mov, SE_GUNCAM_SHOT);
    s19b_jblood_800C7FB8(&m);
}

void s19b_spark2_m_800D8B54(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 0;
        GM_ConfigObjectAction(&work->obj, 0, 0, 4);
    }
    if (s19b_spark2_m_800D88D8(work) == 0)
    {
        if (s19b_spark2_m_800D899C(work) == 0)
        {
            work->target->class |= 0x14;
        }
    }
}

extern void s19b_spark2_m_800D8F34(LiqWork *work, int mode);

void s19b_spark2_m_800D8BC8(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 1;
        GM_ConfigObjectAction(&work->obj, 1, 0, 4);
    }
    s19b_spark2_m_800D8A88(work);

    if (!(cmd & 1))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D8F34;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

extern void s19b_spark2_m_800D8FB0(LiqWork *work, int mode);

void s19b_spark2_m_800D8CEC(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 3;
        GM_ConfigObjectAction(&work->obj, 3, 0, 4);
    }
    s19b_spark2_m_800D8AAC(work);

    if (!(cmd & 2))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D8FB0;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

extern void s19b_spark2_m_800D902C(LiqWork *work, int mode);

void s19b_spark2_m_800D8E10(LiqWork *work, int mode)
{
    int cmd = work->cmd;

    if (mode == 0)
    {
        work->action = 2;
        GM_ConfigObjectAction(&work->obj, 2, 0, 4);
    }
    s19b_spark2_m_800D8ACC(work);

    if (!(cmd & 4))
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (cmd & 8)
    {
        work->state = s19b_spark2_m_800D902C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D8F34(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->state = s19b_spark2_m_800D8BC8;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D8FB0(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->state = s19b_spark2_m_800D8CEC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}

void s19b_spark2_m_800D902C(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        s19b_spark2_m_800D8AEC(work);
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 1)
    {
        work->state = s19b_spark2_m_800D8E10;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->target->class |= 0x14;
}


void s19b_spark2_m_800D90A8(LiqWork *work, int mode)
{
    if (mode < 8)
    {
        work->target->class |= 0x14;
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->action = 0x10;
        GM_ConfigObjectAction(&work->obj, 0x10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D9148;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9148(LiqWork *work, int mode)
{
    if (!(work->cmd & 0x10))
    {
        work->state = s19b_spark2_m_800D91DC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->action = 0x11;
        GM_ConfigObjectAction(&work->obj, 0x11, 0, 4);
    }
    if (mode >= 0x5B)
    {
        work->state = s19b_spark2_m_800D91DC;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D91DC(LiqWork *work, int mode)
{
    if (mode < 8 && (work->cmd & 0x10))
    {
        work->state = s19b_spark2_m_800D9148;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (mode >= 8)
    {
        work->target->class |= 0x14;
    }

    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }

    if (work->f93C != 0 && mode >= 0xB)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->f93C = 0;
    }

    if (mode == 0)
    {
        work->action = 0x12;
        GM_ConfigObjectAction(&work->obj, 0x12, 0, 4);
    }

    if (work->obj.is_end == 0)
    {
        return;
    }

    work->state = s19b_spark2_m_800D8B54;
    work->state_time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_spark2_m_800D932C(LiqWork *work, int mode);

void s19b_spark2_m_800D92C8(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 10;
        GM_ConfigObjectAction(&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D932C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D932C(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 10;
        GM_ConfigObjectAction(&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D932C;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9390(LiqWork *work, int mode)
{
    if (mode == 0)
    {
        work->action = 20;
        GM_ConfigObjectAction(&work->obj, 20, 0, 4);
        GM_SeSet(&work->control.mov, SE_V_ENE_FOUND02);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->jeep_flags |= 1;
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->f940 = 45;
        work->f93C = 0;
    }
}

void s19b_spark2_m_800D9434(LiqWork *work, int mode)
{
    if (s19b_spark2_m_800D899C(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        GM_SeSet(&work->control.mov, SE_V_ENE_FOUND02);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->jeep_flags |= 1;
    }
    if (mode < 0x11)
    {
        return;
    }
    work->state = s19b_spark2_m_800D8B54;
    work->state_time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

void s19b_spark2_m_800D94C8(LiqWork *work, int mode)
{
    work->target->class |= 0x14;
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->action = 0x13;
        GM_ConfigObjectAction(&work->obj, 0x13, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->state = s19b_spark2_m_800D8B54;
        work->state_time = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9558(LiqWork *work)
{
    int   old;
    LiqFn handler;

    work->target->class = 1;
    old     = work->state_time;
    handler = work->state;
    work->state_time = old + 1;

    if (handler == NULL)
    {
        s19b_spark2_m_800D8918(work);
        handler       = s19b_spark2_m_800D8B54;
        work->state    = handler;
    }
    handler(work, old);

    s19b_spark2_m_800D8A48(work);

    if (work->f940 != 0)
    {
        work->target->class = 1;
        work->f940 -= 1;
    }
}

void s19b_spark2_m_800D95FC(LiqWork *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &diff);
    diff.vy = 0;
    work->player_dir = GV_VecDir2(&diff);
    work->player_dist = GV_VecLen3(&diff);
}

extern void s19b_spark2_m_800D9C04(LiqWork *work);

void s19b_spark2_m_800D964C(LiqWork *work)
{
    s19b_spark2_m_800D95FC(work);
    s19b_spark2_m_800D9C04(work);
    s19b_spark2_m_800D9558(work);
}

int s19b_spark2_m_800D9680(LiqWork *work)
{
    int js = Takabe_JeepSystem.flags_54;

    if (js & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->cmd |= 0x10;
        return 1;
    }
    else if (js & 2)
    {
        work->cmd |= 0x2000000;
    }
    else if (js & 0x8000)
    {
        work->cmd = 0x4000000;
        return 1;
    }
    else if (work->action == 0x14)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->cmd |= 0x10;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D9704(LiqWork *work)
{
    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->player_dist < 0xFA0 || work->f93C != 0)
    {
        int player_dir = work->player_dir;
        int new_f914;

        if ((unsigned)(player_dir - 0x601) < 0x3FF)
        {
            new_f914 = 1;
        }
        else if ((unsigned)(player_dir - 0x201) < 0x3FF)
        {
            new_f914 = 3;
        }
        else if ((unsigned)(player_dir - 0xA01) < 0x3FF)
        {
            new_f914 = 2;
        }
        else
        {
            work->f918 += 1;
            return;
        }

        work->f914 = new_f914;
        work->f918 = 0;
        return;
    }

    work->f918 += 1;
}

void s19b_spark2_m_800D97A8(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 1)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->cmd |= 8;
    }
    work->cmd |= 1;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D985C(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 3)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->cmd |= 8;
    }
    work->cmd |= 2;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D9910(LiqWork *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->action != 2)
    {
        work->f918 = 0;
    }

    if (work->f918 >= 0x4C)
    {
        work->f914 = 0;
        work->f918 = 0;
        return;
    }

    v = s19b_dword_800DE650;
    if (work->f918 == v + 6 || work->f918 == v + 9 || work->f918 == v + 0xC)
    {
        work->cmd |= 8;
    }
    work->cmd |= 4;
    work->cmd_dir = work->player_dir;
    work->f918 += 1;
}

void s19b_spark2_m_800D99C4(LiqWork *work)
{
    int js = Takabe_JeepSystem.flags_54;
    work->cmd |= 0x10;
    if (work->f918 >= 61 || (js & 0x2000))
    {
        work->f93C = 1;
        work->f914 = 0;
    }
    if (js & 0x2)
    {
        work->f914 = 1;
        work->cmd |= 0x02000000;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9A30(LiqWork *work)
{
    if (Takabe_JeepSystem.flags_54 & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->cmd |= 0x10;
    }
    else
    {
        work->f918 += 1;
    }
}

void s19b_spark2_m_800D9A74(LiqWork *work)
{
    int new_f900 = work->cmd | 0x10;
    int js = Takabe_JeepSystem.flags_54;
    work->cmd = new_f900;
    if (js & 0x2000)
    {
        work->f914 = 0;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9AA8(LiqWork *work)
{
    switch (work->f914)
    {
    case 0:
        s19b_spark2_m_800D9704(work);
        break;
    case 1:
        s19b_spark2_m_800D97A8(work);
        break;
    case 2:
        s19b_spark2_m_800D985C(work);
        break;
    case 3:
        s19b_spark2_m_800D9910(work);
        break;
    case 4:
        s19b_spark2_m_800D99C4(work);
        break;
    }
}

void s19b_spark2_m_800D9B38(LiqWork *work)
{
    switch (work->f914)
    {
    case 0:
        s19b_spark2_m_800D9A30(work);
        break;
    case 4:
        s19b_spark2_m_800D9A74(work);
        break;
    }
}

void s19b_spark2_m_800D9B88(LiqWork *work)
{
    switch (work->f910)
    {
    case 0: s19b_spark2_m_800D9AA8(work); break;
    case 1: s19b_spark2_m_800D9B38(work); break;
    }

    if (Takabe_JeepSystem.flags_54 & 0x10000000)
    {
        work->f910 = 1;
    }
    else
    {
        work->f910 = 0;
    }
}

void s19b_spark2_m_800D9C04(LiqWork *work)
{
    short *table = (short *)&s19b_dword_800C3AC8;
    int    idx;

    work->cmd_dir = -1;
    work->cmd = 0;
    idx = GM_GameLevel + 1;
    s19b_dword_800DE650 = table[idx];

    if (work->f90C == 0)
    {
        s19b_spark2_m_800D9B88(work);
    }

    Takabe_JeepSystem.flags_54 &= ~0xFFFF;
    work->f920 += 1;
}

extern int  s19b_dword_800C3AD4;
extern void *NewSpark2M(MATRIX *world);

int s19b_spark2_m_800D9C90(CONTROL *control, int *speed, int unused, SVECTOR *out)
{
    SVECTOR vec[2]; /* only [0] is used, [1] is dead stack space in the original */
    SVECTOR hit;
    SVECTOR check;
    MATRIX  mat;
    int     len;

    check = control->mov;
    check.vy += 250;
    if (HZD_NearHazardCheck(control->map->hzd, &check, 0x1DB, 0xC, 0) > 0)
    {
        HZD_GetNearVector(vec);
        hit = vec[0];
        len = GV_VecLen3(vec);
        GV_AddVec3(vec, &check, &hit);
        if (len < 0x1E5)
        {
            mat = DG_ZeroMatrix;
            mat.t[0] = hit.vx;
            mat.t[1] = hit.vy;
            mat.t[2] = hit.vz;
            NewSpark2M(&mat);
            s19b_dword_800C3AD4 += GV_PassageTime;
            if (s19b_dword_800C3AD4 >= 7)
            {
                s19b_dword_800C3AD4 -= 6;
                GM_SeSetMode(&hit, 0xC3, 1);
            }
        }
        if (len < 0x1DB)
        {
            GV_LenVec3(vec, vec, len, -0x1DB);
            GV_AddVec3(vec, &hit, &hit);
            GV_SubVec3(&check, &hit, out);
            control->mov = hit;
            *speed -= out->vx;
            *speed -= out->vx;
            *speed -= out->vx;
            return 1;
        }
    }
    return 0;
}
short s19b_spark2_m_800D9EC0(SVECTOR *pos, SVECTOR *rot, SVECTOR *step, SVECTOR *prev_step)
{
    int     z = pos->vz;
    SVECTOR p0;
    SVECTOR p1;
    SVECTOR offs = {0, 0, 562};
    SVECTOR dir  = DG_ZeroVector;
    SVECTOR p2;
    int     roll;
    int     dist;

    dir.vy = rot->vy;
    DG_SetPos2(&DG_ZeroVector, &dir);
    DG_RotVector(&offs, &offs, 1);
    s19b_jeep_gls_800CEC24(z, &p0);
    s19b_jeep_gls_800CEC24(z + offs.vz, &p1);
    pos->vy = p0.vy;
    GV_SubVec3(&p0, &p1, &p0);
    s19b_jeep_gls_800CEC24(z + 0x400, &p2);
    rot->vx = -ratan2(p2.vy - pos->vy, 0x400);
    roll = (-step->vx * prev_step->vz + step->vz * prev_step->vx) >> 9;
    *prev_step = *step;
    rot->vz = rot->vz - roll;
    dist = rot->vz;
    if (dist < 0)
    {
        dist = -dist;
    }
    rot->vz = GV_NearSpeed(rot->vz, 0, (200 - dist) / 32 + 1);
    if (rot->vz < -0x8C)
    {
        rot->vz = -0x8C;
    }
    if (rot->vz > 0x8C)
    {
        rot->vz = 0x8C;
    }
    return pos->vy;
}
void s19b_spark2_m_800DA0B4(SVECTOR *rots, int speed, SVECTOR *pos, SVECTOR *prev)
{
    int turn = (speed << 12) / 1178;
    int dy;
    int ang;

    rots[1].vx += turn;
    rots[2].vx += turn;
    rots[3].vx += turn;
    rots[4].vx += turn;
    dy = pos->vy - prev->vy;
    if (speed < 0)
    {
        dy = -dy;
    }
    ang = dy * 4;
    rots[3].vy = GV_NearExp4P(rots[3].vy, ang);
    rots[4].vy = GV_NearExp4P(rots[4].vy, ang);
    *prev = *pos;
}
