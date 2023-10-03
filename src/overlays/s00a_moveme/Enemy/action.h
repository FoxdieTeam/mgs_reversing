#include "watcher.h"

#define COM_ST_DANBOWL 0x2000
#define SP_DANBOWLKERI 0x400000

#define ACTINTERP   4

#define STANDSTILL  0
#define ACTION1     1  //WALKING HOLDING GUN
#define ACTION2     2  //RUNNING HOLDING GUN
#define ACTION3     3  //STANDING AIMING GUN
#define ACTION4     4  //STANDING FIRING GUN
#define ACTION5     5  //SEMI-CROUCHING AIMING GUN
#define ACTION6     6  //SEMI_CROUCHING FIRING GUN
#define GRENADE     7
#define ACTION8     8  //HITTING WITH GUN
#define ACTION9     9  //STANDING LOOKING TO THE RIGHT
#define ACTION10    10 //STANDING LOOKING TO THE LEFT
#define ACTION11    11 //STANDING LOOKING DOWN
#define ACTION12    12 //CROUCHING LOOKING FORWARD
#define ACTION13    13 //CROUCHING LOOKING A BIT TO THE RIGHT
#define ACTION14    14 //LOOKING UP
#define ACTION15    15 //GETTING HIT FROM THE FRONT
#define ACTION16    16 //GETTING HIT FROM BEHIND?
#define DANBOWLKERI 17
#define DANBOWLPOSE 18
#define ACTION19    19 //STRETCHING
#define ACTION20    20 //SLEEPING WHILST STANDING
#define ACTION21    21 //WAKING UP SUDDENLY?
#define ACTION22    22 //TALKING ON RADIO?
#define ACTION23    23 //RUBBING NECK
#define ACTION24    24 //SNEEZING
#define ACTION25    25 //I-POSE Maybe not used on this stage
#define ACTION26    26 //I-POSE Maybe not used on this stage
#define ACTION27    27 //GETTING HELD BY SNAKE
#define ACTION28    28 //PRE-NECK SNAP
#define ACTION29    29 //NECK SNAP AND FALLING TO FLOOR
#define ACTION30    30 //FALLING TO FLOOR
#define ACTION31    31 //GETTING FLIPPED OVER
#define ACTION32    32 //SHEILDING EYES
#define ACTION33    33 //STRUGGLING WHILST BEING HELD?
#define ACTION34    34 //FALLING TO THE FLOOR QUICKLY
#define ACTION35    35 //KNOCKED BACKWARDS
#define ACTION36    36 //KNOCKED FORWARDS
#define ACTION37    37 //NECK SNAP AND FALLING TO FLOOR FORWARDS
#define ACTION38    38 //FALLING TO THE FLOOR AND HAVING SOME SORT OF SEIZURE
#define ACTION39    39 //ON FLOOR ON STOMACH
#define ACTION40    40 //ON FLOOR ON BACK
#define ACTION41    41 //ON FLOOR ON STOMACH FACE DOWN
#define ACTION42    42 //FALLING FACE FIRST AND GETTING UP
#define ACTION43    43 //FALLING BACKWARDS AND GETTING UP
#define ACTION44    44 //BIKKURI GET UP FACE DOWN
#define ACTION45    45 //BIKKURI GET UP BACKWARDS
#define ACTION46    46 //JUST BEEN KNOCKED ONTO THE FLOOR ON FLOOR STOMACH
#define ACTION47    47 //JUST BEEN KNOCKED ONTO THE FLOOR ON BACK
#define ACTION48    48 //BEING DRAGGED BACKWARDS WHILST BEING HELD
#define ACTION49    49 //SAME ID AS 40
#define ACTION50    50 //SAME ID AS 41
#define ACTION51    51 //SAME ID AS 42

extern short    ActTable_800C3358[];

typedef	void    ( *ACTION )( WatcherWork *, int ) ;

static inline void SetModeFields( WatcherWork *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.field_4C_turn_vec.vz = 0;
    work->control.field_4C_turn_vec.vx = 0;
}

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
extern void ActGrenade_800C67EC( WatcherWork *work, int time );