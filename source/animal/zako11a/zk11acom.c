#include "zako.h"

#include <stdio.h>
#include "mts/mts.h"      // for fprintf
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/vibrate.h" // for NewPadVibration

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO11A_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO11A_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO11A_ATTACK_SIZE = {800, 500, 800};
SVECTOR ZAKO11A_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO11A_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO11A_TOUCH_FORCE = {0, 0, 0};
SVECTOR ZAKO11A_NO_POINT = {30000, 30000, 30000};
int     ZAKO11A_EYE_LENGTH = 4000;

SVECTOR SECTION(".bss") ZAKO11A_PlayerPosition;
COMMANDER SECTION(".bss") ZAKO11ACommand;
TOP SECTION(".bss") ZAKO11ATOPCOMMAND;
int SECTION(".bss") ZAKO11A_Unknown;
int SECTION(".bss") ZAKO11A_GameFlag;
int SECTION(".bss") ZAKO11A_PlayerAddress;
int SECTION(".bss") ZAKO11A_PlayerMap;

extern int Rasen_MapSection;

/*---------------------------------------------------------------------------*/

static int SoundPlayTime = 0;
static u_char VibH[] = { 1, 10, 0, 0 };
static u_char VibL[] = { 255, 10, 0, 0 };

/*---------------------------------------------------------------------------*/

int ZAKO11ASetWorkID( Work *work )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( ZAKO11ACommand.watchers[ i ].work == NULL )
        {
            ZAKO11ACommand.watchers[ i ].work = work;
            ZAKO11ACommand.watchers[ i ].field_4 = 2;
            return i;
        }
    }

    return -1;
}

void ZAKO11AResetWorkID( int id )
{
    ZAKO11ACommand.watchers[ id ].work = NULL;
    ZAKO11ACommand.watchers[ id ].field_4 = 1;
}

void ZAKO11ASetTopCommAL( int alert )
{
    ZAKO11ATOPCOMMAND.alert = alert;
}

void ZAKO11ASetTopCommMD( int mode )
{
    ZAKO11ATOPCOMMAND.mode = mode;
}

void ZAKO11ASetGopointLast( void )
{
    ZAKO11ACommand.target_addr = ZAKO11A_PlayerAddress;
    ZAKO11ACommand.target_pos = ZAKO11A_PlayerPosition;
    ZAKO11ACommand.target_map = ZAKO11A_PlayerMap;
}

void ZAKO11ASetGopointNoise( void )
{
    ZAKO11ACommand.target_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKO11ACommand.target_pos = GM_NoisePosition;
    ZAKO11ACommand.target_map = GM_PlayerMap;
}

int ZAKO11AFindRoute( int map, int id )
{
    JDATA *list;
    int i;

    list = &ZAKO11ACommand.jdata;
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
    ZAKO11ACommand.zones[ 0 ] = HZD_Zone1( GM_PlayerAddress );
    ZAKO11ACommand.far_zone = 0;
}

static int GetTime( int mod )
{
    return ZAKO11ACommand.time % mod;
}

static void s11a_800D22D8( int *id )
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

static void s11a_800D232C( int *id )
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

static void s11a_800D2380( int *id )
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

static void s11a_800D2428( int *id )
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

static void s11a_800D2560( int *id )
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
        s11a_800D22D8( &id );
        break;
    case 241:
        s11a_800D232C( &id );
        break;
    case 242:
        s11a_800D2380( &id );
        break;
    case 243:
        AsiatoVoice( &id );
        break;
    case 244:
        s11a_800D2428( &id );
        break;
    case 245:
        ReturnVoice( &id );
        break;
    case 246:
        CallGroupVoice( &id );
        break;
    case 247:
        s11a_800D2560( &id );
        break;
    }

    return id;
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
            ZAKO11ACommand.field_60++;
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
        switch ( ZAKO11ACommand.alert_mode )
        {
        case 0:
            if ( ZAKO11ACommand.field_10C & 0x1 )
            {
                ResetPlayerZone();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;
        case 1:
            if ( ZAKO11ACommand.field_60 < 256 )
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

    if ( comm->alert_level < ZAKO11ATOPCOMMAND.alert )
    {
        comm->alert_level = ZAKO11ATOPCOMMAND.alert;
    }

    ZAKO11ASetTopCommAL( 0 );
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
            GM_AlertModeSet( ALERT_ACTIVE );
            comm->alert_mode = 1;
            GM_SeSet2( 0, 63, SE_ALERT_SIREN );
            ZAKO11ACommand.field_60 = 0;
        }
        break;
    case 1:
        if ( comm->alert_level <= 0 )
        {
            GM_AlertModeSet( ALERT_EVASION );
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
            GM_AlertModeSet( ALERT_OFF );
            comm->alert_mode = 0;
            comm->alert_time = 0;
        }

        if ( comm->alert_level >= 255 )
        {
            comm->alert_level = 255;
            GM_AlertModeSet( ALERT_ACTIVE );
            comm->alert_mode = 1;
            ZAKO11ACommand.field_60 = 0;
        }

        level = comm->alert_time;
        if ( level > 256 ) level = 256;
        if ( level > GM_AlertMax ) GM_AlertMax = level;
        break;
    }

    ZAKO11ATOPCOMMAND.mode = comm->alert_mode;
}

static void UpdateAlert( CommanderWork *work )
{
    int alert, i;

    alert = 0;

    for ( i = 0; i < ZAKO11ACommand.n_watchers; i++ )
    {
        if ( ZAKO11ACommand.watchers[ i ].field_4 == 2 )
        {
            alert = Max( alert, ZAKO11ACommand.watchers[ i ].work->alert_level );
        }
        else if ( ZAKO11ACommand.watchers[ i ].field_4 == 1 )
        {
            UpdateWatcher( &ZAKO11ACommand.watchers[ i ], i );
        }
    }

    SoundSetCom( &ZAKO11ACommand );
    AlertSetCom( alert, &ZAKO11ACommand );
    ChangeAlert( &ZAKO11ACommand );

    ZAKO11ACommand.field_10C = 0;
}

static void UpdatePlayerPosition( void )
{
    ZAKO11A_PlayerPosition = GM_PlayerPosition;
    ZAKO11A_PlayerAddress = GM_PlayerAddress;
    ZAKO11A_PlayerMap = GM_PlayerMap;
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

static int InChaseArea( SVECTOR *vec )
{
    if ( vec->vx <  -8000 || vec->vx > -3000 ||
         vec->vz < -12500 || vec->vz > -6000 )
    {
        return 0;
    }

    return 1;
}

static void UpdateGameFlag( void )
{
    int level, z1, z2, i;

    level = Rasen_MapSection;
    z1 = HZD_Zone1( GM_PlayerAddress );
    z2 = HZD_Zone2( GM_PlayerAddress );

    if ( GM_GameOverTimer != 0 ) return;
    if ( GM_Vitality <= 0 ) return;

    switch ( ZAKO11A_GameFlag )
    {
    case 0:
        if ( z1 == z2 && z1 == 24 && level == 0 )
        {
            GM_EnemyWatchCount++;
            ZAKO11A_GameFlag = 1;

            NewPadVibration( VibH, 1 );
            NewPadVibration( VibL, 2 );
            printf( " FLAG1!!\n" );

            if ( ZAKO11ACommand.start_proc >= 0 )
            {
                GCL_ExecProc( ZAKO11ACommand.start_proc, NULL );
                ZAKO11ACommand.start_proc = -1;
            }
        }

        if ( z1 > 13 && z1 < 24 && level == 0 && GM_NoisePower == 255 && InChaseArea( &GM_NoisePosition ) )
        {
            GM_EnemyWatchCount++;
            ZAKO11A_GameFlag = 1;

            NewPadVibration( VibH, 1 );
            NewPadVibration( VibL, 2 );

            if ( ZAKO11ACommand.start_proc2 >= 0 )
            {
                GCL_ExecProc( ZAKO11ACommand.start_proc2, NULL );
                ZAKO11ACommand.start_proc2 = -1;
            }

            printf( " FLAG1!!\n" );
        }
        break;
    case 1:
        if ( z1 == z2 && z1 == 56 && level == 0 )
        {
            ZAKO11A_GameFlag = 2;
            printf( " FLAG2!!\n" );
        }
        break;
    case 2:
        if ( z1 == z2 && z1 == 68 && level == 0 )
        {
            ZAKO11A_GameFlag = 3;
            printf( " FLAG3!!\n" );
        }
        break;
    case 3:
        if ( z1 == z2 && z1 == 11 && level == 1 )
        {
            ZAKO11A_GameFlag = 4;
            printf( " FLAG4!!\n" );
        }
        break;
    case 4:
        if ( z1 == z2 )
        {
            if ( z1 == 24 && level == 1 )
            {
                ZAKO11A_GameFlag = 5;
                printf( " FLAG5!!\n" );
            }
            else if ( z1 == 10 && level == 1 )
            {
                ZAKO11A_GameFlag = 3;
            }
        }
        break;
    case 5:
        if ( z1 == z2 )
        {
            if ( z1 == 36 && level == 1 )
            {
                ZAKO11A_GameFlag = 6;
                printf( " FLAG6!!\n" );
            }
            else if ( z1 == 10 && level == 1 )
            {
                ZAKO11A_GameFlag = 3;
            }
        }
        break;
    case 6:
        if ( z1 == z2 )
        {
            if ( z1 == 44 && level == 1 )
            {
                ZAKO11A_GameFlag = 7;
                printf( " FLAG7!!\n" );
            }
            else if ( z1 == 10 && level == 1 )
            {
                ZAKO11A_GameFlag = 3;
            }
        }
        break;
    case 7:
        if ( z1 == z2 )
        {
            if ( z1 == 52 && level == 1 )
            {
                ZAKO11A_GameFlag = 8;
                printf( " FLAG8!!\n" );
            }
            else if ( z1 == 10 && level == 1 )
            {
                ZAKO11A_GameFlag = 3;
            }
        }
        break;
    case 8:
        if ( z1 == z2 && z1 == 12 && level == 2 )
        {
            ZAKO11A_GameFlag = 9;
            printf( " FLAG9!!\n" );
        }
        break;
    case 9:
        if ( z1 == z2 && z1 == 40 && level == 2 )
        {
            ZAKO11A_GameFlag = 10;
            printf( " FLAG10!!\n" );
        }
        break;
    case 10:
        if ( ZAKO11ATOPCOMMAND.mode == 0 )
        {
            ZAKO11A_GameFlag = 16;
            ZAKO11ACommand.time2 = 0;
        }

        if ( GM_AlertLevel < 180 )
        {
            if ( ZAKO11ACommand.end_proc >= 0 )
            {
                GCL_ExecProc( ZAKO11ACommand.end_proc, NULL );
                ZAKO11ACommand.end_proc = -1;
            }
        }
        break;
    case 16:
        ZAKO11A_GameFlag = 17;
        for ( i = 0; i < 8; i++ )
        {
            if ( ZAKO11ACommand.watchers[ i ].work != NULL ) ZAKO11A_GameFlag = 16;
        }
        break;
    case 17:
        break;
    }

    ZAKO11ACommand.time2++;
}

static void Act( CommanderWork *work )
{
    UpdateGameFlag();
    UpdatePlayerPosition();
    UpdateAlert( work );

    ZAKO11ACommand.time++;
    if ( ZAKO11A_GameFlag == 17 ) GV_DestroyActor( work );
}

static void Die( CommanderWork *work )
{
    /* do nothing */
}

static void GetResources( CommanderWork *work, int name, int where )
{
    int i;
    char *opt;

    ZAKO11A_GameFlag = 0;
    ZAKO11ACommand.time2 = ZAKO11ACommand.alert_level = ZAKO11ACommand.field_20 = 0;

    for ( i = 0; i < 8; i++ )
    {
        ZAKO11ACommand.watchers[ i ].field_0 = 0;
        ZAKO11ACommand.watchers[ i ].field_4 = 0;
        ZAKO11ACommand.watchers[ i ].field_8 = 0;
        ZAKO11ACommand.watchers[ i ].work = NULL;
    }

    for ( i = 0; i < 8; i++ )
    {
        ZAKO11ACommand.field_40[ i ] = i;
    }

    ZAKO11ACommand.time = 0;
    ZAKO11ACommand.alert_mode = 0;

    ZAKO11ATOPCOMMAND.mode = 0;
    ZAKO11ATOPCOMMAND.alert = 0;

    ZAKO11ACommand.map = GM_GetMap( where );

    opt = GCL_GetOption( 'v' );
    if ( opt )
    {
        ZAKO11ACommand.n_zones = ReadZones( opt, ZAKO11ACommand.zones );
    }
    else
    {
        ZAKO11ACommand.n_zones = 1;
        ZAKO11ACommand.zones[ 0 ] = 0;
    }

    for ( i = 0; i < ZAKO11ACommand.n_zones; i++ )
    {
        fprintf( 1, "zone=%d ", ZAKO11ACommand.zones[ i ] );
    }

    ZAKO11ACommand.far_zone = 0;
    ZAKO11A_Unknown = 0;

    opt = GCL_GetOption( 'j' );
    if ( opt )
    {
        ZAKO11ACommand.jdata.count = ReadMapJdata( opt, &ZAKO11ACommand.jdata );
    }
    else
    {
        ZAKO11ACommand.jdata.count = 1;
        ZAKO11ACommand.jdata.data[ 0 ][ 0 ] = 0;
        ZAKO11ACommand.jdata.data[ 0 ][ 1 ] = 0;
    }

    ZAKO11ACommand.jdata.map = where;

    if ( GCL_GetOption( 'e' ) )
    {
        ZAKO11ACommand.end_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ACommand.end_proc = -1;
    }

    if ( GCL_GetOption( 't' ) )
    {
        ZAKO11ACommand.start_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ACommand.start_proc = -1;
    }

    if ( GCL_GetOption( 'u' ) )
    {
        ZAKO11ACommand.start_proc2 = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ACommand.start_proc2 = -1;
    }

    ZAKO11ACommand.n_watchers = 0;
    opt = GCL_GetOption( 'n' );
    if ( opt ) ZAKO11ACommand.n_watchers = InitWatchers( opt );

    ZAKO11ACommand.field_0 = 0;
    ZAKO11ACommand.field_4 = 0;
    ZAKO11ACommand.field_110 = 0;
}

void *NewZako11ACommander( int name, int where )
{
    CommanderWork *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(CommanderWork) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "zk11acom.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
