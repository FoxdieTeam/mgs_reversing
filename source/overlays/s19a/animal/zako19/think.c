#include "zako.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "enemy/eyeflash.h"     // for NewEyeflash

// enemy/asiato.c
extern void AsiatoPos( int index, SVECTOR *pos );
extern char NearAsiato( void );
extern int  NextAsiato();

/*---------------------------------------------------------------------------*/

unsigned short ZAKO19ThinkProb[4] = { 100, 50, 25, 10 };

unsigned short ZAKO19ThinkTime[8] = { 300, 15, 30, 60, 90, 0, 0, 30000 };

int ZAKO19ThinkAction[32] =
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

/*== protos ==*/
void s19a_800D3A4C( Work* work );
void s19a_800D3A84( Work* work );
void s19a_800D3ACC( Work* work );
void s19a_800D3B48( Work* work );
void s19a_800D3B88( Work* work );
void s19a_800D3BE4( Work* work );
void s19a_800D3C6C( Work *work );
void s19a_800D3CCC( Work* work );
void s19a_800D3CE4( Work* work );
void s19a_800D3CFC( Work *work );
void s19a_800D3D6C( Work *work );
void s19a_800D3DD8( Work* work );
void s19a_800D3E9C( Work* work );
void s19a_800D3EB4( Work* work );
void s19a_800D3F70( Work* work );
void s19a_800D3F88( Work *work );
/* look around: turn left and right in turn */
int s19a_800D3FC0( Work *work );
int s19a_800D4060( Work *work );
int s19a_800D40CC( Work *work );
int s19a_800D40E8( Work *work );
int s19a_800D4124( Work *work );
int s19a_800D43E4( Work* work );
int s19a_800D4438( Work *work );
int s19a_800D4530( Work *work );
int s19a_800D4580( Work *work );
int s19a_800D46B8( Work *work );
int s19a_800D4728( Work *work );
int s19a_800D479C( Work *work );
int s19a_800D480C( Work *work );
int s19a_800D4854( Work *work );
int s19a_800D48D0( Work *work );
int s19a_800D48E0( Work *work );
int s19a_800D48F0( Work  *work);
int s19a_800D4960( Work* work, int a1 );
/* BUG: the comparisons are the wrong way round, this always returns 0 for r > 0 */
int s19a_800D49E8( SVECTOR *pos1, SVECTOR *pos2, int r );
int s19a_800D4A3C( Work *work );
int s19a_800D4A88( Work *work );
int s19a_800D4AF8( Work *work );
int s19a_800D4B4C( Work *work );
int s19a_800D4BE0( Work *work );
int s19a_800D4C7C( Work *work );
int s19a_800D4CD8( Work *work );
int s19a_800D4D3C( Work *work );
int s19a_800D4D98( Work *work );
int s19a_800D4E04( Work *work );
int s19a_800D4F38( Work *work );
int s19a_800D4FB4( Work *work );
void s19a_800D5030( Work *work );
int s19a_800D50B0( Work *work );
int s19a_800D51A4( Work* work );
void s19a_800D5210( Work* work );
int s19a_800D53C0( Work *work );
int s19a_800D5484( Work *work );
int s19a_800D555C( Work *work );
int s19a_800D5624( Work *work );
int s19a_800D57F4( Work *work );
void s19a_800D59B8( Work *work );
void s19a_800D5AB0( Work *work );
void s19a_800D5CB4( Work *work );
void s19a_800D5DAC( Work *work );
int s19a_800D5E58( Work *work );
int s19a_800D5F50( Work *work );
int s19a_800D607C( Work *work );
void s19a_800D61A4( Work *work );
void s19a_800D649C( Work *work );

/*== functions ==*/

void s19a_800D3A4C( Work* work )
{
    work->target_addr = work->field_BE4;
    work->target_pos  = work->start_pos;
    work->target_map  = work->start_map;
}

void s19a_800D3A84( Work* work )
{
    work->target_addr = ZAKO19_PlayerAddress;
    work->target_pos  = ZAKO19_PlayerPosition;
    work->target_map  = ZAKO19_PlayerMap;
}

void s19a_800D3ACC( Work* work )
{
    work->target_addr = HZD_GetAddress( GM_WhereList[0]->map->hzd, &GM_NoisePosition, -1 );
    work->target_pos  = GM_NoisePosition;
    work->target_map  = ZAKO19_PlayerMap;
}

void s19a_800D3B48( Work* work )
{
    work->target_addr = ZAKO19Command.target_addr;
    work->target_pos  = ZAKO19Command.target_pos;
    work->target_map  = ZAKO19Command.target_map;
}

void s19a_800D3B88( Work* work )
{
    HZD_ZON *zone;

    zone = HZD_GetZone( work->control.map->hzd, work->param.next );
    work->target_addr = work->param.next | ( work->param.next << 8 );
    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

void s19a_800D3BE4( Work* work )
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

void s19a_800D3C6C( Work *work )
{
    AsiatoPos( work->modetime[ 4 ], &work->target_pos );
    work->target_addr = HZD_GetAddress( work->control.map->hzd, &work->target_pos, -1 );
    work->target_map = work->control.map->index;
}

void s19a_800D3CCC( Work* work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->field_B4C = 0;
}

void s19a_800D3CE4( Work* work )
{
    work->think2 = 7;
    work->think3 = 11;
    work->count3 = 0;
}

void s19a_800D3CFC( Work *work )
{
    if ( work->param.next == 0xFF )
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
        s19a_800D3B88( work );
    }
    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s19a_800D3D6C( Work *work )
{
    if ( work->param.next == 0xFF )
    {
        s19a_800D3B48( work );
    }
    else
    {
        s19a_800D3B88( work );
    }
    work->think1 = 1;
    work->think2 = 10;
    work->think3 = 23;
    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s19a_800D3DD8( Work* work )
{
    if ( work->param.next != 0xFF )
    {
        if ( !( HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.next ) ) )
        {
            s19a_800D3B88( work );
            work->think1 = 2;
            work->think2 = 11;
            work->count3 = 0;
            work->pad.field_4 = 1;
        }
        else
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 24;
            work->think4 = 2;
            work->count3 = 0;
            work->pad.field_4 = 0;
        }
    }
    else
    {
        if ( work->chase_dis >= 7000 )
        {
            work->think1 = 2;
            work->think2 = 13;
            work->think3 = 24;
            work->think4 = 2;
            work->count3 = 0;
            work->pad.field_4 = 0;
        }
        else
        {
            s19a_800D3B48( work );
            work->think1 = 2;
            work->think2 = 12;
            work->count3 = 0;
            work->pad.field_4 = 1;
        }
    }
}

void s19a_800D3E9C( Work* work )
{
    work->think2 = 4;
    work->think3 = 4;
    work->count3 = 0;
    work->modetime[2] = 0;
}

void s19a_800D3EB4( Work* work )
{
    switch( GM_NoisePower )
    {
    case 5:
        work->think2 = 1;
        work->think3 = 7;
        break;
    case 200:
    case 255:
        s19a_800D3ACC( work );
        ZAKO19SetGopointNoise();
        work->think2 = 7;
        work->think3 = 12;
        break;
    default:
    case 100:
        s19a_800D3ACC( work );
        work->think2 = 1;
        work->think3 = 5;
        work->modetime[( T_NOISE )] = 0;
        break;
    }
    work->count3 = 0;
}

void s19a_800D3F70( Work* work )
{
    work->think2 = 2;
    work->think3 = 5;
    work->count3 = 0;
}

void s19a_800D3F88( Work *work )
{
    work->think2 = 5;
    work->think3 = 5;
    work->modetime[4] = NearAsiato();
    work->count3 = 0;
}

/* look around: turn left and right in turn */
int s19a_800D3FC0( Work *work )
{
    int count;
    int phase;

    count = work->count3;
    phase = count / 30;
    phase += work->param.index;

    if ( phase == 1 || phase == 4 )
    {
        work->pad.press |= 0x2;
    }
    else if ( phase == 2 || phase == 5 )
    {
        work->pad.press |= 0x1;
    }

    if ( count > 90 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4060( Work *work )
{
    int count;

    count = work->count3;
    if ( !( count & 0x1F ) )
    {
        work->field_B58 = GV_RandU( 8 ) << 9;
    }
    else if ( count > 64 )
    {
        return 1;
    }

    work->pad.dir = work->field_B58;
    work->count3++;
    return 0;
}

int s19a_800D40CC( Work *work )
{
    work->count3++;
    work->pad.dir = work->sn_dir;
    return 0;
}

int s19a_800D40E8( Work *work )
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

int s19a_800D4124( Work *work )
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
        temp_addr  = ZAKO19FindRoute( work->control.map->index , work->target_map );
        zone = &hzd->def->zones[ temp_addr ];
        target_pos->vx = zone->x;
        target_pos->vy = zone->y;
        target_pos->vz = zone->z;
        addr = (temp_addr << 8) | temp_addr;
    }

    ctrl = &work->control;
    work->current_addr = HZD_GetAddress( hzd, &ctrl->mov, work->current_addr );
    addr2 = work->current_addr;
    reach = HZD_ReachTo( hzd, addr2, work->next_addr );

    if ( addr != work->last_addr || reach <= 0 )
    {
        work->last_addr = addr;

        if ( HZD_ReachTo( hzd, addr2, addr ) < 2 )
        {
                if ( work->target_map == work->control.map->index )
                {
                        work->next_pos = *target_pos;
                        work->next_addr = addr;

                        GV_SubVec3( &work->next_pos, &ctrl->mov, &svec );

                        work->pad.dir = GV_VecDir2( &svec );
                        return -1;
                }

                addr2 = ZAKO19FindRoute( work->target_map, ctrl->map->index );
                ctrl->map = GM_GetMap( work->target_map );
                zone = &ctrl->map->hzd->def->zones[ addr2 ];
                work->control.mov.vx = zone->x;
                ctrl->mov.vy = zone->y;
                ctrl->mov.vz = zone->z;
                work->current_addr = -1;
                work->last_addr = -1;
                return ctrl->rot.vy;
        }

        addr3 = HZD_Navigate( hzd, addr2, addr, &ctrl->mov );
        zone = &hzd->def->zones[ addr3 ];
        if ( work->chase_dis == 0xFA0 )
        {
            work->next_pos.vx = zone->x + 0xFA;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z + 0xFA;
        } else
        {
            work->next_pos.vx = zone->x;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z;
        }

        work->next_pos.vx = zone->x;
        work->next_pos.vy = zone->y;
        work->next_pos.vz = zone->z;

        temp = addr3 & 0xFF;
        work->next_addr = temp | temp << 8;
    }

    GV_SubVec3( &work->next_pos, &work->control.mov, &svec );
    target_pos = &svec;
    return GV_VecDir2( target_pos );
}

int s19a_800D43E4( Work* work )
{
    if ( work->pad.time )
    {
        work->pad.press |= work->pad.field_8;
        work->pad.time--;
    }

    if ( s19a_800D4960( work, 350 ) )
    {
        return 1;
    }

    return 0;
}

int s19a_800D4438( Work *work )
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

    if ( a2 >= ZAKO19ThinkProb[ a0 ] || work->field_B4C == 1 )
    {
        work->pad.time = 0;
        work->pad.field_8 = 0;
        work->field_B4C = 0;
        return 0;
    }

    if ( con != 0 )
    {
        work->field_B4C = 1;
    }

    time = ( command & 0xE0 ) >> 5;
    work->pad.time = ZAKO19ThinkTime[ time ];
    act = command & 0x1F;
    work->pad.field_8  = ZAKO19ThinkAction[ act ];

    if ( act & 0x10 )
    {
        return 0;
    }

    work->pad.dir = ( ( command & 0x300 ) >> 8 ) * 1024;
    return 1;
}

int s19a_800D4530( Work *work )
{
    if ( work->pad.time )
    {
        work->pad.press |= work->pad.field_8;
        work->pad.time--;
    }
    else if ( !work->action2 )
    {
        return 1;
    }

    return 0;
}

int s19a_800D4580( Work *work )
{
    if ( work->count3 == 0 )
    {
        fprintf( 1, " watch act time = %d \n ", work->modetime[ T_NOISE ] );

        if ( work->modetime[ T_NOISE ] <= 1 )
        {
            work->pad.sound = SE_V_ENE_HUH;
        }

        if ( work->modetime[ T_NOISE ] == 0 )
        {
            ZAKO19_PutMark( work, 5 );
        }

        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    switch ( work->modetime[ T_NOISE ] )
    {
    case 0:
        if ( work->count3 >= 16 )
        {
            work->pad.sound = 241;
            return 1;
        }
        break;
    case 1:
        if ( work->count3 >= 48 )
        {
            return 1;
        }
        break;
    case 2:
        if ( work->count3 >= 48 )
        {
            work->pad.field_4 = 1;
            return 1;
        }
        break;
    case 3:
        work->alert_level = 255;
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D46B8( Work *work )
{
    SVECTOR svec;

    GV_SubVec3( &GM_NoisePosition, &work->control.mov, &svec );
    work->pad.dir = GV_VecDir2( &svec );
    work->pad.press |= 0x20;

    if ( !( work->modetime[ 6 ] & 1 ) )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4728( Work *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.sound = SE_V_ENE_HUH;
        ZAKO19_PutMark( work, 5 );
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

int s19a_800D479C( Work *work )
{
    if ( work->act.motion1 == 0 )
    {
        if ( work->modetime[ 2 ] == 0 )
        {
            work->pad.dir = work->sn_dir;
        }

        if ( ++work->modetime[ 2 ] > 30 )
        {
            return 1;
        }
    }
    else
    {
        work->modetime[ 2 ] = 0;
    }

    work->count3++;
    return 0;
}

int s19a_800D480C( Work *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.sound = SE_V_ENE_HUH;
        ZAKO19_PutMark( work, 5 );
    }

    return s19a_800D3FC0( work ) != 0;
}

int s19a_800D4854( Work *work )
{
    if ( work->count3 == 0 )
    {
        work->pad.sound = SE_V_ENE_HUH;
        ZAKO19_PutMark( work, 4 );
        work->pad.dir = work->sn_dir;
    }
    else
    {
        work->pad.dir = -1;
    }

    if ( work->count3 > 15 )
    {
        work->pad.sound = 243;
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D48D0( Work *work )
{
    SVECTOR unused[2];

    return 1;
}

int s19a_800D48E0( Work *work )
{
    SVECTOR unused[2];

    return 1;
}

int s19a_800D48F0( Work  *work)
{

    short temp_v0;

    if (!(work->count3 & 0x1F)) {

        work->current_addr = -1;
        work->last_addr = -1;
        s19a_800D4124(work);
    }

    temp_v0 = s19a_800D4124(work);
    work->pad.dir = temp_v0;

    if (work->pad.dir < 0) {

        return 1;
    }

    work->count3 += 1;
    return 0;
}

int s19a_800D4960( Work* work, int a1 )
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

/* BUG: the comparisons are the wrong way round, this always returns 0 for r > 0 */
int s19a_800D49E8( SVECTOR *pos1, SVECTOR *pos2, int r )
{
    int dx, dz;

    dx = pos1->vx - pos2->vx;
    dz = pos1->vz - pos2->vz;

    if ( -r < dx || dx < r || -r < dz || dz < r )
    {
        return 0;
    }

    return 1;
}

int s19a_800D4A3C( Work *work )
{
    if ( work->count3 == 20 )
    {
        ZAKO19_PutMark( work, 5 );
        work->pad.sound = 244;
    }

    return s19a_800D3FC0( work ) != 0;
}

int s19a_800D4A88( Work *work )
{
    work->pad.press |= 0x4;

    if ( work->count3 == 20 )
    {
        ZAKO19_PutMark( work, 5 );
        work->pad.sound = 242;
    }

    if ( work->count3 > 120 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4AF8( Work *work )
{
    int next;

    next = NextAsiato( work->control.map->hzd, work->modetime[ 4 ] );

    if ( next >= 0 )
    {
        work->modetime[ 4 ] = next;
        return 1;
    }

    work->modetime[ 4 ] = -1;
    return 0;
}

int s19a_800D4B4C( Work *work )
{
    MAP *map;
    s19a_800D3A84( work );

    map = work->control.map;

    if ( !( map->index == work->target_map ) )
    {
        return -1;
    }

    if ( work->count3 & 16 )
    {
        work->current_addr = HZD_GetAddress( map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->current_addr, work->target_addr ) > 1 )
        {
            return -1;
        }
    }

    return s19a_800D4960( work, 1500 );
}

int s19a_800D4BE0( Work *work )
{
    int count;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    count = work->count3;
    if ( count == 0 )
    {
        work->count3 = GV_RandU( 8 );
    }

    if ( count < 9 && !( count & 1 ) )
    {
        work->pad.press |= 0x40000;
    }

    if ( count >= 12 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4C7C( Work *work )
{
    work->pad.press |= 0x20000;
    work->pad.dir = work->sn_dir;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x80000;
    }
    else if ( work->count3 == 8 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4CD8( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->count3 != 30 )
    {
        if ( work->body.is_end )
        {
            return 1;
        }
    }
    else
    {
        work->pad.press |= 0x100000;
    }

    work->count3++;
    return 0;
}

int s19a_800D4D3C( Work *work )
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
        work->pad.press |= 0x200000;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}


int s19a_800D4D98( Work *work )
{
    int count;

    count = work->count3;
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( count < 10 )
    {
        if ( !( count & 1 ) )
        {
            work->pad.press |= 0x40000;
        }
    }
    else if ( count >= 20 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s19a_800D4E04( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->param.next == 0xFF )
    {
        if ( work->count3 == 16 )
        {
            work->count3 += GV_RandU( 14 );
        }

        if ( work->count3 > 32 && work->sn_dis < 6500 && work->vision.pad == 2 )
        {
            if ( work->sn_dis < 1000 && !( GM_PlayerStatus & ( PLAYER_CB_BOX | PLAYER_GROUND | PLAYER_SQUAT ) ) )
            {
                return 20;
            }

            return 16;
        }
    }
    else if ( work->sn_dis < 6500 && work->vision.pad == 2 && ( work->count3 & 1 ) )
    {
        if ( work->sn_dis < 1000 && !( GM_PlayerStatus & ( PLAYER_CB_BOX | PLAYER_GROUND | PLAYER_SQUAT ) ) )
        {
            return 20;
        }

        return 21;
    }

    work->count3++;
    return 0;
}

int s19a_800D4F38( Work *work )
{
    switch ( work->think4 )
    {
    case 2:
        if ( s19a_800D3FC0( work ) )
        {
            work->think4 = 3;
            work->count3 = 0;
        }
        break;
    case 3:
        if ( s19a_800D4060( work ) )
        {
            work->think4 = 2;
            work->count3 = 0;
        }
        break;
    }

    return 0;
}

int s19a_800D4FB4( Work *work )
{
    switch ( work->think4 )
    {
    case 2:
        if ( s19a_800D3FC0( work ) )
        {
            work->think4 = 0;
            work->count3 = 0;
            s19a_800D3A84( work );
        }
        break;
    case 0:
        if ( s19a_800D48F0( work ) )
        {
            work->think4 = 2;
            work->count3 = 0;
        }
        break;
    }

    return 0;
}

void s19a_800D5030( Work *work )
{
    if ( work->think3 == 3 && s19a_800D40E8( work ) )
    {
        s19a_800D3A4C( work );
        work->next_node = work->n_nodes - 1;
        s19a_800D3CCC( work );
        work->pad.field_4 = 1;
    }

    if ( work->alert_level >= 2 )
    {
        s19a_800D3CE4( work );
    }
}

int s19a_800D50B0( Work *work )
{
    int      i;
    MAP     *map;
    PARAM   *param;
    HZD_PAT *patrol;
    HZD_PTP *points;

    map = GM_GetMap( work->start_map );
    param = &work->param;
    patrol = map->hzd->def->routes;
    patrol = &patrol[ param->root ];

    work->n_nodes = patrol->n_points;

    if ( work->n_nodes <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->n_nodes ; i++ )
    {
        work->nodes[ i ].vx  = points->x;
        work->nodes[ i ].vy  = points->y;
        work->nodes[ i ].vz  = points->z;
        work->nodes[ i ].pad = points->command;
        points++;
    }

    work->start_pos = work->nodes[ 0 ];
    work->field_BE4 = HZD_GetAddress( map->hzd, &work->start_pos, -1 );
    return 0;
}

int s19a_800D51A4( Work* work )
{
    if ( work->param.c_root != ZAKO19Command.field_24 )
    {
        fprintf( 1, " Root Change !!\n" );
        work->param.c_root = ZAKO19Command.field_24;
        s19a_800D50B0( work );
        return 1;
    }

    return 0;
}

void s19a_800D5210( Work* work )
{
    switch ( work->think3 )
    {
    case 0:
        if ( s19a_800D48F0( work ) )
        {
            work->pad.field_4 = 0;
            work->think2 = 0;
            work->think3 = 1;
            s19a_800D3BE4( work );
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s19a_800D43E4( work ) )
        {
            if ( s19a_800D51A4( work ) )
            {
                s19a_800D3A4C( work );
                work->next_node = work->n_nodes - 1;
                s19a_800D3CCC( work );
                work->pad.field_4 = 1;
                return;
            }

            if ( s19a_800D4438( work ) )
            {
                work->think3 = 2;
            }
            else
            {
                s19a_800D3BE4( work );
                work->count3 = 0;
            }
        }
        break;
    case 2:
        if ( s19a_800D4530( work ) )
        {
            s19a_800D3BE4( work );
            work->think3 = 1;
            work->count3 = 0;
        }
        break;
    }

    if ( work->modetime[6] & 4 )
    {
        s19a_800D3E9C( work );
    }
    else if ( work->modetime[6] & 2 )
    {
        s19a_800D3F70( work );
    }
    else if ( work->modetime[6] & 1 )
    {
        s19a_800D3EB4( work );
    }
    else if ( work->modetime[6] & 16 )
    {
        s19a_800D3F88( work );
    }
    else if ( work->alert_level > 2 )
    {
        ZAKO19SetGopointLast();
        s19a_800D3CE4( work );
    }
}

void s19a_800D53B8( Work *work )
{
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D53C0.s")
int s19a_800D53C0( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5484.s")
int s19a_800D5484( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D555C.s")
int s19a_800D555C( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5624.s")
int s19a_800D5624( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D57F4.s")
int s19a_800D57F4( Work *work );

void s19a_800D59B8( Work *work )
{
    switch ( work->think3 )
    {
    case 11:
        if ( s19a_800D48D0( work ) )
        {
            s19a_800D3CFC( work );
            if ( ZAKO19Command.alert_mode == 0 )
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
        if ( s19a_800D48E0( work ) )
        {
            work->think1 = 1;
            work->think2 = 10;
            work->think3 = 23;
            work->pad.field_4 = 1;
            work->pad.sound = 240;
            work->count3 = 0;
            work->alert_level = 255;
        }
        break;
    case 13:
        if ( s19a_800D48E0( work ) )
        {
            s19a_800D3CFC( work );
            work->pad.sound = 240;
            work->alert_level = 255;
        }
        break;
    }
}

void s19a_800D5AB0( Work *work )
{
    int res;
    short x;

    x = work->think3 - 16;
    switch ( x )
    {
    case 0:
        if ( s19a_800D4BE0( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 1:
        if ( s19a_800D4C7C( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 3:
        if ( s19a_800D4CD8( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 4:
        if ( s19a_800D4D3C( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 5:
        if ( s19a_800D4D98( work ) )
        {
            work->think3 = 22;
            work->count3 = 0;
        }
        break;
    case 6:
        res = s19a_800D4E04( work );
        if ( res )
        {
            work->think3 = res;
            work->count3 = 0;
        }
        break;
    }

    if ( ( ZAKO19Command.time / 4 ) % 4 == work->param.index )
    {
        if ( work->param.next == 0xFF )
        {
            if ( work->current_addr != ZAKO19_PlayerAddress )
            {
                if ( work->chase_dis <= 4000 )
                {
                    if ( work->sn_dis > work->chase_dis || work->vision.pad != 2 )
                    {
                        s19a_800D3CFC( work );
                    }
                }
                else if ( work->sn_dis > work->chase_dis )
                {
                    s19a_800D3CFC( work );
                }
            }
        }
        else if ( work->vision.pad != 2 && !HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.next ) )
        {
            s19a_800D3CFC( work );
        }
    }

    if ( work->vision.pad == 2 )
    {
        ZAKO19SetGopointLast();
        work->alert_level = 255;
    }
}

void s19a_800D5CB4( Work *work )
{
    int res;

    switch ( work->think3 )
    {
    case 14:
        s19a_800D3A84( work );
        if ( s19a_800D48F0( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 15:
        res = s19a_800D4B4C( work );
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

    if ( work->sn_dis < work->chase_dis && ( work->chase_dis >= 7000 || work->vision.pad == 2 ) )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }

    if ( work->vision.pad == 2 )
    {
        work->alert_level = 255;
    }

    ZAKO19SetGopointLast();
}

void s19a_800D5DAC( Work *work )
{
    if ( work->think3 == 23 && s19a_800D48F0( work ) )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }

    if ( work->param.next == 0xFF && ( work->modetime[6] & 1 ) )
    {
        ZAKO19SetGopointLast();
        work->think2 = 7;
        work->think3 = 13;
        work->count3 = 0;
    }
    else if ( work->vision.pad == 2 )
    {
        work->think2 = 9;
        work->think3 = 22;
        work->count3 = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5E58.s")
int s19a_800D5E58( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D5F50.s")
int s19a_800D5F50( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D607C.s")
int s19a_800D607C( Work *work );

/* the compiler aligns jump tables to 8 bytes */
const int s19a_pad_800E020C = 0;
const int s19a_jt_800E0210[] = {
    0x800D61F4, 0x800D6204, 0x800D6220, 0x800D623C, 0x800D6258, 0x800D6274, 0x800D61E4, 0x800D6290,
};
const int s19a_jt_800E0230[] = {
    0x800D6418, 0x800D6408, 0x800D6430, 0x800D6428, 0x800D6430, 0x800D6430, 0x800D6430, 0x800D63D8,
    0x800D63E8, 0x800D63F8,
};
#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D61A4.s")
void s19a_800D61A4( Work *work );

#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D649C.s")
void s19a_800D649C( Work *work );

