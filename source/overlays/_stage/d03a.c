#include "common.h"
#include "charadef.h"

#include "thing/door.h"
#include "../_shared/okajima/uji.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/enemy/demokage.h"
#include "../_shared/takabe/sepia.h"
#include "../_shared/okajima/red_alrt.h"
#include "../_shared/takabe/gas_efct.h"
#include "../_shared/okajima/blurpure.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_DOOR, NewDoor },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_SEPIA_0028, (NEWCHARA)NewSepia_800C5214 },
    { CHARA_RED_ALERT_0037, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_GAS_EFCT, (NEWCHARA)NewGasEffect_800C4EF8 },
    { CHARA_BLURPURE, (NEWCHARA)NewBlurPure_800C54D4 },
    { 0, NULL }
};
