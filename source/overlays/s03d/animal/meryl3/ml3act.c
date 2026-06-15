#include "common.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    OBJECT          field_180;      /* 0x180 */
    char            pad_264[0x718 - 0x264];
    SVECTOR         field_718;      /* 0x718 */
    char            pad_720[0x728 - 0x720];
    short           field_728;      /* 0x728 */
    char            pad_72A[0x734 - 0x72A];
    short           field_734;      /* 0x734 */
    char            pad_736[0x748 - 0x736];
    short           field_748;      /* 0x748 */
    char            pad_74A[0x750 - 0x74A];
    short           field_750;      /* 0x750 */
    char            pad_752[0x8CC - 0x752];
    TARGET         *field_8CC;      /* 0x8CC */
    char            pad_8D0[0x920 - 0x8D0];
    int             field_920;      /* 0x920 */
    char            pad_924[0x954 - 0x924];
    void          (*field_954)(struct _Work *, int);  /* 0x954 */
    char            pad_958[0x95C - 0x958];
    int             field_95C;      /* 0x95C */
    char            pad_960[0x964 - 0x960];
    int             field_964;      /* 0x964 */
    int             field_968;      /* 0x968 */
    int             field_96C;      /* 0x96C */
    char            pad_970[0x974 - 0x970];
    int             field_974;      /* 0x974 */
    int             field_978;      /* 0x978 */
    char            pad_97C[0x9A4 - 0x97C];
    int             field_9A4;      /* 0x9A4 */
    int             field_9A8;      /* 0x9A8 */
    char            pad_9AC[0xC00 - 0x9AC];
} Work;

extern short s03d_word_800C3970[8];
extern int s03d_dword_800C3980;
extern int s03d_dword_800C3988;
extern int s03d_dword_800C3990;

extern void NewBlood(MATRIX *, int);
extern void *NewAnime_8005DDE0(MATRIX *);
extern void NewAnime_8005D6BC(MATRIX *, int);
extern void NewAnime_8005D604(MATRIX *);
extern void *NewBulletEx(int, MATRIX *, int, int, int, int, int, int, int);

int  s03d_800CBA60(Work *work);
void s03d_800CBB2C(Work *work);
void s03d_800CBC10(Work *work, int arg);
void s03d_800CBCDC(Work *work, int arg);
void s03d_800CC168(Work *work, int arg);
void s03d_800CC2E8(Work *work, int arg);
void s03d_800CBE2C(Work *work, int arg);
void s03d_800CBEF4(Work *work, int arg);
void s03d_800CC05C(Work *work, int arg);
void s03d_800CC374(Work *work);
void Zako_800CCA64(Work *work);
int  Zako_800CB9E8(Work *work);

int Zako_800CB9E8(Work *work)
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
int s03d_800CBA60(Work *work)
{
    TARGET *t = work->field_8CC;

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
void Zako_800CBAEC(Work *work)
{
    int v = work->field_96C;

    work->field_728 = v;
    work->field_748 = v;
    if (v < 0)
    {
        work->field_750 = v * 3;
    }
    else
    {
        work->field_750 = v * 3 / 2;
    }
}
void s03d_800CBB2C(Work *work)
{
    MATRIX  mat;
    SVECTOR rot;
    MATRIX *m = &work->field_9C.objs->objs[4].world;

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
void s03d_800CBC10(Work *work, int arg)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 0;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[0], 0, 4);
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
    work->field_8CC->class |= 0x14;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800CBCDC.s")
void s03d_800CBE2C(Work *work, int arg)
{
    CONTROL *ctl = &work->control;

    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 5;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[5], 0, 4);
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
        work->field_8CC->class |= 0x14;
    }
}
void s03d_800CBEF4(Work *work, int arg)
{
    CONTROL *ctl = &work->control;

    if (arg == 0)
    {
        work->field_964 = 2;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[2], 0, 4);
    }
    if (arg < 0x1E && (arg & 7) == 0)
    {
        GM_SeSetMode(&work->control.mov, 4, 1);
    }
    if (arg == 0x1E)
    {
        work->field_964 = 6;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[6], 0, 4);
        NewAnime_8005DDE0(&work->field_9C.objs->objs[4].world);
    }
    if (arg == 0x2E)
    {
        GM_SeSetMode(&work->control.mov, 0x2F, 1);
    }
    if (arg >= 0x1F && work->field_9C.is_end)
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
        work->field_8CC->class |= 0x14;
    }
}
void s03d_800CC05C(Work *work, int arg)
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
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[2], 0, 4);
        GM_ConfigMotionAdjust(&work->field_9C, &work->field_718);
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
            work->field_8CC->class |= 0x14;
        }
    }
}
void s03d_800CC168(Work *work, int arg)
{
    if (s03d_800CBA60(work))
    {
        return;
    }
    if (arg == 0)
    {
        work->field_964 = 2;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[2], 0, 0);
        s03d_800CBB2C(work);
        GM_ConfigMotionAdjust(&work->field_9C, &work->field_718);
    }
    Zako_800CBAEC(work);
    work->control.turn.vy = *(unsigned short *)&work->field_968;
    work->control.step = DG_ZeroVector;
    work->field_954 = s03d_800CC05C;
    work->field_95C = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    work->field_8CC->class |= 0x14;
}
void Zako_800CC244(Work *work, int index, int count)
{
    MATRIX m;

    DG_SetPos(&work->field_9C.objs->objs[index].world);
    DG_MovePos((SVECTOR *)&s03d_dword_800C3988);
    DG_RotatePos((SVECTOR *)&s03d_dword_800C3990);
    ReadRotMatrix(&m);
    NewBlood(&m, count);
    work->control.step = DG_ZeroVector;
}

void s03d_800CC2E8(Work *work, int arg)
{
    work->control.step.vx = 0;
    work->control.step.vz = 0;
    if (arg == 0)
    {
        work->field_964 = 4;
        GM_ConfigObjectAction(&work->field_9C, s03d_word_800C3970[4], 0, 4);
        GM_SeSet(&work->control.mov, 0xBB);
        Zako_800CC244(work, 5, 0);
    }
    if (work->field_9C.is_end)
    {
        work->field_954 = s03d_800CBC10;
        work->field_95C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s03d_800CC374(Work *work)
{
    CONTROL *ctl = &work->control;
    OBJECT  *obj = &work->field_9C;
    void   (*h)(struct _Work *, int);
    int      n;

    work->field_8CC->class = 1;
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
void Zako_800CC430(Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&GM_PlayerPosition, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_9A4 = GV_VecDir2(&vec);
    work->field_9A8 = GV_VecLen3(&vec);
}
void Zako_800CC480(Work *work)
{
    Zako_800CC430(work);
    Zako_800CCA64(work);
    s03d_800CC374(work);
}
