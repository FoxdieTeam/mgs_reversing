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

int   sub_800296C4(HZD_MAP *pHzdMap, SVECTOR *param_2, int flags);
void  sub_800298DC(int *param_1);
void  GM_Sound_800329C4(SVECTOR *, int, int);
int   sub_80028454(HZD_MAP *pHzdMap, SVECTOR *a2, SVECTOR *a3, int flags, int flag);
void  sub_80028890(SVECTOR *pVec);
void  sub_80079004(unsigned short);
int   sub_80029A2C(void);
void  sub_800298C0(void *ptr);
void sub_8002A090(HZD_MAP *pHzdMap, Res_Control_unknown *pCtrlSub, int flags, int hash);
void sub_80029AEC(BindStruct *pBind, Res_Control_unknown *pSubCtrl, int a3, int a4);
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
int    sub_80027384();
void   sub_80027A94(HZD_SEG *pHzdSeg, int a2, int a3);
void   sub_80027F10(HZD_FLR *pHzdFlr);
// TODO: camera.h?
GV_ACT *camera_init_800306A0(void);
int sub_800275A8();
int sub_800276B4();
int sub_80027850(int mult);
int sub_8002799C(int a0);


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
void sub_80029D50(HZD_MAP *pMap, Res_Control_unknown *arg1, int);
void GM_ActControl_helper6_helper_8002A27C(HZD_MAP*, Res_Control_unknown*);
void GM_ActControl_helper6_helper2_8002A4B8(HZD_MAP*, Res_Control_unknown*);
void sub_80029604(HZD_FLR *);
int sub_80029384(HZD_FLR *);
#endif // _UNKNOWN_H_
