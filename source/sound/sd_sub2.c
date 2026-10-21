#include "sd_incl.h"
#include "sd_ext.h"

/************************************************************************/
/*                      External Declarations                           */
/************************************************************************/
extern void tone_set(unsigned char n);
extern void keyoff(void);

/************************************************************************/
/*                      Function Declarations                           */
/************************************************************************/
void rest_set(void), sno_set(void), pan_set(void), pan_move(void);
void vib_set(void), rdm_set(void), lp1_start(void), lp1_end(void);
void lp2_start(void), lp2_end(void), tempo_set(void), tempo_move(void);
void trans_set(void), tre_set(void), vol_chg(void), vol_move(void);
void vib_change(void), por_set(void), sws_set(void), detune_set(void);
void swp_set(void), tie_set(void), echo_set1(void), echo_set2(void);
void kakko_start(void), kakko_end(void), env_set(void), pm_set(void);
void jump_set(void), no_cmd(void);
void ads_set(void), srs_set(void), rrs_set(void);
void eon_set(void), eof_set(void);
void l3s_set(void), l3e_set(void), svl_set(void), svp_set(void), use_set(void);
void block_end(void);

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void tie_set(void)
{
    int x;

    sptr->rest_fg = 1;
    sptr->ngs = mdata2;
    sptr->ngg = mdata3;
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void pan_set(void)
{
    sptr->panmod = mdata2;
    sptr->panf = mdata3 + 20;
    sptr->pand = sptr->panf << 8;
    sptr->panc = 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void pan_move(void)
{
    int pan_data;
    unsigned char pand_shift;

    sptr->panc = mdata2;
    pand_shift = (mdata3 + 20);
    sptr->panm = (pand_shift << 8);
    pan_data = (pand_shift - sptr->panf);

    if (pan_data < 0) {
        sptr->panad = -(((-pan_data) << 8) / mdata2);
        if (sptr->panad < -0x7F0) sptr->panad = -0x7F0;
    } else {
        sptr->panad = ((pan_data << 8) / mdata2);
        if (sptr->panad > 0x7F0) sptr->panad = 0x7F0;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vib_set(void)
{
    sptr->vibhs = mdata2;
    sptr->vibcad = mdata3;

    if (sptr->vibcad < 0x40) {
        if (sptr->vibcad < 0x20) {
            sptr->vib_tc_ofst = 1;
            sptr->vibcad = (sptr->vibcad << 3);
        }
        else {
            sptr->vib_tc_ofst = 2;
            sptr->vibcad = (sptr->vibcad << 2);
        }
    }
    else {
        if (sptr->vibcad < 0x80) {
            sptr->vib_tc_ofst = 4;
            sptr->vibcad = (sptr->vibcad << 1);
        }
        else {
            if (sptr->vibcad != 0xFF) {
                sptr->vib_tc_ofst = 8;
            }
            else {
                sptr->vib_tc_ofst = 16;
            }
        }
    }
    sptr->vibd = mdata4 << 8;
    sptr->vibdm = mdata4 << 8;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vib_change(void)
{
    sptr->vibcs = mdata2;
    sptr->vibad = (sptr->vibdm / mdata2);
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void rdm_set(void)
{
    sptr->rdms = mdata2;
    sptr->rdmd = (mdata3 << 8) + mdata4;
    sptr->rdmc = 0;
    sptr->rdmo = 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void lp1_start(void)
{
    sptr->lp1_addr = mptr;
    sptr->lp1_cnt = 0;
    sptr->lp1_freq = 0;
    sptr->lp1_vol = 0;
}

void lp1_end(void)
{
    if ((stop_jouchuu_se) && (mdata2 == 0)) {
        sptr->lp1_vol = 0;
        sptr->lp1_freq = 0;
        ++stop_jouchuu_se;
    } else {
        if (((++sptr->lp1_cnt) != mdata2) || (mdata2 == 0)) {
            sptr->lp1_vol += (signed char)mdata3;
            sptr->lp1_freq += (signed char)mdata4 * 8;
            mptr = sptr->lp1_addr;
        } else {
            sptr->lp1_vol = 0;
            sptr->lp1_freq = 0;
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void lp2_start(void)
{
    sptr->lp2_addr = mptr;
    sptr->lp2_cnt = 0;
    sptr->lp2_freq = 0;
    sptr->lp2_vol = 0;
}

void lp2_end(void)
{
    if (((++sptr->lp2_cnt) != mdata2) || (mdata2 == 0)) {
        sptr->lp2_vol += (signed char)mdata3;
        sptr->lp2_freq += (signed char)mdata4 << 3;
        mptr = sptr->lp2_addr;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void l3s_set(void)
{
    sptr->lp3_addr = mptr;
}

void l3e_set(void)
{
    if (sptr->lp3_addr) {
        mptr = sptr->lp3_addr;
    } else {
        block_end();
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void tempo_set(void)
{
    sptr->tmp = mdata2;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void tempo_move(void)
{
    register signed int tmp_data;

    sptr->tmpc = mdata2;
    sptr->tmpm = mdata3;
    sptr->tmpw = sptr->tmp << 8;
    tmp_data = sptr->tmpm - sptr->tmp;
    if (tmp_data < 0) {
        if (tmp_data < -127) tmp_data = -127;
        sptr->tmpad = -((-tmp_data << 8) / sptr->tmpc);
        if (sptr->tmpad < -0x7F0) sptr->tmpad = -0x7F0;
    } else {
        if (tmp_data > 127) tmp_data = 127;
        sptr->tmpad =  (tmp_data << 8) / sptr->tmpc;
        if (sptr->tmpad > 0x7F0) sptr->tmpad = 0x7F0;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void trans_set(void)
{
    sptr->ptps = ((signed char)mdata2);
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void tre_set(void)
{
    sptr->trehs = mdata2;
    sptr->trecad = mdata3;
    sptr->tred = mdata4;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vol_chg(void)
{
    sptr->pvod = mdata2 << 8;
    sptr->pvoc = 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void vol_move(void)
{
    int vol_data;

    sptr->pvoc = mdata2;
    sptr->pvom = mdata3;
    vol_data = (mdata3 << 8);
    vol_data -= sptr->pvod;
    if (vol_data < 0) {
        sptr->pvoad = -(-vol_data / sptr->pvoc);
        if (sptr->pvoad < -0x7F0) sptr->pvoad = -0x7F0;
    } else {
        sptr->pvoad = vol_data / sptr->pvoc;
        if (sptr->pvoad > 0x7F0) sptr->pvoad = 0x7F0;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void por_set(void)
{
    sptr->swshc = 0;
    sptr->swsc = mdata2;
    if (mdata2 == 0) {
        sptr->swsk = 0;
    } else {
        sptr->swsk = 1;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void sws_set(void)
{
    sptr->swsk = 0;
    sptr->swshc = mdata2;
    sptr->swsc = mdata3;
    sptr->swss = mdata4 << 8;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void detune_set(void)
{
    sptr->tund = ((signed char)mdata2) << 2;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void swp_set(void)
{
    /* do nothing */
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
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
    if ((mtrack >= SNG_TRACK_NUM) && (mtrack < INTERNAL_TRACK_NUM)) {
        if (!se_playing[mtrack - SNG_TRACK_NUM].kind) {
            rev_on_bit |= spu_ch_tbl[mtrack + 1];
        }
    }
}

void eof_set(void)
{
    if ((mtrack >= SNG_TRACK_NUM) && (mtrack < INTERNAL_TRACK_NUM)) {
        if (!se_playing[mtrack - SNG_TRACK_NUM].kind) {
            rev_off_bit |= spu_ch_tbl[mtrack + 1];
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void kakko_start(void)
{
    sptr->kak1ptr = mptr;
    sptr->kakfg = 0;
}

void kakko_end(void)
{
    switch (sptr->kakfg) {
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void env_set(void)
{
    /* do nothing */
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void ads_set(void)
{
    spu_tr_wk[mtrack].a_mode = SPU_VOICE_LINEARIncN;
    spu_tr_wk[mtrack].ar = 127 - (mdata2 & 0x7F);
    spu_tr_wk[mtrack].dr = 15 - (mdata3 & 0xF);
    spu_tr_wk[mtrack].sl = (mdata4 & 0xF);
    spu_tr_wk[mtrack].env1_fg = 1;
}

void srs_set(void)
{
    spu_tr_wk[mtrack].s_mode = SPU_VOICE_LINEARDecN;
    spu_tr_wk[mtrack].sr = 127 - (mdata2 & 0x7F);
    spu_tr_wk[mtrack].env2_fg = 1;
}

void rrs_set(void)
{
    spu_tr_wk[mtrack].r_mode = SPU_VOICE_LINEARDecN;
    sptr->rrd = spu_tr_wk[mtrack].rr = 31 - (mdata2 & 0x1F);
    spu_tr_wk[mtrack].env3_fg = 1;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void pm_set(void)
{
    /* do nothing */
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void jump_set(void)
{
    /* do nothing */
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void block_end(void)
{
    keyoffs |= keyd;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
void no_cmd(void)
{
    /* do nothing */
}
