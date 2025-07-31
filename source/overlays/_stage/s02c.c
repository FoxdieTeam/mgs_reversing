#include "common.h"
#include "charadef.h"

#include "../_shared/chara/others/intr_cam.h"
#include "../_shared/chara/others/motse.h"
#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/camera.h"
#include "../_shared/enemy/command.h"
#include "../_shared/enemy/kiken.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/enemy/watcher.h"
#include "../_shared/game/evpanel.h"
#include "../_shared/game/lamp.h"
#include "game/vibrate.h"
#include "../_shared/okajima/bub_d_sn.h"
#include "../_shared/okajima/bubble_s.h"
#include "../_shared/takabe/camshake.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/takabe/gas_efct.h"
#include "../_shared/takabe/gasdamge.h"
#include "../_shared/takabe/ir_cens.h"
#include "../_shared/takabe/o2_damge.h"
#include "../_shared/takabe/put_obj.h"
#include "../_shared/takabe/rsurface.h"
#include "../_shared/takabe/shakemdl.h"
#include "../_shared/takabe/shuter.h"
#include "../_shared/takabe/wsurface.h"
#include "../_shared/takabe/wt_area.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { CHARA_INTR_CAM, NewIntrudeCamera },
    { CHARA_BUB_D_SN, NewBubbleDisplayScene_800D90B4 },
    { CHARA_KIKEN, NewKiken_800D6D24 },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_CAMERA_SHAKE, NewCameraShake },
    { CHARA_CINEMA, NewCinemaScreenSet },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_PUT_OBJECT, NewPutObject_800E25C0 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_WSURFACE, NewWsurface_800DB9BC },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_WT_AREA, NewWaterArea },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_LAMP, NewLamp },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_CENSOR, NewIrCens_800DA66C },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_GAS_DAMAGE, NewGasDamage_800E14E8 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel },
    { CHARA_SHUTER, NewShuter_800DFB44 },
    { 0, NULL }
};
