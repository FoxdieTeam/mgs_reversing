#include "common.h"
#include "charadef.h"

extern void *NewPreviousOperation();

CHARA _StageCharacterEntries[] =
{
    { CHARA_PREOPE, (NEWCHARA)NewPreviousOperation },
    { 0, NULL }
};

