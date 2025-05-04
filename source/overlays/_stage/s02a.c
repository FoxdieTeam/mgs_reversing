#include "common.h"
#include "charadef.h"

#include "../_shared/chara/others/motse.h"
#include "../_shared/chara/others/intr_cam.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/okajima/bub_d_sn.h"
#include "game/vibrate.h"
#include "../_shared/takabe/gas_efct.h"
#include "../_shared/takabe/put_obj.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/takabe/shakemdl.h"
#include "../_shared/okajima/ductmous.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/enemy/asioto.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/wt_area.h"
#include "../_shared/okajima/bubble_s.h"
#include "../_shared/takabe/rsurface.h"
#include "../_shared/game/evpanel.h"
#include "../_shared/enemy/command.h"
#include "../_shared/enemy/watcher.h"
#include "../_shared/enemy/camera.h"
#include "../_shared/game/lamp.h"
#include "../_shared/takabe/o2_damge.h"
#include "../_shared/enemy/demokage.h"
#include "../_shared/takabe/focus.h"
#include "../_shared/okajima/blur.h"
#include "../_shared/kojo/famaslit.h"

CHARA _StageCharacterEntries[] = 
{
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { CHARA_INTR_CAM, NewIntrudeCamera },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_BUB_D_SN, NewBubbleDisplayScene_800D90B4 },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_PUT_OBJECT, NewPutObject_800E25C0 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_DUCTMOUS, NewDuctmouse_800DACC8 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_WT_AREA, NewWaterArea },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_FOCUS, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
