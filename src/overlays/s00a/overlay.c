#include <stddef.h> // for NULL
#include "charadef.h"

#include "Anime/animeconv/anime.h"
#include "Takabe/ripples.h"
#include "Game/pad.h"
#include "Game/vibrate.h"
#include "chara/snake/breath.h"
#include "Takabe/env_snd.h"
#include "Takabe/camshake.h"
#include "Takabe/cat_in.h"
#include "Takabe/cinema.h"
#include "Takabe/pad_demo.h"
#include "../s16b/Takabe/dymc_seg.h"
#include "../s16b/Enemy/asioto.h"
#include "Enemy/asiato.h"
#include "../s16b/Enemy/wall.h"
#include "../s16b/Takabe/shakemdl.h"
#include "Okajima/pato_lmp.h"
#include "Enemy/command.h"
#include "Takabe/wt_area.h"
#include "Enemy/watcher.h"
#include "Enemy/smoke.h"
#include "Thing/emitter.h"
#include "Takabe/elevator.h"
#include "Okajima/mouse.h"
#include "Takabe/rsurface.h"
#include "Takabe/telop.h"
#include "Okajima/bubble_s.h"
#include "Takabe/o2_damge.h"
#include "../s16b/Takabe/fadeio.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_VIBRATE, (NEWCHARA)vibrate_init_8005D508 },
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
