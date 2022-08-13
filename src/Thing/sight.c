#include "sight.h"
#include "libgv/libgv.h"

// used for all first person HUDs

extern int dword_8009F608;

void sight_act_helper_8007111C(void)
{
    int     message_result;
    GV_MSG *message;

    message_result = GV_ReceiveMessage_80016620(0x30da, &message);

    if (message_result > 0)
    {
        while (--message_result > -1)
        {
            switch (message->message[0])
            {
            case 0xe4e:
                dword_8009F608 &= ~1;
                break;
            case 0xc927:
                dword_8009F608 |= 1;
                break;
            }

            message++;
        }
    }
}

#pragma INCLUDE_ASM("asm/Thing/sight_800711C0.s")            // 352 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_helper_80071320.s") // 220 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_helper_800713FC.s") // 156 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_helper_80071498.s") // 84 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_800714EC.s")        // 1244 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_kill_800719C8.s")       // 140 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_loader_80071A54.s")     // 648 bytes
#pragma INCLUDE_ASM("asm/Thing/NewSight_80071CDC.s")         // 236 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_init_80071DC8.s")       // 224 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_init_80071EA8.s")       // 240 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_init_80071F98.s")       // 220 bytes

extern short word_8009F5FC;

void sub_80072074()
{
    word_8009F5FC = 0;
}
