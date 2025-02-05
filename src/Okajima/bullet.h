#ifndef _BULLET_H_
#define _BULLET_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewBulletEnemy(MATRIX *arg0, int whichSide, int arg2, int arg3, int arg4);
void *NewBullet(MATRIX *pMtx, int whichSide, int a3, int noiseLen);
void *NewBulletEx(int a1, MATRIX* pMtx, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
void *NewBullet2(MATRIX *pMtx, int a2, int a3, int a4, int a5, int a6, int a7, int a8);

#endif // _BULLET_H_
