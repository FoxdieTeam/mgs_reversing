#include "menuman.h"

extern menu_0x14 stru_800BDA48[2];

void menu_800470B4(int idx, menu_chara_struct *pStru, int chara, int code, int faceUnk, int taskWup)
{
    stru_800BDA48[idx].field_0_bUnknown = 1;
    stru_800BDA48[idx].field_10_pCharaStru = pStru;
    stru_800BDA48[idx].field_4_chara = chara;
    stru_800BDA48[idx].field_8_code = code;
    stru_800BDA48[idx].field_C = faceUnk;
    stru_800BDA48[idx].field_2_bTaskWup = taskWup;
}
