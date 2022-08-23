#include "linker.h"
#include "mts_new.h"
#include "psyq.h"

extern unsigned char gMtsPadRecvBuffers_800C1480[2][36];
extern int           gMtsPadInitStates_800C14F0[2];
extern unsigned char gMtsPadSendBuffers_800C14D0[2][8];

extern int gMtsPadInited_800A3DBC;
extern int dword_800A3DC8;

#pragma INCLUDE_ASM("asm/mts/mts_8008BC8C.s")                     // 352 bytes
#pragma INCLUDE_ASM("asm/mts/mts_callback_controller_8008BDEC.s") // 684 bytes

void mts_init_controller_8008C098(void)
{
    if (gMtsPadInited_800A3DBC == 0)
    {
        PadInitDirect_8009C6CC(gMtsPadRecvBuffers_800C1480[0], gMtsPadRecvBuffers_800C1480[1]);
        PadSetAct_8009A678(0, gMtsPadSendBuffers_800C14D0[0], 8);
        PadSetAct_8009A678(0x10, gMtsPadSendBuffers_800C14D0[1], 8);
        PadStartCom_8009A22C();
        gMtsPadInitStates_800C14F0[1] = 1;
        gMtsPadInitStates_800C14F0[0] = 1;
        mts_set_callback_controller_800893D8(mts_callback_controller_8008BDEC);
        gMtsPadInited_800A3DBC = 1;
    }
}

void mts_stop_controller_8008C12C(void)
{
    if (gMtsPadInited_800A3DBC != 0)
    {
        StopPAD_80099F08();
        ChangeClearPAD_8009960C(0);
        mts_set_callback_controller_800893D8(0);
        gMtsPadInited_800A3DBC = 0;
    }
}

#pragma INCLUDE_ASM("asm/mts/mts_get_pad_8008C170.s")             // 236 bytes
#pragma INCLUDE_ASM("asm/mts/mts_read_pad_8008C25C.s")            // 200 bytes
#pragma INCLUDE_ASM("asm/mts/mts_PadRead_8008C324.s")             // 92 bytes
#pragma INCLUDE_ASM("asm/mts/mts_get_controller_data_8008C380.s") // 60 bytes

int mts_control_vibration_8008C3BC(int arg0)
{
    int ret;

    ret = dword_800A3DC8;
    if (arg0 >= 0)
    {
        dword_800A3DC8 = arg0;
    }
    memset(gMtsPadSendBuffers_800C14D0, 0, sizeof(gMtsPadSendBuffers_800C14D0));
    return ret;
}

#pragma INCLUDE_ASM("asm/mts/mts_set_pad_vibration_8008C408.s")      // 76 bytes
#pragma INCLUDE_ASM("asm/mts/mts_set_pad_vibration2_8008C454.s")     // 104 bytes
#pragma INCLUDE_ASM("asm/mts/mts_get_pad_vibration_type_8008C4BC.s") // 120 bytes
