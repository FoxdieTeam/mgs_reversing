#include "common.h"
#include "charadef.h"

#include "../_shared/game/select.h"
#include "../_shared/takabe/vib_edit.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_SELECT, (NEWCHARA)NewSelect },
    { CHARA_VIB_EDIT, (NEWCHARA)NewVibEdit_800C47B4 },
    { 0, NULL }
};
