#ifndef _BULLET_H
#define _BULLET_H

#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/target.h"

typedef struct Bullet_vecs
{
    SVECTOR vecs[4];
} Bullet_vecs;

typedef struct Bullet_0x130
{
    char  field_0_pad[6];
    short field_6;
} Bullet_0x130;

typedef struct BulletWork
{
    GV_ACT        field_0_actor;
    int           field_20;
    MATRIX        field_24;
    TARGET     field_44_target;
    DG_PRIM      *field_8C_pPrim;
    SVECTOR       field_90[8];
    Bullet_vecs   field_D0[2];
    SVECTOR       field_110;
    SVECTOR       field_118;
    SVECTOR       field_120;
    SVECTOR       field_128;
    Bullet_0x130 *field_130;
    int           field_134;
    int           field_138;
    int           field_13C;
    int           field_140;
    int           field_144_noise_len;
    int           field_148_side;
    int           field_14C;
    int           field_150;
    int           field_154_hp;
    int           field_158;
    int           field_15C;
    int           field_160;
    int           field_164;
    int           field_168;
    int           field_16C;
} BulletWork;

STATIC_ASSERT_SIZE(BulletWork, 0x170);

GV_ACT *bullet_init_80076584(MATRIX *pMtx, int whichSide, int a3, int noiseLen);
BulletWork * NewBulletEx_80076708(int a1, MATRIX* pMtx, int a3, int a4, int a5, int a6, int a7, int a8, int a9);

#endif // _BULLET_H
