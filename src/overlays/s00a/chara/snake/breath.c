#include "linker.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

/*
TODO:
    Matched on decomp.me, pipeline not set up to match overlays yet
*/

extern int          GV_Time_800AB330;
extern int          GM_AlertMode_800ABA00;
extern unsigned int GM_PlayerStatus_800ABA50;
extern OBJECT      *dword_800ABA20;

extern void sub_800C3AA8( DG_OBJ *obj );

#define EXEC_LEVEL 5 //goes in libgv.h

extern const char aBreathC[];

typedef struct Work
{
    GV_ACT         actor;
    unsigned short unk;
    unsigned short unk2;
    int            unk3;
} Work;


void BreathAct_800C38A0( Work* work )
{
    GV_MSG    *message;
    int        message_result;
    OBJECT    *object;

    message_result = GV_ReceiveMessage_80016620( work->unk, &message );

    for (; message_result > 0 ; --message_result, ++message )
    {
        switch ( message->message[0] )
        {
            case 0xDD2:
                work->unk2 = 1;
                break;
            default:
                work->unk2 = 0;
        }        
    }
    
    if ( work->unk2 != 0 && GM_AlertMode_800ABA00 != 3 && !( GM_PlayerStatus_800ABA50 & 0x2013 ) )
    {
        object = dword_800ABA20;
        if  ( object != NULL && ( GV_Time_800AB330 % work->unk3 == 0 ) )
        {
            sub_800C3AA8( &object->objs->objs[6] );
        }
    }     
}


void BreathDie_800C39AC( Work* work )
{
    return;
}


int BreathGetResources_800C39B4( Work *work, int name, int where )
{
    if (GCL_GetParam_80020968(0x74) != 0)
    {
         work->unk3 = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->unk3 = 0x40;
    }

    work->unk = name;
    work->unk2 = 1;
    return 0;   
}

void        *NewBreath_800C3A1C( int name, int where, int argc, char **argv )
{
    Work        *work ;


    work = (Work *)GV_NewActor_800150E4( EXEC_LEVEL, sizeof( Work ) ) ;
    if ( work != NULL ) {
        /* ワークにコールバックを登録する */
        GV_SetNamedActor_8001514C( &( work->actor ), ( TActorFunction )BreathAct_800C38A0, ( TActorFunction )BreathDie_800C39AC, aBreathC ) ;
        if ( BreathGetResources_800C39B4( work, name, where ) >= 0 ) {
            return (void *)work ;            
        }
        GV_DestroyActor_800151C8( (GV_ACT *) work ) ;
    }    
    return NULL ;
}