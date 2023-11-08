#include "enemy_externs.h"
#include "libhzd/libhzd.h"
int s00a_command_800CA898( WatcherWork* work, HZD_ZON* zone )
{
    int i;
    for ( i = 0 ; i < work->field_C34 ; i++ )
    {
        if ( zone->padding == work->field_C35[i] ) return 1;
    }
    return 0;
}

extern const char aErrerrerrnotlinkroutedtod_800E0690[];

int s00a_command_800CA8E0( WatcherWork *work, int addr_in )
{
    int temp, temp2;
    int res;
    int addr;
    HZD_HDL *hzd;
    SVECTOR svec;
    HZD_ZON *zone;
    CONTROL *ctrl;
    int local_addr;

    ctrl = &work->control;
    hzd = ctrl->field_2C_map->field_8_hzd;
    addr = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, -1 ) & 0xFF;
    zone = &hzd->f00_header->navmeshes[ addr ];
    svec.vx = zone->x;
    svec.vy = zone->y;
    svec.vz = zone->z;

    temp2 = addr_in & 0xFF;
    local_addr = temp2 | (temp2 << 8);

    for (  ;; )
    {
        temp = addr & 0xFF;
        res = HZD_LinkRoute_8005C974( hzd, temp | ( temp << 8 ), local_addr, &svec );
        if ( res == addr )
        {
            printf( aErrerrerrnotlinkroutedtod_800E0690, addr, addr_in );
            return addr;
        }

        zone = &hzd->f00_header->navmeshes[ res ];
        if ( s00a_command_800CA898( work, zone ) )
        {
            return addr;
        }
        
        svec.vx = zone->x;
        svec.vy = zone->y;
        svec.vz = zone->z;
        addr = res;
    }
}

extern const char aErrnozoneidingcl_800E06C0[];

void s00a_command_800CAA2C( WatcherWork *work, int addr )
{
    MAP     *map;
    HZD_ZON *zone;

    work->target_addr = (addr | addr << 8);
    zone = &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;

    map = Map_FindByZoneId_80031624( 1 << zone->padding );
    if ( map )
    {
        work->target_map = map->field_0_map_index_bit;
    }
    else
    {
        printf( aErrnozoneidingcl_800E06C0 );
    }
}

void s00a_command_800CAACC( WatcherWork* work ) 
{
    work->target_addr = work->start_addr;
    work->target_pos  = work->start_pos;
    work->target_map  = work->start_map;
}

void s00a_command_800CAB04( WatcherWork* work ) 
{
    work->target_addr = COM_PlayerAddressOne_800E0F40[ work->field_B78 ];
    work->target_pos  = COM_PlayerPositionOne_800E0D48[ work->field_B78 ];
    work->target_map  = COM_PlayerMapOne_800E0F70[ work->field_B78 ];
}

extern CONTROL *GM_WhereList_800B56D0[94];

void s00a_command_800CAB74( WatcherWork* work )
{
    int addr;
    MAP *map;
    HZD_ZON *zone;
    
    addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd, &GM_NoisePosition_800AB9F8, -1 ) & 0xFF;
    zone = &GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

    if ( work->field_C34 && s00a_command_800CA898( work , zone ) )
    {
        s00a_command_800CAA2C( work, s00a_command_800CA8E0( work, addr ) );
        return;
    }

    addr &= 0xFF;
    work->target_addr = addr | ( addr << 8 );
    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;

    map = Map_FindByZoneId_80031624( 1 << zone->padding );
    if ( map == NULL )
    {
        printf( aErrnozoneidingcl_800E06C0 );
        work->target_map = COM_PlayerMapOne_800E0F70[ work->field_B78 ];
    }
    else
    {
        work->target_map = map->field_0_map_index_bit;
    }
}

int s00a_command_800CACA0( WatcherWork *work, int addr, int addr2 )
{
    SVECTOR svec;
    SVECTOR svec2;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    HZD_ZON *zone2;
    
    if ( work->param_blood != 0x51 )
    {
        return 0;
    }

    hzd = work->control.field_2C_map->field_8_hzd; 

    zone  = &hzd->f00_header->navmeshes[ addr ];
    zone2 = &hzd->f00_header->navmeshes[ addr2 ];

    if ( zone->y || zone2->y )
    {
        return 0;
    }
    
    svec.vx = zone->x;
    svec.vy = zone->y + 500;
    svec.vz = zone->z;

    svec2.vx = zone2->x;
    svec2.vy = zone2->y + 500;
    svec2.vz = zone2->z;
    
    return sub_80028454( hzd, &svec, &svec2, 0x8, 0x2 ) != 0;
}

extern int sub_8005D168(HZD_HDL *pHzd, int a2, int *a3);
int s00a_command_800CEA9C( int addr );
void s00a_command_800CEA84( int a, int addr );

void s00a_command_800CAD84( WatcherWork *work )
{
    int i;
    int vx;
    int res;
    int addr;
    MAP *map;
    CONTROL *ctrl;
    int addr_copy;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    HZD_ZON *zone2;
    HZD_ZON *zone3;
    int unk[5]; //?

    ctrl = &work->control;
    hzd = work->control.field_2C_map->field_8_hzd;

    addr = HZD_GetAddress_8005C6C4( hzd, &ctrl->field_0_mov, -1 ) & 0xFF;
    i = 0;
    zone = &hzd->f00_header->navmeshes[ addr ];
    addr_copy = addr;

    res = sub_8005D168( hzd, addr, unk );
    work->field_AEC = 1;
    
    if ( res > 0 )
    {
        vx = work->control.field_0_mov.vx % res; 

        if ( vx < 0 )
        {
            vx = -vx;
        }

        for ( i = 0 ; i < res ; i++ )
        {
            addr  = unk[vx];
            zone2 = &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];

            if ( !s00a_command_800CA898( work , zone2 ) )
            {
                map = Map_FindByZoneId_80031624( 1 << zone2->padding );
                if ( map )
                {
                    if ( map->field_6_bUsed || zone->padding == zone2->padding )
                    {
                        if ( !s00a_command_800CACA0( work, addr_copy, addr ) )
                        {
                            if ( s00a_command_800CEA9C( addr ) )
                            {
                                goto loop;
                            }
                            else
                            {
                                goto end;
                            }
                        }
                    }
                }
                else
                {
                    printf( aErrnozoneidingcl_800E06C0 );
                    if ( s00a_command_800CEA9C( addr ) )
                    {
                        goto loop;
                    }
                    else
                    {
end:
                        work->field_AEC = 0;
                        s00a_command_800CEA84( work->field_B78, addr );
                        break;
                    }
                }
                
                
            }
loop:
            vx++;
            addr = addr_copy;
            if ( vx >= res )
            {
                vx = 0;
            }
        }
        
    }
    else
    {
        work->field_AEC = 0;
    }
    
    zone3 = &hzd->f00_header->navmeshes[ addr ];
    work->target_addr = addr << 8 | addr;
    
    work->target_pos.vx = zone3->x;
    work->target_pos.vy = zone3->y;
    work->target_pos.vz = zone3->z;
    work->target_map = COM_PlayerMap_800E0F1C;
}


void s00a_command_800CAFD4( WatcherWork* work )
{
    unsigned char addr;
    
    if ( !work->field_C34 )
    {
        work->target_addr = EnemyCommand_800E0D98.com_addr;
        work->target_pos  = EnemyCommand_800E0D98.com_pos;
        work->target_map  = EnemyCommand_800E0D98.com_map;
        return;
    }

    addr = EnemyCommand_800E0D98.com_addr;
    if ( s00a_command_800CA898( work, &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ] ) )
    {
        s00a_command_800CAA2C( work, s00a_command_800CA8E0( work, addr ) );
        return;
    }

    work->target_addr = EnemyCommand_800E0D98.com_addr;
    work->target_pos  = EnemyCommand_800E0D98.com_pos;
    work->target_map  = EnemyCommand_800E0D98.com_map;
}

void s00a_command_800CB0E0( WatcherWork* work )
{
    int v0, v1, a2;
    HZD_HDL *hzd;
    void *a1;
    MAP *map;
    HZD_HEADER *hdr;

    v0 = work->field_B7C;
    do {} while (0);
    map = work->control.field_2C_map;
    v1 = v0 << 1;
    v1 = v1 + v0;
    hzd = map->field_8_hzd;
    a2 = v0 << 8; 
    hdr = hzd->f00_header;
    v0 = v0 | a2;
    a1 = hdr->navmeshes;
    v1 = v1 << 3; 
    work->target_addr = v0;
    a1 = a1  + v1; 
        
    work->target_pos.vx = ((HZD_ZON*)a1)->x;
    work->target_pos.vy = ((HZD_ZON*)a1)->y;
    work->target_pos.vz = ((HZD_ZON*)a1)->z;
    work->target_map = work->start_map;

    //should just be this
    /*
    addr = work->field_B7C;
    work->target_addr = addr | (addr << 8);
    zone = &work->control.field_2C_map->field_8_hzd->f00_header->navmeshes[ addr ];
    
    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
    */
}

void s00a_command_800CB13C( WatcherWork* work )
{
    int x;

    x = work->pad.field_00 + 1;
    if ( x >= work->field_9E8 )
    {
        x = 0;
    }
    work->pad.field_00 = x;
    work->target_pos = work->nodes[ x ];
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &work->target_pos, -1 );
    work->target_map = work->start_map;
}

extern void AsiatoPos_800D129C( signed char, SVECTOR * );

void s00a_command_800CB1C4( WatcherWork* work ) 
{
    AsiatoPos_800D129C( work->field_BA0, &work->target_pos );
    work->target_addr = HZD_GetAddress_8005C6C4( work->control.field_2C_map->field_8_hzd, &work->target_pos, -1 );
    work->target_map = work->control.field_2C_map->field_0_map_index_bit;
}
