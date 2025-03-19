#include "common.h"
#include "charadef.h"

#include "../_shared/Enemy/wall.h"
#include "../_shared/Takabe/shakemdl.h"
#include "../_shared/Okajima/pato_lmp.h"
#include "../_shared/Enemy/command.h"
#include "../_shared/Takabe/wt_view.h"
#include "../_shared/Enemy/watcher.h"
#include "../_shared/Enemy/smoke.h"
#include "../_shared/Thing/emitter.h"
#include "../_shared/Takabe/elevator.h"
#include "../_shared/Okajima/mouse.h"
#include "../_shared/Takabe/rsurface.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Takabe/fadeio.h"
#include "../_shared/Takabe/telop.h"
#include "../_shared/Enemy/demokage.h"
#include "../_shared/Okajima/bubble_t.h"
#include "../_shared/Okajima/bubble_p.h"
#include "../_shared/Okajima/blur.h"
#include "../_shared/Okajima/d_bloods.h"
#include "../_shared/Okajima/red_alrt.h"
#include "../_shared/Okajima/blurpure.h"
#include "../_shared/Kojo/famaslit.h"

void AN_Breath(MATRIX *matrix);

CHARA _StageCharacterEntries[] = 
{
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WT_VIEW, NewWaterView },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_ELEVATOR, NewElevator_800D9F30 },
    { CHARA_MOUSE, NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_TELOP_0005, (NEWCHARA)NewTelop_800DDD7C },
    { CHARA_UNKNOWN_000E, (NEWCHARA)AN_Breath },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_BUBBLE_T, (NEWCHARA)NewBubbleT_800DA380 },
    { CHARA_BUBBLE_P, (NEWCHARA)NewBubbleP_800D9D94 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_D_BLOODS_002B, (NEWCHARA)NewDBloods_800D5B70 },
    { CHARA_RED_ALERT_0037, (NEWCHARA)NewRedAlert2_800C4E84 },
    { CHARA_RED_ALERT_0038, (NEWCHARA)RedAlert_800C4F48 },
    { CHARA_BLURPURE, NewBlurPure_800C54D4 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
