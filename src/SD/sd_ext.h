#ifndef _SD_EXT_H_
#define _SD_EXT_H_

#include <libspu.h>
#include "sd_incl.h"

/*---------------------------------------------------------------------------*/
// do not #include this file externally! use sound.h instead.

/* sd_main.c */
void sound_main_80081910(int argc, const char *argv[]);
void nullsub_7_80081A10(int *arg0, int arg1, int arg2);
void SdMain_80081A18(void);
void SdInt_80081BDC(void);
void sd_init_80081C7C(void);
void SdTerm_80081F8C(void);
void keyOff_80081FC4(unsigned int ch);
void KeyOffStr_80081FE8(void);
void sub_800820EC(void);
void keyOn_80082170(unsigned int ch);
int sd_mem_alloc_80082194(void);

/* sd_str.c */
extern int dword_8009F7B4;
extern char *dword_8009F7B8;

void StrFadeIn_800822C8(unsigned int arg0);
int StrFadeOut_80082310(unsigned int arg0);
int StrFadeOutStop_80082380(unsigned int fadeSpeed);
int StartStream_80082448(void);
void UserSpuIRQProc_80082640(void);
void sub_8008279C(void);
void SD_nullsub_20_800827A4(void);
int StrSpuTransWithNoLoop_800827AC(void);
void StrSpuTransClose_80083394(void);
void StrSpuTrans_800833FC(void);

/* sd_file.c */
int SD_LoadSeFile_8008341C(void);
int SD_LoadWaveFile_800834FC(void);
void WaveCdLoad_80083804(void);
void WaveSpuTrans_80083944(void);
int SD_SongLoadData_8008394C(int a1, int a2);
int SD_80083954(int a1, unsigned char *a2, int a3);
int SD_8008395C(int a1, int a2);
void StrFadeWkSet_80083964(void);
int StrFadeInt_800839C8(void);
void code2name_80083BB4(unsigned int code, char *name);
char num2char_80083E68(unsigned int num);
unsigned char *SD_SngDataLoadInit_80083E8C(unsigned short unused);
void SD_80083ED4(void);
unsigned char *SD_80083EE8(unsigned short unused);
void SD_80083EF8(void);
char *LoadInit_80083F08(unsigned short unused);
int SD_80083F54(char *end);
char *SD_WavLoadBuf_800841D4(char *arg0);
void SD_Unload_800843BC(void);

/* sd_drv.c */
void IntSdMain_80084494(void);
void SD_SongFadeIn_80084CCC(unsigned int mode);
int SngFadeOutP_80084D60(unsigned int code);
int SD_SongFadeoutAndStop_80084E48(unsigned int code);
int SD_SongKaihiMode_80084F88(void);
void SngFadeWkSet_80085020(void);
void SD_80085164(void);
void SD_80085480(void);
int SD_800854F0(void);
void init_sng_work_8008559C(void);
void sng_adrs_set_80085658(int idx);
void se_adrs_set_8008576C(int idx);
void sng_track_init_800859B8(SOUND_W *ptr);

/* sd_sub1.c */
extern void (*cntl_tbl_8009F7BC[128])(void);
extern unsigned char rdm_tbl_8009F9BC[129]; /* char[] */
extern unsigned char VIBX_TBL_8009FA40[32];

int sound_sub_80085A50(void);
int tx_read_80085B84(void);
void note_set_80085CD8(void);
void adsr_reset_80085D98(void);
void note_compute_80085DE0(void);
void vol_compute_8008604C(void);
void pan_generate_80086198(void);
void key_cut_off_80086220(void);
void keych_80086280(void);
int vib_generate_80086694(int cnt);
void bendch_80086734(void);
void note_cntl_8008686C(void);
unsigned int random_80086B84(void);
void tempo_ch_80086C08(void);
void volxset_80086C98(unsigned char depth);

/* sd_sub2.c */
void rest_set_80086D18(void);
void tie_set_80086D9C(void);
void sno_set_80086E38(void);
void svl_set_80086E78(void);
void svp_set_80086EB8(void);
void use_set_80086EF8(void);
void pan_set_80086F00(void);
void pan_move_80086F50(void);
void vib_set_80087018(void);
void vib_change_80087120(void);
void rdm_set_8008716C(void);
void lp1_start_800871B4(void);
void lp1_end_800871E0(void);
void lp2_start_800872C0(void);
void lp2_end_800872EC(void);
void l3s_set_8008736C(void);
void l3e_set_80087384(void);
void tempo_set_800873CC(void);
void tempo_move_800873E4(void);
void trans_set_8008750C(void);
void tre_set_80087524(void);
void vol_chg_8008756C(void);
void vol_move_8008758C(void);
void por_set_80087670(void);
void sws_set_800876D4(void);
void detune_set_80087730(void);
void swp_set_8008774C(void);
void echo_set1_80087754(void);
void echo_set2_8008775C(void);
void eon_set_80087764(void);
void eof_set_800877CC(void);
void kakko_start_80087834(void);
void kakko_end_80087854(void);
void env_set_800878FC(void);
void ads_set_80087904(void);
void srs_set_8008798C(void);
void rrs_set_800879E4(void);
void pm_set_80087A48(void);
void jump_set_80087A50(void);
void block_end_80087A58(void);
void no_cmd_80087A80(void);

/* sd_ioset.c */
extern unsigned int freq_tbl_8009FC08[108];

void spuwr_80087A88(void);
void sound_off_80087DAC(void);
void sng_off_80087E2C(void);
void se_off_80087E94(int i);
void sng_pause_80087EF4(void);
void sng_pause_off_80087F24(void);
void keyon_80087F58(void);
void keyoff_80087F80(void);
void tone_set_80087FA8(unsigned char n);
void pan_set2_800882E4(unsigned char x);
void vol_set_80088320(unsigned int vol_data);
void freq_set_800885D4(unsigned int note_tune);
void drum_set_80088694(unsigned char n);

/* sd_cli.c */
int sd_task_active_800886C4(void);
int sd_str_play_800886DC(void);
int SD_800886F4(void);
int sub_8008870C(void);
int sub_8008877C(void);
int sd_set_cli_800887EC(int sound_code, int sync_mode);
void sd_set_path_8008880C(const char *str);
unsigned int sub_80088838(void);
void sub_80088860(void);
void start_xa_sd_80088868(void);
void stop_xa_sd_800888B4(void);
int SePlay_800888F8(int sound_code);
int get_str_counter_80088CA0(void);
void sd_set_80088CB0(int sound_code);

/* in se_tbl.c */
extern SETBL se_tbl_800A22C4[128];

/* in sd_wk.c */
extern unsigned long spu_ch_tbl_800A2AC8[24+1];
extern unsigned char blank_data_800A2B28[512];
extern unsigned char dummy_data_800A2D28[4096];

/*---------------------------------------------------------------------------*/
#ifndef __BSSDEFINE__

extern  unsigned long   sd_main_stack_800BE7C8[512];
extern  unsigned long   sd_int_stack_800BEFC8;
extern  int             dword_800BEFCC;

extern  int             sd_debug_800BEFD4;
extern  int             str_pause_wait;

extern  char           *stream_data_ptr_800BEFE4;
extern  int             str_mono_offset_800BEFE8;
extern  int             dword_800BEFEC;
extern  int             str_mute_fg_800BEFF0;
extern  unsigned int    str_int_ctr_800BEFF4;
extern  int             dword_800BEFF8;

extern  int             dword_800BEFFC;
extern  int             dword_800BF000;
extern  int             se_tracks_800BF004;

extern  int             dword_800BF008;
extern  unsigned long   blank_data_addr_800BF00C;
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
extern  unsigned long   spu_load_offset_800BF140;
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
extern  unsigned long   wave_unload_size_800BF274;
extern  int             str_mute_off_idx;
extern  unsigned int    dword_800BF27C;
extern  int             str_trans_offset;
extern  char           *se_header_800BF284; /* struct SETBL* */
extern  int             sd_code_read_800BF288;
extern  unsigned long   se_load_code_800BF28C;
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
extern  unsigned long   song_end_800C04E8;
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
extern  unsigned long   wave_load_code_800C0528;
extern  unsigned long   spu_wave_start_ptr_800C052C;
extern  WAVE_W         *voice_tbl_800C0530;

extern  int             sng_fade_value_800C0538[13];
extern  unsigned char   byte_800C056C;

extern  unsigned char  *mptr_800C0570;
extern  int             se_rev_on_800C0574;
extern  unsigned long   wave_save_code_800C0578;
extern  SOUND_W        *sptr_800C057C;
extern  int             dword_800C0580;
extern  unsigned int    str_fade_value_800C0584;
extern  char            spu_malloc_rec_800C0588[200];
extern  int             dword_800C0650;
extern  int             dword_800C0654;
extern  SPU_TRACK_REG   spu_tr_wk_800C0658[23];

extern  int             sng_fade_in_2_800C0BC0;

extern  int             sng_master_vol_800C0BC8[13];
extern  volatile int    sd_task_status_800C0BFC;


#endif // __BSSDEFINE__
#endif // _SD_EXT_H_
