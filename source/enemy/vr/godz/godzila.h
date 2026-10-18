#ifndef __MGS_ENEMY_VR_GODZILA_H__
#define __MGS_ENEMY_VR_GODZILA_H__

#include "enemy/enemy.h"

// motion archive of the godzilla soldier (instead of OAR_ENEMY)
#define OAR_GODZ 0x2652

// Godz = "Godzila", the soldier of the VR godzilla mission (vcd_n05). It is the s10a
// zako10 guard (a stripped down zako11e: no z parameter, no optical camouflage, no
// 'o' option) with four more hit boxes: the layout is the zako10 one with 4 TARGET
// pointers (parts[]) inserted behind "target", so everything after is shifted by 0x10.
typedef struct _GodzWork
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
    TARGET        *targets[5];                 //0x900 main target + 4 body part hit boxes (objs 1, 6, 11, 14)
    TARGET         field_914;                  //0x914
    TARGET         field_95C;                  //0x95C
    TARGET         punch;                      //0x9A4
    HOMING        *hom;                        //0x9EC
    int            scale;                      //0x9F0
    int            visible;                    //0x9F4
    int            n_nodes;                    //0x9F8
    SVECTOR        nodes[32];                  //0x9FC
    int            search_flag;                //0xAFC
    GV_ACT        *shadow;                     //0xB00
    int           *shadow_enable;              //0xB04
    GV_ACT        *glight;                     //0xB08
    int           *glight_enable;              //0xB0C
    void          *field_B10[8];               //0xB10
    short          think1;                     //0xB30
    short          think2;                     //0xB32
    short          think3;                     //0xB34
    short          think4;                     //0xB36
    unsigned int   count3;                     //0xB38
    int            t_count;                    //0xB3C
    int            l_count;                    //0xB40
    int            next_node;                  //0xB44
    WatcherPad     pad;                        //0xB48
    short          field_B5C;                  //0xB5C
    short          field_B5E;                  //0xB5E
    u_long         trigger;                    //0xB60
    GV_ACT        *subweapon;                  //0xB64
    short          field_B68;                  //0xB68
    short          field_B6A;                  //0xB6A
    short          field_B6C;                  //0xB6C
    short          field_B6E;                  //0xB6E
    GV_ACT        *mark;                       //0xB70
    GV_ACT        *field_B74;                  //0xB74
    int            mark_time;                  //0xB78
    int            act_status;                 //0xB7C
    int            field_B80;                  //0xB80
    PARAM          param;                      //0xB84
    short          local_data;                 //0xB92
    int            field_B94;                  //0xB94
    VISION         vision;                     //0xB98
    short          field_BA0;                  //0xBA0
    short          field_BA2;                  //0xBA2
    int            alert_level;                //0xBA4
    signed char    modetime[8];                //0xBA8
    SVECTOR        field_BB0;                  //0xBB0
    int            field_BB8;                  //0xBB8
    int            field_BBC[8];               //0xBBC set_time
    short          field_BDC[4];               //0xBDC set_dir
    SVECTOR        start_pos;                  //0xBE4
    SVECTOR        target_pos;                 //0xBEC
    int            start_addr;                 //0xBF4
    int            start_map;                  //0xBF8
    int            field_BFC;                  //0xBFC
    int            target_addr;                //0xC00
    int            target_map;                 //0xC04
    int            field_C08;                  //0xC08
    int            field_C0C;                  //0xC0C
    SVECTOR        field_C10;                  //0xC10
    int            field_C18;                  //0xC18
    int            field_C1C;                  //0xC1C
    int            field_C20;                  //0xC20
    int            field_C24;                  //0xC24
    SVECTOR        field_C28;                  //0xC28
    int            field_C30;                  //0xC30
    int            field_C34;                  //0xC34
    int            sn_dis;                     //0xC38
    int            sn_dir;                     //0xC4C
    int            faseout;                    //0xC40
    int            field_C44;                  //0xC44
    char           field_C48;                  //0xC48 num_set_time
    char           field_C49[3];               //0xC49
    int            field_C4C;                  //0xC4C GCL option 'e'
} GodzWork;                                  //0xC50

// zk10com.c: like ZAKO_COMMAND with the commander's name in front
typedef struct _GODZ_COMMAND
{
    int       name;         //0x00
    int       n_proc_c;     //0x04 number of procs run by the 'c' option
    int       n_proc_s;     //0x08 number of procs run by the 's' option
    int       n_watchers;   //0x0C
    int       counter;      //0x10 incremented every frame
    int       timer;        //0x14
    int       evasion_time; //0x18
    int       alert;        //0x1C
    int       mode;         //0x20
    int       c_root;       //0x24
    int       com_addr;     //0x28
    int       com_map;      //0x2C
    SVECTOR   com_pos;      //0x30
    short     n_zones;      //0x38
    short     reset_zone;   //0x3A
    short     zones[4];     //0x3C
    int       order[8];     //0x44 watcher indices sorted by distance to snake
    int       n_reset;      //0x64
    MAP      *map;          //0x68
    A4_STRUCT field_6C;     //0x6C
    WATCHER   watchers[8];  //0x90
    int       field_110;    //0x110
    int       field_114;    //0x114
    int       field_118;    //0x118
    int       voice;        //0x11C
} GODZ_COMMAND;

// FIXME: the action and think files of the godzilla soldier are not decompiled yet. The functions that the
// decompiled files use are referenced by their address based symbols of the vcd_n05 overlay.
#define GodzThink            vcd_n05_800CBF4C
#define GodzActionUpdate     vcd_n05_800C73B0

typedef void ( *GODZACTION )( GodzWork *, int );
typedef void ( *GODZPUTFUNC )( GodzWork * );

static inline void SetGodzMode( GodzWork *work, GODZACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust( &( work->body ), 0 );
}

static inline void SetGodzModeFields( GodzWork *work, GODZACTION action )
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetGodzMode2( GodzWork *work, GODZACTION action )
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

#endif // __MGS_ENEMY_VR_GODZILA_H__
