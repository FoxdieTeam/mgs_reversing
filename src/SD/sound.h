#ifndef _SOUND_H_
#define _SOUND_H_

/* sd_main.c */
void SdMain_80081A18(void);

/* sd_cli.c */
int sd_task_active_800886C4(void);
int sd_str_play_800886DC(void);
int SD_800886F4(void);
int sd_set_cli_800887EC(int sound_code, int sync_mode);
void start_xa_sd_80088868(void);
void stop_xa_sd_800888B4(void);
int get_str_counter_80088CA0(void);

/* sd_file.c */
unsigned char *SD_SngDataLoadInit_80083E8C(unsigned short);
void SD_80083ED4(void);
unsigned char *SD_80083EE8(unsigned short);
char *LoadInit_80083F08(unsigned short);
char *SD_WavLoadBuf_800841D4(char *arg0);
void SD_Unload_800843BC(void);

#endif // _SOUND_H_
