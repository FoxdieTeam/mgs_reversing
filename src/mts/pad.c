#include "linker.h"
#include "mts_new.h"
#include "psyq.h"

extern char          gMtsPadActBuffers_800C1470[2][6];
extern unsigned char gMtsPadRecvBuffers_800C1480[2][36];
extern int           gMtsPadInitStates_800C14F0[2];
extern unsigned char gMtsPadSendBuffers_800C14D0[2][8];

extern int gMtsPadInited_800A3DBC;
extern int dword_800A3DC8;

void mts_init_controller_actuators_8008BC8C(int pad)
{
    int port;
    int act;
    int i;
    int func, subfunc, size;

    port = pad * 16;
    act = PadInfoAct_8009A47C(port, -1, 0);

    for (i = 0; i < 6; i++)
    {
        gMtsPadActBuffers_800C1470[pad][i] = 0xFF;
    }

    for (i = act - 1; i >= 0; i--)
    {
        func = PadInfoAct_8009A47C(port, i, InfoActFunc);
        subfunc = PadInfoAct_8009A47C(port, i, InfoActSub);
        size = PadInfoAct_8009A47C(port, i, InfoActSize);

        if (func != 1)
        {
            continue;
        }

        if ((subfunc == 1) && (size == 1))
        {
            gMtsPadActBuffers_800C1470[pad][1] = i;
            continue;
        }

        if ((subfunc == 2) && (size == 0))
        {
            gMtsPadActBuffers_800C1470[pad][0] = i;
        }
    }

    PadSetActAlign_8009A5F8(port, gMtsPadActBuffers_800C1470[pad]);
}

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

unsigned char * mts_get_controller_data_8008C380(int pad)
{
    int buffer;

    buffer = pad;
    if (pad == 0)
    {
        if (gMtsPadRecvBuffers_800C1480[0][0] == 0)
        {
            buffer = 1;
        }
        else
        {
            buffer = 2;
        }
    }

    return gMtsPadRecvBuffers_800C1480[buffer - 1];
}

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
