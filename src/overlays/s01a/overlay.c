#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "Anime/animeconv/anime.h"
#include "Game/tobcnt.h"
#include "../s03e/chara/others/motse.h"
#include "Game/cancel.h"
#include "../s00a/Takabe/camshake.h"
#include "Game/vibrate.h"
#include "../d11c/Takabe/gas_efct.h"
#include "../s00a/chara/snake/breath.h"
#include "../s00a/Takabe/env_snd.h"
#include "../s00a/Takabe/cat_in.h"
#include "animal/doll/doll.h"
#include "Takabe/tracktrp.h"
#include "../s16b/Takabe/dymc_seg.h"
#include "../s00a/Enemy/asiato.h"
#include "../s16b/Enemy/asioto.h"
#include "Enemy/camera.h"
#include "../s00a/Takabe/cinema.h"
#include "../s00a/Takabe/pad_demo.h"
#include "../s00a/Enemy/command.h"
#include "../s00a/Enemy/watcher.h"
#include "Thing/sphere.h"
#include "../s00a/Enemy/smoke.h"
#include "Okajima/blink_tx.h"
#include "Enemy/object.h"
#include "Enemy/searchli.h"
#include "Thing/snow.h"
#include "../s16b/Enemy/wall.h"
#include "../s16b/Takabe/fadeio.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_TOBCNT, NewTobcnt_800C4BC8 },
    { CHARA_MOTION_SEQUENCE, NewMotse_800C5944 },
    { CHARA_CANCEL, NewCancel_800C3FFC },
    { CHARA_CAMERA_SHAKE, NewCameraShake_800DF6AC },
    { CHARA_VIBRATE, (NEWCHARA)vibrate_init_8005D508 },
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
