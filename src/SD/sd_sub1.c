#include "SD/sd.h"

void vol_set_80088320(unsigned int a1);

unsigned char rdm_tbl_8009F9BC[129];
extern SOUND_W* sptr_800C057C;

#pragma INCLUDE_ASM("asm/SD/SD_80085A50.s")
#pragma INCLUDE_ASM("asm/SD/tx_read_80085B84.s")
#pragma INCLUDE_ASM("asm/SD/note_set_80085CD8.s")
#pragma INCLUDE_ASM("asm/sub_80085D98.s")
#pragma INCLUDE_ASM("asm/SD/note_compute_80085DE0.s")
#pragma INCLUDE_ASM("asm/SD/swpadset_80085F98.s")
#pragma INCLUDE_ASM("asm/SD/SD_8008604C.s")
#pragma INCLUDE_ASM("asm/SD/SD_80086198.s")
#pragma INCLUDE_ASM("asm/sub_80086220.s")
#pragma INCLUDE_ASM("asm/SD/SD_80086280.s")
#pragma INCLUDE_ASM("asm/SD/SD_80086504.s")
#pragma INCLUDE_ASM("asm/SD/vib_compute_800865CC.s")
#pragma INCLUDE_ASM("asm/sub_80086694.s")
#pragma INCLUDE_ASM("asm/SD/SD_80086734.s")
#pragma INCLUDE_ASM("asm/SD/note_cntl_8008686C.s")

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

#pragma INCLUDE_ASM("asm/SD/tempo_ch_80086C08.s")

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
