#include "animal/zako14/zako.h"

#include <stdio.h>
#include "enemy/eyeflash.h"

extern SVECTOR   ZAKO14_PlayerPosition;
extern COMMANDER ZAKO14Command;
extern TOP       ZAKO14TOPCOMMAND;
extern int       ZAKO14_Unknown;
extern int       ZAKO14_GameFlag;
extern int       ZAKO14_PlayerAddress;
extern int       ZAKO14_PlayerMap;

void s14e_800CD764( Work *work );
void s14e_800CD858( Work *work );
void s14e_800CD9DC( Work *work );
void s14e_800CDADC( Work *work );
int  s14e_800CCCC4( Work *work );

static SVECTOR s14e_dword_800C34D8[] = {
    { 5750, 0, -1000 },
    { 6250, 0, 500 },
    { 5750, 0, 2000 }
};

/* Indexed by [work->param.index][ZAKO14_GameFlag] */
static int ActionPatternA[ 4 ][ 16 ] = {
    { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 1, 2, 0, 1, 2, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 1, 2, 0, 0, 1, 0, 0, 1, 0, 1, 2, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

/* Same indexing; only the first byte of each entry is read */
static u_char ActionPatternB[ 4 ][ 16 ][ 4 ] = {
    {
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 32, 0, 0, 0 },
        { 32, 0, 0, 0 },
        { 3, 0, 0, 0 },
        { 9, 0, 0, 0 },
        { 9, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 3, 0, 0, 0 },
        { 23, 0, 0, 0 },
        { 23, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 6, 0, 0, 0 },
        { 6, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 2, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
};

void TargetPlayer( Work *work )
{
    work->target_addr = ZAKO14_PlayerAddress;
    work->target_pos = ZAKO14_PlayerPosition;
    work->target_map = ZAKO14_PlayerMap;
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

void s14e_800CCC04( Work *work )
{
    if ( work->param.next == 255 )
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
        TargetNext( work );
    }

    work->count3 = 0;
    work->pad.field_4 = 1;
}

void s14e_800CCC70( Work *work )
{
    work->think1 = 0;
    work->think2 = 0;
    work->think3 = 0;
    work->count3 = 0;
    work->pad.field_4 = 1;
}

int s14e_800CCC8C( SVECTOR *from, SVECTOR *to )
{
    SVECTOR diff;

    GV_SubVec3( to, from, &diff );
    diff.vy = 0;

    return GV_VecDir2( &diff );
}

#pragma INCLUDE_ASM("asm/overlays/s14e/s14e_800CCCC4.s")
/* cf. zako11a: s11a_800D0A98 */
int s14e_800CCF84( Work *work )
{
    if ( work->count3 == 0 )
    {
        ZAKO14_PutMark( work, 0 );
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

/* cf. zako11a: s11a_800D0B38 */
int s14e_800CD024( Work *work )
{
    if ( work->count3 == 0 )
    {
        GM_SeSet( &work->control.mov, SE_EXCLAMATION );
        ZAKO14_PutMark( work, 0 );
    }

    if ( work->count3 < 0 || work->count3 > 20 ) return 1;

    work->count3++;
    return 0;
}

/* cf. zako11a: s11a_800D0BA0 */
int s14e_800CD08C( Work *work )
{
    if ( !( work->count3 & 0x1F ) )
    {
        work->current_addr = -1;
        work->last_addr = -1;
        s14e_800CCCC4( work );
    }

    work->pad.dir = s14e_800CCCC4( work );
    if ( work->pad.dir < 0 ) return 1;

    work->count3++;
    return 0;
}
/* cf. zako11a: s11a_800D0C2C */
int s14e_800CD0FC( Work *work, int r )
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

/* cf. zako11a: s11a_800D0CB4 */
int s14e_800CD184( Work *work )
{
    TargetPlayer( work );
    if ( work->control.map->index != work->target_map ) return -1;

    if ( work->count3 & 0x10 )
    {
        work->current_addr = HZD_GetAddress( work->control.map->hzd, &work->control.mov, -1 );
        if ( HZD_ReachTo( work->control.map->hzd, work->current_addr, work->target_addr ) >= 2 ) return -1;
    }

    return s14e_800CD0FC( work, 1500 );
}

/* cf. zako11a: s11a_800D0D48 */
int s14e_800CD218( Work *work )
{
    int count;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    count = work->count3;

    if ( count == 0 ) work->count3 = GV_RandU( 8 );
    if ( count <= 8 && ( count & 1 ) == 0 ) work->pad.press |= 0x40000;
    if ( count >= 12 ) return 1;

    work->count3++;
    return 0;
}
/* cf. zako11a: s11a_800D0DE8 */
int s14e_800CD2B4( Work *work )
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

/* cf. zako11a: s11a_800D0EB0 */
int s14e_800CD37C( Work *work )
{
    work->pad.press |= 0x10000;

    if ( work->count3 == 30 )
    {
        work->pad.press |= 0x100000;
        work->field_C04 = s14e_dword_800C34D8[ work->param.index ];
    }
    else if ( work->body.is_end )
    {
        return 1;
    }

    work->pad.dir = s14e_800CCC8C( &work->control.mov, &s14e_dword_800C34D8[ work->param.index ] );
    work->count3++;
    return 0;
}

/* cf. zako11a: s11a_800D0F74 */
int s14e_800CD440( Work *work )
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

/* cf. zako11a: s11a_800D0FDC */
int s14e_800CD4A8( Work *work )
{
    int count;

    count = work->count3;
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( count < 10 )
    {
        if ( !( count & 1 ) ) work->pad.press |= 0x40000;
    }
    else if ( count > 19 )
    {
        return 1;
    }

    work->count3++;
    return 0;
}
/* cf. zako11a: s11a_800D103C */
int s14e_800CD514( Work *work )
{
    if ( work->count3 > 200 ) return 1;

    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;
    work->count3++;
    return 0;
}
/* cf. zako11a: s11a_800D10A0 */
int s14e_800CD55C( Work *work )
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

/* cf. zako11a: s11a_800D10E8 */
int s14e_800CD5A4( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    if ( work->count3 == 16 )
    {
        work->count3 += GV_RandU( 14 );
    }

    if ( work->count3 < 0 || work->count3 > 32 )
    {
        switch ( ActionPatternA[ work->param.index ][ ZAKO14_GameFlag ] )
        {
        case 0:
            if ( work->sn_dis < 800 )
            {
                if ( !( GM_PlayerStatus & ( PLAYER_CB_BOX | PLAYER_GROUND | PLAYER_SQUAT ) ) )
                {
                    return 10;
                }
            }

            return 6;
        case 2:
            return 7;
        case 3:
            return 12;
        case 4:
            return 13;
        case 1:
            return 14;
        }
    }

    work->count3++;
    return 0;
}
/* cf. zako11a: s11a_800D1230 */
int s14e_800CD6C4( Work *work )
{
    work->pad.press |= 0x10000;
    work->pad.dir = work->sn_dir;

    work->param.next = ActionPatternB[ work->param.index ][ ZAKO14_GameFlag ][ 0 ];
    return 15;
}
void s14e_800CD714( Work *work )
{
    s14e_800CCC04( work );
}

/* cf. zako11a: s11a_800D13DC */
void s14e_800CD734( Work *work )
{
    if ( work->think3 == 0 )
    {
        s14e_800CD714( work );
    }
}

/* cf. zako11a: s11a_800D142C */
void s14e_800CD764( Work *work )
{
    switch ( work->think3 )
    {
    case 1:
        if ( !s14e_800CCF84( work ) ) break;
        s14e_800CCC04( work );

        if ( ZAKO14Command.alert_mode != 0 )
        {
            work->pad.sound = 246;
        }
        else
        {
            work->pad.sound = 240;
        }

        work->alert_level = 255;
        break;
    case 2:
        if ( !s14e_800CD024( work ) ) break;
        work->think1 = 0;
        work->think2 = 3;
        work->think3 = 16;
        work->count3 = 0;
        work->pad.field_4 = 1;
        work->pad.sound = 240;
        work->alert_level = 255;
        break;
    case 3:
        if ( !s14e_800CD024( work ) ) break;
        s14e_800CCC04( work );
        work->pad.sound = 240;
        work->alert_level = 255;
        break;
    }
}
/* cf. zako11a: s11a_800D1524 */
void s14e_800CD858( Work *work )
{
    int result;

    switch ( work->think3 )
    {
    case 6:
        if ( s14e_800CD218( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 7:
        if ( s14e_800CD2B4( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 9:
        if ( s14e_800CD37C( work ) )
        {
            s14e_800CCC70( work );
            work->count3 = 0;
        }
        break;
    case 10:
        if ( s14e_800CD440( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 11:
        if ( s14e_800CD4A8( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 12:
        if ( s14e_800CD514( work ) )
        {
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    case 13:
        if ( s14e_800CD55C( work ) )
        {
            work->think3 = 10;
            work->count3 = 0;
        }
        break;
    case 15:
        result = s14e_800CD5A4( work );
        if ( result )
        {
            work->think3 = result;
            work->count3 = 0;
        }
        break;
    case 14:
        result = s14e_800CD6C4( work );
        if ( result )
        {
            work->think3 = result;
            work->count3 = 0;
        }

        if ( !HZD_InsideZone( work->control.map->hzd, &work->control.mov, work->param.next ) )
        {
            s14e_800CCC04( work );
        }
        break;
    }

    if ( work->vision.pad == 2 )
    {
        ZAKO14SetGopointLast();
        work->alert_level = 255;
    }
}
/* cf. zako11a: s11a_800D1804 */
void s14e_800CD9DC( Work *work )
{
    int result;

    switch ( work->think3 )
    {
    case 4:
        TargetPlayer( work );
        if ( s14e_800CD08C( work ) )
        {
            work->think3 = 5;
            work->count3 = 0;
        }
        break;
    case 5:
        result = s14e_800CD184( work );
        if ( result < 0 )
        {
            work->think3 = 4;
            work->count3 = 0;
        }
        else if ( result > 0 )
        {
            work->think2 = 2;
            work->think3 = 14;
            work->count3 = 0;
        }
        break;
    }

    if ( work->sn_dis < 800 && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 10;
        work->count3 = 0;
        work->pad.press |= 0x10000;
        work->pad.dir = work->sn_dir;
    }

    if ( work->vision.pad == 2 ) work->alert_level = 255;
    ZAKO14SetGopointLast();
}
void s14e_800CDADC( Work *work )
{
    if ( work->think3 == 16 && s14e_800CD08C( work ) )
    {
        work->think2 = 2;
        work->think3 = 14;
        work->count3 = 0;
    }

    if ( work->sn_dis < 800 && GM_PlayerStance == STAND )
    {
        work->think2 = 2;
        work->think3 = 10;
        work->count3 = 0;
        work->pad.press |= 0x10000;
        work->pad.dir = work->sn_dir;
    }
}
void s14e_800CDB78( Work *work )
{
    switch ( work->think2 )
    {
    case 0:
        s14e_800CD734( work );
        break;
    case 1:
        s14e_800CD9DC( work );
        break;
    case 2:
        s14e_800CD858( work );
        break;
    case 3:
        s14e_800CDADC( work );
        break;
    case 4:
        s14e_800CD764( work );
        break;
    }
}
void Zako14Think( Work *work )
{
    work->pad.dir = -1;
    work->control.radar_atr = RADAR_VISIBLE | RADAR_SIGHT;
    work->pad.press = 0;
    work->alert_level = 255;

    if ( work->think1 == 0 )
    {
        work->act.field_1E = 1;
        s14e_800CDB78( work );
    }
}
