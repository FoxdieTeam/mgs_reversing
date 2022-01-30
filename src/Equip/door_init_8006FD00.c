#include "linker.h"
#include "door.h"
#include "gcl.h"

extern int door_where_8009F5F4;

extern const char aDoorC[]; // "door.c";

int door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where);
void door_act_8006F318(struct Actor_Door *pDoor);
void door_kill_8006F718(struct Actor_Door *pDoor);
int door_read_with_default_value_8006FA28(int param_char, int defaul_val);
void GM_ConfigControl_SetVectorsGCL_800261C0(Res_Control *pControl, char *bReadVec1, char *bReadVec2);
void GM_ConfigControlHazard_8002622C(Res_Control *pControl, short height, short f36, short f38);
void DG_PutObjs_8001BDB8(DG_OBJS *);
int Res_Control_init_loader_44EB9E(Res_Control *pControl, int scriptData, int scriptBinds);
void GM_InitObjectNoRots_800349B0(OBJECT_NO_ROTS *obj, int model, int flag, int motion);
void GM_ConfigObjectSlide_80034CC4(OBJECT *obj);
void GM_ReshadeObjs_80031660(DG_OBJS *pObj);
void door_loader_param_h_8006F978(struct Actor_Door *pDoor, int a_param_v);
void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
void GV_DirVec2_80016F24(int a1, int a2, SVECTOR *a3);

static inline void SetFlag(Res_Control *pCtrl, int flag)
{
    pCtrl->field_55_flags |= flag;
}

// not matching, a few reg swaps
/*
int door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where)
{
    Res_Control *pCtrl; // $s2
    char *door_dir;     // $v0
    char *door_pos;     // $s0
                        //    int door_model;           // $v0
                        //    int door_model_v;         // $v0
    int a_param_v;      // $s2
    int have_c_param;   // $s0
                        //    int param_g_v;            // $v0
                        //    short field_E6_param_w_v; // $v1

    pCtrl = &pDoor->field_20_ctrl;

    if (Res_Control_init_loader_44EB9E(&pDoor->field_20_ctrl, name, where) < 0)
    {
        return -1;
    }

    pDoor->field_E0_where = where;
    door_pos = GCL_GetParam_80020968('p');
    door_dir = GCL_GetParam_80020968('d');
    GM_ConfigControl_SetVectorsGCL_800261C0(&pDoor->field_20_ctrl, door_pos, door_dir);
    GM_ConfigControlHazard_8002622C(&pDoor->field_20_ctrl, -1, -1, -1);

    SetFlag(pCtrl, 2u);

    GM_InitObjectNoRots_800349B0((OBJECT *)&pDoor->field_9C, GCL_GetNextInt_800209E8(GCL_GetParam_80020968('m')), 23, 0);
    GM_ConfigObjectSlide_80034CC4((OBJECT *)&pDoor->field_9C);
    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_vec, &pDoor->field_20_ctrl.field_8_vec);
    DG_PutObjs_8001BDB8(&pDoor->field_9C.objs->world);
    GM_ReshadeObjs_80031660(pDoor->field_9C.objs);

    pDoor->field_E6_param_w_v = pDoor->field_9C.objs->def[2].num_bones_0;

    pDoor->field_E6_param_w_v = door_read_with_default_value_8006FA28('w', 1000);
    pDoor->field_E8_param_s_v = door_read_with_default_value_8006FA28('s', 100);
    pDoor->field_FC_param_u_v = door_read_with_default_value_8006FA28('u', 0);
    pDoor->field_EA_param_h_v = door_read_with_default_value_8006FA28('h', 0);
    pDoor->field_100_param_f_v = door_read_with_default_value_8006FA28('f', -1);
    pDoor->field_EC_param_v_v = door_read_with_default_value_8006FA28('v', 2500);

    a_param_v = door_read_with_default_value_8006FA28('a', 16);
    have_c_param = GCL_GetParam_80020968('c') != 0;

    if (GCL_GetParam_80020968('g'))
    {
        pDoor->field_F4_param_g_v = GCL_GetNextParamValue_80020AD4();
        if (!pDoor->field_F4_param_g_v)
        {
            pDoor->field_F4_param_g_v = -1;
        }
        pDoor->field_F8_maps[0] = GCL_GetNextParamValue_80020AD4();
        pDoor->field_F8_maps[1] = GCL_GetNextParamValue_80020AD4();
    }
    else
    {
        pDoor->field_F4_param_g_v = 0;
    }

    if (GCL_GetParam_80020968('e'))
    {
        pDoor->field_FE_e_param_v1 = GCL_GetNextParamValue_80020AD4();
        pDoor->field_FF_e_param_v2 = GCL_GetNextParamValue_80020AD4();
    }

    if (pDoor->field_E4_t_param_v == 1 && have_c_param == 1) // $s0, $v1, 0x238
    {
        SVECTOR v15; // [sp+10h] [-8h] BYREF
        pCtrl = &pDoor->field_20_ctrl;

        //  SVECTOR *p = &v15;
        GV_DirVec2_80016F24((pCtrl->field_8_vec.vy + 3072) & 0xFFF, pDoor->field_E6_param_w_v / 2, &v15);
        pCtrl->field_0_vec.vx += v15.vx;
        pCtrl->field_0_vec.vz += v15.vz; // lhu		$v0, 4($s0)
    }

    pDoor->field_F2_door_counter = 0;

    if (GCL_GetParam_80020968('o'))
    {
        pDoor->field_E2_maybe_state = 5;
        pDoor->field_F2_door_counter = 1;
        pDoor->field_C0 = pDoor->field_E6_param_w_v;
    }
    else
    {
        pDoor->field_E2_maybe_state = 3;
    }

    if (pDoor->field_EA_param_h_v >= 0)
    {
        door_loader_param_h_8006F978(pDoor, a_param_v);
    }

    return 0;
}
*/

Actor *door_init_8006FD00(int name, int where, int argc, char **argv)
{
    int t_param_v;
    struct Actor_Door *pDoor;

    if (GCL_GetParam_80020968('t'))
    {
        t_param_v = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        t_param_v = 1;
    }

    pDoor = (struct Actor_Door *)GV_ActorAlloc_800150e4(5, sizeof(struct Actor_Door) + (sizeof(struct Actor_Door_TParam) * (t_param_v - 1)));

    door_where_8009F5F4 = 0;

    if (pDoor)
    {

        GV_ActorInit_8001514c(&pDoor->field_0_actor, (TActorFunction)door_act_8006F318, (TActorFunction)door_kill_8006F718, aDoorC);

        pDoor->field_E4_t_param_v = t_param_v;

        if (door_loader_8006FA60(pDoor, name, where) < 0)
        {
            GV_ActorDelayedKill_800151c8(&pDoor->field_0_actor);
            return 0;
        }
    }
    return &pDoor->field_0_actor;
}