#ifndef _S03D_ZAKO_H
#define _S03D_ZAKO_H

#include "mgstype.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct _PARAM
{
    signed char fAF8;
    char        fAF9;
    char        fAFA;
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
    short           field_04;       /* 0x04 */
    short           field_06;       /* 0x06 */
    int             field_08;       /* 0x08 */
    SVECTOR         field_0C;       /* 0x0C */
    int             field_14;       /* 0x14 */
    short           motion1;        /* 0x18 */
    short           motion2;        /* 0x1A */
    short           field_1C;       /* 0x1C */
    short           field_1E;       /* 0x1E */
} ACT;

struct _Work;
typedef void (*ACTION)(struct _Work *, int);

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
    short           field_ACE;      /* 0xACE */
    int             field_AD0;      /* 0xAD0 */
    int             field_AD4;      /* 0xAD4 */
    int             field_AD8;      /* 0xAD8 */
    int             field_ADC;      /* 0xADC */
    int             field_AE0;      /* 0xAE0 */
    char            pad_AE4[0xAE6 - 0xAE4];
    short           field_AE6;      /* 0xAE6 */
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xAEC - 0xAEA];
    int             field_AEC;      /* 0xAEC */
    char            pad_AF0[0xAF6 - 0xAF0];
    short           field_AF6;      /* 0xAF6 */
    short           field_AF8;      /* 0xAF8 */
    char            pad_AFA[0xB00 - 0xAFA];
    int             field_B00;      /* 0xB00 */
    int             field_B04;      /* 0xB04 */
    PARAM           param;          /* 0xB08 */
    char            pad_B1A[0xB20 - 0xB1A];
    VISION          vision;         /* 0xB20 */
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB32 - 0xB2C];
    unsigned char   field_B32;      /* 0xB32 */
    unsigned char   field_B33;      /* 0xB33 */
    SVECTOR         field_B34;      /* 0xB34 */
    int             field_B3C;      /* 0xB3C */
    SVECTOR         field_B40;      /* 0xB40 */
    SVECTOR         field_B48;      /* 0xB48 */
    int             field_B50;      /* 0xB50 */
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
    int             field_B94;      /* 0xB94 */
    int             field_B98;      /* 0xB98 */
    int             field_B9C;      /* 0xB9C */
    short           field_BA0;      /* 0xBA0 */
    short           field_BA2;      /* 0xBA2 */
    char            pad_BA4[0xC00 - 0xBA4];
} Work;

typedef struct _ZakoActor
{
    char            pad_0[0xAE8];
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xB28 - 0xAEA];
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB64 - 0xB2C];
    int             field_B64;      /* 0xB64 */
    char            pad_B68[0xB90 - 0xB68];
    int             field_B90;      /* 0xB90 */
} ZakoActor;

typedef struct _ZakoComEntry
{
    int             field_0;        /* 0x00 */
    int             field_4;        /* 0x04 */
    int             field_8;        /* 0x08 */
    ZakoActor      *field_C;        /* 0x0C - zako actor work */
} ZakoComEntry;                     /* 0x10 */

typedef struct _A4_INNER_STRUCT
{
    unsigned short field_00;    //0x00
    unsigned short field_02;    //0x02
} A4_INNER_STRUCT;

typedef struct _A4_STRUCT
{
    unsigned short  map_id;      //0x00
    unsigned short  n_entry;     //0x02
    A4_INNER_STRUCT field_04[8]; //0x04
} A4_STRUCT;

typedef struct _ZakoComMgr
{
    int             field_0;        /* 0x00 */
    int             field_4;        /* 0x04 */
    int             count;          /* 0x08 */
    int             field_C;        /* 0x0C */
    int             field_10;       /* 0x10 */
    int             field_14;       /* 0x14 */
    int             field_18;       /* 0x18 */
    int             field_1C;       /* 0x1C */
    int             field_20;       /* 0x20 */
    int             field_24;       /* 0x24 */
    int             field_28;       /* 0x28 */
    SVECTOR         field_2C;       /* 0x2C */
    short           field_34;       /* 0x34 */
    short           field_36;       /* 0x36 */
    short           field_38[4];    /* 0x38 */
    int             field_40[8];    /* 0x40 */
    int             field_60;       /* 0x60 */
    MAP            *field_64;       /* 0x64 */
    A4_STRUCT       field_68;       /* 0x68 */
    ZakoComEntry    entries[8];     /* 0x8C - 0x10C */
    int             field_10C;      /* 0x10C */
    int             field_110;      /* 0x110 */
    int             field_114;      /* 0x114 */
    int             field_118;      /* 0x118 */
    int             field_11C;      /* 0x11C */
    int             field_120;      /* 0x120 */
    int             field_124[8];   /* 0x124 */
    int             field_144;      /* 0x144 */
} ZakoComMgr;

typedef struct _TOP
{
    int mode;
    int alert;
} TOP;

extern TOP s03d_dword_800DC2E8;
extern int s03d_dword_800DC310;
#define ZAKOCOM_MGR ((ZakoComMgr *)&s03d_dword_800DC310)

#endif // _S03D_ZAKO_H
