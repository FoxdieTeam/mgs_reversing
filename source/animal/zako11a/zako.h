#ifndef __MGS_ANIMAL_ZAKO11A_ZAKO_H__
#define __MGS_ANIMAL_ZAKO11A_ZAKO_H__

#include "game/game.h"

// TODO: These structures should be unified with the other zakos, using stage
//       ifdefs to add or remove fields where necessary.

typedef struct _ACT {
    /* 0x8C8 */ int            field_00;
    /* 0x8CC */ short          field_04;
    /* 0x8CE */ short          field_06;
    /* 0x8D0 */ int            field_08;
    /* 0x8D4 */ SVECTOR        field_0C;
    /* 0x8DC */ int            field_14;
    /* 0x8E0 */ short          last_set;
    /* 0x8E2 */ short          last_unset;
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
    /* 0xB78 */ char           next;   // guessed from option 'n'
    /* 0xB79 */ signed char    root;
    /* 0xB7A */ char           c_root;
    /* 0xB7B */ char           c_next; // guessed from option 'n'
    /* 0xB7C */ signed char    item;
    /* 0xB7D */ char           g_flag;
    /* 0xB7E */ short          life;
    /* 0xB80 */ short          faint;
    /* 0xB82 */ short          z_flag;
} PARAM;

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
    /* 0x8EC */ int            field_8EC;
    /* 0x8F0 */ int            field_8F0;
    /* 0x8F4 */ int            field_8F4;
    /* 0x8F8 */ int            field_8F8;
    /* 0x8FC */ char           pad8FC[ 0x4 ];
    /* 0x900 */ TARGET        *target;
    /* 0x904 */ TARGET         attack;
    /* 0x94C */ TARGET         touch;
    /* 0x994 */ char           pad994[ 0x48 ];
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
    /* 0xB00 */ void          *field_B00[ 8 ];
    /* 0xB20 */ short          think1;
    /* 0xB22 */ short          think2;
    /* 0xB24 */ short          think3;
    /* 0xB26 */ short          think4;
    /* 0xB28 */ int            count3;
    /* 0xB2C */ int            t_count;
    /* 0xB30 */ int            l_count;
    /* 0xB34 */ int            next_node;
    /* 0xB38 */ char           padB38[ 0xC ];
    /* 0xB44 */ int            field_B44;
    /* 0xB48 */ char           padB48[ 0x2 ];
    /* 0xB4A */ short          field_B4A;
    /* 0xB4C */ char           padB4C[ 0x8 ];
    /* 0xB54 */ int            field_B54;
    /* 0xB58 */ char           padB58[ 0x10 ];
    /* 0xB68 */ int            mark_time;
    /* 0xB6C */ int            act_status; // verify this
    /* 0xB70 */ char           padB70[ 0x4 ];
    /* 0xB74 */ PARAM          param;
    /* 0xB84 */ char           padB84[ 0x4 ];
    /* 0xB88 */ short          field_B88;
    /* 0xB8A */ short          field_B8A;
    /* 0xB8C */ short          field_B8C;
    /* 0xB8E */ char           padB8E[ 0x2 ];
    /* 0xB90 */ short          field_B90;
    /* 0xB92 */ char           padB92[ 0x2 ];
    /* 0xB94 */ int            alert_level;
    /* 0xB98 */ signed char    field_B98[ 8 ];
    /* 0xBA0 */ SVECTOR        field_BA0;
    /* 0xBA8 */ char           padBA8[ 0x4 ];
    /* 0xBAC */ int            time[ 8 ];
    /* 0xBCC */ short          dir[ 4 ];
    /* 0xBD4 */ int            field_BD4;
    /* 0xBD8 */ SVECTOR        field_BD8;
    /* 0xBE0 */ SVECTOR        target_pos;
    /* 0xBE8 */ int            field_BE8;
    /* 0xBEC */ int            field_BEC;
    /* 0xBE8 */ int            field_BF0;
    /* 0xBF4 */ int            target_addr;
    /* 0xBF8 */ int            target_map;
    /* 0xBFC */ int            field_BFC; // some distance flag
    /* 0xC00 */ int            field_C00; // some distance index
    /* 0xC04 */ char           padC04[ 0x8 ];
    /* 0xC0C */ int            field_C0C;
    /* 0xC10 */ int            field_C10;
    /* 0xC14 */ char           padC14[ 0x8 ];
    /* 0xC1C */ SVECTOR        field_C1C;
    /* 0xC24 */ char           padC24[ 0x8 ];
    /* 0xC2C */ int            field_C2C;
    /* 0xC30 */ char           padC30[ 0x8 ];
    /* 0xC38 */ int            field_C38;
    /* 0xC3C */ char           padC3C[ 0x8 ];
    /* 0xC44 */ short          field_C44;
    /* 0xC46 */ char           padC46[ 0x2 ];
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
    /* 0x010 */ int     field_10;
    /* 0x014 */ int     alert_time;
    /* 0x018 */ int     alert_level;
    /* 0x01C */ int     alert_mode;
    /* 0x020 */ int     field_20;
    /* 0x024 */ int     field_24;
    /* 0x028 */ int     field_28;
    /* 0x02C */ SVECTOR field_2C;
    /* 0x034 */ short   n_zones;
    /* 0x036 */ short   field_36;
    /* 0x038 */ short   zones[ 4 ];
    /* 0x040 */ int     field_40[ 8 ];
    /* 0x060 */ int     field_60;
    /* 0x064 */ MAP    *map;
    /* 0x068 */ JDATA   jdata;
    /* 0x08C */ WATCHER watchers[ 8 ];
    /* 0x10C */ int     field_10C;
    /* 0x110 */ int     field_110;
    /* 0x114 */ int     field_114;
    /* 0x118 */ int     field_118;
    /* 0x11C */ int     field_11C;
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

extern SVECTOR   ZAKO11A_TARGET_SIZE;
extern SVECTOR   ZAKO11A_TARGET_FORCE;
extern SVECTOR   ZAKO11A_ATTACK_SIZE;
extern SVECTOR   ZAKO11A_ATTACK_FORCE;
extern SVECTOR   ZAKO11A_TOUCH_SIZE;
extern SVECTOR   ZAKO11A_TOUCH_FORCE;
extern SVECTOR   ZAKO11A_NO_POINT;
extern u_short   ZAKO11A_EYE_LENGTH;
extern SVECTOR   ZAKO11A_PlayerPosition;
extern COMMANDER ZAKO11ACommand;
extern TOP       ZAKO11ATOPCOMMAND;
extern int       ZAKO11A_Unknown;
extern int       ZAKO11A_GameFlag;
extern int       ZAKO11A_PlayerAddress;
extern int       ZAKO11A_PlayerMap;

int  ZAKO11ASetWorkID( Work *work );
void ZAKO11AResetWorkID( int id );

void ZAKO11ASetTopCommAL( int alert );
void ZAKO11ASetTopCommMD( int mode );

void ZAKO11ASetGopointLast( void );
void ZAKO11ASetGopointNoise( void );

int ZAKO11AFindRoute( int map, int id );

#endif // __MGS_ANIMAL_ZAKO11A_ZAKO_H__
