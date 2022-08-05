#ifndef _PSYQ_H_
#define _PSYQ_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

MATRIX        *RotMatrixYXZ_80093798(SVECTOR *r, MATRIX *m);
void           SetRotMatrix_80093218(MATRIX *m);
void           ReadRotMatrix_80092DD8(MATRIX *m);
int            SquareRoot0_80092708(int);
MATRIX        *MulMatrix0_80092A48(MATRIX *m0, MATRIX *m1, MATRIX *m2);
int            Square0_80093340(VECTOR *, VECTOR *);
int            ratan2_80094308(int, int);
int            rsin_80092508(int a1);
int            rcos_800925D8(int a1);
int            StoreImage_8008FB70(RECT *, u_long *);
int            LoadImage2_80091FB0(RECT *, u_long *);
int            StoreImage2_8009209C(RECT *, u_long *);
void          *memset_8008E688(void *pSrc, int value, int len);
int            rand_8008E6B8(void);
void           SetMem_8009944C(int);
int            VSync_80098108(int);
void           DrawSyncCallback_8008F76C(void *);
unsigned int   GetRCnt_800996E8(unsigned int rcnt);
void           DrawOTag_8008FE58(unsigned int *pOt);
u_long        *ClearOTagR_8008FD50(u_long *ot, int n);
void           SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);
void           LoadImage_8008FB10(RECT *, unsigned char *);
DISPENV       *PutDispEnv_80090094(DISPENV *env);
void           PutDrawEnv_8008FEC8(DRAWENV *);
unsigned short GetTPage_80092418(int tp, int abr, int x, int y);
void           DrawPrim_8008FDFC(void *p);
void           VectorNormal_80092838(VECTOR *v0, VECTOR *v1);
void           OuterProduct12_800933AC(VECTOR *v0, VECTOR *v1, VECTOR *v2);
VECTOR        *ApplyMatrixLV_80092C48(MATRIX *m, VECTOR *v0, VECTOR *v1);
MATRIX        *RotMatrixYXZ_gte_80094108(SVECTOR *r, MATRIX *m);
MATRIX        *MulRotMatrix_80092B58(MATRIX *m0);

#endif // _PSYQ_H_
