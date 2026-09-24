#ifndef __MGS_ANIMAL_ZAKO14_ZAKO_H__
#define __MGS_ANIMAL_ZAKO14_ZAKO_H__

#include "game/game.h"

#define TARGET_FLAG ( TARGET_AVAIL | TARGET_CAPTURE | TARGET_POWER \
                    | TARGET_PUSH | TARGET_SEEK | TARGET_TOUCH )

// TODO: These structures should be unified with the other zakos, using stage
//       ifdefs to add or remove fields where necessary.

// TODO: check name
typedef struct _ACT {
    /* 0x8C8 */ int            field_00;
    /* 0x8CC */ short          field_04;
    /* 0x8CE */ short          field_06;
    /* 0x8D0 */ int            field_08;
    /* 0x8D4 */ SVECTOR        field_0C;
    /* 0x8DC */ int            field_14;
    /* 0x8E0 */ short          motion1;
    /* 0x8E2 */ short          motion2;
    /* 0x8E4 */ short          field_1C;
    /* 0x8E6 */ short          field_1E;
    /* 0x8E8 */ short          field_20;
    /* 0x8EA */ short          field_22;
} ACT;

typedef struct _PARAM {
    /* 0xB74 */ signed char    index;
    /* 0xB75 */ signed char    blood;
    /* 0xB76 */ signed char    area;
    /* 0xB77 */ signed char    low_poly;
    /* 0xB78 */ char           next;
    /* 0xB79 */ signed char    root;
    /* 0xB7A */ char           c_root;
    /* 0xB7B */ char           c_next;
    /* 0xB7C */ signed char    item;
    /* 0xB7D */ char           g_flag;
    /* 0xB7E */ short          life;
    /* 0xB80 */ short          faint;
    /* 0xB82 */ short          damage;
} PARAM;

typedef struct _VISION {
    /* 0xB88 */ short facedir;
    /* 0xB8A */ short range;
    /* 0xB8C */ short length;
    /* 0xB8E */ short pad;
} VISION;

typedef struct _PAD {
    /* 0xB38 */ int   press;
    /* 0xB3C */ int   field_4;
    /* 0xB40 */ int   field_8;
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
    /* 0x8FC */ int            field_8FC;
    /* 0x900 */ TARGET        *target;
    /* 0x904 */ TARGET         attack;
    /* 0x94C */ TARGET         touch;
    /* 0x994 */ TARGET         punch;
    /* 0x9DC */ HOMING        *hom;
    /* 0x9E0 */ int            scale;
    /* 0x9E4 */ int            field_9E4;
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
    /* 0xB28 */ int            count3;
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
    /* 0xB5E */ char           padB5E[ 0x2 ];
    /* 0xB60 */ void          *mark;
    /* 0xB64 */ char           padB64[ 0x4 ];
    /* 0xB68 */ int            mark_time;
    /* 0xB6C */ int            act_status;
    /* 0xB70 */ char           padB70[ 0x4 ];
    /* 0xB74 */ PARAM          param;
    /* 0xB84 */ char           padB84[ 0x4 ];
    /* 0xB88 */ VISION         vision;
    /* 0xB90 */ short          field_B90;

    /* 0xB94 */ int            newpad;

    /* 0xB94 */ int            alert_level;
    /* 0xB98 */ signed char    modetime[ 8 ];
    /* 0xBA0 */ SVECTOR        player_pos;
    /* 0xBA8 */ int            player_dir;
    /* 0xBAC */ int            acttime[ 8 ];
    /* 0xBCC */ short          dir[ 4 ];
    /* 0xBD4 */ int            field_BD4;
    /* 0xBD8 */ SVECTOR        start_pos;
    /* 0xBE0 */ SVECTOR        target_pos;
    // /* 0xBE8 */ int            field_BE8;
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
    /* 0xC34 */ int            field_C34;
    /* 0xC38 */ int            field_C38;
    /* 0xC3C */ int            field_C3C;
    /* 0xC40 */ int            gameflag;
    /* 0xC44 */ short          field_C44;
} Work;

typedef struct _JDATA {
    u_short map;
    u_short count;
    u_short data[ 8 ][ 2 ];
} JDATA;

// TODO: check name
typedef struct _WATCHER {
    int  field_0;
    int  field_4;
    int  field_8;
    Work *work;
} WATCHER;

typedef struct _COMMANDER {
    /* 0x000 */ int     field_0;
    /* 0x004 */ int     field_4;
    /* 0x008 */ int     n_watchers;
    /* 0x00C */ int     time;
    /* 0x010 */ int     time2;
    /* 0x014 */ int     alert_time;
    /* 0x018 */ int     alert_level;
    /* 0x01C */ int     alert_mode;
    /* 0x020 */ int     field_20;
    /* 0x024 */ int     target_addr;
    /* 0x028 */ int     target_map;
    /* 0x02C */ SVECTOR target_pos;
    /* 0x034 */ short   n_zones;
    /* 0x036 */ short   far_zone;
    /* 0x038 */ short   zones[ 4 ];
    /* 0x040 */ int     prio[ 8 ];
    /* 0x060 */ int     field_60;
    /* 0x064 */ MAP    *map;
    /* 0x068 */ JDATA   jdata;
    /* 0x08C */ WATCHER watchers[ 8 ];
    /* 0x10C */ int     field_10C;
    /* 0x110 */ int     field_110;
    /* 0x114 */ int     end_proc;
} COMMANDER;

// TODO: check name
typedef struct _TOP {
    int mode;
    int alert;
} TOP;

typedef struct _CommanderWork {
    /* 0x000 */ GV_ACT actor;
    /* 0x020 */ char   pad20[ 0x4 ];
} CommanderWork;

typedef struct _PATTERN {
    short field_0;
    short set;
    short field_4;
    short reset;
} PATTERN;

/*---------------------------------------------------------------------------*/

/*

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

*/

/*---------------------------------------------------------------------------*/

extern SVECTOR   ZAKO14_TARGET_SIZE;
extern SVECTOR   ZAKO14_TARGET_FORCE;
extern SVECTOR   ZAKO14_ATTACK_SIZE;
extern SVECTOR   ZAKO14_ATTACK_FORCE;
extern SVECTOR   ZAKO14_TOUCH_SIZE;
extern SVECTOR   ZAKO14_TOUCH_FORCE;
extern SVECTOR   ZAKO14_NO_POINT;
extern int       ZAKO14_EYE_LENGTH;
// extern SVECTOR   ZAKO14_PlayerPosition;
// extern COMMANDER ZAKO14Command;
// extern TOP       ZAKO14TOPCOMMAND;
// extern int       ZAKO14_Unknown;
// extern int       ZAKO14_GameFlag;
// extern int       ZAKO14_PlayerAddress;
// extern int       ZAKO14_PlayerMap;

// zako14.c
void *NewZako14( int name, int where );

// action.c
void s11a_800CB964( Work *work, int time );
void ZAKO14_ActionUpdate( Work *work );

// override.c
void s11a_800CD198( Work *work, int time );
void s11a_800CD264( Work *work, int time );
void s11a_800CD330( Work *work, int time );
void s11a_800CD3C8( Work *work, int time );
void s11a_800CD460( Work *work, int time );
void s11a_800CD514( Work *work, int time );
void s11a_800CD5DC( Work *work, int time );
void s11a_800CD680( Work *work, int time );
void s11a_800CD748( Work *work, int time );
void s11a_800CD960( Work *work, int time );
void s11a_800CDAA8( Work *work, int time );

// put.c
void ZAKO14_PutBlood( Work *work, int unit, int count );
void ZAKO14_PutFog( Work *work );
void ZAKO14_PutItem( Work *work );
void ZAKO14_PutMark( Work *work, int mark );
int  ZAKO14_SetPutChar( Work *work, int index );
int  ZAKO14_ClearPutChar( Work *work, void *func );
void ZAKO14_ExecPutChars( Work *work );

// zk11aact.c
void Zako14ActionMain( Work *work );
void Zako14PushMove( Work *work );

// think.c
void Zako14Think( Work *work );

// zk11acom.c
int  ZAKO14SetWorkID( Work *work );
void ZAKO14ResetWorkID( int id );
void ZAKO14SetTopCommAL( int alert );
void ZAKO14SetTopCommMD( int mode );
void ZAKO14SetGopointLast( void );
void ZAKO14SetGopointNoise( void );
int  ZAKO14FindRoute( int map, int id );

#endif // __MGS_ANIMAL_ZAKO14_ZAKO_H__
