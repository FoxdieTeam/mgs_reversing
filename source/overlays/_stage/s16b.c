#include "common.h"
#include "charadef.h"

#include "../_shared/Enemy/wall.h"
#include "../_shared/Enemy/asioto.h"
#include "../_shared/Takabe/fadeio.h"
#include "../_shared/Takabe/sepia.h"

void *NewShakemdl_800C54E8(int name, int where, int argc, char **argv);
void *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv);

CHARA _StageCharacterEntries[] =
{
    { 0xBA52, (NEWCHARA)NewShakemdl_800C54E8 },
    { 0xEC77, (NEWCHARA)NewWall_800C3718 },
    { 0x92BC, (NEWCHARA)NewAsioto_800C3E08 },
    { 0xA12E, (NEWCHARA)NewFadeIo_800C42BC },
    { 0xB103, (NEWCHARA)NewDymcSeg_800C4BCC },
    { 0x0003, (NEWCHARA)NewFadeIo_800C4224 },
    { 0x0004, (NEWCHARA)NewFadeIo_800C4224 },
    { 0x001F, (NEWCHARA)NewSepia_800C4F9C },
    { 0, NULL }
};
