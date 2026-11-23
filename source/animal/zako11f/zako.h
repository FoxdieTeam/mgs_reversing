#ifndef __MGS_ANIMAL_ZAKO11F_ZAKO_H__
#define __MGS_ANIMAL_ZAKO11F_ZAKO_H__

#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define TARGET_FLAG     ( TARGET_AVAIL | TARGET_CAPTURE | TARGET_POWER \
                        | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

#define ACTINTERP       4

#define SP_WEAPON       0x10000
#define SP_WEAPON2      0x20000
#define SP_DANBOWLKERI  0x400000

#define ACTINTERP       4

#define STANDSTILL      0
#define GRENADE         7

#define TOP_COMM_TRAVEL 0
#define TOP_COMM_ALERT  1

#define PUTBREATH       1
#define GUNSHOOT        3

/*---------------------------------------------------------------------------*/

// TODO: check name
typedef struct _ACT {
    /* 0x8C8 */ int     field_00;
    /* 0x8CC */ short   field_04;
    /* 0x8CE */ short   field_06;
    /* 0x8D0 */ int     field_08;
    /* 0x8D4 */ SVECTOR field_0C;
    /* 0x8DC */ int     field_14;
    /* 0x8E0 */ short   motion1;
    /* 0x8E2 */ short   motion2;
    /* 0x8E4 */ short   field_1C;
    /* 0x8E6 */ short   field_1E;
    /* 0x8E8 */ short   field_20;
    /* 0x8EA */ short   field_22;
} ACT;

typedef struct _PARAM {
    /* 0xB74 */ signed char index;
    /* 0xB75 */ signed char blood;
    /* 0xB76 */ signed char area;
    /* 0xB77 */ signed char low_poly;
    /* 0xB78 */ char        next;
    /* 0xB79 */ signed char root;
    /* 0xB7A */ char        c_root;
    /* 0xB7B */ char        c_next;
    /* 0xB7C */ signed char item;
    /* 0xB7D */ char        reset;
    /* 0xB7E */ short       life;
    /* 0xB80 */ short       faint;
    /* 0xB82 */ short       life_prev;
    /* 0xB84 */ short       damage;
    /* 0xB86 */ short       damage2;
} PARAM;

typedef struct _VISION {
    /* 0xB88 */ short facedir;
    /* 0xB8A */ short range;
    /* 0xB8C */ short length;
    /* 0xB8E */ short pad;
} VISION;

typedef struct _PAD {
    /* 0xB38 */ int   press;
    /* 0xB3C */ int   mode;
    /* 0xB40 */ int   tmp;
    /* 0xB44 */ int   time;
    /* 0xB48 */ short dir;
    /* 0xB4A */ short sound;
} PAD;

struct _Work;

typedef void ( *ACTION )( struct _Work *, int ) ;
typedef void ( *PUTFUNC )( struct _Work * ) ;

typedef struct _Work {
    /* 0x000 */ GV_ACT         actor;
    /* 0x020 */ CONTROL        control;
    /* 0x09C */ OBJECT         body;
    /* 0x180 */ int            lod;
    /* 0x184 */ DG_DEF        *lod_models[ 2 ];
    /* 0x18C */ MOTION_CONTROL m_ctrl;
    /* 0x1DC */ MOTION_SEGMENT m_segs1[ 17 ];
    /* 0x440 */ MOTION_SEGMENT m_segs2[ 17 ];
    /* 0x6A4 */ SVECTOR        rots[ 16 ];
    /* 0x724 */ SVECTOR        adjust[ 16 ];
    /* 0x7A4 */ OBJECT         weapon;
    /* 0x888 */ MATRIX         light[ 2 ];
    /* 0x8C8 */ ACT            act;
    /* 0x8EC */ ACTION         action;
    /* 0x8F0 */ ACTION         action2;
    /* 0x8F4 */ int            time;
    /* 0x8F8 */ int            time2;
    /* 0x8FC */ int            actend;
    /* 0x900 */ TARGET        *target;
    /* 0x904 */ TARGET         attack;
    /* 0x94C */ TARGET         touch;
    /* 0x994 */ TARGET         punch;
    /* 0x9DC */ HOMING        *hom;
    /* 0x9E0 */ int            scale;
    /* 0x9E4 */ int            visible;
    /* 0x9E8 */ int            n_nodes;
    /* 0x9EC */ SVECTOR        nodes[ 32 ];
    /* 0xAEC */ int            search_flag;
    /* 0xAF0 */ void          *shadow;
    /* 0xAF4 */ int           *shadow_enable;
    /* 0xAF8 */ void          *glight;
    /* 0xAFC */ int           *glight_enable;
    /* 0xB00 */ PUTFUNC        putchar[ 8 ];
    /* 0xB20 */ short          think1;
    /* 0xB22 */ short          think2;
    /* 0xB24 */ short          think3;
    /* 0xB26 */ short          think4;
    /* 0xB28 */ u_int          count3;
    /* 0xB2C */ int            t_count;
    /* 0xB30 */ int            l_count;
    /* 0xB34 */ int            next_node;
    /* 0xB38 */ PAD            pad;
    /* 0xB4C */ char           padB4C[ 0x4 ];
    /* 0xB50 */ u_long         trigger;
    /* 0xB54 */ void          *subweapon;
    /* 0xB58 */ short          field_B58;
    /* 0xB5A */ short          field_B5A;
    /* 0xB5C */ short          field_B5C;
    /* 0xB60 */ void          *mark;
    /* 0xB64 */ char           padB64[ 0x4 ];
    /* 0xB68 */ int            mark_time;
    /* 0xB6C */ int            act_status;
    /* 0xB70 */ char           padB70[ 0x4 ];
    /* 0xB74 */ PARAM          param;
    /* 0xB88 */ char           padB88[ 0x4 ];
    /* 0xB8C */ VISION         vision;
    /* 0xB94 */ short          field_B94;
    /* 0xB98 */ int            alert_level;
    /* 0xB9C */ signed char    modetime[ 8 ];
    /* 0xBA4 */ SVECTOR        player_pos;
    /* 0xBAC */ int            player_dir;
    /* 0xBB0 */ int            set_time[ 8 ];
    /* 0xBD0 */ short          set_dir[ 4 ];
    /* 0xBD8 */ SVECTOR        start_pos;
    /* 0xBE0 */ SVECTOR        target_pos;
    /* 0xBE8 */ int            start_addr;
    /* 0xBEC */ int            start_map;
    /* 0xBF0 */ int            last_addr;
    /* 0xBF4 */ int            target_addr;
    /* 0xBF8 */ int            target_map;
    /* 0xBFC */ int            chase_dis;
    /* 0xC00 */ int            chase_index;
    /* 0xC04 */ SVECTOR        field_C04;
    /* 0xC0C */ int            current_addr;
    /* 0xC10 */ int            next_addr;
    /* 0xC14 */ char           padC14[ 0x8 ];
    /* 0xC1C */ SVECTOR        next_pos;
    /* 0xC24 */ char           padC24[ 0x8 ];
    /* 0xC2C */ int            sn_dis;
    /* 0xC30 */ int            sn_dir;
    /* 0xC34 */ int            faseout;
    /* 0xC38 */ int            field_C38;
    /* 0xC3C */ int            gameflag;
    /* 0xC40 */ short          field_C40;
    /* 0xC42 */ short          field_C42;
} Work;

typedef struct _JOINT {
    u_short map;
    u_short zone;
} JOINT;

typedef struct _JOINT_DATA {
    u_short map;
    u_short n_joints;
    JOINT   joints[ 8 ];
} JOINT_DATA;

// TODO: check name
typedef struct _WATCHER {
    int   field_0;
    int   field_4;
    int   field_8;
    Work *work;
} WATCHER;

typedef struct _COMMANDER {
    /* 0x000 */ int        field_0;
    /* 0x004 */ int        field_4;
    /* 0x008 */ int        n_watchers;
    /* 0x00C */ int        time;
    /* 0x010 */ int        time2;
    /* 0x014 */ int        alert_time;
    /* 0x018 */ int        alert_level;
    /* 0x01C */ int        alert_mode;
    /* 0x020 */ int        field_20;
    /* 0x024 */ int        target_addr;
    /* 0x028 */ int        target_map;
    /* 0x02C */ SVECTOR    target_pos;
    /* 0x034 */ short      n_zones;
    /* 0x036 */ short      c_reset_pos;
    /* 0x038 */ short      zones[ 4 ];
    /* 0x040 */ int        field_40[ 8 ];
    /* 0x060 */ int        field_60;
    /* 0x064 */ MAP       *map;
    /* 0x068 */ JOINT_DATA joint_data;
    /* 0x08C */ WATCHER    watchers[ 8 ];
    /* 0x10C */ int        field_10C;
    /* 0x110 */ short      field_110;
    /* 0x112 */ short      field_112;
    /* 0x114 */ short      field_114;
    /* 0x116 */ short      firstdamage;
    /* 0x118 */ SVECTOR    field_118;
    /* 0x120 */ int        end_proc;
    /* 0x124 */ int        proc[ 8 ];
    /* 0x144 */ int        field_144;
} COMMANDER;

// TODO: check name
typedef struct _TOP {
    int mode;
    int alert;
} TOP;

typedef struct _CommanderWork {
    /* 0x000 */ GV_ACT actor;
    /* 0x000 */ int    name;
    /* 0x020 */ char   pad24[ 0x4 ];
} CommanderWork;

typedef struct _PATTERN {
    short field_0;
    short set;
    short field_4;
    short reset;
} PATTERN;

/*---------------------------------------------------------------------------*/

static inline void SetAction( Work *work, int action, int interp )
{
    extern short ActionTable[];

    work->act.motion1 = action;
    GM_ConfigObjectAction( &( work->body ), ActionTable[ action ], 0, interp );
}

static inline void SetAction2( Work *work, int action, int interp, u_long mask )
{
    extern short ActionTable[];

    work->act.motion2 = action;
    GM_ConfigObjectOverride( &( work->body ), ActionTable[ action ], 0, interp, mask );
}

static inline void SetMode( Work *work, ACTION action )
{
    work->action = action;
    work->time = 0;

    work->control.turn.vx = work->control.turn.vz = 0;
    GM_ConfigMotionAdjust( &( work->body ), NULL );
}

static inline void SetMode2( Work *work, ACTION action )
{
    if ( work->action2 == NULL )
    {
        work->action2 = action;
        work->time2 = 0;
    }

    work->control.turn.vx = work->control.turn.vz = 0;
    GM_ConfigMotionAdjust( &( work->body ), NULL );
}

static inline void SetModeNoAdjust( Work *work, ACTION action )
{
    work->action = action;
    work->time = 0;

    work->control.turn.vx = work->control.turn.vz = 0;
}

static inline void UnsetMode( Work *work )
{
    SetAction2( work, 0, 4, 0 );
    work->action2 = NULL;
    work->time2 = 0;
    work->act.motion2 = 0;
    work->control.turn.vx = work->control.turn.vz = 0;
}

/*---------------------------------------------------------------------------*/

#ifndef __ANIMAL_ZAKO11F_ZAKOCOM_C__
extern SVECTOR   ZAKO11F_TARGET_SIZE;
extern SVECTOR   ZAKO11F_TARGET_FORCE;
extern SVECTOR   ZAKO11F_ATTACK_SIZE;
extern SVECTOR   ZAKO11F_ATTACK_FORCE;
extern SVECTOR   ZAKO11F_TOUCH_SIZE;
extern SVECTOR   ZAKO11F_TOUCH_FORCE;
extern SVECTOR   ZAKO11F_NO_POINT;
extern int       ZAKO11F_EYE_LENGTH;
extern SVECTOR   ZAKO11F_PlayerPosition;
extern COMMANDER ZAKO11FCommand;
extern TOP       ZAKO11FTOPCOMMAND;
extern int       ZAKO11F_GameFlag;
extern int       ZAKO11F_GameStatus;
extern int       ZAKO11F_PlayerAddress;
extern int       ZAKO11F_PlayerMap;
#endif // __ANIMAL_ZAKO11F_ZAKOCOM_C__

// zako11f.c
void *NewZako11F( int name, int where, int argc, char **argv );

// action.c
void s11i_asiato_800CAD34( Work *work, int time );
void ZAKO11F_ActionUpdate( Work *work );

// override.c
void s11i_asiato_800CC528( Work *work, int time );
void s11i_asiato_800CC5F4( Work *work, int time );
void ActOverScoutD_800CC6C0( Work *work, int time );
void s11i_asiato_800CC758( Work *work, int time );
void s11i_asiato_800CC7F0( Work *work, int time );
void s11i_asiato_800CC8A4( Work *work, int time );
void s11i_asiato_800CC96C( Work *work, int time );
void s11i_asiato_800CCA10( Work *work, int time );
void s11i_asiato_800CCAD8( Work *work, int time );
void s11i_asiato_800CCCF0( Work *work, int time );
void s11i_asiato_800CCE38( Work *work, int time );

// put.c
void ZAKO11F_PutBlood( Work *work, int unit, int count );
void ZAKO11F_PutFog( Work *work );
void ZAKO11F_PutItem( Work *work );
void ZAKO11F_PutMark( Work *work, int mark );
int  ZAKO11F_SetPutChar( Work *work, int index );
int  ZAKO11F_ClearPutChar( Work *work, void *func );
void ZAKO11F_ExecPutChars( Work *work );

// zk11fact.c
void Zako11FActionMain( Work *work );
void Zako11FPushMove( Work *work );

// think.c
void Zako11FThink( Work *work );

// zk11fcom.c
int  ZAKO11FSetWorkID( Work *work );
void ZAKO11FResetWorkID( int id );
void ZAKO11FSetTopCommAL( int alert );
void ZAKO11FSetTopCommMD( int mode );
void ZAKO11FSetGopointLast( void );
void ZAKO11FSetGopointNoise( void );
int  ZAKO11FGetMapJointZone( int map, int id );
int  s11i_zk11fcom_800D0DA8( void );
void s11i_zk11fcom_800D0DB8( void );
void ZAKO11FSetFirstDamage( void );

#endif // __MGS_ANIMAL_ZAKO11F_ZAKO_H__
