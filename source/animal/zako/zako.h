#ifndef __MGS_ANIMAL_ZAKO11A_ZAKO_H__
#define __MGS_ANIMAL_ZAKO11A_ZAKO_H__

#include "game/game.h"

// TODO: check name
typedef struct _ACT {
    int     field_00;
    short   field_04;
    short   field_06;
    int     field_08;
    SVECTOR field_0C;
    int     field_14;
    short   field_18;
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
typedef void ( *PUTFUNC )( struct _Work * ) ;

typedef struct _Work {
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          body;           /* 0x09C */
    int             lod;            /* 0x180 */
    DG_DEF         *models[2];      /* 0x184 */
    MOTION_CONTROL  m_ctrl;         /* 0x18C */
    MOTION_SEGMENT  m_segs1[17];    /* 0x1DC */
    MOTION_SEGMENT  m_segs2[17];    /* 0x440 */
    SVECTOR         rots[16];       /* 0x6A4 */
    SVECTOR         adjust[16];     /* 0x724 */
    OBJECT          weapon;         /* 0x7A4 */
    MATRIX          light[2];       /* 0x888 */
    ACT             act;            /* 0x8C8 */
    ACTION          action;         /* 0x8E8 */
    ACTION          action2;        /* 0x8EC */
    int             time;           /* 0x8F0 */
    int             time2;          /* 0x8F4 */
    int             actend;         /* 0x8F8 */
    TARGET         *target;         /* 0x8FC */
    TARGET          attack;         /* 0x900 */
    TARGET          touch;          /* 0x948 */
    HOMING         *hom;            /* 0x990 */
    int             n_nodes;        /* 0x994 */
    SVECTOR         nodes[32];      /* 0x998 */
    void           *shadow;         /* 0xA98 */
    int            *enable_shadow;  /* 0xA9C */
    void           *glight;         /* 0xAA0 */
    int            *enable_glight;  /* 0xAA4 */
    PUTFUNC         putfuncs[8];    /* 0xAA8 */
    short           think1;         /* 0xAC8 */
    short           think2;         /* 0xACA */
    short           think3;         /* 0xACC */
    short           think4;         /* 0xACE */
    int             count3;         /* 0xAD0 */
    int             next_node;      /* 0xAD4 could be t_count or l_count */
    PAD             pad;            /* 0xAD8 */
    char            pad_AEC[0x4];
    void           *subweapon;      /* 0xAF0 */
    char            pad_AF4[0x2];
    short           field_AF6;      /* 0xAF6 */
    short           field_AF8;      /* 0xAF8 */
    char            pad_AFA[0x6];
    int             visible;        /* 0xB00 */
    int             n_dead;         /* 0xB04 */
    PARAM           param;          /* 0xB08 */
    char            pad_B1A[0x6];
    VISION          vision;         /* 0xB20 */
    int             alert_level;    /* 0xB28 */
    signed char     modetime[8];    /* 0xB2C */
    SVECTOR         player_pos;     /* 0xB34 */
    int             player_dir;     /* 0xB3C */
    SVECTOR         start_pos;      /* 0xB40 */
    SVECTOR         target_pos;     /* 0xB48 */
    int             start_addr;     /* 0xB50 */
    int             start_map;      /* 0xB54 */
    int             last_addr;      /* 0xB58 */
    int             target_addr;    /* 0xB5C */
    int             target_map;     /* 0xB60 */
    int             chase_dis;      /* 0xB64 */
    SVECTOR         current_pos;    /* 0xB68 */
    int             current_addr;   /* 0xB70 */
    int             next_addr;      /* 0xB74 */
    char            pad_B78[0x8];
    SVECTOR         next_pos;       /* 0xB80 */
    char            pad_B88[0x8];
    int             sn_dis;         /* 0xB90 */
    int             sn_dir;         /* 0xB94 */
    char            pad_B98[0x8];
    short           in_grip;        /* 0xBA0 */
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
    int             field_0;         /* 0x000 */
    int             field_4;         /* 0x004 */
    int             count;           /* 0x008 */
    int             field_C;         /* 0x00C */
    int             field_10;        /* 0x010 */
    int             field_14;        /* 0x014 */
    int             field_18;        /* 0x018 */
    int             field_1C;        /* 0x01C */
    int             field_20;        /* 0x020 */
    int             target_addr;     /* 0x024 */
    int             target_map;      /* 0x028 */
    SVECTOR         target_pos;      /* 0x02C */
    short           n_zones;         /* 0x034 */
    short           c_reset_pos;     /* 0x036 */
    short           zones[4];        /* 0x038 */
    int             order[8];        /* 0x040 */
    int             reset_enemy_num; /* 0x060 */
    MAP            *map;             /* 0x064 */
    JOINT_DATA      joint_data;      /* 0x068 */
    WATCHER         watchers[8];     /* 0x08C */
    int             field_10C;       /* 0x10C */
    int             field_110;       /* 0x110 */
    int             sounds[3];       /* 0x114 */
    int             end_proc;        /* 0x120 */
    int             procs[8];        /* 0x124 */
    int             field_144;       /* 0x144 */
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

/*---------------------------------------------------------------------------*/

#ifndef __ANIMAL_ZAKO_ZAKOCOM_C__
extern SVECTOR   ZAKO_NO_POINT;
extern SVECTOR   ZAKO_PlayerPosition;
extern COMMANDER ZAKOCommand;
extern TOP       ZAKOTOPCOMMAND;
extern int       ZAKO_GameFlag;
extern int       ZAKO_GameStatus;
extern int       ZAKO_PlayerAddress;
extern int       ZAKO_PlayerMap;
#endif // __ANIMAL_ZAKO_ZAKOCOM_C__

// zako.c
void *NewZako( int name, int where );

// action.c
// ...

// override.c
// ...

// put.c
void s03d_800D0C90( Work *work, int index );
int  Zako_800D0EF0( Work *work, int index );

// think.c
void ZakoThink( Work *work );

// zakoact.c
void ZakoActionMain( Work *work );
void ZakoPushMove( Work *work );

// zakocom.c
int  ZAKOSetWorkID( Work *work );
int  ZAKO_800D4038( void ); /* TODO: name */
void ZAKOResetWorkID( int id );
void ZAKOSetTopCommAL( int alert );
void ZAKOSetTopCommMD( int mode );
void ZAKOSetGopointLast( void );
void ZAKOSetGopointNoise( void );
int  ZAKOGetMapJointZone( int map, int id );

#endif // __MGS_ANIMAL_ZAKO11A_ZAKO_H__
