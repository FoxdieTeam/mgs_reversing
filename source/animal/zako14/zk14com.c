#include "zako.h"

#include "mts/mts.h" // for fprintf
#include "libgcl/libgcl.h"

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO14_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO14_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO14_ATTACK_SIZE = {800, 500, 800};
SVECTOR ZAKO14_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO14_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO14_TOUCH_FORCE = {0, 0, 0};
SVECTOR ZAKO14_NO_POINT = {30000, 30000, 30000};
int     ZAKO14_EYE_LENGTH = 4000;

COMMANDER SECTION(".bss") ZAKO14Command;
TOP SECTION(".bss") ZAKO14TOPCOMMAND;
int SECTION(".bss") ZAKO14_Unknown;
int SECTION(".bss") ZAKO14_GameFlag;
int SECTION(".bss") ZAKO14_PlayerAddress;
int SECTION(".bss") ZAKO14_PlayerMap;
SVECTOR SECTION(".bss") ZAKO14_PlayerPosition;

/*---------------------------------------------------------------------------*/

static int ChaseDis[] = {
    3000, 4000, 7000, 8000,
    8000, 8000, 8000, 8000,
};

static int SoundPlayTime = 0;

/*---------------------------------------------------------------------------*/

int ZAKO14SetWorkID( Work *work )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( ZAKO14Command.watchers[ i ].work == NULL )
        {
            ZAKO14Command.watchers[ i ].work = work;
            ZAKO14Command.watchers[ i ].field_4 = 2;
            return i;
        }
    }

    return -1;
}

void ZAKO14ResetWorkID( int id )
{
    ZAKO14Command.watchers[ id ].work = NULL;
    ZAKO14Command.watchers[ id ].field_4 = 1;
}

void ZAKO14SetTopCommAL( int alert )
{
    ZAKO14TOPCOMMAND.alert = alert;
}

void ZAKO14SetTopCommMD( int mode )
{
    ZAKO14TOPCOMMAND.mode = mode;
}

void ZAKO14SetGopointLast( void )
{
    ZAKO14Command.target_addr = ZAKO14_PlayerAddress;
    ZAKO14Command.target_pos = ZAKO14_PlayerPosition;
    ZAKO14Command.target_map = ZAKO14_PlayerMap;
}

void ZAKO14SetGopointNoise( void )
{
    ZAKO14Command.target_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKO14Command.target_pos = GM_NoisePosition;
    ZAKO14Command.target_map = GM_PlayerMap;
}

int ZAKO14FindRoute( int map, int id )
{
    JDATA *list;
    int i;

    list = &ZAKO14Command.jdata;
    if ( list->map == map )
    {
        for ( i = 0; i < list->count; i++ )
        {
            if ( list->data[ i ][ 0 ] == id ) return list->data[ i ][ 1 ];
        }

        goto not_found;
    }

    return 0;

not_found:
    return -1;
}

/*---------------------------------------------------------------------------*/

static int ReadMapJdata( char *opt, JDATA *list )
{
    int count;

    count = 0;
    do {
        list->data[ count ][ 0 ] = GCL_StrToInt( GCL_NextStr() );
        list->data[ count ][ 1 ] = GCL_StrToInt( GCL_NextStr() );
        count++;
    } while ( GCL_NextStr() != NULL );

    return count;
}

static int ReadZones( char *opt, short *zones )
{
    int count;
    char *str;

    count = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        *zones = GCL_StrToInt( str );
        zones++;
        count++;
    }

    return count;
}

static void ResetPlayerZone( void )
{
    SVECTOR pos;
    int max, index, i, len;
    HZD_ZON *zone;

    max = 0;
    index = 0;

    for ( i = 0; i < ZAKO14Command.n_zones; i++ )
    {
        zone = &ZAKO14Command.map->hzd->def->zones[ ZAKO14Command.zones[ i ] ];
        pos.vx = zone->x;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = zone->z;

        len = GV_DiffVec3( &pos, &GM_PlayerPosition );
        if ( len > max )
        {
            max = len;
            index = i;
        }
    }

    ZAKO14Command.far_zone = index;
}

static int GetTime( int mod )
{
    return ZAKO14Command.time % mod;
}

static void s14e_800CE43C( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "dareda!!\n" );
        *id = SE_V_ENE_FOUND01;
        break;
    case 1:
        fprintf( 1, "dareda!!\n" );
        *id = SE_V_ENE_FOUND01;
        break;
    }
}

static void s14e_800CE490( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "nanno otoda!!\n" );
        *id = SE_V_ENE_NOISE;
        break;
    case 1:
        fprintf( 1, "nanno otoda!!\n" );
        *id = SE_V_ENE_NOISE;
        break;
    }
}

static void s14e_800CE4E4( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "tadano hakoka\n" );
        *id = SE_V_ENE_JUSTABOX;
        break;
    case 1:
        fprintf( 1, "tadano hakoka\n" );
        *id = SE_V_ENE_JUSTABOX;
        break;
    }
}

static void AsiatoVoice( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "kono asiatoha??\n" );
        *id = SE_V_ENE_FOOTPRINTS;
        break;
    case 1:
        fprintf( 1, "kono asiatoha??\n" );
        *id = SE_V_ENE_FOOTPRINTS;
        break;
    }
}

static void s14e_800CE58C( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "kinoseika !!\n" );
        *id = SE_V_ENE_NOTHING;
        break;
    case 1:
        fprintf( 1, "kinoseika !!\n" );
        *id = SE_V_ENE_NOTHING;
        break;
    }
}

static void CallGroupVoice( int *id )
{
    switch ( GetTime( 3 ) )
    {
    case 0:
        fprintf( 1, "itazo \n" );
        *id = SE_V_ENE_FOUND03;
        break;
    case 1:
        fprintf( 1, "kottida!!\n" );
        *id = SE_V_ENE_FOUND02;
        break;
    case 2:
        fprintf( 1, "kottida!!\n" );
        *id = SE_V_ENE_FOUND02;
        break;
    }
}

static void ReturnVoice( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "haitini modoruzo!!\n" );
        *id = SE_V_ENE_RETURN;
        break;
    case 1:
        fprintf( 1, "haitini modoruzo!!\n" );
        *id = SE_V_ENE_RETURN;
        break;
    }
}

static void s14e_800CE6C4( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *id = SE_V_ENE_FOUND02;
        break;
    case 1:
        *id = SE_DUMMY;
        return;
    }
}

static int GetSoundId( int id )
{
    switch ( id )
    {
    case 240:
        s14e_800CE43C( &id );
        break;
    case 241:
        s14e_800CE490( &id );
        break;
    case 242:
        s14e_800CE4E4( &id );
        break;
    case 243:
        AsiatoVoice( &id );
        break;
    case 244:
        s14e_800CE58C( &id );
        break;
    case 245:
        ReturnVoice( &id );
        break;
    case 246:
        CallGroupVoice( &id );
        break;
    case 247:
        s14e_800CE6C4( &id );
        break;
    }

    return id;
}

static void ChangePrio( COMMANDER *com )
{
    int dis[ 8 ];
    int i, iter, next, tmp;
    Work *work;

    for ( i = 0; i < com->n_watchers; i++ )
    {
        work = com->watchers[ ZAKO14Command.prio[ i ] ].work;
        dis[ i ] = work->sn_dis;
    }

    for ( iter = com->n_watchers - 1; iter >= 0; iter = next )
    {
        next = -1;
        for ( i = 1; i <= iter; i++ )
        {
            if ( dis[ i - 1 ] > dis[ i ] )
            {
                tmp = dis[ i - 1 ];
                dis[ i - 1 ] = dis[ i ];
                dis[ i ] = tmp;

                tmp = ZAKO14Command.prio[ i - 1 ];
                ZAKO14Command.prio[ i - 1 ] = ZAKO14Command.prio[ i ];
                ZAKO14Command.prio[ i ] = tmp;

                next = i - 1;
            }
        }
    }

    for ( i = 0; i < com->n_watchers; i++ )
    {
        work = com->watchers[ ZAKO14Command.prio[ i ] ].work;
        work->chase_dis = ChaseDis[ ZAKO14Command.prio[ i ] ];
    }
}

static void SoundSetCom( COMMANDER *comm )
{
    int id, dist, i;
    Work *work;

    if ( --SoundPlayTime < 0 ) SoundPlayTime = 0;
    if ( SoundPlayTime > 0 ) return;

    id = 0;
    dist = 100000;

    for ( i = 0; i < comm->n_watchers; i++ )
    {
        if ( comm->watchers[ i ].field_4 == 2 )
        {
            work = comm->watchers[ i ].work;
            if ( work->pad.sound != 0 && work->sn_dis < dist )
            {
                id = work->pad.sound;
                dist = work->sn_dis;
            }
            work->pad.sound = 0;
        }
    }

    if ( id != 0 )
    {
        SoundPlayTime = 30;
        GM_SeSet2( 0, 48, GetSoundId( id ) );
    }
}

static void UpdateWatcher( WATCHER *watcher, int index )
{
    switch ( watcher->field_8 )
    {
    case 0:
        if ( watcher->field_4 == 1 )
        {
            watcher->field_8 = 1;
            watcher->field_0 = 1;
            ZAKO14Command.field_60++;
        }
        break;
    case 1:
        if ( --watcher->field_0 <= 0 )
        {
            watcher->field_8 = 2;
            watcher->field_0 = 0;
        }
        break;
    case 2:
        switch ( ZAKO14Command.alert_mode )
        {
        case 0:
            if ( ZAKO14Command.field_10C & 0x1 )
            {
                ResetPlayerZone();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;
        case 1:
            if ( ZAKO14Command.field_60 < 0 )
            {
                ResetPlayerZone();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;
        }
        break;
    }
}

static int Max( int a, int b )
{
    return ( a >= b ) ? a : b;
}

static void AlertSetCom( int alert, COMMANDER *comm )
{
    if ( ( comm->alert_level - alert ) > 4 )
    {
        comm->alert_level -= 4;
    }
    else
    {
        comm->alert_level = alert;
    }

    if ( comm->alert_level < ZAKO14TOPCOMMAND.alert )
    {
        comm->alert_level = ZAKO14TOPCOMMAND.alert;
    }

    ZAKO14SetTopCommAL( 0 );
}

static void ChangeAlert( COMMANDER *comm )
{
    int level;

    switch ( comm->alert_mode )
    {
    case 0:
        if ( comm->alert_level >= 255 )
        {
            comm->alert_level = 255;
            GM_AlertModeSet( 3 );
            comm->alert_mode = 1;
        }
        break;
    case 1:
        if ( comm->alert_level <= 0 )
        {
            GM_AlertModeSet( 2 );
            comm->alert_mode = 2;
            comm->alert_time = 0;
        }

        level = comm->alert_level;
        if ( level > 256 ) level = 256;
        if ( level > GM_AlertMax ) GM_AlertMax = level;
        break;
    case 2:
        if ( --comm->alert_time <= 0 )
        {
            GM_AlertModeSet( 0 );
            comm->alert_mode = 0;
            comm->alert_time = 0;
        }

        if ( comm->alert_level >= 255 )
        {
            comm->alert_level = 255;
            GM_AlertModeSet( 3 );
            comm->alert_mode = 1;
        }

        level = comm->alert_time;
        if ( level > 256 ) level = 256;
        if ( level > GM_AlertMax ) GM_AlertMax = level;
        break;
    }

    ZAKO14TOPCOMMAND.mode = comm->alert_mode;
}

static void UpdateAlert( CommanderWork *work )
{
    int alert, i;

    alert = 0;

    for ( i = 0; i < ZAKO14Command.n_watchers; i++ )
    {
        if ( ZAKO14Command.watchers[ i ].field_4 == 2 )
        {
            alert = Max( alert, ZAKO14Command.watchers[ i ].work->alert_level );
        }
        else if ( ZAKO14Command.watchers[ i ].field_4 == 1 )
        {
            UpdateWatcher( &ZAKO14Command.watchers[ i ], i );
        }
    }

    SoundSetCom( &ZAKO14Command );
    AlertSetCom( alert, &ZAKO14Command );
    ChangeAlert( &ZAKO14Command );
    ChangePrio( &ZAKO14Command );

    ZAKO14Command.field_10C = 0;
}

static void UpdatePlayerPosition( void )
{
    int z1, z2;

    z1 = HZD_Zone1( GM_PlayerAddress );
    z2 = HZD_Zone2( GM_PlayerAddress );
    if ( z1 == z2 && z1 != 255 )
    {
        ZAKO14_PlayerAddress = GM_PlayerAddress;
        ZAKO14_PlayerPosition = GM_PlayerPosition;
        ZAKO14_PlayerMap = GM_PlayerMap;
    }
}

static int InitWatchers( char *opt )
{
    int count, proc;

    count = 0;
    while ( opt != NULL )
    {
        proc = GCL_StrToInt( opt );
        opt = GCL_NextStr();
        GCL_ExecProc( proc, NULL );
        count++;
    }

    return count;
}

static void UpdateGameFlag( void )
{
    int i;

    switch ( ZAKO14_GameFlag )
    {
    case 0:
        if ( ZAKO14Command.time2 > 180 )
        {
            ZAKO14_GameFlag = 1;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 1:
        if ( ZAKO14Command.time2 > 60 )
        {
            ZAKO14_GameFlag = 2;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 2:
        if ( ZAKO14Command.time2 > 90 )
        {
            ZAKO14_GameFlag = 3;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 3:
        if (ZAKO14Command.time2 > 180 )
        {
            ZAKO14_GameFlag = 4;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 4:
        if ( ZAKO14Command.time2 > 60 )
        {
            ZAKO14_GameFlag = 5;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 5:
        if ( ZAKO14Command.time2 > 90 )
        {
            ZAKO14_GameFlag = 6;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 6:
        if ( ZAKO14Command.time2 > 180 )
        {
            ZAKO14_GameFlag = 7;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 7:
        if ( ZAKO14Command.time2 > 60 )
        {
            ZAKO14_GameFlag = 8;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 8:
        if ( ZAKO14Command.time2 > 90 )
        {
            ZAKO14_GameFlag = 9;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 9:
        if ( ZAKO14Command.time2 > 180 )
        {
            ZAKO14_GameFlag = 10;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 10:
        if ( ZAKO14Command.time2 > 60 )
        {
            ZAKO14_GameFlag = 11;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 11:
    case 13:
        if ( ZAKO14Command.time2 > 90 )
        {
            ZAKO14_GameFlag = 0;
            ZAKO14Command.time2 = 0;
        }

        if ( ZAKO14Command.field_60 > 2 )
        {
            ZAKO14_GameFlag = 15;
        }
        break;
    case 15:
        if ( ZAKO14TOPCOMMAND.mode == 0 )
        {
            ZAKO14_GameFlag = 16;
            for ( i = 0; i < 8; i++ )
            {
                if ( ZAKO14Command.watchers[ i ].work != NULL )
                {
                    ZAKO14_GameFlag = 15;
                }
            }
        }

        if ( GM_GameOverTimer == 0 && GM_Vitality > 0 && ZAKO14Command.end_proc >= 0 )
        {
            GCL_ExecProc( ZAKO14Command.end_proc, NULL );
            ZAKO14Command.end_proc = -1;
        }
    case 16:
        break;
    }

    ZAKO14Command.time2++;
}

static void Act( CommanderWork *work )
{
    UpdateGameFlag();
    UpdatePlayerPosition();
    UpdateAlert( work );

    ZAKO14Command.time++;
    if ( ZAKO14_GameFlag == 16 )
    {
        GV_DestroyActor( work );
    }
}

static void Die( CommanderWork *work )
{
    /* do nothing */
}

static void GetResources( CommanderWork *work, int name, int where )
{
    int i;
    char *opt;

    ZAKO14_GameFlag = 0;
    ZAKO14Command.time2 = ZAKO14Command.alert_level = ZAKO14Command.field_20 = 0;

    for ( i = 0; i < 8; i++ )
    {
        ZAKO14Command.watchers[ i ].field_0 = 0;
        ZAKO14Command.watchers[ i ].field_4 = 0;
        ZAKO14Command.watchers[ i ].field_8 = 0;
        ZAKO14Command.watchers[ i ].work = NULL;
    }

    for ( i = 0; i < 8; i++ )
    {
        ZAKO14Command.prio[ i ] = i;
    }

    ZAKO14Command.time = 0;
    ZAKO14Command.alert_mode = 0;

    ZAKO14TOPCOMMAND.mode = 0;
    ZAKO14TOPCOMMAND.alert = 0;

    ZAKO14Command.map = GM_GetMap( where );

    opt = GCL_GetOption( 'v' );
    if ( opt )
    {
        ZAKO14Command.n_zones = ReadZones( opt, ZAKO14Command.zones );
    }
    else
    {
        ZAKO14Command.n_zones = 1;
        ZAKO14Command.zones[ 0 ] = 0;
    }

    ZAKO14Command.far_zone = 0;
    ZAKO14Command.field_60 = 0;
    ZAKO14_Unknown = 0;

    opt = GCL_GetOption( 'j' );
    if ( opt )
    {
        ZAKO14Command.jdata.count = ReadMapJdata( opt, &ZAKO14Command.jdata );
    }
    else
    {
        ZAKO14Command.jdata.count = 1;
        ZAKO14Command.jdata.data[ 0 ][ 0 ] = 0;
        ZAKO14Command.jdata.data[ 0 ][ 1 ] = 0;
    }

    ZAKO14Command.jdata.map = where;

    if ( GCL_GetOption( 'e' ) )
    {
        ZAKO14Command.end_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO14Command.end_proc = -1;
    }

    ZAKO14Command.n_watchers = 0;
    opt = GCL_GetOption( 'n' );
    if ( opt ) ZAKO14Command.n_watchers = InitWatchers( opt );

    ZAKO14Command.field_0 = 0;
    ZAKO14Command.field_4 = 0;
    ZAKO14Command.field_110 = 0;
}

void *NewZako14Commander( int name, int where )
{
    CommanderWork *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(CommanderWork) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "zk14com.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
