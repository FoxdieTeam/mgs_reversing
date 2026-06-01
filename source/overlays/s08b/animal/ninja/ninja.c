#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"

typedef struct _NinjaWork
{
    GV_ACT          actor;       /* 0x000 */
    CONTROL         control;     /* 0x020 */
    char            pad_9C[0x9C - 0x20 - sizeof(CONTROL)];
    OBJECT_NO_ROTS  body;        /* 0x09C */
    char            pad_798[0x798 - 0x9C - sizeof(OBJECT_NO_ROTS)];
    MATRIX          light;       /* 0x798 */
    char            pad_7D8[0x7D8 - 0x798 - sizeof(MATRIX)];
    int             field_7D8;   /* 0x7D8 */
    char            pad_8C4[0x8C4 - 0x7D8 - 4];
    TARGET         *target;      /* 0x8C4 */
    char            pad_19D8[0x19D8 - 0x8C4 - 4];
    int             field_19D8;  /* 0x19D8 */
    char            pad_19E4[0x19E4 - 0x19D8 - 4];
    int             field_19E4;  /* 0x19E4 */
    char            pad_1B24[0x1B24 - 0x19E4 - 4];
    short           field_1B24;  /* 0x1B24 */
} NinjaWork;

extern int s08b_dword_800E4318;
extern int s08b_dword_800E4320;
extern int s08b_dword_800C3390;
extern int s08b_dword_800C3398;
extern int s08b_dword_800C338C;
extern int s08b_dword_800C3380;
extern void s08b_bunsin2_800CDB10(NinjaWork *work);
extern void s08b_ninja_800C81C8(NinjaWork *work);
extern int  s08b_ninja_800C8170(void);
extern int  fprintf(int stream, const char *format, ...);
extern GM_CameraSystemWork GM_Camera;
extern char *s08b_dword_800E431C;
extern int s08b_dword_800E4324;
extern void s08b_ninja_800C79D4(int a0);
extern void s08b_ninja_800C796C(short *a, short *b);

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
void s08b_ninja_800C811C(void *work)
{
    short *p = *(short **)((char *)work + 0x8C4);

    if (p[3] & 8)
    {
        GV_AddVec3((SVECTOR *)((char *)p + 0x34), (SVECTOR *)((char *)work + 0x64),
                   (SVECTOR *)((char *)work + 0x64));
        p[3] &= 0xFFF7;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8170.s")
void s08b_ninja_800C81C8(NinjaWork *work)
{
    if (work->field_1B24 == 0)
    {
        if (s08b_ninja_800C8170() != 0 && (GM_PlayerStatus & 0x20000) &&
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
void s08b_ninja_800C8264(NinjaWork *work)
{
    CONTROL *c = &work->control;

    s08b_ninja_800C811C(work);
    GM_ActControl(c);
    GM_ActObject2((OBJECT *)&work->body);
    DG_GetLightMatrix2((SVECTOR *)c, &work->light);
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
        MENU_DrawBar(0x10, 0x1C, s08b_dword_800C338C << 2, work->field_19E4 << 2,
                     (MENU_BAR_CONF *)&s08b_dword_800C3380);
    }
    s08b_ninja_800C81C8(work);
}
void s08b_ninja_800C8354(void *work)
{
    TARGET *t = *(TARGET **)((char *)work + 0x8C4);

    GM_SetTarget(t, 0x1F, 2, (SVECTOR *)&s08b_dword_800C3390);
    GM_SetPowerTarget(t, 1, -1, 0xFF, 0xFF, (SVECTOR *)&s08b_dword_800C3398);
    GM_SetCaptureTarget(t, -1, 0xFF, (int *)0, (SVECTOR *)0);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C83CC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8558.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8624.s")
void s08b_ninja_800C8798(void *work)
{
    void *p;

    GM_FreeControl((CONTROL *)((char *)work + 0x20));
    GM_FreeObject((OBJECT *)((char *)work + 0x9C));
    GM_FreeObject((OBJECT *)((char *)work + 0x7DC));
    GM_FreeHomingTarget(*(HOMING **)((char *)work + 0x910));
    GV_DestroyActorQuick(*(void **)((char *)work + 0x1A20));
    GV_DestroyActorQuick(*(void **)((char *)work + 0x1A24));
    if (*(void **)((char *)work + 0x19BC) != NULL)
    {
        GV_DestroyActorQuick(*(void **)((char *)work + 0x19BC));
    }
    if (*(int *)((char *)work + 0x7D8) == 0)
    {
        GM_FreeTarget(*(TARGET **)((char *)work + 0x8C4));
        p = *(void **)((char *)work + 0x1A80);
        if (p != NULL)
        {
            DG_DequeuePrim((DG_PRIM *)p);
            DG_FreePrim((DG_PRIM *)p);
        }
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
extern const char s08b_aErrerrerrsoundbuffover_800E3764[];

int s08b_ninja_800C8988(void *work)
{
    char *opt = GCL_GetOption(0x76);

    if (opt == NULL)
    {
        return 0;
    }
    if (s08b_ninja_800C8930(opt, (int *)((char *)work + 0x1A98)) < 0x23)
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8DCC.s")
