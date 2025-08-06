#include "control.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/map.h"
#include "strcode.h"

int SECTION(".sbss") GM_CurrentMap;
int SECTION(".sbss") gControlCount_800AB9B4;

extern CONTROL *GM_WhereList[96];
extern CONTROL  gDefaultControl_800B5650;

/* static? */
int GM_ControlPushBack(CONTROL *control)
{
    // スネーク must always be the first item
    if (control->name == CHARA_SNAKE)
    {
        GM_WhereList[0] = control;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        GM_WhereList[gControlCount_800AB9B4] = control;
        gControlCount_800AB9B4++;
    }

    return 0;
}

/* static? */
void GM_ControlRemove(CONTROL *control)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    CONTROL **pControlIter = GM_WhereList;

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

    if (pControlIter != GM_WhereList)
    {
        *pControlIter = GM_WhereList[--totalCount];
        gControlCount_800AB9B4 = totalCount;
    }
    else
    {
        GM_WhereList[0] = &gDefaultControl_800B5650;
    }
}

void GM_InitWhereSystem(void)
{
    GM_WhereList[0] = &gDefaultControl_800B5650;
    gControlCount_800AB9B4 = 1;
}

int GM_InitControl(CONTROL *control, int scriptData, int scriptBinds)
{
    MAP *pMapRec;
    const int mapId = scriptBinds ? scriptBinds : GM_CurrentMap;
    GM_CurrentMap = mapId;

    GV_ZeroMemory(control, sizeof(CONTROL));

    pMapRec = GM_GetMap(mapId);
    control->map = pMapRec;
    if (!pMapRec)
    {
        printf("InitControl : no map %X\n", mapId);
        return -1;
    }

    control->name = scriptData;
    if (scriptData)
    {
        HZD_SetEvent(&control->event, scriptData);
        if (GM_ControlPushBack(control) < 0)
        {
            return -1;
        }
    }

    control->height = 850;
    control->hzd_height = -32767;
    control->field_38 = 450;
    control->step_size = 450;
    control->exclude_flag = 2;
    control->skip_flag = CTRL_SKIP_TRAP;
    control->levels[0] = -32000;
    control->levels[1] = 32000;

    return 0;
}

static inline void CheckMessage(CONTROL *control)
{
    int         scriptData;
    int         count;
    GV_MSG     *pMsg;
    int         map_msg, move_msg;
    MAP *pMap;

    scriptData = control->name;

    if ((scriptData != 0) && !(control->skip_flag & CTRL_SKIP_MESSAGE))
    {
        count = GV_ReceiveMessage(scriptData, &control->messages);
        control->n_messages = count;

        pMsg = control->messages;

        map_msg = HASH_MAP;
        move_msg = HASH_MOVE2;

        for (count--; count >= 0; count--, pMsg++)
        {
            if (pMsg->message[0] == map_msg)
            {
                pMap = GM_FindMap(pMsg->message[1]);

                if (pMap)
                {
                    control->map = pMap;
                }
            }
            else if (pMsg->message[0] == move_msg)
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

static inline void CheckCollide(CONTROL *control, HZD_HDL *hzd)
{
    SVECTOR vec;
    int     vx;
    int     new_var;
    int     len;
    int     diff;

    vx = control->step.vx;
    new_var = control->step_size / 2;

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

        if (HZD_LineCheck(hzd, &control->mov, &vec, HZD_CHECK_ALL, control->exclude_flag))
        {
            control->touch_flag = 0x1;
            control->nears[0] = HZD_LineNearSurface();
            control->nearflags[0] = HZD_LineNearFlag();

            HZD_LineNearDir(control->nearvecs);

            len = GV_VecLen3(control->nearvecs);
            diff = len - new_var;

            if (diff < 0)
            {
                diff = -diff;
                GV_LenVec3(control->nearvecs, &vec, len, diff);
                GV_SubVec3(&DG_ZeroVector, &vec, &vec);
            }
            else
            {
                GV_LenVec3(control->nearvecs, &vec, len, diff);
            }

            control->step = vec;
        }
    }
}

static inline void CheckNear(CONTROL *control, HZD_HDL *hzd)
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
    i = HZD_PointCheck(hzd,&control->mov, 500, ( HZD_CHECK_DYNSEG | HZD_CHECK_SEG ), control->exclude_flag);

    if (i <= 0)
    {
        return;
    }

    control->touch_flag = i;

    HZD_PointNearSurface(control->nears);
    HZD_PointNearFlag(control->nearflags);
    HZD_PointNearVec(control->nearvecs);

    if (!HZD_StepCheck(control->nearvecs, i, control->step_size, &vec) && !bVar7)
    {
        GV_LenVec3(&control->step, &vec2, GV_VecLen3(&control->step), control->step_size / 2);
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

static inline void CheckHeight(CONTROL *control, HZD_HDL *hzd)
{
    int levels[2];
    int vy, vz;
    int iVar11;
    int uVar14;
    int uVar15;
    int uVar16;

    vy = control->mov.vy + control->step.vy;
    vz = control->height;

    control->level_flag = 0;
    uVar14 = HZD_LevelTestHazard(hzd, &control->mov, 3);
    HZD_LevelMinMaxHeights(levels);
    control->nearvecs[0].pad = HZD_LevelMaxHeight();
    uVar15 = uVar14 & 1;

    if (((uVar14 & 2) != 0) && ((levels[1] - control->levels[0]) + 199U < 399))
    {
        levels[0] = levels[1];
        uVar14 &= ~2;
        uVar14 |= 1;
        uVar15 = uVar14 & 1;
    }

    uVar16 = uVar14 & 2;

    if (uVar15 == 0)
    {
        levels[0] = 0;
    }

    if (uVar16 == 0)
    {
        levels[1] = 32000;
    }

    iVar11 = vz;

    if (uVar15 != 0)
    {
        iVar11 = vz + levels[0];
    }

    if (iVar11 > vy)
    {
        vy = iVar11;
        control->level_flag = 1;
    }
    else if (uVar16 != 0)
    {
        iVar11 = levels[1] - vz;

        if (iVar11 < vy)
        {
            vy = iVar11;
            control->level_flag = 2;
        }
    }

    control->levels[0] = levels[0];
    control->levels[1] = levels[1];
    control->mov.vy = vy;
}

void GM_ActControl(CONTROL *control)
{
    HZD_HDL *hzd;
    int      vy;
    int      time;

    hzd = control->map->hzd;

    CheckMessage(control);

    GM_CurrentMap = control->map->index;

    if (control->step_size > 0)
    {
        control->touch_flag = 0;

        if (control->hzd_height != -0x7fff)
        {
            vy = control->mov.vy;
            control->mov.vy = control->hzd_height;
        }

        CheckCollide(control, hzd);

        control->mov.vx += control->step.vx;
        control->mov.vz += control->step.vz;

        CheckNear(control, hzd);

        if (control->hzd_height != -0x7fff)
        {
            control->mov.vy = vy;
        }

        time = control->interp;

        if (control->interp == 0)
        {
            GV_NearExp4PV(&control->rot.vx, &control->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&control->rot.vx, &control->turn.vx, control->interp, 3);
            control->interp = time - 1;
        }

        CheckHeight(control, hzd);
    }
    else if (control->step_size < 0)
    {
        control->touch_flag = 0;

        time = control->interp;

        control->mov.vx += control->step.vx;
        control->mov.vz += control->step.vz;

        if (time == 0)
        {
            GV_NearExp4PV(&control->rot.vx, &control->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&control->rot.vx, &control->turn.vx, time, 3);
            control->interp = time - 1;
        }

        if (control->step_size >= -1)
        {
            CheckHeight(control, hzd);
        }
    }

    if (!(control->skip_flag & CTRL_SKIP_TRAP))
    {
        control->event.pos = control->mov;
        control->event.pos.pad = control->rot.vy;
        HZD_EnterTrap(hzd, &control->event);
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

void GM_ConfigControlMatrix(CONTROL *control, MATRIX *matrix)
{
    control->mov.vx = matrix->t[0];
    control->mov.vy = matrix->t[1];
    control->mov.vz = matrix->t[2];

    DG_MatrixRotYXZ(matrix, &control->rot);

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
    control->step_size = f36;
    control->field_38 = f38;
}

void GM_ConfigControlAttribute(CONTROL *control, int radar_atr)
{
    control->radar_atr = radar_atr;
}

void GM_ConfigControlInterp(CONTROL *control, char interp)
{
    control->interp = interp;
}

int GM_CheckControlTouches(CONTROL *control, int param_2)
{
    HZD_SEG *near;

    if (control->touch_flag == 0)
    {
        return 0;
    }

    if (control->touch_flag == 2)
    {
        near = control->nears[1];

        if (near->p1.h < 0 || GV_VecLen3(&control->nearvecs[1]) <= param_2)
        {
            return 2;
        }
    }

    near = control->nears[0];

    if (near->p1.h < 0 || GV_VecLen3(&control->nearvecs[0]) <= param_2)
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
    int     len;

    for (len = GV_ReceiveMessage(msgType, &msg) - 1; len >= 0; len--)
    {
        if (msg->message[0] == toFind)
        {
            return msg;
        }
        msg++;
    }
    return NULL;
}
