#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
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
void s15c_dyncon_800D5EA8(void *base, int i,
                          short ax, short ay, short az,
                          short bx, short by, short bz)
{
    char *p = (char *)base + i * 8;
    *(short *)(p + 0x3F60) = ax;
    *(short *)(p + 0x3F62) = ay;
    *(short *)(p + 0x3F64) = az;
    *(short *)(p + 0x3F40) = bx;
    *(short *)(p + 0x3F42) = by;
    *(short *)(p + 0x3F44) = bz;
}
extern void s15c_dyncon_800D5354(void *work, int a, int b);
extern void s15c_dyncon_800D567C(void *work, int a, int b, int c);
extern void s15c_dyncon_800D518C(void *work, int a, int b);
extern void s15c_dyncon_800D5270(void *work, int a, int b);

void s15c_dyncon_800D5EDC(void *work, int a1, int a2)
{
    if (a1 == 4)
    {
        return;
    }
    s15c_dyncon_800D5354(work, a1, 1);
    s15c_dyncon_800D567C(work, a1, 1, a2);
    if (*(int *)((char *)work + 0x4050) == 3)
    {
        s15c_dyncon_800D518C(work, a1, 1);
    }
    else
    {
        s15c_dyncon_800D5270(work, a1, 1);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5F68.s")
void s15c_dyncon_800D6004(void *base, int i)
{
    int *p1 = (int *)((char *)base + i * 4 + 0x3F10);
    int *p2 = (int *)((char *)base + i * 4 + 0x3F20);

    *p1 = *p1 - 1;
    if (*p1 == 0)
    {
        *p1 = 32;
        *p2 = *p2 + 1;
    }
}
void s15c_dyncon_800D603C(void *base, int i)
{
    int *p1 = (int *)((char *)base + i * 4 + 0x3F10);
    int *p2 = (int *)((char *)base + i * 4 + 0x3F20);

    *p1 = *p1 - 1;
    if (*p1 == 0)
    {
        *p2 = *p2 + 1;
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

void s15c_dyncon_800D89F8(void *work)
{
    s15c_dyncon_800D82FC(work);
    if (*(int *)((char *)work + 0x4050) == 1)
    {
        s15c_dyncon_800D88C8(work);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A34.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A9C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8C9C.s")
