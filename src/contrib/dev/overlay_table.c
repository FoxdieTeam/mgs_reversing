#include "common.h"
#include "charadef.h"
#include "overlays/s16b/Enemy/wall.h"
#include "overlays/s16b/Enemy/asioto.h"
#include "overlays/s16b/Takabe/fadeio.h"
#include "overlays/select1/Game/select.h"
#include "Anime/animeconv/anime.h"
#include "overlays/s00a/Takabe/ripples.h"
#include "overlays/s00a/Game/pad.h"
#include "Game/vibrate.h"
#include "overlays/s00a/chara/snake/breath.h"
#include "overlays/s00a/Takabe/env_snd.h"
#include "overlays/s00a/Takabe/camshake.h"
#include "overlays/s00a/Takabe/cat_in.h"
#include "overlays/s00a/Takabe/cinema.h"
#include "overlays/s00a/Takabe/pad_demo.h"
#include "overlays/s16b/Takabe/dymc_seg.h"
#include "overlays/s16b/Enemy/asioto.h"
#include "overlays/s00a/Enemy/asiato.h"
#include "overlays/s16b/Enemy/wall.h"
#include "overlays/s16b/Takabe/shakemdl.h"
#include "overlays/s00a/Okajima/pato_lmp.h"
#include "overlays/s00a/Enemy/command.h"
#include "overlays/s00a/Takabe/wt_area.h"
#include "overlays/s00a/Enemy/watcher.h"
#include "overlays/s00a/Enemy/smoke.h"
#include "overlays/s00a/Thing/emitter.h"
#include "overlays/s00a/Takabe/elevator.h"
#include "overlays/s03e/Game/evpanel.h"
#include "overlays/s00a/Okajima/mouse.h"
#include "overlays/s00a/Takabe/rsurface.h"
#include "overlays/s00a/Takabe/telop.h"
#include "overlays/s00a/Okajima/bubble_s.h"
#include "overlays/s00a/Takabe/o2_damge.h"
#include "overlays/s16b/Takabe/fadeio.h"

GV_ACT *NewShakemdl_800C54E8(int name, int where, int argc, char **argv);
GV_ACT *NewSepia_800C4F9C(int name, int where, int argc);
GV_ACT *NewDymcSeg_800C4BCC(int name, int where, int argc, char **argv);
GV_ACT *NewVibEdit_800C47B4(int flags, int perms);

CHARA _StageCharacterEntries[] =
{
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_SEPIA, (NEWCHARA)NewSepia_800C4F9C },
    { CHARA_SELECT, NewSelect_800C3434 },
    { CHARA_VIB_EDIT, (NEWCHARA)NewVibEdit_800C47B4 },
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, NewPad_800C37EC },
    { CHARA_VIBRATE, (NEWCHARA)vibrate_init_8005D508 },
    { CHARA_BREATH, NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, NewEnvSnd_800DF424 },
    { CHARA_CAMERA_SHAKE, NewCameraShake_800DF6AC },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, NewPadDemo_800DCFD4 },
    { CHARA_DYNAMIC_SEGMENT, NewDymcSeg_800C4BCC },
    { CHARA_ASIOTO, NewAsioto_800C3E08 },
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_OBSTACLE, NewWall_800C3718 },
    { CHARA_SHAKE_MODEL, NewShakemdl_800C54E8 },
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, NewCommand_800D0908 },
    { CHARA_WT_AREA, NewWaterArea_800DACCC },
    { CHARA_WATCHER, NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter_800C3E50 },
    { CHARA_ELEVATOR, NewElevator_800D9F30 },
    { CHARA_ELEVATOR_PANEL, NewEvPanel_800C4AD8 },
    { CHARA_MOUSE, NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_TELOP, NewTelopSet_800DDB34 },
    { CHARA_BUBBLE_S, NewBubbleS_800D5D9C },
    { CHARA_O2_DAMAGE, NewO2Damage_800DE9C8 },
    { CHARA_FADE_IN_OUT, NewFadeIo_800C42BC },
    { 0, NULL }
};
