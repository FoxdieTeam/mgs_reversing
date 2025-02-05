#include <stdio.h>

#include "meryl72.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"

extern unsigned short GM_WeaponTypes[];
extern unsigned short GM_ItemTypes[];

int SECTION("overlay.bss") meryl72_800D5300;
int SECTION("overlay.bss") meryl72_800D5304;

extern SVECTOR meryl72_800D52F8;

#define TH1_PHASE0 0
#define TH1_PHASE1 1
#define TH1_PHASE2 2

void s07c_meryl72_unk2_800CEBBC(Meryl72Work *work)
{
    work->target_addr = work->player_addr;
    work->target_pos  = work->player_pos;
    work->target_map  = work->player_map;
}

void s07c_meryl72_unk2_800CEBF4(Meryl72Work *work)
{
    work->target_pos = work->nodes[work->next_node];
    work->target_addr = HZD_GetAddress(work->control.map->hzd, &work->target_pos, -1);
    work->target_map = work->start_map;
}

int s07c_meryl72_unk2_800CEC64(SVECTOR *vec)
{
    if (vec->vz > 1000 || vec->vx < 6000)
    {
        return 0;
    }

    if (vec->vz > -1000 && vec->vx < 8500)
    {
        return 0;
    }

    return 1;
}

int s07c_meryl72_unk2_800CECB4(SVECTOR *vec)
{
    if (vec->vz > -5000 || vec->vx < 6000)
    {
        return 0;
    }

    return 1;
}

void s07c_meryl72_unk2_800CECEC(Meryl72Work *work, int index)
{
    int proc_id;

    proc_id = work->fC1C[index];
    if (proc_id >= 0)
    {
        GCL_ExecProc(proc_id, NULL);
    }
}

int s07c_meryl72_unk2_800CED24(Meryl72Work *work)
{
    SVECTOR  diff;
    SVECTOR *mov;
    HZD_HDL *hzd;
    int      to_addr, from_addr;
    int      reach;
    int      link;
    HZD_ZON *zone;

    mov = &work->control.mov;
    hzd = work->control.map->hzd;

    to_addr = work->target_addr;
    from_addr = HZD_GetAddress(hzd, mov, work->fB5C);

    work->fB5C = from_addr;
    reach = HZD_ReachTo(hzd, from_addr, work->fB60);

    if (to_addr != work->fB4C || reach <= 0)
    {
        work->fB4C = to_addr;

        if (HZD_ReachTo(hzd, from_addr, to_addr) < 2)
        {
            work->fB6C = work->target_pos;
            work->fB60 = to_addr;
            GV_SubVec3(&work->fB6C, mov, &diff);
            work->pad.dir = GV_VecDir2(&diff);
            return -1;
        }

        link = HZD_LinkRoute(hzd, from_addr, to_addr, mov);
        zone = &hzd->header->zones[link];

        work->fB6C.vx = zone->x;
        work->fB6C.vy = zone->y;
        work->fB6C.vz = zone->z;

        work->fB60 = (link & 0xff) | ((link & 0xff) << 8);
    }

    GV_SubVec3(&work->fB6C, &work->control.mov, &diff);
    return GV_VecDir2(&diff);
}

int s07c_meryl72_unk2_800CEE88(Meryl72Work *work)
{
    if ((work->count3 % 32) == 0)
    {
        work->fB5C = -1;
        work->fB4C = -1;
        s07c_meryl72_unk2_800CED24(work);
    }

    work->pad.dir = s07c_meryl72_unk2_800CED24(work);
    return work->pad.dir < 0;
}

int s07c_meryl72_unk2_800CEEDC(Meryl72Work *work, int range)
{
    SVECTOR diff;
    int     dx, dz;

    diff.vx = dx = work->target_pos.vx - work->control.mov.vx;
    diff.vz = dz = work->target_pos.vz - work->control.mov.vz;

    if (dx > -range && dx < range && dz > -range && dz < range)
    {
        return 1;
    }

    work->pad.dir = GV_VecDir2(&diff);
    return 0;
}

void s07c_meryl72_unk2_800CEF58(Meryl72Work *work)
{
    if (work->stage == 1)
    {
        work->think3 = 4;
        work->fC04 = 0;
    }
    else
    {
        work->think1 = 2;
        work->think2 = 2;
        work->think3 = 4;
        work->fC04 = 5400;
    }

    work->count3 = 0;
}

void s07c_meryl72_unk2_800CEF98(Meryl72Work *work)
{
    CONTROL *control;
    int      dir;

    control = &work->control;

    if (work->fC38 > 900)
    {
        work->think3 = 4;
        work->fC38 = 0;
        work->count3 = 0;
    }
    else if (!HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[0]))
    {
        s07c_meryl72_unk2_800CEBF4(work);
        work->think3 = 2;
        work->count3 = 0;
    }
    else if (GM_StreamStatus() == -1 && work->act_status & 0x1)
    {
        dir = work->sn_dir + 2048;
        GM_PlayerControl->turn.vy = dir & 0xFFF;

        work->think3 = 4;
        work->fC38 = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CF060(Meryl72Work* work)
{
    if (work->count3 == 0 && GM_StreamStatus() != -1)
    {
        GM_StreamPlayStop();
    }

    if (work->fC08 == 2)
    {
        work->think3 = 2;
        work->count3 = 0;
        GM_GameStatus |= STATE_PADRELEASE;
        work->pad.dir = work->sn_dir;
    }
    else if (work->count3 > 6000 && work->act_status & 0x1)
    {
        s07c_meryl72_unk2_800CEBF4(work);
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CF144(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think3 = 6;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
        return;
    }

    if (work->count3 == 0)
    {
        if (GM_PlayerStatus & (PLAYER_GROUND | PLAYER_SQUAT))
        {
            work->pad.press |= 0x800000;
        }
        else if (GM_PlayerStatus & PLAYER_CB_BOX)
        {
            work->pad.press |= 0x1000000;

            if (GM_StreamStatus() == -1)
            {
                GM_VoxStream(work->voices[12], 0);
            }
        }
        else
        {
            work->pad.press |= 0x400000;
        }

        work->fC0E -= 2;
        if (work->fC0E < 0)
        {
            work->fC0E = 0;
        }

        printf(" binta dis=%d\n", work->sn_dis);
    }

    if (work->count3 > 30 && !(work->act_status & 0x8))
    {
        work->think3 = 9;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else if (work->fC08 == 3)
    {
        work->think3 = 9;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CF2A4(Meryl72Work *work)
{
    if (work->fC08 == 1)
    {
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->count3 == 0)
    {
        meryl72_800D5300 = 1;
    }

    if (work->count3 == 2 && meryl72_800D5300 & 0x2)
    {
        meryl72_800D5300 &= ~0x2;
        work->think3 = 7;
        work->count3 = 0;
        return;
    }

    if (work->count3 == 4)
    {
        work->pad.press |= 0x4000;
        work->fC0E -= 2;
        if (work->fC0E < 0)
        {
            work->fC0E = 0;
        }
    }

    if (work->count3 >= 5 && (work->count3 > 1500 || !(meryl72_800D5300 & 0x1)))
    {
        work->think3 = 9;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
        return;
    }

    work->count3++;
}

void s07c_meryl72_unk2_800CF3AC(Meryl72Work *work)
{
    int tick;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if (work->fC08 == 1)
    {
        work->think3 = 6;
        work->count3 = 0;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
        }
    }
    else
    {
        if (work->count3 == 0 && GM_StreamStatus() == -1)
        {
            tick = GV_Time % 2;
            GM_VoxStream(work->voices[13 + tick], 0);
        }

        if (work->count3 > 30)
        {
            if (GM_StreamStatus() == -1)
            {
                s07c_meryl72_unk2_800CEBF4(work);
                work->think2 = 2;
                work->think3 = 4;
                work->count3 = 0;
            }
        }
        else
        {
            work->count3++;
        }
    }
}

void s07c_meryl72_unk2_800CF4C0(Meryl72Work *work)
{
    CONTROL *control;

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition))
    {
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x20000000;
    }

    work->pad.dir = work->sn_dir;

    if ((work->count3 % 32) == 0)
    {
        control = &work->control;

        if (!HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[0]))
        {
            s07c_meryl72_unk2_800CEBF4(work);
            work->think3 = 2;
            work->count3 = 0;
        }
    }

    work->count3++;
}

void s07c_meryl72_unk2_800CF568(Meryl72Work* work)
{
    if (work->count3 == 0)
    {
        work->pad.dir = work->sn_dir;
        GM_VoxStream(work->voices[0], 0x40000000);
    }

    if (work->count3 < 150)
    {
        work->pad.press |= 0x2000000;
    }

    if (work->count3 == 160)
    {
        GM_StreamPlayStart();
        work->fC10[0] = 1800;
        work->pad.press |= 0x40000000;
    }

    if (work->count3 > 180 && GM_StreamStatus() == -1)
    {
        work->think1 = 2;
        work->think2 = 2;
        work->think3 = 4;
        work->count3 = 0;
        work->fC04 = 0;

        GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY | GAME_FLAG_BIT_07);
        s07c_meryl72_unk2_800CECEC(work, 1);
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CF67C(Meryl72Work *work)
{
    work->fC0A = 0;

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition) && work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;

        if (GM_StreamStatus() != -1)
        {
            GM_StreamPlayStop();
        }

        return;
    }

    if (work->count3 == 0)
    {
        if (GM_StreamStatus() == -1)
        {
            if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
            {
                GM_VoxStream(work->voices[work->fC0C + 7], 0);
            }

            if (++work->fC0E > 14)
            {
                work->fC0E = 14;
            }

            if (++work->fC0C > 4)
            {
                work->fC0C = 0;
            }
        }
        else
        {
            work->think3 = 4;
            work->count3 = 0;
            return;
        }
    }

    if (work->count3 > 60 && GM_StreamStatus() == -1)
    {
        work->think3 = 4;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x10000;
        work->pad.dir = work->sn_dir;
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CF824(Meryl72Work *work)
{
    CONTROL *control;

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition))
    {
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x20000000;
        work->fC04++;
    }

    work->pad.dir = work->sn_dir;

    if (GM_StreamStatus() != -1)
    {
        work->count3 = 0;
    }

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition) && work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
        return;
    }

    if (work->fC04 > 5400)
    {
        if (s07c_meryl72_unk2_800CECB4(&GM_PlayerPosition))
        {
            if (GM_StreamStatus() == -1 && GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
            {
                GM_VoxStream(work->voices[18], 0);
            }

            work->fC04 = 0;
        }
    }
    else if (work->count3 > 60 && work->fC0A > 150)
    {
        work->think3 = 5;
        work->count3 = 0;
        work->pad.press |= 0x10000;
        return;
    }

    control = &work->control;

    if ((work->count3 & 0x1F) == 0 && !HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[0]))
    {
        s07c_meryl72_unk2_800CEBF4(work);
        work->think3 = 2;
        work->count3 = 0;
    }

    work->count3++;
}

void s07c_meryl72_unk2_800CF9E0(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFA28(Meryl72Work *work)
{
    if (work->fC38 > 900)
    {
        work->think3 = 4;
        work->fC38 = 0;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFA98(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition) && work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFB14(Meryl72Work *work)
{
    s07c_meryl72_unk2_800CEBBC(work);

    if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->think3 = 3;
        work->count3 = 0;
    }
    else if (!s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition))
    {
        work->think3 = 9;
        work->count3 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else if (work->sn_dis < 1000)
    {
        work->think3 = 8;
        work->count3 = 0;
    }
    else if (work->count3 > 300)
    {
        work->think3 = 8;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFBBC(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition) && work->fC08 == 1)
    {
        work->think2 = 3;
        work->think3 = 6;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->think2 = 2;
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFC54(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->think3 = 4;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFCA4(Meryl72Work *work)
{
    if (work->fC38 > 900)
    {
        work->think3 = 4;
        work->fC38 = 0;
        work->count3 = 0;
    }
    else if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->think3 = 4;
        work->fC38 = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFD0C(Meryl72Work *work)
{
    s07c_meryl72_unk2_800CEBBC(work);

    if (s07c_meryl72_unk2_800CEEDC(work, 1000) > 0 || work->count3 > 300)
    {
        printf(" stop dis=%d\n", work->sn_dis);

        work->think3 = 8;
        work->pad.mode = 0;
        work->count3 = 0;
    }
    else
    {
        work->count3++;
    }
}

void s07c_meryl72_unk2_800CFD80(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 0:
        s07c_meryl72_unk2_800CEF58(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF4C0(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CF9E0(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFC54(work);
        break;
    }

    if (s07c_meryl72_unk2_800CECB4(&GM_PlayerPosition))
    {
        work->think1 = 1;
        work->think2 = 0;
        work->think3 = 0;

        // Unequip item if it changes camera
        if (GM_ItemTypes[GM_CurrentItemId + 1] & 0x2)
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        // Unequip weapon if it changes camera
        if (GM_WeaponTypes[GM_CurrentWeaponId + 1] & 0x200)
        {
            GM_CurrentWeaponId = WEAPON_NONE;
        }

        work->fC38 = 0;
        work->count3 = 0;
        work->fC04 = 0;

        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY | GAME_FLAG_BIT_07;
        s07c_meryl72_unk2_800CECEC(work, 0);
    }
}

void s07c_meryl72_unk2_800CFED0(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 0:
        s07c_meryl72_unk2_800CEF98(work);
        break;

    case 2:
        s07c_meryl72_unk2_800CFA28(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFCA4(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF568(work);
        break;
    }
}

void s07c_meryl72_unk2_800CFF64(Meryl72Work *work)
{
    switch (work->think3)
    {
        case 6:
            s07c_meryl72_unk2_800CF060(work);
            break;

        case 2:
            s07c_meryl72_unk2_800CFB14(work);
            break;

        case 3:
            s07c_meryl72_unk2_800CFD0C(work);
            break;

        case 7:
            s07c_meryl72_unk2_800CF144(work);
            break;

        case 8:
            s07c_meryl72_unk2_800CF2A4(work);
            break;

        case 9:
            s07c_meryl72_unk2_800CF3AC(work);
            break;
    }
}

void s07c_meryl72_unk2_800D0010(Meryl72Work *work)
{
    switch (work->think3)
    {
    case 2:
        s07c_meryl72_unk2_800CFA98(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFBBC(work);
        break;

    case 4:
        s07c_meryl72_unk2_800CF824(work);
        break;

    case 5:
        s07c_meryl72_unk2_800CF67C(work);
        break;
    }
}

void Think1_Phase0_800D00A4(Meryl72Work *work)
{
    if (work->think2 == 0)
    {
        s07c_meryl72_unk2_800CFD80(work);
    }
}

void Think1_Phase1_800D00D4(Meryl72Work *work)
{
    if (work->think2 == 0)
    {
        s07c_meryl72_unk2_800CFED0(work);
    }
}

void Think1_Phase2_800D0104(Meryl72Work *work)
{
    switch (work->think2)
    {
    case 2:
        s07c_meryl72_unk2_800D0010(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFF64(work);
        break;
    }
}

void Meryl9Think_800D0154(Meryl72Work *work)
{
    int i;

    work->pad.dir = -1;
    work->pad.press = 0;

    switch (work->think1)
    {
    case TH1_PHASE0:
        Think1_Phase0_800D00A4(work);
        break;

    case TH1_PHASE1:
        Think1_Phase1_800D00D4(work);
        break;

    case TH1_PHASE2:
        Think1_Phase2_800D0104(work);
        break;
    }

    for (i = 0; i < 3; i++)
    {
        if (--work->fC10[i] < 0)
        {
            work->fC10[i] = 0;
        }
    }

    work->fC38++;
}

void s07c_meryl72_unk2_800D0220(void)
{
    meryl72_800D52F8 = DG_ZeroVector;
    meryl72_800D5300 = 0;
}

void s07c_meryl72_unk2_800D025C(void)
{
}
