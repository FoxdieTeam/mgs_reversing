#include "SD/sd_incl.h"
#include "SD/sd_ext.h"

/* local inlines */
inline int  vib_compute_800865CC(void);
inline void por_compute_80086504(void);
inline void swpadset_80085F98(int xfreq);

void (*cntl_tbl_8009F7BC[128])(void) = {
    /* 0x00 */ no_cmd_80087A80,
    /* 0x01 */ no_cmd_80087A80,
    /* 0x02 */ no_cmd_80087A80,
    /* 0x03 */ no_cmd_80087A80,
    /* 0x04 */ no_cmd_80087A80,
    /* 0x05 */ no_cmd_80087A80,
    /* 0x06 */ no_cmd_80087A80,
    /* 0x07 */ no_cmd_80087A80,
    /* 0x08 */ no_cmd_80087A80,
    /* 0x09 */ no_cmd_80087A80,
    /* 0x0a */ no_cmd_80087A80,
    /* 0x0b */ no_cmd_80087A80,
    /* 0x0c */ no_cmd_80087A80,
    /* 0x0d */ no_cmd_80087A80,
    /* 0x0e */ no_cmd_80087A80,
    /* 0x0f */ no_cmd_80087A80,
    /* 0x10 */ no_cmd_80087A80,
    /* 0x11 */ no_cmd_80087A80,
    /* 0x12 */ no_cmd_80087A80,
    /* 0x13 */ no_cmd_80087A80,
    /* 0x14 */ no_cmd_80087A80,
    /* 0x15 */ no_cmd_80087A80,
    /* 0x16 */ no_cmd_80087A80,
    /* 0x17 */ no_cmd_80087A80,
    /* 0x18 */ no_cmd_80087A80,
    /* 0x19 */ no_cmd_80087A80,
    /* 0x1a */ no_cmd_80087A80,
    /* 0x1b */ no_cmd_80087A80,
    /* 0x1c */ no_cmd_80087A80,
    /* 0x1d */ no_cmd_80087A80,
    /* 0x1e */ no_cmd_80087A80,
    /* 0x1f */ no_cmd_80087A80,
    /* 0x20 */ no_cmd_80087A80,
    /* 0x21 */ no_cmd_80087A80,
    /* 0x22 */ no_cmd_80087A80,
    /* 0x23 */ no_cmd_80087A80,
    /* 0x24 */ no_cmd_80087A80,
    /* 0x25 */ no_cmd_80087A80,
    /* 0x26 */ no_cmd_80087A80,
    /* 0x27 */ no_cmd_80087A80,
    /* 0x28 */ no_cmd_80087A80,
    /* 0x29 */ no_cmd_80087A80,
    /* 0x2a */ no_cmd_80087A80,
    /* 0x2b */ no_cmd_80087A80,
    /* 0x2c */ no_cmd_80087A80,
    /* 0x2d */ no_cmd_80087A80,
    /* 0x2e */ no_cmd_80087A80,
    /* 0x2f */ no_cmd_80087A80,
    /* 0x30 */ no_cmd_80087A80,
    /* 0x31 */ no_cmd_80087A80,
    /* 0x32 */ no_cmd_80087A80,
    /* 0x33 */ no_cmd_80087A80,
    /* 0x34 */ no_cmd_80087A80,
    /* 0x35 */ no_cmd_80087A80,
    /* 0x36 */ no_cmd_80087A80,
    /* 0x37 */ no_cmd_80087A80,
    /* 0x38 */ no_cmd_80087A80,
    /* 0x39 */ no_cmd_80087A80,
    /* 0x3a */ no_cmd_80087A80,
    /* 0x3b */ no_cmd_80087A80,
    /* 0x3c */ no_cmd_80087A80,
    /* 0x3d */ no_cmd_80087A80,
    /* 0x3e */ no_cmd_80087A80,
    /* 0x3f */ no_cmd_80087A80,
    /* 0x40 */ no_cmd_80087A80,
    /* 0x41 */ no_cmd_80087A80,
    /* 0x42 */ no_cmd_80087A80,
    /* 0x43 */ no_cmd_80087A80,
    /* 0x44 */ no_cmd_80087A80,
    /* 0x45 */ no_cmd_80087A80,
    /* 0x46 */ no_cmd_80087A80,
    /* 0x47 */ no_cmd_80087A80,
    /* 0x48 */ no_cmd_80087A80,
    /* 0x49 */ no_cmd_80087A80,
    /* 0x4a */ no_cmd_80087A80,
    /* 0x4b */ no_cmd_80087A80,
    /* 0x4c */ no_cmd_80087A80,
    /* 0x4d */ no_cmd_80087A80,
    /* 0x4e */ no_cmd_80087A80,
    /* 0x4f */ no_cmd_80087A80,
    /* 0x50 */ tempo_set_800873CC,
    /* 0x51 */ tempo_move_800873E4,
    /* 0x52 */ sno_set_80086E38,
    /* 0x53 */ svl_set_80086E78,
    /* 0x54 */ svp_set_80086EB8,
    /* 0x55 */ vol_chg_8008756C,
    /* 0x56 */ vol_move_8008758C,
    /* 0x57 */ ads_set_80087904,
    /* 0x58 */ srs_set_8008798C,
    /* 0x59 */ rrs_set_800879E4,
    /* 0x5a */ no_cmd_80087A80,
    /* 0x5b */ no_cmd_80087A80,
    /* 0x5c */ no_cmd_80087A80,
    /* 0x5d */ pan_set_80086F00,
    /* 0x5e */ pan_move_80086F50,
    /* 0x5f */ trans_set_8008750C,
    /* 0x60 */ detune_set_80087730,
    /* 0x61 */ vib_set_80087018,
    /* 0x62 */ vib_change_80087120,
    /* 0x63 */ rdm_set_8008716C,
    /* 0x64 */ swp_set_8008774C,
    /* 0x65 */ sws_set_800876D4,
    /* 0x66 */ por_set_80087670,
    /* 0x67 */ lp1_start_800871B4,
    /* 0x68 */ lp1_end_800871E0,
    /* 0x69 */ lp2_start_800872C0,
    /* 0x6a */ lp2_end_800872EC,
    /* 0x6b */ l3s_set_8008736C,
    /* 0x6c */ l3e_set_80087384,
    /* 0x6d */ kakko_start_80087834,
    /* 0x6e */ kakko_end_80087854,
    /* 0x6f */ no_cmd_80087A80,
    /* 0x70 */ no_cmd_80087A80,
    /* 0x71 */ use_set_80086EF8,
    /* 0x72 */ rest_set_80086D18,
    /* 0x73 */ tie_set_80086D9C,
    /* 0x74 */ echo_set1_80087754,
    /* 0x75 */ echo_set2_8008775C,
    /* 0x76 */ eon_set_80087764,
    /* 0x77 */ eof_set_800877CC,
    /* 0x78 */ no_cmd_80087A80,
    /* 0x79 */ no_cmd_80087A80,
    /* 0x7a */ no_cmd_80087A80,
    /* 0x7b */ no_cmd_80087A80,
    /* 0x7c */ no_cmd_80087A80,
    /* 0x7d */ no_cmd_80087A80,
    /* 0x7e */ no_cmd_80087A80,
    /* 0x7f */ block_end_80087A58
};

unsigned char rdm_tbl_8009F9BC[129] = {
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

unsigned char VIBX_TBL_8009FA40[32] = {
      0, 32,   56,  80, 104, 128, 144, 160,
    176, 192, 208, 224, 232, 240, 240, 248,
    255, 248, 244, 240, 232, 224, 208, 192,
    176, 160, 144, 128, 104,  80,  56,  32
};


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

    if (cnt << 24 < 0)
    {
        vib_char = -cnt * 2;
        if ((-cnt << 25) < 0)
        {
            vib_char = -vib_char;
        }
        vib_data = ((char*)&sptr_800C057C->vibd)[1] * (vib_char / 4);
        vib_data = -vib_data;
    }
    else
    {
        vib_char = cnt * 2;
        if (cnt << 25 < 0)
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
