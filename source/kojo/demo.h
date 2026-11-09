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
 * definitions and typedefs and structures
 */

#define DMT_EXECUTE       0x00000001
#define DMT_STATEVIEWLOAD 0x00000002
#define DMT_WRITEFILEAVI  0x00000004

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
