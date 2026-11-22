#ifndef __MGS_ANIMAL_ZAKO11A_ZAKO_H__
#define __MGS_ANIMAL_ZAKO11A_ZAKO_H__

#include "game/game.h"

typedef struct _PARAM {
    signed char fAF8;
    char        fAF9;
    char        fAFA;
    signed char c_root;
    char        defends[4];
    signed char roots[4];
    short       life;
    short       max_life; /* for the red damage bar */
    short       faint;
} PARAM;

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

    int             field_8C8;      /* 0x8C8 */
    int             field_8CC;      /* 0x8CC */
    char            pad_8D0[0x8D4 - 0x8D0];
    SVECTOR         field_8D4;      /* 0x8D4 */
    int             field_8DC;      /* 0x8DC */
    short           field_8E0;      /* 0x8E0 */
    short           field_8E2;      /* 0x8E2 */
    short           field_8E4;      /* 0x8E4 */
    short           field_8E6;      /* 0x8E6 */

    void          (*field_8E8)(struct _Work *, int);  /* 0x8E8 */
    int             field_8EC;      /* 0x8EC */
    int             field_8F0;      /* 0x8F0 */
    int             field_8F4;      /* 0x8F4 */
    int             field_8F8;      /* 0x8F8 */
    TARGET         *field_8FC;      /* 0x8FC */
    TARGET          field_900;      /* 0x900 */
    char            pad_948[0x954 - 0x948];
    void          (*field_954)(struct _Work *);  /* 0x954 */
    int             field_958;      /* 0x958 */
    int             field_95C;      /* 0x95C */
    int             field_960;      /* 0x960 */
    int             field_964;      /* 0x964 */
    int             field_968;      /* 0x968 */
    int             field_96C;      /* 0x96C */
    short           field_970;      /* 0x970 */
    short           field_972;      /* 0x972 */
    int             field_974;      /* 0x974 */
    int             field_978;      /* 0x978 */
    int             field_97C;      /* 0x97C */
    int             field_980;      /* 0x980 */
    int             field_984;      /* 0x984 */
    int             field_988;      /* 0x988 */
    int             field_98C;      /* 0x98C */

    HOMING         *hom;            /* 0x990 */

    int             n_nodes;        /* 0x994 */
    SVECTOR         nodes[32];      /* 0x998 */

    void           *shadow;         /* 0xA98 */
    int            *enable_shadow;  /* 0xA9C */
    void           *glight;         /* 0xAA0 */
    int            *enable_glight;  /* 0xAA4 */

    int             field_AA8[8];   /* 0xAA8 */
    short           field_AC8;      /* 0xAC8 */
    short           field_ACA;      /* 0xACA */
    short           field_ACC;      /* 0xACC */
    char            pad_ACE[0xAD0 - 0xACE];
    int             field_AD0;      /* 0xAD0 */
    char            pad_AD4[0xAD8 - 0xAD4];
    int             field_AD8;      /* 0xAD8 */
    int             field_ADC;      /* 0xADC */
    int             field_AE0;      /* 0xAE0 */
    char            pad_AE4[0xAE6 - 0xAE4];
    short           field_AE6;      /* 0xAE6 */
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xAF6 - 0xAEA];
    short           field_AF6;      /* 0xAF6 */
    char            pad_AF8[0xB00 - 0xAF8];
    int             field_B00;      /* 0xB00 */
    int             field_B04;      /* 0xB04 */
    PARAM           param;          /* 0xB08 */
    char            pad_B1A[0xB20 - 0xB1A];
    unsigned short  field_B20;      /* 0xB20 */
    unsigned short  field_B22;      /* 0xB22 */
    unsigned short  field_B24;      /* 0xB24 */
    short           field_B26;      /* 0xB26 */
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB32 - 0xB2C];
    unsigned char   field_B32;      /* 0xB32 */
    unsigned char   field_B33;      /* 0xB33 */
    char            pad_B34[0xB48 - 0xB34];
    SVECTOR         field_B48;      /* 0xB48 */
    char            pad_B50[0xB54 - 0xB50];
    int             field_B54;      /* 0xB54*/
    int             field_B58;      /* 0xB58 */
    int             field_B5C;      /* 0xB5C */
    int             field_B60;      /* 0xB60 */
    int             field_B64;      /* 0xB64 */
    SVECTOR         field_B68;      /* 0xB68 */
    int             field_B70;      /* 0xB70 */
    int             field_B74;      /* 0xB74 */
    char            pad_B74[0xB80 - 0xB78];
    SVECTOR         field_B80;      /* 0xB80 */
    char            pad_B88[0xB90 - 0xB88];
    int             field_B90;      /* 0xB90 */
    unsigned short  field_B94;      /* 0xB94 */
    char            pad_B96[0xBA0 - 0xB96];
    short           field_BA0;      /* 0xBA0 */
    char            pad_BA2[0xC00 - 0xBA2];
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
// ...

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
