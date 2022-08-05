#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include "Game/GM_Control.h"
#include "map/map.h"

// all funcs that don't have header to go in yet

int   sub_800296C4(HZD_MAP *param_1, SVECTOR *param_2, unsigned int param_3);
void  sub_800298DC(int *param_1);
void  sub_80026734(short *, SVECTOR *, int);
void  sub_800329C4(GM_Control *, int, int);
int   sub_80026418(int arg0, int arg1);
short sub_8002646C(int, int, char); // dummy signature
int   sub_80028454(void *pHzd, SVECTOR *a2, SVECTOR *a3, int a4, int a5);
void  sub_80028890(SVECTOR *pVec);
void  sub_80079004(unsigned short);
int   sub_80029A2C(void);
void  sub_800298C0(int *int_arr);

int HZD_SlopeFloorLevel_800298F8(short *param_1, int arg1);

// libfs.h?
void CDFS_Init_80021EC4();
void CDBIOS_ForceStop_80022864(void);
int  CDBIOS_ReadSync_80022854(void);

#endif // _UNKNOWN_H_
