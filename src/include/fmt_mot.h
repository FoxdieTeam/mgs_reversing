#ifndef _FMT_MOT_H_
#define _FMT_MOT_H_

#include <sys/types.h>
#include <libgte.h>

typedef unsigned short MOTION_ARCHIVE;
typedef unsigned short MOTION_TABLE;

typedef struct MOTION_SEGMENT
{
    SVECTOR         field_0;
    SVECTOR         field_8;
    int             field_10;
    unsigned short *field_14;
    short           field_18;
    short           field_1A;
    unsigned char   field_1C;
    char            field_1D[7];
} MOTION_SEGMENT;

#endif // _FMT_MOT_H_
