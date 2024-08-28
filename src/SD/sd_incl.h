#ifndef _SD_INCL_H_
#define _SD_INCL_H_

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

#endif // _SD_INCL_H_
