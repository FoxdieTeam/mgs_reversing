#include "../../../s00a/Enemy/enemy.h"
#include "common.h"
#include "Game/linkvarbuf.h"

extern ZAKO_COMMAND ZakoCommand_800DF280;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800DF3A8;

extern int s11e_dword_800DF3B0;
extern int s11e_dword_800DF3B4;

extern int     ZAKOCOM_PlayerAddress_800DF3B8;
extern SVECTOR ZAKOCOM_PlayerPosition_800DF278;
extern int     ZAKOCOM_PlayerMap_800DF3BC;

extern SVECTOR  GM_PlayerPosition_800ABA10;
extern SVECTOR  GM_NoisePosition_800AB9F8;
extern CONTROL *GM_WhereList_800B56D0[94];
extern int      GM_PlayerMap_800ABA0C;
extern int      GM_PlayerAddress_800AB9F0;

int s11e_zk11ecom_800D9A20( ZakoWork *work )
{
    int i;
    for ( i = 0 ; i <  8 ; i++ )
    {
        if ( ZakoCommand_800DF280.field_0x8C[ i ].watcher == 0 )
        {
            ZakoCommand_800DF280.field_0x8C[ i ].watcher = ( WatcherWork * )work;
            ZakoCommand_800DF280.field_0x8C[ i ].field_04 = 2;
            return i;
        }
    }
    return -1;
}

void s11e_zk11ecom_800D9A64( int idx )
{
    ZakoCommand_800DF280.field_0x8C[ idx ].watcher  = 0;
    ZakoCommand_800DF280.field_0x8C[ idx ].field_04 = 1;
}

void ZAKO11E_SetTopCommAL_800D9A84( int alert )
{
    TOPCOMMAND_800DF3A8.alert = alert;
}

void ZAKO11E_SetTopCommMD_800D9A90( int mode )
{
    TOPCOMMAND_800DF3A8.mode = mode;
}

void ZAKO11E_SetGoPointLast_800D9A9C( void )
{
    ZakoCommand_800DF280.com_addr = ZAKOCOM_PlayerAddress_800DF3B8;
    ZakoCommand_800DF280.com_pos  = ZAKOCOM_PlayerPosition_800DF278;
    ZakoCommand_800DF280.com_map  = ZAKOCOM_PlayerMap_800DF3BC;
}

void s11e_zk11ecom_800D9AE8(void)
{
    ZakoCommand_800DF280.com_addr = HZD_GetAddress_8005C6C4( GM_WhereList_800B56D0[ 0 ]->map->hzd, &GM_NoisePosition_800AB9F8, -1 );
    ZakoCommand_800DF280.com_pos  = GM_NoisePosition_800AB9F8;
    ZakoCommand_800DF280.com_map  = GM_PlayerMap_800ABA0C;
}

int s11e_zk11ecom_800D9B60( int map_id, int val )
{
    int i;
    A4_STRUCT *unk = &ZakoCommand_800DF280.field_0x68;

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

int s11e_zk11ecom_800D9BD4( char *ops, A4_STRUCT *unk )
{
    int i;
    i = 0;

    do {
        unk->field_04[ i ].field_00 = GCL_StrToInt( GCL_GetParamResult() );
        unk->field_04[ i ].field_02 = GCL_StrToInt( GCL_GetParamResult() );
        i++;
    } while ( GCL_GetParamResult() != NULL );


    return i;
}

int s11e_zk11ecom_800D9C34( char *ops, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_GetParamResult() ) ; i++ )
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

    for ( ; i < ZakoCommand_800DF280.field_0x34 ; i++  )
    {
        zone = &ZakoCommand_800DF280.field_0x64->hzd->f00_header->navmeshes[ ZakoCommand_800DF280.field_0x38[ i ] ];

        svec.vx = zone->x;
        svec.vy = GM_PlayerPosition_800ABA10.vy;
        svec.vz = zone->z;


        dist2 = GV_DiffVec3( &svec, &GM_PlayerPosition_800ABA10 );
        if ( dist1 < dist2 )
        {
            dist1 = dist2;
            reset_pos = i;
        }
    }

    ZakoCommand_800DF280.field_0x36 = reset_pos;
}

int s11e_zk11ecom_800D9D7C( int val )
{
    return ZakoCommand_800DF280.field_0x0C % val;
}

extern const char s11e_aDareda_800DEC78[];// = "dareda!!\n";
extern const char s11e_aNannootoda_800DEC84[];// = "nanno otoda!!\n";
extern const char s11e_aTadanohakoka_800DEC94[]; //= "tadano hakoka\n";
extern const char s11e_aKonoasiatoha_800DECA4[];// = "kono asiatoha??\n";
extern const char s11e_aKinoseika_800DECB8[];// = "kinoseika !!\n";
extern const char s11e_aItazo_800DECC8[]; //= "itazo \n";
extern const char s11e_aKottida_800DECD0[];// = "kottida!!\n";
extern const char s11e_aHaitinimodoruzo_800DECDC[];// = "haitini modoruzo!!\n";
extern const char s11e_aKottida_800DECF0[];// = "kottida !!\n";


void s11e_zk11ecom_800D9DBC( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aDareda_800DEC78 );
        *val = 0x80;
        break;
    case 1:
        fprintf( 1, s11e_aDareda_800DEC78 );
        *val = 0x80;
        break;
    }
}



void s11e_zk11ecom_800D9E10( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aNannootoda_800DEC84 );
        *val = 0x87;
        break;
    case 1:
        fprintf( 1, s11e_aNannootoda_800DEC84 );
        *val = 0x87;
        break;
    }
}


void s11e_zk11ecom_800D9E64( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aTadanohakoka_800DEC94 );
        *val = 0x8B;
        break;
    case 1:
        fprintf( 1, s11e_aTadanohakoka_800DEC94 );
        *val = 0x8B;
        break;
    }
}

void s11e_zk11ecom_800D9EB8( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aKonoasiatoha_800DECA4 );
        *val = 0x8A;
        break;
    case 1:
        fprintf( 1, s11e_aKonoasiatoha_800DECA4 );
        *val = 0x8A;
        break;
    }
}

void s11e_zk11ecom_800D9F0C( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aKinoseika_800DECB8 );
        *val = 0x86;
        break;
    case 1:
        fprintf( 1, s11e_aKinoseika_800DECB8 );
        *val = 0x86;
        break;
    }
}

void s11e_zk11ecom_800D9F60( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 3 ) )
    {
    case 0:
        fprintf( 1, s11e_aItazo_800DECC8 );
        *val = 0x82;
        return;
    case 1:
        fprintf( 1, s11e_aKottida_800DECD0 );
        *val = 0x81;
        break;
    case 2:
        fprintf( 1, s11e_aKottida_800DECD0 );
        *val = 0x81;
        break;
    }
}

void s11e_zk11ecom_800D9FF0( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {

    case 0:
        fprintf( 1, s11e_aHaitinimodoruzo_800DECDC );
        *val = 0x85;
        break;
    case 1:
        fprintf( 1, s11e_aHaitinimodoruzo_800DECDC );
        *val = 0x85;
        break;
    }
}

void s11e_zk11ecom_800DA044( int* val )
{
    switch ( s11e_zk11ecom_800D9D7C( 2 ) )
    {
    case 0:
        fprintf( 1, s11e_aKottida_800DECF0 );
        *val = 0x81;
        return;
    case 1:
        *val = 0;
        return;
    }
}

int s11e_zk11ecom_800DA0A8( int val ) {
    switch( val )
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

extern int s11e_dword_800C3908[];

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
        work = ( ZakoWork * )command->field_0x8C[ ZakoCommand_800DF280.field_0x40[ i ] ].watcher;
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

                temp4 = ZakoCommand_800DF280.field_0x40[ i - 1 ];
                temp3 = ZakoCommand_800DF280.field_0x40[ i  ];
                t4 = t2;

                ZakoCommand_800DF280.field_0x40[ i - 1 ] = temp3;
                ZakoCommand_800DF280.field_0x40[ i ] = temp4;
            }
        }
    }

    for ( i = 0 ; i < command->field_0x08 ; i++ )
    {
        work = ( ZakoWork * )command->field_0x8C[ ZakoCommand_800DF280.field_0x40[ i ] ].watcher;
        work->field_BFC = s11e_dword_800C3908[ ZakoCommand_800DF280.field_0x40[ i ] ];
    }
}

extern int s11e_dword_800C3928;

void s11e_zk11ecom_800DA2BC( ZAKO_COMMAND* command )
{
    int i;
    int dis;
    int sound;
    ZakoWork *work;

    s11e_dword_800C3928--;

    if ( s11e_dword_800C3928 < 0 )
    {
        s11e_dword_800C3928 = 0;
    }

    if ( s11e_dword_800C3928 > 0 )
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
            work->pad.sound = 0;
        }
    }

    if ( sound )
    {
        s11e_dword_800C3928 = 0x1E;
        GM_SeSet2(NULL, 0x30, s11e_zk11ecom_800DA0A8( sound ) );
    }
}

void s11e_zk11ecom_800DA3A0( C8_STRUCT* struct_c8 , int i )
{
    int x = struct_c8->field_08;
    switch ( x )
    {
    case 0:
        if ( struct_c8->field_04 == 1 )
        {
            struct_c8->field_08 = 1;
            struct_c8->field_00 = 1;
            ZakoCommand_800DF280.field_0x60++;
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
        switch ( ZakoCommand_800DF280.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( ZakoCommand_800DF280.field_0x10C & 1 )
            {
                s11e_zk11ecom_800D9C8C();
                struct_c8->field_04 = x;
                struct_c8->field_08 = 0;
            }
        return;
        case TOP_COMM_ALERT:
                    if ( ZakoCommand_800DF280.field_0x60 < 0 )
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

    if ( command->alert < TOPCOMMAND_800DF3A8.alert )
    {
        command->alert = TOPCOMMAND_800DF3A8.alert;
    }

    ZAKO11E_SetTopCommAL_800D9A84( 0 );
}

extern void GM_AlertModeSet( int a1 );

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

                if ( ZakoCommand_800DF280.field_0x11C >= 0 )
                {
                    GCL_ExecProc( ZakoCommand_800DF280.field_0x11C, NULL );
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

    TOPCOMMAND_800DF3A8.mode = command->mode;
}

void s11e_zk11ecom_800DA690( ZakoCommanderWork* work )
{
    int i;
    int alert;
    ZakoWork *watcher;

    alert = 0;

    for ( i = 0; i < ZakoCommand_800DF280.field_0x08; i++ )
    {
        if ( ZakoCommand_800DF280.field_0x8C[ i ].field_04 == 2 )
        {
            watcher = ( ZakoWork * )ZakoCommand_800DF280.field_0x8C[ i ].watcher;
            alert =  s11e_zk11ecom_800DA4B8( alert, watcher->alert_level );
        }
        else if ( ZakoCommand_800DF280.field_0x8C[ i ].field_04 == 1 )
        {
            s11e_zk11ecom_800DA3A0( &ZakoCommand_800DF280.field_0x8C[ i ], i );
        }
    }

    s11e_zk11ecom_800DA2BC( &ZakoCommand_800DF280 );
    s11e_zk11ecom_800DA4D0( alert, &ZakoCommand_800DF280 );
    s11e_zk11ecom_800DA534( &ZakoCommand_800DF280 );
    s11e_zk11ecom_800DA16C( &ZakoCommand_800DF280 );

    ZakoCommand_800DF280.field_0x10C = 0;
}

void s11e_zk11ecom_800DA784( void )
{
    int addr;
    int addr2;

    addr = GM_PlayerAddress_800AB9F0 & 0xFF;
    addr2 = ( GM_PlayerAddress_800AB9F0 >> 8 ) & 0xFF;

    if ( addr == addr2 && addr != 0xFF )
    {
        ZAKOCOM_PlayerAddress_800DF3B8  = GM_PlayerAddress_800AB9F0;
        ZAKOCOM_PlayerPosition_800DF278 = GM_PlayerPosition_800ABA10;
        ZAKOCOM_PlayerMap_800DF3BC      = GM_PlayerMap_800ABA0C;
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
            res = GCL_GetParamResult();
            GCL_ExecProc( proc_id, NULL );
            i++;
        } while ( res );
    }
    return i;
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/s11e_zk11ecom_800DA85C.s")
//extern void s11e_zk11ecom_800DA85C( void );

extern int GM_GameOverTimer;

void s11e_zk11ecom_800DA85C(void)
{
    int i;
    int a0 = ZakoCommand_800DF280.field_0x60;

    if ( GM_GameOverTimer || GM_SnakeCurrentHealth <= 0 )
    {
        return;
    }

    switch( s11e_dword_800DF3B4 )
    {
    case 0:
        GM_GameStatus |= STATE_PADRELEASE;

        if ( GM_StreamStatus_80037CD8() == 1 )
        {
            GM_StreamPlayStart_80037D1C();
        }

        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {

            s11e_dword_800DF3B4 = 1;
            ZakoCommand_800DF280.field_0x10 = 0;
            GM_GameStatus &= ~STATE_PADRELEASE;
        }
    break;
    case 1:
        if ( ZakoCommand_800DF280.field_0x10 > 60 )
        {
            s11e_dword_800DF3B4 = 2;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 2:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 3;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 3:
        if ( ZakoCommand_800DF280.field_0x10 > 60 )
        {
            s11e_dword_800DF3B4 = 4;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 4:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 5;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 5:
        if ( ZakoCommand_800DF280.field_0x10 > 60 )
        {
            s11e_dword_800DF3B4 = 6;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 6:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 7;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 7:
        if ( ZakoCommand_800DF280.field_0x10 > 60 )
        {
            s11e_dword_800DF3B4 = 8;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 8:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 9;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 9:
        if ( ZakoCommand_800DF280.field_0x10 > 120 )
        {
            s11e_dword_800DF3B4 = 10;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 10:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 1;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 11:
        if ( ZakoCommand_800DF280.field_0x10 > 90 )
        {
            s11e_dword_800DF3B4 = 12;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 12:
        if ( ZakoCommand_800DF280.field_0x10 > 120 )
        {
            s11e_dword_800DF3B4 = 1;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 13:
        if ( ZakoCommand_800DF280.field_0x10 > 120 )
        {
            s11e_dword_800DF3B4 = 0;
            ZakoCommand_800DF280.field_0x10 = 0;
        }

        if ( a0 > 3 )
        {
            s11e_dword_800DF3B4 = 15;
        }
    break;
    case 15:
        if ( TOPCOMMAND_800DF3A8.mode == 0 )
        {
            s11e_dword_800DF3B4 = 16;
            for ( i = 0 ; i < 8 ; i++ )
            {
                if ( ZakoCommand_800DF280.field_0x8C[i].watcher )
                {
                    s11e_dword_800DF3B4 = 15;
                }
            }
        }
        if ( ZakoCommand_800DF280.field_0x120 >= 0 )
        {
            GCL_ExecProc( ZakoCommand_800DF280.field_0x120, 0 );
            ZakoCommand_800DF280.field_0x120 = -1;
        }
    break;
    case 16:
    break;
    }

    ZakoCommand_800DF280.field_0x10++;
}


void ZakoCommanderAct_800DABF4( ZakoCommanderWork* work )
{
    s11e_zk11ecom_800DA85C();
    s11e_zk11ecom_800DA784();
    s11e_zk11ecom_800DA690( work );
    ZakoCommand_800DF280.field_0x0C++;

    if ( s11e_dword_800DF3B4 == 0x10 )
    {
        GV_DestroyActor( &work->actor );
    }
}

void ZakoCommanderDie_800DAC5C( void )
{

    if ( ZakoCommand_800DF280.field_0x118 >= 0 )
    {
        GCL_ExecProc( ZakoCommand_800DF280.field_0x118, NULL );
        ZakoCommand_800DF280.field_0x118 = -1;
    }
}


extern const char s11e_aZoned_800DED64[]; // = "zone=%d ";
extern const char s11e_aEnemyvoicexx_800DED70[]; // = "ENEMY VOICE [0x%x]\n";

void ZakoCommanderGetResources_800DACA0( ZakoCommanderWork *work, int name, int where )
{
    int i;
    char *ops;

    s11e_dword_800DF3B4 = 0;

    ZakoCommand_800DF280.field_0x20 = 0;
    ZakoCommand_800DF280.alert = 0;
    ZakoCommand_800DF280.field_0x10 = 0;
    ZakoCommand_800DF280.field_0x60 = 0;

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZakoCommand_800DF280.field_0x8C[i].field_00 = 0;
        ZakoCommand_800DF280.field_0x8C[i].field_04 = 0;
        ZakoCommand_800DF280.field_0x8C[i].field_08 = 0;
        ZakoCommand_800DF280.field_0x8C[i].watcher  = 0;
    }

    for ( i = 0 ; i < 8 ; i++ )
    {
        ZakoCommand_800DF280.field_0x40[i]  = i;
    }

    ZakoCommand_800DF280.field_0x0C = 0;
    ZakoCommand_800DF280.mode = 0;

    TOPCOMMAND_800DF3A8.mode = 0;
    TOPCOMMAND_800DF3A8.alert = 0;

    ZakoCommand_800DF280.field_0x64 = Map_FromId_800314C0( where );

    ops = GCL_GetOption( 'v' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x34 = s11e_zk11ecom_800D9C34( ops, ZakoCommand_800DF280.field_0x38 );
    }
    else
    {
        ZakoCommand_800DF280.field_0x34 = 1;
        ZakoCommand_800DF280.field_0x38[0] = 0;
    }

    for ( i = 0 ; i < ZakoCommand_800DF280.field_0x34 ; i++ )
    {
        fprintf( 1, s11e_aZoned_800DED64, ZakoCommand_800DF280.field_0x38[i] );
    }

    ZakoCommand_800DF280.field_0x36 = 0;
    s11e_dword_800DF3B0 = 0;

    ops = GCL_GetOption( 'j' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x68.n_entry = s11e_zk11ecom_800D9BD4( ops, &ZakoCommand_800DF280.field_0x68 );
    }
    else
    {
        ZakoCommand_800DF280.field_0x68.n_entry = 1;
        ZakoCommand_800DF280.field_0x68.field_04->field_00 = 0;
        ZakoCommand_800DF280.field_0x68.field_04->field_02 = 0;
    }

    ZakoCommand_800DF280.field_0x68.map_id  = where;
    ZakoCommand_800DF280.field_0x114  = 0;

    ops = GCL_GetOption( 'b' );
    if ( ops )
    {
        int res = GCL_StrToInt( (unsigned char*)ops );
        ZakoCommand_800DF280.field_0x114 = res;
        printf( s11e_aEnemyvoicexx_800DED70, res );
    }

    ops = GCL_GetOption( 'e' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x118 = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        ZakoCommand_800DF280.field_0x118 = -1;
    }

    ops = GCL_GetOption( 'm' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x120 = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        ZakoCommand_800DF280.field_0x120 = -1;
    }

    ops = GCL_GetOption( 'k' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x11C = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        ZakoCommand_800DF280.field_0x11C = -1;
    }

    ZakoCommand_800DF280.field_0x08 = 0;
    ops = GCL_GetOption( 'n' );
    if ( ops )
    {
        ZakoCommand_800DF280.field_0x08 = s11e_zk11ecom_800DA7F8( ops );
    }

    ZakoCommand_800DF280.field_0x00  = 0;
    ZakoCommand_800DF280.field_0x04  = 0;
    ZakoCommand_800DF280.field_0x110 = 0;
    GM_VoxStream_80037E40( ZakoCommand_800DF280.field_0x114, 0x40000000 );
}

//#pragma INCLUDE_ASM("asm/overlays/s11e/NewZakoCommander_800DAF38.s")

extern void ZakoCommanderAct_800DABF4();
extern void ZakoCommanderDie_800DAC5C();
extern const char s11e_aZkecomc_800DED84[];

GV_ACT *NewZakoCommander_800DAF38( int name, int where, int argc, char **argv )
{
    ZakoCommanderWork *work ;

    work = (ZakoCommanderWork *)GV_NewActor( 4, sizeof( ZakoCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ( GV_ACTFUNC )ZakoCommanderAct_800DABF4, ( GV_ACTFUNC )ZakoCommanderDie_800DAC5C, s11e_aZkecomc_800DED84 );
        ZakoCommanderGetResources_800DACA0( work, name, where );
    }
    return &work->actor;
}
