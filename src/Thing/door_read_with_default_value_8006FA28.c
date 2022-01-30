#include "linker.h"
#include "gcl.h"
#include "door.h"

void door_init_t_value_8006F7AC(
    struct Actor_Door *pDoor,
    struct Actor_Door_TParam *pTParam,
    int param_h_v,
    int param_w_v,
    int param_a_v);

void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
extern void GV_ZeroMemory_8001619c(void *, int);

void door_loader_param_h_8006F978(struct Actor_Door *pDoor, int a_param_v)
{
    int param_w_alternating; 
    int i;
    struct Actor_Door_TParam *pOffset;

    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_vec, &pDoor->field_20_ctrl.field_8_vec);

    param_w_alternating = pDoor->field_E6_param_w_v;
    for (i = 0; i < pDoor->field_E4_t_param_v; i++)
    {
        pOffset = &pDoor->field_104[i];

        GV_ZeroMemory_8001619c(pOffset->field_30, sizeof(pOffset->field_30));
        door_init_t_value_8006F7AC(pDoor, pOffset, pDoor->field_EA_param_h_v, param_w_alternating, a_param_v);

        param_w_alternating = -param_w_alternating;
    }
}

int door_read_with_default_value_8006FA28(unsigned char param_char, int defaul_val)
{
    if (GCL_GetParam_80020968(param_char))
    {
        return GCL_GetNextParamValue_80020AD4();
    }
    return defaul_val;
}
