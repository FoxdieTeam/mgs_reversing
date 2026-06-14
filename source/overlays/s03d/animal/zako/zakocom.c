#include "common.h"
#include "game/game.h"

extern int s03d_dword_800DC2E0;
extern int s03d_dword_800DC2E8;
extern int s03d_dword_800DC2EC;

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3FF4.s")
int ZakoCom_800D4038(void)
{
    int v = s03d_dword_800DC2E0;

    s03d_dword_800DC2E0 = v + 1;
    return v;
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4050.s")
void ZakoCom_800D4070(int value)
{
    s03d_dword_800DC2EC = value;
}

void ZakoCom_800D407C(int value)
{
    s03d_dword_800DC2E8 = value;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4088.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D414C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D41C0.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4224.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4284.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D42DC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D43CC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D440C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4460.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D44B4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4508.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D455C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D45B0.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4640.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4694.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D46F8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D47BC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D490C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D49F0.s")
int ZakoCom_800D4B08(int a, int b)
{
    if (a < b)
    {
        a = b;
    }
    return a;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4B20.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4B84.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4CE0.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4DD4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4E48.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D4EAC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D5484.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D54DC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D5538.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D55C8.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D5888.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D58D4.s")
