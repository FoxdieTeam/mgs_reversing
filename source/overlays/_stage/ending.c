#include "common.h"
#include "charadef.h"

CHARA _StageCharacterEntries[] =
{
    { 0x02C4, (NEWCHARA)0x800C6CA0 },   // NewAsiatoKun_800D1A70
    { 0x3453, (NEWCHARA)0x800C4F34 },   // NewMovieGCL
    { 0x7A05, (NEWCHARA)0x800C9E6C },   // NewCinemaScreenSet
    { 0x73EA, (NEWCHARA)0x800C5F7C },   // NewSphere
    { 0x0003, (NEWCHARA)0x800C8F18 },   // NewFadeIo_800C4224
    { 0x0004, (NEWCHARA)0x800C8F18 },   // NewFadeIo_800C4224
    { 0x000F, (NEWCHARA)0x800C7864 },   // NewDemoKage_800C48A4
    { 0x0010, (NEWCHARA)0x800C70C0 },   // NewDemoasi_800C414C
    { 0x001C, (NEWCHARA)0x800CA3A4 },   // NewEnvmap3_800CA3A4
    { 0x0021, (NEWCHARA)0x800CAAA8 },   // NewFocus_800CEFF8
    { 0x0025, (NEWCHARA)0x800C89D4 },   // NewBlur_800CD530
    { 0x002F, (NEWCHARA)0x800C50C0 },   // AN_Smoke_800CE164
    { 0x0033, (NEWCHARA)0x8007DA94 },   // demothrd_2_8007DA94
    { 0x0044, (NEWCHARA)0x800C7ED0 },   // NewBlurPure_800C54D4
    { 0, NULL }
};

int SECTION("overlay.bss") ending_dword_800CCD9C;
