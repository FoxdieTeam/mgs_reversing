#ifndef __MGS_KOJO_MGREX_H__
#define __MGS_KOJO_MGREX_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "menu/menuman.h"

/* Metal Gear REX (boss) */

typedef struct _MGREX_WORK
{
    GV_ACT          actor;
    CONTROL         control;            // 0x20
    OBJECT          body;               // 0x9C  "mgrexw"
    OBJECT          leg_l;              // 0x180 "mgrexll"
    OBJECT          leg_r;              // 0x264 "mgrexrl"
    MATRIX          light[2];           // 0x348
    int             name;               // 0x388
    int             where;              // 0x38C
    int             f390;
    int             f394;
    int             target_size;        // 0x398
    TARGET          target1;            // 0x39C
    TARGET          target2;            // 0x3E4
    CONTROL         ctrl_a;             // 0x42C
    TARGET         *target_a;           // 0x4A8
    CONTROL         ctrl_b;             // 0x4AC
    TARGET         *target_b;           // 0x528
    CONTROL         ctrl_c;             // 0x52C
    TARGET         *target_c;           // 0x5A8

    /* GCL options (also saved in mgrex_saved) */
    int             f5AC;               // 'e'
    int             f5B0;
    int             f5B4;
    int             f5B8;
    int             f5BC;               // 'd'
    int             f5C0;
    int             f5C4;
    int             f5C8;
    int             f5CC;
    int             f5D0;
    int             f5D4;               // 'c'
    int             f5D8;
    int             f5DC;
    int             f5E0;
    int             f5E4;               // 's'
    int             f5E8;
    int             f5EC;
    int             f5F0;               // 'g'
    int             f5F4;
    int             f5F8;
    int             f5FC;
    int             f600;
    int             f604;
    int             f608;
    int             f60C;
    int             f610;
    int             f614;
    int             f618;
    int             f61C;
    int             f620;
    int             f624;               // 'l'
    int             f628;
    int             f62C;
    int             f630;
    int             f634;
    int             f638;
    int             f63C;
    int             f640;
    int             f644;
    int             f648;
    int             f64C;
    int             f650;
    int             f654;
    int             f658;
    int             f65C;
    int             f660;               // 'm'
    int             f664;
    int             f668;
    int             f66C;
    int             f670;
    int             f674;
    int             f678;
    int             f67C;
    int             f680;
    SVECTOR        *f684;
    SVECTOR         f688;               // 'p'
    SVECTOR         f690;
    SVECTOR         f698;
    SVECTOR         f6A0;
    SVECTOR         f6A8;
    SVECTOR         f6B0;

    short           f6B8;
    short           f6BA;
    short           f6BC;
    short           f6BE;
    short           f6C0;
    short           f6C2;
    short           f6C4;
    short           f6C6;
    int             f6C8;
    int             f6CC;
    int             f6D0;
    int             f6D4;
    short           f6D8;
    short           f6DA;
    short           f6DC;
    short           f6DE;
    int             f6E0;
    int             f6E4;
    int             f6E8;
    short           f6EC;
    short           f6EE;
    short           f6F0;
    short           f6F2;
    short           f6F4;
    short           f6F6;
    short           f6F8;
    short           f6FA;
    int             f6FC;
    char            pad_700[0xC];
    int             f70C;
    int             f710;
    char            pad_714[0xC];
    int             f720;
    int             f724;
    char            pad_728[0x30];
    int             timers[8];          // 0x758
    int             f778;
    int             f77C;
    char            pad_780[0x14];
    SVECTOR         f794;
    char            pad_79C[0x10];
    int             f7AC;
    int             f7B0;
    int             f7B4;
    int             f7B8;
    int             f7BC;
    int             f7C0;
    int             f7C4;

    MOTION_CONTROL  body_m_ctrl;        // 0x7C8
    MOTION_SEGMENT  body_m_segs1[11];   // 0x818
    MOTION_SEGMENT  body_m_segs2[11];   // 0x9A4
    CONTROL         body_control;       // 0xB30
    SVECTOR         body_rots[10];      // 0xBAC
    SVECTOR         body_adjust[10];    // 0xBFC

    MOTION_CONTROL  leg_l_m_ctrl;       // 0xC4C
    MOTION_SEGMENT  leg_l_m_segs1[14];  // 0xC9C
    MOTION_SEGMENT  leg_l_m_segs2[14];  // 0xE94
    CONTROL         leg_l_control;      // 0x108C
    SVECTOR         leg_l_rots[13];     // 0x1108
    SVECTOR         leg_l_adjust[13];   // 0x1170

    MOTION_CONTROL  leg_r_m_ctrl;       // 0x11D8
    MOTION_SEGMENT  leg_r_m_segs1[14];  // 0x1228
    MOTION_SEGMENT  leg_r_m_segs2[14];  // 0x1420
    CONTROL         leg_r_control;      // 0x1618
    SVECTOR         leg_r_rots[13];     // 0x1694
    SVECTOR         leg_r_adjust[13];   // 0x16FC

    int             f1764;              // 'z'
    int             f1768;
    int             f176C;
    OBJECT_NO_ROTS  pit_t;              // 0x1770 "pit_t"
    OBJECT          pit_liq;            // 0x1794 "pit_liq"
    OBJECT_NO_ROTS  pit_u;              // 0x1878 "pit_u"
    OBJECT_NO_ROTS  radar;              // 0x189C "radar_f1" / "radar_f3"
    OBJECT_NO_ROTS  hatch_l;            // 0x18C0 "l_hatch1" + n
    OBJECT_NO_ROTS  hatch_r;            // 0x18E4 "r_hatch1" + n
    MATRIX          pit_light[2];       // 0x1908
    TARGET         *target3;            // 0x1948
    TARGET         *target4;            // 0x194C
    int             f1950;
    int             f1954;
    int             f1958;
    int             f195C;
    int             f1960;
    int             frame;              // 0x1964
    int             f1968;
    int             mode;               // 0x196C
    int             hatch_l_model;      // 0x1970
    int             hatch_r_model;      // 0x1974
    int             f1978;
    int             f197C;
    int             f1980;
    int             f1984;
    int             f1988;
    SVECTOR         f198C;
    SVECTOR         f1994;
    SVECTOR         f199C;
    SVECTOR         f19A4;
    CONTROL         control2;           // 0x19AC
    DG_OBJ         *radar_parent;       // 0x1A28
    SVECTOR         player_pos;         // 0x1A2C
    int             f1A34;
    int             f1A38;
    int             f1A3C;
    int             f1A40;
    SVECTOR         f1A44;
    int             f1A4C;
    int             f1A50;
    int             f1A54;
    int             f1A58;
    int             f1A5C;
    int             f1A60;
    int             f1A64;
    char            pad_1A68[0x34];
    int             f1A9C;
    HZD_SEG        *segs;               // 0x1AA0
    HZD_SEG        *segs2;              // 0x1AA4
    int             f1AA8;
    int             f1AAC;
    MENU_BAR_CONF   life_bar;           // 0x1AB0
    int             f1ABC;
    int             f1AC0;
    int             f1AC4;
    int             f1AC8;
    int             f1ACC;
    int             f1AD0;
    char            pad_1AD4[0x24];
} MGREX_WORK;

extern MGREX_WORK mgrex_saved;
extern int        s17a_dword_800E5E30;
extern int        s17a_dword_800E5E34;

#endif // __MGS_KOJO_MGREX_H__
