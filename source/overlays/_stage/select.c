#include "common.h"
#include "charadef.h"
#include "../_shared/Game/select.h"

void *NewVibEdit_800C47B4(int flags, int perms);

CHARA _StageCharacterEntries[] =
{
    { CHARA_SELECT, (NEWCHARA)NewSelect_800C3434 },
    { CHARA_VIB_EDIT, (NEWCHARA)NewVibEdit_800C47B4 },
    { 0, NULL }
};
