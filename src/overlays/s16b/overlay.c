#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "Enemy/wall.h"
#include "Enemy/asioto.h"
#include "Takabe/fadeio.h"

GV_ACT *NewShakemdl_800C54E8(int name, int where, int argc, char **argv);
GV_ACT *NewSepia_800C4F9C(int name, int where, int argc);
GV_ACT *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv);

CHARA _StageCharacterEntries[] =
{
    { 0xBA52, NewShakemdl_800C54E8 },
    { 0xEC77, NewWall_800C3718 },
    { 0x92BC, NewAsioto_800C3E08 },
    { 0xA12E, NewFadeIo_800C42BC },
    { 0xB103, NewDymcSeg_800C4BCC },
    { 0x0003, NewFadeIo_800C4224 },
    { 0x0004, NewFadeIo_800C4224 },
    { 0x001F, (NEWCHARA)NewSepia_800C4F9C },
    { 0, 0 }
};
