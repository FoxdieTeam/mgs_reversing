#include "enemy.h"
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
    work->target_pos  = COM_PlayerPosOne_800E0D48[ work->field_B78 ];
    work->target_map  = COM_PlayerMapOne_800E0F70[ work->field_B78 ];
}