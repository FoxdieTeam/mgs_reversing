#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "Thing/door.h"
#include "Okajima/uji.h"
#include "../s00a/Takabe/cinema.h"
#include "../s16b/Takabe/fadeio.h"
#include "../d11c/Enemy/demokage.h"
#include "../s16b/Takabe/sepia.h"
#include "Okajima/red_alrt.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../d03a/Okajima/blurpure.h"

GCL_ActorTableEntry d03aOverlayCharas[] =
{
    { CHARA_DOOR, NewDoor_8006FD00 },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (TGCL_ActorCreateFn)NewDemoKage_800C48A4 },
    { CHARA_SEPIA, (TGCL_ActorCreateFn)NewSepia_800C5214 },
    { CHARA_RED_ALERT, (TGCL_ActorCreateFn)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (TGCL_ActorCreateFn)RedAlert_800C4F48 },
    { CHARA_GAS_EFCT, (TGCL_ActorCreateFn)NewGasEffect_800C4EF8 },
    { CHARA_FALL_SPL, (TGCL_ActorCreateFn)NewBlurPure_800C54D4 },
    { NULL, NULL }
};
