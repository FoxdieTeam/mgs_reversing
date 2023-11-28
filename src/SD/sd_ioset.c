#include "SD/sd.h"
#include "psyq.h"

extern SOUND_W      *sptr_800C057C;
extern int           freq_tbl_8009FC08[ 108 ];
extern SPU_TRACK_REG spu_tr_wk_800C0658[ 23 ];
extern unsigned int  mtrack_800BF1EC;
extern int           keyons_800BF260;
extern int           keyd_800C0524;
extern int           keyoffs_800BF29C;
extern int           song_end_800C04E8;
extern unsigned int  spu_ch_tbl_800A2AC8[];
extern volatile int  sd_flags_800C0BFC;
extern unsigned int  gStr_FadeOut1_800BF16C;
extern int           sng_status_800BF158;
extern SEPLAYTBL     se_playing_800BF068[ 8 ];
extern WAVE_W       *voice_tbl_800C0530;
extern int           pant_8009FA60[ 41 ];
extern int           se_pant_8009FB04[ 65 ];
extern int           se_pan_800BF180[ 8 ];
extern int           se_pan_800BF1B8[ 8 ];
extern int           dword_800C050C;
extern int           fade_unk_1_800C0BC8[ 13 ];
extern int           dword_800BF064;
extern int           dword_800BF210;
extern int           spu_wave_start_ptr_800C052C;
extern unsigned char byte_800C056C;

void               pan_set2_800882E4( unsigned char a1 );

void                 SD_spuwr_80087A88()
{
    int          i;         // $s7
    SpuVoiceAttr voiceAttr; // [sp+10h] [-40h] BYREF

    if ( keyoffs_800BF29C )
    {
        SpuSetKey( 0, keyoffs_800BF29C );
        keyoffs_800BF29C = 0;
    }

    if ( dword_800BF210 )
    {
        SpuSetReverbVoice( 0, dword_800BF210 );
        dword_800BF210 = 0;
    }

    for ( i = 0; i < 21; i++ )
    {
        voiceAttr.mask = 0;
        voiceAttr.voice = spu_ch_tbl_800A2AC8[ i + 1 ];
        if ( spu_tr_wk_800C0658[ i ].field_4_vol_fg )
        {
            voiceAttr.mask = 3;
            voiceAttr.volume.left = spu_tr_wk_800C0658[ i ].field_0_vol_l;
            voiceAttr.volume.right = spu_tr_wk_800C0658[ i ].field_2_vol_r;
            spu_tr_wk_800C0658[ i ].field_4_vol_fg = 0;
        }

        if ( spu_tr_wk_800C0658[ i ].field_C_pitch_fg )
        {
            voiceAttr.mask |= 0x10u;
            voiceAttr.pitch = spu_tr_wk_800C0658[ i ].field_8_pitch;
            spu_tr_wk_800C0658[ i ].field_C_pitch_fg = 0;
        }

        if ( spu_tr_wk_800C0658[ i ].field_14_addr_fg )
        {
            voiceAttr.mask |= 0x80u;
            voiceAttr.addr = spu_tr_wk_800C0658[ i ].field_10_addr + spu_wave_start_ptr_800C052C;
            spu_tr_wk_800C0658[ i ].field_14_addr_fg = 0;
        }

        if ( spu_tr_wk_800C0658[ i ].field_20_env1_fg )
        {
            voiceAttr.mask |= 0x1900u;
            voiceAttr.a_mode = spu_tr_wk_800C0658[ i ].field_18_a_mode;
            voiceAttr.ar = spu_tr_wk_800C0658[ i ].field_1C_ar;
            voiceAttr.dr = spu_tr_wk_800C0658[ i ].field_1E_dr;
            spu_tr_wk_800C0658[ i ].field_20_env1_fg = 0;
        }

        if ( spu_tr_wk_800C0658[ i ].field_2C_env2_fg )
        {
            voiceAttr.mask |= 0xA200u;
            voiceAttr.s_mode = spu_tr_wk_800C0658[ i ].field_24_s_mode;
            voiceAttr.sr = spu_tr_wk_800C0658[ i ].field_28_sr;
            voiceAttr.sl = spu_tr_wk_800C0658[ i ].field_2A_sl;
            spu_tr_wk_800C0658[ i ].field_2C_env2_fg = 0;
        }

        if ( spu_tr_wk_800C0658[ i ].field_38_env3_fg )
        {
            voiceAttr.mask |= 0x4400u;
            voiceAttr.r_mode = spu_tr_wk_800C0658[ i ].field_30_r_mode;
            voiceAttr.rr = spu_tr_wk_800C0658[ i ].field_34_rr;
            spu_tr_wk_800C0658[ i ].field_38_env3_fg = 0;
        }

        if ( voiceAttr.mask )
        {
            SpuSetVoiceAttr( &voiceAttr );
        }
    }

    if ( dword_800BF064 )
    {
        SpuSetReverbVoice( 1, dword_800BF064 );
        dword_800BF064 = 0;
    }

    if ( keyons_800BF260 )
    {
        SpuSetKey( 1, keyons_800BF260 );
        keyons_800BF260 = 0;
    }
}

void sound_off_80087DAC()
{
    int          i; // $a1
    unsigned int t;
    for ( i = 0; i < 23; i++ )
    {
        spu_tr_wk_800C0658[ i ].field_34_rr = 7;
        spu_tr_wk_800C0658[ i ].field_38_env3_fg = 1;

        t = spu_ch_tbl_800A2AC8[ mtrack_800BF1EC + 1 ];
        song_end_800C04E8 |= t;
    }
    keyoffs_800BF29C = 0x7FFFFF;
}

void sng_off_80087E2C()
{
    int i; // $a0
    for ( i = 0; i < 13; i++ )
    {
        spu_tr_wk_800C0658[ i ].field_34_rr = 7;
        spu_tr_wk_800C0658[ i ].field_38_env3_fg = 1;
    }
    song_end_800C04E8 |= 0x1FFFu;
    keyoffs_800BF29C |= 0x1FFFu;
}

void se_off_80087E94( int a1 )
{
    spu_tr_wk_800C0658[ a1 + 13 ].field_38_env3_fg = 1;
    spu_tr_wk_800C0658[ a1 + 13 ].field_34_rr = 0;
    song_end_800C04E8 |= 1 << ( a1 + 13 );
    keyoffs_800BF29C |= 1 << ( a1 + 13 );
}

void sng_pause_80087EF4()
{
    SpuCommonAttr attr; // [sp+10h] [-28h] BYREF

    attr.mask = 3; // TODO constants
    attr.mvol.left = 0;
    attr.mvol.right = 0;
    SpuSetCommonAttr( &attr );
}

void sng_pause_off_80087F24()
{
    SpuCommonAttr attr; // [sp+10h] [-28h] BYREF

    attr.mask = 3;
    attr.mvol.left = 0x3FFF;
    attr.mvol.right = 0x3FFF;
    SpuSetCommonAttr( &attr );
}

void keyon_80087F58()
{
    keyons_800BF260 |= keyd_800C0524;
}

void keyoff_80087F80()
{
    keyoffs_800BF29C |= keyd_800C0524;
}

void tone_set_80087FA8( unsigned char a1 )
{
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_10_addr = voice_tbl_800C0530[ a1 ].field_0_addr;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_14_addr_fg = 1;
    sptr_800C057C->field_D0_macro = voice_tbl_800C0530[ a1 ].field_4_sample_note;
    sptr_800C057C->field_D1_micro = voice_tbl_800C0530[ a1 ].field_5_sample_tune;

    if ( voice_tbl_800C0530[ a1 ].field_6_a_mode )
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_18_a_mode = 5;
    }
    else
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_18_a_mode = 1;
    }

    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_1C_ar = ~voice_tbl_800C0530[ a1 ].field_7_ar & 0x7F;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_1E_dr = ~voice_tbl_800C0530[ a1 ].field_8_dr & 0xF;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_20_env1_fg = 1;

    switch ( voice_tbl_800C0530[ a1 ].field_9_s_mode )
    {
    case 0:
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_24_s_mode = 3;
        break;

    case 1:
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_24_s_mode = 7;
        break;

    case 2:
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_24_s_mode = 1;
        break;

    default:
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_24_s_mode = 5;
        break;
    }

    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_28_sr = ~voice_tbl_800C0530[ a1 ].field_A_sr & 0x7F;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_2A_sl = voice_tbl_800C0530[ a1 ].field_B_sl & 0xF;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_2C_env2_fg = 1;

    if ( !voice_tbl_800C0530[ a1 ].field_C_r_mode )
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_30_r_mode = 3;
    }
    else
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_30_r_mode = 7;
    }

    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_34_rr = sptr_800C057C->field_D2_rrd = ~voice_tbl_800C0530[ a1 ].field_D_rr & 0x1F;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_38_env3_fg = 1;
    if ( !sptr_800C057C->field_56_panmod )
    {
        pan_set2_800882E4( voice_tbl_800C0530[ a1 ].field_E_pan );
    }
    sptr_800C057C->field_AC_dec_vol = (unsigned char)voice_tbl_800C0530[ a1 ].field_F_decl_vol;
}

void pan_set2_800882E4( unsigned char a1 )
{
    if ( !sptr_800C057C->field_55 )
    {
        sptr_800C057C->field_54_panf = 2 * a1;
        sptr_800C057C->field_48_pand = a1 << 9;
    }
}

void vol_set_80088320( unsigned int vol )
{
    unsigned int pan;

    if ( ( mtrack_800BF1EC < 13 ) ||
         ( se_playing_800BF068[ mtrack_800BF1EC - 13 ].field_1_kind == 0 ) )
    {
        if ( vol >= sptr_800C057C->field_AC_dec_vol )
        {
            vol -= sptr_800C057C->field_AC_dec_vol;
        }
        else
        {
            vol = 0;
        }

        pan = sptr_800C057C->field_48_pand >> 8;

        if ( pan > 40 )
        {
            pan = 40;
        }

        if ( dword_800C050C != 0 )
        {
            pan = 20;
        }

        if ( mtrack_800BF1EC < 13 )
        {
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_2_vol_r = ( vol * pant_8009FA60[ pan ] * fade_unk_1_800C0BC8[ mtrack_800BF1EC ] ) >> 16;
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_0_vol_l = ( vol * pant_8009FA60[ 40 - pan ] * fade_unk_1_800C0BC8[ mtrack_800BF1EC ] ) >> 16;
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_4_vol_fg = 1;
        }
        else
        {
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_2_vol_r = vol * pant_8009FA60[ pan ];
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_0_vol_l = vol * pant_8009FA60[ 40 - pan ];
            spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_4_vol_fg = 1;
        }
    }
    else
    {
        if ( vol >= sptr_800C057C->field_AC_dec_vol )
        {
            vol -= sptr_800C057C->field_AC_dec_vol;
        }
        else
        {
            vol = 0;
        }

        pan = se_pan_800BF180[ mtrack_800BF1EC + 1 ];
        vol = ( vol * se_pan_800BF1B8[ mtrack_800BF1EC + 1 ] ) >> 16;

        if ( dword_800C050C != 0 )
        {
            pan = 32;
        }

        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_2_vol_r = vol * se_pant_8009FB04[ pan ];
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_0_vol_l = vol * se_pant_8009FB04[ 64 - pan ];
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_4_vol_fg = 1;
    }
}

void freq_set_800885D4( unsigned int a1 )
{
    unsigned char temp, temp2, temp3, temp4;
    int           temp5;
    int          *temp6;

    a1 += (signed char)sptr_800C057C->field_D1_micro;
    temp4 = a1;
    temp3 = ( a1 >> 8 ) + sptr_800C057C->field_D0_macro;
    temp3 &= 0x7F;
    temp6 = freq_tbl_8009FC08;
    temp5 = temp6[ temp3 + 1 ] - temp6[ temp3 ];

    if ( temp5 & 0x8000 )
    {
        temp5 = 0xC9;
    }

    temp = temp5;
    temp2 = temp5 >> 8;
    temp5 = ( ( temp * temp4 ) >> 8 ) + ( temp2 * temp4 );
    temp5 += temp6[ temp3 ];

    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_8_pitch = temp5;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_C_pitch_fg = 1;
}

void drum_set_80088694( unsigned char a1 )
{
    unsigned char addend = byte_800C056C + 0xB8;
    a1 += addend;
    tone_set_80087FA8( a1 );
}

// TODO: Might be part of sd_cli.c or another file
// from here on
int sd_task_active_800886C4( void )
{
    if ( sd_flags_800C0BFC & 0x80 )
    {
        return 1;
    }

    return 0;
}

int sd_str_play_800886DC( void )
{
    return gStr_FadeOut1_800BF16C > 4;
}

int SD_800886F4( void )
{
    return sng_status_800BF158 > 2;
}

int sub_8008870C()
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = (unsigned int)song_end_800C04E8 >> 13; // TODO: Fix type
    for ( i = 0; i < 8; i++ )
    {
        if ( ( bits & 1 ) == 0 && se_playing_800BF068[ i ].field_0_pri != 255 )
        {
            return se_playing_800BF068[ i ].field_8_code;
        }
        bits >>= 1;
    }
    return 0;
}

int sub_8008877C()
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = (unsigned int)song_end_800C04E8 >> 13; // TODO: Fix type
    for ( i = 0; i < 8; i++ )
    {
        if ( ( bits & 1 ) == 0 && se_playing_800BF068[ i ].field_0_pri == 255 )
        {
            return se_playing_800BF068[ i ].field_8_code;
        }
        bits >>= 1;
    }
    return 0;
}
