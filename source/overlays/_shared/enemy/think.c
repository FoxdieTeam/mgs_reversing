#include "enemy.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern unsigned int  COM_GameStatus_800E0F3C;
extern SVECTOR       COM_PlayerPosition_800E0F30;
extern SVECTOR       COM_PlayerPositionOne_800E0D48[8];
extern int           COM_PlayerMapOne_800E0F70[8];
extern int           COM_PlayerAddressOne_800E0F40[8];
extern int           COM_VibTime_800E0F68;
extern int           COM_PlayerMap_800E0F1C;
extern int           COM_SHOOTRANGE_800E0D88;

const char aErrerrerrnotlinkroutedtod_800E0690[] = " Err Err Err Not Link Route [%d] to [%d] !!!!\n";
const char aErrnozoneidingcl_800E06C0[] = "!!!!!!Err No Zone ID In Gcl !!!!!!!!\n";
const char aKirari_800E06E8[] = "kirari01";
const char aBefmapnamed_800E06F4[] = "bef map name =%d \n";
const char aAftmapnamed_800E0708[] = "aft map name =%d \n";
const char aRootchange_800E071C[] = " Root Change !!\n";

unsigned short s00a_dword_800C351C[4] = { 100, 50, 25, 10 };

int s00a_dword_800C3524[32] =
{
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00002000, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000100, 0x00800000,
    0x01000000, 0x04000000, 0x08000000, 0x00000000,
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00002000, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x0000001F
};

extern void NewEyeflash_800D0CF4( MATRIX *, SVECTOR *, const char *, int );
extern char NearAsiato_800D13A0();
extern void CleanAsiato_800D1378();

int s00a_command_800CA898( WatcherWork* work, HZD_ZON* zone )
{
    int i;
    for ( i = 0 ; i < work->field_C34 ; i++ )
    {
        if ( zone->padding == work->field_C35[i] ) return 1;
    }
    return 0;
}

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
    hzd = ctrl->map->hzd;
    addr = HZD_GetAddress( hzd, &ctrl->mov, -1 ) & 0xFF;
    zone = &hzd->header->zones[ addr ];
    svec.vx = zone->x;
    svec.vy = zone->y;
    svec.vz = zone->z;

    temp2 = addr_in & 0xFF;
    local_addr = temp2 | (temp2 << 8);

    for (  ;; )
    {
        temp = addr & 0xFF;
        res = HZD_LinkRoute( hzd, temp | ( temp << 8 ), local_addr, &svec );
        if ( res == addr )
        {
            printf( (char *)aErrerrerrnotlinkroutedtod_800E0690, addr, addr_in );
            return addr;
        }

        zone = &hzd->header->zones[ res ];
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

void s00a_command_800CAA2C( WatcherWork *work, int addr )
{
    MAP     *map;
    HZD_ZON *zone;

    work->target_addr = (addr | addr << 8);
    zone = &work->control.map->hzd->header->zones[ addr ];

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;

    map = GM_FindMapZone( 1 << zone->padding );
    if ( map )
    {
        work->target_map = map->index;
    }
    else
    {
        printf( (char *)aErrnozoneidingcl_800E06C0 );
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

    addr = HZD_GetAddress( GM_WhereList_800B56D0[0]->map->hzd, &GM_NoisePosition, -1 ) & 0xFF;
    zone = &GM_WhereList_800B56D0[0]->map->hzd->header->zones[ addr ];

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

    map = GM_FindMapZone( 1 << zone->padding );
    if ( map == NULL )
    {
        printf( (char *)aErrnozoneidingcl_800E06C0 );
        work->target_map = COM_PlayerMapOne_800E0F70[ work->field_B78 ];
    }
    else
    {
        work->target_map = map->index;
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

    hzd = work->control.map->hzd;

    zone  = &hzd->header->zones[ addr ];
    zone2 = &hzd->header->zones[ addr2 ];

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

    return HZD_LineCheck( hzd, &svec, &svec2, HZD_CHECK_DYNSEG, 0x2 ) != 0;
}

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
    hzd = work->control.map->hzd;

    addr = HZD_GetAddress( hzd, &ctrl->mov, -1 ) & 0xFF;
    i = 0;
    zone = &hzd->header->zones[ addr ];
    addr_copy = addr;

    res = HZD_8005D168( hzd, addr, unk );
    work->search_flag = 1;

    if ( res > 0 )
    {
        vx = work->control.mov.vx % res;

        if ( vx < 0 )
        {
            vx = -vx;
        }

        for ( i = 0 ; i < res ; i++ )
        {
            addr  = unk[vx];
            zone2 = &work->control.map->hzd->header->zones[ addr ];

            if ( !s00a_command_800CA898( work , zone2 ) )
            {
                map = GM_FindMapZone( 1 << zone2->padding );
                if ( map )
                {
                    if ( map->used || zone->padding == zone2->padding )
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
                    printf( (char *)aErrnozoneidingcl_800E06C0 );
                    if ( s00a_command_800CEA9C( addr ) )
                    {
                        goto loop;
                    }
                    else
                    {
end:
                        work->search_flag = 0;
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
        work->search_flag = 0;
    }

    zone3 = &hzd->header->zones[ addr ];
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
    if ( s00a_command_800CA898( work, &work->control.map->hzd->header->zones[ addr ] ) )
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
    HZD_MAP *hdr;

    v0 = work->field_B7C;
    do {} while (0);
    map = work->control.map;
    v1 = v0 << 1;
    v1 = v1 + v0;
    hzd = map->hzd;
    a2 = v0 << 8;
    hdr = hzd->header;
    v0 = v0 | a2;
    a1 = hdr->zones;
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
    zone = &work->control.map->hzd->header->zones[ addr ];

    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
    */
}

void s00a_command_800CB13C( WatcherWork* work )
{
    int x;

    x = work->next_node + 1;
    if ( x >= work->n_nodes )
    {
        x = 0;
    }
    work->next_node = x;
    work->target_pos = work->nodes[ x ];
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = work->start_map;
}

extern void AsiatoPos_800D129C( signed char, SVECTOR * );

void s00a_command_800CB1C4( WatcherWork* work )
{
    AsiatoPos_800D129C( work->field_BA0, &work->target_pos );
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = work->control.map->index;
}

void EnemyResetThink_800CB224( WatcherWork* work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
    work->pad.mode = 0;
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
    work->pad.mode = 1;
}

void s00a_command_800CB2C8( WatcherWork *work )
{

    work->think1 = 1;
    work->think2 = 9;
    work->think3 = 27;
    work->count3 = 32;
    work->pad.mode = 1;
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
    work->pad.mode = 1;
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
    work->pad.mode = 1;
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

void s00a_command_800CB42C( WatcherWork* work )
{
    EnemyCommand_800E0D98.field_0x40 = 0;
    if ( work->act_status & 4 )
    {
        work->think1 = 2;
        s00a_command_800CB3F0( work );
        work->pad.mode = 0;
        return;
    }

    if ( work->field_B7C != 0xFF )
    {
        if ( !( HZD_8005D134( work->control.map->hzd, &work->control.mov, work->field_B7C ) ) )
        {
            s00a_command_800CB0E0( work );
            work->think1 = 2;
            work->think2 = 11;
            work->pad.mode = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 34;
            work->think4 = 3;
            work->pad.mode = 0;
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
            work->pad.mode = 0;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 11;
            work->pad.mode = 1;
        }
    }
    work->count3 = 0;
}

void s00a_command_800CB504( WatcherWork* work )
{
    switch( GM_NoisePower )
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
        work->modetime[(  T_NOISE  )] = 0;
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

    hzd  = work->control.map->hzd;
    addr = HZD_GetAddress( hzd, &work->control.mov, -1 );

    work->field_C04 = addr;
    if ( HZD_ZoneDistance( hzd, addr & 0xFF, work->target_addr & 0xFF ) < 200 )
    {
        work->pad.mode = 0;
    }
    else
    {
        work->pad.mode = 1;
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
        work->control.turn.vy = ( work->control.turn.vy + 0x800 ) & 0xFFF;
    }

    if ( count == 24 )
    {
        work->control.turn.vy = ( work->control.turn.vy + 0x800 ) & 0xFFF;
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
    hzd  = work->control.map->hzd;
    addr = work->target_addr;

    addr2 = HZD_GetAddress( hzd, &ctrl->mov, work->field_C04 );
    work->field_C04 = addr2;

    reach = HZD_ReachTo( hzd, addr2, work->field_C08 );

    if ( addr != work->field_BF0 || reach <= 0 )
    {
        work->field_BF0 = addr;
        if ( HZD_8005D134( hzd, &work->control.mov, work->target_addr & 0xFF ) )
        {
            work->field_C14 = work->target_pos;
            work->field_C08 = addr;

            GV_SubVec3( &work->field_C14, &ctrl->mov, &svec );

            work->pad.dir = GV_VecDir2( &svec );
            return -1;
        }

        if ( !( work->field_C00 & 1 ) )
        {
            addr3 = HZD_8005CB48( hzd, addr2, addr, &ctrl->mov );
            zone = &hzd->header->zones[ addr3 ];

            if ( GM_PlayerPosition.vx & 1 )
            {
                work->field_C14.vx = zone->x + 230;
            }
            else
            {
                 work->field_C14.vx = zone->x - 230;
            }

            if ( GM_PlayerPosition.vz & 1 )
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
            addr3 = HZD_LinkRoute( hzd, addr2, addr, &ctrl->mov );
            zone = &hzd->header->zones[ addr3 ];
            work->field_C14.vx = zone->x;
            work->field_C14.vy = zone->y;
            work->field_C14.vz = zone->z;
        }
        temp = addr3 & 0xFF;
        work->field_C08 = temp | temp << 8;
    }

    GV_SubVec3( &work->field_C14, &work->control.mov, &svec );
    return GV_VecDir2( &svec );
}

int s00a_command_800CBA50( WatcherWork *work )
{
    int i;
    MAP *map;
    HZD_PAT *patrol;
    HZD_PTP *points;

    map = GM_GetMap( work->start_map );
    patrol = map->hzd->header->routes;
    patrol = &patrol[ work->param_root ];

    work->n_nodes = patrol->n_points;

    if ( work->n_nodes <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->n_nodes ; i++ )
    {
        work->nodes[i].vx  = points->x;
        work->nodes[i].vy  = points->y;
        work->nodes[i].vz  = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }

    work->start_pos = work->nodes[0];
    work->start_addr = HZD_GetAddress( map->hzd, &work->start_pos, -1 );
    return 0;
}

int s00a_command_800CBB44( WatcherWork *work )
{
    int a2;
    int a0, con;
    int act, time, dir;
    int command;

start:
    //    starting from lo
    //   |con |dir|tim| act   //
    //000|0 00|00 |000|0 0000//

    command = work->target_pos.pad;
    act  = ( command & 0x1F );         //5 bits
    time = ( command & 0xE0 ) >> 5;    //3 bits
    dir  = ( command & 0x300 ) >> 8;   //2 bits
    con  = ( command & 0x1C00 ) >> 10; //3 bits

    if ( s00a_dword_800C3524[ act ] == 0x1F )
    {
        work->param_c_root = con + ( dir * 8 );
        return 0;
    }

    if ( time != 6 )
    {

        a2  = GV_Time % 100;
        a0  = con & 3;
        con = con & 4;

        if ( a2 >= s00a_dword_800C351C[ a0 ] || work->field_B4C == 1 )
        {
            work->field_B4C = 0;
            s00a_command_800CB13C( work );
            if ( !DirectTrace_800CC154( work , 350 ) )
            {
                return 0;
            }
            goto start;
        }

        if ( con != 0 )
        {
            work->field_B4C = 1;
        }
    }

    work->pad.time = work->field_BB0[ time ];
    work->pad.tmp  = s00a_dword_800C3524[ act ];

    if ( COM_GameStatus_800E0F3C & 1 )
    {
        if ( work->pad.tmp == 0x80 || work->pad.tmp == 0x200 || work->pad.tmp == 0x400 || work->pad.tmp == 0x800 )
        {
            work->pad.tmp = 0;
            if ( work->pad.time == 450 )
            {
                work->pad.time = 90;
            }
        }
    }

    if ( act == 0 && time == 0 )
    {
        work->pad.time = 0;
        work->pad.dir = work->control.rot.vy;
        s00a_command_800CB13C( work );
        return 0;
    }

    if ( act & 0x10 && act != 0x1F )
    {
        s00a_command_800CB13C( work );
        return 0;
    }

    work->pad.dir = work->field_BD0[ dir ];
    return 1;
}

int s00a_command_800CBD2C( WatcherWork* work )
{
    int len;
    CONTROL *ctrl;
    GV_MSG  *msg;

    ctrl = &work->control;
    len = ctrl->n_messages;
    msg = ctrl->messages;

    for ( ; len > 0 ; len--, msg++ )
    {
        if ( msg->message[0]  == work->field_B4C )
        {
            return 1;
        }
    }
    return 0;
}

int s00a_command_800CBD6C( WatcherWork* work )
{
    if ( work->pad.time == 32001 )
    {
        if ( s00a_command_800CBD2C( work ) )
        {
            work->field_B4C = 0;
            work->pad.time  = 0;
            return 1;
        }
        work->pad.press |= work->pad.tmp;
        return 0;
    }

    if ( !work->pad.time )
    {
        return 1;
    }

    work->pad.press |= work->pad.tmp;
    work->pad.time--;
    return 0;
}

int s00a_command_800CBDFC( WatcherWork* work )
{
    int count;

    count = work->count3;

    if ( count == 0 )
    {
        ENE_PutMark_800C9378( work, 0 );
        NewEyeflash_800D0CF4( &work->body.objs->objs[6].world, &work->control.mov, aKirari_800E06E8, 0 );
        COM_VibTime_800E0F68 = 10;
    }

    if ( count < 20 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;

}

int s00a_command_800CBE90( WatcherWork* work )
{
    if ( work->count3 == 0 )
    {
        ENE_PutMark_800C9378( work, 0 );
        s00a_command_800CC210( work );
        COM_VibTime_800E0F68 = 10;
    }

    if ( work->count3 > 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CBF00( WatcherWork *work )
{
    int addr2;
    SVECTOR svec;
    int addr;
    CONTROL *ctrl;
    DG_OBJS* objs;
    HZD_ZON *zone;
    MAP *map;

    objs = work->body.objs;
    if ( objs->bound_mode )
    {
        return 0;
    }

    if (!( work->act_status & 0x100 ) )
    {
        return 0;
    }

    ctrl = &work->control;
    addr2 = work->field_C04 & 0xFF;
    addr = HZD_8005CFAC( ctrl->map->hzd, work->target_addr & 0xFF, addr2, 0xC8 );

    if ( addr == addr2 )
    {
        return 0;
    }

    zone = &ctrl->map->hzd->header->zones[ addr ];
    svec.vx = zone->x;
    svec.vy = zone->y;
    svec.vz = zone->z;
    DG_PointCheck( &svec, 1 );

    if ( svec.pad == 1 )
    {
        return 0;
    }

    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;

    printf( (char *)aBefmapnamed_800E06F4, ctrl->map->index );

    map = GM_FindMapZone( 1 << zone->padding );
    if ( map )
    {
        ctrl->map = map;
    }
    else
    {
        printf( (char *)aErrnozoneidingcl_800E06C0 );
    }

    printf( (char *)aAftmapnamed_800E0708, ctrl->map->index );
    return 1;
}

int s00a_command_800CC064( WatcherWork* work )
{
    if ( !(work->count3 & 31 ) )
    {
        work->field_C04 = -1;
        work->field_BF0 = -1;
        s00a_command_800CB838( work );
    }

    work->pad.dir = s00a_command_800CB838( work );
    if ( work->pad.dir < 0 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CC0D4( WatcherWork* work )
{
    if ( s00a_command_800CBF00( work ) )
    {
        return 1;
    }

    if ( !(work->count3 & 31 ) )
    {
        work->field_C04 = -1;
        work->field_BF0 = -1;
        s00a_command_800CB838( work );
    }

    work->pad.dir = s00a_command_800CB838( work );
    if ( work->pad.dir < 0 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int DirectTrace_800CC154( WatcherWork* work, int a1 )
{
    int x, z;
    SVECTOR svec;


    svec.vx = x = work->target_pos.vx - work->control.mov.vx;
    svec.vz = z = work->target_pos.vz - work->control.mov.vz;

    if ( -a1 >= x || x >= a1 || -a1 >= z || z >= a1 )
    {
        work->pad.dir = GV_VecDir2( &svec );
        work->count3++;
        return 0;
    }

    return 1;
}

int s00a_command_800CC1DC(SVECTOR* arg0, SVECTOR* arg1 )
{
    SVECTOR svec;

    GV_SubVec3(arg1, arg0, &svec);
    return GV_VecDir2(&svec);
}

void s00a_command_800CC210( WatcherWork* work )
{
    work->pad.dir = s00a_command_800CC1DC( &work->control.mov, &work->target_pos );
}

int s00a_command_800CC240(SVECTOR* svec, SVECTOR* svec2, int a1) {
    int x, z;

    x = svec->vx - svec2->vx;
    z = svec->vz - svec2->vz;

    if ( -a1 < x || x < a1 || -a1 < z || z < a1 )
    {
        return 0;
    }

    return 1;
}

int NextAsiato_800D12D0( HZD_HDL*, signed char, SVECTOR * );

int s00a_command_800CC294( WatcherWork *work )
{
    int x;

    x = NextAsiato_800D12D0( work->control.map->hzd, work->field_BA0, &work->control.mov );

    if ( x >= 0 )
    {
        work->field_BA0 = x;
        return 1;
    }

    work->field_BA0 = -1;
    return 0;
}

int s00a_command_800CC2E8( WatcherWork* work )
{

    if ( work->param_c_root != work->param_root )
    {
        fprintf( 1, (char *)aRootchange_800E071C );
        work->param_root = work->param_c_root;
        s00a_command_800CBA50( work );
        return 1;
    }

    return 0;
}

int s00a_command_800CC344( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
       if ( COM_GameStatus_800E0F3C & 0x2000 )
       {
           work->think3 = 13;
           return 0;
       }

        COM_GameStatus_800E0F3C |= 0x2000;
        work->pad.dir = work->sn_dir;
    }

    if ( work->count3 == 63 && !( work->field_BA1 & 16 ) && EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->pad.sound = 140;
    }

    if ( work->actend || work->count3 >= 301 )
    {
        return 1;
    }

    work->pad.press |= SP_DANBOWLKERI;
    work->count3++;

    return 0;
}

int s00a_command_800CC40C( WatcherWork *work )
{
    if ( !( COM_GameStatus_800E0F3C & 0x2000 ) )
    {
        return 1;
    }

    work->pad.press |= 0x4;
    work->count3++;
    return 0;
}

int s00a_command_800CC44C( WatcherWork *work )
{
    int count;
    int v1;

    count = work->l_count;

    if ( count == 0 && work->field_C00 == 0 )
    {
        work->pad.sound = 132;
    }

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

    work->l_count++;
    return 0;
}

int Think3_GoNext_800CC514( WatcherWork* work ) {
    if ( work->pad.time ) {
        (work->pad.press |= (  work->pad.tmp  )) ;
        work->pad.time -- ;
    }

    if ( DirectTrace_800CC154( work, 350 ) ) {
        return 1 ;
    }

    return 0 ;
}

int Think3_BikkuriGetUp_800CC568( WatcherWork* work )
{
    if( work->count3 == 0){
        work->pad.press |= 0x00001000  ;
    } else  if( work->count3 > 90 || work->actend ){

        return 1 ;
    }
    work->count3 ++ ;
    return 0 ;
}

int Think3_NoiseModeWatch_800CC5C0( WatcherWork *work )
{
    if ( work->act_status & 0x00000080  )
    {
        work->pad.press |= 0x00800000  ;
    }

    if( work->count3 == 0)
    {
        if( EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
        {
            if( work->modetime[(  T_NOISE  )]  <= 1 )
            {
                work->pad.sound = (  0x88   ) ;
            }
            if( work->modetime[(  T_NOISE  )]  <= 3 )
            {
                ENE_PutMark_800C9378( work ,BW_MARK );
            }
            if ( !( work->act_status & 0x00000080 ) )
            {
                work->pad.dir = work->sn_dir;
            }
        }
        else
        {
            if( work->modetime[(  T_NOISE  )] ) return 1;
            work->pad.sound = 0x95;
            ENE_PutMark_800C9378( work ,BW_MARK );
            work->pad.dir = work->sn_dir;
        }
    }
    else
    {
        work->pad.dir = -1;
    }

    switch( work->modetime[(  T_NOISE  )] )
    {
        case 0:
            if( work->count3 >= 16)
            {
                if( EnemyCommand_800E0D98.mode  == TOP_COMM_TRAVEL )
                {
                    if ( !(work->act_status & 0x00000080 ) )
                    {
                        work->pad.sound = 0xF1;
                    }
                }
                return 1;
            }
            break;
        case 1:
        case 2:
            if ( work->count3 >= 48 )
            {
                return 1;
            }
            break;
        case 3:
            return 1;
    }
    work->count3++;
    return 0;
}

int s00a_command_800CC760( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.dir = work->sn_dir;
    }

    if ( work->count3 > 14 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CC7A4( WatcherWork *work )
{
    SVECTOR svec;
    GV_SubVec3( &GM_NoisePosition, &work->control.mov, &svec );
    work->pad.dir = GV_VecDir2( &svec );
    work->pad.press |= 0x02000000;

    if ( work->count3 == 0 )
    {
        ENE_PutMark_800C9378( work, BW_MARK );
    }

    if ( work->count3 > 30 )
    {
        return 1;
    }

    if ( work->field_BA1 & 1 )
    {
        work->count3 = 1;
    }
    else
    {
        work->count3++;
    }

    return 0;
}

int s00a_command_800CC83C( WatcherWork* work )
{
    if ( work->count3 == 0 )
    {
        if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
        {
            work->pad.sound = 136;
        }
        else
        {
            work->pad.sound = 150;
        }
        ENE_PutMark_800C9378( work, 5 );
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    if ( work->count3 > 15 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CC8C8( WatcherWork *work )
{
    if ( work->count3 > 2 && work->act_status & 1 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CC90C( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.dir = work->sn_dir;
    }

    if ( work->count3 == 30 )
    {
        work->pad.sound = 136;
        ENE_PutMark_800C9378( work, 5 );
    }

    if ( work->count3 > 29 && s00a_command_800CB6CC( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CC99C( WatcherWork *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.sound = 136;
        ENE_PutMark_800C9378( work, BW_MARK );
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    if ( work->count3 >= 16 )
    {
        if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
        {
            work->pad.sound = 243;
        }
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CCA28( WatcherWork *work )
{
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800C9378( work, 5 );
        if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
        {
            work->pad.sound = 244;
        }
        else
        {
            work->pad.sound = 132;
        }
    }

    if ( s00a_command_800CB6CC( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CCA9C( WatcherWork *work )
{
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800C9378( work, 5 );
        work->pad.sound = 244;
    }

    if ( s00a_command_800CB6CC( work ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s00a_command_800CCAFC( WatcherWork *work )
{
    work->pad.press |= 0x4;
    if ( work->count3 == 20 )
    {
        ENE_PutMark_800C9378( work, 5 );
        if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
        {
            work->pad.sound = 242;
        }
    }

    if ( work->count3 > 120 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}



int s00a_command_800CCB7C( WatcherWork *work )
{
    MAP *map;
    s00a_command_800CAB04( work );

    map = work->control.map;

    if ( !( map->index & work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->field_C04 = HZD_GetAddress( map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->field_C04, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return DirectTrace_800CC154( work, 1500 );
}

int s00a_command_800CCC14( WatcherWork *work )
{
    int count;

    count = work->count3;

    work->pad.press |= 0x10000;

    if ( count == 0 )
    {
        work->count3 = GV_RandU( 8 );
    }

    if ( count < 9 )
    {
        if ( !( count & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }

    if ( count > 11 )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;

}

int s00a_command_800CCCAC( WatcherWork *work )
{
    work->pad.press |= 0x10000;

    if ( work->param_blood == 71 )
    {
        return 1;
    }

    if ( work->count3 == 30 )
    {
        work->pad.press |= 0x100000;
        if ( work->act_status & 1 )
        {
            work->pad.sound = 131;
        }

    }
    else
    {
        if ( work->actend || work->count3 > 150 )
        {
            return 1;
        }
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s00a_command_800CCD38( WatcherWork *work )
{

    work->pad.press |= 0x10000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x200000;
    }
    else
    {
        if ( work->body.is_end || work->count3 > 30 )
        {
            return 1;
        }
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s00a_command_800CCDA0( WatcherWork *work )
{
    int count;
    work->pad.press |= 0x10000;

    count = work->count3;
    if ( count < 10 )
    {
        if ( !( work->count3 & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }
    else if ( count >= 20 )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int Think3_AttackSetup_800CCE08( WatcherWork *work )
{
    /*
    if ( ID == 2 ) {
        work->pad.press |= SP_WEAPON2 ;
    } else {
        work->pad.press |= SP_WEAPON ;
    }
    */
    work->pad.press |= 0x10000; //SP_WEAPON?
    work->pad.dir = work->sn_dir;

    /*
    switch( ZAKO_GameFlag ) {
    case FLAG_FIGHT1_DEMO :
    case FLAG_FIGHT1_DEMO1 :
    case FLAG_FIGHT1_DEMO2 :
        return 0 ;
    break ;
    }
    */

    if ( work->field_B7C == 0xFF )
    {
        if ( work->count3 == 16 )
        {
            work->count3 += GV_RandU( 14 );
        }

        if ( work->count3 > 32 )
        {
            /*
            if( work->chase_dis <= CHASE_DIS1
            && GM_PlayerStatus & PLAYER_INTRUDE  ){
                return TH3_ATTACK_GRENADE ;
            }
            */
            if ( work->field_C00   == 0    &&
                 work->alert_level == 255  &&
                 GM_PlayerStatus & ( PLAYER_NOHIDDEN | PLAYER_INTRUDE )  &&
                 work->vision.field_B92  == 0 )
            {
                return 0x18;
            }

            if ( work->sn_dis < COM_SHOOTRANGE_800E0D88 && work->vision.field_B92 == 2 )
            {
                if ( work->sn_dis < 1000 &&                 /* 距離が近かなかったら */
                    !(GM_PlayerStatus & PLAYER_SQUAT) &&    /* しゃがんでなかったら */
                    !(GM_PlayerStatus & PLAYER_GROUND) &&   /* 匍匐じゃなかったら */
                    !(GM_PlayerStatus & PLAYER_CB_BOX) ) {  /* 段ボールじゃなかったら */
                    return TH3_ATTACK_NEAR;
                }
                else
                {
                    return TH3_ATTACK_HANDGUN;
                }
            }
        }
    }
    else
    {
        if ( work->sn_dis < COM_SHOOTRANGE_800E0D88 && work->vision.field_B92 == 2 && (work->count3 & 1) )
        {
            if ( work->sn_dis < 1000 &&                 /* 距離が近かなかったら */
                !(GM_PlayerStatus & PLAYER_SQUAT) &&    /* しゃがんでなかったら */
                !(GM_PlayerStatus & PLAYER_GROUND) &&   /* 匍匐じゃなかったら */
                !(GM_PlayerStatus & PLAYER_CB_BOX) ) {  /* 段ボールじゃなかったら */
                return TH3_ATTACK_NEAR;
            }
            else
            {
                return 0x1A;
            }
        }

        if ( work->count3 > 32 )
        {
            if ( work->field_C00   == 0    &&
                 work->alert_level == 255  &&
                 (GM_PlayerStatus & ( PLAYER_NOHIDDEN | PLAYER_INTRUDE ))  &&
                 work->vision.field_B92  == 0 )
            {
                return 0x18;
            }
        }
    }

    work->count3++;
    return 0;
}

int s00a_command_800CD000( WatcherWork* work )
{
    switch ( work->think4 )
        {
        case 3:
            if ( s00a_command_800CB6CC( work ) )
            {
                work->think4 = 1;
                work->count3 = 0;
                s00a_command_800CAB04( work );
            }
            work->count3++;
            break;
        case 1:
            if (s00a_command_800CC064( work ) )
            {
                work->think4 = 3;
                work->count3 = 0;
            }
            break;
        }
    return 0;
}

int s00a_command_800CD08C( WatcherWork *work )
{
    switch( work->think4 )
    {
        case 0:
            if ( s00a_command_800CC44C(work) )
            {
                work->think4 = 2;
                s00a_command_800CAD84( work );
                work->count3 = 0;
            }
            break;
        case 3:
            if ( s00a_command_800CB6CC(work) )
            {
                work->think4 = 2;
                s00a_command_800CAD84( work );
                work->count3 = 0;
            }
            work->count3++;
            break;
        case 2:
            if ( DirectTrace_800CC154( work, 250 ) )
            {
                s00a_command_800CAD84( work );
                work->count3 = 0;
            }
            break;
    }

    return 0;
}

void s00a_command_800CD158( WatcherWork *work )
{
    if ( work->think3 == 3 && s00a_command_800CB7FC( work ) )
    {
        s00a_command_800CAACC( work );
        work->next_node = work->n_nodes;
        EnemyResetThink_800CB224( work );
        work->pad.mode = 1;
    }

    if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
    }
    else if ( work->field_BA1 & 1 )
    {
        s00a_command_800CB504( work );
    }
    else if ( work->alert_level > 1 )
    {
        s00a_command_800CB240( work );
    }
}

static inline void set_dir( WatcherWork *work )
{
    if ( GV_DiffDirAbs( work->pad.dir, work->control.rot.vy ) < 128 )
    {
        work->pad.dir = -1;
    }
}

static inline void think_reset( WatcherWork *work )
{
    s00a_command_800CAACC( work );
    work->next_node = work->n_nodes;
    EnemyResetThink_800CB224( work );
}

static inline void think_reset2( WatcherWork *work )
{
    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->next_node--;
        s00a_command_800CB13C( work );
        EnemyResetThink_800CB224( work );
        s00a_command_800CB660( work );
    }
    else
    {
        s00a_command_800CB42C( work );
    }
}

static inline void think_noise_inline( WatcherWork *work )
{
    s00a_command_800CAB74( work );
    s00a_command_800CEB54();
    work->think2 = 7;
    work->think3 = 16;
    work->count3 = 0;
}

void s00a_command_800CD210( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 0:
       if ( s00a_command_800CC064( work ) )
       {
           work->pad.mode = 0;
           work->think3 = 1;
           work->count3 = 0;
           work->next_node--;
           s00a_command_800CB13C( work );
           work->pad.time = 0;
       }
        break;
    case 1:
        if ( Think3_GoNext_800CC514( work ) )
        {
            if (!s00a_command_800CC2E8( work ) )
            {
                if ( s00a_command_800CBB44( work ) )
                {
                    work->think3 = 2;
                    set_dir( work );
                }
                work->count3 = 0;
            }
            else
            {
                think_reset( work );
            }
        }
        else
        {
            if ( work->field_BA1 & 64 )
            {
                s00a_command_800CB610( work );
                work->think3 = 12;
                return;
            }
        }
        break;
    case 2:
        if ( s00a_command_800CBD6C( work ) )
        {
            if ( s00a_command_800CC2E8( work ) )
            {
                think_reset( work );
            }
            else
            {
                s00a_command_800CB13C( work );
                if ( DirectTrace_800CC154( work, 350 ) )
                {
                    if ( !s00a_command_800CBB44( work ) )
                    {
                        if ( s00a_command_800CC2E8( work ) )
                        {
                            think_reset( work );
                            break;
                        }
                        work->think3 = 1;
                    }
                    else
                    {
                        set_dir( work );
                    }
                }
                else
                {
                    work->think3 = 1;
                }
                work->count3 = 0;
            }
        }
        break;
    }


    if ( s00a_command_800CC2E8( work ) )
    {
        think_reset( work );
    }

    if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
    }
    else if ( work->field_BA1 & 2)
    {
        s00a_command_800CB610( work );
    }
    else if ( work->field_BA1 & 1)
    {
        s00a_command_800CB504( work );
    }
    else if ( work->field_BA1 & 16 )
    {
        s00a_command_800CB628( work );
    }
    else if ( work->alert_level > 2 )
    {
        ENE_SetGopointLast_800CEB00();
        s00a_command_800CB240( work );
    }
}

void s00a_command_800CD470( WatcherWork *work )
{

}

void s00a_command_800CD478( WatcherWork *work )
{
    switch ( work->think3 )
    {
        case 14:
            if ( Think3_BikkuriGetUp_800CC568( work ) )
            {
                work->think3 = 5;
                work->count3 = 0;
            }
            break;
        case 4:
            if ( s00a_command_800CC8C8( work ) )
            {
                work->think3 = 5;
                work->count3 = 0;
            }
            break;
        case 5:
           if ( s00a_command_800CC90C( work ) )
           {
               think_reset2( work );
           }
           if ( ( work->field_BA1 & 1 ) && ( GM_NoisePower == 200 || GM_NoisePower == 255 ) )
           {
                think_noise_inline( work );
           }
           if ( work->field_BA1 & 2 )
           {
               s00a_command_800CB610( work );
               return;
           }
        break;
    }

    if ( ( *( int * )&work->field_BA0 & 0xC00 ) == 0x400 )
    {
        s00a_command_800CB3F0( work );
    }
    else if ( work->alert_level > 1 )
    {
        s00a_command_800CB240( work );
    }
}


void s00a_command_800CD608( WatcherWork *work )
{
    short x;
    x = work->think3 - 5;
    switch ( x )
    {
    case 0:
        if ( s00a_command_800CC83C( work ) )
        {
            s00a_command_800CAB04( work );
            work->think3 = 9;
            work->count3 = 0;
            if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
            {
                work->pad.mode = 0;
            }
            else
            {
                work->pad.mode = 1;
            }
        }
        break;
    case 4:
        if ( s00a_command_800CC064( work ) )
        {
            work->think3 = 10;
            work->count3 = 0;
        }
        if ( s00a_command_800CC240( &work->target_pos, &work->control.mov, 1500 ) )
        {
            work->think3 = 11;
            work->count3 = 0;
        }
        if ( work->sn_dis < 1500 )
        {
            if ( ( signed char )work->field_BA1 & 128 )
            {
                if ( ( ( work->field_BA1 & 16 ) || work->think1 == 2 ) )
                {
                    work->think3 = 12;
                    work->count3 = 0;
                    break;
                }
                work->think3 = 11;
                work->count3 = 0;
            }
        }
        break;
    case 5:
    if  ( DirectTrace_800CC154( work, 1500 ) )
    {
        int a;
        a = work->field_BA1;
        work->pad.dir = work->sn_dir;

        if ( !( a & 16 ) )
        {
            if ( work->think1 != 2 )
            {
                work->think3 = 11;
                work->count3 = 0;
                break;
            }
        }

        if ( a & 128 )
        {
            work->think3 = 12;
            work->count3 = 0;
            break;
        }

        work->think3 = 11;
        work->count3 = 0;
    }
    break;
    case 6:
        if ( s00a_command_800CCAFC( work ) )
        {
            think_reset2( work );
        }
        break;
    case 7:
        if ( s00a_command_800CC344( work ) )
        {
            think_reset2( work );
        }
        break;
    case 8:
        if ( s00a_command_800CC40C( work ) )
        {
            think_reset2( work );
        }
        break;
    }

    if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
        return;
    }

    if ( work->alert_level > 1 || work->field_BA1 & 2 )
    {
        s00a_command_800CB240( work );
        return;
    }

    if ( work->field_BA1 & 1 )
    {
        if ( (GM_NoisePower != 100) )
        {
            if ( GM_NoisePower == 255 )
            {
                think_noise_inline( work );
                return;
            }
        }
        s00a_command_800CB240( work );
        work->count3 = 0;
        return ;
    }
}

void s00a_command_800CD8B0( WatcherWork *work )
{
    short x;
    x = work->think3 - 5;
    switch ( x )
    {
        case 10:
        if ( Think3_BikkuriGetUp_800CC568( work ) )
        {
            work->think3 = 6;
            work->count3 = 0;
        }
        break;
        case 1:
            if ( s00a_command_800CC760( work ) )
            {
                think_noise_inline( work );
                break;
            }
        break;
        case 9:
        if ( Think3_BikkuriGetUp_800CC568( work ) )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;
        case 0:
            if ( Think3_NoiseModeWatch_800CC5C0( work ) )
            {
                if ( ( work->act_status & 0x80 ) )
                {
                    work->think2 = 0;
                    work->think3 = 2;
                }
                else
                {
                    work->modetime[(  T_NOISE  )]++;
                    work->think3 = 9;
                    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL && work->modetime[(  T_NOISE  )] < 2 )
                    {
                        work->pad.mode = 0;
                    }
                    else
                    {
                        work->pad.mode = 1;
                    }

                }
                work->count3 = 0;
            }
            break;
        case 4:
            if ( s00a_command_800CC064( work ) )
            {
                work->think3 = 11;
                work->count3 = 0;
            }

            if ( work-> count3 > 32 )
            {
                if ( work->field_BA1 & 1 && work->modetime[(  T_NOISE  )] < 3 )
                {
                    s00a_command_800CAB74( work );
                    work->think3 = 5;
                    work->count3 = 0;
                }
            }
        break;
        case 6:
            if ( s00a_command_800CCA28( work ) )
            {
                think_reset2( work );
            }
        break;
        case 3:
            if ( s00a_command_800CC7A4( work ) )
            {
                think_reset2( work );
            }
        break;
    }

    if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
    }
    else if ( work->alert_level > 2 )
    {
        s00a_command_800CB240( work );
    }
    else if ( work->field_BA1 & 2 )
    {
        s00a_command_800CB610( work );
    }
    else if ( work->field_BA1 & 16 )
    {
        s00a_command_800CB628( work );
    }
    else if ( work->field_BA1 & 1 )
    {
        if ( GM_NoisePower == 200 || GM_NoisePower == 255 )
        {
            think_noise_inline( work );
        }
    }
}

void s00a_command_800CDB88( WatcherWork *work )
{
    switch ( work->think3 )
    {
        case 5:
            if ( s00a_command_800CC99C( work ) )
            {
                s00a_command_800CB1C4( work );
                work->think3 = 10;
                work->t_count = 0;
                work->pad.mode = 0;
                work->count3 = 0;
            }
        break;
        case 10:
        work->pad.press |= 0x4;
        if ( DirectTrace_800CC154( work , 500 ) )
        {
            if ( s00a_command_800CC294( work ) != 0 )
            {
                s00a_command_800CB1C4( work );
                work->t_count++;
                if ( work->t_count == 12 )
                {
                    work->think3 = 32;
                }
                else
                {
                    work->unknown.field_1E = 0;
                    work->pad.dir = work->control.turn.vy;
                }
                work->count3 = 0;
                break;
            }
            else
            {
                work->think3 = 11;
                CleanAsiato_800D1378();
                work->count3 = 0;
            }
        }
        break;
        case 32:
        if ( s00a_command_800CB770( work ) )
        {
            work->think3  = 10;
            work->t_count = 0;
            work->count3  = 0;
        }
        break;
        case 11:
        if ( s00a_command_800CCA9C ( work ) )
        {
            think_reset2( work );
        }
        break;
    }

    if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
        CleanAsiato_800D1378();
    }
    else if ( work->alert_level > 1 )
    {
        s00a_command_800CB240( work );
        CleanAsiato_800D1378();
    }
    else if ( work->field_BA1 & 2 )
    {
        s00a_command_800CB610( work );
    }
    else if ( work->field_BA1 & 1 )
    {
        s00a_command_800CB504( work );
        CleanAsiato_800D1378();
    }
}

void s00a_command_800CDD80( WatcherWork *work )
{
    switch( work->think3 )
    {
        case 14:
        if ( s00a_command_800CBDFC( work ) )
        {
            s00a_command_800CB2C8( work );
            if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
            {
                work->pad.sound = 240;
            }
            else
            {
                work->pad.sound = 246;
            }
            work->alert_level = 255;
            ENE_SetGopointLast_800CEB00();
        }
        break;
        case 16:
        if ( s00a_command_800CBE90( work ) )
        {
            if ( EnemyCommand_800E0D98.field_0x180 < 2 )
            {
                s00a_command_800CB394( work );
            }
            else
            {
                ENE_SetGopointLast_800CEB00();
                s00a_command_800CB2F4( work );
            }
            work->alert_level = 255;
        }
        break;
        case 17:
        ENE_SetGopointLast_800CEB00();
        s00a_command_800CB258( work );
        work->pad.sound   = 246;
        work->alert_level = 255;
    }
}

void s00a_command_800CDE90( WatcherWork *work ) {
    int res;
    short x;
    x = work->think3 - 21;
    switch ( x )
    {
    case 0:
        if ( s00a_command_800CCC14( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
    case 3:
        if ( s00a_command_800CCCAC( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 4:
        if ( s00a_command_800CCD38( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 5:
        if ( s00a_command_800CCDA0( work ) )
        {
            work->think3 = 27;
            work->count3 = 0;
        }
        break;
     case 6:
        res = Think3_AttackSetup_800CCE08( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }
        break;
    }


    if ( ( ( GV_Time / 4 ) % 4 ) == work->field_B78 % 4 )
    {
        if ( work->field_B7C == 0xFF )
        {
            if ( work->field_C04 != COM_PlayerAddressOne_800E0F40[ work->field_B78 ] )
            {
                if ( work->field_BFC < 0xDAD )
                {
                    if ( (work->field_BFC + 0x3E8) < work->sn_dis || work->vision.field_B92 != 2 )
                    {
                        s00a_command_800CB258( work );
                    }
                }
                else
                {
                    if (  work->field_BFC < work->sn_dis )
                    {
                        s00a_command_800CB258( work );
                    }
                }
            }
        }
        else
        {
            if ( work->vision.field_B92 != 2 )
            {
                if ( work->alert_level != 0xFF )
                {
                    if (!(HZD_8005D134( work->control.map->hzd, &work->control.mov, work->field_B7C )))
                    {
                        s00a_command_800CB258(work);
                    }
                }
            }
        }
    }

    if ( work->vision.field_B92 == 2 )
    {
        ENE_SetGopointLast_800CEB00();
        work->alert_level = 0xFF;
        return;
    }
}

void s00a_command_800CE0B8( WatcherWork *work )
{
    int res;
    switch ( work->think3 )
    {
        case 18:
        s00a_command_800CAB04( work );
        if ( s00a_command_800CC0D4(work) )
        {
            work->think3 = 19;
            work->count3 = 0;
        }
        break;
        case 19:
        s00a_command_800CAB04( work );
        if ( s00a_command_800CC064( work ) )
        {
            work->think3 = 20;
            work->count3 = 0;
        }
        break;
        case 20:
        res = s00a_command_800CCB7C( work );
        if ( res < 0 )
        {
            work->think3 = 19;
            work->count3 = 0;
        }
        else if ( res > 0 )
        {
            s00a_command_800CB2C8( work );
        }
        break;
    }

    if ( work->sn_dis < work->field_BFC )
    {
        if ( ( work->field_BFC >= 0xFA0 ) || ( work->vision.field_B92 == 2 ) )
        {
            s00a_command_800CB2C8( work );
        }
    }

    if ( work->vision.field_B92 == 2 )
    {
        work->alert_level = 255;
    }

    ENE_SetGopointLast_800CEB00();
}

void s00a_command_800CE1E0( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 29:
        if ( s00a_command_800CC0D4( work ) )
        {
            work->think3 = 28;
            work->count3 = 0;
        }
    break;
    case 28:
        if ( ( work->field_B7C != 0xFF ) && (char)work->target_addr != (short)work->field_B7C )
        {
            s00a_command_800CB0E0( work );
        }
        if ( s00a_command_800CC064( work ) )
        {
            if ( EnemyCommand_800E0D98.field_0x40 == 1  || ( work->field_B7C != 0xFF) )
            {
                s00a_command_800CB2C8( work );
            }
            else
            {
                work->think3 = 30;
                work->count3 = 0;
            }
        }
    break;
    case 30:
        if ( EnemyCommand_800E0D98.field_0x40 == 1 )
        {
            s00a_command_800CB2C8( work );
            return;
        }
    break;

    }

    if ( ( work->field_B7C == 0xFF) || EnemyCommand_800E0D98.field_0x40 != 1 )
    {
        if ( work->vision.field_B92 == 2 )
        {
            if ( EnemyCommand_800E0D98.field_0x40 != 1 )
            {
                work->think2 = 7;
                work->think3 = 17;
                work->count3 = 0;
                return;
            }
            work->pad.dir = work->sn_dir;
            s00a_command_800CB2C8( work );
            return;
        }
    }
    else
    {
        if ( work->vision.field_B92 == 2 )
        {
            work->pad.dir = work->sn_dir;
            s00a_command_800CB2C8( work );
            return;
        }
    }
}

void s00a_command_800CE354( WatcherWork* work )
{
    if ( s00a_command_800CC064( work ) )
    {
        work->think2 = 13;
        work->think3 = 34;
        work->think4 = 3;
        work->pad.mode = 0;
        work->count3 = 0;
    }

    if ( work->alert_level > 1 )
    {
        s00a_command_800CB240( work );
    }

    if ( work->field_BA1 & 2 )
    {
        s00a_command_800CB610( work );
    }

    if ( work->field_BA1 & 1 )
    {
        s00a_command_800CB504( work );
    }

    if ( work->field_BA1 & 16 )
    {
        s00a_command_800CB628( work );
        work->pad.mode = 0;
    }
    else if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
        work->pad.mode = 0;
    }
}

void s00a_command_800CE428( WatcherWork* work )
{
    s00a_command_800CAB04( work );

    if ( s00a_command_800CC064( work ) || ( work->sn_dis < ( work->field_BFC + 500 ) ) || GM_AlertLevel < 150 )
    {
        work->think2 = 13;
        work->think3 = 34;
        work->think4 = 0;
        work->pad.mode = 0;
        work->count3 = 0;
    }

    if ( work->alert_level > 1 )
    {
        s00a_command_800CB240( work );
    }

    if ( work->field_BA1 & 2 )
    {
        s00a_command_800CB610( work );
    }

    if ( work->field_BA1 & 1 )
    {
        s00a_command_800CB504( work );
    }

    if ( work->field_BA1 & 16 )
    {
        s00a_command_800CB628( work );
        work->pad.mode = 0;
    }
    else if ( work->field_BA1 & 4 )
    {
        s00a_command_800CB3F0( work );
        work->pad.mode = 0;
    }
}

void s00a_command_800CE530( WatcherWork* work )
{
    switch ( work->think3 )
    {
    case 32:
        s00a_command_800CB7E0( work );
        break;
    case 33:
        s00a_command_800CD000( work );
        break;
    case 34:
        s00a_command_800CD08C( work );
        break;
    }

    if ( work->alert_level > 1 )
    {
        s00a_command_800CB240(work);
    }
    if (work->field_BA1 & 2)
    {
        s00a_command_800CB610(work);
    }
    else if (work->field_BA1 & 1)
    {
        s00a_command_800CB504(work);
    }
    else if (work->field_BA1 & 16 )
    {
        s00a_command_800CB628(work);
    }
    else if (work->field_BA1 & 4)
    {
        s00a_command_800CB3F0(work);
    }
}

void s00a_command_800CE634( WatcherWork *work )
{
    switch( work->think2 )
    {
        case 6:
        s00a_command_800CD158( work );
        break;
        case 0:
        s00a_command_800CD210( work );
        break;
        case 1:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CD8B0( work );
        break;
        case 2:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CD608( work );
        break;
        case 3:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CD470( work );
        break;
        case 4:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CD478( work );
        break;
        case 5:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CDB88( work );
        break;
        case 7:
            work->control.radar_atr |= 0x1000;
            s00a_command_800CDD80( work );
        break;
    }

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        return;
    }

    if ( work->think2 == 7 )
    {
        work->think1 = 1;
    }
    else
    {
        s00a_command_800CB2F4( work );
    }
}

void s00a_command_800CE778( WatcherWork* work )
{
    switch ( work->think2 )
    {
    case 8:
        s00a_command_800CE0B8( work );
        break;
    case 9:
        s00a_command_800CDE90( work );
        break;
    case 10:
        s00a_command_800CE1E0( work );
        break;
    case 7:
        s00a_command_800CDD80( work );
        break;
    }

    if ( EnemyCommand_800E0D98.mode != TOP_COMM_ALERT )
    {
        s00a_command_800CB42C( work );
    }
}

void s00a_command_800CE830( WatcherWork *work )
{
    short x;
    x = work->think2 - 1;
    switch( x )
    {
        case 10:
        s00a_command_800CE354( work );
        break;
        case 11:
        s00a_command_800CE428( work );
        break;
        case 12:
        s00a_command_800CE530( work );
        break;
        case 4:
        s00a_command_800CDB88( work );
        break;
        case 0:
        s00a_command_800CD8B0( work );
        break;
        case 1:
        s00a_command_800CD608( work );
        break;
        case 3:
        s00a_command_800CD478( work );
        break;
        case 6:
        s00a_command_800CDD80( work );
        break;
    }

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_ALERT )
    {
        s00a_command_800CB2F4( work );
    }

    if ( EnemyCommand_800E0D98.mode == TOP_COMM_TRAVEL )
    {
        work->think1 = 0;
        if ( work->think2 != 7 && work->think2 != 4 )
        {
            if ( work->think2 == 2 )
            {
                unsigned short th3 = work->think3;
                if ( ( th3 - 12 ) < 2u )
                {
                    return;
                }
            }

            if ( work->think2 == 5 )
            {
                CleanAsiato_800D1378();
            }

            work->think2 = 6;
            work->think3 = 3;
            work->count3 = 0;
        }
    }
}

void Enemy_Think_800CE99C( WatcherWork* work )
{
    work->pad.dir = -1;
    work->pad.press = 0;
    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT | RADAR_ALL_MAP;

    switch ( work->think1 )
    {
    case 0:
        work->unknown.field_1E = 1;
        s00a_command_800CE634( work );
        break;
    case 1:
        work->unknown.field_1E = 1;
        s00a_command_800CE778( work );
        break;
    case 2:
        work->unknown.field_1E = 1;
        s00a_command_800CE830( work );
        break;
    }
}
