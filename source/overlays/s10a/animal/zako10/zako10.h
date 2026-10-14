#ifndef __MGS_S10A_ZAKO10_H__
#define __MGS_S10A_ZAKO10_H__

#include "enemy/enemy.h"

// Zako10 (the guards of s10a) is a stripped down zako11e: no z parameter,
// no optical camouflage and no 'o' option. Up to 0xB84 the layout is the
// same as ZakoWork, after that everything is shifted by -4.
typedef struct _Zako10Work
{
    GV_ACT         actor;
    CONTROL        control;                    //0x20
    OBJECT         body;                       //0x9C
    int            has_kmd;                    //0x180
    DG_DEF        *kmd;                        //0x184
    DG_DEF        *def;                        //0x188
    MOTION_CONTROL m_ctrl;                     //0x18C
    MOTION_SEGMENT m_segs1[17];                //0x1DC
    MOTION_SEGMENT m_segs2[17];                //0x440
    SVECTOR        rots[16];                   //0x6A4
    SVECTOR        adjust[16];                 //0x724
    OBJECT         weapon;                     //0x7A4
    MATRIX         light[2];                   //0x888
    WatcherUnk     unknown;                    //0x8C8
    void          *action;                     //0x8EC
    void          *action2;                    //0x8F0
    int            time;                       //0x8F4
    int            time2;                      //0x8F8
    int            actend;                     //0x8FC
    TARGET        *target;                     //0x900
    TARGET         field_904;                  //0x904
    TARGET         field_94C;                  //0x94C
    TARGET         punch;                      //0x994
    HOMING        *hom;                        //0x9DC
    int            scale;                      //0x9E0
    int            visible;                    //0x9E4
    int            n_nodes;                    //0x9E8
    SVECTOR        nodes[32];                  //0x9EC
    int            search_flag;                //0xAEC
    GV_ACT        *shadow;                     //0xAF0
    int           *shadow_enable;              //0xAF4
    GV_ACT        *glight;                     //0xAF8
    int           *glight_enable;              //0xAFC
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
    u_long         trigger;                    //0xB50
    GV_ACT        *subweapon;                  //0xB54
    short          field_B58;                  //0xB58
    short          field_B5A;                  //0xB5A
    short          field_B5C;                  //0xB5C
    short          field_B5E;                  //0xB5E
    GV_ACT        *mark;                       //0xB60
    GV_ACT        *field_B64;                  //0xB64
    int            mark_time;                  //0xB68
    int            act_status;                 //0xB6C
    int            field_B70;                  //0xB70
    signed char    field_B74;                  //0xB74 param.index
    signed char    param_blood;                //0xB75
    signed char    param_area;                 //0xB76
    signed char    param_low_poly;             //0xB77
    char           field_B78;                  //0xB78
    signed char    param_root;                 //0xB79
    char           param_c_root;               //0xB7A
    char           field_B7B;                  //0xB7B
    signed char    param_item;                 //0xB7C
    char           field_B7D;                  //0xB7D
    short          param_life;                 //0xB7E
    short          param_faint;                //0xB80
    short          local_data;                 //0xB82
    int            field_B84;                  //0xB84
    VISION         vision;                     //0xB88
    short          field_B90;                  //0xB90
    short          field_B92;                  //0xB92
    int            alert_level;                //0xB94
    signed char    modetime[8];                //0xB98
    SVECTOR        field_BA0;                  //0xBA0
    int            field_BA8;                  //0xBA8
    int            field_BAC[8];               //0xBAC set_time
    short          field_BCC[4];               //0xBCC set_dir
    SVECTOR        start_pos;                  //0xBD4
    SVECTOR        target_pos;                 //0xBDC
    int            start_addr;                 //0xBE4
    int            start_map;                  //0xBE8
    int            field_BEC;                  //0xBEC
    int            target_addr;                //0xBF0
    int            target_map;                 //0xBF4
    int            field_BF8;                  //0xBF8
    int            field_BFC;                  //0xBFC
    SVECTOR        field_C00;                  //0xC00
    int            field_C08;                  //0xC08
    int            field_C0C;                  //0xC0C
    int            field_C10;                  //0xC10
    int            field_C14;                  //0xC14
    SVECTOR        field_C18;                  //0xC18
    int            field_C20;                  //0xC20
    int            field_C24;                  //0xC24
    int            sn_dis;                     //0xC28
    int            sn_dir;                     //0xC2C
    int            faseout;                    //0xC30
    int            field_C34;                  //0xC34
    char           field_C38;                  //0xC38 num_set_time
    char           field_C39[3];               //0xC39
} Zako10Work;                                  //0xC3C

// zk10com.c: like ZAKO_COMMAND with an extra word in front
typedef struct _ZAKO10_COMMAND
{
    int       field_00;     //0x00
    int       field_04;     //0x04
    int       field_08;     //0x08
    int       n_watchers;   //0x0C
    int       counter;      //0x10 incremented every frame
    int       timer;        //0x14
    int       field_18;     //0x18
    int       alert;        //0x1C
    int       mode;         //0x20
    int       field_24;     //0x24
    int       com_addr;     //0x28
    int       com_map;      //0x2C
    SVECTOR   com_pos;      //0x30
    short     n_zones;      //0x38
    short     reset_zone;   //0x3A
    short     zones[4];     //0x3C
    int       field_44[8];  //0x44
    int       field_64;     //0x64
    MAP      *map;          //0x68
    A4_STRUCT field_6C;     //0x6C
    WATCHER   watchers[8];  //0x90
    int       field_110;    //0x110
    int       field_114;    //0x114
    int       voice;        //0x118
    int       proc;         //0x11C
    int       field_120;    //0x120
    int       field_124;    //0x124
} ZAKO10_COMMAND;

typedef void ( *ZAKO10ACTION )( Zako10Work *, int );
typedef void ( *ZAKO10PUTFUNC )( Zako10Work * );

static inline void SetZako10Mode( Zako10Work *work, ZAKO10ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust( &( work->body ), 0 );
}

static inline void SetZako10ModeFields( Zako10Work *work, ZAKO10ACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetZako10Mode2( Zako10Work *work, ZAKO10ACTION action )
{
    if ( work->action2 == NULL )
    {
        work->action2 = action;
        work->time2 = 0;
    }

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust( &( work->body ), 0 );
}

#endif // __MGS_S10A_ZAKO10_H__
