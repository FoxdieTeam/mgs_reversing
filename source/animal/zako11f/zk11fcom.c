#include "zako.h"

#include <stdio.h>
#include "strcode.h"
#include "mts/mts.h"      // for fprintf

/*---------------------------------------------------------------------------*/

SVECTOR ZAKO11F_TARGET_SIZE = {300, 1500, 300};
SVECTOR ZAKO11F_TARGET_FORCE = {0, 0, 0};
SVECTOR ZAKO11F_ATTACK_SIZE = {800, 500, 800};
SVECTOR ZAKO11F_ATTACK_FORCE = {100, 0, 0};
SVECTOR ZAKO11F_TOUCH_SIZE = {300, 800, 300};
SVECTOR ZAKO11F_TOUCH_FORCE = {0, 0, 0};
SVECTOR ZAKO11F_NO_POINT = {30000, 30000, 30000};
int     ZAKO11F_EYE_LENGTH = 4000;

SVECTOR SECTION(".bss") ZAKO11F_PlayerPosition;
COMMANDER SECTION(".bss") ZAKO11FCommand;
TOP SECTION(".bss") ZAKO11FTOPCOMMAND;
int SECTION(".bss") ZAKO11F_Unknown;
int SECTION(".bss") ZAKO11F_GameFlag;
int SECTION(".bss") ZAKO11F_PlayerAddress;
int SECTION(".bss") ZAKO11F_PlayerMap;

/*---------------------------------------------------------------------------*/

static int SoundPlayTime = 0;

/*---------------------------------------------------------------------------*/

int ZAKO11FSetWorkID( Work *work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( ZAKO11FCommand.watchers[ i ].work == NULL )
        {
            ZAKO11FCommand.watchers[ i ].work = work;
            ZAKO11FCommand.watchers[ i ].field_4 = 2;
            return i;
        }
    }

    return -1;
}

void ZAKO11FResetWorkID( int id )
{
    ZAKO11FCommand.watchers[ id ].work = NULL;
    ZAKO11FCommand.watchers[ id ].field_4 = 1;
}

void ZAKO11FSetTopCommAL( int alert )
{
    ZAKO11FTOPCOMMAND.alert = alert;
}

void ZAKO11FSetTopCommMD( int mode )
{
    ZAKO11FTOPCOMMAND.mode = mode;
}

void ZAKO11FSetGopointLast( void )
{
    ZAKO11FCommand.target_addr = ZAKO11F_PlayerAddress;
    ZAKO11FCommand.target_pos = ZAKO11F_PlayerPosition;
    ZAKO11FCommand.target_map = ZAKO11F_PlayerMap;
}

void ZAKO11FSetGopointNoise( void )
{
    ZAKO11FCommand.target_addr = HZD_GetAddress( GM_WhereList[ 0 ]->map->hzd, &GM_NoisePosition, -1 );
    ZAKO11FCommand.target_pos = GM_NoisePosition;
    ZAKO11FCommand.target_map = GM_PlayerMap;
}

int ZAKO11FFindRoute( int map, int id )
{
    JDATA *list;
    int i;

    list = &ZAKO11FCommand.jdata;
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

int s11i_zk11fcom_800D0DA8( void )
{
    return ZAKO11FCommand.field_112 > 0;
}

void s11i_zk11fcom_800D0DB8( void )
{
    ZAKO11FCommand.field_112 = 5;
    ZAKO11FCommand.field_114++;
}

void s11i_zk11fcom_800D0DD8( void )
{
    if ( ZAKO11FCommand.firstdamage == 0 )
    {
        ZAKO11FCommand.field_112 = 5;
        ZAKO11FCommand.firstdamage = 1;
    }
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

int s11i_zk11fcom_800D0E64(char *opt, short *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_NextStr()))
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
    int      far_zone;
    int      i;
    HZD_ZON *zone;
    int      dist;

    max = 0;
    far_zone = 0;

    for ( i = 0; i < ZAKO11FCommand.n_zones ; i++ )
    {
        zone = &ZAKO11FCommand.map->hzd->def->zones[ ZAKO11FCommand.zones[ i ] ];

        dest.vx = zone->x;
        dest.vy = GM_PlayerPosition.vy;
        dest.vz = zone->z;

        dist = GV_DiffVec3( &dest, &GM_PlayerPosition );
        if ( max < dist )
        {
            max = dist;
            far_zone = i;
        }
    }

    ZAKO11FCommand.far_zone = far_zone;
}

int s11i_zk11fcom_800D0FAC( int n )
{
    return ZAKO11FCommand.time % n;
}

void s11i_zk11fcom_800D0FEC( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "dareda!!\n" );
        *se_id = SE_V_ENE_FOUND01; // 敵兵「誰だ！」
        break;

    case 1:
        fprintf( 1, "dareda!!\n" );
        *se_id = SE_V_ENE_FOUND01; // 敵兵「誰だ！」
        break;
    }
}

void s11i_zk11fcom_800D1040( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "nanno otoda!!\n" );
        *se_id = SE_V_ENE_NOISE; // 敵兵「何の音だ？」
        break;

    case 1:
        fprintf( 1, "nanno otoda!!\n" );
        *se_id = SE_V_ENE_NOISE; // 敵兵「何の音だ？」
        break;
    }
}

void s11i_zk11fcom_800D1094( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "tadano hakoka\n" );
        *se_id = SE_V_ENE_JUSTABOX; // 敵兵「ただの箱か」
        break;

    case 1:
        fprintf( 1, "tadano hakoka\n" );
        *se_id = SE_V_ENE_JUSTABOX; // 敵兵「ただの箱か」
        break;
    }
}

void s11i_zk11fcom_800D10E8( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kono asiatoha??\n" );
        *se_id = SE_V_ENE_FOOTPRINTS; // 敵兵「この足跡は？」
        break;

    case 1:
        fprintf( 1, "kono asiatoha??\n" );
        *se_id = SE_V_ENE_FOOTPRINTS; // 敵兵「この足跡は？」
        break;
    }
}

void s11i_zk11fcom_800D113C( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kinoseika !!\n" );
        *se_id = SE_V_ENE_NOTHING; // 敵兵「気のせいか」
        break;

    case 1:
        fprintf( 1, "kinoseika !!\n" );
        *se_id = SE_V_ENE_NOTHING; // 敵兵「気のせいか」
        break;
    }
}

void s11i_zk11fcom_800D1190( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 3 ) )
    {
    case 0:
        fprintf( 1, "itazo \n" );
        *se_id = SE_V_ENE_FOUND03; // 敵兵「（無線）いたぞ！」
        break;

    case 1:
        fprintf( 1, "kottida!!\n" );
        *se_id = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        break;

    case 2:
        fprintf( 1, "kottida!!\n" );
        *se_id = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        break;
    }
}

void s11i_zk11fcom_800D1220( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "haitini modoruzo!!\n" );
        *se_id = SE_V_ENE_RETURN; // 敵兵「（無線）配置に戻るぞ！」
        break;

    case 1:
        fprintf( 1, "haitini modoruzo!!\n" );
        *se_id = SE_V_ENE_RETURN; // 敵兵「（無線）配置に戻るぞ！」
        break;
    }
}

void s11i_zk11fcom_800D1274( int *se_id )
{
    switch ( s11i_zk11fcom_800D0FAC( 2 ) )
    {
    case 0:
        fprintf( 1, "kottida !!\n" );
        *se_id = SE_V_ENE_FOUND02; // 敵兵「（無線）こっちだ！」
        break;

    case 1:
        *se_id = 0;
        break;
    }
}

int s11i_zk11fcom_800D12D8( int se_id )
{
    switch ( se_id )
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

void s11i_zk11fcom_800D139C( COMMANDER *command )
{
    int          sound;
    int          min;
    int          i;
    Work *watcher;

    if ( --SoundPlayTime < 0 )
    {
        SoundPlayTime = 0;
    }

    if ( SoundPlayTime > 0 )
    {
        return;
    }

    sound = SE_DUMMY;
    min   = 100000;

    for ( i = 0 ; i < command->n_watchers ; i++ )
    {
        if ( command->watchers[ i ].field_4 == 2 )
        {
            watcher = command->watchers[ i ].work;
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
        SoundPlayTime = 30;
        GM_SeSet2(0, 48, s11i_zk11fcom_800D12D8( sound ) );
    }
}

void s11i_zk11fcom_800D1480( WATCHER *watcher, int i )
{
    switch (watcher->field_8)
    {
    case 0:
        if ( watcher->field_4 == 1 )
        {
            watcher->field_8 = 1;
            watcher->field_0 = 1;
            ZAKO11FCommand.field_60++;

            // This is probably a shared base struct
            ZAKO11FCommand.field_118 = watcher->work->control.mov;
        }
        break;

    case 1:
        watcher->field_0--;
        if ( watcher->field_0 <= 0 )
        {
            watcher->field_8 = 2;
            watcher->field_0 = 0;
        }
        break;

    case 2:
        switch ( ZAKO11FCommand.alert_mode )
        {
        case TOP_COMM_TRAVEL:
            if ( ZAKO11FCommand.field_10C & 1 )
            {
                s11i_zk11fcom_800D0EBC();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
            }
            break;

        case TOP_COMM_ALERT:
            if ( ZAKO11FCommand.field_60 < 0 )
            {
                s11i_zk11fcom_800D0EBC();
                watcher->field_4 = 2;
                watcher->field_8 = 0;
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

void s11i_zk11fcom_800D15DC( int alert_level, COMMANDER *command )
{
    if ( (command->alert_level - alert_level) > 4 )
    {
        command->alert_level -= 4;
    }
    else
    {
        command->alert_level = alert_level;
    }

    if ( command->alert_level < ZAKO11FTOPCOMMAND.alert )
    {
        command->alert_level = ZAKO11FTOPCOMMAND.alert;
    }

    ZAKO11FSetTopCommAL( 0 );
}

void s11i_zk11fcom_800D1640(COMMANDER *command)
{
    switch (command->alert_mode)
    {
    case 0:
        if (ZAKO11F_GameFlag == 1 || ZAKO11F_GameFlag == 2 || ZAKO11FCommand.firstdamage == 1)
        {
            printf(" gameflag=%d   firstdamage=%d \n", ZAKO11F_GameFlag, ZAKO11FCommand.firstdamage);
            ZAKO11FCommand.firstdamage = 2;

            command->alert_level = 0xFF;
            command->alert_mode = 1;

            if (ZAKO11FCommand.proc[0] >= 0)
            {
                GCL_ExecProc(ZAKO11FCommand.proc[0], 0);
            }
        }
        break;

    case 1:
        if (command->alert_level <= 0)
        {
            command->alert_mode = 2;
            command->alert_time = 0;
        }
        break;

    case 2:
        command->alert_time--;
        break;
    }

    ZAKO11FTOPCOMMAND.mode = command->alert_mode;
}

void s11i_zk11fcom_800D1754(CommanderWork *work)
{
    int level;
    int i;

    level = 0;

    for (i = 0; i < ZAKO11FCommand.n_watchers; i++)
    {
        if (ZAKO11FCommand.watchers[i].field_4 == 2)
        {
            level = s11i_zk11fcom_800D15C4(level, ZAKO11FCommand.watchers[i].work->alert_level);
        }
        else if (ZAKO11FCommand.watchers[i].field_4 == 1)
        {
            s11i_zk11fcom_800D1480(&ZAKO11FCommand.watchers[i], i);
        }
    }

    s11i_zk11fcom_800D139C(&ZAKO11FCommand);
    s11i_zk11fcom_800D15DC(level, &ZAKO11FCommand);
    s11i_zk11fcom_800D1640(&ZAKO11FCommand);

    ZAKO11FCommand.field_10C = 0;

    if (--ZAKO11FCommand.field_112 < 0)
    {
        ZAKO11FCommand.field_112 = 0;
    }
}

void s11i_zk11fcom_800D185C(void)
{
    int lo, hi;

    lo = GM_PlayerAddress & 0xFF;
    hi = ( GM_PlayerAddress >> 8 ) & 0xFF;

    if ( lo == hi && lo != 0xFF )
    {
        ZAKO11F_PlayerAddress = GM_PlayerAddress;
        ZAKO11F_PlayerPosition = GM_PlayerPosition;
        ZAKO11F_PlayerMap = GM_PlayerMap;
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
        opt = GCL_NextStr();

        GCL_ExecProc(proc, NULL);
        count++;
    }

    return count;
}

int s11i_zk11fcom_800D1934(int arg0)
{
    if (GM_PlayerPosition.vx < 4500)
    {
        return 0;
    }

    if (GM_PlayerPosition.vx > 7500)
    {
        return 0;
    }

    if (GM_PlayerPosition.vz < -16000)
    {
        return 0;
    }

    if (arg0 == 1 && GM_PlayerPosition.vz > 6000)
    {
        return 0;
    }

    return 1;
}

int s11i_zk11fcom_800D1990(int arg0)
{
    if (arg0 == 0)
    {
        if (GM_PlayerPosition.vz > -15000)
        {
            return 0;
        }
    }
    else
    {
        if (GM_PlayerPosition.vz > -13000)
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

    f114 = ZAKO11FCommand.field_114;

    switch( ZAKO11F_GameFlag )
    {
    case 0:
        if (f114 != 0)
        {
            ZAKO11F_GameFlag = 2;
            ZAKO11FCommand.time2 = 0;

        }
        else if (s11i_zk11fcom_800D1934(1))
        {
            ZAKO11F_GameFlag = 1;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 1:
        if (f114 != 0)
        {
            ZAKO11F_GameFlag = 2;
            ZAKO11FCommand.time2 = 0;
        }
        else if (!s11i_zk11fcom_800D1934(0))
        {
            ZAKO11F_GameFlag = 0;
            ZAKO11FCommand.time2 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag = 9;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 2:
        if ( ZAKO11FCommand.time2 > 150 )
        {
            ZAKO11F_GameFlag = 3;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 3:
        if ( f114 > 1 )
        {
            ZAKO11F_GameFlag = 5;
            ZAKO11FCommand.time2 = 0;
        }
        else if (s11i_zk11fcom_800D1934(0))
        {
            if (ZAKO11FCommand.time2 > 120 || s11i_zk11fcom_800D1934(1))
            {
                ZAKO11F_GameFlag = 4;
                ZAKO11FCommand.time2 = 0;
            }
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag = 9;
            ZAKO11FCommand.time2 = 0;
        }
        else
        {
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 4:
        if ( f114 > 1 )
        {
            ZAKO11F_GameFlag = 5;
            ZAKO11FCommand.time2 = 0;
        }
        else if (!s11i_zk11fcom_800D1934(0))
        {
            ZAKO11F_GameFlag = 3;
            ZAKO11FCommand.time2 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag = 9;
            ZAKO11FCommand.time2 = 0;
        }
        else
        {
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 5:
        if ( ZAKO11FCommand.time2 > 60 )
        {
            ZAKO11F_GameFlag = 6;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 6:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag = 8;
            ZAKO11FCommand.time2 = 0;
        }
        else if (ZAKO11FCommand.time2 >= 2)
        {
            ZAKO11F_GameFlag = 7;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 7:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag = 8;
            ZAKO11FCommand.time2 = 0;
        }
        else if (ZAKO11FCommand.time2 > 60)
        {
            ZAKO11F_GameFlag = 5;
            ZAKO11FCommand.time2 = 0;
        }
        else if (s11i_zk11fcom_800D1990(0))
        {
            ZAKO11F_GameFlag = 9;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 8:
        if (f114 > 2)
        {
            ZAKO11F_GameFlag = 15;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 9:
        if (!s11i_zk11fcom_800D1990(1))
        {
            switch (f114)
            {
            case 0:
                ZAKO11F_GameFlag = 1;
                break;

            case 1:
                ZAKO11F_GameFlag = 4;
                break;

            case 2:
                ZAKO11F_GameFlag = 7;
                break;
            }

            ZAKO11FCommand.time2 = 0;
        }

        if (ZAKO11FCommand.field_60 > 2)
        {
            ZAKO11F_GameFlag = 8;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 13:
        if (ZAKO11FCommand.time2 > 60)
        {
            ZAKO11F_GameFlag = 0;
            ZAKO11FCommand.time2 = 0;
        }
        break;

    case 15:
        if (ZAKO11FTOPCOMMAND.mode == 2)
        {
            ZAKO11F_GameFlag = 16;

            for (i = 0; i < 8; i++)
            {
                if (ZAKO11FCommand.watchers[i].work)
                {
                    ZAKO11F_GameFlag = 15;
                }
            }

            if (ZAKO11F_GameFlag == 16 && ZAKO11FCommand.end_proc > -1)
            {
                GCL_ExecProc(ZAKO11FCommand.end_proc, NULL);
            }
        }
        break;

    case 16:
        break;
    }

    ZAKO11FCommand.time2++;
}

/*---------------------------------------------------------------------------*/

static void Act(CommanderWork *work)
{
    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
        return;
    }

    s11i_zk11fcom_800D19D4();
    s11i_zk11fcom_800D185C();
    s11i_zk11fcom_800D1754(work);

    ZAKO11FCommand.time++;

    if (ZAKO11F_GameFlag == 16)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(CommanderWork *work)
{
    /* do nothing */
}

/*---------------------------------------------------------------------------*/

static int GetProcs(void)
{
    int   i;
    char *opt;

    for (i = 0; i < 8; i++)
    {
        ZAKO11FCommand.proc[i] = -1;
    }

    i = 0;
    opt = GCL_GetOption('a');
    while (opt)
    {
        if (i >= 8)
        {
            return -1;
        }

        ZAKO11FCommand.proc[i] = GCL_StrToInt(opt);
        opt = GCL_NextStr();
        i++;
    }

    return i;
}

static void GetResources(CommanderWork *work, int name, int where)
{
    int   i;
    char *opt;

    work->name = name;

    ZAKO11F_GameFlag = 0;

    ZAKO11FCommand.field_20 = 0;
    ZAKO11FCommand.alert_level = 0;
    ZAKO11FCommand.time2 = 0;
    ZAKO11FCommand.field_60 = 0;
    ZAKO11FCommand.field_112 = 0;
    ZAKO11FCommand.field_114 = 0;
    ZAKO11FCommand.firstdamage = 0;

    for (i = 0; i < 8; i++)
    {
        ZAKO11FCommand.watchers[i].field_0 = 0;
        ZAKO11FCommand.watchers[i].field_4 = 0;
        ZAKO11FCommand.watchers[i].field_8 = 0;
        ZAKO11FCommand.watchers[i].work = NULL;
    }

    for (i = 0; i < 8; i++)
    {
        ZAKO11FCommand.field_40[i] = i;
    }

    ZAKO11FCommand.time = 0;
    ZAKO11FCommand.alert_mode = 0;

    ZAKO11FTOPCOMMAND.mode = 0;
    ZAKO11FTOPCOMMAND.alert = 0;

    ZAKO11FCommand.map = GM_GetMap(where);

    opt = GCL_GetOption('e');
    if (opt)
    {
        ZAKO11FCommand.end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        ZAKO11FCommand.end_proc = -1;
    }

    GetProcs();

    opt = GCL_GetOption('v');
    if (opt)
    {
        ZAKO11FCommand.n_zones = s11i_zk11fcom_800D0E64(opt, ZAKO11FCommand.zones);
    }
    else
    {
        ZAKO11FCommand.n_zones = 1;
        ZAKO11FCommand.zones[0] = 0;
    }

    for (i = 0; i < ZAKO11FCommand.n_zones; i++)
    {
        fprintf(1, "zone=%d ", ZAKO11FCommand.zones[i]);
    }

    ZAKO11FCommand.far_zone = 0;
    ZAKO11F_Unknown = 0;

    opt = GCL_GetOption('j');
    if (opt)
    {
        ZAKO11FCommand.jdata.count = ReadMapJdata(opt, &ZAKO11FCommand.jdata);
    }
    else
    {
        ZAKO11FCommand.jdata.count = 1;
        ZAKO11FCommand.jdata.data[0][0] = 0;
        ZAKO11FCommand.jdata.data[0][1] = 0;
    }

    ZAKO11FCommand.jdata.map = where;
    ZAKO11FCommand.n_watchers = 0;

    opt = GCL_GetOption('n');
    if (opt)
    {
        ZAKO11FCommand.n_watchers = s11i_zk11fcom_800D18D0(opt);
    }

    ZAKO11FCommand.field_0 = 0;
    ZAKO11FCommand.field_4 = 0;
    ZAKO11FCommand.field_110 = 0;
}

/*---------------------------------------------------------------------------*/

void *NewZako11FCommander( int name, int where )
{
    CommanderWork *work ;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( CommanderWork ) ) ;
    if ( work != NULL ) {
        GV_SetNamedActor( &( work->actor ), Act, Die, "zk11fcom.c" );
        GetResources( work, name, where );
    }
    return (void *)work;
}
