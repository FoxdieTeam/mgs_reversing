#include "libgcl/libgcl.h"

GV_ACT *NewAsioto_800C3E08(int name, int where, int argc, char **argv);
GV_ACT *s16b_800C54E8(int name, int where, int argc, char **argv);
GV_ACT *NewWall_800C3718(int name, int where, int argc, char **argv);
GV_ACT *NewFadeIo_800C42BC(int name, int where, int argc, char **argv);
GV_ACT *NewFadeIo_800C4224(int name, int where, int argc, char **argv);
GV_ACT *s16b_800C4F9C(int name, int where, int argc, char **argv);
GV_ACT *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv);

GCL_ActorTableEntry s16bOverlayCharas[] =
{
    { 0xBA52, s16b_800C54E8 },
    { 0xEC77, NewWall_800C3718 },
    { 0x92BC, NewAsioto_800C3E08 },
    { 0xA12E, NewFadeIo_800C42BC },
    { 0xB103, NewDymcSeg_800C4BCC },
    { 0x0003, NewFadeIo_800C4224 },
    { 0x0004, NewFadeIo_800C4224 },
    { 0x001F, s16b_800C4F9C },
    { 0, 0 }
};

int s16b_dword_800C3250 = 0x71F13223;
int s16b_dword_800C3254 = 0x006BD182;
int s16b_dword_800C3258 = 0x00E20300;
int s16b_dword_800C325C = 0x00020100;
int s16b_dword_800C3260 = 0x00C40300;
int s16b_dword_800C3264 = 0x00020100;
int s16b_dword_800C3268 = 0x00E20300;
int s16b_dword_800C326C = 0x00020100;
int s16b_dword_800C3270 = 0x00C40300;
int s16b_dword_800C3274 = 0x00020100;


const char s16b_dword_800C5800[] = "destroy\n";
const char s16b_dword_800C580C[] = "box_01";
const char s16b_dword_800C5814[] = "dbx1";
const char s16b_dword_800C581C[] = "dbx2";
const char s16b_dword_800C5824[] = "wall.c";
const char s16b_dword_800C582C[] = " asioto se set err \n";
const char s16b_dword_800C5844[] = " asioto se noise set err \n";
const char s16b_dword_800C5860[] = " migi sodesuri %d \n";
const char aAsioto_800C5874[] = "asioto.c";
const char aFadeIo_800C5880[] = "fadeio.c";
const char s16b_dword_800C588C[] = "dymc_seg.c";
const char s16b_dword_800C5898[] = "sepia.c";
const char s16b_dword_800C58A0[] = "shakemdl.c";
const char s16b_dword_800C58AC[] = {0x0, 0x0, 0x0, 0x0};
const char s16b_dword_800C58B0[] = {0x0, 0x0, 0x0, 0x0};
