#ifndef _S03D_ZAKO_H
#define _S03D_ZAKO_H

#include "mgstype.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct _PARAM
{
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

typedef struct _VISION
{
    short facedir; /* 0x0 */
    short range;   /* 0x2 */
    short length;  /* 0x4 */
    short pad;     /* 0x6 */
} VISION;

typedef struct _ACT
{
    int             field_00;       /* 0x00 */
    short           field_04;       /* 0x04 vertical speed */
    short           field_06;       /* 0x06 */
    int             field_08;       /* 0x08 */
    SVECTOR         field_0C;       /* 0x0C item drop step */
    int             field_14;       /* 0x14 kind of damage */
    short           motion1;        /* 0x18 */
    short           r_sphere;       /* 0x1A target for control.r_sphere */
    short           field_1C;       /* 0x1C */
    short           field_1E;       /* 0x1E */
} ACT;

typedef struct _PAD
{
    int             press;          /* 0x00 */
    int             field_4;        /* 0x04 */
    int             field_8;        /* 0x08 */
    short           time;           /* 0x0C */
    short           dir;            /* 0x0E */
    short           sound;          /* 0x10 */
} PAD;

struct _Work;
typedef void (*ACTION)(struct _Work *, int);
typedef void (*PUTFUNC)(struct _Work *);

typedef struct _Work
{
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
    int             field_8F8;      /* 0x8F8 */
    TARGET         *target;         /* 0x8FC */
    TARGET          attack;         /* 0x900 */
    TARGET          punch;          /* 0x948 */
    HOMING         *hom;            /* 0x990 */
    int             n_nodes;        /* 0x994 */
    SVECTOR         nodes[32];      /* 0x998 */
    void           *shadow;         /* 0xA98 */
    int            *enable_shadow;  /* 0xA9C */
    void           *glight;         /* 0xAA0 */
    int            *enable_glight;  /* 0xAA4 */
    PUTFUNC         putchar[8];     /* 0xAA8 */
    short           think1;         /* 0xAC8 */
    short           think2;         /* 0xACA */
    short           think3;         /* 0xACC */
    short           think4;         /* 0xACE */
    int             count3;         /* 0xAD0 */
    int             field_AD4;      /* 0xAD4 */
    PAD             pad;            /* 0xAD8 */
    int             trigger;        /* 0xAEC */
    void           *subweapon;      /* 0xAF0 */
    char            pad_AF4[0xAF6 - 0xAF4];
    short           field_AF6;      /* 0xAF6 */
    short           field_AF8;      /* 0xAF8 */
    char            pad_AFA[0xB00 - 0xAFA];
    int             visible;        /* 0xB00 */
    int             n_dead;         /* 0xB04 */
    PARAM           param;          /* 0xB08 */
    char            pad_B1A[0xB20 - 0xB1A];
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
    SVECTOR         throw_pos;      /* 0xB68 */
    int             current_addr;   /* 0xB70 */
    int             next_addr;      /* 0xB74 */
    char            pad_B78[0xB80 - 0xB78];
    SVECTOR         next_pos;       /* 0xB80 */
    char            pad_B88[0xB90 - 0xB88];
    int             sn_dis;         /* 0xB90 */
    int             sn_dir;         /* 0xB94 */
    int             field_B98;      /* 0xB98 */
    int             field_B9C;      /* 0xB9C */
    short           field_BA0;      /* 0xBA0 */
    short           last_vital;     /* 0xBA2 */
} Work;

typedef struct _JDATA
{
    u_short         map;            /* 0x00 */
    u_short         count;          /* 0x02 */
    u_short         data[8][2];     /* 0x04 */
} JDATA;

typedef struct _WATCHER
{
    int             field_0;        /* 0x00 */
    int             field_4;        /* 0x04 */
    int             field_8;        /* 0x08 */
    Work           *work;           /* 0x0C */
} WATCHER;

typedef struct _COMMANDER
{
    int             field_0;        /* 0x000 */
    int             field_4;        /* 0x004 */
    int             n_watchers;     /* 0x008 */
    int             time;           /* 0x00C */
    int             time2;          /* 0x010 */
    int             alert_time;     /* 0x014 */
    int             alert_level;    /* 0x018 */
    int             alert_mode;     /* 0x01C */
    int             field_20;       /* 0x020 */
    int             target_addr;    /* 0x024 */
    int             target_map;     /* 0x028 */
    SVECTOR         target_pos;     /* 0x02C */
    short           n_zones;        /* 0x034 */
    short           far_zone;       /* 0x036 */
    short           zones[4];       /* 0x038 */
    int             order[8];       /* 0x040 */
    int             n_reset;        /* 0x060 */
    MAP            *map;            /* 0x064 */
    JDATA           jdata;          /* 0x068 */
    WATCHER         watchers[8];    /* 0x08C */
    int             field_10C;      /* 0x10C */
    int             field_110;      /* 0x110 */
    int             vox[3];         /* 0x114 */
    int             end_proc;       /* 0x120 */
    int             procs[8];       /* 0x124 */
    int             field_144;      /* 0x144 */
} COMMANDER;

typedef struct _TOP
{
    int mode;
    int alert;
} TOP;

extern SVECTOR   ZAKO_NO_POINT;
extern SVECTOR   ZAKO_TARGET_SIZE;
extern SVECTOR   ZAKO_TARGET_FORCE;
extern SVECTOR   ZAKO_ATTACK_SIZE;
extern SVECTOR   ZAKO_ATTACK_FORCE;
extern short     ZakoActionTable[];
#ifndef __S03D_OVERLAY3_C__ // the bss definitions must not follow an extern declaration
extern TOP       ZakoTopCommand;
extern COMMANDER ZakoCommand;
extern int       ZakoGameFlag;
extern int       ZakoPlayerAddress;
extern int       ZakoPlayerMap;
extern SVECTOR   ZakoPlayerPosition;
#endif

static inline void SetMode(Work *work, ACTION action)
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, NULL);
}

static inline void SetMode2(Work *work, ACTION action)
{
    if (work->action2 == NULL)
    {
        work->action2 = action;
        work->time2 = 0;
    }
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust(&work->body, NULL);
}

static inline void UnsetMode(Work *work)
{
    GM_ConfigObjectOverride(&work->body, ZakoActionTable[0], 0, 4, 0);
    work->action2 = NULL;
    work->time2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

#endif // _S03D_ZAKO_H
