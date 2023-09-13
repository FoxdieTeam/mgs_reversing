// Not sure of the actual name of this file
#include "mts/mts_new.h"

void GV_Assert_800156E8(char *filename, int line)
{
    printf("Assertion failed: %s, line %d\n", filename, line);
}

void GV_Warning_80015718(char *format, int id)
{
    printf(format, id);
}

void GV_Error_80015738(char *format, int id)
{
    GV_Warning_80015718(format, id);
}
