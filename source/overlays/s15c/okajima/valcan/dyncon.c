#include "common.h"

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D3EBC.s")
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
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D5EDC.s")
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
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D89F8.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A34.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8A9C.s")
#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_dyncon_800D8C9C.s")
