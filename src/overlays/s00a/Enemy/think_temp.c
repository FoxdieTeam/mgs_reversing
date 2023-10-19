#include "enemy.h"

void EnemyResetThink_800CB224( WatcherWork* work ) 
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
    work->pad.field_08 = 0;
}

void s00a_command_800CB240( WatcherWork* work ) 
{
    work->think2 = 7;
    work->think3 = 14;
    work->count3 = 0;
}

void s00a_command_800CB258( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        work->think1 = 1;
        work->think2 = 8;
        work->think3 = 19;
    }
    else
    {
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28; 
        s00a_command_800CB0E0( work );
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB2C8( WatcherWork *work )
{

    work->think1 = 1;
    work->think2 = 9;
    work->think3 = 27;
    work->count3 = 32;
    work->pad.field_08 = 1;
}

void s00a_command_800CB2F4( WatcherWork *work )
{
    if ( work->field_B7C == 0xFF )
    {
        s00a_command_800CAFD4( work );
        work->think1 = 1;

        if ( EnemyCommand_800E0D98.field_0x40 == 1 )
        {
            work->think2 = 8;
            work->think3 = 18;
        }
        else
        {
            work->think2 = 10;
            work->think3 = 29;
        }
    }
    else
    {
        s00a_command_800CB0E0( work );
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 28;
    }
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB394( WatcherWork *work )
{
    work->think1 = 1;
    work->think2 = 10;
    
    if ( work->field_B7C == 0xFF )
    {
        work->think3 = 29;
    }
    else
    {
        s00a_command_800CB0E0( work );
        work->think3 = 28;
    }
    
    work->count3 = 0;
    work->pad.field_08 = 1;
}

void s00a_command_800CB3F0( WatcherWork *work )
{

    work->think2 = 4;

    if ( (work->act_status & 0x10) && (work->field_BA1 & 8) )
    {
        work->think3 = 0xE;
    }
    else
    {
        work->think3 = 4;
    }
    
    work->count3 = 0;
    work->modetime[2] = 0;
}

void SetThink_Move_800CB42C( WatcherWork* work )
{
    EnemyCommand_800E0D98.field_0x40 = 0;
    if ( work->act_status & 4 )
    {
        work->think1 = 2;
        s00a_command_800CB3F0( work );
        work->pad.field_08 = 0;
        return;       
    }

    if ( work->field_B7C != 0xFF )
    {
        if ( !( sub_8005D134( work->control.field_2C_map->field_8_hzd, &work->control.field_0_mov, work->field_B7C ) ) )
        {
            s00a_command_800CB0E0( work );
            work->think1 = 2;
            work->think2 = 11;
            work->pad.field_08 = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->pad.field_08 = 0;
        }
    }
    else
    {
        if ( work->field_BFC >= 5800 )
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->pad.field_08 = 0;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 11;
            work->pad.field_08 = 1;
        }
    }
    work->count3 = 0;
}

void s00a_command_800CB504( WatcherWork* work )
{
    switch( GM_NoisePower_800ABA24 )
    {
    case 5:
        work->think2 = 1;
        work->think3 = 8;
        break;
    case 200:
        s00a_command_800CAB74( work );
        s00a_command_800CEB54();
        work->think2 = 1;

        if (work->act_status & 0x10 )
        {
            work->think3 = 15;
        }
        else 
        {
            work->think3 = 6;
        }
        break;
    case 255:
        s00a_command_800CAB74( work );
        s00a_command_800CEB54();
        work->think2 = 7;
        work->think3 = 16;
        break;
    default:
    case 100:
        s00a_command_800CAB74( work );
        work->think2 = 1;

        if ( work->act_status & 0x10 )
        {
            work->think3 = 14;
        } 
        else
        {
            work->think3 = 5;
        }
        work->modetime[0] = 0;
        break;
    }
    work->count3 = 0;
}

void s00a_command_800CB610( WatcherWork* work ) 
{
    work->think2 = 2;
    work->think3 = 5;
    work->count3 = 0;
}


extern char NearAsiato_800D13A0();

void s00a_command_800CB628( WatcherWork *work )
{
    work->think2 = 5;
    work->think3 = 5;
    work->field_BA0 = NearAsiato_800D13A0();
    work->count3 = 0;
}

void s00a_command_800CB660( WatcherWork *work )
{
    int addr;
    HZD_HDL *hzd;

    hzd  = work->control.field_2C_map->field_8_hzd;
    addr = HZD_GetAddress_8005C6C4( hzd, &work->control.field_0_mov, -1 );

    work->field_C04 = addr;
    if ( sub_8005CD1C( hzd, addr & 0xFF, work->target_addr & 0xFF ) < 200 )
    {
        work->pad.field_08 = 0;
    }
    else
    {
        work->pad.field_08 = 1;
    }
}

int s00a_command_800CB6CC( WatcherWork* work )
{
    int count;
    int v1;

    count = work->l_count;
    v1 = count / 30;
    v1 = v1 + work->field_B78;

    if ( v1 == 1 || v1 == 4 )
    {
        work->pad.press |= 0x2;
    }
    else if ( v1 == 2 || v1 == 5 )
    {
        work->pad.press |= 0x1;
    }

    if ( count > 90 )
    {
        work->l_count = 0;
        return 1;
    }
    else
    {
        work->l_count++;
        return 0;
    }
}

int s00a_command_800CB770( WatcherWork* work )
{
    int count;

    count = work->l_count;

    if ( count == 0 )
    {
        work->control.field_4C_turn_vec.vy = ( work->control.field_4C_turn_vec.vy + 0x800 ) & 0xFFF;
    }

    if ( count == 24 )
    {
        work->control.field_4C_turn_vec.vy = ( work->control.field_4C_turn_vec.vy + 0x800 ) & 0xFFF;
    }

    if ( count > 30 )
    {
        work->l_count = 0;
        return 1;
    }
    else
    {
        work->l_count++;
        return 0;
    }
}

int s00a_command_800CB7E0( WatcherWork *work )
{
    work->count3++;
    work->pad.dir = work->sn_dir;
    return 0;
}

int s00a_command_800CB7FC( WatcherWork *work )
{
    int count = work->count3;
    
    if ( count == 0 )
    {
        work->pad.sound = 245;
    }
    else
    {
        if ( count > 32 )
        {
            return 1;
        }       
    }
    work->count3++;
    return 0;
}

extern SVECTOR GM_PlayerPosition_800ABA10;

int s00a_command_800CB838( WatcherWork *work )
{
    int temp;
    SVECTOR svec;
    CONTROL *ctrl;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int addr, addr2, addr3;
    int reach;
    
    ctrl = &work->control;
    hzd  = work->control.field_2C_map->field_8_hzd;
    addr = work->target_addr;

    addr2 = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, work->field_C04 );
    work->field_C04 = addr2;

    reach = HZD_ReachTo_8005C89C( hzd, addr2, work->field_C08 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;
        if ( sub_8005D134( hzd, &work->control.field_0_mov, work->target_addr & 0xFF ) )
        {
            work->field_C14 = work->target_pos;
            work->field_C08 = addr;

            GV_SubVec3_80016D40( &work->field_C14, &ctrl->field_0_mov, &svec );

            work->pad.dir = GV_YawVec3_80016EF8( &svec );
            return -1;
        }
    
        if ( !( work->field_C00 & 1 ) )
        {
            addr3 = sub_8005CB48( hzd, addr2, addr, &ctrl->field_0_mov );
            zone = &hzd->f00_header->navmeshes[ addr3 ];
    
            if ( GM_PlayerPosition_800ABA10.vx & 1 )
            {
                work->field_C14.vx = zone->x + 230;
            }
            else
            {
                 work->field_C14.vx = zone->x - 230;
            }
    
            if ( GM_PlayerPosition_800ABA10.vz & 1 )
            {
                work->field_C14.vz = zone->z + 230;
            }
            else
            {
                 work->field_C14.vz = zone->z - 230;
            }
            work->field_C14.vy = zone->y;
        }
        else
        {
            addr3 = HZD_LinkRoute_8005C974( hzd, addr2, addr, &ctrl->field_0_mov );
            zone = &hzd->f00_header->navmeshes[ addr3 ];
            work->field_C14.vx = zone->x;
            work->field_C14.vy = zone->y;
            work->field_C14.vz = zone->z;
        }
        temp = addr3 & 0xFF;
        work->field_C08 = temp | temp << 8;
    }

    GV_SubVec3_80016D40( &work->field_C14, &work->control.field_0_mov, &svec );
    return GV_YawVec3_80016EF8( &svec );
}

int s00a_command_800CBA50( WatcherWork *work )
{
    int i;
    MAP *map;
    HZD_PAT *patrol;
    HZD_PTP *points;

    map = Map_FromId_800314C0( work->start_map );
    patrol = map->field_8_hzd->f00_header->routes;
    patrol = &patrol[ work->field_B7D ];
    
    work->field_9E8 = patrol->n_points;

    if ( work->field_9E8 <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->field_9E8 ; i++ )
    {
        work->nodes[i].vx  = points->x;
        work->nodes[i].vy  = points->y;
        work->nodes[i].vz  = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    
    work->start_pos = work->nodes[0];
    work->start_addr = HZD_GetAddress_8005C6C4( map->field_8_hzd, &work->start_pos, -1 );
    return 0;
}