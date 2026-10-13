#ifndef __SD_INCL_H__
#define __SD_INCL_H__

/*---------------------- SPU Channel Allocation ------------------------*/

#define INTERNAL_TRACK_NUM  (SNG_TRACK_NUM+SE_TRACK_NUM)

#define SNG_TRACK_NUM       13

#define SE_START_TRACK      SNG_TRACK_NUM
#define SE_TRACK_NUM        8

#define STR_TRACK_NUM       2

/*---------------------- Main RAM Allocation ---------------------------*/

#define SNG_DATA_SIZE       0x4000
#define WAVEHEADERSIZE      0x1000
#define SEHEADERSIZE        0x800
#define SE_DATA_SIZE        0x2000
#define CDLOAD_BUF_SIZE     0x18000

/*---------------------- SNG Driver ------------------------------------*/

#define ENV_CUT_OFF         7       /* cutoff release register value */
#define SEQ_DRC             0x0048  /* sequence control drum start code */
#define SNG_NOTE_SIZE       4
#define SNG_VOL             0x10000 /* BGM fade ratio max */

/*---------------------- SNG Control Code ------------------------------*/

#define REST_SET    0xf2
#define KYU_SET     0xf2
#define TIE_SET     0xf3
#define SNO_SET     0xd2            /* tone set                 */

#define SWP_SET     0xe4            /* event set                */
#define L1_S        0xe7            /* loop1 start              */
#define L1_E        0xe8            /* loop1 end                */
#define L2_S        0xe9            /* loop2 start              */
#define L2_E        0xea            /* loop2 end                */
#define L3_S        0xeb            /* loop3 start              */
#define L3_E        0xec            /* loop3 end                */
#define KAKKO_S     0xed            /* kakko start              */
#define KAKKO_E     0xee            /* kakko end                */

/*---------------------- XXX -------------------------------------------*/

#define ERR_STR_OPEN        -1
#define ERR_VOX_OPEN        -2
#define ERR_VOX_NOBLOCK     -3
#define ERR_SE_OPEN         -4
#define ERR_SNG_OPEN        -5

#define SD_TASK_ACTIVE      0x80

/*---------------------- XXX -------------------------------------------*/

#define KIND_STR    1
#define KIND_WVX    2
#define KIND_MDX    3
#define KIND_EFX    4

#define INT1SEC     (100)   /* approx. interrupts per second. */

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
struct WAVE_W {
    unsigned long   addr;
    char            sample_note;
    char            sample_tune;
    unsigned char   a_mode;
    unsigned char   ar;
    unsigned char   dr;
    unsigned char   s_mode;
    unsigned char   sr;
    unsigned char   sl;
    unsigned char   r_mode;
    unsigned char   rr;
    unsigned char   pan;
    unsigned char   decl_vol;
};

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
struct SPU_TRACK_REG {
    unsigned short  vol_l;
    unsigned short  vol_r;
    int             vol_fg;
    unsigned short  pitch;
    int             pitch_fg;
    unsigned long   addr;
    int             addr_fg;
    long            a_mode;
    unsigned short  ar;
    unsigned short  dr;
    int             env1_fg;
    long            s_mode;
    unsigned short  sr;
    unsigned short  sl;
    int             env2_fg;
    long            r_mode;
    unsigned short  rr;
    int             env3_fg;
};

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
struct SETBL {
    unsigned char   pri;
    unsigned char   tracks;
    unsigned char   kind;       /**/
    unsigned char   character;  /**/
    unsigned char   *addr[3];
};

struct SEPLAYTBL {
    unsigned char   pri;
    unsigned char   kind;       /**/
    unsigned char   character;  /**/
    unsigned char   *addr;
    unsigned long   code;
};

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
struct SOUND_W {
    unsigned char   *mpointer;  /* music data pointer */
    unsigned char   ngc;        /* sweep counter */
    unsigned char   ngo;        /* keyoff counter */
    unsigned char   ngs;        /* step time */
    unsigned char   ngg;        /* gate time */
    unsigned char   lp1_cnt;    /* loop counter */
    unsigned char   lp2_cnt;
    int             lp1_vol;    /* loop volume */
    int             lp2_vol;
    int             lp1_freq;   /* loop frequency */
    int             lp2_freq;
    unsigned char   *lp1_addr;  /* loop address */
    unsigned char   *lp2_addr;
    unsigned char   *lp3_addr;
    unsigned char   kakfg;      /* kakko flag */
    unsigned char   *kak1ptr;   /* kakko start address */
    unsigned char   *kak2ptr;   /* kakko return address */
    unsigned char   pvoc;       /* volume move counter */
    int             pvod;       /* volume move data */
    int             pvoad;      /* volume move change per interrupt */
    unsigned int    pvom;       /* volume move memory */
    unsigned char   vol;        /* volume (velosity) */
    char            panc;       /* pan counter */
    int             pand;       /* pan data */
    int             panad;      /* pan movement addition value */
    int             panm;       /* pan memory */
    char            panf;       /* pan phase */
    char            panoff;     /* pan off flag */
    char            panmod;     /* pan mode */
    unsigned char   swpc;       /* sweep counter */
    unsigned char   swphc;      /* sweep hold counter */
    unsigned int    swpd;       /* sweep depth data */
    int             swpad;      /* sweep change per interrupt */
    unsigned int    swpm;       /* sweep memory (target value) */
    unsigned char   swsc;       /* sweep counter */
    unsigned char   swshc;      /* sweep hold counter */
    char            swsk;       /* sweep flag */
    int             swss;       /* sweep change (in semitones) */
    unsigned char   vibhc;      /* vibrato hold counter */
    unsigned int    vib_tmp_cnt;/* vibrato counter */
    unsigned char   vib_tbl_cnt;/* vibrato table counter */
    unsigned char   vib_tc_ofst;/* vibrato table counter offset */
    unsigned char   vibcc;      /* vibrato change counter */
    unsigned int    vibd;       /* vibrato depth */
    unsigned int    vibdm;      /* vibrato depth memory */
    unsigned char   vibhs;      /* vibrato hold step num */
    unsigned char   vibcs;      /* vibrato change step num */
    unsigned char   vibcad;     /* vibrato movement per step */
    unsigned int    vibad;      /* vibrato change per step */
    unsigned int    rdmc;       /* LFO counter */
    unsigned int    rdmo;       /* LFO offset pointer */
    unsigned char   rdms;       /* LFO speed data */
    unsigned int    rdmd;       /* LFO data */
    signed char     trec;       /* tremolo counter */
    unsigned char   trehc;      /* tremolo hold counter */
    char            tred;       /* tremolo depth */
    unsigned char   trecad;     /* tremolo change per interrupt */
    unsigned char   trehs;      /* tremolo hold step num */
    unsigned int    snos;       /* tone number */
    int             ptps;       /* part-transpose value */
    unsigned long   dec_vol;    /* PSX volume correction value */
    int             tund;       /* tuning data */
    unsigned int    tmpd;       /* tempo counter */
    unsigned char   tmp;        /* tempo data */
    unsigned int    tmpad;      /* tempo change per interrupt */
    unsigned char   tmpc;       /* tempo movement counter */
    unsigned int    tmpw;       /* tempo movement value */
    unsigned char   tmpm;       /* tempo memory value */
    unsigned int    rest_fg;    /* rest flag */
    char            macro;      /* tuning data (pitch) */
    char            micro;      /* tuning data (tune) */
    unsigned short  rrd;        /* release depth */
};

#endif // __SD_INCL_H__
