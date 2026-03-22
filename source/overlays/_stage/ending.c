#include "common.h"
#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIATOKUN,    /* chara 足跡君 */
    CHARA_MOVIE_3453,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_SPHERE,       /* chara 天球 */

    CHARA_0003_FADEIO,
    CHARA_0004_FADEIO,
    CHARA_000F_DEMOKAGE,
    CHARA_0010_DEMOASI,
    CHARA_001C_ENVMAP3,
    CHARA_0021_FOCUS,
    CHARA_0025_BLOOD_BL,
    CHARA_002F,
    CHARA_0033,
    CHARA_0044_BLURPURE,

    CHARA_END
};

int SECTION("overlay.bss") ending_dword_800CCD9C;
