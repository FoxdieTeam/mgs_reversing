#include "Game/game.h"
#include "Game/object.h"
#include "Game/camera.h"
#include "Weapon/weapon.h"
#include "Game/homing_target.h"

typedef struct _WatcherPad
{
    int   press;           //0x04       //0xB38
    int   field_08;        //0x08       //0xB3C
    int   tmp;             //0x0A       //0xB40
    int   time;            //0x0C       //0xB44
    short dir;             //0x10       //0xB48
    short sound;           //0x12       //0xB4A
} WatcherPad;

typedef struct _WatcherUnk
{
    int   field_00;    //0x00        //0x8C8
    short field_04;    //0x04        //0x8CC
    short field_06;    //0x06        //0x8CE
    int   field_08;    //0x08        //0x8D0
    int   field_0C;    //0x0C        //0x8D4
    int   field_10;    //0x10        //0x8D8
    int   field_14;    //0x14        //0x8DC
    short field_18;    //0x18        //0x8E0
    short field_1A;    //0x1A        //0x8E2
    short field_1C;    //0x1C        //0x8E4
    short field_1E;    //0x1E        //0x8E6
    short field_20;    //0x20        //0x8E8
    short field_22;    //0x22        //0x8EA
} WatcherUnk;

typedef struct _VISION
{
    short          facedir;                    //0xB8C
    short          field_B8E;                  //0xB8A
    short          length;                     //0xB90
    short          field_B92;                  //0xB92
} VISION;

typedef struct _WatcherWork
{
    GV_ACT         actor;
    CONTROL        control;                    //0x20
    OBJECT         body;                       //0x9C
    int            field_180;                  //0x180
    void          *kmd;                        //0x184
    DG_DEF        *def;                        //0x188
    MOTION_CONTROL m_ctrl;                     //0x18C
    OAR_RECORD     field_1DC[34];              //0x1DC
    SVECTOR        rots[16];                   //0x6A4
    SVECTOR        field_724;                  //0x724
    int            field_72C;                  //0x72C
    int            field_730;                  //0x730
    short          field_734;                  //0x734
    short          field_736;                  //0x736
    char           field_738[0x1C];            //0x738
    short          field_754;                  //0x754
    short          field_756;                  //0x756
    short          field_758;                  //0x756
    short          field_75A;                  //0x756
    short          field_75C;                  //0x75C
    short          field_75E;                  //0x75C
    char           field_760[0x44];            //0x760
    OBJECT         field_7A4;                  //0x7A4
    MATRIX         field_888;                  //0x888
    int            field_8A8;                  //0x8A8
    int            field_8AC;                  //0x8AC
    int            field_8B0;                  //0x8B0
    int            field_8B4;                  //0x8B4
    int            field_8B8;                  //0x8B8
    int            field_8BC;                  //0x8BC
    int            field_8C0;                  //0x8C0
    int            field_8C4;                  //0x8C4
    int            field_8C8;                  //0x8C8
    int            field_8CC;                  //0x8CC
    int            field_8D0;                  //0x8D0
    SVECTOR        field_8D4;                  //0x8D4
    int            field_8DC;                  //0x8DC
    short          field_8E0;                  //0x8E0
    short          field_8E2;                  //0x8E2
    short          field_8E4;                  //0x8E4
    short          field_8E6;                  //0x8E6
    int            field_8E8;                  //0x8E8
    void*          action;                     //0x8EC
    void*          action2;                    //0x8F0
    int            time;                       //0x8F4
    int            time2;                      //0x8F8
    int            actend;                     //0x8FC
    TARGET        *target;                     //0x900
    TARGET         field_904;                  //0x904
    TARGET         field_94C;                  //0x94C
    TARGET         punch;                      //0x994
    HOMING        *hom;                        //0x9DC
    short          scale;                      //0x9E0
    short          field_9E2;                  //0x9E2
    short          visible;                    //0x9E4
    short          field_9E6;                  //0x9E6
    int            field_9E8;                  //0x9E8
    SVECTOR        nodes[0x20];                //0x9EC
    int            search_flag;                //0xAEC
    GV_ACT*        field_AF0;                  //0xAF0
    int           *field_AF4;                  //0xAF4
    GV_ACT*        field_AF8;                  //0xAF8
    int           *field_AFC;                  //0xAFC
    void          *field_B00[8];               //0xB00
    short          think1;                     //0xB20
    short          think2;                     //0xB22
    short          think3;                     //0xB24
    short          think4;                     //0xB26
    unsigned int   count3;                     //0xB28
    int            t_count;                    //0xB2C
    int            l_count;                    //0xB30
    int            next_node;                  //0xB34
    WatcherPad     pad;                        //0xB38
    short          field_B4C;                  //0xB4C
    short          field_B4E;                  //0xB4E
    unsigned int   trigger;                    //0xB50
    GV_ACT*        subweapon;                  //0xB54
    short          field_B58;                  //0xB58
    short          field_B5A;                  //0xB5A
    short          field_B5C;                  //0xB5C
    short          field_B5E;                  //0xB5E
    int            field_B60;                  //0xB60
    int            field_B64;                  //0xB64
    GV_ACT        *field_B68;                  //0xB68
    int            mark_time;                  //0xB6C    //could be wrong
    int            act_status;                 //0xB70
    int            field_B74;                  //0xB74
    signed char    field_B78;                  //0xB78
    signed char    param_blood;                //0xB79  //param.blood (should be struct)
    signed char    param_area;                 //0xB7A  //param.area  (should be struct)
    signed char    field_B7B;                  //0xB7B
    char           field_B7C;                  //0xB7C
    signed char    field_B7D;                  //0xB7D  //used as node index
    char           field_B7E;                  //0xB7E
    char           field_B7F;                  //0xB7F
    signed char    param_item;                 //0xB80  //param.item  (should be struct)
    char           field_B81;                  //0xB81
    short          param_life;                 //0xB82  //param.life  (should be struct)
    short          param_faint;                //0xB84  //param.faint (should be struct)
    char           local_data;                 //0xB86
    char           local_data2;                //0xB87
    int            field_B88;                  //0xB88
    VISION         vision;                     //0xB8C
    short          field_B94;                  //0xB94
    short          field_B96;                  //0xB96
    int            alert_level;                //0xB98
    signed char    modetime[4];                //0xB9C
    signed char    field_BA0;                  //0xBA0
    char           field_BA1;                  //0xBA1
    char           field_BA2;                  //0xBA2
    char           field_BA3;                  //0xBA3
    SVECTOR        field_BA4;                  //0xBA4
    int            field_BAC;                  //0xBAC
    int            field_BB0[8];               //0xBB0 //set_time
    short          field_BD0[4];               //0xBD0 //set_dir, might be svector
    SVECTOR        start_pos;                  //0xBD8
    SVECTOR        target_pos;                 //0xBE0
    int            start_addr;                 //0xBE8
    int            start_map;                  //0xBEC
    int            field_BF0;                  //0xBF0
    int            target_addr;                //0xBF4
    int            target_map;                 //0xBF8
    int            field_BFC;                  //0xBFC
    int            field_C00;                  //0xC00
    int            field_C04;                  //0xC04
    int            field_C08;                  //0xC08
    int            field_C0C;                  //0xC0C
    int            field_C10;                  //0xC10
    SVECTOR        field_C14;                  //0xC14
    int            field_C1C;                  //0xC1C
    int            field_C20;                  //0xC20
    int            sn_dis;                     //0xC24
    int            sn_dir;                     //0xC28
    short          faseout;                    //0xC2C
    short          field_C2E;                  //0xC2E
    int            field_C30;                  //0xC30
    char           field_C34;                  //0xC34 //num_set_time
    char           field_C35[7];               //0xC35 //set_time
    int            field_C3C;                  //0xC3C
    int            field_C40;                  //0xC40
    int            field_C44;                  //0xC44
    short          field_C48;                  //0xC48
    short          field_C4A;                  //0xC4A
} WatcherWork;

typedef struct _CommanderWork
{
    GV_ACT         actor;
    unsigned short unk;  //0x20
    unsigned short unk2; //0x22
    int            name; //0x24
} CommanderWork;

typedef struct _TOPCOMMAND_STRUCT {
    int mode;
    int alert;
} TOPCOMMAND_STRUCT;

typedef struct _A4_INNER_STRUCT
{
    unsigned short field_00;    //0x00
    unsigned short field_02;    //0x02

} A4_INNER_STRUCT;

typedef struct _A4_STRUCT
{
    unsigned short  map_id;      //0x00
    unsigned short  n_entry;     //0x02
    A4_INNER_STRUCT field_04[8]; //0x04
} A4_STRUCT;

typedef struct _C8_STRUCT
{
    int          field_00;      //0x00
    int          field_04;      //0x04
    int          field_08;      //0x08
    WatcherWork *watcher;       //0x0C
} C8_STRUCT;

typedef struct _ENEMY_COMMAND
{
    int       field_0x00;
    int       field_0x04;
    int       field_0x08;
    int       field_0x0C;
    int       field_0x10;
    int       alert;        //0x14
    int       mode;         //0x18
    int       field_0x1C;
    int       field_0x20[8];
    int       field_0x40;
    int       com_addr;   //0x44
    int       com_map;    //0x48
    SVECTOR   com_pos;    //0x4C
    short     field_0x54;
    short     c_reset_pos; //0x56
    short     field_0x58[8];
    int       field_0x68[8];
    SVECTOR   field_0x88;
    int       reset_enemy_num;
    int       reset_enemy_max;
    int       field_0x98;
    int       field_0x9C;
    MAP      *map;            //0xA0
    A4_STRUCT field_0xA4;
    C8_STRUCT field_0xC8[8];
    int       field_0x148[8];
    int       field_0x168;
    int       field_0x16C;
    int       field_0x170;
    int       field_0x174;
    short     field_0x178;
    short     field_0x17A;
    int       field_0x17C;
    short     field_0x180;
    short     field_0x182;
} ENEMY_COMMAND;

//command.c
#define TOP_COMM_TRAVEL 0
#define TOP_COMM_ALERT  1

void  s00a_command_800CEC40( SVECTOR *mov , int n );
int  s00a_command_800CEA2C( WatcherWork *work );
void  s00a_command_800CEC90( void ) ;
void  s00a_command_800CECF4( void ) ;
int   s00a_command_800CEDE8( int ops, short *val, int where );
int   s00a_command_800CED88( int ops, A4_STRUCT * );
void  s00a_command_800CFA94( CommanderWork* work ) ;
void  s00a_command_800CFEA8( void ) ;
int   s00a_command_800D0128( int ops );
void  s00a_command_800D018C( CommanderWork* work ) ;
void  s00a_command_800D0218( void ) ;
void  s00a_command_800D0344( void ) ;
void  EnemyPushMove_800CA0E8( WatcherWork* work );
void  EnemyActionMain_800CA07C( WatcherWork* work );
void *AN_Unknown_800CA1EC( MATRIX* mat, int mark);
void ENE_SetGopointLast_800CEB00();
void ENE_SetTopCommAL_800CEAE8( int alert );

void SetCameraActCall_800D043C();
void UnsetCameraActCall_800D047C();

//watcher.c
#define EN_FASEOUT 0x10000000

//check.c
int s00a_command_800C580C( int a, int b );
int CheckDamage_800C5424( WatcherWork * work ) ;
int CheckPad_800C5A60( WatcherWork *work ) ;
void s00a_command_800C55B0( WatcherWork* work ) ;
void s00a_command_800C5860( WatcherWork* work ) ;
int  AttackForce_800C58E8( WatcherWork * work ) ;
void s00a_command_800C59F8( WatcherWork *work ) ;
int  s00a_command_800C513C( WatcherWork* work ) ;

//put.c

#define PUTBREATH 1


#define BW_MARK 4

typedef void( *PUTFUNC )( WatcherWork * ) ;

void ENE_PutMark_800C9378( WatcherWork *work, int mark ) ;
void ENE_PutBlood_800C8FF8( WatcherWork *work, int put, int i ) ;
void ENE_PutItem_800C90CC( WatcherWork *work ) ;
int  ENE_SetPutChar_800C979C( WatcherWork *work, int put ) ;

void ENE_PutFog_800C9068( WatcherWork *work ) ;
int  ENE_ClearPutChar_800C97E4( WatcherWork *work, void *func ) ;
void ENE_ExecPutChar_800C9818( WatcherWork *work ) ;



//route.c
void s00a_command_800CB0E0( WatcherWork* work );
void s00a_command_800CAFD4( WatcherWork* work );
void s00a_command_800CAB74( WatcherWork* work );
void s00a_command_800CAB04( WatcherWork* work );
void s00a_command_800CAD84( WatcherWork *work );
void s00a_command_800CAACC( WatcherWork* work );
void s00a_command_800CB1C4( WatcherWork* work );

//action.c
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

typedef void    ( *ACTION )( WatcherWork *, int ) ;

static inline void SetModeFields( WatcherWork *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
}

static inline void SetMode( WatcherWork *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

static inline void SetMode2( WatcherWork *work, void *func )
{
    if ( work->action2 == NULL )
    {
        work->action2 = func;
        work->time2 = 0;
    }

    work->control.field_4C_turn.vz = 0;
    work->control.field_4C_turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

void s00a_command_800C82B0( WatcherWork *work );

void s00a_command_800C78E0( WatcherWork *work, int time );
void s00a_command_800C77C8( WatcherWork *work, int time );
void s00a_command_800C7354( WatcherWork *work, int time );

void s00a_command_800C841C( WatcherWork *work, int time );
void s00a_command_800C84FC( WatcherWork *work, int time );
void s00a_command_800C8688( WatcherWork *work, int time );
void s00a_command_800C8734( WatcherWork *work, int time );
void s00a_command_800C87FC( WatcherWork *work, int time );

void s00a_command_800C88D8( WatcherWork *work, int time );
void s00a_command_800C8990( WatcherWork *work, int time );
void s00a_command_800C8A6C( WatcherWork *work, int time );
void s00a_command_800C8C98( WatcherWork *work, int time );
void s00a_command_800C8DF8( WatcherWork *work, int time );
void s00a_command_800C615C( WatcherWork *work, int time );
void s00a_command_800C6164( WatcherWork *work, int time );
void s00a_command_800C624C( WatcherWork *work, int time );
void s00a_command_800C6320( WatcherWork *work, int time );
void s00a_command_800C65A8( WatcherWork *work, int time );
void s00a_command_800C5E48( WatcherWork *work, int time );


void s00a_command_800C6724( WatcherWork *work, int time );
void s00a_command_800C67E4( WatcherWork *work, int time );
void s00a_command_800C6A40( WatcherWork *work, int time );
void s00a_command_800C8054( WatcherWork *work, int time );
void s00a_command_800C7498( WatcherWork *work, int time );

void s00a_command_800C76BC( WatcherWork *work, int time );
void s00a_command_800C76C4( WatcherWork *work, int time );
void s00a_command_800C7E28( WatcherWork *work, int time );
void s00a_command_800C818C( WatcherWork *work, int time );


void ActGrenade_800C67EC( WatcherWork *work, int time );
void ActOverScoutD_800C85DC( WatcherWork *work, int time );


//think.c ?
#define T_NOISE 0

#define TH3_ATTACK_NEAR    0x19
#define TH3_ATTACK_GRENADE 0x18 //?
#define TH3_ATTACK_HANDGUN 0x15

void Enemy_Think_800CE99C( WatcherWork * work );
void s00a_command_800CA69C( SVECTOR *svec );
void s00a_command_800CA7DC( SVECTOR *svec );
void s00a_command_800CA618( SVECTOR *svec );
void s00a_command_800CB13C( WatcherWork * work );
void s00a_command_800CC210( WatcherWork * work );
void s00a_command_800CEB54();

int  DirectTrace_800CC154( WatcherWork *work, int val );
