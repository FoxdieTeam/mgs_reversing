#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_PAUSE,
    CHARA_CAT_IN,
    CHARA_ASIOTO,
    CHARA_JEEP_SRL,
    CHARA_JDRUM,
    CHARA_JEEP_EMY,
    CHARA_VOICE_SYSTEM,
    { 0xd6fb, (NEWCHARA)0x800CB120 },   // s19b_fog_800CB120 (NewFog_800D4208)
    CHARA_FADE_IN_OUT,

    CHARA_END
};
