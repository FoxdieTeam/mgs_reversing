#include "common.h"
#include "charadef.h"

#include "../_shared/animal/doll/doll.h"
#include "anime/animconv/anime.h"
#include "../_shared/chara/others/motse.h"
#include "../_shared/chara/snake/breath.h"
#include "../_shared/enemy/asiato.h"
#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/camera.h"
#include "../_shared/enemy/command.h"
#include "../_shared/enemy/object.h"
#include "../_shared/enemy/searchli.h"
#include "../_shared/enemy/smoke.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/enemy/watcher.h"
#include "../_shared/game/cancel.h"
#include "../_shared/game/tobcnt.h"
#include "game/vibrate.h"
#include "../_shared/okajima/blink_tx.h"
#include "../_shared/takabe/camshake.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/takabe/env_snd.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/takabe/gas_efct.h"
#include "../_shared/takabe/pad_demo.h"
#include "../_shared/takabe/tracktrp.h"
#include "../_shared/thing/snow.h"
#include "../_shared/thing/sphere.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_TOBCNT, NewToBeContinued },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { CHARA_CANCEL, NewCancel },
    { CHARA_CAMERA_SHAKE, NewCameraShake },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_DOLL, NewDoll_800DCD78 },
    { CHARA_TRACK_TRAP, NewTruckTrap },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIATOKUN, NewAsiatoKun_800D1A70 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CAMERA, NewCamera_800D67F8 },
    { CHARA_CINEMA, NewCinemaScreenSet },
    { CHARA_PAD_DEMO, NewPadDemo },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SPHERE, NewSphere },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_BLINK_TX, NewBlinkTx_800DECD8 },
    { CHARA_OBJECT, NewObjectChara_800DA3A4 },
    { CHARA_SEARCH_LIGHT, NewSearchlight_800D92BC },
    { CHARA_SNOW, NewSnow },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
