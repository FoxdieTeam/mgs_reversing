#ifndef _SD_EXT_H_
#define _SD_EXT_H_

// Do not #include this file externally! Use sd_cli.h instead.

#include <libspu.h>
#include "sd_incl.h"

#define CDLOAD_BUF_SIZE    (2048 * 48)
#define SD_MAIN_STACK_SIZE (2048)
#define SD_INT_STACK_SIZE  (2048)

/* sd_main.c */
void sound_main(int argc, const char *argv[]);
void sub_80081A10(int *arg0, int arg1, int arg2);
void SdMain(void);
void SdInt(void);
void sd_init(void);
void SdTerm(void);
void keyOff(unsigned int ch);
void KeyOffStr(void);
void sub_800820EC(void);
void keyOn(unsigned int ch);
int sd_mem_alloc(void);

/* sd_str.c */
extern int dword_8009F7B4;
extern char *dword_8009F7B8;

void StrFadeIn(unsigned int fade_speed);
int StrFadeOut(unsigned int fade_speed);
int StrFadeOutStop(unsigned int fade_speed);
int StartStream(void);
void UserSpuIRQProc(void);
void sub_8008279C(void);
void sub_800827A4(void);
int StrSpuTransWithNoLoop(void);
void StrSpuTransClose(void);
void StrSpuTrans(void);

/* sd_file.c */
int LoadSeFile(void);
int LoadWaveHeader(void);
void WaveCdLoad(void);
void WaveSpuTrans(void);
int PcmOpen(int code, int path_idx);
int PcmRead(int fd, unsigned char *buf, int size);
int PcmClose(int fd, int path_idx);
void StrFadeWkSet(void);
int StrFadeInt(void);
void code2name(unsigned int code, char *name);
char num2char(unsigned int num);
unsigned char *SD_SngDataLoadInit(unsigned short id);
void SD_80083ED4(void);
unsigned char *SD_SeDataLoadInit(unsigned short id);
void SD_80083EF8(void);
char *SD_WavDataLoadInit(unsigned short id);
int SD_80083F54(char *end);
char *SD_WavLoadBuf(char *arg0);
void SD_WavUnload(void);

/* sd_drv.c */
void IntSdMain(void);
void SngFadeIn(unsigned int mode);
int SngFadeOutP(unsigned int code);
int SngFadeOutS(unsigned int code);
int SngKaihiP(void);
void SngFadeWkSet(void);
void SngFadeInt(void);
void SngTempoInt(void);
int LoadSngData(void);
void init_sng_work(void);
void sng_adrs_set(int idx);
void se_adrs_set(int idx);
void sng_track_init(SOUND_W *ptr);

/* sd_sub1.c */
extern void (*cntl_tbl[128])(void);
extern unsigned char rdm_tbl[129]; /* char[] */
extern unsigned char VIBX_TBL[32];

int sound_sub(void);
int tx_read(void);
void note_set(void);
void adsr_reset(void);
void note_compute(void);
void vol_compute(void);
void pan_generate(void);
void key_cut_off(void);
void keych(void);
int vib_generate(int cnt);
void bendch(void);
void note_cntl(void);
unsigned int random(void);
void tempo_ch(void);
void volxset(unsigned char depth);

/* sd_sub2.c */
void rest_set(void);
void tie_set(void);
void sno_set(void);
void svl_set(void);
void svp_set(void);
void use_set(void);
void pan_set(void);
void pan_move(void);
void vib_set(void);
void vib_change(void);
void rdm_set(void);
void lp1_start(void);
void lp1_end(void);
void lp2_start(void);
void lp2_end(void);
void l3s_set(void);
void l3e_set(void);
void tempo_set(void);
void tempo_move(void);
void trans_set(void);
void tre_set(void);
void vol_chg(void);
void vol_move(void);
void por_set(void);
void sws_set(void);
void detune_set(void);
void swp_set(void);
void echo_set1(void);
void echo_set2(void);
void eon_set(void);
void eof_set(void);
void kakko_start(void);
void kakko_end(void);
void env_set(void);
void ads_set(void);
void srs_set(void);
void rrs_set(void);
void pm_set(void);
void jump_set(void);
void block_end(void);
void no_cmd(void);

/* sd_ioset.c */
extern unsigned int freq_tbl[108];

void spuwr(void);
void sound_off(void);
void sng_off(void);
void se_off(int i);
void sng_pause(void);
void sng_pause_off(void);
void keyon(void);
void keyoff(void);
void tone_set(unsigned char n);
void pan_set2(unsigned char x);
void vol_set(unsigned int vol_data);
void freq_set(unsigned int note_tune);
void drum_set(unsigned char n);

/* sd_cli.c */
int sd_task_active(void);
int sd_str_play(void);
int sd_sng_play(void);
int sd_se_play(void);
int sd_se_play2(void);
int sd_set_cli(int sound_code, int sync_mode);
void sd_set_path(const char *str);
int get_sng_code(void);
unsigned char *get_sd_buf(int size);
void start_xa_sd(void);
void stop_xa_sd(void);
int SePlay(int sound_code);
int get_str_counter(void);
void sd_set(int sound_code);

/* in se_tbl.c */
extern SETBL se_tbl[128];

/* in sd_wk.c */
extern unsigned long spu_ch_tbl[24+1];
extern unsigned char blank_data[512];
extern unsigned char dummy_data[4096];

/*---------------------------------------------------------------------------*/
#ifndef __BSSDEFINE__

extern  int             dword_800BEFCC;

extern  int             sd_debug_mode_800BEFD4;
extern  int             str_pause_wait;

extern  char           *stream_data_ptr_800BEFE4;
extern  int             str_mono_offset_800BEFE8;
extern  int             mute_l_r_fg;
extern  int             str_mute_fg_800BEFF0;
extern  unsigned int    str_int_ctr_800BEFF4;
extern  int             dword_800BEFF8;

extern  int             dword_800BEFFC;
extern  int             sd_print_fg;
extern  int             se_tracks_800BF004;

extern  int             dword_800BF008;
extern  unsigned int    blank_data_addr_800BF00C; /* unsigned long */
extern  char           *cdload_buf_800BF010; /* unsigned char * */
extern  int             se_fp_800BF014;
extern  int             sd_sng_code_buf_800BF018[16];
extern  char           *str_header_800BF058;
extern  int             sng_fadein_time_800BF05C;
extern  int             spu_bgm_start_ptr_l_800BF060;
extern  int             dword_800BF064;
extern  SEPLAYTBL       se_playing_800BF068[8];
extern  int             spu_bgm_start_ptr_r_800BF0C8;
extern  int             str_fadein_time_800BF0CC;
extern  unsigned long   mdata1_800BF0D0;
extern  unsigned long   mdata2_800BF0D4;
extern  unsigned long   mdata3_800BF0D8;
extern  unsigned long   mdata4_800BF0DC;
extern  SEPLAYTBL       se_request_800BF0E0[8];
extern  unsigned int    spu_load_offset_800BF140; /* unsigned long */
extern  int             vox_rev_on_800BF144;

extern  int             dword_800BF154;
extern  int             sng_status_800BF158;
extern  unsigned int    str_volume_800BF15C;
extern  int             str_vox_on_800BF160;
extern  int             str_play_offset_800BF164;
extern  int             str_unload_size_800BF168;
extern  unsigned int    str_status_800BF16C;
extern  int             str_read_status;

extern  int             se_pan_800BF180[8];
extern  int             stop_jouchuu_se_800BF1A0;
extern  int             dword_800BF1A4;
extern  int             dword_800BF1A8;
extern  int             str_unplay_size_800BF1AC;
extern  unsigned long   key_fg_800BF1B0;

extern  int             se_pan_800BF1B8[8];
extern  int             sng_fp_800BF1D8;
extern  int             str_mute_status_800BF1DC;
extern  WAVE_W         *wave_header_800BF1E0; /* unsigned char* */

extern  int             bgm_idx_800BF1E8;
extern  unsigned long   mtrack_800BF1EC;
extern  int             se_vol_800BF1F0[8];
extern  int             dword_800BF210;

extern  SpuVoiceAttr    s_attr_800BF218;
extern  int             str_fp_800BF258;
extern  int             sng_fout_fg_800BF25C;
extern  unsigned long   keyons_800BF260;
extern  int             str_off_idx_800BF264;
extern  int             str_mono_fg_800BF268;
extern  int             str_fout_fg_800BF26C;
extern  int             dword_800BF270;
extern  unsigned int    wave_unload_size_800BF274; /* unsigned long */
extern  int             str_mute_off_idx;
extern  unsigned int    dword_800BF27C;
extern  int             str_trans_offset;
extern  char           *se_header_800BF284; /* struct SETBL* */
extern  int             sd_code_read_800BF288;
extern  unsigned int    se_load_code_800BF28C; /* unsigned long */
extern  int             sng_kaihi_fg_800BF290;
extern  int             wave_data_800BF294;
extern  int             sng_pause_fg_800BF298;
extern  unsigned long   keyoffs_800BF29C;
extern  int             str_read_idx;

extern  SOUND_W         sound_w_800BF2A8[21];
extern  int             str_play_idx_800C040C;
extern  int             dword_800C0410;
extern  int             str_next_idx_800C0414;
extern  int             str_mute_ctr_800C0418;
extern  int             sng_fadein_fg_800C041C;
extern  unsigned char  *sng_data_800C0420;

extern  int             sng_load_code_800C0428;

extern  int             sng_fade_time_800C0430[14];
extern  char            byte_800C0468[128];
extern  unsigned int    song_end_800C04E8; /* unsigned long */
extern  int             str_fadein_fg_800C04EC;
extern  int             str_load_code_800C04F0;
extern  int             str_fade_time_800C04F4;
extern  unsigned int    sng_play_code_800C04F8;

extern  int             dword_800C0500;
extern  int             str_freq_800C0504;
extern  char           *wave_load_ptr_800C0508; /* unsigned char* */
extern  int             sound_mono_fg_800C050C;
extern  int             sng_syukan_fg_800C0510;
extern  char           *str_trans_buf_800C0514;
extern  int             sng_fout_term_800C0518;
extern  int             str_wave_size_800C051C;
// extern  unsigned char  *se_exp_table_800C0520;
// extern  SETBL          *se_exp_table_800C0520;
extern  unsigned long   keyd_800C0524;
extern  unsigned int    wave_load_code_800C0528; /* unsigned long */
extern  unsigned int    spu_wave_start_ptr_800C052C; /* unsigned long */
extern  WAVE_W         *voice_tbl_800C0530;

extern  int             sng_fade_value_800C0538[13];
extern  unsigned char   wavs_800C056C;

extern  unsigned char  *mptr_800C0570;
extern  int             se_rev_on_800C0574;
extern  unsigned long   wave_save_code_800C0578;
extern  SOUND_W        *sptr_800C057C;
extern  int             dword_800C0580;
extern  unsigned int    str_fade_value_800C0584;
extern  char            spu_malloc_rec_800C0588[200];
extern  unsigned int    wave_load_size_800C0650; /* unsigned long */
extern  int             dword_800C0654;
extern  SPU_TRACK_REG   spu_tr_wk_800C0658[23];

extern  int             sng_fade_in_2_800C0BC0;

extern  int             sng_master_vol_800C0BC8[13];
extern  volatile int    sd_task_status_800C0BFC;


#endif // __BSSDEFINE__
#endif // _SD_EXT_H_
