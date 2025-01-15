#include "door.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "mts/mts.h" // for fprintf
#include "Game/object.h"
#include "Game/map.h"
#include "strcode.h"

// Doors can have multiple moveable leaves (wings),
// for example elevator doors have 2 leaves (left part, right part),
// while most typical doors in MGS have only a single leaf (the entire door).
typedef struct DoorLeafData
{
    HZD_SEG seg[3];
    SVECTOR field_30;
} DoorLeafData;

typedef struct DoorWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS object;
    SVECTOR        field_C0[4]; // Might not be an SVECTOR, it's not used very often
    short          where;
    char           field_E2_maybe_state;
    char           field_E3;
    char           leaf_count;
    char           field_E5;
    short          field_E6_param_w_v;
    short          field_E8_param_s_v;
    short          field_EA_param_h_v;
    short          field_EC_param_v_v;
    short          field_EE;
    short          field_F0;
    short          field_F2_door_counter;
    short          field_F4_param_g_v;
    short          field_F6_map_num;
    unsigned short field_F8_maps[2];
    short          field_FC_param_u_v;
    unsigned char  field_FE_sound_effect;
    char           field_FF_e_param_v2;
    int            field_100_param_f_v;
    DoorLeafData   leaves[1]; // 1 or more leaves
} DoorWork;

#define EXEC_LEVEL 5

extern CONTROL *GM_PlayerControl_800AB9F4;
extern int      GM_PlayerMap_800ABA0C;
extern int      dword_8009F470;
extern int      GM_CurrentMap_800AB9B0;

int door_where_8009F5F4 = 0;

STATIC void door_send_msg_8006EC10(unsigned short addr, unsigned short a2)
{
    GV_MSG msg;

    msg.address = addr;
    msg.message[0] = HASH_MAP;
    msg.message[1] = a2;
    msg.message_len = 2;
    GV_SendMessage(&msg);
}

STATIC void door_act_helper_8006EC48(DoorWork *work)
{
    int      message_type;
    GCL_ARGS args;
    long     argv[4];

    if (work->field_100_param_f_v >= 0)
    {
        if (work->field_E2_maybe_state == 2)
        {
            message_type = HASH_ENTER;
        }
        else
        {
            message_type = HASH_LEAVE;
        }

        argv[0] = message_type;
        argv[1] = work->field_F0;
        argv[2] = (unsigned short)work->field_F6_map_num;

        args.argc = 3;
        args.argv = argv;

        GCL_ExecProc(work->field_100_param_f_v, &args);
    }
}

STATIC void DoorOpen_8006ECB8(DoorWork *work)
{
    SVECTOR *pos;

    fprintf(1, " open!! \n");
    pos = &work->control.mov;

    if ((GM_PlayerMap_800ABA0C & work->where) && work->field_E2_maybe_state != 4 && work->field_FE_sound_effect != 0 &&
        work->field_C0[0].vx == 0)
    {
        GM_SeSet(pos, work->field_FE_sound_effect);
    }

    work->field_E2_maybe_state = 2;
}

STATIC void DoorClose_8006ED48(DoorWork *work)
{
    SVECTOR *pos;

    fprintf(1, " close!! \n");
    work->field_E2_maybe_state = 1;
    pos = &work->control.mov;

    if ((GM_PlayerMap_800ABA0C & work->where) != 0)
    {
        if (work->field_FE_sound_effect != 0)
        {
            GM_SeSet(pos, work->field_FE_sound_effect);
        }
    }

    work->field_E3 = 0;
}

STATIC int DoorPollMessages_8006EDB8(DoorWork *work)
{
    int hash_enter = HASH_ENTER; // open
    int hash_leave = HASH_LEAVE; // close

    GV_MSG *msg;
    int     message_type; // e.g. hash_enter, hash_leave

    CONTROL *control;

    int i;

    int temp_s1;
    int temp_s1_2;
    int var_v2;
    int var_v0;

    control = &work->control;
    control->field_56 = GV_ReceiveMessage(control->name, &control->field_5C_mesg);

    // Process door close messages:
    for (i = control->field_56, msg = control->field_5C_mesg; i > 0; i--, msg++)
    {
        message_type = msg->message[0];

        if (message_type != hash_leave)
        {
            continue;
        }

        fprintf(3, "door:close %d\n", work->field_F2_door_counter);

        if (msg->message_len > 2)
        {
            if (work->field_F4_param_g_v > 0)
            {
                temp_s1 = msg->message[1];
                var_v2 = (short)msg->message[2];

                switch (work->field_F4_param_g_v)
                {
                case 1:
                    var_v0 = var_v2 >= work->control.mov.vz;
                    break;

                case 2:
                    var_v0 = var_v2 >= work->control.mov.vx;
                    break;

                default:
                    var_v0 = 0;
                    break;
                }

                work->field_F6_map_num = work->field_F8_maps[var_v0];
                door_send_msg_8006EC10(temp_s1, work->field_F6_map_num);
            }

            if (msg->message[1] > 0 && msg->message[1] < 64)
            {
                continue;
            }
        }

        if (--work->field_F2_door_counter <= 0)
        {
            if (((work->field_E2_maybe_state != 0) || (work->field_C0[0].vx != 0)) && (GM_GameOverTimer == 0))
            {
                if (msg->message_len < 4)
                {
                    work->field_EE = 3;
                }
                else
                {
                    work->field_EE = msg->message[3];
                }

                work->field_E2_maybe_state = 4;
            }
        }
        else
        {
            fprintf(3, "cancel\n");
        }
    }

    // Process other door messages:
    for (i = control->field_56, msg = control->field_5C_mesg; i > 0; i--, msg++)
    {
        message_type = msg->message[0];
        temp_s1_2 = msg->message[1];

        if ((msg->message[1] > 0) && (msg->message[1] < 64))
        {
            continue;
        }

        if (message_type == hash_enter)
        {
            if (temp_s1_2 == CHARA_RCM)
            {
                message_type = 0x1AAA;
            }

            if (message_type == hash_enter)
            {
                fprintf(3, "door:open %d\n", work->field_F2_door_counter);

                if (++work->field_F2_door_counter > 0)
                {
                    DoorOpen_8006ECB8(work);

                    work->field_F6_map_num = GM_GetMap(GM_PlayerMap_800ABA0C)->name;

                    if (msg->message_len > 1 && work->field_F4_param_g_v > 0)
                    {
                        work->field_F0 = temp_s1_2;

                        if (work->field_F0 == CHARA_SNAKE || (GM_PlayerMap_800ABA0C & work->where))
                        {
                            GM_AddMap(work->field_F8_maps[0]);
                            GM_AddMap(work->field_F8_maps[1]);
                        }

                        if (work->field_F0 == CHARA_SNAKE)
                        {
                            printf("Snake Door %X\n", work->where);
                            door_where_8009F5F4 = work->where;
                            work->field_E5 = 1;
                        }
                    }

                    door_act_helper_8006EC48(work);
                }

                continue;
            }
        }

        if (message_type == 0x1AAA && ++work->field_F2_door_counter > 0)
        {
            fprintf(3, "door:opencancel %d\n", work->field_F2_door_counter);

            if (work->field_E2_maybe_state != 0)
            {
                DoorOpen_8006ECB8(work);
            }

            if (msg->message[1] == CHARA_SNAKE)
            {
                printf("Snake Door %X\n", work->where);
                door_where_8009F5F4 = work->where;
                work->field_E5 = 1;
            }

            if (temp_s1_2 == CHARA_RCM)
            {
                work->field_E3 = 1;
            }
        }
    }

    if (work->field_F2_door_counter < 0)
    {
        work->field_F2_door_counter = 0;
    }

    return 0;
}

STATIC void door_act_helper_8006F184(DoorWork *work, int arg1)
{
    SVECTOR       dir;
    int           i, j;
    DoorLeafData *leaf;
    HZD_SEG      *pSeg;
    int           x1, x2, z1, z2;

    if (work->field_EA_param_h_v < 0)
    {
        return;
    }

    GV_DirVec2((work->control.rot.vy + 1024) & 0xFFF, arg1, &dir);

    for (i = 0; i < work->leaf_count; i++)
    {
        leaf = &work->leaves[i];
        pSeg = work->leaves[i].seg;

        x1 = leaf->field_30.vx;
        x2 = dir.vx;
        z1 = leaf->field_30.vz;
        z2 = dir.vz;

        leaf->field_30 = dir;

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

STATIC int door_act_helper_8006F290(CONTROL *pControl, int param_h)
{
    int param_h_50; // $a1
    int diff;       // $v1

    if (param_h < 250)
    {
        param_h = 250;
    }

    param_h_50 = param_h + 50;

    if (!GM_PlayerControl_800AB9F4)
    {
        return 0;
    }

    diff = GM_PlayerControl_800AB9F4->mov.vx - pControl->mov.vx;

    if ((diff < -param_h_50) || (param_h_50 < diff))
    {
        return 0;
    }

    diff = GM_PlayerControl_800AB9F4->mov.vz - pControl->mov.vz;

    if ((diff < -param_h_50) || (param_h_50 < diff))
    {
        return 0;
    }

    diff = GM_PlayerControl_800AB9F4->mov.vy - pControl->mov.vy;

    if ((diff > 2500) || (diff < 0))
    {
        return 0;
    }

    return 1;
}

STATIC void DoorAct_8006F318(DoorWork *work)
{
    SVECTOR       *pVecs;
    int            temp_s5;
    int            var_s0;
    int            var_s3;
    int            mapIter;
    MAP           *pMap;
    unsigned short hash;
    int            mapIter2;
    unsigned short map;
    int            var_t1;
    DG_OBJS       *pObjs;
    int            i;
    int            temp_t2;

    if (!DoorPollMessages_8006EDB8(work))
    {
        if (work->field_E2_maybe_state == 4 && (!work->field_E3 || dword_8009F470 == 0))
        {
            if (--work->field_EE < 0)
            {
                if (door_act_helper_8006F290(&work->control, work->field_EA_param_h_v))
                {
                    work->field_EE = 30;
                }
                else
                {
                    DoorClose_8006ED48(work);
                }
            }
        }

        if ((work->field_E2_maybe_state == 0) || (work->field_E2_maybe_state == 4))
        {
            return;
        }
    }

    GM_ActControl(&work->control);
    GM_CurrentMap_800AB9B0 = work->where;
    GM_ActObject2((OBJECT *)&work->object);

    pVecs = work->field_C0;
    temp_s5 = work->field_E6_param_w_v;
    var_s0 = 0;

    if (work->field_E2_maybe_state == 2)
    {
        var_s0 = temp_s5;
    }

    if (work->field_E2_maybe_state == 5)
    {
        var_s0 = temp_s5;
        work->field_E2_maybe_state = 3;
    }

    if ((work->field_E2_maybe_state == 1) && door_act_helper_8006F290(&work->control, work->field_EA_param_h_v))
    {
        var_s0 = temp_s5 - 2;
    }

    var_s3 = GV_NearSpeed(pVecs->vx, var_s0, work->field_E8_param_s_v);

    if ((var_s3 == work->field_E6_param_w_v) || (var_s3 == 0))
    {
        if (work->field_E2_maybe_state != 3)
        {
            if ((pVecs->vx != var_s3) && (GM_PlayerMap_800ABA0C & work->where) && work->field_FF_e_param_v2)
            {
                GM_SeSet(&work->control.mov, work->field_FF_e_param_v2);
            }

            if (work->field_E2_maybe_state == 1)
            {
                if (work->field_F4_param_g_v > 0)
                {
                    if (door_where_8009F5F4 && ((work->field_E5 == 0) || (door_where_8009F5F4 != work->where)))
                    {
                        printf("close door %X\n", door_where_8009F5F4);

                        for (mapIter = 0; mapIter < 2; mapIter++)
                        {
                            pMap = GM_FindMap(work->field_F8_maps[mapIter]);

                            if ((pMap->index & door_where_8009F5F4) == 0)
                            {
                                GM_DelMap(pMap->name);
                            }
                        }
                    }
                    else
                    {
                        printf("CLOSE door %X\n", door_where_8009F5F4);
                        hash = GM_PlayerControl_800AB9F4->map->name;

                        for (mapIter2 = 0; mapIter2 < 2; mapIter2++)
                        {
                            map = work->field_F8_maps[mapIter2];

                            if (map != hash)
                            {
                                GM_DelMap(map);
                            }
                        }
                    }
                }

                if (work->field_E5 && (door_where_8009F5F4 == work->where))
                {
                    door_where_8009F5F4 = 0;
                }

                work->field_E5 = 0;
                door_act_helper_8006EC48(work);
            }
        }

        work->field_E2_maybe_state = 0;
    }

    door_act_helper_8006F184(work, var_s3);

    if (var_s3 < temp_s5 / 8)
    {
        var_t1 = -work->field_FC_param_u_v;
    }
    else
    {
        var_t1 = -1000 - work->field_FC_param_u_v;
    }

    pObjs = work->object.objs;

    if (pObjs->n_models < 2 * work->leaf_count)
    {
        for (i = 0; i < work->leaf_count; i++)
        {
            pVecs[i].vx = var_s3;
            pObjs->objs[i].raise = var_t1;
            var_s3 = -var_s3;
        }
    }
    else
    {
        temp_t2 = temp_s5 - var_s3;

        for (i = 0; i < 2 * work->leaf_count; i += 2)
        {
            pVecs[i].vx = var_s3;
            pObjs->objs[i].raise = var_t1;
            pObjs->objs[i + 1].raise = -work->field_FC_param_u_v - temp_t2 * 2;
            var_s3 = -var_s3;
        }
    }
}

STATIC void DoorDie_8006F718(DoorWork *work)
{
    char pad[8]; // unused stack...

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->object);
}

STATIC void door_loader_t_param_sub_8006F748(HZD_SEG *pSeg, SVECTOR *pVec1, SVECTOR *pVec2, int param_v)
{
    pSeg->p1.x = pVec1->vx;
    pSeg->p1.z = pVec1->vz;

    pSeg->p2.x = pVec2->vx;
    pSeg->p2.z = pVec2->vz;

    pSeg->p1.y = pSeg->p2.y = pVec1->vy;

    pSeg->p2.h = param_v;
    pSeg->p1.h = param_v;

    HZD_SetDynamicSegment(pSeg, pSeg);
}

STATIC void DoorInitHzdSegments_8006F7AC(DoorWork *work, DoorLeafData *leaf, int arg2, int arg3, int flags)
{
    SVECTOR   vecs[4];
    HZD_HDL  *pMaps[2];
    int       z;
    int       i;
    int       count;
    int       param_v;
    HZD_HDL **ppMaps;
    HZD_SEG  *pSeg;

    flags |= 0x8000;
    GV_ZeroMemory(vecs, sizeof(vecs));

    z = -arg2 / 2;

    for (i = 0; i < 4; i += 2)
    {
        vecs[i].vz = z;
        vecs[i + 1].vz = z;
        vecs[i + 1].vx = arg3;
        z += arg2;
    }

    DG_PutVector(vecs, vecs, 4);

    if (work->field_F4_param_g_v == 0)
    {
        count = 1;
        pMaps[0] = work->control.map->hzd;
    }
    else
    {
        count = 2;

        for (i = 0; i < count; i++)
        {
            pMaps[i] = GM_FindMap(work->field_F8_maps[i])->hzd;
        }
    }

    param_v = work->field_EC_param_v_v;

    for (i = 0, ppMaps = pMaps; i < count; i++, ppMaps++)
    {
        pSeg = &leaf->seg[0];
        door_loader_t_param_sub_8006F748(pSeg, &vecs[0], &vecs[1], param_v);
        HZD_QueueDynamicSegment2(*ppMaps, pSeg, flags);

        if (arg2 > 0)
        {
            pSeg = &leaf->seg[1];
            door_loader_t_param_sub_8006F748(pSeg, &vecs[2], &vecs[3], param_v);
            HZD_QueueDynamicSegment2(*ppMaps, pSeg, flags);

            pSeg = &leaf->seg[2];
            door_loader_t_param_sub_8006F748(pSeg, &vecs[0], &vecs[2], param_v);
            HZD_QueueDynamicSegment2(*ppMaps, pSeg, flags);
        }
    }
}

STATIC void door_loader_param_h_8006F978(DoorWork *work, int a_param_v)
{
    int           param_w_alternating;
    int           i;
    DoorLeafData *leaf;

    DG_SetPos2(&work->control.mov, &work->control.rot);

    param_w_alternating = work->field_E6_param_w_v;
    for (i = 0; i < work->leaf_count; i++)
    {
        leaf = &work->leaves[i];

        GV_ZeroMemory(&leaf->field_30, sizeof(leaf->field_30));
        DoorInitHzdSegments_8006F7AC(work, leaf, work->field_EA_param_h_v, param_w_alternating, a_param_v);

        param_w_alternating = -param_w_alternating;
    }
}

// Poor man's THING_Gcl_GetIntDefault
STATIC int Door_Gcl_GetIntDefault_8006FA28(unsigned char param, int def)
{
    if (GCL_GetOption(param))
    {
        return GCL_GetNextParamValue();
    }
    return def;
}

STATIC int DoorGetResources_8006FA60(DoorWork *work, int name, int where)
{
    SVECTOR         vec;
    CONTROL        *pControl;
    char           *door_pos;
    char           *door_dir;
    char           *m_param;
    OBJECT_NO_ROTS *obj;
    int             door_model_v;
    int             a_param_v;
    int             have_c_param;
    CONTROL        *pControl2;

    pControl = &work->control;

    if (GM_InitControl(pControl, name, where) < 0)
    {
        return -1;
    }

    work->where = where;

    door_pos = GCL_GetOption('p');
    door_dir = GCL_GetOption('d');

    GM_ConfigControlString(pControl, door_pos, door_dir);
    GM_ConfigControlHazard(pControl, -1, -1, -1);

    pControl->skip_flag |= CTRL_SKIP_TRAP;

    m_param = GCL_GetOption('m');
    obj = &work->object;
    door_model_v = GCL_StrToInt(m_param);

    GM_InitObjectNoRots(obj, door_model_v, 23, 0);
    GM_ConfigObjectSlide((OBJECT *)&work->object);
    DG_SetPos2(&pControl->mov, &pControl->rot);
    DG_PutObjs(work->object.objs);
    GM_ReshadeObjs(work->object.objs);

    work->field_E6_param_w_v = work->object.objs->def[2].num_bones_0; // is this correct?

    work->field_E6_param_w_v = Door_Gcl_GetIntDefault_8006FA28('w', 1000);
    work->field_E8_param_s_v = Door_Gcl_GetIntDefault_8006FA28('s', 100);
    work->field_FC_param_u_v = Door_Gcl_GetIntDefault_8006FA28('u', 0);
    work->field_EA_param_h_v = Door_Gcl_GetIntDefault_8006FA28('h', 0);
    work->field_100_param_f_v = Door_Gcl_GetIntDefault_8006FA28('f', -1);
    work->field_EC_param_v_v = Door_Gcl_GetIntDefault_8006FA28('v', 2500);

    a_param_v = Door_Gcl_GetIntDefault_8006FA28('a', 16);
    have_c_param = GCL_GetOption('c') != 0;

    if (GCL_GetOption('g'))
    {
        work->field_F4_param_g_v = GCL_GetNextParamValue();
        if (!work->field_F4_param_g_v)
        {
            work->field_F4_param_g_v = -1;
        }
        work->field_F8_maps[0] = GCL_GetNextParamValue();
        work->field_F8_maps[1] = GCL_GetNextParamValue();
    }
    else
    {
        work->field_F4_param_g_v = 0;
    }

    if (GCL_GetOption('e')) // (sound) effect?
    {
        work->field_FE_sound_effect = GCL_GetNextParamValue();
        work->field_FF_e_param_v2 = GCL_GetNextParamValue();
    }

    if (work->leaf_count == 1 && have_c_param == 1) // $s0, $v1, 0x238
    {
        pControl2 = &work->control;
        GV_DirVec2((pControl2->rot.vy + 3072) & 0xFFF, work->field_E6_param_w_v / 2, &vec);
        pControl2->mov.vx += vec.vx;
        pControl2->mov.vz += vec.vz;
    }

    work->field_F2_door_counter = 0;

    if (GCL_GetOption('o'))
    {
        work->field_E2_maybe_state = 5;
        work->field_F2_door_counter = 1;
        work->field_C0[0].vx = work->field_E6_param_w_v;
    }
    else
    {
        work->field_E2_maybe_state = 3;
    }

    if (work->field_EA_param_h_v >= 0)
    {
        door_loader_param_h_8006F978(work, a_param_v);
    }

    return 0;
}

GV_ACT *NewDoor(int name, int where, int argc, char **argv)
{
    int       leaf_count;
    DoorWork *work;

    if (GCL_GetOption('t'))
    {
        leaf_count = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        leaf_count = 1;
    }

    work = (DoorWork *)GV_NewActor(EXEC_LEVEL, sizeof(DoorWork) + sizeof(DoorLeafData) * (leaf_count - 1));

    door_where_8009F5F4 = 0;

    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)DoorAct_8006F318,
                         (GV_ACTFUNC)DoorDie_8006F718, "door.c");

        work->leaf_count = leaf_count;

        if (DoorGetResources_8006FA60(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
