#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_FADEIO,       /* chara 白黒フェド */
    { 0x8e70, (NEWCHARA)0x800DB50C },   //  CHARA_GLASS,        /* chara ガラス */
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

    CHARA_0003_FADEIN,
    CHARA_0004_FADEOUT,
    CHARA_0005_TEXT,
    CHARA_000E_BREATH,
    CHARA_000F_SHADOW,
    CHARA_0011_NINJAEYE,
    CHARA_0014_SCOPE,
    CHARA_0017_IRRAYSGOGGLE,
    CHARA_0018_IRRAYSGOGGLE2,
    CHARA_001A_OPTICSCAMOUFLAGE,
    CHARA_001B_OPTICSCAMOUFLAGE2,
    CHARA_0021_UNSHAPEVIEW,
    { 0x0023, (NEWCHARA)0x800D6AF4 },   //  CHARA_0023_URINATIONCIRCLE,
    { 0x0025, (NEWCHARA)0x800D8D84 },   //  CHARA_0025_BLUR,
    CHARA_002D_NINJASWORD,
    CHARA_0042_GUSEFFECT,
    CHARA_004C_TEXT2,

    CHARA_END
};
