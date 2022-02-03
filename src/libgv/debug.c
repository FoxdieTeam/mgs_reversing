//Not sure of the actual name of this file
#include "mts_new.h"

extern const char aAssertionFaile[];

void GV_Assert_800156E8( char* filename, int line )
{
    mts_printf_8008BBA0( aAssertionFaile, filename, line );
}

void GV_Warning_80015718( char* format, int id )
{
    mts_printf_8008BBA0( format, id );
}

void GV_Error_80015738( char* format, int id )
{
    GV_Warning_80015718( format, id );
}