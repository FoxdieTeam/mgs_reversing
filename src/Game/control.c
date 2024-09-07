#include "linker.h"
#include "control.h"
#include "mts/mts_new.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "Game/map.h"
#include "strcode.h"

int SECTION(".sbss") GM_CurrentMap_800AB9B0;
int SECTION(".sbss") gControlCount_800AB9B4;

extern CONTROL *GM_WhereList_800B56D0[96];
extern CONTROL  gDefaultControl_800B5650;
extern SVECTOR DG_ZeroVector_800AB39C;

int GM_ControlPushBack(CONTROL *control)
{
    // sna_init must always be the first item
    if (control->name == CHARA_SNAKE)
    {
        GM_WhereList_800B56D0[0] = control;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        GM_WhereList_800B56D0[gControlCount_800AB9B4] = control;
        gControlCount_800AB9B4++;
    }

    return 0;
}

void GM_ControlRemove(CONTROL *control)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    CONTROL **pControlIter = GM_WhereList_800B56D0;

    while (i > 0)
    {
        i--;

        if (*pControlIter == control)
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

void GM_InitWhereSystem(void)
{
    GM_WhereList_800B56D0[0] = &gDefaultControl_800B5650;
    gControlCount_800AB9B4 = 1;
}

int GM_InitControl(CONTROL *control, int scriptData, int scriptBinds)
{
    MAP *pMapRec;
    const int mapId = scriptBinds ? scriptBinds : GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = mapId;

    GV_ZeroMemory(control, sizeof(CONTROL));

    pMapRec = Map_FromId_800314C0(mapId);
    control->map = pMapRec;
    if (!pMapRec)
    {
        printf("InitControl : no map %X\n", mapId);
        return -1;
    }

    control->name = scriptData;
    if (scriptData)
    {
        HZD_SetEvent_80029AB4(&control->field_10_events, scriptData);
        if (GM_ControlPushBack(control) < 0)
        {
            return -1;
        }
    }

    control->height = 850;
    control->hzd_height = -32767;
    control->field_38 = 450;
    control->field_36 = 450;
    control->field_59 = 2;
    control->skip_flag = CTRL_SKIP_TRAP;
    control->levels[0] = -32000;
    control->levels[1] = 32000;

    return 0;
}


extern SVECTOR DG_ZeroVector_800AB39C;

static inline void GM_ActControl_helper(CONTROL *control)
{
    int         scriptData;
    int         count;
    GV_MSG     *pMsg;
    int         hash1, hash2;
    MAP *pMap;

    scriptData = control->name;

    if ((scriptData != 0) && !(control->skip_flag & CTRL_SKIP_MESSAGE))
    {
        count = GV_ReceiveMessage(scriptData, &control->field_5C_mesg);
        control->field_56 = count;

        pMsg = control->field_5C_mesg;

        hash1 = 0xF9AD;
        hash2 = 0x89CB;

        for (count--; count >= 0; count--, pMsg++)
        {
            if (pMsg->message[0] == hash1)
            {
                pMap = Map_FindByNum_80031504(pMsg->message[1]);

                if (pMap)
                {
                    control->map = pMap;
                }
            }
            else if (pMsg->message[0] == hash2)
            {
                control->mov.vx = pMsg->message[1];
                control->mov.vy = pMsg->message[2];
                control->mov.vz = pMsg->message[3];
                control->levels[0] = -32000;
                control->levels[1] = 32000;
            }
        }
    }
}

static inline void GM_ActControl_helper2(CONTROL *control, HZD_HDL *pHzd)
{
    SVECTOR vec;
    int     vx;
    int     new_var;
    int     len;
    int     diff;

    vx = control->step.vx;
    new_var = control->field_36 / 2;

    if (vx < 0)
    {
        vx = -vx;
    }

    if (control->step.vz > 0)
    {
        vx += control->step.vz;
    }
    else
    {
        vx -= control->step.vz;
    }

    if ((vx > new_var) || (control->skip_flag & (CTRL_BOTH_CHECK | CTRL_SKIP_NEAR_CHECK)))
    {
        GV_AddVec3(&control->mov, &control->step, &vec);

        if (sub_80028454(pHzd, &control->mov, &vec, 15, control->field_59))
        {
            control->field_58 = 0x1;
            control->field_70[0] = sub_80028820();
            control->field_5A[0] = sub_80028830();

            GetVecFromScratchpad_80028840(control->field_60_vecs_ary);

            len = GV_VecLen3(control->field_60_vecs_ary);
            diff = len - new_var;

            if (diff < 0)
            {
                diff = -diff;
                GV_LenVec3(control->field_60_vecs_ary, &vec, len, diff);
                GV_SubVec3(&DG_ZeroVector_800AB39C, &vec, &vec);
            }
            else
            {
                GV_LenVec3(control->field_60_vecs_ary, &vec, len, diff);
            }

            control->step = vec;
        }
    }
}

static inline void GM_ActControl_helper3(CONTROL *control, HZD_HDL *pHzd)
{
    SVECTOR vec;
    SVECTOR vec2;
    int     bVar7;
    int     i;

    bVar7 = 0;

    if (control->skip_flag & CTRL_SKIP_NEAR_CHECK)
    {
        return;
    }

retry:
    i = sub_80029098(pHzd,&control->mov, 500, 12, control->field_59);

    if (i <= 0)
    {
        return;
    }

    control->field_58 = i;

    GM_ActControl_helper3_800292E4(control->field_70);
    GM_ActControl_helper4_80029304(control->field_5A);
    GM_ActControl_helper5_80029324(control->field_60_vecs_ary);

    if (!GM_ActControl_helper_80026C68(control->field_60_vecs_ary, i, control->field_36, &vec) && !bVar7)
    {
        GV_LenVec3(&control->step, &vec2, GV_VecLen3(&control->step), control->field_36 / 2);
        bVar7 = 1;
        vec2.vy = 0;
        GV_SubVec3(&control->mov, &vec2, &control->mov);
        goto retry;
    }
    else
    {
        control->mov.vx += vec.vx;
        control->mov.vz += vec.vz;
    }
}

static inline void GM_ActControl_helper4(CONTROL *control, HZD_HDL *pHzd)
{
    HZD_VEC vec;
    int     vy, vz;
    int     iVar11;
    int     uVar14;
    int     uVar15;
    int     uVar16;

    vy = control->mov.vy + control->step.vy;
    vz = control->height;

    control->field_57 = 0;
    uVar14 = sub_800296C4(pHzd, &control->mov, 3);
    sub_800298DC(&vec);
    control->field_60_vecs_ary[0].pad = sub_80029A2C();
    uVar15 = uVar14 & 1;

    if (((uVar14 & 2) != 0) && ((vec.long_access[1] - control->levels[0]) + 199U < 399))
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
        control->field_57 = 1;
    }
    else if (uVar16 != 0)
    {
        iVar11 = vec.long_access[1] - vz;

        if (iVar11 < vy)
        {
            vy = iVar11;
            control->field_57 = 2;
        }
    }

    control->levels[0] = vec.long_access[0];
    control->levels[1] = vec.long_access[1];
    control->mov.vy = vy;
}

extern void GM_ActControl_helper6_8002A538(HZD_HDL *pMap, HZD_EVT *arg1);

void GM_ActControl(CONTROL *control)
{
    HZD_HDL *pHzd;
    int      vy;
    int      time;

    pHzd = control->map->hzd;

    GM_ActControl_helper(control);

    GM_CurrentMap_800AB9B0 = control->map->index;

    if (control->field_36 > 0)
    {
        control->field_58 = 0;

        if (control->hzd_height != -0x7fff)
        {
            vy = control->mov.vy;
            control->mov.vy = control->hzd_height;
        }

        GM_ActControl_helper2(control, pHzd);

        control->mov.vx += control->step.vx;
        control->mov.vz += control->step.vz;

        GM_ActControl_helper3(control, pHzd);

        if (control->hzd_height != -0x7fff)
        {
            control->mov.vy = vy;
        }

        time = control->field_54;

        if (control->field_54 == 0)
        {
            GV_NearExp4PV(&control->rot.vx, &control->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&control->rot.vx, &control->turn.vx, control->field_54, 3);
            control->field_54 = time - 1;
        }

        GM_ActControl_helper4(control, pHzd);
    }
    else if (control->field_36 < 0)
    {
        control->field_58 = 0;

        time = control->field_54;

        control->mov.vx += control->step.vx;
        control->mov.vz += control->step.vz;

        if (time == 0)
        {
            GV_NearExp4PV(&control->rot.vx, &control->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&control->rot.vx, &control->turn.vx, time, 3);
            control->field_54 = time - 1;
        }

        if (control->field_36 >= -1)
        {
            GM_ActControl_helper4(control, pHzd);
        }
    }

    if (!(control->skip_flag & CTRL_SKIP_TRAP))
    {
        control->field_10_events.field_14_vec = control->mov;
        control->field_10_events.field_14_vec.pad = control->rot.vy;
        GM_ActControl_helper6_8002A538(pHzd, &control->field_10_events);
    }

    DG_SetPos2(&control->mov, &control->rot);
}


void GM_FreeControl(CONTROL *control)
{
    if (control->name)
    {
        GM_ControlRemove(control);
    }
}

void GM_ConfigControlVector(CONTROL *control, SVECTOR *pVec1, SVECTOR *pVec2)
{
    if (pVec1)
    {
        control->mov = *pVec1;
    }

    if (pVec2)
    {
        control->rot = *pVec2;
    }
}

void GM_ConfigControlMatrix(CONTROL *control, MATRIX *pMatrix)
{
    control->mov.vx = pMatrix->t[0];
    control->mov.vy = pMatrix->t[1];
    control->mov.vz = pMatrix->t[2];

    DG_MatrixRotYXZ(pMatrix, &control->rot);

    control->turn = control->rot;
}

void GM_ConfigControlString(CONTROL *control, char *param_pos, char *param_dir)
{
    if (param_pos)
    {
        GCL_StrToSV(param_pos, &control->mov);
    }

    if (param_dir)
    {
        GCL_StrToSV(param_dir, &control->rot);
    }

    control->turn = control->rot;
}

void GM_ConfigControlHazard(CONTROL *control, short height, short f36, short f38)
{
    control->height = height;
    control->field_36 = f36;
    control->field_38 = f38;
}

void GM_ConfigControlAttribute(CONTROL *control, int radar_atr)
{
    control->radar_atr = radar_atr;
}

void GM_ConfigControlInterp(CONTROL *control, char f5a)
{
    control->field_54 = f5a;
}

int GM_CheckControlTouches(CONTROL *control, int param_2)
{
    if (control->field_58 == 0)
    {
        return 0;
    }

    if (control->field_58 == 2)
    {
        if (control->field_70[1]->b1.h < 0 || GV_VecLen3(&control->field_60_vecs_ary[1]) <= param_2)
        {
            return 2;
        }
    }

    if (control->field_70[0]->b1.h < 0 || GV_VecLen3(&control->field_60_vecs_ary[0]) <= param_2)
    {
        return 1;
    }

    return 0;
}

void GM_ConfigControlRadarparam(CONTROL *control, u_short dir, u_short len, u_short ang, u_short pad)
{
    RADAR_CONE *cone;

    cone = &control->radar_cone;
    cone->dir = dir;
    cone->len = len;
    cone->ang = ang;
    cone->_pad = pad;
}

void GM_ConfigControlTrapCheck(CONTROL *control)
{
    control->skip_flag &= ~CTRL_SKIP_TRAP;
}

GV_MSG *GM_CheckMessage(GV_ACT *actor, int msgType, int toFind)
{
    GV_MSG *msg;
    int     foundCount;

    for (foundCount = GV_ReceiveMessage(msgType, &msg) - 1; foundCount >= 0; foundCount--)
    {
        if (msg->message[0] == toFind)
        {
            return msg;
        }
        msg++;
    }
    return 0;
}
