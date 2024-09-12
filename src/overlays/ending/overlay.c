#include "common.h"
#include "charadef.h"

CHARA _StageCharacterEntries[] =
{
    { 0x02C4, (NEWCHARA)0x800C6CA0 },
    { 0x3453, (NEWCHARA)0x800C4F34 },
    { 0x7A05, (NEWCHARA)0x800C9E6C },
    { 0x73EA, (NEWCHARA)0x800C5F7C },
    { 0x0003, (NEWCHARA)0x800C8F18 },
    { 0x0004, (NEWCHARA)0x800C8F18 },
    { 0x000F, (NEWCHARA)0x800C7864 },
    { 0x0010, (NEWCHARA)0x800C70C0 },
    { 0x001C, (NEWCHARA)0x800CA3A4 },
    { 0x0021, (NEWCHARA)0x800CAAA8 },
    { 0x0025, (NEWCHARA)0x800C89D4 },
    { 0x002F, (NEWCHARA)0x800C50C0 },
    { 0x0033, (NEWCHARA)0x8007DA94 },
    { 0x0044, (NEWCHARA)0x800C7ED0 },
    { 0, NULL }
};

int SECTION("overlay.bss") ending_dword_800CCD9C;
