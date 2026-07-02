#include "game/game.h"
#include "game/target.h"
#include "kojo/m1e1.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"
#include "linkvar.h"

extern int rand(void);
extern void *NewFadeInOut(int mode, int shade);
extern void *NewSmokeLn_800CDFA4(int a0, int a1, int a2, SVECTOR *p, SVECTOR *q,
                                 SVECTOR *r, char b, char c, char d);
extern void AN_Blast_high2(SVECTOR *pos, SVECTOR *offset);

typedef struct
{
    HZD_SEG seg[4];
    HZD_FLR flr[2];
} HzdBlock; /* 0xA0 */

typedef struct _Work
{
    char     pad_000[0x20];
    CONTROL  control;       /* 0x020 (mov@0x20, map@0x4C, turn@0x6C) */
    char     pad_9C[0xDC - 0x9C];
    OBJECT   body;          /* 0x0DC */
    OBJECT   bodies_a[3];   /* 0x1C0 */
    OBJECT   bodies_b[3];   /* 0x46C */
    void    *field_718[10]; /* 0x718 */
    int      field_740;     /* 0x740 */
    char     pad_744[0x74C - 0x744];
    char     snap_control[0x7C];   /* 0x74C */
    char     snap_body[0xE4];      /* 0x7C8 */
    char     pad_8AC[0x8BC - 0x8AC];
    int      field_8BC;     /* 0x8BC */
    char     pad_8C0[0x8CC - 0x8C0];
    TARGET   target0;       /* 0x8CC */
    TARGET   target1;       /* 0x914 */
    char     pad_95C[0x960 - 0x95C];
    TARGET   target2;       /* 0x960 */
    TARGET   target3;       /* 0x9A8 */
    TARGET   target4;       /* 0x9F0 */
    TARGET   target5;       /* 0xA38 */
    char     pad_A80[0xA84 - 0xA80];
    TARGET   field_A84[10]; /* 0xA84 */
    int      field_D54;     /* 0xD54 */
    int      field_D58;     /* 0xD58 */
    int      field_D5C;
    int      field_D60;
    int      field_D64;     /* 0xD64 */
    int      field_D68;     /* 0xD68 */
    int      field_D6C;
    int      field_D70;
    int      field_D74;
    int      field_D78;
    int      field_D7C;
    int      field_D80;
    int      field_D84;
    int      field_D88;
    int      field_D8C;
    int      field_D90;
    int      field_D94;
    int      field_D98;
    int      field_D9C;
    int      field_DA0;
    int      field_DA4;
    int      field_DA8;
    int      field_DAC;
    int      field_DB0;
    int      field_DB4;
    int      field_DB8;
    char     pad_DBC[0xDC4 - 0xDBC];
    int      field_DC4;
    char     pad_DC8[0xE08 - 0xDC8];
    int      field_E08;     /* 0xE08 */
    int      field_E0C;     /* 0xE0C */
    int      field_E10;     /* 0xE10 */
    char     pad_E14[0xE14 - 0xE14];
    int      field_E14;
    char     pad_E18[0xE1C - 0xE18];
    int      field_E1C;     /* 0xE1C */
    int      field_E20;     /* 0xE20 */
    char     pad_E24[0xE24 - 0xE24];
    int      field_E24;
    int      field_E28;
    char     pad_E2C[0xE2C - 0xE2C];
    int      field_E2C;
    int      field_E30;
    char     pad_E34[0xE34 - 0xE34];
    int      field_E34;
    char     pad_E38[0xE3C - 0xE38];
    int      field_E3C;
    char     pad_E40[0xE44 - 0xE40];
    int      field_E44;
    int      field_E48;
    int      field_E4C;
    char     pad_E50[0xE54 - 0xE50];
    u_short  field_E54;     /* 0xE54 */
    u_short  field_E56;     /* 0xE56 */
    u_short  field_E58;     /* 0xE58 */
    char     pad_E5A[0xE5C - 0xE5A];
    int      field_E5C;
    int      field_E60;
    int      field_E64;     /* 0xE64 */
    int      field_E68;
    char     pad_E6C[0xE88 - 0xE6C];
    int      field_E88;
    char     pad_E8C[0xE9C - 0xE8C];
    u_short  field_E9C;     /* 0xE9C */
    short    field_E9E;     /* 0xE9E */
    u_short  field_EA0;     /* 0xEA0 */
    char     pad_EA2[0xEA4 - 0xEA2];
    short    field_EA4;     /* 0xEA4 */
    char     pad_EA6[0xEB0 - 0xEA6];
    void    *field_EB0;     /* 0xEB0 */
    char     pad_EB4[0xEC0 - 0xEB4];
    int      field_EC0;     /* 0xEC0 */
    int      field_EC4;
    int      field_EC8;
    char     pad_ECC[0xED0 - 0xECC];
    int      field_ED0;     /* 0xED0 */
    char     pad_ED4[0xED8 - 0xED4];
    int      field_ED8;
    void    *field_EDC;     /* 0xEDC */
    char     pad_EE0[0xEF0 - 0xEE0];
    SVECTOR  field_EF0[10]; /* 0xEF0 */
    char     pad_F40[0xF40 - 0xF40];
    int      field_F40;     /* 0xF40 */
    int      field_F44;
    int      field_F48;
    int      field_F4C;
    int      field_F50;
    int      field_F54;
    int      field_F58;     /* 0xF58 */
    int      field_F5C;
    int      field_F60;
    int      field_F64;
    int      field_F68;
    int      field_F6C;
    int      field_F70;
    int      field_F74;
    int      field_F78;
    char     pad_F7C[0xF80 - 0xF7C];
    int      field_F80;
    char     pad_F84[0xF88 - 0xF84];
    int      field_F88;
    SVECTOR  bbox[10];      /* 0xF8C */
    char     pad_FDC[0xFEC - 0xFDC];
    HzdBlock hzd[5];        /* 0xFEC */
    HZD_FLR  copy0;         /* 0x130C */
    HZD_FLR  copy1;         /* 0x133C */
    HZD_FLR  copy2;         /* 0x136C */
} Work;

extern Work *s05a_dword_800C362C;
extern int   s05a_dword_800C3630;
extern int   s05a_dword_800C3634;
extern int   s05a_dword_800C3638;

extern void sub_8007E1C0(HZD_SEG *seg, HZD_FLR *flr, MATRIX *pTransform,
                         SVECTOR *pMin, SVECTOR *pMax);
extern void AN_Smoke_800CE08C(SVECTOR *pos);

void  s05a_800D627C(Work *work);
void  s05a_800D797C(Work *work);
void  s05a_800D863C(Work *work);
void  s05a_800D9754(Work *work);
void  s05a_800DA02C(Work *work);
void  s05a_800DA62C(Work *work);
void  s05a_800DA940(Work *work);
void  s05a_800DACF0(Work *work);
void  s05a_800DD1C8(Work *work);

void s05a_800D4A74(Work *work)
{
    SVECTOR va;         /* sp+0x28 */
    SVECTOR vb;         /* sp+0x30 */
    SVECTOR vc;         /* sp+0x38 */
    int     i;
    int     s0;
    OBJECT *bodyp;

    MENU_Locate(0x50, 0x5a, 0);

    /* control + light-matrix snapshot */
    memcpy(work->snap_control, &work->control, 0x7C);
    memcpy(work->snap_body, &work->body, 0xE4);

    bodyp = &work->body;
    work->body.rots[10].vy = 0x11c;
    GM_ActMotion(bodyp);

    /* ---- animation/control update ---- */
    work->control.turn.vx += work->field_E9C;
    work->control.turn.vy += work->field_E9E;
    work->control.turn.vz += work->field_EA0;
    GM_ActControl(&work->control);
    GM_ActObject(bodyp);
    for (i = 0; i < 3; i++)
    {
        GM_ActMotion(&work->bodies_a[i]);
        GM_ActMotion(&work->bodies_b[i]);
    }

    va = work->control.mov;
    va.vy -= work->field_EA4;
    vb.vx = work->control.rot.vx - work->field_E9C;
    vb.vy = work->control.rot.vy - work->field_E9E;
    vb.vz = work->control.rot.vz - work->field_EA0;
    DG_SetPos2(&va, &vb);

    for (i = 0; i < 3; i++)
    {
        GM_ActObject(&work->bodies_a[i]);
        GM_ActObject(&work->bodies_b[i]);
    }
    DG_GetLightMatrix2(&work->control.mov, (MATRIX *)&work->pad_9C[0]);

    if (work->field_740 == 0)
    {
        work->body.objs->flag &= ~0x80;
    }

    if (--work->field_F40 < 0) work->field_F40 = 0;
    if (--work->field_F44 < 0) work->field_F44 = 0;
    if (--work->field_F48 < 0) work->field_F48 = 0;
    if (--work->field_F4C < 0) work->field_F4C = 0;
    if (--work->field_F50 < 0) work->field_F50 = 0;
    if (--work->field_F54 < 0) work->field_F54 = 0;
    if (--work->field_F58 < 0) work->field_F58 = 0;
    if (--work->field_F60 < 0) work->field_F60 = 0;
    if (--work->field_F64 < 0) work->field_F64 = 0;
    if (--work->field_F5C < 0) work->field_F5C = 0;
    if (--work->field_F68 < 0) work->field_F68 = 0;
    if (--work->field_F6C < 0) work->field_F6C = 0;
    if (--work->field_F70 < 0) work->field_F70 = 0;
    if (--work->field_F74 < 0) work->field_F74 = 0;
    if (--work->field_F78 < 0) work->field_F78 = 0;
    if (--work->field_F80 < 0) work->field_F80 = 0;

    /* ======== EC0 audio state machine ======== */
    if (work->field_EC0 == 1)
    {
        work->field_EC4++;
        work->field_EC8 = 0;
    }
    else if (work->field_EC0 == 2 && !(GM_PlayerStatus & 0x800300))
    {
        if (++work->field_EC8 >= 3)
        {
            work->field_EC8 = 0;
            if (rand() & 3)
                GM_SeSetPan(&work->control.mov, 0x86, work->field_E60);
        }
    }
    else if (work->field_EC0 == 3)
    {
        work->field_EC8 = 0;
    }

    /* snapshot player position into E44/E48/E4C, compute distance + volume */
    if (s05a_dword_800C362C->field_ED0 == 0)
    {
        work->field_E44 = GM_PlayerPosition.vx;
        work->field_E48 = GM_PlayerPosition.vy;
        work->field_E4C = GM_PlayerPosition.vz;
    }
    va.vx = (work->control.mov.vx - work->field_E44) >> 2;
    va.vy = (work->control.mov.vy - work->field_E48) >> 2;
    va.vz = (work->control.mov.vz - work->field_E4C) >> 2;
    work->field_E5C = SquareRoot0(va.vx * va.vx + va.vy * va.vy + va.vz * va.vz) << 2;
    work->field_E60 = 0x1f;
    {
        int d = work->field_E5C;
        if (d < 0x1f41)
            work->field_E60 = 0x3f;
        else if (d < 0x7531)
        {
            int r = 0x3f;
            r -= ((d - 0x1f40) << 5) / 22000;
            work->field_E60 = r;
        }
    }

    /* ======== F. D54 transition machine ======== */
    if (work->field_D54 == 1 && work->field_740 == 0 && work->field_E5C < work->field_DC4)
    {
        work->field_D54 = 2;
    }
    if (work->field_EB0 && *(int *)((char *)work->field_EB0 + 0x1f0) == 1)
    {
        if (--work->field_E08 <= 0)
        {
            work->field_D54 = 5;
            work->field_F80 = 0x1e;
            NewFadeInOut(2, 0x1e);
        }
        else
        {
            work->field_D54 = 4;
            work->field_F4C = work->field_D78;
        }
    }

    if (work->field_E08 <= 0 && work->field_D54 == 5 && work->field_F80 <= 0)
    {
        GV_DestroyActor(work);
        return;
    }

    if (work->field_F4C <= 0 && work->field_D54 == 4 &&
        work->field_EB0 == 0 && work->field_ED0 == 0)
    {
        if (!work->field_D58)
            work->field_D54 = 2;
        else
            work->field_D54 = 7;
        work->field_F5C = work->field_E14;
    }

    /* ======== G. MENU progress bar ======== */
    if (work->field_D54 != 1 && work->field_D54 != 6)
    {
        s0 = ((work->field_E0C + work->field_D74 * (work->field_E08 - 1)) << 10) /
             (work->field_D74 * work->field_D70);
        if (s0 < 0)
            s0 = 0;
        MENU_DrawBar(0x10, 0x1c, work->field_ED8, s0, (MENU_BAR_CONF *)&work->field_8BC);
        work->field_ED8 = s0;
    }

    /* ======== H. memset + 11-call cascade ======== */
    memset(&work->field_E9C, 0, 8);
    *(int *)&work->field_EA4 = 0;
    s05a_800D797C(work);
    s05a_800D863C(work);
    s05a_800D627C(work);
    s05a_800DA02C(work);
    s05a_800DA62C(work);
    s05a_800D9754(work);
    work->control.mov.vy += work->field_EA4;
    s05a_800DA940(work);
    M1E1Caterpiller((LPM1E1ACTOR)work);
    s05a_800DACF0(work);
    s05a_800DD1C8(work);

    /* ======== I. ED0/EC0/740 reset ======== */
    if (work->field_ED0 == 1)
        work->field_ED0 = 0;
    work->field_EC0 = 0;
    work->field_740 = 0;
    work->field_E2C = work->field_E30;
    if (work->field_D54 == 6)
        return;

    /* ======== J. Target-power section 1 ======== */
    if (work->field_F78 <= 0)
    {
        for (i = 0; i < 10; i++)
        {
            GM_PowerTarget(&work->field_A84[i]);
            if (work->field_A84[i].vital != work->field_DA0)
            {
                GM_PlayerStatus |= 0x200;
                work->field_F78 = 0x5a;
                GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
                break;
            }
        }
        for (i = 0; i < 10; i++)
            work->field_A84[i].vital = work->field_DA0;
    }

    s0 = work->field_E68 - work->field_D9C;
    i = 0;
    if (s0 >= 0)
        i = (work->field_E24 * s0) / work->field_E28 + work->field_D90;

    work->target0.vital = i;
    work->target1.vital = i;
    work->target2.vital = i;
    work->target3.vital = i;
    work->target4.vital = i;
    work->target5.vital = i;
    if (work->field_F78 <= 0 && i > 0)
    {
        int r;
        int d;
        va = work->control.turn;
        while (va.vy < -0x800)
            va.vy += 0x1000;
        while (va.vy >= 0x801)
            va.vy -= 0x1000;
        r = ratan2(work->field_E34, work->field_E3C);
        d = va.vy;
        d -= r;
        if (d < 0)
            d = -d;
        d = d < 0x400;
        if (d)
        {
            GM_PowerTarget(&work->target0);
            GM_PowerTarget(&work->target2);
            GM_PowerTarget(&work->target4);
        }
        else
        {
            GM_PowerTarget(&work->target1);
            GM_PowerTarget(&work->target3);
            GM_PowerTarget(&work->target5);
        }
        if (work->target0.vital != i || work->target1.vital != i ||
            work->target2.vital != i || work->target3.vital != i ||
            work->target4.vital != i || work->target5.vital != i)
        {
            GM_PlayerStatus |= 0x200;
            work->field_F78 = 0x5a;
            GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
        }
    }

    /* ======== K. Smoke/blast keyed on F4C ======== */
    if (work->field_F4C > 0 && (work->field_F4C & 0xf) == 0)
    {
        DG_SetPos((MATRIX *)&work->body.objs->objs[10].world);
        memset(&va, 0, 8);
        DG_PutVector(&va, &va, 1);
        va.vy -= 0x1f4;
        vb = va;
        vb.vy += 0x3e8;
        memset(&vc, 0, 8);
        vc.vy = 0x3e;
        NewSmokeLn_800CDFA4(7, 1, 0, &va, &vb, &vc, 0, 0, 0);
    }

    /* ======== L. Target-power section 2 keyed on F50 ======== */
    if (work->field_F4C <= 0)
    {
        if (work->field_F50 <= 0)
        {
            if (work->field_D64 > work->field_D88 || work->field_D68 > work->field_D8C)
            {
                s0 = 0;
                for (i = 0; i < 10; i++)
                {
                    TARGET *t = (TARGET *)work->field_718[i];
                    if (t->damaged != 0 && t->damaged >= s0 &&
                        (unsigned int)(t->weapon - 2) < 5)
                    {
                        s0 = t->damaged;
                        work->field_E88 = i;
                        work->field_F50 = work->field_D78 >> 1;
                    }
                }
                if (s0)
                {
                    int dx;
                    dx = (work->field_D7C * s0) / work->field_D84;
                    work->field_D64 -= dx;
                    work->field_D68 -= (work->field_D80 * s0) / work->field_D84;
                    {
                        int lo = work->field_D88;
                        if (lo < work->field_D64)
                            lo = work->field_D64;
                        work->field_D64 = lo;
                    }
                    {
                        int lo = work->field_D8C;
                        if (lo < work->field_D68)
                            lo = work->field_D68;
                        work->field_D68 = lo;
                    }
                    DG_SetPos2(&DG_ZeroVector, &work->control.rot);
                    memset(&va, 0, 8);
                    if (work->field_E88 < 5)
                        va.vy = 0x400;
                    else
                        va.vy = -0x400;
                    DG_RotatePos(&va);
                    memset(&va, 0, 8);
                    va.vz = 0x258;
                    DG_PutVector(&va, &va, 1);
                    AN_Blast_high2((SVECTOR *)((char *)work->field_718[work->field_E88] + 8), &va);
                    GM_SeSetPan(&work->control.mov, 0xb1, work->field_E60);
                }
            }
        }
    }

    if (work->field_F50 > 0 && (work->field_F50 & 0xf) == 0)
    {
        va = *(SVECTOR *)((char *)work->field_718[work->field_E88] + 8);
        vb = va;
        vb.vy += 0x3e8;
        memset(&vc, 0, 8);
        vc.vy = 0x3e;
        NewSmokeLn_800CDFA4(7, 2, 0, &va, &vb, &vc, 0, 0, 0);
    }

    for (i = 0; i < 10; i++)
    {
        ((TARGET *)work->field_718[i])->vital = 0x2710;
        ((TARGET *)work->field_718[i])->damage = 0;
        ((TARGET *)work->field_718[i])->damaged = 0;
    }

    /* ======== M. Pad-driven 14-case state machine ======== */
    if (GM_BonusItemsFlag == 0)
        return;

    {
        int *p3634 = &s05a_dword_800C3634;

        if (--*p3634 < 0)
        {
            s05a_dword_800C3630 = 0;
            *p3634 = 0;
        }

        if (work->field_D54 == 7)
        {
            if (GV_PadData[1].status == 0xf0)
            {
                work->field_D58 = 0;
                work->field_D54 = 2;
                return;
            }
        }
        else
        {
            if (s05a_dword_800C3630 == 0)
            {
                if (GV_PadData[1].status == 0xf0)
                {
                    s05a_dword_800C3630 = 1;
                    *p3634 = 0x1e;
                    return;
                }
            }

            if ((unsigned int)(s05a_dword_800C3634 - 1) >= 0x1d)
                return;

            if (s05a_dword_800C3630 == 1 && GV_PadData[1].status == 5)
            {
                s05a_dword_800C3630 = 2;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 2 && GV_PadData[1].status == 0xa)
            {
                s05a_dword_800C3630 = 3;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 3 && GV_PadData[1].status == 0xc)
            {
                s05a_dword_800C3630 = 4;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 4 && GV_PadData[1].status == 0x1000)
            {
                s05a_dword_800C3630 = 5;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 5 && GV_PadData[1].status == 0x4000)
            {
                s05a_dword_800C3630 = 6;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 6 && GV_PadData[1].status == 6)
            {
                s05a_dword_800C3630 = 7;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 7 && GV_PadData[1].status == 0x8000)
            {
                s05a_dword_800C3630 = 8;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 8 && GV_PadData[1].status == 0x2000)
            {
                s05a_dword_800C3630 = 9;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 9 && GV_PadData[1].status == 3)
            {
                s05a_dword_800C3630 = 0xa;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xa && GV_PadData[1].status == 0xe0)
            {
                s05a_dword_800C3630 = 0xb;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xb && GV_PadData[1].status == 0x1000)
            {
                s05a_dword_800C3630 = 0xc;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xc && GV_PadData[1].status == 3)
            {
                s05a_dword_800C3630 = 0xd;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xd && GV_PadData[1].status == 0x90)
            {
                work->field_D58 = 1;
                work->field_D54 = 7;
            }
        }
    }

    /* ======== N. D54==7 final pad input + DG_LookAt + AN_Blast tail ======== */
    if (work->field_D54 == 7)
    {
        u_short pad;
        if (GV_PadData[1].status & 1)
        {
            va.vx = work->field_E44;
            va.vy = work->field_E48;
            va.vz = work->field_E4C;
            va.vy += 0x320;
            vb = work->control.mov;
            vb.vx = va.vx + (vb.vx - va.vx) / 3;
            vb.vy = va.vy + (vb.vy - va.vy) / 3;
            vb.vz = va.vz + (vb.vz - va.vz) / 3;
            DG_LookAt(DG_Chanl(0), &va, &vb, 0x140);
            GM_PlayerBody->objs->flag |= 0x80;
            s05a_dword_800C3638 = 1;
        }
        else if (s05a_dword_800C3638 == 1)
        {
            GM_PlayerBody->objs->flag &= ~0x80;
            s05a_dword_800C3638 = 0;
        }

        pad = GV_PadData[1].status;
        if (!(pad & 4))
            return;
        if (pad & 8)
            work->field_F88 += 0x32;
        else if (pad & 2)
            work->field_F88 -= 0x32;

        DG_SetPos((MATRIX *)&work->body.objs->objs[6].world);
        memset(&va, 0, 8);
        memset(&vb, 0, 8);
        va.vz = 0x3e8;
        va.vy = 0x3e8;
        vb.vz = 0x7d0;
        vb.vy = work->field_F88 + 0x3e8;
        DG_PutVector(&va, &va, 1);
        DG_PutVector(&vb, &vb, 1);
        DG_LookAt(DG_Chanl(0), &va, &vb, 0x140);
    }
}
void s05a_800D5E30(Work *work)
{
    int i;

    GM_uTenageMotion = -1;
    if (work->field_EDC) GV_DestroyActor(work->field_EDC);
    GM_lpfnPlayerActControl = 0;
    GM_lpfnPlayerActObject2 = 0;
    GM_lpfnBombHoming = 0;
    GM_lpfnBombBound = 0;
    GM_lpfnBombExplosion = 0;
    if (work->field_EB0) GV_DestroyActor(work->field_EB0);

    if (work->field_E1C >= 0)
    {
        long     argv[5];
        GCL_ARGS args;
        argv[0] = work->field_D64 / 10 * 30 / 100 * 60 / 1000 * 60;
        argv[1] = work->field_D68 * 30;
        argv[2] = work->field_E08;
        argv[3] = work->field_E0C;
        argv[4] = work->field_E10;
        args.argv = argv;
        args.argc = 5;
        GCL_ForceExecProc(work->field_E1C, &args);
    }

    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[0].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[0].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[0].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[1].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[1].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[1].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[2].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[2].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[2].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[3].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[3].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[3].flr[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[0]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[1]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[2]);
    HZD_DequeueDynamicSegment(work->control.map->hzd, &work->hzd[4].seg[3]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[4].flr[0]);
    HZD_DequeueDynamicFloor(work->control.map->hzd, &work->hzd[4].flr[1]);

    GM_FreeObject(&work->body);
    for (i = 0; i < 3; i++)
    {
        GM_FreeObject(&work->bodies_a[i]);
        GM_FreeObject(&work->bodies_b[i]);
    }
    for (i = 0; i < 8; i++) GM_FreeTarget(work->field_718[i]);
    GM_FreeControl(&work->control);
    s05a_dword_800C362C = 0;
    if (work->field_D54 == 5 && work->field_E20 >= 0) GCL_ExecProc(work->field_E20, 0);
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D627C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D797C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D863C.s")
void s05a_800D9754(Work *work)
{
    SVECTOR vec;
    int     s0;

    if (work->field_F58 <= 0) return;
    if (work->field_F58 >= 0xF)
    {
        DG_SetPos2(&work->control.mov, &work->control.turn);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&work->bbox[1].vy; vec.vz = (short)*(u_short *)&work->bbox[0].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&work->bbox[1].vy; vec.vz = (short)*(u_short *)&work->bbox[1].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8);
        vec.vx = *(u_short *)((char *)work->body.objs->objs[1].model + 0x20);
        vec.vy = *(u_short *)((char *)work->body.objs->objs[1].model + 0x24) + (*(u_short *)&work->bbox[9].vy - *(u_short *)&work->bbox[8].vy);
        vec.vz = *(u_short *)((char *)work->body.objs->objs[1].model + 0x28);
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
    }
    s0 = work->field_F58 - 0xA;
    {
        int d;
        if (s0 >= 0) { d = 5; s0 = 5 - s0; } else { d = 0xA; s0 = work->field_F58; }
        s0 = s0 * 34 / d;
    }
    memset(&vec, 0, 8); vec.vx = s0; DG_SetPos2(&DG_ZeroVector, &vec);
    DG_RotatePos(&work->body.rots[3]);
    {
        int dist, r;
        short pv[3];
        memset(&vec, 0, 8); vec.vz = 0x64; DG_PutVector(&vec, &vec, 1);
        dist = SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz); r = ratan2(vec.vy, dist);
        pv[0] = r;
        r = (short)r; if (r < 0) r = -r; pv[2] = s0 - r;
        s0 = work->body.rots[3].vy;
        while (s0 < 0) s0 += 0x1000;
        while (s0 >= 0x1001) s0 -= 0x1000;
        if (s0 >= 0x801) pv[2] = -pv[2];
        work->field_E9C += pv[0];
        work->field_EA0 += pv[2];
    }
}
extern const char s05a_dword_800E349C[]; /* "drive4" */
extern const char s05a_dword_800E34A4[]; /* "drive5" */
extern const char s05a_dword_800E34AC[]; /* "drive6" */
extern const char s05a_dword_800E34B4[]; /* "drive7" */
extern const char s05a_dword_800E34BC[]; /* "drive1" */
extern const char s05a_dword_800E34C4[]; /* "drive2" */
extern const char s05a_dword_800E34CC[]; /* "drive3" */

void s05a_800D9A14(Work *work)
{
    int      cnt;
    HZD_TRP *trap;
    HZD_DEF *def;
    HZD_PAT *route;
    SVECTOR  d;
    int      dist, thr, s5;

    {
    HZD_HDL *hzd = work->control.map->hzd;
    HZD_GRP *grp = hzd->grp;
    trap = (HZD_TRP *)grp->triggers;
    cnt = grp->n_triggers - hzd->n_cameras;
    }
    for (; cnt > 0; cnt--, trap++)
    {
        if (trap->name_id == GV_StrCode(s05a_dword_800E349C))
        {
            if (trap->b1.x <= work->field_E44 && work->field_E44 <= trap->b2.x &&
                trap->b1.y <= work->field_E48 && work->field_E48 <= trap->b2.y &&
                trap->b1.z <= work->field_E4C && work->field_E4C <= trap->b2.z)
                break;
        }
        if (work->field_F78 > 0)
        {
            if (trap->name_id == GV_StrCode(s05a_dword_800E34A4) ||
                trap->name_id == GV_StrCode(s05a_dword_800E34AC) ||
                trap->name_id == GV_StrCode(s05a_dword_800E34B4))
            {
                if (trap->b1.x <= work->field_E44 && work->field_E44 <= trap->b2.x &&
                    trap->b1.y <= work->field_E48 && work->field_E48 <= trap->b2.y &&
                    trap->b1.z <= work->field_E4C && work->field_E4C <= trap->b2.z)
                    break;
            }
        }
    }

    if (cnt <= 0)
    {
        HZD_HDL *hzd = work->control.map->hzd;
        HZD_GRP *grp = hzd->grp;
        trap = (HZD_TRP *)grp->triggers;
        cnt = grp->n_triggers - hzd->n_cameras;
        if (cnt <= 0) return;
        for (; cnt > 0; cnt--, trap++)
        {
            if (work->field_E08 < 2 && work->field_E64 == 0)
            {
                if (trap->name_id == GV_StrCode(s05a_dword_800E34BC) ||
                    trap->name_id == GV_StrCode(s05a_dword_800E34C4) ||
                    trap->name_id == GV_StrCode(s05a_dword_800E34CC))
                {
                    if (trap->b1.x <= work->control.mov.vx && work->control.mov.vx <= trap->b2.x &&
                        trap->b1.y <= work->control.mov.vy && work->control.mov.vy <= trap->b2.y &&
                        trap->b1.z <= work->control.mov.vz && work->control.mov.vz <= trap->b2.z)
                        break;
                }
            }
        }
        if (cnt <= 0) return;
    }

    /* phase 3: dispatch found trap's name_id -> field_E30 + route */
    def = work->control.map->hzd->def;
    route = def->routes;
    if (trap->name_id == GV_StrCode(s05a_dword_800E34BC)) { work->field_E30 = 8; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E34C4)) { work->field_E30 = 9; route += 1; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E34CC)) { work->field_E30 = 0xA; route += 2; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E349C)) { work->field_E30 = 0xB; route += 3; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E34A4)) { work->field_E30 = 0xC; route += 4; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E34AC)) { work->field_E30 = 0xD; route += 5; }
    else if (trap->name_id == GV_StrCode(s05a_dword_800E34B4)) { work->field_E30 = 0xE; route += 6; }

    /* phase 4: initial distance target->route->points[0] */
    d.vx = (work->control.mov.vx - route->points->x) >> 2;
    d.vy = (work->control.mov.vy - route->points->y) >> 2;
    d.vz = (work->control.mov.vz - route->points->z) >> 2;
    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    cnt = 1;
    thr = (dist << 2) - 0x7d0;
    s5 = 0xbb8;

    /* phase 5: find nearest patrol point */
    {
        HZD_PTP *cur = route->points + 1;
        if (cnt < route->n_points)
        do
        {
            d.vx = (route->points[0].x - cur->x) >> 2;
            d.vy = (route->points[0].y - cur->y) >> 2;
            d.vz = (route->points[0].z - cur->z) >> 2;
            dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
            if ((dist << 2) >= thr)
                break;
            if (cur->x - s5 <= work->control.mov.vx &&
                work->control.mov.vx <= cur->x + s5 &&
                cur->z - s5 <= work->control.mov.vz &&
                work->control.mov.vz <= cur->z + s5)
                break;
            cnt++;
            cur++;
        } while (cnt < route->n_points);
    }

    /* phase 6: store chosen point */
    cnt--;
    work->field_E54 = route->points[cnt].x;
    work->field_E56 = route->points[cnt].y;
    work->field_E58 = route->points[cnt].z;
}
extern void M1E1GetCaterpillerVertex(OBJECT *obj1, OBJECT *obj2, SVECTOR *pos, int a4);

#define HZD_FLOOR(v)                                                            \
    if (HZD_LevelHazardCheck(work->control.map->hzd, (v), HZD_CHK_F_FLOOR) != 1) \
    {                                                                          \
        (v)->vy = 0;                                                          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        HZD_GetLevelHeight(levels);                                           \
        (v)->vy = levels[0];                                                  \
    }

void s05a_800DA02C(Work *work)
{
    int     levels[2];
    SVECTOR mov;
    SVECTOR turn;
    SVECTOR verts[10];
    SVECTOR mid[4];

    mov = work->control.mov;
    mov.vy = mov.vy + *(u_short *)&work->body.objs->def->max.vy;
    turn.vx = 0;
    turn.vy = work->control.turn.vy;
    turn.vz = 0;
    DG_SetPos2(&mov, &turn);

    M1E1GetCaterpillerVertex(&work->bodies_a[0], &work->bodies_b[0], verts, 1);
    DG_PutVector(verts, verts, 10);

    if ((GV_Time & 1) == 0)
    {
        verts[0].vy = work->field_EF0[0].vy;
        verts[1].vy = work->field_EF0[1].vy;
        verts[2].vy = work->field_EF0[2].vy;
        verts[3].vy = work->field_EF0[3].vy;
        verts[4].vy = work->field_EF0[4].vy;
    }
    else
    {
        HZD_FLOOR(&verts[0]);
        HZD_FLOOR(&verts[1]);
        HZD_FLOOR(&verts[3]);
        HZD_FLOOR(&verts[4]);
        work->field_EF0[0].vy = verts[0].vy;
        work->field_EF0[1].vy = verts[1].vy;
        work->field_EF0[2].vy = verts[2].vy;
        work->field_EF0[3].vy = verts[3].vy;
        work->field_EF0[4].vy = verts[4].vy;
    }

    {
        SVECTOR *r = &verts[5];
        if (GV_Time & 1)
        {
            verts[5].vy = work->field_EF0[5].vy;
            verts[6].vy = work->field_EF0[6].vy;
            verts[7].vy = work->field_EF0[7].vy;
            verts[8].vy = work->field_EF0[8].vy;
            verts[9].vy = work->field_EF0[9].vy;
        }
        else
        {
            if (HZD_LevelHazardCheck(work->control.map->hzd, r, HZD_CHK_F_FLOOR) != 1)
            {
                verts[5].vy = 0;
            }
            else
            {
                HZD_GetLevelHeight(levels);
                verts[5].vy = levels[0];
            }
            HZD_FLOOR(&verts[6]);
            HZD_FLOOR(&verts[8]);
            HZD_FLOOR(&verts[9]);
            work->field_EF0[5].vy = verts[5].vy;
            work->field_EF0[6].vy = verts[6].vy;
            work->field_EF0[7].vy = verts[7].vy;
            work->field_EF0[8].vy = verts[8].vy;
            work->field_EF0[9].vy = verts[9].vy;
        }
    }

    {
    SVECTOR *mp = mid;
    int i = 0;
    mid[0].vx = (verts[0].vx + verts[1].vx) >> 1;
    mid[0].vy = (verts[0].vy + verts[1].vy) >> 1;
    mid[0].vz = (verts[0].vz + verts[1].vz) >> 1;
    mid[1].vx = (verts[3].vx + verts[4].vx) >> 1;
    mid[1].vy = (verts[3].vy + verts[4].vy) >> 1;
    mid[1].vz = (verts[3].vz + verts[4].vz) >> 1;
    mid[2].vx = (verts[5].vx + verts[6].vx) >> 1;
    mid[2].vy = (verts[5].vy + verts[6].vy) >> 1;
    mid[2].vz = (verts[5].vz + verts[6].vz) >> 1;
    mid[3].vx = (verts[8].vx + verts[9].vx) >> 1;
    mid[3].vy = (verts[8].vy + verts[9].vy) >> 1;
    mid[3].vz = (verts[8].vz + verts[9].vz) >> 1;

    work->control.mov.vy = 0;
    for (i = 0; i < 4; i++)
    {
        work->control.mov.vy = work->control.mov.vy + mp[i].vy;
    }
    work->control.mov.vy = (short)work->control.mov.vy >> 2;
    }

    mov.vx = (mid[1].vx + mid[3].vx) - (mid[0].vx + mid[2].vx);
    mov.vy = (mid[1].vy + mid[3].vy) - (mid[0].vy + mid[2].vy);
    mov.vz = (mid[1].vz + mid[3].vz) - (mid[0].vz + mid[2].vz);
    work->control.turn.vx = ratan2(mov.vy, SquareRoot0(mov.vx * mov.vx + mov.vz * mov.vz));

    mov.vx = (mid[0].vx + mid[1].vx) - (mid[2].vx + mid[3].vx);
    mov.vy = (mid[0].vy + mid[1].vy) - (mid[2].vy + mid[3].vy);
    mov.vz = (mid[0].vz + mid[1].vz) - (mid[2].vz + mid[3].vz);
    work->control.turn.vz = ratan2(mov.vy, SquareRoot0(mov.vx * mov.vx + mov.vz * mov.vz));
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DA62C.s")
#define WMDL(off) (*(u_short *)((char *)work->body.objs->objs[0].model + (off)))

void s05a_800DA940(Work *work)
{
    SVECTOR vec;
    SVECTOR verts[10];
    int     i;
    int     s0, s1;

    if (work->field_D54 == 6)
    {
        return;
    }

    DG_SetPos2(&work->control.mov, &work->control.turn);
    M1E1GetCaterpillerVertex(&work->bodies_a[0], &work->bodies_b[0], verts, 1);
    for (i = 0; i < 10; i++) verts[i].vy += 0x258;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget((TARGET *)work->field_718[i], &verts[i]);
        GM_PushTarget((TARGET *)work->field_718[i]);
    }

    M1E1GetCaterpillerVertex(&work->bodies_a[0], &work->bodies_b[0], verts, 0);
    for (i = 0; i < 10; i++) verts[i].vy += 0x12C;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget((TARGET *)&work->field_A84[i], &verts[i]);
    }

    s0 = (*(int *)((char *)work + 0x8C8) * 3) >> 2;
    s1 = (*(int *)((char *)work + 0x95C) * 3) >> 2;

    vec.vx = 0; vec.vz = WMDL(0x1C) - s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x8CC), &vec);
    vec.vx = 0; vec.vz = WMDL(0x10) + s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x914), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x960), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x9A8), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0x9F0), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)work + 0xA38), &vec);
}

void s05a_800DACF0(Work *work)
{
    work->copy0 = work->hzd[0].flr[1];
    work->copy1 = work->hzd[1].flr[1];
    work->copy2 = work->hzd[4].flr[1];

    sub_8007E1C0(work->hzd[0].seg, work->hzd[0].flr,
                 (MATRIX *)((char *)work->body.objs + 0xA4), &work->bbox[0], &work->bbox[1]);
    sub_8007E1C0(work->hzd[1].seg, work->hzd[1].flr,
                 (MATRIX *)((char *)work->body.objs + 0x100), &work->bbox[2], &work->bbox[3]);
    sub_8007E1C0(work->hzd[2].seg, work->hzd[2].flr,
                 (MATRIX *)((char *)work->bodies_a[0].objs + 0x48), &work->bbox[4], &work->bbox[5]);
    sub_8007E1C0(work->hzd[3].seg, work->hzd[3].flr,
                 (MATRIX *)((char *)work->bodies_b[0].objs + 0x48), &work->bbox[6], &work->bbox[7]);
    sub_8007E1C0(work->hzd[4].seg, work->hzd[4].flr,
                 (MATRIX *)((char *)work->body.objs + 0x15C), &work->bbox[8], &work->bbox[9]);
}
