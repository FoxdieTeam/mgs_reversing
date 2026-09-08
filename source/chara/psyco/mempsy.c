#include <stdio.h>
#include <stddef.h>
#include "mts/mts.h"    // for cprintf

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

#include "chara/snake/sna_init.h"
#include "chara/snake/shadow.h"         // for NewShadow
#include "okajima/blurpure.h"           // for NewBlurPure
#include "takabe/cineutil.h"            // for OpenCinemaScreen, etc.

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "psycho" )
#define MOTION_DATA GV_StrCode( "psy_07b2" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | \
                      DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _ACTION {
    int time;
    int action;
} ACTION;

typedef struct _SAVEFILE {
    char *name;
    int   mask;
} SAVEFILE;

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[ 17 ];
    MOTION_SEGMENT m_segs2[ 17 ];
    SVECTOR        rots[ 16 ];
    SVECTOR        adjust[ 16 ];
    MATRIX         light[ 2 ];
    void          *shadow;
    void          *blur;
    short          field_7E0; /* unused */
    short          field_7E2; /* unused */
    int            field_7E4; /* unused */
    int            field_7E8; /* unused */
    int            flag;
    void          *action;
    int            time;
    ACTION        *action_list;
    int            time2;
    short          field_800;
    short          field_802;
    short          field_804;
    short          field_806;
    SVECTOR        field_808; /* unused */
    int            field_810;
    int            field_814[ 40 ];
    int            field_8B4[ 7 ];
} Work;

/*---------------------------------------------------------------------------*/

static ACTION s07b_dword_800C34A8[] = 
{
    { 0x0000, 0x0006 },
    { 0x0010, 0x0005 },
    { 0x0064, 0x0003 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x006E, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0073, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x006E, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x00BE, 0x0001 },
    { 0x0000, 0x0001 },
    { 0x008E, 0x0002 },
    { 0x0000, 0x0008 },
    { 0x0033, 0x0009 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0001 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0001 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0009 },
    { 0x0041, 0x0004 },
    { 0x0078, 0x0005 },
    { 0x0000, 0x0009 },
    { 0x003C, 0x0006 },
    { 0x0082, 0x0007 },
    { 0x0000, 0x0009 },
    { 0x003D, 0x0004 },
    { 0x0077, 0x0005 },
    { 0x0000, 0x0001 },
    { 0x0079, 0x0002 },
    { 0x0000, 0x000A },
    { 0x0054, 0x0002 },
    { 0x00C2, 0x0003 },
    { 0x0154, 0x000D },
    { 0x0000, 0x0004 },
    { 0x004A, 0x0005 },
    { 0x0000, 0x0007 },
    { 0x0047, 0x0002 },
    { 0x0000, 0x0007 },
    { 0x0040, 0x000C },
    { 0x0000, 0x000B },
    { 0x0000, 0x000B },
    { 0x0000, 0x000B },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0000 },
};

static int s07b_dword_800C3698[] =
{
    1, 5, 4, 3, 3, 4, 3, 3,
    5, 4, 3, 3, 4, 5, 5, 1,
    1, 2, 2, 1, 2, 1, 3, 3,
    4, 2, 5, 1, 5, 5, 1, 5,
    1, 2, 1, 1, 1, 1, 1, 1,
};

static char s07b_dword_800C3738[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 1, 3,
};

static int s07b_dword_800C3748[] =
{
    17, 18, -1, -1, 39, 26, -1, -1,
    22, 19, 21, 20, 24, 23, -1, 25,
};

/*---------------------------------------------------------------------------*/

#define GENRE_MISC              (0x0000)
#define GENRE_ACTION            (0x0100)
#define GENRE_ADV               (0x0200)    // Japanese-style Adventure Game
#define GENRE_FIGHTING          (0x0200)
#define GENRE_FIGHTINGACTION    (GENRE_ACTION | GENRE_FIGHTING)
#define GENRE_RPG               (0x0400)
#define GENRE_ACTIONRPG         (GENRE_ACTION | GENRE_RPG)
#define GENRE_RENAI_SIM         (0x0800)    // Japan-only
#define GENRE_ADVENTURE         (0x0800)
#define GENRE_ACTIONADVENTURE   (GENRE_ACTION | GENRE_ADVENTURE)
#define GENRE_ARCADE            (0x1000)
#define GENRE_ACTIONARCADE      (GENRE_ACTION | GENRE_ARCADE)
#define GENRE_SPORTS            (0x2000)

/* Japanese version */
#define TITLE_TOKIMEMO          (0x0001)
#define TITLE_POLICENAUTS       (0x0002)
#define TITLE_HIDEOKOJIMA       (0x0010)    // "A Hideo Kojima Game"
#define TITLE_KCEJAPAN          (0x0020)    // Developed by KCE Japan

/* International versions */
#define TITLE_SUIKODEN          (0x0001)
#define TITLE_AZUREDREAMS       (0x0002)
#define TITLE_CASTLEVANIA       (0x0010)
#define TITLE_VANDALHEARTS      (0x0020)

static SAVEFILE s07b_dword_800C3788[] =
{
    { "SLPS-00002", /* 0x1000 */ GENRE_ARCADE },
    { "SLPS-00015", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00016", /* 0x2000 */ GENRE_SPORTS },
    { "SLPS-00067", /* 0x2000 */ GENRE_SPORTS },
    { "SLPS-00068", /* 0x2000 */ GENRE_SPORTS },
    { "SLPS-00090", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00100", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00065", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00064", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00097", /* 0x0401 */ GENRE_RPG | TITLE_SUIKODEN },
    { "SLPS-00188", /* 0x2000 */ GENRE_SPORTS },
    { "SLPS-00215", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00228", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00154", /* 0x0000 */ GENRE_MISC },
    { "SLPS-00255", /* 0x1000 */ GENRE_ARCADE },
    { "SLPS-00272", /* 0x2000 */ GENRE_SPORTS },
    { "SLPS-00217", /* 0x0800 */ GENRE_ADVENTURE },
    { "SLPS-00303", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86001", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86003", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86002", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86005", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86006", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86004", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86007", /* 0x0420 */ GENRE_RPG | TITLE_VANDALHEARTS },
    { "SLPM-86009", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86010", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86011", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86013", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86008", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86015", /* 0x0200 */ GENRE_FIGHTING },
    { "SLPM-86014", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86021", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86023", /* 0x0910 */ GENRE_ACTIONADVENTURE | TITLE_CASTLEVANIA },
    { "SLPM-86012", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86029", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86035", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86034", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86036", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86037", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86039", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86024", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86042", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86044", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86016", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86047", /* 0x0502 */ GENRE_ACTIONRPG | TITLE_AZUREDREAMS },
    { "SLPM-86025", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86052", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86022", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86254", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86055", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86053", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86056", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86060", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86062", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86068", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86072", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86065", /* 0x1100 */ GENRE_ACTIONARCADE },
    { "SLPM-86070", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86076", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86077", /* 0x0400 */ GENRE_RPG },
    { "SLPM-86078", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86086", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86026", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86046", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86075", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86119", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86124", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86122", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86123", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86099", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86100", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86101", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86102", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86097", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86096", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86061", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86087", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86094", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86111", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86124", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86132", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86162", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86133", /* 0x0200 */ GENRE_FIGHTING },
    { "SLPM-86134", /* 0x0400 */ GENRE_RPG },
    { "SLPM-86150", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86154", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86155", /* 0x0800 */ GENRE_ADVENTURE },
    { "SLPM-80349", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86168", /* 0x0401 */ GENRE_RPG | TITLE_SUIKODEN },
    { "SLPM-86173", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86176", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86184", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86149", /* 0x2000 */ GENRE_SPORTS },
    { "SLPM-86191", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86192", /* 0x0800 */ GENRE_ADVENTURE },
    { "SLPM-86190", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86200", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86177", /* 0x0100 */ GENRE_ACTION },
    { "SLPM-86210", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86211", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86212", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86183", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86222", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86224", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86225", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86199", /* 0x0000 */ GENRE_MISC },
    { "SLPM-86229", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86228", /* 0x1000 */ GENRE_ARCADE },
    { "SLPM-86233", /* 0x0000 */ GENRE_MISC },
};

/*---------------------------------------------------------------------------*/

extern u_short GM_WeaponTypes[];
extern u_short GM_ItemTypes[];

extern void s07b_800D2988( void );
extern void s07b_800D2A0C( int );
extern void s07b_800D2A64( void );
extern int  s07b_800D2C4C( void );
extern int  s07b_800D2CB4( int );

void s07b_800D8564( Work *work, int time );
void s07b_800D88E4( Work *work, int time );
void s07b_800D8B8C( Work *work, int time );

static inline void SetMode( Work *work, void *action )
{
    work->action = action;
    work->time = 0;
    work->field_802 = 0;
    work->field_800 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static int CheckCutsceneSkip( Work *work )
{
    GV_PAD *pad;

    pad = &GV_PadData[ 2 ];
    if ( ( pad[ 0 ].press | pad[ 1 ].press ) & PAD_CROSS )
    {
        s07b_800D2988();
        CloseCinemaScreen();
        GCL_ExecProc( work->field_8B4[ 0 ], NULL );
        return 1;
    }
    return 0;
}

static void s07b_800D7ED8( Work *work, int index )
{
    ACTION *list;
    int i;

    work->flag |= 0x1;
    work->time2 = 0;

    list = s07b_dword_800C34A8;
    i = 0;

    /* TODO: figure out this loop */
    for ( ;; )
    {
        if ( list->time != 0 )
        {
            /* do nothing */
        }
        else
        {
            if ( i == index ) break;
            i++;
        }

        list++;
    }

    work->action_list = list;
    work->field_810 = work->field_814[ index ];

    GCL_ExecProc( work->field_8B4[ s07b_dword_800C3698[ index ] ], NULL );
}

void s07b_800D7F6C( Work *work )
{
    ACTION *list;
    int time, action;

    if ( work->flag & 0x4 ) return;

    if ( work->flag & 0x2 )
    {
        work->flag &= ~0x1;
        if ( work->body.is_end )
        {
            work->flag |= 0x1;
            work->flag &= ~0x2;
        }
    }

    if ( work->flag & 0x1 )
    {
        time = work->time2++;
        list = work->action_list;

        if ( time == 0 && work->field_810 >= 0 )
        {
            s07b_800D2A0C( work->field_810 );
        }

        if ( time == list->time )
        {
            action = list->action;
            if ( work->body.action != action )
            {
                GM_ConfigObjectAction( &work->body, action, 0, 4 );
            }

            work->action_list++;
        }

        if ( work->body.is_end )
        {
            if ( list->time == 0 ) work->flag &= ~0x1;
            if ( work->body.action != 0 && work->body.action != 9 && work->body.action != 0 )
            {
                GM_ConfigObjectAction( &work->body, 0, 0, 4 );
            }
        }
    }
}

void s07b_800D80B8( Work *work, int time )
{
    int var_s1, index;

    if ( time == 0 )
    {
        OpenCinemaScreen( 1, 1000000 );
        s07b_800D7ED8( work, 0 );
        GCL_ExecProc( work->field_8B4[ 1 ], NULL );
    }

    var_s1 = work->field_800;
    switch ( work->field_802 )
    {
    case 0:
        if ( !s07b_800D2C4C() ) break;
        printf( "enemy watch %d\n", GM_EnemyWatchCount );
        index = 8;

        if ( GM_EnemyWatchCount > 8 )
        {
            index = 1;
            var_s1 = 1;
        }

        s07b_800D7ED8( work, index );

        work->field_800 = var_s1;
        work->field_802++;
        break;
    case 1:
        if ( !s07b_800D2C4C() ) break;
        printf( "continue count %d\n", GM_ContinueCount );

        if ( GM_ContinueCount > 8 )
        {
            index = ( var_s1 == 1 ) ? 2 : 9;
            var_s1 |= 2;
        }
        else
        {
            index = ( var_s1 == 1 ) ? 5 : 12;
        }

        s07b_800D7ED8( work, index );
        work->field_800 = var_s1;
        work->field_802++;
        break;
    case 2:
        if ( !s07b_800D2C4C() ) break;

        printf( "trap out count %d\n", GM_PitfallDeathCount );

        if ( GM_PitfallDeathCount > 4 )
        {
            switch ( var_s1 )
            {
            case 0:
                index = 13;
                break;
            case 1:
                index = 6;
                break;
            case 2:
                index = 10;
                break;
            default:
                index = 3;
                break;
            }
        }
        else
        {
            switch ( var_s1 )
            {
            case 0:
                index = 14;
                break;
            case 1:
                index = 7;
                break;
            case 2:
                index = 11;
                break;
            default:
                index = 4;
                break;
            }
        }

        s07b_800D7ED8( work, index );
        work->field_802++;
        break;
    case 3:
        if ( !s07b_800D2C4C() ) break;
        SetMode( work, s07b_800D8564 );
        break;
    }
}

void s07b_800D8338( char *name, char *arg1, char *arg2 )
{
    SAVEFILE *save;
    int i, j, match, mask, bit;

    save = s07b_dword_800C3788;

    for ( i = 0; i < COUNTOF( s07b_dword_800C3788 ); i++ )
    {
        match = 0;

        for ( j = 2; j < 12; j++ )
        {
            if ( name[ j ] != save->name[ j - 2 ] )
            {
                match = 1;
                break;
            }
        }

        if ( match == 0 ) break;
        save++;
    }

    if ( i != 110 && arg2[ i ] == 0 )
    {
        arg1[ 15 ]++;
        arg2[ i ] = 1;

        mask = save->mask;
        for ( i = 0; i < 15; i++ )
        {
            bit = 1 << i;
            if ( bit & mask ) arg1[ i ]++;
        }
    }
}

int s07b_800D8410( MEMCARD **cards )
{
    char sp10[ 16 ];
    char sp20[ 110 ];
    short mask;
    int i, j;
    MEMCARD *card;

    mask = 0;

    for ( i = 0; i < 16; i++ )
    {
        sp10[ i ] = 0;
    }

    for ( i = 0; i < COUNTOF( s07b_dword_800C3788 ); i++ )
    {
        sp20[ i ] = 0;
    }

    for ( i = 0; i < 2; i++ )
    {
        card = cards[ i ];
        if ( card == NULL ) continue;

        for ( j = 0; j < card->file_count; j++ )
        {
            printf( "name %s\n", card->files[ j ].name );
            s07b_800D8338( card->files[ j ].name, sp10, sp20 );
        }
    }

    for ( i = 0; i < 16; i++ )
    {
        if ( sp10[ i ] >= s07b_dword_800C3738[ i ] ) mask |= 1 << i;
    }

    return mask;
}

void s07b_800D8564( Work *work, int time )
{
    MEMCARD *cards[ 2 ];
    int i;

    if ( time == 0 )
    {
        cards[ 0 ] = cards[ 1 ] = 0;

        if ( !( memcard_check( 0 ) & 0x80000000 ) )
        {
            cards[ 0 ] = memcard_files( 0 );
        }

        if ( !( memcard_check( 1 ) & 0x80000000 ) )
        {
            cards[ 1 ] = memcard_files( 1 );
        }

        if ( cards[ 0 ] == NULL && cards[ 1 ] == NULL )
        {
            SetMode( work, s07b_800D88E4 );
            return;
        }

        work->field_804 = 1;
        s07b_800D7ED8( work, 15 );
        work->field_800 = s07b_800D8410( cards );
    }

    if ( work->field_806 == 0 )
    {
        if ( s07b_800D2CB4( work->field_814[ 15 ] ) )
        {
            work->field_804 = 0;
            if ( work->field_800 != 0 )
            {
                work->field_804 = 1;
                s07b_800D7ED8( work, 16 );
            }
            work->field_806 = 1;
        }
        return;
    }

    if ( work->field_800 == 0 )
    {
        if ( work->field_804 == 0 )
        {
            s07b_800D7ED8( work, 30 );

            if ( work->body.action != 8 )
            {
                GM_ConfigObjectAction( &work->body, 8, 0, 4 );
            }

            work->field_802 = 16;
            work->field_804 = 1;
            work->flag |= 0x2;
        }
        else if ( s07b_800D2C4C() )
        {
            work->field_800 = 1;
            work->field_804--;
        }
    }
    else if ( work->field_804 == 0 )
    {
        for ( i = work->field_802; i < 16; i++ )
        {
            if ( ( work->field_800 >> i ) & 0x1 ) break;
        }

        if ( i == 16 )
        {
            work->field_802 = 17;
            printf( "save count %d\n", GM_SaveCount );

            if ( GM_SaveCount > 8 )
            {
                if ( work->field_800 != 0 )
                {
                    s07b_800D7ED8( work, 28 );

                    if ( work->body.action != 8 )
                    {
                        GM_ConfigObjectAction( &work->body, 8, 0, 4 );
                    }

                    work->field_804 = 1;
                    work->flag |= 0x2;
                }
            }
            else
            {
                if ( work->field_800 != 0 )
                {
                    s07b_800D7ED8( work, 29 );

                    if ( work->body.action != 8 )
                    {
                        GM_ConfigObjectAction( &work->body, 8, 0, 4 );
                    }

                    work->flag |= 0x2;
                }
                else
                {
                    s07b_800D7ED8( work, 31 );
                }

                work->field_804 = 1;
            }
        }
        else
        {
            work->field_802 = i + 1;
            printf( "set %d\n", s07b_dword_800C3748[ i ] );
            s07b_800D7ED8(work, s07b_dword_800C3748[ i ] );
            work->field_804 = 1;
        }
    }
    else if ( s07b_800D2C4C() )
    {
        work->field_804--;
    }

    if ( work->field_802 == 17 && work->field_804 == 0 )
    {
        work->field_802 = 18;
        s07b_800D7ED8( work, 27 );
        work->field_804 = 1;
    }
    else if ( work->field_802 == 18 && ( work->field_804 == 0 || s07b_800D2C4C() ) )
    {
        SetMode( work, s07b_800D88E4 );
    }
}

void s07b_800D88E4( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( mts_get_pad_vibration_type( 1 ) == 0 )
        {
            SetMode( work, s07b_800D8B8C );
            return;
        }
        else if ( GM_Configuration & ( GM_CONFIG_UNKNOWN_2000 | GM_CONFIG_VIBRATION_OFF ) )
        {
            SetMode( work, s07b_800D8B8C );
            return;
        }
        else
        {
            s07b_800D7ED8( work, 32 );
        }
    }

    switch ( work->field_800 )
    {
    case 0:
        if ( s07b_800D2C4C() )
        {
            s07b_800D7ED8( work, 33 );
            work->field_800++;
        }
        break;
    case 1:
        if ( s07b_800D2CB4( work->field_814[ 33 ] ) )
        {
            work->field_800++;
        }
        break;
    case 2:
        if ( work->field_802 == 0 )
        {
            s07b_800D7ED8( work, 36 );
        }

        if ( s07b_800D2CB4( work->field_814[ 36 ] ) )
        {
            s07b_800D7ED8( work, 37 );
        }

        if ( s07b_800D2CB4( work->field_814[ 37 ] ) )
        {
            s07b_800D7ED8( work, 38 );
        }

        if ( work->field_802 == 30 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 == 75 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 == 122 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 > 38 )
        {
            if ( work->field_802 < 48 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 70;
            }
            else if ( work->field_802 > 70 && work->field_802 < 112 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 75;
            }
            else if ( work->field_802 > 132 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 74;
            }
        }

        if ( ++work->field_802 > 179 )
        {
            s07b_800D7ED8( work, 34 );
            work->field_800++;
        }
        break;
    case 3:
        if ( s07b_800D2CB4( work->field_814[ 34 ] ) )
        {
            SetMode( work, s07b_800D8B8C );
        }
        break;
    }
}

void s07b_800D8B8C( Work *work, int time )
{
    if ( time == 0 )
    {
        s07b_800D7ED8( work, 35 );
    }

    if ( !( work->flag & 0x4 ) )
    {
        if ( work->body.is_end && work->body.action == 12 )
        {
            work->flag |= 0x4;
            work->m_ctrl.info1.field_14 = 0;
            work->m_ctrl.interp = 15;
        }
    }

    if ( time == 148 )
    {
        GCL_ExecProc( work->field_8B4[ 6 ], NULL );
    }

    if ( s07b_800D2C4C() )
    {
        CloseCinemaScreen();
        if ( work->blur ) GV_DestroyOtherActor( work->blur );
        GCL_ExecProc( work->field_8B4[ 0 ], NULL );
    }
}

void s07b_800D8C60( Work *work )
{
    int frame, se_id;

    frame = work->m_ctrl.info1.frame;
    se_id = 0;
    switch ( work->body.action )
    {
    case 8:
        if ( frame == 0 ) se_id = 195;
        if ( frame == 50 ) se_id = 196;
        break;
    case 11:
        if ( frame == 26 || frame == 66 || frame == 128 || frame == 158 ) se_id = 197;
        break;
    case 12:
        if ( frame == 37 ) se_id = 56;
        break;
    }
    if ( se_id != 0 ) GM_SeSetMode( &work->control.mov, se_id, GM_SEMODE_BOMB );
}

void s07b_800D8D20( Work *work )
{
    int ( *action )( Work *, int );
    int time;

    s07b_800D2A64();
    CheckCinemaTimeout();

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    action = work->action;
    time = work->time;
    if ( time < 16000 ) work->time++;

    if ( !CheckCutsceneSkip( work ) )
    {
        action( work, time );
        s07b_800D7F6C( work );
        s07b_800D8C60( work );
    }
}

static void Act( Work *work )
{
    int ang;

    GM_ActMotion( &work->body );
    GM_ActControl( &work->control );
    GM_ActObject( &work->body );
    DG_GetLightMatrix2( &work->control.mov, work->light );

    ang = GV_Time % 128;
    ang = rsin( ang * 32 ) - rsin( ( ang - 1 ) * 32 );
    work->control.mov.vy += ang * 80 / 4096;

    s07b_800D8D20( work );
}

static void Die( Work *work )
{
    if ( work->shadow != NULL ) GV_DestroyActor( work->shadow );
    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
    GM_PlayerStatus &= ~PLAYER_PAD_OFF;
    GM_GameStatus &= ~STATE_PADMASK;
}

static void s07b_800D8EEC( Work *work )
{
    work->field_7E8 = 0;
    work->flag = 0;

    work->field_800 = work->field_802 = 0;
    work->field_804 = work->field_806 = 0;

    work->field_808 = DG_ZeroVector;

    work->field_7E2 = -1;
    work->field_7E0 = 0;
    work->field_7E4 = 0;

    SetMode( work, s07b_800D80B8 );
}

static void s07b_800D8F60( Work *work )
{
    int i;
    int *data;
    char *str;

    i = 0;
    data = work->field_814;

    if ( GCL_GetOption( 't' ) )
    {
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 40 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

static void s07b_800D8FD4( Work *work )
{
    int i;
    int *data;
    char *str;

    if ( GCL_GetOption( 'f' ) )
    {
        i = 0;
        data = work->field_8B4;
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 7 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

static void InitShadow( Work *work )
{
    SVECTOR indices;

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow( &work->control, &work->body, indices );
}

static int GetResources( Work *work, int name, int where )
{
    CONTROL *control;
    OBJECT  *body;
    u_short  motion;

    control = &work->control;
    if ( GM_InitControl( control, name, where ) < 0 ) return -1;

    GM_ConfigControlString( control, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlHazard( control, 750, -2, -2 );
    control->seg_flag = HZD_SEG_NO_NAVIGATE;
    GM_ConfigControlTrapCheck( control );

    body = &work->body;
    GM_InitObject( body, BODY_DATA, BODY_FLAG, BODY_DATA );
    GM_ConfigObjectJoint( body );

    if ( GCL_GetOption( 'o' ) )
    {
        motion = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        motion = MOTION_DATA;
    }

    GM_ConfigMotionControl( body, &work->m_ctrl, motion, work->m_segs1, work->m_segs2, &work->control, work->rots );
    GM_ConfigObjectLight( body, work->light );
    GM_ConfigObjectAction( body, 0, 0, 0 );

    GM_ConfigMotionAdjust( &work->body, work->adjust );
    work->body.objs->light->t[ 0 ] = 0;
    work->body.objs->light->t[ 1 ] = 0;
    work->body.objs->light->t[ 2 ] = 0;

    InitShadow( work );
    s07b_800D8EEC( work );
    s07b_800D8FD4( work );
    s07b_800D8F60( work );

    GM_GameStatus |= ( STATE_PAUSE_ONLY | PLAYER_PAD_OFF | PLAYER_SECOND_AVAILABLE );
    GM_GameStatus &= ~STATE_PADRELEASE;

    GV_PadMask = ~PAD_START;
    GM_PlayerStatus |= PLAYER_PAD_OFF;
    GM_GameStatus |= STATE_PADMASK;

    /* unequip scope/camera */
    if ( GM_ItemTypes[ GM_Item + 1 ] & 0x2 )
    {
        GM_Item = IT_None;
    }

    /* unequip stinger/psg1 */
    if ( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 )
    {
        GM_Weapon = WP_None;
    }

    if ( GM_Item == IT_NVG || GM_Item == IT_ThermG )
    {
        GM_Item = IT_None;
    }

    work->blur = NewBlurPure();
    return 0;
}

void *NewMemoryPsycho( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work == NULL ) return NULL;

    GV_SetNamedActor( work, Act, Die, "mempsy.c" );
    if ( GetResources( work, name, where ) < 0 )
    {
        GV_DestroyActor( work );
        return NULL;
    }
    return (void *)work;
}
