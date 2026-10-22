#ifndef __MGS_KOJO_COMMON_H__
#define __MGS_KOJO_COMMON_H__

/******************************************************************************
 * prototypes
 */

/* common.c */
extern void InitChain(void* lpAddress);
extern void NextChain(void* lpManeger, void* lpChain);
extern void DeleteChain(void* lpManeger, void* lpDelete);

#endif // __MGS_KOJO_COMMON_H__
