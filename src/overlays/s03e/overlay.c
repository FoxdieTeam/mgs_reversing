#include "libgcl/hash.h"
#include "libgcl/libgcl.h"
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

GCL_ActorTableEntry s03eOverlayCharas[] =
{
    { 0x92BC, NewAsioto_800C3E08 },
    { 0x7A05, NewCinemaScreenSet_800DE4D8 },
    { 0xEC77, NewWall_800C3718 },
    { 0xE253, NewEvPanel_800C4AD8 },
    { 0xF5C5, NewUji_800C42F8 },
    { 0x1AD3, NewLamp_800C3B34 },
    { 0xA9C5, NewGunCamE_800C9190 },
    { 0xA12E, NewFadeIo_800C42BC },
    { 0xDD8B, NewIntrCam_800C5748 },
    { 0x51C6, NewZoom_800DFA88 },
    { 0x0FAD, NewMotse_800C5944 },
    { NULL, NULL }
};
