#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "../s03e/Game/evpanel.h"
#include "../s00a/Enemy/command.h"
#include "../s00a/Enemy/watcher.h"
#include "../s00a/Thing/emitter.h"
#include "../s16b/Enemy/wall.h"
#include "Takabe/dummy_wl.h"
#include "../s02c/Takabe/ir_cens.h"
#include "Takabe/dummy_fl.h"
#include "../d11c/Game/lamp.h"
#include "../s16b/Enemy/asioto.h"
#include "../s16b/Takabe/fadeio.h"
#include "../s00a/Takabe/cat_in.h"
#include "Game/vibrate.h"
#include "../s16b/Takabe/dymc_seg.h"

GCL_ActorTableEntry s04aOverlayCharas[] = 
{
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_EMITTER, NewEmitter_800C3E50 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_DUMMY_WALL, NewDummyWall_800D7384 },
    { CHARA_INFRARED_CENSOR, NewIrCens_800DA66C },
    { CHARA_DUMMY_FLOOR, NewDummyFloor_800D6BF8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_VIBRATE, (TGCL_ActorCreateFn)vibrate_init_8005D508 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { NULL, NULL }
};
