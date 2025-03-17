#include "common.h"
#include "charadef.h"

#include "../_shared/Enemy/asioto.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Takabe/cat_in.h"
#include "../_shared/Enemy/wall.h"
#include "../_shared/Game/evpanel.h"
#include "../_shared/Okajima/uji.h"
#include "../_shared/Game/lamp.h"
#include "../_shared/Okajima/guncame.h"
#include "../_shared/Takabe/fadeio.h"
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
