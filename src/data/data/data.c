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
    {CHARA_SNAKE, sna_NewSnake_8005B650},
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

short SECTION(".data") word_8009D69C[15][64] = {
    {0x01EE, 0x0428, 0x056E, 0x0666, 0x072E, 0x07DA, 0x086E, 0x08F4, 0x096C, 0x09DA, 0x0A3E, 0x0A9A, 0x0AEE, 0x0B3E, 0x0B88, 0x0BCE, 0x0C0E, 0x0C4C, 0x0C86, 0x0CBC, 0x0CEF, 0x0D20, 0x0D4E, 0x0D78, 0x0DA2, 0x0DC8, 0x0DEE, 0x0E10, 0x0E32, 0x0E52, 0x0E6F, 0x0E8C, 0x0EA6, 0x0EC0, 0x0ED8, 0x0EEF, 0x0F04, 0x0F19, 0x0F2C, 0x0F3F, 0x0F50, 0x0F60, 0x0F6F, 0x0F7E, 0x0F8B, 0x0F98, 0x0FA3, 0x0FAE, 0x0FB8, 0x0FC2, 0x0FCA, 0x0FD2, 0x0FD9, 0x0FE0, 0x0FE6, 0x0FEB, 0x0FEF, 0x0FF3, 0x0FF7, 0x0FFA, 0x0FFC, 0x0FFE, 0x0FFF, 0x0FFF},
    {0x00B2, 0x0288, 0x03C6, 0x04C0, 0x0590, 0x0644, 0x06E4, 0x0774, 0x07F6, 0x086C, 0x08DA, 0x0940, 0x09A0, 0x09F8, 0x0A4C, 0x0A9A, 0x0AE2, 0x0B28, 0x0B6A, 0x0BA8, 0x0BE4, 0x0C1C, 0x0C52, 0x0C86, 0x0CB6, 0x0CE4, 0x0D10, 0x0D3A, 0x0D62, 0x0D8A, 0x0DAE, 0x0DD1, 0x0DF2, 0x0E13, 0x0E32, 0x0E4F, 0x0E6B, 0x0E86, 0x0E9F, 0x0EB8, 0x0ECF, 0x0EE5, 0x0EFA, 0x0F0E, 0x0F22, 0x0F34, 0x0F46, 0x0F56, 0x0F66, 0x0F75, 0x0F83, 0x0F90, 0x0F9D, 0x0FA9, 0x0FB4, 0x0FBE, 0x0FC8, 0x0FD1, 0x0FDA, 0x0FE2, 0x0FE9, 0x0FF0, 0x0FF6, 0x0FFC},
    {0x005C, 0x0196, 0x0298, 0x0374, 0x0434, 0x04E0, 0x057C, 0x060C, 0x0690, 0x070A, 0x077C, 0x07E6, 0x084A, 0x08AA, 0x0902, 0x0958, 0x09A8, 0x09F4, 0x0A3E, 0x0A84, 0x0AC6, 0x0B06, 0x0B42, 0x0B7C, 0x0BB4, 0x0BEA, 0x0C1D, 0x0C4E, 0x0C7E, 0x0CAC, 0x0CD7, 0x0D02, 0x0D2A, 0x0D51, 0x0D76, 0x0D9A, 0x0DBE, 0x0DDF, 0x0E00, 0x0E1E, 0x0E3C, 0x0E59, 0x0E75, 0x0E90, 0x0EAA, 0x0EC2, 0x0EDA, 0x0EF1, 0x0F07, 0x0F1C, 0x0F30, 0x0F44, 0x0F57, 0x0F69, 0x0F7A, 0x0F8B, 0x0F9A, 0x0FAA, 0x0FB8, 0x0FC6, 0x0FD3, 0x0FE0, 0x0FEC, 0x0FF7},
    {0x0038, 0x0110, 0x01D2, 0x0284, 0x0326, 0x03BE, 0x044C, 0x04D0, 0x054C, 0x05C2, 0x0632, 0x069C, 0x0700, 0x0760, 0x07BC, 0x0814, 0x0868, 0x08BA, 0x0906, 0x0952, 0x099A, 0x09DE, 0x0A20, 0x0A62, 0x0AA0, 0x0ADC, 0x0B14, 0x0B4C, 0x0B83, 0x0BB8, 0x0BEA, 0x0C1B, 0x0C4A, 0x0C78, 0x0CA6, 0x0CD0, 0x0CFA, 0x0D23, 0x0D4A, 0x0D71, 0x0D96, 0x0DBA, 0x0DDD, 0x0DFE, 0x0E20, 0x0E40, 0x0E5E, 0x0E7C, 0x0E9A, 0x0EB6, 0x0ED1, 0x0EEC, 0x0F06, 0x0F1F, 0x0F37, 0x0F4E, 0x0F65, 0x0F7C, 0x0F91, 0x0FA6, 0x0FBA, 0x0FCD, 0x0FE0, 0x0FF2},
    {0x0026, 0x00C0, 0x0152, 0x01DC, 0x0260, 0x02DE, 0x0356, 0x03CA, 0x043A, 0x04A4, 0x050C, 0x056E, 0x05CE, 0x062C, 0x0684, 0x06DC, 0x0730, 0x0780, 0x07D0, 0x081C, 0x0866, 0x08AE, 0x08F6, 0x093A, 0x097C, 0x09BC, 0x09FC, 0x0A3A, 0x0A74, 0x0AAF, 0x0AE8, 0x0B20, 0x0B56, 0x0B8A, 0x0BBE, 0x0BF0, 0x0C20, 0x0C50, 0x0C7F, 0x0CAC, 0x0CD9, 0x0D04, 0x0D2F, 0x0D58, 0x0D81, 0x0DA8, 0x0DD0, 0x0DF6, 0x0E1A, 0x0E3E, 0x0E62, 0x0E84, 0x0EA6, 0x0EC8, 0x0EE8, 0x0F08, 0x0F26, 0x0F44, 0x0F62, 0x0F7F, 0x0F9B, 0x0FB6, 0x0FD2, 0x0FEC},
    {0x001C, 0x008C, 0x00FA, 0x0166, 0x01CE, 0x0234, 0x0298, 0x02F8, 0x0358, 0x03B4, 0x0410, 0x0468, 0x04BE, 0x0514, 0x0568, 0x05B8, 0x0608, 0x0656, 0x06A4, 0x06EE, 0x0738, 0x0782, 0x07C8, 0x080E, 0x0852, 0x0896, 0x08D8, 0x0918, 0x0958, 0x0996, 0x09D4, 0x0A10, 0x0A4C, 0x0A86, 0x0AC0, 0x0AF8, 0x0B2F, 0x0B66, 0x0B9C, 0x0BD0, 0x0C04, 0x0C36, 0x0C69, 0x0C9A, 0x0CCB, 0x0CFB, 0x0D2A, 0x0D58, 0x0D86, 0x0DB3, 0x0DE0, 0x0E0A, 0x0E36, 0x0E60, 0x0E8A, 0x0EB2, 0x0EDA, 0x0F02, 0x0F2A, 0x0F50, 0x0F76, 0x0F9C, 0x0FC0, 0x0FE4},
    {0x0014, 0x0068, 0x00BC, 0x0110, 0x0162, 0x01B2, 0x0204, 0x0252, 0x02A2, 0x02F0, 0x033C, 0x038A, 0x03D4, 0x0420, 0x046A, 0x04B4, 0x04FC, 0x0544, 0x058C, 0x05D2, 0x0618, 0x065E, 0x06A4, 0x06E8, 0x072A, 0x076E, 0x07B0, 0x07F2, 0x0832, 0x0874, 0x08B4, 0x08F2, 0x0932, 0x0970, 0x09AE, 0x09EC, 0x0A28, 0x0A64, 0x0AA0, 0x0ADA, 0x0B16, 0x0B50, 0x0B8A, 0x0BC2, 0x0BFA, 0x0C34, 0x0C6A, 0x0CA2, 0x0CD8, 0x0D10, 0x0D46, 0x0D7A, 0x0DB0, 0x0DE4, 0x0E18, 0x0E4C, 0x0E80, 0x0EB2, 0x0EE4, 0x0F16, 0x0F48, 0x0F7A, 0x0FAA, 0x0FDB},
    {0x000F, 0x004F, 0x008F, 0x00CF, 0x010F, 0x014F, 0x018F, 0x01CF, 0x020F, 0x024F, 0x028F, 0x02CF, 0x030F, 0x034F, 0x038F, 0x03CF, 0x040F, 0x044F, 0x048F, 0x04CF, 0x050F, 0x054F, 0x058F, 0x05CF, 0x060F, 0x064F, 0x068F, 0x06CF, 0x070F, 0x074F, 0x078F, 0x07CF, 0x080F, 0x084F, 0x088F, 0x08CF, 0x090F, 0x094F, 0x098F, 0x09CF, 0x0A0F, 0x0A4F, 0x0A8F, 0x0ACF, 0x0B0F, 0x0B4F, 0x0B8F, 0x0BCF, 0x0C0F, 0x0C4F, 0x0C8F, 0x0CCF, 0x0D0F, 0x0D4F, 0x0D8F, 0x0DCF, 0x0E0F, 0x0E4F, 0x0E8F, 0x0ECF, 0x0F0F, 0x0F4F, 0x0F8F, 0x0FCF},
    {0x000C, 0x003C, 0x006C, 0x009E, 0x00CE, 0x0100, 0x0132, 0x0166, 0x0198, 0x01CC, 0x0200, 0x0234, 0x0269, 0x029E, 0x02D4, 0x030A, 0x0340, 0x0378, 0x03B0, 0x03E8, 0x0420, 0x0458, 0x0492, 0x04CC, 0x0506, 0x0540, 0x057C, 0x05B8, 0x05F4, 0x0632, 0x066F, 0x06AE, 0x06EC, 0x072A, 0x076A, 0x07AA, 0x07EC, 0x082C, 0x086E, 0x08B2, 0x08F4, 0x0938, 0x097E, 0x09C2, 0x0A08, 0x0A4E, 0x0A96, 0x0ADE, 0x0B26, 0x0B70, 0x0BB8, 0x0C04, 0x0C4E, 0x0C9A, 0x0CE8, 0x0D36, 0x0D84, 0x0DD2, 0x0E22, 0x0E74, 0x0EC6, 0x0F18, 0x0F6C, 0x0FC0},
    {0x0008, 0x002C, 0x0050, 0x0076, 0x009C, 0x00C2, 0x00E8, 0x0110, 0x0138, 0x0160, 0x018A, 0x01B4, 0x01DE, 0x020A, 0x0235, 0x0262, 0x028F, 0x02BD, 0x02EC, 0x031C, 0x034C, 0x037C, 0x03AE, 0x03E0, 0x0414, 0x0448, 0x047E, 0x04B4, 0x04EA, 0x0522, 0x055C, 0x0596, 0x05D0, 0x060C, 0x0648, 0x0686, 0x06C6, 0x0706, 0x0748, 0x078A, 0x07CE, 0x0812, 0x085A, 0x08A0, 0x08EA, 0x0934, 0x0980, 0x09CE, 0x0A1E, 0x0A6E, 0x0AC0, 0x0B14, 0x0B6A, 0x0BC2, 0x0C1C, 0x0C78, 0x0CD6, 0x0D36, 0x0D98, 0x0DFC, 0x0E64, 0x0ECE, 0x0F3A, 0x0FAA},
    {0x0006, 0x0020, 0x003A, 0x0056, 0x0072, 0x008E, 0x00AB, 0x00C9, 0x00E8, 0x0107, 0x0127, 0x0148, 0x0169, 0x018B, 0x01AE, 0x01D2, 0x01F6, 0x021C, 0x0242, 0x026A, 0x0292, 0x02BA, 0x02E4, 0x0310, 0x033C, 0x0368, 0x0396, 0x03C6, 0x03F6, 0x0428, 0x045A, 0x048E, 0x04C4, 0x04FA, 0x0532, 0x056C, 0x05A6, 0x05E4, 0x0622, 0x0662, 0x06A2, 0x06E6, 0x072C, 0x0772, 0x07BC, 0x0808, 0x0856, 0x08A6, 0x08F8, 0x094E, 0x09A6, 0x0A00, 0x0A5E, 0x0AC0, 0x0B26, 0x0B8E, 0x0BFC, 0x0C6C, 0x0CE4, 0x0D5E, 0x0DE0, 0x0E66, 0x0EF4, 0x0F8A},
    {0x0004, 0x0016, 0x0028, 0x003B, 0x004F, 0x0064, 0x0078, 0x008E, 0x00A4, 0x00BC, 0x00D4, 0x00EC, 0x0106, 0x0120, 0x013B, 0x0157, 0x0174, 0x0191, 0x01B0, 0x01CF, 0x01EF, 0x0210, 0x0233, 0x0256, 0x027B, 0x02A0, 0x02C8, 0x02F0, 0x0318, 0x0344, 0x036F, 0x039C, 0x03CC, 0x03FC, 0x042E, 0x0460, 0x0496, 0x04CD, 0x0506, 0x0540, 0x057E, 0x05BC, 0x05FE, 0x0642, 0x0688, 0x06D2, 0x071E, 0x076C, 0x07C0, 0x0816, 0x086E, 0x08CC, 0x0930, 0x0996, 0x0A04, 0x0A76, 0x0AEE, 0x0B70, 0x0BF8, 0x0C8A, 0x0D28, 0x0DD2, 0x0E8A, 0x0F56},
    {0x0002, 0x000D, 0x0019, 0x0025, 0x0032, 0x0040, 0x004E, 0x005C, 0x006C, 0x007C, 0x008D, 0x009F, 0x00B1, 0x00C4, 0x00D8, 0x00ED, 0x0102, 0x0119, 0x0130, 0x0148, 0x0162, 0x017C, 0x0198, 0x01B4, 0x01D1, 0x01F0, 0x020F, 0x0230, 0x0252, 0x0276, 0x029A, 0x02C1, 0x02E8, 0x0312, 0x033D, 0x036A, 0x0398, 0x03C8, 0x03FA, 0x042F, 0x0466, 0x049E, 0x04DA, 0x0518, 0x055A, 0x059E, 0x05E4, 0x062E, 0x067E, 0x06D0, 0x0728, 0x0784, 0x07E4, 0x084C, 0x08BA, 0x0930, 0x09B0, 0x0A38, 0x0ACE, 0x0B72, 0x0C28, 0x0CF4, 0x0DE2, 0x0EFC},
    {0x0001, 0x0006, 0x000C, 0x0012, 0x0019, 0x0021, 0x0029, 0x0032, 0x003C, 0x0046, 0x0050, 0x005C, 0x0068, 0x0075, 0x0083, 0x0092, 0x00A1, 0x00B1, 0x00C2, 0x00D4, 0x00E6, 0x00FA, 0x010F, 0x0124, 0x013B, 0x0153, 0x016C, 0x0186, 0x01A2, 0x01BE, 0x01DC, 0x01FC, 0x021C, 0x023E, 0x0262, 0x0288, 0x02B0, 0x02D8, 0x0304, 0x0331, 0x0360, 0x0392, 0x03C6, 0x03FE, 0x0438, 0x0474, 0x04B4, 0x04F8, 0x0540, 0x058C, 0x05DC, 0x0632, 0x068E, 0x06F0, 0x075A, 0x07CC, 0x0848, 0x08D0, 0x0968, 0x0A10, 0x0AD2, 0x0BB4, 0x0CCC, 0x0E42},
    {0x0000, 0x0000, 0x0001, 0x0002, 0x0004, 0x0007, 0x000A, 0x000D, 0x0012, 0x0017, 0x001C, 0x0022, 0x0029, 0x0031, 0x0039, 0x0042, 0x004C, 0x0056, 0x0061, 0x006D, 0x007A, 0x0088, 0x0097, 0x00A6, 0x00B7, 0x00C9, 0x00DC, 0x00F0, 0x0105, 0x011B, 0x0132, 0x014B, 0x0166, 0x0181, 0x019E, 0x01BC, 0x01DD, 0x01FF, 0x0223, 0x0249, 0x0271, 0x029B, 0x02C8, 0x02F6, 0x0328, 0x035D, 0x0394, 0x03D0, 0x0410, 0x0452, 0x049A, 0x04E6, 0x0538, 0x0592, 0x05F2, 0x065A, 0x06CC, 0x074A, 0x07D8, 0x0878, 0x0930, 0x0A0C, 0x0B24, 0x0CB8}
};
int SECTION(".data") dword_8009DE1C[] = {0x10000, 0x10000, 0x8000, 0x5555, 0x4000, 0x3333, 0x2AAA, 0x2492,
                                         0x2000,  0x1C71,  0x1999, 0x1745, 0x1555, 0x13B1, 0x1249, 0x1111};

int SECTION(".data") dword_8009DE5C[] = {0x8001000, 0x4000555, 0x2AA0333, 0x2000249,
                                         0x19901C7, 0x1550174, 0x124013B, 0x1000111};
int SECTION(".data") dword_8009DE7C = 0;
int SECTION(".data") dword_8009DE80 = 0;
int SECTION(".data") dword_8009DE84 = 0;
int SECTION(".data") dword_8009DE88 = 0;
int SECTION(".data") dword_8009DE8C[] = {0, 0, 0, 0};
MATRIX SECTION(".data") matrix_8009DE9C = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {0, 0, 0}};

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

MenuPrim SECTION(".data") gMenuPrimBuffer_8009E2D0 = {{0, 0, 0}, {0, 0}};

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

RadioUnknown SECTION(".data") dword_8009E618 =
{
    {{1, 0, 7, 2}, {0, 1, 2, 7}, {7, 1, 2, 7}, {1, 7, 7, 2}, {0, 9, 2, 7}, {7, 9, 2, 7}, {1, 15, 7, 2}},
    0x3D472E,
    0x3D472E
};

RadioUnknown SECTION(".data") dword_8009E63C =
{
    {{1, 0, 5, 2}, {0, 1, 2, 6}, {5, 1, 2, 6}, {1, 6, 5, 2}, {0, 8, 2, 6}, {5, 8, 2, 6}, {1, 13, 5, 2}},
    0x3D472E,
    0x3D472E
};

char SECTION(".data") dword_8009E660[] = {10, 10, 15, 12};

Radio_8009E664 SECTION(".data") dword_8009E664[] = {
    // x0  y0   w   h    r0    g0    b0  code (code = TILE)
    {120,  58, 80, 48, 0x13, 0x1F, 0x1A, 0x60},
    {116,  55,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {199,  55,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {116, 107,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {199, 107,  5,  2, 0x20, 0x30, 0x29, 0x60},
    {121,  55, 78,  1, 0x20, 0x30, 0x29, 0x60},
    {121, 108, 78,  1, 0x20, 0x30, 0x29, 0x60},
    {129,  38, 62, 10, 0x13, 0x1F, 0x1A, 0x60},
    {129, 117, 62, 10, 0x13, 0x1F, 0x1A, 0x60},
    {90,   76, 25, 11, 0x13, 0x1F, 0x1A, 0x60},
    {205,  76, 25, 11, 0x13, 0x1F, 0x1A, 0x60},
    {84,   38, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193,  38, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {84,  126, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193, 126, 43,  1, 0x13, 0x1F, 0x1A, 0x60},
    {91,   46, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193,  46, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {91,  118, 36,  1, 0x13, 0x1F, 0x1A, 0x60},
    {193, 118, 36,  1, 0x13, 0x1F, 0x1A, 0x60}
};

RadioCoordsStru_8009E6FC SECTION(".data") gRadioCoords_8009E6FC[] = {
    {222, 81, 214, 77, 214, 85},
    {98,  81, 106, 77, 106, 85}
};
RadioIncomingCall SECTION(".data") gRadioIncomingCall_8009E708 = {0, 0, -1, 0};
int   SECTION(".data") dword_8009E714[] = {0x240022E, 0x45F023A, 0x63F0221, 0x62D062B, 0x62A062F, 0x37D037B, 0};
TUnkRadioFn SECTION(".data") dword_8009E730[] = {sub_80043678, sub_80043A24, sub_80043FD0, sub_800442E4, sub_800445F8};

extern char aEmpty[];
extern char aMem[];
extern char aPow[];
extern char aPly[];
extern char aObj[];
extern char aTex[];

char *SECTION(".data") dword_8009E744[] = {aEmpty, aMem, aPow, aPly, aObj, aTex};
void *SECTION(".data") dword_8009E75C[] = {NULL, NULL, NULL, NULL};

signed char SECTION(".data") dword_8009E76C[] = {-1, 0, 1, 0, 0, 1, 0, -1};

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
char *SECTION(".data") gMemoryCardNames_8009EC00[] = {(char *)aMemoryCard1, (char *)aMemoryCard2};
int  SECTION(".data") off_8009EC08[] = {(int)dword_800AB754, (int)aNo};
char SECTION(".data") dword_8009EC10[] = {0x82, 0x63, 0x82, 0x8F, 0x82, 0x83, 0x82, 0x8B, 0x00};
char *SECTION(".data") off_8009EC1C[] = {(char *)dword_800122D8, (char *)dword_800122CC, (char *)dword_800122C0,
                                        (char *)dword_800122B4, (char *)dword_800122A8};

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
    (void *)0x8005275C, // sna_anim_idle_8005275C
    (void *)0x800527DC, // sna_anim_crouch_800527DC
    (void *)0x800528BC  // sna_anim_prone_idle_800528BC
};

void *SECTION(".data") dword_8009EEB0[] = {
    (void *)0x80052A5C, // sna_anim_wall_idle_and_c4_80052A5C
    (void *)0x80052CCC  // sna_anim_wall_crouch_80052CCC
};

void *SECTION(".data") dword_8009EEB8[] = {
    (void *)0x8005292C, // sna_anim_run_8005292C
    (void *)0x8005292C, // sna_anim_run_8005292C
    (void *)0x800529C0  // sna_anim_prone_move_800529C0
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
WeaponCreateEntry kSnakeNoWeapon = {0, sna_anim_chokethrow_begin1_80054210};
*/

int SECTION(".data") dword_8009EF2C[] = {0x4C8023C, 0x228, 0, 0x80054210};

WeaponCreateEntry SECTION(".data") gSnakeWeapons_8009EF3C[] = {
    {NewSOCOM_80065D74, sna_gun_800540D0},
    {famas_create_80066374, sna_gun_800540D0},
    {grenade_create_80066A4C, sna_anim_grenade_80058470},
    {NewRCM_80066FF0, sna_gun_800540D0},
    {NewAAM_80067480, sna_anim_stinger_800570C0},
    {mine_init_800677BC, sna_anim_claymore_80057474},
    {NewBomb_80067B20, sna_bomb_800541A8},
    {NewStanGrenade_80066A74, sna_anim_grenade_80058470},
    {NewChaffGrenade_80066AA0, sna_anim_grenade_80058470},
    {NewRifle_80068214, sna_anim_psg1_80056DDC}};

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
