#include "common.h"

typedef struct JeepWork {
    unsigned char  field_0_pad[40];         
    unsigned char  control_dummy[124];      
    unsigned char  field_A4_pad[804];       
    short          field_3C8_current_speed; 
    short          field_3CA_target_speed;  
    int            field_3CC_timer;         
    int            field_3D0_unk;           
    unsigned char  field_3D4_pad[1044];     
    void          *field_7E8_target;        
} JeepWork;

extern int s19b_dword_800DE64C;
extern int rand(void);

void s19b_jeep_mrl_800D2CE8(JeepWork *work);
void s19b_jeep_mrl_800D2D3C(JeepWork *work);

int GV_NearSpeed(int current_speed, int target_speed, int step_modifier);

void GM_FreeTarget(void *target);
void GM_FreeControl(void *control);
void GM_FreeObject(void *object);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2CE8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D2E78.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D32B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D368C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D36A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D37D0.s")

void rpk_jeep_speed_logic(JeepWork *work)
{
    int rand_val;
    int target_speed;

    s19b_jeep_mrl_800D2CE8(work);
    s19b_jeep_mrl_800D2D3C(work);

    if ((work->field_3CC_timer & 0x3F) == 0) {
        rand_val = rand(); 

        target_speed = (((rand_val * 16) - rand_val) * 4) >> 15;
        work->field_3CA_target_speed = target_speed - 600;
    }

    work->field_3C8_current_speed = GV_NearSpeed(
        work->field_3C8_current_speed,
        work->field_3CA_target_speed,
        30
    );
}

int s19b_jeep_mrl_800D399C(void)
{
    return ((JeepWork *)s19b_dword_800DE64C)->field_3D0_unk;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D39B4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D39F0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3A54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3CA8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3D30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D3E98.s")

void s19b_jeep_mrl_800D4098(JeepWork *work)
{
    GM_FreeTarget(work->field_7E8_target);
    GM_FreeControl(&work->control_dummy);
    GM_FreeObject((unsigned char *)work + 0xA4);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_mrl_800D40D4.s")
