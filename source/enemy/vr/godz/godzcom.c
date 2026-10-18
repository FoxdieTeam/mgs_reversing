// (VR only) this file is empty in the main executable build
#ifdef VR_EXE
#include "godzila.h"

#include <stdio.h>
#include "mgstype.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "game/vibrate.h"

typedef struct _GodzCommanderWork
{
    GV_ACT actor;
    int    name;
} GodzCommanderWork;

SVECTOR GODZ_TARGET_SIZE  = { 300, 1500, 300 };
SVECTOR GODZ_TARGET_FORCE = { 0, 0, 0 };
SVECTOR GODZ_ATTACK_SIZE  = { 800, 500, 800 };
SVECTOR GODZ_ATTACK_FORCE = { 100, 0, 0 };
SVECTOR GODZ_TOUCH_SIZE   = { 300, 800, 300 };
SVECTOR GODZ_TOUCH_FORCE  = { 0, 0, 0 };
SVECTOR GODZ_NO_POINT     = { 30000, 30000, 30000 };
int     GODZ_EYE_LENGTH   = 4000;

int GodzEyeLength[8] =
{
    4000, 4000, 7000, 8000, 8000, 8000, 8000, 8000
};

// vibration data
char GodzVibH[] = { 1, 10, 0, 0 };
char GodzVibL[] = { 255, 10, 0, 0 };

SVECTOR           SECTION(".bss") GodzCameraPos;
GODZ_COMMAND    SECTION(".bss") GodzCommand;
TOPCOMMAND_STRUCT SECTION(".bss") GodzTopCommand;
int               SECTION(".bss") GodzFlag;
int               SECTION(".bss") GODZ_GameFlag;
int               SECTION(".bss") GODZCOM_PlayerAddress;
int               SECTION(".bss") GODZCOM_PlayerMap;
SVECTOR           SECTION(".bss") GODZCOM_PlayerPosition;

extern void NewAsiato( void );



void GODZ_SetTopCommAL( int alert );
void s10a_zk10com_800CE3C0( void );

int GODZ_GetIndex( GodzWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( GodzCommand.watchers[ i ].watcher == 0 )
        {
            GodzCommand.watchers[ i ].watcher = ( WatcherWork * )work;
            GodzCommand.watchers[ i ].field_04 = 2;
            return i;
        }
    }
    return -1;
}

void GODZ_FreeIndex( int idx )
{
    GodzCommand.watchers[ idx ].watcher  = 0;
    GodzCommand.watchers[ idx ].field_04 = 1;
}

void GODZ_SetTopCommAL( int alert )
{
    GodzTopCommand.alert = alert;
}

void GODZ_SetTopCommMD( int mode )
{
    GodzTopCommand.mode = mode;
}

void GODZ_SetGoPointLast( void )
{
    GodzCommand.com_addr = GODZCOM_PlayerAddress;
    GodzCommand.com_pos  = GODZCOM_PlayerPosition;
    GodzCommand.com_map  = GODZCOM_PlayerMap;
}

void GODZ_SetGoPointNoise(void)
{
    GodzCommand.com_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    GodzCommand.com_pos  = GM_NoisePosition;
    GodzCommand.com_map  = GM_PlayerMap;
}

int GODZ_GetMapZone( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &GodzCommand.field_6C;

    if ( unk->map_id == map_id )
    {
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[ i ].field_00 == val )
            {
                return unk->field_04[ i ].field_02;
            }
        }
        /* returning -1 here instead of the goto does not match */
        goto end;
    }
    return 0;
end:
    return -1;
}

int s10a_zk10com_800CE308( char *ops, A4_STRUCT *unk )
{
    int i;
    i = 0;

    do {
        unk->field_04[ i ].field_00 = GCL_StrToInt( GCL_NextStr() );
        unk->field_04[ i ].field_02 = GCL_StrToInt( GCL_NextStr() );
        i++;
    } while ( GCL_NextStr() != NULL );


    return i;
}

int s10a_zk10com_800CE368( char *ops, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_NextStr() ) ; i++ )
    {
        *s = GCL_StrToInt( res );
        s++;
    }
    return i;
}

void s10a_zk10com_800CE3C0( void )
{
    int i;
    int dist2;
    int dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;

    i = dist1 = reset_pos = 0;

    for ( ; i < GodzCommand.n_zones ; i++  )
    {
        zone = &GodzCommand.map->hzd->def->zones[ GodzCommand.zones[ i ] ];

        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition.vy;
        svec.vz = zone->z;


        dist2 = GV_DiffVec3( &svec, &GM_PlayerPosition );
        if ( dist1 < dist2 )
        {
            dist1 = dist2;
            reset_pos = i;
        }
    }

    GodzCommand.reset_zone = reset_pos;
}

void s10a_zk10com_800CE4B0( GODZ_COMMAND* command )
{
    int i;
    int t2;
    int t3;
    int t4;
    int dists[8];
    int temp1, temp2;
    int temp3, temp4;
    GodzWork *work;

    for ( i = 0 ; i < command->n_watchers ; i ++ )
    {
        work = ( GodzWork * )command->watchers[ GodzCommand.order[ i ] ].watcher;
        dists[i] = work->sn_dis;
    }

    for ( t3 = command->n_watchers - 1 ; t3 > -1 ; t3 = t4  )
    {
        t4 = -1;
        for ( i = 1 ; t3 >= i ; i ++ )
        {
            //TODO, fix without using dowhile
            do
            {
                temp2 = dists[ i - 1 ];
                t2 = i - 1;
            } while (0);

            temp1 = dists[ i ];

            if ( temp1 < temp2 )
            {
                dists[ i - 1 ] = temp1;
                dists[ i ] = temp2;

                temp4 = GodzCommand.order[ i - 1 ];
                temp3 = GodzCommand.order[ i  ];
                t4 = t2;

                GodzCommand.order[ i - 1 ] = temp3;
                GodzCommand.order[ i ] = temp4;
            }
        }
    }

    for ( i = 0 ; i < command->n_watchers ; i++ )
    {
        work = ( GodzWork * )command->watchers[ GodzCommand.order[ i ] ].watcher;
        work->field_C08 = GodzEyeLength[ GodzCommand.order[ i ] ];
    }
}

void s10a_zk10com_800CE600( WATCHER *struct_c8 , int i )
{
    GodzWork *watcher;
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = 1;
            GodzCommand.n_reset++;
        }
        return;
    case 1:
        struct_c8->field_00--;
        if ( struct_c8->field_00 <= 0  )
        {
            struct_c8->field_08 = 2;
            struct_c8->field_00 = 0;
        }
        return;
    case 2:
        switch ( GodzCommand.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( GodzCommand.field_110 & 1 )
            {
                s10a_zk10com_800CE3C0();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
            return;
        case TOP_COMM_ALERT:
            watcher = ( GodzWork * )struct_c8->watcher;
            if ( GodzCommand.n_reset < 255 && watcher->param.field_B7C == 0xFF )
            {
                s10a_zk10com_800CE3C0();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
            return;
        }
        return;
    }
}

int s10a_zk10com_800CE72C( int a0, int a1 )
{
    if ( a0 < a1 )
    {
        a0 = a1;
    }

    return a0;
}

void s10a_zk10com_800CE744( int val, GODZ_COMMAND* command )
{
    if ( command->alert - val > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = val;
    }

    if ( command->alert < GodzTopCommand.alert )
    {
        command->alert = GodzTopCommand.alert;
    }

    GODZ_SetTopCommAL( 0 );
}

void s10a_zk10com_800CE7A8( GODZ_COMMAND *command )
{
    int alert;

    switch ( command->mode )
    {
        case 0:
            if ( command->alert >= 255 )
            {
                command->mode = 1;
                command->alert = 255;
                GM_SeSet2( 0, 0x3F, SE_ALERT_SIREN);
                GodzCommand.n_reset = 0;
            }
        break;
        case 1:
            if ( command->alert <= 0 )
            {
                command->mode = 2;
                command->evasion_time = 300;
            }
            alert = command->alert;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
        case 2:
            command->evasion_time--;
            if ( command->evasion_time <= 0 )
            {
                command->mode = 0;
                command->evasion_time = 0;
            }
            if ( command->alert >= 255 )
            {
                command->alert = 0xFF;
                command->mode = 1;
                GodzCommand.n_reset = 0;
            }
            alert = command->evasion_time;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
    }

    GodzTopCommand.mode = command->mode;
}

void s10a_zk10com_800CE8DC( void )
{
    /* do nothing */
}

int s10a_zk10com_800CE8E4( void )
{
    return 0;
}

void s10a_zk10com_800CE8EC( GodzCommanderWork* work )
{
    int i;
    int alert;
    GodzWork *watcher;

    s10a_zk10com_800CE8DC();
    s10a_zk10com_800CE8E4();

    alert = 0;

    for ( i = 0; i < GodzCommand.n_watchers; i++ )
    {
        if ( GodzCommand.watchers[ i ].field_04 == 2 )
        {
            watcher = ( GodzWork * )GodzCommand.watchers[ i ].watcher;
            alert =  s10a_zk10com_800CE72C( alert, watcher->alert_level );
        }
        else if ( GodzCommand.watchers[ i ].field_04 == 1 )
        {
            s10a_zk10com_800CE600( &GodzCommand.watchers[ i ], i );
        }
    }

    s10a_zk10com_800CE744( alert, &GodzCommand );
    s10a_zk10com_800CE7A8( &GodzCommand );
    s10a_zk10com_800CE4B0( &GodzCommand );

    GodzCommand.field_110 = 0;
}

void s10a_zk10com_800CE9E0( void )
{
    int addr;
    int addr2;

    addr = GM_PlayerAddress & 0xFF;
    addr2 = ( GM_PlayerAddress >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        GODZCOM_PlayerAddress  = GM_PlayerAddress;
        GODZCOM_PlayerPosition = GM_PlayerPosition;
        GODZCOM_PlayerMap      = GM_PlayerMap;
    }
}

int s10a_zk10com_800CEA54( char *arg0 )
{
    int i;
    unsigned char* res;
    int proc_id;

    res = arg0;
    i = 0;
    if ( res )
    {
        do
        {
            proc_id = GCL_StrToInt( res );
            res = GCL_NextStr();
            GCL_ExecProc( proc_id, NULL );
            i++;
        } while ( res );
    }
    return i;
}

int s10a_zk10com_800CEAB8( void )
{
    GV_MSG *msg;

    if ( GV_ReceiveMessage( GodzCommand.name, &msg ) > 0 )
    {
        return msg->message[0];
    }

    return -1;
}

void s10a_zk10com_800CEAF4( void )
{
    switch ( GODZ_GameFlag )
    {
    case 0:
        if ( s10a_zk10com_800CEAB8() == 1 )
        {
            GODZ_GameFlag = 1;
            NewPadVibration( GodzVibH, 1 );
            NewPadVibration( GodzVibL, 2 );
            if ( GM_StreamStatus() == -1 )
            {
                GM_VoxStream( GodzCommand.voice, 0x40000000 );
            }
            GodzCommand.timer = 0;
        }
        break;
    case 1:
        if ( GodzCommand.timer > 30 && GM_StreamStatus() == 1 )
        {
            GM_StreamPlayStart();
        }
        break;
    case 2:
        break;
    }

    GodzCommand.timer++;
}

static void Act( GodzCommanderWork* work )
{
    s10a_zk10com_800CEAF4();
    s10a_zk10com_800CE9E0();
    s10a_zk10com_800CE8EC( work );
    GodzCommand.counter++;
}

static void Die( GodzCommanderWork* work )
{
}

void s10a_zk10com_800CEC44( SVECTOR *pos )
{
    GodzCameraPos = *pos;
    GM_Camera.interp_mode = 2;
    GM_Camera.interp = 4;
}

static void GetResources( GodzCommanderWork *work, int name, int where )
{
    int i;
    char *ops;

    GODZ_GameFlag = 0;

    GodzCommand.c_root = 0;
    GodzCommand.alert = 0;
    GodzCommand.name = name;

    for ( i = 0 ; i < 8 ; i++ )
    {
        GodzCommand.watchers[i].field_00 = 0;
        GodzCommand.watchers[i].field_04 = 0;
        GodzCommand.watchers[i].field_08 = 0;
        GodzCommand.watchers[i].watcher  = 0;
    }

    for ( i = 7 ; i >= 0 ; i-- )
    {
        GodzCommand.order[i]  = i;
    }

    GodzCommand.counter = 0;
    GodzCommand.mode = 0;

    GodzTopCommand.mode = 0;
    GodzTopCommand.alert = 0;

    GodzCommand.map = GM_GetMap( where );

    ops = GCL_GetOption( 'v' );
    if ( ops )
    {
        GodzCommand.n_zones = s10a_zk10com_800CE368( ops, GodzCommand.zones );
    }
    else
    {
        GodzCommand.n_zones = 1;
        GodzCommand.zones[0] = 0;
    }

    for ( i = 0 ; i < GodzCommand.n_zones ; i++ )
    {
        fprintf( 1, "zone=%d ", GodzCommand.zones[i] );
    }

    GodzCommand.reset_zone = 0;

    ops = GCL_GetOption( 'f' );
    if ( ops )
    {
        GCL_StrToInt( ops );    /* value not used */
        GodzFlag = 1;
    }
    else
    {
        GodzFlag = 1;
    }

    NewAsiato();

    ops = GCL_GetOption( 'j' );
    if ( ops )
    {
        GodzCommand.field_6C.n_entry = s10a_zk10com_800CE308( ops, &GodzCommand.field_6C );
    }
    else
    {
        GodzCommand.field_6C.n_entry = 1;
        GodzCommand.field_6C.field_04->field_00 = 0;
        GodzCommand.field_6C.field_04->field_02 = 0;
    }

    GodzCommand.field_6C.map_id  = where;

    ops = GCL_GetOption( 'b' );
    if ( ops )
    {
        GodzCommand.voice = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        GodzCommand.voice = 0;
    }

    GodzCommand.n_watchers = 0;
    ops = GCL_GetOption( 'n' );
    if ( ops )
    {
        GodzCommand.n_watchers = s10a_zk10com_800CEA54( ops );
    }

    GodzCommand.n_proc_c = 0;
    ops = GCL_GetOption( 'c' );
    if ( ops )
    {
        GodzCommand.n_proc_c = s10a_zk10com_800CEA54( ops );
    }

    GodzCommand.n_proc_s = 0;
    ops = GCL_GetOption( 's' );
    if ( ops )
    {
        GodzCommand.n_proc_s = s10a_zk10com_800CEA54( ops );
    }

    GodzCommand.field_114 = 0;
}


void *NewGodzCommander( int name, int where, int argc, char **argv )
{
    GodzCommanderWork *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( GodzCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "zk10com.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
#endif
