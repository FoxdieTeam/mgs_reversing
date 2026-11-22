#define __ANIMAL_ZAKO_ZAKOCOM_C__
#include "zako.h"

#include <stdio.h>
#include "mts/mts.h"      // for fprintf
#include "game/vibrate.h" // for NewPadVibration
#include "takabe/cineutil.h" // for OpenCinemaScreen, etc.

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO_NO_POINT = {30000, 30000, 30000};

int SECTION(".bss") ZAKO_Unknown;
int SECTION(".bss") s03d_dword_800DC2E4;
TOP SECTION(".bss") ZAKOTOPCOMMAND;
int SECTION(".bss") ZAKO_GameStatus;
int SECTION(".bss") ZAKO_VibTime;
int SECTION(".bss") ZAKO_GameFlag;
int SECTION(".bss") ZAKO_PlayerAddress;
int SECTION(".bss") ZAKO_PlayerMap;
int SECTION(".bss") s03d_dword_800DC304;
SVECTOR SECTION(".bss") ZAKO_PlayerPosition;
COMMANDER SECTION(".bss") ZAKOCommand;

/*---------------------------------------------------------------------------*/

static SVECTOR SocomPos = {8000, 0, 1000};

static u_char VibH[4] = { 1, 1, 0, 0 };
static u_char VibL[4] = { 255, 1, 0, 0 };

static int ChaseDis[] = {
    3000, 4000, 7000, 8000,
    8000, 8000, 8000, 8000,
};

static int SoundPlayTime = 0;

/*---------------------------------------------------------------------------*/

int ZAKOSetWorkID( Work *work )
{
    int i;

    for ( i = 0; i < 8; i++ )
    {
        if ( ZAKOCommand.watchers[ i ].work == NULL )
        {
            ZAKOCommand.watchers[ i ].work = work;
            ZAKOCommand.watchers[ i ].field_4 = 2;
            return i;
        }
    }

    return -1;
}

int ZAKO_800D4038( void )
{
    int v;

    v = ZAKO_Unknown;
    ZAKO_Unknown++;
    return v;
}

void ZAKOResetWorkID( int index )
{
    ZAKOCommand.watchers[ index ].work = NULL;
    ZAKOCommand.watchers[ index ].field_4 = 1;
}

void ZAKOSetTopCommAL( int alert )
{
    ZAKOTOPCOMMAND.alert = alert;
}

void ZAKOSetTopCommMD( int mode )
{
    ZAKOTOPCOMMAND.mode = mode;
}

void ZAKOSetGopointLast( void )
{
    ZAKOCommand.target_addr = ZAKO_PlayerAddress;
    ZAKOCommand.target_pos = ZAKO_PlayerPosition;
    ZAKOCommand.target_map = ZAKO_PlayerMap;
}

void ZAKOSetGopointNoise( void )
{
    ZAKOCommand.target_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKOCommand.target_pos = GM_NoisePosition;
    ZAKOCommand.target_map = GM_PlayerMap;
}

int ZAKOGetMapJointZone( int from, int to )
{
    JOINT_DATA *data;
    int i;

    data = &ZAKOCommand.joint_data;
    if ( data->map == from )
    {
        for ( i = 0; i < data->n_joints; i++ )
        {
            if ( data->joints[ i ].map == to ) return data->joints[ i ].zone;
        }

        goto not_found;
    }

    return 0;

not_found:
    return -1;
}

/*---------------------------------------------------------------------------*/

static void ZakoCom_800D41C0(void)
{
    if (ZAKO_VibTime > 0)
    {
        NewPadVibration(VibH, 1);
        NewPadVibration(VibL, 2);
        ZAKO_VibTime--;
    }
    else
    {
        ZAKO_VibTime = 0;
    }
}

static int ReadMapJdata( char *opt, JOINT_DATA *data )
{
    int i;

    i = 0;
    do
    {
        data->joints[ i ].map = GCL_StrToInt( GCL_NextStr() );
        data->joints[ i ].zone = GCL_StrToInt( GCL_NextStr() );
        i++;
    } while ( GCL_NextStr() != 0 );

    return i;
}

static int ZakoCom_800D4284(char *arg0, short *out)
{
    short *p = out;
    int count = 0;
    char *str;

    while ((str = GCL_NextStr()) != 0)
    {
        *p = GCL_StrToInt(str);
        p++;
        count++;
    }

    return count;
}

static void SetCurrentReset( void )
{
    SVECTOR pos;
    int max, reset, i, dist;
    HZD_ZON *zone;

    max = 0;
    reset = 0;

    for ( i = 0; i < ZAKOCommand.n_zones ; i++ )
    {
        zone = &ZAKOCommand.map->hzd->def->zones[ ZAKOCommand.zones[ i ] ];

        pos.vx = zone->x;
        pos.vy = GM_PlayerPosition.vy;
        pos.vz = zone->z;

        dist = GV_DiffVec3( &pos, &GM_PlayerPosition );
        if ( max < dist )
        {
            max = dist;
            reset = i;
        }
    }

    ZAKOCommand.c_reset_pos = reset;
}

static int ZakoCom_800D43CC(int arg)
{
    return ZAKOCommand.field_C % arg;
}

static void ZakoCom_800D440C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "dareda!!\n");
        *out = 0x80;
    }
    else if (r == 1)
    {
        fprintf(1, "dareda!!\n");
        *out = 0x80;
    }
}

static void ZakoCom_800D4460(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "nanno otoda!!\n");
        *out = 0x87;
    }
    else if (r == 1)
    {
        fprintf(1, "nanno otoda!!\n");
        *out = 0x87;
    }
}

static void ZakoCom_800D44B4(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "tadano hakoka\n");
        *out = 0x8B;
    }
    else if (r == 1)
    {
        fprintf(1, "tadano hakoka\n");
        *out = 0x8B;
    }
}

static void ZakoCom_800D4508(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "kono asiatoha??\n");
        *out = 0x8A;
    }
    else if (r == 1)
    {
        fprintf(1, "kono asiatoha??\n");
        *out = 0x8A;
    }
}

static void ZakoCom_800D455C(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "kinoseika !!\n");
        *out = 0x86;
    }
    else if (r == 1)
    {
        fprintf(1, "kinoseika !!\n");
        *out = 0x86;
    }
}

static void ZakoCom_800D45B0(int *out)
{
    switch (ZakoCom_800D43CC(3))
    {
    case 0:
        fprintf(1, "itazo \n");
        *out = 0x82;
        break;
    case 1:
        fprintf(1, "kottida!!\n");
        *out = 0x81;
        break;
    case 2:
        fprintf(1, "kottida!!\n");
        *out = 0x81;
        break;
    }
}

static void ZakoCom_800D4640(int *out)
{
    int r = ZakoCom_800D43CC(2);

    if (r == 0)
    {
        fprintf(1, "haitini modoruzo!!\n");
        *out = 0x85;
    }
    else if (r == 1)
    {
        fprintf(1, "haitini modoruzo!!\n");
        *out = 0x85;
    }
}

static void ZakoCom_800D4694(int *out)
{
    switch ( ZakoCom_800D43CC( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *out = 0x81;
        break;
    case 1:
        *out = 0;
        break;
    }
}

static int s03d_800D46F8( int id )
{
    switch ( id )
    {
    case 240:
        ZakoCom_800D440C( &id );
        break;
    case 241:
        ZakoCom_800D4460( &id );
        break;
    case 242:
        ZakoCom_800D44B4( &id );
        break;
    case 243:
        ZakoCom_800D4508( &id );
        break;
    case 244:
        ZakoCom_800D455C( &id );
        break;
    case 245:
        ZakoCom_800D4640( &id );
        break;
    case 246:
        ZakoCom_800D45B0( &id );
        break;
    case 247:
        ZakoCom_800D4694( &id );
        break;
    }

    return id;
}

static void s03d_800D47BC(COMMANDER *comm)
{
    int i;
    int prev;
    int t3;
    int t4;
    int dists[8];
    int cur, min;
    int a, b;
    Work *work;

    for (i = 0; i < comm->count; i++)
    {
        work = comm->watchers[ZAKOCommand.order[i]].work;
        dists[i] = work->field_B90;
    }

    for (t3 = comm->count - 1; t3 > -1; t3 = t4)
    {
        t4 = -1;
        for (i = 1; t3 >= i; i++)
        {
            /* do/while(0) is required to reproduce the match */
            do
            {
                min = dists[i - 1];
                prev = i - 1;
            } while (0);

            cur = dists[i];

            if (cur < min)
            {
                dists[i - 1] = cur;
                dists[i] = min;

                b = ZAKOCommand.order[i - 1];
                a = ZAKOCommand.order[i];
                t4 = prev;

                ZAKOCommand.order[i - 1] = a;
                ZAKOCommand.order[i] = b;
            }
        }
    }

    for (i = 0; i < comm->count; i++)
    {
        work = comm->watchers[ZAKOCommand.order[i]].work;
        work->field_B64 = ChaseDis[ZAKOCommand.order[i]];
    }
}

static void ZakoCom_800D490C(COMMANDER *comm)
{
    int i;
    int min;
    int best;

    SoundPlayTime--;
    if (SoundPlayTime < 0)
    {
        SoundPlayTime = 0;
    }
    if (SoundPlayTime > 0)
    {
        return;
    }
    min = 100000;
    best = 0;
    for (i = 0; i < comm->count; i++)
    {
        if (comm->watchers[i].field_4 == 2)
        {
            Work *work = comm->watchers[i].work;

            if (work->field_AE8 != 0 && work->field_B90 < min)
            {
                best = work->field_AE8;
                min = work->field_B90;
            }
            work->field_AE8 = 0;
        }
    }
    if (best != 0)
    {
        SoundPlayTime = 0x1E;
        GM_SeSet2(0, 0x30, s03d_800D46F8(best));
    }
}

static void ZakoCom_800D49F0(WATCHER *watcher, int idx)
{
    switch (watcher->field_8)
    {
    case 0:
        if (watcher->field_4 == 1)
        {
            watcher->field_8 = 1;
            watcher->field_0 = 1;
            printf("%d reset_enemy_num[%d ]\n", idx, ++ZAKOCommand.reset_enemy_num);
        }
        break;
    case 1:
        watcher->field_0--;
        if (watcher->field_0 <= 0)
        {
            watcher->field_8 = 2;
            watcher->field_0 = 0;
        }
        break;
    case 2:
    {
        switch (ZAKOCommand.field_1C)
        {
        case 0:
            if (ZAKOCommand.field_10C & 1)
            {
                SetCurrentReset();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;
        case 1:
            if (ZAKOCommand.reset_enemy_num < 16)
            {
                SetCurrentReset();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;
        }
        break;
    }
    }
}

static int ZakoCom_800D4B08(int a, int b)
{
    if (a < b)
    {
        a = b;
    }
    return a;
}

static void ZakoCom_800D4B20(int targetval, COMMANDER *comm)
{
    int v = comm->field_18;

    if (v - targetval >= 5)
    {
        comm->field_18 = v - 4;
    }
    else
    {
        comm->field_18 = targetval;
    }

    if (comm->field_18 < ZAKOTOPCOMMAND.alert)
    {
        comm->field_18 = ZAKOTOPCOMMAND.alert;
    }

    ZAKOSetTopCommAL( 0 );
}

static void s03d_800D4B84(COMMANDER *comm)
{
    int alert;

    switch (comm->field_1C)
    {
    case 0:
        if (comm->field_18 >= 255)
        {
            comm->field_18 = 0xFF;
            GM_AlertModeSet(3);
            comm->field_1C = 1;
            GM_SeSet2(NULL, 0x3F, 0x2A);
            ZAKOCommand.reset_enemy_num = 0;
        }
        break;
    case 1:
        if (comm->field_18 <= 0)
        {
            GM_AlertModeSet(2);
            comm->field_1C = 2;
            comm->field_14 = 0;
        }
        alert = comm->field_18;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    case 2:
        comm->field_14--;
        if (comm->field_14 <= 0)
        {
            GM_AlertModeSet(0);
            comm->field_1C = 0;
            comm->field_14 = 0;
        }
        if (comm->field_18 >= 255)
        {
            comm->field_18 = 0xFF;
            GM_AlertModeSet(3);
            comm->field_1C = 1;
            ZAKOCommand.reset_enemy_num = 0;
        }
        alert = comm->field_14;
        if (alert >= 0x101)
        {
            alert = 0x100;
        }
        GM_SetAlertMax(alert);
        break;
    }
    ZAKOTOPCOMMAND.mode = comm->field_1C;
}

static void s03d_800D4CE0( CommanderWork *work )
{
    int alert, i;

    alert = 0;
    for (i = 0; i < ZAKOCommand.count; i++)
    {
        if (ZAKOCommand.watchers[i].field_4 == 2)
        {
            alert = ZakoCom_800D4B08(alert, ZAKOCommand.watchers[i].work->field_B28);
        }
        else if (ZAKOCommand.watchers[i].field_4 == 1)
        {
            ZakoCom_800D49F0(&ZAKOCommand.watchers[i], i);
        }
    }

    ZakoCom_800D490C(&ZAKOCommand);
    ZakoCom_800D4B20(alert, &ZAKOCommand);
    s03d_800D4B84(&ZAKOCommand);
    s03d_800D47BC(&ZAKOCommand);
    ZAKOCommand.field_10C = 0;
}

static void ZakoCom_800D4DD4(void)
{
    int addr = GM_PlayerAddress;

    if ((addr & 0xFF) == ((addr >> 8) & 0xFF) && (addr & 0xFF) != 0xFF)
    {
        ZAKO_PlayerAddress = addr;
        ZAKO_PlayerPosition = GM_PlayerPosition;
        ZAKO_PlayerMap = GM_PlayerMap;
    }
}

static int InitWorkCom( char *opt )
{
    int i, proc;

    i = 0;
    while ( opt != NULL )
    {
        proc = GCL_StrToInt( opt );
        opt = GCL_NextStr();
        GCL_ExecProc( proc, NULL );
        i++;
    }

    return i;
}

static void GameFlagChk( void )
{
    int reset, i;

    reset = ZAKOCommand.reset_enemy_num;

    if ( GM_GameOverTimer != 0 ) return;
    if ( GM_Vitality <= 0 ) return;

    switch ( ZAKO_GameFlag )
    {
    case 0:
        if ( ZAKOCommand.field_10 == 0 && GM_StreamStatus() == -1 )
        {
            GM_VoxStream( ZAKOCommand.sounds[ 0 ], 0x40000000 );
        }

        if ( reset != 0 )
        {
            ZAKO_GameFlag = 1;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 1:
        if ( reset > 2 )
        {
            if (GM_ItemTypes[ GM_Item + 1 ] & 0x2 )
            {
                GM_Item = IT_None;
            }

            if ( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 )
            {
                GM_Weapon = WP_None;
            }

            OpenCinemaScreen( 0, 60000 );
            GM_GameStatus |= ( STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF );
            ZAKO_GameFlag = 2;
            ZAKOCommand.field_10 = 0;
        }
        break;
    case 2:
        if ( ZAKOCommand.field_10 == 0 )
        {
            if ( GM_StreamStatus() == 1 )
            {
                GM_StreamPlayStart();
            }

            if ( ZAKOCommand.procs[ 5 ] >= 0 )
            {
                GCL_ExecProc( ZAKOCommand.procs[ 5 ], NULL );
            }
        }

        if ( ZAKOCommand.field_10 > 10 )
        {
            ZAKO_GameFlag = 3;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 3:
        if ( ZAKOCommand.field_10 > 30 )
        {
            if ( ZAKOCommand.procs[ 0 ] >= 0 )
            {
                GCL_ExecProc( ZAKOCommand.procs[ 0 ], NULL );
            }

            ZAKO_GameFlag = 4;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 4:
        if ( ZAKOCommand.field_10 > 60 && GM_StreamStatus() == -1 )
        {
            GM_VoxStream( ZAKOCommand.sounds[ 1 ], 0 );

            if ( ZAKOCommand.procs[ 1 ] >= 0 )
            {
                GCL_ExecProc( ZAKOCommand.procs[ 1 ], NULL );
            }

            ZAKO_GameFlag = 5;
            ZAKOCommand.field_10 = 0;

            if ( GM_Weapons[ WP_Socom ] < 0 )
            {
                GM_PlayerControl->mov.vx = SocomPos.vx;
                GM_PlayerControl->mov.vz = SocomPos.vz;
            }
        }

        ZAKOCommand.field_10++;
        break;
    case 5:
        if ( ZAKOCommand.field_10 == 60 )
        {
            if ( ZAKOCommand.procs[ 2 ] >= 0 )
            {
                GCL_ExecProc( ZAKOCommand.procs[ 2 ], NULL );
            }

            ZAKO_GameFlag = 6;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 6:
        if ( ZAKOCommand.field_10 == 30 && ZAKOCommand.procs[ 3 ] >= 0 )
        {
            GCL_ExecProc( ZAKOCommand.procs[ 3 ], NULL );
        }

        if ( ZAKOCommand.field_10 == 180 && ZAKOCommand.procs[ 4 ] >= 0 )
        {
            GCL_ExecProc( ZAKOCommand.procs[ 4 ], NULL );
        }

        if ( ZAKOCommand.field_10 > 182 )
        {
            CloseCinemaScreen();
            GM_GameStatus &= ~( STATE_PADRELEASE | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_RADIO_OFF );
            ZAKO_GameFlag = 8;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 8:
        if ( reset > 12 && reset < 15 )
        {
            ZAKO_GameFlag = 9;
            ZAKOCommand.field_10 = 0;
        }

        ZAKOCommand.field_10++;
        break;
    case 9:
        if ( reset > 14 )
        {
            ZAKO_GameFlag = 10;
            ZAKOCommand.field_10 = 0;
        }
        break;
    case 10:
        ZAKOCommand.field_10++;
        if ( ZAKOCommand.field_10++ > 30 )
        {
            ZAKO_GameFlag = 11;
            ZAKOCommand.field_10 = 0;
        }
        break;
    case 11:
        ZAKOCommand.field_10++;
        if ( ZAKOCommand.field_10++ > 220 )
        {
            ZAKO_GameFlag = 12;
        }
        break;
    case 12:
        if ( reset > 16 )
        {
            ZAKO_GameFlag = 13;
            ZAKOCommand.field_10 = 0;
        }
        break;
    case 13:
        if ( ZAKOTOPCOMMAND.mode == 0 )
        {
            ZAKO_GameFlag = 14;
            ZAKOCommand.field_10 = 0;

            for ( i = 0; i < 8; i++ )
            {
                if ( ZAKOCommand.watchers[ i ].work != NULL )
                {
                    ZAKO_GameFlag = 13;
                }
            }
        }
        break;
    case 14:
        if ( ZAKOCommand.field_10 > 30 )
        {
            ZAKO_GameFlag = 15;
        }

        ZAKOCommand.field_10++;
        break;
    case 15:
        break;
    }
}

/*---------------------------------------------------------------------------*/

static void Act( CommanderWork *work )
{
    GameFlagChk();
    ZakoCom_800D4DD4();
    s03d_800D4CE0( work );

    ZAKOCommand.field_C++;
    ZakoCom_800D41C0();

    if ( ZAKO_GameFlag == 15 )
    {
        GV_DestroyActor( work );
    }
}

static void Die( CommanderWork *work )
{
    if ( ZAKOCommand.end_proc >= 0 )
    {
        GCL_ExecProc( ZAKOCommand.end_proc, NULL );
    }
}

/*---------------------------------------------------------------------------*/

static int GetInts( char *opt, int *out )
{
    int i;
    char *str;

    i = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        *out = GCL_StrToInt( str );
        out++;
        i++;
    }

    return i;
}

static int SetSoundCom( void )
{
    char *opt;

    opt = GCL_GetOption( 's' );
    if ( opt == NULL ) return 0;

    if ( GetInts( opt, ZAKOCommand.sounds ) < 4 ) return 0;

    fprintf( 0, "Err Err Err Sound Buff Over !!\n" );
    return -1;
}

static int GetProcs( void )
{
    int i;
    char *opt;

    for ( i = 0; i < 8; i++ )
    {
        ZAKOCommand.procs[ i ] = -1;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while ( opt != NULL )
    {
        if ( i >= 8 ) return -1;
        ZAKOCommand.procs[ i ] = GCL_StrToInt( opt );
        opt = GCL_NextStr();
        i++;
    }

    return i;
}

static void GetResources( void *work, int name, int where )
{
    int i;
    char *opt;

    ZAKO_Unknown = 0;
    ZAKO_GameFlag = 0;

    ZAKOCommand.field_20 = 0;
    ZAKOCommand.field_18 = 0;

    ZAKO_VibTime = 0;

    ZAKOCommand.reset_enemy_num = 0;
    ZAKOCommand.field_10 = 0;

    SetSoundCom();
    GM_InitHomingSystem();

    for ( i = 0; i < 8; i++ )
    {
        ZAKOCommand.watchers[ i ].field_0 = 0;
        ZAKOCommand.watchers[ i ].field_4 = 0;
        ZAKOCommand.watchers[ i ].field_8 = 0;
        ZAKOCommand.watchers[ i ].work = NULL;
    }

    for ( i = 0; i < 8; i++ )
    {
        ZAKOCommand.order[ i ] = i;
    }

    ZAKOCommand.field_C = 0;
    ZAKOCommand.field_1C = 0;

    ZAKOTOPCOMMAND.mode = 0;
    ZAKOTOPCOMMAND.alert = 0;

    ZAKOCommand.map = GM_GetMap( where );

    if ( GCL_GetOption( 'e' ) )
    {
        ZAKOCommand.end_proc = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKOCommand.end_proc = -1;
    }

    GetProcs();

    if ( GCL_GetOption( 'b' ) )
    {
        ZAKOCommand.field_144 = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKOCommand.field_144 = -1;
    }

    opt = GCL_GetOption( 'v' );
    if ( opt != NULL )
    {
        ZAKOCommand.n_zones = ZakoCom_800D4284( opt, ZAKOCommand.zones );
    }
    else
    {
        ZAKOCommand.n_zones = 1;
        ZAKOCommand.zones[ 0 ] = 0;
    }

    for ( i = 0; i < ZAKOCommand.n_zones; i++ )
    {
        fprintf( 1, "zone=%d ", ZAKOCommand.zones[ i ] );
    }

    ZAKOCommand.c_reset_pos = 0;
    ZAKO_GameStatus = 0;

    opt = GCL_GetOption( 'j' );
    if ( opt != NULL )
    {
        ZAKOCommand.joint_data.n_joints = ReadMapJdata( opt, &ZAKOCommand.joint_data );
    }
    else
    {
        ZAKOCommand.joint_data.n_joints = 1;
        ZAKOCommand.joint_data.joints[ 0 ].map = 0;
        ZAKOCommand.joint_data.joints[ 0 ].zone = 0;
    }

    ZAKOCommand.joint_data.map = where;
    ZAKOCommand.count = 0;

    opt = GCL_GetOption( 'n' );
    if ( opt != NULL )
    {
        ZAKOCommand.count = InitWorkCom( opt );
    }

    ZAKOCommand.field_0 = 0;
    ZAKOCommand.field_4 = 0;
    ZAKOCommand.field_110 = 0;
}

/*---------------------------------------------------------------------------*/

void *NewZakoCommander( int name, int where )
{
    CommanderWork *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof(CommanderWork) );
    if ( work != NULL )
    {
        GV_SetNamedActor( work, Act, Die, "zakocom.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
