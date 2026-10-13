#include "sd_incl.h"
#include "sd_ext.h"

#define ENDOFMEASURE    0xFE
#define ENDOFBLOCK      0xFE
#define ENDOFSONG       0xFF

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

/* in sd_ioset.c */
extern void keyon(void);
extern void keyoff(void);
extern void vol_set(unsigned int vol_data);
extern void freq_set(unsigned int note_tune);
extern void drum_set(unsigned char n);

/* in sd_sub2.c */
extern void rest_set(void);
extern void tie_set(void);
extern void sno_set(void);
extern void svl_set(void);
extern void svp_set(void);
extern void use_set(void);
extern void pan_set(void);
extern void pan_move(void);
extern void vib_set(void);
extern void vib_change(void);
extern void rdm_set(void);
extern void lp1_start(void);
extern void lp1_end(void);
extern void lp2_start(void);
extern void lp2_end(void);
extern void l3s_set(void);
extern void l3e_set(void);
extern void tempo_set(void);
extern void tempo_move(void);
extern void trans_set(void);
extern void tre_set(void);
extern void vol_chg(void);
extern void vol_move(void);
extern void por_set(void);
extern void sws_set(void);
extern void detune_set(void);
extern void swp_set(void);
extern void echo_set1(void);
extern void echo_set2(void);
extern void eon_set(void);
extern void eof_set(void);
extern void kakko_start(void);
extern void kakko_end(void);
extern void env_set(void);
extern void ads_set(void);
extern void srs_set(void);
extern void rrs_set(void);
extern void pm_set(void);
extern void jump_set(void);
extern void block_end(void);
extern void no_cmd(void);

/*----------------------------------------------------------------------*/
/*                                                                      */
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

unsigned char rdm_tbl[129] = { /* char[] */
    159,  60, 178,  82, 175,  69, 199, 137,
     16, 127, 224, 157, 220,  31,  97,  22,
     57, 201, 156, 235,  87,   8, 102, 248,
     90,  36, 191,  14,  62,  21,  75, 219,
    171, 245,  49,  12,  67,   2,  85, 222,
     65, 218, 189, 174,  25, 176,  72,  87,
    186, 163,  54,  11, 249, 223,  23, 168,
      4,  12, 224, 145,  24,  93, 221, 211,
     40, 138, 242,  17,  89, 111,   6,  10,
     52,  42, 121, 172,  94, 167, 131, 198,
     57, 193, 180,  58,  63, 254,  79, 239,
     31,   0,  48, 153,  76,  40, 131, 237,
    138,  47,  44, 102,  63, 214, 108, 183,
     73,  34, 188, 101, 250, 207,   2, 177,
     70, 240, 154, 215, 226,  15,  17, 197,
    116, 246, 122,  44, 143, 251,  25, 106,
    229
};

unsigned char VIBX_TBL[32] = {
      0, 32,   56,  80, 104, 128, 144, 160,
    176, 192, 208, 224, 232, 240, 240, 248,
    255, 248, 244, 240, 232, 224, 208, 192,
    176, 160, 144, 128, 104,  80,  56,  32
};

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

/* local inlines */
inline int  vib_compute(void);
inline void por_compute(void);
inline void swpadset(int xfreq);

int sound_sub(void);
int tx_read(void);
void note_set(void);
void adsr_reset(void);
void note_compute(void);
void vol_compute(void);
void pan_generate(void);
void key_cut_off(void);
void keych(void);
int vib_generate(int cnt);
void bendch(void);
void note_cntl(void);
unsigned int random(void);
void tempo_ch(void);
void volxset(unsigned char depth);

/*----------------------------------------------------------------------*/
/*                                                                      */
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
    int          fade2_shifted;
    unsigned int tmpd;

    key_fg = 0;
    sptr->tmpd += sptr->tmp;
    if ((unsigned int)mtrack < 0xD)
    {
        if (sng_tempo_move)
        {
            fade2_shifted = sng_tempo_move >> 5;
            if (fade2_shifted < (unsigned char)sptr->tmp)
            {
                sptr->tmpd -= fade2_shifted;
            }
        }
    }

    tmpd = sptr->tmpd;
    if (tmpd >= 256)
    {
        sptr->tmpd = tmpd & 0xff;
        --sptr->ngc;

        if (sptr->ngc)
        {
            keych();
        }
        else if (tx_read())
        {
            keyoff();
            return 1;
        }
        tempo_ch();
        bendch();
        vol_compute();
    }
    else
    {
        note_cntl();
    }

    if (key_fg)
    {
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
    int loop_count;

    loop_count = 0;
    read_fg = 1;
    while (read_fg)
    {
        loop_count++;
        if (loop_count == 256)
        {
            return 1;
        }

        mdata1 = mptr[3];
        if (!mdata1)
        {
            return 1;
        }
        mdata2 = mptr[2];
        mdata3 = mptr[1];
        mdata4 = mptr[0];
        mptr += SNG_NOTE_SIZE;

        if ((char)mdata1 >= 128)
        {
            cntl_tbl[mdata1 - 128]();
            if (mdata1 == REST_SET || mdata1 == TIE_SET || mdata1 == 0xFF)
            {
                read_fg = 0;
            }

            if (mdata1 == ENDOFSONG)
            {
                return 1;
            }
        }
        else
        {
            if ((unsigned char)sptr->ngg < 0x64 && mdata4)
            {
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

    if (!x)
    {
        x = 1;
    }
    sptr->ngo = x;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void adsr_reset(void)
{
    spu_tr_wk[mtrack].rr = sptr->rrd;
    spu_tr_wk[mtrack].env3_fg = 1;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void note_compute(void)
{
    int      x;
    int      swp_ex;
    struct SOUND_W *pSound;

    if (mdata1 >= SEQ_DRC)
    {
        drum_set(mdata1);
        x = 0x24;
    }
    else
    {
        x = mdata1;
    }

    x += sptr->ptps;
    x = (x << 8) + sptr->tund;
    x = x + sptr->lp1_freq + sptr->lp2_freq;

    while (x >= 0x6000)
    {
        x -= 0x6000;
    }

    swp_ex = sptr->swpd;

    pSound = sptr;
    pSound->vibcc = 0;
    pSound->vibhc = 0;
    pSound->swpd = x;

    sptr->vib_tmp_cnt = 0;
    sptr->vib_tbl_cnt = 0;

    pSound = sptr;
    pSound->trehc = 0;
    pSound->trec = 0;
    pSound->vibd = 0;

    spu_tr_wk[mtrack].rr = sptr->rrd;
    spu_tr_wk[mtrack].env3_fg = 1;

    sptr->swpc = sptr->swsc;

    if (sptr->swpc != 0)
    {
        sptr->swphc = sptr->swshc;

        if (sptr->swsk == 0)
        {
            x = sptr->swpd;

            if (sptr->swss >= 0x7F01)
            {
                sptr->swpd += 0x10000 - (sptr->swss & 0xFFFF);
            }
            else
            {
                sptr->swpd -= sptr->swss;
            }

            swpadset(x);
        }
        else
        {
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

    if (sptr->swpc)
    {
        flame_dat = sptr->swpc << 8;
        flame_dat = flame_dat / sptr->tmp;
        if (xfreq < 0)
        {
            xfreq = 0;
        }
        else if (xfreq >= 0x6000)
        {
            xfreq = 0x5FFF;
        }

        sptr->swpm = xfreq;

        xfreq -= sptr->swpd;

        if (xfreq < 0)
        {
            xfreq = -xfreq / flame_dat;
            sptr->swpad = -xfreq;
        }
        else
        {
            sptr->swpad = xfreq / flame_dat;
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vol_compute(void)
{
    int          mult;
    unsigned int depth;

    if (sptr->pvoc != 0)
    {
        if (--sptr->pvoc == 0)
        {
            sptr->pvod = sptr->pvom << 8;
        }
        else
        {
            sptr->pvod += sptr->pvoad;
        }
    }

    if (sptr->vol != 0)
    {
        if (sptr->tred == 0)
        {
            depth = 0;
        }
        else
        {
            if (sptr->trehs == sptr->trehc)
            {
                sptr->trec += sptr->trecad;
                mult = sptr->trec;
                if (mult < 0)
                {
                    depth = sptr->tred * -mult;
                }
                else if (mult == 0)
                {
                    depth = 1;
                }
                else
                {
                    depth = sptr->tred * mult;
                }
            }
            else
            {
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
    if (sptr->panc)
    {
        if (!--sptr->panc)
        {
            sptr->pand = sptr->panm;
        }
        else
        {
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
    if (sptr->rrd > ENV_CUT_OFF)
    {
        spu_tr_wk[mtrack].rr = ENV_CUT_OFF;
        spu_tr_wk[mtrack].env3_fg = 1;
    }
}

void keych(void)
{
    int swpc;
    int set_fg;
    int swphc;
    int vibdm;
    int vib_data;
    int vibhc;
    int rdm_data;

    if ((unsigned char)sptr->ngg < 0x64u && sptr->ngc == 1 &&
         (unsigned short)sptr->rrd >= 8u)
    {
        spu_tr_wk[mtrack].rr = 7;
        spu_tr_wk[mtrack].env3_fg = 1;
    }

    if (sptr->ngo)
    {
        sptr->ngo--;
        if (!sptr->ngo)
        {
            keyoff();
        }
    }

    set_fg = 0;

    swpc = sptr->swpc;
    if (swpc)
    {
        swphc = (unsigned char)sptr->swphc;
        if (swphc)
        {
            sptr->swphc--;
        }
        else
        {
            if (!sptr->swsk)
            {
                sptr->swpc = swpc - 1;
                if (!((swpc - 1) & 0xFF))
                {
                    sptr->swpd = sptr->swpm;
                }
                else
                {
                    sptr->swpd += sptr->swpad;
                }
            }
            else
            {
                por_compute();
            }
            set_fg = 1;
        }
    }

    vibdm = sptr->vibdm;
    vib_data = 0;

    if (vibdm)
    {
        vibhc = (unsigned char)sptr->vibhc;
        if (vibhc != (unsigned char)sptr->vibhs)
        {
            sptr->vibhc = vibhc + 1;
        }
        else
        {
            if (sptr->vibcc == sptr->vibcs)
            {
                sptr->vibd = vibdm;
            }
            else
            {
                if (sptr->vibcc)
                {
                    sptr->vibd =
                        sptr->vibd + sptr->vibad;
                }
                else
                {
                    sptr->vibd = sptr->vibad;
                }
                ++sptr->vibcc;
            }
            sptr->vib_tmp_cnt =
                sptr->vib_tmp_cnt + sptr->vibcad;
            if ((unsigned)sptr->vib_tmp_cnt >= 256)
            {
                sptr->vib_tmp_cnt = sptr->vib_tmp_cnt & 0xFF;
                vib_data = vib_compute();
                set_fg = 1;
            }
        }
    }

    rdm_data = random();
    if (rdm_data)
    {
        vib_data += rdm_data;
        set_fg = 1;
    }

    if (set_fg)
    {
        freq_set(sptr->swpd + vib_data);
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
inline void por_compute(void)
{
    int          por_freq;
    unsigned int pfreq_h;
    unsigned int pfreq_l;

    por_freq = sptr->swpm - sptr->swpd;
    if (por_freq < 0)
    {
        por_freq = -por_freq;
        pfreq_l = por_freq & 0xFF;
        pfreq_h = por_freq >> 8;
        pfreq_l = (pfreq_l * sptr->swsc) >> 8;
        pfreq_h *= sptr->swsc;
        por_freq = pfreq_h + pfreq_l;

        if (por_freq == 0)
        {
            por_freq = 1;
        }
        por_freq = -por_freq;
    }
    else if (por_freq == 0)
    {
        sptr->swpc = 0;
    }
    else
    {
        pfreq_l = por_freq & 0xFF;
        pfreq_h = por_freq >> 8;
        pfreq_l = (pfreq_l * sptr->swsc) >> 8;
        pfreq_h *= sptr->swsc;
        por_freq = pfreq_h + pfreq_l;

        if (por_freq == 0)
        {
            por_freq = 1;
        }
    }

    sptr->swpd += por_freq;
}

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
    if (0x7FFF >= tmp)
    {
        vib_data = ((tmp >> 7) & 0xFE);
        vib_data = (vib_data * tbl_data) >> 8;
    }
    else
    {
        vib_data = ((tmp >> 8) & 0x7F) + 2;
        vib_data = (vib_data * tbl_data) >> 1;
    }

    if ((unsigned char)sptr->vib_tbl_cnt >= 32u)
    {
        vib_data = -vib_data;
    }

    return vib_data;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
int vib_generate(int cnt)
{
    unsigned char vib_char;
    int           vib_data;

    if (cnt << 24 < 0)
    {
        vib_char = -cnt * 2;
        if ((-cnt << 25) < 0)
        {
            vib_char = -vib_char;
        }
        vib_data = ((sptr->vibd >> 8) & 0xff) * (vib_char / 4);
        vib_data = -vib_data;
    }
    else
    {
        vib_char = cnt * 2;
        if (cnt << 25 < 0)
        {
            vib_char = -vib_char;
        }
        vib_data = ((sptr->vibd >> 8) & 0xff) * (vib_char / 4);
    }
    if (sptr->vibdm < 0x8000)
    {
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

    if (!sptr->swpc)
    {
        mdata1 = mptr[3];
        if (mdata1 == SWP_SET)
        {
            sptr->swphc = mptr[2];
            sptr->swpc = mptr[1];
            bend_frq = mptr[0];
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
    int            rdm_data;
    int            fset_fg;
    unsigned int   depth;
    int            frq_data;

    if (sptr->vol != 0 && sptr->tred != 0 &&
        sptr->trehs == sptr->trehc)
    {
        sptr->trec +=
            (unsigned)(sptr->trecad * (char)sptr->tmpd) >> 8;

        if (sptr->trec < 0)
        {
            depth = sptr->tred * -sptr->trec;
        }
        else if (sptr->trec == 0)
        {
            depth = 1;
        }
        else
        {
            depth = sptr->tred * sptr->trec;
        }

        volxset(depth >> 8);
    }

    fset_fg = 0;
    frq_data = sptr->swpd;

    if (sptr->swpc != 0 && sptr->swphc == 0)
    {
        fset_fg = 1;

        if (sptr->swsk == 0)
        {
            sptr->swpd += sptr->swpad;
        }
        else
        {
            por_compute();
        }

        frq_data = sptr->swpd;
    }

    if (sptr->vibd != 0 && sptr->vibhs == sptr->vibhc)
    {
        sptr->vib_tmp_cnt += sptr->vibcad;
        if ((unsigned)sptr->vib_tmp_cnt >= 256)
        {
            sptr->vib_tmp_cnt &= 0xFF;
            frq_data += vib_compute();
            fset_fg = 1;
        }
    }

    rdm_data = random();

    if (rdm_data != 0)
    {
        fset_fg = 1;
        frq_data += rdm_data;
    }

    if (fset_fg)
    {
        freq_set(frq_data);
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
unsigned int random(void)
{
    unsigned int  frq_dt = 0;
    unsigned char temp2;

    if (sptr->rdms)
    {
        sptr->rdmc += sptr->rdms;
        if (sptr->rdmc > 256)
        {
            sptr->rdmc &= 255;
            sptr->rdmo++;
            sptr->rdmo &= 0x7F;
            temp2 = rdm_tbl[sptr->rdmo];
            frq_dt = rdm_tbl[sptr->rdmo + 1] << 8;
            frq_dt += temp2;
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
    if (sptr->tmpc)
    {
        if (!--sptr->tmpc)
        {
            sptr->tmpw = (unsigned char)sptr->tmpm << 8;
        }
        else
        {
            sptr->tmpw += sptr->tmpad;
        }
        sptr->tmp = (unsigned int)sptr->tmpw >> 8;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void volxset(unsigned char depth)
{
    int vol_data;
    int pvod_w;

    vol_data = sptr->vol;
    vol_data -= depth;
    vol_data += sptr->lp1_vol;
    vol_data += sptr->lp2_vol;
    if (vol_data < 0)
    {
        vol_data = 0;
    }
    else if (vol_data >= 128)
    {
        vol_data = 127;
    }
    pvod_w = (sptr->pvod >> 8) & 0xFF;
    vol_set(((pvod_w * vol_data) >> 8) & 0xFF);
}
