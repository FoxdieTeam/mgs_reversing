#include "sd/sd_incl.h"
#include "sd/sd_ext.h"

#include <libspu.h>
#include "common.h"

STATIC unsigned long pant[41] = {
    0,   2,   4,   7,   10,  13,  16,  20,  24,  28,  32,  36,  40,  45,
    50,  55,  60,  65,  70,  75,  80,  84,  88,  92,  96,  100, 104, 107,
    110, 112, 114, 116, 118, 120, 122, 123, 124, 125, 126, 127, 127
};

STATIC unsigned long se_pant[65] = {
    0,   2,   4,   6,   8,   10,  14,  18,  22,  28,  34,  40,  46,
    52,  58,  64,  70,  76,  82,  88,  94,  100, 106, 112, 118, 124,
    130, 136, 142, 148, 154, 160, 166, 172, 178, 183, 188, 193, 198,
    203, 208, 213, 217, 221, 224, 227, 230, 233, 236, 238, 240, 242,
    244, 246, 248, 249, 250, 251, 252, 253, 254, 254, 255, 255, 255
};

unsigned int freq_tbl[108] = {
    0x010B, 0x011B, 0x012C, 0x013E, 0x0151, 0x0165, 0x017A, 0x0191,
    0x01A9, 0x01C2, 0x01DD, 0x01F9, 0x0217, 0x0237, 0x0259, 0x027D,
    0x02A3, 0x02CB, 0x02F5, 0x0322, 0x0352, 0x0385, 0x03BA, 0x03F3,
    0x042F, 0x046F, 0x04B2, 0x04FA, 0x0546, 0x0596, 0x05EB, 0x0645,
    0x06A5, 0x070A, 0x0775, 0x07E6, 0x085F, 0x08DE, 0x0965, 0x09F4,
    0x0A8C, 0x0B2C, 0x0BD6, 0x0C8B, 0x0D4A, 0x0E14, 0x0EEA, 0x0FCD,
    0x10BE, 0x11BD, 0x12CB, 0x13E9, 0x1518, 0x1659, 0x17AD, 0x1916,
    0x1A94, 0x1C28, 0x1DD5, 0x1F9B, 0x217C, 0x237A, 0x2596, 0x27D2,
    0x2A30, 0x2CB2, 0x2F5A, 0x322C, 0x3528, 0x3850, 0x3BAC, 0x3F36,
    0x0021, 0x0023, 0x0026, 0x0028, 0x002A, 0x002D, 0x002F, 0x0032,
    0x0035, 0x0038, 0x003C, 0x003F, 0x0042, 0x0046, 0x004B, 0x004F,
    0x0054, 0x0059, 0x005E, 0x0064, 0x006A, 0x0070, 0x0077, 0x007E,
    0x0085, 0x008D, 0x0096, 0x009F, 0x00A8, 0x00B2, 0x00BD, 0x00C8,
    0x00D4, 0x00E1, 0x00EE, 0x00FC
};

void spuwr(void)
{
    int          i;
    SpuVoiceAttr attr;

    if (keyoffs)
    {
        SpuSetKey(SPU_OFF, keyoffs);
        keyoffs = 0;
    }

    if (eoffs)
    {
        SpuSetReverbVoice(SPU_OFF, eoffs);
        eoffs = 0;
    }

    for (i = 0; i < 21; i++)
    {
        attr.mask = 0;
        attr.voice = spu_ch_tbl[i + 1];
        if (spu_tr_wk[i].vol_fg)
        {
            attr.mask |= SPU_VOICE_VOLL | SPU_VOICE_VOLR;
            attr.volume.left = spu_tr_wk[i].vol_l;
            attr.volume.right = spu_tr_wk[i].vol_r;
            spu_tr_wk[i].vol_fg = 0;
        }

        if (spu_tr_wk[i].pitch_fg)
        {
            attr.mask |= SPU_VOICE_PITCH;
            attr.pitch = spu_tr_wk[i].pitch;
            spu_tr_wk[i].pitch_fg = 0;
        }

        if (spu_tr_wk[i].addr_fg)
        {
            attr.mask |= SPU_VOICE_WDSA;
            attr.addr = spu_tr_wk[i].addr + spu_wave_start_ptr;
            spu_tr_wk[i].addr_fg = 0;
        }

        if (spu_tr_wk[i].env1_fg)
        {
            attr.mask |= SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_AR | SPU_VOICE_ADSR_DR;
            attr.a_mode = spu_tr_wk[i].a_mode;
            attr.ar = spu_tr_wk[i].ar;
            attr.dr = spu_tr_wk[i].dr;
            spu_tr_wk[i].env1_fg = 0;
        }

        if (spu_tr_wk[i].env2_fg)
        {
            attr.mask |= SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_SL;
            attr.s_mode = spu_tr_wk[i].s_mode;
            attr.sr = spu_tr_wk[i].sr;
            attr.sl = spu_tr_wk[i].sl;
            spu_tr_wk[i].env2_fg = 0;
        }

        if (spu_tr_wk[i].env3_fg)
        {
            attr.mask |= SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_RR;
            attr.r_mode = spu_tr_wk[i].r_mode;
            attr.rr = spu_tr_wk[i].rr;
            spu_tr_wk[i].env3_fg = 0;
        }

        if (attr.mask)
        {
            SpuSetVoiceAttr(&attr);
        }
    }

    if (eons)
    {
        SpuSetReverbVoice(SPU_ON, eons);
        eons = 0;
    }

    if (keyons)
    {
        SpuSetKey(SPU_ON, keyons);
        keyons = 0;
    }
}

void sound_off(void)
{
    int          i;
    unsigned int key_no;

    for (i = 0; i < 23; i++)
    {
        spu_tr_wk[i].rr = 7;
        spu_tr_wk[i].env3_fg = 1;

        key_no = spu_ch_tbl[mtrack + 1];
        song_end |= key_no;
    }
    keyoffs = 0x7FFFFF;
}

void sng_off(void)
{
    int i;

    for (i = 0; i < 13; i++)
    {
        spu_tr_wk[i].rr = 7;
        spu_tr_wk[i].env3_fg = 1;
    }
    song_end |= 0x1FFFu;
    keyoffs |= 0x1FFFu;
}

void se_off(int i)
{
    spu_tr_wk[i + 13].env3_fg = 1;
    spu_tr_wk[i + 13].rr = 0;
    song_end |= 1 << (i + 13);
    keyoffs |= 1 << (i + 13);
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

void keyon(void)
{
    keyons |= keyd;
}

void keyoff(void)
{
    keyoffs |= keyd;
}

void tone_set(unsigned char n)
{
    spu_tr_wk[mtrack].addr = voice_tbl[n].addr;
    spu_tr_wk[mtrack].addr_fg = 1;
    sptr->macro = voice_tbl[n].sample_note;
    sptr->micro = voice_tbl[n].sample_tune;

    if (voice_tbl[n].a_mode)
    {
        spu_tr_wk[mtrack].a_mode = 5;
    }
    else
    {
        spu_tr_wk[mtrack].a_mode = 1;
    }

    spu_tr_wk[mtrack].ar = ~voice_tbl[n].ar & 0x7F;
    spu_tr_wk[mtrack].dr = ~voice_tbl[n].dr & 0xF;
    spu_tr_wk[mtrack].env1_fg = 1;

    switch (voice_tbl[n].s_mode)
    {
    case 0:
        spu_tr_wk[mtrack].s_mode = 3;
        break;

    case 1:
        spu_tr_wk[mtrack].s_mode = 7;
        break;

    case 2:
        spu_tr_wk[mtrack].s_mode = 1;
        break;

    default:
        spu_tr_wk[mtrack].s_mode = 5;
        break;
    }

    spu_tr_wk[mtrack].sr = ~voice_tbl[n].sr & 0x7F;
    spu_tr_wk[mtrack].sl = voice_tbl[n].sl & 0xF;
    spu_tr_wk[mtrack].env2_fg = 1;

    if (!voice_tbl[n].r_mode)
    {
        spu_tr_wk[mtrack].r_mode = 3;
    }
    else
    {
        spu_tr_wk[mtrack].r_mode = 7;
    }

    spu_tr_wk[mtrack].rr = sptr->rrd = ~voice_tbl[n].rr & 0x1F;
    spu_tr_wk[mtrack].env3_fg = 1;
    if (!sptr->panmod)
    {
        pan_set2(voice_tbl[n].pan);
    }
    sptr->dec_vol = (unsigned char)voice_tbl[n].decl_vol;
}

void pan_set2(unsigned char x)
{
    if (!sptr->panoff)
    {
        sptr->panf = 2 * x;
        sptr->pand = x << 9;
    }
}

void vol_set(unsigned int vol_data)
{
    unsigned int pan;

    if ((mtrack < 13) ||
         (se_playing[mtrack - 13].kind == 0))
    {
        if (vol_data >= sptr->dec_vol)
        {
            vol_data -= sptr->dec_vol;
        }
        else
        {
            vol_data = 0;
        }

        pan = sptr->pand >> 8;

        if (pan > 40)
        {
            pan = 40;
        }

        if (sound_mono_fg != 0)
        {
            pan = 20;
        }

        if (mtrack < 13)
        {
            spu_tr_wk[mtrack].vol_r = (vol_data * pant[pan] * sng_master_vol[mtrack]) >> 16;
            spu_tr_wk[mtrack].vol_l = (vol_data * pant[40 - pan] * sng_master_vol[mtrack]) >> 16;
            spu_tr_wk[mtrack].vol_fg = 1;
        }
        else
        {
            spu_tr_wk[mtrack].vol_r = vol_data * pant[pan];
            spu_tr_wk[mtrack].vol_l = vol_data * pant[40 - pan];
            spu_tr_wk[mtrack].vol_fg = 1;
        }
    }
    else
    {
        if (vol_data >= sptr->dec_vol)
        {
            vol_data -= sptr->dec_vol;
        }
        else
        {
            vol_data = 0;
        }

        pan = se_pan[mtrack - 13];
        vol_data = (vol_data * se_vol[mtrack - 13]) >> 16;

        if (sound_mono_fg != 0)
        {
            pan = 32;
        }

        spu_tr_wk[mtrack].vol_r = vol_data * se_pant[pan];
        spu_tr_wk[mtrack].vol_l = vol_data * se_pant[64 - pan];
        spu_tr_wk[mtrack].vol_fg = 1;
    }
}

void freq_set(unsigned int note_tune)
{
    unsigned char temp, temp2, temp3, temp4;
    int           freq;
    int          *ptr;

    note_tune += (signed char)sptr->micro;
    temp4 = note_tune;
    temp3 = (note_tune >> 8) + sptr->macro;
    temp3 &= 0x7F;
    ptr = freq_tbl;
    freq = ptr[temp3 + 1] - ptr[temp3];

    if (freq & 0x8000)
    {
        freq = 0xC9;
    }

    temp = freq;
    temp2 = freq >> 8;
    freq = ((temp * temp4) >> 8) + (temp2 * temp4);
    freq += ptr[temp3];

    spu_tr_wk[mtrack].pitch = freq;
    spu_tr_wk[mtrack].pitch_fg = 1;
}

void drum_set(unsigned char n)
{
    unsigned char addend = wavs + 0xB8;
    n += addend;
    tone_set(n);
}
