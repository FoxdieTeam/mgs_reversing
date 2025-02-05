#include "common.h"
#include "charadef.h"

#include "../_shared/Game/evpanel.h"
#include "../_shared/Enemy/command.h"
#include "../_shared/Enemy/watcher.h"
#include "../_shared/Thing/emitter.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Takabe/dummy_wl.h"
#include "../_shared/Takabe/ir_cens.h"
#include "../_shared/Takabe/dummy_fl.h"
#include "../_shared/Game/lamp.h"
#include "../_shared/Enemy/asioto.h"
#include "../_shared/Takabe/fadeio.h"
#include "../_shared/Takabe/cat_in.h"
#include "Game/vibrate.h"
#include "../_shared/Takabe/dymc_seg.h"

CHARA _StageCharacterEntries[] = 
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
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { 0, NULL }
};
