#ifndef _INC_M1E1
#define _INC_M1E1

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/******************************************************************************
 * included
 */

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

#include "common.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagM1E1ACT M1E1ACT, *PM1E1ACT, *LPM1E1ACT;

typedef struct tagM1E1GUNNERACT
{
    GV_ACT         actor;               /* 0x000 */
    CONTROL        control;             /* 0x020 */
    MATRIX         light[2];            /* 0x09C */
    OBJECT         body;                /* 0x0DC */
    TARGET        *target;              /* 0x1C0 */
    HOMING        *homing;              /* 0x1C4 */
    MATRIX         field_1C8;           /* 0x1C8 */
    int            field_1E8;           /* 0x1E8 */
    LPM1E1ACT      lpParent;            /* 0x1EC */
    int            field_1F0;           /* 0x1F0 */
    int            field_1F4;           /* 0x1F4 */
    int            nWeaponSave;         /* 0x1F8 */
    int            nItemSave;           /* 0x1FC */
    int            field_200;           /* 0x200 */
    int            field_204;           /* 0x204 */
    int            field_208;           /* 0x208 */
    int            field_20C;           /* 0x20C */
    char           pad_210[0x218 - 0x210];
    int            field_218;           /* 0x218 */
    int            field_21C;           /* 0x21C */
    char           pad_220[0x228 - 0x220];
    void          *field_228;           /* 0x228 */
    int            field_22C;           /* 0x22C */
    int            field_230;           /* 0x230 */
    MOTION_CONTROL m_ctrl;              /* 0x234 */
    MOTION_SEGMENT m_segs1[17];         /* 0x284 */
    MOTION_SEGMENT m_segs2[17];         /* 0x4E8 */
    CONTROL        subcontrol;          /* 0x74C */
    SVECTOR        rots[16];            /* 0x7C8 */
} M1E1GUNNERACT, *PM1E1GUNNERACT, *LPM1E1GUNNERACT;

typedef struct tagM1E1VALCANACT
{
    GV_ACT    actor;                    /* 0x000 */
    CONTROL   control;                  /* 0x020 */
    MATRIX    light[2];                 /* 0x09C */
    OBJECT    body;                     /* 0x0DC */
    char      pad_1C0[0x1E8 - 0x1C0];
    int       field_1E8;                /* 0x1E8 */
    LPM1E1ACT lpParent;                 /* 0x1EC */
    char      pad_1F0[0x1F8 - 0x1F0];
    int       nWeaponSave;              /* 0x1F8 */
    int       nItemSave;                /* 0x1FC */
    char      pad_200[0x214 - 0x200];
    int       field_214;                /* 0x214 */
    char      pad_218[0x220 - 0x218];
    int       field_220;                /* 0x220 */
    int       field_224;                /* 0x224 */
    char      pad_228[0x234 - 0x228];
    MOTION_CONTROL m_ctrl;              /* 0x234 */
    MOTION_SEGMENT m_segs1[17];         /* 0x284 */
    MOTION_SEGMENT m_segs2[17];         /* 0x4E8 */
    CONTROL        subcontrol;          /* 0x74C */
    SVECTOR        rots[16];            /* 0x7C8 */
} M1E1VALCANACT, *PM1E1VALCANACT, *LPM1E1VALCANACT;

struct tagM1E1ACT
{
    GV_ACT          actor;              /* 0x000 */
    CONTROL         control;            /* 0x020 */
    MATRIX          light[2];           /* 0x09C */
    OBJECT          objBody;            /* 0x0DC */
    OBJECT          objLeftCater[3];    /* 0x1C0 */
    OBJECT          objRightCater[3];   /* 0x46C */
    TARGET*         lpTarget[10];       /* 0x718 */
    BOOL            bInitialize;        /* 0x740 */
    int             field_744;          /* 0x744 */
    int             field_748;          /* 0x748 */
    CONTROL         oldControl;         /* 0x74C */
    OBJECT          oldBody;            /* 0x7C8 */
    char            life_name[16];      /* 0x8AC "GUNNER" */
    MENU_BAR_CONF   life_conf;          /* 0x8BC */
    int             field_8C8;          /* 0x8C8 */
    TARGET          target0;            /* 0x8CC */
    TARGET          target1;            /* 0x914 */
    int             field_95C;          /* 0x95C */
    TARGET          target2;            /* 0x960 */
    TARGET          target3;            /* 0x9A8 */
    TARGET          target4;            /* 0x9F0 */
    TARGET          target5;            /* 0xA38 */
    int             field_A80;
    TARGET          field_A84[10];
    int             field_D54;      /* mode (1 / 6) */
    int             field_D58;
    int             field_D5C;      /* 'e' block */
    int             field_D60;
    int             field_D64;
    int             field_D68;
    int             field_D6C;
    int             field_D70;      /* 'd' block */
    int             field_D74;
    int             field_D78;
    int             field_D7C;
    int             field_D80;
    int             field_D84;
    int             field_D88;
    int             field_D8C;
    int             field_D90;      /* 's' block */
    int             field_D94;
    int             field_D98;
    int             field_D9C;
    int             field_DA0;
    int             field_DA4;      /* 'g' block */
    int             field_DA8;
    int             field_DAC;
    int             field_DB0;
    int             field_DB4;
    int             field_DB8;      /* 'c' block */
    int             field_DBC;
    int             field_DC0;
    int             field_DC4;
    int             field_DC8;
    SVECTOR         field_DCC;      /* mov source; .pad = enable flag */
    SVECTOR         field_DD4;      /* turn source; .pad = enable flag */
    short           field_DDC;
    short           field_DDE;
    short           field_DE0;
    short           field_DE2;
    short           field_DE4;
    short           field_DE6;
    short           field_DE8;
    short           field_DEA;
    int             field_DEC;      /* 'o' block */
    int             field_DF0;
    int             field_DF4;
    int             field_DF8;
    int             field_DFC;
    int             field_E00;
    int             field_E04;      /* 'w' block */
    int             field_E08;
    int             field_E0C;
    int             field_E10;
    int             field_E14;
    int             field_E18;
    int             field_E1C;      /* 'z' block */
    int             field_E20;
    int             field_E24;      /* 's' derived */
    int             field_E28;
    int             field_E2C;
    int             field_E30;
    VECTOR          field_E34;
    VECTOR          field_E44;
    SVECTOR         field_E54;
    int             field_E5C;
    int             nSoundVolume;       /* 0xE60 */
    int             field_E64;
    int             field_E68;
    int             field_E6C;
    int             field_E70;
    int             field_E74;
    int             field_E78;
    int             nLeftCaterDirection;    /* 0xE7C */
    int             nRightCaterDirection;   /* 0xE80 */
    int             nCaterLength;           /* 0xE84 */
    int             field_E88;              /* 0xE88 */
    SVECTOR         svectLeftCater;         /* 0xE8C */
    SVECTOR         svectRightCater;        /* 0xE94 */
    u_short         field_E9C;              /* 0xE9C */
    short           field_E9E;              /* 0xE9E */
    u_short         field_EA0;              /* 0xEA0 */
    char            pad_EA2[0xEA4 - 0xEA2];
    short           field_EA4;              /* 0xEA4 */
    char            pad_EA6[0xEA8 - 0xEA6];
    SVECTOR         field_EA8;              /* 0xEA8 */
    LPM1E1GUNNERACT lpGunner;               /* 0xEB0 */
    SVECTOR         field_EB4;              /* 0xEB4 */
    LPM1E1VALCANACT lpValcan;               /* 0xEBC */
    int             field_EC0;              /* 0xEC0 */
    int             field_EC4;              /* 0xEC4 */
    int             field_EC8;              /* 0xEC8 */
    int             field_ECC;              /* 0xECC */
    int             field_ED0;              /* 0xED0 */
    int             field_ED4;              /* 0xED4 */
    int             field_ED8;              /* 0xED8 */
    void*           lpM1Throw;              /* 0xEDC */
    SVECTOR         field_EE0;              /* 0xEE0 */
    SVECTOR         field_EE8;              /* 0xEE8 */
    SVECTOR         field_EF0[10];          /* 0xEF0 */
    int             field_F40;              /* 0xF40 */
    int             field_F44;              /* 0xF44 */
    int             field_F48;              /* 0xF48 */
    int             field_F4C;              /* 0xF4C */
    int             field_F50;              /* 0xF50 */
    int             field_F54;              /* 0xF54 */
    int             field_F58;              /* 0xF58 */
    int             field_F5C;              /* 0xF5C */
    int             nLeftCaterSmokeTCount;  /* 0xF60 */
    int             nRightCaterSmokeTCount; /* 0xF64 */
    int             field_F68;              /* 0xF68 */
    int             field_F6C;              /* 0xF6C */
    int             nCaterSoundTCount;      /* 0xF70 */
    int             nCaterSoundStartTCount; /* 0xF74 */
    int             field_F78;              /* 0xF78 */
    int             field_F7C;              /* 0xF7C */
    int             field_F80;              /* 0xF80 */
    int             field_F84;              /* 0xF84 */
    int             field_F88;              /* 0xF88 */
    SVECTOR         bbox[12];               /* 0xF8C */
    struct {
        HZD_SEG seg[4];
        HZD_FLR flr[2];
    } hzdBlock[5];                      /* 0xFEC */
    HZD_FLR copy0;                      /* 0x130C */
    HZD_FLR copy1;                      /* 0x133C */
    HZD_FLR copy2;                      /* 0x136C */
};

/******************************************************************************
 * prototypes
 */

/* m1e1catr.c */
void M1E1Caterpiller(LPM1E1ACT lpAct);
void M1E1GetCaterpillerVertex(
    OBJECT*  lpobjLeftCater,
    OBJECT*  lpobjRightCater,
    SVECTOR* lpsvectPos,
    BOOL     arg3);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_M1E1 */
