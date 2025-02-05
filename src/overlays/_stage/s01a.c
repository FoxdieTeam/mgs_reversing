#include "common.h"
#include "charadef.h"

#include "Anime/animconv/anime.h"
#include "../_shared/Game/tobcnt.h"
#include "../_shared/chara/others/motse.h"
#include "../_shared/Game/cancel.h"
#include "../_shared/Takabe/camshake.h"
#include "Game/vibrate.h"
#include "../_shared/Takabe/gas_efct.h"
#include "../_shared/chara/snake/breath.h"
#include "../_shared/Takabe/env_snd.h"
#include "../_shared/Takabe/cat_in.h"
#include "../_shared/animal/doll/doll.h"
#include "../_shared/Takabe/tracktrp.h"
#include "../_shared/Takabe/dymc_seg.h"
#include "../_shared/Enemy/asiato.h"
#include "../_shared/Enemy/asioto.h"
#include "../_shared/Enemy/camera.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Takabe/pad_demo.h"
#include "../_shared/Enemy/command.h"
#include "../_shared/Enemy/watcher.h"
#include "../_shared/Thing/sphere.h"
#include "../_shared/Enemy/smoke.h"
#include "../_shared/Okajima/blink_tx.h"
#include "../_shared/Enemy/object.h"
#include "../_shared/Enemy/searchli.h"
#include "../_shared/Thing/snow.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Takabe/fadeio.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_TOBCNT, NewTobcnt_800C4BC8 },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { CHARA_CANCEL, NewCancel_800C3FFC },
    { CHARA_CAMERA_SHAKE, NewCameraShake_800DF6AC },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_DOLL, NewDoll_800DCD78 },
    { CHARA_TRACK_TRAP, NewTracktrp_800E1DB0 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, NewPadDemo_800DCFD4 },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SPHERE, NewSphere_800C69C0 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_BLINK_TX, NewBlinkTx_800DECD8 },
    { CHARA_OBJECT, NewObjectChara_800DA3A4 },
    { CHARA_SEARCH_LIGHT, NewSearchlight_800D92BC },
    { CHARA_SNOW, NewSnow_800C6058 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
