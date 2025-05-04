#include "../../_shared/enemy/enemy.h"

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

extern void s07a_meryl_unk_800D9E48( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D9F14( WatcherWork *work, int time );
extern void ActOverScoutD_800D9FE0( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA078( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA110( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA1C4( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA28C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA330( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA3F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA610( WatcherWork *work, int time );
extern void s07a_meryl_unk_800DA75C( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7474( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D7504( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D75F8( WatcherWork *work, int time );
extern void s07a_meryl_unk_800D76CC( WatcherWork *work, int time );
extern void ActReadyGun_800D7924( WatcherWork *work, int time );

#define SP_DANBOWLKERI 0x400000