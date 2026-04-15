#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT  actor;
    int     map;
    int     flags;
    int     name;
    SVECTOR color;
    SVECTOR pos;
    char   *text;
    RECT    offset;
} Work;

/*---------------------------------------------------------------------------*/

extern int fonttext_dword_800C32B0;

static int CheckMessage( Work *work, int name )
{
    GV_MSG *msg;
    int     count;

    count = GV_ReceiveMessage( name, &msg );
    if ( count > 0 )
    {
        for ( count--; count >= 0; count--, msg++ )
        {
            if ( msg->message[0] == HASH_KILL )
            {
                return 1;
            }

            if ( msg->message[0] == 0xB84C )
            {
                work->offset.w = msg->message[1];
                work->offset.h = msg->message[2];
            }
        }
    }

    return 0;
}

static void Act( Work *work )
{
    int x, y;

    if ( CheckMessage( work, work->name ) || fonttext_dword_800C32B0 == work->name )
    {
        fonttext_dword_800C32B0 = 0;
        GV_DestroyActor( &( work->actor ) );
        return;
    }

    x = work->offset.x;
    y = work->offset.y;

    MENU_Locate( work->pos.vx + x, work->pos.vy + y, work->flags );
    MENU_Color( work->color.vx, work->color.vy, work->color.vz );
    MENU_Printf( "%s", work->text );

    work->offset.x += work->offset.w;
    work->offset.y += work->offset.h;
}

static void Die( Work *work )
{
    /* do nothing */
}

static int GetResources( Work *work )
{
    SVECTOR pos;
    int     flags;

    if ( !GCL_GetOption( 't' ) )
    {
        return -1;
    }

    work->text = GCL_ReadString( GCL_GetParamResult() );

    flags = 0;
    if ( GCL_GetOption( 'f' ) )
    {
        flags = GCL_GetNextParamValue() ? 16 : 0;
    }

    if ( GCL_GetOption( 'l' ) )
    {
        GCL_ReadParamVector( &pos );
    }
    else
    {
        pos = DG_ZeroVector;
    }

    work->pos = pos;

    if ( GCL_GetOption( 'c' ) )
    {
        GCL_ReadParamVector( &work->color );
    }

    if ( GCL_GetOption( 's' ) )
    {
        flags |= 0x20 | ( GCL_GetNextParamValue() << 8 );
    }

    work->flags = flags;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewFontText( int name, int where )
{
    Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), Act, Die, "fonttext.c" );

        if ( GetResources( work ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return (void *)work;
}
