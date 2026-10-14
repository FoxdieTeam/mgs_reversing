#ifndef __S19B_JEEPDEMO_H__
#define __S19B_JEEPDEMO_H__

#include <libgte.h>

/* State of the jeep chase camera (jeepdemo.c), at 0x800DE5C8 */
typedef struct _JlampState
{
    SVECTOR eye;        /* 0x00 */
    int     mode;       /* 0x08 */
    int     dist;       /* 0x0C: eye distance ahead of the jeep */
    int     height;     /* 0x10 */
    int     field_14;   /* 0x14 */
    int     use_target; /* 0x18 */
    SVECTOR target;     /* 0x1C */
} JlampState; /* 0x24 */

#endif
