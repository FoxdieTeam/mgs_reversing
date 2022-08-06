#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include "Game/GM_Control.h"
#include "map/map.h"
#include "Game/game.h"
#include "Font/kcb.h"

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
void  sub_8003603C(int, int);
void  sub_8002A090(int param_1, unsigned short *param_2, unsigned int flags, unsigned int param_4);
void  sub_8002AA48(void);
void  sub_8007913C();
void  sub_80037EE0(int, int);

int HZD_SlopeFloorLevel_800298F8(short *param_1, int arg1);

// TODO: make font.h
void font_set_font_addr_80044BC0(int arg1, void *data);
void font_update_8004695C(KCB *kcb);
void font_clear_800468FC(KCB *kcb);
int font_get_buffer_size_80044F38(KCB *kcb);
int font_init_kcb_80044BE0(KCB *kcb, RECT *rect_data, short x, short y);
void font_set_buffer_80044FD8(KCB *kcb, void *buffer);
void  font_set_color_80044DC4(KCB *kcb, int arg1, int arg2, int arg3);
int font_set_kcb_80044C90(KCB *kcb, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void font_clut_update_80046980(KCB *kcb);

// TODO: make libfs.h?
void FS_StartDaemon_80014A7C(void);
void CDFS_Init_80021EC4();
void CDBIOS_ForceStop_80022864(void);
int  CDBIOS_ReadSync_80022854(void);

// TODO: make sd.h?
void SdMain_80081A18(void);
int sd_task_active_800886C4();

// no idea where these go
void EQ_InvisibleHead_80060D5C(OBJECT *pObj, short *pnPacks, short *pRaise);
void EQ_VisibleHead_80060DF0(OBJECT *pObj, short *pnPacks, short *pRaise);

#endif // _UNKNOWN_H_
