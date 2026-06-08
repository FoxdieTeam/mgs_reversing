#include "common.h"
#include "linkvar.h"
#include "chara/snake/sna_init.h"
#include "game/game.h"
#include "game/jimctrl.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "menu/menuman.h"
#include "mts/mts.h" // for fprintf

#include <stdio.h>

struct _Work;
typedef void (*NinjaFunc)(struct _Work *);

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
    char       pad_920[0x920 - 0x910 - sizeof(HOMING *)];
    NinjaClone clones[11];  /* 0x920 */
    char       pad_1964[0x1964 - 0x920 - 11 * sizeof(NinjaClone)];
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
    char      pad_19A4[0x19A4 - 0x198C - sizeof(SVECTOR)];
    int       field_19A4;  /* 0x19A4 */
    int       field_19A8;  /* 0x19A8 */
    int       field_19AC;  /* 0x19AC */
    int       field_19B0;  /* 0x19B0 */
    int       field_19B4;  /* 0x19B4 */
    int       field_19B8;  /* 0x19B8 */
    void     *field_19BC;  /* 0x19BC */
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
    char      pad_19F0[0x19F0 - 0x19E4 - 4];
    int       field_19F0;  /* 0x19F0 */
    int       field_19F4;  /* 0x19F4 */
    int       field_19F8;  /* 0x19F8 */
    char      pad_1A00[0x1A00 - 0x19F8 - 4];
    int       field_1A00;  /* 0x1A00 */
    int       field_1A04;  /* 0x1A04 */
    int       field_1A08;  /* 0x1A08 */
    int       field_1A0C;  /* 0x1A0C */
    char      pad_1A14[0x1A14 - 0x1A0C - sizeof(int)];
    int       field_1A14;  /* 0x1A14 */
    char      pad_1A20[0x1A20 - 0x1A14 - sizeof(int)];
    void     *field_1A20;  /* 0x1A20 */
    void     *field_1A24;  /* 0x1A24 */
    int       field_1A28;     // 0x1A28
    int       field_1A2C;     // 0x1A2C
    char      pad_1A30[0x4]; /* 0x1A28 */
    int       field_1A34;     /* 0x1A34 */
    int       field_1A38;     /* 0x1A38 */
    char      pad_1A40[0x4]; /* 0x1A3C */
    NinjaFunc field_1A40[8];  /* 0x1A40 */
    char      pad_1A80[0x1A80 - 0x1A60];
    DG_PRIM  *field_1A80;  /* 0x1A80 */
    char      pad_1A8C[0x1A8C - 0x1A84];
    int       field_1A8C;  /* 0x1A8C */
    int       field_1A90;  /* 0x1A90 */
    int       field_1A94;  /* 0x1A94 */
    int       field_1A98[0x23]; /* 0x1A98 */
    short     field_1B24;  /* 0x1B24 */
    char      pad_1B28[0x1B28 - 0x1B24 - sizeof(short)];
    short     field_1B28;  /* 0x1B28 */
    char      pad_1B34[0x1B34 - 0x1B28 - sizeof(short)];
} Work;

/* forward declarations for helpers called by the migrated functions */
extern int   s08b_bunsin2_800C9978(OBJECT *body);
extern void  s08b_bunsin2_800CDE74(Work *work);
extern void  s08b_bunsin2_800CE0A4(void);
extern void  s08b_bunsin2_800CE180(Work *work);
extern int   s08b_bunsin2_800CE584(Work *work);
extern void  s08b_bunsin2_800CE800(Work *work, int arg);
extern int   s08b_bunsin2_800CE8A0(Work *work);
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
extern void  s08b_bunsin2_800D4FBC(DG_OBJ *obj, int arg);
extern void  s08b_bunsin2_800D53E8(int a0, int a1);
extern void  s08b_bunsin2_800D5434(void);
extern void *s08b_p_sphere_800D9834(void *a, void *b);
extern void *NewCinemaScreenClose(void *addr);
extern int   okajima_CHAF_LIFE;
extern unsigned short GM_ItemTypes[];
extern unsigned short GM_WeaponTypes[];
extern int     s08b_dword_800C3440;
extern int     s08b_dword_800C3444;
extern int     s08b_dword_800C3448;
extern int     s08b_dword_800C344C;
extern int     s08b_dword_800C3450;
extern SVECTOR s08b_dword_800C34F8[];
extern int     s08b_dword_800C3588;

extern GM_CameraSystemWork GM_Camera;

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
extern int     s08b_dword_800C3610;
extern int     s08b_dword_800C3614;
extern int     s08b_dword_800C3618;

extern int   s08b_dword_800E4318;
extern char *s08b_dword_800E431C;
extern int   s08b_dword_800E4320;
extern int   s08b_dword_800E4324;
extern int   s08b_dword_800E4334[];
extern int   s08b_dword_800E4338;
extern int   s08b_dword_800E433C;
extern int   s08b_dword_800E4340;

extern char s08b_aErrerrerrsoundbuffover_800E3764[];
extern char s08b_aNinjac_800E37F8[];
extern char s08b_aKorekorekor_800E39A8[];

int  s08b_bunsin2_800CD95C(Work *work, void *func);
void s08b_bunsin2_800CDB10(Work *work);
void s08b_bunsin2_800D4ED0(Work *work);

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
    *(int *)s08b_dword_800E4318 = a0;
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
        GM_Camera.target = *(SVECTOR *)(s08b_dword_800E431C + 0x1968);
        if (*(short *)(s08b_dword_800E431C + 0x1968) >= -0x7CF)
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
    GM_Camera.target = *(SVECTOR *)(s08b_dword_800E431C + 0x1968);
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
        GM_Camera.target = *(SVECTOR *)(s08b_dword_800E431C + 0x1968);
        if (*(short *)(s08b_dword_800E431C + 0x1968) >= -0x7CF)
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
        GM_Camera.target = *(SVECTOR *)(s08b_dword_800E431C + 0x1968);
    }
    if (s08b_dword_800E4320 >= 0x2E)
    {
        GM_Camera.type = 0;
        if (*(short *)(s08b_dword_800E431C + 0x1968) >= -0x7CF)
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7F74.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C83CC.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8558.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8624.s")

void s08b_ninja_800C8798(Work *work) // Die
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeHomingTarget(work->field_910);
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8848.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8BE8.s")
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

int Bunsin2_800C8F04(void)
{
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8FF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C908C.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9B38.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9BF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CA8F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAA78.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAB50.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAD28.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAE14.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAF6C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAFF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB0A8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB158.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB210.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB2AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB38C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB444.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB52C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB7A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB914.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBAA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBCEC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBE30.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC080.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC2F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC434.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC578.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC71C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC7EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC90C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCA4C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCAF0.s")

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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCE34.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD000.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD544.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD5AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD614.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD690.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD770.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD808.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDA40.s")
void s08b_bunsin2_800CDA40(Work *work);

void s08b_bunsin2_800CDB10(Work *work)
{
    s08b_bunsin2_800CDA40(work);
    s08b_bunsin2_800CD9F0(work);
    s08b_bunsin2_800D4ED0(work);
    s08b_bunsin2_800CD000(work);
    s08b_bunsin2_800CD990(work);
}

void s08b_bunsin2_800CDB54(Work *work)
{
    if (GM_StreamStatus() == -1 &&
        GM_GameOverTimer == 0 &&
        GM_SnakeCurrentHealth > 0)
    {
        GM_VoxStream((int)work, 0);
    }
}
void s08b_bunsin2_800CDBAC(Work *work)
{
    if (s08b_dword_800C3440 % 12 == 1)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
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
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
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
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
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
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
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
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDE74.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE0A4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE180.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE21C.s")
void s08b_bunsin2_800CE21C(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE2E8.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEA34.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF150.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF254.s")
int s08b_bunsin2_800CF254(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF354.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF464.s")
int s08b_bunsin2_800CF464(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF54C.s")
int s08b_bunsin2_800CF54C(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF660.s")

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
        GM_GameStatus |= STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_PADRELEASE | 0x40;
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
            GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_PADRELEASE | 0x40);
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
            GM_GameStatus &= ~(STATE_RADIO_OFF | STATE_LIFEBAR_OFF | STATE_MENU_OFF | STATE_PADRELEASE | 0x40);
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF960.s")

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
            GM_SnakeCurrentHealth > 0)
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFB98.s")

void s08b_bunsin2_800CFC64(Work *work)
{
    work->field_19D0++;
    s08b_bunsin2_800CEEB8(work, 500);
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFD88.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0078.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0200.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0330.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D044C.s")
int s08b_bunsin2_800D044C(Work *work);

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D06A0.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0784.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D08C8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D093C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D09C4.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0A90.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0CD8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0D80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0EB8.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0F88.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1014.s")
int s08b_bunsin2_800D10C4(Work *work)
{
    if (GM_PlayerStatus & (PLAYER_SQUAT | PLAYER_GROUND | PLAYER_CB_BOX))
    {
        work->field_19B0 = 0x12;
    }
    else if (GM_CurrentWeaponId == WP_None)
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D138C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1400.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1638.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1738.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D17F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D195C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1A18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1AF8.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1D44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1F9C.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D21B8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D231C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2420.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2510.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2600.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2860.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D29DC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2B24.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2BFC.s")

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2DB0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2EA0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2F80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3064.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D30E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3160.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D31EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3394.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3468.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D367C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D37F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D38F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D39F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3A84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3B00.s")
void s08b_bunsin2_800D3B00(Work *work);

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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3C44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3CCC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3EA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3F5C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D401C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4128.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D41DC.s")

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D42D8.s")
int s08b_bunsin2_800D42D8(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D43D8.s")
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

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D452C.s")

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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D47E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4884.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4984.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4A34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4AF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4C84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4D18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4DA8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4E3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4ED0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4FBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D53E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5434.s")
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
