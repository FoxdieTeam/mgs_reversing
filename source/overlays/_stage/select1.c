#include "common.h"
#include "charadef.h"

#include "../_shared/game/select.h"

CHARA _StageCharacterEntries[] = {
    { CHARA_SELECT, (NEWCHARA)NewSelect },
    { 0, NULL }
};
