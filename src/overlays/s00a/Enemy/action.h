#include "watcher.h"

#define COM_ST_DANBOWL 0x2000
#define SP_DANBOWLKERI 0x400000

#define ACTINTERP   4

#define STANDSTILL  0
#define ACTION1     1
#define ACTION2     2
#define ACTION3     3
#define ACTION4     4
#define ACTION5     5
#define ACTION6     6
#define GRENADE     7
#define ACTION8     8
#define ACTION9     9
#define ACTION10    10
#define ACTION11    11
#define ACTION12    12
#define ACTION13    13
#define ACTION14    14
#define ACTION15    15
#define ACTION16    16
#define DANBOWLKERI 17
#define DANBOWLPOSE 18

extern short    ActTable_800C3358[];

typedef	void	( *ACTION )( WatcherWork *, int ) ;

static inline void SetMode( WatcherWork *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

static inline void SetMode2( WatcherWork *work, void *func )
{
    if ( work->field_8F0_func == NULL )
    {
        work->field_8F0_func = func;
        work->field_8F8 = 0;
    }

    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

static inline void UnsetMode2( WatcherWork *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    
    work->field_8F0_func = 0;
    work->field_8F8 = 0;
    work->field_8E2 = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
    
    if ( work->field_B68 )
    {
        GV_DestroyOtherActor_800151D8( work->field_B68 );
        work->field_B68 = 0;
    }
    
}

static inline void SetAction( WatcherWork *work, int n_action, int interp )
{
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction_80034CD4( &( work->body ), ActTable_800C3358[n_action], 0, interp );
}

static inline void UnsetAction( WatcherWork *work, int n_action )
{
    work->field_8E2 = n_action;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetAction2( WatcherWork *work )
{
    work->field_8E2 = 0;
    GM_ConfigObjectOverride_80034D30( &( work->body ), ActTable_800C3358[STANDSTILL], 0, ACTINTERP, 0 );
    GV_DestroyOtherActor_800151D8( work->subweapon );
}

extern void ActUnknown1_800C841C();
extern void ActUnknown2_800C84FC();
extern void ActOverScoutD_800C85DC();
extern void ActUnknown4_800C8688();
extern void ActUnknown5_800C8734();
extern void ActUnknown6_800C87FC();
extern void ActUnknown7_800C88D8();
extern void ActUnknown8_800C8990();
extern void ActUnknown9_800C8A6C();
extern void ActUnknown10_800C8C98();
extern void ActUnknown11_800C8DF8();
extern void ActUnknown12_800C615C(); 
extern void ActUnknown13_800C6164();
extern void ActUnknown14_800C624C();
extern void ActUnknown15_800C6320();
extern void ActUnknown16_800C65A8();
extern void ActStandStill_800C5C84();
extern void ActUnknown_800C5E48();