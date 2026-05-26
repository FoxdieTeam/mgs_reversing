#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/map.h"

extern DG_OBJS *Takabe_MakePreshade(int model, LIT *lit);

void s15c_dyncon_800D3EBC(OBJECT_NO_ROTS *obj, int model, int flag)
{
    GV_ZeroMemory(obj, sizeof(*obj));
    obj->flag = flag;
    obj->map_name = GM_CurrentMap;
    obj->objs = Takabe_MakePreshade(model, GM_GetMap(GM_CurrentMap)->lit);
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D3F24.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5090.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5114.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D518C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5270.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5354.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5428.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D567C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5910.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D59C0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5A3C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5C38.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5DC0.s")

typedef struct _DynCon
{
    char    pad_0[0x3F00];
    int     field_3F00[4];   /* 0x3F00 */
    int     field_3F10[4];   /* 0x3F10 - countdown, reset to 32 (800D6004/603C) */
    int     field_3F20[4];   /* 0x3F20 - cycle counter (800D6004/603C) */
    int     field_3F30[4];   /* 0x3F30 */
    SVECTOR field_3F40[4];   /* 0x3F40 */
    SVECTOR field_3F60[4];   /* 0x3F60 */
    char    pad_3F80[0x4050 - 0x3F80];
    int     field_4050;      /* 0x4050 - mode/state (1 or 3) */
} DynCon;

void s15c_dyncon_800D5EA8(DynCon *work, int i,
                          short ax, short ay, short az,
                          short bx, short by, short bz)
{
    work->field_3F60[i].vx = ax;
    work->field_3F60[i].vy = ay;
    work->field_3F60[i].vz = az;
    work->field_3F40[i].vx = bx;
    work->field_3F40[i].vy = by;
    work->field_3F40[i].vz = bz;
}
extern void s15c_dyncon_800D5354(void *work, int a, int b);
extern void s15c_dyncon_800D567C(void *work, int a, int b, int c);
extern void s15c_dyncon_800D518C(void *work, int a, int b);
extern void s15c_dyncon_800D5270(void *work, int a, int b);

void s15c_dyncon_800D5EDC(DynCon *work, int a1, int a2)
{
    if (a1 == 4)
    {
        return;
    }
    s15c_dyncon_800D5354(work, a1, 1);
    s15c_dyncon_800D567C(work, a1, 1, a2);
    if (work->field_4050 == 3)
    {
        s15c_dyncon_800D518C(work, a1, 1);
    }
    else
    {
        s15c_dyncon_800D5270(work, a1, 1);
    }
}
typedef struct _DynStack
{
    char  pad[0x70];
    short val_70;
    short val_72;
    short val_74;
    short pad2;
    short val_78;
    short val_7A;
    short val_7C;
} DynStack;

void s15c_dyncon_800D5F68(DynCon *work, int index, int arg2, int a3_val,
                          int sp28, int sp2c, int sp30, int sp34,
                          int sp38, int sp3c)
{
    DynStack *item;

    item = (DynStack *)((char *)work + (index * 156));

    item->val_78 += (short)a3_val;
    item->val_7A += (short)sp28;

    item->val_7C += (short)sp2c;
    item->val_70 += (short)sp30;

    item->val_72 += (short)sp34;
    item->val_74 += (short)sp38;

    s15c_dyncon_800D5EDC(work, arg2, sp3c);
}
void s15c_dyncon_800D6004(DynCon *work, int i)
{
    work->field_3F10[i] = work->field_3F10[i] - 1;
    if (work->field_3F10[i] == 0)
    {
        work->field_3F10[i] = 32;
        work->field_3F20[i] = work->field_3F20[i] + 1;
    }
}
void s15c_dyncon_800D603C(DynCon *work, int i)
{
    work->field_3F10[i] = work->field_3F10[i] - 1;
    if (work->field_3F10[i] == 0)
    {
        work->field_3F20[i] = work->field_3F20[i] + 1;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6070.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6128.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D61E0.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D6434.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7A84.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7D44.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7E30.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7EF4.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D7F88.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D82FC.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8510.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D88C8.s")
extern void s15c_dyncon_800D82FC(void *work);
extern void s15c_dyncon_800D88C8(void *work);

void s15c_dyncon_800D89F8(DynCon *work)
{
    s15c_dyncon_800D82FC(work);
    if (work->field_4050 == 1)
    {
        s15c_dyncon_800D88C8(work);
    }
}
void s15c_dyncon_800D8A34(int unused, short *out, int count)
{
    int   i;
    char *s;

    (void)unused;
    for (i = 0; i < count; i++)
    {
        s = GCL_NextStr();
        if (s == NULL)
        {
            break;
        }
        *out = GCL_StrToInt(s);
        out++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A9C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8C9C.s")
