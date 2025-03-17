#include "common.h"
#include "charadef.h"

#include "Anime/animconv/anime.h"
#include "../_shared/Okajima/pato_lmp.h"
#include "../_shared/Thing/sphere.h"
#include "../_shared/Enemy/smoke.h"
#include "../_shared/Thing/emitter.h"
#include "../_shared/Enemy/object.h"
#include "../_shared/Enemy/searchli.h"
#include "../_shared/Thing/snow.h"
#include "../_shared/Takabe/cinema.h"
#include "../_shared/Takabe/fadeio.h"
// #include "../_shared/Anime/animconv/breath.c" AN_Breath_800C3AA8
#include "../_shared/Enemy/demokage.h"
#include "../_shared/Takabe/windcrcl.h"
#include "../_shared/Takabe/focus.h"
#include "../_shared/Okajima/blur.h"
#include "../_shared/Kojo/famaslit.h"

void AN_Breath_800C3AA8( MATRIX *matrix );

CHARA _StageCharacterEntries[] =
{
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_SPHERE, NewSphere_800C69C0 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter },
    { CHARA_OBJECT, NewObjectChara_800DA3A4 },
    { CHARA_SEARCH_LIGHT, NewSearchlight_800D92BC },
    { CHARA_SNOW, NewSnow_800C6058 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO_0003, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_UNKNOWN_000E, (NEWCHARA)AN_Breath_800C3AA8 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_WINDCRCL_001E, (NEWCHARA)NewWindcrcl_800CF6BC },
    { CHARA_FOCUS, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
