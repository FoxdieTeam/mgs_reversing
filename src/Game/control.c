#include "linker.h"
#include "control.h"
#include "mts/mts_new.h"
#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "Game/map.h"
#include "libhzd/libhzd.h"

#include "libgcl/libgcl.h"
#include "libdg/libdg.h"

int SECTION(".sbss") GM_CurrentMap_800AB9B0;
int SECTION(".sbss") gControlCount_800AB9B4;

extern CONTROL *GM_WhereList_800B56D0[96];
extern CONTROL  gDefaultControl_800B5650;
extern SVECTOR DG_ZeroVector_800AB39C;

int GM_ControlPushBack_800258B0(CONTROL *pControlToAdd)
{
    // sna_init must always be the first item
    if (pControlToAdd->field_30_scriptData == CHARA_SNAKE)
    {
        GM_WhereList_800B56D0[0] = pControlToAdd;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        GM_WhereList_800B56D0[gControlCount_800AB9B4] = pControlToAdd;
        gControlCount_800AB9B4++;
    }

    return 0;
}

void GM_ControlRemove_80025904(CONTROL *pControl)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    CONTROL **pControlIter = GM_WhereList_800B56D0;

    while (i > 0)
    {
        i--;

        if (*pControlIter == pControl)
        {
            goto found;
        }
        pControlIter++;
    }

    return;

found:

    if (pControlIter != GM_WhereList_800B56D0)
    {
        *pControlIter = GM_WhereList_800B56D0[--totalCount];
        gControlCount_800AB9B4 = totalCount;
    }
    else
    {
        GM_WhereList_800B56D0[0] = &gDefaultControl_800B5650;
    }
}

void GM_InitWhereSystem_8002597C(void)
{
    GM_WhereList_800B56D0[0] = &gDefaultControl_800B5650;
    gControlCount_800AB9B4 = 1;
}

int GM_InitLoader_8002599C(CONTROL *pControl, int scriptData, int scriptBinds)
{
    MAP *pMapRec;
    const int          mapId = scriptBinds ? scriptBinds : GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = mapId;

    GV_ZeroMemory_8001619C(pControl, sizeof(CONTROL));

    pMapRec = Map_FromId_800314C0(mapId);
    pControl->field_2C_map = pMapRec;
    if (!pMapRec)
    {
        printf("InitControl : no map %X\n", mapId);
        return -1;
    }

    pControl->field_30_scriptData = scriptData;
    if (scriptData)
    {
        HZD_SetEvent_80029AB4(&pControl->field_10_events, scriptData);
        if (GM_ControlPushBack_800258B0(pControl) < 0)
        {
            return -1;
        }
    }

    pControl->field_32_height = 850;
    pControl->field_34_hzd_height = -32767;
    pControl->field_38 = 450;
    pControl->field_36 = 450;
    pControl->field_59 = 2;
    pControl->field_55_skip_flag = CTRL_SKIP_TRAP;
    pControl->field_78_levels[0] = -32000;
    pControl->field_78_levels[1] = 32000;

    return 0;
}


extern SVECTOR DG_ZeroVector_800AB39C;

static inline void GM_ActControl_helper_80025A7C(CONTROL *pControl)
{
    int         scriptData;
    int         count;
    GV_MSG     *pMsg;
    int         hash1, hash2;
    MAP *pMap;

    scriptData = pControl->field_30_scriptData;

    if ((scriptData != 0) && !(pControl->field_55_skip_flag & CTRL_SKIP_MESSAGE))
    {
        count = GV_ReceiveMessage_80016620(scriptData, &pControl->field_5C_mesg);
        pControl->field_56 = count;

        pMsg = pControl->field_5C_mesg;

        hash1 = 0xF9AD;
        hash2 = 0x89CB;

        for (count--; count >= 0; count--, pMsg++)
        {
            if (pMsg->message[0] == hash1)
            {
                pMap = Map_FindByNum_80031504(pMsg->message[1]);

                if (pMap)
                {
                    pControl->field_2C_map = pMap;
                }
            }
            else if (pMsg->message[0] == hash2)
            {
                pControl->field_0_mov.vx = pMsg->message[1];
                pControl->field_0_mov.vy = pMsg->message[2];
                pControl->field_0_mov.vz = pMsg->message[3];
                pControl->field_78_levels[0] = -32000;
                pControl->field_78_levels[1] = 32000;
            }
        }
    }
}

static inline void GM_ActControl_helper2_80025A7C(CONTROL *pControl, HZD_HDL *pHzd)
{
    SVECTOR vec;
    int     vx;
    int     new_var;
    int     len;
    int     diff;

    vx = pControl->field_44_step.vx;
    new_var = pControl->field_36 / 2;

    if (vx < 0)
    {
        vx = -vx;
    }

    if (pControl->field_44_step.vz > 0)
    {
        vx += pControl->field_44_step.vz;
    }
    else
    {
        vx -= pControl->field_44_step.vz;
    }

    if ((vx > new_var) || (pControl->field_55_skip_flag & (CTRL_BOTH_CHECK | CTRL_SKIP_NEAR_CHECK)))
    {
        GV_AddVec3_80016D00(&pControl->field_0_mov, &pControl->field_44_step, &vec);

        if (sub_80028454(pHzd, &pControl->field_0_mov, &vec, 15, pControl->field_59))
        {
            pControl->field_58 = 0x1;
            pControl->field_70[0] = sub_80028820();
            pControl->field_5A[0] = sub_80028830();

            GetVecFromScratchpad_80028840(pControl->field_60_vecs_ary);

            len = GV_VecLen3_80016D80(pControl->field_60_vecs_ary);
            diff = len - new_var;

            if (diff < 0)
            {
                diff = -diff;
                GV_LenVec3_80016DDC(pControl->field_60_vecs_ary, &vec, len, diff);
                GV_SubVec3_80016D40(&DG_ZeroVector_800AB39C, &vec, &vec);
            }
            else
            {
                GV_LenVec3_80016DDC(pControl->field_60_vecs_ary, &vec, len, diff);
            }

            pControl->field_44_step = vec;
        }
    }
}

static inline void GM_ActControl_helper3_80025A7C(CONTROL *pControl, HZD_HDL *pHzd)
{
    SVECTOR vec;
    SVECTOR vec2;
    int     bVar7;
    int     i;

    bVar7 = 0;

    if (pControl->field_55_skip_flag & CTRL_SKIP_NEAR_CHECK)
    {
        return;
    }

retry:
    i = sub_80029098(pHzd,&pControl->field_0_mov, 500, 12, pControl->field_59);

    if (i <= 0)
    {
        return;
    }

    pControl->field_58 = i;

    GM_ActControl_helper3_800292E4(pControl->field_70);
    GM_ActControl_helper4_80029304(pControl->field_5A);
    GM_ActControl_helper5_80029324(pControl->field_60_vecs_ary);

    if (!GM_ActControl_helper_80026C68(pControl->field_60_vecs_ary, i, pControl->field_36, &vec) && !bVar7)
    {
        GV_LenVec3_80016DDC(&pControl->field_44_step, &vec2, GV_VecLen3_80016D80(&pControl->field_44_step), pControl->field_36 / 2);
        bVar7 = 1;
        vec2.vy = 0;
        GV_SubVec3_80016D40(&pControl->field_0_mov,&vec2,&pControl->field_0_mov);
        goto retry;
    }
    else
    {
        pControl->field_0_mov.vx += vec.vx;
        pControl->field_0_mov.vz += vec.vz;
    }
}

static inline void GM_ActControl_helper4_80025A7C(CONTROL *pControl, HZD_HDL *pHzd)
{
    HZD_VEC vec;
    int     vy, vz;
    int     iVar11;
    int     uVar14;
    int     uVar15;
    int     uVar16;

    vy = pControl->field_0_mov.vy + pControl->field_44_step.vy;
    vz = pControl->field_32_height;

    pControl->field_57 = 0;
    uVar14 = sub_800296C4(pHzd, &pControl->field_0_mov, 3);
    sub_800298DC(&vec);
    pControl->field_60_vecs_ary[0].pad = sub_80029A2C();
    uVar15 = uVar14 & 1;

    if (((uVar14 & 2) != 0) && ((vec.long_access[1] - pControl->field_78_levels[0]) + 199U < 399))
    {
        vec.long_access[0] = vec.long_access[1];
        uVar14 &= ~2;
        uVar14 |= 1;
        uVar15 = uVar14 & 1;
    }

    uVar16 = uVar14 & 2;

    if (uVar15 == 0)
    {
        vec.long_access[0] = 0;
    }

    if (uVar16 == 0)
    {
        vec.long_access[1] = 32000;
    }

    iVar11 = vz;

    if (uVar15 != 0)
    {
        iVar11 = vz + vec.long_access[0];
    }

    if (iVar11 > vy)
    {
        vy = iVar11;
        pControl->field_57 = 1;
    }
    else if (uVar16 != 0)
    {
        iVar11 = vec.long_access[1] - vz;

        if (iVar11 < vy)
        {
            vy = iVar11;
            pControl->field_57 = 2;
        }
    }

    pControl->field_78_levels[0] = vec.long_access[0];
    pControl->field_78_levels[1] = vec.long_access[1];
    pControl->field_0_mov.vy = vy;
}

extern void GM_ActControl_helper6_8002A538(HZD_HDL *pMap, HZD_EVT *arg1);

void GM_ActControl_80025A7C(CONTROL *pControl)
{
    HZD_HDL *pHzd;
    int      vy;
    int      time;

    pHzd = pControl->field_2C_map->field_8_hzd;

    GM_ActControl_helper_80025A7C(pControl);

    GM_CurrentMap_800AB9B0 = pControl->field_2C_map->field_0_map_index_bit;

    if (pControl->field_36 > 0)
    {
        pControl->field_58 = 0;

        if (pControl->field_34_hzd_height != -0x7fff)
        {
            vy = pControl->field_0_mov.vy;
            pControl->field_0_mov.vy = pControl->field_34_hzd_height;
        }

        GM_ActControl_helper2_80025A7C(pControl, pHzd);

        pControl->field_0_mov.vx += pControl->field_44_step.vx;
        pControl->field_0_mov.vz += pControl->field_44_step.vz;

        GM_ActControl_helper3_80025A7C(pControl, pHzd);

        if (pControl->field_34_hzd_height != -0x7fff)
        {
            pControl->field_0_mov.vy = vy;
        }

        time = pControl->field_54;

        if (pControl->field_54 == 0)
        {
            GV_NearExp4PV_800269A0(&pControl->field_8_rot.vx, &pControl->field_4C_turn.vx, 3);
        }
        else
        {
            GV_NearTimePV_80026BC4(&pControl->field_8_rot.vx, &pControl->field_4C_turn.vx, pControl->field_54, 3);
            pControl->field_54 = time - 1;
        }

        GM_ActControl_helper4_80025A7C(pControl, pHzd);
    }
    else if (pControl->field_36 < 0)
    {
        pControl->field_58 = 0;

        time = pControl->field_54;

        pControl->field_0_mov.vx += pControl->field_44_step.vx;
        pControl->field_0_mov.vz += pControl->field_44_step.vz;

        if (time == 0)
        {
            GV_NearExp4PV_800269A0(&pControl->field_8_rot.vx, &pControl->field_4C_turn.vx, 3);
        }
        else
        {
            GV_NearTimePV_80026BC4(&pControl->field_8_rot.vx, &pControl->field_4C_turn.vx, time, 3);
            pControl->field_54 = time - 1;
        }

        if (pControl->field_36 >= -1)
        {
            GM_ActControl_helper4_80025A7C(pControl, pHzd);
        }
    }

    if (!(pControl->field_55_skip_flag & CTRL_SKIP_TRAP))
    {
        pControl->field_10_events.field_14_vec = pControl->field_0_mov;
        pControl->field_10_events.field_14_vec.pad = pControl->field_8_rot.vy;
        GM_ActControl_helper6_8002A538(pHzd, &pControl->field_10_events);
    }

    DG_SetPos2_8001BC8C(&pControl->field_0_mov, &pControl->field_8_rot);
}


void GM_FreeControl_800260CC(CONTROL *pControl)
{
    if (pControl->field_30_scriptData)
    {
        GM_ControlRemove_80025904(pControl);
    }
}

void GM_ConfigControlVector_800260FC(CONTROL *pControl, SVECTOR *pVec1, SVECTOR *pVec2)
{
    if (pVec1)
    {
        pControl->field_0_mov = *pVec1;
    }

    if (pVec2)
    {
        pControl->field_8_rot = *pVec2;
    }
}

void GM_ConfigControlMatrix_80026154(CONTROL *pControl, MATRIX *pMatrix)
{
    pControl->field_0_mov.vx = pMatrix->t[0];
    pControl->field_0_mov.vy = pMatrix->t[1];
    pControl->field_0_mov.vz = pMatrix->t[2];

    DG_MatrixRotYXZ_8001E734(pMatrix, &pControl->field_8_rot);

    pControl->field_4C_turn = pControl->field_8_rot;
}

void GM_ConfigControlString_800261C0(CONTROL *pControl, char *param_pos, char *param_dir)
{
    if (param_pos)
    {
        GCL_StrToSV_80020A14(param_pos, &pControl->field_0_mov);
    }

    if (param_dir)
    {
        GCL_StrToSV_80020A14(param_dir, &pControl->field_8_rot);
    }

    pControl->field_4C_turn = pControl->field_8_rot;
}

void GM_ConfigControlHazard_8002622C(CONTROL *pControl, short height, short f36, short f38)
{
    pControl->field_32_height = height;
    pControl->field_36 = f36;
    pControl->field_38 = f38;
}

void GM_ConfigControlAttribute_8002623C(CONTROL *pControl, int radar_atr)
{
    pControl->field_3A_radar_atr = radar_atr;
}

void GM_ConfigControlInterp_80026244(CONTROL *pControl, char f5a)
{
    pControl->field_54 = f5a;
}

int GM_CheckControlTouches_8002624C(CONTROL *pControl, int param_2)
{
    if (pControl->field_58 == 0)
    {
        return 0;
    }

    if (pControl->field_58 == 2)
    {
        if (pControl->field_70[1]->pad < 0 || GV_VecLen3_80016D80(&pControl->field_60_vecs_ary[1]) <= param_2)
        {
            return 2;
        }
    }

    if (pControl->field_70[0]->pad < 0 || GV_VecLen3_80016D80(&pControl->field_60_vecs_ary[0]) <= param_2)
    {
        return 1;
    }

    return 0;
}

void GM_ConfigControlRadarparam_800262EC(CONTROL *pControl, short param_2, short param_3, short param_4,
                                         short param_5)
{
    SVECTOR *pVec;

    pVec = &pControl->field_3C;
    pVec->vx = param_2;
    pVec->vy = param_3;
    pVec->vz = param_4;
    pVec->pad = param_5;
}

void GM_ConfigControlTrapCheck_80026308(CONTROL *pControl)
{
    pControl->field_55_skip_flag &= ~CTRL_SKIP_TRAP;
}

GV_MSG *GM_CheckMessage_8002631C(GV_ACT *pActor, int msgType, int toFind)
{
    GV_MSG *pMsg;
    int     foundCount;
    for (foundCount = GV_ReceiveMessage_80016620(msgType, &pMsg) - 1; foundCount >= 0; foundCount--)
    {
        if (pMsg->message[0] == toFind)
        {
            return pMsg;
        }
        pMsg++;
    }
    return 0;
}
