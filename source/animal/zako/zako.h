#ifndef __MGS_ANIMAL_ZAKO11A_ZAKO_H__
#define __MGS_ANIMAL_ZAKO11A_ZAKO_H__

#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define TARGET_FLAG     ( TARGET_CAPTURE | TARGET_POWER | TARGET_PUSH \
                        | TARGET_SEEK | TARGET_TOUCH )

#define PUTFOOTNOISE    0
#define PUTBREATH       1
#define PUTSIGHTLINE    2
#define GUNSHOOT        3

// TODO: check name
typedef struct _ACT {
    int     field_00;
    short   field_04;
    short   field_06;
    int     field_08;
    SVECTOR field_0C;
    int     field_14;
    short   motion1;
    short   field_1A;
    short   field_1C;
    short   field_1E;
} ACT;

typedef struct _PARAM {
    signed char index;
    signed char blood;
    signed char area;
    signed char c_root;
    char        defends[4];
    signed char roots[4];
    short       life;
    short       faint;
    short       damage;
} PARAM;

typedef struct _VISION {
    short facedir;
    short range;
    short length;
    short pad;
} VISION;

typedef struct _PAD {
    int   press;
    int   mode;
    int   tmp;
    short time;
    short dir;
    short sound;
} PAD;

struct _Work;

typedef void ( *ACTION )( struct _Work *, int ) ;
typedef void ( *PUTCHAR )( struct _Work * ) ;

typedef struct _Work {
    GV_ACT          actor;
    CONTROL         control;
    OBJECT          body;
    int             lod;
    DG_DEF         *models[2];
    MOTION_CONTROL  m_ctrl;
    MOTION_SEGMENT  m_segs1[17];
    MOTION_SEGMENT  m_segs2[17];
    SVECTOR         rots[16];
    SVECTOR         adjust[16];
    OBJECT          weapon;
    MATRIX          light[2];
    ACT             act;
    ACTION          action;
    ACTION          action2;
    int             time;
    int             time2;
    int             actend;
    TARGET         *target;
    TARGET          attack;
    TARGET          touch;
    HOMING         *hom;
    int             n_nodes;
    SVECTOR         nodes[32];
    void           *shadow;
    int            *enable_shadow;
    void           *glight;
    int            *enable_glight;
    PUTCHAR         putchar[8];
    short           think1;
    short           think2;
    short           think3;
    short           think4;
    int             count3;
    int             next_node;
    PAD             pad;
    u_long          trigger;
    void           *subweapon;
    char            pad_AF4[0x2];
    short           field_AF6;
    short           field_AF8;
    char            pad_AFA[0x6];
    int             visible;
    int             n_dead;
    PARAM           param;
    char            pad_B1A[0x6];
    VISION          vision;
    int             alert_level;
    signed char     modetime[8];
    SVECTOR         player_pos;
    int             player_dir;
    SVECTOR         start_pos;
    SVECTOR         target_pos;
    int             start_addr;
    int             start_map;
    int             last_addr;
    int             target_addr;
    int             target_map;
    int             chase_dis;
    SVECTOR         current_pos;
    int             current_addr;
    int             next_addr;
    char            pad_B78[0x8];
    SVECTOR         next_pos;
    char            pad_B88[0x8];
    int             sn_dis;
    int             sn_dir;
    int             field_B98;
    int             act_status;
    short           in_grip;
    short           vital_prev;
} Work;

// TODO: check name
typedef struct _WATCHER {
    int   field_0;
    int   field_4;
    int   field_8;
    Work *work;
} WATCHER;

typedef struct _JOINT {
    u_short map;
    u_short zone;
} JOINT;

typedef struct _JOINT_DATA {
    u_short map;
    u_short n_joints;
    JOINT   joints[ 8 ];
} JOINT_DATA;

typedef struct _COMMANDER {
    int             field_0;
    int             field_4;
    int             count;
    int             field_C;
    int             field_10;
    int             field_14;
    int             field_18;
    int             field_1C;
    int             field_20;
    int             target_addr;
    int             target_map;
    SVECTOR         target_pos;
    short           n_zones;
    short           c_reset_pos;
    short           zones[4];
    int             order[8];
    int             reset_enemy_num;
    MAP            *map;
    JOINT_DATA      joint_data;
    WATCHER         watchers[8];
    int             field_10C;
    int             field_110;
    int             sounds[3];
    int             end_proc;
    int             procs[8];
    int             field_144;
} COMMANDER;

// TODO: check name
typedef struct _TOP {
    int mode;
    int alert;
} TOP;

typedef struct _CommanderWork {
    GV_ACT actor;
    char   pad_20[ 0x4 ];
} CommanderWork;

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
    work->control.turn.vx = work->control.turn.vz = 0;
}

/*---------------------------------------------------------------------------*/

#ifndef __ANIMAL_ZAKO_ZAKOCOM_C__
extern SVECTOR   ZAKO_TARGET_SIZE;
extern SVECTOR   ZAKO_TARGET_FORCE;
extern SVECTOR   ZAKO_ATTACK_SIZE;
extern SVECTOR   ZAKO_ATTACK_FORCE;
extern SVECTOR   ZAKO_TOUCH_SIZE;
extern SVECTOR   ZAKO_TOUCH_FORCE;
extern SVECTOR   ZAKO_NO_POINT;
extern SVECTOR   ZAKO_PlayerPosition;
extern COMMANDER ZAKOCommand;
extern TOP       ZAKOTOPCOMMAND;
extern int       ZAKO_GameFlag;
extern int       ZAKO_GameStatus;
extern int       ZAKO_PlayerAddress;
extern int       ZAKO_PlayerMap;
extern int       ZAKO_VibTime;
#endif // __ANIMAL_ZAKO_ZAKOCOM_C__

// zako.c
void *NewZako( int name, int where );

// action.c
void s03d_800CE12C( Work *work, int time );
void s03d_800CE318( Work *work, int time );
void s03d_800CE5B4( Work *work, int time );
void s03d_800CE644( Work *work, int time );
void s03d_800CE720( Work *work, int time );
void s03d_800CE8F4( Work *work, int time );
void s03d_800CE9E8( Work *work, int time );
void s03d_800CEB38( Work *work, int time );
void s03d_800CECBC( Work *work, int time );
void s03d_800CED94( Work *work, int time );
void s03d_800CEE3C( Work *work, int time );
void s03d_800CF194( Work *work, int time );
void s03d_800CF4D4( Work *work, int time );
void s03d_800CF548( Work *work, int time );
void s03d_800CF68C( Work *work, int time );
void s03d_800CF844( Work *work, int time );
void s03d_800CF90C( Work *work, int time );
void s03d_800CFA04( Work *work, int time );
void s03d_800CFB04( Work *work, int time );
void s03d_800CFFF0( Work *work, int time );
void s03d_800D01C4( Work *work, int time );
void ZAKO_Action( Work *work );

// override.c
void ActOverScoutR( Work *work, int time );
void ActOverScoutL( Work *work, int time );
void s03d_800D0754( Work *work, int time );
void s03d_800D07DC( Work *work, int time );
void s03d_800D085C( Work *work, int time );
void s03d_800D08DC( Work *work, int time );
void s03d_800D0958( Work *work, int time );
void s03d_800D09D8( Work *work, int time );

// put.c
void ZAKO_PutBlood( Work *work, int unit, int count );
void ZAKO_PutDust( Work *work );
void ZAKO_PutItem( Work *work, int type );
void ZAKO_PutMark( Work *work, int mark );
int  ZAKO_SetPutChar( Work *work, int index );
void ZAKO_ExecPutChars( Work *work );

// think.c
void ZakoThink( Work *work );

// zakoact.c
void ZakoActionMain( Work *work );
void ZakoPushMove( Work *work );

// zakocom.c
int  ZAKOSetWorkID( Work *work );
int  ZAKOSetDead( void );
void ZAKOResetWorkID( int id );
void ZAKOSetTopCommAL( int alert );
void ZAKOSetTopCommMD( int mode );
void ZAKOSetGopointLast( void );
void ZAKOSetGopointNoise( void );
int  ZAKOGetMapJointZone( int map, int id );

#endif // __MGS_ANIMAL_ZAKO11A_ZAKO_H__
