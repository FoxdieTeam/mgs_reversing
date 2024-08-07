#include "SD/sound.h"
#include "psyq.h"

extern SOUND_W      *sptr_800C057C;
extern int           freq_tbl_8009FC08[108];
extern SPU_TRACK_REG spu_tr_wk_800C0658[23];
extern unsigned int  mtrack_800BF1EC;
extern int           keyons_800BF260;
extern int           keyd_800C0524;
extern int           keyoffs_800BF29C;
extern int           song_end_800C04E8;
extern unsigned int  spu_ch_tbl_800A2AC8[];
extern volatile int  sd_flags_800C0BFC;
extern unsigned int  gStr_FadeOut1_800BF16C;
extern int           sng_status_800BF158;
extern SEPLAYTBL     se_playing_800BF068[8];
extern WAVE_W       *voice_tbl_800C0530;
extern int           pant_8009FA60[41];
extern int           se_pant_8009FB04[65];
extern int           se_pan_800BF180[8];
extern int           se_pan_800BF1B8[8];
extern int           sound_mono_fg_800C050C;
extern int           fade_unk_1_800C0BC8[13];
extern int           dword_800BF064;
extern int           dword_800BF210;
extern int           spu_wave_start_ptr_800C052C;
extern unsigned char byte_800C056C;

void pan_set2_800882E4(unsigned char x);

void spuwr_80087A88(void)
{
    int          i;
    SpuVoiceAttr attr;

    if (keyoffs_800BF29C)
    {
        SpuSetKey(0, keyoffs_800BF29C);
        keyoffs_800BF29C = 0;
    }

    if (dword_800BF210)
    {
        SpuSetReverbVoice(0, dword_800BF210);
        dword_800BF210 = 0;
    }

    for (i = 0; i < 21; i++)
    {
        attr.mask = 0;
        attr.voice = spu_ch_tbl_800A2AC8[i + 1];
        if (spu_tr_wk_800C0658[i].vol_fg)
        {
            attr.mask = 3;
            attr.volume.left = spu_tr_wk_800C0658[i].vol_l;
            attr.volume.right = spu_tr_wk_800C0658[i].vol_r;
            spu_tr_wk_800C0658[i].vol_fg = 0;
        }

        if (spu_tr_wk_800C0658[i].pitch_fg)
        {
            attr.mask |= 0x10u;
            attr.pitch = spu_tr_wk_800C0658[i].pitch;
            spu_tr_wk_800C0658[i].pitch_fg = 0;
        }

        if (spu_tr_wk_800C0658[i].addr_fg)
        {
            attr.mask |= 0x80u;
            attr.addr = spu_tr_wk_800C0658[i].addr + spu_wave_start_ptr_800C052C;
            spu_tr_wk_800C0658[i].addr_fg = 0;
        }

        if (spu_tr_wk_800C0658[i].env1_fg)
        {
            attr.mask |= 0x1900u;
            attr.a_mode = spu_tr_wk_800C0658[i].a_mode;
            attr.ar = spu_tr_wk_800C0658[i].ar;
            attr.dr = spu_tr_wk_800C0658[i].dr;
            spu_tr_wk_800C0658[i].env1_fg = 0;
        }

        if (spu_tr_wk_800C0658[i].env2_fg)
        {
            attr.mask |= 0xA200u;
            attr.s_mode = spu_tr_wk_800C0658[i].s_mode;
            attr.sr = spu_tr_wk_800C0658[i].sr;
            attr.sl = spu_tr_wk_800C0658[i].sl;
            spu_tr_wk_800C0658[i].env2_fg = 0;
        }

        if (spu_tr_wk_800C0658[i].env3_fg)
        {
            attr.mask |= 0x4400u;
            attr.r_mode = spu_tr_wk_800C0658[i].r_mode;
            attr.rr = spu_tr_wk_800C0658[i].rr;
            spu_tr_wk_800C0658[i].env3_fg = 0;
        }

        if (attr.mask)
        {
            SpuSetVoiceAttr(&attr);
        }
    }

    if (dword_800BF064)
    {
        SpuSetReverbVoice(1, dword_800BF064);
        dword_800BF064 = 0;
    }

    if (keyons_800BF260)
    {
        SpuSetKey(1, keyons_800BF260);
        keyons_800BF260 = 0;
    }
}

void sound_off_80087DAC(void)
{
    int          i; // $a1
    unsigned int key_no;

    for (i = 0; i < 23; i++)
    {
        spu_tr_wk_800C0658[i].rr = 7;
        spu_tr_wk_800C0658[i].env3_fg = 1;

        key_no = spu_ch_tbl_800A2AC8[mtrack_800BF1EC + 1];
        song_end_800C04E8 |= key_no;
    }
    keyoffs_800BF29C = 0x7FFFFF;
}

void sng_off_80087E2C(void)
{
    int i; // $a0
    for (i = 0; i < 13; i++)
    {
        spu_tr_wk_800C0658[i].rr = 7;
        spu_tr_wk_800C0658[i].env3_fg = 1;
    }
    song_end_800C04E8 |= 0x1FFFu;
    keyoffs_800BF29C |= 0x1FFFu;
}

void se_off_80087E94(int i)
{
    spu_tr_wk_800C0658[i + 13].env3_fg = 1;
    spu_tr_wk_800C0658[i + 13].rr = 0;
    song_end_800C04E8 |= 1 << (i + 13);
    keyoffs_800BF29C |= 1 << (i + 13);
}

void sng_pause_80087EF4(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = 3; // TODO constants
    c_attr.mvol.left = 0;
    c_attr.mvol.right = 0;
    SpuSetCommonAttr(&c_attr);
}

void sng_pause_off_80087F24(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = 3;
    c_attr.mvol.left = 0x3FFF;
    c_attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr(&c_attr);
}

void keyon_80087F58(void)
{
    keyons_800BF260 |= keyd_800C0524;
}

void keyoff_80087F80(void)
{
    keyoffs_800BF29C |= keyd_800C0524;
}

void tone_set_80087FA8(unsigned char n)
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].addr = voice_tbl_800C0530[n].addr;
    spu_tr_wk_800C0658[mtrack_800BF1EC].addr_fg = 1;
    sptr_800C057C->macro = voice_tbl_800C0530[n].sample_note;
    sptr_800C057C->micro = voice_tbl_800C0530[n].sample_tune;

    if (voice_tbl_800C0530[n].a_mode)
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].a_mode = 5;
    }
    else
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].a_mode = 1;
    }

    spu_tr_wk_800C0658[mtrack_800BF1EC].ar = ~voice_tbl_800C0530[n].ar & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].dr = ~voice_tbl_800C0530[n].dr & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env1_fg = 1;

    switch (voice_tbl_800C0530[n].s_mode)
    {
    case 0:
        spu_tr_wk_800C0658[mtrack_800BF1EC].s_mode = 3;
        break;

    case 1:
        spu_tr_wk_800C0658[mtrack_800BF1EC].s_mode = 7;
        break;

    case 2:
        spu_tr_wk_800C0658[mtrack_800BF1EC].s_mode = 1;
        break;

    default:
        spu_tr_wk_800C0658[mtrack_800BF1EC].s_mode = 5;
        break;
    }

    spu_tr_wk_800C0658[mtrack_800BF1EC].sr = ~voice_tbl_800C0530[n].sr & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].sl = voice_tbl_800C0530[n].sl & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env2_fg = 1;

    if (!voice_tbl_800C0530[n].r_mode)
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].r_mode = 3;
    }
    else
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].r_mode = 7;
    }

    spu_tr_wk_800C0658[mtrack_800BF1EC].rr = sptr_800C057C->rrd = ~voice_tbl_800C0530[n].rr & 0x1F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].env3_fg = 1;
    if (!sptr_800C057C->panmod)
    {
        pan_set2_800882E4(voice_tbl_800C0530[n].pan);
    }
    sptr_800C057C->dec_vol = (unsigned char)voice_tbl_800C0530[n].decl_vol;
}

void pan_set2_800882E4(unsigned char x)
{
    if (!sptr_800C057C->panoff)
    {
        sptr_800C057C->panf = 2 * x;
        sptr_800C057C->pand = x << 9;
    }
}

void vol_set_80088320(unsigned int vol_data)
{
    unsigned int pan;

    if ((mtrack_800BF1EC < 13) ||
         (se_playing_800BF068[mtrack_800BF1EC - 13].kind == 0))
    {
        if (vol_data >= sptr_800C057C->dec_vol)
        {
            vol_data -= sptr_800C057C->dec_vol;
        }
        else
        {
            vol_data = 0;
        }

        pan = sptr_800C057C->pand >> 8;

        if (pan > 40)
        {
            pan = 40;
        }

        if (sound_mono_fg_800C050C != 0)
        {
            pan = 20;
        }

        if (mtrack_800BF1EC < 13)
        {
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_r = (vol_data * pant_8009FA60[pan] * fade_unk_1_800C0BC8[mtrack_800BF1EC]) >> 16;
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_l = (vol_data * pant_8009FA60[40 - pan] * fade_unk_1_800C0BC8[mtrack_800BF1EC]) >> 16;
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_fg = 1;
        }
        else
        {
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_r = vol_data * pant_8009FA60[pan];
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_l = vol_data * pant_8009FA60[40 - pan];
            spu_tr_wk_800C0658[mtrack_800BF1EC].vol_fg = 1;
        }
    }
    else
    {
        if (vol_data >= sptr_800C057C->dec_vol)
        {
            vol_data -= sptr_800C057C->dec_vol;
        }
        else
        {
            vol_data = 0;
        }

        pan = se_pan_800BF180[mtrack_800BF1EC + 1];
        vol_data = (vol_data * se_pan_800BF1B8[mtrack_800BF1EC + 1]) >> 16;

        if (sound_mono_fg_800C050C != 0)
        {
            pan = 32;
        }

        spu_tr_wk_800C0658[mtrack_800BF1EC].vol_r = vol_data * se_pant_8009FB04[pan];
        spu_tr_wk_800C0658[mtrack_800BF1EC].vol_l = vol_data * se_pant_8009FB04[64 - pan];
        spu_tr_wk_800C0658[mtrack_800BF1EC].vol_fg = 1;
    }
}

void freq_set_800885D4(unsigned int note_tune)
{
    unsigned char temp, temp2, temp3, temp4;
    int           freq;
    int          *ptr;

    note_tune += (signed char)sptr_800C057C->micro;
    temp4 = note_tune;
    temp3 = (note_tune >> 8) + sptr_800C057C->macro;
    temp3 &= 0x7F;
    ptr = freq_tbl_8009FC08;
    freq = ptr[temp3 + 1] - ptr[temp3];

    if (freq & 0x8000)
    {
        freq = 0xC9;
    }

    temp = freq;
    temp2 = freq >> 8;
    freq = ((temp * temp4) >> 8) + (temp2 * temp4);
    freq += ptr[temp3];

    spu_tr_wk_800C0658[mtrack_800BF1EC].pitch = freq;
    spu_tr_wk_800C0658[mtrack_800BF1EC].pitch_fg = 1;
}

void drum_set_80088694(unsigned char n)
{
    unsigned char addend = byte_800C056C + 0xB8;
    n += addend;
    tone_set_80087FA8(n);
}

/***** sd_cli.c *****/
// TODO: move the followng funcs to sd_cli.c

int sd_task_active_800886C4(void)
{
    if (sd_flags_800C0BFC & 0x80)
    {
        return 1;
    }

    return 0;
}

int sd_str_play_800886DC(void)
{
    return gStr_FadeOut1_800BF16C > 4;
}

int SD_800886F4(void)
{
    return sng_status_800BF158 > 2;
}

int sub_8008870C(void)
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = (unsigned int)song_end_800C04E8 >> 13; // TODO: Fix type
    for (i = 0; i < 8; i++)
    {
        if ((bits & 1) == 0 && se_playing_800BF068[i].pri != 255)
        {
            return se_playing_800BF068[i].code;
        }
        bits >>= 1;
    }
    return 0;
}

int sub_8008877C(void)
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = (unsigned int)song_end_800C04E8 >> 13; // TODO: Fix type
    for (i = 0; i < 8; i++)
    {
        if ((bits & 1) == 0 && se_playing_800BF068[i].pri == 255)
        {
            return se_playing_800BF068[i].code;
        }
        bits >>= 1;
    }
    return 0;
}
