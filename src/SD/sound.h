#ifndef _SOUND_H_
#define _SOUND_H_

typedef struct WAVE_W
{
    unsigned long  addr;
    char           sample_note;
    char           sample_tune;
    unsigned char  a_mode;
    unsigned char  ar;
    unsigned char  dr;
    unsigned char  s_mode;
    unsigned char  sr;
    unsigned char  sl;
    unsigned char  r_mode;
    unsigned char  rr;
    unsigned char  pan;
    unsigned char  decl_vol;
} WAVE_W;

typedef struct SPU_TRACK_REG
{
    unsigned short vol_l;
    unsigned short vol_r;
    int            vol_fg;
    unsigned short pitch;
    short          field_A_pad;
    int            pitch_fg;
    unsigned long  addr;
    int            addr_fg;
    long           a_mode;
    unsigned short ar;
    unsigned short dr;
    int            env1_fg;
    long           s_mode;
    unsigned short sr;
    unsigned short sl;
    int            env2_fg;
    long           r_mode;
    unsigned short rr;
    short          field_36_pad;
    int            env3_fg;
} SPU_TRACK_REG;

typedef struct SETBL
{
    unsigned char  pri;
    unsigned char  tracks;
    unsigned char  kind;
    unsigned char  character;
/*  unsigned char *addr[3]; -- todo */
    int            addr[3];
} SETBL;

typedef struct SEPLAYTBL
{
    unsigned char  pri;
    unsigned char  kind;
    unsigned char  character;
    unsigned char *addr;
    unsigned long  code;
} SEPLAYTBL;

typedef struct SOUND_W
{
    unsigned char *mpointer;
    unsigned char  ngc;
    unsigned char  ngo;
    unsigned char  ngs;
    unsigned char  ngg;
    unsigned char  lp1_cnt;
    unsigned char  lp2_cnt;
    int            lp1_vol;
    int            lp2_vol;
    int            lp1_freq;
    int            lp2_freq;
    unsigned char *lp1_addr;
    unsigned char *lp2_addr;
    unsigned char *lp3_addr;
    unsigned char  kakfg;
    unsigned char *kak1ptr;
    unsigned char *kak2ptr;
    unsigned char  pvoc;
    int            pvod;
    int            pvoad;
    unsigned int   pvom;
    unsigned char  vol;
    char           panc;
    int            pand;
    int            panad;
    int            panm;
    char           panf;
    char           panoff;
    char           panmod;
    unsigned char  swpc;
    unsigned char  swphc;
    unsigned int   swpd;
    int            swpad;
    unsigned int   swpm;
    unsigned char  swsc;
    unsigned char  swshc;
    char           swsk;
    int            swss;
    unsigned char  vibhc;
    unsigned int   vib_tmp_cnt;
    unsigned char  vib_tbl_cnt;
    unsigned char  vib_tc_ofst;
    unsigned char  vibcc;
    unsigned int   vibd;
    unsigned int   vibdm;
    unsigned char  vibhs;
    unsigned char  vibcs;
    unsigned char  vibcad;
    unsigned int   vibad;
    unsigned int   rdmc;
    unsigned int   rdmo;
    unsigned char  rdms;
    unsigned int   rdmd;
    signed char    trec;
    unsigned char  trehc;
    char           tred;
    unsigned char  trecad;
    unsigned char  trehs;
    unsigned int   snos;
    int            ptps;
    unsigned long  dec_vol;
    int            tund;
    unsigned int   tmpd;
    unsigned char  tmp;
    unsigned int   tmpad;
    unsigned char  tmpc;
    unsigned int   tmpw;
    unsigned char  tmpm;
    unsigned int   rest_fg;
    char           macro;
    char           micro;
    unsigned short rrd;
} SOUND_W;

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
