#include "linker.h"
#include "gcl.h"
#include "door.h"
#include "map.h"

void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
void DG_PutVector_8001BE48(SVECTOR *svector, SVECTOR *svector2, int count);
map_record *Map_FindByNum_80031504(int mapNameHash);
extern void GV_ZeroMemory_8001619C(void *, int);

int HZD_QueueDynamicSegment2_8006FDDC(int pHzd_f0, struct Actor_Door_TParam_sub *pTSub, int a_param_with_flag);

void door_loader_t_param_sub_8006F748(
    struct Actor_Door_TParam_sub *pTSub,
    SVECTOR *pVec1,
    SVECTOR *pVec2,
    int param_v);


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

        GV_ZeroMemory_8001619C(pOffset->field_30, sizeof(pOffset->field_30));
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
