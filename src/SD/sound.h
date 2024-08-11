#ifndef _SOUND_H_
#define _SOUND_H_

void               keyoff_80087F80(void);
int                SD_8008395C(int a1, int a2);
int                SD_80083954(int a1, unsigned char *a2, int a3);
void               init_sng_work_8008559C(void);
int                SD_SongLoadData_8008394C(int a1, int a2);
void               freq_set_800885D4(unsigned int note_tune);
int                get_str_counter_80088CA0(void);
int                sd_str_play_800886DC(void);
int                sd_set_cli_800887EC(int sound_code, int sync_mode);
unsigned char     *SD_SngDataLoadInit_80083E8C(unsigned short);
char              *LoadInit_80083F08(unsigned short);
void               SD_80083ED4(void);
unsigned char     *SD_80083EE8(unsigned short);
void               SD_Unload_800843BC(void);
char              *SD_WavLoadBuf_800841D4(char *arg0);
void               StrFadeWkSet_80083964(void);
void               volxset_80086C98(unsigned char depth);
void               pan_generate_80086198(void);
void               drum_set_80088694(unsigned char n);
void               vol_set_80088320(unsigned int vol_data);
void               StrFadeIn_800822C8(unsigned int a1);
int                StrFadeOut_80082310(unsigned int a1);
int                StrFadeOutStop_80082380(unsigned int fadeSpeed);
void               SdMain_80081A18(void);
int                sd_task_active_800886C4(void);
void               start_xa_sd_80088868(void);
void               stop_xa_sd_800888B4(void);
int                SD_800886F4(void);

#endif // _SOUND_H_
