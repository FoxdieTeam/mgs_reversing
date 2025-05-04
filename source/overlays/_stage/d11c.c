#include "common.h"
#include "charadef.h"

#include "../_shared/game/lamp.h"
#include "thing/door.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/takabe/gas_efct.h"
#include "../_shared/takabe/fadeio.h"
#include "equip/equip.h"
#include "../_shared/enemy/demokage.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_DOOR, NewDoor },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_GAS_EFFECT, NewGasEffect_800C4E5C },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_KOGAKU2_001A, (NEWCHARA)NewKogaku2 },
    { CHARA_KOGAKU2_001B, (NEWCHARA)NewKogaku3 },
    { 0, NULL }
};
