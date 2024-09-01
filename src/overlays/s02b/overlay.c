#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "Game/vibrate.h"
#include "../s00a/Game/pad.h"
#include "../s03e/chara/others/motse.h"
#include "../s03e/chara/others/intr_cam.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../s02c/Takabe/put_obj.h"
#include "../s16b/Enemy/wall.h"
#include "../s16b/Takabe/shakemdl.h"
#include "../s02a/Okajima/ductmous.h"
#include "../s00a/Takabe/cat_in.h"
#include "../s16b/Takabe/fadeio.h"
#include "../s16b/Enemy/asioto.h"
#include "../s00a/Takabe/cinema.h"
#include "../s00a/Takabe/wt_area.h"
#include "../s00a/Okajima/bubble_s.h"
#include "../s00a/Takabe/rsurface.h"
#include "../s03e/Game/evpanel.h"
#include "../s00a/Enemy/command.h"
#include "../s00a/Enemy/watcher.h"
#include "../s02c/Takabe/shuter.h"
#include "../s01a/Enemy/camera.h"
#include "../d11c/Game/lamp.h"
#include "../s00a/Takabe/o2_damge.h"
#include "../d11c/Enemy/demokage.h"
#include "../d01a/Takabe/focus.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../d03a/Okajima/blurpure.h"
#include "../d01a/Kojo/famaslit.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_VIBRATE, (NEWCHARA)vibrate_init_8005D508 },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_MOTION_SEQUENCE, NewMotse_800C5944 },
    { CHARA_INTR_CAM, NewIntrCam_800C5748 },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_PUT_OBJECT, NewPutObject_800E25C0 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_DUCTMOUS, NewDuctmouse_800DACC8 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_WT_AREA, NewWaterArea_800DACCC },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SHUTER_03D9, NewShuter_800DFB44 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_SUB_EFCT, NewFocus_800CEFF8 },
    { CHARA_GAS_EFCT, (NEWCHARA)NewGasEffect_800C4EF8 },
    { CHARA_FALL_SPL, (NEWCHARA)NewBlurPure_800C54D4 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
