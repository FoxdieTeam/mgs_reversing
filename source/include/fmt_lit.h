#ifndef __MGS_FMT_LIT_H__
#define __MGS_FMT_LIT_H__

#include <sys/types.h>
#include <libgte.h>

/*----------------------------------------------------------------*/

typedef struct {
    SVECTOR point;
    u_short r_range;
    u_short e_range;
    CVECTOR color;
} DG_LIT;

typedef struct {
    int    n_lights;
    DG_LIT lights[ 0 ];
} DG_LITS;

#endif // __MGS_FMT_LIT_H__
