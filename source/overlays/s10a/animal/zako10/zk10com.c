#include "zako10.h"

#include <stdio.h>
#include "mgstype.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "game/vibrate.h"

typedef struct _Zako10CommanderWork
{
    GV_ACT actor;
    int    name;
} Zako10CommanderWork;

SVECTOR ZAKO10_TARGET_SIZE  = { 300, 1500, 300 };
SVECTOR ZAKO10_TARGET_FORCE = { 0, 0, 0 };
SVECTOR ZAKO10_ATTACK_SIZE  = { 800, 500, 800 };
SVECTOR ZAKO10_ATTACK_FORCE = { 100, 0, 0 };
SVECTOR ZAKO10_TOUCH_SIZE   = { 300, 800, 300 };
SVECTOR ZAKO10_TOUCH_FORCE  = { 0, 0, 0 };
SVECTOR ZAKO10_NO_POINT     = { 30000, 30000, 30000 };
int     ZAKO10_EYE_LENGTH   = 4000;

int Zako10EyeLength[8] =
{
    4000, 4000, 7000, 8000, 8000, 8000, 8000, 8000
};

// vibration data
char Zako10VibH[] = { 1, 10, 0, 0 };
char Zako10VibL[] = { 255, 10, 0, 0 };

SVECTOR           SECTION(".bss") Zako10CameraPos;
ZAKO10_COMMAND    SECTION(".bss") Zako10Command;
TOPCOMMAND_STRUCT SECTION(".bss") Zako10TopCommand;
int               SECTION(".bss") Zako10Flag;
int               SECTION(".bss") ZAKO10_GameFlag;
int               SECTION(".bss") ZAKO10COM_PlayerAddress;
int               SECTION(".bss") ZAKO10COM_PlayerMap;
SVECTOR           SECTION(".bss") ZAKO10COM_PlayerPosition;

extern void NewAsiato( void );



void ZAKO10_SetTopCommAL( int alert );
void s10a_zk10com_800CE3C0( void );

int ZAKO10_GetIndex( Zako10Work *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( Zako10Command.watchers[ i ].watcher == 0 )
        {
            Zako10Command.watchers[ i ].watcher = ( WatcherWork * )work;
            Zako10Command.watchers[ i ].field_04 = 2;
            return i;
        }
    }
    return -1;
}

void ZAKO10_FreeIndex( int idx )
{
    Zako10Command.watchers[ idx ].watcher  = 0;
    Zako10Command.watchers[ idx ].field_04 = 1;
}

void ZAKO10_SetTopCommAL( int alert )
{
    Zako10TopCommand.alert = alert;
}

void ZAKO10_SetTopCommMD( int mode )
{
    Zako10TopCommand.mode = mode;
}

void ZAKO10_SetGoPointLast( void )
{
    Zako10Command.com_addr = ZAKO10COM_PlayerAddress;
    Zako10Command.com_pos  = ZAKO10COM_PlayerPosition;
    Zako10Command.com_map  = ZAKO10COM_PlayerMap;
}

void ZAKO10_SetGoPointNoise(void)
{
    Zako10Command.com_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    Zako10Command.com_pos  = GM_NoisePosition;
    Zako10Command.com_map  = GM_PlayerMap;
}

int ZAKO10_GetMapZone( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &Zako10Command.field_6C;

    if ( unk->map_id == map_id )
    {
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[ i ].field_00 == val )
            {
                return unk->field_04[ i ].field_02;
            }
        }
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

    for ( ; i < Zako10Command.n_zones ; i++  )
    {
        zone = &Zako10Command.map->hzd->def->zones[ Zako10Command.zones[ i ] ];

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

    Zako10Command.reset_zone = reset_pos;
}

void s10a_zk10com_800CE4B0( ZAKO10_COMMAND* command )
{
    int i;
    int t2;
    int t3;
    int t4;
    int dists[8];
    int temp1, temp2;
    int temp3, temp4;
    Zako10Work *work;

    for ( i = 0 ; i < command->n_watchers ; i ++ )
    {
        work = ( Zako10Work * )command->watchers[ Zako10Command.order[ i ] ].watcher;
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

                temp4 = Zako10Command.order[ i - 1 ];
                temp3 = Zako10Command.order[ i  ];
                t4 = t2;

                Zako10Command.order[ i - 1 ] = temp3;
                Zako10Command.order[ i ] = temp4;
            }
        }
    }

    for ( i = 0 ; i < command->n_watchers ; i++ )
    {
        work = ( Zako10Work * )command->watchers[ Zako10Command.order[ i ] ].watcher;
        work->field_BF8 = Zako10EyeLength[ Zako10Command.order[ i ] ];
    }
}

void s10a_zk10com_800CE600( WATCHER *struct_c8 , int i )
{
    Zako10Work *watcher;
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = 1;
            Zako10Command.n_reset++;
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
        switch ( Zako10Command.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( Zako10Command.field_110 & 1 )
            {
                s10a_zk10com_800CE3C0();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
            return;
        case TOP_COMM_ALERT:
            watcher = ( Zako10Work * )struct_c8->watcher;
            if ( Zako10Command.n_reset < 255 && watcher->param.field_B7C == 0xFF )
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

void s10a_zk10com_800CE744( int val, ZAKO10_COMMAND* command )
{
    if ( command->alert - val > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = val;
    }

    if ( command->alert < Zako10TopCommand.alert )
    {
        command->alert = Zako10TopCommand.alert;
    }

    ZAKO10_SetTopCommAL( 0 );
}

void s10a_zk10com_800CE7A8( ZAKO10_COMMAND *command )
{
    int alert;

    switch ( command->mode )
    {
        case 0:
            if ( command->alert >= 255 )
            {
                command->mode = 1;
                command->alert = 255;
                GM_SeSet2( 0, 0x3F, 0x2A );
                Zako10Command.n_reset = 0;
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
                Zako10Command.n_reset = 0;
            }
            alert = command->evasion_time;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
    }

    Zako10TopCommand.mode = command->mode;
}

void s10a_zk10com_800CE8DC( void )
{
    /* do nothing */
}

int s10a_zk10com_800CE8E4( void )
{
    return 0;
}

void s10a_zk10com_800CE8EC( Zako10CommanderWork* work )
{
    int i;
    int alert;
    Zako10Work *watcher;

    s10a_zk10com_800CE8DC();
    s10a_zk10com_800CE8E4();

    alert = 0;

    for ( i = 0; i < Zako10Command.n_watchers; i++ )
    {
        if ( Zako10Command.watchers[ i ].field_04 == 2 )
        {
            watcher = ( Zako10Work * )Zako10Command.watchers[ i ].watcher;
            alert =  s10a_zk10com_800CE72C( alert, watcher->alert_level );
        }
        else if ( Zako10Command.watchers[ i ].field_04 == 1 )
        {
            s10a_zk10com_800CE600( &Zako10Command.watchers[ i ], i );
        }
    }

    s10a_zk10com_800CE744( alert, &Zako10Command );
    s10a_zk10com_800CE7A8( &Zako10Command );
    s10a_zk10com_800CE4B0( &Zako10Command );

    Zako10Command.field_110 = 0;
}

void s10a_zk10com_800CE9E0( void )
{
    int addr;
    int addr2;

    addr = GM_PlayerAddress & 0xFF;
    addr2 = ( GM_PlayerAddress >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        ZAKO10COM_PlayerAddress  = GM_PlayerAddress;
        ZAKO10COM_PlayerPosition = GM_PlayerPosition;
        ZAKO10COM_PlayerMap      = GM_PlayerMap;
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

    if ( GV_ReceiveMessage( Zako10Command.name, &msg ) > 0 )
    {
        return msg->message[0];
    }

    return -1;
}

void s10a_zk10com_800CEAF4( void )
{
    switch ( ZAKO10_GameFlag )
    {
    case 0:
        if ( s10a_zk10com_800CEAB8() == 1 )
        {
            ZAKO10_GameFlag = 1;
            NewPadVibration( Zako10VibH, 1 );
            NewPadVibration( Zako10VibL, 2 );
            if ( GM_StreamStatus() == -1 )
            {
                GM_VoxStream( Zako10Command.voice, 0x40000000 );
            }
            Zako10Command.timer = 0;
        }
        break;
    case 1:
        if ( Zako10Command.timer > 30 && GM_StreamStatus() == 1 )
        {
            GM_StreamPlayStart();
        }
        break;
    case 2:
        break;
    }

    Zako10Command.timer++;
}

static void Act( Zako10CommanderWork* work )
{
    s10a_zk10com_800CEAF4();
    s10a_zk10com_800CE9E0();
    s10a_zk10com_800CE8EC( work );
    Zako10Command.counter++;
}

static void Die( Zako10CommanderWork* work )
{
}

void s10a_zk10com_800CEC44( SVECTOR *pos )
{
    Zako10CameraPos = *pos;
    GM_Camera.interp_mode = 2;
    GM_Camera.interp = 4;
}

static void GetResources( Zako10CommanderWork *work, int name, int where )
{
    int i;
    char *ops;

    ZAKO10_GameFlag = 0;

    Zako10Command.c_root = 0;
    Zako10Command.alert = 0;
    Zako10Command.name = name;

    for ( i = 0 ; i < 8 ; i++ )
    {
        Zako10Command.watchers[i].field_00 = 0;
        Zako10Command.watchers[i].field_04 = 0;
        Zako10Command.watchers[i].field_08 = 0;
        Zako10Command.watchers[i].watcher  = 0;
    }

    for ( i = 7 ; i >= 0 ; i-- )
    {
        Zako10Command.order[i]  = i;
    }

    Zako10Command.counter = 0;
    Zako10Command.mode = 0;

    Zako10TopCommand.mode = 0;
    Zako10TopCommand.alert = 0;

    Zako10Command.map = GM_GetMap( where );

    ops = GCL_GetOption( 'v' );
    if ( ops )
    {
        Zako10Command.n_zones = s10a_zk10com_800CE368( ops, Zako10Command.zones );
    }
    else
    {
        Zako10Command.n_zones = 1;
        Zako10Command.zones[0] = 0;
    }

    for ( i = 0 ; i < Zako10Command.n_zones ; i++ )
    {
        fprintf( 1, "zone=%d ", Zako10Command.zones[i] );
    }

    Zako10Command.reset_zone = 0;

    ops = GCL_GetOption( 'f' );
    if ( ops )
    {
        GCL_StrToInt( ops );    /* value not used */
        Zako10Flag = 1;
    }
    else
    {
        Zako10Flag = 1;
    }

    NewAsiato();

    ops = GCL_GetOption( 'j' );
    if ( ops )
    {
        Zako10Command.field_6C.n_entry = s10a_zk10com_800CE308( ops, &Zako10Command.field_6C );
    }
    else
    {
        Zako10Command.field_6C.n_entry = 1;
        Zako10Command.field_6C.field_04->field_00 = 0;
        Zako10Command.field_6C.field_04->field_02 = 0;
    }

    Zako10Command.field_6C.map_id  = where;

    ops = GCL_GetOption( 'b' );
    if ( ops )
    {
        Zako10Command.voice = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        Zako10Command.voice = 0;
    }

    Zako10Command.n_watchers = 0;
    ops = GCL_GetOption( 'n' );
    if ( ops )
    {
        Zako10Command.n_watchers = s10a_zk10com_800CEA54( ops );
    }

    Zako10Command.n_proc_c = 0;
    ops = GCL_GetOption( 'c' );
    if ( ops )
    {
        Zako10Command.n_proc_c = s10a_zk10com_800CEA54( ops );
    }

    Zako10Command.n_proc_s = 0;
    ops = GCL_GetOption( 's' );
    if ( ops )
    {
        Zako10Command.n_proc_s = s10a_zk10com_800CEA54( ops );
    }

    Zako10Command.field_114 = 0;
}


void *NewZako10Commander( int name, int where, int argc, char **argv )
{
    Zako10CommanderWork *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( Zako10CommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "zk10com.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
