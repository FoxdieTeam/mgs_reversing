#include <stdio.h>

#include "../../../s00a/Enemy/enemy.h"
#include "mts/mts.h"

typedef struct _Zako11FCommanderWork
{
    GV_ACT actor;
    int    name;
    char   pad[0x4];
} Zako11FCommanderWork;

extern int GM_GameStatus;
extern int GM_GameOverTimer;

extern int      GM_PlayerAddress_800AB9F0;
extern SVECTOR  GM_NoisePosition;
extern int      GM_PlayerMap_800ABA0C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern CONTROL *GM_WhereList_800B56D0[96];

extern int               s11i_dword_800C3698;
extern SVECTOR           ZAKOCOM_PlayerPosition_800D5AF0;
extern ZAKO11F_COMMAND   Zako11FCommand_800D5AF8;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800D5C40;
extern int               s11i_dword_800D5C48;
extern int               ZAKO11F_GameFlag_800D5C4C;
extern int               ZAKOCOM_PlayerAddress_800D5C50;
extern int               ZAKOCOM_PlayerMap_800D5C54;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int s11i_zk11fcom_800D0BF4( Zako11FWork *watcher ) // SetZako
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( !Zako11FCommand_800D5AF8.watchers[ i ].watcher )
        {
            Zako11FCommand_800D5AF8.watchers[ i ].watcher = watcher;
            Zako11FCommand_800D5AF8.watchers[ i ].field_04 = 2;
            return i;
        }
    }

    return -1;
}

void s11i_zk11fcom_800D0C38( int index ) // ClearZako
{
    Zako11FCommand_800D5AF8.watchers[index].watcher = NULL;
    Zako11FCommand_800D5AF8.watchers[index].field_04 = 1;
}

void s11i_zk11fcom_800D0C58( int alert )
{
    TOPCOMMAND_800D5C40.alert = alert;
}

void s11i_zk11fcom_800D0C64( int mode )
{
    TOPCOMMAND_800D5C40.mode = mode;
}

void s11i_zk11fcom_800D0C70( void )
{
    Zako11FCommand_800D5AF8.com_addr = ZAKOCOM_PlayerAddress_800D5C50;
    Zako11FCommand_800D5AF8.com_pos  = ZAKOCOM_PlayerPosition_800D5AF0;
    Zako11FCommand_800D5AF8.com_map  = ZAKOCOM_PlayerMap_800D5C54;
}

void s11i_zk11fcom_800D0CBC(void)
{
    Zako11FCommand_800D5AF8.com_addr = HZD_GetAddress( GM_WhereList_800B56D0[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    Zako11FCommand_800D5AF8.com_pos  = GM_NoisePosition;
    Zako11FCommand_800D5AF8.com_map  = GM_PlayerMap_800ABA0C;
}

int s11i_zk11fcom_800D0D34( int map_id, int val )
{
    A4_STRUCT *unk = &Zako11FCommand_800D5AF8.field_0x68;
    int        i;

    if ( unk->map_id == map_id )
    {
        for ( i = 0 ; i < unk->n_entry ; i++ )
        {
            if ( unk->field_04[ i ].field_00 == val )
            {
                return unk->field_04[ i ].field_02;
            }
        }

        goto not_found;
    }

    return 0;

not_found:
    return -1;
}

int s11i_zk11fcom_800D0DA8(void)
{
    return Zako11FCommand_800D5AF8.field_0x112 > 0;
}

void s11i_zk11fcom_800D0DB8(void)
{
    Zako11FCommand_800D5AF8.field_0x112 = 5;
    Zako11FCommand_800D5AF8.field_0x114++;
}

void s11i_zk11fcom_800D0DD8(void)
{
    if (Zako11FCommand_800D5AF8.first_damage == 0)
    {
        Zako11FCommand_800D5AF8.field_0x112 = 5;
        Zako11FCommand_800D5AF8.first_damage = 1;
    }
}

int s11i_zk11fcom_800D0E04(char *opt, A4_STRUCT *out)
{
    int count;

    count = 0;

    do
    {
        out->field_04[count].field_00 = GCL_StrToInt(GCL_GetParamResult());
        out->field_04[count].field_02 = GCL_StrToInt(GCL_GetParamResult());
        count++;
    } while (GCL_GetParamResult());

    return count;
}

int s11i_zk11fcom_800D0E64(char *opt, short *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_GetParamResult()))
    {
        *out++ = GCL_StrToInt(param);
        count++;
    }

    return count;
}

void s11i_zk11fcom_800D0EBC( void )
{
    SVECTOR  dest;
    int      max;
    int      reset_zone;
    int      i;
    HZD_ZON *zone;
    int      dist;

    max = 0;
    reset_zone = 0;

    for ( i = 0; i < Zako11FCommand_800D5AF8.n_zones ; i++ )
    {
        zone = &Zako11FCommand_800D5AF8.map->hzd->header->zones[ Zako11FCommand_800D5AF8.zones[ i ] ];

        dest.vx = zone->x;
        dest.vy = GM_PlayerPosition_800ABA10.vy;
        dest.vz = zone->z;

        dist = GV_DiffVec3( &dest, &GM_PlayerPosition_800ABA10 );
        if ( max < dist )
        {
            max = dist;
            reset_zone = i;
        }
    }

    Zako11FCommand_800D5AF8.reset_zone = reset_zone;
}

int s11i_zk11fcom_800D0FAC( int n )
{
    return Zako11FCommand_800D5AF8.field_0x0C % n;
}

void s11i_zk11fcom_800D0FEC( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "dareda!!\n" );
        *se_id = 0x80;
        break;

    case 1:
        fprintf( 1, "dareda!!\n" );
        *se_id = 0x80;
        break;
    }
}

void s11i_zk11fcom_800D1040( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "nanno otoda!!\n" );
        *se_id = 0x87;
        break;

    case 1:
        fprintf( 1, "nanno otoda!!\n" );
        *se_id = 0x87;
        break;
    }
}

void s11i_zk11fcom_800D1094( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "tadano hakoka\n" );
        *se_id = 0x8B;
        break;

    case 1:
        fprintf( 1, "tadano hakoka\n" );
        *se_id = 0x8B;
        break;
    }
}

void s11i_zk11fcom_800D10E8( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kono asiatoha??\n" );
        *se_id = 0x8A;
        break;

    case 1:
        fprintf( 1, "kono asiatoha??\n" );
        *se_id = 0x8A;
        break;
    }
}

void s11i_zk11fcom_800D113C( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kinoseika !!\n" );
        *se_id = 0x86;
        break;

    case 1:
        fprintf( 1, "kinoseika !!\n" );
        *se_id = 0x86;
        break;
    }
}

void s11i_zk11fcom_800D1190( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 3 ) )
    {
    case 0:
        fprintf( 1, "itazo \n" );
        *se_id = 0x82;
        break;

    case 1:
        fprintf( 1, "kottida!!\n" );
        *se_id = 0x81;
        break;

    case 2:
        fprintf( 1, "kottida!!\n" );
        *se_id = 0x81;
        break;
    }
}

void s11i_zk11fcom_800D1220( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "haitini modoruzo!!\n" );
        *se_id = 0x85;
        break;

    case 1:
        fprintf( 1, "haitini modoruzo!!\n" );
        *se_id = 0x85;
        break;
    }
}

void s11i_zk11fcom_800D1274( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *se_id = 0x81;
        break;

    case 1:
        *se_id = 0;
        break;
    }
}

int s11i_zk11fcom_800D12D8( int se_id )
{
    switch( se_id )
    {
        case 240:
            s11i_zk11fcom_800D0FEC( &se_id );
            break;

        case 241:
            s11i_zk11fcom_800D1040( &se_id );
            break;

        case 242:
            s11i_zk11fcom_800D1094( &se_id );
            break;

        case 243:
            s11i_zk11fcom_800D10E8( &se_id );
            break;

        case 244:
            s11i_zk11fcom_800D113C( &se_id );
            break;

        case 245:
            s11i_zk11fcom_800D1220( &se_id );
            break;

        case 246:
            s11i_zk11fcom_800D1190( &se_id );
            break;

        case 247:
            s11i_zk11fcom_800D1274( &se_id );
            break;
    }

    return se_id;
}

void s11i_zk11fcom_800D139C( ZAKO11F_COMMAND *command )
{
    int          sound;
    int          min;
    int          i;
    Zako11FWork *watcher;

    if ( --s11i_dword_800C3698 < 0 )
    {
        s11i_dword_800C3698 = 0;
    }

    if ( s11i_dword_800C3698 > 0 )
    {
        return;
    }

    sound = SE_DUMMY;
    min   = 100000;

    for ( i = 0 ; i < command->n_watchers ; i++ )
    {
        if ( command->watchers[ i ].field_04 == 2 )
        {
            watcher = command->watchers[ i ].watcher;
            if ( watcher->pad.sound != SE_DUMMY && watcher->sn_dis < min )
            {
                sound = watcher->pad.sound;
                min = watcher->sn_dis;
            }
            watcher->pad.sound = SE_DUMMY;
        }
    }

    if ( sound != SE_DUMMY )
    {
        s11i_dword_800C3698 = 30;
        GM_SeSet2(0, 48, s11i_zk11fcom_800D12D8( sound ) );
    }
}

void s11i_zk11fcom_800D1480( WATCHER *watcher, int i )
{
    switch (watcher->field_08)
    {
    case 0:
        if ( watcher->field_04 == 1 )
        {
            watcher->field_08 = 1;
            watcher->field_00 = 1;
            Zako11FCommand_800D5AF8.field_0x60++;

            // This is probably a shared base struct
            Zako11FCommand_800D5AF8.field_0x118 = ((WatcherWork *)watcher->watcher)->control.mov;
        }
        break;

    case 1:
        watcher->field_00--;
        if ( watcher->field_00 <= 0 )
        {
            watcher->field_08 = 2;
            watcher->field_00 = 0;
        }
        break;

    case 2:
        switch ( Zako11FCommand_800D5AF8.mode )
        {
        case TOP_COMM_TRAVEL:
            if ( Zako11FCommand_800D5AF8.field_0x10C & 1 )
            {
                s11i_zk11fcom_800D0EBC();
                watcher->field_04 = 2;
                watcher->field_08 = 0;
            }
            break;

        case TOP_COMM_ALERT:
            if ( Zako11FCommand_800D5AF8.field_0x60 < 0 )
            {
                s11i_zk11fcom_800D0EBC();
                watcher->field_04 = 2;
                watcher->field_08 = 0;
            }
            break;
        }
        break;
    }
}

int s11i_zk11fcom_800D15C4( int a0, int a1 )
{
    return MAX(a1, a0);
}

void s11i_zk11fcom_800D15DC( int alert, ZAKO11F_COMMAND *command )
{
    if ( (command->alert - alert) > 4 )
    {
        command->alert -= 4;
    }
    else
    {
        command->alert = alert;
    }

    if ( command->alert < TOPCOMMAND_800D5C40.alert )
    {
        command->alert = TOPCOMMAND_800D5C40.alert;
    }

    s11i_zk11fcom_800D0C58( 0 );
}

void s11i_zk11fcom_800D1640(ZAKO11F_COMMAND *command)
{
    switch (command->mode)
    {
    case 0:
        if (ZAKO11F_GameFlag_800D5C4C == 1 || ZAKO11F_GameFlag_800D5C4C == 2 || Zako11FCommand_800D5AF8.first_damage == 1)
        {
            printf(" gameflag=%d   firstdamage=%d \n", ZAKO11F_GameFlag_800D5C4C, Zako11FCommand_800D5AF8.first_damage);
            Zako11FCommand_800D5AF8.first_damage = 2;

            command->alert = 0xFF;
            command->mode = 1;

            if (Zako11FCommand_800D5AF8.field_0x124[0] >= 0)
            {
                GCL_ExecProc(Zako11FCommand_800D5AF8.field_0x124[0], 0);
            }
        }
        break;

    case 1:
        if (command->alert <= 0)
        {
            command->mode = 2;
            command->field_0x14 = 0;
        }
        break;

    case 2:
        command->field_0x14--;
        break;
    }

    TOPCOMMAND_800D5C40.mode = command->mode;
}

void s11i_zk11fcom_800D1754(Zako11FCommanderWork *work)
{
    int level;
    int i;

    level = 0;

    for (i = 0; i < Zako11FCommand_800D5AF8.n_watchers; i++)
    {
        if (Zako11FCommand_800D5AF8.watchers[i].field_04 == 2)
        {
            level = s11i_zk11fcom_800D15C4(level, ((WatcherWork *)Zako11FCommand_800D5AF8.watchers[i].watcher)->alert_level);
        }
        else if (Zako11FCommand_800D5AF8.watchers[i].field_04 == 1)
        {
            s11i_zk11fcom_800D1480(&Zako11FCommand_800D5AF8.watchers[i], i);
        }
    }

    s11i_zk11fcom_800D139C(&Zako11FCommand_800D5AF8);
    s11i_zk11fcom_800D15DC(level, &Zako11FCommand_800D5AF8);
    s11i_zk11fcom_800D1640(&Zako11FCommand_800D5AF8);

    Zako11FCommand_800D5AF8.field_0x10C = 0;

    if (--Zako11FCommand_800D5AF8.field_0x112 < 0)
    {
        Zako11FCommand_800D5AF8.field_0x112 = 0;
    }
}

void s11i_zk11fcom_800D185C(void)
{
    int lo, hi;

    lo = GM_PlayerAddress_800AB9F0 & 0xFF;
    hi = ( GM_PlayerAddress_800AB9F0 >> 8 ) & 0xFF;

    if ( lo == hi && lo != 0xFF )
    {
        ZAKOCOM_PlayerAddress_800D5C50 = GM_PlayerAddress_800AB9F0;
        ZAKOCOM_PlayerPosition_800D5AF0 = GM_PlayerPosition_800ABA10;
        ZAKOCOM_PlayerMap_800D5C54 = GM_PlayerMap_800ABA0C;
    }
}

int s11i_zk11fcom_800D18D0( char *opt )
{
    int count;
    int proc;

    count = 0;

    while (opt)
    {
        proc = GCL_StrToInt(opt);
        opt = GCL_GetParamResult();

        GCL_ExecProc(proc, NULL);
        count++;
    }

    return count;
}

int s11i_zk11fcom_800D1934(int arg0)
{
    if (GM_PlayerPosition_800ABA10.vx < 4500)
    {
        return 0;
    }

    if (GM_PlayerPosition_800ABA10.vx > 7500)
    {
        return 0;
    }

    if (GM_PlayerPosition_800ABA10.vz < -16000)
    {
        return 0;
    }

    if (arg0 == 1 && GM_PlayerPosition_800ABA10.vz > 6000)
    {
        return 0;
    }

    return 1;
}

int s11i_zk11fcom_800D1990(int arg0)
{
    if (arg0 == 0)
    {
        if (GM_PlayerPosition_800ABA10.vz > -15000)
        {
            return 0;
        }
    }
    else
    {
        if (GM_PlayerPosition_800ABA10.vz > -13000)
        {
            return 0;
        }
    }

    return 1;
}

void s11i_zk11fcom_800D19D4(void)
{
    int f114;
    int i;

    f114 = Zako11FCommand_800D5AF8.field_0x114;

    switch( ZAKO11F_GameFlag_800D5C4C )
    {
    case 0:
        if (f114 != 0)
        {
            ZAKO11F_GameFlag_800D5C4C = 2;
            Zako11FCommand_800D5AF8.field_0x10 = 0;

        }
        else if (s11i_zk11fcom_800D1934(1))
        {
            ZAKO11F_GameFlag_800D5C4C = 1;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 1:
        if (f114 != 0)
        {
            ZAKO11F_GameFlag_800D5C4C = 2;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (!s11i_zk11fcom_800D1934(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 0;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 9;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 2:
        if ( Zako11FCommand_800D5AF8.field_0x10 > 150 )
        {
            ZAKO11F_GameFlag_800D5C4C = 3;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 3:
        if ( f114 > 1 )
        {
            ZAKO11F_GameFlag_800D5C4C = 5;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (s11i_zk11fcom_800D1934(0))
        {
            if (Zako11FCommand_800D5AF8.field_0x10 > 120 || s11i_zk11fcom_800D1934(1))
            {
                ZAKO11F_GameFlag_800D5C4C = 4;
                Zako11FCommand_800D5AF8.field_0x10 = 0;
            }
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 9;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else
        {
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 4:
        if ( f114 > 1 )
        {
            ZAKO11F_GameFlag_800D5C4C = 5;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (!s11i_zk11fcom_800D1934(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 3;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 9;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else
        {
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 5:
        if ( Zako11FCommand_800D5AF8.field_0x10 > 60 )
        {
            ZAKO11F_GameFlag_800D5C4C = 6;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 6:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 8;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (Zako11FCommand_800D5AF8.field_0x10 >= 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 7;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 7:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 8;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (Zako11FCommand_800D5AF8.field_0x10 > 60)
        {
            ZAKO11F_GameFlag_800D5C4C = 5;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag_800D5C4C = 9;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 8:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 15;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 9:
        if (!s11i_zk11fcom_800D1990(1))
        {
            switch (f114)
            {
            case 0:
                ZAKO11F_GameFlag_800D5C4C = 1;
                break;

            case 1:
                ZAKO11F_GameFlag_800D5C4C = 4;
                break;

            case 2:
                ZAKO11F_GameFlag_800D5C4C = 7;
                break;
            }

            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }

        if (Zako11FCommand_800D5AF8.field_0x60 > 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 8;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 13:
        if (Zako11FCommand_800D5AF8.field_0x10 > 60)
        {
            ZAKO11F_GameFlag_800D5C4C = 0;
            Zako11FCommand_800D5AF8.field_0x10 = 0;
        }
        break;

    case 15:
        if (TOPCOMMAND_800D5C40.mode == 2)
        {
            ZAKO11F_GameFlag_800D5C4C = 16;

            for (i = 0; i < 8; i++)
            {
                if (Zako11FCommand_800D5AF8.watchers[i].watcher)
                {
                    ZAKO11F_GameFlag_800D5C4C = 15;
                }
            }

            if (ZAKO11F_GameFlag_800D5C4C == 16 && Zako11FCommand_800D5AF8.field_0x120 > -1)
            {
                GCL_ExecProc(Zako11FCommand_800D5AF8.field_0x120, NULL);
            }
        }
        break;

    case 16:
        break;
    }

    Zako11FCommand_800D5AF8.field_0x10++;
}

void ZakoCommanderAct_800D1DB0(Zako11FCommanderWork *work)
{
    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s11i_zk11fcom_800D19D4();
    s11i_zk11fcom_800D185C();
    s11i_zk11fcom_800D1754(work);

    Zako11FCommand_800D5AF8.field_0x0C++;

    if (ZAKO11F_GameFlag_800D5C4C == 16)
    {
        GV_DestroyActor(&work->actor);
    }
}

void ZakoCommanderDie_800D1E30(Zako11FCommanderWork *work)
{
}

int ZakoCommander_800D1E38(void)
{
    int   i;
    char *opt;

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.field_0x124[i] = -1;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while (opt)
    {
        if (i >= 8)
        {
            return -1;
        }

        Zako11FCommand_800D5AF8.field_0x124[i] = GCL_StrToInt(opt);
        opt = GCL_GetParamResult();
        i++;
    }

    return i;
}

void ZakoCommanderGetResources_800D1EC8(Zako11FCommanderWork *work, int name, int where)
{
    int   i;
    char *opt;

    work->name = name;

    ZAKO11F_GameFlag_800D5C4C = 0;

    Zako11FCommand_800D5AF8.field_0x20 = 0;
    Zako11FCommand_800D5AF8.alert = 0;
    Zako11FCommand_800D5AF8.field_0x10 = 0;
    Zako11FCommand_800D5AF8.field_0x60 = 0;
    Zako11FCommand_800D5AF8.field_0x112 = 0;
    Zako11FCommand_800D5AF8.field_0x114 = 0;
    Zako11FCommand_800D5AF8.first_damage = 0;

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.watchers[i].field_00 = 0;
        Zako11FCommand_800D5AF8.watchers[i].field_04 = 0;
        Zako11FCommand_800D5AF8.watchers[i].field_08 = 0;
        Zako11FCommand_800D5AF8.watchers[i].watcher = NULL;
    }

    for (i = 0; i < 8; i++)
    {
        Zako11FCommand_800D5AF8.field_0x40[i] = i;
    }

    Zako11FCommand_800D5AF8.field_0x0C = 0;
    Zako11FCommand_800D5AF8.mode = 0;

    TOPCOMMAND_800D5C40.mode = 0;
    TOPCOMMAND_800D5C40.alert = 0;

    Zako11FCommand_800D5AF8.map = GM_GetMap(where);

    opt = GCL_GetOption('e');
    if (opt)
    {
        Zako11FCommand_800D5AF8.field_0x120 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        Zako11FCommand_800D5AF8.field_0x120 = -1;
    }

    ZakoCommander_800D1E38();

    opt = GCL_GetOption('v');
    if (opt)
    {
        Zako11FCommand_800D5AF8.n_zones = s11i_zk11fcom_800D0E64(opt, Zako11FCommand_800D5AF8.zones);
    }
    else
    {
        Zako11FCommand_800D5AF8.n_zones = 1;
        Zako11FCommand_800D5AF8.zones[0] = 0;
    }

    for (i = 0; i < Zako11FCommand_800D5AF8.n_zones; i++)
    {
        fprintf(1, "zone=%d ", Zako11FCommand_800D5AF8.zones[i]);
    }

    Zako11FCommand_800D5AF8.reset_zone = 0;
    s11i_dword_800D5C48 = 0;

    opt = GCL_GetOption('j');
    if (opt)
    {
        Zako11FCommand_800D5AF8.field_0x68.n_entry = s11i_zk11fcom_800D0E04(opt, &Zako11FCommand_800D5AF8.field_0x68);
    }
    else
    {
        Zako11FCommand_800D5AF8.field_0x68.n_entry = 1;
        Zako11FCommand_800D5AF8.field_0x68.field_04[0].field_00 = 0;
        Zako11FCommand_800D5AF8.field_0x68.field_04[0].field_02 = 0;
    }

    Zako11FCommand_800D5AF8.field_0x68.map_id = where;
    Zako11FCommand_800D5AF8.n_watchers = 0;

    opt = GCL_GetOption('n');
    if (opt)
    {
        Zako11FCommand_800D5AF8.n_watchers = s11i_zk11fcom_800D18D0(opt);
    }

    Zako11FCommand_800D5AF8.field_0x00 = 0;
    Zako11FCommand_800D5AF8.field_0x04 = 0;
    Zako11FCommand_800D5AF8.field_0x110 = 0;
}

void *NewZakoCommander_800D20D8( int name, int where )
{
    Zako11FCommanderWork *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Zako11FCommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), ZakoCommanderAct_800D1DB0, ZakoCommanderDie_800D1E30, "zk11fcom.c" );
        ZakoCommanderGetResources_800D1EC8( work, name, where );
    }
    return (void *)work;
}
