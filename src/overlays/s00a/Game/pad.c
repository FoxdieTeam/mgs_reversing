#include "linker.h"
#include "Game/game.h"
#include "libgv/libgv.h"
#include "libgcl/hash.h"
#include "libgcl/libgcl.h"

extern unsigned short GV_DemoPadStatus_800AB958;

#define EXEC_LEVEL 5

typedef struct _PadWork
{
    GV_ACT         actor;
    int            name; //0x20
    unsigned short status; //0x24
    short          unk2; //0x26
    char*          unk3; //0x28
    int            unk4; //0x2C
} PadWork;

int PadGetResources_800C3690( PadWork* work )
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

void PadAct_800C370C( PadWork* work )
{
    if ( GM_CheckMessage_8002631C( &work->actor, work->name, HASH_KILL ) )
    {
        GV_DestroyActor( &work->actor );
        return;
    }

    if ( (work->unk2 <= 0) && ( PadGetResources_800C3690( work ) == 0) )
    {
        GV_DestroyActor( &work->actor );
    }

    --work->unk2;
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_31;
    GV_DemoPadStatus_800AB958 = work->status;
}

void PadDie_800C37A4( PadWork* work )
{
    GV_DemoPadStatus_800AB958 = 0 ;
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_31;

    if ( work->unk4 > 0 )
    {
        GCL_ExecProc( work->unk4 , NULL) ;
    }
}

GV_ACT * NewPad_800C37EC(int name, int where, int argc, char **argv)
{
    char *ops;
    PadWork *work ;

    work = (PadWork *)GV_NewActor( EXEC_LEVEL, sizeof( PadWork ) ) ;

    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor( &( work->actor ), ( TActorFunction )PadAct_800C370C, ( TActorFunction )PadDie_800C37A4, "pad.c" ) ;

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
    return &work->actor;
}
