#include "psyq.h"
#include "Menu/menuman.h"

extern char aFfCS[]; // = "\f%c%s";

void sub_8004D14C(char *outstr, char *param_2)
{
    char *str1;
    char *str2;
    int   val;

    sub_8004CF20(param_2[6] - 0x40, &str1, &str2);

    val = (param_2[5] - 0x40) & 7;
    if (val == 0)
    {
        val = 2;
    }
    else if (val < 3)
    {
        val = 1;
    }
    else
    {
        val = 3;
    }
    sprintf(outstr, aFfCS, val | 0x30, str1);
}
