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

#define MAX_WHERES 96

int SECTION(".sbss") GM_CurrentMap;
int SECTION(".sbss") GM_N_WhereList;

extern CONTROL *GM_WhereList[96];
extern CONTROL  DummyPlayer;

static int QueueWhere(CONTROL *where)
{
    int num;

    // スネーク must always be the first item
    if (where->name == CHARAID_SNAKE)
    {
        GM_WhereList[0] = where;
    }
    else
    {
        num = GM_N_WhereList;

        if (num >= MAX_WHERES)
        {
            return -1;
        }

        GM_WhereList[num] = where;
        GM_N_WhereList = num + 1;
    }

    return 0;
}

static void DequeueWhere(CONTROL *where)
{
    CONTROL **list;
    int       i, n;

    list = GM_WhereList;
    n = GM_N_WhereList;

    for (i = n; i > 0; i--)
    {
        if (*list == where)
        {
            goto found;
        }
        list++;
    }
    return;

found:
    if (list != GM_WhereList)
    {
        n--;
        *list = GM_WhereList[n];
        GM_N_WhereList = n;
    }
    else
    {
        GM_WhereList[0] = &DummyPlayer;
    }
}

void GM_InitWhereSystem(void)
{
    GM_WhereList[0] = &DummyPlayer;
    GM_N_WhereList = 1;
}

int GM_InitControl(CONTROL *ctrl, int name, int map)
{
    MAP *ctrl_map;

    if (map == 0)
    {
        map = GM_CurrentMap;
    }

    GM_CurrentMap = map;

    GV_ZeroMemory(ctrl, sizeof(CONTROL));

    ctrl_map = GM_GetMap(map);
    ctrl->map = ctrl_map;
    if (!ctrl_map)
    {
        printf("InitControl : no map %X\n", map);
        return -1;
    }

    ctrl->name = name;
    if (name)
    {
        HZD_SetEvent(&ctrl->evt, name);
        if (QueueWhere(ctrl) < 0)
        {
            return -1;
        }
    }

    ctrl->height = 850;
    ctrl->hzd_height = -32767;
    ctrl->r_sphere = ctrl->s_sphere = 450;
    ctrl->seg_flag = 2;
    ctrl->skip_flag = CTRL_SKIP_TRAP;
    ctrl->levels[0] = -32000;
    ctrl->levels[1] = 32000;

    return 0;
}

static inline void CheckMessage(CONTROL *ctrl)
{
    int     name;
    int     n_msg;
    GV_MSG *msg;
    int     map_msg, move_msg;
    MAP    *ctrl_map;

    name = ctrl->name;

    if ((name != 0) && !(ctrl->skip_flag & CTRL_SKIP_MESSAGE))
    {
        n_msg = GV_ReceiveMessage(name, &ctrl->msg);
        ctrl->n_msg = n_msg;

        msg = ctrl->msg;

        map_msg = HASH_MAP;
        move_msg = HASH_MOVE2;

        for (n_msg--; n_msg >= 0; n_msg--, msg++)
        {
            if (msg->message[0] == map_msg)
            {
                ctrl_map = GM_FindMap(msg->message[1]);

                if (ctrl_map)
                {
                    ctrl->map = ctrl_map;
                }
            }
            else if (msg->message[0] == move_msg)
            {
                ctrl->mov.vx = msg->message[1];
                ctrl->mov.vy = msg->message[2];
                ctrl->mov.vz = msg->message[3];
                ctrl->levels[0] = -32000;
                ctrl->levels[1] = 32000;
            }
        }
    }
}

static inline void CheckCollide(CONTROL *ctrl, HZD_HDL *hzd)
{
    SVECTOR vec;
    int     vx;
    int     new_var;
    int     len;
    int     diff;

    vx = ctrl->step.vx;
    new_var = ctrl->r_sphere / 2;

    if (vx < 0)
    {
        vx = -vx;
    }

    if (ctrl->step.vz > 0)
    {
        vx += ctrl->step.vz;
    }
    else
    {
        vx -= ctrl->step.vz;
    }

    if ((vx > new_var) || (ctrl->skip_flag & (CTRL_BOTH_CHECK | CTRL_SKIP_NEAR_CHECK)))
    {
        GV_AddVec3(&ctrl->mov, &ctrl->step, &vec);

        if (HZD_OnlineHazardCheck(hzd, &ctrl->mov, &vec, HZD_CHK_ALL, ctrl->seg_flag))
        {
            ctrl->n_touches = 0x1;
            ctrl->segs[0] = HZD_GetOnlineHazard();
            ctrl->is_edge[0] = HZD_GetOnlineHazardAtr();

            HZD_GetOnlineVector(ctrl->vecs);

            len = GV_VecLen3(ctrl->vecs);
            diff = len - new_var;

            if (diff < 0)
            {
                diff = -diff;
                GV_LenVec3(ctrl->vecs, &vec, len, diff);
                GV_SubVec3(&DG_ZeroVector, &vec, &vec);
            }
            else
            {
                GV_LenVec3(ctrl->vecs, &vec, len, diff);
            }

            ctrl->step = vec;
        }
    }
}

static inline void CheckNear(CONTROL *ctrl, HZD_HDL *hzd)
{
    SVECTOR vec;
    SVECTOR vec2;
    int     bVar7;
    int     i;

    bVar7 = 0;

    if (ctrl->skip_flag & CTRL_SKIP_NEAR_CHECK)
    {
        return;
    }

retry:
    i = HZD_NearHazardCheck(hzd, &ctrl->mov, 500, HZD_CHK_SEGMENT, ctrl->seg_flag);

    if (i <= 0)
    {
        return;
    }

    ctrl->n_touches = i;

    HZD_GetNearHazard(ctrl->segs);
    HZD_GetIsEdge(ctrl->is_edge);
    HZD_GetNearVector(ctrl->vecs);

    if (!HZD_HazardReaction(ctrl->vecs, i, ctrl->r_sphere, &vec) && !bVar7)
    {
        GV_LenVec3(&ctrl->step, &vec2, GV_VecLen3(&ctrl->step), ctrl->r_sphere / 2);
        bVar7 = 1;
        vec2.vy = 0;
        GV_SubVec3(&ctrl->mov, &vec2, &ctrl->mov);
        goto retry;
    }
    else
    {
        ctrl->mov.vx += vec.vx;
        ctrl->mov.vz += vec.vz;
    }
}

static inline void CheckHeight(CONTROL *ctrl, HZD_HDL *hzd)
{
    int levels[2];
    int vy, vz;
    int iVar11;
    int uVar14;
    int uVar15;
    int uVar16;

    vy = ctrl->mov.vy + ctrl->step.vy;
    vz = ctrl->height;

    ctrl->grounded = 0;
    uVar14 = HZD_LevelHazardCheck(hzd, &ctrl->mov, HZD_CHK_FLOOR);
    HZD_GetLevelHeight(levels);
    ctrl->vecs[0].pad = HZD_GetFloorLevel();
    uVar15 = uVar14 & 1;

    if (((uVar14 & 2) != 0) && ((levels[1] - ctrl->levels[0]) + 199U < 399))
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
        ctrl->grounded = 1;
    }
    else if (uVar16 != 0)
    {
        iVar11 = levels[1] - vz;

        if (iVar11 < vy)
        {
            vy = iVar11;
            ctrl->grounded = 2;
        }
    }

    ctrl->levels[0] = levels[0];
    ctrl->levels[1] = levels[1];
    ctrl->mov.vy = vy;
}

void GM_ActControl(CONTROL *ctrl)
{
    HZD_HDL *hzd;
    int      vy;
    int      time;

    hzd = ctrl->map->hzd;

    CheckMessage(ctrl);

    GM_CurrentMap = ctrl->map->index;

    if (ctrl->r_sphere > 0)
    {
        ctrl->n_touches = 0;

        if (ctrl->hzd_height != -0x7fff)
        {
            vy = ctrl->mov.vy;
            ctrl->mov.vy = ctrl->hzd_height;
        }

        CheckCollide(ctrl, hzd);

        ctrl->mov.vx += ctrl->step.vx;
        ctrl->mov.vz += ctrl->step.vz;

        CheckNear(ctrl, hzd);

        if (ctrl->hzd_height != -0x7fff)
        {
            ctrl->mov.vy = vy;
        }

        time = ctrl->interp;

        if (ctrl->interp == 0)
        {
            GV_NearExp4PV(&ctrl->rot.vx, &ctrl->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&ctrl->rot.vx, &ctrl->turn.vx, ctrl->interp, 3);
            ctrl->interp = time - 1;
        }

        CheckHeight(ctrl, hzd);
    }
    else if (ctrl->r_sphere < 0)
    {
        ctrl->n_touches = 0;

        time = ctrl->interp;

        ctrl->mov.vx += ctrl->step.vx;
        ctrl->mov.vz += ctrl->step.vz;

        if (time == 0)
        {
            GV_NearExp4PV(&ctrl->rot.vx, &ctrl->turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&ctrl->rot.vx, &ctrl->turn.vx, time, 3);
            ctrl->interp = time - 1;
        }

        if (ctrl->r_sphere >= -1)
        {
            CheckHeight(ctrl, hzd);
        }
    }

    if (!(ctrl->skip_flag & CTRL_SKIP_TRAP))
    {
        ctrl->evt.mov = ctrl->mov;
        ctrl->evt.mov.pad = ctrl->rot.vy;
        HZD_EnterTrap(hzd, &ctrl->evt);
    }

    DG_SetPos2(&ctrl->mov, &ctrl->rot);
}

void GM_FreeControl(CONTROL *ctrl)
{
    if (ctrl->name)
    {
        DequeueWhere(ctrl);
    }
}

void GM_ConfigControlVector(CONTROL *ctrl, SVECTOR *mov, SVECTOR *rot)
{
    if (mov)
    {
        ctrl->mov = *mov;
    }

    if (rot)
    {
        ctrl->rot = *rot;
    }
}

void GM_ConfigControlMatrix(CONTROL *ctrl, MATRIX *world)
{
    // GV_ConvertVec3
    ctrl->mov.vx = world->t[0];
    ctrl->mov.vy = world->t[1];
    ctrl->mov.vz = world->t[2];

    DG_MatrixRotYXZ(world, &ctrl->rot);
    ctrl->turn = ctrl->rot;
}

void GM_ConfigControlString(CONTROL *ctrl, char *mov, char *rot)
{
    if (mov)
    {
        GCL_StrToSV(mov, &ctrl->mov);
    }

    if (rot)
    {
        GCL_StrToSV(rot, &ctrl->rot);
    }

    ctrl->turn = ctrl->rot;
}

void GM_ConfigControlHazard(CONTROL *ctrl, int height, int r_sphere, int s_sphere)
{
    ctrl->height = height;
    ctrl->r_sphere = r_sphere;
    ctrl->s_sphere = s_sphere;
}

void GM_ConfigControlAttribute(CONTROL *ctrl, int atr)
{
    ctrl->radar_atr = atr;
}

void GM_ConfigControlInterp(CONTROL *ctrl, int interp)
{
    ctrl->interp = interp;
}

int GM_CheckControlTouches(CONTROL *ctrl, int range)
{
    int n_touches;

    n_touches = ctrl->n_touches;
    if (n_touches == 0)
    {
        return 0;
    }

    if (ctrl->n_touches == 2)
    {
        if (ctrl->segs[1]->p1.h < 0 || GV_VecLen3(&ctrl->vecs[1]) <= range)
        {
            return 2;
        }
    }

    if (ctrl->segs[0]->p1.h < 0 || GV_VecLen3(&ctrl->vecs[0]) <= range)
    {
        return 1;
    }

    return 0;
}

// TODO: range should be u_short
void GM_ConfigControlRadarparam(CONTROL *ctrl, u_short dir, u_short dis, int range, u_short r)
{
    RADAR_SIGHT_PARAM *r_param;

    r_param = &ctrl->radar_param;
    r_param->dir = dir;
    r_param->dis = dis;
    r_param->range = range;
    r_param->r = r;
}

void GM_ConfigControlTrapCheck(CONTROL *ctrl)
{
    ctrl->skip_flag &= ~CTRL_SKIP_TRAP;
}

GV_MSG *GM_CheckMessage(void *work, int name, int msgcode)
{
    GV_MSG *msg;
    int     n_msg;

    n_msg = GV_ReceiveMessage(name, &msg);
    while (--n_msg >= 0)
    {
        if (msg->message[0] == msgcode)
        {
            return msg;
        }
        msg++;
    }
    return NULL;
}
