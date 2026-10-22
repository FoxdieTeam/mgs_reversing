#include "zako10.h"
#include "enemy/eyeflash.h"     // for NewEyeflash

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

extern ZAKO10_COMMAND Zako10Command;
extern int            ZAKO10_GameFlag;
extern int            ZAKO10COM_PlayerAddress;
extern int            ZAKO10COM_PlayerMap;
extern SVECTOR        ZAKO10COM_PlayerPosition;

extern void ZAKO10_PutMark( Zako10Work *work, int mark );
extern int  ZAKO10FindRoute( int map, int id );
extern void ZAKO10_SetGoPointLast( void );
extern void ZAKO10_SetGoPointNoise( void );

// in enemy/asiato.c
extern char NearAsiato( void );

unsigned short Zako10ThinkProb[4] = { 100, 50, 25, 10 };

unsigned short Zako10ThinkTime[8] = { 300, 15, 30, 60, 90, 0, 0, 30000 };

int Zako10ThinkAction[32] =
{
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00000004, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000100, 0x00010000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000001, 0x00000002, 0x00000004,
    0x00000004, 0x00000040, 0x00000080, 0x00000200,
    0x00000400, 0x00000800, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000
};

int  s10a_zk10think_800CCF6C( Zako10Work* work, int a1 );
int  s10a_zk10think_800CD308( Zako10Work *work );
void s10a_zk10think_800CD76C( Zako10Work *work );

/* go back to the start position */
void s10a_zk10think_800CC448( Zako10Work* work )
{
    work->target_addr = work->start_addr;
    work->target_pos  = work->start_pos;
    work->target_map  = work->start_map;
}

void s10a_zk10think_800CC480( Zako10Work* work )
{
    work->target_addr = ZAKO10COM_PlayerAddress;
    work->target_pos  = ZAKO10COM_PlayerPosition;
    work->target_map  = ZAKO10COM_PlayerMap;
}

void s10a_zk10think_800CC4C8( Zako10Work* work )
{
    work->target_addr = HZD_GetAddress( GM_WhereList[0]->map->hzd, &GM_NoisePosition, -1 );
    work->target_pos  = GM_NoisePosition;
    work->target_map  = ZAKO10COM_PlayerMap;
}

void s10a_zk10think_800CC544( Zako10Work* work )
{
    work->target_addr = Zako10Command.com_addr;
    work->target_pos  = Zako10Command.com_pos;
    work->target_map  = Zako10Command.com_map;
}

void s10a_zk10think_800CC584( Zako10Work* work )
{
    HZD_ZON *zone;

    zone = HZD_GetZone( work->control.map->hzd, work->param.field_B7C );
    work->target_addr = work->param.field_B7C | ( work->param.field_B7C << 8 );
    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

void s10a_zk10think_800CC5E0( Zako10Work* work )
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

void s10a_zk10think_800CC668( Zako10Work* work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
}

void s10a_zk10think_800CC680( Zako10Work* work )
{
    work->think2 = 7;
    work->think3 = 11;
    work->count3 = 0;
}

void s10a_zk10think_800CC698( Zako10Work *work )
{
    if ( work->param.field_B7C == 0xFF )
    {
        work->think1 = 1;
        work->think2 = 8;
        work->think3 = 14;
    }
    else
    {
        work->think1 = 1;
        work->think2 = 10;
        work->think3 = 23;
        s10a_zk10think_800CC584( work );
    }
    work->count3 = 0;
    work->pad.mode = 1;
}

void s10a_zk10think_800CC708( Zako10Work *work )
{
    if ( work->param.field_B7C == 0xFF )
    {
        s10a_zk10think_800CC544( work );
    }
    else
    {
        s10a_zk10think_800CC584( work );
    }
    work->think1 = 1;
    work->think2 = 10;
    work->think3 = 23;
    work->count3 = 0;
    work->pad.mode = 1;
}

void s10a_zk10think_800CC774( Zako10Work* work )
{
    if ( work->param.field_B7C != 0xFF )
    {
        if ( !( HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.field_B7C ) ) )
        {
            s10a_zk10think_800CC584( work );
            work->think1 = 2;
            work->think2 = 11;
            work->count3 = 0;
            work->pad.mode = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 24;
            work->think4 = 2;
            work->count3 = 0;
            work->pad.mode = 0;
        }
    }
    else
    {
        if ( work->field_BF8 >= 7000 )
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 24;
            work->think4 = 2;
            work->count3 = 0;
            work->pad.mode = 0;
        }
        else
        {
            s10a_zk10think_800CC544( work );
            work->think1 = 2;
            work->think2 = 12;
            work->count3 = 0;
            work->pad.mode = 1;
        }
    }
}

void s10a_zk10think_800CC838( Zako10Work* work )
{
    work->think2 = 4;
    work->think3 = 4;
    work->count3 = 0;
    work->modetime[2] = 0;
}

void s10a_zk10think_800CC850( Zako10Work* work )
{
    switch( GM_NoisePower )
    {
    case 5:
        work->think2 = 1;
        work->think3 = 7;
        break;
    case 200:
    case 255:
        s10a_zk10think_800CC4C8( work );
        ZAKO10_SetGoPointNoise();
        work->think2 = 7;
        work->think3 = 12;
        break;
    default:
    case 100:
        s10a_zk10think_800CC4C8( work );
        work->think2 = 1;
        work->think3 = 5;
        work->modetime[( T_NOISE )] = 0;
        break;
    }
    work->count3 = 0;
}

void s10a_zk10think_800CC90C( Zako10Work* work )
{
    work->think2 = 2;
    work->think3 = 5;
    work->count3 = 0;
}

void s10a_zk10think_800CC924( Zako10Work *work )
{
    work->think2 = 5;
    work->think3 = 5;
    work->modetime[4] = NearAsiato();
    work->count3 = 0;
}

int s10a_zk10think_800CC95C( Zako10Work *work )
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

int s10a_zk10think_800CC998( Zako10Work *work )
{
    int temp;
    int temp_addr;
    SVECTOR svec;
    CONTROL *ctrl;
    HZD_HDL *hzd;
    HZD_ZON *zone;
    int addr, addr2, addr3;
    int reach;
    SVECTOR *target_pos;

    hzd = work->control.map->hzd;

    if ( work->target_map == work->control.map->index )
    {
        target_pos = &work->target_pos;
        addr = work->target_addr;
    }
    else
    {
        target_pos = &work->target_pos;
        temp_addr  = ZAKO10FindRoute( work->control.map->index , work->target_map );
        zone = &hzd->def->zones[ temp_addr ];
        target_pos->vx = zone->x;
        target_pos->vy = zone->y;
        target_pos->vz = zone->z;
        addr = (temp_addr << 8) | temp_addr;
    }

    ctrl = &work->control;
    work->field_C08 = HZD_GetAddress( hzd, &ctrl->mov, work->field_C08 );
    addr2 = work->field_C08;
    reach = HZD_ReachTo( hzd, addr2, work->field_C0C );

    if ( addr != work->field_BEC || reach <= 0 )
    {
        work->field_BEC = addr;

        if ( HZD_ReachTo( hzd, addr2, addr ) < 2 )
        {
                if ( work->target_map == work->control.map->index )
                {
                        work->field_C18 = *target_pos;
                        work->field_C0C = addr;

                        GV_SubVec3( &work->field_C18, &ctrl->mov, &svec );

                        work->pad.dir = GV_VecDir2( &svec );
                        return -1;
                }

                addr2 = ZAKO10FindRoute( work->target_map, ctrl->map->index );
                ctrl->map = GM_GetMap( work->target_map );
                zone = &ctrl->map->hzd->def->zones[ addr2 ];
                work->control.mov.vx = zone->x;
                ctrl->mov.vy = zone->y;
                ctrl->mov.vz = zone->z;
                work->field_C08 = -1;
                work->field_BEC = -1;
                return ctrl->rot.vy;
        }

        addr3 = HZD_Navigate( hzd, addr2, addr, &ctrl->mov );
        zone = &hzd->def->zones[ addr3 ];
        if ( work->field_BF8 == 0xFA0 )
        {
            work->field_C18.vx = zone->x + 0xFA;
            work->field_C18.vy = zone->y;
            work->field_C18.vz = zone->z + 0xFA;
        } else
        {
            work->field_C18.vx = zone->x;
            work->field_C18.vy = zone->y;
            work->field_C18.vz = zone->z;
        }

        work->field_C18.vx = zone->x;
        work->field_C18.vy = zone->y;
        work->field_C18.vz = zone->z;

        temp = addr3 & 0xFF;
        work->field_C0C = temp | temp << 8;
    }

    GV_SubVec3( &work->field_C18, &work->control.mov, &svec );
    target_pos = &svec;
    return GV_VecDir2( target_pos );
}

int s10a_zk10think_800CCC58( Zako10Work* work )
{
    if ( work->pad.time )
    {
        work->pad.press |= work->pad.tmp;
        work->pad.time--;
    }

    if ( s10a_zk10think_800CCF6C( work, 350 ) )
    {
        return 1;
    }

    return 0;
}

int s10a_zk10think_800CCCAC( Zako10Work *work )
{
    int a2;
    int a0, con;
    int act, time;
    int command;

    //   |con |dir|tim| act   //
    //000|0 00|00 |000|0 0000//
    command = work->target_pos.pad;
    con = ( command & 0x1C00 ) >> 10;

    a2  = GV_RandU( 100 );
    a0  = con & 3;
    con = con & 4;

    if ( a2 >= Zako10ThinkProb[ a0 ] || work->field_B4C == 1 )
    {
        work->pad.time = 0;
        work->pad.tmp = 0;
        work->field_B4C = 0;
        return 0;
    }

    if ( con != 0 )
    {
        work->field_B4C = 1;
    }

    time = ( command & 0xE0 ) >> 5;
    work->pad.time = Zako10ThinkTime[ time ];
    act = command & 0x1F;
    work->pad.tmp  = Zako10ThinkAction[ act ];

    if ( act & 0x10 )
    {
        return 0;
    }

    work->pad.dir = ( ( command & 0x300 ) >> 8 ) * 1024;
    return 1;
}

int s10a_zk10think_800CCDA4( Zako10Work *work )
{
    if ( work->pad.time )
    {
        work->pad.press |= work->pad.tmp;
        work->pad.time--;
    }
    else if ( !work->action2 )
    {
        return 1;
    }

    return 0;
}

int s10a_zk10think_800CCDF4( Zako10Work* work )
{
    if ( work->count3 == 0 )
    {
        ZAKO10_PutMark( work, 0 );
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        NewEyeflash( &work->body.objs->objs[6].world, &work->control.mov, "kirari01", 0 );
    }

    if ( work->count3 < 20 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;
}

int s10a_zk10think_800CCE94( Zako10Work* work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        ZAKO10_PutMark( work, 0 );
    }

    if ( work->count3 > 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s10a_zk10think_800CCEFC( Zako10Work  *work)
{

    short temp_v0;

    if (!(work->count3 & 0x1F)) {

        work->field_C08 = -1;
        work->field_BEC = -1;
        s10a_zk10think_800CC998(work);
    }

    temp_v0 = s10a_zk10think_800CC998(work);
    work->pad.dir = temp_v0;

    if (work->pad.dir < 0) {

        return 1;
    }

    work->count3 += 1;
    return 0;
}

int s10a_zk10think_800CCF6C( Zako10Work* work, int a1 )
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

int s10a_zk10think_800CCFF4( Zako10Work *work )
{
    MAP *map;
    s10a_zk10think_800CC480( work );

    map = work->control.map;

    if ( !( map->index == work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->field_C08 = HZD_GetAddress( map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->field_C08, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return s10a_zk10think_800CCF6C( work, 1500 );
}

int s10a_zk10think_800CD088( Zako10Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x40000;
    }
    else
    {
        if ( work->count3 == 4 )
        {
            return 1;
        }
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s10a_zk10think_800CD0E0( Zako10Work *work )
{
    work->pad.press |= 0x20000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x80000;
    }
    else
    {
        if ( work->count3 == 8 )
        {
            return 1;
        }
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s10a_zk10think_800CD138( Zako10Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 != 30)
    {
        if (work->body.is_end != 0)
        {
            return 1;
        }
    }
    else
    {
        work->pad.press |= 0x100000;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s10a_zk10think_800CD198( Zako10Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 != 0)
    {
        if (work->body.is_end != 0)
        {
            return 1;
        }
    }
    else
    {
        work->pad.press |= 0x40000;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s10a_zk10think_800CD1F4( Zako10Work *work )
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

int s10a_zk10think_800CD25C( Zako10Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

void s10a_zk10think_800CD288( Zako10Work *work )
{
    if ( work->think3 == 3 && s10a_zk10think_800CC95C( work ) )
    {
        s10a_zk10think_800CC448( work );
        work->next_node = work->n_nodes - 1;
        s10a_zk10think_800CC668( work );
        work->pad.mode = 1;
    }

    if ( work->alert_level >= 2 )
    {
        s10a_zk10think_800CC680( work );
    }
}

int s10a_zk10think_800CD308( Zako10Work *work )
{
    int i;
    MAP *map;
    PARAM *param;
    HZD_PAT *patrol;
    HZD_PTP *points;

    map = GM_GetMap( work->start_map );
    param = &work->param;
    patrol = map->hzd->def->routes;
    patrol = &patrol[ param->root ];

    fprintf( 1, "c_root= %d root %d pat %d n_points = %d \n", param->c_root, param->root, (int)patrol, patrol->n_points );

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
        fprintf( 1, "action = 0x%x \n", work->nodes[i].pad );
    }

    work->start_pos = work->nodes[0];
    work->start_addr = HZD_GetAddress( map->hzd, &work->start_pos, -1 );
    return 0;
}

int s10a_zk10think_800CD460( Zako10Work* work )
{
    if ( work->param.c_root != Zako10Command.c_root )
    {
        fprintf( 1, " Root Change !!\n" );
        work->param.c_root = Zako10Command.c_root;
        s10a_zk10think_800CD308( work );
        return 1;
    }

    return 0;
}

void s10a_zk10think_800CD4CC( Zako10Work* work )
{
    switch ( work->think3 )
    {
    case 0:
        if ( s10a_zk10think_800CCEFC( work ) )
        {
            work->pad.mode = 0;
            work->think2 = 0;
            work->think3 = 1;
            s10a_zk10think_800CC5E0( work );
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s10a_zk10think_800CCC58( work ) )
        {
            if ( s10a_zk10think_800CD460( work ) )
            {
                s10a_zk10think_800CC448( work );
                work->next_node = work->n_nodes - 1;
                s10a_zk10think_800CC668( work );
                work->pad.mode = 1;
                return;
            }

            if ( s10a_zk10think_800CCCAC( work ) )
            {
                work->think3 = 2;
            }
            else
            {
                s10a_zk10think_800CC5E0( work );
                work->count3 = 0;
            }
        }
        break;
    case 2:
        if ( s10a_zk10think_800CCDA4( work ) )
        {
            s10a_zk10think_800CC5E0( work );
            work->think3 = 1;
            work->count3 = 0;
        }
        break;
    }

    if ( work->modetime[6] & 4 )
    {
        s10a_zk10think_800CC838( work );
    }
    else if ( work->modetime[6] & 2 )
    {
        s10a_zk10think_800CC90C( work );
    }
    else if ( work->modetime[6] & 1 )
    {
        s10a_zk10think_800CC850( work );
    }
    else if ( work->modetime[6] & 16 )
    {
        s10a_zk10think_800CC924( work );
    }
    else if ( work->alert_level > 2 )
    {
        ZAKO10_SetGoPointLast();
        s10a_zk10think_800CC680( work );
    }
}

void s10a_zk10think_800CD674( Zako10Work *work )
{
    switch ( work->think3 )
    {
    case 11:
        if ( s10a_zk10think_800CCDF4( work ) )
        {
            s10a_zk10think_800CC698( work );
            if ( Zako10Command.mode == TOP_COMM_TRAVEL )
            {
                work->pad.sound = 240;
            }
            else
            {
                work->pad.sound = 246;
            }
            work->alert_level = 255;
        }
        break;
    case 12:
        if ( s10a_zk10think_800CCE94( work ) )
        {
            work->think1 = 1;
            work->think2 = 10;
            work->think3 = 23;
            work->pad.mode = 1;
            work->pad.sound = 240;
            work->count3 = 0;
            work->alert_level = 255;
        }
        break;
    case 13:
        if ( s10a_zk10think_800CCE94( work ) )
        {
            s10a_zk10think_800CC698( work );
            work->pad.sound = 240;
            work->alert_level = 255;
        }
        break;
    }
}

void s10a_zk10think_800CD76C( Zako10Work *work )
{
    int res;
    short x;

    x = work->think3 - 16;
    switch ( x )
    {
    case 0:
        if ( s10a_zk10think_800CD088( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s10a_zk10think_800CD0E0( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 3:
        if ( s10a_zk10think_800CD138( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 4:
        if ( s10a_zk10think_800CD198( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 5:
        if ( s10a_zk10think_800CD1F4( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 6:
        res = s10a_zk10think_800CD25C( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }
        break;
    }

    if ( ( Zako10Command.counter / 4 ) % 4 == work->param.index )
    {
        if ( work->param.field_B7C == 0xFF )
        {
            if ( work->field_C08 != ZAKO10COM_PlayerAddress )
            {
                if ( work->field_BF8 <= 4000 )
                {
                    if ( work->sn_dis > work->field_BF8 || work->vision.field_B92 != 2 )
                    {
                        s10a_zk10think_800CC698( work );
                    }
                }
                else if ( work->sn_dis > work->field_BF8 )
                {
                    s10a_zk10think_800CC698( work );
                }
            }
        }
        else if ( work->vision.field_B92 != 2 && !HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.field_B7C ) )
        {
            s10a_zk10think_800CC698( work );
        }
    }

    if ( work->vision.field_B92 == 2 )
    {
        ZAKO10_SetGoPointLast();
        work->alert_level = 255;
    }
}

void s10a_zk10think_800CD970( Zako10Work *work )
{
    int res;

    switch ( work->think3 )
    {
    case 14:
        s10a_zk10think_800CC480( work );
        if ( s10a_zk10think_800CCEFC( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 15:
        res = s10a_zk10think_800CCFF4( work );
        if ( res < 0 )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        else if ( res > 0 )
        {
            work->think2 = 9;
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    }

    if ( work->sn_dis < work->field_BF8 && ( work->field_BF8 >= 7000 || work->vision.field_B92 == 2 ) )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }

    if ( work->vision.field_B92 == 2 )
    {
        work->alert_level = 255;
    }

    ZAKO10_SetGoPointLast();
}

void s10a_zk10think_800CDA68( Zako10Work *work )
{
    if ( work->think3 == 23 && s10a_zk10think_800CCEFC( work ) )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }

    if ( work->param.field_B7C == 0xFF && ( work->modetime[6] & 1 ) )
    {
        ZAKO10_SetGoPointLast();
        work->think2 = 7;
        work->think3 = 13;
        work->count3 = 0;
    }
    else if ( work->vision.field_B92 == 2 )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }
}

void s10a_zk10think_800CDB14( Zako10Work *work )
{
    switch ( work->think2 )
    {
    case 6:
        s10a_zk10think_800CD288( work );
        break;
    case 0:
        s10a_zk10think_800CD4CC( work );
        break;
    case 7:
        work->control.radar_atr |= RADAR_UNK4;
        s10a_zk10think_800CD674( work );
        break;
    }

    if ( Zako10Command.mode != TOP_COMM_TRAVEL )
    {
        s10a_zk10think_800CC708( work );
    }
}

void s10a_zk10think_800CDBBC( Zako10Work *work )
{
    switch ( work->think2 )
    {
    case 8:
        s10a_zk10think_800CD970( work );
        break;
    case 9:
        s10a_zk10think_800CD76C( work );
        break;
    case 10:
        s10a_zk10think_800CDA68( work );
        break;
    case 7:
        s10a_zk10think_800CD674( work );
        break;
    }

    if ( Zako10Command.mode != TOP_COMM_ALERT )
    {
        s10a_zk10think_800CC774( work );
    }
}

void Zako10Think( Zako10Work *work )
{
    work->pad.dir   = -1;
    work->pad.press =  0;

    switch ( work->think1 )
    {
    case 0:
        work->unknown.field_1E = 1;
        s10a_zk10think_800CDB14( work );
        break;
    case 1:
        work->unknown.field_1E = 1;
        s10a_zk10think_800CDBBC( work );
        break;
    }

    if ( ZAKO10_GameFlag > 0 )
    {
        work->alert_level = 255;
        return;
    }

    work->alert_level = 0;
    work->control.radar_atr = RADAR_OFF;
}
