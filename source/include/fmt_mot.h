#ifndef __MGS_FMT_MOT_H__
#define __MGS_FMT_MOT_H__

#include <sys/types.h>

typedef u_short MOTION_ARCHIVE;
typedef u_short MOTION_TABLE;

typedef struct _DG_OAR {
    MOTION_ARCHIVE *archive;
    u_int           n_joint;
    u_int           n_motion;
    MOTION_TABLE   *table;
    u_short         data[ 0 ];
} DG_OAR;

/*----------------------------------------------------------------*/

/* Older motion format */
typedef struct _DG_NARS {
    u_int   unknown0;
    u_char *unknown1;
} DG_NARS;

#endif // __MGS_FMT_MOT_H__
