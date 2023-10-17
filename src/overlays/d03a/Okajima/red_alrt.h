#ifndef _RED_ALRT_H_
#define _RED_ALRT_H_

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _RedAlrtPrims
{
    DR_TPAGE tpage[2];
    TILE     tile[2];
} RedAlrtPrims;

typedef struct _RedAlrtWork
{
    GV_ACT        actor;
    RedAlrtPrims *prims;
    int           f24;
    int           length;
    int           time;
    SVECTOR       f30;
    SVECTOR       f38;
    int           f40;
    SVECTOR       color1;
    SVECTOR       color2;
    int           map;
    int           name;
    int           f5C;
    int           f60;
    int           f64;
    int           f68;
    int           f6C;
} RedAlrtWork;

#endif // _RED_ALRT_H_
