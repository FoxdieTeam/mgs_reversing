#ifndef _JIRAI_H_
#define _JIRAI_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/object.h"
#include "Game/GM_Control.h"
#include "Game/target.h"

// claymore (on ground)

typedef struct Actor_Jirai
{
    Actor      field_0_actor;
    GM_Control field_20_ctrl;
    OBJECT     field_9C_obj;
    MATRIX     field_C0_mtx;
    int        field_E0;
    int        field_E4;
    int        field_E8;
    int        field_EC;
    int        field_F0;
    int        field_F4;
    int        field_F8;
    int        field_FC;
    GM_Target *field_100_pTarget;
    SVECTOR    field_104_vec;
    short      field_10C;
    short      field_10E;
    int        field_110;
    int        field_114;
    int        field_118;
    int        field_11C;
    int        field_120;
    int        field_124;
    int        field_128;
    int        field_12C;
    int        field_130;
    long       field_134_gcl_arg;
    int        field_138_gcl;
    int        field_13C_idx;
    int        field_140;
    SVECTOR    field_144_vec;
    int        field_14C;
    int        field_150;
} Actor_Jirai;

typedef struct Jirai_unknown
{
    int         field_0_ypos; // might be a short
    Actor      *field_4_pActor;
    GM_Control *field_8_pCtrl;
    GM_Target  *field_C_pTarget;
} Jirai_unknown;

int          jirai_act_8006AB5C(Actor_Jirai *pActor);
int          jirai_loader_8006B564(Actor_Jirai *pActor, int a2, int a3);
void         jirai_loader_helper_8006A798(MATRIX *pMtx1, MATRIX *pMtx2, GM_Target *pTarget);
int          jirai_loader_helper_8006B124(Actor_Jirai *pActor, MATRIX *pMtx, int a3);
void         jirai_kill_8006B05C(Actor_Jirai *pActor);
Actor_Jirai *NewJirai_8006B48C(DG_OBJ *pObj, GM_Target *pTarget);

#endif // _JIRAI_H_
