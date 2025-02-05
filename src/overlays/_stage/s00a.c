#include "common.h"
#include "charadef.h"

#include "Anime/animeconv/anime.h"
#include "../_shared/Takabe/ripples.h"
#include "../_shared/Game/pad.h"
#include "Game/vibrate.h"
#include "../_shared/chara/snake/breath.h"
#include "../_shared/Takabe/env_snd.h"
#include "../_shared/Takabe/camshake.h"
#include "../_shared/Takabe/cat_in.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Takabe/pad_demo.h"
#include "../_shared/Takabe/dymc_seg.h"
#include "../_shared/Enemy/asioto.h"
#include "../_shared/Enemy/asiato.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Takabe/shakemdl.h"
#include "../_shared/Okajima/pato_lmp.h"
#include "../_shared/Enemy/command.h"
#include "../_shared/Takabe/wt_area.h"
#include "../_shared/Enemy/watcher.h"
#include "../_shared/Enemy/smoke.h"
#include "../_shared/Thing/emitter.h"
#include "../_shared/Takabe/elevator.h"
#include "../_shared/Okajima/mouse.h"
#include "../_shared/Takabe/rsurface.h"
#include "../_shared/Takabe/telop.h"
#include "../_shared/Okajima/bubble_s.h"
#include "../_shared/Takabe/o2_damge.h"
#include "../_shared/Takabe/fadeio.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAMERA_SHAKE, NewCameraShake_800DF6AC },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, NewPadDemo_800DCFD4 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WT_AREA, NewWaterArea_800DACCC },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter_800C3E50 },
    { CHARA_ELEVATOR, NewElevator_800D9F30 },
    { CHARA_MOUSE, NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_TELOP, NewTelopSet_800DDB34 },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
