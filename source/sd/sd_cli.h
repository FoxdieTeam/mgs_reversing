/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/sd_cli.h (Nov.09,1999)
 */
#ifndef __SD_CLI_H__
#define __SD_CLI_H__

#define SD_SYNC     1
#define SD_ASYNC    0

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

/* sd_main.c */
void SdMain(void);

/* sd_file.c */
unsigned char *SD_SngDataLoadInit(unsigned short id);
void SD_80083ED4(void);
unsigned char *SD_SeDataLoadInit(unsigned short id);
char *SD_WavDataLoadInit(unsigned short id);
char *SD_WavLoadBuf(char *arg0);
void SD_WavUnload(void);

#endif // __SD_CLI_H__
