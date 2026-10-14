#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_SNEBREATH,    /* chara スネーク息 */
    CHARA_CAT_IN,       /* chara カットインカメラ */
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_TEXTURE,      /* chara テクスチャ */
    CHARA_SNOW,         /* chara 雪 */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_FADEIO,       /* chara フェードイン・アウト */
    CHARA_MI24HIND,
    CHARA_SPHERE,       /* chara 天球 */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_11B_DEMO,

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_MISSILESMOKE,
    DEMO_BREATH,
    DEMO_SHADOW,
    DEMO_WINDCIRCLE,
    DEMO_BLUR,
    DEMO_BLASTLINE,
    DEMO_SMOKELINE,
    DEMO_ENVIRONMENTLIGHT,
    DEMO_ENVIRONMENTLIGHT2,
    { 0x0039, (NEWCHARA *)0x800c8168 }, //  DEMO_CRASHSMOKE,
    { 0x003b, (NEWCHARA *)0x800ce9ec }, //  DEMO_INVERSLIGHT,
    DEMO_SPACK,
    DEMO_SPACK2,
    DEMO_GHOST,

    CHARA_END
};
