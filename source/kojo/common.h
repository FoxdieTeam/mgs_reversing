#ifndef __MGS_KOJO_COMMON_H__
#define __MGS_KOJO_COMMON_H__

/******************************************************************************
 * prototypes
 */

// TODO: arg types should be void pointers

/* common.c */
extern void InitChain(ACTNODE *root);
extern void NextChain(ACTNODE *root, ACTNODE *node);
extern void DeleteChain(ACTNODE *root, ACTNODE *node);

#endif // __MGS_KOJO_COMMON_H__
