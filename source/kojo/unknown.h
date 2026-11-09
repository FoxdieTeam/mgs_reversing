#ifndef _INC_UNKNOWN
#define _INC_UNKNOWN

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/******************************************************************************
 * included
 */

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libdg/libdg.h"    // for VECTOREX

/******************************************************************************
 * prototypes
 */

/* unknown1.c */
void sub_8007F06C(VECTOREX *param_1, VECTOR *param_2, VECTOR *param_3);
void sub_8007F0D0(VECTOR *out, VECTOR *a, VECTOR *b, VECTOR *c);
VECTOR *sub_8007F1DC(VECTOR *out, VECTOREX *arg1, VECTOR *arg2);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_UNKNOWN */
