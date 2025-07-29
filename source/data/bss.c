#define __BSSDEFINE__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libspu.h> // for SpuVoiceAttr

#include "common.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/control.h"
#include "game/game.h"
#include "chara/snake/sna_init.h"
#include "memcard/memcard.h"
#include "game/map.h"
#include "game/jimctrl.h"
#include "game/strctrl.h"
#include "mts/mts_new.h"
#include "mts/mts_pad.h"
#include "mts/terminal.h"
#include "game/homing.h"
#include "game/hittable.h"
#include "sd/sd_cli.h"
#include "sd/sd_incl.h"
#include "game/camera.h"
#include "equip/equip.h"
#include "bullet/bakudan.h"

#define BSS SECTION(".bss")
#define gap char BSS

// simply add a new var at any random place below the line then run bss.py and it will automatically put it in then
// correct place and re-adjust the gaps, sizes, and byte size comments. the only thing allowed below the line are
// var declarations. put everything else in a header. all comments below the line will also be deleted.
// you must use "BSS" instead of SECTION, and for EVERY var.

// NOTE: If any included headers has an extern to the same vars defined here, matches will fail.
// Never put extern data in a header without wrapping it with #ifndef __BSSDEFINE__!!

// --------------------------------------------------------------------------------------------------------------------

/* main/main.obj */
char BSS            GameStack_800ABBF0[2048]; // 0x800 (2048) bytes
char BSS            SdStack_800AC3F0[2048]; // 0x800 (2048) bytes

/* libfs/select.obj */
int BSS             FS_DiskNum_800ACBF0; // 0x4 (4) bytes
int BSS             pad_800ACBF4; // 0x4 (4) bytes

/* libgv/gvd.obj */
GV_ACT BSS          GV_Work_800ACBF8; // 0x20 (32) bytes

/* libgv/actor.obj */
ActorList BSS       gActorsList_800ACC18[GV_ACTOR_LEVEL]; // 0x264 (612) bytes

gap                                     gap_800ACE7C[0x4]; // 4 bytes

/* libgv/cache.obj */
GV_LOADFUNC BSS     GV_LoaderFunctions[GV_MAX_LOADERS]; // 0x68 (104) bytes

gap                                     gap_800ACEE8[0x8]; // 8 bytes

GV_CACHE_PAGE BSS   GV_CacheSystem; // 0x400 (1024) bytes

/* libgv/memory.obj */
GV_HEAP BSS         MemorySystems_800AD2F0[3]; // 0x3030 (12336) bytes

/* libgv/message.obj */
MESSAGE_LIST BSS    message_list_800B0320[2]; // 0x288 (648) bytes

/* libgv/pad.obj */
int BSS             dword_800B05A8[6]; // 0x18 (24) bytes
GV_PAD BSS          GV_PadData_800B05C0[4]; // 0x40 (64) bytes

/* libdg/display.c */
DISPENV BSS         gDispEnv_800B0600; // 0x14 (20) bytes

gap                                     gap_800B0614[0xC]; // 12 bytes

VECTOR BSS          DG_RightVector_800B0620; // 0x10 (16) bytes

/* libdg/chanl.obj */
int BSS             dword_800B0630[68]; // 0x110 (272) bytes
int BSS             dword_800B0740[516]; // 0x810 (2064) bytes
int BSS             dword_800B0F50[4]; // 0x10 (16) bytes
DG_OBJS *BSS        dword_800B0F60[8]; // 0x20 (32) bytes
DG_OBJS *BSS        dword_800B0F80[256]; // 0x400 (1024) bytes
DR_ENV BSS          stru_800B1380[2]; // 0x80 (128) bytes
unsigned int *BSS   ptr_800B1400[256]; // 0x400 (1024) bytes
DG_CHANL BSS        DG_Chanls_800B1800[3]; // 0x5C4 (1476) bytes

gap                                     gap_800B1DC4[0x4]; // 4 bytes

unsigned short BSS  gOldRootCnt_800B1DC8[32]; // 0x40 (64) bytes

/* libdg/light.obj */
DG_FixedLight BSS   gFixedLights_800B1E08[8]; // 0x40 (64) bytes
DG_TmpLightList BSS LightSystems_800B1E48[2]; // 0x108 (264) bytes

/* libdg/text.obj */
DG_TEX BSS          DG_TextureCache[DG_MAX_TEXTURES]; // 0x1800 (6144) bytes

/* libdg/dgd.obj */
GV_ACT BSS          DG_StartFrameActor_800B3750; // 0x20 (32) bytes
GV_ACT BSS          DG_EndFrameActor_800B3770; // 0x20 (32) bytes
int BSS             dword_800B3790; // 0x4 (4) bytes

gap                                     gap_800B3794[0x4]; // 4 bytes

/* libdg/loader.obj */
unsigned char BSS   pcxBuffer_800B3798[128]; // 0x80 (128) bytes

/* libdg/palette.obj (?) */
u_long BSS          DG_PaletteBuffer_800B3818[256]; // 0x400 (1024) bytes

/* libgcl/command.obj */
GCL_SCRIPT BSS      current_script_800B3C18; // 0xC (12) bytes

gap                                     gap_800B3C24[0x4]; // 4 bytes

/* libgcl/parse.obj */
int BSS             argstack_800B3C28[32]; // 0x80 (128) bytes
unsigned char *BSS  commandlines_800B3CA8[8]; // 0x20 (32) bytes

/* libgcl/variable.obj */
GCL_Vars BSS        gGcl_vars_800B3CC8; // 0x800 (2048) bytes
short BSS           sv_linkvarbuf_800B44C8[0x60]; // 0xC0 (192) bytes
GCL_Vars BSS        gGcl_memVars_800b4588; // 0x800 (2048) bytes
char BSS            gStageName_800B4D88[16]; // 0x10 (16) bytes
short BSS           linkvarbuf_800B4D98[0x60]; // 0xC0 (192) bytes

/* libfs/cdbios.obj */
CDBIOS_TASK BSS     cd_bios_task_800B4E58; // 0x24 (36) bytes

gap                                     gap_800B4E7C[0xC]; // 12 bytes

char BSS            cd_bios_stack_800B4E88[1024]; // 0x400 (1024) bytes
FS_STAGE_INFO *BSS  gStageInfo_800B5288; // 0x4 (4) bytes
int BSS             gLoaderStartTime_800B528C; // 0x4 (4) bytes
int BSS             gOverlayBinSize_800B5290; // 0x4 (4) bytes
int BSS             FS_ResidentCacheDirty; // 0x4 (4) bytes
int BSS             fs_stream_ref_count_800B5298; // 0x4 (4) bytes
int BSS             fs_dword_800B529C; // 0x4 (4) bytes
int BSS             fs_dword_800B52A0; // 0x4 (4) bytes
void *BSS           fs_stream_heap_800B52A4; // 0x4 (4) bytes
char *BSS           fs_stream_heap_end_800B52A8; // 0x4 (4) bytes
int BSS             fs_stream_heapSize_800B52AC; // 0x4 (4) bytes
int BSS             fs_dword_800B52B0; // 0x4 (4) bytes
char *BSS           fs_ptr_800B52B4; // 0x4 (4) bytes
int *BSS            fs_ptr_800B52B8; // 0x4 (4) bytes
char *BSS           fs_ptr_800B52BC; // 0x4 (4) bytes
unsigned int BSS    fs_stream_task_state_800B52C0; // 0x4 (4) bytes

gap                                     gap_800B52C4[0x4]; // 4 bytes

/* memcard/memcard.obj */
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
MEM_CARD BSS        gMemCards_800B52F8[2]; // 0x350 (848) bytes
volatile long BSS   gMemCard_io_size_800B5648; // 0x4 (4) bytes

gap                                     gap_800B564C[0x4]; // 4 bytes

/* game/control.obj */
CONTROL BSS         gDefaultControl_800B5650; // 0x7C (124) bytes

gap                                     gap_800B56CC[0x4]; // 4 bytes

CONTROL *BSS        GM_WhereList_800B56D0[96]; // 0x180 (384) bytes
AreaHistory BSS     gAreaHistory_800B5850; // 0x10 (16) bytes
char BSS            exe_name_800B5860[32]; // 0x20 (32) bytes
GameWork BSS        GameWork_800B5880; // 0x28 (40) bytes

gap                                     gap_800B58A8[0x8]; // 8 bytes

DG_TEX BSS          gMenuTextureRec_800B58B0; // 0xC (12) bytes

gap                                     gap_800B58BC[0x4]; // 4 bytes

unsigned short BSS  gSystemCallbackProcs_800B58C0[6]; // 0xC (12) bytes

gap                                     gap_800B58CC[0x14]; // 20 bytes

HZD_BIND BSS      gBindsArray_800b58e0[128]; // 0xC00 (3072) bytes
TARGET BSS          gTargets_800B64E0[TARGET_ARRAY_LENGTH]; // 0x1200 (4608) bytes
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
MAP BSS      gMapRecs_800B7910[16]; // 0x140 (320) bytes
DG_LitVertex BSS    DG_LitVertices_800B7A50[84]; // 0x7E0 (2016) bytes
HOMING BSS   gHomingTargets_800B8230[HOMING_ARRAY_LENGTH];
StreamCtrlWork BSS  strctrl_800B82B0; // 0x40 (64) bytes
JimakuCtrlWork BSS  jimCtrlActor_800B82F0; // 0x104C (4172) bytes
array_800B933C_child BSS array_800B933C[array_800B933C_SIZE]; // 0x1C (28) bytes
int BSS             dword_800B9358; // 0x4 (4) bytes

gap                                     gap_800B935C[0x4]; // 4 bytes

unsigned char BSS   gPrimBackingBuffers_800B9360[2][8192]; // 0x4000 (16384) bytes
MenuWork BSS        gMenuWork_800BD360; // 0x220 (544) bytes
MATRIX BSS          gRadarScaleMatrix_800BD580; // 0x20 (32) bytes
PANEL_TEXTURE BSS   gMenuLeftItems_800BD5A0[MENU_ITEM_COUNT]; // 0x1A4 (420) bytes

gap                                     gap_800BD744[0x4]; // 4 bytes

array_800BD748_child BSS array_800BD748[9]; // 0xD8 (216) bytes

gap                                     gap_800BD820[0x8]; // 8 bytes

array_800BD748_child BSS array_800BD828[4]; // 0x60 (96) bytes
PANEL_TEXTURE BSS   gMenuRightItems_800BD888[MENU_WEAPON_COUNT]; // 0xDC (220) bytes

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

#ifndef VR_EXE
/* equip/jpegcam.obj */
int BSS             dword_800BDCC8; // 0x4 (4) bytes
int BSS             dword_800BDCCC; // 0x4 (4) bytes
int BSS             dword_800BDCD0; // 0x4 (4) bytes
gap                                     gap_800BDCD4[0x4]; // 4 bytes
TMat8x8B BSS        gJpegcamMatrix2_800BDCD8; // 0x40 (64) bytes
#endif

/* weapon/rfsight.obj */
DVECTOR BSS         dvector_800BDD18[3]; // 0xC (12) bytes

gap                                     gap_800BDD24[0x4]; // 4 bytes

/* bullet/tenage.obj */
int BSS             dword_800BDD28; // 0x4 (4) bytes

gap                                     gap_800BDD2C[0x4]; // 4 bytes

CONTROL *BSS        tenage_ctrls_800BDD30[16]; // 0x40 (64) bytes
int BSS             tenage_ctrls_count_800BDD70; // 0x4 (4) bytes

gap                                     gap_800BDD74[0x4]; // 4 bytes

/* bullet/bakudan.obj */
HITTABLE BSS        GM_C4Datas_800BDD78[C4_COUNT]; // 0x100 (256) bytes

/* bullet/jirai.obj */
HITTABLE BSS        GM_ClayDatas_800BDE78[8]; // 0x80 (128) bytes

/* bullet/rmissile.obj */
int BSS             dword_800BDEF8[2]; // 0x8 (8) bytes

/* ??? */
TARGET *BSS         target_800BDF00; // 0x4 (4) bytes

gap                                     gap_800BDF04[0x4]; // 4 bytes

/* okajima/claymore.obj */
MAP *BSS     claymore_MAP_800bdf08; // 0x4 (4) bytes

gap                                     gap_800BDF0C[0x4]; // 4 bytes

/* okajima/spark.obj */
short BSS           gSparkRandomTable_800BDF10[0x40]; // 0x80 (128) bytes

/* okajima/stngrnd.obj */
SVECTOR BSS         stru_800BDF90; // 0x8 (8) bytes

/* okajima/chafgrnd.obj */
int BSS             dword_800BDF98; // 0x4 (4) bytes
int BSS             dword_800BDF9C; // 0x4 (4) bytes
int BSS             okajima_CHAF_LIFE; // 0x4 (4) bytes

gap                                     gap_800BDFA4[0x4]; // 4 bytes

/* takabe/goggleir.obj */
int BSS             dword_800BDFA8; // 0x4 (4) bytes

gap                                     gap_800BDFAC[0x4]; // 4 bytes

/* takabe/palette.obj */
void BSS            (*pfn_800BDFB0)(); // 0x4 (4) bytes
unsigned short BSS (*pfn_800BDFB4)(unsigned short); // 0x4 (4) bytes

/* libfs/memfile.obj */
int BSS         dword_800BDFB8; // 0x4 (4) bytes
int BSS         dword_800BDFBC; // 0x4 (4) bytes
FS_MEMFILE *BSS dword_800BDFC0; // 0x4 (4) bytes
int BSS         dword_800BDFC4; // 0x4 (4) bytes

/* sound.lib */

char BSS sd_main_stack[2048]; // 0x800 (2048) bytes
char BSS sd_int_stack[2048]; // 0x800 (2048) bytes

gap gap_800BEFC8[0x4]; // 4 bytes

int BSS             dword_800BEFCC; // 0x4 (4) bytes

gap                                     gap_800BEFD0[0x4]; // 4 bytes

int BSS             sd_debug_mode; // 0x4 (4) bytes
int BSS             str_pause_wait;

gap                                     gap_800BEFDC[0x8]; // 12 bytes

char *BSS           str_data_ptr; // 0x4 (4) bytes
int BSS             str_mono_offset; // 0x4 (4) bytes
int BSS             mute_l_r_fg; // 0x4 (4) bytes
int BSS             str_mute_fg; // 0x4 (4) bytes
unsigned int BSS    str_int_ctr; // 0x4 (4) bytes
int BSS             song_end_last; // 0x4 (4) bytes
#ifdef VR_EXE
gap                                     vrgap1[0x4]; // 4 bytes
#endif
int BSS             dword_800BEFFC; // 0x4 (4) bytes
int BSS             sd_print_fg; // 0x4 (4) bytes
int BSS             se_tracks; // 0x4 (4) bytes
#ifdef VR_EXE
gap                                     vrgap2[0x4]; // 4 bytes
#endif
int BSS             sng_syukan_vol; // 0x4 (4) bytes
unsigned int BSS    blank_data_addr; // 0x4 (4) bytes
char* BSS           cdload_buf; // 0x4 (4) bytes
int BSS             se_fp; // 0x4 (4) bytes
int BSS             sd_sng_code_buf[16]; // 0x40 (64) bytes
char* BSS           str_header; // 0x4 (4) bytes
int BSS             sng_fadein_time; // 0x4 (4) bytes
int BSS             spu_bgm_start_ptr_l; // 0x4 (4) bytes
int BSS             eons; // 0x4 (4) bytes
SEPLAYTBL BSS       se_playing[8]; // 0x60 (96) bytes
int BSS             spu_bgm_start_ptr_r; // 0x4 (4) bytes
int BSS             str_fadein_time; // 0x4 (4) bytes
unsigned long BSS   mdata1; // 0x4 (4) bytes
unsigned long BSS   mdata2; // 0x4 (4) bytes
unsigned long BSS   mdata3; // 0x4 (4) bytes
unsigned long BSS   mdata4; // 0x4 (4) bytes
SEPLAYTBL BSS       se_request[8]; // 0x60 (96) bytes
unsigned int BSS    spu_load_offset; // 0x4 (4) bytes
int BSS             vox_rev_on; // 0x4 (4) bytes

gap                                     gap_800BF148[0xC]; // 12 bytes

int BSS             vox_on_vol; // 0x4 (4) bytes
int BSS             sng_status; // 0x4 (4) bytes
unsigned int BSS    str_volume; // 0x4 (4) bytes
int BSS             str_vox_on; // 0x4 (4) bytes
int BSS             str_play_offset; // 0x4 (4) bytes
int BSS             str_unload_size; // 0x4 (4) bytes
unsigned int BSS    str_status; // 0x4 (4) bytes
int BSS             str_read_status;

gap                                     gap_800BF174[0x0C]; // 16 bytes

int BSS             se_pan_800BF180[8]; // 0x20 (32) bytes
int BSS             stop_jouchuu_se; // 0x4 (4) bytes
int BSS             dword_800BF1A4; // 0x4 (4) bytes
int BSS             dword_800BF1A8; // 0x4 (4) bytes
int BSS             str_unplay_size; // 0x4 (4) bytes
unsigned long BSS   key_fg; // 0x4 (4) bytes

gap                                     gap_800BF1B4[0x4]; // 4 bytes

int BSS             se_pan[8]; // 0x20 (32) bytes
int BSS             sng_fp; // 0x4 (4) bytes
int BSS             str_mute_status; // 0x4 (4) bytes
WAVE_W* BSS         wave_header; // 0x4 (4) bytes

gap                                     gap_800BF1E4[0x4]; // 4 bytes

int BSS             bgm_idx; // 0x4 (4) bytes
unsigned long BSS   mtrack; // 0x4 (4) bytes
int BSS             se_vol[8]; // 0x20 (32) bytes
int BSS             eoffs; // 0x4 (4) bytes

gap                                     gap_800BF214[0x4]; // 4 bytes

SpuVoiceAttr BSS    sd_blank_attr; // 0x40 (64) bytes
int BSS             str_fp; // 0x4 (4) bytes
int BSS             sng_fout_fg; // 0x4 (4) bytes
unsigned long BSS   keyons; // 0x4 (4) bytes
int BSS             str_off_idx; // 0x4 (4) bytes
int BSS             str_mono_fg; // 0x4 (4) bytes
int BSS             str_fout_fg; // 0x4 (4) bytes
int BSS             dword_800BF270; // 0x4 (4) bytes
unsigned int BSS    wave_unload_size; // 0x4 (4) bytes
int BSS             str_mute_off_idx;
unsigned int BSS    dword_800BF27C; // 0x4 (4) bytes
int BSS             str_trans_offset; // 4 bytes
char* BSS           se_data; // 0x4 (4) bytes
int BSS             sd_code_read; // 0x4 (4) bytes
unsigned int BSS    se_load_code; // 0x4 (4) bytes
int BSS             sng_kaihi_fg; // 0x4 (4) bytes
int BSS             wave_data; // 0x4 (4) bytes
int BSS             sng_pause_fg; // 0x4 (4) bytes
unsigned long BSS   keyoffs; // 0x4 (4) bytes
int BSS             str_read_idx;

gap                                     gap_800BF2A4[0x4]; // 8 bytes

SOUND_W BSS         sound_w[21]; // 0x1164 (4452) bytes
int BSS             str_play_idx; // 0x4 (4) bytes
int BSS             dword_800C0410; // 0x4 (4) bytes
int BSS             str_next_idx; // 0x4 (4) bytes
int BSS             str_mute_ctr; // 0x4 (4) bytes
int BSS             sng_fadein_fg; // 0x4 (4) bytes
unsigned char *BSS  sng_data; // 0x4 (4) bytes

gap                                     gap_800C0424[0x4]; // 4 bytes

int BSS             sng_load_code; // 0x4 (4) bytes

gap                                     gap_800C042C[0x4]; // 4 bytes

int BSS             sng_fade_time[14]; // 0x38 (56) bytes
char BSS            sd_path[128]; // 0x80 (128) bytes
unsigned int BSS    song_end; // 0x4 (4) bytes
int BSS             str_fadein_fg; // 0x4 (4) bytes
int BSS             str_load_code; // 0x4 (4) bytes
int BSS             str_fade_time; // 0x4 (4) bytes
unsigned int BSS    sng_play_code; // 0x4 (4) bytes

gap                                     gap_800C04FC[0x4]; // 4 bytes

int BSS             dword_800C0500; // 0x4 (4) bytes
int BSS             str_freq; // 0x4 (4) bytes
char* BSS           wave_load_ptr; // 0x4 (4) bytes
int BSS             sound_mono_fg; // 0x4 (4) bytes
int BSS             sng_syukan_fg; // 0x4 (4) bytes
char* BSS           str_trans_buf; // 0x4 (4) bytes
int BSS             sng_fout_term; // 0x4 (4) bytes
int BSS             str_wave_size; // 0x4 (4) bytes
unsigned char *BSS  se_header; // 0x4 (4) bytes
unsigned long BSS   keyd; // 0x4 (4) bytes
unsigned int BSS    wave_load_code; // 0x4 (4) bytes
unsigned int BSS    spu_wave_start_ptr; // 0x4 (4) bytes
WAVE_W *BSS         voice_tbl; // 0x4 (4) bytes

gap                                     gap_800C0534[0x4]; // 4 bytes

int BSS             sng_fade_value[13]; // 0x34 (52) bytes
unsigned char BSS   wavs; // 0x2 (2) bytes - padded

gap                                     gap_800C0570[0x0]; // 0 bytes

unsigned char *BSS  mptr; // 0x4 (4) bytes
int BSS             se_rev_on; // 0x4 (4) bytes
unsigned long BSS   wave_save_code; // 0x4 (4) bytes
SOUND_W *BSS        sptr; // 0x4 (4) bytes
int BSS             dword_800C0580; // 0x4 (4) bytes
unsigned int BSS    str_fade_value; // 0x4 (4) bytes
char BSS            spu_malloc_rec[SPU_MALLOC_RECSIZ * (24 + 1)]; // 0xC8 (200) bytes
unsigned int BSS    wave_load_size; // 0x4 (4) bytes
int BSS             dword_800C0654; // 0x4 (4) bytes
SPU_TRACK_REG BSS   spu_tr_wk[23]; // 0x564 (1380) bytes

gap                                     gap_800C0BBC[0x4]; // 4 bytes

int BSS             sng_kaihi_time; // 0x4 (4) bytes

gap                                     gap_800C0BC4[0x4]; // 4 bytes

int BSS             sng_master_vol[13]; // 0x34 (52) bytes
volatile int BSS    sd_task_status; // 0x4 (4) bytes

/* mts.lib (mts_new.obj) */

MTS_ITASK *BSS      D_800C0C00; // 0x4 (4) bytes
MTS_ITASK *BSS      D_800C0C04; // 0x4 (4) bytes

gap                                     gap_800C0C08[0x8]; // 8 bytes

signed char BSS     mts_semaphore_waiters_800C0C10[MTS_MAX_SEMAPHORE]; // 0x20 (32) bytes
MTS_TASK BSS        mts_tasks_800C0C30[MTS_NR_TASK]; // 0x180 (384) bytes
int BSS             mts_active_task_800C0DB0; // 0x4 (4) bytes
int BSS             mts_ready_tasks_800C0DB4; // 0x4 (4) bytes

gap                                     gap_800C0DB8[0x8]; // 8 bytes

unsigned int BSS    mts_system_task_stack_800C0DC0[128]; // 0x200 (512) bytes
unsigned int BSS    mts_sio_task_stack_800C0FC0[256]; // 0x400 (1024) bytes
volatile int BSS    mts_active_task_idx_800C13C0; // 0x4 (4) bytes

gap                                     gap_800C13C4[0xC]; // 12 bytes

MTS_ITASK BSS       mts_intr_tasks_800C13D0[MTS_NR_INT_TASK]; // 0xA0 (160) bytes

/* mts.lib (mts_pad.obj) */

char BSS                    param_800C1470[2][6]; // 0xC (12) bytes

gap                                     gap_800C147C[0x4]; // 4 bytes

PAD_RECV_BUF BSS            padbuf_800C1480[2]; // 0x48 (72) bytes

gap                                     gap_800C14C8[0x8]; // 8 bytes

unsigned char BSS           sendbuf_800C14D0[2][8]; // 0x10 (16) bytes
MTS_PAD_IN BSS              pad_800C14E0[2]; // 0x10 (16) bytes
int BSS                     pad_state_800C14F0[2]; // 0x8 (8) bytes
