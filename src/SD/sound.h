#ifndef _SOUND_H_
#define _SOUND_H_

/* sd_main.c */
void SdMain(void);

/* sd_cli.c */
int sd_task_active(void);
int sd_str_play(void);
int SD_800886F4(void);
int sd_set_cli(int sound_code, int sync_mode);
void start_xa_sd(void);
void stop_xa_sd(void);
int get_str_counter(void);

/* sd_file.c */
unsigned char *SD_SngDataLoadInit(unsigned short);
void SD_80083ED4(void);
unsigned char *SD_80083EE8(unsigned short);
char *LoadInit(unsigned short);
char *SD_WavLoadBuf(char *arg0);
void SD_Unload(void);

#endif // _SOUND_H_
