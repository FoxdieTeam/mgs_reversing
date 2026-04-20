#include "navigate.h"

void NagivateInit(NAVIGATE *nav, HZD_HDL *hzd, SVECTOR *pos)
{
    nav->addr = HZD_GetAddress(hzd, pos, -1);
    nav->target = -1;
    nav->target_next = -1;
    nav->next = nav->addr;
    nav->next_pos = DG_ZeroVector;
    nav->target_pos = DG_ZeroVector;
}

void NavigateSetTarget(NAVIGATE *nav, HZD_HDL *hzd, SVECTOR *pos)
{
    nav->target = HZD_GetAddress(hzd, pos, -1);
    nav->target_pos = *pos;
    nav->target_next = -1;
}

void NavigateSetTargetPlayer(NAVIGATE *nav)
{
    nav->target = GM_PlayerAddress;
    nav->target_pos = GM_PlayerPosition;
}

int NavigateGetTargetDist(NAVIGATE *nav, SVECTOR *pos)
{
    SVECTOR vec;
    SVECTOR diff;

    vec = *pos;
    vec.vy = nav->target_pos.vy;

    GV_SubVec3(&nav->target_pos, &vec, &diff);
    return GV_VecLen3(&diff);
}

int NavigateTargetNear(NAVIGATE *nav, SVECTOR *pos, int dist)
{
    return NavigateGetTargetDist(nav, pos) < dist;
}

int NavigateUpdate(NAVIGATE *nav, CONTROL *control)
{
    SVECTOR  diff;
    SVECTOR *pos;
    HZD_HDL *hzd;
    int      addr;
    int      target_next;
    int      target;
    int      next;
    int      reach;
    int      zon;
    HZD_ZON *zone;

    pos = &control->mov;
    hzd = control->map->hzd;

    addr = nav->addr;
    target_next = nav->target_next;
    target = nav->target;
    next = nav->next;

    reach = HZD_ReachTo(hzd, addr, next);

    if ((target != target_next) || (reach <= 0))
    {
        nav->target_next = target;

        if (HZD_ReachTo(hzd, addr, target) < 2)
        {
            nav->next_pos = nav->target_pos;
            nav->next = target;

            GV_SubVec3(&nav->target_pos, pos, &diff);
            control->turn.vy = GV_VecDir2(&diff);
            return -1;
        }

        zon = HZD_LinkRoute(hzd, addr, target, &control->mov);
        zone = &hzd->header->zones[zon];

        nav->next_pos.vx = zone->x;
        nav->next_pos.vy = zone->y;
        nav->next_pos.vz = zone->z;

        nav->next = (char)zon | ((char)zon << 8);
    }

    GV_SubVec3(&nav->next_pos, pos, &diff);
    control->turn.vy = GV_VecDir2(&diff);
    return 0;
}
