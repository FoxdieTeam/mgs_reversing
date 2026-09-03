#include "zako.h"

#include "common.h"
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

extern int s03d_dword_800DC2F8;
extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern SVECTOR s03d_dword_800DC308;
extern int s03d_dword_800DC32C;

void s03d_800D2C20(Work *work)
{
    work->field_B5C = s03d_dword_800DC2FC;
    work->field_B48 = s03d_dword_800DC308;
    work->field_B60 = s03d_dword_800DC300;
}

void s03d_800D2C68(Work *work)
{
    int      addr;
    int      index;
    HZD_HDL *hzd;
    HZD_ZON *zone;

    addr = work->param.defends[work->param.c_root];

    index = addr << 1;
    index = addr + index;

    hzd = work->control.map->hzd;
    zone = (HZD_ZON *)((char *)hzd->def->zones + index * 8);

    work->field_B5C = addr | (addr << 8);

    work->field_B48.vx = zone->x;
    work->field_B48.vy = zone->y;
    work->field_B48.vz = zone->z;
    work->field_B60 = work->field_B54;
}

void s03d_800D2CCC(Work *work)
{
    if (work->param.defends[work->param.c_root] == 0xFF)
    {
        work->field_ACA = 1;
        work->field_AC8 = 0;
        work->field_ACC = 4;
    }
    else
    {
        work->field_ACA = 3;
        work->field_AC8 = 0;
        work->field_ACC = 13;
        s03d_800D2C68(work);
    }

    work->field_AD0 = 0;
    work->field_ADC = 1;
}

void s03d_800D2D44(Work *work)
{
    work->field_ACA = 2;
    work->field_ACC = 9;
    work->field_AC8 = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
}

void s03d_800D2D68(Work *work)
{
    work->field_AC8 = 0;
    work->field_ACA = 0;
    work->field_ACC = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
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

    if (work->field_B60 == work->control.map->index)
    {
        pos = &work->field_B48;
        to = work->field_B5C;
    }
    else
    {
        pos = &work->field_B48;
        addr = s03d_800D414C(work->control.map->index, work->field_B60);
        to = (addr << 8) | addr;

        zone = &hzd->def->zones[addr];
        pos->vx = zone->x;
        pos->vy = zone->y;
        pos->vz = zone->z;
    }

    control = &work->control;

    from = work->field_B70 = HZD_GetAddress(hzd, &control->mov, work->field_B70);
    reach = HZD_ReachTo(hzd, from, work->field_B74);
    if (to != work->field_B58 || reach <= 0)
    {
        work->field_B58 = to;

        if (HZD_ReachTo(hzd, from, to) < 2)
        {
            if (work->field_B60 == work->control.map->index)
            {
                work->field_B80 = *pos;
                work->field_B74 = to;
                GV_SubVec3(&work->field_B80, &control->mov, &dir);
                work->field_AE6 = GV_VecDir2(&dir);
                return -1;
            }

            addr2 = s03d_800D414C(work->field_B60, control->map->index);
            control->map = GM_GetMap(work->field_B60);

            zone = &control->map->hzd->def->zones[addr2];
            control->mov.vx = zone->x;
            control->mov.vy = zone->y;
            control->mov.vz = zone->z;

            work->field_B70 = -1;
            work->field_B58 = -1;

            return control->rot.vy;
        }

        addr3 = HZD_Navigate(hzd, from, to, &control->mov);
        zone = &hzd->def->zones[addr3];

        if (work->field_B64 == 4000)
        {
            work->field_B80.vx = zone->x + 250;
            work->field_B80.vy = zone->y;
            work->field_B80.vz = zone->z + 250;
        }
        else
        {
            work->field_B80.vx = zone->x;
            work->field_B80.vy = zone->y;
            work->field_B80.vz = zone->z;
        }

        work->field_B80.vx = zone->x;
        work->field_B80.vy = zone->y;
        work->field_B80.vz = zone->z;

        work->field_B74 = (addr3 & 0xff) | (addr3 & 0xff) << 8;
    }

    GV_SubVec3(&work->field_B80, &work->control.mov, &dir);

    pos = &dir;
    return GV_VecDir2(pos);
}

int s03d_800D307C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        s03d_800D0C90(work, 0);
        GM_SeSet(&work->control.mov, 0x53);
        NewEyeflash(&work->body.objs->objs[6].world, &work->control.mov, "kirari01", 0);
    }

    if (work->field_AD0 < 20)
    {
        work->field_AD8 |= 0x20;
        work->field_AD0++;
        return 0;
    }

    return 1;
}

int s03d_800D311C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        GM_SeSet(&work->control.mov, 0x53);
        s03d_800D0C90(work, 0);
    }
    if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}

int s03d_800D3184(Work *work)
{
    if ((work->field_AD0 % 32) == 0)
    {
        work->field_B70 = -1;
        work->field_B58 = -1;
        s03d_800D2DBC(work);
    }

    work->field_AE6 = s03d_800D2DBC(work);
    if (work->field_AE6 < 0)
    {
        return 1;
    }

    work->field_AD0++;
    return 0;
}

int s03d_800D31F4(Work *work, int range)
{
    SVECTOR local;
    int dx = work->field_B48.vx - work->control.mov.vx;
    int dz;

    local.vx = dx;
    dz = work->field_B48.vz - work->control.mov.vz;
    local.vz = dz;
    if (-range < dx && dx < range && -range < dz && dz < range)
    {
        return 1;
    }
    work->field_AE6 = GV_VecDir2(&local);
    work->field_AD0++;
    return 0;
}

int s03d_800D327C(Work *work)
{
    s03d_800D2C20(work);
    if (work->control.map->index != work->field_B60)
    {
        return -1;
    }
    if (work->field_AD0 & 0x10)
    {
        work->field_B70 = HZD_GetAddress(work->control.map->hzd, &work->control.mov, -1);
        if (HZD_ReachTo(work->control.map->hzd, work->field_B70, work->field_B5C) >= 2)
        {
            return -1;
        }
    }
    return s03d_800D31F4(work, 0x5DC);
}

int s03d_800D3310(Work *work)
{
    if (work->param.fAF8 == 2)
    {
        work->field_AD8 |= 0x20000;
    }
    else
    {
        work->field_AD8 |= 0x10000;
    }
    if (work->field_AD0 < 4)
    {
        if ((work->field_AD0 & 1) != 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}

int s03d_800D3390(Work *work)
{
    work->field_AD8 |= 0x20000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x80000;
    }
    else if (work->field_AD0 == 8)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}

int s03d_800D33E8(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 30)
    {
        work->field_AD8 |= 0x100000;
        work->field_B68 = s03d_dword_800C3B68[work->param.fAF8];
    }
    else if (work->body.is_end != 0)
    {
        return 1;
    }
    work->field_AE6 = s03d_800D2D84(&work->control.mov, &s03d_dword_800C3B68[work->param.fAF8]);
    work->field_AD0++;
    return 0;
}

int s03d_800D34AC(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x200000;
    }
    else if (work->body.is_end != 0)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}

int s03d_800D3508(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 < 10)
    {
        if ((work->field_AD0 & 1) == 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 20)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}

int s03d_800D3570(Work *work)
{
    if (work->param.fAF8 == 2)
    {
        work->field_AD8 |= 0x20000;
    }
    else
    {
        work->field_AD8 |= 0x10000;
    }
    work->field_AE6 = work->field_B94;
    if (s03d_dword_800DC2F8 < 7)
    {
        if (s03d_dword_800DC2F8 >= 4)
        {
            return 0;
        }
    }
    if (work->field_AD0 == 0x10)
    {
        work->field_AD0 += GV_RandU(0xE);
    }
    if (work->field_AD0 >= 0x21)
    {
        if (work->field_B64 < 0xBB9 && (GM_PlayerStatus & 2))
        {
            return 9;
        }
        if (work->field_B90 < 0x3E8 && !(GM_PlayerStatus & 0x1060))
        {
            return 0xA;
        }
        return 6;
    }
    work->field_AD0++;
    return 0;
}

void s03d_800D367C(Work *work)
{
    switch (s03d_dword_800DC2F8)
    {
    case 9:
        if (work->field_B04 >= 0xF)
        {
            break;
        }
        /* fallthrough */
    case 8:
        if (work->field_AD0 < 0x1F)
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
        work->field_AD0 = 0;
        return;
    case 10:
        s03d_800D2D44(work);
        work->field_AD0 = 0;
        return;
    }
    work->field_AD0++;
}

void s03d_800D3724(Work *work)
{
    if (work->field_ACC == 0)
    {
        s03d_800D367C(work);
    }
}

void s03d_800D3754(Work *work)
{
    switch (work->field_ACC)
    {
    case 1:
        if (s03d_800D307C(work) != 0)
        {
            s03d_800D2CCC(work);
            if (s03d_dword_800DC32C != 0)
            {
                work->field_AE8 = 0xF6;
            }
            else
            {
                work->field_AE8 = 0xF0;
            }
            work->field_B28 = 0xFF;
        }
        break;
    case 2:
        if (s03d_800D311C(work) != 0)
        {
            work->field_ACA = 3;
            work->field_ACC = 0xD;
            work->field_ADC = 1;
            work->field_AE8 = 0xF0;
            work->field_AC8 = 0;
            work->field_AD0 = 0;
            work->field_B28 = 0xFF;
        }
        break;
    case 3:
        if (s03d_800D311C(work) != 0)
        {
            s03d_800D2CCC(work);
            work->field_AE8 = 0xF0;
            work->field_B28 = 0xFF;
        }
        break;
    }
}

void s03d_800D3848(Work *work)
{
    switch (work->field_ACC)
    {
    case 6:
        if (s03d_800D3310(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 7:
        if (s03d_800D3390(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 9:
        if (s03d_800D33E8(work) != 0)
        {
            s03d_800D2D68(work);
            work->field_AD0 = 0;
        }
        break;
    case 10:
        if (s03d_800D34AC(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 11:
        if (s03d_800D3508(work) != 0)
        {
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
        break;
    case 12:
    {
        int r = s03d_800D3570(work);

        if (r != 0)
        {
            work->field_ACC = r;
            work->field_AD0 = 0;
        }
        if (work->field_B26 != 2)
        {
            if (HZD_InsideZone(work->control.map->hzd, &work->control.mov, work->param.defends[work->param.c_root]) == 0)
            {
                s03d_800D2CCC(work);
            }
        }
        break;
    }
    }
    if (work->field_B26 == 2)
    {
        ZakoCom_800D4088();
        work->field_B28 = 0xFF;
    }
}

void s03d_800D3984(Work *work)
{
    switch (work->field_ACC)
    {
    case 4:
        s03d_800D2C20(work);
        if (s03d_800D3184(work) != 0)
        {
            work->field_ACC = 5;
            work->field_AD0 = 0;
        }
        break;
    case 5:
        {
            int r = s03d_800D327C(work);

            if (r < 0)
            {
                work->field_ACC = 4;
                work->field_AD0 = 0;
            }
            else if (r > 0)
            {
                work->field_ACA = 2;
                work->field_ACC = 0xC;
                work->field_AD0 = 0;
            }
        }
        break;
    }
    if (work->field_B90 < work->field_B64)
    {
        if (work->field_B64 >= 0x1B58 || work->field_B26 == 2)
        {
            work->field_ACA = 2;
            work->field_ACC = 0xC;
            work->field_AD0 = 0;
        }
    }
    if (work->field_B26 == 2)
    {
        work->field_B28 = 0xFF;
    }
    ZakoCom_800D4088();
}

void s03d_800D3A7C(Work *work)
{
    if (work->field_ACC == 13)
    {
        if (s03d_800D3184(work))
        {
            work->field_ACA = 2;
            work->field_ACC = 12;
            work->field_AD0 = 0;
        }
    }
}

void s03d_800D3ACC(Work *work)
{
    switch (work->field_ACA)
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
    work->field_AE6 = -1;
    work->control.radar_atr = 5;
    work->field_AD8 = 0;
    work->field_B28 = 0xFF;
    if (work->field_AC8 == 0)
    {
        work->field_8E4 = 1;
        s03d_800D3ACC(work);
    }
}
