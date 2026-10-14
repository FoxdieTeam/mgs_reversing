#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_CAT_IN,       /* chara カットインカメラ */
    CHARA_SNEBREATH,    /* chara スネーク息 */
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_SPHERE,       /* chara 天球 */
    CHARA_TEXTURE,      /* chara テクスチャ */
    CHARA_SNOW,         /* chara 雪 */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_FADEIO,       /* chara フェードイン・アウト */
    CHARA_MI24HIND,
    CHARA_S11_OBJS,     /* chara コントロールＳ１１物 */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_LIFEUP,       /* chara ライフ増加 */
    { 0x91aa, (NEWCHARA *)0x800ccbf0 }, //  CHARA_PUTHZD,

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_SHADOW,
    DEMO_BLUR,
    DEMO_MONOTONE,
    DEMO_BLASTLINE,
    DEMO_SMOKELINE,
    DEMO_ENVIRONMENTLIGHT,
    DEMO_ENVIRONMENTLIGHT2,
    { 0x003b, (NEWCHARA *)0x800ccfa4 }, //  DEMO_INVERSLIGHT,
    DEMO_INVERSLIGHT2,

    CHARA_END
};
