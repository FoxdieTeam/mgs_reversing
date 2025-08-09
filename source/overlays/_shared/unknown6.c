#include <stddef.h>

#include "overlays/_shared/takabe/cinema.h"     // for NewCinemaScreen, NewCinemaScreenClose

int   s03b_dword_800C3390 = 0;
int   s03b_dword_800C3394 = 0;
void *s03b_dword_800C3398 = NULL;

void s03b_boxall_800C969C(int event, int time)
{
    void *screen;

    if (s03b_dword_800C3390 == 0)
    {
        s03b_dword_800C3390 = 1;
        s03b_dword_800C3394 = time;
        screen = NewCinemaScreen(time, event);
        s03b_dword_800C3398 = screen;
    }
}

void s03b_boxall_800C96E8(void)
{
    if (s03b_dword_800C3394 != 0 && s03b_dword_800C3390 != 0 && s03b_dword_800C3398 != NULL)
    {
        NewCinemaScreenClose(s03b_dword_800C3398);
        s03b_dword_800C3398 = NULL;
        s03b_dword_800C3390 = 0;
    }
}

void s03b_boxall_800C974C(void)
{
    if (s03b_dword_800C3394 != 0 && --s03b_dword_800C3394 == 0)
    {
        s03b_dword_800C3398 = NULL;
        s03b_dword_800C3390 = 0;
    }
}
