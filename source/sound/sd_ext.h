#ifndef __SD_EXT_H__
#define __SD_EXT_H__

#include <libspu.h>     // for SpuVoiceAttr
#include "sd_incl.h"

/* in sd_wk.c */
extern unsigned long spu_ch_tbl[24+1];
extern unsigned char blank_data[512];
extern unsigned char dummy_data[4096];

/*----------------------------------------------------------------------*/
#ifndef __BSSDEFINE__

/* in sd_main.c */
extern int              dword_800BEFCC;         // ???_fg
extern int              sd_debug_mode;
extern int              str_pause_wait;

/* in sd_str.c */
extern char             *str_data_ptr;          // static?
extern int              str_mono_offset;
extern int              mute_l_r_fg;
extern int              str_mute_fg;
extern unsigned int     str_int_ctr;
extern int              song_end_last;          // static?

/* in sd_cli.c */
extern int              se_stop_fg;
extern int              sd_print_fg;            // static?
extern int              se_tracks;

/* in sd_wk.c */
extern int              sng_syukan_vol;         // long
extern unsigned int     blank_data_addr;        // unsigned long
extern char             *cdload_buf;            // unsigned char *
extern int              se_fp;
extern int              sd_sng_code_buf[16];
extern char             *str_header;
extern int              sng_fadein_time;        // long
extern int              spu_bgm_start_ptr_l;
extern int              rev_on_bit;             // unsigned long
extern struct SEPLAYTBL se_playing[SE_TRACK_NUM];
extern int              spu_bgm_start_ptr_r;
extern int              str_fadein_time;
extern unsigned long    mdata1;
extern unsigned long    mdata2;
extern unsigned long    mdata3;
extern unsigned long    mdata4;
extern struct SEPLAYTBL se_request[SE_TRACK_NUM];
extern unsigned int     spu_load_offset;        // unsigned long
extern int              vox_rev_on;
extern int              vox_on_vol;
extern int              sng_status;
extern unsigned int     str_volume;
extern int              str_vox_on;
extern int              str_play_offset;
extern int              str_unload_size;
extern unsigned int     str_status;
extern int              str_read_status;
extern int              se_pan_800BF180[SE_TRACK_NUM]; // ???
extern int              stop_jouchuu_se;
extern int              dword_800BF1A4;
extern int              spu_irq_counter;        // long
extern int              str_unplay_size;
extern unsigned long    key_fg;
extern int              se_pan[SE_TRACK_NUM];
extern int              sng_fp;
extern int              str_mute_status;
extern unsigned char    *wave_header;
extern int              bgm_idx;
extern unsigned long    mtrack;
extern int              se_vol[SE_TRACK_NUM];
extern int              rev_off_bit;            // unsigned long
extern SpuVoiceAttr     s_attr;
extern int              str_fp;
extern int              sng_fout_fg;
extern unsigned long    keyons;
extern int              str_off_idx;
extern int              str_mono_fg;
extern int              str_fout_fg;
extern int              irq_addr;               // unsigned long
extern unsigned int     wave_unload_size;       // unsigned long
extern int              str_mute_off_idx;
extern unsigned int     wave_load_status;       // unsigned long
extern int              str_trans_offset;
extern char             *se_data;               // unsigned char *
extern int              sd_code_read;
extern unsigned int     se_load_code;           // unsigned long
extern int              sng_kaihi_fg;
extern int              wave_data;
extern int              sng_pause_fg;
extern unsigned long    keyoffs;
extern int              str_read_idx;
extern struct SOUND_W   sound_w[INTERNAL_TRACK_NUM];
extern int              str_play_idx;
extern int              se_save_code2;          // unsigned long
extern int              str_next_idx;
extern int              str_mute_ctr;
extern int              sng_fadein_fg;          // long
extern unsigned char    *sng_data;
extern int              sng_load_code;          // unsigned long
extern int              sng_fade_time[SNG_TRACK_NUM+1]; // long[SNG_TRACK_NUM]
extern char             pcm_path[128];
extern unsigned int     song_end;               // unsigned long
extern int              str_fadein_fg;
extern int              str_load_code;
extern int              str_fade_time;
extern unsigned int     sng_play_code;          // unsigned long
extern int              reply_fg;               /* guessed name */
extern int              str_freq;
extern char             *wave_load_ptr;         // unsigned char *
extern int              sound_mono_fg;
extern int              sng_syukan_fg;
extern char             *str_trans_buf;
extern int              sng_fout_term;
extern int              str_wave_size;
extern struct SETBL     *se_header;
extern unsigned long    keyd;
extern unsigned int     wave_load_code;         // unsigned long
extern unsigned int     spu_wave_start_ptr;     // unsigned long
extern struct WAVE_W    *voice_tbl;
extern int              sng_fade_value[SNG_TRACK_NUM]; // long
extern unsigned char    wavs;
extern unsigned char    *mptr;
extern int              se_rev_on;
extern unsigned long    wave_save_code;         // unsigned long
extern struct SOUND_W   *sptr;
extern int              dword_800C0580;
extern unsigned int     str_fade_value;
extern char             spu_malloc_rec[SPU_MALLOC_RECSIZ * (24 + 1)];
extern unsigned int     wave_load_size;         // unsigned long
extern int              dword_800C0654;
extern struct SPU_TRACK_REG spu_tr_wk[USE_TRACK_NUM];
extern int              sng_tempo_move;
extern int              sng_master_vol[SNG_TRACK_NUM];
extern volatile int     sd_task_status;

#endif // __BSSDEFINE__
/*----------------------------------------------------------------------*/
#endif // __SD_EXT_H__
