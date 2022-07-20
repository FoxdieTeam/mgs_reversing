#ifndef _TARGET_H_
#define _TARGET_H_

#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

typedef struct GM_Target
{
    short field_0_flags;
    short field_2;
    unsigned short field_4;
    short field_6_flags;
    SVECTOR field_8_vec;
    short field_10;
    short field_12;
    short field_14;
    short field_16;
    int field_18;
    int field_1C;
    MATRIX *field_20;
    short field_24;
    short field_26_hp;
    short field_28;
    short field_2A;
    short field_2C_vec;
    short field_2E;
    int field_30;
    short field_34_vec;
    short field_36;
    short field_38;
    short field_3A;
    short field_3C;
    short field_3E;
    short field_40;
    short field_42;
    int field_44;
} GM_Target;

#endif // _TARGET_H_
