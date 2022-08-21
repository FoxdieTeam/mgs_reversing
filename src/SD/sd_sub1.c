#include "SD/sd.h"

void vol_set_80088320(unsigned int a1);

unsigned char rdm_tbl_8009F9BC[129];
extern SOUND_W* sptr_800C057C;
extern SPU_TRACK_REG spu_tr_wk_800C0658[23];
extern unsigned int mtrack_800BF1EC;

unsigned int random_80086B84();

#pragma INCLUDE_ASM("asm/SD/SD_80085A50.s") // 308 bytes
#pragma INCLUDE_ASM("asm/SD/tx_read_80085B84.s") // 340 bytes
#pragma INCLUDE_ASM("asm/SD/note_set_80085CD8.s") // 192 bytes

void adsr_reset_80085D98()
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_34_rr = sptr_800C057C->field_D2_rrd;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_38_env3_fg = 1;
}

#pragma INCLUDE_ASM("asm/SD/note_compute_80085DE0.s") // 440 bytes
#pragma INCLUDE_ASM("asm/SD/swpadset_80085F98.s") // 180 bytes
#pragma INCLUDE_ASM("asm/SD/SD_8008604C.s") // 332 bytes

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

#pragma INCLUDE_ASM("asm/sub_80086220.s") // 96 bytes

void keych_80086280()
{
    int field_57_swpc; // $a0
    int bSetFreq; // $s1
    int field_58_swphc; // $v0
    int field_80_vibdm; // $a1
    int computed_vib; // $s0
    int field_70_vibhc; // $v1
    int rnd; // $v0

    if ( (unsigned char)sptr_800C057C->field_7_ngg < 0x64u
      && sptr_800C057C->field_4_ngc == 1
      && (unsigned short)sptr_800C057C->field_D2_rrd >= 8u )
    {
        spu_tr_wk_800C0658[mtrack_800BF1EC].field_34_rr = 7;
        spu_tr_wk_800C0658[mtrack_800BF1EC].field_38_env3_fg = 1;
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
                if ( !((field_57_swpc - 1) & 0xFF) )
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
                    
                    sptr_800C057C->field_7C_vibd = sptr_800C057C->field_7C_vibd + sptr_800C057C->field_88_vibad;
                }
                else
                {
                    sptr_800C057C->field_7C_vibd = sptr_800C057C->field_88_vibad;
                }
                ++sptr_800C057C->field_7A;
            }
            sptr_800C057C->field_74_vib_tmp_cnt = sptr_800C057C->field_74_vib_tmp_cnt + sptr_800C057C->field_86_vibcad;
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

#pragma INCLUDE_ASM("asm/SD/por_compute_80086504.s") // 200 bytes
#pragma INCLUDE_ASM("asm/SD/vib_compute_800865CC.s") // 200 bytes
#pragma INCLUDE_ASM("asm/sub_80086694.s") // 160 bytes
#pragma INCLUDE_ASM("asm/SD/SD_80086734.s") // 312 bytes
#pragma INCLUDE_ASM("asm/SD/note_cntl_8008686C.s") // 792 bytes

unsigned int random_80086B84()
{
    unsigned int temp = 0; // $a1
    unsigned char temp2;

    if ( sptr_800C057C->field_94_rdms )
    {
        sptr_800C057C->field_8C_rdmc += sptr_800C057C->field_94_rdms;
        if ( sptr_800C057C->field_8C_rdmc > 256 )
        {
            sptr_800C057C->field_8C_rdmc &= 255;
            sptr_800C057C->field_90_rdmo++;
            sptr_800C057C->field_90_rdmo &= 0x7F;
            temp2 = rdm_tbl_8009F9BC[sptr_800C057C->field_90_rdmo];
            temp = rdm_tbl_8009F9BC[sptr_800C057C->field_90_rdmo+1] << 8;
            temp += temp2;
            temp &= sptr_800C057C->field_98_rdmd;
        }
    }
    return temp;
}

void tempo_ch_80086C08()
{
    if (  sptr_800C057C->field_C0_tmpc )
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

void volxset_80086C98(unsigned char a1)
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
    temp2 = (sptr_800C057C->field_38_pvod >> 8) & 0xFF;
    vol_set_80088320(((temp2 * temp) >> 8) & 0xFF);
}
