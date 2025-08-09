#include "common.h"
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIATOKUN,    /* chara 足跡君 */
    CHARA_MOVIE_3453,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_SPHERE,       /* chara 天球 */

    CHARA_FADEIO_0003,
    CHARA_FADEIO_0004,
    CHARA_DEMOKAGE,
    CHARA_DEMOASI,
    CHARA_ENVMAP3,
    CHARA_FOCUS,
    CHARA_BLOOD_BL,
    CHARA_UNKNOWN_002F,
    CHARA_UNKNOWN_0033,
    CHARA_BLURPURE,

    CHARA_END
};

int SECTION("overlay.bss") ending_dword_800CCD9C;
