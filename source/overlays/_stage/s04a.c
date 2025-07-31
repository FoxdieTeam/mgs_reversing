#include "common.h"
#include "charadef.h"

#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/command.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/enemy/watcher.h"
#include "../_shared/game/evpanel.h"
#include "../_shared/game/lamp.h"
#include "game/vibrate.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/takabe/dummy_fl.h"
#include "../_shared/takabe/dummy_wl.h"
#include "../_shared/takabe/dymc_seg.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/takabe/ir_cens.h"
#include "../_shared/thing/emitter.h"

CHARA _StageCharacterEntries[] = 
{
    { CHARA_ELEVATOR_PANEL, NewEvPanel },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_DMYWALL, NewDummyWall_800D7384 },
    { CHARA_CENSOR, NewIrCens_800DA66C },
    { CHARA_DMYFLOOR, NewDummyFloor_800D6BF8 },
    { CHARA_LAMP, NewLamp },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { 0, NULL }
};
