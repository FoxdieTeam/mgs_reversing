#ifndef _FMT_MOT_H_
#define _FMT_MOT_H_

#include <sys/types.h>
#include <libgte.h>

typedef u_short MOTION_ARCHIVE;
typedef u_short MOTION_TABLE;

typedef struct MOTION_SEGMENT
{
    SVECTOR       base;
    SVECTOR       delta;
    int           interp;
    u_short      *stream;
    short         field_18;
    short         field_1A;
    unsigned char field_1C;
    char          bit_offset;
    char          x_size;
    char          y_size;
    char          z_size;
} MOTION_SEGMENT;

#endif // _FMT_MOT_H_
