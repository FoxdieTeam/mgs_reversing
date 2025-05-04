#include "common.h"
#include "charadef.h"

#include "../_shared/enemy/asioto.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/cat_in.h"
#include "../_shared/enemy/wall.h"
#include "../_shared/game/evpanel.h"
#include "../_shared/okajima/uji.h"
#include "../_shared/game/lamp.h"
#include "../_shared/okajima/guncame.h"
#include "../_shared/takabe/fadeio.h"
#include "../_shared/chara/others/intr_cam.h"
#include "../_shared/chara/others/motse.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_GUNCAME, NewGunCame_800C9190 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_INTR_CAM, NewIntrudeCamera },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { 0, NULL }
};
