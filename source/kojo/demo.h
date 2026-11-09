#ifndef _INC_DEMO
#define _INC_DEMO

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/******************************************************************************
 * included
 */

#include "define.h"

/******************************************************************************
 * prototypes
 */

/* demothrd.c */
extern int DM_ThreadStream(DWORD dwStyle, int unused);
extern int DM_ThreadFile(DWORD dwStyle, char* lpstrFileName);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_DEMO */
