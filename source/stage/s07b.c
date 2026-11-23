#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_FADEIO,       /* chara フェードイン・アウト */
    CHARA_PSYCHOMANTIS, /* chara サイコマンティス */
    { 0xf4b0, (NEWCHARA *)0x800ca8f8 }, //  CHARA_PSYCHOMERYL,  /* chara サイコメリル */
    CHARA_MEMPSY,
    CHARA_PSYOBJ,       /* chara サイコ物体 */
    CHARA_TEXTURE,      /* chara テクスチャ */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_LIFEUP,       /* chara ライフ増加 */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_CAT_IN,       /* chara カットインカメラ */
    CHARA_GASEFFECT,    /* chara ガス効果 */
    CHARA_DEMODOLL,     /* chara デモ人形 */
    CHARA_9FFD_2ND,
    CHARA_2D0A_2ND,
    CHARA_MOTIONSE,

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_TEXT,
    DEMO_SHADOW,
    DEMO_OPTICSCAMOUFLAGE,
    DEMO_OPTICSCAMOUFLAGE2,
    DEMO_UNSHAPEVIEW,
    DEMO_BLUR,
    DEMO_MONOTONE,
    DEMO_ENVIRONMENTLIGHT,
    DEMO_ENVIRONMENTLIGHT2,
    DEMO_GHOST,

    CHARA_END
};
