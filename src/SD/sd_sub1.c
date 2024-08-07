#include "SD/sd.h"

unsigned char         rdm_tbl_8009F9BC[129];
extern SOUND_W       *sptr_800C057C;
extern SPU_TRACK_REG  spu_tr_wk_800C0658[23];
extern unsigned int   mtrack_800BF1EC;
extern unsigned int   mdata1_800BF0D0;
extern int            mdata2_800BF0D4;
extern int            mdata3_800BF0D8;
extern int            mdata4_800BF0DC;
extern int            sng_fade_in_2_800C0BC0;
extern int            key_fg_800BF1B0;
extern unsigned char *mptr_800C0570;

extern void (*cntl_tbl_8009F7BC[128])(void);
extern unsigned char VIBX_TBL_8009FA40[32];

unsigned int random_80086B84(void);
void note_set_80085CD8(void);
void tempo_ch_80086C08(void);
void keych_80086280(void);
int  tx_read_80085B84(void);
void bendch_80086734(void);
void vol_compute_8008604C(void);
void note_cntl_8008686C(void);
void keyon_80087F58(void);

void note_compute_80085DE0(void);
inline int  vib_compute_800865CC(void);
inline void por_compute_80086504(void);
inline void swpadset_80085F98(int xfreq);

int sound_sub_80085A50(void)
{
    int          fade2_shifted; // $a0
    unsigned int tmpd;          // $a1

    key_fg_800BF1B0 = 0;
    sptr_800C057C->tmpd += sptr_800C057C->tmp;
    if ((unsigned int)mtrack_800BF1EC < 0xD)
    {
        if (sng_fade_in_2_800C0BC0)
        {
            fade2_shifted = sng_fade_in_2_800C0BC0 >> 5;
            if (fade2_shifted < (unsigned char)sptr_800C057C->tmp)
            {
                sptr_800C057C->tmpd -= fade2_shifted;
            }
        }
    }

    tmpd = sptr_800C057C->tmpd;
    if (tmpd >= 256)
    {
        sptr_800C057C->tmpd = tmpd & 0xff;
        --sptr_800C057C->ngc;

        if (sptr_800C057C->ngc)
        {
            keych_80086280();
        }
        else if (tx_read_80085B84())
        {
            keyoff_80087F80();
            return 1;
        }
        tempo_ch_80086C08();
        bendch_80086734();
        vol_compute_8008604C();
    }
    else
    {
        note_cntl_8008686C();
    }

    if (key_fg_800BF1B0)
    {
        keyon_80087F58();
        return 0;
    }
    return 0;
}

int tx_read_80085B84(void)
{
    int read_fg; // $s0
    int loop_count; // $s1

    loop_count = 0;
    read_fg = 1;
    while (read_fg)
    {
        loop_count++;
        if (loop_count == 256)
        {
            return 1;
        }

        mdata1_800BF0D0 = mptr_800C0570[3];
        if (!mdata1_800BF0D0)
        {
            return 1;
        }
        mdata2_800BF0D4 = mptr_800C0570[2];
        mdata3_800BF0D8 = mptr_800C0570[1];
        mdata4_800BF0DC = mptr_800C0570[0];
        mptr_800C0570 += 4;

        if ((char)mdata1_800BF0D0 >= 128)
        {
            cntl_tbl_8009F7BC[mdata1_800BF0D0 - 128]();
            if (mdata1_800BF0D0 == 0xF2 || mdata1_800BF0D0 == 0xF3 || mdata1_800BF0D0 == 0xFF)
            {
                read_fg = 0;
            }

            if (mdata1_800BF0D0 == 0xFF)
            {
                return 1;
            }
        }
        else
        {
            if ((unsigned char)sptr_800C057C->ngg < 0x64 && mdata4_800BF0DC)
            {
                key_fg_800BF1B0 = 1;
            }
            read_fg = 0;
            sptr_800C057C->rest_fg = 0;
            note_set_80085CD8();
        }
    }
    return 0;
}

void note_set_80085CD8(void)
{
    unsigned int x;

    sptr_800C057C->ngs = mdata2_800BF0D4;
    sptr_800C057C->ngg = mdata3_800BF0D8;
    sptr_800C057C->vol = (mdata4_800BF0DC & 0x7F);
    note_compute_80085DE0();
    sptr_800C057C->ngc = sptr_800C057C->ngs;
    x = (sptr_800C057C->ngg * sptr_800C057C->ngc) / 100;

    if (!x)
    {
        x = 1;
    }
    sptr_800C057C->ngo = x;
}

void adsr_reset_80085D98(void)
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].rr = sptr_800C057C->rrd;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;
}

void note_compute_80085DE0(void)
{
    int      x;
    int      swp_ex;
    SOUND_W *pSound;

    if (mdata1_800BF0D0 >= 0x48)
    {
        drum_set_80088694(mdata1_800BF0D0);
        x = 0x24;
    }
    else
    {
        x = mdata1_800BF0D0;
    }

    x += sptr_800C057C->ptps;
    x = (x << 8) + sptr_800C057C->tund;
    x = x + sptr_800C057C->lp1_freq + sptr_800C057C->lp2_freq;

    while (x >= 0x6000)
    {
        x -= 0x6000;
    }

    swp_ex = sptr_800C057C->swpd;

    pSound = sptr_800C057C;
    pSound->vibcc = 0;
    pSound->vibhc = 0;
    pSound->swpd = x;

    sptr_800C057C->vib_tmp_cnt = 0;
    sptr_800C057C->vib_tbl_cnt = 0;

    pSound = sptr_800C057C;
    pSound->trehc = 0;
    pSound->trec = 0;
    pSound->vibd = 0;

    spu_tr_wk_800C0658[mtrack_800BF1EC].rr = sptr_800C057C->rrd;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;

    sptr_800C057C->swpc = sptr_800C057C->swsc;

    if (sptr_800C057C->swpc != 0)
    {
        sptr_800C057C->swphc = sptr_800C057C->swshc;

        if (sptr_800C057C->swsk == 0)
        {
            x = sptr_800C057C->swpd;

            if (sptr_800C057C->swss >= 0x7F01)
            {
                sptr_800C057C->swpd += 0x10000 - (sptr_800C057C->swss & 0xFFFF);
            }
            else
            {
                sptr_800C057C->swpd -= sptr_800C057C->swss;
            }

            swpadset_80085F98(x);
        }
        else
        {
            sptr_800C057C->swpm = sptr_800C057C->swpd;
            sptr_800C057C->swpd = swp_ex;
        }
    }

    freq_set_800885D4(sptr_800C057C->swpd);
}

inline void swpadset_80085F98(int xfreq)
{
    unsigned int flame_dat; // $lo

    if (sptr_800C057C->swpc)
    {
        flame_dat = sptr_800C057C->swpc << 8;
        flame_dat = flame_dat / sptr_800C057C->tmp;
        if (xfreq < 0)
        {
            xfreq = 0;
        }
        else if (xfreq >= 0x6000)
        {
            xfreq = 0x5FFF;
        }

        sptr_800C057C->swpm = xfreq;

        xfreq -= sptr_800C057C->swpd;

        if (xfreq < 0)
        {
            xfreq = -xfreq / flame_dat;
            sptr_800C057C->swpad = -xfreq;
        }
        else
        {
            sptr_800C057C->swpad = xfreq / flame_dat;
        }
    }
}

void vol_compute_8008604C(void)
{
    int          mult;
    unsigned int depth;

    if (sptr_800C057C->pvoc != 0)
    {
        if (--sptr_800C057C->pvoc == 0)
        {
            sptr_800C057C->pvod = sptr_800C057C->pvom << 8;
        }
        else
        {
            sptr_800C057C->pvod += sptr_800C057C->pvoad;
        }
    }

    if (sptr_800C057C->vol != 0)
    {
        if (sptr_800C057C->tred == 0)
        {
            depth = 0;
        }
        else
        {
            if (sptr_800C057C->trehs == sptr_800C057C->trehc)
            {
                sptr_800C057C->trec += sptr_800C057C->trecad;
                mult = sptr_800C057C->trec;
                if (mult < 0)
                {
                    depth = sptr_800C057C->tred * -mult;
                }
                else if (mult == 0)
                {
                    depth = 1;
                }
                else
                {
                    depth = sptr_800C057C->tred * mult;
                }
            }
            else
            {
                sptr_800C057C->trehc++;
                depth = 0;
            }
        }
        volxset_80086C98(depth >> 8);
    }
    pan_generate_80086198();
}

void pan_generate_80086198(void)
{
    if (sptr_800C057C->panc)
    {
        if (!--sptr_800C057C->panc)
        {
            sptr_800C057C->pand = sptr_800C057C->panm;
        }
        else
        {
            sptr_800C057C->pand += sptr_800C057C->panad;
        }
        sptr_800C057C->panf = sptr_800C057C->pand >> 8;
    }
}

void key_cut_off_80086220(void)
{
    if (sptr_800C057C->rrd > 7)
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].rr = 7;
        spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;
    }
}

void keych_80086280(void)
{
    int swpc;   // $a0
    int set_fg; // $s1
    int swphc;  // $v0
    int vibdm; // $a1
    int vib_data;       // $s0
    int vibhc; // $v1
    int rdm_data;       // $v0

    if ((unsigned char)sptr_800C057C->ngg < 0x64u && sptr_800C057C->ngc == 1 &&
         (unsigned short)sptr_800C057C->rrd >= 8u)
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].rr = 7;
        spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;
    }

    if (sptr_800C057C->ngo)
    {
        sptr_800C057C->ngo--;
        if (!sptr_800C057C->ngo)
        {
            keyoff_80087F80();
        }
    }

    set_fg = 0;

    swpc = sptr_800C057C->swpc;
    if (swpc)
    {
        swphc = (unsigned char)sptr_800C057C->swphc;
        if (swphc)
        {
            sptr_800C057C->swphc--;
        }
        else
        {
            if (!sptr_800C057C->swsk)
            {
                sptr_800C057C->swpc = swpc - 1;
                if (!((swpc - 1) & 0xFF))
                {
                    sptr_800C057C->swpd = sptr_800C057C->swpm;
                }
                else
                {
                    sptr_800C057C->swpd += sptr_800C057C->swpad;
                }
            }
            else
            {
                por_compute_80086504();
            }
            set_fg = 1;
        }
    }

    vibdm = sptr_800C057C->vibdm;
    vib_data = 0;

    if (vibdm)
    {
        vibhc = (unsigned char)sptr_800C057C->vibhc;
        if (vibhc != (unsigned char)sptr_800C057C->vibhs)
        {
            sptr_800C057C->vibhc = vibhc + 1;
        }
        else
        {
            if (sptr_800C057C->vibcc == sptr_800C057C->vibcs)
            {
                sptr_800C057C->vibd = vibdm;
            }
            else
            {
                if (sptr_800C057C->vibcc)
                {
                    sptr_800C057C->vibd =
                        sptr_800C057C->vibd + sptr_800C057C->vibad;
                }
                else
                {
                    sptr_800C057C->vibd = sptr_800C057C->vibad;
                }
                ++sptr_800C057C->vibcc;
            }
            sptr_800C057C->vib_tmp_cnt =
                sptr_800C057C->vib_tmp_cnt + sptr_800C057C->vibcad;
            if ((unsigned)sptr_800C057C->vib_tmp_cnt >= 256)
            {
                sptr_800C057C->vib_tmp_cnt = sptr_800C057C->vib_tmp_cnt & 0xFF;
                vib_data = vib_compute_800865CC();
                set_fg = 1;
            }
        }
    }

    rdm_data = random_80086B84();
    if (rdm_data)
    {
        vib_data += rdm_data;
        set_fg = 1;
    }

    if (set_fg)
    {
        freq_set_800885D4(sptr_800C057C->swpd + vib_data);
    }
}

inline void por_compute_80086504(void)
{
    int          por_freq; // $a1
    unsigned int pfreq_h;
    unsigned int pfreq_l;

    por_freq = sptr_800C057C->swpm - sptr_800C057C->swpd;
    if (por_freq < 0)
    {
        por_freq = -por_freq;
        pfreq_l = por_freq & 0xFF;
        pfreq_h = por_freq >> 8;
        pfreq_l = (pfreq_l * sptr_800C057C->swsc) >> 8;
        pfreq_h *= sptr_800C057C->swsc;
        por_freq = pfreq_h + pfreq_l;

        if (por_freq == 0)
        {
            por_freq = 1;
        }
        por_freq = -por_freq;
    }
    else if (por_freq == 0)
    {
        sptr_800C057C->swpc = 0;
    }
    else
    {
        pfreq_l = por_freq & 0xFF;
        pfreq_h = por_freq >> 8;
        pfreq_l = (pfreq_l * sptr_800C057C->swsc) >> 8;
        pfreq_h *= sptr_800C057C->swsc;
        por_freq = pfreq_h + pfreq_l;

        if (por_freq == 0)
        {
            por_freq = 1;
        }
    }

    sptr_800C057C->swpd += por_freq;
}

inline int vib_compute_800865CC(void)
{
    unsigned int tmp;  // $a0
    int          tbl_data; // $a1
    unsigned int vib_data; // $v1

    sptr_800C057C->vib_tbl_cnt += sptr_800C057C->vib_tc_ofst;
    sptr_800C057C->vib_tbl_cnt &= 0x3Fu;
    tbl_data = VIBX_TBL_8009FA40[sptr_800C057C->vib_tbl_cnt & 0x1F];

    tmp = sptr_800C057C->vibd;
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

    if ((unsigned char)sptr_800C057C->vib_tbl_cnt >= 32u)
    {
        vib_data = -vib_data;
    }

    return vib_data;
}

int vib_generate_80086694(int cnt)
{
    unsigned char vib_char;
    int           vib_data;

    if (cnt << 0x18 < 0)
    {
        vib_char = -cnt * 2;
        if ((-cnt << 0x19) < 0)
        {
            vib_char = -vib_char;
        }
        vib_data = ((char*)&sptr_800C057C->vibd)[1] * (vib_char / 4);
        vib_data = -vib_data;
    }
    else
    {
        vib_char = cnt * 2;
        if (cnt << 0x19 < 0)
        {
            vib_char = -vib_char;
        }
        vib_data = ((char*)&sptr_800C057C->vibd)[1] * (vib_char / 4);
    }
    if (*(unsigned int *)&sptr_800C057C->vibdm < 0x8000)
    {
        vib_data >>= 2;
    }
    return vib_data;
}

void bendch_80086734(void)
{
    int bend_frq;

    if (!sptr_800C057C->swpc)
    {
        mdata1_800BF0D0 = mptr_800C0570[3];
        if (mdata1_800BF0D0 == 0xe4)
        {
            sptr_800C057C->swphc = mptr_800C0570[2];
            sptr_800C057C->swpc = mptr_800C0570[1];
            bend_frq = mptr_800C0570[0];
            mptr_800C0570 += 4;

            bend_frq = (bend_frq + sptr_800C057C->ptps) << 8;
            bend_frq += sptr_800C057C->tund;

            swpadset_80085F98(bend_frq);
        }
    }
}

void note_cntl_8008686C(void)
{
    int            rdm_data;
    int            fset_fg;
    unsigned int   depth;
    int            frq_data;

    if (sptr_800C057C->vol != 0 && sptr_800C057C->tred != 0 &&
        sptr_800C057C->trehs == sptr_800C057C->trehc)
    {
        sptr_800C057C->trec +=
            (unsigned)(sptr_800C057C->trecad * (char)sptr_800C057C->tmpd) >> 8;

        if (sptr_800C057C->trec < 0)
        {
            depth = sptr_800C057C->tred * -sptr_800C057C->trec;
        }
        else if (sptr_800C057C->trec == 0)
        {
            depth = 1;
        }
        else
        {
            depth = sptr_800C057C->tred * sptr_800C057C->trec;
        }

        volxset_80086C98(depth >> 8);
    }

    fset_fg = 0;
    frq_data = sptr_800C057C->swpd;

    if (sptr_800C057C->swpc != 0 && sptr_800C057C->swphc == 0)
    {
        fset_fg = 1;

        if (sptr_800C057C->swsk == 0)
        {
            sptr_800C057C->swpd += sptr_800C057C->swpad;
        }
        else
        {
            por_compute_80086504();
        }

        frq_data = sptr_800C057C->swpd;
    }

    if (sptr_800C057C->vibd != 0 && sptr_800C057C->vibhs == sptr_800C057C->vibhc)
    {
        sptr_800C057C->vib_tmp_cnt += sptr_800C057C->vibcad;
        if ((unsigned)sptr_800C057C->vib_tmp_cnt >= 256)
        {
            sptr_800C057C->vib_tmp_cnt &= 0xFF;
            frq_data += vib_compute_800865CC();
            fset_fg = 1;
        }
    }

    rdm_data = random_80086B84();

    if (rdm_data != 0)
    {
        fset_fg = 1;
        frq_data += rdm_data;
    }

    if (fset_fg)
    {
        freq_set_800885D4(frq_data);
    }
}

unsigned int random_80086B84(void)
{
    unsigned int  frq_dt = 0; // $a1
    unsigned char temp2;

    if (sptr_800C057C->rdms)
    {
        sptr_800C057C->rdmc += sptr_800C057C->rdms;
        if (sptr_800C057C->rdmc > 256)
        {
            sptr_800C057C->rdmc &= 255;
            sptr_800C057C->rdmo++;
            sptr_800C057C->rdmo &= 0x7F;
            temp2 = rdm_tbl_8009F9BC[sptr_800C057C->rdmo];
            frq_dt = rdm_tbl_8009F9BC[sptr_800C057C->rdmo + 1] << 8;
            frq_dt += temp2;
            frq_dt &= sptr_800C057C->rdmd;
        }
    }
    return frq_dt;
}

void tempo_ch_80086C08(void)
{
    if (sptr_800C057C->tmpc)
    {
        if (!--sptr_800C057C->tmpc)
        {
            sptr_800C057C->tmpw = (unsigned char)sptr_800C057C->tmpm << 8;
        }
        else
        {
            sptr_800C057C->tmpw += sptr_800C057C->tmpad;
        }
        sptr_800C057C->tmp = (unsigned int)sptr_800C057C->tmpw >> 8;
    }
}

void volxset_80086C98(unsigned char depth)
{
    int vol_data; // $a1
    int pvod_w;

    vol_data = sptr_800C057C->vol;
    vol_data -= depth;
    vol_data += sptr_800C057C->lp1_vol;
    vol_data += sptr_800C057C->lp2_vol;
    if (vol_data < 0)
    {
        vol_data = 0;
    }
    else if (vol_data >= 128)
    {
        vol_data = 127;
    }
    pvod_w = (sptr_800C057C->pvod >> 8) & 0xFF;
    vol_set_80088320(((pvod_w * vol_data) >> 8) & 0xFF);
}
