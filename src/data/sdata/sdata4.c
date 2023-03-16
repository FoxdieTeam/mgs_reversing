#include "linker.h"
#include "chara/snake/sna_init.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Menu/menuman.h"

GCL_ARGS SECTION(".sdata") gcl_null_args_800AB3BC = {};

int SECTION(".sdata") gCurrentStageName_800AB3C4 = 0;

int SECTION(".sdata") dword_800AB3C8 = 0;

int SECTION(".sdata") GM_GameStatus_800AB3CC = 0;
int SECTION(".sdata") GM_LoadRequest_800AB3D0 = 0;
int SECTION(".sdata") GM_GameOverTimer_800AB3D4 = 0;
int SECTION(".sdata") GM_lpsvectWind_800AB3D8 = 0;

TSnakeActFunction SECTION(".sdata") GM_lpfnPlayerActControl_800AB3DC = NULL;
TSnakeActFunction SECTION(".sdata") GM_lpfnPlayerActObject2_800AB3E0 = NULL;

short SECTION(".sdata") GM_uBombHoming_800AB3E4 = 0;
short SECTION(".sdata") GM_uTenageMotion_800AB3E6 = -1;

TBombFunction  SECTION(".sdata") GM_lpfnBombHoming_800AB3E8 = NULL;
TBombFunction2 SECTION(".sdata") GM_lpfnBombBound_800AB3EC = NULL;
TBombFunction3 SECTION(".sdata") GM_lpfnBombExplosion_800AB3F0 = NULL;

int SECTION(".sdata") GM_PadResetDisable_800AB3F4 = 0;

char SECTION(".sdata") aInit[] = "init";

int SECTION(".sdata") dword_800AB400 = 0;

char SECTION(".sdata") aGamedC[] = "gamed.c";
char SECTION(".sdata") aGcawi[5] = "gcawi";

int SECTION(".sdata") demodebug_finish_proc_800AB414 = 0xFFFFFFFF;

char SECTION(".sdata") aPrint[] = "print: ";
char SECTION(".sdata") aS_2[] = "%s ";
char SECTION(".sdata") aD_3[] = "%d ";

const char SECTION(".sdata") asc_800AB428[] = "\n";

int SECTION(".sdata") GM_CameraTrackSave_800AB42C = 0x2710;

SVECTOR SECTION(".sdata") GM_CameraRotateSave_800AB430 = { 0x0280, 0x0800, 0, 0 };

int SECTION(".sdata") GM_CameraTrackOrg_800AB438 = 0x2710;
int SECTION(".sdata") GM_CameraTrackOrg_800AB43C = 0;
int SECTION(".sdata") GM_CameraTrackOrg_800AB440 = 0;
int SECTION(".sdata") GM_CameraTrackOrg_800AB444 = 0;
int SECTION(".sdata") GM_CameraTrackOrg_800AB448 = 0;

const char SECTION(".sdata") aNoHzd[] = "no hzd\n";
const char SECTION(".sdata") aDelayC[] = "delay.c";

int SECTION(".sdata") GM_GameOverVox_800AB45C = 0xFFFFFFFF;

const char SECTION(".sdata") aInit_0[] = "init";
const char SECTION(".sdata") aTitle[] = "title";
const char SECTION(".sdata") aOverC[] = "over.c";
const char SECTION(".sdata") aItem[] = "item";

int SECTION(".sdata") MENU_RadarScale_800AB480 = 0xD;
int SECTION(".sdata") MENU_RadarRangeH_800AB484 = 0x5555;
int SECTION(".sdata") MENU_RadarRangeV_800AB488 = 0x3FFF;
int SECTION(".sdata") gFn_radar_800AB48C = 0;

RECT SECTION(".sdata") rect_800AB490 = {992, 382, 32, 2};

int SECTION(".sdata") gRadarClut_800AB498 = 0x5FBF5FBE;
int SECTION(".sdata") dword_800AB49C = 0x5FFF5FFE;
int SECTION(".sdata") dword_800AB4A0 = 0x8D118C91;
int SECTION(".sdata") dword_800AB4A4 = 0x9A238C91;
int SECTION(".sdata") dword_800AB4A8 = 0x80238023;
int SECTION(".sdata") dword_800AB4AC = 0x8023;
int SECTION(".sdata") dword_800AB4B0 = 0;
int SECTION(".sdata") dword_800AB4B4 = 0;

const char SECTION(".sdata") aSuppr[] = "SUPPR.";
const char SECTION(".sdata") aScarf[] = "SCARF";
const char SECTION(".sdata") aRope[] = "ROPE";
const char SECTION(".sdata") aDisc[] = "DISC";
const char SECTION(".sdata") aMineD[] = "MINE.D";
const char SECTION(".sdata") aTimerB[] = "TIMER.B";
const char SECTION(".sdata") aCard[] = "CARD";
const char SECTION(".sdata") aPalKey[] = "PAL KEY";
const char SECTION(".sdata") aRation[] = "RATION";
const char SECTION(".sdata") aCamera[] = "CAMERA";
const char SECTION(".sdata") aBandana[] = "BANDANA";
const char SECTION(".sdata") aStealth[] = "STEALTH";
const char SECTION(".sdata") aKetchup[] = "KETCHUP";
const char SECTION(".sdata") aBArmor[] = "B.ARMOR";
const char SECTION(".sdata") aGasmask[] = "GASMASK";
const char SECTION(".sdata") aThermG[] = "THERM.G";
const char SECTION(".sdata") aNVG[] = "N.V.G";
const char SECTION(".sdata") aCBoxC[] = "C.BOX C";
const char SECTION(".sdata") aCBoxB[] = "C.BOX B";
const char SECTION(".sdata") aCBoxA[] = "C.BOX A";
const char SECTION(".sdata") aScope[] = "SCOPE";
const char SECTION(".sdata") aCigs[] = "CIGS";
const char SECTION(".sdata") aLv[] = "LV.";
const char SECTION(".sdata") aNoItem[] = "NO ITEM";

int SECTION(".sdata") dword_800AB574 = 0;
int SECTION(".sdata") dword_800AB578 = 0;

const char SECTION(".sdata") aEquip[] = "EQUIP";
struct PANEL_CONF *SECTION(".sdata") dword_800AB584 = 0;
const char SECTION(".sdata") aPsg1[] = "PSG1";
const char SECTION(".sdata") aChaffG[] = "CHAFF.G";
const char SECTION(".sdata") aStunG[] = "STUN.G";
const char SECTION(".sdata") aC4_800AB5A0[] = "C4";
const char SECTION(".sdata") aStinger_800AB5A4[] = "STINGER";
const char SECTION(".sdata") aNikita_800AB5AC[] = "NIKITA";
const char SECTION(".sdata") aGrenade_800AB5B4[] = "GRENADE";
const char SECTION(".sdata") aFamas_800AB5BC[] = "FA-MAS";
const char SECTION(".sdata") aSocom[] = "SOCOM";

int SECTION(".sdata") dword_800AB5CC = 0x80011B04;

const char SECTION(".sdata") aMp5Sd[] = "MP 5 SD";
const char SECTION(".sdata") aNoItem_0[] = "NO ITEM";

int SECTION(".sdata") dword_800AB5E0 = 0;
int SECTION(".sdata") dword_800AB5E4 = 0;

const char SECTION(".sdata") aWeapon[] = "WEAPON";
const char SECTION(".sdata") aLife[] = "LIFE";
const char SECTION(".sdata") aO2[] = "O2";

int SECTION(".sdata") gTakeDamageCounter_800AB5FC = 0;

RECT SECTION(".sdata") rect_800AB600 = {960, 256, 50, 80};
short SECTION(".sdata") coords_800AB600[2][2] = {
	{86, 72},
	{44, 72}
};
int SECTION(".sdata") dword_800AB610 = 0x1030402;
int SECTION(".sdata") dword_800AB614 = 0x10304;

const char SECTION(".sdata") aCall[] = "call";
const char SECTION(".sdata") aP3t3t[] = "P#3T#3T";
const char SECTION(".sdata") aMemory[] = "MEMORY";

RECT SECTION(".sdata") rect_800AB630 = {960, 260, 63, 76};

int SECTION(".sdata") dword_800AB638 = 0x36B0;
