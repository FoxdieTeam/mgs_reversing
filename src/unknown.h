#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "Game/control.h"
#include "map/map.h"
#include "Game/game.h"
#include "Font/font.h"

// all funcs that don't have header to go in yet

int   sub_800296C4(HZD_MAP *param_1, SVECTOR *param_2, unsigned int param_3);
void  sub_800298DC(int *param_1);
void  GM_Sound_800329C4(SVECTOR *, int, int);
int   sub_80028454(void *pHzd, SVECTOR *a2, SVECTOR *a3, int a4, int a5);
void  sub_80028890(SVECTOR *pVec);
void  sub_80079004(unsigned short);
int   sub_80029A2C(void);
void  sub_800298C0(void *ptr);
void  sub_8002A090(HZD_MAP *param_1, Res_Control_unknown *param_2, unsigned int flags, unsigned int param_4);
void  sub_8007913C();
Actor_strctrl *sub_80037EE0(int vox_stream, int gcl_proc);
void   sub_800790E8(); // Takabe
void   sub_800241B4(void *);
int    sub_80029514(SVECTOR *);
void   sub_8002A258(HZD_MAP *param_1, Res_Control_unknown *param_2);
int    sub_80029098(HZD_MAP *, SVECTOR *, int, int, int);
void   sub_80032AEC(int byte_2, int byte_1, int byte_0);
int    sub_80028830(void);
void   sub_800272E0(SVECTOR *param_1, SVECTOR *param_2);
SVECTOR *sub_80028820(void);
void   sub_800241C8(char *arg0, int arg1);

// TODO: bullet.h?
GV_ACT* bullet_init_80076584(MATRIX *pMtx, int a2, int a3, int noiseLen);

// TODO: camera.h?
GV_ACT *camera_init_800306A0(void);

void DrawReadError_8002AC9C(void);

// TODO: make sd.h?
void SdMain_80081A18(void);
int  sd_task_active_800886C4();
void sd_set_80088CB0(int sdCode);
int  StrSpuTransWithNoLoop_800827AC();

// no idea where these go, Equip/util.h ?
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);
int  EQ_VisibleUnit_80060F20(short *, char *);
void EQ_InvisibleUnit_80060E68(DG_OBJS *pObjs, unsigned int color, int arg2);
void EQ_ChangeTexture_80060CE4(const char *itemName1, const char *itemName2);
void face_item_helper_80060CB8(u_short *in, u_short *out);

#endif // _UNKNOWN_H_
