

#include "common.h"
#include "Game/homing.h"
#include "Game/game.h"
#include "Game/object.h"

#include "Game/linkvarbuf.h"
#include "Weapon/weapon.h"
#include "Game/vibrate.h"

typedef struct _PARAM
{
    char        fAF8;
    char        fAF9;
    char        fAFA;
    signed char c_root;
    char        defends[4];
    signed char roots[4];
    short       life;
    short       max_life;
} PARAM;

typedef struct UNK
{
    int   field_00;    //0x00        //0x8BC
    short field_04;    //0x04        //0x8C0
    short field_06;    //0x06        //0x8C2
    int   field_08;    //0x08        //0x8C4
    int   field_0C;    //0x0C        //0x8C8
    int   field_10;    //0x10        //0x8CC
    int   field_14;    //0x14        //0x8D0
    short field_18;    //0x18        //0x8D4
    short field_1A;    //0x1A        //0x8D6
    short field_1C;    //0x1C        //0x8D8
    short field_1E;    //0x1E        //0x8DA
} UNK;

typedef struct _Meryl72Pad
{
    int   press;           //0x04       //0xACC
    int   mode;            //0x08       //0xAD0
    int   tmp;             //0x0A       //0xAD4
    short time;            //0x0C       //0xAD8
    short dir;             //0x10       //0xADA
    short sound;           //0x12       //0xADC
    short field_14;        //0x14       //0xADE
} Meryl72Pad;


typedef struct _VISION
{
    short          facedir;                //0xB10
    short          angle;                  //0xB12
    short          length;                 //0xB14
    short          field_06;              //0xB16
} VISION;

typedef struct Meryl72Work
{
    GV_ACT         actor;
    CONTROL        control; //0x20
    OBJECT         body;    //0x9C
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[17];
    MOTION_SEGMENT m_segs2[17];
    SVECTOR        rots[32];
    OBJECT         weapon;
    MATRIX         light[2];
    UNK            f8BC;
    void*          action; //8DC
    void*          action2; //8E0
    int            time; //8E4
    int            time2; //8E8
    char           pad24[0x4];
    TARGET        *target;
    TARGET         target2;
    TARGET         punch;
    HOMING        *homing;
    int            n_patrols;
    SVECTOR        nodes[1]; //98C
    char           pad20[0x10];
    SVECTOR        f9A4;
    char           pad18[0xE0];
    GV_ACT        *shadow;
    int           *enable_shadow;
    char           pad23[0x28];
    short          fABC;
    short          fABE;
    short          fAC0;
    short          fAC2;
    int            fAC4;
    int            fAC8;
    Meryl72Pad     pad; //0xACC
    unsigned int   trigger; //0xAE0
    GV_ACT*        subweapon; //0xAE4
    short          fAE8;
    short          fAEA;
    short          fAEC;
    short          fAEE;
    int            fAF0;
    int            fAF4;
    PARAM          param;
    short          fB08;
    char           fB0A;
    char           fB0B;
    char           pad7[0x4];
    VISION         vision;
    int            fB18;
    signed char    modetime[8];   //B1C
    int            act_status;
    SVECTOR        fB28;
    char           pad19[0x4];
    SVECTOR        start_pos; //B34
    SVECTOR        target_pos; //B3C
    int            start_addr; //B44
    int            start_map; //B48
    int            fB4C;
    int            target_addr; //B50
    int            target_map; //B54
    int            fB58;
    char           pad10[0x4];
    int            fB60;
    char           pad11[0x8];
    SVECTOR        fB6C;
    int            field_B74;
    int            field_B78;
    int            sn_dis;
    int            sn_dir;
    int            fB84;
    SVECTOR        fB88;
    int            fB90;
    short          fB94;
    short          fB96;
    int            fB98;
    char           pad12[0x4];
    int            voices[25];
    int            fC04;
    short          fC08;
    short          fC0A;
    short          fC0C;
    short          fC0E;
    int            fC10;
    int            fC14;
    int            fC18;
    int            fC1C[6];
    short          fC34;
    short          fC36;
    char           pad15[0x4];
    int            fC3C;
    int            proc_id;
} Meryl72Work;

typedef void    ( *ACTION )( Meryl72Work *, int ) ;
/*
static inline void SetModeFields( Meryl72Work *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
*/
static inline void SetMode( Meryl72Work *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    //GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

static inline void SetMode2( Meryl72Work *work, void *func )
{
    if ( work->action2 == NULL )
    {
        work->action2 = func;
        work->time2 = 0;
    }

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), 0 );
}

//action.c
#define COM_ST_DANBOWL 0x2000
#define SP_DANBOWLKERI 0x400000

#define GUNSHOOT 3

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
#define ACTION19    19
#define ACTION20    20
#define ACTION21    21
#define ACTION22    22
#define ACTION23    23
#define ACTION24    24
#define ACTION25    25
#define ACTION26    26
#define ACTION27    27
#define ACTION28    28
#define ACTION29    29
#define ACTION30    30
#define ACTION31    31
#define ACTION32    32
#define ACTION33    33
#define ACTION34    34
#define ACTION35    35
#define ACTION36    36
#define ACTION37    37
#define ACTION38    38
#define ACTION39    39
#define ACTION40    40
#define ACTION41    41
#define ACTION42    42
#define ACTION43    43
#define ACTION44    44
#define ACTION45    45
#define ACTION46    46
#define ACTION47    47
#define ACTION48    48
#define ACTION49    49
#define ACTION50    50
#define ACTION51    51
#define ACTION52    52
#define ACTION53    53
#define ACTION54    54
#define ACTION55    55
#define ACTION56    56
#define ACTION57    57
#define ACTION58    58

//check funcs
int CheckPad_800C8308( Meryl72Work *work ) ;
int CheckDamage_800C7F6C(Meryl72Work* work ) ;
void ReviseReadyGun_800C8020( Meryl72Work* work ) ;
int s07c_meryl72_unk1_800C829C( Meryl72Work* work ) ;
int s07c_meryl72_unk1_800C7FCC( int dir, int dist ) ;
void ExecProc_800C7C58( Meryl72Work *work, int mode ) ;
int AttackForce_800C80DC( Meryl72Work * work, int check ) ;
//action funcs
extern void s07c_meryl72_unk1_800CAD30( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CADEC( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CAEA8( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CAF30( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CAFB8( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CB038( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CB0B8( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CB134( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800CB1B4( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C88EC( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C8970( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C8A30( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C8BC4( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C8E74( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C8C7C( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9000( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C90C8( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9318( Meryl72Work *work, int time ) ;
extern void ActReadyGun_800C9428( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9258( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9190( Meryl72Work *work, int time ) ;
extern void s07c_meryl72_unk1_800C9594( Meryl72Work* work, int time ) ;
extern void s07c_meryl72_unk1_800C964C( Meryl72Work* work, int time ) ;
extern void ActGrenade_800C9790( Meryl72Work* work, int time ) ;
extern void s07c_meryl72_unk1_800CA0EC( Meryl72Work* work, int time ) ;
extern void s07c_meryl72_unk1_800CA538( Meryl72Work* work, int time ) ;
extern void s07c_meryl72_unk1_800CAA48( Meryl72Work* work, int time ) ;

//put funcs
extern void s07c_meryl72_unk1_800CB584( Meryl72Work* work, int time ) ; //PutChar
extern void s07c_meryl72_unk1_800CB2EC( Meryl72Work*, int, int ) ; //PutBlood

