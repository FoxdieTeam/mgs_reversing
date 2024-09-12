#include "common.h"
#include "charadef.h"

#include "Anime/animeconv/anime.h"
#include "../s00a/Okajima/pato_lmp.h"
#include "../s01a/Thing/sphere.h"
#include "../s00a/Enemy/smoke.h"
#include "../s00a/Thing/emitter.h"
#include "../s01a/Enemy/object.h"
#include "../s01a/Enemy/searchli.h"
#include "../s01a/Thing/snow.h"
#include "../s00a/Takabe/cinema.h"
#include "../s16b/Takabe/fadeio.h"
// #include "../s00a/Anime/animeconv/breath.c" AN_Breath_800C3AA8
#include "../d11c/Enemy/demokage.h"
#include "Takabe/windcrcl.h"
#include "Takabe/focus.h"
#include "Okajima/blur.h"
#include "Kojo/famaslit.h"

void AN_Breath_800C3AA8( MATRIX *matrix );

CHARA _StageCharacterEntries[] =
{
    { CHARA_PATO_LAMP, NewPatrolLamp_800D7A2C },
    { CHARA_SPHERE, NewSphere_800C69C0 },
    { CHARA_SMOKE, NewSmoke_800D2BEC },
    { CHARA_EMITTER, NewEmitter_800C3E50 },
    { CHARA_OBJECT, NewObjectChara_800DA3A4 },
    { CHARA_SEARCH_LIGHT, NewSearchlight_800D92BC },
    { CHARA_SNOW, NewSnow_800C6058 },
    { CHARA_CINEMA, NewCinemaScreenSet_800DE4D8 },
    { CHARA_FADEIO, NewFadeIo_800C4224 },
    { CHARA_FADEIO_0004, NewFadeIo_800C4224 },
    { CHARA_UNKNOWN_000E, (NEWCHARA)AN_Breath_800C3AA8 },
    { CHARA_DEMOKAGE, (NEWCHARA)NewDemoKage_800C48A4 },
    { CHARA_WINDCRCL, (NEWCHARA)NewWindcrcl_800CF6BC },
    { CHARA_SUB_EFCT, NewFocus_800CEFF8 },
    { CHARA_BLOOD_BL, NewBlur_800CD530 },
    { CHARA_FAMASLIT, (NEWCHARA)NewFamaslit_800D06F0 },
    { 0, NULL }
};
