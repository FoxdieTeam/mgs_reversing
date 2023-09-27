#include "psyq.h"

int camera_800C8314(int, int);
int camera_800C838C(int, int, char *);

void camera_800C8564(int arg0, int arg1, char *arg2)
{
    char sp10[64];

    sprintf(sp10, arg2);
    camera_800C838C(arg0, arg1, sp10);
    camera_800C8314(arg0, arg1);
}
