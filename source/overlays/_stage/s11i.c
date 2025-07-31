#include "common.h"
#include "charadef.h"

CHARA _StageCharacterEntries[] =
{
    { 0x51C6, (NEWCHARA)0x800D4344 },   // NewZoom_800DFA88
    { 0x7A05, (NEWCHARA)0x800D3D38 },   // NewCinemaScreenSet
    { 0x4170, (NEWCHARA)0x800C4204 },   // NewBreath_800C3A1C
    { 0xEC77, (NEWCHARA)0x800C7F8C },   // NewWall_800C3718
    { 0xB103, (NEWCHARA)0x800D3F68 },   // NewDymcSeg_800C4BCC
    { 0x92BC, (NEWCHARA)0x800C867C },   // NewAsioto_800C3E08
    { 0xA12E, (NEWCHARA)0x800D355C },   // NewFadeIo_800C42BC
    { 0x1AD3, (NEWCHARA)0x800C3F94 },   // NewLamp
    { 0x18E3, (NEWCHARA)0x800C70FC },   // NewSnow
    { 0xA6F5, (NEWCHARA)0x800D43D8 },   // NewSnowStorm
    { 0x5F0E, (NEWCHARA)0x800D20D8 },   // NewZakoCommander_800D20D8
    { 0xA60D, (NEWCHARA)0x800C94D8 },   // NewZako11F
    { 0x73EA, (NEWCHARA)0x800C7A64 },   // NewSphere
    { 0xB959, (NEWCHARA)0x800C588C },   // NewHind2
    { 0x58F0, (NEWCHARA)0x800D2674 },   // NewDummyWall_800D7384
    { 0, NULL }
};

int SECTION("overlay.bss") s11i_dword_800D5944;
