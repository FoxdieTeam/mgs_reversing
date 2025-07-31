#include "common.h"
#include "charadef.h"

#include "../_shared/animal/doll/doll.h"
#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/camera.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/kojo/inverlt2.h"
#include "../_shared/okajima/blur.h"
#include "../_shared/okajima/blurpure.h"
#include "../_shared/okajima/red_alrt.h"
#include "../_shared/okajima/smke_ln.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/takabe/focus.h"
#include "../_shared/takabe/sepia.h"

extern void *NewSpark2_800CA714();
extern void *NewSpark();

CHARA _StageCharacterEntries[] = 
{
    { CHARA_CINEMA, NewCinemaScreenSet },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_DOLL, NewDoll_800DCD78 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_CINEMA, NewCinemaScreenSet },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_FOCUS, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_SEPIA_0028, (NEWCHARA)NewSepia_800C5214 },
    { CHARA_SMKE_LN, (NEWCHARA)NewSmokeLn_800CDFA4 },
    { CHARA_RED_ALERT_0037, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_SPARK2, (NEWCHARA)NewSpark2_800CA714 },
    { CHARA_SPARK, (NEWCHARA)NewSpark },
    { CHARA_INVERLT2, (NEWCHARA)NewInverlt2_800D0FF4 },
    { CHARA_BLURPURE, (NEWCHARA)NewBlurPure_800C54D4 },
    { 0, NULL }
};
