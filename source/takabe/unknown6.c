#include <stddef.h>

#include "common.h"
#include "takabe/cinema.h"      // for NewCinemaScreen, NewCinemaScreenClose

int   cinema_screen_alive = FALSE;
int   cinema_screen_time = 0;
void *cinema_screen_actor = NULL;

void s03b_boxall_800C969C(int event, int time)
{
    void *screen;

    if (!cinema_screen_alive)
    {
        cinema_screen_alive = TRUE;
        cinema_screen_time = time;
        screen = NewCinemaScreen(time, event);
        cinema_screen_actor = screen;
    }
}

void s03b_boxall_800C96E8(void)
{
    if (cinema_screen_time != 0 && cinema_screen_alive && cinema_screen_actor)
    {
        NewCinemaScreenClose(cinema_screen_actor);
        cinema_screen_actor = NULL;
        cinema_screen_alive = FALSE;
    }
}

void s03b_boxall_800C974C(void)
{
    if (cinema_screen_time != 0 && --cinema_screen_time == 0)
    {
        cinema_screen_actor = NULL;
        cinema_screen_alive = FALSE;
    }
}
