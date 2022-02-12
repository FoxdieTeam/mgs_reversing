#include "linker.h"
#include "door.h"

void HZD_SetDynamicSegment_8006FEE4(short *a1, short *a2);

void GM_FreeControl_800260CC(Res_Control *pControl);
extern void GM_FreeObject_80034BF8(OBJECT *obj);

static inline void do_nothing_vec_func(SVECTOR* vec)
{
    // Perhaps this had an SVECTOR on the stack with some compiled out code that used it?
}

void door_kill_8006F718(struct Actor_Door *pDoor)
{
    SVECTOR unused;
    do_nothing_vec_func(&unused);
    GM_FreeControl_800260CC(&pDoor->field_20_ctrl);
    GM_FreeObject_80034BF8((OBJECT*)&pDoor->field_9C);
}

void door_loader_t_param_sub_8006F748(
    struct Actor_Door_TParam_sub *pTSub,
    SVECTOR *pVec1,
    SVECTOR *pVec2,
    short param_v)
{
    short vec1_y;

    pTSub->field_0_x = pVec1->vx;
    pTSub->field_2_z = pVec1->vz;

    pTSub->field_8_x = pVec2->vx;
    pTSub->field_A_z = pVec2->vz;

    vec1_y = pVec1->vy;
    pTSub->field_E_param_v1 = param_v;
    pTSub->field_6_param_v2 = param_v;

    pTSub->field_C_y = vec1_y;
    pTSub->field_4_y = vec1_y;
    HZD_SetDynamicSegment_8006FEE4(&pTSub->field_0_x, &pTSub->field_0_x);
}
