// Not sure of the actual name of this file

#include "libgv/libgv.h"
#include "mts/mts.h"

void GV_Assert(char *filename, int line)
{
    printf("Assertion failed: %s, line %d\n", filename, line);
}

void GV_Warning(char *format, int id)
{
    printf(format, id);
}

void GV_Error(char *format, int id)
{
    GV_Warning(format, id);
}
