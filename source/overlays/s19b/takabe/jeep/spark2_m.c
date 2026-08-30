#include "../jeep_liq/jeep_liq.h"

#include <rand.h>
#include "game/game.h"
#include "linkvar.h"

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
extern int   s19b_dword_800C3AD4;
extern void  s19b_jeep_gls_800CEC24(int arg0, SVECTOR *out);
extern void *NewSpark2M(MATRIX *world);

void s19b_spark2_m_800D8724(Work *work, int arg1, int arg2)
{
    MATRIX  m;
    DG_OBJ *obj = &work->obj.objs->objs[arg1];

    DG_SetPos(&obj->world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AA0);
    DG_RotatePos((SVECTOR *)&s19b_dword_800C3AA8);
    ReadRotMatrix(&m);
    NewJeepBlood(&m, arg2, &obj->world);
}

extern void s19b_spark2_m_800D9390(Work *work, int mode);
extern void s19b_spark2_m_800D9434(Work *work, int mode);
extern void s19b_spark2_m_800D94C8(Work *work, int mode);

int s19b_spark2_m_800D87A4(Work *work)
{
    TARGET *target = work->f8E4;
    int     level;
    int     vital;

    if (target->damaged & 4)
    {
        target->force = DG_ZeroVector;
        GM_SeSet((SVECTOR *)&work->ctrl, 0x81);

        /* both arms spell out the same tail: cross-jumping merges it back */
        if (!(Takabe_JeepSystem.field_54 & 0x20000))
        {
            work->f8EC = (void *)s19b_spark2_m_800D9390;
            work->f8F4 = 0;
            work->ctrl.turn.vz = 0;
            work->ctrl.turn.vx = 0;
        }
        else
        {
            work->f8EC = (void *)s19b_spark2_m_800D9434;
            work->f8F4 = 0;
            work->ctrl.turn.vz = 0;
            work->ctrl.turn.vx = 0;
        }

        target->damage  = 0;
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

    if (work->f900 & 0x2000000)
    {
        work->f8EC = (void *)s19b_spark2_m_800D94C8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }

    return 0;
}
extern int s19b_spark2_m_800D87A4(Work *work);

int s19b_spark2_m_800D88D8(Work *work)
{
    if (s19b_spark2_m_800D87A4(work) != 0)
    {
        work->f8E4->class = 1;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8918(Work *work)
{
    TARGET *target = work->f8E4;
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

int s19b_spark2_m_800D899C(Work *work)
{
    int v = work->f900;

    if (v & 0x1)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8BC8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x2)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8CEC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x4)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8E10;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x10)
    {
        work->f8EC = (void *)s19b_spark2_m_800D90A8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    if (v & 0x04000000)
    {
        work->f8EC = (void *)s19b_spark2_m_800D92C8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D8A48(Work *work)
{
    GV_NearExp4PV(&work->svecs2[2], &work->sv_7A0, 3);
    GV_NearExp4PV(&work->svecs2[6], &work->sv_7A8, 3);
}

void s19b_spark2_m_800D8A88(Work *work)
{
    int v = work->f930 - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AAC(Work *work)
{
    int base = work->f930 + 0xCC0;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8ACC(Work *work)
{
    int base = work->f930 + 0x340;
    int v    = base - work->control->rot.vy;
    work->sv_7A0.vy = v;
    work->sv_7A8.vy = v;
}

void s19b_spark2_m_800D8AEC(Work *work)
{
    MATRIX m;

    DG_SetPos(&work->obj.objs->objs[4].world);
    DG_MovePos((SVECTOR *)&s19b_dword_800C3AC0);
    ReadRotMatrix(&m);
    NewJeepBullet(&m, 2, 1, 0);
    GM_SeSet(&work->ctrl.mov, 0x2E);
    s19b_jblood_800C7FB8(&m);
}

void s19b_spark2_m_800D8B54(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 0;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0, 0, 4);
    }
    if (s19b_spark2_m_800D88D8(work) == 0)
    {
        if (s19b_spark2_m_800D899C(work) == 0)
        {
            work->f8E4->class |= 0x14;
        }
    }
}

extern void s19b_spark2_m_800D8F34(Work *work, int mode);

void s19b_spark2_m_800D8BC8(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 1;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 1, 0, 4);
    }
    s19b_spark2_m_800D8A88(work);

    if (!(f900 & 1))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8F34;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D8FB0(Work *work, int mode);

void s19b_spark2_m_800D8CEC(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 3;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 3, 0, 4);
    }
    s19b_spark2_m_800D8AAC(work);

    if (!(f900 & 2))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8FB0;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D902C(Work *work, int mode);

void s19b_spark2_m_800D8E10(Work *work, int mode)
{
    int f900 = work->f900;

    if (mode == 0)
    {
        work->f8FC = 2;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 2, 0, 4);
    }
    s19b_spark2_m_800D8ACC(work);

    if (!(f900 & 4))
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->sv_7A0 = DG_ZeroVector;
        work->sv_7A8 = DG_ZeroVector;
        return;
    }

    if (f900 & 8)
    {
        work->f8EC = (void *)s19b_spark2_m_800D902C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (s19b_spark2_m_800D899C(work) != 0) return;
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8F34(Work *work, int mode)
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
        work->f8EC = (void *)s19b_spark2_m_800D8BC8;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D8FB0(Work *work, int mode)
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
        work->f8EC = (void *)s19b_spark2_m_800D8CEC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

void s19b_spark2_m_800D902C(Work *work, int mode)
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
        work->f8EC = (void *)s19b_spark2_m_800D8E10;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
    work->f8E4->class |= 0x14;
}

extern void s19b_spark2_m_800D9148(Work *work, int mode);
extern void s19b_spark2_m_800D91DC(Work *work, int mode);

void s19b_spark2_m_800D90A8(Work *work, int mode)
{
    if (mode < 8)
    {
        work->f8E4->class |= 0x14;
    }
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->f8FC = 0x10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D9148;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9148(Work *work, int mode)
{
    int f900 = work->f900;

    if (!(f900 & 0x10))
    {
        work->f8EC = (void *)s19b_spark2_m_800D91DC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }
    if (s19b_spark2_m_800D88D8(work) != 0) return;
    if (mode == 0)
    {
        work->f8FC = 0x11;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x11, 0, 4);
    }
    if (mode >= 0x5B)
    {
        work->f8EC = (void *)s19b_spark2_m_800D91DC;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D91DC(Work *work, int mode)
{
    if (mode < 8 && (work->f900 & 0x10))
    {
        work->f8EC = (void *)s19b_spark2_m_800D9148;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        return;
    }

    if (mode >= 8)
    {
        work->f8E4->class |= 0x14;
    }

    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }

    if (work->f93C != 0 && mode >= 0xB)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->f93C = 0;
    }

    if (mode == 0)
    {
        work->f8FC = 0x12;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x12, 0, 4);
    }

    if (work->obj.is_end == 0)
    {
        return;
    }

    work->f8EC = (void *)s19b_spark2_m_800D8B54;
    work->f8F4 = 0;
    work->ctrl.turn.vz = 0;
    work->ctrl.turn.vx = 0;
}

void s19b_spark2_m_800D932C(Work *work, int mode);

void s19b_spark2_m_800D92C8(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D932C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D932C(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 10;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 10, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D932C;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9390(Work *work, int mode)
{
    if (mode == 0)
    {
        work->f8FC = 20;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 20, 0, 4);
        GM_SeSet(&work->ctrl.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
        work->f940 = 45;
        work->f93C = 0;
    }
}

void s19b_spark2_m_800D9434(Work *work, int mode)
{
    if (s19b_spark2_m_800D899C(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        GM_SeSet(&work->ctrl.mov, 0x81);
        s19b_spark2_m_800D8724(work, 5, 1);
        *work->f944 |= 1;
    }
    if (mode < 0x11)
    {
        return;
    }
    work->f8EC = (void *)s19b_spark2_m_800D8B54;
    work->f8F4 = 0;
    work->ctrl.turn.vz = 0;
    work->ctrl.turn.vx = 0;
}

void s19b_spark2_m_800D94C8(Work *work, int mode)
{
    work->f8E4->class |= 0x14;
    if (s19b_spark2_m_800D88D8(work) != 0)
    {
        return;
    }
    if (mode == 0)
    {
        work->f8FC = 0x13;
        GM_ConfigObjectAction((OBJECT *)&work->obj, 0x13, 0, 4);
    }
    if (work->obj.is_end != 0)
    {
        work->f8EC = (void *)s19b_spark2_m_800D8B54;
        work->f8F4 = 0;
        work->ctrl.turn.vz = 0;
        work->ctrl.turn.vx = 0;
    }
}

void s19b_spark2_m_800D9558(Work *work)
{
    int   old;
    void *handler;

    work->f8E4->class = 1;
    old     = work->f8F4;
    handler = work->f8EC;
    work->f8F4 = old + 1;

    if (handler == NULL)
    {
        s19b_spark2_m_800D8918(work);
        handler       = (void *)s19b_spark2_m_800D8B54;
        work->f8EC    = handler;
    }
    ((void (*)(Work *, int))handler)(work, old);

    s19b_spark2_m_800D8A48(work);

    if (work->f940 != 0)
    {
        work->f8E4->class = 1;
        work->f940 -= 1;
    }
}

void s19b_spark2_m_800D95FC(Work *work)
{
    SVECTOR diff;

    GV_SubVec3(&GM_PlayerPosition, &work->ctrl.mov, &diff);
    diff.vy = 0;
    work->f930 = GV_VecDir2(&diff);
    work->f934 = GV_VecLen3(&diff);
}

extern void s19b_spark2_m_800D9C04(Work *work);

void s19b_spark2_m_800D964C(Work *work)
{
    s19b_spark2_m_800D95FC(work);
    s19b_spark2_m_800D9C04(work);
    s19b_spark2_m_800D9558(work);
}

int s19b_spark2_m_800D9680(Work *work)
{
    int js = Takabe_JeepSystem.field_54;

    if (js & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
        return 1;
    }
    if (js & 0x2)
    {
        work->f900 |= 0x02000000;
    }
    else if (js & 0x8000)
    {
        work->f900 = 0x04000000;
        return 1;
    }
    else if (work->f8FC == 0x14)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
        return 1;
    }
    return 0;
}

void s19b_spark2_m_800D9704(Work *work)
{
    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f934 < 0xFA0 || work->f93C != 0)
    {
        int f930 = work->f930;
        int new_f914;

        if ((unsigned)(f930 - 0x601) < 0x3FF)
        {
            new_f914 = 1;
        }
        else if ((unsigned)(f930 - 0x201) < 0x3FF)
        {
            new_f914 = 3;
        }
        else if ((unsigned)(f930 - 0xA01) < 0x3FF)
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

void s19b_spark2_m_800D97A8(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 1)
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
        work->f900 |= 8;
    }
    work->f900 |= 1;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D985C(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 3)
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
        work->f900 |= 8;
    }
    work->f900 |= 2;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D9910(Work *work)
{
    int v;

    if (s19b_spark2_m_800D9680(work) != 0)
    {
        return;
    }

    if (work->f8FC != 2)
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
        work->f900 |= 8;
    }
    work->f900 |= 4;
    work->f904 = work->f930;
    work->f918 += 1;
}

void s19b_spark2_m_800D99C4(Work *work)
{
    int js = Takabe_JeepSystem.field_54;
    work->f900 |= 0x10;
    if (work->f918 >= 61 || (js & 0x2000))
    {
        work->f93C = 1;
        work->f914 = 0;
    }
    if (js & 0x2)
    {
        work->f914 = 1;
        work->f900 |= 0x02000000;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9A30(Work *work)
{
    if (Takabe_JeepSystem.field_54 & 0x1000)
    {
        work->f914 = 4;
        work->f918 = 0;
        work->f900 |= 0x10;
    }
    else
    {
        work->f918 += 1;
    }
}

void s19b_spark2_m_800D9A74(Work *work)
{
    int new_f900 = work->f900 | 0x10;
    int js = Takabe_JeepSystem.field_54;
    work->f900 = new_f900;
    if (js & 0x2000)
    {
        work->f914 = 0;
    }
    work->f918 += 1;
}

void s19b_spark2_m_800D9AA8(Work *work)
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
extern void s19b_spark2_m_800D9AA8(Work *work);

void s19b_spark2_m_800D9B38(Work *work)
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

void s19b_spark2_m_800D9B88(Work *work)
{
    switch (work->f910)
    {
    case 0: s19b_spark2_m_800D9AA8(work); break;
    case 1: s19b_spark2_m_800D9B38(work); break;
    }

    if (Takabe_JeepSystem.field_54 & 0x10000000)
    {
        work->f910 = 1;
    }
    else
    {
        work->f910 = 0;
    }
}

void s19b_spark2_m_800D9C04(Work *work)
{
    short *table = (short *)&s19b_dword_800C3AC8;
    int    idx;

    work->f904 = -1;
    work->f900 = 0;
    idx = GM_GameLevel + 1;
    s19b_dword_800DE650 = table[idx];

    if (work->f90C == 0)
    {
        s19b_spark2_m_800D9B88(work);
    }

    Takabe_JeepSystem.field_54 &= 0xFFFF0000;
    work->f920 += 1;
}

int s19b_spark2_m_800D9C90(CONTROL *ctl, int *count, int unused_arg, SVECTOR *out)
{
    SVECTOR near;
    int     unused[2];
    SVECTOR hit;
    SVECTOR pos;
    MATRIX  m;
    int     len;

    pos = ctl->mov;
    pos.vy += 250;
    if (HZD_NearHazardCheck(ctl->map->hzd, &pos, 0x1DB, 0xC, 0) > 0)
    {
        HZD_GetNearVector(&near);
        hit = near;
        len = GV_VecLen3(&near);
        GV_AddVec3(&near, &pos, &hit);
        if (len < 0x1E5)
        {
            m = DG_ZeroMatrix;
            m.t[0] = hit.vx;
            m.t[1] = hit.vy;
            m.t[2] = hit.vz;
            NewSpark2M(&m);
            s19b_dword_800C3AD4 += GV_PassageTime;
            if (s19b_dword_800C3AD4 >= 7)
            {
                s19b_dword_800C3AD4 -= 6;
                GM_SeSetMode(&hit, 0xC3, 1);
            }
        }
        if (len < 0x1DB)
        {
            GV_LenVec3(&near, &near, len, -0x1DB);
            GV_AddVec3(&near, &hit, &hit);
            GV_SubVec3(&pos, &hit, out);
            ctl->mov = hit;
            *count -= out->vx;
            *count -= out->vx;
            *count -= out->vx;
            return 1;
        }
    }
    return 0;
}
const SVECTOR s19b_dword_800DDEA8 = {0, 0, 0x232, 0};

int s19b_spark2_m_800D9EC0(SVECTOR *pos, SVECTOR *rot, SVECTOR *cur, SVECTOR *prev)
{
    int     vz = pos->vz;
    SVECTOR ahead;
    SVECTOR step;
    SVECTOR dir;
    SVECTOR yaw;
    SVECTOR far;
    int     d;
    int     abs;

    dir = s19b_dword_800DDEA8;
    yaw = DG_ZeroVector;
    yaw.vy = rot->vy;
    DG_SetPos2(&DG_ZeroVector, &yaw);
    DG_RotVector(&dir, &dir, 1);
    s19b_jeep_gls_800CEC24(vz, &ahead);
    s19b_jeep_gls_800CEC24(vz + dir.vz, &step);
    pos->vy = ahead.vy;
    GV_SubVec3(&ahead, &step, &ahead);
    s19b_jeep_gls_800CEC24(vz + 0x400, &far);
    rot->vx = -ratan2(far.vy - pos->vy, 0x400);

    d = (-cur->vx * prev->vz + cur->vz * prev->vx) >> 9;
    *prev = *cur;
    rot->vz -= d;
    abs = rot->vz;
    if (abs < 0)
    {
        abs = -abs;
    }
    rot->vz = GV_NearSpeed(rot->vz, 0, (200 - abs) / 32 + 1);
    if (rot->vz < -140)
    {
        rot->vz = -140;
    }
    if (rot->vz > 140)
    {
        rot->vz = 140;
    }
    return pos->vy;
}
void s19b_spark2_m_800DA0B4(POLY_FT4 *poly, int arg1, SVECTOR *from, SVECTOR *to)
{
    int d = (arg1 << 12) / 1178;
    int dy;
    int step;

    poly->x0 += d;
    poly->x1 += d;
    poly->x2 += d;
    poly->x3 += d;

    dy = from->vy - to->vy;
    if (arg1 < 0)
    {
        dy = -dy;
    }
    step = dy * 4;
    poly->y2 = GV_NearExp4P(poly->y2, step);
    poly->y3 = GV_NearExp4P(poly->y3, step);
    *to = *from;
}

typedef struct _SparkWork
{
    GV_ACT   actor;
    int      map;
    DG_PRIM *prim;
    MATRIX   world;
    SVECTOR  speeds[16];
    SVECTOR  verts[32];
    char     unused[0x28];
    int      time;
} SparkWork;

static void InitVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    MATRIX  mat;
    SVECTOR rot;
    SVECTOR pos;
    int     x, y, z;

    pos = DG_ZeroVector;

    rot.vz = 0;

    while (--count >= 0)
    {
        rot.vx = GV_RandS(256);
        rot.vy = GV_RandS(256);

        RotMatrixYXZ_gte(&rot, &mat);
        DG_SetPos(&mat);

        pos.vz = GV_RandU(256) + 64;
        DG_RotVector(&pos, speeds, 1);

        x = speeds->vx / 2;
        y = speeds->vy / 2;
        z = speeds->vz / 2;

        verts[0].vx = x;
        verts[0].vy = y;
        verts[0].vz = z;

        verts[1].vx = x / 4;
        verts[1].vy = y / 4;
        verts[1].vz = z / 4;

        verts += 2;
        speeds++;
    }
}

static void UpdateVerts(SVECTOR *speeds, SVECTOR *verts, int count)
{
    int x, y, z;

    while (--count >= 0)
    {
        x = speeds->vx;
        y = speeds->vy;
        z = speeds->vz;

        verts[1] = verts[0];

        verts->vx += x;
        verts->vy += y - 16;
        verts->vz += z;

        speeds->vx = x - x / 4;
        speeds->vy = y - y / 4;
        speeds->vz = z - z / 4;

        verts += 2;
        speeds++;
    }
}

static void InitPacks(LINE_F2 *packs, int n_packs, int bright)
{
    while (--n_packs >= 0)
    {
        setLineF2(packs);
        packs++;
    }
}

static void ShadePacks(LINE_F2 *packs, int n_packs, int bright)
{
    int color;

    color = bright | (bright / 2) << 8 | (bright / 2) << 16;
    while (--n_packs >= 0)
    {
        LSTORE((LLOAD(&packs->r0) & 0xFF000000) | color, &packs->r0);
        packs++;
    }
}

static void Act(SparkWork *work)
{
    int      time;
    DG_PRIM *prim;
    int      shade;

    GM_CurrentMap = work->map;

    time = --work->time;
    if (time <= 0)
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    UpdateVerts(work->speeds, work->verts, 16);

    prim = work->prim;

    shade = (time * 16) + 50;
    if (shade > 255)
    {
        shade = 255;
    }

    ShadePacks(prim->packs[GV_Clock], 16, shade);

    work->world.t[0] += Takabe_JeepSystem.pos.vx;
    work->world.t[1] += Takabe_JeepSystem.pos.vy;
    work->world.t[2] += Takabe_JeepSystem.pos.vz;

    DG_SetPos(&work->world);
    DG_PutPrim(work->prim);
}

static void Die(SparkWork *work)
{
    GM_FreePrim(work->prim);
}

static int GetResources(SparkWork *work, MATRIX *world)
{
    DG_PRIM *prim;

    work->map = GM_CurrentMap;

    InitVerts(work->speeds, work->verts, 16);

    prim = GM_MakePrim(DG_PRIM_LINE_F2, 16, work->verts, NULL);
    work->prim = prim;
    if (prim != NULL)
    {
        DG_SetPos(world);
        DG_PutPrim(prim);
        work->world = *world;

        InitPacks(prim->packs[0], 16, 0);
        InitPacks(prim->packs[1], 16, 0);
        ShadePacks(prim->packs[GV_Clock], 16, 255);

        work->time = 16;
        return 0;
    }

    return -1;
}

void *NewSpark2M(MATRIX *world)
{
    SparkWork *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(SparkWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "spark2_m.c");

        SetSpadStack(SPAD_STACK_ADDR);

        if (GetResources(work, world) < 0)
        {
            ResetSpadStack();

            GV_DestroyActor(&work->actor);
            return NULL;
        }

        ResetSpadStack();
    }
    return (void *)work;
}

void s19b_fadeio_800DA784(void)
{
    GV_ZeroMemory(&Takabe_JeepSystem, 0x16C);
}
