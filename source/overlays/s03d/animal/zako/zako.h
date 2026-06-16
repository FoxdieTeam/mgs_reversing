#ifndef _S03D_ZAKO_H
#define _S03D_ZAKO_H

#include "common.h"
#include "game/game.h"
#include "libdg/libdg.h"

typedef struct _Work
{
    GV_ACT          actor;          /* 0x000 */
    CONTROL         control;        /* 0x020 */
    OBJECT          field_9C;       /* 0x09C */
    OBJECT          field_180;      /* 0x180 */
    char            pad_264[0x724 - 0x264];
    SVECTOR         field_724;      /* 0x724 */
    char            pad_72C[0x734 - 0x72C];
    short           field_734;      /* 0x734 */
    char            pad_736[0x748 - 0x736];
    short           field_748;      /* 0x748 */
    char            pad_74A[0x750 - 0x74A];
    short           field_750;      /* 0x750 */
    char            pad_752[0x754 - 0x752];
    short           field_754;      /* 0x754 */
    char            pad_756[0x75C - 0x756];
    short           field_75C;      /* 0x75C */
    char            pad_75E[0x8C8 - 0x75E];
    int             field_8C8;      /* 0x8C8 */
    int             field_8CC;      /* 0x8CC */
    char            pad_8D0[0x8D4 - 0x8D0];
    SVECTOR         field_8D4;      /* 0x8D4 */
    int             field_8DC;      /* 0x8DC */
    short           field_8E0;      /* 0x8E0 */
    short           field_8E2;      /* 0x8E2 */
    short           field_8E4;      /* 0x8E4 */
    char            pad_8E6[0x8E8 - 0x8E6];
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
    int             field_990;      /* 0x990 */
    int             field_994;      /* 0x994 */
    short           field_998;      /* 0x998 */
    short           field_99A;      /* 0x99A */
    short           field_99C;      /* 0x99C */
    short           field_99E;      /* 0x99E */
    int             field_9A0;      /* 0x9A0 */
    int             field_9A4;      /* 0x9A4 */
    int             field_9A8;      /* 0x9A8 */
    char            pad_9AC[0xAA8 - 0x9AC];
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
    signed char     field_B08;      /* 0xB08 */
    char            pad_B09[0xB0B - 0xB09];
    signed char     field_B0B;      /* 0xB0B */
    unsigned char   field_B0C[0xB14 - 0xB0C];   /* 0xB0C */
    short           field_B14;      /* 0xB14 */
    short           field_B16;      /* 0xB16 */
    char            pad_B18[0xB20 - 0xB18];
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
    char            pad_B50[0xB58 - 0xB50];
    int             field_B58;      /* 0xB58 */
    int             field_B5C;      /* 0xB5C */
    int             field_B60;      /* 0xB60 */
    int             field_B64;      /* 0xB64 */
    SVECTOR         field_B68;      /* 0xB68 */
    int             field_B70;      /* 0xB70 */
    char            pad_B74[0xB90 - 0xB74];
    int             field_B90;      /* 0xB90 */
    unsigned short  field_B94;      /* 0xB94 */
    char            pad_B96[0xBA0 - 0xB96];
    short           field_BA0;      /* 0xBA0 */
    char            pad_BA2[0xC00 - 0xBA2];
} Work;

#endif // _S03D_ZAKO_H
