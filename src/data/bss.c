#include "bss.h"
#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/GM_Control.h"
#include "Game/game.h"
#include "chara/snake/sna_init.h"
#include "memcard/memcard.h"
#include "map/map.h"
#include "Game/jimctrl.h"
#include "mts/mts_new.h"
#include "Game/homing_target.h"
#include "Bullet/jirai.h"
#include "Kojo/demothrd.h"
#include "SD/sd.h"

#define BSS SECTION(".bss")
#define gap char BSS

// simply add a new var at any random place below the line then run bss.py and it will automatically put it in then
// correct place and re-adjust the gaps, sizes, and byte size comments. the only thing allowed below the line are 
// var declarations. put everything else in a header. all comments below the line will also be deleted.
// you must use "BSS" instead of SECTION, and for EVERY var.

// note: if any included headers has an extern to the same vars defined here, matches will fail. never put extern
// data in a header.

// --------------------------------------------------------------------------------------------------------------------

unsigned char BSS main_task_stack_800ABBF0[2048]; // 0x800 (2048) bytes
unsigned int BSS sdStack_800AC3F0[512]; // 0x800 (2048) bytes
int BSS gDiskNum_800ACBF0; // 0x4 (4) bytes
int BSS pad_800ACBF4; // 0x4 (4) bytes
struct Actor BSS gGVActor_800acbf8; // 0x20 (32) bytes
struct ActorList BSS gActorsList_800ACC18[ACTOR_LIST_COUNT]; // 0x264 (612) bytes

gap gap_800ACE7C[0x4]; // 4 bytes

TFileExtHandler BSS gFileExtHandlers_800ACE80[MAX_FILE_HANDLERS]; // 0x68 (104) bytes

gap gap_800ACEE8[0x8]; // 8 bytes

CacheSystems BSS GV_CacheSystem_800ACEF0; // 0x400 (1024) bytes
GV_Heap BSS MemorySystems_800AD2F0[3]; // 0x3030 (12336) bytes
GV_Messages BSS gMessageQueue_800B0320[2]; // 0x288 (648) bytes
int BSS dword_800B05A8[6]; // 0x18 (24) bytes
GV_PAD BSS GV_PadData_800B05C0[4]; // 0x40 (64) bytes
DISPENV BSS gDispEnv_800B0600; // 0x14 (20) bytes

gap gap_800B0614[0xC]; // 12 bytes

VECTOR BSS gUnknownVector_800B0620; // 0x10 (16) bytes
int BSS dword_800B0630[68]; // 0x110 (272) bytes
int BSS dword_800B0740[516]; // 0x810 (2064) bytes
int BSS dword_800B0F50[4]; // 0x10 (16) bytes
DG_OBJS *BSS dword_800B0F60[8]; // 0x20 (32) bytes
DG_OBJS *BSS dword_800B0F80[256]; // 0x400 (1024) bytes
DR_ENV BSS stru_800B1380[2]; // 0x80 (128) bytes
unsigned char BSS byte_800B1400[1024]; // 0x400 (1024) bytes
DG_CHNL BSS DG_Chanls_800B1800[3]; // 0x5C4 (1476) bytes

gap gap_800B1DC4[0x4]; // 4 bytes

unsigned short BSS gOldRootCnt_800B1DC8[32]; // 0x40 (64) bytes
DG_FixedLight BSS gFixedLights_800B1E08[8]; // 0x40 (64) bytes

gap gap_800B1E48[0x108]; // 264 bytes

DG_TEX BSS gTextureRecs_800B1F50[512]; // 0x1800 (6144) bytes
Actor BSS gDgdActor2_800B3750; // 0x20 (32) bytes
Actor BSS gDgdActor1_800B3770; // 0x20 (32) bytes
int BSS dword_800B3790; // 0x4 (4) bytes

gap gap_800B3794[0x4]; // 4 bytes

unsigned char BSS pcxBuffer_800B3798[128]; // 0x80 (128) bytes
u_long BSS image_data_800B3818[256]; // 0x400 (1024) bytes
GCL_FileData BSS gGCL_fileData_800B3C18; // 0xC (12) bytes

gap gap_800B3C24[0x4]; // 4 bytes

int BSS argstack_800B3C28[32]; // 0x80 (128) bytes
unsigned char *BSS commandlines_800B3CA8[8]; // 0x20 (32) bytes
GCL_Vars BSS gGcl_vars_800B3CC8; // 0x800 (2048) bytes
GameState_800B4D98 BSS gGcl_gameStateVars_800B44C8; // 0xC0 (192) bytes
GCL_Vars BSS gGcl_memVars_800b4588; // 0x800 (2048) bytes
char BSS gStageName_800B4D88[16]; // 0x10 (16) bytes
GameState_800B4D98 BSS gGameState_800B4D98; // 0xC0 (192) bytes
int BSS cd_bios_task_state_800B4E58; // 0x4 (4) bytes

gap gap_800B4E5C[0x18]; // 24 bytes

int BSS int_800B4E74; // 0x4 (4) bytes

gap gap_800B4E78[0x410]; // 1040 bytes

struct Loader_Record *BSS gLoaderRec_800B5288; // 0x4 (4) bytes
int BSS gLoaderStartTime_800B528C; // 0x4 (4) bytes
int BSS gOverlayBinSize_800B5290; // 0x4 (4) bytes
int BSS gSaveCache_800B5294; // 0x4 (4) bytes
int BSS fs_stream_ref_count_800B5298; // 0x4 (4) bytes

gap gap_800B529C[0x8]; // 8 bytes

void *BSS fs_stream_heap_800B52A4; // 0x4 (4) bytes
void *BSS fs_stream_heap_end_800B52A8; // 0x4 (4) bytes
int BSS fs_stream_heapSize_800B52AC; // 0x4 (4) bytes

gap gap_800B52B0[0x10]; // 16 bytes

unsigned int BSS fs_stream_task_state_800B52C0; // 0x4 (4) bytes

gap gap_800B52C4[0x4]; // 4 bytes

long BSS gHardware_end_io_800B52C8; // 0x4 (4) bytes
long BSS gHardware_end_write_800B52CC; // 0x4 (4) bytes
long BSS gHardware_timeout_800B52D0; // 0x4 (4) bytes
long BSS gHardware_new_device_800B52D4; // 0x4 (4) bytes
long BSS gSoftware_end_io_800B52D8; // 0x4 (4) bytes
long BSS gSoftware_end_write_800B52DC; // 0x4 (4) bytes
long BSS gSoftware_timeout_800B52E0; // 0x4 (4) bytes
long BSS gSoftware_new_device_800B52E4; // 0x4 (4) bytes
TMemCardFunc BSS gHwCard_do_op_800B52E8; // 0x4 (4) bytes
TMemCardFunc BSS gSwCard_do_op_800B52EC; // 0x4 (4) bytes
volatile TMemCardSetFunc BSS gSwCardLastOp_800B52F0; // 0x4 (4) bytes
volatile TMemCardSetFunc BSS gHwCardLastOp_800B52F4; // 0x4 (4) bytes
struct mem_card BSS gMemCards_800B52F8[2]; // 0x350 (848) bytes
volatile long BSS gMemCard_io_size_800B5648; // 0x4 (4) bytes

gap gap_800B564C[0x4]; // 4 bytes

GM_Control BSS gDefaultControl_800B5650; // 0x7C (124) bytes

gap gap_800B56CC[0x4]; // 4 bytes

GM_Control *BSS GM_WhereList_800B56D0[96]; // 0x180 (384) bytes
AreaHistory BSS gAreaHistory_800B5850; // 0x10 (16) bytes
char BSS exe_name_800B5860[32]; // 0x20 (32) bytes
Actor_GM_Daemon BSS GM_Daemon_800B5880; // 0x28 (40) bytes

gap gap_800B58A8[0x8]; // 8 bytes

DG_TEX BSS gMenuTextureRec_800B58B0; // 0xC (12) bytes

gap gap_800B58BC[0x24]; // 36 bytes

BindStruct BSS gBindsArray_800b58e0[128]; // 0xC00 (3072) bytes
GM_Target BSS gTargets_800B64E0[64]; // 0x1200 (4608) bytes

gap gap_800B76E0[0x38]; // 56 bytes

CAMERA BSS GM_CameraList_800B7718[8]; // 0xA0 (160) bytes
UnkCameraStruct BSS gUnkCameraStruct_800B77B8; // 0x30 (48) bytes
GM_Camera BSS GM_Camera_800B77E8; // 0x7C (124) bytes

gap gap_800B7864[0x2C]; // 44 bytes

DG_OBJS *BSS StageObjs_800B7890[32]; // 0x80 (128) bytes
map_record BSS gMapRecs_800B7910[16]; // 0x140 (320) bytes
unsigned char BSS byte_800B7A50[2016]; // 0x7E0 (2016) bytes
Homing_Target BSS gHomingTargets_800B8230[8]; // 0x80 (128) bytes

gap gap_800B82B0[0x30]; // 48 bytes

int BSS dword_800B82E0; // 0x4 (4) bytes

gap gap_800B82E4[0x4]; // 4 bytes

int BSS dword_800B82E8; // 0x4 (4) bytes

gap gap_800B82EC[0x4]; // 4 bytes

Actor_JimCtrl BSS jimCtrlActor_800B82F0; // 0x48 (72) bytes

gap gap_800B8338[0x1004]; // 4100 bytes

array_800B933C_child BSS array_800B933C[array_800B933C_SIZE]; // 0x20 (32) bytes

gap gap_800B935C[0x4]; // 4 bytes

unsigned char BSS gPrimBackingBuffers_800B9360[2][8192]; // 0x4000 (16384) bytes
Actor_MenuMan BSS gMenuMan_800BD360; // 0x224 (548) bytes

gap gap_800BD584[0x1C]; // 28 bytes

MenuMan_Inventory_14h_Unk BSS dword_800BD5A0; // 0x14 (20) bytes

gap gap_800BD5B4[0x2D4]; // 724 bytes

MenuMan_Inventory_14h_Unk BSS gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT]; // 0xDC (220) bytes

gap gap_800BD964[0x1D4]; // 468 bytes

RadioMemory BSS gRadioMemory_800BDB38[RADIO_MEMORY_COUNT]; // 0x140 (320) bytes
unsigned char BSS gBulNames_800BDC78[64]; // 0x40 (64) bytes

gap gap_800BDCB8[0x8]; // 8 bytes

short BSS word_800BDCC0; // 0x4 (4) bytes - padded

gap gap_800BDCC4[0x6C]; // 108 bytes

GM_Control *BSS tenage_ctrls_800BDD30[16]; // 0x40 (64) bytes
int BSS tenage_ctrls_count_800BDD70; // 0x4 (4) bytes

gap gap_800BDD74[0x4]; // 4 bytes

Jirai_unknown BSS stru_800BDD78[16]; // 0x100 (256) bytes
Jirai_unknown BSS stru_800BDE78[8]; // 0x80 (128) bytes

gap gap_800BDEF8[0x8]; // 8 bytes

int BSS dword_800BDF00; // 0x4 (4) bytes

gap gap_800BDF04[0xA4]; // 164 bytes

int BSS dword_800BDFA8; // 0x4 (4) bytes

gap gap_800BDFAC[0x4]; // 4 bytes

void BSS (*pfn_800BDFB0)(); // 0x4 (4) bytes
unsigned short BSS (*pfn_800BDFB4)(unsigned short); // 0x4 (4) bytes
int BSS dword_800BDFB8; // 0x4 (4) bytes
int BSS dword_800BDFBC; // 0x4 (4) bytes
int BSS dword_800BDFC0; // 0x4 (4) bytes
int BSS dword_800BDFC4; // 0x4 (4) bytes

gap gap_800BDFC8[0x800]; // 2048 bytes

unsigned int BSS byte_800BE7C8[512]; // 0x800 (2048) bytes
int BSS dword_800BEFC8; // 0x4 (4) bytes
int BSS dword_800BEFCC; // 0x4 (4) bytes

gap gap_800BEFD0[0x4]; // 4 bytes

int BSS sd_debug_800BEFD4; // 0x4 (4) bytes

gap gap_800BEFD8[0x18]; // 24 bytes

int BSS dword_800BEFF0; // 0x4 (4) bytes

gap gap_800BEFF4[0xC]; // 12 bytes

int BSS dword_800BF000; // 0x4 (4) bytes

gap gap_800BF004[0x14]; // 20 bytes

int BSS sd_sng_code_buf_800BF018[16]; // 0x40 (64) bytes

gap gap_800BF058[0x4]; // 4 bytes

int BSS sd_KaihiMode_800BF05C; // 0x4 (4) bytes

gap gap_800BF060[0x4]; // 4 bytes

int BSS dword_800BF064; // 0x4 (4) bytes
SEPLAYTBL BSS se_playing_800BF068[8]; // 0x60 (96) bytes

gap gap_800BF0C8[0x4]; // 4 bytes

int BSS bstr_fade_inProgress_800BF0CC; // 0x4 (4) bytes

gap gap_800BF0D0[0x4]; // 4 bytes

int BSS mdata2_800BF0D4; // 0x4 (4) bytes
int BSS mdata3_800BF0D8; // 0x4 (4) bytes
int BSS mdata4_800BF0DC; // 0x4 (4) bytes

gap gap_800BF0E0[0x64]; // 100 bytes

int BSS dword_800BF144; // 0x4 (4) bytes

gap gap_800BF148[0x10]; // 16 bytes

int BSS sng_status_800BF158; // 0x4 (4) bytes
int BSS gStreamVol_800BF15C; // 0x4 (4) bytes
int BSS dword_800BF160; // 0x4 (4) bytes

gap gap_800BF164[0x8]; // 8 bytes

int BSS gStr_FadeOut1_800BF16C; // 0x4 (4) bytes

gap gap_800BF170[0x30]; // 48 bytes

int BSS stop_jouchuu_se_800BF1A0; // 0x4 (4) bytes
int BSS dword_800BF1A4; // 0x4 (4) bytes
int BSS dword_800BF1A8; // 0x4 (4) bytes

gap gap_800BF1AC[0x2C]; // 44 bytes

int BSS dword_800BF1D8; // 0x4 (4) bytes

gap gap_800BF1DC[0xC]; // 12 bytes

int BSS bgm_idx_800BF1E8; // 0x4 (4) bytes
unsigned int BSS mtrack_800BF1EC; // 0x4 (4) bytes

gap gap_800BF1F0[0x20]; // 32 bytes

int BSS dword_800BF210; // 0x4 (4) bytes

gap gap_800BF214[0x44]; // 68 bytes

int BSS dword_800BF258; // 0x4 (4) bytes

gap gap_800BF25C[0x4]; // 4 bytes

int BSS keyons_800BF260; // 0x4 (4) bytes
int BSS dword_800BF264; // 0x4 (4) bytes
int BSS dword_800BF268; // 0x4 (4) bytes
int BSS dword_800BF26C; // 0x4 (4) bytes
int BSS dword_800BF270; // 0x4 (4) bytes

gap gap_800BF274[0x8]; // 8 bytes

int BSS dword_800BF27C; // 0x4 (4) bytes

gap gap_800BF280[0xC]; // 12 bytes

int BSS se_load_code_800BF28C; // 0x4 (4) bytes
int BSS sng_fade_in_2_800BF290; // 0x4 (4) bytes

gap gap_800BF294[0x8]; // 8 bytes

int BSS keyoffs_800BF29C; // 0x4 (4) bytes

gap gap_800BF2A0[0x8]; // 8 bytes

SOUND_W BSS sound_w_800BF2A8[21]; // 0x1164 (4452) bytes

gap gap_800C040C[0x4]; // 4 bytes

int BSS dword_800C0410; // 0x4 (4) bytes

gap gap_800C0414[0xC]; // 12 bytes

int BSS sd_sng_data_800C0420; // 0x4 (4) bytes

gap gap_800C0424[0x4]; // 4 bytes

int BSS dword_800C0428; // 0x4 (4) bytes

gap gap_800C042C[0x4]; // 4 bytes

int BSS sng_fade_time_800C0430[14]; // 0x38 (56) bytes
char BSS byte_800C0468[128]; // 0x80 (128) bytes
int BSS song_end_800C04E8; // 0x4 (4) bytes
int BSS dword_800C04EC; // 0x4 (4) bytes
int BSS gStream_800C04F0; // 0x4 (4) bytes
int BSS dword_800C04F4; // 0x4 (4) bytes
unsigned int BSS sng_status_800C04F8; // 0x4 (4) bytes

gap gap_800C04FC[0x10]; // 16 bytes

int BSS dword_800C050C; // 0x4 (4) bytes

gap gap_800C0510[0x8]; // 8 bytes

int BSS sng_fout_term_800C0518; // 0x4 (4) bytes

gap gap_800C051C[0x4]; // 4 bytes

int BSS se_exp_table_800C0520; // 0x4 (4) bytes
int BSS keyd_800C0524; // 0x4 (4) bytes
int BSS wave_load_code_800C0528; // 0x4 (4) bytes
int BSS spu_wave_start_ptr_800C052C; // 0x4 (4) bytes
WAVE_W* BSS voice_tbl_800C0530; // 0x4 (4) bytes

gap gap_800C0534[0x3C]; // 60 bytes

unsigned char* BSS mptr_800C0570; // 0x4 (4) bytes
int BSS se_rev_on_800C0574; // 0x4 (4) bytes
int BSS wave_save_code_800C0578; // 0x4 (4) bytes
SOUND_W* BSS sptr_800C057C; // 0x4 (4) bytes
int BSS dword_800C0580; // 0x4 (4) bytes
int BSS gStr_fadeout_2_800C0584; // 0x4 (4) bytes

gap gap_800C0588[0xD0]; // 208 bytes

SPU_TRACK_REG BSS spu_tr_wk_800C0658[23]; // 0x564 (1380) bytes

gap gap_800C0BBC[0x4]; // 4 bytes

int BSS sng_fade_in_2_800C0BC0; // 0x4 (4) bytes

gap gap_800C0BC4[0x38]; // 56 bytes

volatile int BSS sd_flags_800C0BFC; // 0x4 (4) bytes
mts_msg *BSS D_800C0C00; // 0x4 (4) bytes
mts_msg *BSS D_800C0C04; // 0x4 (4) bytes

gap gap_800C0C08[0x8]; // 8 bytes

signed char BSS byte_800C0C10[32]; // 0x20 (32) bytes
mts_task BSS gTasks_800C0C30[12]; // 0x180 (384) bytes
int BSS gTaskIdx_800C0DB0; // 0x4 (4) bytes
int BSS gMts_bits_800C0DB4; // 0x4 (4) bytes
unsigned char BSS byte_800C0DB8[512]; // 0x200 (512) bytes
unsigned char BSS dword_800C0FB8[1024]; // 0x400 (1024) bytes

gap gap_800C13B8[0x8]; // 8 bytes

int BSS gMts_active_task_idx_800C13C0; // 0x4 (4) bytes

gap gap_800C13C4[0xC]; // 12 bytes

mts_msg BSS gMtsMsgs_800C13D0[8]; // 0xA0 (160) bytes

gap gap_800C1470[0x10]; // 16 bytes

unsigned char BSS gMtsPadRecvBuffers_800C1480[2][36]; // 0x48 (72) bytes

gap gap_800C14C8[0x8]; // 8 bytes

unsigned char BSS gMtsPadSendBuffers_800C14D0[2][8]; // 0x10 (16) bytes

gap gap_800C14E0[0x10]; // 16 bytes

int BSS gMtsPadInitStates_800C14F0[2]; // 0x8 (8) bytes
