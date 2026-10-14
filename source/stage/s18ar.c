#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

extern NEWCHARA s18a_800DF70C; // NewSnake18 (still asm in this overlay)

CHARA _StageCharacterEntries[] = {
    CHARA_BLACKSMOKE,   /* chara 黒煙 */
    CHARA_BLUR,         /* chara ブラー */
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_FADEIO,       /* chara フェードイン・アウト */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_LIQUID,       /* chara リキッド */
    CHARA_DEMODOLL,     /* chara デモ人形 */
    { 0x760e, s18a_800DF70C }, // CHARA_SNAKE18, /* chara スネーク１８ */
    CHARA_WALL,         /* chara 障害物 */
    CHARA_SMKTRGT,
    CHARA_WAKE,         /* chara 覚醒スネーク */

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_BLUR,
    DEMO_MONOTONE,

    CHARA_DEMOCANCEL,   /* chara デモキャンセル */

    CHARA_END
};
