#include "door.h"
#include "linker.h"
#include "libgv/libgv.h"
#include "libgcl/gcl.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "map/map.h"

extern int door_where_8009F5F4;

extern const char aDoorC[]; // "door.c";

int  door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where);
void door_act_8006F318(struct Actor_Door *pDoor);
void door_kill_8006F718(struct Actor_Door *pDoor);
int  door_read_with_default_value_8006FA28(unsigned char param_char, int defaul_val);
void GM_ConfigControlString_800261C0(GM_Control *pControl, char *bReadVec1, char *bReadVec2);
void GM_ConfigControlHazard_8002622C(GM_Control *pControl, short height, short f36, short f38);
void DG_PutObjs_8001BDB8(DG_OBJS *);
int  Res_Control_init_loader_8002599C(GM_Control *pControl, int scriptData, int scriptBinds);
void GM_ConfigObjectSlide_80034CC4(OBJECT *obj);
void GM_ReshadeObjs_80031660(DG_OBJS *pObj);
void door_loader_param_h_8006F978(struct Actor_Door *pDoor, int a_param_v);
void DG_SetPos2_8001BC8C(SVECTOR *svector, SVECTOR *svector2);
void GV_DirVec2_80016F24(int a1, int a2, SVECTOR *a3);

map_record *Map_FindByNum_80031504(int mapNameHash);

int HZD_QueueDynamicSegment2_8006FDDC(int pHzd_f0, struct Actor_Door_TParam_sub *pTSub, int a_param_with_flag);

void HZD_SetDynamicSegment_8006FEE4(short *a1, short *a2);

void GM_FreeControl_800260CC(GM_Control *pControl);

int  GV_SendMessage_80016504(GV_MSG *);
void GM_SeSet_80032858(SVECTOR *a1, unsigned int a2);

extern int dword_800ABA0C;

void door_send_msg_8006EC10(unsigned short addr, unsigned short a2)
{
    GV_MSG msg;

    msg.message[0] = 0xF9AD;
    msg.address = addr;
    msg.message[1] = a2;
    msg.message_len = 2;
    GV_SendMessage_80016504(&msg);
}

void door_act_helper_8006EC48(struct Actor_Door *pDoor)
{
    int      v1;
    GCL_ARGS arg_struct;
    long     args[4];

    if (pDoor->field_100_param_f_v >= 0)
    {
        v1 = 54732;
        if (pDoor->field_E2_maybe_state == 2)
        {
            v1 = 3538;
        }

        args[0] = v1;
        args[1] = pDoor->field_F0;
        args[2] = (unsigned short)pDoor->field_F6_map_num;

        arg_struct.argc = 3;
        arg_struct.argv = args;

        GCL_ExecProc_8001FF2C(pDoor->field_100_param_f_v, &arg_struct);
    }
}
#pragma INCLUDE_ASM("asm/Thing/door_open_8006ECB8.s")       // 144 bytes
#pragma INCLUDE_ASM("asm/Thing/door_close_8006ED48.s")      // 112 bytes
#pragma INCLUDE_ASM("asm/Thing/door_act_helper_8006EDB8.s") // 972 bytes
#pragma INCLUDE_ASM("asm/Thing/door_act_helper_8006F184.s") // 268 bytes
#pragma INCLUDE_ASM("asm/Thing/door_act_helper_8006F290.s") // 136 bytes
#pragma INCLUDE_ASM("asm/Thing/door_act_8006F318.s")        // 1024 bytes

static inline void do_nothing_vec_func(SVECTOR *vec)
{
    // Perhaps this had an SVECTOR on the stack with some compiled out code that used it?
}

void door_kill_8006F718(struct Actor_Door *pDoor)
{
    SVECTOR unused;
    do_nothing_vec_func(&unused);
    GM_FreeControl_800260CC(&pDoor->field_20_ctrl);
    GM_FreeObject_80034BF8((OBJECT *)&pDoor->field_9C);
}

void door_loader_t_param_sub_8006F748(struct Actor_Door_TParam_sub *pTSub, SVECTOR *pVec1, SVECTOR *pVec2,
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

#pragma INCLUDE_ASM("asm/Thing/door_init_t_value_8006F7AC.s") // 460 bytes

void door_loader_t_param_sub_8006F748(struct Actor_Door_TParam_sub *pTSub, SVECTOR *pVec1, SVECTOR *pVec2,
                                      short param_v);

void door_init_t_value_8006F7AC(struct Actor_Door *pDoor, struct Actor_Door_TParam *pOffset, short, int, int);
void door_loader_param_h_8006F978(struct Actor_Door *pDoor, int a_param_v)
{
    int                       param_w_alternating;
    int                       i;
    struct Actor_Door_TParam *pOffset;

    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_position, &pDoor->field_20_ctrl.field_8_vec);

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

#pragma INCLUDE_ASM("asm/Thing/door_loader_8006FA60.s") // 672 bytes

static inline void SetFlag(GM_Control *pCtrl, int flag)
{
    pCtrl->field_55_flags |= flag;
}

/*
// not matching, a few reg swaps
int door_loader_8006FA60(struct Actor_Door *pDoor, int name, int where)
{
    GM_Control *pCtrl; // $s2
    char *door_dir;     // $v0
    char *door_pos;     // $s0
                        //    int door_model;           // $v0
                        //    int door_model_v;         // $v0
    int a_param_v;      // $s2
    int have_c_param;   // $s0
                        //    int param_g_v;            // $v0
                        //    short field_E6_param_w_v; // $v1

    pCtrl = &pDoor->field_20_ctrl;

    if (Res_Control_init_loader_8002599C(&pDoor->field_20_ctrl, name, where) < 0)
    {
        return -1;
    }

    pDoor->field_E0_where = where;
    door_pos = GCL_GetParam_80020968('p');
    door_dir = GCL_GetParam_80020968('d');
    GM_ConfigControlString_800261C0(&pDoor->field_20_ctrl, door_pos, door_dir);
    GM_ConfigControlHazard_8002622C(&pDoor->field_20_ctrl, -1, -1, -1);

    SetFlag(pCtrl, 2u);

    GM_InitObjectNoRots_800349B0((OBJECT *)&pDoor->field_9C, GCL_GetNextInt_800209E8(GCL_GetParam_80020968('m')), 23,
0); GM_ConfigObjectSlide_80034CC4((OBJECT *)&pDoor->field_9C);
    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_position, &pDoor->field_20_ctrl.field_8_vec);
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
        pCtrl->field_0_position.vx += v15.vx;
        pCtrl->field_0_position.vz += v15.vz; // lhu		$v0, 4($s0)
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

Actor *NewDoor_8006FD00(int name, int where, int argc, char **argv)
{
    int                t_param_v;
    struct Actor_Door *pDoor;

    if (GCL_GetParam_80020968('t'))
    {
        t_param_v = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        t_param_v = 1;
    }

    pDoor = (struct Actor_Door *)GV_NewActor_800150E4(5, sizeof(struct Actor_Door) +
                                                             (sizeof(struct Actor_Door_TParam) * (t_param_v - 1)));

    door_where_8009F5F4 = 0;

    if (pDoor)
    {

        GV_SetNamedActor_8001514C(&pDoor->field_0_actor, (TActorFunction)door_act_8006F318,
                                  (TActorFunction)door_kill_8006F718, aDoorC);

        pDoor->field_E4_t_param_v = t_param_v;

        if (door_loader_8006FA60(pDoor, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&pDoor->field_0_actor);
            return 0;
        }
    }
    return &pDoor->field_0_actor;
}
