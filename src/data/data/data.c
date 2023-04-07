#include "linker.h"
#include "data.h"

#include "data/rdata/rdata.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Menu/menuman.h"
#include "libdg/libdg.h"
#include "Thing/door.h"
#include "mts/mts_new.h"
#include "Anime/animeconv/anime.h"
#include "Game/game.h"
#include "Game/control.h"
#include "chara/snake/sna_init.h"
#include "Equip/bodyarm.h"
#include "Equip/box.h"
#include "Equip/bandana.h"
#include "Equip/gasmask.h"
#include "Equip/jpegcam.h"
#include "Equip/kogaku2.h"
#include "Equip/scope.h"
#include "Equip/tabako.h"
#include "libgcl/hash.h"
#include "Menu/menuman.h"
#include "Menu/radio.h"
#include "Okajima/d_blood.h"
#include "Takabe/goggle.h"
#include "Takabe/goggleir.h"
#include "Bullet/blast.h"
#include "Weapon/aam.h"
#include "Menu/radar.h"

// sdata
extern const char *aCigs[];
extern const char *aSocom[];
extern const char *aFamas_800AB5BC[];
extern const char *aGrenade_800AB5B4[];
extern const char *aNikita_800AB5AC[];
extern const char *aStinger_800AB5A4[];
extern const char *aClaymore[];
extern const char *aC4_800AB5A0[];
extern const char *aStunG[];
extern const char *aChaffG[];
extern const char *aPsg1[];

extern const char *aScope[];
extern const char *aCBoxA[];
extern const char *aCBoxB[];
extern const char *aCBoxC[];
extern const char *aNVG[];
extern const char *aThermG[];
extern const char *aGasmask[];
extern const char *aBArmor[];
extern const char *aKetchup[];
extern const char *aStealth[];
extern const char *aBandana[];
extern const char *aCamera[];
extern const char *aRation[];
extern const char *aMedicine[];
extern const char *aDiazepam[];
extern const char *aPalKey[];
extern const char *aCard[];
extern const char *aTimerB[];
extern const char *aMineD[];
extern const char *aDisc[];
extern const char *aRope[];
extern const char *aScarf[];
extern const char *aSuppr[];

extern const char  aLife[];
extern const char  aO2[];
extern const char *aError[];
extern const char *aComplete[];
extern const char *dword_800AB728[];
extern const char *dword_800AB724[];
extern const char *dword_800AB720[];
extern const char *aEx[];
extern const char *aMemoryCard1[];
extern const char *aMemoryCard2[];
extern const char *dword_800AB754[];
extern const char *aNo[];
extern const char *dword_800122D8[];
extern const char *dword_800122CC[];
extern const char *dword_800122C0[];
extern const char *dword_800122B4[];
extern const char *dword_800122A8[];
extern const char *aSaveData[];
extern const char  aSnaChest1[];
extern const char  aSnaChest2[];
extern const char  aSnaChest3[];
extern const char  aSnaHip1[];
extern const char  aSnaArmer1[];
extern const char  aSnaArmer2[];
extern const char  aSnaArmer3[];
extern const char  aSnaArmer4[];
extern const char  aCbBox11[];
extern const char  aCbBox12[];
extern const char  aCbBox41[];
extern const char  aCbBox42[];
extern const char  aCbBox21[];
extern const char  aCbBox22[];
extern const char  aCbBox41[];
extern const char  aCbBox42[];
extern const char  aSnaFace[];
extern const char  aSnaFace2[];
extern const char  aSnaFace3[];
extern const char  aSnaMf1[];
extern const char  aSnaMf2[];
extern const char  aSnaMf3[];

GCL_ActorTableEntry SECTION(".data") MainCharacterEntries_8009D2DC[] = {
    {CHARA_SNAKE, sna_init_NewSnake_8005B650},
    {CHARA_ITEM, (TGCL_ActorCreateFn)0x800344F8},
    {CHARA_DOOR, NewDoor_8006FD00},
    {0, 0}};

const char *SECTION(".data") MGS_DiskName_8009D2FC[] = {"SLPM_862.47", "SLPM_862.48", 0};

struct PauseKill SECTION(".data") gPauseKills_8009D308[9] = {{0, 7},  {0, 7},  {9, 4}, {9, 4}, {15, 4},
                                                             {15, 4}, {15, 4}, {9, 4}, {0, 7}};

short SECTION(".data") key_table_8009D32C[] = {0x0000, 0x0800, 0x0400, 0x0600, 0x0000, 0x0000, 0x0200, 0x0000,
                                               0x0C00, 0x0A00, 0x0000, 0x0000, 0x0E00, 0x0000, 0x0000, 0x0000};

VECTOR SECTION(".data") vector_8009D34C = {0, -4096, 0, 0};

void DG_Screen_Chanl_8001CEE0(DG_CHNL *pOt, int idx);
void DG_BoundChanl_800189A4(DG_CHNL *pOt, int idx);
void DG_Trans_Chanl_8001E3C0(DG_CHNL *pOt, int idx);
void DG_Shade_Chanl_8001D324(DG_CHNL *pOt, int idx);
void DG_PrimChanl_8001B66C(DG_CHNL *pOt, int idx);
void DG_DivideChanl_80019D44(DG_CHNL *pOt, int idx);
void DG_Sort_Chanl_8001D5C8(DG_CHNL *pOt, int idx);

// rendering stack ? gLibDg_FuncPtrs_off_6500E0
TChanl_Fn SECTION(".data") off_8009D35C[] = {DG_Screen_Chanl_8001CEE0, DG_BoundChanl_800189A4, DG_Trans_Chanl_8001E3C0,
                                             DG_Shade_Chanl_8001D324,  DG_PrimChanl_8001B66C,  DG_DivideChanl_80019D44,
                                             DG_Sort_Chanl_8001D5C8};

DG_TEX SECTION(".data") DG_UnknownTexture_8009D378 = {0, {.s = 0}, 0, 0, 0, 0, 0, 0};

MATRIX SECTION(".data") DG_LightMatrix_8009D384 = {
    {{0x0000, 0x0000, 0x1000}, {0x0000, 0x0000, 0x0000}, {0x0000, 0x0000, 0x0000}}, {0, 0, 0}};

MATRIX SECTION(".data") DG_ColorMatrix_8009D3A4 = {
    {{0x1000, 0x1000, 0x1000}, {0x1000, 0x1000, 0x1000}, {0x1000, 0x1000, 0x1000}}, {0, 0, 0}};

int SECTION(".data") dword_8009D3C4[] = {0, 0, 0};

//	DG_PRIM_LINE_FT2, DG_PRIM_LINE_GT2,
//	DG_PRIM_FREE
// DG_PRIM_TILE_1  DG_PRIM_TILE_8, DG_PRIM_TILE_16

//  int psize, int verts, int voffset, int vstep ??

struct DG_Rec_Unknown SECTION(".data") stru_8009D3D0[24] = {{16, 2, 8, 4},  // LINE_F2 DG_PRIM_LINE_FT2
                                                            {24, 3, 8, 4},  // LINE_F3
                                                            {28, 4, 8, 4},  // LINE_F4
                                                            {20, 2, 8, 8},  // LINE_G2
                                                            {32, 3, 8, 8},  // LINE_G3
                                                            {40, 4, 8, 8},  // LINE_G4
                                                            {20, 1, 8, 0},  // SPRT
                                                            {16, 1, 8, 0},  // SPRT_16  ?
                                                            {16, 1, 8, 0},  // SPRT_8  ?
                                                            {16, 1, 8, 0},  // TILE ?
                                                            {12, 1, 8, 0},  // TILE_16  ?
                                                            {12, 1, 8, 0},  // TILE_8 ?
                                                            {12, 1, 8, 0},  // TILE_1 ?
                                                            {20, 3, 8, 4},  // POLY_F3 DG_PRIM_POLY_F3
                                                            {24, 4, 8, 4},  // POLY_F4 DG_PRIM_POLY_F4
                                                            {28, 3, 8, 8},  // POLY_G3 DG_PRIM_POLY_G3
                                                            {36, 4, 8, 8},  // POLY_G4 DG_PRIM_POLY_G4
                                                            {32, 3, 8, 8},  // POLY_FT3 DG_PRIM_POLY_FT3
                                                            {40, 4, 8, 8},  // POLY_FT4 DG_PRIM_POLY_FT4
                                                            {40, 3, 8, 12}, // POLY_GT3 DG_PRIM_POLY_GT3
                                                            {52, 4, 8, 12}, // POLY_GT4 DG_PRIM_POLY_GT4
                                                            {40, 2, 8, 8},  {52, 2, 8, 12}, {12, 1, 8, 0}};

MATRIX SECTION(".data") DG_ZeroMatrix_8009D430 = {
    {{0x1000, 0x0000, 0x0000}, {0x0000, 0x1000, 0x0000}, {0x0000, 0x0000, 0x1000}}, {0, 0, 0}};

DG_TEX SECTION(".data") dword_8009D450 = {};
int    SECTION(".data") DG_FrameRate_8009D45C = 2;
int    SECTION(".data") DG_HikituriFlag_8009D460 = 0;
int    SECTION(".data") DG_HikituriFlagOld_8009D464 = 0;
int    SECTION(".data") dword_8009D468 = -1;

int GCL_Command_if_80020274(char *top);
int GCL_Command_eval_80020318(unsigned char *pScript);
int GCL_Cmd_Return_80020404(void);
int GCL_Command_foreach_8002033C(unsigned char *pScript);

// kVertexIndexingOrder_8009D46C provides the indexing order for referencing the transformed vertex sections
unsigned char kVertexIndexingOrder_8009D46C[] = {0, 1, 3, 2};

GCL_COMMANDLIST SECTION(".data") commlist_8009D470[] = {{HASH_CMD_if, (TGCL_CommandFn)&GCL_Command_if_80020274},
                                                        {HASH_CMD_eval, &GCL_Command_eval_80020318},
                                                        {HASH_CMD_return, (TGCL_CommandFn)&GCL_Cmd_Return_80020404},
                                                        {HASH_CMD_foreach, &GCL_Command_foreach_8002033C}};

GCL_COMMANDDEF SECTION(".data") builtin_commands_8009D490 = {0, COUNTOF(commlist_8009D470), commlist_8009D470};

FS_FILE_INFO_8009D49C SECTION(".data") gDirFiles_8009D49C[] = {
    {aStageDir, 0}, {aRadioDat, 0}, {aFaceDat, 0}, {aZmovieStr, 0}, {aVoxDat, 0}, {aDemoDat, 0}, {aBrfDat, 0}, {0, 0}};

int SECTION(".data") dword_8009D4DC = -1;
int SECTION(".data") dword_8009D4E0 = 0;
int SECTION(".data") dword_cdbios_stop_8009D4E4 = 0;

FS_FILE_TABLE SECTION(".data") fs_file_table_8009D4E8 = {0, 0, 0, 0};

TFsCallback      SECTION(".data") gFsCallback_8009D4F8 = NULL;
TFsSoundCallback SECTION(".data") gFsSoundCallback_8009D4FC = NULL;

int   SECTION(".data") dword_8009D500 = 0;
short SECTION(".data") word_8009D504 = 0;
short SECTION(".data") word_8009D506 = 0;
short SECTION(".data") word_8009D508 = 0;

FS_MOVIE_FILE_TABLE *SECTION(".data") fs_movie_file_table_8009D50C = 0;

int SECTION(".data") fs_stream_tick_start_8009D510 = -1;
int SECTION(".data") fs_dword_8009D514 = 0;
int SECTION(".data") fs_stream_is_force_stop_8009D518 = 0;
int SECTION(".data") fs_stream_end_flag_8009D51C = 1;
int SECTION(".data") fs_dword_8009D520 = 0;
int SECTION(".data") gmem_card_system_inited_8009D524 = 0;

short SECTION(".data") TimeInv_8009D528[] = {0x0, 0x800, 0x555, 0x400, 0x333, 0x2AA, 0x249, 0x200,
                                             0x1C7, 0x199, 0x174, 0x155, 0x13B, 0x124, 0x111, 0x100};
int SECTION(".data") dword_8009D548[] = {0, 0x20, 0x40, 8, 0x800, 0x10000, 0x20000, 0x1000, 4, 1};
int SECTION(".data") dword_8009D570[] = {0x20, 0x80, 0x40, 0x10};

int SECTION(".data") GM_WeaponTypes_8009D580[] = {0x90420110, 0x414C9043, 0x222020C0, 0x41104110, 0x414C414C, 0x9220};
unsigned short SECTION(".data") GM_ItemTypes_8009D598[] = {
    0x0000, 0x8000, 0x8003, 0x8001, 0x8001, 0x8001, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8003, 0x2000, 0x2000,
    0x2000, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int GCL_Command_mesg_8002C138(int argc, char **argv);
int GCL_Command_trap_8002BD34(int argc, char **argv);
int GCL_Command_chara_8002C1B0(int argc, char **argv);
int GCL_Command_map_8002BB44(int argc, char **argv);
int GCL_Command_hzd_8002BD04(int argc, char **argv);
int GCL_Command_camera_8002B8F0(int argc, char **argv);
int GCL_Command_light_8002B854(int argc, char **argv);
int GCL_Command_start_8002C22C(int argc, char **argv);
int GCL_Command_load_8002C308(int argc, char **argv);
int GCL_Command_radio_8002C4A8(int argc, char **argv);
int GCL_Command_strstatus_8002C6A4(int argc, char **argv);
int GCL_Command_demo_8002C890(int argc, char **argv);
int GCL_Command_ntrap_8002BE20(int argc, char **argv);
int GCL_Command_delay_8002C074(int argc, char **argv);
int GCL_Command_pad_8002C988(int argc, char **argv);
int GCL_Command_varsave_8002C72C(int argc, char **argv);
int GCL_Command_system_8002C7C8(void);
int GCL_Command_sound_8002CA28(int argc, char **argv);
int GCL_Command_menu_8002CAAC(void);
int GCL_Command_rand_8002CD94(int argc, char **argv);
int GCL_Command_unknown1_8002CDF4(int argc, char **argv);
int GCL_Command_unknown2_8002CFBC(int argc, char **argv);
int GCL_Command_print_8002D0E4(int argc, char **argv);
int GCL_Command_jimaku_8002D188(int argc, char **argv);

GCL_COMMANDLIST SECTION(".data") Commands_8009D5CC[] = {
    {HASH_CMD_mesg, (TGCL_CommandFn)&GCL_Command_mesg_8002C138},
    {HASH_CMD_trap, (TGCL_CommandFn)&GCL_Command_trap_8002BD34},
    {HASH_CMD_chara, (TGCL_CommandFn)&GCL_Command_chara_8002C1B0},
    {HASH_CMD_map, (TGCL_CommandFn)&GCL_Command_map_8002BB44},
    {HASH_CMD_hzd, (TGCL_CommandFn)&GCL_Command_hzd_8002BD04},
    {HASH_CMD_camera, (TGCL_CommandFn)&GCL_Command_camera_8002B8F0},
    {HASH_CMD_light, (TGCL_CommandFn)&GCL_Command_light_8002B854},
    {HASH_CMD_start, (TGCL_CommandFn)&GCL_Command_start_8002C22C},
    {HASH_CMD_load, (TGCL_CommandFn)&GCL_Command_load_8002C308},
    {HASH_CMD_radio, (TGCL_CommandFn)&GCL_Command_radio_8002C4A8},
    {HASH_CMD_str_status, (TGCL_CommandFn)&GCL_Command_strstatus_8002C6A4},
    {HASH_CMD_demo, (TGCL_CommandFn)&GCL_Command_demo_8002C890},
    {HASH_CMD_ntrap, (TGCL_CommandFn)&GCL_Command_ntrap_8002BE20},
    {HASH_CMD_delay, (TGCL_CommandFn)&GCL_Command_delay_8002C074},
    {HASH_CMD_pad, (TGCL_CommandFn)&GCL_Command_pad_8002C988},
    {HASH_CMD_varsave, (TGCL_CommandFn)&GCL_Command_varsave_8002C72C},
    {HASH_CMD_system, (TGCL_CommandFn)&GCL_Command_system_8002C7C8},
    {HASH_CMD_sound, (TGCL_CommandFn)&GCL_Command_sound_8002CA28},
    {HASH_CMD_menu, (TGCL_CommandFn)&GCL_Command_menu_8002CAAC},
    {HASH_CMD_rand, (TGCL_CommandFn)&GCL_Command_rand_8002CD94},
    {HASH_CMD_unk1, (TGCL_CommandFn)&GCL_Command_unknown1_8002CDF4}, // ??
    {HASH_CMD_unk2, (TGCL_CommandFn)&GCL_Command_unknown2_8002CFBC}, // ?? not in pc ver, demo thread related ??
    {HASH_CMD_print, (TGCL_CommandFn)&GCL_Command_print_8002D0E4},
    {HASH_CMD_jimaku, (TGCL_CommandFn)&GCL_Command_jimaku_8002D188}};

GCL_COMMANDDEF SECTION(".data") script_commands_8009D68C = {0, COUNTOF(Commands_8009D5CC), Commands_8009D5CC};

char SECTION(".data") byte_8009D698[] = {0x00, 0x00, 0x01, 0x02};

int SECTION(".data") dword_8009D69C[] = {
    0x42801EE, 0x666056E, 0x7DA072E, 0x8F4086E, 0x9DA096C, 0xA9A0A3E, 0xB3E0AEE, 0xBCE0B88, 0xC4C0C0E, 0xCBC0C86,
    0xD200CEF, 0xD780D4E, 0xDC80DA2, 0xE100DEE, 0xE520E32, 0xE8C0E6F, 0xEC00EA6, 0xEEF0ED8, 0xF190F04, 0xF3F0F2C,
    0xF600F50, 0xF7E0F6F, 0xF980F8B, 0xFAE0FA3, 0xFC20FB8, 0xFD20FCA, 0xFE00FD9, 0xFEB0FE6, 0xFF30FEF, 0xFFA0FF7,
    0xFFE0FFC, 0xFFF0FFF, 0x28800B2, 0x4C003C6, 0x6440590, 0x77406E4, 0x86C07F6, 0x94008DA, 0x9F809A0, 0xA9A0A4C,
    0xB280AE2, 0xBA80B6A, 0xC1C0BE4, 0xC860C52, 0xCE40CB6, 0xD3A0D10, 0xD8A0D62, 0xDD10DAE, 0xE130DF2, 0xE4F0E32,
    0xE860E6B, 0xEB80E9F, 0xEE50ECF, 0xF0E0EFA, 0xF340F22, 0xF560F46, 0xF750F66, 0xF900F83, 0xFA90F9D, 0xFBE0FB4,
    0xFD10FC8, 0xFE20FDA, 0xFF00FE9, 0xFFC0FF6, 0x196005C, 0x3740298, 0x4E00434, 0x60C057C, 0x70A0690, 0x7E6077C,
    0x8AA084A, 0x9580902, 0x9F409A8, 0xA840A3E, 0xB060AC6, 0xB7C0B42, 0xBEA0BB4, 0xC4E0C1D, 0xCAC0C7E, 0xD020CD7,
    0xD510D2A, 0xD9A0D76, 0xDDF0DBE, 0xE1E0E00, 0xE590E3C, 0xE900E75, 0xEC20EAA, 0xEF10EDA, 0xF1C0F07, 0xF440F30,
    0xF690F57, 0xF8B0F7A, 0xFAA0F9A, 0xFC60FB8, 0xFE00FD3, 0xFF70FEC, 0x1100038, 0x28401D2, 0x3BE0326, 0x4D0044C,
    0x5C2054C, 0x69C0632, 0x7600700, 0x81407BC, 0x8BA0868, 0x9520906, 0x9DE099A, 0xA620A20, 0xADC0AA0, 0xB4C0B14,
    0xBB80B83, 0xC1B0BEA, 0xC780C4A, 0xCD00CA6, 0xD230CFA, 0xD710D4A, 0xDBA0D96, 0xDFE0DDD, 0xE400E20, 0xE7C0E5E,
    0xEB60E9A, 0xEEC0ED1, 0xF1F0F06, 0xF4E0F37, 0xF7C0F65, 0xFA60F91, 0xFCD0FBA, 0xFF20FE0, 0xC00026,  0x1DC0152,
    0x2DE0260, 0x3CA0356, 0x4A4043A, 0x56E050C, 0x62C05CE, 0x6DC0684, 0x7800730, 0x81C07D0, 0x8AE0866, 0x93A08F6,
    0x9BC097C, 0xA3A09FC, 0xAAF0A74, 0xB200AE8, 0xB8A0B56, 0xBF00BBE, 0xC500C20, 0xCAC0C7F, 0xD040CD9, 0xD580D2F,
    0xDA80D81, 0xDF60DD0, 0xE3E0E1A, 0xE840E62, 0xEC80EA6, 0xF080EE8, 0xF440F26, 0xF7F0F62, 0xFB60F9B, 0xFEC0FD2,
    0x8C001C,  0x16600FA, 0x23401CE, 0x2F80298, 0x3B40358, 0x4680410, 0x51404BE, 0x5B80568, 0x6560608, 0x6EE06A4,
    0x7820738, 0x80E07C8, 0x8960852, 0x91808D8, 0x9960958, 0xA1009D4, 0xA860A4C, 0xAF80AC0, 0xB660B2F, 0xBD00B9C,
    0xC360C04, 0xC9A0C69, 0xCFB0CCB, 0xD580D2A, 0xDB30D86, 0xE0A0DE0, 0xE600E36, 0xEB20E8A, 0xF020EDA, 0xF500F2A,
    0xF9C0F76, 0xFE40FC0, 0x680014,  0x11000BC, 0x1B20162, 0x2520204, 0x2F002A2, 0x38A033C, 0x42003D4, 0x4B4046A,
    0x54404FC, 0x5D2058C, 0x65E0618, 0x6E806A4, 0x76E072A, 0x7F207B0, 0x8740832, 0x8F208B4, 0x9700932, 0x9EC09AE,
    0xA640A28, 0xADA0AA0, 0xB500B16, 0xBC20B8A, 0xC340BFA, 0xCA20C6A, 0xD100CD8, 0xD7A0D46, 0xDE40DB0, 0xE4C0E18,
    0xEB20E80, 0xF160EE4, 0xF7A0F48, 0xFDB0FAA, 0x4F000F,  0xCF008F,  0x14F010F, 0x1CF018F, 0x24F020F, 0x2CF028F,
    0x34F030F, 0x3CF038F, 0x44F040F, 0x4CF048F, 0x54F050F, 0x5CF058F, 0x64F060F, 0x6CF068F, 0x74F070F, 0x7CF078F,
    0x84F080F, 0x8CF088F, 0x94F090F, 0x9CF098F, 0xA4F0A0F, 0xACF0A8F, 0xB4F0B0F, 0xBCF0B8F, 0xC4F0C0F, 0xCCF0C8F,
    0xD4F0D0F, 0xDCF0D8F, 0xE4F0E0F, 0xECF0E8F, 0xF4F0F0F, 0xFCF0F8F, 0x3C000C,  0x9E006C,  0x10000CE, 0x1660132,
    0x1CC0198, 0x2340200, 0x29E0269, 0x30A02D4, 0x3780340, 0x3E803B0, 0x4580420, 0x4CC0492, 0x5400506, 0x5B8057C,
    0x63205F4, 0x6AE066F, 0x72A06EC, 0x7AA076A, 0x82C07EC, 0x8B2086E, 0x93808F4, 0x9C2097E, 0xA4E0A08, 0xADE0A96,
    0xB700B26, 0xC040BB8, 0xC9A0C4E, 0xD360CE8, 0xDD20D84, 0xE740E22, 0xF180EC6, 0xFC00F6C, 0x2C0008,  0x760050,
    0xC2009C,  0x11000E8, 0x1600138, 0x1B4018A, 0x20A01DE, 0x2620235, 0x2BD028F, 0x31C02EC, 0x37C034C, 0x3E003AE,
    0x4480414, 0x4B4047E, 0x52204EA, 0x596055C, 0x60C05D0, 0x6860648, 0x70606C6, 0x78A0748, 0x81207CE, 0x8A0085A,
    0x93408EA, 0x9CE0980, 0xA6E0A1E, 0xB140AC0, 0xBC20B6A, 0xC780C1C, 0xD360CD6, 0xDFC0D98, 0xECE0E64, 0xFAA0F3A,
    0x200006,  0x56003A,  0x8E0072,  0xC900AB,  0x10700E8, 0x1480127, 0x18B0169, 0x1D201AE, 0x21C01F6, 0x26A0242,
    0x2BA0292, 0x31002E4, 0x368033C, 0x3C60396, 0x42803F6, 0x48E045A, 0x4FA04C4, 0x56C0532, 0x5E405A6, 0x6620622,
    0x6E606A2, 0x772072C, 0x80807BC, 0x8A60856, 0x94E08F8, 0xA0009A6, 0xAC00A5E, 0xB8E0B26, 0xC6C0BFC, 0xD5E0CE4,
    0xE660DE0, 0xF8A0EF4, 0x160004,  0x3B0028,  0x64004F,  0x8E0078,  0xBC00A4,  0xEC00D4,  0x1200106, 0x157013B,
    0x1910174, 0x1CF01B0, 0x21001EF, 0x2560233, 0x2A0027B, 0x2F002C8, 0x3440318, 0x39C036F, 0x3FC03CC, 0x460042E,
    0x4CD0496, 0x5400506, 0x5BC057E, 0x64205FE, 0x6D20688, 0x76C071E, 0x81607C0, 0x8CC086E, 0x9960930, 0xA760A04,
    0xB700AEE, 0xC8A0BF8, 0xDD20D28, 0xF560E8A, 0xD0002,   0x250019,  0x400032,  0x5C004E,  0x7C006C,  0x9F008D,
    0xC400B1,  0xED00D8,  0x1190102, 0x1480130, 0x17C0162, 0x1B40198, 0x1F001D1, 0x230020F, 0x2760252, 0x2C1029A,
    0x31202E8, 0x36A033D, 0x3C80398, 0x42F03FA, 0x49E0466, 0x51804DA, 0x59E055A, 0x62E05E4, 0x6D0067E, 0x7840728,
    0x84C07E4, 0x93008BA, 0xA3809B0, 0xB720ACE, 0xCF40C28, 0xEFC0DE2, 0x60001,   0x12000C,  0x210019,  0x320029,
    0x46003C,  0x5C0050,  0x750068,  0x920083,  0xB100A1,  0xD400C2,  0xFA00E6,  0x124010F, 0x153013B, 0x186016C,
    0x1BE01A2, 0x1FC01DC, 0x23E021C, 0x2880262, 0x2D802B0, 0x3310304, 0x3920360, 0x3FE03C6, 0x4740438, 0x4F804B4,
    0x58C0540, 0x63205DC, 0x6F0068E, 0x7CC075A, 0x8D00848, 0xA100968, 0xBB40AD2, 0xE420CCC, 0,         0x20001,
    0x70004,   0xD000A,   0x170012,  0x22001C,  0x310029,  0x420039,  0x56004C,  0x6D0061,  0x88007A,  0xA60097,
    0xC900B7,  0xF000DC,  0x11B0105, 0x14B0132, 0x1810166, 0x1BC019E, 0x1FF01DD, 0x2490223, 0x29B0271, 0x2F602C8,
    0x35D0328, 0x3D00394, 0x4520410, 0x4E6049A, 0x5920538, 0x65A05F2, 0x74A06CC, 0x87807D8, 0xA0C0930, 0xCB80B24};

int SECTION(".data") dword_8009DE1C[] = {0x10000, 0x10000, 0x8000, 0x5555, 0x4000, 0x3333, 0x2AAA, 0x2492,
                                         0x2000,  0x1C71,  0x1999, 0x1745, 0x1555, 0x13B1, 0x1249, 0x1111};

int SECTION(".data") dword_8009DE5C[] = {0x8001000, 0x4000555, 0x2AA0333, 0x2000249,
                                         0x19901C7, 0x1550174, 0x124013B, 0x1000111};
int SECTION(".data") dword_8009DE7C = 0;
int SECTION(".data") dword_8009DE80 = 0;
int SECTION(".data") dword_8009DE84 = 0;
int SECTION(".data") dword_8009DE88 = 0;
int SECTION(".data") dword_8009DE8C[] = {0, 0, 0, 0};
int SECTION(".data") dword_8009DE9C = 0;
int SECTION(".data") dword_8009DEA0 = 0;
int SECTION(".data") dword_8009DEA4 = 0;
int SECTION(".data") dword_8009DEA8 = 0;
int SECTION(".data") dword_8009DEAC[] = {0, 0, 0, 0};

short SECTION(".data") game_over_lines_8009DEBC[] = {
    120, // table length
    37,  88,  25,  104, 25,  104, 31,  121, 31,  121, 40,  121, 40,  121, 32,  135,
    32,  135, 42,  135, 69,  88,  37,  88,  64,  96,  41,  96,  41,  96,  35,  104,
    35,  104, 38,  113, 38,  113, 45,  113, 62,  100, 45,  100, 45,  100, 40,  108,
    40,  108, 48,  108, 48,  108, 45,  113, 69,  88,  64,  96,  55,  121, 65,  121,
    74,  88,  84,  88,  67,  100, 85,  100, 69,  96,  85,  96,  67,  100, 55,  121,
    69,  96,  74,  88,  84,  88,  85,  96,  85,  100, 87,  121, 87,  121, 78,  121,
    73,  108, 77,  108, 78,  121, 77,  108, 73,  108, 65,  121, 62,  100, 42,  135,
    89,  121, 98,  121, 97,  88,  108, 88,  118, 88,  130, 88,  122, 121, 113, 121,
    113, 121, 117, 104, 117, 104, 108, 121, 108, 121, 103, 121, 103, 121, 102, 104,
    102, 104, 98,  121, 95,  96,  108, 96,  114, 96,  128, 96,  94,  100, 108, 100,
    112, 100, 127, 100, 97,  88,  95,  96,  94,  100, 89,  121, 108, 88,  108, 96,
    108, 100, 108, 108, 112, 100, 108, 108, 114, 96,  118, 88,  127, 100, 122, 121,
    128, 96,  130, 88,  134, 88,  156, 88,  126, 121, 148, 121, 132, 96,  154, 96,
    131, 100, 153, 100, 138, 107, 151, 107, 138, 107, 137, 113, 150, 113, 137, 113,
    134, 88,  132, 96,  131, 100, 126, 121, 150, 113, 148, 121, 151, 107, 153, 100,
    154, 96,  156, 88,  173, 121, 199, 121, 181, 88,  207, 88,  179, 96,  205, 96,
    187, 100, 184, 113, 184, 113, 192, 113, 195, 100, 192, 113, 207, 88,  205, 96,
    204, 100, 199, 121, 181, 88,  179, 96,  178, 100, 173, 121, 178, 100, 187, 100,
    195, 100, 204, 100, 213, 121, 224, 121, 241, 88,  231, 88,  210, 88,  219, 88,
    211, 96,  220, 96,  211, 100, 220, 100, 225, 100, 235, 100, 227, 96,  237, 96,
    225, 100, 221, 108, 231, 88,  227, 96,  235, 100, 224, 121, 237, 96,  241, 88,
    211, 100, 213, 121, 210, 88,  211, 96,  219, 88,  220, 96,  220, 100, 221, 108,
    244, 88,  266, 88,  236, 121, 258, 121, 242, 96,  264, 96,  241, 100, 263, 100,
    247, 113, 260, 113, 248, 108, 261, 108, 248, 108, 247, 113, 244, 88,  242, 96,
    241, 100, 236, 121, 263, 100, 261, 108, 260, 113, 258, 121, 266, 88,  264, 96,
    270, 88,  292, 88,  268, 96,  286, 96,  292, 88,  295, 97,  267, 100, 282, 100,
    275, 107, 277, 107, 262, 121, 272, 121, 275, 107, 272, 121, 277, 107, 285, 135,
    285, 135, 295, 135, 286, 106, 295, 135, 286, 106, 288, 106, 288, 106, 295, 97,
    282, 100, 286, 96,  267, 100, 262, 121, 268, 96,  270, 88,  67,  100, 55,  121,
    53,  125, 47,  135, 53,  125, 279, 125, 282, 135, 47,  135, 282, 135, 279, 125};

int SECTION(".data") str_sector_8009E280 = 0;
int SECTION(".data") str_gcl_proc_8009E284 = 0;
int SECTION(".data") str_8009E288 = 0;
int SECTION(".data") dword_8009E28C = 0;

/* For menu code reversing help
enum
{
    MENU_LIFE = 0,
    MENU_WEAPON,
    MENU_ITEM,
    MENU_RADAR,
    MENU_RADIO,
    MENU_CARD,
    MENU_JIMAKU,

    MENU_VIEWER,

    MENU_MODULE_MAX
};


typedef struct {
    char type;
    char res;
    char x;
    char y;
    unsigned short clut[ 1 ];
} TPK_CLUT;

typedef struct {
    char x;
    char y;
    char w;
    char h;
    unsigned short data[ 1 ];
} TPK_DATA;



typedef struct {
    short id;
    short num;
    short pos;
    short current;
} PANEL;

typedef struct PANEL_TEXTURE {
    // TODO: Missing data
    //ed
    char bufid;
    signed char xofs;
    signed char yofs;
    char pad;
    unsigned long uvclut;
    short w;
    short h;
}PANEL_TEXTURE;


typedef struct {
    DR_ENV dr_env[ 2 ];
    RECT clip_rect;
    DR_ENV org_env[ 2 ];
    short pos_x;
    short pos_y;
    char display_flag;
    char prev_mode;
    short counter;
} RADAR_T;

typedef struct {
    PANEL current;
    PANEL_CONF *panel_conf;
}; // TODO Missing data
*/

TInitKillFn SECTION(".data") gMenuInitFns_8009E290[] = {(TInitKillFn)0x8003CC94, // sub_8003CC94 in menu_right
                                                        (TInitKillFn)0x8003B474, // radar
                                                        (TInitKillFn)0x80042700, // menu_radio_init_80042700
                                                        (TInitKillFn)0x8003CBF0, // invent left
                                                        (TInitKillFn)0x8003EC2C, // invent right
                                                        (TInitKillFn)0x8003F7E0, // bars
                                                        (TInitKillFn)0x80042848, // menu_number_init_80042848
                                                        (TInitKillFn)0x800494C4, // menu_jimaku_init_800494C4
                                                        0};

TInitKillFn SECTION(".data") gMenuKillFns_8009E2B4[] = {(TInitKillFn)0x8003B554,
                                                        (TInitKillFn)0x8004271C, // menu_radio_kill_8004271C
                                                        (TInitKillFn)0x8003CC74,
                                                        (TInitKillFn)0x8003ECAC,
                                                        (TInitKillFn)0x8003F838,
                                                        (TInitKillFn)0x80042980, // menu_number_kill_80042980
                                                        0};

MenuGlue SECTION(".data") gMenuPrimBuffer_8009E2D0 = {{0, 0, 0}, {0, 0}};

TextConfig SECTION(".data") gMenuTextConfig_8009E2E4 = {0, 0, 0, 0x64808080};

int SECTION(".data") dword_8009E2F4[] = {0x808000, 0x100000, 0xA0, 0x10, 0xA0A0, 0x808};

radar_uv_pair SECTION(".data") gRadarUV_8009E30C[] = {
    {{128,  80, 28, 12}, {128,  92, 44,  7}},
    {{156,  80, 28, 12}, {128,  99, 58,  7}},
    {{184,  80, 28, 12}, {180,  92, 44,  7}},
    {{138, 106, 58, 12}, {138, 118, 58,  7}},
    {{188,  99, 36,  3}, {128, 106, 10, 16}}
};

radar_uv SECTION(".data") gRadarUV_8009E334 = {196, 102, 28, 22};

// 32x2 image:
short SECTION(".data") image_8009E338[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC210};

int SECTION(".data") gRadarRGBTable_8009E3B8[] = {0x182589, 0x184789, 0x182589, 0x338918};

int SECTION(".data") dword_8009E3C8[] = {0x1371D07, 0x1373207, 0x2032E21};
int SECTION(".data") gRadarRGBTable2_8009E3D4[] = {0x48A000, 0x6E6E, 0xDE, 0x181800};

// Also see dword_8009E5CC.
// Those strings are passed to font_draw_string_80045D0C().
extern char stru_800115CC[];
extern char IT_Scope_8001158C[];
extern char IT_Box1_80011558[];
extern char IT_Box2_80011524[];
extern char IT_Box3_800114F8[];
extern char IT_InfraRedGoogles_80011494[];
extern char IT_NightVisionGoggles_80011434[];
extern char IT_GasMask_800113D0[];
extern char IT_BodyArmor_80011378[];
extern char IT_Ketchup_80011330[];
extern char IT_Stealth_800112D4[];
extern char IT_Bandana_8001127C[];
extern char IT_Camera_80011224[];
extern char IT_Ration_800111B0[];
extern char IT_ColdMedicine_80011150[];
extern char IT_Diazepam_800110E8[];
extern char IT_PalKey_800110AC[];
extern char stru_80011060[];
extern char stru_8001101C[];
extern char IT_MineDetector_80010FD0[];
extern char IT_Disk_80010F84[];
extern char IT_Rope_80010F50[];
extern char IT_Handkerchief_80010F08[];
extern char IT_Suppressor_80010EAC[];
char *SECTION(".data") itm_descriptions_8009E3E4[] = {
    stru_800115CC,
    IT_Scope_8001158C,
    IT_Box1_80011558,
    IT_Box2_80011524,
    IT_Box3_800114F8,
    IT_InfraRedGoogles_80011494,
    IT_NightVisionGoggles_80011434,
    IT_GasMask_800113D0,
    IT_BodyArmor_80011378,
    IT_Ketchup_80011330,
    IT_Stealth_800112D4,
    IT_Bandana_8001127C,
    IT_Camera_80011224,
    IT_Ration_800111B0,
    IT_ColdMedicine_80011150,
    IT_Diazepam_800110E8,
    IT_PalKey_800110AC,
    stru_80011060,
    stru_8001101C,
    IT_MineDetector_80010FD0,
    IT_Disk_80010F84,
    IT_Rope_80010F50,
    IT_Handkerchief_80010F08,
    IT_Suppressor_80010EAC
};
extern char stru_80011644[];
extern char stru_80011614[];
char *SECTION(".data") dword_8009E444[] = {stru_80011644, stru_80011614};

// TODO: This (whole?) buffer is very likely a EUC-JP/SHIFT-JIS string.
// It starts with SHIFT-JIS: "ｰ針震人仁刃ﾐ" and then EUC-JP: "|HARD, EXTREM B"
int SECTION(".data") dword_8009E44C[] = {0x6A9014B0, 0x6C906B90, 0x6E906D90, 0x7C8015D0, 0x44524148,
                                         0x5845202C, 0x4D455254, 0xD0428220, 0x81298206, 0x902F8127,
                                         0x81499048, 0x810D8127, 0xD004812A, 3};

menu_weapon_rpk_info SECTION(".data") gMenuItemRpkInfo_8009E484[] = {
    {(char *)aCigs, 0xE},    {(char *)aScope, 0x1E},   {(char *)aCBoxA, 0x11},    {(char *)aCBoxB, 0x11},
    {(char *)aCBoxC, 0x11},  {(char *)aNVG, 0xF},      {(char *)aThermG, 0x10},   {(char *)aGasmask, 0x13},
    {(char *)aBArmor, 0x12}, {(char *)aKetchup, 0x19}, {(char *)aStealth, 0x20},  {(char *)aBandana, 0x1F},
    {(char *)aCamera, 0xC},  {(char *)aRation, 0x16},  {(char *)aMedicine, 0x15}, {(char *)aDiazepam, 0x15},
    {(char *)aPalKey, 0x17}, {(char *)aCard, 0x1B},    {(char *)aTimerB, 0x1A},   {(char *)aMineD, 0x14},
    {(char *)aDisc, 0x1C},   {(char *)aRope, 0x18},    {(char *)aScarf, 0x1D},    {(char *)aSuppr, 0xD}};

struct PANEL_CONF SECTION(".data") stru_8009E544[2] = {
    {16, 184, 1, 24576, 36864, sub_8003D64C, sub_8003D594, NULL},
    {256, 184, 2, 12288, 49152, sub_8003D594, sub_8003D5F0, NULL}};

menu_weapon_rpk_info SECTION(".data") gMenuWeaponRpkInfo_8009E57C[] = {
    {(char *)aSocom, 1},
    {(char *)aFamas_800AB5BC, 3},
    {(char *)aGrenade_800AB5B4, 5},
    {(char *)aNikita_800AB5AC, 10},
    {(char *)aStinger_800AB5A4, 9},
    {(char *)aClaymore, 8},
    {(char *)aC4_800AB5A0, 7},
    {(char *)aStunG, 6},
    {(char *)aChaffG, 11},
    {(char *)aPsg1, 4}
};

// Also see dword_8009E3E4, dword_8009E444.
// Those strings are passed to font_draw_string_80045D0C().
extern char WP_Socom_80011A8C[];
extern char WP_Famas_80011A30[];
extern char WP_Grenade_800119C0[];
extern char WP_Nikita_80011954[];
extern char WP_Stinger_800118DC[];
extern char WP_LandMine_8001187C[];
extern char WP_Bomb_80011838[];
extern char WP_StunGrenade_800117C4[];
extern char WP_ChaffGrenade_80011750[];
extern char WP_Rifle_800116E8[];
char *SECTION(".data") wpn_descriptions_8009E5CC[] = {
    WP_Socom_80011A8C,
    WP_Famas_80011A30,
    WP_Grenade_800119C0,
    WP_Nikita_80011954,
    WP_Stinger_800118DC,
    WP_LandMine_8001187C,
    WP_Bomb_80011838,
    WP_StunGrenade_800117C4,
    WP_ChaffGrenade_80011750,
    WP_Rifle_800116E8
};

BarConfig SECTION(".data") gSnakeLifeBarConfig_8009E5F4 = {aLife, {16u, 143u, 127u}, {31u, 223u, 63u}, 0};
BarConfig SECTION(".data") gSnakeO2BarConfig_8009E600 = {aO2, {31u, 63u, 192u}, {31u, 127u, 255u}, 1};

int SECTION(".data") dword_8009E60C[] = {0x6D5D2477, 0x257B6B2E, 0x6F7F};
int SECTION(".data") dword_8009E618[] = {0x2070001, 0x7020100, 0x7020107, 0x2070701, 0x7020900, 0x7020907, 0x2070F01};
int SECTION(".data") dword_8009E634 = 0x3D472E;
int SECTION(".data") dword_8009E638 = 0x3D472E;
int SECTION(".data") dword_8009E63C[] = {0x2050001, 0x6020100, 0x6020105, 0x2050601, 0x6020800, 0x6020805, 0x2050D01};
int SECTION(".data") dword_8009E658 = 0x3D472E;
int SECTION(".data") dword_8009E65C = 0x3D472E;
int SECTION(".data") dword_8009E660 = 0xC0F0A0A;
int SECTION(".data") dword_8009E664[] = {
    0x30503A78, 0x601A1F13, 0x2053774, 0x60293020, 0x20537C7, 0x60293020, 0x2056B74, 0x60293020, 0x2056BC7, 0x60293020,
    0x14E3779,  0x60293020, 0x14E6C79, 0x60293020, 0xA3E2681, 0x601A1F13, 0xA3E7581, 0x601A1F13, 0xB194C5A, 0x601A1F13,
    0xB194CCD,  0x601A1F13, 0x12B2654, 0x601A1F13, 0x12B26C1, 0x601A1F13, 0x12B7E54, 0x601A1F13, 0x12B7EC1, 0x601A1F13,
    0x1242E5B,  0x601A1F13, 0x1242EC1, 0x601A1F13, 0x124765B, 0x601A1F13, 0x12476C1, 0x601A1F13};
RadioCoordsStru_8009E6FC SECTION(".data") gRadioCoords_8009E6FC[] = {
    {222, 81, 214, 77, 214, 85},
    {98,  81, 106, 77, 106, 85}
};
RadioIncomingCall SECTION(".data") gRadioIncomingCall_8009E708 = {0, 0, -1, 0};
int   SECTION(".data") dword_8009E714[] = {0x240022E, 0x45F023A, 0x63F0221, 0x62D062B, 0x62A062F, 0x37D037B, 0};
int   SECTION(".data") dword_8009E730[] = {0x80043678, 0x80043A24, 0x80043FD0, 0x800442E4, 0x800445F8};
int   SECTION(".data") dword_8009E744[] = {0x800AB6A4, 0x800AB6A0, 0x800AB69C, 0x800AB698, 0x800AB694, 0x800AB690};
void *SECTION(".data") dword_8009E75C[] = {NULL, NULL, NULL, NULL};
int   SECTION(".data") dword_8009E76C[] = {0x100FF, 0xFF000100};
int   SECTION(".data") dword_8009E774[] = {
      0x24A51421, 0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,  0x12211,
      0xEA00310,  0x20000000, 0xEC00331,  0x23210012, 0xEB20243,  0x33332213, 0xEA10134,  0x44422233, 0xEA10123,
      0x34322343, 0xED11212,  0x24444443, 0xEE02221,  0x24444343, 0xEE30132,  0x23444233, 0xEE00133,  0x22334301,
      0xEB00123,  0x21224420, 0xD000113,  0x22100100, 0xA100202,  0x32112344, 0x1100201,  0x23233200, 0x1000200,
      0x2212222,  0x1000220,  0,          0,          0x24A51421, 0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6,
      0x10750C13, 0x195A14D8, 0xEEB19BC,  0x11124444, 0x2221131,  0x21000134, 0x2210222,  0x1114,     0x1230,
      0x10000124, 0x241,      0x11123234, 0x20234,    0x43334444, 0x10234,    0x44444444, 0x221233,   0x44444444,
      0x1011133,  0x34444444, 0x2100123,  0x34444334, 0x1110023,  0x33444421, 0x1000012,  0x33433443, 0x100002,
      0x23320211, 0xB001001,  0x13333233, 0xAC10000,  0x1333322,  0xCB10100,  0,          0,          0x24A51421,
      0x45AD3529, 0x88A5631,  0x217414EF, 0x363929D6, 0x10750C13, 0x195A14D8, 0xEEB19BC,  0x1343023,  0x1102021,
      0x13444312, 0x1001020,  0x3444301,  0x120,      0x22343113, 0x10021,    0x32211213, 0x10012,    0x33334433,
      0x21002,    0x24444433, 0x1002002,  0x24444334, 0x2210001,  0x23444314, 0xB100010,  0x12444302, 0xDA10011,
      0x22344421, 0xEBA0002,  0x22212333, 0xEEC1001,  0x21310100, 0xEC10100,  0x12132344, 0xC312200,  0x2112222,
      0x4233101,  0,          0,          0x2CA51C21, 0x456B3908, 0x5E3151CE, 0x217414EF, 0x363929D6, 0x10550C13,
      0x151814B7, 0x19BC195A, 0x34455555, 0xFA12022,  0x255300,   0xFA12300,  0x241CD,    0xFA12240,  0x21000BDA,
      0xFA11234,  0x445521CD, 0xFB11223,  0x34455300, 0xFDA1123,  0x33445552, 0xFFA1122,  0x33445551, 0xFFA1112,
      0x12344551, 0xFFB1221,  0x31344551, 0xFFDA122,  0x31334451, 0xFFFA112,  0x22014451, 0xFFFB012,  0x24213451,
      0xFFFB111,  0x22313441, 0xFFFB201,  0x22312341, 0xFFFA310,  0,          0,          0x14A90425, 0x35B1252D,
      0x88A4635,  0x217414EF, 0x363929D6, 0x49035844, 0x2A4139A2, 0x1E8316E0, 0x10013444, 0xE021020,  0x12221234,
      0xA010031,  0x12224,    0x32,       0x10001224, 0x200030,   0x10022324, 0x410332,   0x32233434, 0x210333,
      0x44444444, 0x110233,   0x44444444, 0xA010133,  0x44444434, 0xCA10133,  0x34444432, 0xECBA023,  0x34433443,
      0xEEDD013,  0x33421211, 0xEEED102,  0x23333222, 0xEEEC101,  0x12334310, 0xEED0100,  0x1233444,  0xEEA1002,
      0,          0,          0x14A90425, 0x35B1252D, 0x88A4635,  0x217414EF, 0x363929D6, 0x44693427, 0x60CD508B,
      0x64896CEF, 0x11001123, 0xED00210,  0x10000003, 0xEB01100,  0x11201013, 0xB200210,  0x12212124, 0xB020221,
      0x22322234, 0xC211123,  0x44322144, 0xDB10123,  0x33321234, 0xEC01012,  0x23211023, 0xEEB0112,  0x22122102,
      0xEED1121,  0x21222332, 0xEED2122,  0x10121100, 0xEEC0122,  0x10123433, 0xEEA0021,  0x12222100, 0xEC00021,
      0x1221111,  0xEA00102,  0x22222333, 0xB000301,  0,          0};
char SECTION(".data") aBislpm99999[] = "BISLPM-99999        ";
int  SECTION(".data") dword_8009EB4C[] = {0x800AB6F8, 0x8001203C, 0x80012020, 0x80012008, 0x80011FEC, 0x80011FC4,
                                          0x80011FB0, 0x80011F90, 0x80011F6C, 0x80011F5C, 0x80011F34, 0x80011F18};
int  SECTION(".data") dword_8009EB7C[] = {0x800AB6F8, 0x800120B4, 0x80012098, 0x80012008, 0x80012078, 0x80011FC4,
                                          0x80012064, 0x80011F90, 0x80011F6C, 0x80012054, 0x80011F34, 0x80011F18};
int  SECTION(".data") dword_8009EBAC[] = {0x800120E4, 0x800120CC};
int  SECTION(".data") dword_8009EBB4[] = {0x8001210C, 0x80012100};

char *SECTION(".data") dword_8009EBBC[] = {NULL, NULL, (char *)aComplete, NULL, (char *)aError};

int  SECTION(".data") dword_8009EBD0[] = {0x4F009B, 0x4A00A0, 0x4F00A5, 0x80808080};
int  SECTION(".data") dword_8009EBE0[] = {0xB8009C, 0xBC00A0, 0xB800A4, 0x80808080};
int  SECTION(".data") off_8009EBF0[] = {(int)dword_800AB728, (int)dword_800AB724, (int)dword_800AB720, (int)aEx};
int  SECTION(".data") off_8009EC00[] = {(int)aMemoryCard1, (int)aMemoryCard2};
int  SECTION(".data") off_8009EC08[] = {(int)dword_800AB754, (int)aNo};
int  SECTION(".data") dword_8009EC10[] = {0x8F826382, 0x8B828382, 0};
int  SECTION(".data") off_8009EC1C[] = {(int)dword_800122D8, (int)dword_800122CC, (int)dword_800122C0,
                                        (int)dword_800122B4, (int)dword_800122A8};

menu_save_mode_data SECTION(".data") stru_8009EC30 = {{0x47, 0}, 0, 1, (void *)aSaveData, (void *)0x8004D008, (void *)0x8004D14C, (void *)0x8004D1D0};

Menu_Triangle SECTION(".data") stru_8009EC44 = {155, 125, 160, 120, 165, 125, 0x80808080};
Menu_Triangle SECTION(".data") stru_8009EC54 = {156, 212, 160, 216, 164, 212, 0x80808080};

Sna_E2 SECTION(".data") e2_8009EC64 = {12u, 82u, 19u, 23u, 24u, 29u, 30u, 12u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009EC70 = {10u, 8u, 17u, 23u, 24u, 27u, 28u, 80u, 106u, 107u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009EC7C = {11u, 9u, 18u, 23u, 24u, 27u, 28u, 73u, 110u, 111u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009EC88 = {75u, 77u, 79u, 23u, 24u, 27u, 28u, 75u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009EC94 = {92u, 91u, 93u, 23u, 24u, 29u, 30u, 92u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ECA0 = {97u, 96u, 98u, 101u, 24u, 29u, 30u, 97u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ECAC = {104u, 103u, 19u, 23u, 24u, 29u, 30u, 104u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ECB8 = {63u, 65u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 SECTION(".data") e2_8009ECC4 = {61u, 64u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 SECTION(".data") e2_8009ECD0 = {62u, 83u, 67u, 68u, 69u, 70u, 71u, 72u, 66u, 123u, 130u, 131u};
Sna_E2 SECTION(".data") e2_8009ECDC = {136u, 136u, 35u, 136u, 36u, 37u, 38u, 39u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ECE8 = {42u, 51u, 35u, 45u, 47u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ECF4 = {5u, 52u, 34u, 46u, 48u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ED00 = {74u, 136u, 136u, 136u, 105u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

Sna_E2 SECTION(".data") e2_8009ED0C = {74u, 136u, 34u, 46u, 81u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ED18 = {43u, 136u, 35u, 136u, 53u, 55u, 49u, 54u, 56u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ED24 = {57u, 136u, 35u, 136u, 58u, 59u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ED30 = {60u, 136u, 35u, 136u, 50u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
Sna_E2 SECTION(".data") e2_8009ED3C = {44u, 136u, 136u, 136u, 136u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};

Sna_E6 SECTION(".data") e6_8009ED48 = {115u, 133u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED4C = {112u, 133u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED50 = {113u, 133u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED54 = {136u, 136u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED58 = {114u, 132u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED5C = {116u, 133u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED60 = {117u, 133u, 0u, 0u};
Sna_E6 SECTION(".data") e6_8009ED64 = {118u, 133u, 0u, 0u};

Sna_E1 SECTION(".data") e7_8009ED68 = {7u, 13u, 4u, 14u, 32u, 119u, 124u, 0u};

extern Sna_E1 e1_800AB78C;
extern Sna_E1 e1_800AB7C4;
extern Sna_E1 e1_800AB794;
extern Sna_E1 e1_800AB79C;
extern Sna_E1 e1_800AB7BC;
extern Sna_E1 e1_800AB7AC;
extern Sna_E1 e1_800AB7A4;
extern Sna_E1 e1_800AB7B4;

Sna_ActionTable SECTION(".data") actions_no_weapon_8009ED70 = {&e1_800AB78C, &e2_8009EC64, &e1_800AB7C4, &e2_8009ECB8,
                                                               &e2_8009ECDC, &e6_8009ED48, &e7_8009ED68};

Sna_ActionTable SECTION(".data") weapon_actions_8009ED8C[10] = {
    {&e1_800AB794, &e2_8009EC70, &e1_800AB7C4, &e2_8009ECC4, &e2_8009ECE8, &e6_8009ED4C, &e7_8009ED68},
    {&e1_800AB79C, &e2_8009EC7C, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ECF4, &e6_8009ED50, &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED64, &e7_8009ED68},
    {&e1_800AB7B4, &e2_8009EC88, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ED0C, &e6_8009ED58, &e7_8009ED68},
    {&e1_800AB79C, &e2_8009EC7C, &e1_800AB7C4, &e2_8009ECD0, &e2_8009ED00, &e6_8009ED54, &e7_8009ED68},
    {&e1_800AB7BC, &e2_8009ECA0, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED24, &e6_8009ED60, &e7_8009ED68},
    {&e1_800AB7AC, &e2_8009EC94, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED18, &e6_8009ED5C, &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED64, &e7_8009ED68},
    {&e1_800AB7A4, &e2_8009ECAC, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED30, &e6_8009ED64, &e7_8009ED68},
    {&e1_800AB78C, NULL, &e1_800AB7C4, &e2_8009ECB8, &e2_8009ED3C, &e6_8009ED54, &e7_8009ED68}};

void *SECTION(".data") dword_8009EEA4[] = {
    (void *)0x8005275C, // sna_init_anim_idle_8005275C
    (void *)0x800527DC, // sna_init_anim_crouch_800527DC
    (void *)0x800528BC  // sna_init_anim_prone_idle_800528BC
};

void *SECTION(".data") dword_8009EEB0[] = {
    (void *)0x80052A5C, // sna_init_anim_wall_idle_and_c4_80052A5C
    (void *)0x80052CCC  // sna_init_anim_wall_crouch_80052CCC
};

void *SECTION(".data") dword_8009EEB8[] = {
    (void *)0x8005292C, // sna_init_anim_run_8005292C
    (void *)0x8005292C, // sna_init_anim_run_8005292C
    (void *)0x800529C0  // sna_init_anim_prone_move_800529C0
};

short SECTION(".data") HzdHeights_8009EEC4[] = {750, 250, 250, 0};

int SECTION(".data")  dword_8009EECC[] = {0x1F0044C, 0x88};
int SECTION(".data")  dword_8009EED4 = 0x47F;
int SECTION(".data")  dword_8009EED8[] = {0x2FF01E1, 0};
int SECTION(".data")  dword_8009EEE0 = 0x67F;
int SECTION(".data")  dword_8009EEE4[] = {0x4FF01E1, 0x84B02E1, 0};
int SECTION(".data")  dword_8009EEF0 = 0x17F;
int SECTION(".data")  dword_8009EEF4 = 0x39B;
int SECTION(".data")  dword_8009EEF8[] = {0x27F0200, 0};
int SECTION(".data")  dword_8009EF00[] = {0x650048C, 0};
int SECTION(".data")  dword_8009EF08[] = {0x27F0A00, 0};
int SECTION(".data")  dword_8009EF10[] = {0x8320250, 0x650048C, 0};
char SECTION(".data") dword_8009EF1C[] = {196, 4, 0, 0};
char SECTION(".data") dword_8009EF20[] = {148, 4, 0, 0};
int SECTION(".data")  dword_8009EF24[] = {0x27F0200, 0};

/*
// TODO: Converting this entry de-syncs data
int SECTION(".data") dword_8009EF2C[] = {0x4C8023C, 0x228};
WeaponCreateEntry kSnakeNoWeapon = {0, sna_init_anim_chokethrow_begin1_80054210};
*/

int SECTION(".data") dword_8009EF2C[] = {0x4C8023C, 0x228, 0, 0x80054210};

WeaponCreateEntry SECTION(".data") gSnakeWeapons_8009EF3C[] = {
    {NewSOCOM_80065D74, sna_init_gun_800540D0},
    {famas_create_80066374, sna_init_gun_800540D0},
    {grenade_create_80066A4C, sna_init_anim_grenade_80058470},
    {NewRCM_80066FF0, sna_init_gun_800540D0},
    {NewAAM_80067480, sna_init_anim_stinger_800570C0},
    {mine_init_800677BC, sna_init_anim_claymore_80057474},
    {NewBomb_80067B20, sna_init_bomb_800541A8},
    {NewStanGrenade_80066A74, sna_init_anim_grenade_80058470},
    {NewChaffGrenade_80066AA0, sna_init_anim_grenade_80058470},
    {NewRifle_80068214, sna_init_anim_psg1_80056DDC}};

TSnakeEquipFuncion SECTION(".data") gSnakeEquips_8009EF8C[] = {
    NewTabako_80062274,
    NewScope_80063508,
    NewBox_80061C7C,
    NewBox_80061C7C,
    NewBox_80061C7C,
    NewGoggle_8007781C,
    NewGoggleIr_80078E6C,
    NewGasmask_80060C14,
    NewBodyarm_80060940,
    NewKetchap_80072B60,
    NewKogaku2_800615FC,
    NewBandana_80061E40,
    NewJpegcam_80065118};

short SECTION(".data") word_8009EFC0[10] = {0, 500, 0, 320, 400, 320, 400, 32, 32, 0};

SVECTOR SECTION(".data") stru_8009EFD4[2] = {{-100, 200, 200, 0}, {-150, 18, 200, 0}};

Target_Data SECTION(".data") stru_8009EFE4[4] =
{
    {{0, 0, 300, 0}, {400, 600, 400, 0}, 0, 0, 64, 0}, // TODO: Might not be part of this array, might be its own element
    {{-400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{400, 0, 600, 0}, {400, 600, 400, 0}, 0, 0, 36, 5},
    {{0, 0, 0, 0}, {501, 600, 501, 0}, 0, 0, 7, 0}
};

MATRIX SECTION(".data") stru_8009F064 = {{{-200, 200, 600}, {0, 400, 200}, {400, 0, 5}}, {50, 0, 1}};
MATRIX SECTION(".data") stru_8009F084 = {{{200, 200, 600}, {0, 400, 200}, {400, 0, -5}}, {50, 0, 1}};
MATRIX SECTION(".data") stru_8009F0A4 = {{{0, 200, 600}, {0, 500, 250}, {500, 0, 0}}, {100, 0, 3}};

GV_PAD SECTION(".data") GV_PadData_8009F0C4 = {0, 0, 0, 0, -1, 0, 0, 0, 0, 0};

struct ANIMATION SECTION(".data") stru_8009F0D4 = {-8302, 2, 2, 4, 1, 0, 5, 50, 50, 250, 0, (void *)0x800124A8};
struct ANIMATION SECTION(".data") stru_8009F0F0 = {20781, 8, 4, 30, 1, 300, 1, 400, 400, 32, 0, (void *)0x8001253C};
struct ANIMATION SECTION(".data") stru_8009F10C = {-6964, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (void *)0x800125CC};
struct ANIMATION SECTION(".data") stru_8009F128 = {-6964, 2, 2, 4, 1, 300, 1, 1400, 1400, 128, 0, (void *)0x800125F4};
struct ANIMATION SECTION(".data") stru_8009F144 = {-6964, 2, 2, 4, 1, 300, 1, 400, 400, 128, 0, (void *)0x8001261C};
struct ANIMATION SECTION(".data") stru_8009F160 = {-370, 2, 2, 3, 1, 300, 1, 600, 600, 100, 0, (void *)0x80012628};
struct ANIMATION SECTION(".data") stru_8009F17C = {32332, 2, 2, 4, 1, 200, 5, 100, 100, 128, 0, (void *)0x80012634};
struct ANIMATION SECTION(".data") stru_8009F198 = {20781, 8, 4, 30, 8, 0, 3, 2200, 2200, 77, 0, (void *)0x80012708};
struct ANIMATION SECTION(".data") stru_8009F1B4 = {20781, 8, 4, 30, 1, 0, 1, 1000, 1000, 77, 0, (void *)0x80012728};
struct ANIMATION SECTION(".data") stru_8009F1D0 = {20781, 8, 4, 30, 4, 0, 1, 2200, 2200, 128, 0, (void *)0x80012750};
struct ANIMATION SECTION(".data") stru_8009F1EC = {20781, 8, 4, 30, 1, 1000, 3, 400, 400, 128, 0, (void *)0x800127A4};
struct ANIMATION SECTION(".data") stru_8009F208 = {20781, 8, 4, 30, 1, 1000, 3, 30, 30, 10, 0, (void *)0x800127D0};

int SECTION(".data") dword_8009F224 = 0;

TAnimeVMFn SECTION(".data") anime_fn_table_8009F228[] = {
    (void *)0x8005EC1C, (void *)0x8005ED0C, (void *)0x8005ED74, (void *)0x8005EDDC, (void *)0x8005EE44,
    (void *)0x8005EEA4, (void *)0x8005EF04, (void *)0x8005EFF8, (void *)0x8005F0F0, (void *)0x8005F180,
    (void *)0x8005F288, (void *)0x8005F2F4, (void *)0x8005F37C, (void *)0x8005F408, (void *)0x8005F438};

// TODO: Warning without const, but can't be const else would end up in rdata section?
const char *SECTION(".data") off_8009F264[4] = {aSnaChest1, aSnaChest2, aSnaChest3, aSnaHip1};
const char *SECTION(".data") off_8009F274[4] = {aSnaArmer1, aSnaArmer2, aSnaArmer3, aSnaArmer4};

int SECTION(".data") dword_8009F284 = 0;

const char *SECTION(".data") off_8009F288[8] = {aCbBox11, aCbBox12, aCbBox41, aCbBox42, aCbBox21, aCbBox22, aCbBox41, aCbBox42};

// TODO: Ditto const stuff
const char *SECTION(".data") off_8009F2A8[3] = {aSnaFace, aSnaFace2, aSnaFace3};
const char *SECTION(".data") off_8009F2B4[3] = {aSnaMf1, aSnaMf2, aSnaMf3};

int     SECTION(".data") dword_8009F2C0 = 0;
short   SECTION(".data") scope_created_8009F2C4 = 0;
SVECTOR SECTION(".data") svec_8009F2C8 = {0, 0, 0, 0};
int     SECTION(".data") dword_8009F2D0[] = {0, 0xC80};

menu_save_mode_data SECTION(".data") stru_8009F2D8 = {{0x43, 4}, 0, 2, (void *)0x800129D4, (void *)0x80063704, (void *)0x80063888, (void *)0x800638B4};

char SECTION(".data") gJpegcamZigZagTable_8009F2EC[64] = {
    0x00, 0x01, 0x08, 0x10, 0x09, 0x02, 0x03, 0x0A,
    0x11, 0x18, 0x20, 0x19, 0x12, 0x0B, 0x04, 0x05,
    0x0C, 0x13, 0x1A, 0x21, 0x28, 0x30, 0x29, 0x22,
    0x1B, 0x14, 0x0D, 0x06, 0x07, 0x0E, 0x15, 0x1C,
    0x23, 0x2A, 0x31, 0x38, 0x39, 0x32, 0x2B, 0x24,
    0x1D, 0x16, 0x0F, 0x17, 0x1E, 0x25, 0x2C, 0x33,
    0x3A, 0x3B, 0x34, 0x2D, 0x26, 0x1F, 0x27, 0x2E,
    0x35, 0x3C, 0x3D, 0x36, 0x2F, 0x37, 0x3E, 0x3F
};

char SECTION(".data") gJpegcamQuantTable_8009F32C[64] = {
    0x02, 0x10, 0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22,
    0x10, 0x10, 0x16, 0x18, 0x1B, 0x1D, 0x22, 0x25,
    0x13, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x22, 0x26,
    0x16, 0x16, 0x1A, 0x1B, 0x1D, 0x22, 0x25, 0x28,
    0x16, 0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30,
    0x1A, 0x1B, 0x1D, 0x20, 0x23, 0x28, 0x30, 0x3A,
    0x1A, 0x1B, 0x1D, 0x22, 0x26, 0x2E, 0x38, 0x45,
    0x1B, 0x1D, 0x23, 0x26, 0x2E, 0x38, 0x45, 0x53
};

TMat8x8B SECTION(".data") gJpegcamMatrix1_8009F36C = {
    {0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D},
    {0x3F, 0x35, 0x23, 0x0C, 0xF4, 0xDD, 0xCB, 0xC1},
    {0x3B, 0x18, 0xE8, 0xC5, 0xC5, 0xE8, 0x18, 0x3B},
    {0x35, 0xF4, 0xC1, 0xDD, 0x23, 0x3F, 0x0C, 0xCB},
    {0x2D, 0xD3, 0xD3, 0x2D, 0x2D, 0xD3, 0xD3, 0x2D},
    {0x23, 0xC1, 0x0C, 0x35, 0xCB, 0xF4, 0x3F, 0xDD},
    {0x18, 0xC5, 0x3B, 0xE8, 0xE8, 0x3B, 0xC5, 0x18},
    {0x0C, 0xDD, 0x35, 0xC1, 0x3F, 0xCB, 0x23, 0xF4}
};
SVECTOR SECTION(".data") dword_8009F3AC = {0, 0, 0, 0};
SVECTOR SECTION(".data") stru_8009F3B4[2] = {{0, 0, 3200, 0}, {20, -370, 60, 0}};
SVECTOR SECTION(".data") stru_8009F3C4[2] = {{0, -215, 32, 0}, {0, -10455, 32, 0}};
SVECTOR SECTION(".data") stru_8009F3D4[2] = {{0, 600, 32, 0}, {0, -9640, 32, 0}};

int        SECTION(".data") dword_8009F3E4[] = {0x7A643B88, 0xF83D7A64};
int        SECTION(".data") dword_8009F3EC[] = {0x800000, 0x96};
int        SECTION(".data") dword_8009F3F4[] = {0x320000, 0xC8};
int        SECTION(".data") dword_8009F3FC[] = {0x200000, 0x20, 0x1180000, 0x50};

char       SECTION(".data") byte_8009F40C[] = {0, 2, 127, 4, 0};
char       SECTION(".data") byte_8009F414[] = {145, 4, 75, 10, 0};

SVECTOR    SECTION(".data") dword_8009F41C[2] = {{0, 0, 0, 0}, {0, 0, 3000, 0}};
int        SECTION(".data") used_counter_8009F42C = 0;
int        SECTION(".data") dword_8009F430 = 0;
int        SECTION(".data") dword_8009F434 = 0;
SVECTOR    SECTION(".data") svector_8009F438 = {3072, 0, 0, 0};
int        SECTION(".data") dword_8009F440 = 0;
int        SECTION(".data") dword_8009F444 = 0;
int        SECTION(".data") counter_8009F448 = 0;
SVECTOR    SECTION(".data") svec_8009F44C = {0xFD8F, 0xFF06, 0x2EE, 0};
SVECTOR    SECTION(".data") svec_8009F454 = {0xFE0C, 0xFF06, 0x2EE, 0};
SVECTOR    SECTION(".data") svec_8009F45C = {0x1F4, 0xC8, 0x1F4, 0};
SVECTOR    SECTION(".data") svec_8009F464 = {0x12C, 0xC8, 0x12C, 0};
int        SECTION(".data") dword_8009F46C = 0;
int        SECTION(".data") dword_8009F470 = 0;
int        SECTION(".data") dword_8009F474 = 0;
SVECTOR    SECTION(".data") svector_8009F478 = {0, 0, 0, 0};
int        SECTION(".data") dword_8009F480 = 0;
short      SECTION(".data") Nik_Blast_8009F484 = 0;
SVECTOR    SECTION(".data") svector_8009F488 = {100, 100, 100, 0};
int        SECTION(".data") dword_8009F490 = 0;
SVECTOR    SECTION(".data") svector_8009F494 = {0, 0, 0, 0};
int        SECTION(".data") dword_8009F49C = 0;
SVECTOR    SECTION(".data") svector_8009F4A0 = {0, -800, 0, 0};
SVECTOR    SECTION(".data") svector_8009F4A8 = {0, -350, 0, 0};
SVECTOR    SECTION(".data") svector_8009F4B0 = {0, -100, -70, 0};

Blast_Data SECTION(".data") blast_data_8009F4B8 = {0x100, 5, 0x3E8, 0x7D0, 2};
Blast_Data SECTION(".data") blast_data_8009F4CC = {0x100, 5, 0x3E8, 0x7D0, 6};
Blast_Data SECTION(".data") blast_data_8009F4E0 = {0x100, 5, 0x3E8, 0x7D0, 5};
Blast_Data SECTION(".data") blast_data_8009F4F4 = {0x100, 5, 0x3E8, 0x7D0, 4};
Blast_Data SECTION(".data") blast_data_8009F508 = {0x100, 5, 0x3E8, 0x7D0, 3};
Blast_Data SECTION(".data") blast_data_8009F51C = {0x100, 5, 0x3E8, 0x7D0, -1};
Blast_Data SECTION(".data") blast_data_8009F530 = {0x400, 5, 0x3E8, 0x7D0, 10};
Blast_Data SECTION(".data") blast_data_8009F544 = {0, 0, 1, 1, -1};

SVECTOR SECTION(".data") svector_8009F558[2] = {{100, 0, 0, 0}, {2000, 2000, 4000, 4000}};

ANIMATION SECTION(".data") stru_8009F568 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BAC};
ANIMATION SECTION(".data") stru_8009F584 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012BEC};
ANIMATION SECTION(".data") stru_8009F5A0 = {-21358, 4, 4, 16, 1, 2000, 1, 500, 500, 128, NULL, (void *)0x80012C2C};
ANIMATION SECTION(".data") stru_8009F5BC = {-21358, 4, 4, 16, 1, 2000, 1, 200, 200, 128, NULL, (void *)0x80012C6C};
ANIMATION SECTION(".data") stru_8009F5D8 = {-21358, 4, 4, 16, 1, 2000, 1, 1000, 1000, 128, NULL, (void *)0x80012CAC};

int SECTION(".data") door_where_8009F5F4 = 0;

char  SECTION(".data") byte_8009F5F8[] = {0, 0, 0, 0};
short SECTION(".data") word_8009F5FC = 1;
int   SECTION(".data") dword_8009F600 = 0;
int   SECTION(".data") dword_8009F604 = 0xFFFFFFFF;
int   SECTION(".data") dword_8009F608 = 0;

RECT SECTION(".data") a22dd_8009F60C = {50, 50, 100, 100};

ANIMATION SECTION(".data") stru_8009F614 = {31572, 1, 1, 1, 1, 500, 3, 300, 300, 200, NULL, (void *)0x80012E84};

SVECTOR SECTION(".data") stru_8009F630[4] = {{20, 0, 0, 0}, {-20, 0, 0, 0}, {0, 20, 0, 0}, {0, -20, 0, 0}};

SVECTOR SECTION(".data") stru_8009F650[2] = {{0, 0, 200, 0}, {0, 0, 10000, 0}};

SVECTOR SECTION(".data") stru_8009F660 = {100, 100, 100, 0};

int SECTION(".data") gSparkRandomTableIndex_8009F668 = 0xFFFFFFFF;
int SECTION(".data") gSparkRandomTableIndex2_8009F66C = 0;

struct ANIMATION SECTION(".data") stru_8009F670 = {
    19692, 1, 1, 1, 1, 500, 3, 800, 800, 128, 0, (void *)dword_80012F2C};
struct ANIMATION SECTION(".data") stru_8009F68C = {
    21926, 1, 1, 1, 1, 500, 3, 600, 600, 180, 0, (void *)dword_80012F50};

int     SECTION(".data") dword_8009F6A8 = 0;

SVECTOR SECTION(".data") svec_8009F6AC[4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

SVECTOR SECTION(".data") svec_8009F6CC = {0, 400, 0, 0};
VECTOR  SECTION(".data") vec_8009F6D4 = {0, 0, 0, 0};
SVECTOR SECTION(".data") svec_8009F6E4 = {0, 55536, 0, 0};
SVECTOR SECTION(".data") svec_8009F6EC = {100, 100, 100, 0};
SVECTOR SECTION(".data") svec_8009F6F4 = {0, 0, 0, 0};
SVECTOR SECTION(".data") svec_8009F6FC = {0, 400, 0, 0};
RECT    SECTION(".data") rect_8009F704 = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F70C = {768, 196, 256, 2};
short   SECTION(".data") word_8009F714[] = {0, 0};
RECT    SECTION(".data") rect_8009F718 = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F720 = {768, 196, 256, 2};
int     SECTION(".data") dword_8009F728 = 0;
RECT    SECTION(".data") rect_8009F72C = {768, 226, 256, 2};
RECT    SECTION(".data") rect_8009F734 = {768, 196, 256, 2};

ANIMATION SECTION(".data") stru_8009F73C = {20781, 8, 4, 30, 1, 1000, 3, 500, 500, 255, NULL, (void *)0x8001345C};
ANIMATION SECTION(".data") stru_8009F758 = {20781, 8, 4, 30, 3, 0, 1, 1000, 1000, 64, NULL, (void *)0x80013488};
ANIMATION SECTION(".data") stru_8009F774 = {20781, 8, 4, 30, 8, 0, 3, 2200, 2200, 255, NULL, (void *)0x800134DC};
ANIMATION SECTION(".data") stru_8009F790 = {9287, 2, 2, 4, 1, 300, 1, 5000, 5000, 128, NULL, (void *)0x80013510};

SVECTOR SECTION(".data") stru_8009F7AC = {0, 255, 0, 0};

// SD data start

int SECTION(".data") dword_8009F7B4 = 0xFFFFFFFF;

void no_cmd_80087A80(void);
void tempo_set_800873CC(void);
void tempo_move_800873E4(void);
void SD_MDX_D2_sno_set_80086E38(void);
void svl_set_80086E78(void);
void svp_set_80086EB8(void);
void vol_chg_8008756C(void);
void SD_MDX_D6_vol_move_8008758C(void);
void SD_MDX_D7_80087904(void);
void SD_MDX_D8_srs_set_8008798C(void);
void SD_MDX_D9_800879E4(void);
void SD_pan_set_80086F00(void);
void SD_MDX_DE_pan_move_80086F50(void);
void trans_set_8008750C(void);
void SD_MDX_E0_detune_set_80087730(void);
void SD_MDX_E1_vib_set_80087018(void);
void SD_MDX_E2_vib_change_80087120(void);
void SD_MDX_E3_rdm_set_8008716C(void);
void swp_set_8008774C(void);
void sws_set_800876D4(void);
void SD_MDX_E6_por_set_80087670(void);
void SD_MDX_E7_lp1_start_800871B4(void);
void SD_MDX_E8_800871E0(void);
void SD_MDX_E9_lp2_start_800872C0(void);
void SD_MDX_EA_lp2_end_800872EC(void);
void SD_MDX_EB_l3s_set_8008736C(void);
void SD_MDX_EC_l3e_set_80087384(void);
void SD_MDX_ED_kakko_start_80087834(void);
void SD_MDX_EE_kakko_end_80087854(void);
void use_set_80086EF8(void);
void SD_MDX_F2_rest_set_80086D18(void);
void tie_set_80086D9C(void);
void echo_set1_80087754(void);
void echo_set2_8008775C(void);
void SD_MDX_F6_80087764(void);
void SD_MDX_F7_800877CC(void);
void SD_MDX_FF_block_end_80087A58(void);

char *SECTION(".data") dword_8009F7B8 = 0;

TMDXFunc SECTION(".data") gMdxTable_8009F7BC[] = {no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               tempo_set_800873CC,
                                               tempo_move_800873E4,
                                               SD_MDX_D2_sno_set_80086E38,
                                               svl_set_80086E78,
                                               svp_set_80086EB8,
                                               vol_chg_8008756C,
                                               SD_MDX_D6_vol_move_8008758C,
                                               SD_MDX_D7_80087904,
                                               SD_MDX_D8_srs_set_8008798C,
                                               SD_MDX_D9_800879E4,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               SD_pan_set_80086F00,
                                               SD_MDX_DE_pan_move_80086F50,
                                               trans_set_8008750C,
                                               SD_MDX_E0_detune_set_80087730,
                                               SD_MDX_E1_vib_set_80087018,
                                               SD_MDX_E2_vib_change_80087120,
                                               SD_MDX_E3_rdm_set_8008716C,
                                               swp_set_8008774C,
                                               sws_set_800876D4,
                                               SD_MDX_E6_por_set_80087670,
                                               SD_MDX_E7_lp1_start_800871B4,
                                               SD_MDX_E8_800871E0,
                                               SD_MDX_E9_lp2_start_800872C0,
                                               SD_MDX_EA_lp2_end_800872EC,
                                               SD_MDX_EB_l3s_set_8008736C,
                                               SD_MDX_EC_l3e_set_80087384,
                                               SD_MDX_ED_kakko_start_80087834,
                                               SD_MDX_EE_kakko_end_80087854,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               use_set_80086EF8,
                                               SD_MDX_F2_rest_set_80086D18,
                                               tie_set_80086D9C,
                                               echo_set1_80087754,
                                               echo_set2_8008775C,
                                               SD_MDX_F6_80087764,
                                               SD_MDX_F7_800877CC,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               no_cmd_80087A80,
                                               SD_MDX_FF_block_end_80087A58};

unsigned char SECTION(".data") rdm_tbl_8009F9BC[129] = {
    159u, 60u,  178u, 82u,  175u, 69u,  199u, 137u, 16u,  127u, 224u, 157u, 220u, 31u,  97u,  22u,  57u,  201u, 156u,
    235u, 87u,  8u,   102u, 248u, 90u,  36u,  191u, 14u,  62u,  21u,  75u,  219u, 171u, 245u, 49u,  12u,  67u,  2u,
    85u,  222u, 65u,  218u, 189u, 174u, 25u,  176u, 72u,  87u,  186u, 163u, 54u,  11u,  249u, 223u, 23u,  168u, 4u,
    12u,  224u, 145u, 24u,  93u,  221u, 211u, 40u,  138u, 242u, 17u,  89u,  111u, 6u,   10u,  52u,  42u,  121u, 172u,
    94u,  167u, 131u, 198u, 57u,  193u, 180u, 58u,  63u,  254u, 79u,  239u, 31u,  0u,   48u,  153u, 76u,  40u,  131u,
    237u, 138u, 47u,  44u,  102u, 63u,  214u, 108u, 183u, 73u,  34u,  188u, 101u, 250u, 207u, 2u,   177u, 70u,  240u,
    154u, 215u, 226u, 15u,  17u,  197u, 116u, 246u, 122u, 44u,  143u, 251u, 25u,  106u, 229u};

unsigned char SECTION(".data") VIBX_TBL_8009FA40[32] = {
    0u,   32u,  56u,  80u,  104u, 128u, 144u, 160u, 176u, 192u, 208u, 224u, 232u, 240u, 240u, 248u,
    255u, 248u, 244u, 240u, 232u, 224u, 208u, 192u, 176u, 160u, 144u, 128u, 104u, 80u,  56u,  32u};

int SECTION(".data") pant_8009FA60[41] = {0,   2,   4,   7,   10,  13,  16,  20,  24,  28,  32,  36,  40,  45,
                                          50,  55,  60,  65,  70,  75,  80,  84,  88,  92,  96,  100, 104, 107,
                                          110, 112, 114, 116, 118, 120, 122, 123, 124, 125, 126, 127, 127};

int SECTION(".data") se_pant_8009FB04[65] = {
    0,   2,   4,   6,   8,   10,  14,  18,  22,  28,  34,  40,  46,  52,  58,  64,  70,  76,  82,  88,  94,  100,
    106, 112, 118, 124, 130, 136, 142, 148, 154, 160, 166, 172, 178, 183, 188, 193, 198, 203, 208, 213, 217, 221,
    224, 227, 230, 233, 236, 238, 240, 242, 244, 246, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255};

int SECTION(".data") freq_tbl_8009FC08[108] = {
    0x10B,  0x11B,  0x12C,  0x13E,  0x151,  0x165,  0x17A,  0x191,  0x1A9,  0x1C2,  0x1DD,  0x1F9,  0x217,  0x237,
    0x259,  0x27D,  0x2A3,  0x2CB,  0x2F5,  0x322,  0x352,  0x385,  0x3BA,  0x3F3,  0x42F,  0x46F,  0x4B2,  0x4FA,
    0x546,  0x596,  0x5EB,  0x645,  0x6A5,  0x70A,  0x775,  0x7E6,  0x85F,  0x8DE,  0x965,  0x9F4,  0xA8C,  0xB2C,
    0xBD6,  0xC8B,  0xD4A,  0xE14,  0xEEA,  0xFCD,  0x10BE, 0x11BD, 0x12CB, 0x13E9, 0x1518, 0x1659, 0x17AD, 0x1916,
    0x1A94, 0x1C28, 0x1DD5, 0x1F9B, 0x217C, 0x237A, 0x2596, 0x27D2, 0x2A30, 0x2CB2, 0x2F5A, 0x322C, 0x3528, 0x3850,
    0x3BAC, 0x3F36, 0x21,   0x23,   0x26,   0x28,   0x2A,   0x2D,   0x2F,   0x32,   0x35,   0x38,   0x3C,   0x3F,
    0x42,   0x46,   0x4B,   0x4F,   0x54,   0x59,   0x5E,   0x64,   0x6A,   0x70,   0x77,   0x7E,   0x85,   0x8D,
    0x96,   0x9F,   0xA8,   0xB2,   0xBD,   0xC8,   0xD4,   0xE1,   0xEE,   0xFC};

int SECTION(".data") dword_8009FDB8[] = {
    0xD0780000, 0xD5FF0000, 0xD2290000, 0xD77F0F08, 0xD8440000, 0xD9100000, 0x2B095A40, 0xFFFE0000, 0xD0780000,
    0xD5FF0000, 0xD22A0000, 0xD77F0F08, 0xD8440000, 0xD9100000, 0x2B095A40, 0xFFFE0000, 0xD0FF0000, 0xD5C00000,
    0xD22B0000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x170C3C7F, 0xFFFE0000, 0xD0FF0100, 0xD57F0000, 0xD2280000,
    0xD77F000F, 0xD8000000, 0xD9140000, 0x210C5A57, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD2180000, 0xD77F000F,
    0xD8000000, 0xD9100000, 0x1F09501E, 0x25095032, 0x2B095046, 0x3130145A, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xD2170000, 0xD77F0F08, 0xD8400000, 0xD9120000, 0x25095028, 0x2B095050, 0x31095064, 0x37301478, 0xFFFE0000,
    0xD0FF0100, 0xD5FF0000, 0xD24900FF, 0xD77F000F, 0xD8000000, 0xD91A0000, 0x29020114, 0xD24A0000, 0xD77F0F08,
    0xD8200000, 0xD9170000, 0x18040140, 0xD2220000, 0xD77F0F08, 0xD8200000, 0xD9170000, 0x303C0120, 0xFFFE0000,
    0xD0FF0100, 0xD57F0000, 0xD2260000, 0xDF00000F, 0xD77F0E08, 0xD8400000, 0xD91F0000, 0x43060A7F, 0x3703237F,
    0xD2171430, 0xD77F0E08, 0xD8400000, 0xD91F0000, 0x450C1440, 0xFFFE0000, 0xD0FF0100, 0xD5E00000, 0xD2400000,
    0xD77F000F, 0xD8000000, 0xD91F0000, 0x21065A50, 0xD2040000, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x34010130,
    0x21065060, 0xE4010210, 0xD9122040, 0x1A182020, 0xE4000209, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xD2260000,
    0xD77F000F, 0xD8000000, 0xD91F0000, 0x2803017F, 0xD9180000, 0x4503017F, 0x2F12017F, 0xFFFE0000, 0xD0FF0000,
    0xD5C00000, 0xD226000F, 0xD77F000F, 0xD8000000, 0xD9180000, 0x37090154, 0x2E120154, 0xFFFE0000, 0xD0FF0100,
    0xD57F0000, 0xD2260000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x4004017F, 0xD20D1430, 0xD77F0E08,
    0xD8400000, 0xD91F0000, 0x450C147F, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD2040000, 0xD75C000F, 0xD8000000,
    0xD9140000, 0x1C0C147F, 0xE4000C04, 0xD77F0F0F, 0xD8360000, 0xD9110000, 0x3C303254, 0xE4000C02, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xD2040000, 0xDF000F0F, 0xD77F000F, 0x1008287F, 0xE4000804, 0x406287F,  0xD2262854,
    0x28102868, 0xE4000604, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xD204507F, 0xD77F000F, 0xD8000000, 0xD9180000,
    0x47030168, 0x23030168, 0xE7060140, 0x3B015A68, 0x3A015A68, 0xE803009D, 0xD91F0000, 0xE7060140, 0x20015A40,
    0x21015A40, 0xE820FCD8, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD203507F, 0xD752000F, 0xD8000000, 0xD9180000,
    0x1312327F, 0xE4030909, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD2040000, 0xD77F000F, 0xC052854,  0xE4000C07,
    0xD210507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0xE7060140, 0x2B015A40, 0x2C015A30, 0xE802E000, 0xE7060140,
    0x34015A20, 0x3A025A18, 0xE808FC00, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xD204507F, 0xD75E000F, 0xD8000000,
    0xD9180000, 0x43080154, 0x44090140, 0x42080154, 0x3C090140, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD2000000,
    0xD77F000F, 0xD8000000, 0xD9000000, 0xE3000000, 0xC06637F,  0x3C076330, 0xE4000607, 0xE3FF0FFF, 0xD77F0F0C,
    0xD8405A64, 0xD9115A64, 0x1530287F, 0xE4006007, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xD24900FF, 0xD77F000F,
    0xD8000000, 0xD91A0000, 0x29020114, 0xD21000FF, 0xD77F0F06, 0xD8000000, 0xD9180000, 0x32090A50, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xD20000FF, 0xD753000F, 0xD8480000, 0xD9100000, 0x3009637F, 0xE4000618, 0x1809637F,
    0xE400060C, 0xD58C01FF, 0xD22601FF, 0xD77F000F, 0xD8400000, 0xD9100000, 0xE7010120, 0x40016404, 0xE80A0400,
    0xE7010120, 0x40016430, 0xE830FFFD, 0xF2020000, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xD204507F, 0xD7570F07,
    0xD8000000, 0xD9180000, 0xE7060140, 0x40055A2C, 0x45045A40, 0xE804F0D0, 0xFFFE0000, 0xD0FF0000, 0xD5C00000,
    0xD202637F, 0xD7520808, 0xD8480C0C, 0xD911637F, 0x46302840, 0xE4000645, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF607507F, 0xD207507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0xDD000018, 0xDF0C3218, 0x43062814, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xD203637F, 0xD75A0808, 0xD8480C0C, 0xD911637F, 0x47182828, 0xE4000645, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xD204507F, 0xD760000F, 0xD8000000, 0xD9180000, 0x4030A7F,  0x90C0A7F,  0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xD24000FF, 0xD77F000F, 0xD8000000, 0xD9180000, 0x1F093C48, 0xD20400FF, 0xD75C000F,
    0xD8000000, 0xD9180000, 0x2606632C, 0xE400060C, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF6020000, 0xD2020000,
    0xD77F0F0F, 0xD8000000, 0xD9000000, 0x402A0450, 0xE4010C46, 0xE00A0A3C, 0x402E0458, 0xE4010C46, 0x40270450,
    0xE4010C46, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF6170000, 0xD2170000, 0xD77F0F0F, 0xD8000000, 0xD9140000,
    0x1301640A, 0x1903641E, 0x1F036432, 0x25036446, 0x2B03645A, 0x3103646E, 0xD77F0F03, 0xD840FF10, 0x34243C7F,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF6170000, 0xD2170000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x1903640A,
    0x1F03641E, 0x25036432, 0x2B036446, 0x3103645A, 0x3703646E, 0xD77F0F03, 0xD848FF10, 0xE128FF10, 0x3A481E7F,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF6170000, 0xD2170000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x1602640A,
    0x1C03641E, 0x22036432, 0x28036446, 0x2E03645A, 0x3403646E, 0xD77F000F, 0xD8480F0F, 0xE128FF20, 0x37481E7F,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF60E507F, 0xD20E507F, 0xD77F080C, 0xD8000000, 0xD9110000, 0xE7065040,
    0x3E045020, 0x42035018, 0xE8040000, 0xE7065040, 0x3E045009, 0x42035006, 0xE8020000, 0xE7065040, 0x3E045020,
    0x42035018, 0xE8040000, 0xE7065040, 0x3E045009, 0x42035006, 0xE8030000, 0xFFFE0000, 0xD0780000, 0xF7FF0000,
    0xD5FF0000, 0xD2410000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x181A6364, 0xFFFE0000, 0xD0780000,
    0xF7FF0000, 0xD5FF0000, 0xD2400000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD9130000, 0x18181E64, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xF713507F, 0xD213507F, 0xD758080C, 0xD8400000, 0xD9120000, 0x37180A7F, 0xE404083E,
    0x37180A30, 0xE404083E, 0x37180A18, 0xE404083E, 0xFFFE0000, 0xD0FF0000, 0xF6FF0000, 0xD5FF0000, 0xD213507F,
    0xD7550802, 0xD8000000, 0xD9110000, 0x26066470, 0xE400061A, 0x1A262870, 0xE400203E, 0xFFFE0000, 0xD0FF0000,
    0xF7FF0000, 0xD5FF0000, 0xD241507F, 0xD77F000F, 0xD8000000, 0xD9110000, 0x24066360, 0xD242507F, 0xD77F000F,
    0xD8000000, 0xD9110000, 0x181C6360, 0xD213507F, 0xD7550802, 0xD8000000, 0xD9110000, 0x26066420, 0xE400061A,
    0x1A262820, 0xE400203E, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF713507F, 0xD213507F, 0xD77F0905, 0xD8000000,
    0xD9110000, 0x3912017F, 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD23F0000, 0xDF00000F, 0xD77F000F,
    0xD8000000, 0xD91F0000, 0x1D2C6350, 0xE4061811, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF738507F, 0xD238507F,
    0xD77F000F, 0xD8000000, 0xD9120000, 0x17126368, 0xE4000C15, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xD239507F,
    0xD77F000F, 0xD8000000, 0xD9100000, 0x18185058, 0xE4000C15, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF63D507F,
    0xD23D507F, 0xD77F000F, 0xD8000000, 0xD9110000, 0x16283C78, 0x16283C40, 0x16283C20, 0x16283C10, 0x16283C08,
    0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2270000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000,
    0x1B326350, 0xE403180F, 0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2270000, 0xDF00000F, 0xD77F000F,
    0xD8000000, 0xD91F0000, 0x1D206350, 0xFFFE0000, 0xD0800000, 0xD5DF0000, 0xF73C507F, 0xD23C507F, 0xD77F000F,
    0xD8000000, 0xD9100000, 0x18285048, 0xFFFE0000, 0xD0FF0100, 0xD5A80000, 0xF7040000, 0xD24A0000, 0xD77F000F,
    0xD8002854, 0xD9182854, 0x1C045A30, 0xD22A507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0x2B065A40, 0xD229507F,
    0xD77F000F, 0xD8000000, 0xD9180000, 0x2B0C5A40, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF6800000, 0xD2430000,
    0xD77F0F08, 0xD840647F, 0xD90F647F, 0x1A18507F, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD20A0130,
    0xD7620F06, 0xD8441430, 0xD9181430, 0x3C0C5068, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2050130,
    0xD74E0C08, 0xD8451430, 0xD9121430, 0xDD000430, 0xDF061430, 0x47601428, 0xE400201B, 0xFFFE0000, 0xD0FF0100,
    0xD5FF0000, 0xF6060118, 0xD20A0130, 0xD74E0C08, 0xD8451430, 0xD9111430, 0xDD000050, 0x2D600A64, 0xFFFE0000,
    0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2370130, 0xD74E0C08, 0xD8451430, 0xD9111430, 0xDD00FC20, 0x39600D3C,
    0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2370130, 0xD7520E04, 0xD8441430, 0xD9101430, 0xDD00FC30,
    0x37603C23, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6060118, 0xD2260130, 0xD7500F03, 0xD8441430, 0xD9161430,
    0xDD000440, 0x43600A20, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF613507F, 0xD213507F, 0xD7560808, 0xD8400000,
    0xD9120000, 0x37180A7F, 0xE404083E, 0x37180A30, 0xE404083E, 0x37180A18, 0xE404083E, 0xFFFE0000, 0xD0FF0000,
    0xD5FF0000, 0xF716507F, 0xD216507F, 0xD7560806, 0xD8400000, 0xD9120000, 0x2B180A20, 0xE4040832, 0xFFFE0000,
    0xD0800000, 0xD5FF0000, 0xD242507F, 0xD77F000F, 0xD8400000, 0xD9120000, 0x1C050A40, 0x26180A40, 0xFFFE0000,
    0xD0FF0100, 0xD5FF0000, 0xD2250000, 0xD77F000F, 0xD8480000, 0xD9140000, 0x18060118, 0xD2220000, 0xD77F000F,
    0xD8480000, 0xD9130000, 0xC180130,  0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xD2250000, 0xD77F000F, 0xD8480000,
    0xD9140000, 0x18060120, 0xD2240000, 0xD77F000F, 0xD8480000, 0xD9130000, 0xC180120,  0xFFFE0000, 0xD0FF0100,
    0xD5FF0000, 0xF7260000, 0xD2320000, 0xD760000F, 0xD8400000, 0xD9100000, 0xC070A30,  0x1060037F, 0xFFFE0000,
    0xD0FF0100, 0xD5FF0000, 0xF7260000, 0xD21E0000, 0xD77F000F, 0xD8000000, 0xD9140000, 0x15060A40, 0xD2240000,
    0xD77F000F, 0xD8400000, 0xD9110000, 0x13401430, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF7260000, 0xD24B0000,
    0xD7500F0D, 0xD8400000, 0xD9100000, 0x284C0A30, 0xE4000329, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7260000,
    0xD2320000, 0xD74E000F, 0xD8400000, 0xD9100000, 0x11903C7F, 0xFFFE0000, 0xD0FF0130, 0xD5FF0130, 0xF6160130,
    0xD2130130, 0xD77F000F, 0xD8001430, 0xD91C1430, 0x390C5030, 0xFFFE0000, 0xD0FF0000, 0xD5A80000, 0xF60E507F,
    0xD202507F, 0xD77F080C, 0xD8000000, 0xD9110000, 0xE7065040, 0x32045050, 0x36035040, 0xE8040000, 0xE7065040,
    0x32045012, 0x3603500C, 0xE8020000, 0xE7065040, 0x32045050, 0x36035040, 0xE8040000, 0xE7065040, 0x32045012,
    0x3603500C, 0xE8030000, 0xFFFE0000, 0xD0800100, 0xD5FF0000, 0xF7000000, 0xD2420130, 0xD77F000F, 0xD8001430,
    0xD9181430, 0x260C0140, 0xFFFE0000, 0xD0FF0000, 0xD5C00000, 0xD23F0100, 0xD77F000F, 0xD8000000, 0xD9000000,
    0x24036330, 0xE4000707, 0xD2470FFF, 0xD77F0F0C, 0xD8405A64, 0xD9115A64, 0x15062860, 0x1A182860, 0xFFFE0000,
    0xD0FF0100, 0xD5A00000, 0xF7260000, 0xD2260000, 0xD77F000F, 0xD8000000, 0xD9130000, 0x34015A60, 0x28015A60,
    0x34015A60, 0x28015A60, 0xD2280000, 0xD77F000F, 0xD8000000, 0xD9130000, 0x28185A40, 0xFFFE0000, 0xD0FF0100,
    0xD5B00000, 0xD2400000, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x1B095A7F, 0xD77F0F01, 0xD9132040, 0x13205060,
    0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7040000, 0xD23F0000, 0xD77F000F, 0xD8000000, 0xD9000000, 0x1106637F,
    0x1806637F, 0xD23F0000, 0xDF10000F, 0xD77F000F, 0xD8000000, 0xD9000000, 0xC07647F,  0xE4000705, 0xD77F0F0C,
    0xD8405A64, 0xD9105A64, 0x890467F,  0xE4009000, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD210507F, 0xD77F000F,
    0xD8000000, 0xD9180000, 0x26030140, 0xE4000328, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD210507F, 0xD77F000F,
    0xD8000000, 0xD9180000, 0x26030140, 0xE4000328, 0xD210507F, 0xD77F000F, 0xD8000000, 0xD9140000, 0x150C0A40,
    0xE4000C21, 0x150C0A20, 0xE4000C21, 0x150C0A10, 0xE4000C21, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD20D507F,
    0xD77F0F08, 0xD8000000, 0xD91F0000, 0x280C1E30, 0x281C6330, 0xFFFE0000, 0xD0FF0000, 0xD5600000, 0xD204507F,
    0xD77F000F, 0xD8000000, 0xD9180000, 0x47030168, 0x23030168, 0xE7060140, 0x3B015A60, 0x3A015A60, 0xE803009D,
    0x47030158, 0x23030158, 0xE7060140, 0x3B015A50, 0x3A015A50, 0xE803009D, 0xFFFE0000, 0xD0FF0000, 0xD5C00000,
    0xD241507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0x3C01647F, 0x240E507F, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF707507F, 0xD23F507F, 0xD77F000F, 0xD8000000, 0xD90F0000, 0x15056360, 0x9056332,  0x405637F,  0x10FF6360,
    0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF707507F, 0xD204507F, 0xD77F000F, 0xD800507F, 0xD914507F, 0x1805017F,
    0xC050150,  0xD204507F, 0xD77F0008, 0xD87F0000, 0xD9100000, 0x13F637F,  0xD77F0004, 0x3C02830,  0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xF707507F, 0xD242507F, 0xD77F000F, 0xD8000000, 0xD9190000, 0x24090140, 0x2B0C0120,
    0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7260000, 0xD21E0000, 0xD77F000F, 0xD8480000, 0xD9140000, 0x18060130,
    0xD2320000, 0xD77F000F, 0xD8420000, 0xD9130000, 0xC303C60,  0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7260000,
    0xD2320000, 0xD74A000F, 0xD8400000, 0xD9100000, 0x17905A7F, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF707507F,
    0xD229507F, 0xD75E000F, 0xD8000000, 0xD9120000, 0x2D0A0148, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF707507F,
    0xD22A507F, 0xD75E000F, 0xD8000000, 0xD9120000, 0x2E0A0148, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F,
    0xE3FF00FF, 0xD226507F, 0xD74C0608, 0xD8000000, 0xD9100000, 0xE5004006, 0x70C6430,  0xE70C6446, 0xF30C6446,
    0xE8000000, 0xF3600100, 0xE4006002, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD232507F, 0xD750000F,
    0xD8000000, 0xD90A0000, 0xE500070C, 0x12103260, 0xD753000F, 0xE5000100, 0x18203C40, 0xD219507F, 0xD742000F,
    0xD8000000, 0xD9110000, 0x390C6403, 0xE7C06446, 0xF30C6446, 0xE8000000, 0xF3180100, 0xE4001835, 0xD232507F,
    0xD750000F, 0xD8000000, 0xD9100000, 0xE5000803, 0x12153260, 0x18303C40, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF607507F, 0xD24B507F, 0xD742000F, 0xD8000000, 0xD9110000, 0x1D0C6410, 0xE7605A32, 0xF30C6432, 0xE8000000,
    0xF318017F, 0xD203507F, 0xD74A0808, 0xD83C0000, 0xD9100000, 0x2B603218, 0xE4006010, 0xFFFE0000, 0xD0FF0000,
    0xD5C80000, 0xF625507F, 0xD225507F, 0xD760000F, 0xD8000000, 0xD91B0000, 0x39030120, 0xD9170000, 0x3A05017F,
    0xD91A0000, 0x38030120, 0xD9160000, 0x39060178, 0xD91B0000, 0x37030120, 0xD9160000, 0x3804016F, 0xD91A0000,
    0x38030120, 0xD9170000, 0x39060166, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF704507F, 0xD229507F, 0xD760000F,
    0xD8000000, 0xD90F0000, 0x2D06637F, 0xD22A507F, 0xD760000F, 0x2803637F, 0xD227507F, 0xD74F0A0F, 0xD8000000,
    0xD91E0000, 0x350C5A40, 0xD7440A0F, 0x37125A50, 0xFFFE0000, 0xD09B0000, 0xD5B40000, 0xF607507F, 0xD20D507F,
    0xD75C000F, 0xD8360000, 0xD9100000, 0xE106FF10, 0xE5000604, 0x22301434, 0x210E630C, 0xFFFE0000, 0xD0FF0000,
    0xD5A80000, 0xF707507F, 0xD204507F, 0xD75D000F, 0xD8000000, 0xD9150000, 0x23060A40, 0x200C0A40, 0xD229507F,
    0xD75D000F, 0xD8000000, 0xD90F0000, 0x2D0C6340, 0xD75D000F, 0x28086320, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF7420000, 0xD2420000, 0xD77F000F, 0xD8000000, 0xD91F0000, 0x1F040160, 0xD9180000, 0x24040160, 0x21205040,
    0xFFFE0000, 0xD0800000, 0xD5C00000, 0xF6800000, 0xD2440000, 0xD77F000F, 0xD8466350, 0xD9106350, 0xDD00F250,
    0x1C0E3C40, 0xDD000E50, 0x1A303C10, 0xFFFE0000, 0xD0FF0000, 0xD5800000, 0xF607507F, 0xD23F507F, 0xD77F000F,
    0xD8000000, 0xD9140000, 0x39035A40, 0xE4000321, 0xD246507F, 0xD77F000F, 0xD8000000, 0xD9140000, 0x24065A40,
    0x260C5A40, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD245507F, 0xD77F000F, 0xD8000000, 0xD9130000, 0x1F245A50,
    0xE4081022, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD248507F, 0xD757000F, 0xD8000000, 0xD9190000, 0xE5001208,
    0x29185A50, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD248507F, 0xD757000F, 0xD8000000, 0xD9190000, 0xE5001208,
    0x21185A50, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD23F507F, 0xD77F0F07, 0xD8440000, 0xD9190000, 0x1C035040,
    0xD247507F, 0xD77F0F0A, 0xD8000000, 0xD9120000, 0x18200A60, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xD247507F,
    0xD77F0F0A, 0xD8000000, 0xD9120000, 0x1A205050, 0xE4061815, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF707507F,
    0xD209507F, 0xD7550A08, 0xD84A0000, 0xD90F0000, 0xE100FF0F, 0x3C303214, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF604507F, 0xD213507F, 0xD7560C06, 0xD8480000, 0xD9110000, 0xE5001224, 0x32240A20, 0xFFFE0000, 0xD0FF0000,
    0xD5FF0000, 0xF604507F, 0xD208507F, 0xD7540C06, 0xD8480000, 0xD9110000, 0xE5001218, 0x45240A0C, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xF605507F, 0xD204507F, 0xD7580F0A, 0xD8000000, 0xD91C0000, 0x2D105A18, 0xD207507F,
    0xD7560C06, 0xD8480000, 0xD9110000, 0xE50012F4, 0x39240A10, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF705507F,
    0xD20A507F, 0xD77F000F, 0xD8000000, 0xD91C0000, 0x2F0C5A12, 0xF613507F, 0xD213507F, 0xD7560C08, 0xD8480000,
    0xD9110000, 0xE50012F4, 0x34240A20, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6000000, 0xD2130130, 0xD77F000F,
    0xD8001430, 0xD91C1430, 0x3C060130, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF61B507F, 0xD203507F, 0xD755000F,
    0xD8000000, 0xD9110000, 0xE5002418, 0x45245030, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xF6000000, 0xD20A0130,
    0xD77F000F, 0xD8001430, 0xD91A1430, 0x3C0C1430, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xF6000000, 0xD2130130,
    0xD77F000F, 0xD84D1430, 0xD91C1430, 0x39035030, 0xD2160130, 0xD77F000F, 0xD8001430, 0xD91A1430, 0x390C0A12,
    0x390C0A04, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF70E507F, 0xD213507F, 0xD77F000F, 0xD8000000, 0xD9160000,
    0xE7065040, 0x3C010118, 0x3C010118, 0xE8080000, 0xF3080140, 0xE4000837, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF70E507F, 0xD217507F, 0xD77F000F, 0xD8000000, 0xD9140000, 0x46183C07, 0xE4100835, 0xFFFE0000, 0xD0FF0000,
    0xD5C00000, 0xF613507F, 0xD20A507F, 0xD77F0F08, 0xD8480000, 0xD9140000, 0x2B06017F, 0xE4030339, 0x37060140,
    0xE4030339, 0x37060130, 0xE4030339, 0x37060120, 0xE4030339, 0x37060118, 0xE4030339, 0x3706010C, 0xE4030339,
    0x37060106, 0xE4030339, 0xFFFE0000, 0xD0FF0000, 0xD5400000, 0xF613507F, 0xD211507F, 0xD760000F, 0xD8000000,
    0xD9120000, 0x2F060140, 0x36060160, 0x3B06017F, 0x42060130, 0x47060140, 0x42060118, 0x47060120, 0xFFFE0000,
    0xD0FF0000, 0xD5A80000, 0xF613507F, 0xDF08507F, 0xD20E507F, 0xD758000F, 0xD8360000, 0xD9160000, 0xE5010C18,
    0x3B0C5060, 0x3E0B5050, 0x410A5040, 0x440A5030, 0x47095020, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F,
    0xD226507F, 0xD77F0C08, 0xD83A0000, 0xD90F0000, 0xDD00007F, 0x3CFF647F, 0xE400FF30, 0xF3803C7F, 0xE400FF2A,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD219507F, 0xD77F0C08, 0xD83A0000, 0xD90F0000, 0xDD00007F,
    0x45FF6440, 0xF3803C00, 0xFFFE0000, 0xD0FF0000, 0xD5800000, 0xF607507F, 0xD203507F, 0xD77F0F0A, 0xD8480000,
    0xD9160000, 0xD640FF40, 0xDF0BEC40, 0xED00EC40, 0xDD00EC40, 0x3B04017F, 0xDD001440, 0x38040170, 0xDD00EC40,
    0x36040160, 0xDD001440, 0x39040170, 0xDD00EC40, 0x3B04017F, 0xDD001440, 0x38040170, 0xDD00EC40, 0x36040160,
    0xDD001440, 0x39040170, 0xEE00EC40, 0xDF0AEC40, 0xEE00EC40, 0xDF09EC40, 0xEE00EC40, 0xD6F40040, 0xDF08EC40,
    0xEE00EC40, 0xDF07EC40, 0xEE00EC40, 0xDF06EC40, 0xEE00EC40, 0xDF05EC40, 0xEE00EC40, 0xDF04EC40, 0xEE00EC40,
    0xDF03EC40, 0xEE00EC40, 0xDF02EC40, 0xEE00EC40, 0xDF01EC40, 0xEE00EC40, 0xFFFE0000, 0xD0FF0000, 0xD5800000,
    0xF707507F, 0xDF0C507F, 0xD209507F, 0xD7600C0F, 0xD8440000, 0xD9120000, 0xED00017F, 0xE000017F, 0x3B040130,
    0xE00C2860, 0x3C0C2820, 0xE0060150, 0x3B040118, 0xE0122860, 0x3C0C2818, 0xE0062830, 0x3C0C2810, 0xEE04F400,
    0xD5700740, 0xEE040740, 0xD5600740, 0xEE040740, 0xD5400740, 0xEE040740, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF707507F, 0xD229507F, 0xD77F0F08, 0xD8000000, 0xD91F0000, 0x32020140, 0xD229507F, 0xD75E000F, 0xD8000000,
    0xD9120000, 0x2B0A0140, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF707507F, 0xD229507F, 0xD77F0F08, 0xD8000000,
    0xD91F0000, 0x33020140, 0xD22A507F, 0xD75E000F, 0xD8000000, 0xD9120000, 0x2D0A0140, 0xFFFE0000, 0xD0FF0000,
    0xD5FF0000, 0xF732507F, 0xD247507F, 0xD758000F, 0xD8000000, 0xD9130000, 0x21035050, 0x15065040, 0xD240507F,
    0xD77F000F, 0xD8000000, 0xD9130000, 0x14182830, 0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF6800000, 0xD2270000,
    0xD77F0F08, 0xD8420000, 0xD9110000, 0x1A12507F, 0x1A125060, 0x1A125030, 0x1A125018, 0x1A12500C, 0x1A125006,
    0xFFFE0000, 0xD0800000, 0xD5FF0000, 0xF6800000, 0xD2270000, 0xD77F000F, 0xD8420000, 0xD9110000, 0x24105060,
    0xD2490000, 0xD77F0F08, 0xD8420000, 0xD9110000, 0x2D0C507F, 0x2D0A5020, 0x2D185010, 0xFFFE0000, 0xD0800000,
    0xD5FF0000, 0xF6800000, 0xD2160000, 0xD77F0F08, 0xD8420000, 0xD9110000, 0xDD00F120, 0x47060410, 0x440C040C,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF613507F, 0xD216507F, 0xD77F000F, 0xD8360000, 0xD9180000, 0xDD000F7F,
    0x3C091E10, 0xD77F0F0B, 0xD8420000, 0xD9120000, 0x3C405018, 0xFFFE0000, 0xD0C00100, 0xD5C00000, 0xF6390130,
    0xD23A0130, 0xD754000F, 0xD8001430, 0xD9121430, 0xE5001805, 0x1730507F, 0x17305040, 0x17305020, 0x17305018,
    0x1730500C, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF705507F, 0xD20A507F, 0xD77F000F, 0xD83E0000, 0xD91C0000,
    0xDD000018, 0x2F0F4612, 0x2F23460C, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF605507F, 0xD204507F, 0xD77F0F0A,
    0xD8000000, 0xD91C0000, 0xDD000020, 0x3901640A, 0x2D016410, 0x32016418, 0xE7016420, 0xED016410, 0x39016420,
    0x2D016420, 0x32016420, 0xEE05FFF8, 0xE80400F8, 0xE7000000, 0xEE000000, 0xE805FEF8, 0xFFFE0000, 0xD0FF0000,
    0xD5A80000, 0xF700507F, 0xD213507F, 0xD77F000F, 0xD8000000, 0xD9140000, 0xE7066430, 0xE0006418, 0x2A016418,
    0xE0106410, 0x29016412, 0xE8080000, 0xE7066430, 0xE0006418, 0x2A016418, 0xE0106410, 0x29016412, 0xE808FEF8,
    0x2A020100, 0xFFFE0000, 0xD0AA507F, 0xD5C8507F, 0xF745507F, 0xD232000F, 0xD77F000F, 0xD8000000, 0xD9110000,
    0x1108506E, 0xD754000F, 0x1D40506E, 0xE418181C, 0xFFFE0000, 0xD0AA507F, 0xD5C8507F, 0xF745507F, 0xD23F000F,
    0xD77F000F, 0xD8000000, 0xD9120000, 0xF2040A50, 0xC480A50,  0xFFFE0000, 0xD0800000, 0xD5AA0000, 0xF704507F,
    0xD24A507F, 0xD764000F, 0xD8000000, 0xD9120000, 0x30063218, 0x2F063216, 0x30063218, 0x2F073216, 0xFFFE0000,
    0xD0800000, 0xD5AA0000, 0xF704507F, 0xD24B507F, 0xD768000F, 0xD8000000, 0xD9120000, 0x1C303230, 0xFFFE0000,
    0xD0800000, 0xD5FF0000, 0xF642507F, 0xD242507F, 0xD77F000F, 0xD8400000, 0xD9120000, 0x1C030A40, 0x24180A40,
    0xFFFE0000, 0xD0FF0100, 0xD5C00000, 0xF6330000, 0xD2110000, 0xD77F0F06, 0xD8400000, 0xD9100000, 0x34400A50,
    0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xF218507F, 0xD232507F, 0xD750000F, 0xD8000000, 0xD9100000,
    0xE5000803, 0x12153240, 0x18303C28, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD203507F, 0xD74A0F08,
    0xD83C0000, 0xD9100000, 0x1F601E40, 0xE4005E0C, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xD204507F, 0xD75B000F,
    0xD8000000, 0xD9150000, 0x23060A30, 0x280C1420, 0xD2450000, 0xD75D0808, 0xD8400000, 0xD9100000, 0x18061E20,
    0x18061E10, 0xFFFE0000, 0xD0FF0100, 0xD5A00000, 0xD204507F, 0xD75B000F, 0xD8000000, 0xD9150000, 0x23060A30,
    0x1F0C1420, 0xD2450000, 0xD75D0808, 0xD8400000, 0xD9100000, 0x18061E20, 0x18061E10, 0xFFFE0000, 0xD0FF0000,
    0xD5FF0000, 0xF642507F, 0xD245507F, 0xD77F000F, 0xD8000000, 0xD9140000, 0x24090A30, 0xD201507F, 0xD77F0F0A,
    0xD8440000, 0xD9130000, 0x30120A40, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6040000, 0xD24C0000, 0xD7500F0F,
    0xD8000000, 0xD9110000, 0x1C482830, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF7040000, 0xD23F0000, 0xD77F000F,
    0xD8000000, 0xD9130000, 0x10093260, 0xD77F000F, 0xD8005A64, 0xD9105A64, 0x24485050, 0xE4002C00, 0xFFFE0000,
    0xD0FF0100, 0xD5780000, 0xF6040000, 0xF2030000, 0xE0100000, 0xD2130000, 0xD77F0F08, 0xD8000000, 0xD9120000,
    0xDD00F630, 0x39050130, 0x36050138, 0x38050140, 0x35050148, 0x3B050150, 0x38050158, 0x3A050160, 0x37050158,
    0x3A050150, 0x37050148, 0x39050140, 0x36050148, 0x3C050150, 0x39050158, 0x3B050160, 0x38050158, 0x3B050150,
    0x38050148, 0x3A050140, 0x37050138, 0x3D050130, 0x3A050128, 0x3C050120, 0x39050118, 0x3B050110, 0x3805010C,
    0x3A050108, 0x37050105, 0xFFFE0000, 0xD0FF0100, 0xD5780000, 0xF6040000, 0xD2130000, 0xD77F0F08, 0xD8000000,
    0xD9120000, 0xDD000A30, 0x3A050130, 0x37050138, 0x39050140, 0x36050148, 0x3C050150, 0x39050158, 0x3B050160,
    0x38050158, 0x39050150, 0x36050148, 0x38050140, 0x35050148, 0x3B050150, 0x38050158, 0x3A050160, 0x37050158,
    0x3B050150, 0x38050148, 0x3A050140, 0x37050138, 0x3D050130, 0x3A050128, 0x3C050120, 0x39050118, 0x3B050110,
    0x3805010C, 0x3A050108, 0x37050105, 0xFFFE0000, 0xD0C00100, 0xD5DF0000, 0xF6390130, 0xD23A0130, 0xD77F000F,
    0xD8001430, 0xD9121430, 0xE50B06FD, 0xDD000060, 0x132A5070, 0x132A5038, 0x132A501C, 0x132A500E, 0xFFFE0000,
    0xD0FF0000, 0xD5800000, 0xF7066430, 0xD24B507F, 0xD768000F, 0xD8000000, 0xD9130000, 0xDFF03210, 0x45303210,
    0xE4181842, 0xFFFE0000, 0xD0540000, 0xD5FF0000, 0xF6185A0A, 0xD2185A0A, 0xD77F0F05, 0xD8005A0A, 0xD90E5A0A,
    0xDD00000C, 0x33045A60, 0x39045A70, 0x3F045A7F, 0x450C5A70, 0x33045A0C, 0x39045A0E, 0x3F045A10, 0x45245A0E,
    0xFFFE0000, 0xD0540000, 0xD5FF0000, 0xF60C5A0A, 0xF20C5A0A, 0xD2185A0A, 0xD77F0F05, 0xD8005A0A, 0xD90E5A0A,
    0xDD00000C, 0x33045A18, 0x39045A1C, 0x3F045A20, 0x450C5A1C, 0x33045A06, 0x39045A07, 0x3F045A08, 0x450C5A07,
    0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A, 0xD744060A, 0xD83C5A0A, 0xD9105A0A, 0xDD00FA0C,
    0x3FA84620, 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6365A0A, 0xD2365A0A, 0xD744060A, 0xD83C5A0A, 0xD9105A0A,
    0xDD00060C, 0x3CA84620, 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6365A0A, 0xD2175A0A, 0xD744060A, 0xD83C5A0A,
    0xD9105A0A, 0xDD00000C, 0x39A84610, 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A, 0xD77F0806,
    0xD8385A0A, 0xD90F5A0A, 0xDD00000C, 0x39903C50, 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A, 0xD2365A0A,
    0xD77F0806, 0xD8385A0A, 0xD90F5A0A, 0xDD00000C, 0x38903C50, 0xFFFE0000, 0xD0400000, 0xD5FF0000, 0xF6175A0A,
    0xF2180A40, 0xD2355A0A, 0xD754080A, 0xD8385A0A, 0xD90F5A0A, 0xDD00000C, 0x22183C40, 0x21483230, 0xFFFE0000,
    0xD0FF0000, 0xD5FF0000, 0xF607507F, 0xD206507F, 0xD77F0F06, 0xD8000000, 0xD9120000, 0xDD000018, 0x46182860,
    0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6390130, 0xDD01F660, 0xD2040130, 0xD758000F, 0xD8001430, 0xD9121430,
    0x300C0A60, 0x240C0A60, 0x18180560, 0xD2480130, 0xD752000F, 0xD8001430, 0xD9121430, 0x1D095028, 0x1A095028,
    0x1C203C20, 0xE4002010, 0xFFFE0000, 0xD0FF0000, 0xD5C80000, 0xF6800000, 0xD2420000, 0xD7600F08, 0xD844647F,
    0xD91C647F, 0xDD00007F, 0x37180A7F, 0x2B180A20, 0x34180A40, 0x2B180A20, 0xFFFE0000, 0xD0FF0000, 0xD5FF0000,
    0xF607507F, 0xD207507F, 0xD77F000F, 0xD8000000, 0xD9180000, 0xDD000018, 0x47062818, 0x470C2818, 0xFFFE0000,
    0xD0FF0000, 0xD57F0000, 0xF604507F, 0xD204507F, 0xDD000F7F, 0xD77F000F, 0xD8001430, 0xD91C1430, 0x240C5014,
    0xD754000F, 0xD8001430, 0xD91C1430, 0x3030630E, 0xFFFE0000, 0xD0FF0000, 0xD57F0000, 0xF604507F, 0xD20A507F,
    0xDD000F7F, 0xD754000F, 0xD8001430, 0xD91C1430, 0x30406318, 0xE40C0637, 0xFFFE0000, 0xD0FF0100, 0xD5A00000,
    0xD204507F, 0xD759000F, 0xD8000000, 0xD9140000, 0x17060A40, 0x1C0C1430, 0x100C3C18, 0xFFFE0000, 0xD0FF0100,
    0xD5A00000, 0xD204507F, 0xD759000F, 0xD8000000, 0xD9140000, 0x1C060A40, 0x170C1430, 0xB0C3C18,  0xFFFE0000,
    0xD0FC0000, 0xD5C00000, 0xF613507F, 0xD20E507F, 0xD7540605, 0xD8400000, 0xD9120000, 0x2F202830, 0xE4002047,
    0xFFFE0000, 0xD0FC0100, 0xD5780000, 0xF613507F, 0xD237507F, 0xD77F000F, 0xD8400000, 0xD9120000, 0x30302810,
    0xFFFE0000, 0xD0FC0100, 0xD5780000, 0xF613507F, 0xD213507F, 0xD77F000F, 0xD8400000, 0xD9120000, 0x3030280C,
    0xFFFE0000, 0xD0780000, 0xF7FF0000, 0xD5FF0000, 0xD2270000, 0xDF00000F, 0xD77F000F, 0xD8000000, 0xD91F0000,
    0xE5000303, 0x1E206350, 0xE4041C1B, 0xFFFE0000, 0xD0FF0000, 0xD5600000, 0xF604507F, 0xD204507F, 0xDD00F67F,
    0xD77F000F, 0xD8001430, 0xD91C1430, 0x30035018, 0x24095018, 0xE4000C47, 0xFFFE0000, 0xD0FF0000, 0xD5600000,
    0xF604507F, 0xD20A507F, 0xDD00F67F, 0xD77F0F08, 0xD8401430, 0xD9121430, 0x30186340, 0xE4001846, 0xFFFE0000,
    0xD080507F, 0xD5C8507F, 0xF204000F, 0xD227000F, 0xD77F000F, 0xD83F0000, 0xD9110000, 0xE50004FA, 0x10302820,
    0xFFFE0000, 0xD080507F, 0xD5C8507F, 0xD232000F, 0xD754000F, 0xD8460000, 0xD9110000, 0x1030637F, 0xFFFE0000,
    0xD0FC0000, 0xD5FF0000, 0xF604507F, 0xDD01007F, 0xD203507F, 0xD77F000F, 0xD8001430, 0xD91F1430, 0x241A6320,
    0xE4001A39, 0xD226507F, 0xD77F0905, 0xD8471430, 0xD9121430, 0x3C145060, 0x3C145028, 0x3C1B3C14, 0xD203507F,
    0xD75C000F, 0xD8001430, 0xD9121430, 0x30302810, 0xE4003000, 0xFF008D00, 0xFFFE0000, 0xD0FC0000, 0xD5FF0000,
    0xF604507F, 0xDD01007F, 0xF2286318, 0xD219507F, 0xD74E000F, 0xD8001430, 0xD9121430, 0x2148320C, 0xD237000F,
    0xD77F000F, 0xD8001430, 0xD9121430, 0x39302808, 0xFFFE0000, 0xD0FC0000, 0xD5C80000, 0xF6920000, 0xD24D0100,
    0xD748000F, 0xD8000000, 0xD9110000, 0x16186428, 0xE4001818, 0xE7C05A64, 0x180C642C, 0xE8000000, 0xF3601464,
    0xFFFE0000, 0xD0FC0000, 0xD5FF0000, 0xF607507F, 0xD2190F0C, 0xD7440308, 0xD8400000, 0xD9110000, 0x24FF4628,
    0xFFFE0000, 0xD0FC0000, 0xD5FF0000, 0xF607507F, 0xD2190F0C, 0xD7440308, 0xD8400000, 0xD9110000, 0x22FF4614,
    0xFFFE0000, 0xD0FC0000, 0xD5FF0000, 0xF607507F, 0xD2360F0C, 0xD7440308, 0xD8400000, 0xD9110000, 0x2BFF4614,
    0xFFFE0000, 0xD0FF0000, 0xD5C00000, 0xF613507F, 0xD213507F, 0xD77F0905, 0xD8000000, 0xD9110000, 0xDD000E60,
    0x39120160, 0xFFFE0000, 0xD0FF0100, 0xD5FF0000, 0xF6260000, 0xD21E0000, 0xD77F000F, 0xD8000000, 0xD9140000,
    0x15060A40, 0xD2240000, 0xD77F000F, 0xD8400000, 0xD9110000, 0x13241430, 0xD2250000, 0xD77F000F, 0xD8480000,
    0xD9140000, 0x18060118, 0xD2220000, 0xD77F000F, 0xD8480000, 0xD9130000, 0xC180130,  0xFFFE0000, 0xD0FF0100,
    0xD5FF0000, 0xF7260000, 0xD2320000, 0xD74E000F, 0xD8400000, 0xD9100000, 0x11405A7F, 0xD2320000, 0xD760000F,
    0xD8400000, 0xD9100000, 0x1060037F, 0xFFFE0000, 0xD0FC0100, 0xD5960000, 0xF6800000, 0xD2270100, 0xD77F000F,
    0xD8006366, 0xD9196366, 0x22010146, 0xD24E0100, 0xD77F000F, 0xD8006366, 0xD9126366, 0xE00E6356, 0x220A635A,
    0xD762000F, 0x240F6324, 0xFFFE0000, 0xFFFE0000};
char SECTION(".data") se_tbl_800A22C4[] = {1, 1, 1, 0};

// temporary
#define SE_START 0x8009FDB8
// 0xFFFE0000 as seen above
#define SE_END 0x800A22C0
// contains pointers to the data above
// SePlay_800888F8
VECTOR SECTION(".data") se_tbl2_800A22C8[128] = { // temporary type, make struct
    {SE_END, SE_END, SE_END, 0x10140},
    {0x800A067C, SE_END, SE_END, 0x10110},
    {SE_START, SE_END, SE_END, 0x10110},
    {0x8009FDD8, SE_END, SE_END, 0x10130},
    {0x800A0A48, SE_END, SE_END, 0x10120},
    {0x800A1EE0, SE_END, SE_END, 0x10120},
    {0x800A1F08, SE_END, SE_END, 0x10120},
    {0x800A0F14, SE_END, SE_END, 0x10120},
    {0x800A0F90, SE_END, SE_END, 0x10130},
    {0x800A0FD4, SE_END, SE_END, 0x130},
    {0x800A1004, SE_END, SE_END, 0x190},
    {0x800A1338, SE_END, SE_END, 0x1B0},
    {0x800A13CC, SE_END, SE_END, 0x190},
    {0x800A1390, SE_END, SE_END, 0x190},
    {0x800A16E8, SE_END, SE_END, 0x3F0},
    {0x800A1408, 0x800A143C, 0x800A1468, 0x120},
    {0x800A0410, SE_END, SE_END, 0x190},
    {0x800A0470, SE_END, SE_END, 0x10101A0},
    {0x800A1BBC, SE_END, SE_END, 0x10101A0},
    {0x800A06A4, SE_END, SE_END, 0x10190},
    {0x800A088C, SE_END, SE_END, 0x120},
    {0x800A04C0, SE_END, SE_END, 0x290},
    {0x800A04F8, 0x800A0528, SE_END, 0x110},
    {0x800A0580, SE_END, SE_END, 0x10101A0},
    {0x800A05D0, SE_END, SE_END, 0x10101A0},
    {0x800A05F8, SE_END, SE_END, 0x10001F0},
    {0x800A061C, SE_END, SE_END, 0x10140},
    {0x800A0650, SE_END, SE_END, 0x10120},
    {0x800A06C8, SE_END, SE_END, 0x10110},
    {0x800A0EB8, SE_END, SE_END, 0x10120},
    {0x800A0714, SE_END, SE_END, 0x190},
    {0x800A0738, SE_END, SE_END, 0x290},
    {0x800A07DC, 0x800A0804, SE_END, 0x390},
    {0x800A075C, 0x800A078C, 0x800A07B4, 0x290},
    {0x800A082C, 0x800A0864, SE_END, 0x10190},
    {0x800A0BE0, SE_END, SE_END, 0x220},
    {0x800A12D8, 0x800A1310, SE_END, 0x10160},
    {0x800A0A6C, SE_END, SE_END, 0x10160},
    {0x8009FDF8, SE_END, SE_END, 0x10110},
    {0x8009FE18, SE_END, SE_END, 0x10140},
    {0x800A0AA8, SE_END, SE_END, 0x10190},
    {0x800A0B18, SE_END, SE_END, 0x1A0},
    {0x800A0300, SE_END, SE_END, 0x10120},
    {0x8009FE90, SE_END, SE_END, 0x10130},
    {0x8009FED8, SE_END, SE_END, 0x10130},
    {0x800A0AEC, SE_END, SE_END, 0x10130},
    {0x8009FF14, SE_END, SE_END, 0x10130},
    {0x8009FF5C, SE_END, SE_END, 0x10140},
    {0x800A0498, SE_END, SE_END, 0x10140},
    {0x8009FF88, SE_END, SE_END, 0x10140},
    {0x8009FFAC, SE_END, SE_END, 0x10170},
    {0x800A1608, SE_END, SE_END, 0x10140},
    {0x800A1114, SE_END, SE_END, 0x10140},
    {0x800A10E0, SE_END, SE_END, 0x110},
    {0x800A21BC, SE_END, SE_END, 0x10130},
    {0x800A0B70, SE_END, SE_END, 0x10120},
    {0x800A1098, SE_END, SE_END, 0x10120},
    {0x800A10BC, SE_END, SE_END, 0x290},
    {0x800A1A8C, 0x800A1B28, SE_END, 0x10160},
    {0x800A0C04, SE_END, SE_END, 0x10140},
    {0x800A004C, SE_END, SE_END, 0x10130},
    {0x800A00B8, SE_END, SE_END, 0x10140},
    {0x800A1034, SE_END, SE_END, 0x10160},
    {0x800A1074, SE_END, SE_END, 0x10130},
    {0x800A0204, SE_END, SE_END, 0x10290},
    {0x800A0C74, 0x800A0CA4, SE_END, 0x10170},
    {0x800A1A54, SE_END, SE_END, 0x10130},
    {0x800A21E4, SE_END, SE_END, 0x10130},
    {0x800A2244, SE_END, SE_END, 1},
    {SE_END, SE_END, SE_END, 1},
    {SE_END, SE_END, SE_END, 1},
    {SE_END, SE_END, SE_END, 0x10130},
    {0x800A0174, SE_END, SE_END, 0x10140},
    {0x800A1FA0, SE_END, SE_END, 0x280},
    {0x800A1FD0, 0x800A2000, SE_END, 0x1FF},
    {0x800A2118, SE_END, SE_END, 0x10140},
    {0x800A05A4, SE_END, SE_END, 0x10140},
    {0x800A01A8, SE_END, SE_END, 0x10130},
    {0x800A0230, SE_END, SE_END, 0x130},
    {0x800A0254, SE_END, SE_END, 0x10130},
    {0x800A0280, SE_END, SE_END, 0x10160},
    {0x800A02A4, SE_END, SE_END, 0x10140},
    {0x800A02C8, SE_END, SE_END, 0x3A0},
    {0x800A033C, 0x800A0380, 0x800A03C8, 0x280},
    {0x800A1160, 0x800A1188, SE_END, 0x180},
    {0x800A09C4, SE_END, SE_END, 0x180},
    {0x800A09E8, SE_END, SE_END, 0x280},
    {0x800A11B0, 0x800A11EC, SE_END, 0x10130},
    {0x800A08B0, SE_END, SE_END, 0x10130},
    {0x800A08E4, SE_END, SE_END, 0x10130},
    {0x800A0918, SE_END, SE_END, 0x10130},
    {0x800A0940, SE_END, SE_END, 0x10130},
    {0x800A0978, SE_END, SE_END, 0x10130},
    {0x800A09A0, SE_END, SE_END, 0x10110},
    {0x800A1BF4, SE_END, SE_END, 0x10190},
    {0x800A0C50, SE_END, SE_END, 0x10120},
    {0x800A0CE8, SE_END, SE_END, 0x10120},
    {0x800A0D10, SE_END, SE_END, 0x10120},
    {0x800A0D48, SE_END, SE_END, 0x10110},
    {0x800A1138, SE_END, SE_END, 0x3FF},
    {0x800A0DB4, 0x800A0DF4, 0x800A0E6C, 0x10140},
    {0x800A227C, SE_END, SE_END, 0x2F0},
    {0x800A1644, 0x800A167C, SE_END, 0x120},
    {0x800A122C, SE_END, SE_END, 0x180},
    {0x800A1278, SE_END, SE_END, 0x180},
    {0x800A129C, SE_END, SE_END, 0x190},
    {0x800A16BC, SE_END, SE_END, 0x1000190},
    {0x800A1720, SE_END, SE_END, 0x280},
    {0x800A1758, 0x800A1784, SE_END, 0x10120},
    {0x800A17DC, SE_END, SE_END, 0x10240},
    {0x800A1830, 0x800A1860, SE_END, 0x10230},
    {0x800A1888, 0x800A18B8, SE_END, 0x10120},
    {0x800A1904, SE_END, SE_END, 0x10230},
    {0x800A1928, 0x800A1958, SE_END, 0x190},
    {0x800A1A30, SE_END, SE_END, 0x1B0},
    {0x800A19F8, SE_END, SE_END, 0x140},
    {0x800A1E50, SE_END, SE_END, 0x1B0},
    {0x800A1E1C, SE_END, SE_END, 0x180},
    {0x800A1DCC, SE_END, SE_END, 0x1B0},
    {0x800A1DA4, SE_END, SE_END, 0x290},
    {0x800A1E7C, 0x800A1EB4, SE_END, 0x2F0},
    {0x800A1C20, 0x800A1C64, SE_END, 0x3F0},
    {0x800A1CAC, 0x800A1CD4, 0x800A1CFC, 0x3F0},
    {0x800A2150, 0x800A2174, 0x800A2198, 0x10240},
    {0x800A202C, 0x800A2054, SE_END, 0x2F0},
    {0x800A2074, 0x800A20D8, SE_END, 0x3B0},
    {0x800A1F30, 0x800A1F58, 0x800A1F7C, 0x190},
    {0x800A18DC, SE_END, SE_END, 1}};

int SECTION(".data") spu_ch_tbl_800A2AC8[] = {
    1,      2,      4,      8,      0x10,    0x20,    0x40,    0x80,    0x100,    0x200,    0x400,    0x800,
    0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000};

unsigned char SECTION(".data") blank_data_800A2B28[512] = {
    12u, 6u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 3u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u};

unsigned SECTION(".data") char byte_800A2D28[4096] = {
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 12u, 2u,
    0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u, 0u,  0u};

unsigned char SECTION(".data") v800A3D28[64] = {
    196u, 61u, 1u, 128u, 192u, 61u, 1u, 128u, 184u, 61u, 1u, 128u, 176u, 61u, 1u, 128u,
    152u, 61u, 1u, 128u, 128u, 61u, 1u, 128u, 112u, 61u, 1u, 128u, 92u,  61u, 1u, 128u,
    76u,  61u, 1u, 128u, 56u,  61u, 1u, 128u, 44u,  61u, 1u, 128u, 36u,  61u, 1u, 128u,
    20u,  61u, 1u, 128u, 16u,  61u, 1u, 128u, 16u,  61u, 1u, 128u, 16u,  61u, 1u, 128u};
