#ifndef __S19B_JEEPDEMO_H__
#define __S19B_JEEPDEMO_H__

#include <libgte.h>
#include "../democame.h"

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

/* demo camera script callbacks (DEMOCAM_CMD tables in overlay2.c) */
void s19b_jlamp_800D06E0(DemoCamera *work);
void s19b_jlamp_800D072C(DemoCamera *work);
void s19b_jlamp_800D07EC(DemoCamera *work);
void s19b_jlamp_800D087C(DemoCamera *work);
void s19b_jlamp_800D08C8(DemoCamera *work);
void s19b_jlamp_800D08F0(DemoCamera *work);
void s19b_jlamp_800D0928(DemoCamera *work);
void s19b_jlamp_800D094C(DemoCamera *work);
void s19b_jlamp_800D0970(DemoCamera *work);
void s19b_jlamp_800D09B8(DemoCamera *work);
void s19b_jlamp_800D0990(DemoCamera *work);
void s19b_jlamp_800D09DC(DemoCamera *work);

#endif
