#include "common.h"

const char s19b_dword_800DDD4C[] = {0xe4, 0xfd, 0xbe, 0x4};
const char s19b_dword_800DDD50[] = {'=', 0xfc, 0x0, 0x0};
const char s19b_dword_800DDD54[] = {0xac, 0x1, 'U', 0x2};
const char s19b_dword_800DDD58[] = {0xb6, 0x6, 0x0, 0x0};
const char s19b_dword_800DDD5C[] = {'O', 0xfd, 0xde, 0x3};
const char s19b_dword_800DDD60[] = {'Q', 0xfe, 0x0, 0x0};
const char s19b_dword_800DDD64[] = {0xcb, 0x1, 'o', 0x3};
const char s19b_a_800DDD68[] = ";";

int SECTION(".bss") s19b_dword_800DE5B0;
int SECTION(".bss") s19b_dword_800DE5B4;
int SECTION(".bss") s19b_dword_800DE5B8;
int SECTION(".bss") s19b_dword_800DE5BC;
int SECTION(".bss") s19b_dword_800DE5C0;
int SECTION(".bss") s19b_dword_800DE5C4;
typedef struct _JeepCamParams
{
    short field_0;
    short field_2;
    short field_4;
    short field_6;
    int   field_8;
    int   field_C;
    int   field_10;
    int   field_14;
    int   field_18;
    short field_1C[4];
} JeepCamParams; /* 0x24, at 0x800DE5C8 */

JeepCamParams SECTION(".bss") s19b_JeepCamParams_800DE5C8;
int SECTION(".bss") s19b_dword_800DE5EC;
