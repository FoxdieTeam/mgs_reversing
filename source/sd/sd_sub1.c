#include "sd_incl.h"
#include "sd_ext.h"

/* local inlines */
inline int  vib_compute(void);
inline void por_compute(void);
inline void swpadset(int xfreq);

void (*cntl_tbl[128])(void) = {
    /* 0x00 */ no_cmd,
    /* 0x01 */ no_cmd,
    /* 0x02 */ no_cmd,
    /* 0x03 */ no_cmd,
    /* 0x04 */ no_cmd,
    /* 0x05 */ no_cmd,
    /* 0x06 */ no_cmd,
    /* 0x07 */ no_cmd,
    /* 0x08 */ no_cmd,
    /* 0x09 */ no_cmd,
    /* 0x0a */ no_cmd,
    /* 0x0b */ no_cmd,
    /* 0x0c */ no_cmd,
    /* 0x0d */ no_cmd,
    /* 0x0e */ no_cmd,
    /* 0x0f */ no_cmd,
    /* 0x10 */ no_cmd,
    /* 0x11 */ no_cmd,
    /* 0x12 */ no_cmd,
    /* 0x13 */ no_cmd,
    /* 0x14 */ no_cmd,
    /* 0x15 */ no_cmd,
    /* 0x16 */ no_cmd,
    /* 0x17 */ no_cmd,
    /* 0x18 */ no_cmd,
    /* 0x19 */ no_cmd,
    /* 0x1a */ no_cmd,
    /* 0x1b */ no_cmd,
    /* 0x1c */ no_cmd,
    /* 0x1d */ no_cmd,
    /* 0x1e */ no_cmd,
    /* 0x1f */ no_cmd,
    /* 0x20 */ no_cmd,
    /* 0x21 */ no_cmd,
    /* 0x22 */ no_cmd,
    /* 0x23 */ no_cmd,
    /* 0x24 */ no_cmd,
    /* 0x25 */ no_cmd,
    /* 0x26 */ no_cmd,
    /* 0x27 */ no_cmd,
    /* 0x28 */ no_cmd,
    /* 0x29 */ no_cmd,
    /* 0x2a */ no_cmd,
    /* 0x2b */ no_cmd,
    /* 0x2c */ no_cmd,
    /* 0x2d */ no_cmd,
    /* 0x2e */ no_cmd,
    /* 0x2f */ no_cmd,
    /* 0x30 */ no_cmd,
    /* 0x31 */ no_cmd,
    /* 0x32 */ no_cmd,
    /* 0x33 */ no_cmd,
    /* 0x34 */ no_cmd,
    /* 0x35 */ no_cmd,
    /* 0x36 */ no_cmd,
    /* 0x37 */ no_cmd,
    /* 0x38 */ no_cmd,
    /* 0x39 */ no_cmd,
    /* 0x3a */ no_cmd,
    /* 0x3b */ no_cmd,
    /* 0x3c */ no_cmd,
    /* 0x3d */ no_cmd,
    /* 0x3e */ no_cmd,
    /* 0x3f */ no_cmd,
    /* 0x40 */ no_cmd,
    /* 0x41 */ no_cmd,
    /* 0x42 */ no_cmd,
    /* 0x43 */ no_cmd,
    /* 0x44 */ no_cmd,
    /* 0x45 */ no_cmd,
    /* 0x46 */ no_cmd,
    /* 0x47 */ no_cmd,
    /* 0x48 */ no_cmd,
    /* 0x49 */ no_cmd,
    /* 0x4a */ no_cmd,
    /* 0x4b */ no_cmd,
    /* 0x4c */ no_cmd,
    /* 0x4d */ no_cmd,
    /* 0x4e */ no_cmd,
    /* 0x4f */ no_cmd,
    /* 0x50 */ tempo_set,
    /* 0x51 */ tempo_move,
    /* 0x52 */ sno_set,
    /* 0x53 */ svl_set,
    /* 0x54 */ svp_set,
    /* 0x55 */ vol_chg,
    /* 0x56 */ vol_move,
    /* 0x57 */ ads_set,
    /* 0x58 */ srs_set,
    /* 0x59 */ rrs_set,
    /* 0x5a */ no_cmd,
    /* 0x5b */ no_cmd,
    /* 0x5c */ no_cmd,
    /* 0x5d */ pan_set,
    /* 0x5e */ pan_move,
    /* 0x5f */ trans_set,
    /* 0x60 */ detune_set,
    /* 0x61 */ vib_set,
    /* 0x62 */ vib_change,
    /* 0x63 */ rdm_set,
    /* 0x64 */ swp_set,
    /* 0x65 */ sws_set,
    /* 0x66 */ por_set,
    /* 0x67 */ lp1_start,
    /* 0x68 */ lp1_end,
    /* 0x69 */ lp2_start,
    /* 0x6a */ lp2_end,
    /* 0x6b */ l3s_set,
    /* 0x6c */ l3e_set,
    /* 0x6d */ kakko_start,
    /* 0x6e */ kakko_end,
    /* 0x6f */ no_cmd,
    /* 0x70 */ no_cmd,
    /* 0x71 */ use_set,
    /* 0x72 */ rest_set,
    /* 0x73 */ tie_set,
    /* 0x74 */ echo_set1,
    /* 0x75 */ echo_set2,
    /* 0x76 */ eon_set,
    /* 0x77 */ eof_set,
    /* 0x78 */ no_cmd,
    /* 0x79 */ no_cmd,
    /* 0x7a */ no_cmd,
    /* 0x7b */ no_cmd,
    /* 0x7c */ no_cmd,
    /* 0x7d */ no_cmd,
    /* 0x7e */ no_cmd,
    /* 0x7f */ block_end
};

unsigned char rdm_tbl[129] = {
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


int sound_sub(void)
{
    int          fade2_shifted;
    unsigned int tmpd;

    key_fg = 0;
    sptr->tmpd += sptr->tmp;
    if ((unsigned int)mtrack < 0xD)
    {
        if (sng_kaihi_time)
        {
            fade2_shifted = sng_kaihi_time >> 5;
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
        mptr += 4;

        if ((char)mdata1 >= 128)
        {
            cntl_tbl[mdata1 - 128]();
            if (mdata1 == 0xF2 || mdata1 == 0xF3 || mdata1 == 0xFF)
            {
                read_fg = 0;
            }

            if (mdata1 == 0xFF)
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

void adsr_reset(void)
{
    spu_tr_wk[mtrack].rr = sptr->rrd;
    spu_tr_wk[mtrack].env3_fg = 1;
}

void note_compute(void)
{
    int      x;
    int      swp_ex;
    SOUND_W *pSound;

    if (mdata1 >= 0x48)
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

void key_cut_off(void)
{
    if (sptr->rrd > 7)
    {
        spu_tr_wk[mtrack].rr = 7;
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

void bendch(void)
{
    int bend_frq;

    if (!sptr->swpc)
    {
        mdata1 = mptr[3];
        if (mdata1 == 0xe4)
        {
            sptr->swphc = mptr[2];
            sptr->swpc = mptr[1];
            bend_frq = mptr[0];
            mptr += 4;

            bend_frq = (bend_frq + sptr->ptps) << 8;
            bend_frq += sptr->tund;

            swpadset(bend_frq);
        }
    }
}

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
