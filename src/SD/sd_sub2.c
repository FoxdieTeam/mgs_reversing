#include "SD/sound.h"
#include "SD/sd_incl.h"

extern int keyoffs_800BF29C;
extern int keyd_800C0524;
extern SOUND_W* sptr_800C057C;
extern unsigned int mtrack_800BF1EC;
extern SPU_TRACK_REG spu_tr_wk_800C0658[];
extern int mdata2_800BF0D4;
extern int mdata3_800BF0D8;
extern int mdata4_800BF0DC;
extern unsigned char* mptr_800C0570;
extern int spu_ch_tbl_800A2AC8[]; /* in sd_wk.c */
extern int dword_800BF210;
extern SEPLAYTBL se_playing_800BF068[8];
extern int dword_800BF064;
extern int stop_jouchuu_se_800BF1A0;

void tone_set_80087FA8(unsigned char n);
void block_end_80087A58(void);

void rest_set_80086D18(void)
{
    sptr_800C057C->rest_fg = 1;
    keyoff_80087F80();
    sptr_800C057C->ngs = mdata2_800BF0D4;
    sptr_800C057C->ngg = 0;
    sptr_800C057C->vol = 0;
    sptr_800C057C->ngc = sptr_800C057C->ngs;
    sptr_800C057C->ngo = 0;
}

void tie_set_80086D9C(void)
{
    int temp1; // $v1

    sptr_800C057C->rest_fg = 1;
    sptr_800C057C->ngs = mdata2_800BF0D4;
    sptr_800C057C->ngg = mdata3_800BF0D8;
    sptr_800C057C->ngc = sptr_800C057C->ngs;
    temp1 = (sptr_800C057C->ngg * sptr_800C057C->ngc) / 100;
    if (!temp1)
    {
       temp1 = 1;
    }

    sptr_800C057C->ngo = temp1;
}

void sno_set_80086E38(void)
{
    sptr_800C057C->snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void svl_set_80086E78(void)
{
    sptr_800C057C->snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void svp_set_80086EB8(void)
{
    sptr_800C057C->snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void use_set_80086EF8(void)
{
    /* do nothing */
}

void pan_set_80086F00(void)
{
    sptr_800C057C->panmod = mdata2_800BF0D4;
    sptr_800C057C->panf = mdata3_800BF0D8 + 20;
    sptr_800C057C->pand = sptr_800C057C->panf << 8;
    sptr_800C057C->panc = 0;
}

void pan_move_80086F50(void)
{
    unsigned char pand_shift; // $v0
    int pan_data; // $v0

    sptr_800C057C->panc = mdata2_800BF0D4;
    pand_shift = (mdata3_800BF0D8 + 0x14);
    sptr_800C057C->panm = pand_shift << 8;
    pan_data = pand_shift - sptr_800C057C->panf;

    if (pan_data < 0)
    {
        sptr_800C057C->panad = -(((-pan_data) << 8) / (unsigned int)mdata2_800BF0D4);
        if (sptr_800C057C->panad < -2032)
        {
            sptr_800C057C->panad = -2032;
        }
    }
    else
    {
        sptr_800C057C->panad = (pan_data << 8) / (unsigned int)mdata2_800BF0D4;
        if (sptr_800C057C->panad > 2032)
        {
            sptr_800C057C->panad = 2032;
        }
        
    }
}

void vib_set_80087018(void)
{
    sptr_800C057C->vibhs = mdata2_800BF0D4;
    sptr_800C057C->vibcad = mdata3_800BF0D8;
    if (sptr_800C057C->vibcad < 64)
    {
        if (sptr_800C057C->vibcad < 32)
        {
            sptr_800C057C->vib_tc_ofst = 1;
            sptr_800C057C->vibcad = sptr_800C057C->vibcad << 3;
        }
        else
        {
            sptr_800C057C->vib_tc_ofst = 2;
            sptr_800C057C->vibcad = sptr_800C057C->vibcad << 2;
        }
    }
    else
    {
        if (sptr_800C057C->vibcad < 128)
        {
            sptr_800C057C->vib_tc_ofst = 4;
            sptr_800C057C->vibcad = sptr_800C057C->vibcad << 1;
        }
        else if (sptr_800C057C->vibcad != 255)
        {
            sptr_800C057C->vib_tc_ofst = 8;
        }
        else
        {
            sptr_800C057C->vib_tc_ofst = 16;
        }
    }

    sptr_800C057C->vibd = mdata4_800BF0DC << 8;
    sptr_800C057C->vibdm = mdata4_800BF0DC << 8;
}

void vib_change_80087120(void)
{
    sptr_800C057C->vibcs = mdata2_800BF0D4;
    sptr_800C057C->vibad = sptr_800C057C->vibdm / (unsigned int)mdata2_800BF0D4;
}

void rdm_set_8008716C(void)
{
    sptr_800C057C->rdms = mdata2_800BF0D4;
    sptr_800C057C->rdmd = (mdata3_800BF0D8 << 8) + mdata4_800BF0DC;
    sptr_800C057C->rdmc = 0;
    sptr_800C057C->rdmo = 0;
}

void lp1_start_800871B4(void)
{
    sptr_800C057C->lp1_addr = mptr_800C0570;
    sptr_800C057C->lp1_cnt = 0;
    sptr_800C057C->lp1_freq = 0;
    sptr_800C057C->lp1_vol = 0;
}

void lp1_end_800871E0(void)
{
    char v1;

    if (stop_jouchuu_se_800BF1A0 && !mdata2_800BF0D4)
    {
        sptr_800C057C->lp1_vol = 0;
        sptr_800C057C->lp1_freq = 0;
        ++stop_jouchuu_se_800BF1A0;
    }
    else
    {
        v1 = sptr_800C057C->lp1_cnt + 1;
        sptr_800C057C->lp1_cnt = v1;
        
        if (v1 != mdata2_800BF0D4 || v1  == 0)
        {
            sptr_800C057C->lp1_vol += (signed char)mdata3_800BF0D8;
            sptr_800C057C->lp1_freq += (signed char)mdata4_800BF0DC * 8;
            mptr_800C0570 = sptr_800C057C->lp1_addr;
        }
        else
        {
            sptr_800C057C->lp1_vol = 0;
            sptr_800C057C->lp1_freq = 0;
        }
    }
}

void lp2_start_800872C0(void)
{
    sptr_800C057C->lp2_addr = mptr_800C0570;
    sptr_800C057C->lp2_cnt = 0;
    sptr_800C057C->lp2_freq = 0;
    sptr_800C057C->lp2_vol = 0;
}

void lp2_end_800872EC(void)
{
    unsigned char cnt; // $v1
    cnt = sptr_800C057C->lp2_cnt + 1;
    sptr_800C057C->lp2_cnt = cnt;
    if (cnt != mdata2_800BF0D4 || !cnt)
    {
        sptr_800C057C->lp2_vol += (signed char)mdata3_800BF0D8;
        sptr_800C057C->lp2_freq +=  8 * (signed char)mdata4_800BF0DC;
        mptr_800C0570 =  sptr_800C057C->lp2_addr;
    }
}

void l3s_set_8008736C(void)
{
    sptr_800C057C->lp3_addr = mptr_800C0570;
}

void l3e_set_80087384(void)
{
    if (sptr_800C057C->lp3_addr)
    {
        mptr_800C0570 = sptr_800C057C->lp3_addr;
    }
    else
    {
        block_end_80087A58();
    }
}

void tempo_set_800873CC(void)
{
    sptr_800C057C->tmp = mdata2_800BF0D4;
}

void tempo_move_800873E4(void)
{
    int tmp_data; // $a0

    sptr_800C057C->tmpc = mdata2_800BF0D4;
    sptr_800C057C->tmpm = mdata3_800BF0D8;
    sptr_800C057C->tmpw = sptr_800C057C->tmp << 8;

    tmp_data = (unsigned char)sptr_800C057C->tmpm - (unsigned char)sptr_800C057C->tmp;
    if (tmp_data < 0)
    {
        if (tmp_data < -127)
        {
            tmp_data = -127;
        }
        sptr_800C057C->tmpad = -((-tmp_data << 8) / (unsigned char)sptr_800C057C->tmpc);
        if ((unsigned int)sptr_800C057C->tmpad < -2032) // madness, but works
        {
            sptr_800C057C->tmpad = -2032;
        }
       
    }
    else
    {
        if (tmp_data > 127)
        {
            tmp_data = 127;
        }

        sptr_800C057C->tmpad =  (tmp_data << 8) / (unsigned char)sptr_800C057C->tmpc;
        if ((unsigned int)sptr_800C057C->tmpad > 0x7F0)
        {
            sptr_800C057C->tmpad = 0x7F0;
        }
    }
}

void trans_set_8008750C(void)
{
    sptr_800C057C->ptps = (signed char)mdata2_800BF0D4;
}

void tre_set_80087524(void)
{
    sptr_800C057C->trehs = mdata2_800BF0D4;
    sptr_800C057C->trecad = mdata3_800BF0D8;
    sptr_800C057C->tred = mdata4_800BF0DC;
}

void vol_chg_8008756C(void)
{
    sptr_800C057C->pvod = mdata2_800BF0D4 << 8;
    sptr_800C057C->pvoc = 0;
}

void vol_move_8008758C(void)
{
    int vol_data; // $a0

    sptr_800C057C->pvoc = mdata2_800BF0D4;
    sptr_800C057C->pvom = mdata3_800BF0D8;
    vol_data = (mdata3_800BF0D8 << 8);
    vol_data = vol_data - sptr_800C057C->pvod;
    if (vol_data < 0)
    {
        sptr_800C057C->pvoad = -(-vol_data / sptr_800C057C->pvoc);
        if (sptr_800C057C->pvoad < -2032)
        {
            sptr_800C057C->pvoad = -2032;
        }
    }
    else
    {
        sptr_800C057C->pvoad = vol_data / sptr_800C057C->pvoc;
        if (sptr_800C057C->pvoad > 0x7F0)
        {
            sptr_800C057C->pvoad = 0x7F0;
        }
       
    }
}

void por_set_80087670(void)
{
    sptr_800C057C->swshc = 0;
    sptr_800C057C->swsc = mdata2_800BF0D4;
    if (!mdata2_800BF0D4)
    {
        sptr_800C057C->swsk = 0;
    }
    else
    {
        sptr_800C057C->swsk = 1;
    }
}

void sws_set_800876D4(void)
{
    sptr_800C057C->swsk = 0;
    sptr_800C057C->swshc = mdata2_800BF0D4;
    sptr_800C057C->swsc = mdata3_800BF0D8;
    sptr_800C057C->swss = mdata4_800BF0DC << 8;
}

void detune_set_80087730(void)
{
    sptr_800C057C->tund = (signed char)mdata2_800BF0D4 << 2;
}

void swp_set_8008774C(void)
{
    /* do nothing */
}

void echo_set1_80087754(void)
{
    /* do nothing */
}

void echo_set2_8008775C(void)
{
    /* do nothing */
}

void eon_set_80087764(void)
{
    if ((unsigned int)(mtrack_800BF1EC - 13) < 8 && !se_playing_800BF068[mtrack_800BF1EC - 13].kind)
    {
        dword_800BF064 |= spu_ch_tbl_800A2AC8[mtrack_800BF1EC + 1];
    }
}

void eof_set_800877CC(void)
{
    if ((unsigned int)(mtrack_800BF1EC - 13) < 8 && !se_playing_800BF068[mtrack_800BF1EC - 13].kind)
    {
        dword_800BF210 |= spu_ch_tbl_800A2AC8[mtrack_800BF1EC + 1];
    }
}

void kakko_start_80087834(void)
{
    sptr_800C057C->kak1ptr = mptr_800C0570;
    sptr_800C057C->kakfg = 0;
}

void kakko_end_80087854(void)
{
    switch (sptr_800C057C->kakfg)
    {
    case 0:
        sptr_800C057C->kakfg++;
        break;

    case 1:
        sptr_800C057C->kakfg++;
        sptr_800C057C->kak2ptr = mptr_800C0570;
        mptr_800C0570 = sptr_800C057C->kak1ptr;
        break;

    case 2:
        sptr_800C057C->kakfg--;
        mptr_800C0570 = sptr_800C057C->kak2ptr;
        break;
    }
}

void env_set_800878FC(void)
{
    /* do nothing */
}

void ads_set_80087904(void)
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].a_mode = 1;
    spu_tr_wk_800C0658[mtrack_800BF1EC].ar = ~mdata2_800BF0D4 & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].dr = ~mdata3_800BF0D8 & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].sl = mdata4_800BF0DC & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env1_fg = 1;
}

void srs_set_8008798C(void)
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].s_mode = 3;
    spu_tr_wk_800C0658[mtrack_800BF1EC].sr = ~mdata2_800BF0D4 & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env2_fg = 1;
}

void rrs_set_800879E4(void)
{
    const short flags = ~mdata2_800BF0D4 & 0x1F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].r_mode = 3;
    spu_tr_wk_800C0658[mtrack_800BF1EC].rr = flags;
    sptr_800C057C->rrd = flags;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;
}

void pm_set_80087A48(void)
{
    /* do nothing */
}

void jump_set_80087A50(void)
{
    /* do nothing */
}

void block_end_80087A58(void)
{
    keyoffs_800BF29C |= keyd_800C0524;
}

void no_cmd_80087A80(void)
{
    /* do nothing */
}
