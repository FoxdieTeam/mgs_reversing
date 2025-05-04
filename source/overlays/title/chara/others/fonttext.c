#include "common.h"
#include "menu/menuman.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT  actor;
    int     map;
    int     flags;
    int     hash;
    SVECTOR color;
    SVECTOR position;
    char   *text;
    RECT    offset;
} Work;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern int fonttext_dword_800C32B0;
extern const char fonttext_aS[];
extern const char aFonttextC[];

int FonttextPollMessages_800C41EC( Work *work, int hash )
{
    GV_MSG *message;
    int     count;

    count = GV_ReceiveMessage( hash, &message );
    if ( count > 0 )
    {
        for ( count--; count >= 0; count--, message++ )
        {
            if ( message->message[0] == HASH_KILL )
            {
                return 1;
            }

            if ( message->message[0] == 0xB84C )
            {
                work->offset.w = message->message[1];
                work->offset.h = message->message[2];
            }
        }
    }

    return 0;
}

void FonttextAct_800C4290( Work *work )
{
    int x, y;

    if ( FonttextPollMessages_800C41EC( work, work->hash ) || fonttext_dword_800C32B0 == work->hash )
    {
        fonttext_dword_800C32B0 = 0;
        GV_DestroyActor( &( work->actor ) );
        return;
    }

    x = work->offset.x;
    y = work->offset.y;

    MENU_Locate( work->position.vx + x, work->position.vy + y, work->flags );
    MENU_Color( work->color.vx, work->color.vy, work->color.vz );
    MENU_Printf( fonttext_aS, work->text );

    work->offset.x += work->offset.w;
    work->offset.y += work->offset.h;
}

void FonttextDie_800C4350( Work *work )
{
}

int FonttextGetResources_800C4358( Work *work )
{
    SVECTOR position;
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
        GCL_ReadParamVector( &position );
    }
    else
    {
        position = DG_ZeroVector;
    }

    work->position = position;

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

void *NewFonttext_800C446C( int name, int where )
{
    Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &( work->actor ), FonttextAct_800C4290, FonttextDie_800C4350, aFonttextC );

        if ( FonttextGetResources_800C4358( work ) < 0 )
        {
            GV_DestroyActor( &( work->actor ) );
            return NULL;
        }

        work->map = where;
        work->hash = name;
    }

    return (void *)work;
}
