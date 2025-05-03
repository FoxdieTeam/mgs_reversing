#include "common.h"
#include "charadef.h"

#include "Anime/animconv/anime.h"
#include "Game/vibrate.h"
#include "overlays/_shared/Enemy/asiato.h"
#include "overlays/_shared/Enemy/asioto.h"
#include "overlays/_shared/Enemy/command.h"
#include "overlays/_shared/Enemy/smoke.h"
#include "overlays/_shared/Enemy/wall.h"
#include "overlays/_shared/Enemy/watcher.h"
#include "overlays/_shared/Game/evpanel.h"
#include "overlays/_shared/Game/pad.h"
#include "overlays/_shared/Game/select.h"
#include "overlays/_shared/Okajima/bubble_s.h"
#include "overlays/_shared/Okajima/mouse.h"
#include "overlays/_shared/Okajima/pato_lmp.h"
#include "overlays/_shared/Takabe/camshake.h"
#include "overlays/_shared/Takabe/cat_in.h"
#include "overlays/_shared/Takabe/cinema.h"
#include "overlays/_shared/Takabe/dymc_seg.h"
#include "overlays/_shared/Takabe/elevator.h"
#include "overlays/_shared/Takabe/env_snd.h"
#include "overlays/_shared/Takabe/fadeio.h"
#include "overlays/_shared/Takabe/o2_damge.h"
#include "overlays/_shared/Takabe/pad_demo.h"
#include "overlays/_shared/Takabe/ripples.h"
#include "overlays/_shared/Takabe/rsurface.h"
#include "overlays/_shared/Takabe/sepia.h"
#include "overlays/_shared/Takabe/shakemdl.h"
#include "overlays/_shared/Takabe/telop.h"
#include "overlays/_shared/Takabe/wt_area.h"
#include "overlays/_shared/Thing/emitter.h"
#include "overlays/_shared/chara/snake/breath.h"

void *NewVibEdit_800C47B4(int flags, int perms);

CHARA _StageCharacterEntries[] =
{
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_SEPIA_0028, (NEWCHARA)NewSepia_800C4F9C },
    { CHARA_SELECT, NewSelect_800C3434 },
    { CHARA_VIB_EDIT, (NEWCHARA)NewVibEdit_800C47B4 },
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_VIBRATE, (NEWCHARA)NewVibration },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAMERA_SHAKE, NewCameraShake },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, NewPadDemo_800DCFD4 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_WALL, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WT_AREA, NewWaterArea },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_ELEVATOR, NewElevator_800D9F30 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_MOUSE, NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_TELOP_SET, NewTelopSet_800DDB34 },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
