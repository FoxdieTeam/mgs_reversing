#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

extern int s08b_dword_800E4318;
extern int s08b_dword_800E4320;
extern int s08b_dword_800C3390;
extern int s08b_dword_800C3398;

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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C79F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7A3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7B68.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7BC8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7CF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7E14.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C7ED8.s")
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
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C81C8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_ninja_800C8264.s")
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
