/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/sd_cli.h (Nov.09,1999)
 */
/* clang-format off */
#ifndef __SD_CLI_H__
#define __SD_CLI_H__

/*===================================================================
 *  Title           : "METALGEAR SOLID" SOUND
 *                  : - Include File 4 Client Task -
 *  version         : 1.00
 *
 *  Code            : mj001
 *  Filename        : SD_CLI.H
 *  Creator         : K.C.E JAPAN - K.Muraoka
 *  First edition   : 1996/11/13
 *
 *  Note            : 
 *                  : 
 *===================================================================*/

/*--------------------- External Declaration 4 Client Task ----------*/

extern int sd_task_active(void);
extern int sd_set_cli (int sound_code, int sync_mode);
extern void sd_set_path(const char *str);
extern unsigned char *get_sd_buf(int size);
extern int SePlay(int sound_code); /* If "sound_code" is wrong, return < 0 */
extern int sd_str_play(void);   /* If "STREAM is PLAYING", return 1 */
extern int sd_sng_play(void);   /* If "SONG is PLAYING", return 1 */
extern int sd_se_play(void);    /* If "SE(without JOUCHUU SE) is PLAYING", return SoundCode */
extern int sd_se_play2(void);   /* If "JOUCHUU SE is PLAYING", return SoundCode */
extern int get_sng_code(void);  /* Return "SONG PLAY" SoundCode */
extern int get_str_counter(void);
/*
extern int sd_bgm_play(void);
extern int sd_bgm_fade(void);
extern int sd_bgm_load(void);
extern int sd_vox_play(void);
extern int sd_vox_load(void);
extern int sd_se_play(void);
extern int sd_se_load(void);
extern int get_bgm_code(void);
extern int get_se_code(void);
extern int get_se_code2(void);
extern void sd_clr_save_code(void);
*/

/*-----------------------------------------------------------------------*/

extern void start_xa_sd(void);
extern void stop_xa_sd(void);

/*--------------------- Sync Mode 4 SdSet -------------------------------*/

#define SD_SYNC     1
#define SD_ASYNC    0


#endif
/* clang-format on */
