#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_COUNTDOWN,
    CHARA_CAT_IN,
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_JEEP_SRL,
    CHARA_JDRUM,
    CHARA_JEEP_EMY,
    CHARA_VOICESYS,     /* chara 音声制御 */
    { 0xd6fb, (NEWCHARA)0x800CB120 },   // CHARA_FOG,
    CHARA_FADEIO,

    CHARA_END
};
