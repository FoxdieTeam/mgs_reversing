#ifndef _PSYQ_H_
#define _PSYQ_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

MATRIX *RotMatrixYXZ_80093798(SVECTOR *r, MATRIX *m);
void SetRotMatrix_80093218(MATRIX *m);
void ReadRotMatrix_80092DD8(MATRIX *m);
int SquareRoot0_80092708(int);
MATRIX *MulMatrix0_80092A48(MATRIX *m0, MATRIX *m1, MATRIX *m2);
int Square0_80093340(VECTOR *, VECTOR *);
int ratan2_80094308(int, int);
int rsin_80092508(int a1);
int rcos_800925D8(int a1);
int StoreImage_8008FB70(RECT *, u_long *);
int LoadImage2_80091FB0(RECT *, u_long *);
int StoreImage2_8009209C(RECT *, u_long *);
void *memset_8008E688(void *pSrc, int value, int len);
int rand_8008E6B8(void);

#endif // _PSYQ_H_
