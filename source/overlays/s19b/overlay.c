#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_PAUSE,
    CHARA_CAT_IN,
    { 0x92bc, (NEWCHARA)0x800C483C },   // s19b_asioto_800C483C (NewAsioto_800C3E08)
    CHARA_JEEP_SRL,
    CHARA_JDRUM,
    CHARA_JEEP_EMY,
    CHARA_VOICESYS,
    { 0xd6fb, (NEWCHARA)0x800CB120 },   // s19b_fog_800CB120 (NewFog_800D4208)
    { 0xa12e, (NEWCHARA)0x800DABEC },   // s19b_fadeio_800DABEC (NewFadeIo_800C42BC)

    CHARA_END
};
