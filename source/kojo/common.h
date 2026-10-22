#ifndef _INC_COMMON
#define _INC_COMMON

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/******************************************************************************
 * included
 */

#include <stddef.h>
#include "mgstype.h"
#include "define.h"

/******************************************************************************
 * prototypes
 */

/* common.c */
extern void InitChain(void* lpAddress);
extern void NextChain(void* lpManeger, void* lpChain);
extern void DeleteChain(void* lpManeger, void* lpDelete);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_COMMON */
