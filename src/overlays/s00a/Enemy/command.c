#include "command.h"
#include "enemy.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"
#include "Game/map.h"
#include "SD/g_sound.h"
#include "strcode.h"

int SECTION("overlay.bss") s00a_dword_800E0CA0;
int SECTION("overlay.bss") s00a_dword_800E0CA4;
int SECTION("overlay.bss") s00a_dword_800E0CA8;
int SECTION("overlay.bss") s00a_dword_800E0CAC;

GM_Camera SECTION("overlay.bss") s00a_dword_800E0CB0;

int SECTION("overlay.bss") s00a_dword_800E0D2C;
int SECTION("overlay.bss") s00a_dword_800E0D30;
int SECTION("overlay.bss") s00a_dword_800E0D34;

SVECTOR SECTION("overlay.bss") s00a_dword_800E0D38;

int SECTION("overlay.bss") COM_PlayerOnZone_800E0D40;

int SECTION("overlay.bss") COM_NoiseMinDisID_800E0D44;

SVECTOR SECTION("overlay.bss") COM_PlayerPositionOne_800E0D48[8];

int SECTION("overlay.bss") COM_SHOOTRANGE_800E0D88;
int SECTION("overlay.bss") COM_EYE_LENGTH_800E0D8C;
int SECTION("overlay.bss") COM_PlayerAddress_800E0D90;
unsigned int SECTION("overlay.bss") ENE_SPECIAL_FLAG_800E0D94;

ENEMY_COMMAND SECTION("overlay.bss")  EnemyCommand_800E0D98;

int SECTION("overlay.bss") COM_PlayerMap_800E0F1C;

TOPCOMMAND_STRUCT SECTION("overlay.bss") TOPCOMMAND_800E0F20;

TOPCOMMAND_STRUCT SECTION("overlay.bss") s00a_dword_800E0F28;

SVECTOR SECTION("overlay.bss")  COM_PlayerPosition_800E0F30;

int SECTION("overlay.bss") COM_NOISEMODE_DIS_800E0F38;

unsigned int SECTION("overlay.bss") COM_GameStatus_800E0F3C;

int SECTION("overlay.bss") COM_PlayerAddressOne_800E0F40[8];

int SECTION("overlay.bss") COM_ALERT_DECREMENT_800E0F60;

int SECTION("overlay.bss") GM_GameFlag_800E0F64;

int SECTION("overlay.bss") COM_VibTime_800E0F68;

int SECTION("overlay.bss") s00a_dword_800E0F6C;

int SECTION("overlay.bss") COM_PlayerMapOne_800E0F70[8];

extern int       GV_Time;
extern SVECTOR   DG_ZeroVector;
extern int       GM_PlayerAddress_800AB9F0;
extern SVECTOR   GM_NoisePosition_800AB9F8;
extern int       GM_PlayerMap_800ABA0C;
extern SVECTOR   GM_PlayerPosition_800ABA10;
extern OBJECT   *GM_PlayerBody_800ABA20;
extern int       GM_event_camera_flag_800ABA9C;
extern CONTROL  *GM_WhereList_800B56D0[94];
extern GM_Camera GM_Camera_800B77E8;

SVECTOR ENEMY_TARGET_SIZE_800C35A4  = { 300, 1000, 300 };
SVECTOR ENEMY_TARGET_FORCE_800C35AC = { 0, 0, 0 };
SVECTOR ENEMY_ATTACK_SIZE_800C35B4  = { 800, 500, 800 };
SVECTOR ENEMY_ATTACK_FORCE_800C35BC = { 100, 0, 0 };
SVECTOR ENEMY_TOUCH_SIZE_800C35C4   = { 300, 800, 300 };
SVECTOR ENEMY_TOUCH_FORCE_800C35CC  = { 0, 0, 0, 0 };
SVECTOR COM_NO_POINT_800C35D4       = { 30000, 30000, 30000 };

unsigned char s00a_dword_800C35DC[4] = { 1,   1, 0, 0 };
unsigned char s00a_dword_800C35E0[4] = { 255, 1, 0, 0 };

int s00a_dword_800C35E4[] = {
    0x000009C4,
    0x00000DAC,
    0x00000FA0,
    0x00001388,
    0x0000157C,
    0x000015E0,
    0x00001644,
    0x000016A8
};

const char aCresetposd_800E07FC[] = " c_reset_pos = %d \n";
const char aKottida_800E0810[] = "kottida !!\n";

void GM_AlertModeSet( int );
void NewPadVibration_8005D58C( unsigned char *ptr, int flags );

int s00a_command_800CEA2C( WatcherWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0xC8[i].watcher == 0 )
        {
            EnemyCommand_800E0D98.field_0xC8[i].watcher = work; //update to be a struct with watcher ptr as 4th attribute
            EnemyCommand_800E0D98.field_0xC8[i].field_04 = 2;
            COM_PlayerAddressOne_800E0F40[i] = -1;
            return i;
        }
    }

    return -1;
}

void s00a_command_800CEA84( int idx, int val )
{
    EnemyCommand_800E0D98.field_0x148[ idx ] = val;
}

int s00a_command_800CEA9C( int val )
{
    int i;
    for ( i = 0 ; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0x148[i] == val )
        {
            return 1;
        }
    }
    return 0;
}

void ENE_SetTopCommAL_800CEAE8( int alert )
{
    TOPCOMMAND_800E0F20.alert = alert;
}

void ENE_SetTopCommMD_800CEAF4( int mode )
{
    TOPCOMMAND_800E0F20.mode = mode;
}

void ENE_SetGopointLast_800CEB00(void)
{
    EnemyCommand_800E0D98.com_addr = COM_PlayerAddress_800E0D90;
    EnemyCommand_800E0D98.com_pos  = COM_PlayerPosition_800E0F30;
    EnemyCommand_800E0D98.com_map  = COM_PlayerMap_800E0F1C;
    EnemyCommand_800E0D98.field_0x40 = 1;
}

void s00a_command_800CEB54(void)
{
    EnemyCommand_800E0D98.com_addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[0]->map->hzd, &GM_NoisePosition_800AB9F8, -1 );
    EnemyCommand_800E0D98.com_pos = GM_NoisePosition_800AB9F8;
    EnemyCommand_800E0D98.com_map = GM_PlayerMap_800ABA0C;
}

int s00a_command_800CEBCC( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &EnemyCommand_800E0D98.field_0xA4;

    if ( unk->map_id == map_id )
    {
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[i].field_00 == val )
            {
                return unk->field_04[i].field_02;
            }
        }
        goto end;
    }
    return 0;
end:
    return -1;
}

void s00a_command_800CEC40( SVECTOR *mov , int flag )
{
    s00a_dword_800E0D38.vx = mov->vx;
    s00a_dword_800E0D30 |= 1 | flag;
    s00a_dword_800E0D38.vy = mov->vy;
    s00a_dword_800E0D38.vz = mov->vz;

    if ( s00a_dword_800E0CA0 == 0 )
    {
        s00a_dword_800E0CA0 = 32;
    }
}

void s00a_command_800CEC90( void )
{
    if ( COM_VibTime_800E0F68 > 0 )
    {
        NewPadVibration_8005D58C( s00a_dword_800C35DC, 1 );
        NewPadVibration_8005D58C( s00a_dword_800C35E0, 2 );
        COM_VibTime_800E0F68--;
        return;
    }

    COM_VibTime_800E0F68 = 0;
}

void s00a_command_800CECF4(void)
{
    if ( s00a_dword_800E0CA0 == 32 )
    {
         GM_SeSet2( 0, 0x3F, SE_EXCLAMATION );
    }

    s00a_dword_800E0CA0--;

    if ( s00a_dword_800E0CA0 < 0 )
    {
        s00a_dword_800E0CA0 = 0;
    }
}

void s00a_command_800CED48( void )
{
    int i;
    for ( i = 0; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        EnemyCommand_800E0D98.field_0x148[i] = 255;
    }
}

int s00a_command_800CED88( char *ops, A4_STRUCT *unk )
{
    int i;
    i = 0;

    do {
        unk->field_04[i].field_00 = GCL_StrToInt( GCL_GetParamResult() );
        unk->field_04[i].field_02 = GCL_StrToInt( GCL_GetParamResult() );
        i++;
    } while ( GCL_GetParamResult() != NULL );


    return i;
}

int s00a_command_800CEDE8( char *ops, short *addr, int map_id )
{
    int i;
    MAP *map;
    SVECTOR svec;
    unsigned char *res;
    map = Map_FromId_800314C0( map_id );

    for ( i = 0; ( res = GCL_GetParamResult() ) && i < 4 ; i++ )
    {
        GCL_StrToSV( res, &svec );

        if ( svec.vy < 30000 )
        {
            addr[i] = HZD_GetAddress_8005C6C4( map->hzd, &svec, -1 ) & 0xFF;
        }
        else
        {
            addr[i] = 255;
        }
    }

    return i;
}

void s00a_command_800CEE98(void)
{
    int i;
    int s0;
    int dist2;
    int total;
    int delta;
    short dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;

    i = 0;
    delta = GV_Time % EnemyCommand_800E0D98.field_0x54;
    total = EnemyCommand_800E0D98.field_0x54;
    reset_pos = 0;

    for ( ; i < total ; i++  )
    {
        s0 = i + delta;
        if ( s0 >= total )
        {
            s0 -= total;
        }

        zone = &EnemyCommand_800E0D98.map->hzd->f00_header->navmeshes[ EnemyCommand_800E0D98.field_0x58[ s0 ] ];

        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition_800ABA10.vy;
        svec.vz = zone->z;

        dist1 =  10000;
        dist2 = GV_DiffVec3( &svec, &GM_PlayerPosition_800ABA10 );
        if ( dist1 < dist2 )
        {
            reset_pos = s0;
            break;
        }

    }

    EnemyCommand_800E0D98.c_reset_pos = reset_pos;
    fprintf( 1, aCresetposd_800E07FC, reset_pos );
}


int s00a_command_800CEFE4( int val )
{
    return  EnemyCommand_800E0D98.field_0x0C % val;
}

void s00a_command_800CF024( int *val )
{
    if ( COM_GameStatus_800E0F3C & 1 )
    {
        *val = 0x82;
    }
    else
    {
        *val = 0x80;
    }
}

void s00a_command_800CF050( int *val )
{
    *val = 0x87;
}

void s00a_command_800CF05C( int *val )
{
    *val = 0x8B;
}

void s00a_command_800CF068( int *val )
{
    *val = 0x8A;
}

void s00a_command_800CF074( int *val )
{
    *val = 0x86;
}

void s00a_command_800CF080( int* val )
{
    switch( s00a_command_800CEFE4( 3 ) )
    {
    case 0:
        *val = 0x82;
        break;
    case 1:
    case 2:
        *val = 0x81;
        break;
    }
}

void s00a_command_800CF0CC( int *val )
{
    *val = 0x85;
}

void s00a_command_800CF0D8( int* val )
{
    switch ( s00a_command_800CEFE4( 2 ) )
    {
    case 0:
        fprintf( 1, aKottida_800E0810 );
        *val = 0x81;
        return;
    case 1:
        *val = 0;
        return;
    }
}


int s00a_command_800CF13C( int val )
{
    switch( val )
    {
        case 240:
            s00a_command_800CF024( &val );
            break;
        case 241:
            s00a_command_800CF050( &val );
            break;
        case 242:
            s00a_command_800CF05C( &val );
            break;
        case 243:
            s00a_command_800CF068( &val );
            break;
        case 244:
            s00a_command_800CF074( &val );
            break;
        case 245:
            s00a_command_800CF0CC( &val );
            break;
        case 246:
            s00a_command_800CF080( &val );
            break;
        case 247:
            s00a_command_800CF0D8( &val );
            break;
    }

    return val;
}

void s00a_command_800CF200(void)
{
    if ( EnemyCommand_800E0D98.field_0x170 < 6000 && ( mts_get_tick_count() - EnemyCommand_800E0D98.field_0x174 ) > 40 )
    {
       if ( EnemyCommand_800E0D98.field_0x17A && GM_CurrentWeaponId != WEAPON_PSG1 )
       {
           GM_SeSetMode( &GM_PlayerPosition_800ABA10, SE_HEARTBEAT, GM_SEMODE_REAL );
       }
       EnemyCommand_800E0D98.field_0x174 = mts_get_tick_count();
    }
}

void s00a_command_800CF298( ENEMY_COMMAND* command )
{
    int i;
    int t2;
    int t3;
    int t4;
    int dists[8];
    int temp1, temp2;
    int temp3, temp4;
    WatcherWork *work;

    dists[0] = 0x7530;

    for ( i = 0 ; i < command->field_0x08 ; i ++ )
    {
        //WatcherWork *work;
        work = command->field_0xC8[ EnemyCommand_800E0D98.field_0x68[ i ] ].watcher;

        if ( work->act_status & 0x10000000 )
        {
            dists[i] = 0x7530;
        }
        else
        {
            dists[i] = work->sn_dis;
        }
    }


    for ( t3 = command->field_0x08 - 1 ; t3 > -1 ; t3 = t4  )
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

                temp4 = EnemyCommand_800E0D98.field_0x68[ i - 1 ];
                temp3 = EnemyCommand_800E0D98.field_0x68[ i  ];
                t4 = t2;

                EnemyCommand_800E0D98.field_0x68[ i - 1 ] = temp3;
                EnemyCommand_800E0D98.field_0x68[ i ] = temp4;
            }
        }
    }

    EnemyCommand_800E0D98.field_0x170 = dists[0];

    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        //WatcherWork *work;
        work = command->field_0xC8[ EnemyCommand_800E0D98.field_0x68[ i ] ].watcher;
        work->field_BFC = s00a_dword_800C35E4[ i ];
        work->field_C00 = i;
    }
}

void s00a_command_800CF420( ENEMY_COMMAND* command )
{
    int i;
    int dis;
    int sound;
    WatcherWork *work;
    EnemyCommand_800E0D98.field_0x1C--;
    if ( EnemyCommand_800E0D98.field_0x1C < 0 )
    {
        EnemyCommand_800E0D98.field_0x1C = 0;
    }

    if ( EnemyCommand_800E0D98.field_0x1C > 0 )
    {
        return;
    }

    sound = 0;
    dis   = 100000;
    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        if ( command->field_0xC8[ i ].field_04 == 2 )
        {
            work = command->field_0xC8[ i ].watcher;
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
        EnemyCommand_800E0D98.field_0x1C = 0x1E;
        GM_SeSet( NULL, s00a_command_800CF13C( sound ) );
    }
}

const char s00a_aResetmaxdnumd_800E083C[] = "reset max=%d num=%d \n";
const char aGmenemywatchcountd_800E0854[] = " GM_EnemyWatchCount = [%d] \n";
const char aNowzonedrzoned_800E0874[] = " now zone = %d r_zone=%d\n";
const char aNotrestrctedaread_800E0890[] = " ? ? ? Not Restrcted Area [%d] !!!!\n";
const char aErrerrerrnotlinkroutedtod_800E08B8[] = " Err Err Err Not Link Route [%d] to [%d] !!!!\n";
const char aCommanderrnozoneidingclzdidd_800E08E8[] = "command:!!!Err No Zone ID In Gcl z%d id%d!!!!!!!!\n";
const char aCommandcwhereissnake_800E091C[] = "command.c:  Where Is Snake ????\n";
const char aCom_noisemode_disD_800E0940[] = " COM_NOISEMODE_DIS =%d \n";
const char aEeeDDDTD_800E095C[] = "eee %d %d %d t %d \n";

void s00a_command_800CF504( C8_STRUCT* struct_c8 , int i )
{
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = struct_c8->watcher->field_B78 + 1;
        }
        return;
    case 1:
        struct_c8->field_00--;
        if ( !struct_c8->field_00 && struct_c8->watcher->field_B81  )
        {
            struct_c8->field_08 = 2;
            struct_c8->field_00 = 0;
            EnemyCommand_800E0D98.reset_enemy_num++;
        }
        return;
    case 2:
        switch ( EnemyCommand_800E0D98.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( EnemyCommand_800E0D98.field_0x168 & 1 )
            {
                s00a_command_800CEE98();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
        return;
        case TOP_COMM_ALERT:
                if ( EnemyCommand_800E0D98.reset_enemy_num < EnemyCommand_800E0D98.reset_enemy_max + 1  || EnemyCommand_800E0D98.reset_enemy_max == 255 )
                {
                    if ( EnemyCommand_800E0D98.reset_enemy_num < 0 )
                    {
                        EnemyCommand_800E0D98.reset_enemy_num = 0;
                    }

                    s00a_command_800CEE98();
                    struct_c8->field_04 = x;
                    struct_c8->field_08 = 0;
                    printf( s00a_aResetmaxdnumd_800E083C, EnemyCommand_800E0D98.reset_enemy_max, EnemyCommand_800E0D98.reset_enemy_num );
                }
            return;
        }
        return;
    }
}

int s00a_command_800CF688( int a0, int a1 )
{
    if ( a0 < a1 )
    {
        a0 = a1;
    }

    return a0;
}

void s00a_command_800CF6A0( int val, ENEMY_COMMAND* command )
{
    if ( command->alert - val > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = val;
    }

    if ( command->alert < TOPCOMMAND_800E0F20.alert )
    {
        command->alert = TOPCOMMAND_800E0F20.alert;
    }

    ENE_SetTopCommAL_800CEAE8( 0 );
}

void s00a_command_800CF704( ENEMY_COMMAND *command )
{
    int alert;

    switch ( command->mode )
    {
        default:
            TOPCOMMAND_800E0F20.mode = command->mode;
            return;
        case 0:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vx;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vx + 500;
            if ( command->alert >= 255 )
            {
                command->alert = 255;
                GM_AlertModeSet(3);
                command->mode = 1;
                EnemyCommand_800E0D98.reset_enemy_num = 0;
                COM_GameStatus_800E0F3C |= 0x1;

                if ( !( COM_GameStatus_800E0F3C & 2 ) )
                {
                    GM_EnemyWatchCount ++;
                    printf( aGmenemywatchcountd_800E0854, GM_EnemyWatchCount );
                }
                EnemyCommand_800E0D98.field_0x182 = 0;
            }
        break;
        case 1:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vy;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vy + 500;


            if ( command->alert <= 0 )
            {
                GM_AlertModeSet(2);
                command->mode = 2;
                command->field_0x10 = 300;
                GM_SetAlertMax( 0x100 );
                s00a_command_800CED48();
                EnemyCommand_800E0D98.field_0x182 = 1;
                return;
            }
            alert = command->alert;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
        case 2:
            COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vz;
            COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vz + 500;
            command->field_0x10--;
            if ( command->field_0x10 <= 0 )
            {
                GM_AlertModeSet(0);
                command->mode = 0;
                command->field_0x10 = 0;
                EnemyCommand_800E0D98.field_0x180 = 0;
                EnemyCommand_800E0D98.field_0x182 = 0;
            }
            if ( command->alert >= 255 )
            {
                command->alert = 0xFF;
                GM_AlertModeSet(3);
                command->mode = 1;
            }
            alert = command->field_0x10;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
            s00a_command_800CF200();
        break;
    }

    TOPCOMMAND_800E0F20.mode = command->mode;
}

int s00a_command_800CF940( HZD_HDL *hzd, SVECTOR *pos, SVECTOR *pos2 )
{
    int from;
    int to;

    from = HZD_GetAddress_8005C6C4( hzd, pos, -1 );

    //TODO: fix
    do
    {
        to = HZD_GetAddress_8005C6C4( hzd, pos2, -1 );
            do   {
            return HZD_ZoneDistance_8005CD1C( hzd, from & 0xFF, to & 0xFF );
        } while (0);
    } while (0);
}

int s00a_command_800CF9A0( WatcherWork *work, int dis, int idx )
{
    CONTROL *ctrl;
    int      x;

    ctrl = &work->control;

    if ( TOPCOMMAND_800E0F20.mode == 1 )
    {
        goto exit;
    }

    if ( GM_NoisePower_800ABA24 != 0x64 )
    {
        goto exit;
    }


    if ( EnemyCommand_800E0D98.field_0xC8[ idx ].watcher->act_status & 0x10000028 )
    {
       goto exit;
    }

    if ( GV_DiffVec3( &GM_NoisePosition_800AB9F8, &ctrl->mov ) >= COM_NOISEMODE_DIS_800E0F38 )
    {
        goto exit;
    }

    x = s00a_command_800CF940( ctrl->map->hzd, &ctrl->mov, &GM_NoisePosition_800AB9F8 );

    if ( x < 300 && x < dis )
    {
        COM_NoiseMinDisID_800E0D44 = idx;
        dis = x;
    }

    exit:
    return dis;
}

void s00a_command_800CFA94( CommanderWork* work )
{
    int i;
    int dis;
    int alert;
    WatcherWork *watcher;

    alert = 0;
    dis = 0x7530;

    COM_NoiseMinDisID_800E0D44 = -1;
    EnemyCommand_800E0D98.field_0x98 = 0;

    for ( i = 0; i < EnemyCommand_800E0D98.field_0x08; i++ )
    {
        if ( EnemyCommand_800E0D98.field_0xC8[ i ].field_04 == 2 )
        {
            watcher = EnemyCommand_800E0D98.field_0xC8[ i ].watcher;
            alert =  s00a_command_800CF688( alert, watcher->alert_level );
            dis   =  s00a_command_800CF9A0( watcher, dis, i );
            if ( !watcher->faseout )
            {
                EnemyCommand_800E0D98.field_0x98++;
            }
        }
        else if ( EnemyCommand_800E0D98.field_0xC8[ i ].field_04 == 1 )
        {
            s00a_command_800CF504( &EnemyCommand_800E0D98.field_0xC8[ i ], i );
        }
    }

    s00a_command_800CF420( &EnemyCommand_800E0D98 );
    s00a_command_800CF6A0( alert, &EnemyCommand_800E0D98 );
    s00a_command_800CF704( &EnemyCommand_800E0D98 );
    s00a_command_800CF298( &EnemyCommand_800E0D98 );

    if ( EnemyCommand_800E0D98.field_0x98 == 0 )
    {
        s00a_dword_800E0D30 |= 2;
        if ( EnemyCommand_800E0D98.field_0x17C >= 0 )
        {
            GCL_ExecProc( EnemyCommand_800E0D98.field_0x17C, NULL );
            EnemyCommand_800E0D98.field_0x17C = -1;
        }
    }

    EnemyCommand_800E0D98.field_0x168 = 0;
}

int s00a_command_800CFC04( WatcherWork *work, HZD_ZON* zone )
{
    int i;
    for ( i = 0; i < work->field_C34 ; i++ )
    {
        if ( zone->padding == work->field_C35[i] )
        {
            return 1;
        }
    }
    return 0;
}

int s00a_command_800CFC4C( WatcherWork* work, int r_zone )
{
    int addr;
    SVECTOR pos;
    HZD_HDL *hzd;
    CONTROL *ctrl;
    HZD_ZON *zone;
    int route_addr;
    int l_zone_shift;
    int r_zone_shift;

    ctrl = &work->control;
    hzd = ctrl->map->hzd;
    addr = HZD_GetAddress_8005C6C4( hzd, &ctrl->mov, -1 ) & 0xFF;

    zone = &hzd->f00_header->navmeshes[ addr ];

    pos.vx = zone->x;
    pos.vy = zone->y;
    pos.vz = zone->z;

    r_zone_shift = HZD_addr_shift( r_zone );

    for (;;)
    {
        printf( aNowzonedrzoned_800E0874, addr, r_zone );

        l_zone_shift = HZD_addr_shift( addr );

        route_addr = HZD_LinkRoute_8005C974( hzd,  l_zone_shift, r_zone_shift, &pos );

        if ( route_addr == addr )
        {
            if ( addr == r_zone )
            {
                printf( aNotrestrctedaread_800E0890, addr );
                return addr;
            }

            printf( aErrerrerrnotlinkroutedtod_800E08B8, addr, r_zone );
            return addr;
        }

        zone = &hzd->f00_header->navmeshes[ route_addr ];

        if ( !s00a_command_800CFC04( work, zone ) )
        {
            pos.vx = zone->x;
            pos.vy = zone->y;
            pos.vz = zone->z;
            addr = route_addr;
        }
        else
        {
            return addr;
        }
    }
}

void s00a_command_800CFDC8( WatcherWork* work, int addr, int idx )
{
    MAP *map;
    SVECTOR *pos;
    HZD_ZON *zone;
    HZD_ZON *zone2;
    HZD_HDL *hzd;
    COM_PlayerAddressOne_800E0F40[ idx ] = (addr | addr << 8);

    hzd = work->control.map->hzd;
    zone2 = &hzd->f00_header->navmeshes[ addr ];
    zone = zone2;

    pos = &COM_PlayerPositionOne_800E0D48[ idx ];

    pos->vx = zone->x;
    pos->vy = zone->y;
    pos->vz = zone->z;

    map = Map_FindByZoneId_80031624( 1 << zone->padding );

    if ( map != NULL )
    {
        COM_PlayerMapOne_800E0F70[ idx ] = map->index;
    }
    else
    {
        printf( aCommanderrnozoneidingclzdidd_800E08E8, addr, zone->padding );
    }
}

void s00a_command_800CFEA8( void )
{
    int i; //s2
    int addr;
    int addr2;
    int check;
    int ret_addr;
    WatcherWork *work;

    addr = GM_PlayerAddress_800AB9F0 & 0xFF;
    addr2 = ( GM_PlayerAddress_800AB9F0 >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        COM_PlayerAddress_800E0D90  = GM_PlayerAddress_800AB9F0;
        COM_PlayerPosition_800E0F30 = GM_PlayerPosition_800ABA10;
        COM_PlayerMap_800E0F1C      = GM_PlayerMap_800ABA0C;
    }

    if ( addr == 0xFF || addr2 == 0xFF )
    {
        COM_PlayerOnZone_800E0D40 = 0;
    }
    else
    {
        COM_PlayerOnZone_800E0D40 = 1;
    }

    for ( i = 0; i < EnemyCommand_800E0D98.field_0x08 ; i++ )
    {
        work = EnemyCommand_800E0D98.field_0xC8[ i ].watcher;

        if ( addr == addr2 && addr != 0xFF )
        {

            check = 0;
            if ( !work->field_C34  || !s00a_command_800CFC04( work, &work->control.map->hzd->f00_header->navmeshes[ addr ] ) )
            {
                check = 1;
            }

            if ( check )
            {
                COM_PlayerAddressOne_800E0F40[ i ]  = GM_PlayerAddress_800AB9F0;
                COM_PlayerPositionOne_800E0D48[ i ] = GM_PlayerPosition_800ABA10;
                COM_PlayerMapOne_800E0F70[ i ]      = GM_PlayerMap_800ABA0C;
            }
        }

        if ( COM_PlayerAddressOne_800E0F40[ i ] == -1 )
        {
            if ( addr != 0xFF )
            {
                check = s00a_command_800CFC04( work, &work->control.map->hzd->f00_header->navmeshes[ addr ] );

                if ( check )
                {
                    ret_addr = s00a_command_800CFC4C( work, addr );
                    s00a_command_800CFDC8( work, ret_addr, i );
                }
                else
                {
                    s00a_command_800CFDC8( work, addr, i );
                }
            }
            else
            {
                printf( aCommandcwhereissnake_800E091C );
            }
        }

    }
}

int s00a_command_800D0128( char *arg0 )
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
            res = GCL_GetParamResult();
            GCL_ExecProc( proc_id, NULL );
            i++;
        } while ( res );
    }
    return i;
}

void s00a_command_800D018C( CommanderWork* work )
{
    GV_MSG *msg;
    int count;

    count = GV_ReceiveMessage( work->name, &msg );

    for (; count > 0; count--, msg++)
    {
        switch (msg->message[0])
        {
        case HASH_SOUND_ON:
            EnemyCommand_800E0D98.field_0x17A = 1;
            break;

        case HASH_SOUND_OFF:
            EnemyCommand_800E0D98.field_0x17A = 0;
            break;
        }
    }
}

void s00a_command_800D0218(void)
{
    if ( EnemyCommand_800E0D98.field_0x182 && GM_NoisePower_800ABA24 == 0xFF )
    {
        EnemyCommand_800E0D98.field_0x182 = 0;
        EnemyCommand_800E0D98.field_0x180++;
    }
}

void CommandAct_800D0258( CommanderWork* work )
{
    if (GM_CheckMessage( &work->actor , work->name, HASH_KILL) != NULL)
    {
        GV_DestroyActor( &work->actor );
        return;
    }

    s00a_command_800D018C( work );
    s00a_command_800D0344();
    s00a_command_800CFEA8();
    s00a_command_800D0218();
    s00a_command_800CFA94( work );
    s00a_command_800CEC90();
    s00a_command_800CECF4();
    EnemyCommand_800E0D98.field_0x0C++;
}

void CommandDie_800D02EC( void )
{
    return;
}

void s00a_command_800D02F4(void)
{
    if ( GM_PlayerBody_800ABA20->objs->bound_mode == 2 )
    {
        GM_Camera_800B77E8.track = GV_NearExp8( GM_Camera_800B77E8.track, 4000 );
    }
}

void s00a_command_800D0344(void)
{
    int flag;
    if ( !( COM_GameStatus_800E0F3C & 0x1000 ) )
    {
        return;
    }

    if ( s00a_dword_800E0D2C > 4 )
    {
        if ( !( GM_Camera_800B77E8.flags & 3 ) )
        {
            s00a_dword_800E0CB0 = GM_Camera_800B77E8;
            flag = 0x40;
            if ( !GM_event_camera_flag_800ABA9C )
            {
                flag = 0x80;
            }
            GM_Camera_800B77E8.flags |= ( 2 | flag );
            GM_SetCameraCallbackFunc_8002FD84( 1, s00a_command_800D02F4 );
        }
    }
    s00a_dword_800E0D2C++;
}

void SetCameraActCall_800D043C()
{
    if ( COM_GameStatus_800E0F3C & 0x1000 ) return;

    COM_GameStatus_800E0F3C |= 0x1000 ;
    GM_GameStatus  |= STATE_PADRELEASE ;
    s00a_dword_800E0D2C = 0 ;

}

void UnsetCameraActCall_800D047C()
{
    if ( !( COM_GameStatus_800E0F3C & 0x1000 ) ) return;

    COM_GameStatus_800E0F3C &= ~( 0x1000 ) ;
    GM_GameStatus  &= ~( STATE_PADRELEASE ) ;

    GM_SetCameraCallbackFunc_8002FD84( 1, NULL ) ;
    s00a_dword_800E0D2C = 0 ;
    GM_Camera_800B77E8.flags &= ~( 2 ) ;
}

void CommandGetResources_800D04F4( CommanderWork *work, int name, int where )
{
    int i;
    char *ops;

    work->name = name;

    GM_GameFlag_800E0F64  = 0;
    EnemyCommand_800E0D98.field_0x17A = 1;

    COM_PlayerAddress_800E0D90  = 0;
    EnemyCommand_800E0D98.alert  = 0;
    EnemyCommand_800E0D98.field_0x170 = 0;


    EnemyCommand_800E0D98.field_0x180 = 0;
    EnemyCommand_800E0D98.field_0x182 = 0;
    EnemyCommand_800E0D98.field_0x40  = 0;

    COM_PlayerPosition_800E0F30 = DG_ZeroVector;
    COM_PlayerMap_800E0F1C = where;
    COM_VibTime_800E0F68 = 0;
    s00a_dword_800E0CA0 = 0;
    s00a_dword_800E0D30 = 0;
    s00a_dword_800E0D2C = 0;

    for ( i = 0 ; i < 8 ; i++ )
    {
        EnemyCommand_800E0D98.field_0xC8[i].field_00  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].field_04  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].field_08  = 0;
        EnemyCommand_800E0D98.field_0xC8[i].watcher   = 0;
    }

    for ( i = 0 ; i < 8 ; i++ )
    {
        EnemyCommand_800E0D98.field_0x68[i]  = i;
        EnemyCommand_800E0D98.field_0x20[i]  = 0;
        EnemyCommand_800E0D98.field_0x148[i] = 0xFF;
    }
    //v_option( where );
    EnemyCommand_800E0D98.field_0x0C = 0;
    EnemyCommand_800E0D98.mode       = 0;

    TOPCOMMAND_800E0F20.mode = 0;
    TOPCOMMAND_800E0F20.alert= 0;
    EnemyCommand_800E0D98.map = Map_FromId_800314C0( where );

    ops = GCL_GetOption( 'v' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x54 = s00a_command_800CEDE8( ops, EnemyCommand_800E0D98.field_0x58 , where );
    }
    else
    {
        EnemyCommand_800E0D98.field_0x54 = 1;
        EnemyCommand_800E0D98.field_0x58[0] = 0;
    }

    EnemyCommand_800E0D98.reset_enemy_max = 5;

    ops = GCL_GetOption( 'b');
    if ( ops )
    {
        EnemyCommand_800E0D98.reset_enemy_max = GCL_StrToInt( ops );
    }

    EnemyCommand_800E0D98.field_0x88.vx = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vy = 0xFA0;
    EnemyCommand_800E0D98.field_0x88.vz = 0xFA0;

    ops = GCL_GetOption( 'l' );
    if ( ops )
    {
        GCL_StrToSV( ops, &EnemyCommand_800E0D98.field_0x88 );
    }

    //loc_800D06A0:
    COM_NOISEMODE_DIS_800E0F38 = 0x1F40;

    ops = GCL_GetOption( 'y' );
    if ( ops )
    {
        COM_NOISEMODE_DIS_800E0F38 = GCL_StrToInt( ops );
    }

    printf( ( void* )&aCom_noisemode_disD_800E0940 , COM_NOISEMODE_DIS_800E0F38 );
    EnemyCommand_800E0D98.field_0x88.pad = 0;

    ops = GCL_GetOption( 't' );
    if ( ops ) {
        EnemyCommand_800E0D98.field_0x88.pad = GCL_StrToInt( ops );
    }

    switch ( EnemyCommand_800E0D98.field_0x88.pad )
    {
        case 0:
            COM_ALERT_DECREMENT_800E0F60 = 4;
            break;
        case 1:
            COM_ALERT_DECREMENT_800E0F60 = 3;
            break;
        case 2:
            COM_ALERT_DECREMENT_800E0F60 = EnemyCommand_800E0D98.field_0x88.pad;
            break;
        default:
            COM_ALERT_DECREMENT_800E0F60 = 4;
    }

    printf( ( void* )&aEeeDDDTD_800E095C, EnemyCommand_800E0D98.field_0x88.vx, EnemyCommand_800E0D98.field_0x88.vy, EnemyCommand_800E0D98.field_0x88.vz, COM_ALERT_DECREMENT_800E0F60  );

    EnemyCommand_800E0D98.field_0x1C  = 0x1E;
    EnemyCommand_800E0D98.c_reset_pos = 0;
    EnemyCommand_800E0D98.field_0x16C = 0;
    EnemyCommand_800E0D98.field_0x174 = 0;

    s00a_dword_800E0F28.mode = 0;
    EnemyCommand_800E0D98.field_0x178 = 0;
    COM_EYE_LENGTH_800E0D8C = EnemyCommand_800E0D98.field_0x88.vx;
    COM_SHOOTRANGE_800E0D88 = EnemyCommand_800E0D98.field_0x88.vx + 0x1F4;

    ops = GCL_GetOption( 'w' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x178 = GCL_StrToInt( ops );
    }

    ops = GCL_GetOption( 'z' );
    if ( ops )
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x17C) = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        *(int*)(&EnemyCommand_800E0D98.field_0x17C) = -1;
    }

    COM_GameStatus_800E0F3C = 0;

    ops = GCL_GetOption( 'a' );
    if ( ops )
    {
        COM_GameStatus_800E0F3C |= GCL_StrToInt( ops );
    }

    ops = GCL_GetOption( 'j' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0xA4.n_entry = s00a_command_800CED88( ops, &EnemyCommand_800E0D98.field_0xA4 );
    }
    else
    {
        EnemyCommand_800E0D98.field_0xA4.n_entry = 1;
        EnemyCommand_800E0D98.field_0xA4.field_04->field_00 = 0;
        EnemyCommand_800E0D98.field_0xA4.field_04->field_02 = 0;
    }

    EnemyCommand_800E0D98.field_0xA4.map_id  = where;
    EnemyCommand_800E0D98.field_0x08 = 0;

    ops = GCL_GetOption( 'n' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 = s00a_command_800D0128( ops );
    }

    ops = GCL_GetOption( 'm' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x08 += s00a_command_800D0128( ops );
    }

    EnemyCommand_800E0D98.field_0x00 = 0;

    ops = GCL_GetOption( 'c' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x00 = s00a_command_800D0128( ops );
    }

    EnemyCommand_800E0D98.field_0x04 = 0;

    ops = GCL_GetOption( 's' );
    if ( ops )
    {
        EnemyCommand_800E0D98.field_0x04 = s00a_command_800D0128( ops );
    }
}

GV_ACT *NewCommand_800D0908(int name, int where, int argc, char **argv)
{
    CommanderWork *work ;

    work = (CommanderWork *)GV_NewActor( 4, sizeof( CommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( TActorFunction )CommandAct_800D0258, ( TActorFunction )CommandDie_800D02EC, "command.c" );
        CommandGetResources_800D04F4( work, name, where );
    }
    return &work->actor;
}
