#include "zako.h"

#include "mgstype.h"
#include "enemy/eyeflash.h"     // for NewEyeflash
#include "game/game.h"

void ZakoCom_800D4088(void);

void s03d_800D0C90(Work *work, int arg);
int s03d_800D414C(int, int);

SVECTOR s03d_dword_800C3B68[] =
{
    {6750, 0, -1000},
    {7250, 0, 500},
    {6750, 0, 2000},
};


void s03d_800D2C20(Work *work)
{
    work->target_addr = ZakoPlayerAddress;
    work->target_pos = ZakoPlayerPosition;
    work->target_map = ZakoPlayerMap;
}

void s03d_800D2C68(Work *work)
{
    int      addr;
    int      index;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    addr = work->param.defends[work->param.c_root];

    /* &zones[addr], spelled out to match (addr * 3 * 8 == addr * sizeof(HZD_ZON)) */
    index = addr << 1;
    index = addr + index;

    hzd = work->control.map->hzd;
    zone = (HZD_ZON *)((char *)hzd->def->zones + index * 8);

    work->target_addr = addr | (addr << 8);

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

void s03d_800D2CCC(Work *work)
{
    if (work->param.defends[work->param.c_root] == 0xFF)
    {
        work->think2 = 1;
        work->think1 = 0;
        work->think3 = 4;
    }
    else
    {
        work->think2 = 3;
        work->think1 = 0;
        work->think3 = 13;
        s03d_800D2C68(work);
    }

    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s03d_800D2D44(Work *work)
{
    work->think2 = 2;
    work->think3 = 9;
    work->think1 = 0;
    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s03d_800D2D68(Work *work)
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->pad.field_4 = 1;
}

int s03d_800D2D84(SVECTOR *a, SVECTOR *b)
{
    SVECTOR diff;

    GV_SubVec3(b, a, &diff);
    diff.vy = 0;
    return GV_VecDir2(&diff);
}

int s03d_800D2DBC(Work *work)
{
    SVECTOR  dir;
    HZD_HDL *hzd;
    SVECTOR *pos;
    int      from, to;
    int      addr, addr2, addr3;
    HZD_ZON *zone;
    CONTROL *control;
    int      reach;

    hzd = work->control.map->hzd;

    if (work->target_map == work->control.map->index)
    {
        pos = &work->target_pos;
        to = work->target_addr;
    }
    else
    {
        pos = &work->target_pos;
        addr = s03d_800D414C(work->control.map->index, work->target_map);
        to = (addr << 8) | addr;

        zone = &hzd->def->zones[addr];
        pos->vx = zone->x;
        pos->vy = zone->y;
        pos->vz = zone->z;
    }

    control = &work->control;

    from = work->current_addr = HZD_GetAddress(hzd, &control->mov, work->current_addr);
    reach = HZD_ReachTo(hzd, from, work->next_addr);
    if (to != work->last_addr || reach <= 0)
    {
        work->last_addr = to;

        if (HZD_ReachTo(hzd, from, to) < 2)
        {
            if (work->target_map == work->control.map->index)
            {
                work->next_pos = *pos;
                work->next_addr = to;
                GV_SubVec3(&work->next_pos, &control->mov, &dir);
                work->pad.dir = GV_VecDir2(&dir);
                return -1;
            }

            addr2 = s03d_800D414C(work->target_map, control->map->index);
            control->map = GM_GetMap(work->target_map);

            zone = &control->map->hzd->def->zones[addr2];
            control->mov.vx = zone->x;
            control->mov.vy = zone->y;
            control->mov.vz = zone->z;

            work->current_addr = -1;
            work->last_addr = -1;

            return control->rot.vy;
        }

        addr3 = HZD_Navigate(hzd, from, to, &control->mov);
        zone = &hzd->def->zones[addr3];

        if (work->chase_dis == 4000)
        {
            work->next_pos.vx = zone->x + 250;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z + 250;
        }
        else
        {
            work->next_pos.vx = zone->x;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z;
        }

        work->next_pos.vx = zone->x;
        work->next_pos.vy = zone->y;
        work->next_pos.vz = zone->z;

        work->next_addr = (addr3 & 0xff) | (addr3 & 0xff) << 8;
    }

    GV_SubVec3(&work->next_pos, &work->control.mov, &dir);

    pos = &dir;
    return GV_VecDir2(pos);
}

int s03d_800D307C(Work *work)
{
    if (work->count3 == 0)
    {
        s03d_800D0C90(work, 0);
        GM_SeSet(&work->control.mov, 0x53);
        NewEyeflash(&work->body.objs->objs[6].world, &work->control.mov, "kirari01", 0);
    }

    if (work->count3 < 20)
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;
}

int s03d_800D311C(Work *work)
{
    if (work->count3 == 0)
    {
        GM_SeSet(&work->control.mov, 0x53);
        s03d_800D0C90(work, 0);
    }
    if (work->count3 >= 21)
    {
        return 1;
    }
    work->count3++;
    return 0;
}

int s03d_800D3184(Work *work)
{
    if ((work->count3 % 32) == 0)
    {
        work->current_addr = -1;
        work->last_addr = -1;
        s03d_800D2DBC(work);
    }

    work->pad.dir = s03d_800D2DBC(work);
    if (work->pad.dir < 0)
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s03d_800D31F4(Work *work, int range)
{
    SVECTOR local;
    int dx = work->target_pos.vx - work->control.mov.vx;
    int dz;

    local.vx = dx;
    dz = work->target_pos.vz - work->control.mov.vz;
    local.vz = dz;
    if (-range < dx && dx < range && -range < dz && dz < range)
    {
        return 1;
    }
    work->pad.dir = GV_VecDir2(&local);
    work->count3++;
    return 0;
}

int s03d_800D327C(Work *work)
{
    s03d_800D2C20(work);
    if (work->control.map->index != work->target_map)
    {
        return -1;
    }
    if (work->count3 & 0x10)
    {
        work->current_addr = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);
        if (HZD_ReachTo(work->control.map->hzd, work->current_addr, work->target_addr) >= 2)
        {
            return -1;
        }
    }
    return s03d_800D31F4(work, 0x5DC);
}

int s03d_800D3310(Work *work)
{
    if (work->param.index == 2)
    {
        work->pad.press |= 0x20000;
    }
    else
    {
        work->pad.press |= 0x10000;
    }
    if (work->count3 < 4)
    {
        if ((work->count3 & 1) != 0)
        {
            work->pad.press |= 0x40000;
        }
    }
    else if (work->count3 >= 21)
    {
        return 1;
    }
    work->count3++;
    return 0;
}

int s03d_800D3390(Work *work)
{
    work->pad.press |= 0x20000;
    if (work->count3 == 0)
    {
        work->pad.press |= 0x80000;
    }
    else if (work->count3 == 8)
    {
        return 1;
    }
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s03d_800D33E8(Work *work)
{
    work->pad.press |= 0x10000;
    if (work->count3 == 30)
    {
        work->pad.press |= 0x100000;
        work->throw_pos = s03d_dword_800C3B68[work->param.index];
    }
    else if (work->body.is_end != 0)
    {
        return 1;
    }
    work->pad.dir = s03d_800D2D84(&work->control.mov, &s03d_dword_800C3B68[work->param.index]);
    work->count3++;
    return 0;
}

int s03d_800D34AC(Work *work)
{
    work->pad.press |= 0x10000;
    if (work->count3 == 0)
    {
        work->pad.press |= 0x200000;
    }
    else if (work->body.is_end != 0)
    {
        return 1;
    }
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s03d_800D3508(Work *work)
{
    work->pad.press |= 0x10000;
    if (work->count3 < 10)
    {
        if ((work->count3 & 1) == 0)
        {
            work->pad.press |= 0x40000;
        }
    }
    else if (work->count3 >= 20)
    {
        return 1;
    }
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s03d_800D3570(Work *work)
{
    if (work->param.index == 2)
    {
        work->pad.press |= 0x20000;
    }
    else
    {
        work->pad.press |= 0x10000;
    }
    work->pad.dir = work->sn_dir;
    if (ZakoGameFlag < 7)
    {
        if (ZakoGameFlag >= 4)
        {
            return 0;
        }
    }
    if (work->count3 == 0x10)
    {
        work->count3 += GV_RandU(0xE);
    }
    if (work->count3 >= 0x21)
    {
        if (work->chase_dis < 0xBB9 && (GM_PlayerStatus & 2))
        {
            return 9;
        }
        if (work->sn_dis < 0x3E8 && !(GM_PlayerStatus & 0x1060))
        {
            return 0xA;
        }
        return 6;
    }
    work->count3++;
    return 0;
}

void s03d_800D367C(Work *work)
{
    switch (ZakoGameFlag)
    {
    case 9:
        if (work->n_dead >= 0xF)
        {
            break;
        }
        /* fallthrough */
    case 8:
        if (work->count3 < 0x1F)
        {
            break;
        }
        /* fallthrough */
    case 0:
    case 4:
    case 5:
    case 7:
    case 12:
        s03d_800D2CCC(work);
        work->count3 = 0;
        return;
    case 10:
        s03d_800D2D44(work);
        work->count3 = 0;
        return;
    }
    work->count3++;
}

void s03d_800D3724(Work *work)
{
    if (work->think3 == 0)
    {
        s03d_800D367C(work);
    }
}

void s03d_800D3754(Work *work)
{
    switch (work->think3)
    {
    case 1:
        if (s03d_800D307C(work) != 0)
        {
            s03d_800D2CCC(work);
            if (ZakoCommand.alert_mode != 0)
            {
                work->pad.sound = 0xF6;
            }
            else
            {
                work->pad.sound = 0xF0;
            }
            work->alert_level = 0xFF;
        }
        break;
    case 2:
        if (s03d_800D311C(work) != 0)
        {
            work->think2 = 3;
            work->think3 = 0xD;
            work->pad.field_4 = 1;
            work->pad.sound = 0xF0;
            work->think1 = 0;
            work->count3 = 0;
            work->alert_level = 0xFF;
        }
        break;
    case 3:
        if (s03d_800D311C(work) != 0)
        {
            s03d_800D2CCC(work);
            work->pad.sound = 0xF0;
            work->alert_level = 0xFF;
        }
        break;
    }
}

void s03d_800D3848(Work *work)
{
    switch (work->think3)
    {
    case 6:
        if (s03d_800D3310(work) != 0)
        {
            work->think3 = 0xC;
            work->count3 = 0;
        }
        break;
    case 7:
        if (s03d_800D3390(work) != 0)
        {
            work->think3 = 0xC;
            work->count3 = 0;
        }
        break;
    case 9:
        if (s03d_800D33E8(work) != 0)
        {
            s03d_800D2D68(work);
            work->count3 = 0;
        }
        break;
    case 10:
        if (s03d_800D34AC(work) != 0)
        {
            work->think3 = 0xC;
            work->count3 = 0;
        }
        break;
    case 11:
        if (s03d_800D3508(work) != 0)
        {
            work->think3 = 0xC;
            work->count3 = 0;
        }
        break;
    case 12:
    {
        int r = s03d_800D3570(work);

        if (r != 0)
        {
            work->think3 = r;
            work->count3 = 0;
        }
        if (work->vision.pad != 2)
        {
            if (HZD_InsideZone(work->control.map->hzd, &work->control.mov, work->param.defends[work->param.c_root]) == 0)
            {
                s03d_800D2CCC(work);
            }
        }
        break;
    }
    }
    if (work->vision.pad == 2)
    {
        ZakoCom_800D4088();
        work->alert_level = 0xFF;
    }
}

void s03d_800D3984(Work *work)
{
    switch (work->think3)
    {
    case 4:
        s03d_800D2C20(work);
        if (s03d_800D3184(work) != 0)
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;
    case 5:
        {
            int r = s03d_800D327C(work);

            if (r < 0)
            {
                work->think3 = 4;
                work->count3 = 0;
            }
            else if (r > 0)
            {
                work->think2 = 2;
                work->think3 = 0xC;
                work->count3 = 0;
            }
        }
        break;
    }
    if (work->sn_dis < work->chase_dis)
    {
        if (work->chase_dis >= 0x1B58 || work->vision.pad == 2)
        {
            work->think2 = 2;
            work->think3 = 0xC;
            work->count3 = 0;
        }
    }
    if (work->vision.pad == 2)
    {
        work->alert_level = 0xFF;
    }
    ZakoCom_800D4088();
}

void s03d_800D3A7C(Work *work)
{
    if (work->think3 == 13)
    {
        if (s03d_800D3184(work))
        {
            work->think2 = 2;
            work->think3 = 12;
            work->count3 = 0;
        }
    }
}

void s03d_800D3ACC(Work *work)
{
    switch (work->think2)
    {
    case 0:
        s03d_800D3724(work);
        break;
    case 1:
        s03d_800D3984(work);
        break;
    case 2:
        s03d_800D3848(work);
        break;
    case 3:
        s03d_800D3A7C(work);
        break;
    case 4:
        s03d_800D3754(work);
        break;
    }
}

void s03d_800D3B5C(Work *work)
{
    work->pad.dir = -1;
    work->control.radar_atr = 5;
    work->pad.press = 0;
    work->alert_level = 0xFF;
    if (work->think1 == 0)
    {
        work->act.field_1C = 1;
        s03d_800D3ACC(work);
    }
}
