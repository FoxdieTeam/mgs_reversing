#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_SHAKEMODEL,
    CHARA_WALL,         /* chara 障害物 */
    CHARA_COMMANDER,    /* chara コマンダー */
    CHARA_WATCHER,      /* chara 巡回兵 */
    CHARA_KIKENKUN,     /* chara 危険君 */
    CHARA_CAMERA,       /* chara カメラ */
    CHARA_DEMODOLL,     /* chara デモ人形 */
    CHARA_FADEIO,       /* chara 白黒フェド */
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_ASIOTOKUN,    /* chara 足音君 */

    DEMO_FADEIN,
    DEMO_FADEOUT,
    DEMO_MONOTONE,
    DEMO_ENVIRONMENTLIGHT,
    DEMO_ENVIRONMENTLIGHT2,
    DEMO_GUSEFFECT,
    DEMO_GHOST,

    CHARA_END
};
