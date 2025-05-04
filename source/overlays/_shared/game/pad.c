#include "common.h"
#include "game/game.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "strcode.h"

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _PadWork
{
    GV_ACT         actor;
    int            name; //0x20
    unsigned short status; //0x24
    short          unk2; //0x26
    char*          unk3; //0x28
    int            unk4; //0x2C
} PadWork;

STATIC int PadGetResources_800C3690( PadWork* work )
{
    GCL_SetArgTop( work->unk3 ) ;

    if ( !work->unk3 )
    {
        return 0 ;
    }


    if ( GCL_GetParamResult() )
    {
        work->status = GCL_StrToInt( GCL_GetParamResult() ) ;
        work->unk2   = GCL_StrToInt( GCL_GetParamResult() ) ;
        work->unk3   = GCL_GetParamResult() ;
        return 1 ;
    }

    return 0 ;
}

STATIC void PadAct_800C370C( PadWork* work )
{
    if ( GM_CheckMessage( &work->actor, work->name, HASH_KILL ) )
    {
        GV_DestroyActor( &work->actor );
        return;
    }

    if ( (work->unk2 <= 0) && ( PadGetResources_800C3690( work ) == 0) )
    {
        GV_DestroyActor( &work->actor );
    }

    --work->unk2;
    GM_GameStatus |= STATE_PADDEMO;
    GV_DemoPadStatus[0] = work->status;
}

STATIC void PadDie_800C37A4( PadWork* work )
{
    GV_DemoPadStatus[0] = 0 ;
    GM_GameStatus &= ~STATE_PADDEMO;

    if ( work->unk4 > 0 )
    {
        GCL_ExecProc( work->unk4 , NULL) ;
    }
}

void *NewPad_800C37EC(int name, int where, int argc, char **argv)
{
    char *ops;
    PadWork *work ;

    work = GV_NewActor( EXEC_LEVEL, sizeof( PadWork ) ) ;

    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor( &( work->actor ), PadAct_800C370C, PadDie_800C37A4, "pad.c" ) ;

        ops = GCL_GetOption( 's' ) ;
        if ( !ops ) {
            GV_DestroyActor( &work->actor ) ;
        }
        work->unk3 = ops ;
        work->unk2 = 0;
        work->name = name ;

        if ( GCL_GetOption( 'p' ) )
        {
            work->unk4 = GCL_GetNextParamValue();
        } else
        {
            work->unk4 = -1;
        }

    }
    return (void *)work;
}
