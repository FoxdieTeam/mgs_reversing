#include "charadef.h"
#include "../s00a/Takabe/cinema.h"
#include "../s16b/Enemy/wall.h"
#include "../s01a/animal/doll/doll.h"
#include "../s16b/Takabe/dymc_seg.h"
#include "../s16b/Takabe/fadeio.h"
#include "../s16b/Enemy/asioto.h"
#include "../s01a/Enemy/camera.h"
#include "../d01a/Takabe/focus.h"
#include "../d01a/Okajima/blur.h"
#include "../s16b/Takabe/sepia.h"
#include "Okajima/smke_ln.h"
#include "../d03a/Okajima/red_alrt.h"
#include "Kojo/inverlt2.h"
#include "../d03a/Okajima/blurpure.h"

GV_ACT * NewSpark2_800CA714(MATRIX *world);
GV_ACT * NewSpark_80074564(MATRIX *pMatrix, int pCnt);

CHARA _StageCharacterEntries[] = 
{
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_DOLL, NewDoll_800DCD78 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_SUB_EFCT, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_SEPIA, (NEWCHARA)NewSepia_800C5214 },
    { CHARA_SMKE_LN, (NEWCHARA)NewSmokeLn_800CDFA4 },
    { CHARA_RED_ALERT, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_SPARK2, (NEWCHARA)NewSpark2_800CA714 },
    { CHARA_SPARK, (NEWCHARA)NewSpark_80074564 },
    { CHARA_INVERLT2, (NEWCHARA)NewInverlt2_800D0FF4 },
    { CHARA_FALL_SPL, (NEWCHARA)NewBlurPure_800C54D4 },
    { 0, NULL }
};
