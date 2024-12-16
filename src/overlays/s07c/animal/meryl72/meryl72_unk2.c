#include <stdio.h>

#include "meryl72.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"

extern SVECTOR DG_ZeroVector;
extern int     GM_GameStatus;
extern int     GM_GameOverTimer;

extern unsigned short GM_WeaponTypes_8009D580[];
extern unsigned short GM_ItemTypes_8009D598[];
extern SVECTOR        GM_PlayerPosition_800ABA10;

extern SVECTOR meryl72_800D52F8;
extern int     meryl72_800D5300;

void s07c_meryl72_unk2_800CEBBC(Meryl72Work *work)
{
    work->target_addr = work->fB84;
    work->target_pos = work->fB88;
    work->target_map = work->fB90;
}

void s07c_meryl72_unk2_800CEBF4(Meryl72Work *work)
{
    work->target_pos = work->nodes[work->fAC8];
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

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEE88.s")
int s07c_meryl72_unk2_800CEE88(Meryl72Work *);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEEDC.s")
int s07c_meryl72_unk2_800CEEDC(Meryl72Work *, int);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEF58.s")
void s07c_meryl72_unk2_800CEF58(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CEF98.s")
void s07c_meryl72_unk2_800CEF98(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF060.s")
void s07c_meryl72_unk2_800CF060(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF144.s")
void s07c_meryl72_unk2_800CF144(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF2A4.s")
void s07c_meryl72_unk2_800CF2A4(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF3AC.s")
void s07c_meryl72_unk2_800CF3AC(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF4C0.s")
void s07c_meryl72_unk2_800CF4C0(Meryl72Work *work);

#pragma INCLUDE_ASM("asm/overlays/s07c/s07c_meryl72_unk2_800CF568.s")
void s07c_meryl72_unk2_800CF568(Meryl72Work *work);

void s07c_meryl72_unk2_800CF67C(Meryl72Work *work)
{
    work->fC0A = 0;

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10) && work->fC08 == 1)
    {
        work->fABE = 3;
        work->fAC0 = 6;
        work->fAC4 = 0;

        if (GM_StreamStatus_80037CD8() != -1)
        {
            GM_StreamPlayStop_80037D64();
        }
    }
    else
    {
        if (work->fAC4 == 0)
        {
            if (GM_StreamStatus_80037CD8() == -1)
            {
                if (GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream_80037E40(work->voices[work->fC0C + 7], 0);
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
                work->fAC0 = 4;
                work->fAC4 = 0;
                return;
            }
        }

        if (work->fAC4 > 60 && GM_StreamStatus_80037CD8() == -1)
        {
            work->fAC0 = 4;
            work->fAC4 = 0;
            work->pad.press |= 0x10000;
        }
        else
        {
            work->pad.press |= 0x10000;
            work->pad.dir = work->sn_dir;
            work->fAC4++;
        }
    }
}

void s07c_meryl72_unk2_800CF824(Meryl72Work *work)
{
    CONTROL *control;

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10))
    {
        work->pad.press |= 0x10000;
    }
    else
    {
        work->pad.press |= 0x20000000;
        work->fC04++;
    }

    work->pad.dir = work->sn_dir;

    if (GM_StreamStatus_80037CD8() != -1)
    {
        work->fAC4 = 0;
    }

    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10) && work->fC08 == 1)
    {
        work->fABE = 3;
        work->fAC0 = 6;
        work->fAC4 = 0;
    }
    else
    {
        if (work->fC04 > 5400)
        {
            if (s07c_meryl72_unk2_800CECB4(&GM_PlayerPosition_800ABA10))
            {
                if (GM_StreamStatus_80037CD8() == -1 && GM_GameOverTimer == 0 && GM_SnakeCurrentHealth > 0)
                {
                    GM_VoxStream_80037E40(work->voices[18], 0);
                }

                work->fC04 = 0;
            }
        }
        else if (work->fAC4 > 60 && work->fC0A > 150)
        {
            work->fAC0 = 5;
            work->fAC4 = 0;
            work->pad.press |= 0x10000;
            return;
        }

        control = &work->control;

        if ((work->fAC4 & 0x1F) == 0 && !HZD_8005D134(control->map->hzd, &control->mov, work->param.defends[0]))
        {
            s07c_meryl72_unk2_800CEBF4(work);
            work->fAC0 = 2;
            work->fAC4 = 0;
        }

        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CF9E0(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->fAC0 = 3;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFA28(Meryl72Work *work)
{
    if (work->fC38 > 900)
    {
        work->fAC0 = 4;
        work->fC38 = 0;
        work->fAC4 = 0;
    }
    else if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->fAC0 = 3;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFA98(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10) && work->fC08 == 1)
    {
        work->fABE = 3;
        work->fAC0 = 6;
        work->fAC4 = 0;
    }
    else if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->fAC0 = 3;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFB14(Meryl72Work *work)
{
    s07c_meryl72_unk2_800CEBBC(work);

    if (s07c_meryl72_unk2_800CEE88(work))
    {
        work->fAC0 = 3;
        work->fAC4 = 0;
    }
    else if (!s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10))
    {
        work->fAC0 = 9;
        work->fAC4 = 0;
        GM_GameStatus &= ~STATE_PADRELEASE;
    }
    else if (work->sn_dis < 1000)
    {
        work->fAC0 = 8;
        work->fAC4 = 0;
    }
    else if (work->fAC4 > 300)
    {
        work->fAC0 = 8;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFBBC(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEC64(&GM_PlayerPosition_800ABA10) && work->fC08 == 1)
    {
        work->fABE = 3;
        work->fAC0 = 6;
        work->fAC4 = 0;
    }
    else if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->fABE = 2;
        work->fAC0 = 4;
        work->pad.mode = 0;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFC54(Meryl72Work *work)
{
    if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->fAC0 = 4;
        work->pad.mode = 0;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFCA4(Meryl72Work *work)
{
    if (work->fC38 > 900)
    {
        work->fAC0 = 4;
        work->fC38 = 0;
        work->fAC4 = 0;
    }
    else if (s07c_meryl72_unk2_800CEEDC(work, 300) > 0)
    {
        work->fAC0 = 4;
        work->fC38 = 0;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFD0C(Meryl72Work *work)
{
    s07c_meryl72_unk2_800CEBBC(work);

    if (s07c_meryl72_unk2_800CEEDC(work, 1000) > 0 || work->fAC4 > 300)
    {
        printf(" stop dis=%d\n", work->sn_dis);

        work->fAC0 = 8;
        work->pad.mode = 0;
        work->fAC4 = 0;
    }
    else
    {
        work->fAC4++;
    }
}

void s07c_meryl72_unk2_800CFD80(Meryl72Work *work)
{
    switch (work->fAC0)
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

    if (s07c_meryl72_unk2_800CECB4(&GM_PlayerPosition_800ABA10))
    {
        work->fABC = 1;
        work->fABE = 0;
        work->fAC0 = 0;

        // Unequip item if it changes camera
        if (GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 0x2)
        {
            GM_CurrentItemId = ITEM_NONE;
        }

        // Unequip weapon if it changes camera
        if (GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200)
        {
            GM_CurrentWeaponId = WEAPON_NONE;
        }

        work->fC38 = 0;
        work->fAC4 = 0;
        work->fC04 = 0;

        GM_GameStatus |= STATE_PADRELEASE | STATE_PAUSE_ONLY | GAME_FLAG_BIT_07;
        s07c_meryl72_unk2_800CECEC(work, 0);
    }
}

void s07c_meryl72_unk2_800CFED0(Meryl72Work *work)
{
    switch (work->fAC0)
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
    switch (work->fAC0)
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
    switch (work->fAC0)
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

void s07c_meryl72_unk2_800D00A4(Meryl72Work *work)
{
    if (work->fABE == 0)
    {
        s07c_meryl72_unk2_800CFD80(work);
    }
}

void s07c_meryl72_unk2_800D00D4(Meryl72Work *work)
{
    if (work->fABE == 0)
    {
        s07c_meryl72_unk2_800CFED0(work);
    }
}

void s07c_meryl72_unk2_800D0104(Meryl72Work *work)
{
    switch (work->fABE)
    {
    case 2:
        s07c_meryl72_unk2_800D0010(work);
        break;

    case 3:
        s07c_meryl72_unk2_800CFF64(work);
        break;
    }
}

void s07c_meryl72_unk2_800D0154(Meryl72Work *work)
{
    int i;

    work->pad.dir = -1;
    work->pad.press = 0;

    switch (work->fABC)
    {
    case 0:
        s07c_meryl72_unk2_800D00A4(work);
        break;

    case 1:
        s07c_meryl72_unk2_800D00D4(work);
        break;

    case 2:
        s07c_meryl72_unk2_800D0104(work);
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
