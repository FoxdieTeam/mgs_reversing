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

#include "mgstype.h" // for SECTION

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

char BSS sd_main_stack[2048];
char BSS sd_int_stack[2048];

gap gap_800BEFC8[0x4]; // 4 bytes

int BSS             dword_800BEFCC;

gap                                     gap_800BEFD0[0x4]; // 4 bytes

int BSS             sd_debug_mode;
int BSS             str_pause_wait;

gap                                     gap_800BEFDC[0x8]; // 12 bytes

char *BSS           str_data_ptr;
int BSS             str_mono_offset;
int BSS             mute_l_r_fg;
int BSS             str_mute_fg;
unsigned int BSS    str_int_ctr;
int BSS             song_end_last;
#ifdef VR_EXE
gap                                     vrgap1[0x4]; // 4 bytes
#endif
int BSS             se_stop_fg;
int BSS             sd_print_fg;
int BSS             se_tracks;
#ifdef VR_EXE
gap                                     vrgap2[0x4]; // 4 bytes
#endif
int BSS             sng_syukan_vol;
unsigned int BSS    blank_data_addr;
char* BSS           cdload_buf;
int BSS             se_fp;
int BSS             sd_sng_code_buf[16];
char* BSS           str_header;
int BSS             sng_fadein_time;
int BSS             spu_bgm_start_ptr_l;
int BSS             eons;
SEPLAYTBL BSS       se_playing[8];
int BSS             spu_bgm_start_ptr_r;
int BSS             str_fadein_time;
unsigned long BSS   mdata1;
unsigned long BSS   mdata2;
unsigned long BSS   mdata3;
unsigned long BSS   mdata4;
SEPLAYTBL BSS       se_request[8];
unsigned int BSS    spu_load_offset;
int BSS             vox_rev_on;

gap                                     gap_800BF148[0xC]; // 12 bytes

int BSS             vox_on_vol;
int BSS             sng_status;
unsigned int BSS    str_volume;
int BSS             str_vox_on;
int BSS             str_play_offset;
int BSS             str_unload_size;
unsigned int BSS    str_status;
int BSS             str_read_status;

gap                                     gap_800BF174[0x0C]; // 16 bytes

int BSS             se_pan_800BF180[8];
int BSS             stop_jouchuu_se;
int BSS             dword_800BF1A4;
int BSS             dword_800BF1A8;
int BSS             str_unplay_size;
unsigned long BSS   key_fg;

gap                                     gap_800BF1B4[0x4]; // 4 bytes

int BSS             se_pan[8];
int BSS             sng_fp;
int BSS             str_mute_status;
WAVE_W* BSS         wave_header;

gap                                     gap_800BF1E4[0x4]; // 4 bytes

int BSS             bgm_idx;
unsigned long BSS   mtrack;
int BSS             se_vol[8];
int BSS             eoffs;

gap                                     gap_800BF214[0x4]; // 4 bytes

SpuVoiceAttr BSS    sd_blank_attr;
int BSS             str_fp;
int BSS             sng_fout_fg;
unsigned long BSS   keyons;
int BSS             str_off_idx;
int BSS             str_mono_fg;
int BSS             str_fout_fg;
int BSS             dword_800BF270;
unsigned int BSS    wave_unload_size;
int BSS             str_mute_off_idx;
unsigned int BSS    dword_800BF27C;
int BSS             str_trans_offset;
char* BSS           se_data;
int BSS             sd_code_read;
unsigned int BSS    se_load_code;
int BSS             sng_kaihi_fg;
int BSS             wave_data;
int BSS             sng_pause_fg;
unsigned long BSS   keyoffs;
int BSS             str_read_idx;

gap                                     gap_800BF2A4[0x4]; // 8 bytes

SOUND_W BSS         sound_w[21];
int BSS             str_play_idx;
int BSS             dword_800C0410;
int BSS             str_next_idx;
int BSS             str_mute_ctr;
int BSS             sng_fadein_fg;
unsigned char *BSS  sng_data;

gap                                     gap_800C0424[0x4]; // 4 bytes

int BSS             sng_load_code;

gap                                     gap_800C042C[0x4]; // 4 bytes

int BSS             sng_fade_time[14];
char BSS            sd_path[128];
unsigned int BSS    song_end;
int BSS             str_fadein_fg;
int BSS             str_load_code;
int BSS             str_fade_time;
unsigned int BSS    sng_play_code;

gap                                     gap_800C04FC[0x4]; // 4 bytes

int BSS             dword_800C0500;
int BSS             str_freq;
char* BSS           wave_load_ptr;
int BSS             sound_mono_fg;
int BSS             sng_syukan_fg;
char* BSS           str_trans_buf;
int BSS             sng_fout_term;
int BSS             str_wave_size;
unsigned char *BSS  se_header;
unsigned long BSS   keyd;
unsigned int BSS    wave_load_code;
unsigned int BSS    spu_wave_start_ptr;
WAVE_W *BSS         voice_tbl;

gap                                     gap_800C0534[0x4]; // 4 bytes

int BSS             sng_fade_value[13];
unsigned char BSS   wavs;

gap                                     gap_800C0570[0x0]; // 0 bytes

unsigned char *BSS  mptr;
int BSS             se_rev_on;
unsigned long BSS   wave_save_code;
SOUND_W *BSS        sptr;
int BSS             dword_800C0580;
unsigned int BSS    str_fade_value;
char BSS            spu_malloc_rec[SPU_MALLOC_RECSIZ * (24 + 1)];
unsigned int BSS    wave_load_size;
int BSS             dword_800C0654;
SPU_TRACK_REG BSS   spu_tr_wk[23];

gap                                     gap_800C0BBC[0x4]; // 4 bytes

int BSS             sng_kaihi_time;

gap                                     gap_800C0BC4[0x4]; // 4 bytes

int BSS             sng_master_vol[13];
volatile int BSS    sd_task_status;

/* mts.lib (mts_new.obj) */

MTS_ITASK *BSS      D_800C0C00;
MTS_ITASK *BSS      D_800C0C04;

gap                                     gap_800C0C08[0x8]; // 8 bytes

signed char BSS     mts_semaphore_waiters_800C0C10[MTS_MAX_SEMAPHORE];
MTS_TASK BSS        mts_tasks_800C0C30[MTS_NR_TASK];
int BSS             mts_active_task_800C0DB0;
int BSS             mts_ready_tasks_800C0DB4;

gap                                     gap_800C0DB8[0x8]; // 8 bytes

unsigned int BSS    mts_system_task_stack_800C0DC0[128];
unsigned int BSS    mts_sio_task_stack_800C0FC0[256];
volatile int BSS    mts_active_task_idx_800C13C0;

gap                                     gap_800C13C4[0xC]; // 12 bytes

MTS_ITASK BSS       mts_intr_tasks_800C13D0[MTS_NR_INT_TASK];

/* mts.lib (mts_pad.obj) */

char BSS            param_800C1470[2][6];

gap                                     gap_800C147C[0x4]; // 4 bytes

PAD_RECV_BUF BSS    padbuf_800C1480[2];

gap                                     gap_800C14C8[0x8]; // 8 bytes

unsigned char BSS   sendbuf_800C14D0[2][8];
MTS_PAD_IN BSS      pad_800C14E0[2];
int BSS             pad_state_800C14F0[2];
