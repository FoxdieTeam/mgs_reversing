#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_FADEIO,       /* chara 白黒フェド */
    { 0x8e70, (NEWCHARA *)0x800DB50C }, //  CHARA_GLASS,        /* chara ガラス */
    CHARA_PAPER,        /* chara 書類 */
    CHARA_CHAIR,        /* chara 椅子 */
    CHARA_PANEL2,       /* chara パネル２ */
    CHARA_MONITOR1,     /* chara モニタ１ */
    CHARA_NINJA,        /* chara 忍者 */
    CHARA_TEXTURE,      /* chara テクスチャ */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_MOVIE,        /* chara ムービー */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_LIFEUP,       /* chara ライフ増加 */
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_CAT_IN,

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_TEXT,
    DEMO_BREATH,
    DEMO_SHADOW,
    DEMO_NINJAEYE,
    DEMO_SCOPE,
    DEMO_IRRAYSGOGGLE,
    DEMO_IRRAYSGOGGLE2,
    DEMO_OPTICSCAMOUFLAGE,
    DEMO_OPTICSCAMOUFLAGE2,
    DEMO_UNSHAPEVIEW,
    { 0x0023, (NEWCHARA *)0x800D6AF4 }, //  DEMO_URINATIONCIRCLE,
    { 0x0025, (NEWCHARA *)0x800D8D84 }, //  DEMO_BLUR,
    DEMO_NINJASWORD,
    DEMO_GUSEFFECT,
    DEMO_TEXT2,

    CHARA_END
};
