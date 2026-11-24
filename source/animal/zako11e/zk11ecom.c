#include "enemy/enemy.h"

#include <stdio.h>
#include "mts/mts.h" // for fprintf

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO11E_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO11E_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO11E_ATTACK_SIZE = {800, 500, 800};
SVECTOR ZAKO11E_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO11E_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO11E_TOUCH_FORCE = {0, 0, 0};
SVECTOR ZAKO11E_NO_POINT = {30000, 30000, 30000};
int     ZAKO11E_EYE_LENGTH = 4000;

SVECTOR SECTION(".bss") ZAKO11E_PlayerPosition;
ZAKO_COMMAND SECTION(".bss") ZAKO11ECommand;
TOPCOMMAND_STRUCT SECTION(".bss") ZAKO11ETOPCOMMAND;
int SECTION(".bss") ZAKO11E_GameStatus;
int SECTION(".bss") ZAKO11E_GameFlag;
int SECTION(".bss") ZAKO11E_PlayerAddress;
int SECTION(".bss") ZAKO11E_PlayerMap;

/*---------------------------------------------------------------------------*/

static int ChaseDis[] = {
    3000, 4000, 7000, 8000,
    8000, 8000, 8000, 8000,
};

static int SoundPlayTime = 0;

/*---------------------------------------------------------------------------*/

int s11e_zk11ecom_800D9A20( ZakoWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( ZAKO11ECommand.field_0x8C[ i ].watcher == 0 )
        {
            ZAKO11ECommand.field_0x8C[ i ].watcher = ( WatcherWork * )work;
            ZAKO11ECommand.field_0x8C[ i ].field_04 = 2;
            return i;
        }
    }
    return -1;
}

void s11e_zk11ecom_800D9A64( int idx )
{
    ZAKO11ECommand.field_0x8C[ idx ].watcher  = 0;
    ZAKO11ECommand.field_0x8C[ idx ].field_04 = 1;
}

void ZAKO11E_SetTopCommAL_800D9A84( int alert )
{
    ZAKO11ETOPCOMMAND.alert = alert;
}

void ZAKO11E_SetTopCommMD_800D9A90( int mode )
{
    ZAKO11ETOPCOMMAND.mode = mode;
}

void ZAKO11E_SetGoPointLast_800D9A9C( void )
{
    ZAKO11ECommand.com_addr = ZAKO11E_PlayerAddress;
    ZAKO11ECommand.com_pos  = ZAKO11E_PlayerPosition;
    ZAKO11ECommand.com_map  = ZAKO11E_PlayerMap;
}

void s11e_zk11ecom_800D9AE8(void)
{
    ZAKO11ECommand.com_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKO11ECommand.com_pos  = GM_NoisePosition;
    ZAKO11ECommand.com_map  = GM_PlayerMap;
}

int s11e_zk11ecom_800D9B60( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &ZAKO11ECommand.field_0x68;

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

/*---------------------------------------------------------------------------*/

int s11e_zk11ecom_800D9BD4( char *ops, A4_STRUCT *unk )
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

int s11e_zk11ecom_800D9C34( char *ops, short* s )
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

void s11e_zk11ecom_800D9C8C( void )
{
    int i;
    int dist2;
    int dist1;
    int reset_pos;
    HZD_ZON *zone;
    SVECTOR svec;

    i = dist1 = reset_pos = 0;

    for ( ; i < ZAKO11ECommand.field_0x34 ; i++  )
    {
        zone = &ZAKO11ECommand.field_0x64->hzd->def->zones[ ZAKO11ECommand.field_0x38[ i ] ];

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

    ZAKO11ECommand.field_0x36 = reset_pos;
}

int s11e_zk11ecom_800D9D7C( int val )
{
    return ZAKO11ECommand.field_0x0C % val;
}

void s11e_zk11ecom_800D9DBC( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "dareda!!\n" );
        *val = SE_V_ENE_FOUND01; // 敵兵「誰だ！」
        break;
    case 1:
        fprintf( 1, "dareda!!\n" );
        *val = SE_V_ENE_FOUND01; // 敵兵「誰だ！」
        break;
    }
}

void s11e_zk11ecom_800D9E10( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "nanno otoda!!\n" );
        *val = SE_V_ENE_NOISE; // 敵兵「何の音だ？」
        break;
    case 1:
        fprintf( 1, "nanno otoda!!\n" );
        *val = SE_V_ENE_NOISE; // 敵兵「何の音だ？」
        break;
    }
}

void s11e_zk11ecom_800D9E64( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "tadano hakoka\n" );
        *val = SE_V_ENE_JUSTABOX; // 敵兵「ただの箱か」
        break;
    case 1:
        fprintf( 1, "tadano hakoka\n" );
        *val = SE_V_ENE_JUSTABOX; // 敵兵「ただの箱か」
        break;
    }
}

void s11e_zk11ecom_800D9EB8( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "kono asiatoha??\n" );
        *val = SE_V_ENE_FOOTPRINTS; // 敵兵「この足跡は？」
        break;
    case 1:
        fprintf( 1, "kono asiatoha??\n" );
        *val = SE_V_ENE_FOOTPRINTS; // 敵兵「この足跡は？」
        break;
    }
}

void s11e_zk11ecom_800D9F0C( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "kinoseika !!\n" );
        *val = SE_V_ENE_NOTHING; // 敵兵「気のせいか」
        break;
    case 1:
        fprintf( 1, "kinoseika !!\n" );
        *val = SE_V_ENE_NOTHING; // 敵兵「気のせいか」
        break;
    }
}

void s11e_zk11ecom_800D9F60( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 3 ) )
    {
    case 0:
        fprintf( 1, "itazo \n" );
        *val = SE_V_ENE_FOUND03; // 敵兵「（無線）いたぞ！」
        return;
    case 1:
        fprintf( 1, "kottida!!\n" );
        *val = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        break;
    case 2:
        fprintf( 1, "kottida!!\n" );
        *val = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        break;
    }
}

void s11e_zk11ecom_800D9FF0( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "haitini modoruzo!!\n" );
        *val = SE_V_ENE_RETURN; // 敵兵「（無線）配置に戻るぞ！」
        break;
    case 1:
        fprintf( 1, "haitini modoruzo!!\n" );
        *val = SE_V_ENE_RETURN; // 敵兵「（無線）配置に戻るぞ！」
        break;
    }
}

void s11e_zk11ecom_800DA044( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *val = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        return;
    case 1:
        *val = 0;
        return;
    }
}

int s11e_zk11ecom_800DA0A8( int val )
{
    switch ( val )
    {
    case 240:
        s11e_zk11ecom_800D9DBC( &val );
        break;
    case 241:
        s11e_zk11ecom_800D9E10( &val );
        break;
    case 242:
        s11e_zk11ecom_800D9E64( &val );
        break;
    case 243:
        s11e_zk11ecom_800D9EB8( &val );
        break;
    case 244:
        s11e_zk11ecom_800D9F0C( &val );
        break;
    case 245:
        s11e_zk11ecom_800D9FF0( &val );
        break;
    case 246:
        s11e_zk11ecom_800D9F60( &val );
        break;
    case 247:
        s11e_zk11ecom_800DA044( &val );
        break;
    }

    return val;
}

void s11e_zk11ecom_800DA16C( ZAKO_COMMAND* command )
{
    int i;
    int t2;
    int t3;
    int t4;
    int dists[8];
    int temp1, temp2;
    int temp3, temp4;
    ZakoWork *work;

    for ( i = 0 ; i < command->field_0x08 ; i ++ )
    {
        work = ( ZakoWork * )command->field_0x8C[ ZAKO11ECommand.field_0x40[ i ] ].watcher;
        dists[i] = work->sn_dis;
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

                temp4 = ZAKO11ECommand.field_0x40[ i - 1 ];
                temp3 = ZAKO11ECommand.field_0x40[ i  ];
                t4 = t2;

                ZAKO11ECommand.field_0x40[ i - 1 ] = temp3;
                ZAKO11ECommand.field_0x40[ i ] = temp4;
            }
        }
    }

    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        work = ( ZakoWork * )command->field_0x8C[ ZAKO11ECommand.field_0x40[ i ] ].watcher;
        work->field_BFC = ChaseDis[ ZAKO11ECommand.field_0x40[ i ] ];
    }
}

extern int SoundPlayTime;

void s11e_zk11ecom_800DA2BC( ZAKO_COMMAND* command )
{
    int i;
    int dis;
    int sound;
    ZakoWork *work;

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
    dis   = 100000;
    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        if ( command->field_0x8C[ i ].field_04 == 2 )
        {
            work = (ZakoWork * )command->field_0x8C[ i ].watcher;
            if ( work->pad.sound && work->sn_dis < dis )
            {
                sound = work->pad.sound;
                dis = work->sn_dis;
            }
            work->pad.sound = SE_DUMMY;
        }
    }

    if ( sound )
    {
        SoundPlayTime = 0x1E;
        GM_SeSet2(NULL, 0x30, s11e_zk11ecom_800DA0A8( sound ) );
    }
}

void s11e_zk11ecom_800DA3A0( WATCHER *struct_c8 , int i )
{
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = 1;
            ZAKO11ECommand.field_0x60++;
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
        switch ( ZAKO11ECommand.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( ZAKO11ECommand.field_0x10C & 1 )
            {
                s11e_zk11ecom_800D9C8C();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
        return;
        case TOP_COMM_ALERT:
                    if ( ZAKO11ECommand.field_0x60 < 0 )
                    {
                        s11e_zk11ecom_800D9C8C();
                        struct_c8->field_04 = x;
                        struct_c8->field_08 = 0;
                    }
            return;
        }
        return;
    }
}

int s11e_zk11ecom_800DA4B8( int a0, int a1 )
{
    if ( a0 < a1 )
    {
        a0 = a1;
    }

    return a0;
}

void s11e_zk11ecom_800DA4D0( int val, ZAKO_COMMAND* command )
{
    if ( command->alert - val > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = val;
    }

    if ( command->alert < ZAKO11ETOPCOMMAND.alert )
    {
        command->alert = ZAKO11ETOPCOMMAND.alert;
    }

    ZAKO11E_SetTopCommAL_800D9A84( 0 );
}

void s11e_zk11ecom_800DA534( ZAKO_COMMAND *command )
{
    int alert;

    switch ( command->mode )
    {
        case 0:
            if ( command->alert >= 255 )
            {
                command->alert = 255;
                GM_AlertModeSet(3);
                command->mode = 1;

                if ( ZAKO11ECommand.field_0x11C >= 0 )
                {
                    GCL_ExecProc( ZAKO11ECommand.field_0x11C, NULL );
                }
            }
        break;
        case 1:
            if ( command->alert <= 0 )
            {
                GM_AlertModeSet(2);
                command->mode = 2;
                command->field_0x14 = 0;
            }
            alert = command->alert;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
        case 2:
            command->field_0x14--;
            if ( command->field_0x14 <= 0 )
            {
                GM_AlertModeSet(0);
                command->mode = 0;
                command->field_0x14 = 0;
            }
            if ( command->alert >= 255 )
            {
                command->alert = 0xFF;
                GM_AlertModeSet(3);
                command->mode = 1;
            }
            alert = command->field_0x14;
            if ( alert >= 0x101 )
            {
                alert = 0x100;
            }
            GM_SetAlertMax( alert );
        break;
    }

    ZAKO11ETOPCOMMAND.mode = command->mode;
}

void s11e_zk11ecom_800DA690( ZakoCommanderWork* work )
{
    int i;
    int alert;
    ZakoWork *watcher;

    alert = 0;

    for ( i = 0; i < ZAKO11ECommand.field_0x08; i++ )
    {
        if ( ZAKO11ECommand.field_0x8C[ i ].field_04 == 2 )
        {
            watcher = ( ZakoWork * )ZAKO11ECommand.field_0x8C[ i ].watcher;
            alert =  s11e_zk11ecom_800DA4B8( alert, watcher->alert_level );
        }
        else if ( ZAKO11ECommand.field_0x8C[ i ].field_04 == 1 )
        {
            s11e_zk11ecom_800DA3A0( &ZAKO11ECommand.field_0x8C[ i ], i );
        }
    }

    s11e_zk11ecom_800DA2BC( &ZAKO11ECommand );
    s11e_zk11ecom_800DA4D0( alert, &ZAKO11ECommand );
    s11e_zk11ecom_800DA534( &ZAKO11ECommand );
    s11e_zk11ecom_800DA16C( &ZAKO11ECommand );

    ZAKO11ECommand.field_0x10C = 0;
}

void s11e_zk11ecom_800DA784( void )
{
    int addr;
    int addr2;

    addr = GM_PlayerAddress & 0xFF;
    addr2 = ( GM_PlayerAddress >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        ZAKO11E_PlayerAddress  = GM_PlayerAddress;
        ZAKO11E_PlayerPosition = GM_PlayerPosition;
        ZAKO11E_PlayerMap      = GM_PlayerMap;
    }
}

int s11e_zk11ecom_800DA7F8( char *arg0 )
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

void s11e_zk11ecom_800DA85C(void)
{
    int i;
    int a0 = ZAKO11ECommand.field_0x60;

    if ( GM_GameOverTimer || GM_Vitality <= 0 )
    {
        return;
    }

    switch( ZAKO11E_GameFlag )
    {
    case 0:
        GM_GameStatus |= STATE_PADRELEASE;

        if ( GM_StreamStatus() == 1 )
        {
            GM_StreamPlayStart();
        }

        if ( ZAKO11ECommand.field_0x10 > 90 )
        {

            ZAKO11E_GameFlag = 1;
            ZAKO11ECommand.field_0x10 = 0;
            GM_GameStatus &= ~STATE_PADRELEASE;
        }
    break;
    case 1:
        if ( ZAKO11ECommand.field_0x10 > 60 )
        {
            ZAKO11E_GameFlag = 2;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 2:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 3;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 3:
        if ( ZAKO11ECommand.field_0x10 > 60 )
        {
            ZAKO11E_GameFlag = 4;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 4:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 5;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 5:
        if ( ZAKO11ECommand.field_0x10 > 60 )
        {
            ZAKO11E_GameFlag = 6;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 6:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 7;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 7:
        if ( ZAKO11ECommand.field_0x10 > 60 )
        {
            ZAKO11E_GameFlag = 8;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 8:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 9;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 9:
        if ( ZAKO11ECommand.field_0x10 > 120 )
        {
            ZAKO11E_GameFlag = 10;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 10:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 1;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 11:
        if ( ZAKO11ECommand.field_0x10 > 90 )
        {
            ZAKO11E_GameFlag = 12;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 12:
        if ( ZAKO11ECommand.field_0x10 > 120 )
        {
            ZAKO11E_GameFlag = 1;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 13:
        if ( ZAKO11ECommand.field_0x10 > 120 )
        {
            ZAKO11E_GameFlag = 0;
            ZAKO11ECommand.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            ZAKO11E_GameFlag = 15;
        }
    break;
    case 15:
        if ( ZAKO11ETOPCOMMAND.mode == 0 )
        {
            ZAKO11E_GameFlag = 16;
            for ( i = 0 ; i < 8 ; i++ )
            {
                if ( ZAKO11ECommand.field_0x8C[i].watcher )
                {
                    ZAKO11E_GameFlag = 15;
                }
            }
        }
        if ( ZAKO11ECommand.field_0x120 >= 0 )
        {
            GCL_ExecProc( ZAKO11ECommand.field_0x120, 0 );
            ZAKO11ECommand.field_0x120 = -1;
        }
    break;
    case 16:
    break;
    }

    ZAKO11ECommand.field_0x10++;
}

/*---------------------------------------------------------------------------*/

static void Act( ZakoCommanderWork* work )
{
    s11e_zk11ecom_800DA85C();
    s11e_zk11ecom_800DA784();
    s11e_zk11ecom_800DA690( work );
    ZAKO11ECommand.field_0x0C++;

    if ( ZAKO11E_GameFlag == 0x10 )
    {
        GV_DestroyActor( &work->actor );
    }
}

static void Die( ZakoCommanderWork* work )
{
    if ( ZAKO11ECommand.field_0x118 >= 0 )
    {
        GCL_ExecProc( ZAKO11ECommand.field_0x118, NULL );
        ZAKO11ECommand.field_0x118 = -1;
    }
}

static void GetResources( ZakoCommanderWork *work, int name, int where )
{
    int i;
    char *ops;

    ZAKO11E_GameFlag = 0;

    ZAKO11ECommand.field_0x20 = 0;
    ZAKO11ECommand.alert = 0;
    ZAKO11ECommand.field_0x10 = 0;
    ZAKO11ECommand.field_0x60 = 0;

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZAKO11ECommand.field_0x8C[i].field_00 = 0;
        ZAKO11ECommand.field_0x8C[i].field_04 = 0;
        ZAKO11ECommand.field_0x8C[i].field_08 = 0;
        ZAKO11ECommand.field_0x8C[i].watcher  = 0;
    }

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZAKO11ECommand.field_0x40[i]  = i;
    }

    ZAKO11ECommand.field_0x0C = 0;
    ZAKO11ECommand.mode = 0;

    ZAKO11ETOPCOMMAND.mode = 0;
    ZAKO11ETOPCOMMAND.alert = 0;

    ZAKO11ECommand.field_0x64 = GM_GetMap( where );

    ops = GCL_GetOption( 'v' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x34 = s11e_zk11ecom_800D9C34( ops, ZAKO11ECommand.field_0x38 );
    }
    else
    {
        ZAKO11ECommand.field_0x34 = 1;
        ZAKO11ECommand.field_0x38[0] = 0;
    }

    for ( i = 0 ; i < ZAKO11ECommand.field_0x34 ; i++ )
    {
        fprintf( 1, "zone=%d ", ZAKO11ECommand.field_0x38[i] );
    }

    ZAKO11ECommand.field_0x36 = 0;
    ZAKO11E_GameStatus = 0;

    ops = GCL_GetOption( 'j' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x68.n_entry = s11e_zk11ecom_800D9BD4( ops, &ZAKO11ECommand.field_0x68 );
    }
    else
    {
        ZAKO11ECommand.field_0x68.n_entry = 1;
        ZAKO11ECommand.field_0x68.field_04->field_00 = 0;
        ZAKO11ECommand.field_0x68.field_04->field_02 = 0;
    }

    ZAKO11ECommand.field_0x68.map_id  = where;
    ZAKO11ECommand.field_0x114  = 0;

    ops = GCL_GetOption( 'b' );
    if ( ops )
    {
        int res = GCL_StrToInt( (unsigned char*)ops );
        ZAKO11ECommand.field_0x114 = res;
        printf( "ENEMY VOICE [0x%x]\n", res );
    }

    ops = GCL_GetOption( 'e' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x118 = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ECommand.field_0x118 = -1;
    }

    ops = GCL_GetOption( 'm' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x120 = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ECommand.field_0x120 = -1;
    }

    ops = GCL_GetOption( 'k' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x11C = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        ZAKO11ECommand.field_0x11C = -1;
    }

    ZAKO11ECommand.field_0x08 = 0;
    ops = GCL_GetOption( 'n' );
    if ( ops )
    {
        ZAKO11ECommand.field_0x08 = s11e_zk11ecom_800DA7F8( ops );
    }

    ZAKO11ECommand.field_0x00  = 0;
    ZAKO11ECommand.field_0x04  = 0;
    ZAKO11ECommand.field_0x110 = 0;
    GM_VoxStream( ZAKO11ECommand.field_0x114, 0x40000000 );
}

/*---------------------------------------------------------------------------*/

void *NewZako11ECommander( int name, int where, int argc, char **argv )
{
    ZakoCommanderWork *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( ZakoCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "zk11ecom.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
