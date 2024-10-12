#define __BSSDEFINE__

#include "common.h"
#include "chara/snake/sna_init.h"
#include "Menu/radio.h"

int SECTION(".sbss") dword_800ABB3C;

void *SECTION(".sbss") MENU_JimakuTextBody_800ABB40;

int SECTION(".sbss") dword_800ABB44;
int SECTION(".sbss") dword_800ABB48;

DATA_INFO *SECTION(".sbss") dataInfo_800ABB4C;

void *SECTION(".sbss") dword_800ABB50;
int SECTION(".sbss") dword_800ABB54;
int SECTION(".sbss") dword_800ABB58;
int SECTION(".sbss") dword_800ABB5C;

int SECTION(".sbss") mcd_last_check_800ABB60[2];
mem_card *SECTION(".sbss") mcd_last_file_800ABB68[2];

int SECTION(".sbss") dword_800ABB70;
SELECT_INFO *SECTION(".sbss") dword_800ABB74;
int SECTION(".sbss") dword_800ABB78;

RadioFileModeStru_800ABB7C *SECTION(".sbss") stru_800ABB7C;

int SECTION(".sbss") dword_800ABB80;
int SECTION(".sbss") dword_800ABB84;
SELECT_INFO *SECTION(".sbss") dword_800ABB88;
int SECTION(".sbss") dword_800ABB8C;
int SECTION(".sbss") dword_800ABB90;
int SECTION(".sbss") dword_800ABB94;

RadioCodecStru_800ABB98 *SECTION(".sbss") stru_800ABB98;

short SECTION(".sbss") word_800ABB9C;
short SECTION(".sbss") gRadioCodecFrequency_800ABB9E;

#ifndef VR_EXE
SnaInitWork *SECTION(".sbss") sna_800ABBA0;
#endif

int SECTION(".sbss") gSnaMoveDir_800ABBA4;
int SECTION(".sbss") dword_800ABBA8;
SVECTOR *SECTION(".sbss") dword_800ABBAC;
void *SECTION(".sbss") dword_800ABBB0;
int SECTION(".sbss") dword_800ABBB4;

#ifdef VR_EXE
int sna_800ABBA0_pad;
#endif
