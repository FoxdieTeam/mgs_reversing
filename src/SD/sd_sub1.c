#include "SD/sd.h"

void                  note_compute_80085DE0();

unsigned char         rdm_tbl_8009F9BC[ 129 ];
extern SOUND_W       *sptr_800C057C;
extern SPU_TRACK_REG  spu_tr_wk_800C0658[ 23 ];
extern unsigned int   mtrack_800BF1EC;
extern unsigned int   mdata1_800BF0D0;
extern int            mdata2_800BF0D4;
extern int            mdata3_800BF0D8;
extern int            mdata4_800BF0DC;
extern int            sng_fade_in_2_800C0BC0;
extern int            key_fg_800BF1B0;
extern unsigned char *mptr_800C0570;

extern TMDXFunc       gMdxTable_8009F7BC[];
extern unsigned char  VIBX_TBL_8009FA40[ 32 ];

unsigned int          random_80086B84();
void                  note_set_80085CD8();
void                  tempo_ch_80086C08();
void                  keych_80086280();
int                   tx_read_80085B84();
void                  bendch_80086734();
void                  vol_compute_8008604C();
void                  note_cntl_8008686C();
void                  keyon_80087F58();

inline int            vib_compute_800865CC();
inline void           por_compute_80086504();
inline void           swpadset_80085F98( int a1 );

int SD_80085A50()
{
    int          fade2_shifted; // $a0
    unsigned int tmpd;          // $a1

    key_fg_800BF1B0 = 0;
    sptr_800C057C->field_B4_tmpd += sptr_800C057C->field_B8_tmp;
    if ( (unsigned int)mtrack_800BF1EC < 0xD )
    {
        if ( sng_fade_in_2_800C0BC0 )
        {
            fade2_shifted = sng_fade_in_2_800C0BC0 >> 5;
            if ( fade2_shifted < (unsigned char)sptr_800C057C->field_B8_tmp )
            {
                sptr_800C057C->field_B4_tmpd -= fade2_shifted;
            }
        }
    }

    tmpd = sptr_800C057C->field_B4_tmpd;
    if ( tmpd >= 256 )
    {
        sptr_800C057C->field_B4_tmpd = tmpd & 0xff;
        --sptr_800C057C->field_4_ngc;

        if ( sptr_800C057C->field_4_ngc )
        {
            keych_80086280();
        }
        else if ( tx_read_80085B84() )
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

    if ( key_fg_800BF1B0 )
    {
        keyon_80087F58();
        return 0;
    }
    return 0;
}

int tx_read_80085B84()
{
    int bContinue; // $s0
    int i;         // $s1

    i = 0;
    bContinue = 1;
    while ( bContinue )
    {
        i++;
        if ( i == 256 )
        {
            return 1;
        }

        mdata1_800BF0D0 = mptr_800C0570[ 3 ];
        if ( !mdata1_800BF0D0 )
        {
            return 1;
        }
        mdata2_800BF0D4 = mptr_800C0570[ 2 ];
        mdata3_800BF0D8 = mptr_800C0570[ 1 ];
        mdata4_800BF0DC = mptr_800C0570[ 0 ];
        mptr_800C0570 += 4;

        if ( (char)mdata1_800BF0D0 >= 128 )
        {
            gMdxTable_8009F7BC[ mdata1_800BF0D0 - 128 ]();
            if ( mdata1_800BF0D0 == 0xF2 || mdata1_800BF0D0 == 0xF3 || mdata1_800BF0D0 == 0xFF )
            {
                bContinue = 0;
            }

            if ( mdata1_800BF0D0 == 0xFF )
            {
                return 1;
            }
        }
        else
        {
            if ( (unsigned char)sptr_800C057C->field_7_ngg < 0x64 && mdata4_800BF0DC )
            {
                key_fg_800BF1B0 = 1;
            }
            bContinue = 0;
            sptr_800C057C->field_CC_rest_fg = 0;
            note_set_80085CD8();
        }
    }
    return 0;
}

void note_set_80085CD8()
{
    unsigned int temp;

    sptr_800C057C->field_6_ngs = mdata2_800BF0D4;
    sptr_800C057C->field_7_ngg = mdata3_800BF0D8;
    sptr_800C057C->field_44_vol = ( mdata4_800BF0DC & 0x7F );
    note_compute_80085DE0();
    sptr_800C057C->field_4_ngc = sptr_800C057C->field_6_ngs;
    temp = ( sptr_800C057C->field_7_ngg * sptr_800C057C->field_4_ngc ) / 100;

    if ( !temp )
    {
        temp = 1;
    }
    sptr_800C057C->field_5_ngo = temp;
}

void adsr_reset_80085D98()
{
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_34_rr = sptr_800C057C->field_D2_rrd;
    spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_38_env3_fg = 1;
}

void note_compute_80085DE0()
{
    int      newswpd;
    int      oldswpd;
    SOUND_W *pSound;

    if (mdata1_800BF0D0 >= 0x48)
    {
        drum_set_80088694(mdata1_800BF0D0);
        newswpd = 0x24;
    }
    else
    {
        newswpd = mdata1_800BF0D0;
    }

    newswpd += sptr_800C057C->field_A8_ptps;
    newswpd = (newswpd << 8) + sptr_800C057C->field_B0_tund;
    newswpd = newswpd + sptr_800C057C->field_14_lp1_freq + sptr_800C057C->field_18_lp2_freq;

    while (newswpd >= 0x6000)
    {
        newswpd -= 0x6000;
    }

    oldswpd = sptr_800C057C->field_5C_swpd;

    pSound = sptr_800C057C;
    pSound->field_7A = 0;
    pSound->field_70_vibhc = 0;
    pSound->field_5C_swpd = newswpd;

    sptr_800C057C->field_74_vib_tmp_cnt = 0;
    sptr_800C057C->field_78_vib_tbl_cnt = 0;

    pSound = sptr_800C057C;
    pSound->field_9D_trehc = 0;
    pSound->field_9C_trec = 0;
    pSound->field_7C_vibd = 0;

    spu_tr_wk_800C0658[mtrack_800BF1EC].field_34_rr = sptr_800C057C->field_D2_rrd;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_38_env3_fg = 1;

    sptr_800C057C->field_57_swpc = sptr_800C057C->field_68_swsc;

    if (sptr_800C057C->field_57_swpc != 0)
    {
        sptr_800C057C->field_58_swphc = sptr_800C057C->field_69_swshc;

        if (sptr_800C057C->field_6A_swsk == 0)
        {
            newswpd = sptr_800C057C->field_5C_swpd;

            if (sptr_800C057C->field_6C_swss >= 0x7F01)
            {
                sptr_800C057C->field_5C_swpd += 0x10000 - (sptr_800C057C->field_6C_swss & 0xFFFF);
            }
            else
            {
                sptr_800C057C->field_5C_swpd -= sptr_800C057C->field_6C_swss;
            }

            swpadset_80085F98(newswpd);
        }
        else
        {
            sptr_800C057C->field_64_swpm = sptr_800C057C->field_5C_swpd;
            sptr_800C057C->field_5C_swpd = oldswpd;
        }
    }

    freq_set_800885D4(sptr_800C057C->field_5C_swpd);
}

inline void swpadset_80085F98( int a1 )
{
    unsigned int temp; // $lo

    if ( sptr_800C057C->field_57_swpc )
    {
        temp = sptr_800C057C->field_57_swpc << 8;
        temp = temp / sptr_800C057C->field_B8_tmp;
        if ( a1 < 0 )
        {
            a1 = 0;
        }
        else if ( a1 >= 0x6000 )
        {
            a1 = 0x5FFF;
        }

        sptr_800C057C->field_64_swpm = a1;

        a1 -= sptr_800C057C->field_5C_swpd;

        if ( a1 < 0 )
        {
            a1 = -a1 / temp;
            sptr_800C057C->field_60_swpad = -a1;
        }
        else
        {
            sptr_800C057C->field_60_swpad = a1 / temp;
        }
    }
}

void vol_compute_8008604C()
{
    int          mult;
    unsigned int vol;

    if (sptr_800C057C->field_34_pvoc != 0)
    {
        if (--sptr_800C057C->field_34_pvoc == 0)
        {
            sptr_800C057C->field_38_pvod = sptr_800C057C->field_40_pvom << 8;
        }
        else
        {
            sptr_800C057C->field_38_pvod += sptr_800C057C->field_3C_pvoad;
        }
    }

    if (sptr_800C057C->field_44_vol != 0)
    {
        if (sptr_800C057C->field_9E_tred == 0)
        {
            vol = 0;
        }
        else
        {
            if (sptr_800C057C->field_A0_trehs == sptr_800C057C->field_9D_trehc)
            {
                sptr_800C057C->field_9C_trec += sptr_800C057C->field_9F_trecad;
                mult = sptr_800C057C->field_9C_trec;
                if (mult < 0)
                {
                    vol = sptr_800C057C->field_9E_tred * -mult;
                }
                else if (mult == 0)
                {
                    vol = 1;
                }
                else
                {
                    vol = sptr_800C057C->field_9E_tred * mult;
                }
            }
            else
            {
                sptr_800C057C->field_9D_trehc++;
                vol = 0;
            }
        }
        volxset_80086C98(vol >> 8);
    }
    pan_generate_80086198();
}

void pan_generate_80086198()
{
    if ( sptr_800C057C->field_45_panc )
    {
        if ( !--sptr_800C057C->field_45_panc )
        {
            sptr_800C057C->field_48_pand = sptr_800C057C->field_50_panm;
        }
        else
        {
            sptr_800C057C->field_48_pand += sptr_800C057C->field_4C_panad;
        }
        sptr_800C057C->field_54_panf = sptr_800C057C->field_48_pand >> 8;
    }
}

void sub_80086220()
{
    if ( sptr_800C057C->field_D2_rrd > 7 )
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_34_rr = 7;
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_38_env3_fg = 1;
    }
}

void keych_80086280()
{
    int field_57_swpc;  // $a0
    int bSetFreq;       // $s1
    int field_58_swphc; // $v0
    int field_80_vibdm; // $a1
    int computed_vib;   // $s0
    int field_70_vibhc; // $v1
    int rnd;            // $v0

    if ( (unsigned char)sptr_800C057C->field_7_ngg < 0x64u && sptr_800C057C->field_4_ngc == 1 &&
         (unsigned short)sptr_800C057C->field_D2_rrd >= 8u )
    {
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_34_rr = 7;
        spu_tr_wk_800C0658[ mtrack_800BF1EC ].field_38_env3_fg = 1;
    }

    if ( sptr_800C057C->field_5_ngo )
    {
        sptr_800C057C->field_5_ngo--;
        if ( !sptr_800C057C->field_5_ngo )
        {
            keyoff_80087F80();
        }
    }

    bSetFreq = 0;

    field_57_swpc = sptr_800C057C->field_57_swpc;
    if ( field_57_swpc )
    {
        field_58_swphc = (unsigned char)sptr_800C057C->field_58_swphc;
        if ( field_58_swphc )
        {
            sptr_800C057C->field_58_swphc--;
        }
        else
        {
            if ( !sptr_800C057C->field_6A_swsk )
            {
                sptr_800C057C->field_57_swpc = field_57_swpc - 1;
                if ( !( ( field_57_swpc - 1 ) & 0xFF ) )
                {
                    sptr_800C057C->field_5C_swpd = sptr_800C057C->field_64_swpm;
                }
                else
                {
                    sptr_800C057C->field_5C_swpd += sptr_800C057C->field_60_swpad;
                }
            }
            else
            {
                por_compute_80086504();
            }
            bSetFreq = 1;
        }
    }

    field_80_vibdm = sptr_800C057C->field_80_vibdm;
    computed_vib = 0;

    if ( field_80_vibdm )
    {
        field_70_vibhc = (unsigned char)sptr_800C057C->field_70_vibhc;
        if ( field_70_vibhc != (unsigned char)sptr_800C057C->field_84_vibhs )
        {
            sptr_800C057C->field_70_vibhc = field_70_vibhc + 1;
        }
        else
        {
            if ( sptr_800C057C->field_7A == sptr_800C057C->field_85_vibcs )
            {
                sptr_800C057C->field_7C_vibd = field_80_vibdm;
            }
            else
            {
                if ( sptr_800C057C->field_7A )
                {
                    sptr_800C057C->field_7C_vibd =
                        sptr_800C057C->field_7C_vibd + sptr_800C057C->field_88_vibad;
                }
                else
                {
                    sptr_800C057C->field_7C_vibd = sptr_800C057C->field_88_vibad;
                }
                ++sptr_800C057C->field_7A;
            }
            sptr_800C057C->field_74_vib_tmp_cnt =
                sptr_800C057C->field_74_vib_tmp_cnt + sptr_800C057C->field_86_vibcad;
            if ( (unsigned)sptr_800C057C->field_74_vib_tmp_cnt >= 256 )
            {
                sptr_800C057C->field_74_vib_tmp_cnt = sptr_800C057C->field_74_vib_tmp_cnt & 0xFF;
                computed_vib = vib_compute_800865CC();
                bSetFreq = 1;
            }
        }
    }

    rnd = random_80086B84();
    if ( rnd )
    {
        computed_vib += rnd;
        bSetFreq = 1;
    }

    if ( bSetFreq )
    {
        freq_set_800885D4( sptr_800C057C->field_5C_swpd + computed_vib );
    }
}

inline void por_compute_80086504()
{
    int          temp; // $a1
    unsigned int temp2;
    unsigned int temp3;

    temp = sptr_800C057C->field_64_swpm - sptr_800C057C->field_5C_swpd;
    if ( temp < 0 )
    {
        temp = -temp;
        temp3 = temp & 0xFF;
        temp2 = temp >> 8;
        temp3 = ( temp3 * sptr_800C057C->field_68_swsc ) >> 8;
        temp2 *= sptr_800C057C->field_68_swsc;
        temp = temp2 + temp3;

        if ( temp == 0 )
        {
            temp = 1;
        }
        temp = -temp;
    }
    else if ( temp == 0 )
    {
        sptr_800C057C->field_57_swpc = 0;
    }
    else
    {
        temp3 = temp & 0xFF;
        temp2 = temp >> 8;
        temp3 = ( temp3 * sptr_800C057C->field_68_swsc ) >> 8;
        temp2 *= sptr_800C057C->field_68_swsc;
        temp = temp2 + temp3;

        if ( temp == 0 )
        {
            temp = 1;
        }
    }

    sptr_800C057C->field_5C_swpd += temp;
}

inline int vib_compute_800865CC()
{
    unsigned int vibd;  // $a0
    int          temp2; // $a1
    unsigned int temp;  // $v1

    sptr_800C057C->field_78_vib_tbl_cnt += sptr_800C057C->field_79_vib_tc_ofst;
    sptr_800C057C->field_78_vib_tbl_cnt &= 0x3Fu;
    temp2 = VIBX_TBL_8009FA40[ sptr_800C057C->field_78_vib_tbl_cnt & 0x1F ];

    vibd = sptr_800C057C->field_7C_vibd;
    if ( 0x7FFF >= vibd )
    {
        temp = ( ( vibd >> 7 ) & 0xFE );
        temp = ( temp * temp2 ) >> 8;
    }
    else
    {
        temp = ( ( vibd >> 8 ) & 0x7F ) + 2;
        temp = ( temp * temp2 ) >> 1;
    }

    if ( (unsigned char)sptr_800C057C->field_78_vib_tbl_cnt >= 32u )
    {
        temp = -temp;
    }

    return temp;
}

int sub_80086694( int param_1 )
{
    unsigned char uVar1;
    int           ret;

    if ( param_1 << 0x18 < 0 )
    {
        uVar1 = -param_1 * 2;
        if ( ( -param_1 << 0x19 ) < 0 )
        {
            uVar1 = -uVar1;
        }
        ret = ((char*)&sptr_800C057C->field_7C_vibd)[1] * ( uVar1 / 4 );
        ret = -ret;
    }
    else
    {
        uVar1 = param_1 * 2;
        if ( param_1 << 0x19 < 0 )
        {
            uVar1 = -uVar1;
        }
        ret = ((char*)&sptr_800C057C->field_7C_vibd)[1] * ( uVar1 / 4 );
    }
    if ( *(unsigned int *)&sptr_800C057C->field_80_vibdm < 0x8000 )
    {
        ret >>= 2;
    }
    return ret;
}

void bendch_80086734()
{
    int arg1;

    if (!sptr_800C057C->field_57_swpc)
    {
        mdata1_800BF0D0 = mptr_800C0570[3];
        if (mdata1_800BF0D0 == 0xe4)
        {
            sptr_800C057C->field_58_swphc = mptr_800C0570[2];
            sptr_800C057C->field_57_swpc = mptr_800C0570[1];
            arg1 = mptr_800C0570[0];
            mptr_800C0570 += 4;

            arg1 = (arg1 + sptr_800C057C->field_A8_ptps) << 8;
            arg1 += sptr_800C057C->field_B0_tund;

            swpadset_80085F98(arg1);
        }
    }
}

void note_cntl_8008686C()
{
    int            randomval;
    int            set_freq;
    unsigned int   vol;
    int            swpd;

    if (sptr_800C057C->field_44_vol != 0 && sptr_800C057C->field_9E_tred != 0 &&
        sptr_800C057C->field_A0_trehs == sptr_800C057C->field_9D_trehc)
    {
        sptr_800C057C->field_9C_trec +=
            (unsigned)(sptr_800C057C->field_9F_trecad * (char)sptr_800C057C->field_B4_tmpd) >> 8;

        if (sptr_800C057C->field_9C_trec < 0)
        {
            vol = sptr_800C057C->field_9E_tred * -sptr_800C057C->field_9C_trec;
        }
        else if (sptr_800C057C->field_9C_trec == 0)
        {
            vol = 1;
        }
        else
        {
            vol = sptr_800C057C->field_9E_tred * sptr_800C057C->field_9C_trec;
        }

        volxset_80086C98(vol >> 8);
    }

    set_freq = 0;
    swpd = sptr_800C057C->field_5C_swpd;

    if (sptr_800C057C->field_57_swpc != 0 && sptr_800C057C->field_58_swphc == 0)
    {
        set_freq = 1;

        if (sptr_800C057C->field_6A_swsk == 0)
        {
            sptr_800C057C->field_5C_swpd += sptr_800C057C->field_60_swpad;
        }
        else
        {
            por_compute_80086504();
        }

        swpd = sptr_800C057C->field_5C_swpd;
    }

    if (sptr_800C057C->field_7C_vibd != 0 && sptr_800C057C->field_84_vibhs == sptr_800C057C->field_70_vibhc)
    {
        sptr_800C057C->field_74_vib_tmp_cnt += sptr_800C057C->field_86_vibcad;
        if ((unsigned)sptr_800C057C->field_74_vib_tmp_cnt >= 256)
        {
            sptr_800C057C->field_74_vib_tmp_cnt &= 0xFF;
            swpd += vib_compute_800865CC();
            set_freq = 1;
        }
    }

    randomval = random_80086B84();

    if (randomval != 0)
    {
        set_freq = 1;
        swpd += randomval;
    }

    if (set_freq)
    {
        freq_set_800885D4(swpd);
    }
}

unsigned int random_80086B84()
{
    unsigned int  temp = 0; // $a1
    unsigned char temp2;

    if ( sptr_800C057C->field_94_rdms )
    {
        sptr_800C057C->field_8C_rdmc += sptr_800C057C->field_94_rdms;
        if ( sptr_800C057C->field_8C_rdmc > 256 )
        {
            sptr_800C057C->field_8C_rdmc &= 255;
            sptr_800C057C->field_90_rdmo++;
            sptr_800C057C->field_90_rdmo &= 0x7F;
            temp2 = rdm_tbl_8009F9BC[ sptr_800C057C->field_90_rdmo ];
            temp = rdm_tbl_8009F9BC[ sptr_800C057C->field_90_rdmo + 1 ] << 8;
            temp += temp2;
            temp &= sptr_800C057C->field_98_rdmd;
        }
    }
    return temp;
}

void tempo_ch_80086C08()
{
    if ( sptr_800C057C->field_C0_tmpc )
    {
        if ( !--sptr_800C057C->field_C0_tmpc )
        {
            sptr_800C057C->field_C4_tmpw = (unsigned char)sptr_800C057C->field_C8_tmpm << 8;
        }
        else
        {
            sptr_800C057C->field_C4_tmpw += sptr_800C057C->field_BC_tmpad;
        }
        sptr_800C057C->field_B8_tmp = (unsigned int)sptr_800C057C->field_C4_tmpw >> 8;
    }
}

void volxset_80086C98( unsigned char a1 )
{
    int temp; // $a1
    int temp2;

    temp = sptr_800C057C->field_44_vol;
    temp -= a1;
    temp += sptr_800C057C->field_C_lp1_vol;
    temp += sptr_800C057C->field_10_lp2_vol;
    if ( temp < 0 )
    {
        temp = 0;
    }
    else if ( temp >= 128 )
    {
        temp = 127;
    }
    temp2 = ( sptr_800C057C->field_38_pvod >> 8 ) & 0xFF;
    vol_set_80088320( ( ( temp2 * temp ) >> 8 ) & 0xFF );
}
