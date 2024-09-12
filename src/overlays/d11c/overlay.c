#include "common.h"
#include "charadef.h"

#include "Game/lamp.h"
#include "Thing/door.h"
#include "../s00a/Takabe/cinema.h"
#include "../s16b/Enemy/wall.h"
#include "Takabe/gas_efct.h"
#include "../s16b/Takabe/fadeio.h"
#include "Equip/kogaku2.h"
#include "Enemy/demokage.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_DOOR, NewDoor_8006FD00 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_KOGAKU2_001A, (NEWCHARA)NewKogaku2_800615FC },
    { CHARA_KOGAKU2_001B, (NEWCHARA)NewKogaku3_80061708 },
    { 0, NULL }
};
