#include "change.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

#include "common.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "Font/font.h"
#include "Game/game.h"
#include "SD/g_sound.h"

// FIXME: it's the same struct as in preope.c (in preope overlay)
typedef struct _Unknown
{
    SPRT  sprt[2];
    SPRT  sprt2[2][4];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short f0;
    short f2;
    short f4;
    short f6;
} Unknown;

typedef struct _Work
{
    GV_ACT   actor;
    GV_PAD  *pad_data;
    int      proc;
    KCB      kcb[6];
    char     pad[0x14];
    DR_TPAGE tpage;
    Unknown  f14C[6];
    int      f68C;
    int      f690;
    int      clut_x;
    int      clut_y;
    GV_ACT  *f69C;
    int      f6A0;
    int      f6A4;
    int      f6A8;
    int      f6AC;
    int      f6B0;
    int      f6B4;
    int      f6B8;
    int      f6BC;
} Work;

extern int    GV_Clock;
extern int    GM_CurrentMap;
extern int    FS_DiskNum_800ACBF0;
extern GV_PAD GV_PadData_800B05C0[4];

// FIXME: it's the same struct (but different data) as in preope.c (in preope overlay)
typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

Unknown2 dword_800C3218[6] = {
    {1, 160, 190, 0x6739},
    {1, 160, 210, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
    {1, 160, 190, 0x6739},
};

signed char byte_800C3260[] = {
    -1,  0,
     1,  0,
     0,  1,
     0, -1,
};

int  Safety_800C45F8( int lba, int timeout );
void Safety_800C4714( void );

GV_ACT *NewMetLogo_800C5A90( int * );

#define EXEC_LEVEL 1

void Change_800C364C( Work *work, int index )
{
    RECT rect;
    KCB *kcb;

    kcb = &work->kcb[ index ];

    rect.x = work->f68C;
    rect.y = work->f690;
    rect.w = 64;
    rect.h = 21;

    work->f14C[ index ].f0 = work->f68C;
    work->f14C[ index ].f2 = work->f690;
    work->f690 += 21;

    font_init_kcb( kcb, &rect, work->clut_x, work->clut_y );

    work->f14C[ index ].f4 = work->clut_x;
    work->f14C[ index ].f6 = work->clut_y;
    work->clut_y += 21;

    font_set_kcb( kcb, -1, -1, 0, 6, 2, 0 );

    font_set_buffer( kcb, GV_AllocMemory( GV_NORMAL_MEMORY, font_get_buffer_size( kcb ) ) );
    font_set_color( kcb, 0, dword_800C3218[ index ].color, 0 );
    font_clut_update( kcb );
}

void Change_800C378C( Work *work, int index )
{
    KCB      *kcb;
    char     *string;
    Unknown2 *unknown;

    string = work->f14C[ index ].string;

    if ( string )
    {
        kcb = &work->kcb[ index ];

        font_print_string( kcb, string );
        font_update( kcb );
        font_clut_update( kcb );

        work->f14C[ index ].rect.w = kcb->max_width;
        work->f14C[ index ].rect.h = kcb->short3 - 1;

        unknown = &dword_800C3218[ index ];

        if ( unknown->num == 0 )
        {
            work->f14C[ index ].rect.x = unknown->x;
            work->f14C[ index ].rect.y = unknown->y;
        }
        else if ( unknown->num == 1 )
        {
            work->f14C[ index ].rect.x = unknown->x - kcb->max_width / 2;
            work->f14C[ index ].rect.y = unknown->y - kcb->short3 / 2;
        }

        work->f14C[ index ].string = NULL;
        work->f14C[ index ].num = 1;
    }
}

void Change_800C38D0( Work *work, char *ot )
{
    int       found;
    int       index;
    int       i;
    SPRT     *sprt;
    SPRT     *sprt2;
    int       j;
    DR_TPAGE *tpage;

    found = 0;

    index = 0;
    for ( i = 0; i < 6; i++ )
    {
        // BUG: The index doesn't increment on continue
        if ( work->f14C[ index ].num != 1 )
        {
            continue;
        }

        found = 1;

        sprt = &work->f14C[ index ].sprt[ GV_Clock ];
        LSTORE( 0x808080, &sprt->r0 );
        LCOPY( &work->f14C[ index ].rect.x, &sprt->x0 );
        LCOPY( &work->f14C[ index ].rect.w, &sprt->w );
        sprt->u0 = 0;
        sprt->v0 = work->f14C[ index ].f2;
        sprt->clut = getClut( work->f14C[ index ].f4, work->f14C[ index ].f6 );
        setSprt( sprt );
        addPrim( ot, sprt );

        sprt2 = work->f14C[ index ].sprt2[ GV_Clock ];
        for ( j = 0; j < 8; j += 2 )
        {
            *sprt2 = *sprt;
            LSTORE( 0x64000000, &sprt2->r0 );
            sprt2->x0 += byte_800C3260[ j ];
            sprt2->y0 += byte_800C3260[ j + 1 ];
            addPrim( ot, sprt2 );
            sprt2++;
        }

        index++;
    }

    if ( found != 0 )
    {
        tpage = &work->tpage;
        setDrawTPage( tpage, 1, 0, getTPage( 0, 0, 832, 256 ) );
        addPrim( ot, tpage );
    }
}

void change_800C3B34( Work *work, int index, int color )
{
    KCB *kcb;

    kcb = &work->kcb[ index ];
    font_set_color( kcb, 0, color, 0 );
    font_clut_update( kcb );
}

void * Change_800C3B84( KCB *kcb )
{
    return kcb->font_clut_buffer;
}

void change_800C3B90( Work *work )
{
    int i;
    int shade;

    for ( i = 0; i < 6; i++ )
    {
        change_800C3B34( work, i, 0 );
    }

    if ( work->f6AC != 0 )
    {
        if ( work->f6A4 <= 64 )
        {
            shade = 25 - ( work->f6A4 * 25 ) / 64;
            change_800C3B34( work, 4, shade << 10 | shade << 5 | shade );
        }

        return;
    }
    else if ( work->f6BC == 0 )
    {
        return;
    }

    switch ( work->f6B0 )
    {
    case 0:
    case 1:
    case 2:
        change_800C3B34( work, 0, 0x6739 );
        break;

    case 3:
    case 4:
        change_800C3B34( work, 1, 0x6739 );
        change_800C3B34( work, 2, 0x6739 );
        break;

    case 5:
    case 6:
    case 7:
    case 8:
        change_800C3B34( work, 3, 0x6739 );
        break;

    case 9:
        change_800C3B34( work, 4, 0x6739 );
        break;

    case 10:
        change_800C3B34( work, 5, 0x6739 );
        break;
    }
}

void change_800C3CD0( Work *work )
{
    char   result[8];
    char   result2[8];
    CdlLOC loc;
    char   param[8];
    int    press;
    int    status;
    int    intr;
    int    error;
    void  *alloc;

    press = work->pad_data->press;

    switch ( work->f6B0 )
    {
    case 0:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->f6B0 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlSetmode, param, result );

        if ( status == 0 )
        {
            printf( "CD NORMAL SPEED SET FAILED!!\n" );
            work->f6A8++;
        }
        else if ( status == 1 )
        {
            work->f6B0 = 1;
            printf( "CD NORMAL SPEED SET SUCCESS!!\n" );
            mts_wait_vbl( 3 );
            work->f6A8 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->f6A8 >= 300 )
        {
            work->f6B0 = 10;
            work->f6B8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 1:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( result[ 0 ] & CdlStatShellOpen )
        {
            work->f6B0 = 3;
            printf( "CD CASE OPEN!!\n" );
            mts_wait_vbl( 3 );
            break;
        }

        param[ 0 ] = 0;
        status = CdControlB( CdlStop, param, result );

        if ( status == 0 )
        {
            printf( "CD STOP FAILED!!\n" );
            work->f6A8++;
        }
        else if ( status == 1 )
        {
            work->f6B0 = 2;
            printf( "CD STOP SUCCESS!!\n" );
            work->f6A8 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->f6A8 >= 300 )
        {
            work->f6B0 = 10;
            work->f6B8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 2:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( !( result[ 0 ] & CdlStatShellOpen ) )
        {
            printf( "CD CASE CLOSE!!\n" );
        }
        else
        {
            work->f6B0 = 3;
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 3:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        if ( !( result[ 0 ] & CdlStatShellOpen ) )
        {
            work->f6B0 = 4;
            printf( "CD CASE CLOSE!!\n" );
        }
        else
        {
            printf( "CD CASE OPEN!!\n" );
        }
        break;

    case 4:
        if ( work->f6BC != 0 && ( press & PAD_START ) )
        {
            work->f6B0 = 5;
            printf( "START BUTTON PUSH!!\n" );

            GM_SeSet2( 0, 63, SE_MENU_SELECT );

            work->f6A8 = 0;
        }
        break;

    case 5:
        param[ 0 ] = 0;
        CdControlB( CdlNop, param, result );

        work->f6A8++;

        if ( result[ 0 ] & CdlStatStandby )
        {
            work->f6B0 = 6;
            printf( "CD SPIN START!!\n" );
            work->f6A8 = 0;
        }
        else
        {
            printf( "CD NOT SPIN!!\n" );
        }

        if ( work->f6A8 >= 300 )
        {
            work->f6B0 = 10;
            work->f6B8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 6:
        param[ 0 ] = 0;
        status = CdControlB( CdlGetTN, param, result );

        if ( status == 0 )
        {
            printf( "CD TOC READ NOT FINISH!!\n" );
            work->f6A8++;
        }
        else if ( status == 1 )
        {
            work->f6B0 = 7;
            printf( "CD TOC READ SUCCESS!!\n" );
            work->f6A8 = 0;
        }
        else
        {
            printf( "???????\n" );
        }

        if ( work->f6A8 >= 600 )
        {
            work->f6B0 = 10;
            work->f6B8 = 0;
            printf( "THIS IS NOT PS DISC!!\n" );
        }
        break;

    case 7:
        work->f6B0 = 8;
        work->f6A8 = 0;
        printf( "CD SPEED INIT SUCCESS!!\n" );
        break;

    case 8:
        CdIntToPos( 16, &loc );
        status = CdControlB( CdlReadN, (char *)&loc, result );

        if ( status == 0 )
        {
            printf( "CD CHECK FAILED[%X:%X]!!\n", result[ 0 ], result[ 1 ] );
            work->f6A8++;

            if ( work->f6A8 >= 300 )
            {
                work->f6B0 = 10;
                work->f6B8 = 0;
                printf( "THIS IS NOT PS DISC!!\n" );
                break;
            }

            if ( result[ 0 ] & ( CdlStatSeek | CdlStatRead ) )
            {
                break;
            }

            if ( result[ 0 ] & CdlStatError && result[ 1 ] & CdlStatSeek )
            {
                work->f6B0 = 10;
                work->f6B8 = 0;
                printf( "THIS IS NOT PS DISC!!\n" );
            }

            if ( result[ 0 ] & CdlStatStandby )
            {
                printf( "This is CDDA\n" );
                work->f6B0 = 10;
                work->f6B8 = 0;
            }

            break;
        }
        else if ( status == 1 )
        {
            intr = CdReady( 0, result2 );

            error = 0;
            if ( intr == CdlDataReady )
            {
                printf( "CD CHECK OK!!\n" );

                if ( result2[ 0 ] & CdlStatError && result2[ 1 ] & CdlStatSeek )
                {
                    error = 1;
                    printf( "THIS IS NOT PS DISC!!!\n" );
                    work->f6B0 = 10;
                    work->f6B8 = 0;
                }
            }
            else if ( intr == CdlDiskError )
            {
                error = 1;
                printf( "CD CHECK ERROR!!\n" );
            }

            if ( error )
            {
                break;
            }

            printf( "THIS IS PS DISC!!\n" );

            Safety_800C45F8( 16, 600 );
            Safety_800C4714();

            alloc = GV_Malloc( 8192 );
            status = FS_ResetCdFilePosition( alloc );

            if ( status == 1 )
            {
                printf( "THIS IS DISC 2!!\n" );
                work->f6B0 = 9;
                FS_DiskNum_800ACBF0 = status;
            }
            else
            {
                printf( "THIS IS NOT DISC 2!!!\n" );
                work->f6B0 = 10;
                work->f6B8 = 0;
            }

            GV_Free( alloc );
        }
        else
        {
            printf( "???????\n" );
        }
        break;

    case 9:
        param[ 0 ] = 0;
        status = CdControlB( CdlPause, param, result );

        work->f6AC = 1;
        work->f6B4 = 1;
        printf( "OK! OK!\n" );
        break;

    case 10:
        work->f6B8++;
        printf( "NOT OK! NOT OK!\n" );

        if ( work->f6B8 >= 30 )
        {
            work->f6B0 = 0;
        }
        break;
    }
}

void ChangeAct_800C4324( Work *work )
{
    if ( work->f6AC != 0 )
    {
        work->f6A4++;
    }

    change_800C3B90( work );
    Change_800C38D0( work, DG_Chanl(1)->mOrderingTables[ GV_Clock ] );
    change_800C3CD0( work );

    if ( work->f6BC == 0 && work->f6A0 >= 160 )
    {
        work->f6BC = 1;
    }

    work->f6A0++;

    if ( work->f6A4 >= 72 )
    {
        GCL_ExecProc( work->proc, NULL );
        GV_DestroyActor( &( work->actor ) );
    }
}

void ChangeDie_800C43EC( Work *work )
{
    int i;

    for ( i = 0; i < 6; i++ )
    {
        GV_FreeMemory( GV_NORMAL_MEMORY, Change_800C3B84( &work->kcb[i] ) );
    }
}

int ChangeGetResources_800C4448( Work *work, int map )
{
    int i;

    GM_CurrentMap = map;

    work->pad_data = &GV_PadData_800B05C0[ 2 ];

    work->f68C = 832;
    work->f690 = 256;
    work->clut_x = 832;
    work->clut_y = 276;

    if ( GCL_GetOption( 'e' ) )
    {
        work->proc = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->proc = -1;
    }

    for ( i = 0; i < 6; i++ )
    {
        work->f14C[i].string = GCL_ReadString( GCL_GetParamResult() );
        work->f14C[i].num = 0;
        Change_800C364C( work, i );
    }

    for ( i = 0; i < 6; i++ )
    {
        Change_800C378C( work, i );
    }

    work->f6B4 = 0;
    work->f69C = NewMetLogo_800C5A90( &work->f6B4 );
    work->f6A0 = 0;
    work->f6AC = 0;
    work->f6A4 = 0;
    work->f6B0 = 0;
    work->f6A8 = 0;
    work->f6BC = 0;

    return 0;
}

GV_ACT *NewChange_800C455C( int name, int where, int argc, char **argv )
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = (Work *)GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if (work != NULL)
    {
        GV_SetNamedActor( &( work->actor ), (GV_ACTFUNC)ChangeAct_800C4324, (GV_ACTFUNC)ChangeDie_800C43EC, "change.c" );

        if ( ChangeGetResources_800C4448( work, where ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }
    }

    return &( work->actor );
}
