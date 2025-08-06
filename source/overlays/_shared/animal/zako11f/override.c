#include "../../../_shared/enemy/enemy.h"
#include "linkvar.h"

extern SVECTOR s11i_dword_800C34C4[3];
extern int     s11i_dword_800C34DC[3][16];
extern int     s11i_dword_800C359C[3][16];
extern int     ZAKO11F_EYE_LENGTH_800C3694;
extern SVECTOR ZAKOCOM_PlayerPosition_800D5AF0;
extern int     ZAKO11F_GameFlag_800D5C4C;
extern int     ZAKOCOM_PlayerAddress_800D5C50;
extern int     ZAKOCOM_PlayerMap_800D5C54;

void ZAKO11F_PutMark_800CD224( Zako11FWork *work, int mark );

void s11i_zk11fcom_800D0C70( void );
int  s11i_zk11fcom_800D0D34( int map_id, int val );
int  s11i_zk11fcom_800D0DA8( void );

void s11i_zk11fcom_800CF9E4( Zako11FWork *work )
{
    work->target_addr = ZAKOCOM_PlayerAddress_800D5C50;
    work->target_pos  = ZAKOCOM_PlayerPosition_800D5AF0;
    work->target_map  = ZAKOCOM_PlayerMap_800D5C54;
}

void s11i_zk11fcom_800CFA2C( Zako11FWork *work )
{
    int      addr;
    int      index;
    HZD_ZON *zone;

    addr = work->param.field_B7C;

    index = addr << 1;
    index = index + addr;
    zone = (HZD_ZON *)((char *)work->control.map->hzd->header->zones + index * 8);

    work->target_addr = addr | addr << 8;

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

void s11i_zk11fcom_800CFA88( Zako11FWork *work )
{
    if ( work->param.field_B7C == 0xFF )
    {
        work->think2 = 1;
        work->think1 = 0;
        work->think3 = 4;
    }
    else
    {
        work->think2 = 3;
        work->think1 = 0;
        work->think3 = 16;
        s11i_zk11fcom_800CFA2C( work );
    }

    work->count3 = 0;
    work->pad.mode = TOP_COMM_ALERT;
}

void s11i_zk11fcom_800CFAF4( Zako11FWork *work )
{
    work->think1 = 0;
    work->think2 = 4;
    work->think3 = 1;
    work->count3 = 0;
}

void s11i_zk11fcom_800CFB10( Zako11FWork *work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->pad.mode = TOP_COMM_ALERT;
}

int s11i_zk11fcom_800CFB2C( SVECTOR *from, SVECTOR *to )
{
    SVECTOR diff;

    GV_SubVec3(to, from, &diff);
    diff.vy = 0;

    return GV_VecDir2(&diff);
}

int s11i_zk11fcom_800CFB64( Zako11FWork *work )
{
    SVECTOR  svec;
    HZD_HDL *hzd;
    SVECTOR *target_pos;
    int      addr, addr2, addr3;
    int      route;
    HZD_ZON *zone;
    CONTROL *control;
    int      reach;

    hzd = work->control.map->hzd;

    if ( work->target_map == work->control.map->index )
    {
        target_pos = &work->target_pos;
        addr = work->target_addr;
    }
    else
    {
        target_pos = &work->target_pos;
        route = s11i_zk11fcom_800D0D34( work->control.map->index , work->target_map );

        zone = &hzd->header->zones[ route ];
        target_pos->vx = zone->x;
        target_pos->vy = zone->y;
        target_pos->vz = zone->z;

        addr = (route << 8) | route;
    }

    control = &work->control;

    work->field_C0C = HZD_GetAddress( hzd, &control->mov, work->field_C0C );

    addr2 = work->field_C0C;
    reach = HZD_ReachTo( hzd, addr2, work->field_C10 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;

        if ( HZD_ReachTo( hzd, addr2, addr ) < 2 )
        {
                if ( work->target_map == work->control.map->index )
                {
                        work->field_C1C = *target_pos;
                        work->field_C10 = addr;

                        GV_SubVec3( &work->field_C1C, &control->mov, &svec );

                        work->pad.dir = GV_VecDir2( &svec );
                        return -1;
                }

                addr2 = s11i_zk11fcom_800D0D34( work->target_map, control->map->index );
                control->map = GM_GetMap( work->target_map );
                zone = &control->map->hzd->header->zones[ addr2 ];
                work->control.mov.vx = zone->x;
                control->mov.vy = zone->y;
                control->mov.vz = zone->z;
                work->field_C0C = -1;
                work->field_BF0 = -1;
                return control->rot.vy;
        }

        addr3 = HZD_LinkRoute( hzd, addr2, addr, &control->mov );
        zone = &hzd->header->zones[ addr3 ];
        if ( work->field_BFC == 0xFA0 )
        {
            work->field_C1C.vx = zone->x + 0xFA;
            work->field_C1C.vy = zone->y;
            work->field_C1C.vz = zone->z + 0xFA;
        } else
        {
            work->field_C1C.vx = zone->x;
            work->field_C1C.vy = zone->y;
            work->field_C1C.vz = zone->z;
        }

        work->field_C1C.vx = zone->x;
        work->field_C1C.vy = zone->y;
        work->field_C1C.vz = zone->z;

        work->field_C10 = (addr3 & 0xFF) | (addr3 & 0xFF) << 8;
    }

    GV_SubVec3( &work->field_C1C, &work->control.mov, &svec );
    target_pos = &svec;
    return GV_VecDir2( target_pos );
}

int s11i_zk11fcom_800CFE24( Zako11FWork *work )
{
    if ( work->count3 == 0 && !( work->act_status & 0x8 ) )
    {
        ZAKO11F_PutMark_800CD224( work, 0 );
    }

    if ( work->count3 < 20 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;
}

int s11i_zk11fcom_800CFEA4( Zako11FWork *work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        ZAKO11F_PutMark_800CD224( work, 0 );
    }

    if ( work->count3 > 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s11i_zk11fcom_800CFF0C( Zako11FWork *work )
{
    if ((work->count3 % 32) == 0)
    {
        work->field_C0C = -1;
        work->field_BF0 = -1;
        s11i_zk11fcom_800CFB64(work);
    }

    work->pad.dir = s11i_zk11fcom_800CFB64(work);
    if (work->pad.dir < 0)
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int DirectTrace_800CFF7C( Zako11FWork *work, int range )
{
    SVECTOR dist;
    int     x, z;

    dist.vx = x = work->target_pos.vx - work->control.mov.vx;
    dist.vz = z = work->target_pos.vz - work->control.mov.vz;

    if ( x <= -range || x >= range || z <= -range || z >= range )
    {
        work->pad.dir = GV_VecDir2( &dist );
        work->count3++;
        return 0;
    }

    return 1;
}

int s11i_zk11fcom_800D0004( Zako11FWork *work )
{
    MAP *map;

    s11i_zk11fcom_800CF9E4( work );

    map = work->control.map;

    if ( map->index != work->target_map )
    {
        return -1;
    }

    if ( work->count3 & 0x10 )
    {
        work->field_C0C = HZD_GetAddress( map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->field_C0C, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return DirectTrace_800CFF7C( work, 1500 );
}

int s11i_zk11fcom_800D0098( Zako11FWork *work )
{
    work->pad.dir = work->sn_dir;
    work->pad.press |= 0x10000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x40000;
    }
    else if ( work->count3 == 4 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D00EC( Zako11FWork *work )
{
    work->pad.press |= 0x20000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x80000;
    }

    if ( work->count3 > 80 )
    {
        return 1;
    }

    work->pad.dir = 0xA00;
    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D0148( Zako11FWork *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 30 )
    {
        work->pad.press |= 0x100000;
        work->field_C04 = s11i_dword_800C34C4[ work->param.index ];
    }
    else if ( work->body.is_end )
    {
        return 1;
    }

    work->pad.dir = s11i_zk11fcom_800CFB2C( &work->control.mov, &s11i_dword_800C34C4[ work->param.index ] );
    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D020C( Zako11FWork *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x200000;
    }
    else if ( work->actend || work->count3 > 30 )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D0274( Zako11FWork *work )
{
    int count3;

    work->pad.press |= 0x10000;

    count3 = work->count3;
    if ( count3 == 0 )
    {
        work->pad.press |= 0x40;
    }
    else if ( count3 >= 60 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D02BC( Zako11FWork *work )
{
    int count3;

    work->pad.press |= 0x10000;

    count3 = work->count3;
    if (count3 < 10)
    {
        if ((work->count3 % 2) == 0)
        {
            work->pad.press |= 0x2000000;
        }
    }
    else if (count3 >= 20)
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;

    if (GM_PlayerPosition.vz > 10500 && (GM_PlayerPosition.vx < 5500 || GM_PlayerPosition.vx > 7500))
    {
        work->pad.dir &= 0xFFF;

        if (work->pad.dir >= 39 && work->pad.dir <= 1023)
        {
            work->pad.dir = 38;
        }

        if (work->pad.dir < 6 || work->pad.dir > 3072)
        {
            work->pad.dir = 6;
        }
    }

    work->pad.dir += 47;
    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D039C( Zako11FWork *work )
{
    if (work->sn_dis < 800)
    {
        work->pad.press |= 0x10000;
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D03E4( Zako11FWork *work )
{
    work->pad.press |= 0x10000;

    if (work->count3 == 8)
    {
        work->count3 += GV_RandU(8);
    }

    work->pad.dir = work->sn_dir & 0xFFF;

    if (GM_PlayerPosition.vz > 10500 && (GM_PlayerPosition.vx < 5500 || GM_PlayerPosition.vx > 7500))
    {
        if (work->pad.dir > 38 && work->pad.dir < 1024)
        {
            work->pad.dir = 38;
        }

        if (work->pad.dir < 5 || work->pad.dir > 3072)
        {
            work->pad.dir = 5;
        }
    }

    if (work->count3 > 18)
    {
        switch (s11i_dword_800C34DC[work->param.index][work->field_C3C])
        {
        case 0:
            if (work->vision.field_B92 != 2)
            {
                return 14;
            }

            if (work->sn_dis < 1000 && !(GM_PlayerStatus & (PLAYER_CB_BOX | PLAYER_GROUND | PLAYER_SQUAT)))
            {
                return 10;
            }

            if (work->sn_dis < work->field_BFC)
            {
                return 6;
            }

            return 14;

        case 1:
            return 14;

        case 3:
            return 7;

        case 6:
            work->pad.dir += 47;
            return 12;

        case 5:
            return 13;

        case 2:
            if (GV_RandU(8) == 0)
            {
                return 11;
            }

            return 14;
        }
    }

    if (work->field_C3C != ZAKO11F_GameFlag_800D5C4C)
    {
        return 14;
    }

    work->count3++;
    return 0;
}

int s11i_zk11fcom_800D05D4( Zako11FWork *work )
{
    work->pad.dir = work->sn_dir;
    work->pad.press |= 0x10000;

    work->field_C3C = ZAKO11F_GameFlag_800D5C4C;
    work->param.field_B7C = s11i_dword_800C359C[work->param.index][ZAKO11F_GameFlag_800D5C4C];
    return 15;
}


void s11i_zk11fcom_800D0628( Zako11FWork *work )
{
    work->field_C3C = ZAKO11F_GameFlag_800D5C4C;
    work->param.field_B7C = s11i_dword_800C359C[work->param.index][ZAKO11F_GameFlag_800D5C4C];
    s11i_zk11fcom_800CFA88(work);
}

void s11i_zk11fcom_800D0674( Zako11FWork *work )
{
    switch (work->think3)
    {
    case 0:
        s11i_zk11fcom_800D0628(work);
        break;
    }
}

void s11i_zk11fcom_800D06A4( Zako11FWork *work )
{
    switch (work->think3)
    {
    case 1:
        if (s11i_zk11fcom_800CFE24(work))
        {
            work->think2 = 2;
            work->think3 = 14;
            work->count3 = 0;
        }
        break;

    case 2:
        if (s11i_zk11fcom_800CFEA4(work))
        {
            work->think2 = 3;
            work->think3 = 16;
            work->pad.mode = 1;
            work->pad.sound = 0xF0;
            work->think1 = 0;
            work->count3 = 0;
            work->alert_level = 0xFF;
        }
        break;

    case 3:
        if (s11i_zk11fcom_800CFEA4(work))
        {
            s11i_zk11fcom_800CFA88(work);
            work->pad.sound = 0xF0;
            work->alert_level = 0xFF;
        }
        break;
    }
}

void s11i_zk11fcom_800D078C( Zako11FWork *work )
{
    int think;

    switch(work->think3)
    {
    case 6:
        if (s11i_zk11fcom_800D0098(work))
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;

    case 7:
        if (s11i_zk11fcom_800D00EC(work))
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;

    case 9:
        if (s11i_zk11fcom_800D0148(work))
        {
            s11i_zk11fcom_800CFB10(work);
            work->count3 = 0;
        }
        break;

    case 10:
        if (s11i_zk11fcom_800D020C(work))
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;

    case 11:
        if (s11i_zk11fcom_800D0274(work))
        {
            work->think3 = 14;
            work->count3 = 0;
        }

        if (s11i_zk11fcom_800D0DA8() && work->sn_dis > ZAKO11F_EYE_LENGTH_800C3694 + 2000)
        {
            s11i_zk11fcom_800CFAF4(work);
        }
        break;

    case 12:
        if (s11i_zk11fcom_800D02BC(work))
        {
            work->think3 = 14;
            work->count3 = 0;
        }

        if (s11i_zk11fcom_800D0DA8() && work->sn_dis > ZAKO11F_EYE_LENGTH_800C3694 + 2000)
        {
            s11i_zk11fcom_800CFAF4(work);
        }
        break;

    case 13:
        if (s11i_zk11fcom_800D039C(work))
        {
            work->think3 = 10;
            work->count3 = 0;
        }
        break;

    case 15:
        think = s11i_zk11fcom_800D03E4(work);
        if (think != 0)
        {
            work->think3 = think;
            work->count3 = 0;
        }

        if (s11i_zk11fcom_800D0DA8() && work->sn_dis > ZAKO11F_EYE_LENGTH_800C3694 + 2000)
        {
            s11i_zk11fcom_800CFAF4(work);
        }
        break;

    case 14:
        think = s11i_zk11fcom_800D05D4(work);
        if (think != 0)
        {
            work->think3 = think;
            work->count3 = 0;
        }

        if (work->param.field_B7C == 0xFF)
        {
            if (work->field_C0C == ZAKOCOM_PlayerAddress_800D5C50 || work->sn_dis <= work->field_BFC)
            {
                break;
            }
        }
        else if (HZD_ZoneContains(work->control.map->hzd, &work->control.mov, work->param.field_B7C))
        {
            break;
        }

        s11i_zk11fcom_800CFA88(work);
        break;
    }

    if (work->vision.field_B92 == 2)
    {
        s11i_zk11fcom_800D0C70();
        work->alert_level = 0xFF;
    }
}

void s11i_zk11fcom_800D098C( Zako11FWork *work )
{
    int trace;

    switch (work->think3)
    {
    case 4:
        s11i_zk11fcom_800CF9E4(work);

        if (s11i_zk11fcom_800CFF0C(work))
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;

    case 5:
        trace = s11i_zk11fcom_800D0004(work);
        if (trace < 0)
        {
            work->think3 = 4;
            work->count3 = 0;
        }
        else if (trace > 0)
        {
            work->think2 = 2;
            work->think3 = 0xE;
            work->count3 = 0;
        }
        break;
    }

    if (work->sn_dis < work->field_BFC && GM_PlayerStance == 0)
    {
        work->think2 = 2;
        work->think3 = 14;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }

    if (work->vision.field_B92 == 2)
    {
        work->alert_level = 0xFF;
    }

    s11i_zk11fcom_800D0C70();
}

void s11i_zk11fcom_800D0A88( Zako11FWork *work )
{
    if (work->think3 == 16 && s11i_zk11fcom_800CFF0C(work))
    {
        work->think2 = 2;
        work->think3 = 14;
        work->count3 = 0;
    }

    if (work->sn_dis < 800 && GM_PlayerStance == 0)
    {
        work->think2 = 2;
        work->think3 = 10;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
}

void s11i_zk11fcom_800D0B1C( Zako11FWork *work )
{
    switch ( work->think2 )
    {
    case 0:
        s11i_zk11fcom_800D0674( work );
        break;
    case 1:
        s11i_zk11fcom_800D098C( work );
        break;
    case 2:
        s11i_zk11fcom_800D078C( work );
        break;
    case 3:
        s11i_zk11fcom_800D0A88( work );
        break;
    case 4:
        s11i_zk11fcom_800D06A4( work );
        break;
    }
}

void Zako11FThink_800D0BAC( Zako11FWork *work )
{
    work->pad.dir   = -1;
    work->pad.press =  0;
    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT;
    work->alert_level = 0xFF;

    if (work->think1 == 0)
    {
        work->unknown.field_1E = 1;
        s11i_zk11fcom_800D0B1C( work );
    }
}
