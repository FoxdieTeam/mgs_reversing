#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/control.h"
#include "Game/jimctrl.h"
#include "Game/map.h"
#include "Game/game.h"
#include "Font/font.h"

// all funcs that don't have header to go in yet

void  sub_80028890(SVECTOR *pVec);
void  sub_800298C0(void *ptr);
void  sub_8007913C();
void   sub_800790E8(); // Takabe
void   sub_800241B4(void *);
void   sub_8002A258(HZD_HDL *param_1, HZD_EVT *param_2);
void   sub_800272E0(SVECTOR *param_1, SVECTOR *param_2);
void   sub_800241C8(char *arg0, int arg1);

void DrawReadError_8002AC9C();

// no idea where these go, Equip/util.h ?
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);
int  EQ_VisibleUnit_80060F20(short *, char *);
void EQ_InvisibleUnit_80060E68(DG_OBJS *pObjs, unsigned int color, int arg2);
void EQ_ChangeTexture_80060CE4(const char *itemName1, const char *itemName2);

array_800B933C_child * sub_80038698();

#endif // _UNKNOWN_H_
