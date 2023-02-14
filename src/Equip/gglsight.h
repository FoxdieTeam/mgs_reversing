#ifndef _GGLSIGHT_H
#define _GGLSIGHT_H

// night vision goggles / thermal goggles first person

#include "libgv/libgv.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

typedef struct Actor_gglsight
{
    GV_ACT    field_0_actor;
    int      field_20_type;
    int      field_24;
    int      field_28_rgb;
    DVECTOR  field_2C_4Array[4];
    int      field_3C;
    TILE_1   field_40_tile1[2][24];
    LINE_F2  field_280_lineF2[2][3];
    POLY_F4  field_2E0_polyF4[2][3];
    DR_TPAGE field_370_dr_tpage[2];
    int      field_380;
} Actor_gglsight;

Actor_gglsight *gglsight_init_80078520(int type);
void            gglsight_act_80078228(Actor_gglsight *pActor);
void            gglsight_loader2_80078444(Actor_gglsight *pActor);
void            gglsight_act_helper_80078054(int a1, unsigned short status, DVECTOR *pAxis, int dir, short sens, short max);
void            gglsight_act_helper_80077A24(Actor_gglsight *pActor);
void            gglsight_act_helper_80077F70(Actor_gglsight *pActor);
void            gglsight_act_helper_80077C6C(Actor_gglsight *pActor);
void            gglsight_act_helper_80077D24(Actor_gglsight *pActor);

#endif // _GGLSIGHT_H
