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
    GCL_SetArgTop_80020690( work->unk3 ) ;

    if ( !work->unk3 )
    {
        return 0 ;
    }


    if ( GCL_Get_Param_Result_80020AA4() )
    {
        work->status = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() ) ;
        work->unk2   = GCL_StrToInt_800209E8( GCL_Get_Param_Result_80020AA4() ) ;
        work->unk3   = GCL_Get_Param_Result_80020AA4() ;
        return 1 ;
    }

    return 0 ;
}

void PadAct_800C370C( PadWork* work )
{
    if ( GM_CheckMessage_8002631C( &work->actor, work->name, HASH_KILL ) )
    {
        GV_DestroyActor_800151C8( &work->actor );
        return;
    }

    if ( (work->unk2 <= 0) && ( PadGetResources_800C3690( work ) == 0) )
    {
        GV_DestroyActor_800151C8( &work->actor );
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
        GCL_ExecProc_8001FF2C( work->unk4 , NULL) ;
    }
}

GV_ACT * NewPad_800C37EC(int name, int where, int argc, char **argv)
{
    int ops;
    PadWork *work ;

    work = (PadWork *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( PadWork ) ) ;

    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )PadAct_800C370C, ( TActorFunction )PadDie_800C37A4, "pad.c" ) ;

        ops = GCL_GetOption_80020968( 's' ) ;
        if ( !ops ) {
            GV_DestroyActor_800151C8( &work->actor ) ;
        }
        work->unk3 = ( char* )ops ;
        work->unk2 = 0;
        work->name = name ;

        if ( GCL_GetOption_80020968( 'p' ) )
        {
            work->unk4 = GCL_GetNextParamValue_80020AD4();
        } else
        {
            work->unk4 = -1;
        }

    }
    return &work->actor;
}
