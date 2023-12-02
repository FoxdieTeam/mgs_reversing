#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
#include "Anime/animeconv/anime.h"

GV_ACT *NewAsiatoKun_800D1A70(int name, int where, int argc, char **argv);
GV_ACT *s00a_smoke_800D2BEC(int name, int where, int argc, char **argv);
void   *NewSnakeWatcher_800C5034( int name, int where, int argc, char **argv );
void   *NewEmitter_800C3E50(int name, int where);
GV_ACT *NewRippleSurface_800D8244(int name, int where, int argc, char **argv);
GV_ACT *NewRipples_800D872C(int name, int where, int argc, char **argv);
GV_ACT *NewElevator_800D9F30(int name, int where);
GV_ACT *NewO2Damage_800DE9C8(int name, int where);
GV_ACT *NewPatrolLamp_800D7A2C(int arg0, int arg1);
GV_ACT *NewMouse_800D5234(int name, int where);
GV_ACT *NewBubbleS_800D5D9C(int name, int where);
void   *NewWaterArea_800DACCC(int name, int where, int argc, char **argv);
void   *NewBreath_800C3A1C(int name, int where, int argc, char **argv);
void   *NewPad_800C37EC(int name, int where, int argc, char **argv);
void   *NewCommand_800D0908(int name, int where, int argc, char **argv);
GV_ACT *NewTelopSet_800DDB34(int arg0, int arg1);
GV_ACT *NewZoom_800DFA88(int name, int where, int argc, char **argv);
void   *NewCameraShake_800DF6AC(int name, int where, int argc, char **argv);
GV_ACT *NewEnvSnd_800DF424(int name, int where);
GV_ACT *NewCinemaScreenSet_800DE4D8(int name, int where, int argc, char **argv);
GV_ACT *NewPadDemo_800DCFD4(int name, int where);

GCL_ActorTableEntry s00aOverlayCharas[] =
{
    { CHARA_RIPPLES, NewRipples_800D872C },
    { CHARA_PAD, (TGCL_ActorCreateFn)NewPad_800C37EC },
    { CHARA_VIBRATE, (TGCL_ActorCreateFn)0x8005D508 },
    { CHARA_BREATH, (TGCL_ActorCreateFn)NewBreath_800C3A1C },
    { CHARA_ENV_SOUND, (TGCL_ActorCreateFn)NewEnvSnd_800DF424 },
    { CHARA_CAMERA_SHAKE, (TGCL_ActorCreateFn)NewCameraShake_800DF6AC },
    { CHARA_CAT_IN, NewZoom_800DFA88 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_PAD_DEMO, (TGCL_ActorCreateFn)NewPadDemo_800DCFD4 },
    { CHARA_DYNAMIC_SEGMENT, (TGCL_ActorCreateFn)0x800DEBEC }, // s16b
    { CHARA_ASIOTO, (TGCL_ActorCreateFn)0x800D3808 }, // s16b
    { CHARA_ASIATO, NewAsiatoKun_800D1A70 },
    { CHARA_OBSTACLE, (TGCL_ActorCreateFn)0x800D3118 },
    { CHARA_SHAKE_MODEL, (TGCL_ActorCreateFn)0x800DEEE0 }, // s16b
    { CHARA_PATO_LAMP, (TGCL_ActorCreateFn)NewPatrolLamp_800D7A2C },
    { CHARA_COMMAND, (TGCL_ActorCreateFn)NewCommand_800D0908 },
    { CHARA_WT_AREA, (TGCL_ActorCreateFn)NewWaterArea_800DACCC },
    { CHARA_WATCHER, (TGCL_ActorCreateFn)NewSnakeWatcher_800C5034 },
    { CHARA_SMOKE, s00a_smoke_800D2BEC },
    { CHARA_EMITTER, (TGCL_ActorCreateFn)NewEmitter_800C3E50 },
    { CHARA_ELEVATOR, (TGCL_ActorCreateFn)NewElevator_800D9F30 },
    { CHARA_MOUSE, (TGCL_ActorCreateFn)NewMouse_800D5234 },
    { CHARA_RSURFACE, NewRippleSurface_800D8244 },
    { CHARA_TELOP, (TGCL_ActorCreateFn)NewTelopSet_800DDB34 },
    { CHARA_BUBBLE_S, (TGCL_ActorCreateFn)NewBubbleS_800D5D9C },
    { CHARA_O2_DAMAGE, (TGCL_ActorCreateFn)NewO2Damage_800DE9C8 },
    { CHARA_FADE_IN_OUT, (TGCL_ActorCreateFn)0x800DD4A8 }, // s16b
    { 0, 0 }
};
