#include "common.h"
#include "charadef.h"

#include "anime/animconv/anime.h"
#include "../_shared/takabe/ripples.h"
#include "../_shared/game/pad.h"
#include "game/vibrate.h"
#include "../_shared/chara/snake/breath.h"
#include "../_shared/takabe/env_snd.h"
#include "../_shared/takabe/camshake.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/pad_demo.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/asiato.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/takabe/shakemdl.h"
#include "../_shared/okajima/pato_lmp.h"
#include "../_shared/enemy/command.h"
#include "../_shared/takabe/wt_area.h"
#include "../_shared/enemy/watcher.h"
#include "../_shared/enemy/smoke.h"
#include "../_shared/thing/emitter.h"
#include "../_shared/takabe/elevator.h"
#include "../_shared/okajima/mouse.h"
#include "../_shared/takabe/rsurface.h"
#include "../_shared/takabe/telop.h"
#include "../_shared/okajima/bubble_s.h"
#include "../_shared/takabe/o2_damge.h"
#include "../_shared/takabe/fadeio.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAMERA_SHAKE, NewCameraShake },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, NewPadDemo_800DCFD4 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WT_AREA, NewWaterArea },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_ELEVATOR, NewElevator_800D9F30 },
    { CHARA_MOUSE, NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_TELOP_SET, NewTelopSet_800DDB34 },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
