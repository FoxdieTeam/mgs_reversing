#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTO,
    CHARA_FADE_IN_OUT,
    { 0x8e70, (NEWCHARA)0x800DB50C },   // s08b_glass_800DB50C (NewGlass_800D37A4)
    CHARA_PAPER,
    CHARA_CHAIR,        /* chara 椅子 */
    CHARA_PANEL2,       /* chara パネル２ */
    CHARA_MONITOR1,     /* chara モニタ１ */
    CHARA_NINJA,        /* chara 忍者 */
    CHARA_LAMP,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_MOVIE_3453,
    CHARA_WALL,         /* chara 障害物 */
    CHARA_LIFE_UP,
    CHARA_DYNAMIC_SEGMENT, /* chara 透明壁 */
    CHARA_CAT_IN,

    CHARA_0003_FADEIO,
    CHARA_0004_FADEIO,
    CHARA_0005_TELOP,
    CHARA_000E,
    CHARA_000F_DEMOKAGE,
    CHARA_0011,
    CHARA_0014_SCOPE,
    CHARA_0017_GOGGLEIR,
    CHARA_0018_GGLSIGHT,
    CHARA_001A_KOGAKU2,
    CHARA_001B_KOGAKU3,
    CHARA_0021_FOCUS,
    { 0x0023, (NEWCHARA)0x800D6AF4 },   // s08b_d_bloods_800D6AF4
    { 0x0025, (NEWCHARA)0x800D8D84 },   // s08b_blur_800D8D84 (NewBlur_800CD530)
    CHARA_002D_KATANA,
    CHARA_0042_GAS_EFCT,
    CHARA_004C_TELOP,

    CHARA_END
};
