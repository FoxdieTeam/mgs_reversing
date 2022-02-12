#include "linker.h"
#include "mts_new.h"

void PadInitDirect_8009C6CC(unsigned char *pad1, unsigned char *pad2);
void PadSetAct_8009A678(int port, unsigned char *data, int len);
void PadStartCom_8009A22C(void);
void StopPAD_80099F08(void);
void ChangeClearPAD_8009960C(long val);

void mts_set_callback_controller_800893D8(void *ptr);
void mts_callback_controller_8008BDEC(void);

extern int gMtsPadInited_800A3DBC;

unsigned char SECTION(".gMtsPadRecvBuffers_800C1480") gMtsPadRecvBuffers_800C1480[2][36] = {};
int SECTION(".gMtsPadInitStates_800C14F0") gMtsPadInitStates_800C14F0[2] = {};
unsigned char SECTION(".gMtsPadSendBuffers_800C14D0") gMtsPadSendBuffers_800C14D0[2][8] = {};

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
