#include "zako.h"

#include <stdio.h>
#include "enemy/eyeflash.h"

/*---------------------------------------------------------------------------*/

// rasen.c
extern int Rasen_MapSection;

/*---------------------------------------------------------------------------*/

static SVECTOR s11a_dword_800C3574[] = {
    { 5750, 0, -1000 },
    { 6250, 0, 500 },
    { 5750, 0, 2000 }
};

static PATTERN ActionPattern[ 32 ][ 4 ] = {
    { { 1, 0, 1, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1,  63 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1,  16 }, { 3, 1, 1,  20 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1,  29 }, { 3, 1, 1,  32 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 3, 1, 1,  41 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 3, 1, 1,  47 }, { 3, 1, 1,  49 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 1, 0, 1, 255 } },
    { { 0, 2, 0, 255 }, { 0, 2, 0, 255 }, { 1, 0, 1, 255 }, { 0, 2, 0, 255 } },
    { { 0, 2, 1, 255 }, { 0, 2, 1, 255 }, { 0, 2, 1, 255 }, { 0, 2, 1, 255 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } },
    { { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 }, { 0, 0, 0,   0 } }
};

static SVECTOR TargetSize = {600, 1500, 600};
static SVECTOR TargetForce = {0, 0, 0};
static SVECTOR AttackSize = {500, 500, 500};
static SVECTOR AttackForce = {100, 0, 0};

/* Change zone between map sections */
static int ChangeZone = 87;

int s11a_dword_800C39B0 = 0x0000003D;
int s11a_dword_800C39B4 = 0x0000003E;

/*---------------------------------------------------------------------------*/

void TargetPlayer( Work *work )
{
    work->target_addr = ZAKO11A_PlayerAddress;
    work->target_pos = ZAKO11A_PlayerPosition;
    work->target_map = ZAKO11A_PlayerMap;
}

void TargetNext( Work *work )
{
    HZD_ZON *zone;

    zone = HZD_GetZone( work->control.map->hzd, work->param.next );
    work->target_addr = work->param.next | ( work->param.next << 8 );
    work->target_pos.vx = zone->x;
    work->target_pos.vy = zone->y;
    work->target_pos.vz = zone->z;
    work->target_map = work->start_map;
}

void s11a_800D0408( Work *work )
{
    if ( work->param.next == 255 )
    {
        work->think2 = 1;
        work->think1 = 0;
        work->think3 = 5;
    }
    else
    {
        work->think2 = 3;
        work->think1 = 0;
        work->think3 = 17;
        TargetNext( work );
    }

    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s11a_800D0474( Work *work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s11a_800D0490( Work *work )
{
    TARGET *trg, *attack;
    int life, faint;

    trg = work->target;
    life = work->param.life;
    faint = work->param.faint;

    GM_SetTarget( trg, TARGET_FLAG, ENEMY_SIDE, &TargetSize );
    GM_SetPowerTarget( trg, POWER_DECREASE, -1, life, faint, &TargetForce );
    GM_SetCaptureTarget( trg, -1, faint, NULL, NULL );
    GM_SetC4Target( trg, &work->body.objs->objs[ 1 ].world );

    attack = &work->attack;
    GM_SetTarget( attack, TARGET_POWER, 1, &AttackSize );
    GM_SetPowerTarget( attack, POWER_CONST | POWER_EXPLODE, 5, 0, 0, &AttackForce );
}

int ResetZone0( Work *work )
{
    int zone;

    zone = HZD_Zone1( GM_PlayerAddress );
    if ( work->param.index < 2 || work->gameflag == 10 )
    {
        if ( zone < 14 || zone > 87 )
        {
            zone = 24;
        }
        else if ( zone > 13 && zone < 21 )
        {
            zone += 7;
        }
        else
        {
            zone -= work->param.index + 8;
        }
    }
    else
    {
        zone += 8;
        if ( zone > ChangeZone ) zone -= 12;
    }

    return zone;
}

int ResetZone1( Work *work )
{
    int zone;

    zone = HZD_Zone1( GM_PlayerAddress );
    if ( work->param.index < 2 )
    {
        zone -= 8;
    }
    else
    {
        zone += 8;
    }

    return zone;
}

int ResetZone2( Work *work )
{
    int zone;

    zone = HZD_Zone1( GM_PlayerAddress );
    if ( work->param.index < 2 )
    {
        zone -= 8;
    }
    else
    {
        zone += 8;
    }

    return zone;
}

void ResetZone( Work *work, int mode )
{
    CONTROL *ctrl;
    int reset;
    HZD_ZON *zone;

    ctrl = &work->control;
    reset = 0;

    if ( mode == 1 )
    {
        switch ( Rasen_MapSection )
        {
        case 0:
            reset = ResetZone0( work );
            break;
        case 1:
            reset = ResetZone1( work );
            break;
        case 2:
            reset = ResetZone2( work );
            break;
        }
    }
    else if ( mode == 2 )
    {
        reset = ActionPattern[ work->gameflag ][ work->param.index ].reset;
    }

    printf( ",ID[%d] Flag[%d] RESET ZONE [%d]\n", work->param.index, work->gameflag, reset );

    zone = &ctrl->map->hzd->def->zones[ reset ];
    ctrl->mov.vx = zone->x;
    ctrl->mov.vy = zone->y + 1000;
    ctrl->mov.vz = zone->z;

    work->current_addr = -1;
    work->last_addr = -1;

    if ( ActionPattern[ work->gameflag ][ work->param.index ].field_0 == 3 )
    {
        work->scale = 4323;
    }
    else
    {
        work->scale = 4096;
    }
}

void s11a_800D07C4( Work *work, int mode )
{
    work->field_9E4 = 1;
    GM_ConfigControlAttribute( &work->control, RADAR_VISIBLE | RADAR_SIGHT );
    s11a_800D0490( work );
    ResetZone( work, mode );
}

void s11a_800D0818( Work *work )
{
    CONTROL *control;

    control = &work->control;
    work->field_9E4 = 0;
    GM_ConfigControlAttribute( control, RADAR_OFF );
    control->mov.vx = 30000;
    control->mov.vy = 30000;
    control->mov.vz = 30000;
    work->act.field_04 = 0;
}

int s11a_800D0868( SVECTOR *from, SVECTOR *to )
{
    SVECTOR diff;

    GV_SubVec3( to, from, &diff );
    diff.vy = 0;

    return GV_VecDir2( &diff );
}

int s11a_800D08A0( Work *work )
{
    SVECTOR diff, pos;
    HZD_HDL *hzd;
    int target, current, reach, next;
    HZD_ZON *zone;

    hzd = work->control.map->hzd;
    target = work->target_addr;

    pos = work->control.mov;
    pos.vy -= work->control.height;

    current = work->current_addr = HZD_GetAddress( hzd, &pos, work->current_addr );
    reach = HZD_ReachTo( hzd, current, work->next_addr );
    if ( target != work->last_addr || reach <= 0 )
    {
        work->last_addr = target;
        if ( HZD_ReachTo( hzd, current, target ) < 2 )
        {
            work->next_pos = work->target_pos;
            work->next_addr = target;
            GV_SubVec3( &work->next_pos, &pos, &diff );
            work->pad.dir = GV_VecDir2( &diff );
            return -1;
        }

        next = HZD_Navigate( hzd, current, target, &pos );
        zone = &hzd->def->zones[ next ];
        if ( work->chase_dis == 2000 )
        {
            work->next_pos.vx = zone->x + 250;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z + 250;
        }
        else
        {
            work->next_pos.vx = zone->x;
            work->next_pos.vy = zone->y;
            work->next_pos.vz = zone->z;
        }

        work->next_pos.vx = zone->x;
        work->next_pos.vy = zone->y;
        work->next_pos.vz = zone->z;
        work->next_addr = HZD_Address( next, next );
    }

    GV_SubVec3( &work->next_pos, &pos, &diff );
    return GV_VecDir2( &diff );
}

int s11a_800D0A98( Work *work )
{
    if ( work->count3 == 0 )
    {
        ZAKO11A_PutMark( work, 0 );
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        NewEyeflash( &work->body.objs->objs[ 6 ].world, &work->control.mov, "kirari01", 0 );
    }

    if ( work->count3 >= 0 && work->count3 <= 19 )
    {
        work->pad.press |= 0x20;
        work->count3++;
        return 0;
    }

    return 1;
}

int s11a_800D0B38( Work *work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet( &work->control.mov, 83 );
        ZAKO11A_PutMark( work, 0 );
    }

    if ( work->count3 < 0 || work->count3 > 20 ) return 1;

    work->count3++;
    return 0;
}

int s11a_800D0BA0( Work *work )
{
    work->pad.dir = s11a_800D08A0( work );
    if ( work->pad.dir < 0 ) return 1;

    if ( work->current_addr == work->field_C34 )
    {
        work->count3++;
        if ( work->count3 < 0 || work->count3 > 300 )
        {
            work->current_addr = -1;
            work->last_addr = -1;
            s11a_800D08A0( work );
            work->count3 = 0;
        }
    }
    else
    {
        work->count3 = 1;
    }

    work->field_C34 = work->current_addr;
    return 0;
}

int s11a_800D0C2C( Work *work, int r )
{
    SVECTOR diff;
    int x, z;

    diff.vx = x = work->target_pos.vx - work->control.mov.vx;
    diff.vz = z = work->target_pos.vz - work->control.mov.vz;

    if ( x <= -r || x >= r || z <= -r || z >= r )
    {
        work->pad.dir = GV_VecDir2( &diff );
        work->count3++;
        return 0;
    }

    return 1;

}

int s11a_800D0CB4( Work *work )
{
    TargetPlayer( work );
    if ( work->control.map->index != work->target_map ) return -1;

    if ( work->count3 & 0x10 )
    {
        work->current_addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->current_addr, work->target_addr ) >= 2 ) return -1;
    }

    return s11a_800D0C2C( work, 500 );
}

int s11a_800D0D48( Work *work )
{
    int count;

    count = work->count3;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( count == 0 ) work->count3 = GV_RandU( 4 ) + 4;
    if ( count <= 8 && ( count % 2 ) == 0 ) work->pad.press |= 0x40000;
    if ( count >= 12 ) return 1;

    work->count3++;
    return 0;
}

int s11a_800D0DE8( Work *work )
{
    work->pad.press |= 0x20000;
    if ( work->count3 == 0 ) work->pad.press |= 0x80000;
    if ( work->count3 < 0 || work->count3 > 80 ) return 1;

    switch ( work->param.next )
    {
    case 0:
        work->pad.dir = 1536;
        break;
    case 9:
        work->pad.dir = 2048;
        break;
    case 3:
        work->pad.dir = 2560;
        break;
    case 23:
        work->pad.dir = 3072;
        break;
    case 2:
        work->pad.dir = 3584;
        break;
    case 32:
        work->pad.dir = 0;
        break;
    case 1:
        work->pad.dir = 512;
        break;
    case 6:
        work->pad.dir = 1024;
        break;
    }

    work->count3++;
    return 0;
}

int s11a_800D0EB0( Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 30 )
    {
        work->pad.press |= 0x100000;
        work->field_C04 = s11a_dword_800C3574[ work->param.index ];
    }
    else if ( work->body.is_end )
    {
        return 1;
    }

    work->pad.dir = s11a_800D0868( &work->control.mov, &s11a_dword_800C3574[ work->param.index ] );
    work->count3++;
    return 0;
}

int s11a_800D0F74( Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 0 )
    {
        work->pad.press |= 0x200000;
    }
    else if ( work->field_8FC != 0 || ( work->count3 < 0 || work->count3 > 30 ) )
    {
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s11a_800D0FDC( Work *work )
{
    work->pad.dir = work->sn_dir;
    work->pad.press |= 0x10000;

    if ( work->count3 < 10 )
    {
        if ( !( work->count3 & 2 ) ) work->pad.press |= 0x40000;
    }
    else if ( work->count3 > 19 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}

int s11a_800D103C( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->sn_dis < 1300 )
    {
        work->think3 = 11;
        work->count3 = 0;
        return 0;
    }

    if ( work->sn_dis > 4000 ) return 1;

    work->count3++;
    return 0;
}

int s11a_800D10A0( Work *work )
{
    if ( work->sn_dis < 800 )
    {
        work->pad.press |= 0x10000;
        return 1;
    }

    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}

int s11a_800D10E8( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->count3 == 16 )
    {
        work->count3 += GV_RandU( 14 );
    }

    if ( work->count3 < 0 || work->count3 > 32 )
    {
        switch( ActionPattern[ work->gameflag ][ work->param.index ].field_0 )
        {
        case 0:
            if ( work->sn_dis < 8000 )
            {
                if ( work->sn_dis < 800 && ( GM_PlayerStatus & PLAYER_MOVE ) )
                {
                    return 11;
                }
                else
                {
                    return 7;
                }
            }
            return 15;
        case 2:
            return 8;
        case 4:
            return 14;
        case 3:
            if ( work->sn_dis >= 3900 && work->sn_dis < 8000 )
            {
                return 12;
            }
            else if ( work->sn_dis < 3900 )
            {
                return 13;
            }
            break;
        case 1:
            return 15;
        }
    }

    work->count3++;
    return 0;
}

int s11a_800D1230( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    work->param.next = ActionPattern[ work->gameflag ][ work->param.index ].reset;
    work->scale = 4096;
    if ( work->param.next != 255 ) work->scale += 200;
    return 16;
}

void s11a_800D1298( Work *work )
{
    work->param.next = ActionPattern[ work->gameflag ][ work->param.index ].reset;

    if ( ActionPattern[ 0 ][ work->param.index ].set == 0 )
    {
        s11a_800D0818( work );
        work->think2 = 5;
        work->think3 = 18;
        work->count3 = 0;
        return;
    }
    else
    {
        s11a_800D0408( work );
    }
}

void s11a_800D1328( Work *work )
{
    if ( ActionPattern[ work->gameflag ][ work->param.index ].field_4 == 0 )
    {
        if ( work->gameflag != ZAKO11A_GameFlag ) work->gameflag = ZAKO11A_GameFlag;
        s11a_800D07C4( work, 1 );
        s11a_800D0408( work );
    }
    else if ( work->gameflag == 10 && Rasen_MapSection == 0 )
    {
        s11a_800D07C4( work, 1 );
        s11a_800D0408( work );
        return;
    }
    else
    {
        work->think2 = 5;
        work->think3 = 18;
        work->count3 = 0;
    }
}

void s11a_800D13DC( Work *work )
{
    switch ( work->think3 )
    {
    case 0:
        s11a_800D1298( work );
        break;
    case 1:
        s11a_800D1328( work );
        break;
    }
}

void s11a_800D142C( Work *work )
{
    switch ( work->think3 )
    {
    case 2:
        if ( !s11a_800D0A98( work ) ) break;
        s11a_800D0408( work );

        if ( ZAKO11ACommand.alert_mode != 0 )
        {
            work->pad.sound = 246;
        }
        else
        {
            work->pad.sound = 240;
        }

        work->alert_level = 255;
        break;
    case 3:
        if ( !s11a_800D0B38( work ) ) break;
        work->think1 = 0;
        work->think2 = 3;
        work->think3 = 17;
        work->count3 = 0;
        work->pad.field_4 = 1;
        work->pad.sound = 240;
        work->alert_level = 255;
        break;
    case 4:
        if ( !s11a_800D0B38( work ) ) break;
        s11a_800D0408( work );
        work->pad.sound = 240;
        work->alert_level = 255;
        break;
    }
}

void s11a_800D1524( Work *work )
{
    int think, nextset;

    switch ( work->think3 )
    {
    case 7:
        if ( s11a_800D0D48( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 8:
        if ( s11a_800D0DE8( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 10:
        if ( s11a_800D0EB0( work ) )
        {
            s11a_800D0474( work );
            work->count3 = 0;
        }
        break;
    case 11:
        if ( s11a_800D0F74( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 12:
        if ( s11a_800D0FDC( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 13:
        if ( s11a_800D103C( work ) )
        {
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    case 14:
        if ( s11a_800D10A0( work ) )
        {
            work->think3 = 11;
            work->count3 = 0;
        }
        break;
    case 16:
        think = s11a_800D10E8( work );
        if ( think != 0 )
        {
            work->think3 = think;
            work->count3 = 0;
        }

        if ( work->gameflag == ZAKO11A_GameFlag ) break;

        nextset = ActionPattern[ ZAKO11A_GameFlag ][ work->param.index ].set;
        work->gameflag = ZAKO11A_GameFlag;
        printf( "N [%d] work->gameflag = %d\n", work->param.index, work->gameflag );

        if ( nextset != 0 )
        {
            if ( nextset == 1 )
            {
                ResetZone( work, 2 );
            }

            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        else
        {
            printf( "N GO GRAVEYARD !! \n" );
            work->think2 = 5;
            work->think3 = 19;
            work->count3 = 0;
        }
        break;
    case 15:
        think = s11a_800D1230( work );
        if ( think != 0 )
        {
            work->think3 = think;
            work->count3 = 0;
        }

        if ( work->param.next == 255 )
        {
            if ( work->sn_dis > work->chase_dis || work->vision.pad != 2 )
            {
                s11a_800D0408( work );
            }
        }
        else
        {
            if ( !HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.next ) )
            {
                s11a_800D0408( work );
            }
        }

        if ( work->gameflag == ZAKO11A_GameFlag ) break;

        nextset = ActionPattern[ ZAKO11A_GameFlag ][ work->param.index ].set;
        work->gameflag = ZAKO11A_GameFlag;
        printf( " [%d] work->gameflag = %d\n", work->param.index, work->gameflag );

        if ( nextset != 0 )
        {
            if ( nextset == 1 )
            {
                ResetZone( work, 2 );
            }

            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        else
        {
            printf( " GO GRAVEYARD !! \n" );
            work->think2 = 5;
            work->think3 = 19;
            work->count3 = 0;
        }
        break;
    }

    if ( work->vision.pad == 2 )
    {
        ZAKO11ASetGopointLast();
        work->alert_level = 255;
    }
}

void s11a_800D1804( Work *work )
{
    int temp_v0;

    switch ( work->think3 )
    {
    case 5:
        TargetPlayer( work );
        if ( s11a_800D0BA0( work ) )
        {
            work->think3 = 6;
            work->count3 = 0;
        }
        break;
    case 6:
        temp_v0 = s11a_800D0CB4( work );
        if ( temp_v0 < 0 )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        else if ( temp_v0 > 0 )
        {
            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        break;
    }

    if ( work->sn_dis < work->chase_dis && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 16;
        work->count3 = 33;
        work->pad.press |= 0x10000;
    }

    if ( work->vision.pad == 2 ) work->alert_level = 255;
    ZAKO11ASetGopointLast();
}

void s11a_800D1904( Work *work )
{
    if ( work->think3 == 17 && s11a_800D0BA0( work ) )
    {
        work->think2 = 2;
        work->think3 = 15;
        work->count3 = 0;
    }

    if ( work->sn_dis < 800 && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 11;
        work->count3 = 0;
        work->pad.press |= 0x10000;
    }
}

void s11a_800D1998( Work *work )
{
    switch ( work->think3 )
    {
    case 18:
        if ( work->gameflag != ZAKO11A_GameFlag )
        {
            int nextset;
            work->gameflag = ZAKO11A_GameFlag;
            nextset = ActionPattern[ ZAKO11A_GameFlag ][ work->param.index ].set;

            if ( nextset == 0 ) break;

            if ( nextset == 1 )
            {
                s11a_800D07C4( work, 2 );
                printf( " SET_QUICK !! \n" );
            }

            if ( nextset == 2 )
            {
                s11a_800D07C4( work, 1 );
                printf( " SET_CONTINUE !! \n" );
            }

            work->think2 = 2;
            work->think3 = 15;
            work->count3 = 0;
        }
        else
        {
            s11a_800D0818( work );
        }
        break;
    case 19:
        printf( " SET_NONE !! \n" );
        s11a_800D0818( work );
        work->think3 = 18;
        work->count3 = 0;
        break;
    }
}

void Think1_Phase0( Work *work )
{
    switch ( work->think2 )
    {
    case 0:
        s11a_800D13DC( work );
        break;
    case 1:
        s11a_800D1804( work );
        break;
    case 2:
        s11a_800D1524( work );
        break;
    case 3:
        s11a_800D1904( work );
        break;
    case 4:
        s11a_800D142C( work );
        break;
    case 5:
        s11a_800D1998( work );
        break;
    }
}

/*---------------------------------------------------------------------------*/

void Zako11AThink( Work *work )
{
    work->pad.dir = -1;
    work->pad.press = 0;

    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT;

    if ( ZAKO11A_GameFlag > 0 && ZAKO11A_GameFlag < 10 )
    {
        work->alert_level = 255;
    }
    else if ( work->think3 != 18 && ZAKO11A_GameFlag == 10 )
    {
        work->alert_level = 255;
    }

    switch ( work->think1 )
    {
    case 0:
        work->act.field_1E = 1;
        Think1_Phase0( work );
        break;
    }
}
