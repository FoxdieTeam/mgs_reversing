#ifndef __MGS_OKAJIMA_BULLET_H__
#define __MGS_OKAJIMA_BULLET_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void *NewBulletEnemy(MATRIX *pMtx, int side, int arg2, int noise_len, int arg4);
void *NewBullet(MATRIX *pMtx, int side, int a3, int noise_len);
void *NewBulletEx(int flag, MATRIX* pMtx, int side, int a4, int noise_len, int a6, int damage, int a8, int a9);
void *NewBullet2(MATRIX *pMtx, int side, int a3, int noise_len, int a5, int damage, int a7, int a8);

#endif // __MGS_OKAJIMA_BULLET_H__
