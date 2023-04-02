#include "door.h"
#include "linker.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libdg/libdg.h"
#include "Game/object.h"
#include "map/map.h"
#include "libhzd/libhzd.h"

extern int      door_where_8009F5F4;
extern int      GM_GameOverTimer_800AB3D4;
extern CONTROL *gSnaControl_800AB9F4;
extern int      dword_800ABA0C;
extern int      dword_8009F470;
extern int      GM_CurrentMap_800AB9B0;

extern const char aOpen[];           // = " open!! \n"
extern const char aClose[];          // = " close!! \n"
extern const char aDoorCloseD[];     // = "door:close %d\n"
extern const char aCancel[];         // = "cancel\n"
extern const char aDoorOpenD[];      // = "door:open %d\n"
extern const char aSnakeDoorX[];     // = "Snake Door %X\n"
extern const char aDoorOpencancel[]; // = "door:opencancel %d\n"
extern const char aCloseDoorX[];     // = "close door %X\n"
extern const char aCloseDoorX_0[];   // = "CLOSE door %X\n"
extern const char aDoorC[];          // = "door.c"

void door_send_msg_8006EC10(unsigned short addr, unsigned short a2)
{
    GV_MSG msg;

    msg.message[0] = 0xF9AD;
    msg.address = addr;
    msg.message[1] = a2;
    msg.message_len = 2;
    GV_SendMessage_80016504(&msg);
}

void door_act_helper_8006EC48(Actor_Door *pDoor)
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

void door_open_8006ECB8(Actor_Door *param_1)
{
    SVECTOR *pos;

    mts_nullsub_8_8008BB98(1, aOpen);
    pos = &(param_1->field_20_ctrl).field_0_mov;

    if (((dword_800ABA0C & param_1->field_E0_where) != 0 && param_1->field_E2_maybe_state != 4 &&
         param_1->field_FE_sound_effect != 0) &&
        param_1->field_C0[0].vx == 0)
    {
        GM_SeSet_80032858(pos, param_1->field_FE_sound_effect);
    }

    param_1->field_E2_maybe_state = 2;
}

void door_close_8006ED48(Actor_Door *param_1)
{
    SVECTOR *pos;

    mts_nullsub_8_8008BB98(1, aClose);
    param_1->field_E2_maybe_state = 1;
    pos = &param_1->field_20_ctrl.field_0_mov;

    if ((dword_800ABA0C & param_1->field_E0_where) != 0)
    {
        if (param_1->field_FE_sound_effect != 0)
        {
            GM_SeSet_80032858(pos, param_1->field_FE_sound_effect);
        }
    }

    param_1->field_E3 = 0;
}

int door_act_helper_8006EDB8(Actor_Door *pActor)
{
    int val = 0xdd2;
    int val2 = 0xd5cc;
    CONTROL *pControl;
    int len;
    GV_MSG *pMsg;
    int temp_s1;
    int var_v2;
    int var_v0;
    int var_v1;
    int temp_s1_2;

    pControl = &pActor->field_20_ctrl;
    pControl->field_56 = GV_ReceiveMessage_80016620(pControl->field_30_scriptData, &pControl->field_5C_mesg);

    for (len = pControl->field_56, pMsg = pControl->field_5C_mesg; len > 0; len--, pMsg++)
    {
        var_v1 = pMsg->message[0];

        if (var_v1 != val2)
        {
            continue;
        }

        mts_nullsub_8_8008BB98(3, aDoorCloseD, pActor->field_F2_door_counter);

        if (pMsg->message_len > 2)
        {
            if (pActor->field_F4_param_g_v > 0)
            {
                temp_s1 = pMsg->message[1];
                var_v2 = (short)pMsg->message[2];

                switch (pActor->field_F4_param_g_v)
                {
                case 1:
                    var_v0 = var_v2 >= pActor->field_20_ctrl.field_0_mov.vz;
                    break;

                case 2:
                    var_v0 = var_v2 >= pActor->field_20_ctrl.field_0_mov.vx;
                    break;

                default:
                    var_v0 = 0;
                    break;
                }

                pActor->field_F6_map_num = pActor->field_F8_maps[var_v0];
                door_send_msg_8006EC10(temp_s1, pActor->field_F6_map_num);
            }

            if ((pMsg->message[1] > 0) && (pMsg->message[1] < 64))
            {
                continue;
            }
        }

        if (--pActor->field_F2_door_counter <= 0)
        {
            if (((pActor->field_E2_maybe_state != 0) || (pActor->field_C0[0].vx != 0)) && (GM_GameOverTimer_800AB3D4 == 0))
            {
                if (pMsg->message_len < 4)
                {
                    pActor->field_EE = 3;
                }
                else
                {
                    pActor->field_EE = pMsg->message[3];
                }

                pActor->field_E2_maybe_state = 4;
            }
        }
        else
        {
            mts_nullsub_8_8008BB98(3, aCancel);
        }
    }

    for (len = pControl->field_56, pMsg = pControl->field_5C_mesg; len > 0; len--, pMsg++)
    {
        var_v1 = pMsg->message[0];
        temp_s1_2 = pMsg->message[1];

        if ((pMsg->message[1] > 0) && (pMsg->message[1] < 64))
        {
            continue;
        }

        if (var_v1 == val)
        {
            if (temp_s1_2 == 0x50AE)
            {
                var_v1 = 0x1AAA;
            }

            if (var_v1 == val)
            {
                mts_nullsub_8_8008BB98(3, aDoorOpenD, pActor->field_F2_door_counter);

                if (++pActor->field_F2_door_counter > 0)
                {
                    door_open_8006ECB8(pActor);

                    pActor->field_F6_map_num = Map_FromId_800314C0(dword_800ABA0C)->field_4_mapNameHash;

                    if ((pMsg->message_len > 1) && (pActor->field_F4_param_g_v > 0))
                    {
                        pActor->field_F0 = temp_s1_2;

                        if ((pActor->field_F0 == 0x21CA) || (dword_800ABA0C & pActor->field_E0_where))
                        {
                            Map_MarkUsed_80031324(pActor->field_F8_maps[0]);
                            Map_MarkUsed_80031324(pActor->field_F8_maps[1]);
                        }

                        if (pActor->field_F0 == 0x21CA)
                        {
                            mts_printf_8008BBA0(aSnakeDoorX, pActor->field_E0_where);
                            door_where_8009F5F4 = pActor->field_E0_where;
                            pActor->field_E5 = 1;
                        }
                    }

                    door_act_helper_8006EC48(pActor);
                }

                continue;
            }
        }

        if ((var_v1 == 0x1AAA) && (++pActor->field_F2_door_counter > 0))
        {
            mts_nullsub_8_8008BB98(3, aDoorOpencancel, pActor->field_F2_door_counter);

            if (pActor->field_E2_maybe_state != 0)
            {
                door_open_8006ECB8(pActor);
            }

            if (pMsg->message[1] == 0x21CA)
            {
                mts_printf_8008BBA0(aSnakeDoorX, pActor->field_E0_where);
                door_where_8009F5F4 = pActor->field_E0_where;
                pActor->field_E5 = 1;
            }

            if (temp_s1_2 == 0x50AE)
            {
                pActor->field_E3 = 1;
            }
        }
    }

    if (pActor->field_F2_door_counter < 0)
    {
        pActor->field_F2_door_counter = 0;
    }

    return 0;
}

void door_act_helper_8006F184(Actor_Door *pActor, int arg1)
{
    SVECTOR dir;
    int i, j;
    Actor_Door_TParam *pTparam;
    HZD_SEG *pSeg;
    int x1, x2, z1, z2;

    if (pActor->field_EA_param_h_v < 0)
    {
        return;
    }

    GV_DirVec2_80016F24((pActor->field_20_ctrl.field_8_rotator.vy + 1024) & 0xFFF, arg1, &dir);

    for (i = 0; i < pActor->field_E4_t_param_v; i++)
    {
        pTparam = &pActor->field_104[i];
        pSeg = pActor->field_104[i].field_0;

        x1 = pTparam->field_30.vx;
        x2 = dir.vx;
        z1 = pTparam->field_30.vz;
        z2 = dir.vz;

        pTparam->field_30 = dir;

        for (j = 0; j < 3; j++, pSeg++)
        {
            pSeg->p1.x += x2 - x1;
            pSeg->p1.z += z2 - z1;
            pSeg->p2.x += x2 - x1;
            pSeg->p2.z += z2 - z1;
        }

        dir.vx = -dir.vx;
        dir.vz = -dir.vz;
    }
}

int door_act_helper_8006F290(CONTROL *pControl, int param_h)
{
    int param_h_50; // $a1
    int diff; // $v1

    if ( param_h < 250 )
    {
        param_h = 250;
    }

    param_h_50 = param_h + 50;

    if ( !gSnaControl_800AB9F4 )
    {
        return 0;
    }

    diff = gSnaControl_800AB9F4->field_0_mov.vx - pControl->field_0_mov.vx;

    if ( (diff < -param_h_50) || (param_h_50 < diff) )
    {
        return 0;
    }

    diff = gSnaControl_800AB9F4->field_0_mov.vz - pControl->field_0_mov.vz;

    if ( (diff < -param_h_50) || (param_h_50 < diff) )
    {
        return 0;
    }

    diff = gSnaControl_800AB9F4->field_0_mov.vy - pControl->field_0_mov.vy;

    if ( (diff > 2500) || (diff < 0)  )
    {
        return 0;
    }

    return 1;
}

void door_act_8006F318(Actor_Door *pActor)
{
    SVECTOR *pVecs;
    int temp_s5;
    int var_s0;
    int var_s3;
    int mapIter;
    map_record *pMap;
    unsigned short hash;
    int mapIter2;
    unsigned short map;
    int var_t1;
    DG_OBJS *pObjs;
    int i;
    int temp_t2;

    if (!door_act_helper_8006EDB8(pActor))
    {
        if ((pActor->field_E2_maybe_state == 4) && ((pActor->field_E3 == 0) || (dword_8009F470 == 0)))
        {
            if (--pActor->field_EE < 0)
            {
                if (door_act_helper_8006F290(&pActor->field_20_ctrl, pActor->field_EA_param_h_v))
                {
                    pActor->field_EE = 30;
                }
                else
                {
                    door_close_8006ED48(pActor);
                }
            }
        }

        if ((pActor->field_E2_maybe_state == 0) || (pActor->field_E2_maybe_state == 4))
        {
            return;
        }
    }

    GM_ActControl_80025A7C(&pActor->field_20_ctrl);
    GM_CurrentMap_800AB9B0 = pActor->field_E0_where;
    GM_ActObject2_80034B88((OBJECT *)&pActor->field_9C);

    pVecs = pActor->field_C0;
    temp_s5 = pActor->field_E6_param_w_v;
    var_s0 = 0;

    if (pActor->field_E2_maybe_state == 2)
    {
        var_s0 = temp_s5;
    }

    if (pActor->field_E2_maybe_state == 5)
    {
        var_s0 = temp_s5;
        pActor->field_E2_maybe_state = 3;
    }

    if ((pActor->field_E2_maybe_state == 1) && door_act_helper_8006F290(&pActor->field_20_ctrl, pActor->field_EA_param_h_v))
    {
        var_s0 = temp_s5 - 2;
    }

    var_s3 = sub_8002646C(pVecs->vx, var_s0, pActor->field_E8_param_s_v);

    if ((var_s3 == pActor->field_E6_param_w_v) || (var_s3 == 0))
    {
        if (pActor->field_E2_maybe_state != 3)
        {
            if ((pVecs->vx != var_s3) && (dword_800ABA0C & pActor->field_E0_where) && pActor->field_FF_e_param_v2)
            {
                GM_SeSet_80032858(&pActor->field_20_ctrl.field_0_mov, pActor->field_FF_e_param_v2);
            }

            if (pActor->field_E2_maybe_state == 1)
            {
                if (pActor->field_F4_param_g_v > 0)
                {
                    if (door_where_8009F5F4 && ((pActor->field_E5 == 0) || (door_where_8009F5F4 != pActor->field_E0_where)))
                    {
                        mts_printf_8008BBA0(aCloseDoorX, door_where_8009F5F4);

                        for (mapIter = 0; mapIter < 2; mapIter++)
                        {
                            pMap = Map_FindByNum_80031504(pActor->field_F8_maps[mapIter]);

                            if ((pMap->field_0_map_index_bit & door_where_8009F5F4) == 0)
                            {
                                GM_DelMap_800313C0(pMap->field_4_mapNameHash);
                            }
                        }
                    }
                    else
                    {
                        mts_printf_8008BBA0(aCloseDoorX_0, door_where_8009F5F4);
                        hash = gSnaControl_800AB9F4->field_2C_map->field_4_mapNameHash;

                        for (mapIter2 = 0; mapIter2 < 2; mapIter2++)
                        {
                            map = pActor->field_F8_maps[mapIter2];

                            if (map != hash)
                            {
                                GM_DelMap_800313C0(map);
                            }
                        }
                    }
                }

                if (pActor->field_E5 && (door_where_8009F5F4 == pActor->field_E0_where))
                {
                    door_where_8009F5F4 = 0;
                }

                pActor->field_E5 = 0;
                door_act_helper_8006EC48(pActor);
            }
        }

        pActor->field_E2_maybe_state = 0;
    }

    door_act_helper_8006F184(pActor, var_s3);

    if (var_s3 < temp_s5 / 8)
    {
        var_t1 = -pActor->field_FC_param_u_v;
    }
    else
    {
        var_t1 = -1000 - pActor->field_FC_param_u_v;
    }

    pObjs = pActor->field_9C.objs;

    if (pObjs->n_models < 2 * pActor->field_E4_t_param_v)
    {
        for (i = 0; i < pActor->field_E4_t_param_v; i++)
        {
            pVecs[i].vx = var_s3;
            pObjs->objs[i].raise = var_t1;
            var_s3 = -var_s3;
        }
    }
    else
    {
        temp_t2 = temp_s5 - var_s3;

        for (i = 0; i < 2 * pActor->field_E4_t_param_v; i += 2)
        {
            pVecs[i].vx = var_s3;
            pObjs->objs[i].raise = var_t1;
            pObjs->objs[i + 1].raise = -pActor->field_FC_param_u_v - temp_t2 * 2;
            var_s3 = -var_s3;
        }
    }
}

static inline void do_nothing_vec_func(SVECTOR *vec)
{
    // Perhaps this had an SVECTOR on the stack with some compiled out code that used it?
}

void door_kill_8006F718(Actor_Door *pDoor)
{
    SVECTOR unused;
    do_nothing_vec_func(&unused);
    GM_FreeControl_800260CC(&pDoor->field_20_ctrl);
    GM_FreeObject_80034BF8((OBJECT *)&pDoor->field_9C);
}

void door_loader_t_param_sub_8006F748(HZD_SEG *pSeg, SVECTOR *pVec1, SVECTOR *pVec2, int param_v)
{
    short vec1_y;

    pSeg->p1.x = pVec1->vx;
    pSeg->p1.z = pVec1->vz;

    pSeg->p2.x = pVec2->vx;
    pSeg->p2.z = pVec2->vz;

    vec1_y = pVec1->vy;
    pSeg->p2.h = param_v;
    pSeg->p1.h = param_v;

    pSeg->p2.y = vec1_y;
    pSeg->p1.y = vec1_y;
    HZD_SetDynamicSegment_8006FEE4(pSeg, pSeg);
}

void door_init_t_value_8006F7AC(Actor_Door *pDoor, Actor_Door_TParam *pOffset, int arg2, int arg3, int flags)
{
    SVECTOR vecs[4];
    HZD_MAP *pMaps[2];
    int z;
    int i;
    int count;
    int param_v;
    HZD_MAP **ppMaps;
    HZD_SEG *pSeg;

    flags |= 0x8000;
    GV_ZeroMemory_8001619C(vecs, sizeof(vecs));

    z = -arg2 / 2;

    for (i = 0; i < 4; i += 2)
    {
        vecs[i].vz = z;
        vecs[i + 1].vz = z;
        vecs[i + 1].vx = arg3;
        z += arg2;
    }

    DG_PutVector_8001BE48(vecs, vecs, 4);

    if (pDoor->field_F4_param_g_v == 0)
    {
        count = 1;
        pMaps[0] = pDoor->field_20_ctrl.field_2C_map->field_8_hzd;
    }
    else
    {
        count = 2;

        for (i = 0; i < count; i++)
        {
            pMaps[i] = Map_FindByNum_80031504(pDoor->field_F8_maps[i])->field_8_hzd;
        }
    }

    param_v = pDoor->field_EC_param_v_v;

    for (i = 0, ppMaps = pMaps; i < count; i++, ppMaps++)
    {
        pSeg = &pOffset->field_0[0];
        door_loader_t_param_sub_8006F748(pSeg, &vecs[0], &vecs[1], param_v);
        HZD_QueueDynamicSegment2_8006FDDC(*ppMaps, pSeg, flags);

        if (arg2 > 0)
        {
            pSeg = &pOffset->field_0[1];
            door_loader_t_param_sub_8006F748(pSeg, &vecs[2], &vecs[3], param_v);
            HZD_QueueDynamicSegment2_8006FDDC(*ppMaps, pSeg, flags);

            pSeg = &pOffset->field_0[2];
            door_loader_t_param_sub_8006F748(pSeg, &vecs[0], &vecs[2], param_v);
            HZD_QueueDynamicSegment2_8006FDDC(*ppMaps, pSeg, flags);
        }
    }
}

void door_loader_param_h_8006F978(Actor_Door *pDoor, int a_param_v)
{
    int                param_w_alternating;
    int                i;
    Actor_Door_TParam *pOffset;

    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_mov, &pDoor->field_20_ctrl.field_8_rotator);

    param_w_alternating = pDoor->field_E6_param_w_v;
    for (i = 0; i < pDoor->field_E4_t_param_v; i++)
    {
        pOffset = &pDoor->field_104[i];

        GV_ZeroMemory_8001619C(&pOffset->field_30, sizeof(pOffset->field_30));
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

static inline void SetFlag(CONTROL *pControl, int flag)
{
    pControl->field_55_skip_flag |= flag;
}

int door_loader_8006FA60(Actor_Door *pDoor, int name, int where)
{
    int             door_model_v;
    int             a_param_v;
    int             have_c_param;
    char           *m_param;
    OBJECT_NO_ROTS *obj;
    char           *door_dir;
    char           *door_pos;

    if (Res_Control_init_loader_8002599C(&pDoor->field_20_ctrl, name, where) < 0)
    {
        return -1;
    }

    pDoor->field_E0_where = where;

    door_pos = (char *)GCL_GetParam_80020968('p');
    door_dir = (char *)GCL_GetParam_80020968('d');

    GM_ConfigControlString_800261C0(&pDoor->field_20_ctrl, door_pos, door_dir);
    GM_ConfigControlHazard_8002622C(&pDoor->field_20_ctrl, -1, -1, -1);

    SetFlag(&pDoor->field_20_ctrl, 2);

    m_param = (char *)GCL_GetParam_80020968('m');
    obj = &pDoor->field_9C;
    door_model_v = GCL_GetNextInt_800209E8(m_param);

    GM_InitObjectNoRots_800349B0(obj, door_model_v, 23, 0);
    GM_ConfigObjectSlide_80034CC4((OBJECT *)&pDoor->field_9C);
    DG_SetPos2_8001BC8C(&pDoor->field_20_ctrl.field_0_mov, &pDoor->field_20_ctrl.field_8_rotator);
    DG_PutObjs_8001BDB8(pDoor->field_9C.objs);
    GM_ReshadeObjs_80031660(pDoor->field_9C.objs);

    pDoor->field_E6_param_w_v = pDoor->field_9C.objs->def[2].num_bones_0; // is this correct?

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

    if (GCL_GetParam_80020968('e')) // (sound) effect?
    {
        pDoor->field_FE_sound_effect = GCL_GetNextParamValue_80020AD4();
        pDoor->field_FF_e_param_v2 = GCL_GetNextParamValue_80020AD4();
    }

    if (pDoor->field_E4_t_param_v == 1 && have_c_param == 1) // $s0, $v1, 0x238
    {
        SVECTOR     vec;
        CONTROL *pControl = &pDoor->field_20_ctrl;
        GV_DirVec2_80016F24((pControl->field_8_rotator.vy + 3072) & 0xFFF, pDoor->field_E6_param_w_v / 2, &vec);
        pControl->field_0_mov.vx += vec.vx;
        pControl->field_0_mov.vz += vec.vz;
    }

    pDoor->field_F2_door_counter = 0;

    if (GCL_GetParam_80020968('o'))
    {
        pDoor->field_E2_maybe_state = 5;
        pDoor->field_F2_door_counter = 1;
        pDoor->field_C0[0].vx = pDoor->field_E6_param_w_v;
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

GV_ACT *NewDoor_8006FD00(int name, int where, int argc, char **argv)
{
    int         t_param_v;
    Actor_Door *pDoor;

    if (GCL_GetParam_80020968('t'))
    {
        t_param_v = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        t_param_v = 1;
    }

    pDoor = (Actor_Door *)GV_NewActor_800150E4(5, sizeof(Actor_Door) + (sizeof(Actor_Door_TParam) * (t_param_v - 1)));

    door_where_8009F5F4 = 0;

    if (pDoor)
    {
        GV_SetNamedActor_8001514C(&pDoor->field_0_actor, (TActorFunction)door_act_8006F318,
                                  (TActorFunction)door_kill_8006F718, aDoorC); // "door.c";

        pDoor->field_E4_t_param_v = t_param_v;

        if (door_loader_8006FA60(pDoor, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&pDoor->field_0_actor);
            return 0;
        }
    }
    return &pDoor->field_0_actor;
}
