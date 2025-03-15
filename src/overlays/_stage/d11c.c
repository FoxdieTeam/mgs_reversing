#include "common.h"
#include "charadef.h"

#include "../_shared/Game/lamp.h"
#include "Thing/door.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Takabe/gas_efct.h"
#include "../_shared/Takabe/fadeio.h"
#include "Equip/equip.h"
#include "../_shared/Enemy/demokage.h"

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
