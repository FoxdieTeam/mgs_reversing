#include "common.h"
#include "charadef.h"

#include "anime/animconv/anime.h"
#include "../_shared/okajima/pato_lmp.h"
#include "../_shared/thing/sphere.h"
#include "../_shared/enemy/smoke.h"
#include "../_shared/thing/emitter.h"
#include "../_shared/enemy/object.h"
#include "../_shared/enemy/searchli.h"
#include "../_shared/thing/snow.h"
#include "../_shared/takabe/cinema.h"
#include "../_shared/takabe/fadeio.h"
// #include "../_shared/anime/animconv/breath.c" AN_Breath
#include "../_shared/enemy/demokage.h"
#include "../_shared/takabe/windcrcl.h"
#include "../_shared/takabe/focus.h"
#include "../_shared/okajima/blur.h"
#include "../_shared/kojo/famaslit.h"

void AN_Breath( MATRIX *matrix );

CHARA _StageCharacterEntries[] =
{
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_SPHERE, NewSphere },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_OBJECT, NewObjectChara_800DA3A4 },
    { CHARA_SEARCH_LIGHT, NewSearchlight_800D92BC },
    { CHARA_SNOW, NewSnow },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_UNKNOWN_000E, (NEWCHARA)AN_Breath },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_WINDCRCL_001E, (NEWCHARA)NewWindcrcl_800CF6BC },
    { CHARA_FOCUS, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
