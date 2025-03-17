#include "common.h"
#include "charadef.h"

#include "Game/vibrate.h"
#include "../_shared/Game/pad.h"
#include "../_shared/chara/others/motse.h"
#include "../_shared/chara/others/intr_cam.h"
#include "../_shared/Takabe/gas_efct.h"
#include "../_shared/Takabe/shakemdl.h"
#include "../_shared/Takabe/cat_in.h"
#include "../_shared/Takabe/fadeio.h"
#include "../_shared/Takabe/put_obj.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Enemy/asioto.h"
#include "../_shared/Takabe/wsurface.h"
#include "../_shared/Enemy/command.h"
#include "../_shared/Enemy/watcher.h"
#include "../_shared/Takabe/wt_area.h"
#include "../_shared/Okajima/bubble_s.h"
#include "../_shared/Takabe/rsurface.h"
#include "../_shared/Enemy/camera.h"
#include "../_shared/Game/lamp.h"
#include "../_shared/Takabe/o2_damge.h"
#include "../_shared/Takabe/ir_cens.h"
#include "../_shared/Takabe/gasdamge.h"
#include "../_shared/Game/evpanel.h"
#include "../_shared/Takabe/shuter.h"

CHARA _StageCharacterEntries[] = 
{
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { CHARA_INTR_CAM, NewIntrudeCamera },
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
    { CHARA_WT_AREA, NewWaterArea_800DACCC },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_INFRARED_SENSOR, NewIrCens_800DA66C },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_GAS_DAMAGE, NewGasDamage_800E14E8 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_SHUTER, NewShuter_800DFB44 },
    { 0, NULL }
};
