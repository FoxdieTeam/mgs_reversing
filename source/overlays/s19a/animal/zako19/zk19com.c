#include "zako.h"

#include <stdio.h>
#include "mts/mts.h"      // for fprintf
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO19_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO19_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO19_ATTACK_SIZE = {800, 500, 800};
SVECTOR ZAKO19_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO19_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO19_TOUCH_FORCE = {0, 0, 0};
SVECTOR ZAKO19_NO_POINT = {30000, 30000, 30000};
int     ZAKO19_EYE_LENGTH = 4000;

/* chase distance by order of the distance to snake */
static int chase_dist[] = {
    3000, 4000, 7000, 8000, 8000, 8000, 8000, 8000,
};

static int SoundPlayTime = 0;

SVECTOR   SECTION(".bss") ZAKO19_unk_800E0CC0;
COMMANDER SECTION(".bss") ZAKO19Command;
TOP       SECTION(".bss") ZAKO19TOPCOMMAND;
int       SECTION(".bss") ZAKO19_Unknown;
int       SECTION(".bss") ZAKO19_GameFlag;
int       SECTION(".bss") ZAKO19_PlayerAddress;
int       SECTION(".bss") ZAKO19_PlayerMap;
SVECTOR   SECTION(".bss") ZAKO19_PlayerPosition;

extern void *NewAsiato( void );

/*---------------------------------------------------------------------------*/

int ZAKO19SetWorkID( Work *work )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( ZAKO19Command.watchers[ i ].work == NULL )
        {
            ZAKO19Command.watchers[ i ].work = work;
            ZAKO19Command.watchers[ i ].field_4 = 2;
            return i;
        }
    }

    return -1;
}

void ZAKO19ResetWorkID( int id )
{
    ZAKO19Command.watchers[ id ].work = NULL;
    ZAKO19Command.watchers[ id ].field_4 = 1;
}

void ZAKO19SetTopCommAL( int alert )
{
    ZAKO19TOPCOMMAND.alert = alert;
}

void ZAKO19SetTopCommMD( int mode )
{
    ZAKO19TOPCOMMAND.mode = mode;
}

void ZAKO19SetGopointLast( void )
{
    ZAKO19Command.target_addr = ZAKO19_PlayerAddress;
    ZAKO19Command.target_pos = ZAKO19_PlayerPosition;
    ZAKO19Command.target_map = ZAKO19_PlayerMap;
}

void ZAKO19SetGopointNoise( void )
{
    ZAKO19Command.target_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKO19Command.target_pos = GM_NoisePosition;
    ZAKO19Command.target_map = GM_PlayerMap;
}

int ZAKO19FindRoute( int map, int id )
{
    JDATA *list;
    int i;

    list = &ZAKO19Command.jdata;
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

int ReadMapJdata( char *opt, JDATA *list )
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

int ReadZones( char *opt, short *zones )
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

/* find the zone that is the farthest from snake */
static void SetFarZone( void )
{
    int      i;
    int      dist;
    int      max;
    int      far;
    HZD_ZON *zone;
    SVECTOR  pos;

    i = max = far = 0;

    for ( ; i < ZAKO19Command.n_zones; i++ )
    {
        zone = &ZAKO19Command.map->hzd->def->zones[ ZAKO19Command.zones[ i ] ];

        pos.vx = zone->x;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = zone->z;

        dist = GV_DiffVec3( &pos, &GM_PlayerPosition );
        if ( max < dist )
        {
            max = dist;
            far = i;
        }
    }

    ZAKO19Command.far_zone = far;
}

static int GetTime( int mod )
{
    return ZAKO19Command.time % mod;
}

static void FoundVoice( int *id )
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

static void NoiseVoice( int *id )
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

static void BoxVoice( int *id )
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

static void NothingVoice( int *id )
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
        return;
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

static void HereVoice( int *id )
{
    switch ( GetTime( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *id = SE_V_ENE_FOUND02;
        return;
    case 1:
        *id = 0;
        return;
    }
}

static int GetSoundId( int id )
{
    switch ( id )
    {
    case 240:
        FoundVoice( &id );
        break;
    case 241:
        NoiseVoice( &id );
        break;
    case 242:
        BoxVoice( &id );
        break;
    case 243:
        AsiatoVoice( &id );
        break;
    case 244:
        NothingVoice( &id );
        break;
    case 245:
        ReturnVoice( &id );
        break;
    case 246:
        CallGroupVoice( &id );
        break;
    case 247:
        HereVoice( &id );
        break;
    }

    return id;
}

/* sort the soldiers by their distance to snake and set their chase distance */
static void SortChaseDist( COMMANDER *comm )
{
    int   i;
    int   t2;
    int   last;
    int   next;
    int   dists[ 8 ];
    int   temp1, temp2;
    int   temp3, temp4;
    Work *work;

    for ( i = 0; i < comm->n_watchers; i++ )
    {
        work = comm->watchers[ ZAKO19Command.field_44[ i ] ].work;
        dists[ i ] = work->sn_dis;
    }

    for ( last = comm->n_watchers - 1; last > -1; last = next )
    {
        next = -1;
        for ( i = 1; last >= i; i++ )
        {
            do
            {
                temp2 = dists[ i - 1 ];
                t2 = i - 1;
            } while ( 0 );

            temp1 = dists[ i ];

            if ( temp1 < temp2 )
            {
                dists[ i - 1 ] = temp1;
                dists[ i ] = temp2;

                temp4 = ZAKO19Command.field_44[ i - 1 ];
                temp3 = ZAKO19Command.field_44[ i ];
                next = t2;

                ZAKO19Command.field_44[ i - 1 ] = temp3;
                ZAKO19Command.field_44[ i ] = temp4;
            }
        }
    }

    for ( i = 0; i < comm->n_watchers; i++ )
    {
        work = comm->watchers[ ZAKO19Command.field_44[ i ] ].work;
        work->chase_dis = chase_dist[ ZAKO19Command.field_44[ i ] ];
    }
}

void SoundSetCom( COMMANDER *comm )
{
    int   i;
    int   dis;
    int   sound;
    Work *work;

    SoundPlayTime--;

    if ( SoundPlayTime < 0 )
    {
        SoundPlayTime = 0;
    }

    if ( SoundPlayTime > 0 )
    {
        return;
    }

    sound = 0;
    dis = 100000;
    for ( i = 0; i < comm->n_watchers; i++ )
    {
        if ( comm->watchers[ i ].field_4 == 2 )
        {
            work = comm->watchers[ i ].work;
            if ( work->pad.sound && work->sn_dis < dis )
            {
                sound = work->pad.sound;
                dis = work->sn_dis;
            }
            work->pad.sound = 0;
        }
    }

    if ( sound )
    {
        SoundPlayTime = 30;
        GM_SeSet2( 0, 48, GetSoundId( sound ) );
    }
}

static void UpdateWatcher( WATCHER *watcher, int index )
{
    int state = watcher->field_8;

    switch ( state )
    {
    case 0:
        if ( watcher->field_4 == 1 )
        {
            watcher->field_8 = 1;
            watcher->field_0 = 1;
            ZAKO19Command.field_64++;
        }
        return;
    case 1:
        watcher->field_0--;
        if ( watcher->field_0 <= 0 )
        {
            watcher->field_8 = 2;
            watcher->field_0 = 0;
        }
        return;
    case 2:
        switch ( ZAKO19Command.alert_mode )
        {
        case 0:
            if ( ZAKO19Command.field_110 & 1 )
            {
                SetFarZone();
                watcher->field_4 = state;
                watcher->field_8 = 0;
            }
            return;
        case 1:
            if ( ZAKO19Command.field_64 < 255 )
            {
                SetFarZone();
                watcher->field_4 = state;
                watcher->field_8 = 0;
            }
            return;
        }
        return;
    }
}

static int Max( int a, int b )
{
    if ( a < b )
    {
        a = b;
    }

    return a;
}

static void AlertSetCom( int alert, COMMANDER *comm )
{
    if ( comm->alert_level - alert > 4 )
    {
        comm->alert_level -= 4;
    }
    else
    {
        comm->alert_level = alert;
    }

    if ( comm->alert_level < ZAKO19TOPCOMMAND.alert )
    {
        comm->alert_level = ZAKO19TOPCOMMAND.alert;
    }

    ZAKO19SetTopCommAL( 0 );
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
            ZAKO19Command.field_64 = 0;
        }
        break;
    case 1:
        if ( comm->alert_level <= 0 )
        {
            GM_AlertModeSet( ALERT_EVASION );
            comm->alert_mode = 2;
            comm->alert_time = 300;
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
            ZAKO19Command.field_64 = 0;
        }

        level = comm->alert_time;
        if ( level > 256 ) level = 256;
        if ( level > GM_AlertMax ) GM_AlertMax = level;
        break;
    }

    ZAKO19TOPCOMMAND.mode = comm->alert_mode;
}

static void CheckUnknown( void )
{
    /* do nothing */
}

static int CheckUnknown2( void )
{
    return 0;
}

static void UpdateAlert( CommanderWork *work )
{
    int i, alert;

    CheckUnknown();
    CheckUnknown2();

    alert = 0;

    for ( i = 0; i < ZAKO19Command.n_watchers; i++ )
    {
        if ( ZAKO19Command.watchers[ i ].field_4 == 2 )
        {
            alert = Max( alert, ZAKO19Command.watchers[ i ].work->alert_level );
        }
        else if ( ZAKO19Command.watchers[ i ].field_4 == 1 )
        {
            UpdateWatcher( &ZAKO19Command.watchers[ i ], i );
        }
    }

    AlertSetCom( alert, &ZAKO19Command );
    ChangeAlert( &ZAKO19Command );
    SortChaseDist( &ZAKO19Command );

    ZAKO19Command.field_110 = 0;
}

static void UpdatePlayerPosition( void )
{
    int addr;
    int addr2;

    addr = GM_PlayerAddress & 0xFF;
    addr2 = ( GM_PlayerAddress >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        ZAKO19_PlayerAddress = GM_PlayerAddress;
        ZAKO19_PlayerPosition = GM_PlayerPosition;
        ZAKO19_PlayerMap = GM_PlayerMap;
    }
}

int ExecProcs( char *opt )
{
    int i;
    int proc;

    i = 0;
    if ( opt )
    {
        do
        {
            proc = GCL_StrToInt( opt );
            opt = GCL_NextStr();
            GCL_ExecProc( proc, NULL );
            i++;
        } while ( opt );
    }

    return i;
}

int ZAKO19GetMessage( void )
{
    GV_MSG *msg;

    if ( GV_ReceiveMessage( ZAKO19Command.field_0, &msg ) > 0 )
    {
        return msg->message[ 0 ];
    }

    return -1;
}

static void UpdateGameFlag( void )
{
    int message;

    switch ( ZAKO19_GameFlag )
    {
    case 0:
        message = ZAKO19GetMessage();
        if ( message == 1 )
        {
            ZAKO19_GameFlag = message;
            GM_EnemyWatchCount++;
        }
        break;
    case 1:
        message = 0; /* optimized out, but keeps the case 1 test */
        break;
    case 2:
        break;
    }

    ZAKO19Command.time2++;
}

void Zako19CommanderAct( CommanderWork *work )
{
    UpdateGameFlag();
    UpdatePlayerPosition();
    UpdateAlert( work );
    ZAKO19Command.time++;
}

static void Die( CommanderWork *work )
{
    /* do nothing */
}

void ZAKO19SetCamera( SVECTOR *pos )
{
    ZAKO19_unk_800E0CC0 = *pos;
    GM_Camera.interp_mode = 2;
    GM_Camera.interp = 4;
}

#if 0 /* NON_MATCHING: the address of ZAKO19Command is kept in a register too early */
static void GetResources( CommanderWork *work, int name, int where )
{
    int i;
    char *opt;
    int flag;

    ZAKO19_GameFlag = 0;
    ZAKO19Command.field_24 = 0;
    ZAKO19Command.alert_level = 0;
    ZAKO19Command.field_0 = name;

    for ( i = 0; i < 8; i++ )
    {
        ZAKO19Command.watchers[ i ].field_0 = 0;
        ZAKO19Command.watchers[ i ].field_4 = 0;
        ZAKO19Command.watchers[ i ].field_8 = 0;
        ZAKO19Command.watchers[ i ].work = NULL;
    }

    for ( i = 0; i < 8; i++ )
    {
        ZAKO19Command.field_44[ i ] = i;
    }

    ZAKO19Command.time = 0;
    ZAKO19Command.alert_mode = 0;

    ZAKO19TOPCOMMAND.mode = 0;
    ZAKO19TOPCOMMAND.alert = 0;

    ZAKO19Command.map = GM_GetMap( where );

    opt = GCL_GetOption( 'v' );
    if ( opt )
    {
        ZAKO19Command.n_zones = ReadZones( opt, ZAKO19Command.zones );
    }
    else
    {
        ZAKO19Command.n_zones = 1;
        ZAKO19Command.zones[ 0 ] = 0;
    }

    for ( i = 0; i < ZAKO19Command.n_zones; i++ )
    {
        fprintf( 1, "zone=%d ", ZAKO19Command.zones[ i ] );
    }

    ZAKO19Command.far_zone = 0;

    opt = GCL_GetOption( 'f' );
    if ( opt )
    {
        flag = GCL_StrToInt( opt );
    }

    ZAKO19_Unknown = 1;
    NewAsiato();

    opt = GCL_GetOption( 'j' );
    if ( opt )
    {
        ZAKO19Command.jdata.count = ReadMapJdata( opt, &ZAKO19Command.jdata );
    }
    else
    {
        ZAKO19Command.jdata.count = 1;
        ZAKO19Command.jdata.data[ 0 ][ 0 ] = 0;
        ZAKO19Command.jdata.data[ 0 ][ 1 ] = 0;
    }

    ZAKO19Command.jdata.map = where;

    ZAKO19Command.n_watchers = 0;
    opt = GCL_GetOption( 'n' );
    if ( opt ) ZAKO19Command.n_watchers = ExecProcs( opt );

    ZAKO19Command.field_4 = 0;
    opt = GCL_GetOption( 'c' );
    if ( opt ) ZAKO19Command.field_4 = ExecProcs( opt );

    ZAKO19Command.field_8 = 0;
    opt = GCL_GetOption( 's' );
    if ( opt ) ZAKO19Command.field_8 = ExecProcs( opt );

    ZAKO19Command.field_114 = 0;
}

#endif
const char aZoneD_800E0300[] = "zone=%d ";
#pragma INCLUDE_ASM("asm/overlays/s19a/s19a_800D74FC.s")
void s19a_800D74FC( CommanderWork *work, int name, int where );
void *NewZako19Commander( int name, int where )
{
    CommanderWork *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(CommanderWork) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Zako19CommanderAct, Die, "zk19com.c" );
        s19a_800D74FC( work, name, where );
    }
    return (void *)work;
}
