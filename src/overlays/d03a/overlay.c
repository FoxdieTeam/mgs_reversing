#include "common.h"
#include "charadef.h"

#include "Thing/door.h"
#include "Okajima/uji.h"
#include "../s00a/Takabe/cinema.h"
#include "../s16b/Takabe/fadeio.h"
#include "../d11c/Enemy/demokage.h"
#include "../s16b/Takabe/sepia.h"
#include "Okajima/red_alrt.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../d03a/Okajima/blurpure.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_DOOR, NewDoor },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_SEPIA, (NEWCHARA)NewSepia_800C5214 },
    { CHARA_RED_ALERT, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_GAS_EFCT, (NEWCHARA)NewGasEffect_800C4EF8 },
    { CHARA_FALL_SPL, (NEWCHARA)NewBlurPure_800C54D4 },
    { 0, NULL }
};
