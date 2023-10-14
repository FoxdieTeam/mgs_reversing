#include "libgcl/libgcl.h"
#include "Enemy/wall.h"
#include "libgcl/hash.h"

GV_ACT *NewAsioto_800C3E08(int name, int where, int argc, char **argv);
GV_ACT *NewShakemdl_800C54E8(int name, int where, int argc, char **argv);
GV_ACT *NewFadeIo_800C42BC(int name, int where, int argc, char **argv);
GV_ACT *NewFadeIo_800C4224(int name, int where, int argc, char **argv);
GV_ACT *NewSepia_800C4F9C(int name, int where, int argc);
GV_ACT *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv);

GCL_ActorTableEntry s16bOverlayCharas[] =
{
    { 0xBA52, NewShakemdl_800C54E8 },
    { 0xEC77, NewWall_800C3718 },
    { 0x92BC, NewAsioto_800C3E08 },
    { 0xA12E, NewFadeIo_800C42BC },
    { 0xB103, NewDymcSeg_800C4BCC },
    { 0x0003, NewFadeIo_800C4224 },
    { 0x0004, NewFadeIo_800C4224 },
    { 0x001F, (TGCL_ActorCreateFn)NewSepia_800C4F9C },
    { 0, 0 }
};

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = "wall.c";

// Enemy/asioto.c
const char aAsiotoSeSetErr[] = " asioto se set err \n";
const char aAsiotoSeNoiseSetErr[] = " asioto se noise set err \n";
const char aMigiSodesuri[] = " migi sodesuri %d \n";
const char aAsiotoC[] = "asioto.c";

// Takabe/fadeio.c
unsigned short fadeio_msgs[] = {HASH_KILL, 0x71F1};
const char aFadeioC[] = "fadeio.c";
