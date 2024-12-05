

#include "common.h"
#include "Game/homing.h"
#include "Game/game.h"

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
    char           pad2[0x48];
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
    char           pad5[0x4];
    int            fAE4;
    char           pad13[0xC];
    int            fAF4;
    PARAM          param;
    short          fB08;
    char           fB0A;
    char           fB0B;
    char           pad7[0x4];
    short          fB10;
    short          fB12;
    short          fB14;
    char           pad8[0x2];
    int            fB18;
    signed char    modetime[8];   //B1C
    char           pad9[0x4];
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
    char           pad17[0x2];
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

static inline void SetModeFields( Meryl72Work *work, ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}
