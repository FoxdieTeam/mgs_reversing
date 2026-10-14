#include "mgstype.h"
#include "anime/animconv/anime.h"
#include "okajima/blood.h"
#include "bullet/blast.h"
#include "okajima/bullet.h"
#include "okajima/plasma.h"
#include "okajima/spark.h"
#include "enemy/katana.h"
#include "equip/equip.h"
#include "takabe/cinema.h"
#include "chara/snake/sna_init.h"
#include "game/game.h"
#include "game/jimctrl.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "mts/mts.h" // for fprintf
#include "charadef.h"

#include <stdio.h>

struct _Work;
typedef void (*NinjaFunc)(struct _Work *);

typedef struct _NinjaRoute
{
    u_char      key;
    signed char opts[3];
} NinjaRoute;
typedef void (*NinjaAction)(struct _Work *, int);

typedef struct _NinjaClone
{
    int     field_0;
    SVECTOR field_4[32];
} NinjaClone;

typedef struct _Work
{
    GV_ACT         actor;       /* 0x000 */
    CONTROL        control;     /* 0x020 */
    OBJECT         body;        /* 0x09C */
    MOTION_CONTROL m_ctrl;      /* 0x180 */
    MOTION_SEGMENT m_segs1[17]; /* 0x1D0 */
    MOTION_SEGMENT m_segs2[17]; /* 0x434 */
    SVECTOR        rots[16];    /* 0x698 */
    SVECTOR        adjust[16];  /* 0x718 */
    MATRIX         light[2];    /* 0x798 */
    int            field_7D8;   /* 0x7D8 */
    OBJECT         weapon;      /* 0x7DC */
    int            field_8C0;   /* 0x8C0 */
    TARGET        *target;      /* 0x8C4 */

    char      pad_910[0x910 - 0x8C4 - sizeof(TARGET *)];
    HOMING   *field_910;   /* 0x910 */
    int        field_914;   /* 0x914 */
    SVECTOR    field_918;   /* 0x918 */
    NinjaClone clones[16];  /* 0x920 */
    short      field_1960;  /* 0x1960 */
    char       pad_1962[2];
    short      field_1964;  /* 0x1964 */
    short      field_1966;  /* 0x1966 */
    SVECTOR   field_1968;  /* 0x1968 */
    int       field_1970;  /* 0x1970 */
    int       field_1974;  // 0x1974
    int       field_1978;  // 0x1978
    int       field_197C;  // 0x197C
    SVECTOR   field_1980;  // 0x1980
    int       field_1988;  // 0x1988
    SVECTOR   field_198C;  // 0x198C
    NinjaAction field_1994; /* 0x1994 */
    NinjaAction field_1998; /* 0x1998 */
    int       field_199C;  /* 0x199C */
    int       field_19A0;  /* 0x19A0 */
    int       field_19A4;  /* 0x19A4 */
    int       field_19A8;  /* 0x19A8 */
    int       field_19AC;  /* 0x19AC */
    int       field_19B0;  /* 0x19B0 */
    int       field_19B4;  /* 0x19B4 */
    int       field_19B8;  /* 0x19B8 */
    GV_ACT   *field_19BC;  /* 0x19BC */
    int       field_19C0;  /* 0x19C0 */
    int       field_19C4;  /* 0x19C4 */
    int       field_19C8;  /* 0x19C8 */
    int       field_19CC;  /* 0x19CC */
    int       field_19D0;  /* 0x19D0 */
    int       field_19D4;  /* 0x19D4 */
    int       field_19D8;  /* 0x19D8 */
    int       field_19DC;  /* 0x19DC */
    int       field_19E0;  /* 0x19E0 */
    int       field_19E4;  /* 0x19E4 */
    char      pad_19E8[4];
    int       field_19EC;  /* 0x19EC */
    int       field_19F0;  /* 0x19F0 */
    int       field_19F4;  /* 0x19F4 */
    int       field_19F8;  /* 0x19F8 */
    int       field_19FC;  /* 0x19FC */
    int       field_1A00;  /* 0x1A00 */
    int       field_1A04;  /* 0x1A04 */
    int       field_1A08;  /* 0x1A08 */
    int       field_1A0C;  /* 0x1A0C */
    int       field_1A10;  /* 0x1A10 */
    int       field_1A14;  /* 0x1A14 */
    GV_ACT   *field_1A18;  /* 0x1A18 */
    GV_ACT   *field_1A1C;  /* 0x1A1C */
    void     *field_1A20;  /* 0x1A20 */
    void     *field_1A24;  /* 0x1A24 */
    int       field_1A28;     // 0x1A28
    int       field_1A2C;     // 0x1A2C
    char      pad_1A30[0x4]; /* 0x1A28 */
    int       field_1A34;     /* 0x1A34 */
    int       field_1A38;     /* 0x1A38 */
    int       field_1A3C;  /* 0x1A3C */
    NinjaFunc field_1A40[8];  /* 0x1A40 */
    SVECTOR   shadow_verts[4]; /* 0x1A60 */
    DG_PRIM  *field_1A80;  /* 0x1A80 */
    SVECTOR   field_1A84;  /* 0x1A84 */
    int       field_1A8C;  /* 0x1A8C */
    int       field_1A90;  /* 0x1A90 */
    int       field_1A94;  /* 0x1A94 */
    int       field_1A98[0x23]; /* 0x1A98 */
    short     field_1B24;  /* 0x1B24 */
    short     field_1B26;  /* 0x1B26 */
    short     field_1B28;  /* 0x1B28 */
    char      pad_1B2A[2];
    u_char    damage[6];   /* 0x1B2C */
    char      pad_1B32[2];
} Work;

/* forward declarations for helpers called by the migrated functions */
extern int   s08b_bunsin2_800C9978(OBJECT *body);
extern void  s08b_bunsin2_800CDE74(Work *work);
extern void  s08b_bunsin2_800CE0A4(Work *work);
extern void  s08b_bunsin2_800CE180(Work *work);
extern int   s08b_bunsin2_800CE584(Work *work);
extern void  s08b_bunsin2_800CE800(Work *work, int arg);
extern int   s08b_bunsin2_800CE8A0(Work *work);
extern void  s08b_bunsin2_800CEFF4(Work *work);
extern void  s08b_bunsin2_800CEB40(Work *work);
extern int   s08b_bunsin2_800CF150(Work *work);
extern int   s08b_bunsin2_800CF354(Work *work);
extern void  s08b_bunsin2_800CF660(Work *work);
extern int   s08b_bunsin2_800CFB98(Work *work);
extern int   s08b_bunsin2_800D0078(Work *work);
extern int   s08b_bunsin2_800D0550(Work *work);
extern void  s08b_bunsin2_800D0B4C(Work *work);
extern void  s08b_bunsin2_800D1F9C(Work *work);
extern void  s08b_bunsin2_800D2BFC(Work *work);
extern void  s08b_bunsin2_800D401C(Work *work);
extern void  s08b_bunsin2_800D452C(Work *work);
extern void  s08b_bunsin2_800D4FBC(MATRIX *world, int type);
extern void  s08b_bunsin2_800D53E8(int a0, int a1);
extern void  s08b_bunsin2_800D5434(void);
extern void *s08b_p_sphere_800D9834(void *a, void *b);
extern int   okajima_CHAF_LIFE;
extern int     s08b_dword_800C3440;
extern int     s08b_dword_800C3444;
extern int     s08b_dword_800C3448;
extern int     s08b_dword_800C344C;
extern int     s08b_dword_800C3450;
extern SVECTOR s08b_dword_800C3460[];
extern SVECTOR s08b_dword_800C3568[];
extern NinjaRoute s08b_dword_800C3518[20];
extern SVECTOR s08b_dword_800C3490[];
extern SVECTOR s08b_dword_800C34B0[];
extern SVECTOR s08b_dword_800C34D0[];
extern SVECTOR s08b_dword_800C34F8[];
extern int     s08b_dword_800C3588;

extern NEWCHARA s08c_800C4194;
extern SVECTOR s08b_dword_800C33F0;
extern SVECTOR s08b_dword_800C33F8;
extern SVECTOR s08b_dword_800C3400;
extern SVECTOR s08b_dword_800C3408;
extern SVECTOR s08b_dword_800C3410;
extern SVECTOR s08b_dword_800C3430;
extern int     s08b_dword_800C3438;
extern short   s08b_dword_800C33A0[];
extern int     s08b_dword_800C3380;
extern int     s08b_dword_800C338C;
extern int     s08b_dword_800C3390;
extern int     s08b_dword_800C3398;
extern void   *s08b_dword_800C3418[];
extern int     s08b_dword_800C343C;
extern int     s08b_dword_800C3454;
extern SVECTOR s08b_dword_800C3458;
extern short   s08b_dword_800C3510[];
extern SVECTOR s08b_dword_800C358C;
extern int     s08b_dword_800C3594;
extern int     s08b_dword_800C3614;
extern int     s08b_dword_800C3618;

extern BLAST_DATA blast_data_8009F4B8[8]; // in bullet/blast.c
extern CONTROL *s08b_dword_800E4314;
extern int     *s08b_dword_800E4318;
extern Work    *s08b_dword_800E431C;
extern int   s08b_dword_800E4320;
extern int   s08b_dword_800E4324;
extern int   s08b_dword_800E4334[];
extern int   s08b_dword_800E4338;
extern int   s08b_dword_800E433C;
extern int   s08b_dword_800E4340;

extern char s08b_aErrerrerrsoundbuffover_800E3764[];
extern char s08b_aNinjac_800E37F8[];
extern char s08b_aWeaponxxamodexx_800E3878[];
extern char s08b_aJumpfctrlturnvyd_800E3920[];
extern char s08b_aDcountd_800E39B8[];
extern char s08b_aPunchdamagelifedcombod_800E393C[];
extern char s08b_aNjafist_800E3740[];
extern char s08b_aNjab_800E374C[];
extern char s08b_aKatana_800E3754[];
extern char s08b_aShadow_800E375C[];
extern char s08b_aKorekorekor_800E39A8[];

int  s08b_bunsin2_800C9120(Work *work);
int  s08b_bunsin2_800C9548(Work *work);
int  s08b_bunsin2_800C9588(Work *work, int arg);
void s08b_bunsin2_800C9B38(Work *work, int first);
void s08b_bunsin2_800C9C74(Work *work, int first);
void s08b_bunsin2_800CC578(Work *work, int time);
void s08b_bunsin2_800CC71C(Work *work, int time);
void s08b_bunsin2_800CC7EC(Work *work, int time);
void s08b_bunsin2_800CC90C(Work *work, int time);
void s08b_bunsin2_800CCAF0(Work *work, int time);
void s08b_bunsin2_800CD544(Work *work, int index);
GV_ACT *Bunsin2_800C8F04(int name, int map, CONTROL *control, int type);
int  s08b_bunsin2_800CD914(Work *work, int index);
void s08b_bunsin2_800CD2E8(Work *work);
int  s08b_bunsin2_800CD298(int a, int b, int c);
int  s08b_bunsin2_800CD2C0(int a, int b, int c);
int  s08b_bunsin2_800CD95C(Work *work, void *func);
void *NewBunsin2(OBJECT *root_obj, int arg1, int *arg2);
void *NewTenmetu(MATRIX *world, int *force);
void NewWindcrcl_800CF784(MATRIX *world, int arg1, int arg2, int arg3, int time);
void s08b_bunsin2_800CDB10(Work *work);
void s08b_bunsin2_800D4ED0(Work *work);

void s08b_ninja_800C800C(void);
void s08b_ninja_800C7914(short *a, short *b, short *out)
{
    int i;

    for (i = 0; i < 3; i++, a++, b++, out++)
    {
        int d = *a - *b;
        if (d != (short)d)
        {
            d = (d < 0) ? 0x8000 : 0x7FFF;
        }
        *out = d;
    }
}

void s08b_ninja_800C796C(short *a, short *b)
{
    a[0] = GV_NearRange(a[0], b[0], 0xFA);
    a[1] = GV_NearRange(a[1], b[1], 0x64);
    a[2] = GV_NearRange(a[2], b[2], 0xFA);
}

void s08b_ninja_800C79D4(int a0)
{
    *s08b_dword_800E4318 = a0;
    s08b_dword_800E4320 = 0;
}

void s08b_ninja_800C79F0(void)
{
    GM_Camera.type = 0;
    GM_Camera.position.vx = -0x1ABB;
    GM_Camera.position.vy = 0x4A9;
    GM_Camera.position.vz = -0x2A3;
    GM_Camera.target.vx = -0x1EFF;
    GM_Camera.target.vy = 0x4A9;
    GM_Camera.target.vz = -0xAED;
    s08b_dword_800E4320++;
}

int s08b_ninja_800C7A3C(void)
{
    int ret = 1;

    if (s08b_dword_800E4320 < 0x1F)
    {
        GM_Camera.rotate.vx = 0x280;
        GM_Camera.rotate.vy = 0x800;
        GM_Camera.rotate.vz = 0;
        GM_Camera.track = 0x1F40;
        GM_Camera.target = s08b_dword_800E431C->field_1968;
        if (s08b_dword_800E431C->field_1968.vx >= -0x7CF)
        {
            s08b_dword_800E4324 = 0;
        }
        else
        {
            s08b_dword_800E4324 = 1;
        }
    }
    else
    {
        GM_Camera.type = 0;
        if (s08b_dword_800E4324 == 0)
        {
            GM_Camera.position.vx = 0x960;
            GM_Camera.position.vy = 0x25F;
            GM_Camera.position.vz = -0x23F;
            GM_Camera.target.vx = 0x10C9;
            GM_Camera.target.vy = 0x8FB;
            GM_Camera.target.vz = -0x1FDC;
        }
        else
        {
            GM_Camera.position.vx = -0x10DB;
            GM_Camera.position.vy = 0x2A8;
            GM_Camera.position.vz = 0x4D;
            GM_Camera.target.vx = -0x20DF;
            GM_Camera.target.vy = 0x950;
            GM_Camera.target.vz = -0x19AE;
        }
        ret = 0;
    }
    s08b_dword_800E4320++;
    return ret;
}

void s08b_ninja_800C7B68(void)
{
    GM_Camera.track = 0x1F40;
    GM_Camera.target = s08b_dword_800E431C->field_1968;
    GM_Camera.rotate.vx = 0x280;
    GM_Camera.rotate.vy = 0x800;
    GM_Camera.rotate.vz = 0;
    s08b_dword_800E4320++;
}

int s08b_ninja_800C7BC8(void)
{
    int ret = 1;

    if (s08b_dword_800E4320 < 0x1F)
    {
        GM_Camera.rotate.vx = 0x280;
        GM_Camera.rotate.vy = 0x800;
        GM_Camera.rotate.vz = 0;
        GM_Camera.track = 0x1F40;
        GM_Camera.target = s08b_dword_800E431C->field_1968;
        if (s08b_dword_800E431C->field_1968.vx >= -0x7CF)
        {
            s08b_dword_800E4324 = 0;
        }
        else
        {
            s08b_dword_800E4324 = 1;
        }
    }
    else
    {
        GM_Camera.type = 0;
        if (s08b_dword_800E4324 == 0)
        {
            GM_Camera.position.vx = 0x71F;
            GM_Camera.position.vy = 0x340;
            GM_Camera.position.vz = -0x43B;
            GM_Camera.target.vx = 0x9BF;
            GM_Camera.target.vy = 0x3F7;
            GM_Camera.target.vz = -0x784;
        }
        else
        {
            GM_Camera.position.vx = -0x12F8;
            GM_Camera.position.vy = 0x22F;
            GM_Camera.position.vz = 0xE5;
            GM_Camera.target.vx = -0x18A0;
            GM_Camera.target.vy = 0x8AE;
            GM_Camera.target.vz = -0x130E;
        }
        ret = 0;
    }
    s08b_dword_800E4320++;
    return ret;
}

int s08b_ninja_800C7CF4(void)
{
    int ret = 1;

    if (s08b_dword_800E4320 < 0x3D)
    {
        GM_Camera.rotate.vx = 0x280;
        GM_Camera.rotate.vy = 0x800;
        GM_Camera.rotate.vz = 0;
        GM_Camera.track = 0x1F40;
        GM_Camera.target = s08b_dword_800E431C->field_1968;
    }
    if (s08b_dword_800E4320 >= 0x2E)
    {
        GM_Camera.type = 0;
        if (s08b_dword_800E431C->field_1968.vx >= -0x7CF)
        {
            GM_Camera.position.vx = 0x8EC;
            GM_Camera.position.vy = 0x96;
            GM_Camera.position.vz = -0x3D0;
            GM_Camera.target.vx = 0x920;
            GM_Camera.target.vy = 0xAD;
            GM_Camera.target.vz = -0x41F;
        }
        else
        {
            GM_Camera.position.vx = -0x1857;
            GM_Camera.position.vy = 0x75;
            GM_Camera.position.vz = -0x83;
            GM_Camera.target.vx = 0x73;
            GM_Camera.target.vy = 0xB39;
            GM_Camera.target.vz = -0x2066;
        }
        ret = 0;
    }
    s08b_dword_800E4320++;
    return ret;
}

void s08b_ninja_800C7E14(void)
{
    SVECTOR vec;

    vec = GM_Camera.target;
    s08b_ninja_800C796C((short *)&vec, (short *)&GM_PlayerPosition);
    GV_NearExp4V(&GM_Camera.target, &vec, 3);
    GM_Camera.rotate.vx = 0x280;
    GM_Camera.rotate.vy = GV_NearExp2(GM_Camera.rotate.vy, 0x800);
    GM_Camera.rotate.vz = 0;
    GM_Camera.track = GV_NearExp2(GM_Camera.track, 0xFA0);
    if (s08b_dword_800E4320 >= 0x40)
    {
        s08b_ninja_800C79D4(2);
    }
    else
    {
        s08b_dword_800E4320++;
    }
}

void s08b_ninja_800C7ED8(void)
{
    SVECTOR vec;

    vec = GM_Camera.target;
    s08b_ninja_800C796C((short *)&vec, (short *)&GM_PlayerPosition);
    GV_NearExp4V(&GM_Camera.target, &vec, 3);
    GM_Camera.track = 0x1F40;
    GM_Camera.rotate.vx = 0x280;
    GM_Camera.rotate.vy = 0x800;
    GM_Camera.rotate.vz = 0;
    s08b_dword_800E4320++;
}

void s08b_ninja_800C7F74(void)
{
    GV_NearExp8V(&GM_Camera.target, &GM_PlayerPosition, 3);
    GM_Camera.rotate.vx = GV_NearExp4(GM_Camera.rotate.vx, 0x280);
    GM_Camera.rotate.vy = GV_NearExp4(GM_Camera.rotate.vy, 0x800);
    GM_Camera.rotate.vz = 0;
    GM_Camera.track = GV_NearExp2(GM_Camera.track, 0x1F40);
    if (s08b_dword_800E4320 >= 0x20)
    {
        s08b_ninja_800C79D4(1);
    }
    else
    {
        s08b_dword_800E4320++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C800C.s")

void s08b_ninja_800C811C(Work *work)
{
    TARGET *target = work->target;

    if (target->damaged & 8)
    {
        GV_AddVec3(&target->offset, &work->control.step, &work->control.step);
        target->damaged &= 0xFFF7;
    }
}

int s08b_ninja_800C8170(void)
{
    HZD_EVT *evt = &GM_PlayerControl->evt;
    int      i;

    for (i = 0; i < evt->n_inside; i++)
    {
        if (evt->inside[i] == 0xFFC0)
        {
            return 1;
        }
    }

    return 0;
}

void s08b_ninja_800C81C8(Work *work)
{
    if (work->field_1B24 == 0)
    {
        if (s08b_ninja_800C8170() && (GM_PlayerStatus & PLAYER_CHECK_WALL) &&
            GM_NoisePower == 0x64)
        {
            work->field_1B24 = 0x5A;
        }
    }
    else if (work->field_1B24 == 0x4B)
    {
        GM_SeSet((SVECTOR *)&work->control, 0x8F);
    }

    work->field_1B24--;
    if (work->field_1B24 < 0)
    {
        work->field_1B24 = 0;
    }
}

void s08b_ninja_800C8264(Work *work) // Act
{
    CONTROL *c = &work->control;

    s08b_ninja_800C811C(work);

    GM_ActControl(c);
    GM_ActObject2(&work->body);

    DG_GetLightMatrix2((SVECTOR *)c, work->light);

    s08b_bunsin2_800CDB10(work);

    if (work->field_7D8 == 0)
    {
        GM_MoveTarget(work->target, (SVECTOR *)&work->control);
        GM_PushTarget(work->target);
    }

    work->field_19D8++;

    if (work->field_7D8 == 0)
    {
        if (work->field_19E4 < 0)
        {
            work->field_19E4 = 0;
        }

        if (work->field_19E4 < s08b_dword_800C338C)
        {
            s08b_dword_800C338C--;
        }

        MENU_DrawBar(16, 28, s08b_dword_800C338C << 2, work->field_19E4 << 2, (MENU_BAR_CONF *)&s08b_dword_800C3380);
    }

    s08b_ninja_800C81C8(work);
}

void s08b_ninja_800C8354(Work *work)
{
    TARGET *t = work->target;

    GM_SetTarget(t, 0x1F, 2, (SVECTOR *)&s08b_dword_800C3390);
    GM_SetPowerTarget(t, 1, -1, 0xFF, 0xFF, (SVECTOR *)&s08b_dword_800C3398);
    GM_SetCaptureTarget(t, -1, 0xFF, (int *)0, (SVECTOR *)0);
}

int s08b_ninja_800C83CC(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    OBJECT  *weapon;
    MATRIX  *light;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlAttribute(control, 5);
    control->seg_flag = 2;
    GM_ConfigControlInterp(control, 4);

    body = &work->body;
    GM_InitObject(body, GV_StrCode(s08b_aNjafist_800E3740), 0x32D, GV_StrCode(s08b_aNjab_800E374C));
    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, GV_StrCode(s08b_aNjab_800E374C), work->m_segs1, work->m_segs2,
                           control, work->rots);
    light = work->light;
    GM_ConfigObjectLight(body, light);

    weapon = &work->weapon;
    GM_InitObject(weapon, GV_StrCode(s08b_aKatana_800E3754), 0x6D, 0);
    GM_ConfigObjectLight(weapon, light);
    GM_ConfigObjectRoot(weapon, body, 4);

    work->field_1A20 = NewBunsin2(body, 4, &work->field_19FC);
    work->field_1A24 = NewBunsin2(body, 8, &work->field_19FC);
    work->field_19FC = 0;
    return 0;
}

int s08b_ninja_800C8558(Work *work)
{
    HZD_DEF    *def;
    HZD_PAT    *route;
    NinjaClone *clone;
    HZD_PTP    *points;
    int         n_routes;
    int         i, j;

    def = work->control.map->hzd->def;
    n_routes = def->n_routes;
    route = def->routes;
    clone = work->clones;

    if (n_routes >= 17)
    {
        return -1;
    }

    work->field_1960 = n_routes;

    for (i = 0; i < n_routes; i++)
    {
        clone->field_0 = route->n_points;
        if ((unsigned int)(clone->field_0 - 1) >= 32)
        {
            return -1;
        }

        points = route->points;
        for (j = 0; j < clone->field_0; j++)
        {
            clone->field_4[j].vx = points->x;
            clone->field_4[j].vy = points->y;
            clone->field_4[j].vz = points->z;
            clone->field_4[j].pad = points->command;
            points++;
        }

        clone++;
        route++;
    }

    return 0;
}
int s08b_ninja_800C8624(Work *work)
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *poly;
    SVECTOR  *v0, *v1, *v2, *v3;
    int       i;

    v0 = &work->shadow_verts[0];
    v1 = &work->shadow_verts[1];
    v2 = &work->shadow_verts[2];
    v3 = &work->shadow_verts[3];
    v0->vx = -500;
    v0->vy = 0;
    v0->vz = -500;
    v1->vx = 500;
    v1->vy = 0;
    v1->vz = -500;
    v2->vx = -500;
    v2->vy = 0;
    v2->vz = 500;
    v3->vx = 500;
    v3->vy = 0;
    v3->vz = 500;

    prim = GM_MakePrim(0x12, 1, v0, NULL);
    work->field_1A80 = prim;
    if (prim == NULL)
    {
        return -1;
    }

    tex = DG_GetTexture(GV_StrCode(s08b_aShadow_800E375C));
    if (tex == NULL)
    {
        return -1;
    }

    for (i = 0; i < 2; i++)
    {
        poly = prim->packs[i];
        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 0x34, 0x34, 0x34);
        DG_SetPacketTexture4(poly, tex);
    }

    s08b_bunsin2_800CD914(work, 2);
    return 0;
}

void s08b_ninja_800C8798(Work *work) // Die
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_ResetHomingTarget(work->field_910);
    GV_DestroyActorQuick(work->field_1A20);
    GV_DestroyActorQuick(work->field_1A24);

    if (work->field_19BC != NULL)
    {
        GV_DestroyActorQuick(work->field_19BC);
    }

    if (work->field_7D8 == 0)
    {
        GM_FreeTarget(work->target);
        GM_FreePrim(work->field_1A80);
    }
}

void s08b_ninja_800C8848(Work *work)
{
    s08b_dword_800E4314 = &work->control;
    s08b_dword_800E4318 = &work->field_19EC;
    s08b_dword_800E431C = work;
    s08b_dword_800E4320 = 0;

    GM_SetCameraCallbackFunc(1, s08b_ninja_800C800C);

    GM_Camera.interp_mode = 2;
    GM_Camera.interp = 0;
    GM_Camera.rotate.vx = 0x280;
    GM_Camera.rotate.vz = 0;
    GM_Camera.rotate.vy = 0x800;
    GM_Camera.type = 0;
    GM_Camera.track = 0xFA0;
    GM_Camera.bound[1][0].vx = -0x227E;
    GM_Camera.flag |= 2;
    GM_Camera.bound[1][0].vy = -0x7530;
    GM_Camera.bound[1][0].vz = -0x7530;
    GM_Camera.bound[0][0].vx = 0x1013;
    GM_Camera.limit[1][0].vx = -0x227E;
    GM_Camera.limit[1][0].vy = -0x227E;
    GM_Camera.bound[0][0].vy = 0x7530;
    GM_Camera.bound[0][0].vz = 0x18AB;
    GM_Camera.limit[0][0].vx = 0x1013;
    GM_Camera.limit[0][0].vy = 0x7530;
    GM_Camera.limit[1][0].vz = -0x227E;
    GM_Camera.limit[0][0].vz = 0x1527;
    work->field_19EC = 1;
}

int s08b_ninja_800C8930(char *unused, int *out)
{
    int   count = 0;
    char *s;

    (void)unused;
    while ((s = GCL_NextStr()) != NULL)
    {
        *out = GCL_StrToInt(s);
        out++;
        count++;
    }
    return count;
}

int s08b_ninja_800C8988(Work *work)
{
    char *opt = GCL_GetOption('v');

    if (opt == NULL)
    {
        return 0;
    }
    if (s08b_ninja_800C8930(opt, work->field_1A98) < 0x23)
    {
        return 0;
    }
    fprintf(0, s08b_aErrerrerrsoundbuffover_800E3764);
    return -1;
}

int s08b_ninja_800C89E8(char *unused, char *out)
{
    int   count = 0;
    char *s;

    (void)unused;
    while ((s = GCL_NextStr()) != NULL)
    {
        *out = GCL_StrToInt(s);
        out++;
        count++;
    }
    return count;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8A40.s")
int s08b_ninja_800C8A40(Work *work);

int s08b_ninja_800C8BE8(Work *work, int name, int where) // GetResources
{
    SVECTOR svec1;
    SVECTOR svec2;

    if (s08b_ninja_800C83CC(work, name, where) < 0)
    {
        return -1;
    }

    if (s08b_ninja_800C8558(work) < 0)
    {
        return -1;
    }

    if (s08b_ninja_800C8988(work) < 0)
    {
        return -1;
    }

    if (s08b_ninja_800C8A40(work) < 0)
    {
        return -1;
    }

    if (work->field_7D8 == 0)
    {
        work->target = GM_AllocTarget();
        if (work->target == NULL)
        {
            return -1;
        }

        s08b_ninja_800C8354(work);
        s08b_ninja_800C8624(work);
        s08b_ninja_800C8848(work);
    }

    work->field_910 = GM_SetHomingTarget(&work->body.objs->objs[6].world, &work->control);
    GM_ConfigMotionAdjust(&work->body, work->adjust);

    svec1.vx = 0;
    svec1.vy = -0x41;
    svec1.vz = -0x373;
    svec2.vx = 0;
    svec2.vy = -0x41;
    svec2.vz = -0x2D;
    NewKatana(&work->body.objs->objs[4].world, &svec1, &svec2, &work->field_19F8);
    NewTenmetu(&work->body.objs->objs[6].world, &work->field_19F4);
    s08b_bunsin2_800CD914(work, 1);

    work->control.mov = work->clones[0].field_4[0];
    work->control.mov.vx = -0x1D65;
    work->control.mov.vz = -0x80F;

    work->field_1964 = 0;
    work->field_1966 = 0;
    work->field_199C = 0;
    work->field_19A0 = 0;
    work->field_1994 = 0;
    work->field_1998 = 0;
    work->field_19BC = NULL;
    work->field_19C0 = 0;

    if (work->field_7D8 == 0)
    {
        work->field_19C4 = 0;
    }
    else
    {
        work->field_19C4 = 5;
    }

    work->field_19E4 = 0xFF;
    work->field_19C8 = 0;
    work->field_19CC = 0;
    work->field_19D0 = 0;
    work->field_19D8 = 0;
    work->field_19DC = 0;
    work->field_19B8 = 1;
    work->field_1A3C = 0;
    work->field_8C0 = 0;
    work->field_19F0 = 0;
    work->field_1A84 = DG_ZeroVector;
    work->field_19F8 = 1;
    work->field_1B24 = 0;
    work->field_1A14 = 0;
    return 0;
}
int s08b_ninja_800C8BE8(Work *work, int name, int where); // GetResources

void *NewNinjaBoss(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s08b_ninja_800C8264, s08b_ninja_800C8798, s08b_aNinjac_800E37F8);

        if (GCL_GetOption('e'))
        {
            work->field_1A8C = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->field_1A8C = -1;
        }
        if (GCL_GetOption('w'))
        {
            work->field_1A90 = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->field_1A90 = -1;
        }
        if (GCL_GetOption('b'))
        {
            work->field_1A94 = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->field_1A94 = -1;
        }

        work->field_7D8 = 0;

        if (s08b_ninja_800C8BE8(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        s08b_dword_800E4340 = 0;
        s08b_dword_800E4334[0] = 1;
        s08b_dword_800E4334[1] = 0;
        s08b_dword_800E4334[2] = 0;
    }
    return (void *)work;
}

GV_ACT *Bunsin2_800C8F04(int name, int map, CONTROL *control, int type)
{
    return NULL;
}

void s08b_bunsin2_800C8F0C(Work *work)
{
    MATRIX world;

    world = DG_ZeroMatrix;
    world.t[0] = work->control.mov.vx;
    world.t[1] = 0x14;
    world.t[2] = work->control.mov.vz;

    if (GM_GameLevel == GM_LEVEL_NORMAL)
    {
        NewWindcrcl_800CF784(&world, 200, 100, 300, 10);
    }
    else if (GM_GameLevel > GM_LEVEL_EASY)
    {
        if (GM_GameLevel < GM_LEVEL_EXTREME + 1)
        {
            NewWindcrcl_800CF784(&world, 200, 100, 400, 10);
        }
        else
        {
            goto level_easy;
        }
    }
    else
    {
level_easy:
        NewWindcrcl_800CF784(&world, 200, 100, 200, 10);
    }
}
void s08b_bunsin2_800C8FF8(Work *work)
{
    MATRIX stackData;

    stackData = DG_ZeroMatrix;
    stackData.t[0] = work->control.mov.vx;
    stackData.t[1] = 0x14;
    stackData.t[2] = work->control.mov.vz;

    NewWindcrcl_800CF784(&stackData, 0xc8, 0x64, 0xc8, 0xa);
}

void s08b_bunsin2_800C908C(Work *work)
{
    MATRIX stackData;

    stackData = DG_ZeroMatrix;
    stackData.t[0] = work->control.mov.vx;
    stackData.t[1] = 0x14;
    stackData.t[2] = work->control.mov.vz;

    NewWindcrcl_800CF784(&stackData, 0x190, 0x190, 0x190, 0xa);
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9120.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C933C.s")
int s08b_bunsin2_800C933C(Work *work);

int s08b_bunsin2_800C9514(Work *work)
{
    TARGET *target = work->target;

    if (target->damaged & TARGET_POWER)
    {
        target->damage = 0;
        target->damaged = 0;
        return target->a_mode;
    }

    return -1;
}

int s08b_bunsin2_800C9548(Work *work)
{
    if (s08b_bunsin2_800C933C(work))
    {
        work->target->class = TARGET_AVAIL;
        return 1;
    }
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9978.s")
int s08b_bunsin2_800C9A58(OBJECT *parent)
{
    if ((GV_Time & 3) == 0)
    {
        NewPlasma_800CD1A4(parent, 6, 0, 4, 4, 1000);
        NewPlasma_800CD1A4(parent, 1, 9, 4, 4, 1000);
        NewPlasma_800CD1A4(parent, 5, 4, 4, 4, 1000);
        NewPlasma_800CD1A4(parent, 0, 15, 4, 4, 1000);
        NewPlasma_800CD1A4(parent, 10, 12, 4, 4, 1000);
        return 1;
    }

    return 0;
}
void s08b_bunsin2_800C9B38(Work *work, int first)
{
    work->target->class |= 0x1F;

    if (first == 0)
    {
        work->field_19A4 = 0;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[0], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (s08b_bunsin2_800C9120(work) != 0)
        {
            GM_ConfigObjectOverride(&work->body, s08b_dword_800C33A0[0], 0, 4, 0);
            work->field_1998 = 0;
            work->field_19A0 = 0;
            goto reset;
        }

        if (work->field_19B4 >= 0)
        {
            work->field_1994 = (NinjaAction)s08b_bunsin2_800C9C74;
            work->field_199C = 0;
reset:
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
int s08b_bunsin2_800C9BF8(SVECTOR *pos)
{
    if ((unsigned int)((unsigned short)pos->vx - 0x1389) < 0x2ED && pos->vz >= -0x1F3 && pos->vz < 0x1770)
    {
        return 1;
    }

    if ((unsigned short)(pos->vx + 0xCB1) < 0x1675)
    {
        if (pos->vz >= -0xF9)
        {
            if (pos->vz < 0xFA)
            {
                return 1;
            }
        }
    }

    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9C74.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9F74.s")
void s08b_bunsin2_800CA11C(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      frame = work->m_ctrl.info1.frame;

    work->field_19FC = 1;

    if (time == 0)
    {
        work->field_19A4 = 7;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[7], 0, 4);
        work->field_918 = control->mov;
    }

    if (time == 18)
    {
        GM_SeSetMode(&control->mov, 0xBC, 1);
        s08b_bunsin2_800C8FF8(work);
    }

    if (time == 8)
    {
        GM_SeSetMode(&control->mov, 0x38, 1);
    }

    if (work->body.is_end != 0)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_19A8 = 1;
        return;
    }

    if ((unsigned int)(frame - 7) < 19)
    {
        control->step.vx = (work->field_1968.vx - work->field_918.vx) / 18;
        control->step.vz = (work->field_1968.vz - work->field_918.vz) / 18;
    }
    else
    {
        control->step.vx = 0;
        control->step.vz = 0;
    }

    control->mov.vy = work->body.height;
    control->seg_flag = 4;
}
void s08b_bunsin2_800CA298(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      frame = work->m_ctrl.info1.frame;

    work->field_19FC = 1;

    if (time == 0)
    {
        work->field_19A4 = 6;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[6], 0, 4);
        work->field_918 = control->mov;
    }

    if (time == 18)
    {
        GM_SeSetMode(&control->mov, 0xBC, 1);
        s08b_bunsin2_800C8FF8(work);
    }

    if (time == 8)
    {
        GM_SeSetMode(&control->mov, 0x38, 1);
    }

    if (work->body.is_end != 0)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_19A8 = 1;
        return;
    }

    if ((unsigned int)(frame - 7) < 19)
    {
        control->step.vx = (work->field_1968.vx - work->field_918.vx) / 18;
        control->step.vz = (work->field_1968.vz - work->field_918.vz) / 18;
    }
    else
    {
        control->step.vx = 0;
        control->step.vz = 0;
    }

    control->mov.vy = work->body.height;
    control->seg_flag = 4;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CA414.s")
void s08b_bunsin2_800CA5D8(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      angle = work->field_19B4;

    if (time == 0)
    {
        work->field_19A4 = 5;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[5], 0, 4);
        work->field_918 = control->mov;
        control->turn.vy = angle;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 7)
        {
            GM_SeSetMode(&control->mov, 0xBC, 1);
        }

        if (time == 70)
        {
            GM_SeSetMode(&control->mov, 0xBC, 1);
            s08b_bunsin2_800C8FF8(work);
        }

        if (time == 13 || time == 60)
        {
            GM_SeSetMode(&control->mov, 0xBB, 1);
        }

        if (time == 79)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        if (work->body.is_end != 0)
        {
            work->body.is_end = 0;
        }

        if ((unsigned int)(time - 7) < 62)
        {
            work->field_19F8 = 0;
            work->field_19C0 |= 2;

            if (time == 9)
            {
                work->body.objs->flag |= DG_FLAG_INVISIBLE;
                work->field_1A80->type |= DG_PRIM_INVISIBLE;
            }

            if (time == 65)
            {
                work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
                work->field_1A80->type &= ~DG_PRIM_INVISIBLE;
            }
        }

        if (time == 39)
        {
            control->mov.vx = work->field_1968.vx;
            control->mov.vz = work->field_1968.vz;
        }

        if ((unsigned int)(time - 7) < 9 || (unsigned int)(time - 56) < 10)
        {
            control->mov.vy = control->levels[0] + work->body.height * 2;
        }
        else if ((unsigned int)(time - 16) < 40)
        {
            control->mov.vy = 6000;
            control->step.vy = 0;
        }
        else
        {
            control->mov.vy = work->body.height + control->levels[0];
        }

        if (time >= 67)
        {
            work->target->class |= 0x1F;
        }

        control->step.vx = 0;
        control->step.vz = 0;
    }
}
void s08b_bunsin2_800CA858(Work *work, int time)
{
    CONTROL *control = &work->control;

    work->field_19FC = 1;

    if (time == 0)
    {
        work->field_19A4 = 5;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[5], 0, 4);
        work->field_918 = work->control.mov;
    }

    if (time == 7)
    {
        GM_SeSetMode(&control->mov, 0xBC, 1);
    }

    if (time == 26)
    {
        GM_SeSetMode(&control->mov, 0xBC, 1);
        s08b_bunsin2_800C8FF8(work);
    }

    if (time == 13)
    {
        GM_SeSetMode(&control->mov, 0xBB, 1);
    }

    if (time == 39)
    {
        work->field_19A8 = 1;
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        return;
    }

    if (work->body.is_end != 0)
    {
        work->body.is_end = 0;
    }

    if ((unsigned int)(time - 7) < 22)
    {
        work->field_19C0 |= 2;

        if (time == 9)
        {
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
            work->field_1A80->type |= DG_PRIM_INVISIBLE;
        }

        if (time == 25)
        {
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
            work->field_1A80->type &= ~DG_PRIM_INVISIBLE;
        }
    }

    if (time == 15)
    {
        control->mov.vx = work->field_1968.vx;
        control->mov.vz = work->field_1968.vz;
    }

    if ((unsigned int)(time - 9) < 17)
    {
        control->mov.vy = control->levels[0] + work->body.height * 2;
    }
    else
    {
        control->mov.vy = work->body.height + control->levels[0];
    }

    control->step.vx = 0;
    control->step.vz = 0;
}
void s08b_bunsin2_800CAA78(Work *work, int first)
{
    CONTROL *control = &work->control;
    int      damage;

    if (first == 0)
    {
        work->field_19A4 = 8;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[8], 0, 4);
    }

    if (work->field_19B4 >= 0)
    {
        control->turn.vy = work->field_19B4;
    }

    damage = s08b_bunsin2_800C9514(work);
    if (damage > 0)
    {
        if (damage < 5)
        {
            if (damage >= 3)
            {
                GM_SeSetMode(&control->mov, 0xBD, 1);
            }
        }
    }

    if (work->field_19B0 != 7)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    work->target->class |= 0x1F;
}
void s08b_bunsin2_800CAB50(Work *work, int first)
{
    CONTROL *control = &work->control;

    work->target->class |= 0x1F;

    if (first == 0)
    {
        work->field_19A4 = 9;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[9], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (work->field_19B4 >= 0)
        {
            control->turn.vy = work->field_19B4;
        }

        if (work->field_19B0 != 8)
        {
            if (s08b_bunsin2_800C9120(work) != 0)
            {
                GM_ConfigObjectOverride(&work->body, s08b_dword_800C33A0[0], 0, 4, 0);
                work->field_1998 = 0;
                work->field_19A0 = 0;
            }
            else
            {
                work->field_1994 = s08b_bunsin2_800C9B38;
                work->field_199C = 0;
            }

            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s08b_bunsin2_800CAC3C(Work *work, int first)
{
    CONTROL *control = &work->control;

    work->target->class |= 0x1F;

    if (first == 0)
    {
        work->field_19A4 = 8;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[8], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (work->field_19B4 >= 0)
        {
            control->turn.vy = work->field_19B4;
        }

        if (work->field_19B0 != 9)
        {
            if (s08b_bunsin2_800C9120(work) != 0)
            {
                GM_ConfigObjectOverride(&work->body, s08b_dword_800C33A0[0], 0, 4, 0);
                work->field_1998 = 0;
                work->field_19A0 = 0;
            }
            else
            {
                work->field_1994 = s08b_bunsin2_800C9B38;
                work->field_199C = 0;
            }

            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
}
void s08b_bunsin2_800CAD28(Work *work, int time)
{
    if (time == 0)
    {
        work->field_19A4 = 31;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[31], 0, 4);
    }

    work->field_19F8 = 2;

    if ((unsigned int)(time - 1) < 6 || (unsigned int)(time - 20) < 16 || (unsigned int)(time - 101) < 5)
    {
        work->field_19FC = 1;
    }

    if (time == 22 || time == 30 || time == 100)
    {
        GM_SeSet2(0, 0x3F, 0xB4);
    }

    if (s08b_bunsin2_800C9120(work) == 0 && work->body.is_end != 0)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s08b_bunsin2_800CAE14(Work *work, int time)
{
    CONTROL *control = &work->control;

    work->field_19FC = 1;

    if (time == 0)
    {
        work->field_19A4 = 30;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[30], 0, 4);
        GM_SeSet2(0, 0x3F, 0xB4);
    }

    if (time == 90)
    {
        work->field_19A4 = 0;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[0], 0, 15);
    }

    if (work->field_19B4 >= 0)
    {
        control->turn.vy = work->field_19B4;
    }

    if ((unsigned int)(time - 21) < 13 || (unsigned int)(time - 57) < 13)
    {
        work->field_19FC = 1;
    }

    if (time == 20)
    {
        GM_SeSet2(0, 0x3F, 0xB4);
    }

    if (time == 33)
    {
        GM_SeSet2(0, 0x3F, 0xB3);
        work->field_8C0 = 1;
    }

    if (time < 33)
    {
        work->field_19F8 = 2;
    }

    if (s08b_bunsin2_800C9120(work) == 0 && time == 104)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s08b_bunsin2_800CAF6C(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 27;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[27], 0, 4);
    }

    if (work->field_19B0 != 22)
    {
        if (s08b_bunsin2_800C9120(work) == 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            goto stop;
        }
    }
    else
    {
stop:
        control->step.vx = 0;
        control->step.vz = 0;
    }
}
void s08b_bunsin2_800CAFF8(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 28;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[28], 0, 4);
    }

    work->field_1A00 = 1;

    if (work->field_19B0 != 23)
    {
        if (s08b_bunsin2_800C9120(work) == 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
    else
    {
        control->step.vx = 0;
        control->step.vz = 0;
        work->target->class |= 0x1F;
    }
}
void s08b_bunsin2_800CB0A8(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 29;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[29], 0, 4);
    }

    work->field_1A00 = 1;

    if (work->field_19B0 != 24)
    {
        if (s08b_bunsin2_800C9120(work) == 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
        }
    }
    else
    {
        control->step.vx = 0;
        control->step.vz = 0;
        work->target->class |= 0x1F;
    }
}
void s08b_bunsin2_800CB158(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 32;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[32], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        work->field_1A00 = 1;

        if (work->field_19B0 != 26)
        {
            if (s08b_bunsin2_800C9120(work) == 0)
            {
                work->field_1994 = s08b_bunsin2_800C9B38;
                work->field_199C = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                goto stop;
            }
        }
        else
        {
stop:
            control->step.vx = 0;
            control->step.vz = 0;
            work->target->class |= 0x1F;
        }
    }
}
void s08b_bunsin2_800CB210(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 27;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[27], 0, 4);
    }

    work->field_1A00 = 1;

    if (work->field_19B0 != 27)
    {
        if (s08b_bunsin2_800C9120(work) == 0)
        {
            work->field_19F0 = 30;
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            goto stop;
        }
    }
    else
    {
stop:
        control->step.vx = 0;
        control->step.vz = 0;
    }
}
void s08b_bunsin2_800CB2AC(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 34;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[34], 0, 4);
        s08b_bunsin2_800C9588(work, 5);
        s08b_bunsin2_800C908C(work);
    }

    if ((time & 3) == 0)
    {
        GM_SeSetMode(&control->mov, 0xB7, 1);
        s08b_bunsin2_800C8F0C(work);
    }

    work->field_1A00 = 2;

    if (work->field_19B0 != 28)
    {
        if (s08b_bunsin2_800C9120(work) == 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            goto stop;
        }
    }
    else
    {
stop:
        s08b_bunsin2_800C9588(work, 6);
        control->step.vx = 0;
        control->step.vz = 0;
    }
}
void s08b_bunsin2_800CB38C(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 35;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[35], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        work->field_1A00 = 1;

        if (work->field_19B0 != 30)
        {
            if (s08b_bunsin2_800C9120(work) == 0)
            {
                work->field_1994 = s08b_bunsin2_800C9B38;
                work->field_199C = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                goto stop;
            }
        }
        else
        {
stop:
            control->step.vx = 0;
            control->step.vz = 0;
            work->target->class |= 0x1F;
        }
    }
}
void s08b_bunsin2_800CB444(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 34;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[34], 0, 4);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if ((time & 3) == 0)
        {
            GM_SeSetMode(&control->mov, 0xB7, 1);
            s08b_bunsin2_800C8F0C(work);
        }

        if (work->field_19B0 != 29)
        {
            if (s08b_bunsin2_800C9120(work) == 0)
            {
                work->field_1994 = s08b_bunsin2_800C9B38;
                work->field_199C = 0;
                work->control.turn.vz = 0;
                work->control.turn.vx = 0;
                goto stop;
            }
        }
        else
        {
stop:
            s08b_bunsin2_800C9588(work, 6);
            control->step.vx = 0;
            control->step.vz = 0;
            work->target->class |= 0x1F;
        }
    }
}
void s08b_bunsin2_800CB52C(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    work->field_19F8 = 2;

    if (time == 0)
    {
        work->field_19A4 = 10;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[10], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 3)
        {
            GM_SeSetMode(&control->mov, 0x51, 1);
        }

        if (time == 5)
        {
            GM_SeSetMode(&control->mov, 0xB4, 1);
        }

        if (time == 16)
        {
            GM_SeSetMode(&control->mov, 0x51, 1);
        }

        if ((unsigned int)(time - 5) < 15)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 0);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&control->mov, 0xB1, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            if (work->field_8C0 == 1)
            {
                GM_SeSet2(0, 0x3F, 0xB3);
            }

            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;

        switch (GM_GameLevel)
        {
        case GM_LEVEL_NORMAL:
            control->step.vx *= 2;
            control->step.vz *= 2;
            break;

        case GM_LEVEL_HARD:
            control->step.vx = control->step.vx * 3 / 2;
            control->step.vz = control->step.vz * 3 / 2;
            if ((time & 3) == 0)
            {
                control->turn.vy = work->field_1A28;
            }
            break;

        case GM_LEVEL_EXTREME:
            control->step.vx *= 2;
            control->step.vz *= 2;
            control->turn.vy = work->field_1A28;
            break;
        }
    }
}
void s08b_bunsin2_800CB7A0(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    work->field_19F8 = 2;

    if (time == 0)
    {
        work->field_19A4 = 11;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[11], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 6 || time == 17)
        {
            GM_SeSetMode(&control->mov, 0xB4, 1);
        }

        if ((unsigned int)(time - 7) < 23)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 0);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&work->control.mov, 0xB1, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            if (work->field_8C0 == 1)
            {
                GM_SeSet2(0, 0x3F, 0xB3);
            }

            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
        }
        else
        {
            work->target->class |= 0x1F;
        }
    }
}
void s08b_bunsin2_800CB914(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    work->target->class |= 0x1F;

    if (time == 0)
    {
        work->field_19A4 = 12;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[12], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 12 || time == 38 || time == 56)
        {
            GM_SeSetMode(&work->control.mov, 0x38, 1);
        }

        if ((unsigned int)(time - 13) < 5)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 3);
        }

        if ((unsigned int)(time - 39) < 3)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 3);
        }

        if ((unsigned int)(time - 57) < 3)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 4);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&work->control.mov, 0x34, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
        }
    }
}
void s08b_bunsin2_800CBAA4(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    if (time == 0)
    {
        work->field_19A4 = 13;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[13], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 13 || time == 21 || time == 34)
        {
            GM_SeSetMode(&work->control.mov, 0x38, 1);
        }

        if ((unsigned int)(time - 14) < 5)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 3);
        }

        if ((unsigned int)(time - 22) < 18)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 3);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&work->control.mov, 0x34, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;

        switch (GM_GameLevel)
        {
        case GM_LEVEL_NORMAL:
            control->step.vx *= 2;
            control->step.vz *= 2;
            break;

        case GM_LEVEL_HARD:
            control->step.vx = control->step.vx * 3 / 2;
            control->step.vz = control->step.vz * 3 / 2;
            if ((time & 3) == 0)
            {
                control->turn.vy = work->field_1A28;
            }
            break;

        case GM_LEVEL_EXTREME:
            control->step.vx *= 2;
            control->step.vz *= 2;
            control->turn.vy = work->field_1A28;
            break;
        }
    }
}
void s08b_bunsin2_800CBCEC(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    if (time == 0)
    {
        work->field_19A4 = 14;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[14], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 13)
        {
            GM_SeSetMode(&control->mov, 0x38, 1);
        }

        if ((unsigned int)(time - 14) < 7)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 0);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&control->mov, 0x34, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;
    }
}
void s08b_bunsin2_800CBE30(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;

    if (time == 0)
    {
        work->field_19A4 = 15;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[15], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (time == 6)
    {
        GM_SeSetMode(&control->mov, 0xB6, 1);
    }

    if (time == 10)
    {
        GM_SeSetMode(&control->mov, 0x39, 1);
    }

    if (time == 24)
    {
        GM_SeSetMode(&control->mov, 0xBC, 1);
    }

    if ((unsigned int)(time - 11) < 17)
    {
        result = s08b_bunsin2_800C9588(work, 0);
        work->field_19FC = 1;
    }

    if (result != 0 && work->field_1B26 != 0)
    {
        GM_SeSetMode(&control->mov, 0x34, 1);
        work->field_1B26 = 0;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;

        switch (GM_GameLevel)
        {
        case GM_LEVEL_NORMAL:
            control->step.vx *= 2;
            control->step.vz *= 2;
            break;

        case GM_LEVEL_HARD:
            control->step.vx = control->step.vx * 3 / 2;
            control->step.vz = control->step.vz * 3 / 2;
            if ((time & 3) == 0)
            {
                control->turn.vy = work->field_1A28;
            }
            break;

        case GM_LEVEL_EXTREME:
            control->step.vx *= 2;
            control->step.vz *= 2;
            control->turn.vy = work->field_1A28;
            break;
        }
    }
}
void s08b_bunsin2_800CC080(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result = 0;
    int      frame = work->m_ctrl.info1.frame;
    int      limit;
    unsigned short angle;

    if (time == 0)
    {
        work->field_19A4 = 16;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[16], 0, 4);
        work->field_918 = control->mov;
        angle = work->field_1A28;
        control->rot.vy = angle;
        control->turn.vy = angle;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        limit = 60;
        if (GM_GameLevel != GM_LEVEL_NORMAL)
        {
            limit = 100;
            if (GM_GameLevel > GM_LEVEL_EASY)
            {
                if (GM_GameLevel < GM_LEVEL_EXTREME + 1)
                {
                    limit = 50;
                }
            }
        }

        if (work->body.is_end != 0 || limit < time)
        {
            work->field_19A8 = 1;
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            return;
        }

        if (time == 10)
        {
            GM_SeSetMode(&work->control.mov, 0xBB, 1);
        }

        if (time == 39)
        {
            GM_SeSetMode(&work->control.mov, 0x39, 1);
        }

        if (time == 41)
        {
            GM_SeSetMode(&work->control.mov, 0xBC, 1);
            s08b_bunsin2_800C908C(work);
        }

        if ((unsigned int)(time - 21) < 22)
        {
            work->field_19FC = 1;
        }

        if ((unsigned int)(time - 31) < 12)
        {
            result = s08b_bunsin2_800C9588(work, 2);
        }

        if (result != 0)
        {
            if (work->field_1B26 != 0)
            {
                GM_SeSetMode(&work->control.mov, 0x35, 1);
                work->field_1B26 = 0;
            }
        }

        if ((unsigned int)(frame - 7) < 19)
        {
            control->step.vx = (GM_PlayerPosition.vx - work->field_918.vx) / 18;
            control->step.vz = (GM_PlayerPosition.vz - work->field_918.vz) / 18;
        }
        else
        {
            if (frame != 26)
            {
                work->target->class |= 0x1F;
            }

            control->step.vx = 0;
            control->step.vz = 0;
        }

        control->mov.vy = work->body.height;
    }
}
void s08b_bunsin2_800CC2F8(Work *work, int time)
{
    CONTROL *control = &work->control;
    int      result;

    if (time == 0)
    {
        work->field_19A4 = 17;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[17], 0, 4);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
        work->field_1B26 = 1;
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time == 16)
        {
            GM_SeSetMode(&control->mov, 0x38, 1);
        }

        result = 0;
        if ((unsigned int)(time - 18) < 5)
        {
            work->field_19FC = 1;
            result = s08b_bunsin2_800C9588(work, 0);
        }

        if (result != 0 && work->field_1B26 != 0)
        {
            GM_SeSetMode(&control->mov, 0x34, 1);
            work->field_1B26 = 0;
        }

        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;
    }
}
void s08b_bunsin2_800CC434(Work *work, int time)
{
    CONTROL *control = &work->control;
    MATRIX   mat;

    if (time == 0)
    {
        work->field_19A4 = 33;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[33], 0, 4);
    }

    work->field_19FC = 1;

    if (time < 150)
    {
        DG_SetPos(&work->body.objs->objs[4].world);
        DG_RotatePos(&s08b_dword_800C33F0);
        ReadRotMatrix(&mat);
        NewBullet2(&mat, 2, 1, 0, 50, 3, 10000, 750);
        GM_SeSetMode(&control->mov, 0x49, 1);
    }

    if (s08b_bunsin2_800C9548(work) == 0)
    {
        if (time >= 181)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
            return;
        }

        work->target->class |= 0x1F;
        control->step.vx = 0;
        control->step.vz = 0;
        control->rot.vy += 0x80;
        control->turn.vy += 0x80;
    }
}
void s08b_bunsin2_800CC578(Work *work, int time)
{
    CONTROL *control = &work->control;
    TARGET  *target;
    OBJECT  *body;
    int      rnd;
    int      arg2;

    work->field_19FC = 1;

    if (s08b_bunsin2_800C9548(work) != 0)
    {
        work->field_1A3C++;
        return;
    }

    target = work->target;

    if (time == 0)
    {
        work->field_19E4 -= work->damage[0];
        fprintf(1, s08b_aPunchdamagelifedcombod_800E393C, work->field_19E4, work->field_1A3C);

        body = &work->body;
        work->field_19A4 = 18;
        GM_ConfigObjectAction(body, s08b_dword_800C33A0[18], 0, 4);
        GM_SeSetMode(&control->mov, 0x89, 1);

        if (target->a_mode != 1)
        {
            GM_SeSetMode(&control->mov, 0x34, 1);
        }

        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;

        rnd = GV_RandU(16);
        arg2 = rnd + 2;
        if (arg2 >= 16)
        {
            arg2 = rnd - 14;
        }

        NewPlasma_800CD1A4(body, rnd, arg2, 4, 0, 0);
    }

    if (work->body.is_end != 0)
    {
        work->field_19A8 = 1;
        work->field_19F0 = 30;
        work->field_1A3C = 0;
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }

    if (work->field_1A3C < 2)
    {
        if (time < 10)
        {
            work->target->class |= 0x1F;
        }
    }
}
void s08b_bunsin2_800CC71C(Work *work, int time)
{
    CONTROL *control = &work->control;

    if (time == 0)
    {
        work->field_19A4 = 19;
        work->field_19E4 -= work->damage[1];
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[19], 0, 4);
        GM_SeSetMode(&control->mov, 0x8A, 1);
        GM_SeSetMode(&control->mov, 0x34, 1);
        control->rot.vy = work->field_1A28;
        control->turn.vy = work->field_1A28;
    }

    if (work->body.is_end != 0)
    {
        work->field_19A8 = 1;
        work->field_19F0 = 30;
        work->field_1A3C = 0;
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s08b_bunsin2_800CC7EC(Work *work, int time)
{
    TARGET *target = work->target;

    if (time == 0)
    {
        work->field_19A4 = 21;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[21], 0, 4);
    }

    work->field_19FC = 1;

    if (time == 30)
    {
        GM_SeSetMode(&work->control.mov, 0xB5, 1);
    }

    if (time == 36)
    {
        GM_SeSetMode(&work->control.mov, 0xB6, 1);
    }

    if (time == 60)
    {
        GM_SeSetMode(&work->control.mov, 0xBC, 1);
        s08b_bunsin2_800C8FF8(work);
    }

    if (work->body.is_end != 0)
    {
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        work->field_19A8 = 1;
    }

    if (time < 24)
    {
        work->control.turn = *target->field_1C;
    }
}
void s08b_bunsin2_800CC90C(Work *work, int time)
{
    TARGET *target = work->target;

    if (time == 0)
    {
        work->field_19A4 = 22;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[22], 0, 4);
    }

    if (time == 24)
    {
        GM_SeSetMode(&work->control.mov, 0x33, 1);
    }

    if (time == 30)
    {
        work->field_19A4 = 38;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[38], 0, 4);
    }

    if (time == 60)
    {
        work->field_19A4 = 39;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[39], 0, 4);
    }

    if (time >= 61)
    {
        if (work->body.is_end != 0)
        {
            work->field_1994 = s08b_bunsin2_800C9B38;
            work->field_199C = 0;
            work->control.turn.vz = 0;
            work->control.turn.vx = 0;
            work->field_19A8 = 1;
        }
    }

    if (time < 24)
    {
        work->control.turn = *target->field_1C;
    }
}
void s08b_bunsin2_800CCA4C(Work *work, int time)
{
    if (time == 0)
    {
        work->field_19A4 = 26;
        GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[26], 0, 4);
    }

    if (time == 60)
    {
        GM_SeSetMode(&work->control.mov, 0x33, 1);
    }

    if (s08b_bunsin2_800C9120(work) == 0 && work->body.is_end != 0)
    {
        work->field_19A8 = 1;
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
    }
}
void s08b_bunsin2_800CCAF0(Work *work, int time)
{
    CONTROL *control = &work->control;
    TARGET  *target;
    int      state;

    work->target->class |= 0x1F;
    work->field_19FC = 1;
    work->field_19F8 = 2;

    target = work->target;
    work->field_19C0 &= ~2;

    if (time == 0)
    {
        GM_SeSetMode(&control->mov, 0xBD, 1);
        s08b_bunsin2_800CD544(work, 4);

        target->damage = 0;
        target->damaged = 0;
        target->vital = 30;

        if (GV_Time & 1)
        {
            work->field_19A4 = 23;
            GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[23], 0, 0);
        }
        else
        {
            work->field_19A4 = 24;
            GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[24], 0, 0);
        }
    }

    state = work->field_19A4;

    if (target->damaged & 4)
    {
        target->force = DG_ZeroVector;
        target->vital = 30;
        target->damage = 0;
        target->damaged = 0;

        if (target->a_mode == 1)
        {
            GM_SeSetMode(&work->control.mov, 0xBD, 1);
        }
        else
        {
            GM_SeSetMode(&work->control.mov, 0xB4, 1);
        }

        s08b_bunsin2_800CD544(work, 4);

        if (state == 23)
        {
            work->field_19A4 = 24;
            GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[24], 0, 0);
        }
        else if (state == 24)
        {
            work->field_19A4 = 25;
            GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[25], 0, 0);
        }
        else
        {
            work->field_19A4 = 23;
            GM_ConfigObjectAction(&work->body, s08b_dword_800C33A0[23], 0, 0);
        }
    }

    if (work->body.is_end != 0)
    {
        work->field_19A8 = 1;
        s08b_bunsin2_800CD914(work, 3);
        work->field_1994 = s08b_bunsin2_800C9B38;
        work->field_199C = 0;
        work->control.turn.vz = 0;
        work->control.turn.vx = 0;
        GM_SeSetMode(&work->control.mov, 0x50, 1);
    }

    control->rot.vy = work->field_1A28;
    control->turn.vy = work->field_1A28;
}

void s08b_bunsin2_800CCD18(Work *work)
{
    sna_act_helper2_helper2_80033054(work->control.name, &work->adjust[6]);
}

void s08b_bunsin2_800CCD40(Work *work)
{
    work->field_19F4 = 0;
    work->field_19F4 = jimctrl_helper_80037F68(work->control.name) & 0xFF;
}

void s08b_bunsin2_800CCD74(Work *work)
{
    if (work->field_19F8 == 0)
    {
        DG_InvisibleObjs(work->weapon.objs);
    }
    else
    {
        DG_VisibleObjs(work->weapon.objs);
    }
}

void s08b_bunsin2_800CCDBC(Work *work)
{
    if (work->field_19F0 > 0)
    {
        if (work->field_19F0 & 2)
        {
            work->body.objs->flag |= 0x80;
        }
        else
        {
            work->body.objs->flag &= ~0x80;
        }
        work->target->class = TARGET_AVAIL;
        work->field_19F0 = work->field_19F0 - 1;
    }
    else
    {
        work->field_19F0 = 0;
    }
}
void s08b_bunsin2_800CCE34(Work *work)
{
    if (work->field_19C0 & 2)
    {
        if (GM_GameStatus & STATE_THERMG)
        {
            if (work->field_19BC != NULL)
            {
                GM_SeSetMode(&work->control.mov, 0x4E, 1);
                GV_DestroyActorQuick(work->field_19BC);
                work->field_19BC = NULL;
                work->field_910->flag = 1;
                work->field_1A80->type &= ~DG_PRIM_INVISIBLE;
            }
        }
        else if (work->field_19BC == NULL)
        {
            GM_SeSetMode(&work->control.mov, 0x4E, 1);
            work->field_19BC = NewKogaku2(&work->control, &work->body, 0);
            work->field_910->flag = 0;
            work->field_1A80->type |= DG_PRIM_INVISIBLE;
        }

        work->field_19F4 = -1;
        return;
    }

    if (work->field_19BC != NULL)
    {
        GM_SeSetMode(&work->control.mov, 0x4E, 1);
        GV_DestroyActorQuick(work->field_19BC);
        work->field_19BC = NULL;
        work->field_910->flag = 1;
        work->field_1A80->type &= ~DG_PRIM_INVISIBLE;
    }
}
void s08b_bunsin2_800CCF8C(Work *work)
{
    if (work->field_1A00 == 1)
    {
        if (s08b_bunsin2_800C9978(&work->body))
        {
            GM_SeSetMode(&work->control.mov, 0xB2, 1);
        }
    }
    else if (work->field_1A00 != 2 && work->field_19E4 < 0x5A)
    {
        work->field_1A00 = 1;
    }
}
void s08b_bunsin2_800CD000(Work *work)
{
    CONTROL     *control;
    OBJECT      *body;
    NinjaAction  action;
    int          time;
    int          height;

    work->target->class = TARGET_AVAIL;
    work->field_19A8 = 0;
    work->field_19FC = 0;
    work->field_1A00 = 0;
    work->field_1A10 = 0;

    if (work->field_8C0 == 1)
    {
        work->field_19F8 = 0;
    }
    else
    {
        work->field_19F8 = 1;
    }

    control = &work->control;
    action = work->field_1994;
    control->seg_flag = 2;

    time = work->field_199C;
    body = &work->body;
    work->field_199C = time + 1;

    if (action == NULL)
    {
        action = s08b_bunsin2_800C9B38;
        work->field_1994 = action;
    }

    action(work, time);

    action = work->field_1998;
    if (action != NULL)
    {
        time = work->field_19A0;
        work->field_19A0 = time + 1;
        action(work, time);
    }

    work->target->damaged = 0;

    if (work->field_1A14 != 0)
    {
        work->target->class &= ~TARGET_CAPTURE;
        work->field_19FC = 0;
    }

    s08b_bunsin2_800CCD18(work);
    s08b_bunsin2_800CCD40(work);
    s08b_bunsin2_800CCD74(work);
    s08b_bunsin2_800CCDBC(work);
    s08b_bunsin2_800CCE34(work);
    s08b_bunsin2_800CCF8C(work);

    if (GM_GameStatus & STATE_THERMG)
    {
        work->field_19FC = 0;
    }

    if (work->field_19C0 & 4)
    {
        if (work->field_7D8 == 0 && work->field_1A18 == NULL && work->field_1A1C == NULL)
        {
            goto invisible_off;
        }

        if (work->field_7D8 == GV_Time % 3)
        {
invisible_off:
            work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        }
        else
        {
            work->body.objs->flag |= DG_FLAG_INVISIBLE;
        }
    }

    control->height = body->height;

    if (control->mov.vy >= 3801)
    {
        work->field_1A10 = 2;
    }

    switch (work->field_1A10)
    {
    case 1:
        height = -1;
        break;

    case 2:
        height = -2;
        break;

    default:
        height = GV_NearExp2(control->r_sphere, 450);
        break;
    }

    control->r_sphere = height;

    if (work->field_914 < 0)
    {
        if (control->grounded != 0)
        {
            work->field_914 = 0;
        }

        work->field_914 = work->field_914 - 16;
    }
    else
    {
        work->field_914 = work->field_914 - 16;
    }

    control->step.vy = work->field_914;
    work->target->captured = 0;
}
void s08b_bunsin2_800CD000(Work *work);

int s08b_bunsin2_800CD298(int a, int b, int c)
{
    if (b < a) b = a;
    if (c < b) c = b;
    return c;
}

int s08b_bunsin2_800CD2C0(int a, int b, int c)
{
    if (a < b) b = a;
    if (b < c) c = b;
    return c;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD2E8.s")
void s08b_bunsin2_800CD544(Work *work, int index)
{
    MATRIX mat;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&s08b_dword_800C33F8);
    DG_RotatePos(&s08b_dword_800C3400);
    ReadRotMatrix(&mat);
    NewSpark(&mat, 0);
}
void s08b_bunsin2_800CD5AC(Work *work, int index)
{
    MATRIX mat;

    DG_SetPos(&work->body.objs->objs[index].world);
    DG_MovePos(&s08b_dword_800C3408);
    DG_RotatePos(&s08b_dword_800C3410);
    ReadRotMatrix(&mat);
    NewBlood(&mat, 0);
}
void s08b_bunsin2_800CD614(Work *work)
{
    MATRIX  mat;
    MATRIX *world;

    world = &work->body.objs->objs[4].world;
    DG_SetPos(world);
    DG_MovePos(&s08b_dword_800C3430);
    ReadRotMatrix(&mat);
    GM_SeSet((SVECTOR *)&work->control, 0x49);
    AN_SocomFlash(world, &mat, 0);
    s08b_bunsin2_800CD95C(work, s08b_bunsin2_800CD614);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD690.s")
void s08b_bunsin2_800CD770(Work *work)
{
    SVECTOR rot;
    MATRIX *world;

    s08b_bunsin2_800CD2E8(work);

    rot = DG_ZeroVector;
    rot.vy = work->control.rot.vy;
    RotMatrixYXZ(&rot, &work->field_1A80->world);

    world = &work->field_1A80->world;
    world->t[0] = work->body.objs->world.t[0];
    world->t[1] = work->control.levels[0];
    world->t[2] = work->body.objs->world.t[2];
}
void s08b_bunsin2_800CD808(Work *work)
{
    if (!(s08b_dword_800C3438 & 1))
    {
        s08c_800C4194(&work->body.objs->objs[6].world);
    }

    if (s08b_dword_800C3438 >= 8)
    {
        s08b_dword_800C3438 = 0;
        s08b_bunsin2_800CD95C(work, s08b_bunsin2_800CD808);
    }

    s08b_dword_800C3438++;
}

void s08b_bunsin2_800CD87C(Work *work)
{
    if (s08b_dword_800C343C == 8)
    {
        s08b_dword_800C343C = 0;
        s08b_bunsin2_800CD95C(work, s08b_bunsin2_800CD87C);
        work->field_8C0 = 1;
    }

    s08b_dword_800C343C++;
}

void s08b_bunsin2_800CD8D8(Work *work)
{
    DG_VisibleObjs(work->weapon.objs);
    s08b_bunsin2_800CD95C(work, s08b_bunsin2_800CD87C);
}

int s08b_bunsin2_800CD914(Work *work, int index)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_1A40[i] == NULL)
        {
            work->field_1A40[i] = s08b_dword_800C3418[index];
            return 1;
        }
    }

    return 0;
}

int s08b_bunsin2_800CD95C(Work *work, void *func)
{
    int i;

    for (i = 0; i < 8; i++)
    {
        if (work->field_1A40[i] == func)
        {
            work->field_1A40[i] = NULL;
            return 1;
        }
    }

    return 0;
}

void s08b_bunsin2_800CD990(Work *work)
{
    int i;
    NinjaFunc f;

    for (i = 0; i < 8; i++)
    {
        f = work->field_1A40[i];
        if (f != NULL)
        {
            f(work);
        }
    }
}

void s08b_bunsin2_800CD9F0(Work *work)
{
    TARGET        *target = work->target;
    unsigned short flag   = target->damaged;

    work->field_1A34 = 0;
    if (flag & TARGET_POWER)
    {
        work->field_1A34 = target->a_mode;
        return;
    }
    if (flag & TARGET_CAPTURE)
    {
        if (target->a_mode == 0x24)
        {
            work->field_1A34 = 6;
        }
    }
}

void s08b_bunsin2_800CDA40(Work *work)
{
    SVECTOR  diff;
    SVECTOR *pos;
    MAP     *map;

    pos = &work->control.mov;
    GV_SubVec3(&GM_PlayerPosition, pos, &diff);
    diff.vy = 0;
    work->field_1A28 = GV_VecDir2(&diff);
    work->field_1A2C = GV_VecLen3(&diff);
    work->field_19AC = 0;

    if ((GV_Time & 3) == 0)
    {
        map = work->control.map;
        if (HZD_OnlineHazardCheck(map->hzd, &GM_PlayerPosition, pos, 0xF, 2) != 0 ||
            GM_OnlineTargetCheckAny(pos, &GM_PlayerPosition, map->index, &diff) != 0)
        {
            work->field_19AC = 0;
            return;
        }

        work->field_19AC = 1;
    }
}
void s08b_bunsin2_800CDA40(Work *work);

void s08b_bunsin2_800CDB10(Work *work)
{
    s08b_bunsin2_800CDA40(work);
    s08b_bunsin2_800CD9F0(work);
    s08b_bunsin2_800D4ED0(work);
    s08b_bunsin2_800CD000(work);
    s08b_bunsin2_800CD990(work);
}

void s08b_bunsin2_800CDB54(int vox_code)
{
    if (GM_StreamStatus() == -1 &&
        GM_GameOverTimer == 0 &&
        GM_Vitality > 0)
    {
        GM_VoxStream(vox_code, 0);
    }
}
void s08b_bunsin2_800CDBAC(Work *work)
{
    if (s08b_dword_800C3440 % 12 == 1)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GM_VoxStream(work->field_1A98[1], 0);
            }
            s08b_dword_800C3440 = s08b_dword_800C3440 + 1;
        }
    }
    else if (s08b_dword_800C3440 % 12 == 5)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GM_VoxStream(work->field_1A98[2], 0);
            }
            s08b_dword_800C3440 = s08b_dword_800C3440 + 1;
        }
    }
    if (s08b_dword_800C3450 == 2)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GM_VoxStream(work->field_1A98[15], 0);
            }
            s08b_dword_800C3450 = s08b_dword_800C3450 + 1;
        }
    }
    else if (s08b_dword_800C3450 == 4)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GM_VoxStream(work->field_1A98[16], 0);
            }
            s08b_dword_800C3450 = s08b_dword_800C3450 + 1;
        }
    }
    else if (s08b_dword_800C3450 == 6)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GM_VoxStream(work->field_1A98[14], 0);
            }
            s08b_dword_800C3450 = 0;
        }
    }
    s08b_dword_800C3588 = s08b_dword_800C3588 + 1;
}
void s08b_bunsin2_800CDDD8(Work *work)
{
    NinjaClone *c = &work->clones[work->field_1964];
    int i = work->field_1966 + 1;
    MAP *map;

    if (i >= c->field_0)
    {
        i = 0;
    }
    work->field_1966 = i;
    work->field_1968 = c->field_4[i];
    map = work->control.map;
    work->field_1970 = HZD_GetAddress(map->hzd, &work->field_1968, -1);
}
void s08b_bunsin2_800CDE74(Work *work)
{
    NinjaClone *clone;
    int         route;
    int         point;

    route = GV_Time % work->field_1960;
    clone = &work->clones[route];
    work->field_1964 = route;

    point = GV_Time % clone->field_0;
    work->field_1966 = point;

    work->field_1968 = clone->field_4[point];
    work->field_1970 = HZD_GetAddress(work->control.map->hzd, &work->field_1968, -1);
}

void s08b_bunsin2_800CDF68(Work *work)
{
    work->field_1968 = GM_PlayerPosition;
    work->field_1970 = GM_PlayerAddress;
}

void s08b_bunsin2_800CDFA0(Work *work)
{
    work->field_198C = work->field_1968;
    work->field_1988 = work->field_1970;
    work->field_1968 = work->field_1980;
    work->field_1970 = work->field_197C;
}

void s08b_bunsin2_800CDFF8(Work *work)
{
    work->field_1968 = work->field_198C;
    work->field_1970 = work->field_1988;
}

void s08b_bunsin2_800CE024(Work *work)
{
    work->field_1968 = s08b_dword_800C358C;
    work->field_1970 = s08b_dword_800C3594 | (s08b_dword_800C3594 << 8);
}

void s08b_bunsin2_800CE064(Work *work)
{
    work->field_1968 = s08b_dword_800C3458;
    work->field_1970 = s08b_dword_800C3454 | (s08b_dword_800C3454 << 8);
}

void s08b_bunsin2_800CE0A4(Work *work)
{
    int index;

    index = GV_Time % 6;
    if (GV_DiffVec3(&s08b_dword_800C3460[index], &GM_PlayerPosition) < 3000)
    {
        index++;
        if (index >= 6)
        {
            index = 0;
        }
    }

    work->field_1968 = s08b_dword_800C3460[index];
    work->field_1970 = HZD_GetAddress(work->control.map->hzd, &work->field_1968, -1);
}
void s08b_bunsin2_800CE180(Work *work)
{
    int time;
    int index;

    time = GV_Time;
    index = time % 4;
    index += work->field_7D8;
    if (index >= 4)
    {
        index -= 4;
    }

    work->field_1968 = s08b_dword_800C3490[index];
    work->field_1970 = HZD_GetAddress(work->control.map->hzd, &work->field_1968, -1);
}

void s08b_bunsin2_800CE21C(Work *work)
{
    int index;

    index = GV_Time % 4;
    if (GV_DiffVec3(&s08b_dword_800C34B0[index], &GM_PlayerPosition) < 3000)
    {
        index++;
        if (index >= 6)
        {
            index = 0;
        }
    }

    work->field_1968 = s08b_dword_800C34B0[index];
    work->field_1970 = HZD_GetAddress(work->control.map->hzd, &work->field_1968, -1);
}
void s08b_bunsin2_800CE21C(Work *work);

void s08b_bunsin2_800CE2E8(Work *work)
{
    int dist1;
    int dist2;
    int index;

    dist1 = GV_DiffVec3(&s08b_dword_800C34B0[2], &GM_PlayerPosition);
    dist2 = GV_DiffVec3(&s08b_dword_800C34B0[3], &GM_PlayerPosition);

    if (dist1 < dist2)
    {
        index = 3;
    }
    else
    {
        index = 2;
    }

    work->field_1968 = s08b_dword_800C34B0[index];
    work->field_1970 = HZD_GetAddress(work->control.map->hzd, &work->field_1968, -1);
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE398.s")
void s08b_bunsin2_800CE398(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE584.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE800.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE8A0.s")

void s08b_bunsin2_800CE9BC(Work *work)
{
    int idx = work->field_19E0;
    MAP *map;

    work->field_19E0 = idx + 1;
    work->field_1968 = s08b_dword_800C34F8[idx];
    map = work->control.map;
    work->field_1970 = HZD_GetAddress(map->hzd, &work->field_1968, -1);
}
void s08b_bunsin2_800CE9BC(Work *work);

int s08b_bunsin2_800CEA34(Work *work, int address)
{
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int      from;
    int      to;
    int      dist;
    int      zone_index;

    hzd = work->control.map->hzd;
    from = HZD_GetAddress(hzd, &work->field_1968, -1) & 0xFF;
    to = address & 0xFF;

    zone_index = HZD_FarZoneNavigate(hzd, from, to, &dist);
    if (dist < HZD_GetRoute(hzd, from, to))
    {
        return -1;
    }

    zone = HZD_GetZone(hzd, zone_index);
    work->field_1968.vx = zone->x;
    work->field_1968.vy = zone->y;
    work->field_1968.vz = zone->z;
    work->field_1970 = (zone_index << 8) | zone_index;

    work->field_198C = work->field_1968;
    work->field_1988 = work->field_1970;
    return dist;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEB40.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CECB4.s")
int s08b_bunsin2_800CECB4(Work *work);

int s08b_bunsin2_800CEE18(Work *work)
{
    int ret;
    if ((work->field_19D0 & 0x1F) == 0)
    {
        work->field_1978 = -1;
        work->field_1974 = -1;
        s08b_bunsin2_800CECB4(work);
    }
    ret = s08b_bunsin2_800CECB4(work);
    work->field_19B4 = ret;
    return (unsigned int)ret >> 31;
}

int s08b_bunsin2_800CEE68(Work *work)
{
    int ret;
    if ((work->field_19D0 & 0x1F) == 0)
    {
        work->field_1978 = -1;
        work->field_1974 = -1;
        s08b_bunsin2_800CECB4(work);
    }
    ret = s08b_bunsin2_800CECB4(work);
    work->field_19B4 = ret;
    return (unsigned int)ret >> 31;
}

int s08b_bunsin2_800CEEB8(Work *work, int arg1)
{
    SVECTOR vec;
    int     dx, dz;

    dx = work->field_1968.vx - work->control.mov.vx;
    vec.vx = dx;
    dz = work->field_1968.vz - work->control.mov.vz;
    vec.vz = dz;

    if (dx > -arg1 && dx < arg1 && dz > -arg1 && dz < arg1)
    {
        return 1;
    }
    work->field_19B4 = GV_VecDir2(&vec);
    return 0;
}

int s08b_bunsin2_800CEF34(int a, int b)
{
    short *p;
    int    i;

    if (a > b)
    {
        SWAP(a, b);
    }
    p = s08b_dword_800C3510;
    for (i = 0; i < 2; i++, p += 2)
    {
        if (a == p[0] && b == p[1])
        {
            return 1;
        }
    }
    return 0;
}

int s08b_bunsin2_800CEF94(NinjaClone *p, int n, int initial)
{
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sum += p->field_0;
        p++;
    }
    return sum + initial;
}

void s08b_bunsin2_800CEFC0(NinjaClone *clones, int val, short *out_count, short *out_rem)
{
    int cur = val;
    int count = -1;

    while (cur >= 0)
    {
        val = cur;
        count++;
        cur = val - clones->field_0;
        clones++;
    }
    *out_count = count;
    *out_rem = val;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEFF4.s")
int s08b_bunsin2_800CF150(Work *work)
{
    CONTROL *control = &work->control;
    int      hit;

    if (work->field_1A2C < 1000 && GV_DiffDirAbs(control->rot.vy, work->field_1A28) < 0x400)
    {
        if (HZD_OnlineHazardCheck(control->map->hzd, &GM_PlayerPosition, &control->mov, 0xF, 2) == 0)
        {
            if (GV_Time & 1)
            {
                return 13;
            }

            return 16;
        }

        return 0;
    }

    if (work->field_1A2C < 2000)
    {
        if (GV_DiffDirAbs(control->rot.vy, work->field_1A28) < 0x200)
        {
            hit = HZD_OnlineHazardCheck(control->map->hzd, &GM_PlayerPosition, &control->mov, 0xF, 2);
            if (hit != 0)
            {
                return 18;
            }

            return 12;
        }

        return 0;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF254.s")
int s08b_bunsin2_800CF254(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF354.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF464.s")
int s08b_bunsin2_800CF464(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF54C.s")
int s08b_bunsin2_800CF54C(Work *work);

void s08b_bunsin2_800CF660(Work *work)
{
    switch (work->field_1A34)
    {
    case 2:
        s08b_dword_800C3448 = 0;
        s08b_bunsin2_800CE2E8(work);
        work->field_19C8 = 7;
        work->field_19CC = 0x17;
        break;

    case 1:
        s08b_dword_800C3448 = 0;
        work->field_19C8 = 7;
        work->field_19CC = 0x17;
        break;

    case 3:
    case 4:
        work->field_19C8 = 7;
        work->field_19CC = 0x17;
        s08b_dword_800C3448++;
        break;
    }
}

void s08b_bunsin2_800CF704(Work *work)
{
    int s = work->field_19D0;
    int r;

    if (s == 0)
    {
        s08b_dword_800C3440 = 0;
        s08b_dword_800C3444 = 0;
        s08b_dword_800C3448 = 0;
        s08b_dword_800C344C = 0;
        s08b_dword_800C3450 = 0;
        GM_AlertModeSet(4);
        s08b_bunsin2_800D53E8(1, 0xEA60);
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40;
        GM_VoxStream(work->field_1A98[0], 0);
        s08b_ninja_800C79D4(0);
        work->field_19B4 = work->field_1A28;
    }
    if (s >= 0xB)
    {
        r = GM_StreamStatus();
        if (r == -1)
        {
            s08b_ninja_800C79D4(2);
            s08b_bunsin2_800D5434();
            work->field_1964 = 0;
            work->field_1966 = r;
            work->field_19D4 = 0;
            GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40);
            s08b_bunsin2_800CEB40(work);
            work->field_19C4 = 3;
            work->field_19C8 = 0;
            work->field_19CC = 0x18;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
            return;
        }
    }
    if (s < 0x50)
    {
        work->field_19B0 = 9;
        work->field_19B4 = work->field_1A28;
    }
    else if (s == 0x50)
    {
        work->field_19B0 = 0x15;
    }
    else if (s >= 0xCF)
    {
        work->field_19B0 = 9;
    }
    work->field_19D0 = work->field_19D0 + 1;
}
void s08b_bunsin2_800CF704(Work *work);

void s08b_bunsin2_800CF880(Work *work)
{
    int s;

    if (work->field_19D0 == 0)
    {
        GM_VoxStream(work->field_1A98[1], 0);
        work->field_19B4 = work->field_1A28;
    }
    if (work->field_19D0 >= 0xB)
    {
        s = GM_StreamStatus();
        if (s == -1)
        {
            work->field_1964 = 0;
            work->field_1966 = s;
            work->field_19D4 = 0;
            GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40);
            s08b_bunsin2_800CEB40(work);
            work->field_19C4 = 1;
            work->field_19C8 = 0;
            work->field_19CC = 0x17;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
            return;
        }
    }
    work->field_19B0 = 7;
    work->field_19D0 = work->field_19D0 + 1;
}
void s08b_bunsin2_800CF880(Work *work);

int s08b_bunsin2_800CF950(void)
{
    return 1;
}

int s08b_bunsin2_800CF958(void)
{
    return 1;
}

int s08b_bunsin2_800CF960(Work *work)
{
    CONTROL *control = &work->control;

    if (work->field_19D0 == 5)
    {
        work->field_1A1C = Bunsin2_800C8F04(control->name, GM_CurrentMap, control, 2);
    }
    else if (work->field_19D0 == 4)
    {
        work->field_1A18 = Bunsin2_800C8F04(control->name, GM_CurrentMap, control, 1);
    }

    if (work->field_19D0 >= 6)
    {
        work->field_19C0 |= 4;
    }
    else
    {
        work->field_19B4 = work->field_1A28;
    }

    if (work->field_19D0 >= 21)
    {
        return 1;
    }

    work->field_19B0 = 7;
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800CFA30(Work *work)
{
    int v = ++work->field_19D0;
    if (v == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }
    if (v >= 71)
    {
        work->field_19B0 = 28;
    }
    return work->field_19D0 >= 161;
}

int s08b_bunsin2_800CFA80(Work *work)
{
    int n = work->field_19D0 + 1;
    work->field_19D0 = n;

    if (n == 1)
    {
        work->field_1A14 = 1;
        work->field_19B0 = 0x19;
        if (work->field_1A94 >= 0)
        {
            GCL_ExecProc(work->field_1A94, 0);
        }
        return 0;
    }
    if (n == 0x3C)
    {
        if (GM_StreamStatus() == -1 &&
            GM_GameOverTimer == 0 &&
            GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[18], 0);
        }
    }
    if (work->field_19D0 == 0x46)
    {
        work->field_1A04 = 1;
        s08b_p_sphere_800D9834(&work->body.objs, &work->field_1A04);
    }
    if (work->field_19D0 >= 0x47)
    {
        work->field_19B0 = 0x1C;
    }
    if (work->field_19D0 >= 0xA1 && GM_StreamStatus() == -1)
    {
        work->field_1A04 = 3;
        return 1;
    }
    return 0;
}
int s08b_bunsin2_800CFA80(Work *work);

int s08b_bunsin2_800CFB98(Work *work)
{
    CONTROL *control = &work->control;
    SVECTOR  vec;
    int      dir;

    if (work->field_19D0 < 10)
    {
        if (work->field_7D8 == 1)
        {
            dir = control->rot.vy + 0x400;
        }
        else
        {
            dir = control->rot.vy - 0x400;
        }

        GV_DirVec2(dir & 0xFFF, 100, &vec);
        control->mov.vx += vec.vx;
        control->mov.vz += vec.vz;
    }

    if (s08b_dword_800E4340 == 1)
    {
        return 1;
    }

    work->field_19B0 = 7;
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800CFC64(Work *work)
{
    work->field_19D0++;
    return s08b_bunsin2_800CEEB8(work, 500);
}

int s08b_bunsin2_800CFC90(Work *work)
{
    s08b_bunsin2_800CEEB8(work, 0x64);
    if (work->field_19D0 == 0)
    {
        work->field_19B0 = 1;
        work->field_19D0++;
        return 0;
    }
    if (++work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800CFCF8(Work *work)
{
    if (work->field_19D0 == 0)
    {
        work->field_1B28 = -1;
        s08b_bunsin2_800CE800(work, s08b_bunsin2_800CE584(work));
        work->field_19D0 = work->field_19D0 + 1;
        return 0;
    }
    if (work->field_19D0 == 1)
    {
        work->field_19B4 = work->field_1B28;
    }
    work->field_19D0 = work->field_19D0 + 1;
    if (work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}
int s08b_bunsin2_800CFD88(Work *work)
{
    if (work->field_19D0 == 0)
    {
        work->field_19B0 = 5;
    }
    if (work->field_19D0 >= 0x3D && work->body.is_end != 0)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}
int s08b_bunsin2_800CFDE0(Work *work)
{
    if (work->field_19D0 == 0)
    {
        work->field_19B0 = 6;
    }
    if (work->field_19D0 >= 0x3D)
    {
        printf(s08b_aKorekorekor_800E39A8);
        return 1;
    }
    if (work->body.is_end != 0)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFE54.s")

int s08b_bunsin2_800D0004(Work *work)
{
    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800CE398(work);
        work->field_19B0 = 6;
    }
    if (work->field_19D0 >= 0x1F && work->body.is_end != 0)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D0078(Work *work)
{
    if (work->field_19D0 == 0)
    {
        work->field_19B0 = 5;
    }

    if (work->field_19D0 == 30)
    {
        if (GM_ItemTypes[GM_Item + 1] & 2)
        {
            GM_Item = -1;
        }

        if (GM_WeaponTypes[GM_Weapon + 1] & 0x200)
        {
            GM_Weapon = -1;
        }

        if (GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_GameStatus |= STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF | STATE_CUT_IN;
            s08b_ninja_800C79D4(5);
        }

        s08b_bunsin2_800D53E8(0, 0xEA60);
    }

    if (work->body.is_end != 0)
    {
        return 1;
    }

    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D018C(Work *work)
{
    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800CE21C(work);
        work->field_19B0 = 5;
    }
    if (work->field_19D0 >= 0x3D && work->body.is_end != 0)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D0200(Work *work)
{
    int v;

    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800CDE74(work);
    }
    s08b_bunsin2_800CEEB8(work, 0x64);

    v = work->field_19D0;
    if (v == 0)
    {
        work->field_19B0 = 1;
        work->field_19D0 = work->field_19D0 + 1;
        return 0;
    }
    {
        int ret = work->body.is_end;
        work->field_19D0 = v + 1;
        return ret;
    }
}
int s08b_bunsin2_800D0278(Work *work)
{
    if (work->field_19D0 >= 0x79)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D02A0(Work *work)
{
    int v = ++work->field_19D0;
    if (v == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D02E8(Work *work)
{
    int v = ++work->field_19D0;
    if (v == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D0330(Work *work)
{
    if (work->field_1A34 != 0)
    {
        GM_StreamPlayStop();
        work->field_19CC = 0x17;
        return 1;
    }
    if (okajima_CHAF_LIFE < 0x5A)
    {
        GM_StreamPlayStop();
        work->field_19CC = 0x1C;
        return 1;
    }
    if (work->field_19D0 == 0 &&
        GM_StreamStatus() == -1 &&
        GM_GameOverTimer == 0 &&
        GM_Vitality > 0)
    {
        GM_VoxStream(work->field_1A98[17], 0);
    }
    work->field_19B0 = 0x1A;
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D0410(Work *work)
{
    if (!(GM_GameStatus & STATE_CHAFF))
    {
        return 1;
    }
    work->field_19B0 = 27;
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D044C(Work *work)
{
    int time;

    time = work->field_19D0 + 1;
    work->field_19D0 = time;

    if (time == 1)
    {
        work->field_19B0 = 25;
        return 0;
    }

    if (time == 50)
    {
        NewBlast(&work->body.objs->objs[4].world, blast_data_8009F4B8);
    }

    if (time == 60)
    {
        NewBlast(&work->body.objs->objs[7].world, blast_data_8009F4B8);
    }

    if (time == 65)
    {
        NewBlast(&work->body.objs->objs[12].world, blast_data_8009F4B8);
    }

    if (time == 69)
    {
        NewBlast(&work->body.objs->objs[1].world, blast_data_8009F4B8);
    }

    if (work->field_19D0 >= 301)
    {
        return 1;
    }

    return work->field_19A8;
}

int s08b_bunsin2_800D0530(Work *work)
{
    int v;

    v = work->field_19D0;
    work->field_19B0 = 22;
    v++;
    work->field_19D0 = v;
    return v >= 0x1F;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0550.s")

int s08b_bunsin2_800D0688(Work *work)
{
    return work->field_19D0++;
}

int s08b_bunsin2_800D06A0(Work *work)
{
    int count = work->field_19D0;
    int n;

    if (count == 0)
    {
        GM_StreamPlayStop();
        work->field_19D0++;
        return 0;
    }
    n = count + 1;
    work->field_19D0 = n;
    if (n >= 0x12D)
    {
        return 1;
    }
    if (n >= 0x79 && work->field_19A4 == 0)
    {
        return 1;
    }
    return work->field_19A8;
}
int s08b_bunsin2_800D0720(Work *work)
{
    int val;

    val = work->field_1968.pad;
    return val & 0x1F;
}

int s08b_bunsin2_800D072C(Work *work)
{
    int r1;
    int a0, a1;

    s08b_bunsin2_800CDF68(work);
    r1 = s08b_bunsin2_800CEE18(work);
    a0 = *(unsigned char *)&work->field_1978;
    a1 = *(unsigned char *)&work->field_197C;
    work->field_19D0++;
    if (s08b_bunsin2_800CEF34(a0, a1))
    {
        return 2;
    }
    return r1;
}

int s08b_bunsin2_800D0784(Work *work)
{
    int address;

    s08b_bunsin2_800CDF68(work);

    if (work->field_19D0 & 0x10)
    {
        address = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);
        work->field_1978 = address;
        if (HZD_ReachTo(work->control.map->hzd, address, work->field_1970) >= 2)
        {
            return 1;
        }
    }

    work->field_19B4 = work->field_1A28;
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D0814(Work *work)
{
    int r1 = s08b_bunsin2_800CEE68(work);
    int a0 = *(unsigned char *)&work->field_1978;
    int a1 = *(unsigned char *)&work->field_197C;
    int r2;

    work->field_19D0++;
    r2 = s08b_bunsin2_800CEF34(a0, a1);
    if (r2 != 0)
    {
        return 2;
    }
    return r1;
}

int s08b_bunsin2_800D0864(Work *work)
{
    SVECTOR vec;

    GV_SubVec3(&work->field_1968, &work->control.mov, &vec);
    vec.vy = 0;
    work->field_19B4 = GV_VecDir2(&vec);
    if (GV_VecLen3(&vec) < 0x12C)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D08C8(Work *work)
{
    int r1;
    int a0, a1;

    r1 = s08b_bunsin2_800CEE68(work);
    a0 = *(unsigned char *)&work->field_1978;
    a1 = *(unsigned char *)&work->field_197C;
    work->field_19D0++;

    if (s08b_bunsin2_800CEF34(a0, a1))
    {
        return 2;
    }

    if (r1 != 0)
    {
        if ((unsigned int)s08b_bunsin2_800CEA34(work, GM_PlayerAddress) >= 3)
        {
            return 1;
        }
    }

    return 0;
}
int s08b_bunsin2_800D093C(Work *work)
{
    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800CE0A4(work);
        work->field_19B0 = 5;
    }
    if (work->field_19D0 >= 0xB)
    {
        work->field_19C0 |= 2;
    }
    if (work->field_19D0 >= 0x3D)
    {
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D09C4(Work *work)
{
    int g;
    int threshold;

    if (work->field_19D0 == 0)
    {
        work->field_19B4 = work->field_1A28;
        s08b_dword_800C3450 = s08b_dword_800C3450 + 1;
    }
    work->field_19C0 |= 2;

    g = GM_GameLevel;
    if (g == 1)
    {
        threshold = 0x96;
    }
    else if (g <= 0)
    {
        threshold = 0x1C2;
    }
    else if (g < 4)
    {
        threshold = 0x5A;
    }
    else
    {
        threshold = 0x1C2;
    }

    if (threshold < work->field_19D0)
    {
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D0A54(Work *work)
{
    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    if (work->field_1A2C < 2000)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

void s08b_bunsin2_800D0A90(Work *work)
{
    int g;
    int threshold;

    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    if (work->field_19D0 == 0)
    {
        work->field_19DC = work->field_19DC + 1;
    }

    g = GM_GameLevel;
    if (g == 1)
    {
        threshold = 0xF;
    }
    else if (g <= 0)
    {
        threshold = 0x3C;
    }
    else if (g < 4)
    {
        threshold = 1;
    }
    else
    {
        threshold = 0x3C;
    }

    if (threshold < work->field_19D0)
    {
        work->field_19C8 = 3;
        work->field_19CC = 8;
        work->field_19D0 = 0;
    }
    else
    {
        work->field_19D0 = work->field_19D0 + 1;
    }
}
void s08b_bunsin2_800D0B1C(Work *work)
{
    work->field_19B0 = 7;
    if (work->field_19D0 >= 11)
    {
        work->field_19CC = 5;
        work->field_19D0 = 0;
    }
    else
    {
        work->field_19D0++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0B4C.s")
void s08b_bunsin2_800D0CD8(Work *work)
{
    work->field_19B4 = work->field_1A28;
    if (s08b_bunsin2_800CF354(work))
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }
    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800D4FBC(&work->body.objs->objs[6].world, 0);
    }
    if (work->field_19D0 >= 0x1F)
    {
        s08b_bunsin2_800CDE74(work);
        work->field_19C8 = 1;
        work->field_19CC = 0x1A;
        work->field_19D0 = 0;
    }
    else
    {
        work->field_19B0 = 9;
        work->field_19D0 = work->field_19D0 + 1;
    }
}
void s08b_bunsin2_800D0D80(Work *work)
{
    int dist;

    work->field_19B4 = work->field_1A28;
    dist = work->field_1A2C;

    if (work->field_19D0 == 0)
    {
        work->field_19E0 = 0;
    }

    if (s08b_bunsin2_800CF54C(work) != 0)
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }

    if (dist >= 3001)
    {
        work->field_19C8 = 3;
        work->field_19CC = 8;
        work->field_19D0 = 0;
        return;
    }

    if (dist < 1000)
    {
        if (!(GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND | PLAYER_CB_BOX)) || (GV_Time & 3) == 0)
        {
            work->field_19E0++;
        }
    }

    if (dist < 500 || work->field_19E0 >= 16)
    {
        work->field_19C8 = 6;
        work->field_19CC = 15;
        work->field_19D0 = 0;
        return;
    }

    if (work->field_19D0 >= 31)
    {
        work->field_19C8 = 6;
        if (dist < 1000)
        {
            work->field_19CC = 15;
        }
        else
        {
            work->field_19CC = 16;
        }

        work->field_19D0 = 0;
        return;
    }

    work->field_19B0 = 9;
    work->field_19D0++;
}
void s08b_bunsin2_800D0EB8(Work *work)
{
    int limit;

    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;

    if (GM_GameLevel == GM_LEVEL_NORMAL)
    {
        limit = 15;
    }
    else
    {
        limit = 30;
        if (GM_GameLevel > GM_LEVEL_EASY)
        {
            if (GM_GameLevel < GM_LEVEL_EXTREME + 1)
            {
                limit = 5;
            }
        }
    }

    if (limit < work->field_19D0 && !(GM_PlayerStatus & PLAYER_DOWNED))
    {
        work->field_19C8 = 5;
        work->field_19CC = 24;
        work->field_19D0 = 0;
        return;
    }

    if (work->field_19D0 >= 61)
    {
        work->field_19CC = 19;
        work->field_19D0 = 0;
        return;
    }

    work->field_19D0++;
}

int s08b_bunsin2_800D0F54(Work *work)
{
    work->field_19B0 = 7;
    work->field_19B4 = work->field_1A28;
    if (work->field_19D0 >= 11)
    {
        return 1;
    }
    work->field_19D0++;
    return 0;
}

int s08b_bunsin2_800D0F88(Work *work)
{
    int limit;
    int level;

    if (work->field_19D0 == 0)
    {
        work->field_19B4 = work->field_1A28;
    }

    level = GM_GameLevel;
    limit = 5;
    if (level == GM_LEVEL_NORMAL)
    {
        work->field_19C0 |= 2;
    }
    else if (level > GM_LEVEL_EASY)
    {
        if (level < GM_LEVEL_EXTREME + 1)
        {
            limit = 1;
            work->field_19C0 |= 2;
        }
        else
        {
            limit = 10;
        }
    }
    else
    {
        limit = 10;
    }

    if (limit < work->field_19D0)
    {
        return 1;
    }

    work->field_19D0++;
    return 0;
}
int s08b_bunsin2_800D1014(Work *work)
{
    int g;
    int threshold;
    int n;

    g = GM_GameLevel;
    if (g == 1)
    {
        threshold = 4;
    }
    else if (g <= 0)
    {
        threshold = 0xA;
    }
    else if (g < 4)
    {
        threshold = 1;
    }
    else
    {
        threshold = 0xA;
    }

    if (threshold < work->field_19D0)
    {
        if (GM_PlayerStatus & 0x1060)
        {
            work->field_19B0 = 0x12;
        }
        else if (GM_Weapon == -1)
        {
            work->field_19B0 = 0x11;
        }
        else
        {
            work->field_19B0 = 0xC;
        }
    }
    else
    {
        work->field_19B0 = 7;
    }

    n = work->field_19D0 + 1;
    work->field_19D0 = n;
    if (n >= 0x12D)
    {
        return 1;
    }
    if (n >= 9)
    {
        return work->field_19A8;
    }
    return 0;
}
int s08b_bunsin2_800D10C4(Work *work)
{
    if (GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND | PLAYER_CB_BOX))
    {
        work->field_19B0 = 0x12;
    }
    else if (GM_Weapon == WP_None)
    {
        work->field_19B0 = 0x10;
    }
    else
    {
        work->field_19B0 = 0xD;
    }
    if (++work->field_19D0 == 1)
    {
        return 0;
    }
    if (work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D1138(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND | PLAYER_CB_BOX))
        {
            work->field_19B0 = 0x12;
        }
        else
        {
            work->field_19B0 = 0xE;
        }
    }
    if (++work->field_19D0 == 1)
    {
        return 0;
    }
    if (work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D11A8(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND | PLAYER_CB_BOX))
        {
            work->field_19B0 = 0x12;
        }
        else
        {
            work->field_19B0 = 0xF;
        }
    }
    if (++work->field_19D0 == 1)
    {
        return 0;
    }
    if (work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D1218(Work *work)
{
    int v;
    work->field_19B0 = 16;
    v = ++work->field_19D0;
    if (v == 1)
    {
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D125C(Work *work)
{
    int v;
    work->field_19B0 = 17;
    v = ++work->field_19D0;
    if (v == 1)
    {
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D12A0.s")

int s08b_bunsin2_800D12EC(Work *work)
{
    work->field_19B0 = 0x13;
    if (work->field_19D0 == 0)
    {
        work->field_19B4 = work->field_1A28;
        work->field_19D0 = 1;
        s08b_bunsin2_800CDF68(work);
        return 0;
    }
    if (++work->field_19D0 >= 0x12D)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D1348(Work *work)
{
    int v;
    work->field_19B0 = 20;
    v = ++work->field_19D0;
    if (v == 1)
    {
        return 0;
    }
    if (v >= 301)
    {
        return 1;
    }
    return work->field_19A8;
}

int s08b_bunsin2_800D138C(Work *work)
{
    if (work->field_19D0 == 0)
    {
        work->field_1A04 = 1;
        s08b_p_sphere_800D9834(&work->body.objs, &work->field_1A04);
    }
    if (work->field_19D0 >= 0x1F)
    {
        return 1;
    }
    work->field_19B0 = 0x1C;
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1400(Work *work)
{
    int cond;

    switch (work->field_19E0)
    {
    case 1:
        cond = work->field_19D0 < 0x1F;
        break;
    case 2:
        cond = work->field_19D0 < 0x10;
        break;
    default:
        cond = work->field_19D0 < 0xB;
        break;
    }

    if (!cond)
    {
        return 1;
    }

    if (work->field_19D0 == 4 &&
        work->field_19DC % 3 == 0 &&
        GM_StreamStatus() == -1 &&
        GM_GameOverTimer == 0 &&
        GM_Vitality > 0)
    {
        GM_VoxStream(work->field_1A98[7], 0);
    }
    work->field_19B0 = 0x1D;
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1514(Work *work)
{
    int below;

    switch (work->field_19E0)
    {
    case 1:
        below = work->field_19D0 < 0x3D;
        break;
    case 2:
        below = work->field_19D0 < 0x2E;
        break;
    default:
        below = work->field_19D0 < 0x1F;
        break;
    }
    if (below)
    {
        work->field_19B0 = 0x1E;
        work->field_19D0++;
        return 0;
    }
    return 1;
}

int s08b_bunsin2_800D1588(Work *work)
{
    int s = work->field_19D0;

    if (s == 0)
    {
        if (GM_StreamStatus() == -1 &&
            GM_GameOverTimer == 0 &&
            GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[6], 0);
        }
    }
    if (s == 1)
    {
        return 1;
    }
    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1638(Work *work)
{
    int s = work->field_19D0;

    if (s == 0xA)
    {
        if (GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[3], 0);
        }
    }
    if (s >= 0x83 && GM_StreamStatus() == -1)
    {
        s08b_ninja_800C79D4(2);
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40);
        s08b_bunsin2_800D5434();
        return 1;
    }
    work->field_19B4 = work->field_1A28;
    if (s < 0x64)
    {
        work->field_19B0 = 8;
    }
    else if (s == 0x64)
    {
        work->field_19B0 = 0xA;
    }
    else if (s >= 0xCD)
    {
        work->field_19B0 = 8;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1738(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_StreamStatus() == -1 &&
            GM_GameOverTimer == 0 &&
            GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[1], 0);
        }
        if (work->field_1A90 >= 0)
        {
            GCL_ExecProc(work->field_1A90, 0);
        }
    }
    if (work->field_19D0 >= 2)
    {
        return 1;
    }
    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D17F8(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_ItemTypes[GM_Item + 1] & 2)
        {
            GM_Item = -1;
        }
        if (GM_WeaponTypes[GM_Weapon + 1] & 0x200)
        {
            GM_Weapon = -1;
        }
        if (GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40;
            s08b_ninja_800C79D4(7);
        }
    }
    if (work->field_19D0 == 0x1E)
    {
        if (GM_StreamStatus() == -1 &&
            GM_GameOverTimer == 0 &&
            GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[12], 0);
        }
    }
    work->field_19B0 = 8;
    work->field_19B4 = work->field_1A28;
    if (work->field_19D0 >= 0x1F && GM_StreamStatus() == -1)
    {
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D195C(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_StreamStatus() == -1 &&
            GM_GameOverTimer == 0 &&
            GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[14], 0);
        }
    }
    work->field_19B0 = 9;
    work->field_19B4 = work->field_1A28;
    work->field_19C0 |= 2;
    if (work->field_19D0 >= 0x1F && GM_StreamStatus() == -1)
    {
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1A18(Work *work)
{
    work->field_19C0 |= 2;
    if (work->field_19D0 == 0)
    {
        s08b_bunsin2_800CE0A4(work);
        work->field_19B0 = 5;
    }
    if (work->field_19D0 == 0x1E)
    {
        if (GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            s08b_ninja_800C79D4(6);
        }
    }
    if (work->field_19D0 >= 0x83 && GM_StreamStatus() == -1)
    {
        s08b_ninja_800C79D4(1);
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40);
        s08b_bunsin2_800D5434();
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
int s08b_bunsin2_800D1AF8(Work *work)
{
    if (work->field_19D0 == 0)
    {
        if (GM_ItemTypes[GM_Item + 1] & 2)
        {
            GM_Item = -1;
        }
        if (GM_WeaponTypes[GM_Weapon + 1] & 0x200)
        {
            GM_Weapon = -1;
        }
        if (GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40;
            s08b_ninja_800C79D4(8);
        }
    }
    if (work->field_19D0 == 0x1E)
    {
        if (GM_StreamStatus() == -1 && GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[5], 0);
        }
    }
    if (work->field_19D0 == 0x82)
    {
        if (GM_StreamStatus() == -1 && GM_GameOverTimer == 0 && GM_Vitality > 0)
        {
            GM_VoxStream(work->field_1A98[10], 0);
        }
    }
    work->field_19B4 = work->field_1A28;
    if (work->field_19D0 >= 0x83)
    {
        work->field_19B0 = 0x17;
    }
    else
    {
        work->field_19B0 = 0x18;
    }
    if (work->field_19D0 >= 0xE7 && GM_StreamStatus() == -1)
    {
        s08b_ninja_800C79D4(1);
        GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFE_OFF | STATE_MENU_DISABLE | STATE_PADRELEASE | 0x40);
        s08b_bunsin2_800D5434();
        return 1;
    }
    work->field_19D0 = work->field_19D0 + 1;
    return 0;
}
void s08b_bunsin2_800D1CF4(Work *work)
{
    switch (work->field_19CC)
    {
    case 0:
        s08b_bunsin2_800CF704(work);
        break;
    case 1:
        s08b_bunsin2_800CF880(work);
        break;
    }
}

void s08b_bunsin2_800D1D44(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x18:
        s08b_bunsin2_800D0B4C(work);
        break;
    case 7:
        if (s08b_bunsin2_800CFCF8(work) != 0)
        {
            work->field_19CC = 0x18;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    case 0x20:
        s08b_bunsin2_800D0CD8(work);
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1DE0.s")
void s08b_bunsin2_800D1DE0(Work *work);
void s08b_bunsin2_800D1EC8(Work *work)
{
    extern int s08b_bunsin2_800CF950();
    switch (work->field_19CC)
    {
    case 0:
        if (s08b_bunsin2_800CF950(work) != 0)
        {
            s08b_bunsin2_800CE024(work);
            work->field_19CC = 5;
            work->field_19D0 = 0;
        }
        break;
    case 5:
        if (s08b_bunsin2_800CFDE0(work) != 0)
        {
            work->field_19CC = 0x17;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    case 0x17:
        if (s08b_bunsin2_800D0688(work) >= 0x97)
        {
            work->field_19C8 = 4;
            work->field_19CC = 0xA;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        else
        {
            work->field_19B0 = 0x16;
        }
        break;
    }
}
void s08b_bunsin2_800D1F9C(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800D018C(work) != 0)
        {
            work->field_19CC = 0x17;
            work->field_19D0 = 0;
        }
        break;

    case 0x17:
        if (s08b_bunsin2_800D0688(work) >= 0x97 || work->field_1A2C < 3000)
        {
            work->field_19CC = 0;
            work->field_19D0 = 0;
            return;
        }

        work->field_19B0 = 0x16;
        break;

    case 0:
        if (s08b_bunsin2_800CF960(work) != 0)
        {
            s08b_dword_800E4340 = 1;
            s08b_bunsin2_800CE180(work);
            work->field_19CC = 3;
            work->field_19D0 = 0;
            return;
        }
        break;

    case 3:
        work->field_19C0 |= 4;
        if (s08b_bunsin2_800CFD88(work) != 0)
        {
            work->field_19C8 = 2;
            work->field_19CC = 8;
            work->field_19D0 = 0;
        }
        break;
    }

    if (work->field_1A34 != 0)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x1F;

        if (work->field_1A18 != NULL)
        {
            GV_DestroyActor(work->field_1A18);
            work->field_1A18 = NULL;
        }

        if (work->field_1A1C != NULL)
        {
            GV_DestroyActor(work->field_1A1C);
            work->field_1A1C = NULL;
        }

        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}

void s08b_bunsin2_800D2104(Work *work)
{
    if (work->field_19CC == 0 && s08b_bunsin2_800CFA30(work))
    {
        work->field_19C8 = 1;
        work->field_19CC = 6;
        work->field_19D0 = 0;
        work->field_19E0 = 0;
    }
}

void s08b_bunsin2_800D2158(Work *work)
{
    if (work->field_19CC == 0 && s08b_bunsin2_800CFA80(work))
    {
        work->field_19E0 = 0;
        work->field_19DC = 0;
        s08b_bunsin2_800CE9BC(work);
        work->field_19C8 = 1;
        work->field_19CC = 5;
        work->field_19D0 = 0;
    }
}

void s08b_bunsin2_800D21B8(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D06A0(work))
        {
            if (work->field_1A38 == 1)
            {
                if (work->field_1A2C < 0x4B0)
                {
                    work->field_19C8 = 5;
                    work->field_19CC = 5;
                }
                else
                {
                    work->field_19C8 = 3;
                    work->field_19CC = 8;
                }
            }
            else
            {
                if (work->field_19E4 < 6)
                {
                    work->field_19C4 = 7;
                    work->field_19C8 = 0;
                    work->field_19CC = 0;
                }
                else
                {
                    work->field_19CC = 0x23;
                }
            }
            work->field_19D0 = 0;
        }
        break;
    case 0x1C:
        if (s08b_bunsin2_800D02E8(work))
        {
            work->field_19CC = 0x23;
            work->field_19D0 = 0;
        }
        break;
    case 0x23:
        if (s08b_bunsin2_800D0550(work))
        {
            if (work->field_1A2C < 0x4B0)
            {
                work->field_19C8 = 5;
                work->field_19CC = 5;
            }
            else
            {
                work->field_19C8 = 3;
                work->field_19CC = 8;
            }
            work->field_19D0 = 0;
        }
        else
        {
            work->field_19B0 = 0x16;
        }
        break;
    case 5:
        if (s08b_bunsin2_800CFDE0(work))
        {
            work->field_19C8 = 3;
            work->field_19CC = 8;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D231C(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D06A0(work))
        {
            if (work->field_19E4 < 6)
            {
                work->field_19C4 = 7;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else
            {
                work->field_19CC = 0x1C;
            }
            work->field_19D0 = 0;
        }
        break;
    case 0x1D:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D0330(work))
        {
            work->field_19D0 = 0;
        }
        break;
    case 0x1C:
        if (s08b_bunsin2_800D0410(work))
        {
            if (work->field_1A2C < 0x4B0)
            {
                work->field_19C8 = 5;
                work->field_19CC = 5;
            }
            else
            {
                work->field_19C8 = 3;
                work->field_19CC = 8;
            }
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2420(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            if (work->field_19E4 < 6)
            {
                work->field_19C4 = 7;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else
            {
                work->field_19CC = 0x1C;
            }

            work->field_19D0 = 0;
        }
        break;

    case 0x1D:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D0330(work) != 0)
        {
            work->field_19D0 = 0;
        }
        break;

    case 0x1C:
        if (s08b_bunsin2_800D0410(work) != 0)
        {
            s08b_bunsin2_800CDE74(work);
            work->field_19C8 = 1;
            work->field_19CC = 0x1A;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2510(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            if (work->field_19E4 < 6)
            {
                work->field_19C4 = 7;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else
            {
                work->field_19CC = 0x1C;
            }

            work->field_19D0 = 0;
        }
        break;

    case 0x1D:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D0330(work) == 0)
        {
            work->field_19C0 |= 2;
        }
        else
        {
            work->field_19D0 = 0;
        }
        break;

    case 0x1C:
        if (s08b_bunsin2_800D0410(work) != 0)
        {
            work->field_19C8 = 4;
            work->field_19CC = 0xA;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2600(Work *work)
{
    int time;
    int divisor;
    int dist;
    int command;

    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            time = work->field_19E4;
            if (time < 6)
            {
                work->field_19C4 = 7;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else
            {
                if (GM_GameStatus & STATE_CHAFF)
                {
                    work->field_19C8 = 9;
                    work->field_19CC = 0x1C;
                }
                else if (work->field_1A38 == 3)
                {
                    if (s08b_dword_800C3448 == 0)
                    {
                        s08b_dword_800C3448 = 2;
                        s08b_bunsin2_800CE2E8(work);
                        work->field_19C8 = 8;
                        work->field_19CC = 5;
                    }
                    else if (time < 0x79)
                    {
                        s08b_bunsin2_800CE2E8(work);
                        work->field_19C4 = 2;
                        work->field_19C8 = 8;
                        work->field_19CC = 5;
                    }
                    else
                    {
                        work->field_19DC++;

                        divisor = 3;
                        if (GM_GameLevel != GM_LEVEL_NORMAL)
                        {
                            divisor = 4;
                            if (GM_GameLevel > GM_LEVEL_EASY)
                            {
                                if (GM_GameLevel < GM_LEVEL_EXTREME + 1)
                                {
                                    divisor = 2;
                                }
                            }
                        }

                        if (work->field_19DC % divisor == 0)
                        {
                            work->field_19C8 = 6;
                            work->field_19CC = 0x13;
                        }
                        else
                        {
                            work->field_19CC = 7;
                        }
                    }
                }
                else
                {
                    goto reload;
                }

            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x22:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            work->field_19CC = 7;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 7:
        if (s08b_bunsin2_800CFCF8(work) != 0)
        {
            dist = work->field_1A2C;
            if (dist < 1000)
            {
                work->field_19C8 = 6;
                work->field_19CC = 0xF;
            }
            else if (dist < 5000)
            {
                work->field_19C8 = 6;
                work->field_19CC = 0x10;
            }
            else
            {
                command = 0x18;
                if (work->field_1A0C != 0)
                {
                    goto reload;
                }

                work->field_19C8 = 0;
                work->field_19CC = command;
            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 5:
        if (s08b_bunsin2_800CFDE0(work) != 0)
        {
reload:
            s08b_bunsin2_800CDE74(work);
            work->field_19C8 = 1;
            work->field_19CC = 0x1A;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2860(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            if (work->field_1A38 == 3)
            {
                work->field_19DC++;
            }

            if (work->field_19E4 < 6)
            {
                work->field_19C4 = 7;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else if (work->field_19DC >= 3)
            {
                s08b_bunsin2_800CE2E8(work);
                work->field_19C8 = 8;
                work->field_19C4 = 0;
                work->field_19CC = 5;
            }
            else
            {
                work->field_19C8 = 4;
                work->field_19CC = 10;
            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x22:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            work->field_19C8 = 4;
            work->field_19CC = 10;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x1C:
        if (s08b_bunsin2_800D02A0(work) != 0)
        {
            work->field_19C8 = 3;
            work->field_19C4 = 0;
            work->field_19CC = 8;
            work->field_19D0 = 0;
        }
        break;

    case 0x19:
        if (s08b_bunsin2_800D0200(work) != 0)
        {
            if (work->field_19E4 < 0x5B)
            {
                work->field_19C4 = 4;
                work->field_19C8 = 0;
                work->field_19CC = 0;
            }
            else
            {
                work->field_19C8 = 1;
                work->field_19CC = 6;
            }

            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D29DC(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            work->field_19CC = 0x1C;
            goto reset;
        }

        work->field_1A08 = 1;
        break;

    case 0x1D:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D0330(work) != 0)
        {
            s08b_dword_800C3448 = 0;
            goto reset;
        }
        break;

    case 0x1C:
        if (s08b_bunsin2_800D0410(work) != 0)
        {
            work->field_19C8 = 8;
            work->field_19CC = 0x26;
            s08b_dword_800C3448 = 0;
reset:
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2AB4(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            if (GM_GameStatus & STATE_CHAFF)
            {
                work->field_19C8 = 9;
                work->field_19CC = 0x1C;
            }
            else if (s08b_dword_800C3448 < 2)
            {
                work->field_19CC = 7;
            }
            else
            {
                s08b_bunsin2_800CE2E8(work);
                work->field_19C8 = 8;
                work->field_19CC = 5;
            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x22:
        if (s08b_bunsin2_800D06A0(work) != 0)
        {
            work->field_19C8 = 0;
            work->field_19CC = 0x18;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 5:
        if (s08b_bunsin2_800CFDE0(work) != 0)
        {
            work->field_19C8 = 8;
            work->field_19CC = 0x26;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 7:
        if (s08b_bunsin2_800CFCF8(work) != 0)
        {
            if (s08b_dword_800C3448 == 0)
            {
                work->field_19C8 = 8;
                work->field_19CC = 0x26;
            }
            else
            {
                work->field_19C8 = 0;
                work->field_19CC = 0x24;
            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2BFC(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D0688(work) >= 0x1F)
        {
            work->field_19C8 = 0;
            work->field_19CC = 5;
            work->field_19D0 = 0;
        }
        else
        {
            work->field_19B0 = 0x17;
            if (work->field_1A34 != 0)
            {
                work->field_19C8 = 7;
                work->field_19CC = 0x19;
                work->field_19D0 = 0;
                work->field_19D4 = 0;
            }
        }
        break;

    case 0x19:
        if (s08b_bunsin2_800D0200(work) != 0)
        {
            if (work->field_19E4 < 0x3D)
            {
                work->field_19C8 = 3;
                work->field_19C4 = 0;
                work->field_19CC = 8;
            }
            else
            {
                work->field_19C8 = 0;
                work->field_19CC = 5;
            }

            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x1D:
        if (s08b_bunsin2_800D044C(work) != 0)
        {
            GV_DestroyActor(&work->actor);
        }
        break;

    case 0x1F:
        if (s08b_bunsin2_800D0F54(work) != 0)
        {
            work->field_19C8 = 6;
            work->field_19CC = 0xE;
            work->field_19D0 = 0;
        }
        break;
    }
}

void s08b_bunsin2_800D2D3C(Work *work)
{
    switch (work->field_19CC)
    {
    case 0x17:
        if (s08b_bunsin2_800D0278(work))
        {
            work->field_19CC = 0x1D;
            work->field_19D0 = 0;
        }
        break;
    case 0x1D:
        if (s08b_bunsin2_800D044C(work))
        {
            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void s08b_bunsin2_800D2DB0(Work *work)
{
    int x;

    switch (work->field_19CC)
    {
    case 0x17:
        work->field_1A08 = 1;
        if (s08b_bunsin2_800D06A0(work) == 0)
        {
            return;
        }
        if (work->field_19E0 >= 3)
        {
            s08b_bunsin2_800CE064(work);
            x = work->field_1A8C;
            work->field_19CC = 0x1B;
            work->field_19C8 = 1;
            work->field_19B8 = 3;
            if (x >= 0 && GM_GameOverTimer == 0 && GM_Vitality > 0)
            {
                GCL_ExecProc(x, 0);
            }
        }
        else
        {
            s08b_bunsin2_800CE9BC(work);
            work->field_19C8 = 1;
            work->field_19CC = 5;
        }
        work->field_19D0 = 0;
        break;
    case 0x1D:
        s08b_bunsin2_800D0530(work);
        break;
    }
}
void s08b_bunsin2_800D2EA0(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800D0078(work) != 0)
        {
            work->field_19CC = 0x24;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x24:
        if (s08b_bunsin2_800D1638(work) != 0)
        {
            work->field_19C4 = 1;
            work->field_19C8 = 2;
            work->field_19CC = 8;
            work->field_19DC = 0;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x26:
        if (s08b_bunsin2_800D1738(work) != 0)
        {
            s08b_bunsin2_800CDE74(work);
            work->field_19C4 = 1;
            work->field_19C8 = 1;
            work->field_19CC = 0x1A;
            work->field_1A0C = 1;
            work->field_19DC = 0;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D2F80(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800D0078(work) != 0)
        {
            work->field_19CC = 0x24;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
            work->field_19DC = 0;
        }
        break;

    case 0x24:
        if (s08b_bunsin2_800D17F8(work) != 0)
        {
            work->field_19CC = 0x25;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x25:
        if (s08b_bunsin2_800D195C(work) != 0)
        {
            work->field_19CC = 0x26;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;

    case 0x26:
        if (s08b_bunsin2_800D1A18(work) != 0)
        {
            work->field_19C8 = 4;
            work->field_19CC = 0xB;
            work->field_19D4 = 0;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D3064(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800D0078(work) == 0)
        {
            return;
        }
        work->field_19CC = 0x24;
        break;
    case 0x24:
        if (s08b_bunsin2_800D1638(work) == 0)
        {
            return;
        }
        work->field_19C8 = 2;
        work->field_19CC = 8;
        break;
    default:
        return;
    }
    work->field_19D4 = 0;
    work->field_19D0 = 0;
}
void s08b_bunsin2_800D30E0(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800D0078(work) == 0)
        {
            return;
        }
        work->field_19CC = 0x24;
        break;
    case 0x24:
        if (s08b_bunsin2_800D1AF8(work) == 0)
        {
            return;
        }
        work->field_19C8 = 3;
        work->field_19CC = 8;
        work->field_19DC = 0;
        break;
    default:
        return;
    }
    work->field_19D4 = 0;
    work->field_19D0 = 0;
}
void s08b_bunsin2_800D3160(Work *work)
{
    switch (work->field_19CC)
    {
    case 0:
        if (s08b_bunsin2_800CFB98(work) == 0)
        {
            return;
        }
        s08b_bunsin2_800CE180(work);
        work->field_19CC = 5;
        break;
    case 5:
        work->field_19C0 |= 4;
        if (s08b_bunsin2_800CFD88(work) == 0)
        {
            return;
        }
        work->field_19C8 = 2;
        work->field_19CC = 8;
        break;
    default:
        return;
    }
    work->field_19D0 = 0;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D31EC.s")
void s08b_bunsin2_800D3394(Work *work)
{
    int weapon;

    if (work->field_19D4 >= 0x97 && (weapon = GM_Weapon) == -1)
    {
        work->field_19C8 = 2;
        work->field_19CC = 8;
        work->field_19B0 = weapon;
        work->field_19D4 = 0;
    }
    else
    {
        s08b_bunsin2_800CEFF4(work);

        switch (s08b_bunsin2_800D0720(work))
        {
        case 0:
            work->field_19CC = 2;
            break;

        case 1:
            work->field_19CC = 3;
            break;

        case 5:
            work->field_19CC = 5;
            break;
        }

        s08b_bunsin2_800CDDD8(work);
        s08b_bunsin2_800CEEB8(work, 500);
    }

    work->field_19D0 = 0;
}
void s08b_bunsin2_800D3468(Work *work)
{
    int count;
    int state;

    switch (work->field_19CC)
    {
    case 0x1A:
        switch (s08b_bunsin2_800D0814(work))
        {
        case 1:
            work->field_19CC = 2;
            work->field_19D0 = 0;
            break;

        case 2:
            s08b_bunsin2_800CDFA0(work);
            work->field_19CC = 4;
            work->field_19D0 = 0;
            break;
        }
        break;

    case 4:
        if (s08b_bunsin2_800CFC90(work) != 0)
        {
            s08b_bunsin2_800CDFF8(work);
            work->field_19CC = 0x1A;
            work->field_19D0 = 0;
        }
        break;

    case 2:
        if (s08b_bunsin2_800CFC64(work) != 0)
        {
            s08b_bunsin2_800D3394(work);

            count = s08b_dword_800C3444 + 1;
            s08b_dword_800C3444 = count;
            if (count == 0x14)
            {
                s08b_bunsin2_800CDB54(work->field_1A98[2]);
            }
            else if (count == 0x28)
            {
                s08b_bunsin2_800CDB54(work->field_1A98[1]);
                s08b_dword_800C3444 = 0;
            }
        }

        if (work->field_19D4 >= 0x1C3)
        {
            work->field_19C8 = 5;
            work->field_19CC = 8;
            work->field_19D0 = 0;
            break;
        }

        if (work->field_19D4 >= 0x97 && work->field_1A2C < 3000 && work->field_19AC == 1 && GM_Weapon != -1)
        {
            work->field_19C8 = 6;
            if (work->field_1A2C < 1500)
            {
                work->field_19CC = 14;
            }
            else
            {
                work->field_19CC = 13;
            }

            work->field_19D0 = 0;
        }
        break;

    case 3:
        if (s08b_bunsin2_800CFC90(work) != 0)
        {
            s08b_bunsin2_800D3394(work);
        }
        break;
    }

    if (s08b_bunsin2_800CF354(work) != 0)
    {
        state = work->field_1A38;
        if (state == 3)
        {
            work->field_1A0C = 0;
            work->field_19D0 = 0;
        }
        else if (state == 1)
        {
            work->field_19D0 = state;
        }
        else
        {
            work->field_19D0 = 0;
        }

        work->field_19B0 = -1;
    }
}
void s08b_bunsin2_800D367C(Work *work)
{
    switch (work->field_19CC)
    {
    case 2:
        if (s08b_bunsin2_800CFC64(work) != 0)
        {
            work->field_19CC = 6;
            work->field_19D0 = 0;
        }
        break;

    case 3:
        if (s08b_bunsin2_800CFC90(work) != 0)
        {
            work->field_19CC = 6;
            work->field_19D0 = 0;
        }
        break;

    case 5:
        if (s08b_bunsin2_800CFDE0(work) != 0)
        {
            work->field_19CC = 6;
            work->field_19D0 = 0;
        }
        break;

    case 6:
        if (work->field_19D4 >= 301)
        {
            work->field_19C8 = 4;
            work->field_19CC = 10;
            work->field_19D4 = 0;
            return;
        }

        switch (s08b_bunsin2_800D0720(work))
        {
        case 0:
            work->field_19CC = 2;
            break;

        case 1:
            work->field_19CC = 3;
            break;

        case 5:
            work->field_19CC = 5;
            break;
        }

        s08b_bunsin2_800CEFF4(work);
        s08b_bunsin2_800CDDD8(work);
        work->field_19D0 = 0;
        break;
    }

    if ((unsigned int)(work->field_1A34 - 3) < 2)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x19;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}
void s08b_bunsin2_800D37F0(Work *work)
{
    if (GM_PlayerPosition.vx >= -0x7CF)
    {
        if (GM_PlayerPosition.vz >= 0x9C5)
        {
            work->field_1968 = s08b_dword_800C3568[0];
            work->field_1970 = 0x2828;
        }
        else
        {
            work->field_1968 = s08b_dword_800C3568[1];
            work->field_1970 = 0x1F1F;
        }
    }
    else
    {
        if (GM_PlayerPosition.vz >= 0x9C5)
        {
            work->field_1968 = s08b_dword_800C3568[2];
            work->field_1970 = 0x202;
        }
        else
        {
            work->field_1968 = s08b_dword_800C3568[3];
            work->field_1970 = 0x4040;
        }
    }
}
void s08b_bunsin2_800D38F0(Work *work)
{
    s08b_bunsin2_800D37F0(work);

    switch (work->field_19CC)
    {
    case 0x1A:
        switch (s08b_bunsin2_800D0814(work))
        {
        case 1:
            work->field_19CC = 0x1B;
            work->field_19D0 = 0;
            break;

        case 2:
            s08b_bunsin2_800CDFA0(work);
            work->field_19CC = 3;
            work->field_19D0 = 0;
            break;
        }
        break;

    case 0x1B:
        if (s08b_bunsin2_800D0864(work) != 0)
        {
            work->field_19CC = 0x18;
            work->field_19D0 = 0;
        }
        break;

    case 0x18:
        if (work->field_1A2C < 3000)
        {
            work->field_19CC = 0x1A;
            work->field_19D0 = 0;
        }
        break;

    case 3:
        if (s08b_bunsin2_800CFC90(work) != 0)
        {
            s08b_bunsin2_800CDFF8(work);
            work->field_19CC = 0x1A;
            work->field_19D0 = 0;
        }
        break;
    }
}
void s08b_bunsin2_800D39F8(Work *work)
{
    int state = work->field_19CC;
    switch (state)
    {
    case 5:
        if (s08b_bunsin2_800CFDE0(work) == 0)
        {
            return;
        }
        work->field_19CC = 6;
        break;
    case 6:
        if (s08b_bunsin2_800CE8A0(work) != 0)
        {
            work->field_19C8 = state;
            work->field_19CC = 0x15;
        }
        else
        {
            work->field_19CC = 5;
        }
        break;
    default:
        return;
    }
    work->field_19D0 = 0;
}
void s08b_bunsin2_800D3A84(Work *work)
{
    switch (work->field_19CC)
    {
    case 5:
        if (s08b_bunsin2_800CFDE0(work) == 0)
        {
            return;
        }
        work->field_19C8 = 6;
        work->field_19CC = 0;
        break;
    case 0x1B:
        if (s08b_bunsin2_800D0864(work) == 0)
        {
            return;
        }
        work->field_19C8 = 7;
        work->field_19CC = 0x1D;
        break;
    default:
        return;
    }
    work->field_19D0 = 0;
}
void s08b_bunsin2_800D3B00(Work *work)
{
    switch (work->field_19CC)
    {
    case 8:
        switch (s08b_bunsin2_800D072C(work))
        {
        case 1:
            work->field_19CC = 9;
            work->field_19D0 = 0;
            break;

        case 2:
            s08b_bunsin2_800CDFA0(work);
            work->field_19CC = 3;
            work->field_19D0 = 0;
            break;
        }
        break;

    case 9:
        if (s08b_bunsin2_800D0784(work) != 0)
        {
            work->field_19CC = 8;
            work->field_19D0 = 0;
        }
        break;

    case 3:
        if (s08b_bunsin2_800CFC90(work) != 0)
        {
            work->field_19CC = 8;
            work->field_19D0 = 0;
        }
        break;
    }
}

void s08b_bunsin2_800D3BD4(Work *work)
{
    if (s08b_bunsin2_800CF254(work))
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
    }
    else
    {
        s08b_bunsin2_800D3B00(work);
        work->field_19B8 = 0;

        if (work->field_1A2C < 0x4B0)
        {
            work->field_19C8 = 5;
            work->field_19CC = 5;
            work->field_19B8 = 1;
            work->field_19D0 = 0;
        }
    }
}

void s08b_bunsin2_800D3C44(Work *work)
{
    if (s08b_bunsin2_800CF354(work))
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }
    s08b_bunsin2_800D3B00(work);
    if (work->field_1A2C < 0xBB8 && work->field_19CC != 3 && work->field_19AC == 1)
    {
        work->field_19C8 = 0;
        work->field_19CC = 0x18;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}
void s08b_bunsin2_800D3CCC(Work *work)
{
    if (s08b_bunsin2_800CF354(work) != 0)
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }

    s08b_bunsin2_800D3B00(work);

    if (work->field_1A2C < 3000 && work->field_19CC != 3 && work->field_19AC == 1)
    {
        if (GM_Weapon != -1)
        {
            if ((unsigned int)(s08b_dword_800C3444 - 6) < 9 || (unsigned int)(s08b_dword_800C3444 - 26) < 9)
            {
                s08b_bunsin2_800CDB54(work->field_1A98[11]);
            }

            work->field_19C8 = 6;
            if (work->field_1A2C < 1500)
            {
                work->field_19CC = 14;
            }
            else
            {
                work->field_19CC = 13;
            }
        }
        else
        {
            work->field_19C8 = 0;
            work->field_19CC = 0x18;
        }

        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}
void s08b_bunsin2_800D3DBC(Work *work)
{
    int limit;

    if (s08b_bunsin2_800CF464(work) != 0)
    {
        work->field_19B8 = 1;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19C0 &= ~2;
        return;
    }

    s08b_bunsin2_800D3B00(work);
    work->field_19C0 |= 2;

    limit = 3000;
    if (GM_GameLevel < 4)
    {
        if (GM_GameLevel > 0)
        {
            limit = 2000;
        }
    }

    if (work->field_1A2C < limit && work->field_19CC != 3 && work->field_19AC == 1)
    {
        work->field_19C8 = 6;
        if (work->field_1A2C < 1500)
        {
            work->field_19CC = 14;
        }
        else
        {
            work->field_19CC = 13;
        }

        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}
void s08b_bunsin2_800D3EA4(Work *work)
{
    int state;

    s08b_bunsin2_800D3B00(work);

    if (work->field_1A2C < 2000 && work->field_19CC != 3)
    {
        work->field_19C8 = 4;
        work->field_19CC = 10;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }

    state = work->field_1A34;
    if (state == 2)
    {
        work->field_19C8 = 4;
        work->field_19CC = 10;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }

    if ((unsigned int)(state - 3) < 2)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x17;
        work->field_19D0 = 0;
        work->field_19B8 = 1;
    }
}
void s08b_bunsin2_800D3F5C(Work *work)
{
    if (s08b_bunsin2_800CF54C(work) != 0)
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }
    s08b_bunsin2_800D3B00(work);
    work->field_19B8 = 0;
    if (work->field_1A2C < 0x7D0 && work->field_19AC == 1 && work->field_19CC != 3)
    {
        work->field_19C8 = 0;
        work->field_19CC = 0x18;
        work->field_19D0 = 0;
        work->field_19B8 = 1;
        return;
    }
    if (work->field_1A2C >= 0x1771 && work->field_19CC != 3)
    {
        work->field_19CC = 5;
        work->field_19C8 = 0;
        work->field_19D0 = 0;
        work->field_19B8 = 1;
    }
}
void s08b_bunsin2_800D401C(Work *work)
{
    int result;

    s08b_bunsin2_800D3B00(work);

    if (work->field_19CC != 3)
    {
        result = s08b_bunsin2_800CF150(work);
        if (result != 0)
        {
            work->field_19C8 = 6;

            switch (result)
            {
            case 12:
                work->field_19CC = 13;
                break;

            case 13:
                work->field_19CC = 14;
                break;

            case 16:
                work->field_19CC = 17;
                break;

            case 17:
                work->field_19CC = 18;
                break;

            default:
                work->field_19CC = 19;
                break;
            }

            work->field_19D0 = 0;
            work->field_19D4 = 0;
            return;
        }
    }

    work->field_19C0 |= 4;
    if (work->field_1A34 != 0)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x19;

        if (work->field_1A18 != NULL)
        {
            GV_DestroyActor(work->field_1A18);
            work->field_1A18 = NULL;
        }

        if (work->field_1A1C != NULL)
        {
            GV_DestroyActor(work->field_1A1C);
            work->field_1A1C = NULL;
        }

        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}
void s08b_bunsin2_800D4128(Work *work)
{
    int r;

    s08b_bunsin2_800D3B00(work);
    if (work->field_19CC == 3)
    {
        return;
    }
    r = s08b_bunsin2_800CF150(work);
    if (r == 0)
    {
        return;
    }
    work->field_19C8 = 6;
    switch (r)
    {
    case 0xC:
        work->field_19CC = 0xD;
        break;
    case 0xD:
        work->field_19CC = 0xE;
        break;
    case 0x10:
        work->field_19CC = 0x11;
        break;
    case 0x11:
        work->field_19CC = 0x12;
        break;
    default:
        work->field_19CC = 0x13;
        break;
    }
    work->field_19D0 = 0;
    work->field_19D4 = 0;
}
void s08b_bunsin2_800D41DC(Work *work)
{
    switch (work->field_19CC)
    {
    case 10:
        if (s08b_bunsin2_800D093C(work) != 0)
        {
            work->field_19CC = 11;
            work->field_19D0 = 0;
        }
        break;

    case 11:
        if (s08b_bunsin2_800D09C4(work) != 0)
        {
            work->field_19C8 = 2;
            work->field_19CC = 8;
            work->field_19D0 = 0;
            work->field_19D4 = 0;
        }

        if (work->field_1A2C < 1000)
        {
            work->field_19CC = 12;
            work->field_19D0 = 0;
            work->field_19D4 = 0;
        }
        break;

    case 12:
        if (s08b_bunsin2_800D0F88(work) != 0)
        {
            work->field_19C8 = 6;
            work->field_19CC = 14;
            work->field_19D0 = 0;
            work->field_19D4 = 0;
        }
        break;
    }

    if (s08b_bunsin2_800CF464(work) != 0)
    {
        work->field_19B8 = 1;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19C0 &= ~2;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D42D8.s")
int s08b_bunsin2_800D42D8(Work *work);

void s08b_bunsin2_800D43D8(Work *work)
{
    if (s08b_bunsin2_800CF354(work))
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
        return;
    }
    if (s08b_bunsin2_800D42D8(work) == 0)
    {
        return;
    }
    if (work->field_1A0C != 0)
    {
        s08b_bunsin2_800CDE74(work);
        work->field_19C8 = 1;
        work->field_19CC = 0x1A;
    }
    else
    {
        work->field_19C8 = 0;
        work->field_19CC = 7;
    }
    work->field_19D0 = 0;
    work->field_19D4 = 0;
}
void s08b_bunsin2_800D4460(Work *work)
{
    if (s08b_bunsin2_800CF464(work))
    {
        work->field_19B8 = 1;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19C0 &= ~2;
    }
    else if (s08b_bunsin2_800D42D8(work))
    {
        work->field_19C8 = 4;
        work->field_19CC = 10;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}

void s08b_bunsin2_800D44D0(Work *work)
{
    if (s08b_bunsin2_800CF54C(work))
    {
        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->field_19B8 = 1;
    }
    else if (s08b_bunsin2_800D42D8(work))
    {
        work->field_19C8 = 0;
        work->field_19CC = 7;
        work->field_19D0 = 0;
        work->field_19D4 = 0;
    }
}

void s08b_bunsin2_800D452C(Work *work)
{
    if (s08b_bunsin2_800D42D8(work) != 0)
    {
        s08b_dword_800E4340 = 0;
        work->field_19C8 = 7;
        work->field_19CC = 0x17;

        if (work->field_1A18 != NULL)
        {
            GV_DestroyActor(work->field_1A18);
            work->field_1A18 = NULL;
        }

        if (work->field_1A1C != NULL)
        {
            GV_DestroyActor(work->field_1A1C);
            work->field_1A1C = NULL;
        }

        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        work->field_19D0 = 0;
        return;
    }

    if (work->field_1A34 != 0)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x19;

        if (work->field_1A18 != NULL)
        {
            GV_DestroyActor(work->field_1A18);
            work->field_1A18 = NULL;
        }

        if (work->field_1A1C != NULL)
        {
            GV_DestroyActor(work->field_1A1C);
            work->field_1A1C = NULL;
        }

        work->field_19D0 = 0;
        work->field_19D4 = 0;
        work->body.objs->flag &= ~DG_FLAG_INVISIBLE;
        return;
    }

    work->field_19C0 |= 4;
}

void s08b_bunsin2_800D4638(Work *work)
{
    if (s08b_bunsin2_800D42D8(work))
    {
        GV_DestroyActor(work);
        work->field_19D0 = 0;
    }

    if (work->field_19D0 >= 31)
    {
        GV_DestroyActor(work);
    }
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D468C.s")
void s08b_bunsin2_800D47E0(Work *work)
{
    if (work->field_19CC == 0x15 && s08b_bunsin2_800D1348(work) != 0)
    {
        if (work->field_19E0 < 0xF)
        {
            work->field_19C8 = 1;
            work->field_19CC = 6;
        }
        else
        {
            work->field_19C8 = 7;
            work->field_19CC = 0x1D;
        }
        work->field_19B0 = -1;
        work->field_19D0 = 0;
    }
    if (work->field_1A34 > 2 && work->field_1A34 < 5)
    {
        work->field_19C8 = 7;
        work->field_19CC = 0x17;
        work->field_19D0 = 0;
    }
}
void s08b_bunsin2_800D4884(Work *work)
{
    switch (work->field_19CC)
    {
    case 0:
        if (s08b_bunsin2_800D138C(work))
        {
            work->field_1A04 = 2;
            work->field_19CC = 0x17;
            work->field_19D0 = 0;
        }
        break;
    case 0x16:
        if (s08b_bunsin2_800D1400(work))
        {
            work->field_1A04 = 2;
            work->field_19CC = 0x17;
            work->field_19D0 = 0;
            work->field_19DC = work->field_19DC + 1;
        }
        if (work->field_19D0 == 5)
        {
            work->field_1A04 = 1;
        }
        break;
    case 0x17:
        if (s08b_bunsin2_800D1514(work))
        {
            work->field_19CC = 0x16;
            work->field_19D0 = 0;
        }
        break;
    }

    work->field_1A08 = 1;
    if (work->field_1A34 != 0)
    {
        work->field_1A04 = 3;
        s08b_bunsin2_800CF660(work);
        work->field_19D0 = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4984.s")
void s08b_bunsin2_800D4984(Work *work);
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4A34.s")
void s08b_bunsin2_800D4A34(Work *work);
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4AF4.s")
void s08b_bunsin2_800D4AF4(Work *work);
void s08b_bunsin2_800D4BD4(Work *work)
{
    switch (work->field_19C8)
    {
    case 0:
        s08b_bunsin2_800D1DE0(work);
        break;

    case 1:
        s08b_bunsin2_800D38F0(work);
        break;

    case 3:
        s08b_bunsin2_800D3F5C(work);
        break;

    case 6:
        s08b_bunsin2_800D44D0(work);
        break;

    case 7:
        s08b_bunsin2_800D2AB4(work);
        break;

    case 9:
        s08b_bunsin2_800D29DC(work);
        break;

    case 8:
        s08b_bunsin2_800D2EA0(work);
        break;
    }
}
void s08b_bunsin2_800D4BD4(Work *work);
void s08b_bunsin2_800D4C84(Work *work)
{
    switch (work->field_19C8)
    {
    case 0:
        s08b_bunsin2_800D1F9C(work);
        break;
    case 2:
        s08b_bunsin2_800D401C(work);
        break;
    case 6:
        s08b_bunsin2_800D452C(work);
        break;
    case 7:
        s08b_bunsin2_800D2BFC(work);
        break;
    }
}
void s08b_bunsin2_800D4D18(Work *work)
{
    switch (work->field_19C8)
    {
    case 0:
        s08b_bunsin2_800D3160(work);
        break;
    case 2:
        s08b_bunsin2_800D4128(work);
        break;
    case 6:
        s08b_bunsin2_800D4638(work);
        break;
    }
    work->field_19C0 |= 4;
}
void s08b_bunsin2_800D4DA8(Work *work)
{
    switch (work->field_19C8)
    {
    case 0:
        s08b_bunsin2_800D2104(work);
        break;
    case 1:
        s08b_bunsin2_800D39F8(work);
        break;
    case 6:
        s08b_bunsin2_800D47E0(work);
        break;
    case 7:
        s08b_bunsin2_800D2D3C(work);
        break;
    }
}
void s08b_bunsin2_800D4E3C(Work *work)
{
    switch (work->field_19C8)
    {
    case 0:
        s08b_bunsin2_800D2158(work);
        break;
    case 1:
        s08b_bunsin2_800D3A84(work);
        break;
    case 6:
        s08b_bunsin2_800D4884(work);
        break;
    case 7:
        s08b_bunsin2_800D2DB0(work);
        break;
    }
}
void s08b_bunsin2_800D4ED0(Work *work)
{
    int mode = work->field_19C4;

    work->field_19B4 = -1;
    work->field_19B0 = -1;
    work->field_19C0 = 0;
    work->field_1A08 = 0;
    work->field_1A98[34] = -1;

    switch (mode)
    {
    case 0:
        s08b_bunsin2_800D4984(work);
        break;

    case 1:
        s08b_bunsin2_800D4A34(work);
        break;

    case 2:
        s08b_bunsin2_800D4AF4(work);
        break;

    case 3:
        s08b_bunsin2_800D4BD4(work);
        break;

    case 4:
        s08b_bunsin2_800D4C84(work);
        break;

    case 5:
        s08b_bunsin2_800D4D18(work);
        break;

    case 6:
        s08b_bunsin2_800D4DA8(work);
        break;

    case 7:
        s08b_bunsin2_800D4E3C(work);
        break;
    }

    work->field_19D4++;
}
/* sprite animation scripts */
static const char s08b_anim_script_0[] = {
    0x01, 0x56, 0x04, 0x00, 0x0B, 0x00, 0x5E, 0x00, 0xB1, 0x01, 0x09, 0x01,
    0x00, 0x0C, 0x00, 0x04, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x32, 0x19,
    0x14, 0x02, 0x00, 0x01, 0x0D, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x32,
    0x96, 0xAA, 0x02, 0x00, 0x03, 0x0A, 0xFF, 0x9C, 0xFF, 0x9C, 0x08, 0xCE,
    0x6A, 0x56, 0x02, 0x00, 0x16, 0x0A, 0x01, 0x2C, 0xFE, 0x98, 0x08, 0xCE,
    0xE7, 0xEC, 0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xE2, 0x08, 0xCE,
    0xE7, 0xEC, 0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xF4, 0x02, 0x00,
    0x01, 0x0A, 0xFA, 0xBA, 0x00, 0xF0, 0x02, 0x00, 0x01, 0x0F, 0x01, 0x00,
    0x0C, 0x00, 0x04, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x32, 0x19, 0x14,
    0x02, 0x00, 0x01, 0x0D, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x32, 0x96,
    0xAA, 0x02, 0x00, 0x03, 0x0A, 0xFF, 0xCE, 0xFF, 0xCE, 0x08, 0xCE, 0x6A,
    0x56, 0x02, 0x00, 0x16, 0x0A, 0x00, 0x96, 0xFF, 0x4C, 0x08, 0xCE, 0xE7,
    0xEC, 0x02, 0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xF1, 0x08, 0xCE, 0xE7,
    0xEC, 0x02, 0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xFA, 0x02, 0x00, 0x01,
    0x0A, 0xFD, 0x5D, 0x00, 0x78, 0x02, 0x00, 0x01, 0x0F, 0x0A, 0xFF, 0xD8,
    0xFF, 0xD8, 0x01, 0x00, 0x0C, 0x00, 0x04, 0x0A, 0x00, 0x19, 0x00, 0x19,
    0x08, 0x32, 0x19, 0x14, 0x02, 0x00, 0x01, 0x0D, 0x0A, 0x00, 0x19, 0x00,
    0x19, 0x08, 0x32, 0x96, 0xAA, 0x02, 0x00, 0x03, 0x0A, 0xFF, 0xE7, 0xFF,
    0xE7, 0x08, 0xCE, 0x6A, 0x56, 0x02, 0x00, 0x16, 0x0A, 0x00, 0x4B, 0xFF,
    0xA6, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00, 0x01, 0x0A, 0x00, 0x4B, 0xFF,
    0xF9, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00, 0x01, 0x0A, 0x00, 0x4B, 0xFF,
    0xF9, 0x02, 0x00, 0x01, 0x0A, 0xFE, 0xD4, 0x00, 0x3C, 0x02, 0x00, 0x01,
    0x0F, 0x0A, 0xFF, 0xC4, 0xFF, 0xC4, 0x01, 0x00, 0x0C, 0x00, 0x04, 0x0A,
    0x00, 0x0A, 0x00, 0x0A, 0x08, 0x32, 0x19, 0x14, 0x02, 0x00, 0x01, 0x0D,
    0x0A, 0x00, 0x0A, 0x00, 0x0A, 0x08, 0x32, 0x96, 0xAA, 0x02, 0x00, 0x03,
    0x0A, 0xFF, 0xF6, 0xFF, 0xF6, 0x08, 0xCE, 0x6A, 0x56, 0x02, 0x00, 0x16,
    0x0A, 0x00, 0x1E, 0xFF, 0xDC, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00, 0x01,
    0x0A, 0x00, 0x1E, 0xFF, 0xFE, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00, 0x01,
    0x0A, 0x00, 0x1E, 0xFF, 0xFE, 0x02, 0x00, 0x01, 0x0A, 0xFF, 0xB0, 0x00,
    0x0A, 0x02, 0x00, 0x01, 0x0F, 0x00, 0x00, 0x00,
};

static const char s08b_anim_script_1[] = {
    0x00, 0xF9, 0x03, 0x00, 0x09, 0x00, 0x5C, 0x00, 0xAF, 0x01, 0x00, 0x0C,
    0x00, 0x04, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x2D, 0x23, 0x14, 0x02,
    0x00, 0x01, 0x0D, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x46, 0x6E, 0xAA,
    0x02, 0x00, 0x03, 0x0A, 0xFF, 0x9C, 0xFF, 0x9C, 0x08, 0xBA, 0x92, 0x56,
    0x02, 0x00, 0x16, 0x0A, 0x01, 0x2C, 0xFE, 0x98, 0x08, 0xD3, 0xDD, 0xEC,
    0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xE2, 0x08, 0xD3, 0xDD, 0xEC,
    0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xF4, 0x02, 0x00, 0x01, 0x0A,
    0xFA, 0xBA, 0x00, 0xF0, 0x02, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x0C, 0x00,
    0x04, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x2D, 0x23, 0x14, 0x02, 0x00,
    0x01, 0x0D, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x46, 0x6E, 0xAA, 0x02,
    0x00, 0x03, 0x0A, 0xFF, 0xCE, 0xFF, 0xCE, 0x08, 0xBA, 0x92, 0x56, 0x02,
    0x00, 0x16, 0x0A, 0x00, 0x96, 0xFF, 0x4C, 0x08, 0xD3, 0xDD, 0xEC, 0x02,
    0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xF1, 0x08, 0xD3, 0xDD, 0xEC, 0x02,
    0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xFA, 0x02, 0x00, 0x01, 0x0A, 0xFD,
    0x5D, 0x00, 0x78, 0x02, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x0C, 0x00, 0x04,
    0x0A, 0x00, 0x19, 0x00, 0x19, 0x08, 0x32, 0x19, 0x14, 0x02, 0x00, 0x01,
    0x0D, 0x0A, 0x00, 0x19, 0x00, 0x19, 0x08, 0x32, 0x96, 0xAA, 0x02, 0x00,
    0x03, 0x0A, 0xFF, 0xE7, 0xFF, 0xE7, 0x08, 0xCE, 0x6A, 0x56, 0x02, 0x00,
    0x16, 0x0A, 0x00, 0x4B, 0xFF, 0xA6, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00,
    0x01, 0x0A, 0x00, 0x4B, 0xFF, 0xF9, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00,
    0x01, 0x0A, 0x00, 0x4B, 0xFF, 0xF9, 0x02, 0x00, 0x01, 0x0A, 0xFE, 0xD4,
    0x00, 0x3C, 0x02, 0x00, 0x01, 0x0F, 0x00, 0x00,
};

static const char s08b_anim_script_2[] = {
    0x00, 0xF9, 0x03, 0x00, 0x09, 0x00, 0x5C, 0x00, 0xAF, 0x01, 0x00, 0x0C,
    0x00, 0x04, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x19, 0x26, 0x2D, 0x02,
    0x00, 0x01, 0x0D, 0x0A, 0x00, 0x64, 0x00, 0x64, 0x08, 0x96, 0x62, 0x46,
    0x02, 0x00, 0x03, 0x0A, 0xFF, 0x9C, 0xFF, 0x9C, 0x08, 0x6A, 0x9E, 0xBA,
    0x02, 0x00, 0x16, 0x0A, 0x01, 0x2C, 0xFE, 0x98, 0x08, 0xE7, 0xDA, 0xD3,
    0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xE2, 0x08, 0xE7, 0xDA, 0xD3,
    0x02, 0x00, 0x01, 0x0A, 0x01, 0x2C, 0xFF, 0xF4, 0x02, 0x00, 0x01, 0x0A,
    0xFA, 0xBA, 0x00, 0xF0, 0x02, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x0C, 0x00,
    0x04, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x2D, 0x23, 0x14, 0x02, 0x00,
    0x01, 0x0D, 0x0A, 0x00, 0x32, 0x00, 0x32, 0x08, 0x46, 0x6E, 0xAA, 0x02,
    0x00, 0x03, 0x0A, 0xFF, 0xCE, 0xFF, 0xCE, 0x08, 0xBA, 0x92, 0x56, 0x02,
    0x00, 0x16, 0x0A, 0x00, 0x96, 0xFF, 0x4C, 0x08, 0xD3, 0xDD, 0xEC, 0x02,
    0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xF1, 0x08, 0xD3, 0xDD, 0xEC, 0x02,
    0x00, 0x01, 0x0A, 0x00, 0x96, 0xFF, 0xFA, 0x02, 0x00, 0x01, 0x0A, 0xFD,
    0x5D, 0x00, 0x78, 0x02, 0x00, 0x01, 0x0F, 0x01, 0x00, 0x0C, 0x00, 0x04,
    0x0A, 0x00, 0x19, 0x00, 0x19, 0x08, 0x32, 0x19, 0x14, 0x02, 0x00, 0x01,
    0x0D, 0x0A, 0x00, 0x19, 0x00, 0x19, 0x08, 0x32, 0x96, 0xAA, 0x02, 0x00,
    0x03, 0x0A, 0xFF, 0xE7, 0xFF, 0xE7, 0x08, 0xCE, 0x6A, 0x56, 0x02, 0x00,
    0x16, 0x0A, 0x00, 0x4B, 0xFF, 0xA6, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00,
    0x01, 0x0A, 0x00, 0x4B, 0xFF, 0xF9, 0x08, 0xCE, 0xE7, 0xEC, 0x02, 0x00,
    0x01, 0x0A, 0x00, 0x4B, 0xFF, 0xF9, 0x02, 0x00, 0x01, 0x0A, 0xFE, 0xD4,
    0x00, 0x3C, 0x02, 0x00, 0x01, 0x0F, 0x00, 0x00,
};

static const char s08b_anim_script_3[] = {
    0x00, 0x04, 0x01, 0x00, 0x05, 0x02, 0x00, 0x01, 0x0F, 0x00, 0x00, 0x00,
};

static ANIMATION s08b_anim_0 = {0xDCD3, 1, 1, 1, 1, 0x1F4, 1, 0x50, 0x50, 0, NULL, (char *)s08b_anim_script_0};
static ANIMATION s08b_anim_1 = {0xFAD3, 1, 1, 1, 1, 0x1F4, 1, 0x50, 0x50, 0, NULL, (char *)s08b_anim_script_1};
static ANIMATION s08b_anim_2 = {0xFAD3, 1, 1, 1, 1, 0x1F4, 1, 0x50, 0x50, 0, NULL, (char *)s08b_anim_script_2};
static ANIMATION s08b_anim_3 = {0x1968, 1, 1, 1, 1, 0, 1, 0x46, 0x46, 0xFF, NULL, (char *)s08b_anim_script_3};
static unsigned short s08b_anim_tex[3] = {0xDCD3, 0xFAD3, 0x1968};

int s08b_dword_800C3610 = 0;

void s08b_bunsin2_800D4FBC(MATRIX *world, int type)
{
    PRESCRIPT  prescript;
    ANIMATION *anim;
    SVECTOR   *pos;

    anim = NULL;
    pos = &prescript.pos;
    prescript.pos.vx = 0;
    pos->vy = 800;
    pos->vz = 0;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    switch (type)
    {
    case 0:
        anim = &s08b_anim_0;
        anim->tex = s08b_anim_tex[0];
        break;

    case 1:
        anim = &s08b_anim_0;
        anim->tex = s08b_anim_tex[1];
        break;

    case 2:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[0];
        break;

    case 3:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[1];
        break;

    case 4:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[0];
        break;

    case 5:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[1];
        break;

    case 6:
        anim = &s08b_anim_0;
        prescript.scr_num = 1;
        anim->tex = s08b_anim_tex[2];
        break;
    }

    anim->pre_script = &prescript;
    NewAnime(world, 0, anim);
}

void s08b_bunsin2_800D50F0(MATRIX *world, int type)
{
    PRESCRIPT  prescript;
    ANIMATION *anim;
    SVECTOR   *pos;

    anim = NULL;
    pos = &prescript.pos;
    prescript.pos.vx = 0;
    pos->vy = 600;
    pos->vz = 0;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 1;
    prescript.s_anim = 0;

    switch (type)
    {
    case 0:
        anim = &s08b_anim_0;
        anim->tex = s08b_anim_tex[0];
        break;

    case 1:
        anim = &s08b_anim_0;
        anim->tex = s08b_anim_tex[1];
        break;

    case 2:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[0];
        break;

    case 3:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[1];
        break;

    case 4:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[0];
        break;

    case 5:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[1];
        break;

    case 6:
        anim = &s08b_anim_0;
        prescript.scr_num = 2;
        anim->tex = s08b_anim_tex[2];
        break;
    }

    anim->pre_script = &prescript;
    NewAnime(world, 0, anim);
}

void s08b_bunsin2_800D5228(MATRIX *world, int type)
{
    PRESCRIPT  prescript;
    ANIMATION *anim;
    SVECTOR   *pos;

    anim = NULL;
    pos = &prescript.pos;
    prescript.pos.vx = 0;
    pos->vy = 120;
    pos->vz = 0;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 2;
    prescript.s_anim = 0;

    switch (type)
    {
    case 0:
        anim = &s08b_anim_0;
        prescript.scr_num = 3;
        anim->tex = s08b_anim_tex[0];
        break;

    case 1:
        anim = &s08b_anim_0;
        anim->tex = s08b_anim_tex[1];
        break;

    case 2:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[0];
        break;

    case 3:
        anim = &s08b_anim_1;
        anim->tex = s08b_anim_tex[1];
        break;

    case 4:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[0];
        break;

    case 5:
        anim = &s08b_anim_2;
        anim->tex = s08b_anim_tex[1];
        break;

    case 6:
        anim = &s08b_anim_0;
        prescript.scr_num = 3;
        anim->tex = s08b_anim_tex[2];
        break;
    }

    anim->pre_script = &prescript;
    NewAnime(world, 0, anim);
}
void s08b_bunsin2_800D5364(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector;
    prescript.scr_num = 0;
    prescript.s_anim = 0;
    s08b_anim_3.pre_script = &prescript;
    NewAnime(NULL, 0, &s08b_anim_3);
}
void s08b_bunsin2_800D53E8(int type, int time)
{
    void *screen;

    if (s08b_dword_800C3610 == 0)
    {
        s08b_dword_800C3610 = 1;
        s08b_dword_800C3614 = time;
        screen = NewCinemaScreen(time, type);
        s08b_dword_800C3618 = (int)screen;
    }
}
void s08b_bunsin2_800D5434(void)
{
    if (s08b_dword_800C3614 == 0)
    {
        return;
    }
    if (s08b_dword_800C3610 == 0)
    {
        return;
    }
    if (s08b_dword_800C3618 == 0)
    {
        return;
    }
    NewCinemaScreenClose((void *)s08b_dword_800C3618);
    s08b_dword_800C3618 = 0;
    s08b_dword_800C3610 = 0;
}
void s08b_bunsin2_800D5498(void)
{
    int v;

    v = s08b_dword_800C3614;
    if (v != 0)
    {
        v--;
        s08b_dword_800C3614 = v;
        if (v == 0)
        {
            s08b_dword_800C3618 = 0;
            s08b_dword_800C3610 = 0;
        }
    }
}
