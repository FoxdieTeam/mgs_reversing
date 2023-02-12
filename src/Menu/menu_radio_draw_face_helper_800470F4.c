#include "menuman.h"
#include "mts/mts_new.h"

extern menu_0x14 stru_800BDA48[2];

void  menu_radio_draw_face_helper_helper_80046DF4(int idx, menu_chara_struct *a2, int chara, int code, int a5);

void menu_radio_draw_face_helper_800470F4(int idx)
{
  if (stru_800BDA48[idx].field_0_bUnknown)
  {
    menu_radio_draw_face_helper_helper_80046DF4(idx, stru_800BDA48[idx].field_10_pCharaStru, stru_800BDA48[idx].field_4_chara, stru_800BDA48[idx].field_8_code, stru_800BDA48[idx].field_C);
    if (!stru_800BDA48[idx].field_8_code)
    {
      if (stru_800BDA48[idx].field_2_bTaskWup)
      {
        mts_wup_tsk_8008A540(6);
        stru_800BDA48[idx].field_2_bTaskWup = 0;
      }
    }
    stru_800BDA48[idx].field_0_bUnknown = 0;
  }
}
