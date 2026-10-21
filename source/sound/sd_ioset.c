#include <libspu.h>

#include "sd_incl.h"
#include "sd_ext.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

void spuwr(void);
void sound_off(void);
void sng_off(void);
void se_off(int i);
void sng_pause(void);
void sng_pause_off(void);
void keyon(void);
void keyoff(void);
void tone_set(unsigned char n);
void pan_set2(unsigned char x);
void vol_set(unsigned int vol_data);
void freq_set(unsigned int note_tune);
void drum_set(unsigned char n);

/************************************************************************/
/*                                                                      */
/************************************************************************/

void spuwr(void)
{
    int          i;
    SpuVoiceAttr attr;
/*----------------------------------------------------------------------*/
    if (keyoffs) {
        SpuSetKey(SPU_OFF, keyoffs);
        keyoffs = 0;
    }
/*----------------------------------------------------------------------*/
    if (rev_off_bit) {
        SpuSetReverbVoice(SPU_OFF, rev_off_bit);
        rev_off_bit = 0;
    }
/*----------------------------------------------------------------------*/
    for (i = 0; i < INTERNAL_TRACK_NUM; i++) {
        attr.mask = 0;
        attr.voice = spu_ch_tbl[i + 1];
        if (spu_tr_wk[i].vol_fg) {
            attr.mask |= SPU_VOICE_VOLL | SPU_VOICE_VOLR;
            attr.volume.left = spu_tr_wk[i].vol_l;
            attr.volume.right = spu_tr_wk[i].vol_r;
            spu_tr_wk[i].vol_fg = 0;
        }
/*----------------------------------------------------------------------*/
        if (spu_tr_wk[i].pitch_fg) {
            attr.mask |= SPU_VOICE_PITCH;
            attr.pitch = spu_tr_wk[i].pitch;
            spu_tr_wk[i].pitch_fg = 0;
        }
/*----------------------------------------------------------------------*/
        if (spu_tr_wk[i].addr_fg) {
            attr.mask |= SPU_VOICE_WDSA;
            attr.addr = spu_tr_wk[i].addr + spu_wave_start_ptr;
            spu_tr_wk[i].addr_fg = 0;
        }
/*----------------------------------------------------------------------*/
        if (spu_tr_wk[i].env1_fg) {
            attr.mask |= SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_AR | SPU_VOICE_ADSR_DR;
            attr.a_mode = spu_tr_wk[i].a_mode;
            attr.ar = spu_tr_wk[i].ar;
            attr.dr = spu_tr_wk[i].dr;
            spu_tr_wk[i].env1_fg = 0;
        }
        if (spu_tr_wk[i].env2_fg) {
            attr.mask |= SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_SL;
            attr.s_mode = spu_tr_wk[i].s_mode;
            attr.sr = spu_tr_wk[i].sr;
            attr.sl = spu_tr_wk[i].sl;
            spu_tr_wk[i].env2_fg = 0;
        }
        if (spu_tr_wk[i].env3_fg) {
            attr.mask |= SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_RR;
            attr.r_mode = spu_tr_wk[i].r_mode;
            attr.rr = spu_tr_wk[i].rr;
            spu_tr_wk[i].env3_fg = 0;
        }
/*----------------------------------------------------------------------*/
        if (attr.mask) {
            SpuSetVoiceAttr(&attr);
        }
    }
/*----------------------------------------------------------------------*/
    if (rev_on_bit) {
        SpuSetReverbVoice(SPU_ON, rev_on_bit);
        rev_on_bit = 0;
    }
/*----------------------------------------------------------------------*/
    if (keyons) {
        SpuSetKey(SPU_ON, keyons);
        keyons = 0;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void sound_off(void)
{
    int i;
    int key_no;

    for (i = 0; i < USE_TRACK_NUM; i++) {
        spu_tr_wk[i].rr = ENV_CUT_OFF;
        spu_tr_wk[i].env3_fg = 1;
        key_no = spu_ch_tbl[mtrack + 1];
        song_end |= key_no;
    }
    keyoffs = 0x7FFFFF;
}

void sng_off(void)
{
    int i;

    for (i = 0; i < SNG_TRACK_NUM; i++) {
        spu_tr_wk[i].rr = ENV_CUT_OFF;
        spu_tr_wk[i].env3_fg = 1;
    }
    song_end |= 0x1FFF;
    keyoffs |= 0x1FFF;
}

void se_off(int i)
{
    spu_tr_wk[i + SNG_TRACK_NUM].env3_fg = 1;
    spu_tr_wk[i + SNG_TRACK_NUM].rr = 0; /*ENV_CUT_OFF*/
    song_end |= 1 << (i + SNG_TRACK_NUM);
    keyoffs |= 1 << (i + SNG_TRACK_NUM);
}

void sng_pause(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    c_attr.mvol.left = 0;
    c_attr.mvol.right = 0;
    SpuSetCommonAttr(&c_attr);
}

void sng_pause_off(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    c_attr.mvol.left = 0x3FFF;
    c_attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&c_attr);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void keyon(void)
{
    keyons |= keyd;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void keyoff(void)
{
    keyoffs |= keyd;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void tone_set(unsigned char n)
{
    spu_tr_wk[mtrack].addr = voice_tbl[n].addr;
    spu_tr_wk[mtrack].addr_fg = 1;
    sptr->macro = voice_tbl[n].sample_note;
    sptr->micro = voice_tbl[n].sample_tune;

/* Attack & Decay */
    if (voice_tbl[n].a_mode) {
        spu_tr_wk[mtrack].a_mode = SPU_VOICE_EXPIncN;
    } else {
        spu_tr_wk[mtrack].a_mode = SPU_VOICE_LINEARIncN;
    }
    spu_tr_wk[mtrack].ar = ~voice_tbl[n].ar & 0x7F;
    spu_tr_wk[mtrack].dr = ~voice_tbl[n].dr & 0xF;
    spu_tr_wk[mtrack].env1_fg = 1;

/* Sustain */
    switch (voice_tbl[n].s_mode) {
    case 0: spu_tr_wk[mtrack].s_mode = SPU_VOICE_LINEARDecN; break;
    case 1: spu_tr_wk[mtrack].s_mode = SPU_VOICE_EXPDecN; break;
    case 2: spu_tr_wk[mtrack].s_mode = SPU_VOICE_LINEARIncN; break;
    default: spu_tr_wk[mtrack].s_mode = SPU_VOICE_EXPIncN; break;
    }
    spu_tr_wk[mtrack].sr = ~voice_tbl[n].sr & 0x7F;
    spu_tr_wk[mtrack].sl = voice_tbl[n].sl & 0xF;
    spu_tr_wk[mtrack].env2_fg = 1;

/* Release */
    if (voice_tbl[n].r_mode) {
        spu_tr_wk[mtrack].r_mode = SPU_VOICE_EXPDecN;
    } else {
        spu_tr_wk[mtrack].r_mode = SPU_VOICE_LINEARDecN;
    }
    spu_tr_wk[mtrack].rr = sptr->rrd = ~voice_tbl[n].rr & 0x1F;
    spu_tr_wk[mtrack].env3_fg = 1;

    if (sptr->panmod == 0) {
        pan_set2(voice_tbl[n].pan);
    }
    sptr->dec_vol = voice_tbl[n].decl_vol;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void pan_set2(unsigned char x)
{
    if (sptr->panoff == 0) {
        sptr->panf = x * 2;
        sptr->pand = x * 2 << 8;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

static unsigned long pant[41] = {
      0,  2,  4,  7, 10, 13, 16, 20, 24, 28,
     32, 36, 40, 45, 50, 55, 60, 65, 70, 75,
     80, 84, 88, 92, 96,100,104,107,110,112,
    114,116,118,120,122,123,124,125,126,127,127
};

static unsigned long se_pant[65] = {
      0,   2,   4,      /*0*/
      6,   8,  10,      /*10*/
     14,  18,  22,      /*24*/
     28,  34,  40,      /*40*/
     46,  52,  58,  64, /*60*/
     70,  76,  82,      /*80*/
     88,  94, 100,      /*100*/
    106, 112, 118,      /*120*/
    124, 130, 136,      /*140*/
    142, 148, 154, 160, /*160*/
    166, 172, 178,      /*172*/
    183, 188, 193,      /*196*/
    198, 203, 208,      /*210*/
    213, 217, 221,      /*222*/
    224, 227, 230, 233, /*232*/
    236, 238, 240,      /*240*/
    242, 244, 246,      /*246*/
    248, 249, 250,      /*250*/
    251, 252, 253,      /*253*/
    254, 254, 255, 255, /*255*/
    255
};

void vol_set(unsigned int vol_data)
{
    unsigned int pan;

    if ((mtrack < SNG_TRACK_NUM) || (se_playing[mtrack - SNG_TRACK_NUM].kind == 0)) {
        if (vol_data >= sptr->dec_vol) vol_data -= sptr->dec_vol;
        else vol_data = 0;

        pan = sptr->pand >> 8;
        if (pan > 40) pan = 40;
        if (sound_mono_fg) pan = 20;

        if (mtrack < SNG_TRACK_NUM) {
            spu_tr_wk[mtrack].vol_r = ((vol_data * pant[pan]) * sng_master_vol[mtrack]) >> 16;
            spu_tr_wk[mtrack].vol_l = ((vol_data * pant[40-pan]) * sng_master_vol[mtrack]) >> 16;
            spu_tr_wk[mtrack].vol_fg = 1;
        } else {
            spu_tr_wk[mtrack].vol_r = (vol_data * pant[pan]);
            spu_tr_wk[mtrack].vol_l = (vol_data * pant[40-pan]);
            spu_tr_wk[mtrack].vol_fg = 1;
        }
    } else {
        if (vol_data >= sptr->dec_vol) vol_data -= sptr->dec_vol;
        else vol_data = 0;

        pan = se_pan[mtrack - SNG_TRACK_NUM];
        vol_data = (vol_data * se_vol[mtrack - SNG_TRACK_NUM]) >> 16;
        if (sound_mono_fg != 0) pan = 32;

        spu_tr_wk[mtrack].vol_r = vol_data * se_pant[pan];
        spu_tr_wk[mtrack].vol_l = vol_data * se_pant[64 - pan];
        spu_tr_wk[mtrack].vol_fg = 1;
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

unsigned int freq_tbl[] = {
  267,  283,  300,  318,  337,  357,  378,  401,  425,  450,  477,  505,
  535,  567,  601,  637,  675,  715,  757,  802,  850,  901,  954, 1011,
 1071, 1135, 1202, 1274, 1350, 1430, 1515, 1605, 1701, 1802, 1909, 2022,
 2143, 2270, 2405, 2548, 2700, 2860, 3030, 3211, 3402, 3604, 3818, 4045,
 4286, 4541, 4811, 5097, 5400, 5721, 6061, 6422, 6804, 7208, 7637, 8091,
 8572, 9082, 9622,10194,10800,11442,12122,12844,13608,14416,15276,16182,
   33,   35,   38,  40,    42,   45,   47,   50,   53,   56,   60,   63,
   66,   70,   75,  79,    84,   89,   94,  100,  106,  112,  119,  126,
  133,  141,  150, 159,   168,  178,  189,  200,  212,  225,  238,  252,
};

/************************************************************************/
/*                                                                      */
/************************************************************************/

void freq_set(unsigned int note_tune)
{
    unsigned char   pl, ph, note, tune;
    int             freq;
    int             *ptr;

    note_tune += (signed char)sptr->micro;
    tune = note_tune;
    note = (note_tune >> 8) + sptr->macro;
    note &= 0x7F;
    ptr = freq_tbl;
    freq = ptr[note + 1] - ptr[note];
    if ((freq & 0x8000) != 0) freq = 201;
    pl = freq;
    ph = freq >> 8;
    freq = ((pl * tune) >> 8) + (ph * tune);
    freq += ptr[note];

    spu_tr_wk[mtrack].pitch = freq;
    spu_tr_wk[mtrack].pitch_fg = 1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

void drum_set(unsigned char n)
{
    n = n - SEQ_DRC + wavs;
    tone_set(n);
}
