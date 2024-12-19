#include <stddef.h>

int   s03b_dword_800C3390 = 0;
int   s03b_dword_800C3394 = 0;
void *s03b_dword_800C3398 = NULL;

void * NewCinemaScreen_800DE434(int, int);
int    NewCinemaScreenClose_800DE4CC(void *);

void s03b_boxall_800C969C(int event, int time)
{
    void *screen;

    if (s03b_dword_800C3390 == 0)
    {
        s03b_dword_800C3390 = 1;
        s03b_dword_800C3394 = time;
        screen = NewCinemaScreen_800DE434(time, event);
        s03b_dword_800C3398 = screen;
    }
}

void s03b_boxall_800C96E8(void)
{
    if (s03b_dword_800C3394 != 0 && s03b_dword_800C3390 != 0 && s03b_dword_800C3398 != NULL)
    {
        NewCinemaScreenClose_800DE4CC(s03b_dword_800C3398);
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
