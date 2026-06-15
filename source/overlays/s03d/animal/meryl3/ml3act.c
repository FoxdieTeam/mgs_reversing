#include "meryl3.h"

extern short s03d_word_800C3970[8];
extern int s03d_dword_800C3980;
extern int s03d_dword_800C3988;
extern int s03d_dword_800C3990;

extern void NewBlood(MATRIX *, int);
extern void *NewAnime_8005DDE0(MATRIX *);
extern void NewAnime_8005D6BC(MATRIX *, int);
extern void NewAnime_8005D604(MATRIX *);
extern void *NewBulletEx(int, MATRIX *, int, int, int, int, int, int, int);

int  s03d_800CBA60(Meryl3Work *work);
void s03d_800CBB2C(Meryl3Work *work);
void s03d_800CBC10(Meryl3Work *work, int arg);
void s03d_800CBCDC(Meryl3Work *work, int arg);
void s03d_800CC168(Meryl3Work *work, int arg);
void s03d_800CC2E8(Meryl3Work *work, int arg);
void s03d_800CBE2C(Meryl3Work *work, int arg);
void s03d_800CBEF4(Meryl3Work *work, int arg);
void s03d_800CC05C(Meryl3Work *work, int arg);
void s03d_800CC374(Meryl3Work *work);
void Zako_800CCA64(Meryl3Work *work);
int  Zako_800CB9E8(Meryl3Work *work);

int Zako_800CB9E8(Meryl3Work *work)
{
    int flags = work->field_974;

    if (flags & 1)
    {
        work->field_954 = s03d_800CC05C;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 4)
    {
        work->field_954 = s03d_800CBE2C;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    if (flags & 8)
    {
        work->field_954 = s03d_800CBEF4;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return 1;
    }
    return 0;
}
int s03d_800CBA60(Meryl3Work *work)
{
    TARGET *t = work->target;

    if (t->damaged & 4)
    {
        if (t->a_mode == 1)
        {
            t->force = DG_ZeroVector;
            work->field_954 = s03d_800CC2E8;
            work->field_95C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else if (t->a_mode == 2)
        {
            t->force = DG_ZeroVector;
            work->field_954 = s03d_800CC2E8;
            work->field_95C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        t->damage = 0;
        t->damaged = 0;
        return 1;
    }
    return 0;
}
void Zako_800CBAEC(Meryl3Work *work)
{
    int v = work->field_96C;

    work->adjust[2].vx = v;
    work->adjust[6].vx = v;
    if (v < 0)
    {
        work->adjust[7].vx = v * 3;
    }
    else
    {
        work->adjust[7].vx = v * 3 / 2;
    }
}
void s03d_800CBB2C(Meryl3Work *work)
{
    MATRIX  mat;
    SVECTOR rot;
    MATRIX *m = &work->body.objs->objs[4].world;

    DG_SetPos(m);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3980);
    rot = DG_ZeroVector;
    rot.vx = 0x400;
    DG_RotatePos(&rot);
    ReadRotMatrix(&mat);
    NewBulletEx(0x100, &mat, 1, 1, 0, 0xA, 0x41, 0x2710, 0x2EE);
    GM_SeSetMode(&work->control.mov, 0x2E, 1);
    NewAnime_8005D6BC(m, 0);
    NewAnime_8005D604(&mat);
}
void s03d_800CBC10(Meryl3Work *work, int arg)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 0;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[0], 0, 4);
    }
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (Zako_800CB9E8(work))
    {
        return;
    }
    if (work->field_978 >= 0)
    {
        work->field_954 = s03d_800CBCDC;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    work->control.step = DG_ZeroVector;
    work->target->class |= 0x14;
}
void s03d_800CBCDC(Meryl3Work *work, int arg)
{
    CONTROL *ctl = &work->control;
    int      v = work->field_978;

    if (arg == 0)
    {
        work->field_964 = 1;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[1], 0, 4);
    }
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (Zako_800CB9E8(work))
    {
        return;
    }
    if (v < 0)
    {
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_ConfigObjectOverride(&work->body, s03d_word_800C3970[0], 0, 4, 0);
        work->field_958 = 0;
        work->field_960 = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        int s1;

        ctl->turn.vy = v;
        s1 = (arg < 0xA) ? arg * 4 : 0x28;
        ctl->step.vx = s1 * rsin(v) / 4096;
        ctl->step.vz = s1 * rcos(v) / 4096;
        work->target->class |= 0x14;
    }
}
void s03d_800CBE2C(Meryl3Work *work, int arg)
{
    CONTROL *ctl = &work->control;

    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 5;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[5], 0, 4);
    }
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (!(work->field_974 & 4))
    {
        if (Zako_800CB9E8(work))
        {
            return;
        }
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        ctl->turn.vy = *(unsigned short *)&work->field_968;
        work->target->class |= 0x14;
    }
}
void s03d_800CBEF4(Meryl3Work *work, int arg)
{
    CONTROL *ctl = &work->control;

    if (arg == 0)
    {
        work->field_964 = 2;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[2], 0, 4);
    }
    if (arg < 0x1E && (arg & 7) == 0)
    {
        GM_SeSetMode(&work->control.mov, 4, 1);
    }
    if (arg == 0x1E)
    {
        work->field_964 = 6;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[6], 0, 4);
        NewAnime_8005DDE0(&work->body.objs->objs[4].world);
    }
    if (arg == 0x2E)
    {
        GM_SeSetMode(&work->control.mov, 0x2F, 1);
    }
    if (arg >= 0x1F && work->body.is_end)
    {
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_SeSetMode(&work->control.mov, 9, 1);
    }
    else
    {
        ctl->turn.vy = *(unsigned short *)&work->field_968;
        ctl->step = DG_ZeroVector;
        work->target->class |= 0x14;
    }
}
void s03d_800CC05C(Meryl3Work *work, int arg)
{
    int flags = work->field_974;

    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (arg == 0)
    {
        work->field_964 = 2;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[2], 0, 4);
        GM_ConfigMotionAdjust(&work->body, &work->adjust[0]);
    }
    Zako_800CBAEC(work);
    if (!(flags & 1))
    {
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
    else
    {
        work->control.turn.vy = *(unsigned short *)&work->field_968;
        work->control.step = DG_ZeroVector;
        if (flags & 2)
        {
            work->field_954 = s03d_800CC168;
            work->field_95C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
        else
        {
            work->target->class |= 0x14;
        }
    }
}
void s03d_800CC168(Meryl3Work *work, int arg)
{
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (arg == 0)
    {
        work->field_964 = 2;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[2], 0, 0);
        s03d_800CBB2C(work);
        GM_ConfigMotionAdjust(&work->body, &work->adjust[0]);
    }
    Zako_800CBAEC(work);
    work->control.turn.vy = *(unsigned short *)&work->field_968;
    work->control.step = DG_ZeroVector;
    work->field_954 = s03d_800CC05C;
    work->field_95C = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->target->class |= 0x14;
}
void Zako_800CC244(Meryl3Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3988);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3990);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
    work->control.step = DG_ZeroVector;
}

void s03d_800CC2E8(Meryl3Work *work, int arg)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 4;
        GM_ConfigObjectAction(&work->body, s03d_word_800C3970[4], 0, 4);
        GM_SeSet(&work->control.mov, 0xBB);
        Zako_800CC244(work, 5, 0);
    }
    if (work->body.is_end)
    {
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800CC374(Meryl3Work *work)
{
    CONTROL *ctl = &work->control;
    OBJECT  *obj = &work->body;
    void   (*h)(struct _Meryl3Work *, int);
    int      n;

    work->target->class = 1;
    n = work->field_95C;
    h = work->field_954;
    work->field_95C = n + 1;
    if (h == 0)
    {
        h = s03d_800CBC10;
        work->field_954 = h;
    }
    h(work, n);
    ctl->height = *(unsigned short *)&obj->height;
    ctl->r_sphere = -1;
    if (work->field_920 < 0)
    {
        if (ctl->grounded)
        {
            work->field_920 = 0;
        }
    }
    work->field_920 -= 0x10;
    ctl->step.vy = *(unsigned short *)&work->field_920;
}
void Zako_800CC430(Meryl3Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_9A4 = GV_VecDir2(&vec);
    work->field_9A8 = GV_VecLen3(&vec);
}
void Zako_800CC480(Meryl3Work *work)
{
    Zako_800CC430(work);
    Zako_800CCA64(work);
    s03d_800CC374(work);
}
