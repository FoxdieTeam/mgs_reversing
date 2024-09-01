#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "../s16b/Enemy/asioto.h"
#include "../s00a/Takabe/cinema.h"
#include "../s01a/animal/doll/doll.h"
#include "../s12c/Takabe/findtrap.h"
#include "../s16b/Enemy/wall.h"
#include "../s03e/Game/evpanel.h"
#include "../d03a/Okajima/uji.h"
#include "../s16b/Takabe/dymc_seg.h"
#include "../d11c/Game/lamp.h"
#include "../s00a/Takabe/mosaic.h"
#include "../s03e/Okajima/guncame.h"
#include "../s16b/Takabe/fadeio.h"
#include "../d11c/Takabe/gas_efct.h"
#include "Okajima/hiyoko.h"
#include "Game/point.h"
#include "../s00a/Game/pad.h"
#include "../s03e/chara/others/intr_cam.h"
#include "../s00a/Takabe/cat_in.h"
#include "../s03e/chara/others/motse.h"
#include "Okajima/bullet.h"
#include "../d11c/Enemy/demokage.h"
#include "../d01a/Takabe/focus.h"
#include "../d01a/Okajima/blur.h"
#include "../s16b/Takabe/sepia.h"
#include "../d03a/Okajima/red_alrt.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../d03a/Okajima/blurpure.h"
#include "../s00a/Takabe/telop.h"

CHARA _StageCharacterEntries[] = 
{
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_DOLL, NewDoll_800DCD78 },
    { CHARA_FIND_TRAP, NewFindTrap_800D77DC },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_MOSAIC, NewMosaic_800DCABC },
    { CHARA_GUNCAME, NewGunCame_800C9190 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_HIYOKO, NewHiyoko_800D018C },
    { CHARA_POINT, NewPoint_800C5AB4 },
    { CHARA_PAD_CBF8, NewPad_800C37EC },
    { CHARA_INTR_CAM, NewIntrCam_800C5748 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_MOTION_SEQUENCE, NewMotse_800C5944 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_BULLET, (NEWCHARA)NewBulletEx_80076708 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_SUB_EFCT, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_SEPIA, (NEWCHARA)NewSepia_800C5214 },
    { CHARA_RED_ALERT, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_GAS_EFCT, (NEWCHARA)NewGasEffect_800C4EF8 },
    { CHARA_FALL_SPL, (NEWCHARA)NewBlurPure_800C54D4 },
    { CHARA_UNKNOWN_004C, (NEWCHARA)NewTelop2_800DDC60 },
    { 0, NULL }
};
