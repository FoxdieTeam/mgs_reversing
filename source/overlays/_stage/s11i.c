#include "common.h"
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_CAT_IN,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_BREATH,       /* chara スネーク息 */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_DYNAMIC_SEGMENT, /* chara 透明壁 */
    CHARA_ASIOTO,
    CHARA_FADE_IN_OUT,
    CHARA_LAMP,
    CHARA_SNOW,         /* chara 雪 */
    CHARA_SNOWSTORM,    /* chara 雪嵐 */
    CHARA_ZK11FCOM,     /* chara ざこ１１ｆコマンダー */
    CHARA_ZAKO11F,      /* chara ざこ１１ｆ */
    CHARA_SPHERE,       /* chara 天球 */
    CHARA_HIND2,
    CHARA_DMYWALL,      /* chara 塗り壁 */
    CHARA_END
};

int SECTION("overlay.bss") s11i_dword_800D5944;
