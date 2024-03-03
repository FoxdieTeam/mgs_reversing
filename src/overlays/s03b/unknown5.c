#include "Game/game.h"

static int s03b_dword_800D3300[6];

char s03b_dword_800C336C = 0;
int  s03b_dword_800C3370 = 0;
int  s03b_dword_800C3374 = -1;
int  s03b_dword_800C3378 = -1;
char s03b_dword_800C337C = 0;
char s03b_dword_800C337D = 0;
int  s03b_dword_800C3380 = 0;
int  s03b_dword_800C3384 = 0;
int  s03b_dword_800C3388 = 0;
int  s03b_dword_800C338C = 0;

void s03b_boxall_800C9328(void)
{
    s03b_dword_800C336C = 0;
    s03b_dword_800C3370 = -1;
    s03b_dword_800C3374 = -1;
    s03b_dword_800C3378 = -1;
    s03b_dword_800C337C = 0;
    s03b_dword_800C337D = 0;
    s03b_dword_800C3380 = -1;
    s03b_dword_800C3384 = -1;
    s03b_dword_800C338C = 0;
    s03b_dword_800C3388 = 0;

    if (GM_StreamStatus_80037CD8() != -1)
    {
        GM_StreamPlayStop_80037D64();
    }
}

int s03b_boxall_800C93AC(int arg0)
{
    int index;

    if (s03b_dword_800C336C == 6)
    {
        return -1;
    }

    index = s03b_dword_800C336C;
    s03b_dword_800D3300[index] = arg0;
    s03b_dword_800C336C++;
    return 0;
}

void s03b_boxall_800C93F0(int arg0, int arg1)
{
    s03b_dword_800C3388 = arg0;
    s03b_dword_800C338C = arg1;
}

const char aTimeout[] = "timeout %d\n";
#pragma INCLUDE_ASM("asm/overlays/s03b/s03b_boxall_800C9404.s")

int s03b_boxall_800C95DC(void)
{
    return s03b_dword_800C3374;
}

int s03b_boxall_800C95EC(void)
{
    return s03b_dword_800C337C;
}

int s03b_boxall_800C95FC(void)
{
    return s03b_dword_800C337D;
}

int s03b_boxall_800C960C(void)
{
    return s03b_dword_800C3380 > 0;
}

int s03b_boxall_800C961C(int arg0)
{
    if (s03b_dword_800C3374 == arg0 && s03b_dword_800C3380 == 1)
    {
        return 1;
    }

    return 0;
}

int s03b_boxall_800C9654(int arg0)
{
    if (s03b_dword_800C337C == 1 && s03b_dword_800C3378 == arg0)
    {
        s03b_dword_800C3378 = -1;
        return 1;
    }

    return 0;
}

int s03b_boxall_800C968C(void)
{
    return s03b_dword_800C3370;
}
