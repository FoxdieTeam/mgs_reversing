#include "common.h"
#include "charadef.h"

#include "../s16b/Enemy/asioto.h"
#include "../s00a/Takabe/cinema.h"
#include "../s00a/Takabe/cat_in.h"
#include "../s16b/Enemy/wall.h"
#include "Game/evpanel.h"
#include "../d03a/Okajima/uji.h"
#include "../d11c/Game/lamp.h"
#include "Okajima/guncame.h"
#include "../s16b/Takabe/fadeio.h"
#include "chara/others/intr_cam.h"
#include "chara/others/motse.h"

CHARA _StageCharacterEntries[] =
{
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_UJI, NewUji_800C42F8 },
    { CHARA_LAMP, NewLamp_800C3B34 },
    { CHARA_GUNCAME, NewGunCame_800C9190 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_INTR_CAM, NewIntrCam_800C5748 },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_MOTION_SE, NewMotionSoundEffect },
    { 0, NULL }
};
