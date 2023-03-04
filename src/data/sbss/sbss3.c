#include "linker.h"
#include "Menu/menuman.h"
#include "map/map.h"

int SECTION(".sbss") gTargets_down_count_800ABA68;

int SECTION(".sbss") gTargets_up_count_800ABA6C;

int     SECTION(".sbss") dword_800ABA70;
int     SECTION(".sbss") dword_800ABA74;
int     SECTION(".sbss") dword_800ABA78[2];
short   SECTION(".sbss") GM_RadarMode_800ABA80;
short   SECTION(".sbss") word_800ABA82;
int     SECTION(".sbss") dword_800ABA84;
SVECTOR SECTION(".sbss") svec_800ABA88;
int     SECTION(".sbss") dword_800ABA90;
int     SECTION(".sbss") dword_800ABA94;

int SECTION(".sbss") GM_CameraShakeOffset_800ABA98;
int SECTION(".sbss") GM_event_camera_flag_800ABA9C;

map_record* SECTION(".sbss") pHzdIter_800ABAA0;

int SECTION(".sbss") N_StageObjs_800ABAA4;
int SECTION(".sbss") gMapCount_800ABAA8;
int SECTION(".sbss") gMapsChanged_800ABAAC;

int SECTION(".sbss") fc_rt_800ABAB0;
int SECTION(".sbss") mt_rt1_800ABAB4;
int SECTION(".sbss") mt_rt2_800ABAB8;
int SECTION(".sbss") fc_cnt_800ABABC;
int SECTION(".sbss") mt_count_800ABAC0;

int SECTION(".sbss") dword_800ABAC4;

struct Menu_rpk_item *SECTION(".sbss") gRadar_rpk_800ABAC8;

int SECTION(".sbss") dword_800ABACC;
int SECTION(".sbss") dword_800ABAD0;
int SECTION(".sbss") dword_800ABAD4;
