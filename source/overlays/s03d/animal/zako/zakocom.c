#include "common.h"
#include "game/game.h"
#include "mts/mts.h" // for fprintf
#include "takabe/cinema.h" // for NewCinemaScreen

extern int s03d_dword_800DC2E0;
extern int s03d_dword_800DC2E8;
extern int s03d_dword_800DC2EC;
extern int s03d_dword_800DC310;
extern int s03d_dword_800DC31C;
extern const char s03d_dword_800DBB48[];
extern const char s03d_dword_800DBB54[];
extern const char s03d_dword_800DBB64[];
extern const char s03d_dword_800DBB74[];
extern const char s03d_dword_800DBB88[];

extern int s03d_dword_800C3BC4;
extern int s03d_dword_800C3BC8;
extern int s03d_dword_800C3BCC;

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3FF4.s")
int ZakoCom_800D4038(void)
{
    int v = s03d_dword_800DC2E0;

    s03d_dword_800DC2E0 = v + 1;
    return v;
}

void ZakoCom_800D4050(int idx)
{
    int *base = &s03d_dword_800DC310;

    base[idx * 4 + 0x98 / 4] = 0;
    base[idx * 4 + 0x90 / 4] = 1;
}

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
int ZakoCom_800D43CC(int arg)
{
    return s03d_dword_800DC31C % arg;
}

void ZakoCom_800D440C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB48);
        out[0] = 0x80;
    }
}
void ZakoCom_800D4460(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB54);
        out[0] = 0x87;
    }
}
void ZakoCom_800D44B4(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB64);
        out[0] = 0x8B;
    }
}
void ZakoCom_800D4508(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB74);
        out[0] = 0x8A;
    }
}
void ZakoCom_800D455C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
    else if (r == 1)
    {
        fprintf(1, s03d_dword_800DBB88);
        out[0] = 0x86;
    }
}
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
void ZakoCom_800D5888(int type, int time)
{
    void *screen;

    if (!s03d_dword_800C3BC4)
    {
        s03d_dword_800C3BC4 = 1;
        s03d_dword_800C3BC8 = time;
        screen = NewCinemaScreen(time, type);
        s03d_dword_800C3BCC = (int)screen;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D58D4.s")
