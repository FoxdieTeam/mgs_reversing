#include "sd_incl.h"
#include "sd_ext.h"

void rest_set(void)
{
    sptr->rest_fg = 1;
    keyoff();
    sptr->ngs = mdata2;
    sptr->ngg = 0;
    sptr->vol = 0;
    sptr->ngc = sptr->ngs;
    sptr->ngo = 0;
}

void tie_set(void)
{
    int temp1;

    sptr->rest_fg = 1;
    sptr->ngs = mdata2;
    sptr->ngg = mdata3;
    sptr->ngc = sptr->ngs;
    temp1 = (sptr->ngg * sptr->ngc) / 100;
    if (!temp1)
    {
       temp1 = 1;
    }

    sptr->ngo = temp1;
}

void sno_set(void)
{
    sptr->snos = mdata2;
    keyoff();
    tone_set(mdata2);
}

void svl_set(void)
{
    sptr->snos = mdata2;
    keyoff();
    tone_set(mdata2);
}

void svp_set(void)
{
    sptr->snos = mdata2;
    keyoff();
    tone_set(mdata2);
}

void use_set(void)
{
    /* do nothing */
}

void pan_set(void)
{
    sptr->panmod = mdata2;
    sptr->panf = mdata3 + 20;
    sptr->pand = sptr->panf << 8;
    sptr->panc = 0;
}

void pan_move(void)
{
    unsigned char pand_shift;
    int pan_data;

    sptr->panc = mdata2;
    pand_shift = (mdata3 + 0x14);
    sptr->panm = pand_shift << 8;
    pan_data = pand_shift - sptr->panf;

    if (pan_data < 0)
    {
        sptr->panad = -(((-pan_data) << 8) / (unsigned int)mdata2);
        if (sptr->panad < -2032)
        {
            sptr->panad = -2032;
        }
    }
    else
    {
        sptr->panad = (pan_data << 8) / (unsigned int)mdata2;
        if (sptr->panad > 2032)
        {
            sptr->panad = 2032;
        }

    }
}

void vib_set(void)
{
    sptr->vibhs = mdata2;
    sptr->vibcad = mdata3;
    if (sptr->vibcad < 64)
    {
        if (sptr->vibcad < 32)
        {
            sptr->vib_tc_ofst = 1;
            sptr->vibcad = sptr->vibcad << 3;
        }
        else
        {
            sptr->vib_tc_ofst = 2;
            sptr->vibcad = sptr->vibcad << 2;
        }
    }
    else
    {
        if (sptr->vibcad < 128)
        {
            sptr->vib_tc_ofst = 4;
            sptr->vibcad = sptr->vibcad << 1;
        }
        else if (sptr->vibcad != 255)
        {
            sptr->vib_tc_ofst = 8;
        }
        else
        {
            sptr->vib_tc_ofst = 16;
        }
    }

    sptr->vibd = mdata4 << 8;
    sptr->vibdm = mdata4 << 8;
}

void vib_change(void)
{
    sptr->vibcs = mdata2;
    sptr->vibad = sptr->vibdm / (unsigned int)mdata2;
}

void rdm_set(void)
{
    sptr->rdms = mdata2;
    sptr->rdmd = (mdata3 << 8) + mdata4;
    sptr->rdmc = 0;
    sptr->rdmo = 0;
}

void lp1_start(void)
{
    sptr->lp1_addr = mptr;
    sptr->lp1_cnt = 0;
    sptr->lp1_freq = 0;
    sptr->lp1_vol = 0;
}

void lp1_end(void)
{
    char v1;

    if (stop_jouchuu_se && !mdata2)
    {
        sptr->lp1_vol = 0;
        sptr->lp1_freq = 0;
        ++stop_jouchuu_se;
    }
    else
    {
        v1 = sptr->lp1_cnt + 1;
        sptr->lp1_cnt = v1;

        if (v1 != mdata2 || v1  == 0)
        {
            sptr->lp1_vol += (signed char)mdata3;
            sptr->lp1_freq += (signed char)mdata4 * 8;
            mptr = sptr->lp1_addr;
        }
        else
        {
            sptr->lp1_vol = 0;
            sptr->lp1_freq = 0;
        }
    }
}

void lp2_start(void)
{
    sptr->lp2_addr = mptr;
    sptr->lp2_cnt = 0;
    sptr->lp2_freq = 0;
    sptr->lp2_vol = 0;
}

void lp2_end(void)
{
    unsigned char cnt;
    cnt = sptr->lp2_cnt + 1;
    sptr->lp2_cnt = cnt;
    if (cnt != mdata2 || !cnt)
    {
        sptr->lp2_vol += (signed char)mdata3;
        sptr->lp2_freq +=  8 * (signed char)mdata4;
        mptr =  sptr->lp2_addr;
    }
}

void l3s_set(void)
{
    sptr->lp3_addr = mptr;
}

void l3e_set(void)
{
    if (sptr->lp3_addr)
    {
        mptr = sptr->lp3_addr;
    }
    else
    {
        block_end();
    }
}

void tempo_set(void)
{
    sptr->tmp = mdata2;
}

void tempo_move(void)
{
    int tmp_data;

    sptr->tmpc = mdata2;
    sptr->tmpm = mdata3;
    sptr->tmpw = sptr->tmp << 8;

    tmp_data = (unsigned char)sptr->tmpm - (unsigned char)sptr->tmp;
    if (tmp_data < 0)
    {
        if (tmp_data < -127)
        {
            tmp_data = -127;
        }
        sptr->tmpad = -((-tmp_data << 8) / (unsigned char)sptr->tmpc);
        if ((unsigned int)sptr->tmpad < -2032) // madness, but works
        {
            sptr->tmpad = -2032;
        }

    }
    else
    {
        if (tmp_data > 127)
        {
            tmp_data = 127;
        }

        sptr->tmpad =  (tmp_data << 8) / (unsigned char)sptr->tmpc;
        if ((unsigned int)sptr->tmpad > 0x7F0)
        {
            sptr->tmpad = 0x7F0;
        }
    }
}

void trans_set(void)
{
    sptr->ptps = (signed char)mdata2;
}

void tre_set(void)
{
    sptr->trehs = mdata2;
    sptr->trecad = mdata3;
    sptr->tred = mdata4;
}

void vol_chg(void)
{
    sptr->pvod = mdata2 << 8;
    sptr->pvoc = 0;
}

void vol_move(void)
{
    int vol_data;

    sptr->pvoc = mdata2;
    sptr->pvom = mdata3;
    vol_data = (mdata3 << 8);
    vol_data = vol_data - sptr->pvod;
    if (vol_data < 0)
    {
        sptr->pvoad = -(-vol_data / sptr->pvoc);
        if (sptr->pvoad < -2032)
        {
            sptr->pvoad = -2032;
        }
    }
    else
    {
        sptr->pvoad = vol_data / sptr->pvoc;
        if (sptr->pvoad > 0x7F0)
        {
            sptr->pvoad = 0x7F0;
        }

    }
}

void por_set(void)
{
    sptr->swshc = 0;
    sptr->swsc = mdata2;
    if (!mdata2)
    {
        sptr->swsk = 0;
    }
    else
    {
        sptr->swsk = 1;
    }
}

void sws_set(void)
{
    sptr->swsk = 0;
    sptr->swshc = mdata2;
    sptr->swsc = mdata3;
    sptr->swss = mdata4 << 8;
}

void detune_set(void)
{
    sptr->tund = (signed char)mdata2 << 2;
}

void swp_set(void)
{
    /* do nothing */
}

void echo_set1(void)
{
    /* do nothing */
}

void echo_set2(void)
{
    /* do nothing */
}

void eon_set(void)
{
    if ((unsigned int)(mtrack - 13) < 8 && !se_playing[mtrack - 13].kind)
    {
        eons |= spu_ch_tbl[mtrack + 1];
    }
}

void eof_set(void)
{
    if ((unsigned int)(mtrack - 13) < 8 && !se_playing[mtrack - 13].kind)
    {
        eoffs |= spu_ch_tbl[mtrack + 1];
    }
}

void kakko_start(void)
{
    sptr->kak1ptr = mptr;
    sptr->kakfg = 0;
}

void kakko_end(void)
{
    switch (sptr->kakfg)
    {
    case 0:
        sptr->kakfg++;
        break;

    case 1:
        sptr->kakfg++;
        sptr->kak2ptr = mptr;
        mptr = sptr->kak1ptr;
        break;

    case 2:
        sptr->kakfg--;
        mptr = sptr->kak2ptr;
        break;
    }
}

void env_set(void)
{
    /* do nothing */
}

void ads_set(void)
{
    spu_tr_wk[mtrack].a_mode = 1;
    spu_tr_wk[mtrack].ar = ~mdata2 & 0x7F;
    spu_tr_wk[mtrack].dr = ~mdata3 & 0xF;
    spu_tr_wk[mtrack].sl = mdata4 & 0xF;
    spu_tr_wk[mtrack].env1_fg = 1;
}

void srs_set(void)
{
    spu_tr_wk[mtrack].s_mode = 3;
    spu_tr_wk[mtrack].sr = ~mdata2 & 0x7F;
    spu_tr_wk[mtrack].env2_fg = 1;
}

void rrs_set(void)
{
    const short flags = ~mdata2 & 0x1F;
    spu_tr_wk[mtrack].r_mode = 3;
    spu_tr_wk[mtrack].rr = flags;
    sptr->rrd = flags;
    spu_tr_wk[mtrack].env3_fg = 1;
}

void pm_set(void)
{
    /* do nothing */
}

void jump_set(void)
{
    /* do nothing */
}

void block_end(void)
{
    keyoffs |= keyd;
}

void no_cmd(void)
{
    /* do nothing */
}
