#include "common.h"
#include "charadef.h"

extern void *NewDemoSelect();

CHARA _StageCharacterEntries[] = 
{
    { CHARA_DEMOSEL, (NEWCHARA)NewDemoSelect },
    { 0, NULL }
};
