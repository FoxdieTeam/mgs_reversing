#include "game/game.h"
#include "libgcl/libgcl.h"

/* ------------------------------------------------------------------ *
 * s05a_800D26CC  --  m1e1 DIRECTOR constructor (GCL config parser)
 * ------------------------------------------------------------------ */

typedef struct _M1e1Dir M1e1Dir;

typedef struct
{
    int         field_0;
    short       field_4;
    signed char field_6;
} GunnerTpl;

struct _M1e1Dir
{
    GV_ACT  actor;          /* 0x000 */
    CONTROL control;        /* 0x020 */
    char    pad_9C[0xB0 - (0x20 + sizeof(CONTROL))];
    int     field_B0;       /* 0x0B0 */
    int     field_B4;       /* 0x0B4 */
    int     field_B8;       /* 0x0B8 */
    char    pad_BC[0xDC - 0xBC];
    OBJECT  body[7];        /* 0x0DC stride 0xE4 */
    TARGET *field_718[10];  /* 0x718 */
    int     field_740;      /* 0x740 */
    int     field_744;      /* 0x744 */
    int     field_748;      /* 0x748 */
    char    pad_74C[0x8AC - 0x74C];
    int     field_8AC;      /* 0x8AC template word */
    short   field_8B0;      /* 0x8B0 template short */
    char    field_8B2;      /* 0x8B2 template byte */
    char    pad_8B3[0x8BC - 0x8B3];
    void   *field_8BC;      /* 0x8BC = &field_8AC */
    char    field_8C0;      /* 0x8C0 */
    char    field_8C1;      /* 0x8C1 */
    char    field_8C2;      /* 0x8C2 */
    char    field_8C3;      /* 0x8C3 */
    char    field_8C4;      /* 0x8C4 */
    char    field_8C5;      /* 0x8C5 */
    char    pad_8C6[0x8C8 - 0x8C6];
    int     field_8C8;      /* 0x8C8 */
    char    pad_8CC[0x8CC - 0x8CC];
    SVECTOR field_8CC;      /* 0x8CC target size */
    char    pad_8D4[0x914 - 0x8D4];
    SVECTOR field_914;      /* 0x914 */
    char    pad_91C[0x95C - 0x91C];
    int     field_95C;      /* 0x95C */
    char    pad_960[0x960 - 0x960];
    SVECTOR field_960;      /* 0x960 */
    char    pad_968[0x9A8 - 0x968];
    SVECTOR field_9A8;      /* 0x9A8 */
    char    pad_9B0[0x9F0 - 0x9B0];
    SVECTOR field_9F0;      /* 0x9F0 */
    char    pad_9F8[0xA38 - 0x9F8];
    SVECTOR field_A38;      /* 0xA38 */
    char    pad_A40[0xA80 - 0xA40];
    int     field_A80;      /* 0xA80 */
    char    pad_A84[0xD54 - 0xA84];   /* target array region 0xA84.. */
    int     field_D54;      /* 0xD54  mode (1 / 6) */
    char    pad_D58[0xD5C - 0xD58];
    int     field_D5C;      /* 0xD5C  'e' block */
    int     field_D60;
    int     field_D64;
    int     field_D68;
    int     field_D6C;
    int     field_D70;      /* 'd' block */
    int     field_D74;
    int     field_D78;
    int     field_D7C;
    int     field_D80;
    int     field_D84;
    int     field_D88;
    int     field_D8C;
    int     field_D90;      /* 's' block */
    int     field_D94;
    int     field_D98;
    int     field_D9C;
    int     field_DA0;
    int     field_DA4;      /* 'g' block */
    int     field_DA8;
    int     field_DAC;
    int     field_DB0;
    int     field_DB4;
    int     field_DB8;      /* 'c' block */
    int     field_DBC;
    int     field_DC0;
    int     field_DC4;
    int     field_DC8;
    short   field_DCC;      /* 0xDCC mov-source svec (DCC,DCE,DD0) */
    short   field_DCE;
    short   field_DD0;
    short   field_DD2;
    short   field_DD4;      /* 0xDD4 turn-source svec (DD4,DD6,DD8) */
    short   field_DD6;
    short   field_DD8;
    short   field_DDA;
    short   field_DDC;
    short   field_DDE;
    short   field_DE0;
    short   field_DE2;
    short   field_DE4;
    short   field_DE6;
    short   field_DE8;
    short   field_DEA;
    int     field_DEC;      /* 'o' block */
    int     field_DF0;
    int     field_DF4;
    int     field_DF8;
    int     field_DFC;
    int     field_E00;
    int     field_E04;      /* 'w' block */
    int     field_E08;
    int     field_E0C;
    int     field_E10;
    int     field_E14;
    int     field_E18;
    int     field_E1C;      /* 'z' block */
    int     field_E20;
    int     field_E24;      /* 's' derived */
    int     field_E28;
    char    pad_E2C[0xE34 - 0xE2C];
    int     field_E34;      /* DG_SetPos2/PutVector derived */
    int     field_E38;
    int     field_E3C;
    char    pad_E40[0xE74 - 0xE40];
    int     field_E74;      /* index a */
    int     field_E78;      /* index b */
    int     field_E7C;      /* 0x3E7 */
    int     field_E80;      /* 0x3E7 */
    int     field_E84;      /* 0x53 */
    char    pad_E88[0xE8C - 0xE88];
    SVECTOR field_E8C;      /* 0xE8C */
    SVECTOR field_E94;      /* 0xE94 */
    char    pad_E9C[0xEDC - 0xE9C];
    void   *field_EDC;      /* 0xEDC throw actor */
    char    pad_EE0[0xF44 - 0xEE0];
    int     field_F44;      /* 0xF44 */
    int     field_F48;      /* 0xF48 */
    char    pad_F4C[0xF8C - 0xF4C];
    short   field_F8C[(0xFEC - 0xF8C) / 2]; /* bbox arrays 0xF8C..0xFE8 */
    char    field_FEC[0x139C - 0xFEC];       /* HZD seg/flr queue area */
};

extern void  s05a_800D4A74(M1e1Dir *work);
extern void  s05a_800D5E30(M1e1Dir *work);
extern void *s05a_800D49F8(int code);

/* throw actor function pointers (s05a overlay locals) */
extern int s05a_800E00EC();
extern int s05a_800E066C();
extern int s05a_800DEDE8();
extern int s05a_800DF834();
extern int s05a_800DF9C8();

extern const char s05a_dword_800E340C[]; /* "m1e1.c" */
extern const char s05a_dword_800E3414[]; /* "m1e1" */
extern const char s05a_dword_800E341C[]; /* "m1e1cl1" */
extern const char s05a_dword_800E3424[]; /* "m1e1cl2" */
extern const char s05a_dword_800E342C[]; /* "m1e1cl3" */
extern const char s05a_dword_800E3434[]; /* "m1e1cr1" */
extern const char s05a_dword_800E343C[]; /* "m1e1cr2" */
extern const char s05a_dword_800E3444[]; /* "m1e1cr3" */
extern const char s05a_dword_800E344C[]; /* "throw" */

/* GUNNER template @ 0x800E3454 (word + short + byte) */
extern const GunnerTpl s05a_dword_800E3454; /* "GUNNER\0" @ 0x800E3454 */

extern M1e1Dir *s05a_dword_800C362C;
extern MATRIX   DG_ZeroMatrix;
extern SVECTOR  DG_ZeroVector;

void *s05a_800D26CC(int a0, int a1)
{
    M1e1Dir *work;
    char    *param;
    SVECTOR  svec;
    int      name;
    int      flag;
    int      s1;

    work = GV_NewActor(5, 0x139C);
    if (work == NULL)
    {
        return 0;
    }

    work->field_740 = 1;
    GV_SetNamedActor(work, s05a_800D4A74, s05a_800D5E30, s05a_dword_800E340C);
    work->field_744 = a0;
    work->field_748 = a1;

    if (GM_InitControl(&work->control, 0, a1) < 0)
    {
        GV_DestroyActor(work);
        return 0;
    }

    work->field_B0 = 0xFF;
    work->field_B4 = 0xFF;
    work->field_B8 = 0xFF;

    /* ---- option 'e' ---- */
    if (GCL_GetOption('e'))
    {
        param = GCL_NextStr();
        if (param) work->field_D5C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) work->field_D60 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) work->field_D64 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) work->field_D68 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) work->field_D6C = GCL_StrToInt(param) / 30;
        if (work->field_D64 > work->field_D5C) work->field_D64 = work->field_D5C;
        if (work->field_D68 > work->field_D60) work->field_D68 = work->field_D60;
    }

    /* ---- option 'd' ---- */
    if (GCL_GetOption('d'))
    {
        work->field_D84 = 1;
        param = GCL_NextStr();
        if (param) work->field_D70 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_D74 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_D78 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_D7C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) work->field_D80 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) work->field_D84 = GCL_StrToInt(param);
        if (work->field_D84 <= 0) work->field_D84 = 1;
        param = GCL_NextStr();
        if (param) work->field_D88 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) work->field_D8C = GCL_StrToInt(param) / 30;
    }

    /* ---- option 's' ---- */
    if (GCL_GetOption('s'))
    {
        param = GCL_NextStr();
        if (param) work->field_D94 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_D90 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_D98 = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        param = GCL_NextStr();
        if (param) work->field_D9C = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        param = GCL_NextStr();
        if (param) work->field_DA0 = GCL_StrToInt(param);
        work->field_E24 = work->field_D94 - work->field_D90;
        work->field_E28 = work->field_D98 - work->field_D9C;
        if (work->field_E28 <= 0) work->field_E28 = 1;
    }

    /* ---- option 'g' ---- */
    if (GCL_GetOption('g'))
    {
        param = GCL_NextStr();
        if (param) work->field_DA4 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DA8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DAC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DB0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DB4 = GCL_StrToInt(param) * 1000000 / 108000;
    }

    /* ---- option 'c' ---- */
    if (GCL_GetOption('c'))
    {
        param = GCL_NextStr();
        if (param) work->field_DB8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DBC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DC0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DC4 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DC8 = GCL_StrToInt(param) * 1000000 / 108000;
    }

    /* ---- option 'p' ---- */
    if (GCL_GetOption('p'))
    {
        param = GCL_NextStr();
        if (param) work->control.mov.vx = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->control.mov.vy = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->control.mov.vz = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->control.turn.vx = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->control.turn.vy = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->control.turn.vz = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param)
        {
            svec.vx = 0;
            svec.vy = 0;
            svec.vz = 0;
            DG_SetPos2(&svec, &work->control.turn);
            svec.vz = GCL_StrToInt(param) * 1000000 / 108000 * 16;
            DG_PutVector(&svec, &svec, 1);
            work->field_E34 = svec.vx;
            work->field_E38 = svec.vy;
            work->field_E3C = svec.vz;
        }
        param = GCL_NextStr();
        if (param) work->field_DD2 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DCC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DCE = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DD0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DDA = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DD4 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DD6 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DD8 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DE2 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DDC = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DDE = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DE0 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DEA = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DE4 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DE6 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) work->field_DE8 = GCL_StrToInt(param) * 4096 / 360;
    }

    /* ---- option 'w' ---- */
    if (GCL_GetOption('w'))
    {
        param = GCL_NextStr();
        if (param) work->field_E04 = GCL_StrToInt(param) * 1000000 / 108000;
        param = GCL_NextStr();
        if (param) work->field_E08 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E0C = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E10 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E14 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E18 = GCL_StrToInt(param);
    }

    /* ---- option 'o' ---- */
    if (GCL_GetOption('o'))
    {
        param = GCL_NextStr();
        if (param) work->field_DEC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DF0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DF4 = GCL_StrToInt(param) * 4096 / 720;
        param = GCL_NextStr();
        if (param) work->field_DF8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_DFC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E00 = GCL_StrToInt(param);
    }
    else
    {
        work->field_DEC = 2;
        work->field_DF0 = 4;
        work->field_DF4 = 0x31C;
        work->field_DF8 = 0x2EE0;
        work->field_DFC = 2;
        work->field_E00 = 1;
    }

    /* ---- option 'z' ---- */
    if (GCL_GetOption('z'))
    {
        work->field_E1C = -1;
        work->field_E20 = -1;
        param = GCL_NextStr();
        if (param) work->field_E1C = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) work->field_E20 = GCL_StrToInt(param);
    }

    work->control.r_sphere = -2;
    work->control.interp = 0;
    GM_ConfigControlAttribute(&work->control, 5);
    /* (interp=0 sinks into the jal delay slot) */

    /* ---- 7 sub-objects ---- */
    name = GV_StrCode(s05a_dword_800E3414);
    GM_InitObject(&work->body[0], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[0]);
    GM_ConfigObjectLight(&work->body[0], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[0].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E341C);
    GM_InitObject(&work->body[1], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[1]);
    GM_ConfigObjectLight(&work->body[1], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[1].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E3424);
    GM_InitObject(&work->body[2], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[2]);
    GM_ConfigObjectLight(&work->body[2], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[2].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E342C);
    GM_InitObject(&work->body[3], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[3]);
    GM_ConfigObjectLight(&work->body[3], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[3].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E3434);
    GM_InitObject(&work->body[4], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[4]);
    GM_ConfigObjectLight(&work->body[4], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[4].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E343C);
    GM_InitObject(&work->body[5], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[5]);
    GM_ConfigObjectLight(&work->body[5], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[5].objs->flag |= 0x80;

    name = GV_StrCode(s05a_dword_800E3444);
    GM_InitObject(&work->body[6], name, 0x2D, 0);
    GM_ConfigObjectJoint(&work->body[6]);
    GM_ConfigObjectLight(&work->body[6], (MATRIX *)&work->pad_9C[0]);
    *(int *)&work->body[6].objs->flag |= 0x80;

    /* ======================= SECTION 1: derived ======================= */
    work->field_E84 = 0x53;
    work->field_F44 = work->field_DA8 >> 1;
    work->field_F48 = work->field_DB8 >> 1;

    work->field_E8C.vx =
        (u_short)work->body[1].objs->objs[0].model->min.vx +
        ((work->body[1].objs->objs[0].model->max.vx -
          work->body[1].objs->objs[0].model->min.vx) / 2);
    work->field_E94.vx =
        (u_short)work->body[4].objs->objs[0].model->min.vx +
        ((work->body[4].objs->objs[0].model->max.vx -
          work->body[4].objs->objs[0].model->min.vx) / 2);
    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&work->field_E8C, &work->field_E8C, 1);
    DG_PutVector(&work->field_E94, &work->field_E94, 1);

    {
        M1e1Dir *w2;
        w2 = (M1e1Dir *)((char *)work + work->field_E74 * sizeof(OBJECT));
        *(int *)&w2->body[1].objs->flag &= ~0x80;
        w2 = (M1e1Dir *)((char *)work + work->field_E78 * sizeof(OBJECT));
        *(int *)&w2->body[4].objs->flag &= ~0x80;
    }

    /* ======================= SECTION 2: throw / D54 ======================= */
    if (work->field_E08 > 0)
    {
        work->field_EDC = s05a_800D49F8(GV_StrCode(s05a_dword_800E344C));
        flag = 0x150;
        work->field_D54 = 1;
        GM_lpfnPlayerActControl = (TPlayerActFunction)s05a_800E00EC;
        GM_lpfnPlayerActObject2 = (TPlayerActFunction)s05a_800E066C;
        GM_lpfnBombHoming       = (TBombFunction)s05a_800DEDE8;
        GM_lpfnBombBound        = (TBombFunction2)s05a_800DF834;
        GM_lpfnBombExplosion    = (TBombFunction3)s05a_800DF9C8;
    }
    else
    {
        work->field_D54 = 6;
        if (work->field_DD2) work->control.mov = *(SVECTOR *)&work->field_DCC;
        if (work->field_DDA) work->control.turn = *(SVECTOR *)&work->field_DD4;
        if (work->field_DE2)
        {
            work->body[0].rots[3].vy = work->field_DDE;
            work->body[0].rots[5].vx = work->field_DDC;
            work->body[0].rots[11].vx = work->field_DE8;
        }
        if (work->field_DEA)
        {
            short t;
            t = (svec.vy = work->field_DE6);
            if (t < -0xE3) { svec.vy = t; t = -0xE3; }
            svec.vy = t;
            if (t >= 0xE4) t = 0xE3;
            svec.vy = t;
            work->body[0].rots[13].vy = t;
            t = work->field_DE6 - svec.vy;
            svec.vy = t;
            if (t < -0x155) t = -0x155;
            svec.vy = t;
            if (t >= 0x71D) t = 0x71C;
            svec.vy = t;
            work->body[0].rots[12].vy = t;
            work->body[0].rots[13].vx = work->field_DE4;
        }
        flag = 0x100;
    }

    /* ======================= SECTION 3: bbox-copy 0xF8C..0xFE8 ======================= */
    work->field_F8C[0] = work->body[0].objs->objs[0].model->min.vx; /* F8C */
    work->field_F8C[1] = work->body[0].objs->objs[0].model->min.vy; /* F8E */
    work->field_F8C[2] = work->body[0].objs->objs[0].model->min.vz; /* F90 */
    work->field_F8C[4] = work->body[0].objs->objs[0].model->max.vx; /* F94 */
    work->field_F8C[5] = work->body[0].objs->objs[0].model->max.vy; /* F96 */
    work->field_F8C[6] = work->body[0].objs->objs[0].model->max.vz; /* F98 */
    if (work->field_F8C[1] < 0x258) work->field_F8C[1] = 0x258;
    if (work->field_F8C[5] < work->field_F8C[1]) work->field_F8C[5] = work->field_F8C[1];

    work->field_F8C[8]  = work->body[0].objs->objs[2].model->min.vx; /* F9C */
    work->field_F8C[9]  = work->body[0].objs->objs[2].model->min.vy; /* F9E */
    work->field_F8C[10] = work->body[0].objs->objs[2].model->min.vz; /* FA0 */
    work->field_F8C[12] = work->body[0].objs->objs[2].model->max.vx; /* FA4 */
    work->field_F8C[13] = work->body[0].objs->objs[2].model->max.vy; /* FA6 */
    work->field_F8C[14] = work->body[0].objs->objs[2].model->max.vz; /* FA8 */
    if (work->field_F8C[9] < 0x258) work->field_F8C[9] = 0x258;
    if (work->field_F8C[13] < work->field_F8C[9]) work->field_F8C[13] = work->field_F8C[9];

    work->field_F8C[16] = work->body[1].objs->objs[0].model->min.vx; /* FAC */
    work->field_F8C[17] = work->body[1].objs->objs[0].model->min.vy; /* FAE */
    work->field_F8C[18] = work->body[1].objs->objs[0].model->min.vz; /* FB0 */
    work->field_F8C[20] = work->body[1].objs->objs[0].model->max.vx; /* FB4 */
    work->field_F8C[21] = work->body[1].objs->objs[0].model->max.vy; /* FB6 */
    work->field_F8C[22] = work->body[1].objs->objs[0].model->max.vz; /* FB8 */
    if (work->field_F8C[17] < 0x258) work->field_F8C[17] = 0x258;
    if (work->field_F8C[21] < work->field_F8C[17]) work->field_F8C[21] = work->field_F8C[17];

    work->field_F8C[24] = work->body[4].objs->objs[0].model->min.vx; /* FBC */
    work->field_F8C[25] = work->body[4].objs->objs[0].model->min.vy; /* FBE */
    work->field_F8C[26] = work->body[4].objs->objs[0].model->min.vz; /* FC0 */
    work->field_F8C[28] = work->body[4].objs->objs[0].model->max.vx; /* FC4 */
    work->field_F8C[29] = work->body[4].objs->objs[0].model->max.vy; /* FC6 */
    work->field_F8C[30] = work->body[4].objs->objs[0].model->max.vz; /* FC8 */
    if (work->field_F8C[25] < 0x258) work->field_F8C[25] = 0x258;
    if (work->field_F8C[29] < work->field_F8C[25]) work->field_F8C[29] = work->field_F8C[25];

    work->field_F8C[32] = work->body[0].objs->objs[4].model->min.vx + 0xC8;  /* FCC */
    work->field_F8C[33] = work->body[0].objs->objs[4].model->min.vy;          /* FCE */
    work->field_F8C[34] = work->body[0].objs->objs[4].model->min.vz;          /* FD0 */
    work->field_F8C[36] = work->body[0].objs->objs[4].model->max.vx - 0xC8;  /* FD4 */
    work->field_F8C[37] = work->body[0].objs->objs[4].model->max.vy;          /* FD6 */
    work->field_F8C[38] = work->body[0].objs->objs[4].model->max.vz - 0x2BC; /* FD8 */

    work->field_F8C[41] = work->body[0].objs->objs[5].model->min.vy - 0x1F4; /* FDE */
    work->field_F8C[42] = work->body[0].objs->objs[5].model->min.vz;          /* FE0 */
    work->field_F8C[44] = work->body[0].objs->objs[5].model->max.vx;          /* FE4 */
    work->field_F8C[45] = work->body[0].objs->objs[5].model->max.vy + 0x12C; /* FE6 */
    work->field_F8C[46] = work->body[0].objs->objs[5].model->max.vz - 0x12C; /* FE8 */
    work->field_F8C[40] = -work->field_F8C[44];                                /* FDC */

    if (work->field_D54 == 6)
    {
        work->field_F8C[1]  = 0;
        work->field_F8C[9]  = 0;
        work->field_F8C[17] = 0;
        work->field_F8C[25] = 0;
        work->field_F8C[41] = 0;
    }

    /* ======================= SECTION 4: HZD queue (unrolled) ======================= */
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x000], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x010], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x020], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x030], flag);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x040]);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x070]);

    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x0A0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x0B0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x0C0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x0D0], flag);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x0E0]);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x110]);

    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x140], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x150], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x160], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x170], flag);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x180]);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x1B0]);

    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x1E0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x1F0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x200], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x210], flag);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x220]);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x250]);

    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x280], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x290], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x2A0], flag);
    HZD_QueueDynamicSegment2(work->control.map->hzd, (HZD_SEG *)&work->field_FEC[0x2B0], flag);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x2C0]);
    HZD_QueueDynamicFloor(work->control.map->hzd, (HZD_FLR *)&work->field_FEC[0x2F0]);

    /* ======================= SECTION 6: matrix loop ======================= */
    for (s1 = 0; s1 < 8; s1++)
    {
        MATRIX *base_m = (MATRIX *)((char *)work->body[0].objs + s1 * 0x5c + 0x48);
        *base_m = DG_ZeroMatrix;
    }

    s05a_dword_800C362C = work;
    work->control.rot.vx = work->control.turn.vx;
    work->control.rot.vy = work->control.turn.vy;
    work->control.rot.vz = work->control.turn.vz;

    if (work->field_D54 == 6)
    {
        return work;
    }

    {
        /* ======================= SECTION 5: targets ======================= */
        char    *q;
        int      off2;

        work->field_E7C = 0x3E7;
        work->field_E80 = 0x3E7;
        work->field_A80 =
            (work->body[1].objs->objs[0].model->max.vx -
             work->body[1].objs->objs[0].model->min.vx) / 3;

        s1 = 0;
        svec.vx = (u_short)work->field_A80;
        svec.vz = (u_short)work->field_A80;
        svec.vy = 0x258;
        do
        {
            TARGET *t = GM_AllocTarget();
            work->field_718[s1] = t;
            GM_SetTarget(t, 0xC, 2, &svec);
            GM_SetPowerTarget(work->field_718[s1], 1, -1, 0x2710, 0, &DG_ZeroVector);
            s1 += 1;
        } while (s1 < 10);

        svec.vy = 0x32;
        s1 = 0;
        {
            SVECTOR *zv = &DG_ZeroVector;
            off2 = 0xA84;
            do
            {
                q = (char *)work + off2;
                GM_SetTarget((TARGET *)q, 4, 2, &svec);
                GM_SetPowerTarget((TARGET *)q, 1, 2, work->field_DA0, 0, zv);
                off2 += 0x48;
                s1 += 1;
            } while (s1 < 10);
        }

        work->field_8C8 =
            (work->body[0].objs->objs[0].model->max.vx -
             work->body[0].objs->objs[0].model->min.vx) / 3;
        work->field_95C =
            (work->body[0].objs->objs[0].model->max.vx -
             work->body[0].objs->objs[0].model->min.vx) >> 2;
        svec.vx = (u_short)work->field_8C8;
        svec.vz = (u_short)work->field_8C8;
        svec.vy =
            (work->body[0].objs->objs[0].model->max.vy -
             work->body[0].objs->objs[0].model->min.vy) / 6;
        GM_SetTarget((TARGET *)&work->field_8CC, 4, 2, &svec);
        GM_SetTarget((TARGET *)&work->field_914, 4, 2, &svec);
        svec.vx = (u_short)work->field_95C;
        svec.vz = (u_short)work->field_95C;
        GM_SetTarget((TARGET *)&work->field_960, 4, 2, &svec);
        GM_SetTarget((TARGET *)&work->field_9A8, 4, 2, &svec);
        GM_SetTarget((TARGET *)&work->field_9F0, 4, 2, &svec);
        GM_SetTarget((TARGET *)&work->field_A38, 4, 2, &svec);
        GM_SetPowerTarget((TARGET *)&work->field_8CC, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget((TARGET *)&work->field_914, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget((TARGET *)&work->field_960, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget((TARGET *)&work->field_9A8, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget((TARGET *)&work->field_9F0, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget((TARGET *)&work->field_A38, 1, 2, 0, 0, &DG_ZeroVector);

        /* ======================= SECTION 7: GUNNER tail ======================= */
        memcpy(&work->field_8AC, &s05a_dword_800E3454, 7);
        work->field_8BC = &work->field_8AC;
        work->field_8C0 = 0x10;
        work->field_8C1 = 0x6F;
        work->field_8C2 = (char)0x9F;
        work->field_8C3 = 0x1F;
        work->field_8C4 = (char)0xDF;
        work->field_8C5 = 0x7F;
    }

    return work;
}
