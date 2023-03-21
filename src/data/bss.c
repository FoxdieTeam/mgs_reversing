#include "bss.h"
#include "linker.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/control.h"
#include "Game/game.h"
#include "chara/snake/sna_init.h"
#include "memcard/memcard.h"
#include "map/map.h"
#include "Game/jimctrl.h"
#include "Game/strctrl.h"
#include "mts/mts_new.h"
#include "Game/homing_target.h"
#include "Bullet/jirai.h"
#include "Kojo/demothrd.h"
#include "SD/sd.h"
#include "Game/camera.h"
#include "Equip/jpegcam.h"

#define BSS SECTION(".bss")
#define gap char BSS

// simply add a new var at any random place below the line then run bss.py and it will automatically put it in then
// correct place and re-adjust the gaps, sizes, and byte size comments. the only thing allowed below the line are
// var declarations. put everything else in a header. all comments below the line will also be deleted.
// you must use "BSS" instead of SECTION, and for EVERY var.

// note: if any included headers has an extern to the same vars defined here, matches will fail. never put extern
// data in a header.

// --------------------------------------------------------------------------------------------------------------------

unsigned char BSS   main_task_stack_800ABBF0[2048]; // 0x800 (2048) bytes
unsigned int BSS    sdStack_800AC3F0[512]; // 0x800 (2048) bytes
int BSS             gDiskNum_800ACBF0; // 0x4 (4) bytes
int BSS             pad_800ACBF4; // 0x4 (4) bytes
GV_ACT BSS          gGVActor_800acbf8; // 0x20 (32) bytes
struct ActorList BSS gActorsList_800ACC18[ACTOR_LIST_COUNT]; // 0x264 (612) bytes

gap                                     gap_800ACE7C[0x4]; // 4 bytes

TFileExtHandler BSS gFileExtHandlers_800ACE80[MAX_FILE_HANDLERS]; // 0x68 (104) bytes

gap                                     gap_800ACEE8[0x8]; // 8 bytes

CacheSystems BSS    GV_CacheSystem_800ACEF0; // 0x400 (1024) bytes
GV_Heap BSS         MemorySystems_800AD2F0[3]; // 0x3030 (12336) bytes
GV_Messages BSS     gMessageQueue_800B0320[2]; // 0x288 (648) bytes
int BSS             dword_800B05A8[6]; // 0x18 (24) bytes
GV_PAD BSS          GV_PadData_800B05C0[4]; // 0x40 (64) bytes
DISPENV BSS         gDispEnv_800B0600; // 0x14 (20) bytes

gap                                     gap_800B0614[0xC]; // 12 bytes

VECTOR BSS          gUnknownVector_800B0620; // 0x10 (16) bytes
int BSS             dword_800B0630[68]; // 0x110 (272) bytes
int BSS             dword_800B0740[516]; // 0x810 (2064) bytes
int BSS             dword_800B0F50[4]; // 0x10 (16) bytes
DG_OBJS *BSS        dword_800B0F60[8]; // 0x20 (32) bytes
DG_OBJS *BSS        dword_800B0F80[256]; // 0x400 (1024) bytes
DR_ENV BSS          stru_800B1380[2]; // 0x80 (128) bytes
unsigned int *BSS   ptr_800B1400[256]; // 0x400 (1024) bytes
DG_CHNL BSS         DG_Chanls_800B1800[3]; // 0x5C4 (1476) bytes

gap                                     gap_800B1DC4[0x4]; // 4 bytes

unsigned short BSS  gOldRootCnt_800B1DC8[32]; // 0x40 (64) bytes
DG_FixedLight BSS   gFixedLights_800B1E08[8]; // 0x40 (64) bytes
DG_TmpLightList BSS LightSystems_800B1E48[2]; // 0x108 (264) bytes
DG_TEX BSS          gTextureRecs_800B1F50[512]; // 0x1800 (6144) bytes
GV_ACT BSS          gDgdActor2_800B3750; // 0x20 (32) bytes
GV_ACT BSS          gDgdActor1_800B3770; // 0x20 (32) bytes
int BSS             dword_800B3790; // 0x4 (4) bytes

gap                                     gap_800B3794[0x4]; // 4 bytes

unsigned char BSS   pcxBuffer_800B3798[128]; // 0x80 (128) bytes
u_long BSS          image_data_800B3818[256]; // 0x400 (1024) bytes
GCL_FileData BSS    gGCL_fileData_800B3C18; // 0xC (12) bytes

gap                                     gap_800B3C24[0x4]; // 4 bytes

int BSS             argstack_800B3C28[32]; // 0x80 (128) bytes
unsigned char *BSS  commandlines_800B3CA8[8]; // 0x20 (32) bytes
GCL_Vars BSS        gGcl_vars_800B3CC8; // 0x800 (2048) bytes
short BSS           gGcl_gameStateVars_800B44C8[0x60]; // 0xC0 (192) bytes
GCL_Vars BSS        gGcl_memVars_800b4588; // 0x800 (2048) bytes
char BSS            gStageName_800B4D88[16]; // 0x10 (16) bytes
short BSS           gGameState_800B4D98[0x60]; // 0xC0 (192) bytes
CDBIOS_TASK BSS     cd_bios_task_800B4E58; // 0x24 (36) bytes

gap                                     gap_800B4E7C[0xC]; // 12 bytes

unsigned int BSS    cd_bios_stack_800B4E88[256]; // 0x400 (1024) bytes
STAGE_FILE *BSS     gStageFile_800B5288; // 0x4 (4) bytes
int BSS             gLoaderStartTime_800B528C; // 0x4 (4) bytes
int BSS             gOverlayBinSize_800B5290; // 0x4 (4) bytes
int BSS             gSaveCache_800B5294; // 0x4 (4) bytes
int BSS             fs_stream_ref_count_800B5298; // 0x4 (4) bytes
int BSS             fs_dword_800B529C; // 0x4 (4) bytes
int BSS             fs_dword_800B52A0; // 0x4 (4) bytes
void *BSS           fs_stream_heap_800B52A4; // 0x4 (4) bytes
void *BSS           fs_stream_heap_end_800B52A8; // 0x4 (4) bytes
int BSS             fs_stream_heapSize_800B52AC; // 0x4 (4) bytes
int BSS             fs_dword_800B52B0; // 0x4 (4) bytes
void *BSS           fs_ptr_800B52B4; // 0x4 (4) bytes
void *BSS           fs_ptr_800B52B8; // 0x4 (4) bytes
void *BSS           fs_ptr_800B52BC; // 0x4 (4) bytes
unsigned int BSS    fs_stream_task_state_800B52C0; // 0x4 (4) bytes

gap                                     gap_800B52C4[0x4]; // 4 bytes

long BSS            gHardware_end_io_800B52C8; // 0x4 (4) bytes
long BSS            gHardware_end_write_800B52CC; // 0x4 (4) bytes
long BSS            gHardware_timeout_800B52D0; // 0x4 (4) bytes
long BSS            gHardware_new_device_800B52D4; // 0x4 (4) bytes
long BSS            gSoftware_end_io_800B52D8; // 0x4 (4) bytes
long BSS            gSoftware_end_write_800B52DC; // 0x4 (4) bytes
long BSS            gSoftware_timeout_800B52E0; // 0x4 (4) bytes
long BSS            gSoftware_new_device_800B52E4; // 0x4 (4) bytes
TMemCardFunc BSS    gHwCard_do_op_800B52E8; // 0x4 (4) bytes
TMemCardFunc BSS    gSwCard_do_op_800B52EC; // 0x4 (4) bytes
volatile int BSS    gSwCardLastOp_800B52F0; // 0x4 (4) bytes
volatile int BSS    gHwCardLastOp_800B52F4; // 0x4 (4) bytes
struct mem_card BSS gMemCards_800B52F8[2]; // 0x350 (848) bytes
volatile long BSS   gMemCard_io_size_800B5648; // 0x4 (4) bytes

gap                                     gap_800B564C[0x4]; // 4 bytes

CONTROL BSS         gDefaultControl_800B5650; // 0x7C (124) bytes

gap                                     gap_800B56CC[0x4]; // 4 bytes

CONTROL *BSS        GM_WhereList_800B56D0[96]; // 0x180 (384) bytes
AreaHistory BSS     gAreaHistory_800B5850; // 0x10 (16) bytes
char BSS            exe_name_800B5860[32]; // 0x20 (32) bytes
Actor_GM_Daemon BSS GM_Daemon_800B5880; // 0x28 (40) bytes

gap                                     gap_800B58A8[0x8]; // 8 bytes

DG_TEX BSS          gMenuTextureRec_800B58B0; // 0xC (12) bytes

gap                                     gap_800B58BC[0x4]; // 4 bytes

unsigned short BSS  gSystemCallbackProcs_800B58C0[6]; // 0xC (12) bytes

gap                                     gap_800B58CC[0x14]; // 20 bytes

BindStruct BSS      gBindsArray_800b58e0[128]; // 0xC00 (3072) bytes
TARGET BSS          gTargets_800B64E0[64]; // 0x1200 (4608) bytes
char BSS            GM_NoiseSound_800B76E0[4][3]; // 0xC (12) bytes

gap                                     gap_800B76EC[0x4]; // 4 bytes

UnkCameraStruct2 BSS gUnkCameraStruct2_800B76F0; // 0x24 (36) bytes

gap                                     gap_800B7714[0x4]; // 4 bytes

CAMERA BSS          GM_CameraList_800B7718[8]; // 0xA0 (160) bytes
UnkCameraStruct BSS gUnkCameraStruct_800B77B8; // 0x30 (48) bytes
GM_Camera BSS       GM_Camera_800B77E8; // 0x7C (124) bytes

gap                                     gap_800B7864[0x4]; // 4 bytes

UnkCameraStruct2 BSS gUnkCameraStruct2_800B7868; // 0x24 (36) bytes

gap                                     gap_800B788C[0x4]; // 4 bytes

DG_OBJS *BSS        StageObjs_800B7890[32]; // 0x80 (128) bytes
map_record BSS      gMapRecs_800B7910[16]; // 0x140 (320) bytes
unsigned char BSS   byte_800B7A50[2016]; // 0x7E0 (2016) bytes
Homing_Target BSS   gHomingTargets_800B8230[8]; // 0x80 (128) bytes
Actor_strctrl BSS   strctrl_800B82B0; // 0x40 (64) bytes
Actor_JimCtrl BSS   jimCtrlActor_800B82F0; // 0x48 (72) bytes

gap                                     gap_800B8338[0x1004]; // 4100 bytes

array_800B933C_child BSS array_800B933C[array_800B933C_SIZE]; // 0x20 (32) bytes

gap                                     gap_800B935C[0x4]; // 4 bytes

unsigned char BSS   gPrimBackingBuffers_800B9360[2][8192]; // 0x4000 (16384) bytes
Actor_MenuMan BSS   gMenuMan_800BD360; // 0x220 (544) bytes
MATRIX BSS          gRadarScaleMatrix_800BD580; // 0x20 (32) bytes
PANEL_TEXTURE BSS   gMenuLeftItems_800BD5A0[MENU_ITEMS_LEFT_COUNT]; // 0x1A4 (420) bytes

gap                                     gap_800BD744[0x4]; // 4 bytes

array_800BD748_child BSS array_800BD748[9]; // 0xD8 (216) bytes

gap                                     gap_800BD820[0x68]; // 104 bytes

PANEL_TEXTURE BSS   gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT]; // 0xDC (220) bytes

gap                                     gap_800BD964[0x4]; // 4 bytes

KCB BSS             font_800BD968; // 0x2C (44) bytes

gap                                     gap_800BD994[0x4]; // 4 bytes

SPRT BSS            gMenuSprt_800bd998; // 0x14 (20) bytes

gap                                     gap_800BD9AC[0x4]; // 4 bytes

SPRT BSS            gRadioNumberSprt_800bd9b0; // 0x14 (20) bytes

gap                                     gap_800BD9C4[0xC]; // 12 bytes

SPRT BSS            gRadioNumberSprt2_800bd9d0; // 0x14 (20) bytes

gap                                     gap_800BD9E4[0xC]; // 12 bytes

SPRT BSS            gRadioStringSprt_800BD9F0; // 0x14 (20) bytes

gap                                     gap_800BDA04[0xC]; // 12 bytes

PANEL_TEXTURE BSS   dword_800BDA10; // 0x14 (20) bytes

gap                                     gap_800BDA24[0xC]; // 12 bytes

PANEL_TEXTURE BSS   dword_800BDA30; // 0x14 (20) bytes

gap                                     gap_800BDA44[0x4]; // 4 bytes

menu_0x14 BSS       stru_800BDA48[2]; // 0x28 (40) bytes
UnkJimakuStruct BSS gUnkJimakuStruct_800BDA70; // 0x44 (68) bytes

gap                                     gap_800BDAB4[0x4]; // 4 bytes

radio_table BSS     gRadioBaseTable_800BDAB8; // 0x40 (64) bytes
radio_table BSS     gRadioOverTable_800BDAF8; // 0x40 (64) bytes
RadioMemory BSS     gRadioMemory_800BDB38[RADIO_MEMORY_COUNT]; // 0x140 (320) bytes
unsigned char BSS   gBulNames_800BDC78[64]; // 0x40 (64) bytes
short BSS           snake_mag_size_800BDCB8; // 0x2 (2) bytes
short BSS           snake_weapon_idx_800BDCBA; // 0x2 (2) bytes
short BSS           snake_weapon_max_ammo_800BDCBC; // 0x2 (2) bytes
short BSS           unk_800BDCBE; // 0x2 (2) bytes
short BSS           word_800BDCC0; // 0x2 (2) bytes

gap                                     gap_800BDCC4[0x4]; // 4 bytes

int BSS             dword_800BDCC8; // 0x4 (4) bytes
int BSS             dword_800BDCCC; // 0x4 (4) bytes
int BSS             dword_800BDCD0; // 0x4 (4) bytes

gap                                     gap_800BDCD4[0x4]; // 4 bytes

TMat8x8B BSS        gJpegcamMatrix2_800BDCD8; // 0x40 (64) bytes
DVECTOR BSS         dvector_800BDD18[3]; // 0xC (12) bytes

gap                                     gap_800BDD24[0x4]; // 4 bytes

int BSS             dword_800BDD28; // 0x4 (4) bytes

gap                                     gap_800BDD2C[0x4]; // 4 bytes

CONTROL *BSS        tenage_ctrls_800BDD30[16]; // 0x40 (64) bytes
int BSS             tenage_ctrls_count_800BDD70; // 0x4 (4) bytes

gap                                     gap_800BDD74[0x4]; // 4 bytes

Jirai_unknown BSS   stru_800BDD78[16]; // 0x100 (256) bytes
Jirai_unknown BSS   stru_800BDE78[8]; // 0x80 (128) bytes
int BSS             dword_800BDEF8[2]; // 0x8 (8) bytes
TARGET *BSS         target_800BDF00; // 0x4 (4) bytes

gap                                     gap_800BDF04[0x4]; // 4 bytes

map_record *BSS     claymore_map_record_800bdf08; // 0x4 (4) bytes

gap                                     gap_800BDF0C[0x4]; // 4 bytes

short BSS           gSparkRandomTable_800BDF10[0x40]; // 0x80 (128) bytes
SVECTOR BSS         stru_800BDF90; // 0x8 (8) bytes
int BSS             dword_800BDF98; // 0x4 (4) bytes
int BSS             dword_800BDF9C; // 0x4 (4) bytes
int BSS             dword_800BDFA0; // 0x4 (4) bytes

gap                                     gap_800BDFA4[0x4]; // 4 bytes

int BSS             dword_800BDFA8; // 0x4 (4) bytes

gap                                     gap_800BDFAC[0x4]; // 4 bytes

void BSS            (*pfn_800BDFB0)(); // 0x4 (4) bytes
unsigned short BSS (*pfn_800BDFB4)(unsigned short); // 0x4 (4) bytes
int BSS             dword_800BDFB8; // 0x4 (4) bytes
int BSS             dword_800BDFBC; // 0x4 (4) bytes
int BSS             dword_800BDFC0; // 0x4 (4) bytes
int BSS             dword_800BDFC4; // 0x4 (4) bytes

gap                                     gap_800BDFC8[0x800]; // 2048 bytes

unsigned int BSS    byte_800BE7C8[512]; // 0x800 (2048) bytes
int BSS             dword_800BEFC8; // 0x4 (4) bytes
int BSS             dword_800BEFCC; // 0x4 (4) bytes

gap                                     gap_800BEFD0[0x4]; // 4 bytes

int BSS             sd_debug_800BEFD4; // 0x4 (4) bytes

gap                                     gap_800BEFD8[0xC]; // 12 bytes

int BSS             stream_data_ptr_800BEFE4; // 0x4 (4) bytes

gap                                     gap_800BEFE8[0x8]; // 8 bytes

int BSS             dword_800BEFF0; // 0x4 (4) bytes

gap                                     gap_800BEFF4[0x4]; // 4 bytes

int BSS             dword_800BEFF8; // 0x4 (4) bytes

gap                                     gap_800BEFFC[0x4]; // 4 bytes

int BSS             dword_800BF000; // 0x4 (4) bytes
int BSS             se_tracks_800BF004; // 0x4 (4) bytes
int BSS             dword_800BF008; // 0x4 (4) bytes
int BSS             blank_data_addr_800BF00C; // 0x4 (4) bytes
char* BSS           cdload_buf_800BF010; // 0x4 (4) bytes
int BSS             se_fp_800BF014; // 0x4 (4) bytes
int BSS             sd_sng_code_buf_800BF018[16]; // 0x40 (64) bytes
char* BSS           CDLOAD_BUF_800BF058; // 0x4 (4) bytes
int BSS             sd_KaihiMode_800BF05C; // 0x4 (4) bytes
int BSS             spu_bgm_start_ptr_l_800BF060; // 0x4 (4) bytes
int BSS             dword_800BF064; // 0x4 (4) bytes
SEPLAYTBL BSS       se_playing_800BF068[8]; // 0x60 (96) bytes
int BSS             spu_bgm_start_ptr_r_800BF0C8; // 0x4 (4) bytes
int BSS             bstr_fade_inProgress_800BF0CC; // 0x4 (4) bytes
int BSS             mdata1_800BF0D0; // 0x4 (4) bytes
int BSS             mdata2_800BF0D4; // 0x4 (4) bytes
int BSS             mdata3_800BF0D8; // 0x4 (4) bytes
int BSS             mdata4_800BF0DC; // 0x4 (4) bytes
SEPLAYTBL BSS       se_request_800BF0E0[8]; // 0x60 (96) bytes
int BSS             spu_load_offset_800BF140; // 0x4 (4) bytes
int BSS             dword_800BF144; // 0x4 (4) bytes

gap                                     gap_800BF148[0xC]; // 12 bytes

int BSS             dword_800BF154; // 0x4 (4) bytes
int BSS             sng_status_800BF158; // 0x4 (4) bytes
int BSS             gStreamVol_800BF15C; // 0x4 (4) bytes
int BSS             dword_800BF160; // 0x4 (4) bytes

gap                                     gap_800BF164[0x8]; // 8 bytes

int BSS             gStr_FadeOut1_800BF16C; // 0x4 (4) bytes

gap                                     gap_800BF170[0x30]; // 48 bytes

int BSS             stop_jouchuu_se_800BF1A0; // 0x4 (4) bytes
int BSS             dword_800BF1A4; // 0x4 (4) bytes
int BSS             dword_800BF1A8; // 0x4 (4) bytes

gap                                     gap_800BF1AC[0x4]; // 4 bytes

int BSS             key_fg_800BF1B0; // 0x4 (4) bytes

gap                                     gap_800BF1B4[0x4]; // 4 bytes

int BSS             se_pan_800BF1B8[8]; // 0x20 (32) bytes
int BSS             dword_800BF1D8; // 0x4 (4) bytes

gap                                     gap_800BF1DC[0x4]; // 4 bytes

WAVE_W* BSS         voice_tbl_800BF1E0; // 0x4 (4) bytes

gap                                     gap_800BF1E4[0x4]; // 4 bytes

int BSS             bgm_idx_800BF1E8; // 0x4 (4) bytes
unsigned int BSS    mtrack_800BF1EC; // 0x4 (4) bytes
int BSS             se_vol_800BF1F0[8]; // 0x20 (32) bytes
int BSS             dword_800BF210; // 0x4 (4) bytes

gap                                     gap_800BF214[0x4]; // 4 bytes

SpuVoiceAttr BSS    voiceAttr_800BF218; // 0x40 (64) bytes
int BSS             dword_800BF258; // 0x4 (4) bytes
int BSS             sng_fout_fg_800BF25C; // 0x4 (4) bytes
int BSS             keyons_800BF260; // 0x4 (4) bytes
int BSS             dword_800BF264; // 0x4 (4) bytes
int BSS             dword_800BF268; // 0x4 (4) bytes
int BSS             dword_800BF26C; // 0x4 (4) bytes
int BSS             dword_800BF270; // 0x4 (4) bytes
int BSS             wave_unload_size_800BF274; // 0x4 (4) bytes

gap                                     gap_800BF278[0x4]; // 4 bytes

int BSS             dword_800BF27C; // 0x4 (4) bytes

gap                                     gap_800BF280[0x4]; // 4 bytes

char* BSS           se_header_800BF284; // 0x4 (4) bytes
int BSS             sd_code_read_800BF288; // 0x4 (4) bytes
int BSS             se_load_code_800BF28C; // 0x4 (4) bytes
int BSS             sng_fade_in_2_800BF290; // 0x4 (4) bytes
int BSS             dword_800BF294; // 0x4 (4) bytes
int BSS             sng_pause_fg_800BF298; // 0x4 (4) bytes
int BSS             keyoffs_800BF29C; // 0x4 (4) bytes

gap                                     gap_800BF2A0[0x8]; // 8 bytes

SOUND_W BSS         sound_w_800BF2A8[21]; // 0x1164 (4452) bytes

gap                                     gap_800C040C[0x4]; // 4 bytes

int BSS             dword_800C0410; // 0x4 (4) bytes

gap                                     gap_800C0414[0x8]; // 8 bytes

int BSS             sng_fadein_fg_800C041C; // 0x4 (4) bytes
unsigned char *BSS  sd_sng_data_800C0420; // 0x4 (4) bytes

gap                                     gap_800C0424[0x4]; // 4 bytes

int BSS             dword_800C0428; // 0x4 (4) bytes

gap                                     gap_800C042C[0x4]; // 4 bytes

int BSS             sng_fade_time_800C0430[14]; // 0x38 (56) bytes
char BSS            byte_800C0468[128]; // 0x80 (128) bytes
int BSS             song_end_800C04E8; // 0x4 (4) bytes
int BSS             dword_800C04EC; // 0x4 (4) bytes
int BSS             gStream_800C04F0; // 0x4 (4) bytes
int BSS             dword_800C04F4; // 0x4 (4) bytes
unsigned int BSS    sng_status_800C04F8; // 0x4 (4) bytes

gap                                     gap_800C04FC[0x4]; // 4 bytes

int BSS             dword_800C0500; // 0x4 (4) bytes

gap                                     gap_800C0504[0x4]; // 4 bytes

char* BSS           wave_load_ptr_800C0508; // 0x4 (4) bytes
int BSS             dword_800C050C; // 0x4 (4) bytes
int BSS             sng_syukan_fg_800C0510; // 0x4 (4) bytes
char* BSS           str_header_800C0514; // 0x4 (4) bytes
int BSS             sng_fout_term_800C0518; // 0x4 (4) bytes

gap                                     gap_800C051C[0x4]; // 4 bytes

unsigned char *BSS  se_exp_table_800C0520; // 0x4 (4) bytes
int BSS             keyd_800C0524; // 0x4 (4) bytes
int BSS             wave_load_code_800C0528; // 0x4 (4) bytes
int BSS             spu_wave_start_ptr_800C052C; // 0x4 (4) bytes
WAVE_W *BSS         voice_tbl_800C0530; // 0x4 (4) bytes

gap                                     gap_800C0534[0x4]; // 4 bytes

int BSS             sng_fade_value_800C0538[13]; // 0x34 (52) bytes

gap                                     gap_800C056C[0x4]; // 4 bytes

unsigned char *BSS  mptr_800C0570; // 0x4 (4) bytes
int BSS             se_rev_on_800C0574; // 0x4 (4) bytes
int BSS             wave_save_code_800C0578; // 0x4 (4) bytes
SOUND_W *BSS        sptr_800C057C; // 0x4 (4) bytes
int BSS             dword_800C0580; // 0x4 (4) bytes
int BSS             gStr_fadeout_2_800C0584; // 0x4 (4) bytes
unsigned char BSS   byte_800C0588[200]; // 0xC8 (200) bytes
int BSS             dword_800C0650; // 0x4 (4) bytes
int BSS             dword_800C0654; // 0x4 (4) bytes
SPU_TRACK_REG BSS   spu_tr_wk_800C0658[23]; // 0x564 (1380) bytes

gap                                     gap_800C0BBC[0x4]; // 4 bytes

int BSS             sng_fade_in_2_800C0BC0; // 0x4 (4) bytes

gap                                     gap_800C0BC4[0x4]; // 4 bytes

int BSS             fade_unk_1_800C0BC8[13]; // 0x34 (52) bytes
volatile int BSS    sd_flags_800C0BFC; // 0x4 (4) bytes
mts_msg *BSS        D_800C0C00; // 0x4 (4) bytes
mts_msg *BSS        D_800C0C04; // 0x4 (4) bytes

gap                                     gap_800C0C08[0x8]; // 8 bytes

signed char BSS     byte_800C0C10[32]; // 0x20 (32) bytes
mts_task BSS        gTasks_800C0C30[12]; // 0x180 (384) bytes
int BSS             gTaskIdx_800C0DB0; // 0x4 (4) bytes
int BSS             gMts_bits_800C0DB4; // 0x4 (4) bytes

gap                                     gap_800C0DB8[0x8]; // 8 bytes

unsigned int BSS    dword_800C0DC0[128]; // 0x200 (512) bytes
unsigned int BSS    dword_800C0FC0[256]; // 0x400 (1024) bytes
int BSS             gMts_active_task_idx_800C13C0; // 0x4 (4) bytes

gap                                     gap_800C13C4[0xC]; // 12 bytes

mts_msg BSS         gMtsMsgs_800C13D0[8]; // 0xA0 (160) bytes
char BSS            gMtsPadActBuffers_800C1470[2][6]; // 0xC (12) bytes

gap                                     gap_800C147C[0x4]; // 4 bytes

unsigned char BSS   gMtsPadRecvBuffers_800C1480[2][36]; // 0x48 (72) bytes

gap                                     gap_800C14C8[0x8]; // 8 bytes

unsigned char BSS   gMtsPadSendBuffers_800C14D0[2][8]; // 0x10 (16) bytes
short BSS           gMtsPadUnknBuffers_800C14E0[2][4]; // 0x10 (16) bytes
int BSS             gMtsPadInitStates_800C14F0[2]; // 0x8 (8) bytes

gap                                     gap_800C14F8[0x1D10]; // 7440 bytes

char BSS            gProgramBottom_800C3208[0x53DF8]; // 0x53DF8 (343544) bytes
unsigned char BSS   heap_80117000[0x6b000]; // 0x6B000 (438272) bytes
unsigned char BSS   heap_80182000[0x1F000]; // 0x1F000 (126976) bytes
char BSS            byte_801A1000[0x10000]; // 0x10000 (65536) bytes
char BSS            byte_801B1000[0x36800]; // 0x36800 (223232) bytes
char BSS            byte_801E7800[0x18700]; // 0x18700 (100096) bytes
char BSS            byte_801FFF00[240]; // 0xF0 (240) bytes
