#include "common.h"
#include "charadef.h"

#include "../_shared/enemy/asioto.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/takabe/sepia.h"

extern void *NewShakemdl_800C54E8();
extern void *NewDymcSeg_800C4BCC();

CHARA _StageCharacterEntries[] =
{
    { CHARA_SHAKE_MODEL, (NEWCHARA)NewShakemdl_800C54E8 },
    { CHARA_WALL, (NEWCHARA)NewWall_800C3718 },
    { CHARA_ASIOTO, (NEWCHARA)NewAsioto_800C3E08 },
    { CHARA_FADE_IN_OUT, (NEWCHARA)NewFadeIo_800C42BC },
    { CHARA_DYNAMIC_SEGMENT, (NEWCHARA)NewDymcSeg_800C4BCC },
    { CHARA_FADEIO_0003, (NEWCHARA)NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, (NEWCHARA)NewFadeIo_800C4224 },
    { CHARA_SEPIA_001F, (NEWCHARA)NewSepia_800C4F9C },
    { 0, NULL }
};
