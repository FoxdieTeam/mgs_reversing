#include "linker.h"
#include "psyq.h"
#include "overlays/s00a/Enemy/enemy.h"

const char s00a_aResetmaxdnumd_800E083C[] = "reset max=%d num=%d \n";
const char aGmenemywatchcountd_800E0854[] = " GM_EnemyWatchCount = [%d] \n";
const char aNowzonedrzoned_800E0874[] = " now zone = %d r_zone=%d\n";
const char aNotrestrctedaread_800E0890[] = " ? ? ? Not Restrcted Area [%d] !!!!\n";
const char aErrerrerrnotlinkroutedtod_800E08B8[] = " Err Err Err Not Link Route [%d] to [%d] !!!!\n";
const char aCommanderrnozoneidingclzdidd_800E08E8[] = "command:!!!Err No Zone ID In Gcl z%d id%d!!!!!!!!\n";
const char aCommandcwhereissnake_800E091C[] = "command.c:  Where Is Snake ????\n";
const char aCom_noisemode_disD_800E0940[] = " COM_NOISEMODE_DIS =%d \n";
const char aEeeDDDTD_800E095C[] = "eee %d %d %d t %d \n";
const char aCommandC_800E0970[] = {'c', 'o', 'm', 'm', 'a', 'n', 'd', '.', 'c', 0x0, 'W', 'h'};

// Enemy/eyeflash.c
const RECT eyeflash_rect = {175, 100, 350, 200};
const char s00a_aKirari_800E0984[] = "kirari";
const char s00a_aEyeflashc_800E098C[] = {'e', 'y', 'e', 'f', 'l', 'a', 's', 'h', '.', 'c', 0x0, 'h'};

// Enemy/asiato.c
const char aAsiatoc_800E0998[] = {'a', 's', 'i', 'a', 't', 'o', '.', 'c', 0x0, 0xBA, 0x0A, 0x80};

// Enemy/l_sight.c
const char aLSightC[] = {'l', '_', 's', 'i', 'g', 'h', 't', '.', 'c', 0x0, 's', 0x8};

// Enemy/grnad_e.c
const char aGrenadeModelD[] = "grenade model=%d \n";
const char aGrnadEC[] = {'g', 'r', 'n', 'a', 'd', '_', 'e', '.', 'c', 0x0, 'e', 't'};

const int s01a_dword_800E4490 = 0x800D5810;
const int s01a_dword_800E4494 = 0x800D5840;
const int s01a_dword_800E4498 = 0x800D5870;
const int s01a_dword_800E449C = 0x800D58E8;
const int s01a_dword_800E44A0 = 0x800D5880;
const int s01a_dword_800E44A4 = 0x800D58E8;
const int s01a_dword_800E44A8 = 0x800D58A4;
const char s01a_aCamarm_800E44AC[] = "cam_arm";
const char s01a_aCameral_800E44B4[] = "camera_l";
const char s01a_aScamera_800E44C0[] = "s_camera";
const char s01a_dword_800E44CC[] = {'c', 'a', 'm', 'e'};
const char s01a_dword_800E44D0[] = {'r', 'a', '.', 'c'};
const char s01a_dword_800E44D4[] = {0x0, 'f', 'l', 'a'};

const char anim_data_800E44D8[] = {0x0, 0x1d, 0x3, 0x0};
const char s01a_dword_800E44DC[] = {0x9, 0x0, 0x10, 0x0};
const char s01a_dword_800E44E0[] = {0x1b, 0x9, 0xb, 0xb8};
const char s01a_dword_800E44E4[] = {0x2, 0x0, 0x1, 0xf};
const char s01a_dword_800E44E8[] = {0x7, 0x3, '\n', 0xff};
const char s01a_dword_800E44EC[] = {'8', 0xff, '8', 0x2};
const char s01a_dword_800E44F0[] = {0x0, 0x1, 0xf, 0x7};
const char s01a_dword_800E44F4[] = {0x3, '\n', 0xfe, 0x98};
const char s01a_dword_800E44F8[] = {0xfe, 0xfc, 0x2, 0x0};
const char s01a_dword_800E44FC[] = {0x1, 0xf, 0x0, 0x0};

const char anim_data_800E4500[] = {0x0, 0x13, 0x1, 0x0};
const char s01a_dword_800E4504[] = {0x5, 0xc, 0x0, 0x7};
const char s01a_dword_800E4508[] = {0x1, 0xff, '\n', 0x0};
const char s01a_dword_800E450C[] = {'F', 0x0, 'F', 0x8};
const char s01a_dword_800E4510[] = {0xf0, 0xf0, 0xf0, 0x2};
const char s01a_dword_800E4514[] = {0x0, 0x1, 0xd, 0xf};

const char anim_data_800E4518[] = {0x0, '[', 0x4, 0x0};
const char s01a_dword_800E451C[] = {0xb, 0x0, 0x1e, 0x0};
const char s01a_dword_800E4520[] = {'6', 0x0, 'N', 0xc};
const char s01a_dword_800E4524[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4528[] = {'\n', 0x0, 0xc8, 0x0};
const char s01a_dword_800E452C[] = {0xc8, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E4530[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E4534[] = {0xd, 0xf, '\n', 0x1};
const char s01a_dword_800E4538[] = {0x90, 0x1, 0x90, 0xc};
const char s01a_dword_800E453C[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4540[] = {'\n', 0x1, ',', 0x1};
const char s01a_dword_800E4544[] = {',', 0x8, 0xf0, 0xf0};
const char s01a_dword_800E4548[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E454C[] = {0xd, 0xf, '\n', 0x3};
const char s01a_dword_800E4550[] = {' ', 0x3, ' ', 0xc};
const char s01a_dword_800E4554[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4558[] = {'\n', 0x1, 0x90, 0x1};
const char s01a_dword_800E455C[] = {0x90, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E4560[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E4564[] = {0xd, 0xf, '\n', 0x4};
const char s01a_dword_800E4568[] = {0xb0, 0x4, 0xb0, 0xc};
const char s01a_dword_800E456C[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4570[] = {'\n', 0x1, 0xf4, 0x1};
const char s01a_dword_800E4574[] = {0xf4, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E4578[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E457C[] = {0xd, 0xf, 0x0, 0x0};

const char anim_data_800E4580[] = {0x0, 'k', 0x4, 0x0};
const char s01a_dword_800E4584[] = {0xb, 0x0, '"', 0x0};
const char s01a_dword_800E4588[] = {'>', 0x0, 'Z', 0x8};
const char s01a_dword_800E458C[] = {0xff, 0xff, 0xff, 0xc};
const char s01a_dword_800E4590[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4594[] = {'\n', 0x0, 0xc8, 0x0};
const char s01a_dword_800E4598[] = {0xc8, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E459C[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E45A0[] = {0xd, 0xf, 0x8, 0xff};
const char s01a_dword_800E45A4[] = {0xff, 0xff, '\n', 0x1};
const char s01a_dword_800E45A8[] = {0x90, 0x1, 0x90, 0xc};
const char s01a_dword_800E45AC[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E45B0[] = {'\n', 0x1, ',', 0x1};
const char s01a_dword_800E45B4[] = {',', 0x8, 0xf0, 0xf0};
const char s01a_dword_800E45B8[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E45BC[] = {0xd, 0xf, 0x8, 0xff};
const char s01a_dword_800E45C0[] = {0xff, 0xff, '\n', 0x3};
const char s01a_dword_800E45C4[] = {' ', 0x3, ' ', 0xc};
const char s01a_dword_800E45C8[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E45CC[] = {'\n', 0x1, 0x90, 0x1};
const char s01a_dword_800E45D0[] = {0x90, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E45D4[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E45D8[] = {0xd, 0xf, 0x8, 0xff};
const char s01a_dword_800E45DC[] = {0xff, 0xff, '\n', 0x4};
const char s01a_dword_800E45E0[] = {0xb0, 0x4, 0xb0, 0xc};
const char s01a_dword_800E45E4[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E45E8[] = {'\n', 0x1, 0xf4, 0x1};
const char s01a_dword_800E45EC[] = {0xf4, 0x8, 0xf0, 0xf0};
const char s01a_dword_800E45F0[] = {0xf0, 0x2, 0x0, 0x1};
const char s01a_dword_800E45F4[] = {0xd, 0xf, 0x0, 0x0};

const char anim_data_800E45F8[] = {0x0, '[', 0x4, 0x0};
const char s01a_dword_800E45FC[] = {0xb, 0x0, 0x1e, 0x0};
const char s01a_dword_800E4600[] = {'6', 0x0, 'N', 0xc};
const char s01a_dword_800E4604[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4608[] = {'\n', 0x0, 0xc8, 0x0};
const char s01a_dword_800E460C[] = {0xc8, 0x8, 0xfc, 0xfc};
const char s01a_dword_800E4610[] = {0xfc, 0x2, 0x0, 0x1};
const char s01a_dword_800E4614[] = {0xd, 0xf, '\n', 0x1};
const char s01a_dword_800E4618[] = {0x90, 0x1, 0x90, 0xc};
const char s01a_dword_800E461C[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4620[] = {'\n', 0x1, ',', 0x1};
const char s01a_dword_800E4624[] = {',', 0x8, 0xfc, 0xfc};
const char s01a_dword_800E4628[] = {0xfc, 0x2, 0x0, 0x1};
const char s01a_dword_800E462C[] = {0xd, 0xf, '\n', 0x3};
const char s01a_dword_800E4630[] = {' ', 0x3, ' ', 0xc};
const char s01a_dword_800E4634[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4638[] = {'\n', 0x1, 0x90, 0x1};
const char s01a_dword_800E463C[] = {0x90, 0x8, 0xfc, 0xfc};
const char s01a_dword_800E4640[] = {0xfc, 0x2, 0x0, 0x1};
const char s01a_dword_800E4644[] = {0xd, 0xf, '\n', 0x4};
const char s01a_dword_800E4648[] = {0xb0, 0x4, 0xb0, 0xc};
const char s01a_dword_800E464C[] = {0x0, 0x7, 0x1, 0xff};
const char s01a_dword_800E4650[] = {'\n', 0x1, 0xf4, 0x1};
const char s01a_dword_800E4654[] = {0xf4, 0x8, 0xfc, 0xfc};
const char s01a_dword_800E4658[] = {0xfc, 0x2, 0x0, 0x1};
const char s01a_dword_800E465C[] = {0xd, 0xf, 'N', 'o'};
const char s01a_dword_800E4660[] = {0x0, 0x0, 0x0, 0x0};
const char s01a_dword_800E4664[] = {0x0, 0xfe, 0x0, 0x0};

const char aSearchliUDRotXLRRotY[] = "UD:ROT.X  LR:ROT.Y\n";
const char aSearchliUDPosXLRPosZ[] = "UD:POS.X  LR:POS.Z\n";
const char aSearchliUDPosYLRAngle[] = "UD:POS.Y  LR:ANGLE\n";
const char aSearchliRot7D7D7D[] = "ROT:%7d %7d %7d\n";
const char aSearchliPos7D7D7D[] = "POS:%7d %7d %7d\n";
const char aSearchliAngle4D[] = "ANGLE:%4d \n";

const SVECTOR SearchliCenter_800E46D8 = {0, 0, 3000, 0};

const char aSearchli0[] = "0";
const char aSearchliShadow[] = "shadow";
const char aSearchliC[] = {'s', 'e', 'a', 'r', 'c', 'h', 'l', 'i', '.', 'c', 0x0, 'e'};

const char anim_data_800E46F8[] = {0x0, 0x1f, 0x4, 0x0};
const char s01a_dword_800E46FC[] = {0xb, 0x0, 0xf, 0x0};
const char s01a_dword_800E4700[] = {0x18, 0x0, '!', 0x2};
const char s01a_dword_800E4704[] = {0x0, 0x1, 0xf, '\n'};
const char s01a_dword_800E4708[] = {0xff, 0xce, 0xff, 0xce};
const char s01a_dword_800E470C[] = {0x2, 0x0, 0x1, 0xf};
const char s01a_dword_800E4710[] = {'\n', 0xff, 0x9c, 0xff};
const char s01a_dword_800E4714[] = {0x9c, 0x2, 0x0, 0x1};
const char s01a_dword_800E4718[] = {0xf, '\n', 0xff, 'j'};
const char s01a_dword_800E471C[] = {0xff, 'j', 0x2, 0x0};
const char s01a_dword_800E4720[] = {0x1, 0xf, 0x0, 0x0};
const char anim_data_800E4724[] = {0x0, 0x10, 0x1, 0x0};
const char s01a_dword_800E4728[] = {0x5, 0x2, 0x0, 0x1};
const char s01a_dword_800E472C[] = {0x8, 0xf0, 0xf0, 0xf0};
const char s01a_dword_800E4730[] = {'\n', 0x3, 0xe8, 0x3};
const char s01a_dword_800E4734[] = {0xe8, 0x2, 0x0, 0x1};
const char s01a_dword_800E4738[] = {0xf, 0x0, 0x0, 0x0};
const char anim_data_800E473C[] = {0x0, 0x8, 0x1, 0x0};
const char s01a_dword_800E4740[] = {0x5, 0xc, 0x0, '<'};
const char s01a_dword_800E4744[] = {0x2, 0x0, 0x1, 0xd};
const char s01a_dword_800E4748[] = {0xf, 0x0, 0x0, 0x0};
const char anim_data_800E474C[] = {0x0, 0xd, 0x2, 0x0};
const char s01a_dword_800E4750[] = {0x7, 0x0, 0xb, 0x2};
const char s01a_dword_800E4754[] = {0x0, 0x1, 0xf, '\n'};
const char s01a_dword_800E4758[] = {0xfe, 'p', 0xfe, 'p'};
const char s01a_dword_800E475C[] = {0x2, 0x0, 0x1, 0xf};
const char anim_data_800E4760[] = {0x0, 0x4, 0x1, 0x0};
const char s01a_dword_800E4764[] = {0x5, 0x2, 0x0, 0x1};
const char s01a_dword_800E4768[] = {0xf, 0x0, 0x0, 0x0};

const char anim_data_800E476C[] = {0x0, 0x13, 0x1, 0x0};
const char s01a_dword_800E4770[] = {0x5, 0x8, 0xc8, 0xc8};
const char s01a_dword_800E4774[] = {0xff, 0x2, 0x0, 0x1};
const char s01a_dword_800E4778[] = {0xc, 0x0, 0x1f, 0x8};
const char s01a_dword_800E477C[] = {0xfa, 0xfa, 0xf8, 0x2};
const char s01a_dword_800E4780[] = {0x0, 0x1, 0xd, 0xf};

int SECTION("overlay.bss") s01a_dword_800E4B24;

short SECTION("overlay.bss") sphere_image_width_800E4B28;
short SECTION("overlay.bss") sphere_image_height_800E4B2A;
short SECTION("overlay.bss") sphere_visible_tiles_x_800E4B2C;
short SECTION("overlay.bss") sphere_visible_tiles_y_800E4B2E;
short SECTION("overlay.bss") sphere_tiles_x_800E4B30;
short SECTION("overlay.bss") sphere_tiles_y_800E4B32;
short SECTION("overlay.bss") sphere_tile_width_800E4B34;
short SECTION("overlay.bss") sphere_tile_height_800E4B36;
short SECTION("overlay.bss") sphere_elevation_800E4B38;
short SECTION("overlay.bss") sphere_word_800E4B3A;

int SECTION("overlay.bss") s00a_dword_800E0C9C;

int SECTION("overlay.bss") s00a_dword_800E0CA0;
int SECTION("overlay.bss") s00a_dword_800E0CA4;
int SECTION("overlay.bss") s00a_dword_800E0CA8;
int SECTION("overlay.bss") s00a_dword_800E0CAC;

GM_Camera SECTION("overlay.bss") s00a_dword_800E0CB0;

int SECTION("overlay.bss") s00a_dword_800E0D2C;
int SECTION("overlay.bss") s00a_dword_800E0D30;
int SECTION("overlay.bss") s00a_dword_800E0D34;

SVECTOR SECTION("overlay.bss") s00a_dword_800E0D38;

int SECTION("overlay.bss") COM_PlayerOnZone_800E0D40;

int SECTION("overlay.bss") COM_NoiseMinDisID_800E0D44;

SVECTOR SECTION("overlay.bss") COM_PlayerPositionOne_800E0D48[8];

int SECTION("overlay.bss") COM_SHOOTRANGE_800E0D88;
int SECTION("overlay.bss") COM_EYE_LENGTH_800E0D8C;
int SECTION("overlay.bss") COM_PlayerAddress_800E0D90;
unsigned int SECTION("overlay.bss") ENE_SPECIAL_FLAG_800E0D94;

ENEMY_COMMAND SECTION("overlay.bss") EnemyCommand_800E0D98;

int SECTION("overlay.bss") COM_PlayerMap_800E0F1C;

TOPCOMMAND_STRUCT SECTION("overlay.bss") TOPCOMMAND_800E0F20;

TOPCOMMAND_STRUCT SECTION("overlay.bss") s00a_dword_800E0F28;

SVECTOR SECTION("overlay.bss")  COM_PlayerPosition_800E0F30;

int SECTION("overlay.bss") COM_NOISEMODE_DIS_800E0F38;

unsigned int SECTION("overlay.bss") COM_GameStatus_800E0F3C;

int SECTION("overlay.bss") COM_PlayerAddressOne_800E0F40[8];

int SECTION("overlay.bss") COM_ALERT_DECREMENT_800E0F60;

int SECTION("overlay.bss") GM_GameFlag_800E0F64;

int SECTION("overlay.bss") COM_VibTime_800E0F68;

int SECTION("overlay.bss") s00a_dword_800E0F6C;

int SECTION("overlay.bss") COM_PlayerMapOne_800E0F70[8];

int SECTION("overlay.bss") s00a_dword_800E0F90;

int SECTION("overlay.bss") s00a_dword_800E0F94;
