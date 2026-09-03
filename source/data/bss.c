#define __BSSDEFINE__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libspu.h> // for SpuVoiceAttr

#include "mts/mts_new.h"
#include "mts/mts_pad.h"
#include "mts/terminal.h"
#include "sound/sd_cli.h"
#include "sound/sd_incl.h"

#include "common.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "memcard/memcard.h"

#include "game/game.h"
#include "game/jimctrl.h"
#include "chara/snake/sna_init.h"
#include "equip/equip.h"
#include "bullet/bakudan.h"

#define BSS SECTION(".bss")
#define gap char BSS

// WARNING:
// If any headers included by this file have externs to variables defined here,
// the build won't match!! DO NOT declare any BSS variables in a header without
// wrapping them with #if !defined(__BSSDEFINE__).
//
// The __BSSDEFINE__ flag needs to be defined here and nowhere else.
// This lets us properly declare BSS variables for the rest of the codebase.

// ----------------------------------------------------------------------------

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
int BSS             se_stop_fg; // 0x4 (4) bytes
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
