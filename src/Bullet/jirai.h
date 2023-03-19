#ifndef _JIRAI_H_
#define _JIRAI_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/object.h"
#include "Game/control.h"
#include "Game/target.h"

// claymore (on ground)

typedef struct Actor_Jirai
{
    GV_ACT      field_0_actor;
    CONTROL field_20_ctrl;
    OBJECT     field_9C_obj;
    MATRIX     field_C0_light_matrices[2];
    TARGET *field_100_pTarget;
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
    int        field_14C_map;
    int        field_150;
} Actor_Jirai;

typedef struct Jirai_unknown
{
    int         field_0_ypos; // might be a short
    GV_ACT      *field_4_pActor;
    CONTROL *field_8_pCtrl;
    TARGET *field_C_pTarget;
} Jirai_unknown;

void    jirai_act_8006AB5C(Actor_Jirai *pActor);
int     jirai_loader_8006B564(Actor_Jirai *pActor, int a2, int map);
MATRIX *jirai_loader_helper_8006A798(MATRIX *arg0, MATRIX *arg1, TARGET *pTarget);
int     jirai_loader_helper_8006B124(Actor_Jirai *pActor, MATRIX *pMtx, int a3);
void    jirai_kill_8006B05C(Actor_Jirai *pActor);

Actor_Jirai *NewJirai_8006B48C(DG_OBJ *pObj, TARGET *pTarget);

#endif // _JIRAI_H_
