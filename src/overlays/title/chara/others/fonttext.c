#include "linker.h"
#include "Menu/menuman.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"

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

#define EXEC_LEVEL 5

extern int fonttext_dword_800C32B0;
extern const char fonttext_aS[];
extern const char aFonttextC[];

extern SVECTOR DG_ZeroVector_800AB39C;

int FonttextPollMessages_800C41EC( Work *work, int hash )
{
    GV_MSG *message;
    int     count;

    count = GV_ReceiveMessage_80016620( hash, &message );
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
        GV_DestroyActor_800151C8( &( work->actor ) );
        return;
    }

    x = work->offset.x;
    y = work->offset.y;

    MENU_Locate_80038B34( work->position.vx + x, work->position.vy + y, work->flags );
    MENU_Color_80038B4C( work->color.vx, work->color.vy, work->color.vz );
    MENU_Printf_80038C38( fonttext_aS, work->text );

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

    if ( !GCL_GetOption_80020968( 't' ) )
    {
        return -1;
    }

    work->text = GCL_Read_String_80020A70( GCL_Get_Param_Result_80020AA4() );

    flags = 0;
    if ( GCL_GetOption_80020968( 'f' ) )
    {
        flags = GCL_GetNextParamValue_80020AD4() ? 16 : 0;
    }

    if ( GCL_GetOption_80020968( 'l' ) )
    {
        GCL_ReadParamVector_80020AFC( &position );
    }
    else
    {
        position = DG_ZeroVector_800AB39C;
    }

    work->position = position;

    if ( GCL_GetOption_80020968( 'c' ) )
    {
        GCL_ReadParamVector_80020AFC( &work->color );
    }

    if ( GCL_GetOption_80020968( 's' ) )
    {
        flags |= 0x20 | ( GCL_GetNextParamValue_80020AD4() << 8 );
    }

    work->flags = flags;

    return 0;
}

GV_ACT *NewFonttext_800C446C( int name, int where )
{
    Work *work;

    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)FonttextAct_800C4290, (TActorFunction)FonttextDie_800C4350, aFonttextC );

        if ( FonttextGetResources_800C4358( work ) < 0 )
        {
            GV_DestroyActor_800151C8( &( work->actor ) );
            return NULL;
        }

        work->map = where;
        work->hash = name;
    }

    return &( work->actor );
}
