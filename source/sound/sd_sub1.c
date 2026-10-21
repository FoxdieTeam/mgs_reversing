#include "sd_incl.h"
#include "sd_ext.h"

#define ENDOFMEASURE    0xFE
#define ENDOFBLOCK      0xFE
#define ENDOFSONG       0xFF

/*----------------------------------------------------------------------*/
/*                      External Declarations                           */
/*----------------------------------------------------------------------*/

/* in sd_ioset.c */
extern void keyon(void);
extern void keyoff(void);
extern void vol_set(unsigned int vol_data);
extern void freq_set(unsigned int note_tune);
extern void drum_set(unsigned char n);

/* in sd_sub2.c */
extern void rest_set(void), sno_set(void), pan_set(void), pan_move(void);
extern void vib_set(void), rdm_set(void), lp1_start(void), lp1_end(void);
extern void lp2_start(void), lp2_end(void), tempo_set(void), tempo_move(void);
extern void trans_set(void), tre_set(void), vol_chg(void), vol_move(void);
extern void vib_change(void), por_set(void), sws_set(void), detune_set(void);
extern void swp_set(void), tie_set(void), echo_set1(void), echo_set2(void);
extern void kakko_start(void), kakko_end(void), env_set(void), pm_set(void);
extern void jump_set(void), no_cmd(void);
extern void ads_set(void), srs_set(void), rrs_set(void);
extern void eon_set(void), eof_set(void);
extern void l3s_set(void), l3e_set(void), svl_set(void), svp_set(void), use_set(void);
extern void block_end(void);

/*----------------------------------------------------------------------*/
/*                      Control Code Program Table                      */
/*----------------------------------------------------------------------*/
void (*cntl_tbl[128])(void) = {
/* 0x80 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
/* 0x90 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
/* 0xA0 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
/* 0xB0 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
/* 0xC0 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,
/* 0xD0 */
    tempo_set,tempo_move,sno_set,svl_set,svp_set,vol_chg,vol_move,ads_set,
    srs_set,rrs_set,no_cmd,no_cmd,no_cmd,pan_set,pan_move,trans_set,
/* 0xE0 */
    detune_set,vib_set,vib_change,rdm_set,swp_set,sws_set,por_set,lp1_start,
/* 0xE8 */
    lp1_end,lp2_start,lp2_end,l3s_set,l3e_set,kakko_start,kakko_end,no_cmd,
/* 0xF0 */
    no_cmd,use_set,rest_set,tie_set,echo_set1,echo_set2,eon_set,eof_set,
/* 0xF8 */
    no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,no_cmd,block_end
};

/* RANDOM LFO TABLE */
char rdm_tbl[129] = {
0x9F,0x3C,0xB2,0x52,0xAF,0x45,0xC7,0x89,0x10,0x7F,0xE0,0x9D,0xDC,0x1F,0x61,0x16,
0x39,0xC9,0x9C,0xEB,0x57,0x08,0x66,0xF8,0x5A,0x24,0xBF,0x0E,0x3E,0x15,0x4B,0xDB,
0xAB,0xF5,0x31,0x0C,0x43,0x02,0x55,0xDE,0x41,0xDA,0xBD,0xAE,0x19,0xB0,0x48,0x57,
0xBA,0xA3,0x36,0x0B,0xF9,0xDF,0x17,0xA8,0x04,0x0C,0xE0,0x91,0x18,0x5D,0xDD,0xD3,
0x28,0x8A,0xF2,0x11,0x59,0x6F,0x06,0x0A,0x34,0x2A,0x79,0xAC,0x5E,0xA7,0x83,0xC6,
0x39,0xC1,0xB4,0x3A,0x3F,0xFE,0x4F,0xEF,0x1F,0x00,0x30,0x99,0x4C,0x28,0x83,0xED,
0x8A,0x2F,0x2C,0x66,0x3F,0xD6,0x6C,0xB7,0x49,0x22,0xBC,0x65,0xFA,0xCF,0x02,0xB1,
0x46,0xF0,0x9A,0xD7,0xE2,0x0F,0x11,0xC5,0x74,0xF6,0x7A,0x2C,0x8F,0xFB,0x19,0x6A,
0xE5
};

/*----------------------------------------------------------------------*/
/*                      Function Declarations                           */
/*----------------------------------------------------------------------*/
int sound_sub(void);
int tx_read(void);
void note_set(void);
inline void adsr_reset(void);
void note_compute(void);
inline void swpadset(int xfreq);
void vol_compute(void);
void pan_generate(void);
void key_cut_off(void);
void keych(void);
inline void por_compute(void);
inline int vib_compute(void);
int vib_generate(signed char cnt);
void bendch(void);
void note_cntl(void);
unsigned int random(void);
void tempo_ch(void);
void volxset(unsigned char depth);

/*----------------------------------------------------------------------*/
/*                      Macro Definitions                               */
/*----------------------------------------------------------------------*/

#define GET_VEL     *(mptr)
#define GET_GATE    *(mptr+1)
#define GET_STEP    *(mptr+2)
#define GET_NOTE    *(mptr+3)

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
int sound_sub(void)
{
    int tempo_move;

    key_fg = 0;
    sptr->tmpd += sptr->tmp;

    if (mtrack < SNG_TRACK_NUM) {
        if (sng_tempo_move) {
            tempo_move = sng_tempo_move >> 5;
            if (sptr->tmp > tempo_move) sptr->tmpd -= tempo_move;
        }
    }

    if (sptr->tmpd >= 0x100) {
        sptr->tmpd &= 0xFF;
        --sptr->ngc;

        if (sptr->ngc == 0) {
            if (tx_read() != 0) {
                keyoff();
                return 1;
            }
        } else {
            keych();
        }
        tempo_ch();
        bendch();
        vol_compute();
    } else {
        note_cntl();
    }

    if (key_fg) {
        keyon();
        return 0;
    }
    return 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
int tx_read(void)
{
    int read_fg;
    int loop_count = 0;

    read_fg = 1;

    while (read_fg) {
/*----------------------------------------------------------------------*/
        loop_count++;
        if (loop_count == 256) {
            return 1;
        }
/*----------------------------------------------------------------------*/
        mdata1 = GET_NOTE;

        if (mdata1 == 0) return 1;

        mdata2 = GET_STEP;
        mdata3 = GET_GATE;
        mdata4 = GET_VEL;

        mptr += SNG_NOTE_SIZE;
/*----------------------------------------------------------------------*/
        if ((char)mdata1 >= 0x80) {
            cntl_tbl[mdata1 - 0x80]();
            if ((mdata1 == REST_SET) || (mdata1 == TIE_SET) || (mdata1 == 0xFF)) {
                read_fg = 0;
            }
            if (mdata1 == ENDOFSONG) {
                return 1;
            }
        } else {
            if ((sptr->ngg <= 99) && (mdata4 != 0)) {
                key_fg = 1;
            }
            read_fg = 0;
            sptr->rest_fg = 0;
            note_set();
        }
    }
    return 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void note_set(void)
{
    unsigned int x;

    sptr->ngs = mdata2;
    sptr->ngg = mdata3;
    sptr->vol = (mdata4 & 0x7F);

    note_compute();

    sptr->ngc = sptr->ngs;
    x = (sptr->ngg * sptr->ngc) / 100;
    if (x == 0) {
        x = 1;
    }
    sptr->ngo = x;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
inline void adsr_reset(void)
{
    spu_tr_wk[mtrack].rr = sptr->rrd;
    spu_tr_wk[mtrack].env3_fg = 1;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void note_compute(void)
{
    int x;
    int swp_ex;
    struct SOUND_W *ptr;

    if (mdata1 >= SEQ_DRC) {
        drum_set(mdata1);
        x = 0x24;
    } else {
        x = mdata1;
    }
    x += sptr->ptps;
    x = (x << 8) + sptr->tund;
    x = x + sptr->lp1_freq + sptr->lp2_freq;
    while (x >= 0x6000) {
        x -= 0x6000;
    }

    swp_ex = sptr->swpd;

    ptr = sptr;
    ptr->vibcc = 0;
    ptr->vibhc = 0;
    ptr->swpd = x;

    sptr->vib_tmp_cnt = 0;
    sptr->vib_tbl_cnt = 0;

    ptr = sptr;
    ptr->trehc = 0;
    ptr->trec = 0;
    ptr->vibd = 0;

    adsr_reset();

    sptr->swpc = sptr->swsc;

    if (sptr->swpc != 0) {
        sptr->swphc = sptr->swshc;
        if (sptr->swsk == 0) {
            x = sptr->swpd;
            if (sptr->swss >= 0x7F01) {
                sptr->swpd += 0x10000 - (sptr->swss & 0xFFFF);
            } else {
                sptr->swpd -= sptr->swss;
            }
            swpadset(x);
        } else {
            sptr->swpm = sptr->swpd;
            sptr->swpd = swp_ex;
        }
    }
    freq_set(sptr->swpd);
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
inline void swpadset(int xfreq)
{
    unsigned int flame_dat;

    if (sptr->swpc) {
        flame_dat = sptr->swpc << 8;
        flame_dat = flame_dat / sptr->tmp;
        if (xfreq < 0) {
            xfreq = 0;
        } else {
            if (xfreq >= 0x6000) xfreq = 0x5FFF;
        }
        sptr->swpm = xfreq;
        xfreq -= sptr->swpd;
        if (xfreq < 0) {
            xfreq = -xfreq / flame_dat;
            sptr->swpad = -xfreq;
        } else {
            sptr->swpad = xfreq / flame_dat;
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vol_compute(void)
{
    unsigned int depth;

    if (sptr->pvoc != 0) {
        if ((--sptr->pvoc) == 0) {
            sptr->pvod = sptr->pvom << 8;
        } else {
            sptr->pvod += sptr->pvoad;
        }
    }
    if (sptr->vol != 0) {
        if (sptr->tred == 0) {
            depth = 0;
        } else {
            if (sptr->trehs == sptr->trehc) {
                sptr->trec += sptr->trecad;

                if (sptr->trec < 0) {
                    depth = sptr->tred * -sptr->trec;
                } else {
                    if (sptr->trec == 0) {
                        depth = 1;
                    }
                    else {
                        depth = sptr->tred * sptr->trec;
                    }
                }
            } else {
                sptr->trehc++;
                depth = 0;
            }
        }
        volxset(depth >> 8);
    }
    pan_generate();
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void pan_generate(void)
{
    if (sptr->panc != 0) {
        if ((--sptr->panc) == 0) {
            sptr->pand = sptr->panm;
        } else {
            sptr->pand += sptr->panad;
        }
        sptr->panf = sptr->pand >> 8;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void key_cut_off(void)
{
    if (sptr->rrd > ENV_CUT_OFF) {
        spu_tr_wk[mtrack].rr = ENV_CUT_OFF;
        spu_tr_wk[mtrack].env3_fg = 1;
    }
}

void keych(void)
{
    int vib_data;
    int rdm_data;
    int set_fg;

/*----------------------------------------------------------------------*/
    if ((sptr->ngg < 100) && (sptr->ngc == 1) && (sptr->rrd >= 8)) {
        spu_tr_wk[mtrack].rr = 7;
        spu_tr_wk[mtrack].env3_fg = 1;
    }

/*----------------------------------------------------------------------*/
    if (sptr->ngo != 0) {
        sptr->ngo--;
        if (sptr->ngo == 0) {
            keyoff();
        }
    }
/*----------------------------------------------------------------------*/
    set_fg = 0;
    if (sptr->swpc != 0) {
        if (sptr->swphc != 0) {
            sptr->swphc--;
        } else {
            if (sptr->swsk == 0) {
                if ((--sptr->swpc) == 0) {
                    sptr->swpd = sptr->swpm;
                } else {
                    sptr->swpd += sptr->swpad;
                }
            } else {
                por_compute();
            }
            set_fg = 1;
        }
    }
/*----------------------------------------------------------------------*/
    vib_data = 0;
    if (sptr->vibdm != 0) {
        if (sptr->vibhc != sptr->vibhs) {
            sptr->vibhc++;
        } else {
            if (sptr->vibcc == sptr->vibcs) {
                sptr->vibd = sptr->vibdm;
            } else {
                if (sptr->vibcc != 0) {
                    sptr->vibd += sptr->vibad;
                } else {
                    sptr->vibd = sptr->vibad;
                }
                ++sptr->vibcc;
            }

            sptr->vib_tmp_cnt += sptr->vibcad;
            if (sptr->vib_tmp_cnt >= 0x100) {
                sptr->vib_tmp_cnt &= 0xFF;
                vib_data = vib_compute();
                set_fg = 1;
            }
        }
    }
/*----------------------------------------------------------------------*/
    if ((rdm_data = random()) != 0) {
        vib_data += rdm_data;
        set_fg = 1;
    }

    if (set_fg != 0) {
        freq_set(sptr->swpd + vib_data);
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
inline void por_compute(void)
{
    int          por_freq;
    unsigned int pfreq_h, pfreq_l;

    por_freq = sptr->swpm - sptr->swpd;
    if (por_freq < 0) {
        por_freq = -por_freq;
        pfreq_l = por_freq & 0xFF;
        pfreq_h = por_freq >> 8;
        pfreq_l = (pfreq_l * sptr->swsc) >> 8;
        pfreq_h *= sptr->swsc;
        por_freq = pfreq_h + pfreq_l;
        if (por_freq == 0) por_freq = 1;
        por_freq = -por_freq;
    }
    else {
        if (por_freq == 0) {
            sptr->swpc = 0;
        }
        else {
            pfreq_l = por_freq & 0xFF;
            pfreq_h = por_freq >> 8;
            pfreq_l = (pfreq_l * sptr->swsc) >> 8;
            pfreq_h *= sptr->swsc;
            por_freq = pfreq_h + pfreq_l;
            if (por_freq == 0) {
                por_freq = 1;
            }
        }
    }
    sptr->swpd += por_freq;
}

/*----------------------------------------------------------------------*/
unsigned char VIBX_TBL[32] = {
    0x00,0x20,0x38,0x50,0x68,0x80,0x90,0xA0,
    0xB0,0xC0,0xD0,0xE0,0xE8,0xF0,0xF0,0xF8,
    0xFF,0xF8,0xF4,0xF0,0xE8,0xE0,0xD0,0xC0,
    0xB0,0xA0,0x90,0x80,0x68,0x50,0x38,0x20
};

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
inline int vib_compute(void)
{
    unsigned int tmp;
    int          tbl_data;
    unsigned int vib_data;

    sptr->vib_tbl_cnt += sptr->vib_tc_ofst;
    sptr->vib_tbl_cnt &= 0x3Fu;
    tbl_data = VIBX_TBL[sptr->vib_tbl_cnt & 0x1F];
    tmp = sptr->vibd;
    if (0x7FFF >= tmp) {
        vib_data = ((tmp >> 7) & 0xFE);
        vib_data = (vib_data * tbl_data) >> 8;
    } else {
        vib_data = ((tmp >> 8) & 0x7F) + 2;
        vib_data = (vib_data * tbl_data) >> 1;
    }
    if (sptr->vib_tbl_cnt >= 0x20) {
        vib_data = -vib_data;
    }
    return vib_data;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
int vib_generate(signed char cnt)
{
    signed char vib_char;
    int         vib_data;

    if (cnt < 0) {
        vib_char = -cnt << 1;
        if (vib_char < 0) {
            vib_char = -vib_char;
        }
        vib_char = (unsigned char)vib_char >> 2;
        vib_data = (unsigned char)(sptr->vibd >> 8) * vib_char;
        vib_data = -vib_data;
    } else {
        vib_char = cnt << 1;
        if (vib_char < 0) {
            vib_char = -vib_char;
        }
        vib_char = (unsigned char)vib_char >> 2;
        vib_data = (unsigned char)(sptr->vibd >> 8) * vib_char;
    }
    if (sptr->vibdm < 0x8000) {
        vib_data >>= 2;
    }
    return vib_data;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void bendch(void)
{
    int bend_frq;

    if (sptr->swpc == 0) {
        mdata1 = GET_NOTE;
        if (mdata1 == SWP_SET) {
            sptr->swphc = GET_STEP;
            sptr->swpc = GET_GATE;
            bend_frq = GET_VEL;
            mptr += SNG_NOTE_SIZE;

            bend_frq = (bend_frq + sptr->ptps) << 8;
            bend_frq += sptr->tund;
            swpadset(bend_frq);
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void note_cntl(void)
{
    int             rdm_data;
    int             vib_data;
    int             fset_fg;
    int             frq_data;
    unsigned int    depth;
/*----------------------------------------------------------------------*/
    if (sptr->vol != 0 && sptr->tred != 0 && sptr->trehs == sptr->trehc) {
        sptr->trec += (unsigned)(sptr->trecad * (char)sptr->tmpd) >> 8;

        if (sptr->trec < 0) {
            depth = sptr->tred * -sptr->trec;
        } else {
            if (sptr->trec == 0) {
                depth = 1;
            } else {
                depth = sptr->tred * sptr->trec;
            }
        }
        volxset(depth >> 8);
    }
/*----------------------------------------------------------------------*/
    fset_fg = 0;
    frq_data = sptr->swpd;
    if (sptr->swpc != 0 && sptr->swphc == 0) {
        fset_fg = 1;
        if (sptr->swsk == 0) {
            sptr->swpd += sptr->swpad;
        } else {
            por_compute();
        }
        frq_data = sptr->swpd;
    }
/*----------------------------------------------------------------------*/
    if ((sptr->vibd != 0) && (sptr->vibhs == sptr->vibhc)) {
        sptr->vib_tmp_cnt += sptr->vibcad;
        if ((unsigned)sptr->vib_tmp_cnt >= 256) {
            sptr->vib_tmp_cnt &= 0x00FF;
            vib_data = vib_compute();
            frq_data += vib_data;
            fset_fg = 1;
        }
    }
/*----------------------------------------------------------------------*/
    if ((rdm_data = random()) != 0) {
        fset_fg = 1;
        frq_data += rdm_data;
    }

    if (fset_fg != 0) {
        freq_set(frq_data);
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
unsigned int random(void)
{
    unsigned int frq_dt;
    unsigned char c_data;

    frq_dt = 0;
    if (sptr->rdms) {
        sptr->rdmc += sptr->rdms;
        if (sptr->rdmc > 0x100) {
            sptr->rdmc &= 0xFF;
            sptr->rdmo++;
            sptr->rdmo &= 0x7F;
            c_data = rdm_tbl[sptr->rdmo];
            frq_dt = rdm_tbl[sptr->rdmo + 1] << 8;
            frq_dt += c_data;
            frq_dt &= sptr->rdmd;
        }
    }
    return frq_dt;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void tempo_ch(void)
{
    if (sptr->tmpc != 0) {
        if ((--sptr->tmpc) == 0) {
            sptr->tmpw = sptr->tmpm << 8;
        } else {
            sptr->tmpw += sptr->tmpad;
        }
        sptr->tmp = sptr->tmpw >> 8;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void volxset(unsigned char depth)
{
    int vol_data, pvod_w;

    vol_data = sptr->vol;
    vol_data -= depth;
    vol_data += sptr->lp1_vol;
    vol_data += sptr->lp2_vol;
    if (vol_data < 0) {
        vol_data = 0;
    } else {
        if (vol_data > 0x7F) vol_data = 0x7F;
    }
    pvod_w = (sptr->pvod >> 8) & 0xFF;
    vol_set((unsigned char)((pvod_w * vol_data) >> 8));
}
