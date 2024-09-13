#include "Game/game.h"
#include "mts/mts.h"

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

void s03b_boxall_800C9404(void)
{
    int temp_s1;
    int temp_s2;
    int timeout;
    int i;

    if (s03b_dword_800C338C != 0 && --s03b_dword_800C338C <= 0)
    {
        s03b_boxall_800C93AC(s03b_dword_800C3388);
        s03b_dword_800C338C = 0;
    }

    temp_s1 = s03b_dword_800C3370;

    temp_s2 = GM_StreamStatus_80037CD8();
    s03b_dword_800C3370 = temp_s2;

    s03b_dword_800C337C = 0;
    s03b_dword_800C337D = 0;

    if (s03b_dword_800C3380 >= 0 && s03b_dword_800C336C != 0 && temp_s1 != -1)
    {
        if (temp_s1 == 2)
        {
            s03b_dword_800C3380++;
        }

        if (++s03b_dword_800C3384 > 5400)
        {
            timeout = 1;
            printf("timeout %d\n", s03b_dword_800C3374);
            GM_StreamPlayStop_80037D64();
        }
        else
        {
            timeout = 0;
        }

        if (temp_s2 == -1 || timeout == 1)
        {
            s03b_dword_800C3374 = -1;
            s03b_dword_800C3378 = s03b_dword_800D3300[0];
            s03b_dword_800C337C = 1;

            for (i = 0; i < 5; i++)
            {
                s03b_dword_800D3300[i] = s03b_dword_800D3300[i + 1];
            }

            s03b_dword_800C3384 = -1;
            s03b_dword_800C3380 = -1;
            s03b_dword_800C336C--;
        }
    }

    if (temp_s2 == -1 && s03b_dword_800C336C != 0)
    {
        s03b_dword_800C3384 = 0;
        s03b_dword_800C3380 = 0;
        s03b_dword_800C3374 = s03b_dword_800D3300[0];
        s03b_dword_800C337D = 1;
        GM_VoxStream_80037E40(s03b_dword_800C3374, 0);
    }
}

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
