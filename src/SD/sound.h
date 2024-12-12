#ifndef _SOUND_H_
#define _SOUND_H_

/* sd_main.c */
void SdMain(void);

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

/* sd_file.c */
unsigned char *SD_SngDataLoadInit(unsigned short id);
void SD_80083ED4(void);
unsigned char *SD_SeDataLoadInit(unsigned short id);
char *SD_WavDataLoadInit(unsigned short id);
char *SD_WavLoadBuf(char *arg0);
void SD_WavUnload(void);

#endif // _SOUND_H_
